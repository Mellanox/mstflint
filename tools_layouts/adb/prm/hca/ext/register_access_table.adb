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
<info source_doc_name="Mellanox &lt;Doc Name&gt;" source_doc_version="Rev 0.63" />
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

<node name="MRFV_CVB_ext" descr="" size="0x8.0" >
	<field name="cvb_data_index" descr="[Arcus2]: Index of LUT entry.\;\;[ArcusE]:\;CVB Voltage = -4 + 0.5 * cvb_data_index\;cvb_data_index valid values 0 .. 15\;Process Sigma &lt;-&gt; DVDD (mV)\;-4.0: 856.00\;-3.5: 847.75\;-3.0: 839.50\;-2.5: 831.25\;-2.0: 823.00\;-1.5: 814.75\;-1.0: 806.50\;-0.5: 798.25\;0 (nominal): 790.00\;0.5: 781.75\;1.0: 773.50\;1.5: 765.25\;2.0: 757.00\;2.5: 748.75\;3.0: 740.50\;3.5: 732.25\;4.0: 724.00\;Reserved when selector = 1" access="RO" offset="0x0.0" size="0x0.5" />
	<field name="cnt_out" descr="[DWIP][Internal]\;Valid only if selector = 0.\;The minimum ISM cnt_out value, which is used to determine the selected LUT entry index." access="RO" offset="0x0.6" size="0x0.20" />
	<field name="tav_cvb_voltage_msb" descr="MSB bits of the TAV voltage" access="RO" offset="0x0.26" size="0x0.4" />
	<field name="selector_cause" descr="[DWIP] [Internal]\;Valid only if selector = 1.\;0: Fuses are valid.\;1: Fuses are invalid but LUT entry not located." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="selector" descr="[Arcus]:\;0: cvb_data_index is valid\;1: cvb_voltage is valid\;\;\;[Arcus2]:\;0: cvb_data_index is valid, and cvb_voltage exposes the value in LUT.\;1: cvb_data_index is not valid, and cvb_voltage exposes values from fuses (if selector_cause = 0)." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="cvb_voltage" descr="CVB Voltage\;Returns required CVB voltage in mV.\;\;Reserved when selector = 0" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="voltage_type" descr="The voltage type of the cvb_voltage\;0: DVDD\;1: AVDD\;2: VDD" access="INDEX" offset="0x4.16" size="0x0.3" />
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
	<field name="data" descr="Data\;See Table 3038, &quot;MRFV entry - CVB Layout,&quot; on page 3400\;See Table 3040, &quot;MRFV entry - ULT Layout,&quot; on page 3402\;See Table 3042, &quot;MRFV entry - PVS_MAIN Layout,&quot; on page 3403\;See Table 3044, &quot;MRFV entry - PVS_Tile Layout,&quot; on page 3404\;Reserved when fm = 1" subnode="MRFV_data_auto_ext" access="RO" offset="0x10.0" size="0xc.0" union_selector="$(parent).fuse_id" />
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
	<field name="data" descr="Data\;See Table 2822, &quot;MRSV entry - BF-3 Straps Layout,&quot; on page 3224" subnode="MRSV_data_auto_ext" access="RO" offset="0x10.0" size="0x20.0" union_selector="$(parent).ssid" />
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
	<field name="module" descr="Module number\;NIC: Range 0 .. MGPIR.num_of_modules -1 \;" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="op" descr="Operation\;0: Read only\;1: Clear counters \;2: Read and Clear counters\;3: Reserved" access="OP" offset="0x4.0" size="0x0.2" />
	<field name="abs_max_temp_change" descr="Absolute value of max temperature change between consecutive measurements, in 1C resolution" access="RO" offset="0x4.16" size="0x0.5" />
	<field name="thr_1_cnt" descr="Counter for events when the change in the consecutive temperature measurements crosses threshold_x. Saturated at 0xf value." access="RO" offset="0x8.0" size="0x0.4" />
	<field name="thr_2_cnt" descr="Counter for events when the change in the consecutive temperature measurements crosses threshold_x. Saturated at 0xf value." access="RO" offset="0x8.8" size="0x0.4" />
	<field name="thr_3_cnt" descr="Counter for events when the change in the consecutive temperature measurements crosses threshold_x. Saturated at 0xf value." access="RO" offset="0x8.16" size="0x0.4" />
	<field name="thr_4_cnt" descr="Counter for events when the change in the consecutive temperature measurements crosses threshold_x. Saturated at 0xf value." access="RO" offset="0x8.24" size="0x0.4" />
</node>

<node name="PBWS_reg_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Egress Local port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must be always 0.\;" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="bw_utilization" descr="The percentage of bw, in per-mille units to be used on the port. Must be in the range of min_bw_utilization to 1000.\;The special value of 0x0, means that no bandwidth enforcement is applied." access="RW" offset="0x4.0" size="0x0.10" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to\;the aggregated port only" access="INDEX" offset="0x4.12" size="0x0.4" />
	<field name="min_bw_utilization" descr="The minimum percentage bw" access="RO" offset="0x4.16" size="0x0.7" />
</node>

<node name="PPCR_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port[9:8]\;Reserved for HCA" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number.\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="asymmetry_enable" descr="[DWIP]\;Indicate whether asymmetry is enabled or not.\;\;For HCA, reserved if PPCR.asymmetry_enable_supported=0" access="RO" offset="0x4.30" size="0x0.1" />
	<field name="asymmetry_enable_supported" descr="[DWIP]\;Indicate whether asymmetry_enable supported or not.\;Reserved for switch.\;" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="aggregated_port" descr="Aggregated Port number to be reflected in MAD.\;0 means N/A\;\;Reserved for HCA" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="plane" descr="Plane number to be reflected in MAD.\;0 means N/A\;\;Reserved for HCA" access="RW" offset="0x8.16" size="0x0.3" />
	<field name="split" descr="When planarized  the FW shall respond to Hierarchy Info.Split with the following split value.\;In this use case it represents the split of the APort.\;\;When split = 0, the FW shall send Hierarchy Info without the split field. (meaning it is NA)\;\;When Non planarized (num_of_planes = 0), Hierarchy Info.Split will reflect the actual split value, when 2X- it&apos;ll hold the location within the 4x.\;\;0: NA\;1: Split 1.\;2: Split 2.\;3-7: Reserved\;Reserved for HCA" access="RW" offset="0x8.24" size="0x0.3" />
	<field name="num_of_planes" descr="The number of planes comprising this Aggregated port\;" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="p_type" descr="[DWIP]\;Planarization Type\;0: non planarized\;1: planirized_gen1\;2-7: Reserved" access="RO" offset="0xC.16" size="0x0.3" />
</node>

<node name="access_reg_summary_ctrl_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="id" descr="" subnode="enum_entry" enum="UNIT_PERF_COUNTERS_GLOBAL_CTRL=0x100,UNIT_PERF_COUNTERS_CFG=0x101,UNIT_PERF_COUNTERS_DATA=0x102,MISC_COUNTERS=0x104,Loopback_Control_Register=0x700,DB_TRESHOLD=0x701,DCBX_PARAM=0x4020,DCBX_APPLICATION=0x4021,QPTS=0x4002,QPDPM=0x4013,QSHR=0x4030,QEEC=0x400d,QPDP=0x4007,QPRT=0x4008,QTCT=0x400a,QSPIP=0x400e,QSPCP=0x401e,QHLL=0x4016,QCAM=0x4019,ROCE_ACCL=0x402c,PCAM=0x507f,PCAP=0x5001,PTYS=0x5004,PAOS=0x5006,PLTC=0x5046,PPCNT=0x5008,PIPG=0x5017,PGMR=0x5039,PTER=0x5055,PREI=0x5058,PPRM=0x5059,PMSCR=0x505c,PMLP=0x5002,PMPR=0x5013,PMMP=0x5044,PMCR=0x5045,PEPC=0x5056,PMPT=0x5064,PMPD=0x5065,PLDS=0x5076,PPSC=0x5011,PRTL=0x5014,PPLR=0x5018,PEIR=0x5019,PPLM=0x5023,SLTP=0x5027,SLTPv2=0x502f,SLRG=0x5028,PTASv2=0x502e,SLSIR=0x502c,PDDR=0x5031,PPTT=0x5036,PPRT=0x5037,PMDR=0x503c,PPHCR=0x503e,PPAOS=0x5040,PCNR=0x5050,PPBMP=0x5051,PPBMC=0x5052,SLRED=0x505a,SLLM=0x505b,PEMI=0x5075,SLPRR=0x507b,PLCC=0x505e,PCCT=0x507d,PFLDC=0x5083,PMTU=0x5003,PPAD=0x5005,PFCC=0x5007,PPTB=0x500b,PBMC=0x500c,PGUID=0x5066,PBSR=0x5038,PCMR=0x5041,PPCR=0x504c,PVLS=0x504b,PPCC=0x506e,PBWS=0x5101,SET_NODE=0x6001,POWER_SETTINGS=0x7001,FP_SL_MAP=0x7002,HOST_ENDIANNESS=0x7004,MMDIO=0x9017,MLCR=0x902b,MGCR=0x903a,MJTAG=0x901f,MRSV=0x9164,MTPPS=0x9053,MTUTC=0x9055,MRTC=0x902d,MSMR=0x9058,MRTCQ=0x9182,MTPTM=0x9180,MTCTR=0x9181,MSECQ=0x9155,MSEES=0x9156,MCIA=0x9014,MCION=0x9052,PMAOS=0x5012,PMTM=0x5067,MTCAP=0x9009,MTMP=0x900a,MTMG=0x910d,MTMR=0x910e,MVCAP=0x902e,MVCR=0x900c,MPCS=0x917d,MFRL=0x9028,MROQ=0x902f,MRSI=0x912a,MCQS=0x9060,MCQI=0x9061,MCC=0x9062,MCDA=0x9063,MCDD=0x905c,MIRC=0x9162,MQIS=0x9064,MGIR=0x9020,MSGI=0x9021,MSCI=0x902a,MDIR=0x911a,MISOC=0x9026,MIDV=0x9027,MIDFV=0x9018,MCAM=0x907f,MRFV=0x906d,MTEIR=0x9190,MDTR=0x9073,MDPS=0x9074,MDSR=0x9110,MFSV=0x9115,MTCQ=0x9065,MQDIK=0x9116,MKDC=0x9066,MFCDR=0x9178,MSGCR=0x9179,MNVDA=0x9024,MNVDI=0x9025,MNVQC=0x9030,MNVIA=0x9033,MNVGC=0x9034,MNVGN=0x9035,MGNLE=0x9036,MGLS=0x9068,MVTS=0x902c,MTRC_CAP=0x9040,MTRC_CONF=0x9041,MTRC_STDB=0x9042,MTRC_CTRL=0x9043,MTEIM=0x9118,MTIE=0x911b,MTIM=0x911c,MTDC=0x911d,MFPA=0x9010,MFBA=0x9011,MFBE=0x9012,MPCIR=0x905a,MERR=0x903c,MRPR=0x9117,MHMPR=0x905d,MMHI=0x904a,MPEIN=0x9050,MPCNT=0x9051,MPEGC=0x9056,MPIR=0x9059,MPECS=0x905b,MPCAM=0x9702,MPEINJ=0x9057,MPQD=0x9700,MPLH=0x9701,SBPR=0xb001,SBCM=0xb002,SBCAM=0xb01f,CWTP=0x2802,CWTPM=0x2803,CWCAM=0x281f,Resource_dump_registers=0xc000,NCFG=0xc001,CRYPTO_OPERATIONAL=0xc002,IMPORT_KEK_HANDLE=0xc004,CREDENTIAL_HANDLE=0xc005,ZTT=0xc006,VHCA_TRUST_LEVEL=0xc007,PORT_STATE_BEHAVIOR=0xc008,HCA_CMD_ENCAP=0xc009,NVMF_TARGET_PACER_DEFAULTS=0xc00a,NIC_CAP_REG=0xc00d,DTOR=0xc00e,VHCA_ICM_CTRL=0xc010,NIC_CAP_EXT_REG=0xc011,NIC_DPA_EUG_REG=0xc012,NIC_DPA_PERF_CTRL_REG=0xc014,NIC_DPA_EU_PARTITION_REG=0xc015,ADP_RETX_HISTOGRAM_CONFIG=0xc01d,ADP_RETX_HISTOGRAM=0xc01e,HOST_OS_INIT_CTRL=0xc020" offset="0x0.0" size="0x4.0" />
</node>

<node name="access_reg_summary_ext" descr="" attr_is_union="1" size="0x300" >
	<field name="MRFV" descr="" subnode="MRFV_ext" capability="0" offset="0x0.0" selected_by="MRFV" size="0x40" />
	<field name="MRSV" descr="" subnode="MRSV_ext" capability="0" offset="0x0.0" selected_by="MRSV" size="0x40" />
	<field name="MSECQ_reg" descr="" subnode="MSECQ_reg_ext" capability="0" offset="0x0.0" selected_by="MSECQ" size="0x40" />
	<field name="MSEES_reg" descr="" subnode="MSEES_reg_ext" capability="0" offset="0x0.0" selected_by="MSEES" size="0x40" />
	<field name="MTMG" descr="" subnode="MTMG_ext" capability="0" offset="0x0.0" selected_by="MTMG" size="0x10" />
	<field name="MTMR" descr="" subnode="MTMR_ext" capability="0" offset="0x0.0" selected_by="MTMR" size="0xc" />
	<field name="PBWS_reg" descr="" subnode="PBWS_reg_ext" capability="0" offset="0x0.0" selected_by="PBWS" size="0x8" />
	<field name="PPCR" descr="" subnode="PPCR_ext" capability="0" offset="0x0.0" selected_by="PPCR" size="0x10" />
	<field name="adp_retx_histogram_config_reg" descr="" subnode="adp_retx_histogram_config_reg_ext" capability="0" offset="0x0.0" selected_by="ADP_RETX_HISTOGRAM_CONFIG" size="0x80" />
	<field name="adp_retx_histogram_reg" descr="" subnode="adp_retx_histogram_reg_ext" capability="0" offset="0x0.0" selected_by="ADP_RETX_HISTOGRAM" size="0x18" />
	<field name="credential_handle" descr="" subnode="credential_handle_ext" capability="0" offset="0x0.0" selected_by="CREDENTIAL_HANDLE" size="0x300" />
	<field name="crypto_operational" descr="" subnode="crypto_operational_ext" capability="0" offset="0x0.0" selected_by="CRYPTO_OPERATIONAL" size="0x80" />
	<field name="cwcam" descr="" subnode="cwcam_ext" capability="0" offset="0x0.0" selected_by="CWCAM" size="0x50" />
	<field name="cwtp" descr="" subnode="cwtp_ext" capability="0" offset="0x0.0" selected_by="CWTP" size="0x40" />
	<field name="cwtpm" descr="" subnode="cwtpm_ext" capability="0" offset="0x0.0" selected_by="CWTPM" size="0x44" />
	<field name="db_threshold_register_layout" descr="" subnode="db_threshold_register_layout_ext" capability="0" offset="0x0.0" selected_by="DB_TRESHOLD" size="0x10" />
	<field name="dcbx_app_reg" descr="" subnode="dcbx_app_reg_ext" capability="0" offset="0x0.0" selected_by="DCBX_APPLICATION" size="0x14" />
	<field name="dcbx_param_reg" descr="" subnode="dcbx_param_reg_ext" capability="0" offset="0x0.0" selected_by="DCBX_PARAM" size="0x40" />
	<field name="dtor_reg" descr="" subnode="dtor_reg_ext" capability="0" offset="0x0.0" selected_by="DTOR" size="0x40" />
	<field name="fp_sl_map_arg" descr="" subnode="fp_sl_map_arg_ext" capability="0" offset="0x0.0" selected_by="FP_SL_MAP" size="0x4" />
	<field name="hca_cap_encap" descr="" subnode="hca_cap_encap_ext" capability="0" offset="0x0.0" selected_by="HCA_CMD_ENCAP" size="0x60" />
	<field name="host_os_init_ctrl_reg" descr="" subnode="host_os_init_ctrl_reg_ext" capability="0" offset="0x0.0" selected_by="HOST_OS_INIT_CTRL" size="0x40" />
	<field name="import_kek_handle" descr="" subnode="import_kek_handle_ext" capability="0" offset="0x0.0" selected_by="IMPORT_KEK_HANDLE" size="0x300" />
	<field name="mcam_reg" descr="" subnode="mcam_reg_ext" capability="0" offset="0x0.0" selected_by="MCAM" size="0x48" />
	<field name="mcc_reg" descr="" subnode="mcc_reg_ext" capability="0" offset="0x0.0" selected_by="MCC" size="0x20" />
	<field name="mcda_reg" descr="" subnode="mcda_reg_ext" capability="0" offset="0x0.0" selected_by="MCDA" size="0x90" />
	<field name="mcdd_reg" descr="" subnode="mcdd_reg_ext" capability="0" offset="0x0.0" selected_by="MCDD" size="0x20" />
	<field name="mcia" descr="" subnode="mcia_ext" capability="0" offset="0x0.0" selected_by="MCIA" size="0x94" />
	<field name="mcion" descr="" subnode="mcion_ext" capability="0" offset="0x0.0" selected_by="MCION" size="0x10" />
	<field name="mcqi_reg" descr="" subnode="mcqi_reg_ext" capability="0" offset="0x0.0" selected_by="MCQI" size="0x94" />
	<field name="mcqs_reg" descr="" subnode="mcqs_reg_ext" capability="0" offset="0x0.0" selected_by="MCQS" size="0x10" />
	<field name="mdir_reg" descr="" subnode="mdir_reg_ext" capability="0" offset="0x0.0" selected_by="MDIR" size="0x40" />
	<field name="mdps_reg" descr="" subnode="mdps_reg_ext" capability="0" offset="0x0.0" selected_by="MDPS" size="0x10" />
	<field name="mdsr_reg" descr="" subnode="mdsr_reg_ext" capability="0" offset="0x0.0" selected_by="MDSR" size="0x30" />
	<field name="mdtr_reg" descr="" subnode="mdtr_reg_ext" capability="0" offset="0x0.0" selected_by="MDTR" size="0xb0" />
	<field name="merr" descr="" subnode="merr_ext" capability="0" offset="0x0.0" selected_by="MERR" size="0x14" />
	<field name="mfba_reg" descr="" subnode="mfba_reg_ext" capability="0" offset="0x0.0" selected_by="MFBA" size="0x10c" />
	<field name="mfbe_reg" descr="" subnode="mfbe_reg_ext" capability="0" offset="0x0.0" selected_by="MFBE" size="0xc" />
	<field name="mfcdr_reg" descr="" subnode="mfcdr_reg_ext" capability="0" offset="0x0.0" selected_by="MFCDR" size="0x8" />
	<field name="mfpa_reg" descr="" subnode="mfpa_reg_ext" capability="0" offset="0x0.0" selected_by="MFPA" size="0x20" />
	<field name="mfrl_reg" descr="" subnode="mfrl_reg_ext" capability="0" offset="0x0.0" selected_by="MFRL" size="0x8" />
	<field name="mfsv_reg" descr="" subnode="mfsv_reg_ext" capability="0" offset="0x0.0" selected_by="MFSV" size="0x30" />
	<field name="mgcr_reg" descr="" subnode="mgcr_reg_ext" capability="0" offset="0x0.0" selected_by="MGCR" size="0x20" />
	<field name="mgir" descr="" subnode="mgir_ext" capability="0" offset="0x0.0" selected_by="MGIR" size="0xa0" />
	<field name="mgls" descr="" subnode="mgls_ext" capability="0" offset="0x0.0" selected_by="MGLS" size="0xc" />
	<field name="mgnle_reg" descr="" subnode="mgnle_reg_ext" capability="0" offset="0x0.0" selected_by="MGNLE" size="0x20" />
	<field name="mhmpr_reg" descr="" subnode="mhmpr_reg_ext" capability="0" offset="0x0.0" selected_by="MHMPR" size="0x14" />
	<field name="midfv_reg" descr="" subnode="midfv_reg_ext" capability="0" offset="0x0.0" selected_by="MIDFV" size="0x80" />
	<field name="midv_reg" descr="" subnode="midv_reg_ext" capability="0" offset="0x0.0" selected_by="MIDV" size="0x28c" />
	<field name="mirc_reg" descr="" subnode="mirc_reg_ext" capability="0" offset="0x0.0" selected_by="MIRC" size="0x8" />
	<field name="misoc_reg" descr="" subnode="misoc_reg_ext" capability="0" offset="0x0.0" selected_by="MISOC" size="0x120" />
	<field name="mjtag" descr="" subnode="mjtag_ext" capability="0" offset="0x0.0" selected_by="MJTAG" size="0x30" />
	<field name="mkdc_reg" descr="" subnode="mkdc_reg_ext" capability="0" offset="0x0.0" selected_by="MKDC" size="0x2c" />
	<field name="mlcr" descr="" subnode="mlcr_ext" capability="0" offset="0x0.0" selected_by="MLCR" size="0xc" />
	<field name="mmdio" descr="" subnode="mmdio_ext" capability="0" offset="0x0.0" selected_by="MMDIO" size="0xc" />
	<field name="mmhi_reg" descr="" subnode="mmhi_reg_ext" capability="0" offset="0x0.0" selected_by="MMHI" size="0x80" />
	<field name="mnvda_reg" descr="" subnode="mnvda_reg_ext" capability="0" offset="0x0.0" selected_by="MNVDA" size="0x10c" />
	<field name="mnvdi_reg" descr="" subnode="mnvdi_reg_ext" capability="0" offset="0x0.0" selected_by="MNVDI" size="0xc" />
	<field name="mnvgc_reg" descr="" subnode="mnvgc_reg_ext" capability="0" offset="0x0.0" selected_by="MNVGC" size="0x10" />
	<field name="mnvgn_reg" descr="" subnode="mnvgn_reg_ext" capability="0" offset="0x0.0" selected_by="MNVGN" size="0x20" />
	<field name="mnvia_reg" descr="" subnode="mnvia_reg_ext" capability="0" offset="0x0.0" selected_by="MNVIA" size="0x8" />
	<field name="mnvqc_reg" descr="" subnode="mnvqc_reg_ext" capability="0" offset="0x0.0" selected_by="MNVQC" size="0x8" />
	<field name="mpcam_reg" descr="" subnode="mpcam_reg_ext" capability="0" offset="0x0.0" selected_by="MPCAM" size="0x48" />
	<field name="mpcir" descr="" subnode="mpcir_ext" capability="0" offset="0x0.0" selected_by="MPCIR" size="0xa0" />
	<field name="mpcnt_reg" descr="" subnode="mpcnt_reg_ext" capability="0" offset="0x0.0" selected_by="MPCNT" size="0x100" />
	<field name="mpcs_reg" descr="" subnode="mpcs_reg_ext" capability="0" offset="0x0.0" selected_by="MPCS" size="0x50" />
	<field name="mpecs_reg" descr="" subnode="mpecs_reg_ext" capability="0" offset="0x0.0" selected_by="MPECS" size="0x20" />
	<field name="mpegc_reg" descr="" subnode="mpegc_reg_ext" capability="0" offset="0x0.0" selected_by="MPEGC" size="0x2c" />
	<field name="mpein_reg" descr="" subnode="mpein_reg_ext" capability="0" offset="0x0.0" selected_by="MPEIN" size="0x30" />
	<field name="mpeinj_reg" descr="" subnode="mpeinj_reg_ext" capability="0" offset="0x0.0" selected_by="MPEINJ" size="0x40" />
	<field name="mpir" descr="" subnode="mpir_ext" capability="0" offset="0x0.0" selected_by="MPIR" size="0x10" />
	<field name="mplh_reg" descr="" subnode="mplh_reg_ext" capability="0" offset="0x0.0" selected_by="MPLH" size="0xf8" />
	<field name="mpqd_reg" descr="" subnode="mpqd_reg_ext" capability="0" offset="0x0.0" selected_by="MPQD" size="0x10" />
	<field name="mqdik_reg" descr="" subnode="mqdik_reg_ext" capability="0" offset="0x0.0" selected_by="MQDIK" size="0x208" />
	<field name="mqis_reg" descr="" subnode="mqis_reg_ext" capability="0" offset="0x0.0" selected_by="MQIS" size="0x18" />
	<field name="mroq" descr="" subnode="mroq_ext" capability="0" offset="0x0.0" selected_by="MROQ" size="0x20" />
	<field name="mrpr_reg" descr="" subnode="mrpr_reg_ext" capability="0" offset="0x0.0" selected_by="MRPR" size="0x108" />
	<field name="mrsi" descr="" subnode="mrsi_ext" capability="0" offset="0x0.0" selected_by="MRSI" size="0x40" />
	<field name="mrtc_reg" descr="" subnode="mrtc_reg_ext" capability="0" offset="0x0.0" selected_by="MRTC" size="0x10" />
	<field name="mrtcq_reg" descr="" subnode="mrtcq_reg_ext" capability="0" offset="0x0.0" selected_by="MRTCQ" size="0x40" />
	<field name="msci" descr="" subnode="msci_ext" capability="0" offset="0x0.0" selected_by="MSCI" size="0xc" />
	<field name="msgcr_reg" descr="" subnode="msgcr_reg_ext" capability="0" offset="0x0.0" selected_by="MSGCR" size="0x8" />
	<field name="msgi" descr="" subnode="msgi_ext" capability="0" offset="0x0.0" selected_by="MSGI" size="0x80" />
	<field name="msmr" descr="" subnode="msmr_ext" capability="0" offset="0x0.0" selected_by="MSMR" size="0x10" />
	<field name="mtcap" descr="" subnode="mtcap_ext" capability="0" offset="0x0.0" selected_by="MTCAP" size="0x10" />
	<field name="mtcq_reg" descr="" subnode="mtcq_reg_ext" capability="0" offset="0x0.0" selected_by="MTCQ" size="0x70" />
	<field name="mtctr_reg" descr="" subnode="mtctr_reg_ext" capability="0" offset="0x0.0" selected_by="MTCTR" size="0x18" />
	<field name="mtdc" descr="" subnode="mtdc_ext" capability="0" offset="0x0.0" selected_by="MTDC" size="0x20" />
	<field name="mteim_reg" descr="" subnode="mteim_reg_ext" capability="0" offset="0x0.0" selected_by="MTEIM" size="0x30" />
	<field name="mteir_reg" descr="" subnode="mteir_reg_ext" capability="0" offset="0x0.0" selected_by="MTEIR" size="0xc" />
	<field name="mtie" descr="" subnode="mtie_ext" capability="0" offset="0x0.0" selected_by="MTIE" size="0x30" />
	<field name="mtim" descr="" subnode="mtim_ext" capability="0" offset="0x0.0" selected_by="MTIM" size="0x10" />
	<field name="mtmp" descr="" subnode="mtmp_ext" capability="0" offset="0x0.0" selected_by="MTMP" size="0x20" />
	<field name="mtpps_reg" descr="" subnode="mtpps_reg_ext" capability="0" offset="0x0.0" selected_by="MTPPS" size="0x38" />
	<field name="mtptm_reg" descr="" subnode="mtptm_reg_ext" capability="0" offset="0x0.0" selected_by="MTPTM" size="0x10" />
	<field name="mtrc_cap_reg" descr="" subnode="mtrc_cap_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CAP" size="0x84" />
	<field name="mtrc_conf_reg" descr="" subnode="mtrc_conf_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CONF" size="0x80" />
	<field name="mtrc_ctrl_reg" descr="" subnode="mtrc_ctrl_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CTRL" size="0x40" />
	<field name="mtrc_stdb_reg" descr="" subnode="mtrc_stdb_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_STDB" size="0xc" />
	<field name="mtutc_reg" descr="" subnode="mtutc_reg_ext" capability="0" offset="0x0.0" selected_by="MTUTC" size="0x1c" />
	<field name="mvcap_reg" descr="" subnode="mvcap_reg_ext" capability="0" offset="0x0.0" selected_by="MVCAP" size="0x10" />
	<field name="mvcr" descr="" subnode="mvcr_ext" capability="0" offset="0x0.0" selected_by="MVCR" size="0x18" />
	<field name="mvts_reg" descr="" subnode="mvts_reg_ext" capability="0" offset="0x0.0" selected_by="MVTS" size="0x14" />
	<field name="ncfg_reg" descr="" subnode="ncfg_reg_ext" capability="0" offset="0x0.0" selected_by="NCFG" size="0x40" />
	<field name="nic_cap_ext_reg" descr="" subnode="nic_cap_ext_reg_ext" capability="0" offset="0x0.0" selected_by="NIC_CAP_EXT_REG" size="0x80" />
	<field name="nic_cap_reg" descr="" subnode="nic_cap_reg_ext" capability="0" offset="0x0.0" selected_by="NIC_CAP_REG" size="0x80" />
	<field name="nic_dpa_eu_partition_reg" descr="" subnode="nic_dpa_eu_partition_reg_ext" capability="0" offset="0x0.0" selected_by="NIC_DPA_EU_PARTITION_REG" size="0x300" />
	<field name="nic_dpa_eug_reg" descr="" subnode="nic_dpa_eug_reg_ext" capability="0" offset="0x0.0" selected_by="NIC_DPA_EUG_REG" size="0x100" />
	<field name="nic_dpa_perf_ctrl_reg" descr="" subnode="nic_dpa_perf_ctrl_reg_ext" capability="0" offset="0x0.0" selected_by="NIC_DPA_PERF_CTRL_REG" size="0x40" />
	<field name="nvmf_target_pacer_defaults" descr="" subnode="nvmf_target_pacer_defaults_ext" capability="0" offset="0x0.0" selected_by="NVMF_TARGET_PACER_DEFAULTS" size="0x40" />
	<field name="paos_reg" descr="" subnode="paos_reg_ext" capability="0" offset="0x0.0" selected_by="PAOS" size="0x10" />
	<field name="pbmc_reg" descr="" subnode="pbmc_reg_ext" capability="0" offset="0x0.0" selected_by="PBMC" size="0x6c" />
	<field name="pbsr_reg" descr="" subnode="pbsr_reg_ext" capability="0" offset="0x0.0" selected_by="PBSR" size="0x64" />
	<field name="pcam_reg" descr="" subnode="pcam_reg_ext" capability="0" offset="0x0.0" selected_by="PCAM" size="0x50" />
	<field name="pcap_reg" descr="" subnode="pcap_reg_ext" capability="0" offset="0x0.0" selected_by="PCAP" size="0x14" />
	<field name="pcct_reg" descr="" subnode="pcct_reg_ext" capability="0" offset="0x0.0" selected_by="PCCT" size="0x14" />
	<field name="pcmr_reg" descr="" subnode="pcmr_reg_ext" capability="0" offset="0x0.0" selected_by="PCMR" size="0xc" />
	<field name="pcnr_reg" descr="" subnode="pcnr_reg_ext" capability="0" offset="0x0.0" selected_by="PCNR" size="0xc" />
	<field name="pddr_reg" descr="" subnode="pddr_reg_ext" capability="0" offset="0x0.0" selected_by="PDDR" size="0x100" />
	<field name="peir_reg" descr="" subnode="peir_reg_ext" capability="0" offset="0x0.0" selected_by="PEIR" size="0xc" />
	<field name="pemi" descr="" subnode="pemi_ext" capability="0" offset="0x0.0" selected_by="PEMI" size="0x100" />
	<field name="pepc_reg" descr="" subnode="pepc_reg_ext" capability="0" offset="0x0.0" selected_by="PEPC" size="0x10" />
	<field name="pfcc_reg" descr="" subnode="pfcc_reg_ext" capability="0" offset="0x0.0" selected_by="PFCC" size="0x20" />
	<field name="pfldc" descr="" subnode="pfldc_ext" capability="0" offset="0x0.0" selected_by="PFLDC" size="0x20" />
	<field name="pgmr" descr="" subnode="pgmr_ext" capability="0" offset="0x0.0" selected_by="PGMR" size="0x2c" />
	<field name="pguid_reg" descr="" subnode="pguid_reg_ext" capability="0" offset="0x0.0" selected_by="PGUID" size="0x60" />
	<field name="pipg_reg" descr="" subnode="pipg_reg_ext" capability="0" offset="0x0.0" selected_by="PIPG" size="0x8" />
	<field name="plcc_reg" descr="" subnode="plcc_reg_ext" capability="0" offset="0x0.0" selected_by="PLCC" size="0x10" />
	<field name="plds" descr="" subnode="plds_ext" capability="0" offset="0x0.0" selected_by="PLDS" size="0x18" />
	<field name="pltc_reg" descr="" subnode="pltc_reg_ext" capability="0" offset="0x0.0" selected_by="PLTC" size="0x10" />
	<field name="pmaos_reg" descr="" subnode="pmaos_reg_ext" capability="0" offset="0x0.0" selected_by="PMAOS" size="0x10" />
	<field name="pmcr_reg" descr="" subnode="pmcr_reg_ext" capability="0" offset="0x0.0" selected_by="PMCR" size="0x2c" />
	<field name="pmdr_reg" descr="" subnode="pmdr_reg_ext" capability="0" offset="0x0.0" selected_by="PMDR" size="0x48" />
	<field name="pmlp_reg" descr="" subnode="pmlp_reg_ext" capability="0" offset="0x0.0" selected_by="PMLP" size="0x40" />
	<field name="pmmp_reg" descr="" subnode="pmmp_reg_ext" capability="0" offset="0x0.0" selected_by="PMMP" size="0x40" />
	<field name="pmpd_reg" descr="" subnode="pmpd_reg_ext" capability="0" offset="0x0.0" selected_by="PMPD" size="0x30" />
	<field name="pmpr_reg" descr="" subnode="pmpr_reg_ext" capability="0" offset="0x0.0" selected_by="PMPR" size="0x10" />
	<field name="pmpt_reg" descr="" subnode="pmpt_reg_ext" capability="0" offset="0x0.0" selected_by="PMPT" size="0x1c" />
	<field name="pmscr_reg" descr="" subnode="pmscr_reg_ext" capability="0" offset="0x0.0" selected_by="PMSCR" size="0x48" />
	<field name="pmtm_reg" descr="" subnode="pmtm_reg_ext" capability="0" offset="0x0.0" selected_by="PMTM" size="0x10" />
	<field name="pmtu_reg" descr="" subnode="pmtu_reg_ext" capability="0" offset="0x0.0" selected_by="PMTU" size="0x10" />
	<field name="port_state_behavior" descr="" subnode="port_state_behavior_ext" capability="0" offset="0x0.0" selected_by="PORT_STATE_BEHAVIOR" size="0x10" />
	<field name="ppad_reg" descr="" subnode="ppad_reg_ext" capability="0" offset="0x0.0" selected_by="PPAD" size="0x10" />
	<field name="ppaos_reg" descr="" subnode="ppaos_reg_ext" capability="0" offset="0x0.0" selected_by="PPAOS" size="0x10" />
	<field name="ppbmc_reg" descr="" subnode="ppbmc_reg_ext" capability="0" offset="0x0.0" selected_by="PPBMC" size="0x10" />
	<field name="ppbmp_reg" descr="" subnode="ppbmp_reg_ext" capability="0" offset="0x0.0" selected_by="PPBMP" size="0x30" />
	<field name="ppcc_reg" descr="" subnode="ppcc_reg_ext" capability="0" offset="0x0.0" selected_by="PPCC" size="0xfc" />
	<field name="ppcnt_reg" descr="" subnode="ppcnt_reg_ext" capability="0" offset="0x0.0" selected_by="PPCNT" size="0x100" />
	<field name="pphcr" descr="" subnode="pphcr_ext" capability="0" offset="0x0.0" selected_by="PPHCR" size="0x5c" />
	<field name="pplm_reg" descr="" subnode="pplm_reg_ext" capability="0" offset="0x0.0" selected_by="PPLM" size="0x80" />
	<field name="pplr_reg" descr="" subnode="pplr_reg_ext" capability="0" offset="0x0.0" selected_by="PPLR" size="0x8" />
	<field name="pprm_reg" descr="" subnode="pprm_reg_ext" capability="0" offset="0x0.0" selected_by="PPRM" size="0x94" />
	<field name="pprt_reg" descr="" subnode="pprt_reg_ext" capability="0" offset="0x0.0" selected_by="PPRT" size="0x24" />
	<field name="ppsc_reg" descr="" subnode="ppsc_reg_ext" capability="0" offset="0x0.0" selected_by="PPSC" size="0x30" />
	<field name="pptb_reg" descr="" subnode="pptb_reg_ext" capability="0" offset="0x0.0" selected_by="PPTB" size="0xc" />
	<field name="pptt_reg" descr="" subnode="pptt_reg_ext" capability="0" offset="0x0.0" selected_by="PPTT" size="0x1c" />
	<field name="prei_reg" descr="" subnode="prei_reg_ext" capability="0" offset="0x0.0" selected_by="PREI" size="0x18" />
	<field name="prtl_reg" descr="" subnode="prtl_reg_ext" capability="0" offset="0x0.0" selected_by="PRTL" size="0x20" />
	<field name="ptasv2_reg" descr="" subnode="ptasv2_reg_ext" capability="0" offset="0x0.0" selected_by="PTASv2" size="0x44" />
	<field name="pter_reg" descr="" subnode="pter_reg_ext" capability="0" offset="0x0.0" selected_by="PTER" size="0x20" />
	<field name="ptys_reg" descr="" subnode="ptys_reg_ext" capability="0" offset="0x0.0" selected_by="PTYS" size="0x44" />
	<field name="pvls" descr="" subnode="pvls_ext" capability="0" offset="0x0.0" selected_by="PVLS" size="0x20" />
	<field name="qcam" descr="" subnode="qcam_ext" capability="0" offset="0x0.0" selected_by="QCAM" size="0x48" />
	<field name="qeec" descr="" subnode="qeec_ext" capability="0" offset="0x0.0" selected_by="QEEC" size="0x20" />
	<field name="qhll" descr="" subnode="qhll_ext" capability="0" offset="0x0.0" selected_by="QHLL" size="0xc" />
	<field name="qpdp" descr="" subnode="qpdp_ext" capability="0" offset="0x0.0" selected_by="QPDP" size="0x8" />
	<field name="qpdpm" descr="" subnode="qpdpm_ext" capability="0" offset="0x0.0" selected_by="QPDPM" size="0x84" />
	<field name="qprt" descr="" subnode="qprt_ext" capability="0" offset="0x0.0" selected_by="QPRT" size="0x8" />
	<field name="qpts" descr="" subnode="qpts_ext" capability="0" offset="0x0.0" selected_by="QPTS" size="0x8" />
	<field name="qshr" descr="" subnode="qshr_ext" capability="0" offset="0x0.0" selected_by="QSHR" size="0x50" />
	<field name="qspcp" descr="" subnode="qspcp_ext" capability="0" offset="0x0.0" selected_by="QSPCP" size="0xc" />
	<field name="qspip" descr="" subnode="qspip_ext" capability="0" offset="0x0.0" selected_by="QSPIP" size="0x8" />
	<field name="qtct" descr="" subnode="qtct_ext" capability="0" offset="0x0.0" selected_by="QTCT" size="0x8" />
	<field name="register_host_endianness" descr="" subnode="register_host_endianness_ext" capability="0" offset="0x0.0" selected_by="HOST_ENDIANNESS" size="0x10" />
	<field name="register_loopback_control" descr="" subnode="register_loopback_control_ext" capability="0" offset="0x0.0" selected_by="Loopback_Control_Register" size="0x10" />
	<field name="register_misc_counters" descr="" subnode="register_misc_counters_ext" capability="0" offset="0x0.0" selected_by="MISC_COUNTERS" size="0x20" />
	<field name="register_power_settings" descr="" subnode="register_power_settings_ext" capability="0" offset="0x0.0" selected_by="POWER_SETTINGS" size="0x10" />
	<field name="register_unit_perf_counters_cfg" descr="" subnode="register_unit_perf_counters_cfg_ext" capability="0" offset="0x0.0" selected_by="UNIT_PERF_COUNTERS_CFG" size="0x20" />
	<field name="register_unit_perf_counters_data" descr="" subnode="register_unit_perf_counters_data_ext" capability="0" offset="0x0.0" selected_by="UNIT_PERF_COUNTERS_DATA" size="0x20" />
	<field name="register_unti_perf_global_ctrl" descr="" subnode="register_unti_perf_global_ctrl_ext" capability="0" offset="0x0.0" selected_by="UNIT_PERF_COUNTERS_GLOBAL_CTRL" size="0x10" />
	<field name="resource_dump" descr="" subnode="resource_dump_ext" capability="0" offset="0x0.0" selected_by="Resource_dump_registers" size="0x100" />
	<field name="roce_accl_reg" descr="" subnode="roce_accl_reg_ext" capability="0" offset="0x0.0" selected_by="ROCE_ACCL" size="0x80" />
	<field name="sbcam" descr="" subnode="sbcam_ext" capability="0" offset="0x0.0" selected_by="SBCAM" size="0x4c" />
	<field name="sbcm" descr="" subnode="sbcm_ext" capability="0" offset="0x0.0" selected_by="SBCM" size="0x28" />
	<field name="sbpr" descr="" subnode="sbpr_ext" capability="0" offset="0x0.0" selected_by="SBPR" size="0x18" />
	<field name="set_node_in" descr="" subnode="set_node_in_ext" capability="0" offset="0x0.0" selected_by="SET_NODE" size="0x40" />
	<field name="sllm_reg" descr="" subnode="sllm_reg_ext" capability="0" offset="0x0.0" selected_by="SLLM" size="0x30" />
	<field name="slprr_reg" descr="" subnode="slprr_reg_ext" capability="0" offset="0x0.0" selected_by="SLPRR" size="0x150" />
	<field name="slred_reg" descr="" subnode="slred_reg_ext" capability="0" offset="0x0.0" selected_by="SLRED" size="0xa8" />
	<field name="slrg_reg" descr="" subnode="slrg_reg_ext" capability="0" offset="0x0.0" selected_by="SLRG" size="0x28" />
	<field name="slsir_reg" descr="" subnode="slsir_reg_ext" capability="0" offset="0x0.0" selected_by="SLSIR" size="0x94" />
	<field name="sltp_reg" descr="" subnode="sltp_reg_ext" capability="0" offset="0x0.0" selected_by="SLTP" size="0x4c" />
	<field name="sltpv2_reg" descr="" subnode="sltpv2_reg_ext" capability="0" offset="0x0.0" selected_by="SLTPv2" size="0x10c" />
	<field name="vhca_icm_ctrl" descr="" subnode="vhca_icm_ctrl_ext" capability="0" offset="0x0.0" selected_by="VHCA_ICM_CTRL" size="0x40" />
	<field name="vhca_trust_level" descr="" subnode="vhca_trust_level_ext" capability="0" offset="0x0.0" selected_by="VHCA_TRUST_LEVEL" size="0x10" />
	<field name="ztt" descr="" subnode="ztt_ext" capability="0" offset="0x0.0" selected_by="ZTT" size="0x10" />
</node>

<node name="access_reg_summary_selector_ext" descr="" attr_is_union="1" size="0x300" >
	<field name="access_reg_summary" descr="" subnode="access_reg_summary_ext" offset="0x0.0" size="0x300" union_selector="$(parent).ctrl.id" />
	<field name="ctrl" descr="" subnode="access_reg_summary_ctrl_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="adp_retx_histogram_config_reg_ext" descr="" size="0x80.0" >
	<field name="time_unit_cap" descr="Bitmap indicating support for time_unit values. Set bit indicates the unit is supported. Each bit corresponds to the respective value in time_unit." access="RO" offset="0x0.20" size="0x0.4" />
	<field name="bin_width_mode" descr="Defines how histogram bin width is calculated, for bins other than bin0.\;0x0: BIN_FIXED - All bins have bin1_width width\;0x1: BIN_DOUBLE - Every bin is 2x wider then previous bin.\;Other values are reserved." access="RW" enum="BIN_FIXED=0x0,BIN_DOUBLE=0x1" offset="0x0.24" size="0x0.2" />
	<field name="time_unit" descr="Time granularity for bin0_width and bin1_width fields.\;Supported time units are indicated by time_unit_cap.\;0x0: TIME_NSEC - nanoseconds\;0x1: TIME_USEC - microseconds\;0x2: TIME_USEC_100 - 100 microseconds\;0x3: TIME_MSEC - miliseconds\;Other values are not supported." access="RW" enum="TIME_NSEC=0x0,TIME_USEC=0x1,TIME_USEC_100=0x2,TIME_MSEC=0x3" offset="0x0.26" size="0x0.2" />
	<field name="vhca_id_valid" descr="When set, the histogram will collect timeout events for the function specified by vhca_id. Otherwise, the histogram will collect timeout events for the current function and all its affiliated functions." access="RW" offset="0x0.29" size="0x0.1" />
	<field name="clear_on_read" descr="When set, histogram is reset following their read." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="count_enable" descr="When set, histogram will be updated according to its trigger definition, otherwise the histogram is static. Changing the setting does not reset the histogram" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="vhca_id" descr="VHCA ID for which adaptive-retransmission timeout expiration events are collected in the histogram.\;Valid if vhca_id_valid is set." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="bin_num_max" descr="Maximum supported number of histogram bins" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="bin_num" descr="Number of histogram bins.\;Minimum value is 1.\;Maximum value is indicated by bin_num_max." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="bin1_width" descr="Bin1 width, all relevant timeout event for timeout value within between bin0_width and bin1_width will be counted in Bin1. In addition, bin1_width is used to calculate all following bins, according to bin_width_mode. \;Units are defined by time_unit. Must be non-zero. Valid onlly if num_bin is bigger than 1" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="bin0_width" descr="Bin0 width, all relevant timeout event for timeout value within between 0 and bin0_width will be counted in Bin0. Units are defined by time_unit. Must be non-zero." access="RW" offset="0x8.16" size="0x0.16" />
</node>

<node name="adp_retx_histogram_reg_ext" descr="" size="0x18.0" >
	<field name="bin_num" descr="Number of histogram bins." access="RO" offset="0x0.24" size="0x0.8" />
	<field name="histogram_bin" descr="Array of histogram bins. Units defined by ADP_RETX_COUNTER_CONFIG.time_unit" subnode="uint64" access="RW" high_bound="VARIABLE" low_bound="0" offset="0x10.0" size="0x8.0" />
</node>

<node name="adp_retx_profile_ext" descr="" size="0x30.0" >
	<field name="time_base" descr="Base value for all time parameter, units defined by time_unit" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="time_unit" descr="Time granularity of time_base\;0x1: TIME_USEC - microseconds\;Other values are reserved" access="RW" enum="TIME_USEC=0x1" offset="0x0.22" size="0x0.2" />
	<field name="start_range_index" descr="Index of timeout_range used as the first range following QP creation." access="RW" offset="0x0.24" size="0x0.3" />
	<field name="range_num" descr="Number of valid ranges in timeout_range[] array" access="RW" offset="0x0.28" size="0x0.3" />
	<field name="qp_total_timeout" descr="If set, Total Retransmission Timeout will use QP parameters as timeout value, given by\;QP.retry_count * QP.timeout or\;QP.extended_retry_count * QP.timeout\;If clr, retx_total_timeout is used" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="timeout_init_range_size" descr="Upper bound for QP initial timeout randomization, given by\;base_time &lt;&lt; (timeout_init_low_bound + timeout_init_range_size)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="timeout_init_low_bound" descr="Lower bound for QP initial timeout randomization, given by\;base_time &lt;&lt; timeout_init_low_bound" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="retx_total_timeout" descr="Total Retransmission Timeout, given by\;base_time &lt;&lt; retx_total_timeout\;Valid if qp_total_timeout is 0x0." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="timeout_range" descr="Array of timeout ranges. First range_num entries are valid." subnode="adp_retx_to_range_ext" access="RW" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
</node>

<node name="adp_retx_to_range_ext" descr="" size="0x4.0" >
	<field name="range_size" descr="Upper bound of the timeout range given by\;base_time &lt;&lt; (range_low_bound + range_size)" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="range_low_bound" descr="Lower bound of the timeout range, given by\;base_time &lt;&lt; range_low_bound" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="timeout_retry_num" descr="Number of consecutive retransmissions attempts with the same imeout value, before timeout is increased." access="RW" offset="0x0.16" size="0x0.10" />
	<field name="dec_mode" descr="Defines the behavior of timeout decrease until lower bound is reached\;0x0: TO_DIV_4\;0x1: TO_DIV_2\;0x2: TO_LOW_BOUND\;Other values are reserved" access="RW" enum="TO_DIV_4=0x0,TO_DIV_2=0x1,TO_LOW_BOUND=0x2" offset="0x0.26" size="0x0.2" />
	<field name="prev_range_index" descr="Index of the timeout range to used when the current timeout is the range&apos;s lower-bound, and timeout should be decreased" access="RW" offset="0x0.28" size="0x0.3" />
</node>

<node name="application_prio_entry_ext" descr="" size="0x4.0" >
	<field name="protocol_id" descr="According to 802.1Q application priority TLV" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="sel" descr="According to 802.1Q application priority TLV" access="RO" offset="0x0.16" size="0x0.3" />
	<field name="priority" descr="" access="RO" offset="0x0.21" size="0x0.3" />
</node>

<node name="bufferx_lossless_thresholds_ext" descr="" size="0x4.0" >
	<field name="xon_threshold" descr="When the amount of data in the buffer goes below this value, device stops sending pause frames for the Prios associated with the buffer. Units are represented in cells.\;For shared_headroom_pool, this field is reserved." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="xoff_threshold" descr="Once the amount of data in the buffer goes above this value, device starts sending Pause frames for all Prios associated with the buffer. Units are represented in cells.\;For shared_headroom_pool, this field is reserved." access="RW" offset="0x0.16" size="0x0.16" />
</node>

<node name="bufferx_reg_ext" descr="" size="0x8.0" >
	<field name="size" descr="The part of the packet buffer array is allocated for the specific buffer.\;Units are represented in cells.\;\;For shared_headroom_pool, this field represents the maximum loan from the shared headroom pool and it can be set only when port_shared_buffer is enabled.\;Range is 0..cap_max_shared_headroom_pool_loan_size. \;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="epsb" descr="Eligible for Port Shared buffer.\;If epsb is set, packets assigned to bufferX are allowed to insert the port shared buffer.\;For port_shared_buffer, this field is reserved.\;For shared_headroom_pool, this field is reserved.\;When lossy==1 this field is reserved.\;The field is reserved for Switch-X/-2." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="lossy" descr="The field indicates if the buffer is lossy.\;0: Lossless\;1: Lossy\;\;The field is reserved for Switch-X/-2.\;For port_shared_buffer, this field is reserved.\;For shared_headroom_pool, this field is reserved." access="RW" enum="Lossless=0x0,Lossy=0x1" offset="0x0.25" size="0x0.1" />
	<field name="drop_over_max_mask" descr="[DWIP]\;Write drop_over_mask for lossy buffers.\;Reserved on Query or when lossy=0.\;Supported only on Spectrum switches from Spectrum-3." access="OP" offset="0x0.26" size="0x0.1" />
	<field name="xon_xoff_threshold_mask_n" descr="Mask bit indicating if xon_threshold and xoff_threshold should be updated.\;0: xon_threshold and xoff_threshold will be updated.\;1: xon_threshold and xoff_threshold will not be updated.\;\;Valid only on HCAs." access="WO" offset="0x0.31" size="0x0.1" />
	<field name="thresholds" descr="For lossless (lossy=0) see Table 2597, &quot;BufferX Lossless Thresholds Layout,&quot; on page 2998." subnode="bufferx_reg_thresholds_auto_ext" access="RW" offset="0x4.00" size="0x4.0" union_selector="$(parent).lossy" />
</node>

<node name="bufferx_reg_thresholds_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="bufferx_lossless_thresholds_ext" descr="" subnode="bufferx_lossless_thresholds_ext" offset="0x0.0" selected_by="Lossless" size="0x4.0" />
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
	<field name="type" descr="Configuration item index according to its type_class. \;Table 3112, &quot;Configuration Item Data Type Class Global Layout,&quot; on page 3450\;Table 3114, &quot;Configuration Item Data Type Class Physical Port Layout,&quot; on page 3450\;Table 3116, &quot;Configuration Item Data Type Class Per Host-PF Layout,&quot; on page 3451\;Table 3118, &quot;Configuration Item Data Type Class Log Layout,&quot; on page 3451\;Table 3120, &quot;Configuration Item Data Type Class File Layout,&quot; on page 3452\;Table 3122, &quot;Configuration Item Data Type Class Host Layout,&quot; on page 3452\;\;Table 3124, &quot;Configuration Item Data Type Class Module Layout,&quot; on page 3453\;Table 3126, &quot;Configuration Item Data Type Class Multi Instance Layout,&quot; on page 3454" subnode="config_item_type_auto_ext" access="INDEX" offset="0x4.0" size="0x4.0" />
</node>

<node name="config_item_type_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="configuration_item_type_class_file_ext" descr="" subnode="configuration_item_type_class_file_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_global_ext" descr="" subnode="configuration_item_type_class_global_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_host_ext" descr="" subnode="configuration_item_type_class_host_ext" offset="0x0.0" size="0x4.0" />
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

<node name="configuration_item_type_class_host_ext" descr="" size="0x4.0" >
	<field name="parameter_index" descr="" access="INDEX" offset="0x0.0" size="0x0.18" />
	<field name="type_class" descr="type_class = 0x7" access="INDEX" offset="0x0.24" size="0x0.8" />
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

<node name="credential_handle_ext" descr="" size="0x300.0" >
	<field name="crypto_login_object" descr="Information required to identify an officer.\;modify_field_select is reserved.\;Needed for all operations." subnode="crypto_login_obj_ext" access="RW" offset="0x0.0" size="0x100.0" />
	<field name="credential_object" descr="The import_KEK to add.\;For add, this is input (WO) of new KEK info.\;For query, this output (RO) with limited info of KEK.\;modify_field_select is reserved.\;For delete this field is reserved." subnode="credential_obj_ext" access="RW" offset="0x100.0" size="0x100.0" />
	<field name="credential_id" descr="For query/delete ops, this is input (WO).\;For add, input to this field is ignored, output is the selected\;ID." access="INDEX" offset="0x200.0" size="0x0.24" />
	<field name="write_operation" descr="0x1: ADD_OPERATION\;0x2: DELETE_OPERATION" access="WO" enum="ADD_OPERATION=0x1,DELETE_OPERATION=0x2" offset="0x200.24" size="0x0.4" />
</node>

<node name="credential_obj_ext" descr="" size="0x100.0" >
	<field name="modify_field_select" descr="Field select indicates in QUERY which fields are modifiable (1 means modifiable), and in MODIFY which fields to modify." subnode="uint64" offset="0x0.0" size="0x8.0" />
	<field name="credential_role" descr="0x0: role_officer - Officer role\;0x1: role_user - User role" enum="role_officer=0x0,role_user=0x1" offset="0x8.0" size="0x0.8" />
	<field name="state" descr="Credential state, Valid for Query command only.\;0x0: READY - the Credential state when first created\;0x1: ERROR - Credential unusable, need to destroy and re-create this credential." enum="READY=0x0,ERROR=0x1" offset="0x8.24" size="0x0.8" />
	<field name="credential" descr="The actual secret. Should be wrapped by import_KEK since\;credentials are only used in wrapped import method. Size includes\;8 bytes IV for wrapping." high_bound="11" low_bound="0" offset="0x40.0" size="0x30.0" />
</node>

<node name="crypto_login_obj_ext" descr="" size="0x100.0" >
	<field name="modify_field_select" descr="Field select indicates in QUERY which fields are modifiable (1 means modifiable), and in MODIFY which fields to modify." subnode="uint64" offset="0x0.0" size="0x8.0" />
	<field name="credential_pointer" descr="Credential pointer" offset="0x10.0" size="0x0.24" />
	<field name="state" descr="0x0: VALID - login is valid.\;0x1: INVALID - login is invalid, software can&quot;t manage wrapped crypto keys anymore, should destroy this login object and create a new one if needed. May happen, for example, due to a KEK or Credential used in this login being removed." enum="VALID=0x0,INVALID=0x1" offset="0x10.24" size="0x0.4" />
	<field name="session_import_kek_ptr" descr="Import_KEK pointer to be used for all secured information communicated in crypto commands (key fields), including the provided credential in this command" offset="0x14.0" size="0x0.24" />
	<field name="credential" descr="The credential secret, wrapped by the import_KEK indicated in this command. Size includes 8 bytes IV for wrapping" high_bound="11" low_bound="0" offset="0x40.0" size="0x30.0" />
</node>

<node name="crypto_operational_ext" descr="" size="0x80.0" >
	<field name="kek_size" descr="0x0: SIZE_128\;0x1: SIZE_256" access="WO" enum="SIZE_128=0x0,SIZE_256=0x1" offset="0x0.0" size="0x0.4" />
	<field name="wrapped_crypto_going_to_commissioning" descr="When set to 1, the device receives an authenticated command to go back to crypto commissioning mode. This will happen after the next FW reset. \;Valid only when wrapped_crypto_operational=1. After FW reset, wrapped_crypto_operational will be unset to 0, and this bit will be unset to 0 as well." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="wrapped_crypto_operational" descr="If set to 1, device is in operational mode. Read only." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="credential" descr="Plaintext credential secret for non-volatile index 0" access="WO" high_bound="9" low_bound="0" offset="0x8.0" size="0x28.0" />
	<field name="kek" descr="Plaintext import_KEK for non-volatile index 0.\;In 128bit KEK, Only the 128 MSBs are valid. LSBs are reserved." access="WO" high_bound="7" low_bound="0" offset="0x30.0" size="0x20.0" />
</node>

<node name="cvb_config_error_ext" descr="" size="0xa0.0" >
	<field name="cvb_error_type" descr="0: VDD configuration error\;1: DVDD configuration error" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the timeout." access="RO" offset="0x4.0" size="0x0.4" />
	<field name="tile_v" descr="Tile valid:\;0: The cvb configuration is main related\;1: The cvb configuration is tile related" access="RO" offset="0x4.31" size="0x0.1" />
</node>

<node name="cwcam_ext" descr="" size="0x50.0" >
	<field name="access_reg_group" descr="Access Register ID groups\;0: RegID_0x2800_to_0x287F\;Values 1-255 are Reserved" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features \;Values 1 - 255 are Reserved" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="cw_access_reg_cap_mask" descr="Supported port&apos;s access register bitmaks. Based on access_reg_group index.\;7When bit is set, The register is supported in the device. \;When access_reg_group == 0 :\;Bit_2: 0x2802_CWTP\;Bit_3: 0x2803_CWTPM\;Bit_31: 0x281f_CWCAM" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="feature_cap_mask" descr="Supported port&apos;s enhanced features. Based on feature_group index.\;When bit is set, The feature is supported in the device: \;Bits 0-127 are Reserved" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="cwtp_ext" descr="" size="0x40.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. Determines the way local_port is interpreted:\;2: host_port_number" access="INDEX" enum="host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="traffic_class" descr="Traffic Class\;Range is 0..cap_max_tclass_sb-1" access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="mode" descr="Mode of thresholds for WRED and ECN:\;0: Fixed\;1: Percentage" access="RW" enum="Fixed=0x0,Percentage=0x1" offset="0x24.24" size="0x0.1" />
	<field name="profile1_min" descr="Minimum Average Queue Size of the profile number &lt;i&gt;\;When mode is Fixed:\;Cells. Valid inputs are 1..cap_total_buffer_size/cap_cell_size.\;For Spectrum: must be a multiple of 64\;Note: for Spectrum, must be larger than 2^aqs_weight cells, see Section 30.8.1, &quot;CWGCR - Congestion WRED ECN General Configuration Register&quot;, on page 3079\;When mode is Percentage:\;Percentage of the quota of local_port,traffic_class. Range is 0..100, units of integer percentage. When ECN Source Congestion Detection is enabled then congestion occurs when there are at least 256 cells in the buffer\;" access="RW" offset="0x28.0" size="0x0.24" />
	<field name="profile1_max" descr="Maximum Average Queue Size of the profile number &lt;i&gt;\;When mode is Fixed:\;Cells. Valid inputs are 1..cap_total_buffer_size/cap_cell_size\;For Spectrum: must be a multiple of 64\;When mode is Percentage:\;Percentage of the quota of local_port,traffic_class. Range is 0..100, units of integer percentage.\;profile&lt;i&gt;_max must always be equal or greater than profile&lt;i&gt;_min" access="RW" offset="0x2C.0" size="0x0.24" />
	<field name="profile1_percent" descr="Percentage of WRED and ECN marking for Maximum Average Queue Size of the profile number &lt;i&gt;\;Range is 0..100, units of integer percentage\;Default is 0" access="RW" offset="0x2C.24" size="0x0.7" />
	<field name="profile2_min" descr="Same as above." access="RW" offset="0x30.0" size="0x0.24" />
	<field name="profile2_max" descr="Same as above." access="RW" offset="0x34.0" size="0x0.24" />
	<field name="profile2_percent" descr="Same as above." access="RW" offset="0x34.24" size="0x0.7" />
	<field name="profile3_min" descr="Same as above." access="RW" offset="0x38.0" size="0x0.24" />
	<field name="profile3_max" descr="Same as above." access="RW" offset="0x3C.0" size="0x0.24" />
	<field name="profile3_percent" descr="Same as above." access="RW" offset="0x3C.24" size="0x0.7" />
</node>

<node name="cwtpm_ext" descr="" size="0x44.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. Determines the way local_port is interpreted:\;2: host_port_number" access="INDEX" enum="host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="traffic_class" descr="Traffic Class\;Range is 0..cap_max_tclass_sb-1" access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="ee" descr="Enable ECN on traffic class\;0: Disable\;1: Enable\;Default is 0\;Reserved when Quantum" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x24.0" size="0x0.1" />
	<field name="ew" descr="Enable WRED on traffic class:\;0: Disable\;1: Enable\;Default is 0\;Reserved when Quantum" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x24.1" size="0x0.1" />
	<field name="ece" descr="Eth switch only:\;Enable ECE (TCP.ECE setting by the switch):\;Note: for ECE only tcp_g is used (tcp_y, tcp_r, ntcp_* ignored)\;Note: when both ece and ew are set, then if WRED does a drop then efficiently the ECE has no significance.\;Reserved when IB Switches and when Spectrum/-2/-3\;Note: ECE is per Ingress Port, packet TC\;\;0: Disable\;1: Enable\;Default is 0\;Supported from Spectrum-4 and above." access="RW" enum="Disable=0x0,Enable=0x1" offset="0x24.2" size="0x0.1" />
</node>

<node name="date_time_layout_ext" descr="" size="0x8.0" >
	<field name="hours" descr="hour (UTC) - 2 packed BCD digits" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="minutes" descr="minutes - 2 packed BCD digits" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="seconds" descr="seconds - 2 packed BCD digits" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="day" descr="day - 2 packed BCD digits" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="month" descr="month - 2 packed BCD digits" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="year" descr="year - 4 packed BCD digits" access="RW" offset="0x4.16" size="0x0.16" />
</node>

<node name="db_threshold_register_layout_ext" descr="" size="0x10.0" >
	<field name="threshold" descr="Required upper watermark.\;When FIFO/buffer reaches this size- an event will be sent" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="size" descr="Current FIFO/buffer size" access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="dcbx_app_reg_ext" descr="" size="0x14.0" >
	<field name="port_number" descr="Physical port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="num_app_prio" descr="" access="RO" offset="0x4.0" size="0x0.6" />
	<field name="app_prio" descr="Application priority entry. \;" subnode="application_prio_entry_ext" access="RO" high_bound="VARIABLE" low_bound="0" offset="0x10.0" size="0x4.0" />
</node>

<node name="dcbx_param_reg_ext" descr="" size="0x40.0" >
	<field name="max_application_table_size" descr="The maximum size of DCBX application table." access="RO" offset="0x0.0" size="0x0.6" />
	<field name="port_number" descr="Physical port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="dcbx_standby_cap" descr="If set, device supports DCBX on standby mode (aux power)." access="RO" offset="0x0.29" size="0x0.1" />
	<field name="dcbx_ieee_cap" descr="If set, DCBX IEEE version is supported." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="dcbx_cee_cap" descr="If set, DCBX CEE version is supported." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="version_admin" descr="Set the DCBX version.\;0x0: disabled- host is in charge \;0x1: CEE - supported only when dcbx_cee_cap==1\;0x2: IEEE - supported only when dcbx_ieee_cap==1\;0x3: CEE_and_IEEE - CEE and IEEE auto select. When using this mode, the device uses IEEE mode. If handshake with other party succeed, it will continue on using IEEE, otherwise it will fall back to CEE. Supported only when dcbx_cee_cap==1 and cbx_ieee_cap==1." access="RW" enum="disabled=0x0,CEE=0x1,IEEE=0x2,CEE_and_IEEE=0x3" offset="0x4.0" size="0x0.3" />
	<field name="version_oper" descr="0x0: disabled - host is in charge.\;0x1: CEE_enabled\;0x2: IEEE_enabled\;If the DCBX_PARAM.version_oper is 0x0, all oper and remote fields in DCBX_PARAM () are invalid. DCBX_APPLICATION.num_app_prio is 0\;DCBX_PARAM.version is 0x0 until a successful handshake with remote party.\;" access="RO" enum="disabled=0x0,CEE_enabled=0x1,IEEE_enabled=0x2" offset="0x4.8" size="0x0.3" />
	<field name="num_of_tc_admin" descr="Number of TCs." access="RW" offset="0x8.0" size="0x0.4" />
	<field name="num_of_tc_oper" descr="Number of TCs - operational state after negotiation with remote party.\;" access="RO" offset="0x8.8" size="0x0.4" />
	<field name="pfc_cap_admin" descr="Number of traffic classes that may simultaneously support PFC. Can be set in the range 0   8" access="RW" offset="0x8.16" size="0x0.4" />
	<field name="pfc_cap_oper" descr="Number of traffic classes that may simultaneously support PFC. Can be set in the range 0   8 - operational state after negotiation with remote party.\;" access="RO" offset="0x8.24" size="0x0.4" />
	<field name="willing_admin" descr="0x0: non_willing\;0x1: willing" access="RW" enum="non_willing=0x0,willing=0x1" offset="0x8.31" size="0x0.1" />
	<field name="remote_num_of_tc" descr="Remote side&apos;s number of TCs. Valid only after negotiation with remote party." access="RO" offset="0xC.0" size="0x0.4" />
	<field name="remote_pfc_cap" descr="Remote side&apos;s number of traffic classes that may simultaneously support PFC. Valid only after negotiation with remote party." access="RO" offset="0xC.24" size="0x0.4" />
	<field name="remote_willing" descr="Remote side&apos;s willing state. Valid only after negotiation with remote party" access="RO" offset="0xC.31" size="0x0.1" />
	<field name="error" descr="Bitmask indicates errors reported.\;Bit 0: not enough TC to comply with remote Bit 1: not enough pfc to comply with remote \;Bit 2: TSA unsupported" access="RO" offset="0x10.0" size="0x0.8" />
</node>

<node name="default_timeout_ext" descr="" size="0x4.0" >
	<field name="to_value" descr="Timeout value" access="RO" offset="0x0.0" size="0x0.20" />
	<field name="to_multiplier" descr="0x0: millisecond   \;0x1: seconds   \;0x2: minutes   \;0x3: hours   " access="RO" offset="0x0.29" size="0x0.3" />
</node>

<node name="dtor_reg_ext" descr="" size="0x40.0" >
	<field name="PCIE_TOGGLE_TO" descr="Maximum period for PCIe to be alive after toggle." subnode="default_timeout_ext" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="HEALTH_POLL_TO" descr="Interval for checking if FW health counter incremented." subnode="default_timeout_ext" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="FULL_CRDUMP_TO" descr="On a multi-function device, in case of error, one function dump the CRspace, the other should not do reset till dump is finished." subnode="default_timeout_ext" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="FW_RESET_TO" descr="Maximum period to wait for nic_interface reset." subnode="default_timeout_ext" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="FLUSH_ON_ERR_TO" descr="Maximum period to flush an errored SQ\RQ." subnode="default_timeout_ext" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="PCI_SYNC_UPDATE_TO" descr="Maximum period for pci_sync_for_fw_update_start." subnode="default_timeout_ext" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="TEAR_DOWN_TO" descr="Maximum period for TEARDOWN_HCA." subnode="default_timeout_ext" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="FSM_REACTIVATE_TO" descr="The time that takes to do FW FSM reactivate." subnode="default_timeout_ext" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="RECLAIM_PAGES_TO" descr="Maximum period for PF to reclaim own function pages." subnode="default_timeout_ext" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="RECLAIM_VFS_PAGES_TO" descr="Maximum period for PF to reclaim VF function pages." subnode="default_timeout_ext" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="DRIVER_UNLOAD_AND_RESET_TO" descr="Maximum period for Reset FSM to move from UNLOAD ACCEPTED to LINK_TOGGLE_REQUEST" subnode="default_timeout_ext" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="EMBEDDED_CPU_OS_SHUTDOWN_TO" descr="Maximum period for shutting down/booting the embedded CPU OS. Relevant for DPU devices only.\;Valid only if the timeout value is not zero.\;" subnode="default_timeout_ext" access="RW" offset="0x3C.0" size="0x4.0" />
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
	<field name="egress_link_down_high" descr="Egress link down discards" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="egress_link_down_low" descr="Egress link down discards" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="egress_hoq_high" descr="Head-of-Queue time-out discards" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="egress_hoq_low" descr="Head-of-Queue time-out discards" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="port_isolation_high" descr="Port isolation filter discards" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="port_isolation_low" descr="Port isolation filter discards" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="egress_policy_engine_high" descr="Egress policy engine discards" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="egress_policy_engine_low" descr="Egress policy engine discards" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="egress_stp_filter_high" descr="Egress spanning tree filter" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="egress_stp_filter_low" descr="Egress spanning tree filter" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="egress_hoq_stall_high" descr="Number of sequential packets dropped, due to Head-Of-Queue Lifetime Limit, that causes the port to enter the Stall state \;\;Reserved for Switches" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="egress_hoq_stall_low" descr="Number of sequential packets dropped, due to Head-Of-Queue Lifetime Limit, that causes the port to enter the Stall state \;\;Reserved for Switches" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="egress_sll_high" descr="Number of packets dropped, because the Switch Lifetime Limit was exceeded. \;\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="egress_sll_low" descr="Number of packets dropped, because the Switch Lifetime Limit was exceeded. \;\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="ingress_discard_all_high" descr="Number of packets dropped for of any reason.\; Note: see description in the description area for limitations of this counter.\;Applies for switches only. Reserved for HCAs\;\;Note: deprecated for all Ethernet devices" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="ingress_discard_all_low" descr="Number of packets dropped for of any reason.\; Note: see description in the description area for limitations of this counter.\;Applies for switches only. Reserved for HCAs\;\;Note: deprecated for all Ethernet devices" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="ingress_no_tx_high" descr="[Draft] Number of packets dropped at ingress for lack of TX list.\;Triggered by DISCARD_LOOKUP_SWITCH or more specifically DISCARD_LOOKUP_SWITCH_UC, DISCARD_LOOKUP_SWITCH_MC_NULL or DISCARD_LOOKUP_SWITCH_NO_PORTS. See Section  2.8.3.12, &quot;Discard Extended Trap IDs,&quot; on page  609.\;Supported on switches only from Spectrum-4." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="ingress_no_tx_low" descr="[Draft] Number of packets dropped at ingress for lack of TX list.\;Triggered by DISCARD_LOOKUP_SWITCH or more specifically DISCARD_LOOKUP_SWITCH_UC, DISCARD_LOOKUP_SWITCH_MC_NULL or DISCARD_LOOKUP_SWITCH_NO_PORTS. See Section  2.8.3.12, &quot;Discard Extended Trap IDs,&quot; on page  609.\;Supported on switches only from Spectrum-4." access="RO" offset="0x84.0" size="0x4.0" />
</node>

<node name="eth_extended_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="port_transmit_wait_high" descr="The number of wire speed one-byte period(s) during which the port had data to transmit but no data was sent\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="port_transmit_wait_low" descr="The number of wire speed one-byte period(s) during which the port had data to transmit but no data was sent\;\;" access="RO" offset="0x4.0" size="0x4.0" />
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
	<field name="rx_octets_high" descr="The total number of octets received, including framing characters." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="rx_octets_low" descr="The total number of octets received, including framing characters." access="RO" offset="0x4.0" size="0x4.0" />
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
	<field name="wred_discard_high" descr="The number of packet that are dropped by the Weighted Random Early Detection (WRED) function.\;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt eth per tc cong group supported&quot; is set." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="wred_discard_low" descr="The number of packet that are dropped by the Weighted Random Early Detection (WRED) function.\;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt eth per tc cong group supported&quot; is set." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ecn_marked_tc_high" descr="A count of packets marked as ECN or potentially marked as ECN.\;ECN Counting enable/disable is configurable. \;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt eth per tc cong group supported&quot; is set.\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ecn_marked_tc_low" descr="A count of packets marked as ECN or potentially marked as ECN.\;ECN Counting enable/disable is configurable. \;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt eth per tc cong group supported&quot; is set.\;" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="eth_per_traffic_class_layout_ext" descr="" size="0xf8.0" >
	<field name="transmit_queue_high" descr="Contains the transmit queue depth in bytes on traffic class selected by traffic_class of the port selected by local_port.\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="transmit_queue_low" descr="Contains the transmit queue depth in bytes on traffic class selected by traffic_class of the port selected by local_port.\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_high" descr="The number of unicast packets dropped due to lack of shared buffer resources.\;Valid only for Spectrum.\;Valid for HCA when ppcnt_no_buffer_uc is set in PCAM." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_low" descr="The number of unicast packets dropped due to lack of shared buffer resources.\;Valid only for Spectrum.\;Valid for HCA when ppcnt_no_buffer_uc is set in PCAM." access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="ets_global_ext" descr="" size="0x8.0" >
	<field name="r" descr="Rate limit update. Enables update of the rate limiter (with the max_bw_units, max_bw_value). If this bit is cleared, the rate limiter value will not change." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="max_bw_value" descr="The maximal bandwidth allowed for the use for the port\;Encoding of max_bw_units:\;0x0: DISABLED - rate limiter disabled\;0x3: HUNDREDS_MBPS - max_bw_value is in 100 Mbps units\;0x4: GBPS - max_bw_value is in 1 Gbps units\;Note - Query response will return value in units that allow the most accurate number, not in the units configured using Set()." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="max_bw_units" descr="The maximal bandwidth allowed for the use for the port\;Encoding of max_bw_units:\;0x0: DISABLED - rate limiter disabled\;0x3: HUNDREDS_MBPS - max_bw_value is in 100 Mbps units\;0x4: GBPS - max_bw_value is in 1 Gbps units\;Note - Query response will return value in units that allow the most accurate number, not in the units configured using Set()." access="RW" enum="DISABLED=0x0,HUNDREDS_MBPS=0x3,GBPS=0x4" offset="0x4.16" size="0x0.4" />
</node>

<node name="fp_sl_map_arg_ext" descr="" size="0x4.0" >
	<field name="port" descr="0x0 - reserved\;0x1-0x2 - port number\;0x3-0xff - reserved" access="INDEX" offset="0x0.0" size="0x0.8" />
</node>

<node name="hca_cap_encap_ext" descr="" size="0x60.0" >
	<field name="cmd_data_offset" descr="Defines the start offset of the data (cmd_data_value and cmd_data_mask) that is needed to be set/queried by QUERY_HCA_CAP and SET_HCA_CAP) in granularity of 4Bytes.\;The offset starts from the beginning of the command. i.e. includes the command header.\;For other commands this field is reserved" access="INDEX" offset="0x0.16" size="0x0.16" />
	<field name="cmd_data_mask" descr="For set commands: Bitmask that indicates which bits in cmd_data_value should be written.\;An unset bit in this mask will leave the matching bit in the cmd_data_value unchanged. \;For query commands (QUERY_HCA_CAP): must be 0\;For other commands this field is reserved" access="INDEX" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="cmd_data_value" descr="For set commands: The value to apply starting from cmd_data_offset (in conjunction with the cmd_data_mask defined above). Set by the user.\;For query commands (QUERY_HCA_CAP): User should set to 0; will hold the value the device retrieved.\;For other commands this field is reserved" access="RW" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
	<field name="cmd_header" descr="Icommand_header_in and command_header_out (16 bytes) of QUERY_HCA_CAP or SET_HCA_CAP.\;command_header_in is set by user when issuing the register.\;command_header_out is returned by the device after executing the register." access="RW" high_bound="3" low_bound="0" offset="0x40.0" size="0x10.0" />
</node>

<node name="host_os_init_ctrl_reg_ext" descr="" size="0x40.0" >
	<field name="delay_host_os_init_clr" descr="Write 0x1 to resume host initialization. Valid if delay_host_os_init is set." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="delay_host_os_init" descr="If set, setting delay_host_os_init_clr is supported" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="host_os_init_mode" descr="Defines whether Host OS initialization will be delayed after Internal CPU initialization\;0x1: PRE_BOOT_DELAY - waiting for Pre-boot driver to load\;0x2: NO_DELAY\;0x3: USER_DELAY - waiting for delay_host_os_init_clr to be set\;Other values are reserved" access="RO" enum="PRE_BOOT_DELAY=0x1,NO_DELAY=0x2,USER_DELAY=0x3" offset="0x4.28" size="0x0.4" />
</node>

<node name="hst_link_eth_enabled_ext" descr="" size="0x4.0" >
	<field name="link_eth_active" descr="Ethernet protocols active: see PTYS.ext_eth_proto_oper" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="hst_link_ib_enabled_ext" descr="" size="0x4.0" >
	<field name="link_speed_active" descr="IB link active speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="link_width_active" descr="IB link active width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="hst_link_nvlink_enabled_ext" descr="" size="0x4.0" >
	<field name="link_nvlink_active" descr="NVLink protocols active\;See: Table  1888, &quot;PTYS - Extended Protocol NVLink - cap/oper Layout,&quot; on page  2191" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="import_kek_handle_ext" descr="" size="0x300.0" >
	<field name="crypto_login_object" descr="Information required to identify an officer.\;modify_field_select is reserved.\;Needed for all operations." subnode="crypto_login_obj_ext" access="RW" offset="0x0.0" size="0x100.0" />
	<field name="import_kek_object" descr="The import_KEK to add.\;For add, this is input (WO) of new KEK info.\;For query, this output (RO) with limited info of KEK.\;modify_field_select is reserved.\;For delete this field is reserved." subnode="import_kek_object_ext" access="RW" offset="0x100.0" size="0x100.0" />
	<field name="import_kek_id" descr="For query/delete ops, this is input (WO).\;For add, input to this field is ignored, output is the selected\;ID." access="INDEX" offset="0x200.0" size="0x0.24" />
	<field name="write_operation" descr="0x1: ADD_OPERATION\;0x2: DELETE_OPERATION" access="WO" enum="ADD_OPERATION=0x1,DELETE_OPERATION=0x2" offset="0x200.24" size="0x0.4" />
</node>

<node name="import_kek_object_ext" descr="" size="0x100.0" >
	<field name="modify_field_select" descr="Field select indicates in QUERY which fields are modifiable (1 means modifiable), and in MODIFY which fields to modify." subnode="uint64" offset="0x0.0" size="0x8.0" />
	<field name="key_size" descr="Key size\;0x0: SIZE_128\;0x1: SIZE_256" enum="SIZE_128=0x0,SIZE_256=0x1" offset="0x8.8" size="0x0.4" />
	<field name="state" descr="Key state, Valid for Query command only.\;0x0: READY - the key state when first created\;0x1: ERROR - key unusable, need to destroy and re-create this key" enum="READY=0x0,ERROR=0x1" offset="0x8.24" size="0x0.8" />
	<field name="key" descr="\;Actual size and layout of this field described in Table 428, &quot;IMPORT_KEK Field Construction Summary,&quot; on page 842 below. Note that the layout explained in following table should be used from the MSBs and on." high_bound="31" low_bound="0" offset="0x40.0" size="0x80.0" />
</node>

<node name="lane_2_module_mapping_ext" descr="" size="0x4.0" >
	<field name="module" descr="Module number" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA.\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="tx_lane" descr="TX lane. \;When m_lane_m field is set, this field is ignored (Reserved). \;When rxtx field is cleared, this field is used for RX as well." access="RW" offset="0x0.16" size="0x0.4" />
	<field name="rx_lane" descr="RX lane.\;When m_lane_m field is set, this field is ignored (Reserved). \;When rxtx field is clreared, for set operation this field is ignored and for get operation may return invalid value, Rx mapping for get should be taken from tx_lane." access="RW" offset="0x0.24" size="0x0.4" />
	<field name="mode_b_map" descr="Supported if PCAM.feature_cap_mask bit 116 is set, otherwise field is not valid.\;Relevant for Mode B port only, Mode A port should ignore.\;indicates if module lane Tx or Rx is used.\;0: module_rx_lane_valid - Mode B lane uses module rx lane. \;tx lane value is not valid should be ignored\;1: module_tx_lane_valid - Mode B lane uses module tx lane. \;rx lane value is not valid should be ignored" access="RO" offset="0x0.30" size="0x0.1" />
</node>

<node name="mcam_reg_ext" descr="" size="0x48.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: First_128_REG_ID - Register IDs 0x9001 - 0x907F)\;1: Register_IDs_0x9080 - 0x90FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9080 while bit 127 represents register ID 0x90FF).\;2: Register_IDs_0x9100 - 0x917F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9100 while bit 127 represents register ID 0x917F).\;3: Register_IDs_0x9180 - 0x91FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9180 while bit 127 represents register ID 0x91FF)." access="INDEX" enum="First_128_REG_ID=0x0,Register_IDs_0x9080=0x1,Register_IDs_0x9100=0x2,Register_IDs_0x9180=0x3" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="mng_access_reg_cap_mask" descr="Supported management&apos;s access register bitmask. Based on access_reg_group index. \;When bit is set, the register is supported in the device. \;For example:\;Bit 1: MFCR_0x9001\;Bit 2: MFSC_0x9002\;Bit 3: MFSM_0x9003\;Bit 4: MFSL_0x9004\;Bit 58: MGCR_0x903A\;Bit 73: MPPF_0x9049\;Bit 127: MCAP_0x907F" access="RO" enum="MFCR_0x9001=0x2,MFSC_0x9002=0x4,MFSM_0x9003=0x8,MFSL_0x9004=0x10,MGCR_0x903A=0x4000000,MPPF_0x9049=0x200,MCAP_0x907F=0x80000000" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="mng_feature_cap_mask" descr="Supported port&apos;s enhanced features.Based on feature_group index.\;When bit is set, The feature is supported in the device\;Bit 0: MPCNT counter group- PCIE performance counters supported\;Bit 1: mtpps_fs - If set, field_select field in MTPPS register is supported.\;Bit 2: mtpps_enhanced_out_periodic_adjustment - If set, enhanced_out_periodic_adjustment field in MTPPS register is supported.\;Bit 3: tx_lossy_overflow_oper - If set, tx_overflow_buffer_pkt counter in MPCNT register is supported.\;Bit 4: pcie_outbound_stalled - if set, outbound_stalled_reads, outbound_stalled_writes, outbound_stalled_reads_events and outbound_stalled_writes_events counters in MPCNT are supported.\;Bit 5: Management pass through is supported\;Bit 6: sensor_map - If set, sensor_map is supported in MTCAP register.\;Bit 7: if set, module_status bit 8 (Module Low Power) in MCION register is supported. \;Bit 8: beacon_capability_disable - If set, beacon feature, as appears in MLCR register, in not supported by the device. \;Bit 9: dynamic_tx_overflow - If set, tx_overflow_sense field is supported in MPEGC register. \;Bit 10: mark_tx_action_cqe is supported if set to &apos;1&apos;.\;Bit 11: mark_tx_action_cnp is supported if set to &apos;1&apos;.\;Bit 12: dev_info is supported in  register is set to &apos;1&apos;.\;Bit 13: sensor_count field is 12bit size in MTMP and MTBR\;Bit 14: cs_tokens_supported is supported \;Bit 15: debug_fw_tokens_supported\;Bit 16: long_keys is supported \;Bit 17: pwr_status and pci_power are supported in MPEIN\;Bit 18: If set, accessing through device_type and device_index is supported in MCC, MCQI and MCQS\;Bit 19: pcie_sync_for_fw_update_supported is set to &apos;1&apos;\;Bit 20: ptpCyc2Realtime_modify - If set, the cycle to realtime translation offload is supported\;Bit 21: If set to &apos;1&apos;, reset_state in MFRL is supported\;Bit 22: If set to &apos;1&apos;, link_peer_max_speed is supported in MPEIN Register\;Bit 23: If set to &apos;1&apos;, slot_index field is supported in: MCIA, MCAS, MCION, MQSP, MTCAP, MTECR, MTMP, MTEWE, MTBR, MVCAP, MVCR, MGPIR, MDDT, MDCR.\;Bit 24: If set, transceiver burn flow is supported in MCC, MCQI and MCQS.\;Bit 26: If set, progress field is supported in MCQS\;Bit 28: If set, number_of_slots field is supported in MGPIR.\;Bit 29: If set, virtual hot plug / unplug is supported in MPEGC.\;Bit 30: If set, my_pf_number is supported in MPPF.\;Bit 31: If set, sdee is supported in MTMP\;Bit 32: If set, npps_period is supported in MTPPS.\;Bit 33: If set, out_pulse_duration_ns is supported in MTPPS.\;Bit 34: If set, MCIA supports 32 D-words. Otherwise, 12 D-words.\;Bit 35: If set, MGIR.hw_info.technology is supported. \;Bit 37: If set, lp_msb is supported for MLCR, MPIR \;Bit 39: If set, MRCS and RMDT tokens are supported in MCQS\;Bit 40: If set, &apos;encryption&apos; field in MGIR is supported\;Bit 43: If set, MFCR supports tacho_active_msb field\;Bit 44: If set, FORE supports fan_under_limit_msb and fan_over_limit_msb fields\;Bit 45: If set, MFRL.pci_rescan_required is supported\;Bit 46: time_adjust_range_extended - if set, the MTUTC.time_adjustment range is extended to -200,000 to +200,000 \;Bit 47: If set, MTUTC.freq_adj_units=1 is supported\;Bit 48: If set, MRSRFT/MRSR.command=6 is supported\;Bit 49: If set, MCQS.identifier support CRCS and CRDT tokens\;Bit 51: If set, MTUTC.freq_adj_units=2 is supported\;Bit 53: If set, Mlx mlxfwreset with downstream port is supported by FW [Internal]: NIC only, FW rejects reset till user committed that traffic is disabled\;Bit 59: If set, MCC.component_specific_error_code is valid for LinkX devices\;Bit 60: If set, MGNLE.clr is supported\;Bit 61: If set, MGIR supports life_cycle_msb and pds fields in FW info and development field in HW info.\; \;Bit 65: If set, MVCR support current_sensor_value_msb\;Bit 66: If set. MFRL supports pci_reset_req_method, pci_switch_exist fields. [DWIP]\;Bit 67: If set, MRSR.cmd = 6 works with SBR\;Bit 68: If set, DPNv supported [NIC_Only]\;Bit 70: If set, supports MTCAP support 8 bit internal_sensor_count [DWIP]\;Bit 71: If set, supports MVCAP supports sensor_map_type [DWIP]\;Bit 72: If set, MVCR supports parent_id field [NIC_only]\;Bit 73: If set, MFRL.reset_type=5 Network reset is supported [NIC_only]\;Bit 74: If set, MGIR.hw_info.pci_switch_only_mode is supported [NIC_only]\;Bit 75: If set, PLLP supports oe_identifier and resource_labe_port [switch_internal][DWIP]\;bit 76: If set, MCQS supports the component_not_supported field [DWIP]\;Bit 77: If set, host_id field in MPIR is supported\;Bit 78: If set, MGIR supports 12 bit num_ports field\;\;bit 80: If set, MCQS,identifier supports the DPA_COMPONENT, DPA _COMPONENT_REMOVAL fields and MCQI supports DPA apps info\;Bit 81: If set, MFCDR supports module and query_type fields [DWIP]\;Bit 82: If set, MCIA supports async mode [DWIP][switch_internal]\;Bit 83: If set, MISOC supports types 0x2,0x3,0xF and query_not_availble, query_pending fields[NIC_Only]\;Bit 84: If set, MCANM supports ec_offload_engine_disabled field [NIC_Only]\;Bit 85: If set, MTDT token is supported\;Bit 86: If set, MPCAPM PRM is supported [NIC_Only]\;Bit 87: If set, MTCTR cross timestamp of the DPA timer is supported [NIC_Only]" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="mcc_reg_ext" descr="" size="0x20.0" >
	<field name="instruction" descr="Command to be executed by the FSM\;0x1: LOCK_UPDATE_HANDLE\;0x2: RELEASE_UPDATE_HANDLE \;0x3: UPDATE_COMPONENT\;0x4: VERIFY_COMPONENT\;0x6: ACTIVATE\;0x7: READ_COMPONENT\;0x8: CANCEL\;0x9: CHECK_UPDATE_HANDLE\;0xA: FORCE_HANDLE_RELEASE\;0xB: READ_PENDING_COMPONENT\;0xC: DOWNSRTEAM_DEVICE_TRANSFER\;Other values are reserved. Applicable for write operation only." access="RW" enum="LOCK_UPDATE_HANDLE=0x1,RELEASE_UPDATE_HANDLE=0x2,UPDATE_COMPONENT=0x3,VERIFY_COMPONENT=0x4,ACTIVATE=0x6,READ_COMPONENT=0x7,CANCEL=0x8,CHECK_UPDATE_HANDLE=0x9,FORCE_HANDLE_RELEASE=0xa,READ_PENDING_COMPONENT=0xb,DOWNSRTEAM_DEVICE_TRANSFER=0xc" offset="0x0.0" size="0x0.8" />
	<field name="activation_delay_sec" descr="This is a configuration that delays the activation of the component in seconds. Relevant only for activate command.\;This configuration is volatile." access="RW" offset="0x0.8" size="0x0.8" />
	<field name="time_elapsed_since_last_cmd" descr="The number of seconds elapsed since the update_handle owner last issued a command. The time saturates at 0xFFF." access="RO" offset="0x0.16" size="0x0.12" />
	<field name="component_index" descr="Index of the accessed component. \;Value from MCQS.component_index\;Valid for \;UPDATE_COMPONENT, ACTIVATE_COMPONENET, READ_COMPONENT and READ_PENDING_COMPONENT instructions. Otherwise, this field is reserved." access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="update_handle" descr="Token representing the current flow executed by the FSM.\;See Section 10.2.1, &quot;Component Update State&quot;, on page 1131." access="RW" offset="0x8.0" size="0x0.24" />
	<field name="auto_update" descr="Auto-update to all matching downstream devices is requested." access="WO" offset="0x8.31" size="0x0.1" />
	<field name="control_state" descr="Current Update FSM state, see Section  10.3.8, &quot;FSM States,&quot; on page  1135\;0x0: IDLE\;0x1: LOCKED\;0x2: INITIALIZE\;0x3: DOWNLOAD\;0x4: VERIFY\;0x5: APPLY\;0x6: ACTIVATE\;0x7: UPLOAD\;0x8: UPLOAD_PENDING\;0x9: DOWNSRTEAM_DEVICE_TRANSFER\;Other values are reserved" access="RO" enum="IDLE=0x0,LOCKED=0x1,INITIALIZE=0x2,DOWNLOAD=0x3,VERIFY=0x4,APPLY=0x5,ACTIVATE=0x6,UPLOAD=0x7,UPLOAD_PENDING=0x8,DOWNSRTEAM_DEVICE_TRANSFER=0x9" offset="0xC.0" size="0x0.4" />
	<field name="error_code" descr="Indicates the successful completion of the instruction, or the reason it failed. See Section  10.3.7, &quot;Error Handling,&quot; on page  1134\;0x0: OK\;0x1: ERROR\;0x2: REJECTED_DIGEST_ERR\;0x3: REJECTED_NOT_APPLICABLE\;0x4: REJECTED_UNKNOWN_KEY\;0x5: REJECTED_AUTH_FAILED\;0x6: REJECTED_UNSIGNED\;0x7: REJECTED_KEY_NOT_APPLICABLE\;0x8: REJECTED_BAD_FORMAT\;0x9: BLOCKED_PENDING_RESET\;0xA: REJECTED_NOT_A_SECURED_FW\;0xB: REJECTED_MFG_BASE_MAC_NOT_LISTED\;0xC: REJECTED_NO_DEBUG_TOKEN\;0xD: REJECTED_VERSION_NUM_MISMATCH\;0xE: REJECTED_USER_TIMESTAMP_MISMATCH\;0xF: REJECTED_FORBIDDEN_VERSION\;0x10: FLASH_ERASE_ERROR\;0x11: REJECTED_REBURN_RUNNING_AND_RETRY\;0x12: REJECTED_LINKX_TYPE_NOT_SUPPORTED\;0x13: REJECTED_HOST_STORAGE_IN_USE\;0x14: REJECTED_LINKX_TRANSFER (see module index in rejected_device_index)\;0x15: REJECTED_LINKX_ACTIVATE (see module index in rejected_device_index)\;0x16: REJECTED_INCOMPATIBLE_FLASH\;0x17: REJECTED_TOKEN_ALREADY_APPLIED\;0x18: REJECTED_FW_BURN_DRAM_NOT_AVAILABLE\;0x19: FW_BURN_REJECTED_INVALID_SECURITY_VERSION\;0x1A: FW_BURN_REJECTED_CERT_CER509 \;0x1B: FW_BURN_REJECTED_CERT_SIGNATURE\;0x1C: FW_BURN_REJECTED_CERT_METADATA\;0x1D: FW_BURN_REJECTED_INTERNAL_ERROR_0 \;0x1E: FW_BURN_REJECTED_NO_PLACE\;0x1F: FW_BURN_REJECTED_REMOVAL_NO_MATCH_UIDD\;0x20: FW_BURN_REJECTED_INTERNAL_ERROR_1 0x21: FW_BURN_REJECTED_INTERNAL_ERROR_2 0x22: FW_BURN_REJECTED_NUM_OF_SWAP\;0x23: FW_BURN_REJECTED_INTERNAL_ERROR_3 \;0x24: FW_BURN_REJECTED_INTERNAL_ERROR_4 0x25: FW_BURN_REJECTED_NOT_ALLOWED_SAME_UIDD \;0x26: FW_BURN_REJECTED_INTERNAL_ERROR_5 \;0x27: FW_BURN_REJECTED_INTERNAL_ERROR_6 \;0x28: FW_BURN_REJECTED_FLASH_WRITE_PROTECTED\;0x29: FW_BURN_REJECTED_INTERNAL_ERROR_7 0x2A: FW_BURN_REJECTED_INTERNAL_ERROR_8 0x2B: FW_BURN_REJECTED_INTERNAL_ERROR_90x2C: FW_BURN_REJECTED_DPA_ELF\;0x2D: FW_BURN_REJECTED_DPA_CRYPTO_BLOB\;0x2E: FW_BURN_REJECTED_DPA_APP_METADATA\;0x2F: FW_BURN_REJECTED_DPA_REMOVAL_SIGNATURE\;0x30: FW_BURN_REJECTED_DPA_CONTAINER_VERIFY\;0x31: FW_BURN_REJECTED_INTERNAL_ERROR_10 \;0x32: REJECTED_DEV_IMAGE_ON_PROD_DEVICE\;0x33: FW_BURN_REJECTED_DPA_APP_MANIFEST\;\;Other values should be treated as an unknown error." access="RO" offset="0xC.8" size="0x0.8" />
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
	<field name="offset" descr="Offset of accessed address relative to component start. Accesses must be in accordance to log_mcda_word_size in Table 2973, &quot;MCQI CAPABILITIES Info Layout,&quot; on page 3352" access="RW" offset="0x4.0" size="0x4.0" />
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
	<field name="module" descr="Module number\;NIC: Range 0 .. MGPIR.num_of_modules -1 \;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="pnv" descr="[DWIP]:\;Page Number Valid\;0: write page number\;1: don&apos;t write page number\;Valid only if module is in SW control" access="OP" offset="0x0.29" size="0x0.1" />
	<field name="l" descr="Lock Page bit. \;When bit is set, FW can access the last accessed page.\;After boot and ISSU, default value is 0.\;\;" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="device_address" descr="Device address\;\;" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="page_number" descr="Page number\;Reserved when MCIA.l = 1 or when MCIA.pnv = 1\;\;" access="INDEX" offset="0x4.16" size="0x0.8" />
	<field name="i2c_device_address" descr="I2C device address\;" access="INDEX" offset="0x4.24" size="0x0.8" />
	<field name="size" descr="Number of bytes to read/write (up to 128 bytes)" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="bank_number" descr="Bank number\;" access="INDEX" offset="0x8.16" size="0x0.8" />
	<field name="bg_mode" descr="[DWIP][switch_internal]\;Background operation\;0: Foreground mode (legacy)\;1: Background mode\;\;When working on background mode, FW shall return STS_OK immediately and return the transaction data via MCIA trap." access="OP" offset="0x8.27" size="0x0.1" />
	<field name="passwd_length" descr="0: password length is 4B (password_msb is reserved)\;1: password length is 8B (password_msb is used)" access="OP" offset="0x8.28" size="0x0.1" />
	<field name="password" descr="The password that is written to the module password field.\;This field is reserved when passwd_cap is not set to 1. \;Reserved when module is in SW control." access="OP" offset="0xC.0" size="0x4.0" />
	<field name="dword" descr="Bytes to read/write\;Note: some FW versions support only 12*4B\;See MCAM bit34" access="RW" high_bound="31" low_bound="0" offset="0x10.0" size="0x80.0" />
	<field name="password_msb" descr="password msb\;Supported only when MCAM bit34 is set\;Supported only when passwd_cap is set\;Reserved when passwd_length = 0" access="RW" offset="0x90.0" size="0x4.0" />
</node>

<node name="mcion_ext" descr="" size="0x10.0" >
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number\;NIC: Range 0 .. MGPIR.num_of_modules -1 \;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="module_status_bits" descr="Module IO status, as defined by SFF and CMIS:\;Bit 0: Present\;Bit 1: RX_LOS\;Bit 2: TX_Fault\;Bit 6: LPMode\;Bit 7: Interrupt (IntL)\;Bit 8: Low Power Mode Status \;Bit 9: Power Good\;If bit 0 (Present) is clear, all other bits are reserved." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="module_inputs" descr="Module inputs: \;Bit 0: ResetL - low polarity\;Bit 1: LPMode\;Bit 2: Power Enable\;Reserved when module is controlled by FW" access="RW" offset="0xC.0" size="0x0.4" />
	<field name="module_status_bits_valid" descr="Module Inputs Valid Bitmask\;Bitmask which mentions the validity of module_inputs fields.\;For each bit, 0 means valid, 1 means not valid.\;For example:\;Bit 0: if set, present bit value is ignored. If cleared, value is valid.\;Bit 1: if set, rx loss value is ignored. when cleared, value is valid and so on for all bits mentioned in module_inputs.\;Reserved when module is controlled by FW" access="RO" offset="0xC.16" size="0x0.16" />
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
	<field name="rd_en" descr="When set, this components may be read, see Section 10.3.4, &quot;Read Flow&quot;, on page 1134." access="RO" offset="0x10.31" size="0x0.1" />
</node>

<node name="mcqi_clock_source_properties_ext" descr="" size="0x4.0" >
	<field name="image_version_minor" descr="Image Version Minor Number" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="image_version_major" descr="Image Version Major Number" access="RO" offset="0x0.4" size="0x0.4" />
	<field name="vendor_id" descr="Clock Source Device Vendor Id\;0: Renesas\;1: SiTime 148\;2: SiTime 348\;3: TI\;4-255: Reserved" access="RO" offset="0x0.16" size="0x0.8" />
</node>

<node name="mcqi_dpa_apps_info_ext" descr="" size="0x70.0" >
	<field name="total_number_of_entries" descr="Provides the number of DPA apps in the active DPA_APPS partition.\;If there are no DPA apps, this field is equal to 0 and all the DPA_APP_METADATA fields will be 0." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="DPA_APPS_INFO version." access="RO" offset="0x0.24" size="0x0.8" />
	<field name="dpa_app_metadata" descr="DPA metadata, see Table 2987, &quot;MCQI DPA_APP_METADATA Layout,&quot; on page 3361" subnode="mcqi_dpa_metadata_ext" access="RO" offset="0x8.0" size="0x68.0" />
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
	<field name="info_type" descr="Component properties set.\;0x0: CAPABILITIES\;0x1: VERSION\;0x5: ACTIVATION_METHOD\;0x6: LINKX_PROPERTIES\;0x7: CLOCK_SOURCE_PROPERTIES\;\;0x9: DPA_APPS_INFO\;Other values are reserved" access="INDEX" enum="CAPABILITIES=0x0,VERSION=0x1,ACTIVATION_METHOD=0x5,LINKX_PROPERTIES=0x6,CLOCK_SOURCE_PROPERTIES=0x7,DPA_APPS_INFO=0x9" offset="0x8.0" size="0x0.5" />
	<field name="info_size" descr="Properties set structure size, given in bytes." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="offset" descr="The requested/returned data offset from the section start, given in bytes.\;Must be DWORD aligned.\;If offset is invalid, FW will return an error." access="INDEX" offset="0x10.0" size="0x4.0" />
	<field name="data_size" descr="The requested/returned data size, given in bytes.\;If data_size is not DWORD aligned, the last bytes are zero padded.\;If size is invalid, FW will return an error." access="INDEX" offset="0x14.0" size="0x0.16" />
	<field name="data" descr="Properties set structure according to info_type.\;CAPABILITIES - See Table 2973, &quot;MCQI CAPABILITIES Info Layout,&quot; on page 3352\;VERSION - See Table 2975, &quot;MCQI VERSION Info Layout,&quot; on page 3354\;ACTIVATION_METHOD - See Table 2979, &quot;MCQI ACTIVATION_METHOD Info Layout,&quot; on page 3356\;LINKX_PROPERTIES - See Table 2981, &quot;MCQI LINKX_PROPERTIES Info Layout,&quot; on page 3357\;CLOCK_SOURCE_PROPERTIES - See Table 2983, &quot;MCQI CLOCK_SOURCE_PROPERTIES Layout,&quot; on page 3359\;DPA_APPS_INFO - See Table 2985, &quot;MCQI DPA_APPS_INFO Layout,&quot; on page 3360" subnode="mcqi_reg_data_auto_ext" access="RO" offset="0x18.0" size="0x7c.0" union_selector="$(parent).info_type" />
</node>

<node name="mcqi_version_ext" descr="" size="0x7c.0" >
	<field name="version_string_length" descr="" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="user_defined_time_valid" descr="When set, the component has a valid user-defined version time-stamp in user_defined_time" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="build_time_valid" descr="When set, the component has a valid creation time-stamp in build_time" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="version" descr="Version number" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="build_time" descr="Time of component creation. Valid only if build_time_valid is set. See Table 2977, &quot;Date-Time Layout,&quot; on page 3355" subnode="date_time_layout_ext" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="user_defined_time" descr="User-defined time assigned to the component version. Valid only if user_defined_time_valid is set. See Table 2977, &quot;Date-Time Layout,&quot; on page 3355" subnode="date_time_layout_ext" access="RW" offset="0x10.0" size="0x8.0" />
	<field name="build_tool_version" descr="Build tool version number.\;Valid only when not equal to 0" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="version_string" descr="NULL terminated string representing the version." access="RW" high_bound="91" low_bound="0" offset="0x20.24" size="0x5c.0" />
</node>

<node name="mcqs_reg_ext" descr="" size="0x10.0" >
	<field name="component_index" descr="Component Index. Values range from 0 to the last component indicated by last_index_flag." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die. \;For cables, the index represents the module index starting at index 1. Index 0 indicates the host device.\;For Clock synchronizer, index is used to represent the clock sync&apos; device index. Starting from 1." access="INDEX" offset="0x0.16" size="0x0.12" />
	<field name="component_not_supported" descr="When set, this component not supported." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="last_index_flag" descr="When set, this component is the last component (highest component_index)." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="identifier" descr="This field uniquely identifies a specific component type. \;0x1: BOOT_IMG\;0x4: OEM_NVCONFIG\;0x5: MLNX_NVCONFIG\;0x6: CS_TOKEN\;0x7: DBG_TOKEN\;0xA: Gearbox\;0xB: CC_ALGO - Congestion Control Algorithm\;0xC: LINKX_IMG\;0xD: CRYPTO_TO_COMMISSIONING\;0xE: RMCS_TOKEN\;0xF: RMDT_TOKEN\;0x10: CRCS_TOKEN \;0x11: CRDT_TOKEN \;0x12: CLOCK_SYNC_EEPROM  \;0x15: DIGITAL_CACERT - Certificate to be trusted by the device0x17: DIGITAL_CACERT_REMOVAL\;\;0x20: PSC_TOKEN\;\;Other values are reserved\;[DWIP]: 0x1A: LINKX_FW_ELS\;\;0x1C: DPA_COMPONENT\;0x1D: DPA_COMPONENT_REMOVAL\;0x1E: MTDT_TOKEN\;" access="RO" enum="BOOT_IMG=0x1,OEM_NVCONFIG=0x4,MLNX_NVCONFIG=0x5,CS_TOKEN=0x6,DBG_TOKEN=0x7,Gearbox=0xa,CC_ALGO=0xb,LINKX_IMG=0xc,CRYPTO_TO_COMMISSIONING=0xd,RMCS_TOKEN=0xe,RMDT_TOKEN=0xf,CRCS_TOKEN=0x10,CRDT_TOKEN=0x11,CLOCK_SYNC_EEPROM=0x12,DIGITAL_CACERT=0x15,PSC_TOKEN=0x20,DPA_COMPONENT=0x1c,DPA_COMPONENT_REMOVAL=0x1d,MTDT_TOKEN=0x1e" offset="0x4.0" size="0x0.16" />
	<field name="component_update_state" descr="Component state in update flow, see Section  10.2.1, &quot;Component Update State,&quot; on page  1131:\;0x0: IDLE\;0x1: IN_PROGRESS\;0x2: APPLIED\;0x3: ACTIVE \;0x4: ACTIVE_PENDING_RESET\;0x5: FAILED\;0x6: CANCELED\;0x7: BUSY\;\;Other values are reserved" access="RO" enum="IDLE=0x0,IN_PROGRESS=0x1,APPLIED=0x2,ACTIVE=0x3,ACTIVE_PENDING_RESET=0x4,FAILED=0x5,CANCELED=0x6,BUSY=0x7" offset="0x8.0" size="0x0.4" />
	<field name="component_status" descr="The status of the component:\;0x0: NOT_PRESENT - The component is supported by the device but, currently not present\;0x1: PRESENT - This component is present. For downstream devices link LinkX component, this is an indication that the binary image is present at the host device memory.\;0x2: IN_USE - The component is present and currently in use." access="RO" enum="NOT_PRESENT=0x0,PRESENT=0x1,IN_USE=0x2" offset="0x8.4" size="0x0.5" />
	<field name="progress" descr="Progress in percentage (from 0 to 100). This field is only relevant for cables." access="RO" offset="0x8.9" size="0x0.7" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch_or_NIC\;1: Gearbox" access="INDEX" offset="0xC.0" size="0x0.8" />
	<field name="last_update_state_changer_host_id" descr="For last_update_state_changer_type BMC, command-interface and ICMD, indicates the identifier of the host of the handle owner. Otherwise reserved." access="RO" offset="0xC.24" size="0x0.4" />
	<field name="last_update_state_changer_type" descr="Indicates which entity was the last to change the component_update_state of this component.\;0x0: unspecified\;0x1: Chassis_BMC\;0x2: MAD\;0x3: BMC\;0x4: command_interface\;0x5: ICMD\;\;Other values are reserved" access="RO" enum="unspecified=0x0,Chassis_BMC=0x1,MAD=0x2,BMC=0x3,command_interface=0x4,ICMD=0x5" offset="0xC.28" size="0x0.4" />
</node>

<node name="mdir_reg_ext" descr="" size="0x40.0" >
	<field name="device_id" descr="Device ID" access="RO" high_bound="7" low_bound="0" offset="0x0.0" size="0x20.0" />
</node>

<node name="mdps_reg_ext" descr="" size="0x10.0" >
	<field name="sensor_index" descr="The sensor to stress. Each sensor description can be queried via MVCR" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="supported" descr="Returns true if the sensor supports the stressor" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="stressor_type" descr="0: Under voltage - allowed only with debug token\;1: Over voltage\;2: Voltage loss - allowed only with debug token" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="stressors_params" descr="Layout is according to stressor_type value:\;For over voltage seeTable 3082, &quot;Over Voltage Stressor Parameters Layout,&quot; on page 3429\;For under voltage seeTable 3084, &quot;Under Voltage Stressor Parameters Layout,&quot; on page 3429\;" subnode="mdps_reg_stressors_params_auto_ext" access="RW" offset="0x8.0" size="0x8.0" />
</node>

<node name="mdps_reg_stressors_params_auto_ext" descr="" attr_is_union="1" size="0x8.0" >
	<field name="over_voltage_stressor_parameters_ext" descr="" subnode="over_voltage_stressor_parameters_ext" offset="0x0.0" size="0x8.0" />
	<field name="under_voltage_stressor_parameters_ext" descr="" subnode="under_voltage_stressor_parameters_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="mdsr_reg_ext" descr="" size="0x30.0" >
	<field name="status" descr="0: The debug session ended successfully\;1: Failed to execute the operation. See additional_info for more details.\;2: Debug session active. See type_of_token for more details.\;3: No token applied\;4: Challenge provided, no token installed yet, see type_of_token for details.\;5: Timeout before token installed, see type_of_token for details\;6: Timeout of active token.\;7-15: Reserved\;\;Note: Status might be &apos;0&apos; even when debug query is not allowed and additional_info field will expose the reason." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="additional_info" descr="0: No additional information available \;1: There is no debug session in progress\;2: FW is not secured, debug session cannot be ended\;3: Fail - Debug end request cannot be accepted. \;4: Fail - Host is not allowed to query debug session\;5: Debug session active" access="RO" offset="0x0.8" size="0x0.6" />
	<field name="type_of_token" descr="0: CS token \;1: Debug FW token \;2: FRC token \;3: RMCS token\;4: RMDT token \;5: CRCS token \;6: CRDT token\;\;8: MTFA token\;0xFF: All tokens. Relevant only when end=1" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="revoke_version" descr="Set to &apos;1&apos; to end debug session.\;Setting to &apos;0&apos; will not trigger any operation." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="end" descr="Used to revoke token version from device. Relevant only when end=1." access="WO" offset="0x4.31" size="0x0.1" />
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
	<field name="event_params" descr="event parameters - layout is according to event_id value:\;See Table 3078, &quot;Event_params cvb_config_error Layout,&quot; on page 3427" subnode="mdtr_reg_event_params_auto_ext" access="RW" offset="0x10.0" size="0xa0.0" union_selector="$(parent).event_id" />
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

<node name="mfrl_reg_ext" descr="" size="0x8.0" >
	<field name="reset_trigger" descr="The firmware reset trigger.\;Bit 0: TRIGGER0 - live patch. When selecting this trigger, all other fields are NA.\;Bit 1: TRIGGER1 - Immediate Reset. Note that this reset trigger must be selected explicitly by user and cannot be triggered as part of default logic.\;Bit 3: TRIGGER3 - PCIe link toggle or hot reset. For this reset trigger, you need to configure pci_reset_req_method.\;Bit 6: TRIGGER6 - PERST\;Other bits are reserved." access="RW" enum="TRIGGER0=0x1,TRIGGER1=0x2,TRIGGER3=0x8,TRIGGER6=0x40" offset="0x4.0" size="0x0.8" />
	<field name="reset_type" descr="Each bit represents a chip reset type.\;If set to &apos;1&apos;, the reset is supported.\;Bit 0: Full_Chip_Reset\;Bit 1: Keep_Network_Port_Active_During_Reset\;Bit 3: ARM_Only_Reset\;Bit 4: ARM_OS_Shutdown\;Bit 5: Network_Reset - Keep PCIe active during reset. DWIP" access="RO" enum="Full_Chip_Reset=0x1,Keep_Network_Port_Active_During_Reset=0x2,ARM_Only_Reset=0x8,ARM_OS_Shutdown=0x10,Network_Reset=0x20" offset="0x4.8" size="0x0.8" />
	<field name="reset_state" descr="Reset state.\;0: IDLE\;1: Negotiation_In_Progress\;2: Reset_In_Progress\;3: Error_Negotiation_Timeout\;4: Error_Negotiation_Dis_Acknowledgment\;5: Error_Driver_Unload_Timeout - DWIP\;6: Error- ARM_OS_Is_Up - please shut down. DWIP\;7: ARM_OS_Shut_Down_In_Progress - DWIP\;8: Waiting_For_Reset_Trigger\;All others are reserved" access="RO" enum="IDLE=0x0,Negotiation_In_Progress=0x1,Reset_In_Progress=0x2,Error_Negotiation_Timeout=0x3,Error_Negotiation_Dis_Acknowledgment=0x4,Error_Driver_Unload_Timeout=0x5,Error=0x6,ARM_OS_Shut_Down_In_Progress=0x7,Waiting_For_Reset_Trigger=0x8" offset="0x4.16" size="0x0.4" />
	<field name="pci_reset_req_method" descr="FW reset Method selector; Support for the different reset methods exposed through reset_info register. \;0: Link_Disable\;1: Hot_Reset - SBR)\;All others are reserved" access="RW" enum="Link_Disable=0x0,Hot_Reset=0x1" offset="0x4.21" size="0x0.3" />
	<field name="rst_type_sel" descr="The requested reset type.\;When reset_trigger = Immediate (1), reset_type_sel valid values are: bit3 or bit4 (ARM only reset or ARM os shutdown)" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="pci_sync_for_fw_update_resp" descr="Response of the driver for the reset request.\;1: Acknowledgment\;2: Dis_acknowledgment\;3: Reserved" access="WO" enum="Acknowledgment=0x1,Dis_acknowledgment=0x2,Reserved=0x3" offset="0x4.27" size="0x0.2" />
	<field name="pci_sync_for_fw_update_start" descr="This field defines the reset flow. \;0: Legacy_Flow\;1: Synced_Driver_Flow\;2: Synced_Tool_Flow\;Synced driver flow will not require to issue MFRL command\;from other hosts (x86 / ARM for SoC)\;Synced tool flow required to be executed from external host (should not be executed from internal host)." access="RW" enum="Legacy_Flow=0x0,Synced_Driver_Flow=0x1,Synced_Tool_Flow=0x2" offset="0x4.29" size="0x0.2" />
	<field name="pci_rescan_required" descr="Setting this bit to 1 indicates a need of rescan for the corresponding PCI slot" access="RO" offset="0x4.31" size="0x0.1" />
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
	<field name="hw_info" descr="Hardware Information, see Table 3001, &quot;Hardware Info Layout,&quot; on page 3374" subnode="mgir_hardware_info_ext" access="RW" offset="0x0.0" size="0x20.0" />
	<field name="fw_info" descr="Firmware Information, see Table 3004, &quot;Firmware Info Layout,&quot; on page 3377" subnode="mgir_fw_info_ext" access="RW" offset="0x20.0" size="0x40.0" />
	<field name="sw_info" descr="Software Information, see Table 3006, &quot;Software Info Layout,&quot; on page 3380\;This field indicates the oldest software version compatible with the current firmware" subnode="mgir_sw_info_ext" access="RW" offset="0x60.0" size="0x20.0" />
	<field name="dev_info" descr="Development Information, see Table 3010, &quot;Development Info Layout,&quot; on page 3384" subnode="mgir_dev_info_ext" access="RW" offset="0x80.0" size="0x1c.0" />
</node>

<node name="mgir_fw_info_ext" descr="" size="0x40.0" >
	<field name="sub_minor" descr="Sub-minor firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_sub_minor." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="minor" descr="Minor firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_minor." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="major" descr="Major firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_major." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="secured" descr="When set, the device is running firmware with secure-firmware updates capabilities." access="RO" offset="0x0.24" size="0x0.1" />
	<field name="signed_fw" descr="When set the device is running a signed FW binaries." access="RO" offset="0x0.25" size="0x0.1" />
	<field name="debug" descr="When set, the device is running a debug firmware. &apos;debug&apos; binary can only be installed on specific devices (identified by their &apos;Factory base MAC&apos;), which currently run a specific firmware version. These restrictions are expressed by a signed &apos;debug&apos; token that must be loaded to the device before installing the debug binary." access="RO" offset="0x0.26" size="0x0.1" />
	<field name="dev" descr="*NOTE* this field has diff meaning for Switch vs. NIC \;\;NIC:\;The device is running:\;0: a regular-secure firmware version\;1: a development-secure firmware version\;\;" access="RO" offset="0x0.27" size="0x0.1" />
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
	<field name="life_cycle" descr="Note: has also msb bits in life_cycle_msb. Following values are a combination of both fields.\;0: Production\;1: GA Secured\;2: GA Non-Secured\;3: RMA\;4: Pre Production\;" access="RO" offset="0x34.0" size="0x0.2" />
	<field name="sec_boot" descr="0: Disable\;1: Enable" access="RO" offset="0x34.2" size="0x0.1" />
	<field name="encryption" descr="0: Disable\;1: Enable" access="RO" offset="0x34.3" size="0x0.1" />
	<field name="life_cycle_msb" descr="[DWIP]\;MSB of the life cycle.\;Supported in QM3, CX8 and on.\;See life_cycle field for full value descriptions." access="RO" offset="0x34.4" size="0x0.3" />
	<field name="dev_state" descr="0: device is in prod mode\;1: device is in dev mode" access="RO" offset="0x34.11" size="0x0.1" />
	<field name="issu_able" descr="[DWIP]\;ISSU-able:\;0: not ISSUable\;1: ISSUable\;Supported from Quantum-3 and on\;Supported for Retimers\;Based on FW decisions: fuse, INI, NV and version on flash vs. running version" access="RO" offset="0x34.13" size="0x0.1" />
	<field name="pds" descr="[DWIP]\;0: PSC is not PDS mode\;1: PSC in PDS mode\;Supported in QM3,CX8 and on." access="RO" offset="0x34.14" size="0x0.1" />
	<field name="ec_offload_engine_disabled" descr="[NIC_Only]\;When set, the embedding CPU engine is disabled\;Valid for devices that supports embedded CPU (SOC)\;\;" access="RO" offset="0x34.15" size="0x0.1" />
	<field name="dev_counter" descr="Counter indication of dev fuse value" access="RO" offset="0x34.16" size="0x0.5" />
</node>

<node name="mgir_hardware_info_ext" descr="" size="0x20.0" >
	<field name="device_id" descr="PCI device ID." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="device_hw_revision" descr="See Table 3003, &quot;Device HW Revision Descriptions,&quot; on page 3376" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="pvs" descr="Process Voltage Scaling\;Supported nominal V_CORE voltage (in 50mV units) for the device." access="RO" offset="0x4.0" size="0x0.5" />
	<field name="technology" descr="Process technology\;0: N/A\;1: 40nm\;2: 28nm\;3: 16nm\;4: 7nm\;5: 5nm\;6-31: Reserved" access="RO" offset="0x4.11" size="0x0.5" />
	<field name="num_ports" descr="Number of ports the device supports." access="RO" offset="0x4.16" size="0x0.12" />
	<field name="ib_mad_gen" descr="[DWIP]\;IB MAD Protocol. Based on value from ConfigProfile\;0: IBg1\;1: IBg2\;2-7: Reserved" access="RO" offset="0x4.28" size="0x0.3" />
	<field name="hw_dev_id" descr="The PCI device-ID of the NIC/HCA in recovery (Livefish) mode." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="module_master_fw_default" descr="Module Master FW Default\;0: FW is in control over modules management by default\;1: SW is in control over modules management by default\;2: Standalone ASIC (no I2C connectivity).\; Note: Relevant only for Spectrum-3 and above" access="RO" offset="0xC.16" size="0x0.2" />
	<field name="cpo_indication" descr="[DWIP][switch_internal] \;When set, this bit indicate this is CPO system" access="RO" offset="0xC.27" size="0x0.1" />
	<field name="ga_valid" descr="GA Valid bit\;0: MGIR.HW Info.ga is reserved\;1: MGIR.HW Info.ga is valid\;\;Supported in CX7, QM3 and on." access="RO" offset="0xC.28" size="0x0.1" />
	<field name="development" descr="[DWIP]\;The device is running:\;0: a regular-secure firmware version\;1: a development-secure firmware version\;\;Supported in QM3,CX8 and on." access="RO" offset="0xC.30" size="0x0.1" />
	<field name="pci_switch_only_mode" descr="0: Embedded HCA PCIe endpoint enabled\;1: Embedded HCA PCIe endpoint disabled" access="RO" offset="0xC.31" size="0x0.1" />
	<field name="manufacturing_base_mac_47_32" descr="MSB of the &quot;base&quot; MAC address of the NIC that was allocate during manufacturing. The NIC derives the MAC addresses for the different PCI PFs from this MAC address. This parameter can be used as a canonical unique identifier of the NIC.\;manufacturing_base_mac of value 0 means field is not supported." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="ga" descr="[DWIP]\;Geographical Address\;0: ASIC 0\;1: ASIC 1\;2: ASIC 2\;3: ASIC 3\;Valid for multi ASIC platforms only\;\;." access="RO" offset="0x10.16" size="0x0.6" />
	<field name="chip_type" descr="[DWIP]\;Chip Type\;0: Real chip\;1: Emulation\;2: ChipSim\;3: SimX \;Supported from Quantum-3 and ArcusE" access="RO" offset="0x10.24" size="0x0.4" />
	<field name="manufacturing_base_mac_31_0" descr="LSB of the &quot;base&quot; MAC address of the NIC that was allocate during manufacturing. The NIC derives the MAC addresses for the different PCI PFs from this MAC address. This parameter can be used as a canonical unique identifier of the NIC.\;manufacturing_base_mac of value 0 means field is not supported." access="RO" offset="0x14.0" size="0x4.0" />
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

<node name="mhmpr_reg_ext" descr="" size="0x14.0" >
	<field name="upm" descr="&apos;0&apos; - if the ports are managed by host.\;&apos;1&apos; - if the ports are not managed by host" access="RW" offset="0x0.0" size="0x0.1" />
</node>

<node name="midfv_reg_ext" descr="" size="0x80.0" >
	<field name="dev_branch_tag" descr="The format of the string represented by ASCII.\;" access="RO" high_bound="63" low_bound="0" offset="0x4.24" size="0x40.0" />
</node>

<node name="midv_reg_ext" descr="" size="0x28c.0" >
	<field name="part_number" descr="Requested part number for the current query." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="number_of_parts" descr="Total number of parts the DOCA JSON string is split to. Only valid when part_number = 0." access="RO" offset="0x0.16" size="0x0.16" />
	<field name="length" descr="Length of the version in the version field (including null terminator if present)." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="info_not_available" descr="If true, the version information for this component type is currently unavailable. In this case the version field will be all zeros, and length will be zero." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="version" descr="The version as an ASCII string (might not be null terminated)." access="RO" high_bound="639" low_bound="0" offset="0xC.24" size="0x280.0" />
</node>

<node name="mirc_reg_ext" descr="" size="0x8.0" >
	<field name="status_code" descr="Indicates the successful completion of the instruction, or the reason it failed. See Section  10.3.7, &quot;Error Handling,&quot; on page  1134\;0x0: OK\;0x1: BUSY\;0x2: PROHIBITED_FW_VER_ERR\;0x3: FIRST_PAGE_COPY_FAILED\;0x4: FIRST_PAGE_ERASE_FAILED\;0x5: FIRST_PAGE_RESTORE_FAILED\;0x6: CANDIDATE_FW_DEACTIVATION_FAILED\;0x7: FW_ALREADY_ACTIVATED\;0x8: ERROR_DEVICE_RESET_REQUIRED\;0x9: ERROR_FW_PROGRAMMING_NEEDED\;Other values should be treated as an unknown error." access="RO" offset="0x0.0" size="0x0.8" />
</node>

<node name="misoc_reg_ext" descr="" size="0x120.0" >
	<field name="type" descr="Type of component query:\;0x0: ARM_ATF\;0x1: ARM_UEFI\;0x2: DPU_BMC\;0x3: CEC\;0x5: BF_BUNDLE\;0x7: BSP\;0x8: NIC_GOLDEN\;0x9: ARM_GOLDEN\;All other values are reserved" access="INDEX" enum="ARM_ATF=0x0,ARM_UEFI=0x1,DPU_BMC=0x2,CEC=0x3,BF_BUNDLE=0x5,BSP=0x7,NIC_GOLDEN=0x8,ARM_GOLDEN=0x9" offset="0x0.0" size="0x0.4" />
	<field name="query_pending" descr="If set, the query will be for the pending version instead on the current version" access="INDEX" offset="0x0.30" size="0x0.1" />
	<field name="query_not_available" descr="If set, the version information for this component type is not available\;In this case the version will be all zeros" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="version" descr="The version as a null-terminated ASCII string\;Null termination will not be present if version takes up all of the field size" access="RO" high_bound="255" low_bound="0" offset="0x10.24" size="0x100.0" />
</node>

<node name="mjtag_ext" descr="" size="0x30.0" >
	<field name="size" descr="Size of operation - relevant for JTAG interface access commands only, indicating the number of transaction bytes to execute. Maximum size supported is 40.\;Note: when size=0, no operation is performed (clock is not toggled). The tdo is sampled and provided in the response at jtag_transaction_set_0." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="sequence_number" descr="Command sequence number - to prevent re-execution of the same command due to command retransmission, this command includes a sequence number.\;The enable and disable commands MUST be issues with sequence_number = 0 while any JTAG access command must increase the sequence_number by 1 (the first JTAG access command should start at sequence_number = 1)." access="WO" offset="0x0.24" size="0x0.4" />
	<field name="cmd" descr="Command\;0 - JTAG interface disable - JTAG interface is disabled\;1 - JTAG interface enable - enabling JTAG interface\;2 - JTAG interface access" access="RW" offset="0x0.30" size="0x0.2" />
	<field name="jtag_transaction_set" descr="See Table 2810, &quot;JTAG Transaction Set Byte Layout,&quot; on page 3217" access="RW" high_bound="43" low_bound="0" offset="0x4.24" size="0x2c.0" />
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

<node name="mmhi_reg_ext" descr="" size="0x80.0" >
	<field name="host_number" descr="Identifier for the host used to access the register" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="host_en" descr="Bit per Host, when set indicating this host is present in the current Multi-Host configuration.\;Value 0x0 indicates this field in not valid." access="RO" offset="0x8.0" size="0x0.16" />
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
	<field name="writer_id" descr="The entity which perform the invalidate.\;The encoding same as writer_id in Configuration Item register (See Table 3110, &quot;Configuration Item Header Layout,&quot; on page 3446)." access="RW" offset="0x0.4" size="0x0.5" />
</node>

<node name="mnvqc_reg_ext" descr="" size="0x8.0" >
	<field name="type" descr="Configuration item type according to its class. \;Table 3112, &quot;Configuration Item Data Type Class Global Layout,&quot; on page 3450\;Table 3114, &quot;Configuration Item Data Type Class Physical Port Layout,&quot; on page 3450\;Table 3116, &quot;Configuration Item Data Type Class Per Host-PF Layout,&quot; on page 3451\;Table 3118, &quot;Configuration Item Data Type Class Log Layout,&quot; on page 3451\;Table 3120, &quot;Configuration Item Data Type Class File Layout,&quot; on page 3452\;Table 3122, &quot;Configuration Item Data Type Class Host Layout,&quot; on page 3452\;\;Table 3126, &quot;Configuration Item Data Type Class Multi Instance Layout,&quot; on page 3454" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="support_rd" descr="The configuration item is supported and can be read" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="support_wr" descr="The configuration item is supported and can be updated" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="version" descr="The maximal version of the configuration item supported by the device" access="RO" offset="0x4.4" size="0x0.4" />
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

<node name="mpcam_reg_ext" descr="" size="0x48.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: First_128_REG_ID - Register IDs 0x9000 - 0x907F)\;1: Register_IDs_0x9080 - 0x90FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9080 while bit 127 represents register ID 0x90FF).\;2: Register_IDs_0x9100 - 0x917F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9100 while bit 127 represents register ID 0x917F).\;3: Register_IDs_0x9180 - 0x91FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9180 while bit 127 represents register ID 0x91FF).\;4: Register_IDs_0x9200 - 0x927F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9200 while bit 127 represents register ID 0x927F).\;5: Register_IDs_0x9280 - 0x92FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9280 while bit 127 represents register ID 0x92FF).\;6: Register_IDs_0x9300 - 0x937F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9300 while bit 127 represents register ID 0x937F).\;7: Register_IDs_0x9380 - 0x93FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9380 while bit 127 represents register ID 0x93FF).\;8: Register_IDs_0x9400 - 0x947F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9400 while bit 127 represents register ID 0x947F).\;9: Register_IDs_0x9480 - 0x94FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9480 while bit 127 represents register ID 0x94FF).\;10: Register_IDs_0x9500 - 0x957F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9500 while bit 127 represents register ID 0x957F).\;11: Register_IDs_0x9580 - 0x95FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9580 while bit 127 represents register ID 0x95FF).\;12: Register_IDs_0x9600 - 0x967F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9600 while bit 127 represents register ID 0x967F).\;13: Register_IDs_0x9680 - 0x96FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9680 while bit 127 represents register ID 0x96FF).\;14: Register_IDs_0x9700 - 0x977F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9700 while bit 127 represents register ID 0x967F).\;15: Register_IDs_0x9780 - 0x97FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9780 while bit 127 represents register ID 0x97FF)." access="INDEX" enum="First_128_REG_ID=0x0,Register_IDs_0x9080=0x1,Register_IDs_0x9100=0x2,Register_IDs_0x9180=0x3,Register_IDs_0x9200=0x4,Register_IDs_0x9280=0x5,Register_IDs_0x9300=0x6,Register_IDs_0x9380=0x7,Register_IDs_0x9400=0x8,Register_IDs_0x9480=0x9,Register_IDs_0x9500=0xa,Register_IDs_0x9580=0xb,Register_IDs_0x9600=0xc,Register_IDs_0x9680=0xd,Register_IDs_0x9700=0xe,Register_IDs_0x9780=0xf" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="mng_access_reg_cap_mask" descr="Supported management&apos;s access register bitmaks.Based on access_reg_group index. \;When bit is set, the register is supported in the device. \;For example:\;Bit 1: MFCR_0x9001\;Bit 2: MFSC_0x9002\;Bit 3: MFSM_0x9003\;Bit 4: MFSL_0x9004\;Bit 58: MGCR_0x903A\;Bit 73: MPPF_0x9049\;Bit 127: MCAP_0x907F\;Note that up to version XXX management and PCIe are in the same base id so MCAM and MPCAM are similar in this field" access="RO" enum="MFCR_0x9001=0x2,MFSC_0x9002=0x4,MFSM_0x9003=0x8,MFSL_0x9004=0x10,MGCR_0x903A=0x4000000,MPPF_0x9049=0x200,MCAP_0x907F=0x80000000" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="mng_feature_cap_mask" descr="Supported port&apos;s enhanced features.Based on feature_group index.\;When bit is set, The feature is supported in the device: \;Bit 0: MPCNT counter group- PCIE performance counters supported\;Bit 3: tx_lossy_overflow_oper - If set, tx_overflow_buffer_pkt counter in MPCNT register is supported.\;Bit 4: pcie_outbound_stalled - if set, outbound_stalled_reads, outbound_stalled_writes, outbound_stalled_reads_events and outbound_stalled_writes_events counters in MPCNT are supported.\;Bit 9 - dynamic_tx_overflow - If set, tx_overflow_sense field is supported in MPEGC register. \;Bit 17 - pwr_status and pci_power are supported in MPEIN\;Bit 19 - pcie_sync_for_fw_update_supported is set to &apos;1&apos;\;Bit 22 - If set to &apos;1&apos;, link_peer_max_speed is supported in MPEIN Register\;Bit 29: If set, virtual hot plug / unplug is supported in MPEGC.\;Bit 30: If set, my_pf_number is supported in MPPF.\;Bit 45: If set, MFRL.pci_rescan_required is supported\;Bit 68: If set, DPNv is supported\;Bit 77: If set, host_id field in MPIR is supported\;Bit 78: If set, FBER, FEC correctable and FEC uncorrectable reporting is supported in MPCNT group 0\;Bit 79: If set the MPCNT performance counter 2 is supported\;Bit 80: pcie_segment - if set the MPIR and MPEGC registers supports the segment base, segment_cap and segment_valid are supported.\;Bit 81: cmn_clk_mode- if set the the cmn_clk_mode bit in the MPEIN registers is supported.\;bit 83: lane_cdr_error - if set the lane cdr error field in MPCNT PCIE lane counter group is supported.\;bit 84: mpcnt_perf_cnt_2_ver1 - if set the MPCNT PCIE performance counter 2 version 1 is supported, else version 0 is supported.\;Note - up to bit 77 this is common to MCAM due to legacy reasons." access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="mpcir_ext" descr="" size="0xa0.0" >
	<field name="instance" descr="Bitmask of which instance to select.\;Relevant only to vmod.\;0: update vmod 0\;1: update vmod 1\;..." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="fw_entity" descr="Bitmask of which FW entity to select.\;0: switch_fw\;1: virtual_module\;\;note - if all bits are zero fw_entity will be switch_fw (legacy)\;If more than one bit is set instance field will be ignored - update all instances." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="all" descr="If set to &apos;01&apos;, activates the flow of preparation for FW ISSU, on all services. The values in op-codes for &quot;per-service&quot; are ignored.\;If set to &apos;10&apos;, returns to operational state on all services. The values in op-codes for &quot;per-service&quot; are ignored.\;11 - get_status for all services" access="OP" offset="0x0.30" size="0x0.2" />
	<field name="ports" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding _stat fields." access="OP" offset="0x4.0" size="0x0.2" />
	<field name="ports_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done service handling [Internal]: busy with some other critical flow)." access="RO" offset="0xC.0" size="0x0.2" />
</node>

<node name="mpcnt_reg_counter_set_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="pcie_perf_counters2_ext" descr="" subnode="pcie_perf_counters2_ext" offset="0x0.0" selected_by="PCIE_performance_counters_2" size="0xf8.0" />
	<field name="pcie_perf_counters_ext" descr="" subnode="pcie_perf_counters_ext" offset="0x0.0" selected_by="PCIE_performance_counters" size="0xf8.0" />
	<field name="pcie_physical_layer_ext" descr="" subnode="pcie_physical_layer_ext" offset="0x0.0" selected_by="PCIE_physical_layer_indications" size="0x4.0" />
</node>

<node name="mpcnt_reg_ext" descr="" size="0x100.0" >
	<field name="grp" descr="Performance counter group.\;0: PCIE_performance_counters\;3: PCIE_physical_layer_indications\;4: PCIE_performance_counters_2" access="INDEX" enum="PCIE_performance_counters=0x0,PCIE_physical_layer_indications=0x3,PCIE_performance_counters_2=0x4" offset="0x0.0" size="0x0.6" />
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIe index number (Internal domain index)\;Reserved when access is from the host" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="DPNv" descr="DPN version\;0: multi_topology_unaware_sw\;1: multi_topology_aware_sw" access="INDEX" enum="multi_topology_unaware_sw=0x0,multi_topology_aware_sw=0x1" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Clear counters. Setting the clr bit will reset the counter value for all counters in the counter group. This bit can be set for both Set() and Get() operation." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="counter_set" descr="Counter set as described in\;Table 31, &quot;PCIe Performance Counters Data Layout,&quot; on page 379\;Table 37, &quot;PCIE Physical Layer Indication Layout,&quot; on page 387\;Table 39, &quot;PCIe Performance Counters 2 Data Layout,&quot; on page 388" subnode="mpcnt_reg_counter_set_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).grp" />
</node>

<node name="mpcs_reg_ext" descr="" size="0x50.0" >
	<field name="channel" descr="0: 12V channel\;1: 3.3V channel\;2: 12V ATX channel (if applicable)" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="enabled" descr="Power Capping enabled" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="power_capping_counter" descr="Counter of power capping events" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="max_power" descr="Sticky value of the highest power measured for each channel in Watts." access="RO" offset="0x8.0" size="0x0.8" />
	<field name="small_window_average" descr="The last power average over the window of num_of_avg * time_unit\;" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="power_meas" descr="Last power measurements in Watts." access="RO" high_bound="63" low_bound="0" offset="0x10.24" size="0x40.0" />
</node>

<node name="mpecs_reg_ext" descr="" size="0x20.0" >
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIE index number\;Reserved when access is from the host" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="DPNv" descr="DPN version\;0: multi_topology_unaware_sw\;1: multi_topology_aware_sw" access="INDEX" enum="multi_topology_unaware_sw=0x0,multi_topology_aware_sw=0x1" offset="0x0.30" size="0x0.1" />
	<field name="capability_id" descr="capability ID as defined in PCIE spec" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="reg_num" descr="Register number\;Byte offset from the beginning of the capability ID" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="byte_enable" descr="Enable bit per byte\;bit 0 - byte 0 (bits 7:0)\;bit 1 - byte 1 (bits 15:8)\;bit 2 - byte 2 (bits 23:16)\;bit 3 - byte 3 (bits 31:24)\;Reserved for read operation." access="WO" offset="0xC.0" size="0x0.4" />
	<field name="status" descr="PCIE configuration space access status: \;0x0: SUCCESS - successful access\;0x1: FUNC_NUM_FAILURE - accessing unsupported configuration space function number\;0x2: CAP_ID_FAILURE - accessing unsupported configuration space capability ID number\;0x3: REG_NUM_FAILURE - accessing unsupported configuration space register number\;0x4: WRITE_FAILURE - write access to read-only configuration space\;0x5: PROTECTED_FAILURE - protected configuration" access="RO" enum="SUCCESS=0x0,FUNC_NUM_FAILURE=0x1,CAP_ID_FAILURE=0x2,REG_NUM_FAILURE=0x3,WRITE_FAILURE=0x4,PROTECTED_FAILURE=0x5" offset="0xC.8" size="0x0.8" />
	<field name="func_num" descr="Function number\;physical function index - see PCIE spec" access="INDEX" offset="0xC.16" size="0x0.8" />
	<field name="ext" descr="Extended or regular configuration space, as defined in PCIE spec:\;0 - Regular\;1 - Extended" access="INDEX" offset="0x10.0" size="0x0.2" />
	<field name="data" descr="" access="RW" offset="0x14.0" size="0x4.0" />
</node>

<node name="mpegc_reg_ext" descr="" size="0x2c.0" >
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIe index number (Internal domain index)\;Reserved when access is from the host" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="DPNv" descr="DPN version\;0: multi_topology_unaware_sw\;1: multi_topology_aware_sw" access="INDEX" enum="multi_topology_unaware_sw=0x0,multi_topology_aware_sw=0x1" offset="0x0.30" size="0x0.1" />
	<field name="field_select" descr="Field select indicated which writable fields to modify.\;Bit 0: tx_lossy_overflow_oper\;Bit 1 : outbound_stalled_reads_th\;Bit 2 :outbound_stalled_writes_th\;Bit 3 : tx_overflow_sense\;Bit 4 : mark_tx_action_cqe\;Bit 5 : mark_tx_action_cnp\;Bit 6: virtual_hot_plug_unplug (supported only for internal host)\;Bit 7: segment_base and segment_valid" access="WO" offset="0x4.0" size="0x0.16" />
	<field name="tx_lossy_overflow_oper" descr="When overflow encountered for lossy packets, it will be dropped or marked and will be counted in &quot;tx_overflow_buffer_dropped_pkt&quot; or &quot;tx_overflow_buffer_marked_pkt&quot; counter.\;00 - Disabled\;01 - drop - overflow traffic will be dropped.  \;10 - mark - overflow traffic will be marked in the CE field in the CqE.  Supported only when MCAM.mark_tx_action_cqe or MCAM.mark_tx_action_cnp are &apos;1&apos;. \;" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="segment_base" descr="segment number associated with the link PCI hierarchy\;The value here will be reflected in the MPIR segment base\;reserved when pcie_segment is not set in MPCAM" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="segment_valid" descr="when set the segment base is valid, when clear the segment base is invalid\;the value here will be reflected in the MPIR segment_valid\;reserved when pcie_segment is not set in MPCAM" access="RW" offset="0x8.24" size="0x0.1" />
	<field name="mark_cnp" descr="When this bit is set, the marking action will be generating a CNP for RoCE traffic. Supported only when MCAM.mark_tx_action_cnp is &apos;1&apos;." access="RW" offset="0x8.29" size="0x0.1" />
	<field name="mark_cqe" descr="When this bit is set, the marking action will be set in the CqE for TCP traffic. Supported only when MCAM.mark_tx_action_cqe is &apos;1&apos;." access="RW" offset="0x8.30" size="0x0.1" />
	<field name="tx_overflow_sense" descr="Set the sensibility level of the tx overflow mechanism. \;0 - Aggressive 1 - Dynamic adjustment. When tx_lossy_overflow_oper is disabled, tx_overflow_sense must be disabled. Supported only when MCAM.dynamic_tx_oveflow is &apos;1&apos;." access="RW" offset="0x8.31" size="0x0.1" />
	<field name="outbound_stalled_writes_th" descr="Each time that the counter outbound_stalled_writes will exceed this threshold, will be counted in the counter outbound_stalled_writes_events - range 0   100." access="RW" offset="0xC.0" size="0x0.7" />
	<field name="outbound_stalled_reads_th" descr="Each time that the counter outbound_stalled_reads will exceed this threshold, will be counted in the counter outbound_stalled_reads_events - range 0   100." access="RW" offset="0xC.8" size="0x0.7" />
	<field name="operation" descr="Operation to perform\;0: Idle - no operation required (default)\;1: Emulate hot removal\;2: Emulate hot insertion\;3-15: Reserved" access="RW" offset="0x10.16" size="0x0.4" />
	<field name="status" descr="Operation completion status\;0: Operation in process\;1: Unplugged\;2: Plugged\;3: Warning - disconnecting an already disconnected bus cannot be performed\;4: Warning - connecting an already connected bus cannot be performed\;5: Error - unknown bus number or no device installed on selected bus" access="RO" offset="0x10.24" size="0x0.8" />
</node>

<node name="mpein_reg_ext" descr="" size="0x30.0" >
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIe index number (Internal domain index)\;Reserved when access is from the host, but can be used when operating in Socket-Direct mode." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="DPNv" descr="DPN version\;0: multi_topology_unaware_sw\;1: multi_topology_aware_sw" access="INDEX" enum="multi_topology_unaware_sw=0x0,multi_topology_aware_sw=0x1" offset="0x0.30" size="0x0.1" />
	<field name="link_speed_enabled" descr="Max Link Speed:\;Bit 0: 2.5G - (Gen1)\;Bit 1: 5G - (Gen2)\;Bit 2: 8G - (Gen3)\;Bit 4: 16G - (Gen4)\;Bit 5: 32G (Gen5)\;Bit 6: 32G PAM-4 (Gen6)" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="link_width_enabled" descr="Maximum Link Width enabled:\;1: 1x\;2: 2x\;4: 4x\;8: 8x\;16: 16x" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="link_speed_active" descr="Current Link Speed:\;Bit 0: 2.5G (Gen1)\;Bit 1: 5G (Gen2)\;Bit 2: 8G (Gen3)\;Bit 4: 16G (Gen4)\;Bit 5: 32G (Gen5)\;Bit 6: 32G PAM-4 (Gen6)" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="link_width_active" descr="Negotiated Link Width, pcie_link_width active:\;1: 1x\;2: 2x\;4: 4x\;8: 8x\;16: 16x" access="RO" offset="0xC.16" size="0x0.8" />
	<field name="lane0_physical_position" descr="The physical lane position of logical lane0" access="RO" offset="0xC.24" size="0x0.8" />
	<field name="num_of_vfs" descr="Number of Total Virtual Functions (for all PFs)" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="num_of_pfs" descr="Number of Physical Functions (PFs)" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="bdf0" descr="Bus Device Function - only for function0" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="lane_reversal" descr="Reversal mode of the link:\;0 - straight \;1 - reversal\;\;Note: together with lane0_physical_position provide the physical lane." access="RO" offset="0x18.0" size="0x0.1" />
	<field name="cmn_clk_mode" descr="common clock mode:\;0 - separate clock mode\;1 - common clock mode" access="RO" offset="0x18.1" size="0x0.1" />
	<field name="port_type" descr="Indicates the specific type of this PCI Express Function. Note that different Functions in a multi-Function device can generally be of different types.\;0 - PCI Express Endpoint port\;4 - Root Port of PCI Express Root Complex\;5 - PCI Express Upstream port\;6 - PCI Express Downstream port" access="RO" offset="0x18.12" size="0x0.4" />
	<field name="pwr_status" descr="Indicates the status of PCI power consumption limitations.\;0: PCI power report could not be read.\;1: Sufficient power reported.\;2: Insufficient power reported.\;3-7: Reserved" access="RO" offset="0x18.16" size="0x0.3" />
	<field name="max_payload_size" descr="Max payload size in bytes:\;0 - 128B\;1 - 256B\;2 - 512B\;3 - 1024B\;4 - 2048B\;5 - 4096B" access="RO" offset="0x18.24" size="0x0.4" />
	<field name="max_read_request_size" descr="Max read request size in bytes:\;0 - 128B\;1 - 256B\;2 - 512B\;3 - 1024B\;4 - 2048B\;5 - 4096B" access="RO" offset="0x18.28" size="0x0.4" />
	<field name="pci_power" descr="Power reported by the PCI device. The units are in Watts.\;0: Power is unknown." access="RO" offset="0x1C.0" size="0x0.12" />
	<field name="link_peer_max_speed" descr="Peer Max Link Speed:\;Bit 0: 2.5G - (Gen1)\;Bit 1: 5G - (Gen2)\;Bit 2: 8G - (Gen3)\;Bit 4: 16G - (Gen4)\;Bit 5: 32G (Gen5)\;Bit 6: 32G PAM-4 (Gen6)" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="flit_sup" descr="FLIT is supported for the current active speed" access="RO" offset="0x20.0" size="0x0.1" />
	<field name="precode_sup" descr="Precoding is supported for the current active speed" access="RO" offset="0x20.1" size="0x0.1" />
	<field name="flit_active" descr="FLIT is active for the current speed" access="RO" offset="0x20.8" size="0x0.1" />
	<field name="precode_active" descr="precoding is active for the current speed" access="RO" offset="0x20.9" size="0x0.1" />
	<field name="device_status" descr="device_status bit mask:\;Bit 0: Correctable_error\;Bit 1: Non_Fatal_Error_detection\;Bit 2: Fatal_Error_detected\;Bit 3: Unsupported_request_detected\;Bit 4: AUX_power \;Bit 5: Transaction_Pending" access="RO" enum="Correctable_error=0x1,Non_Fatal_Error_detection=0x2,Fatal_Error_detected=0x4,Unsupported_request_detected=0x8,AUX_power=0x10,Transaction_Pending=0x20" offset="0x24.16" size="0x0.16" />
</node>

<node name="mpeinj_reg_ext" descr="" size="0x40.0" >
	<field name="error_type" descr="Error type selector.\;See at Table  55, &quot;MPEINJ Error List and Params,&quot; on page  406 for error_index." access="RW" offset="0x0.0" size="0x0.8" />
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIE index number\;Reserved when access is from the host" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="DPNv" descr="DPN version\;0: multi_topology_unaware_sw\;1: multi_topology_aware_sw" access="INDEX" enum="multi_topology_unaware_sw=0x0,multi_topology_aware_sw=0x1" offset="0x0.30" size="0x0.1" />
	<field name="error_duration" descr="Depending on the error type, can be either -    \;Number of packets or number of usecs to apply the error according to Table  55, &quot;MPEINJ Error List and Params,&quot; on page  406.\;For Read access, the current value is returned (how many errors/time are left to be executed), or 0 if no error is pending injection" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="start_delay" descr="Delay in usecs before the error is applied.\;For Read access, the current value of this timer is returned." access="RW" offset="0x8.0" size="0x0.24" />
	<field name="dest_bdf" descr="Destination BDF for applicable errors   ." access="RW" offset="0xC.0" size="0x0.16" />
	<field name="error_param3_cap" descr="when applicable error param0 capability mask based on Table  55, &quot;MPEINJ Error List and Params,&quot; on page  406\;Invalid when the error_type is not supported as indicated in the error_trpe_cap." access="RO" offset="0xC.16" size="0x0.4" />
	<field name="error_param2_cap" descr="when applicable error param0 capability mask based on Table  55, &quot;MPEINJ Error List and Params,&quot; on page  406\;Invalid when the error_type is not supported as indicated in the error_trpe_cap." access="RO" offset="0xC.20" size="0x0.4" />
	<field name="error_param1_cap" descr="when applicable error param0 capability mask based on Table  55, &quot;MPEINJ Error List and Params,&quot; on page  406\;Invalid when the error_type is not supported as indicated in the error_trpe_cap." access="RO" offset="0xC.24" size="0x0.4" />
	<field name="error_param0_cap" descr="when applicable error param0 capability mask based on Table  55, &quot;MPEINJ Error List and Params,&quot; on page  406\;Invalid when the error_type is not supported as indicated in the error_trpe_cap." access="RO" offset="0xC.28" size="0x0.4" />
	<field name="error_params_0" descr="Error specific parameters according to Table  55, &quot;MPEINJ Error List and Params,&quot; on page  406." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="error_params_1" descr="Error specific parameters according to Table  55, &quot;MPEINJ Error List and Params,&quot; on page  406." access="RW" offset="0x14.0" size="0x4.0" />
	<field name="error_params_2" descr="Error specific parameters according to Table  55, &quot;MPEINJ Error List and Params,&quot; on page  406." access="RW" offset="0x18.0" size="0x4.0" />
	<field name="error_params_3" descr="Error specific parameters according to Table  55, &quot;MPEINJ Error List and Params,&quot; on page  406." access="RW" offset="0x1C.0" size="0x4.0" />
	<field name="error_type_cap_0" descr="error type capability mask for error types 0-31 when set the corresponding error type is supported: \;bit 0 - error type 0, bit 31 - error type 31." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="error_type_cap_1" descr="error type capability mask for error types 32-63 when set the corresponding error type is supported: \;bit 0 - error type 32, bit 31 - error type 63." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="error_type_cap_2" descr="error type capability mask for error types 64-95 when set the corresponding error type is supported: \;bit 0 - error type 64, bit 31 - error type 95." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="error_type_cap_3" descr="error type capability mask for error types 0-31 when set the corresponding error type is supported: \;bit 0 - error type 96, bit 31 - error type 127." access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="error_type_cap_4" descr="error type capability mask for error types 128-159 when set the corresponding error type is supported: \;bit 0 - error type 128, bit 31 - error type 159." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="error_type_cap_5" descr="error type capability mask for error types 160-191 when set the corresponding error type is supported: \;bit 0 - error type 160, bit 31 - error type 191." access="RO" offset="0x34.0" size="0x4.0" />
	<field name="error_type_cap_6" descr="error type capability mask for error types 192-223 when set the corresponding error type is supported: \;bit 0 - error type 192, bit 31- error type 223." access="RO" offset="0x38.0" size="0x4.0" />
	<field name="error_type_cap_7" descr="error type capability mask for error types 224-255 when set the corresponding error type is supported: \;bit 0 - error type 224, bit 31 - error type 255." access="RO" offset="0x3C.0" size="0x4.0" />
</node>

<node name="mpir_ext" descr="" size="0x10.0" >
	<field name="host_buses" descr="Number of PCIe buses available for the host to connect ot the device.\;&apos;0&apos; when operating in non-Socket-Direct mode." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="Internal domain index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="DPNv" descr="DPN version\;0: multi_topology_unaware_sw\;1: multi_topology_aware_sw" access="INDEX" enum="multi_topology_unaware_sw=0x0,multi_topology_aware_sw=0x1" offset="0x0.30" size="0x0.1" />
	<field name="sdm" descr="Socket-Direct mode indication.\;0: non-Socket-Direct mode (single host or multi-host)\;1: Socket-Direct mode, for querying host" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="subordinate_bus" descr="sunbordinate bus - the highest bus number that subordinates to switch.\;Default value of &apos;0&apos; in case it is not a switch port." access="RO" offset="0x4.0" size="0x0.8" />
	<field name="secondary_bus" descr="secondary bus - the internal logic bus in the switch. \;Default value of &apos;0&apos; in case it is not a switch port." access="RO" offset="0x4.8" size="0x0.8" />
	<field name="segment_base" descr="if segment valid is set this field has the segment number of the PCIe hierarchy of the link. \;segment_cap = 1 : segment base that was captured in Flit mode\;segment_cap = 0 : segment base that was set by software\;reserved when pcie_segment is not set in MPCAM" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="segment_valid" descr="when set segment base is valid, else it is invalid\;must be set if segment_cap is set.\;reserved when pcie_segment is not set in MPCAM" access="RO" offset="0x4.24" size="0x0.1" />
	<field name="segment_cap" descr="segment number (base) was captured in Flit mode. \;reserved when pcie_segment is not set in MPCAM" access="RO" offset="0x4.25" size="0x0.1" />
	<field name="sd_group" descr="The Socket Direct group index of the matching PF. \;Value 0x0 indicates no grouping" access="RO" offset="0x8.0" size="0x0.3" />
	<field name="device" descr="PCIe device number." access="RO" offset="0x8.3" size="0x0.5" />
	<field name="lp_msb" descr="2-bit expansion of the local port. Represents the local_port[9:8] bits" access="RO" offset="0x8.12" size="0x0.2" />
	<field name="bus" descr="PCIe bus number." access="RO" offset="0x8.16" size="0x0.8" />
	<field name="local_port" descr="Local port number" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="slot_number" descr="Slot number" access="RO" offset="0xC.0" size="0x0.13" />
	<field name="num_con_devices" descr="number of PCIe connected deices / EP on the current port." access="RO" offset="0xC.16" size="0x0.8" />
	<field name="host_index" descr="Host index associated with the pcie_inex" access="RO" offset="0xC.24" size="0x0.7" />
	<field name="slot_cap" descr="If set to &apos;1&apos;, slot_number field is supported." access="RO" offset="0xC.31" size="0x0.1" />
</node>

<node name="mplh_reg_ext" descr="" size="0xf8.0" >
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="Internal domain index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="DPNv" descr="DPN version\;0: multi_topology_unaware_sw\;1: multi_topology_aware_sw" access="INDEX" enum="multi_topology_unaware_sw=0x0,multi_topology_aware_sw=0x1" offset="0x0.30" size="0x0.1" />
	<field name="bin_count" descr="number of bins in the histogram\;0 - histogram count disabled\;1 - reserved\;2-10 - number of bis in the histogram from bin 0 to bin bin_count - 1\;\;Each bin is a 64-bit counter of the number of PCIe reads with latency greater than the lower bin limit and less than the upper bin limit.    \;The lower limit of the bin in index n is n*512 nanoseconds.    \;The upper limit of the bin in index n is (n+1)*512 nanoseconds, except for the last bit that has no upper limit" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="bin0_hi" descr="bin 0 counter bits 63:32" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="bin0_lo" descr="bin 0 counter bits 31:0" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="bin1_hi" descr="bin 1 counter bits 63:32" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="bin1_lo" descr="bin 1 counter bits 31:0" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="bin2_hi" descr="bin 2 counter bits 63:32" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="bin2_lo" descr="bin 2 counter bits 31:0" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="bin3_hi" descr="bin 3 counter bits 63:32" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="bin3_lo" descr="bin 3 counter bits 31:0" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="bin4_hi" descr="bin 4 counter bits 63:32" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="bin4_lo" descr="bin 4 counter bits 31:0" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="bin5_hi" descr="bin 5 counter bits 63:32" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="bin5_lo" descr="bin 5 counter bits 31:0" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="bin6_hi" descr="bin 6 counter bits 63:32" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="bin6_lo" descr="bin 6 counter bits 31:0" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="bin7_hi" descr="bin 7counter bits 63:32" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="bin7_lo" descr="bin 7counter bits 31:0" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="bin8_hi" descr="bin 8 counter bits 63:32" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="bin8_lo" descr="bin 8 counter bits 31:0" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="bin9_hi" descr="bin 9 counter bits 63:32" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="bin9_lo" descr="bin 9 counter bits 31:0" access="RO" offset="0x58.0" size="0x4.0" />
</node>

<node name="mpqd_reg_ext" descr="" size="0x10.0" >
	<field name="node" descr="Node for the query" access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="pcie_index for the query" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="Depth level for the query" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="DPNv" descr="DPN version\;0: multi_topology_unaware_sw\;1: multi_topology_aware_sw\;For MPQD SW must set the DPNv bit" access="INDEX" enum="multi_topology_unaware_sw=0x0,multi_topology_aware_sw=0x1" offset="0x0.30" size="0x0.1" />
	<field name="requester_pcie_index" descr="The pcie_index associated with the querying host" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="max_valid_pcie_index" descr="Max available pcie_index" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="max_exist_depth" descr="Max depth for the querying pcie_index" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="is_internal" descr="pcie_index is an internal host PCIe tree\;0: pcie_index is an external host PCIe tree\;1: pcie_index is an internal host PCIe tree" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="number_of_nodes" descr="Number of nodes on querying depth - node numbers are 0 to (number_of_nodes - 1)\;when 0 - no valid nodes on that querying depth in querying pcie_index" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="node_phy" descr="Querying node in querying depth and querying pcie_index a physical node\;0: the node is a virtual node\;1: the node is a physical node" access="RO" offset="0x8.8" size="0x0.1" />
	<field name="valid_index" descr="Querying pcie_index valid\;0 : pcie_index is not a valid index\;1: pcie_index is a valid index" access="RO" offset="0x8.31" size="0x0.1" />
	<field name="valid_node" descr="Is querying node valid\;0: querying node is not a valid node\;1: querying node is valid" access="RW" offset="0xC.0" size="0x0.1" />
	<field name="DSP_node" descr="Is querying node a downstream port\;0: node is upstream port\;1: node is downstream port" access="RO" offset="0xC.1" size="0x0.1" />
	<field name="parent_node_number" descr="Parent node number for the querying node, depth and pcie_index in the parent depth (depth - 1). \;When querying depth is 0 the parent node is invalid." access="RO" offset="0xC.8" size="0x0.8" />
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
	<field name="reset_trigger" descr="The firmware reset trigger\;Bit 0: TRIGGER0 - live patch\;Bit 1: Immediate_Action - used for embedded CPU shut down or reset\;Bit 3: TRIGGER3 - PCIe link disable or hot reset\;Bit 6: TRIGGER6 - PERST\;Other bits are reserved" access="RO" enum="TRIGGER0=0x1,Immediate_Action=0x2,TRIGGER3=0x8,TRIGGER6=0x40" offset="0x0.0" size="0x0.8" />
	<field name="reset_type" descr="Query chip reset type\;0x0: Full_Chip_Reset\;0x1: Keep_Network_Port_Active_During_Reset - phy less reset\;0x2: NIC_Only_Rset - for SoC devices. Keep ARM subsystem operational while NIC subsystem (including PCI) is reset.\;0x3: ARM_Only_Reset\;0x4: ARM_OS_Shutdown\;0x5: Network_Reset - Keep PCIe active during reset. Relevant for ConnectX-8 and onward\;0xff: InService_SW_Update - Keep network port and PCIe port active and operation during reset." access="INDEX" enum="Full_Chip_Reset=0x0,Keep_Network_Port_Active_During_Reset=0x1,NIC_Only_Rset=0x2,ARM_Only_Reset=0x3,ARM_OS_Shutdown=0x4,Network_Reset=0x5,InService_SW_Update=0xff" offset="0x0.8" size="0x0.8" />
	<field name="query_is_valid" descr="Selected type is supported." access="RO" offset="0x0.16" size="0x0.1" />
	<field name="pci_sync_for_fw_update_start" descr="This filed defines the reset flow. \;Bit 0: Legacy_Flow\;Bit 1: Synced_Driver_Flow\;Bit 2: Synced_Tool_Flow - should be 0 for internal host\;Bit 3: Reserved" access="RO" enum="Legacy_Flow=0x1,Synced_Driver_Flow=0x2,Synced_Tool_Flow=0x4,Reserved=0x8" offset="0x0.17" size="0x0.4" />
	<field name="pci_reset_req_method" descr="FW reset Method\;Bit 0: Link_Disable \;Bit 1: Hot_Reset - SBR\;Other bits are reserved \;Note that this field provides information when reset trigger equals TRIGGER3 (e.g., PCIe link toggle, PCIe hot reset)" access="RO" enum="Link_Disable=0x1,Hot_Reset=0x2" offset="0x0.24" size="0x0.8" />
</node>

<node name="mrpr_reg_ext" descr="" size="0x108.0" >
	<field name="type" descr="Runtime parameter to access or query\;" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="status" descr="0: Parameter is not supported\;1: Parameter is supported but is not ready for read\;2: Successful read\;3: Successful write\;Else - Reserved" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="length" descr="Number of Bytes in the parameter data section.\;When reading an unsupported /unavailable parameter, this field is 0 and there is no data field in the read response." access="RW" offset="0x0.24" size="0x0.8" />
	<field name="data" descr="Parameter data.\;Writing to this field for read-only parameter has no effect. \;Reading this field for a write-only parameter returns unpredicted value." access="RW" high_bound="63" low_bound="0" offset="0x8.0" size="0x100.0" />
</node>

<node name="mrsi_ext" descr="" size="0x40.0" >
	<field name="device" descr="[NIC_Only]\;0: Main \;1: Embedded CPU \;Reserved when Switches" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="reset_reason" descr="Reset/shutdown reason\;0: cold reset - A reset triggered following application of power to the component. 1: warm reset - A reset triggered without removal and re-application of power to the device" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="crts" descr="Timestamp (number of clock cycles) since last cold reset" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
	<field name="ecos" descr="[NIC only]\;Embedded CPU OS state\;0: Reset/Boot-ROM\;1: BL2\;2: BL31\;3: UEFI\;4: OS starting\;5: OS is running\;6: Low-Power standby\;7: Firmware update in progress\;8: OS Crash Dump in progress\;9: OS Crash Dump is complete\;10: FW Fault Crash Dump in progress\;11: FW Fault Crash Dump is complete\;Other: Reserved\;\;Reserved when MRSI.device != Embedded CPU" access="RO" offset="0x14.0" size="0x0.8" />
</node>

<node name="mrtc_reg_ext" descr="" size="0x10.0" >
	<field name="time_synced" descr="If set, the time returned in time_l/time_h is the number of microseconds passed since 1/1/1970. \;otherwise, the time_l/time_h measures the time since the NIC boot." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="time_h" descr="MSB of timestemp depnding on time_synced" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="time_l" descr="LSB of timestemp depnding on time_synced" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="mrtcq_reg_ext" descr="" size="0x40.0" >
	<field name="rt_clock_identity" descr="The real-time clock identity of the device" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
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

<node name="msmr_ext" descr="" size="0x10.0" >
	<field name="safe_mode_config" descr="Defines the operation mode:\;0:Safe mode disabled\;1:Safe mode enabled after num_of_bad_reboots\;2:Safe mode is activated once\;3:Safe mode is enforced for any boot\;Other values are reserved." access="RW" offset="0x0.0" size="0x0.8" />
	<field name="num_of_bad_reboots" descr="Number of PCIe bus reset cycles which were not followed by successful driver load" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="max_bad_reboots" descr="Maximum number of bad reboots. this counter is self-reset upon cold-reboot" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="bad_reboots_count" descr="Counter of the current bad reboots." access="RO" offset="0x4.8" size="0x0.8" />
	<field name="state" descr="Safe Mode state:\;0: Device is operating in normal mode\;1: Device is operating in Safe Mode" access="RO" offset="0x8.0" size="0x0.1" />
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
	<field name="token_opcode" descr="The token which a challenge is generated for.\;0: RMCS - (ReMote Customer Support)\;1: RMDT - (ReMote Debug Token)\;2: CRCS - (Challenge-Response Customer Support) - supported from Spectrum-4 and above\;3: CRDT - (Challenge-Response Debug Token) - supported from Spectrum-4 and above\;\;5: MTDT\;6: FRC - (Factory ReCustomization)\;7: MTFA\;Other: Reserved" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="keypair_uuid" descr="The UUID of the key used to generate the challenge." access="RO" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
	<field name="base_mac" descr="Device base MAC address / unique identifier." subnode="uint64" access="RO" offset="0x14.0" size="0x8.0" />
	<field name="psid" descr="Device PSID" access="RO" high_bound="3" low_bound="0" offset="0x1C.0" size="0x10.0" />
	<field name="fw_version_39_32" descr="Device FW version" access="RO" offset="0x2C.0" size="0x0.8" />
	<field name="fw_version_31_0" descr="Device FW version" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="source_address" descr="Source address of debug requester. DLID for Infiniband\;Valid only for RMCS/RMDT." access="RO" high_bound="3" low_bound="0" offset="0x34.0" size="0x10.0" />
	<field name="session_id" descr="Unique debug session identifier. \;See details in REMOTE_DEBUG_KEEP_ALIVE.\;Valid only for RMCS." access="RO" offset="0x44.0" size="0x0.16" />
	<field name="challenge_version" descr="Version of the challenge format.\;" access="RO" offset="0x44.24" size="0x0.8" />
	<field name="challenge" descr="Random generated field. Used for randomness and replay-protection." access="RO" high_bound="7" low_bound="0" offset="0x48.0" size="0x20.0" />
	<field name="token_ratchet" descr="Current device&quot;s token rachet value." subnode="uint64" access="RO" offset="0x68.0" size="0x8.0" />
</node>

<node name="mtctr_reg_ext" descr="" size="0x18.0" >
	<field name="second_clock_cross_timestamp_request" descr="An index for the second clock to get cross-timestamps from:    \;0: NOP - no timestamp requested.   \;1: PTM_ROOT_CLOCK - request timestamp from the PTM root clock. Allowed only if MTPTM.ptsa is set.    \;2: FREE_RUNING - request timestamp from the device&apos;s Free-Running counter (AKA the internal timer). When requested in parallel to PTM root clock, this will return a PTM Requester timestamp from the FR counter.   \;3: REAL_TIME - request timestamp from the device&apos;s Real-Time clock. When requested in parallel to PTM root clock, this will return a PTM Requester timestamp from the RT clock. The return timestamp will be in RT format:   \;- The high 32 bits contain the seconds,    \;- The lower 32 bits contain nanoseconds (only 30 lsbits are used).   \;4: DPA_TIMER - request timestamp from the DPA timer. Supported only when MCAM.mtctr_dpa_timer == 1\;Other values are reserved.\;Must be different than first_clock_cross_timestamps_request." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="first_clock_cross_timestamp_request" descr="An index for the first clock to get cross-timestamps from:    \;0: NOP - no timestamp requested.   \;1: PTM_ROOT_CLOCK - request timestamp from the PTM root clock. Allowed only if MTPTM.ptsa is set.    \;2: FREE_RUNING - request timestamp from the device&apos;s Free-Running counter (AKA the internal timer). When requested in parallel to PTM root clock, this will return a PTM Requester timestamp from the FR counter.   \;3: REAL_TIME - request timestamp from the device&apos;s Real-Time clock. When requested in parallel to PTM root clock, this will return a PTM Requester timestamp from the RT clock. The return timestamp will be in RT format:   \;- The high 32 bits contain the seconds,    \;- The lower 32 bits contain nanoseconds (only 30 lsbits are used).   \;4: DPA_TIMER - request timestamp from the DPA timer. Supported only when MCAM.mtctr_dpa_timer == 1.\;Other values are reserved." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="accuracy" descr="When zero, accuracy is not known. Otherwise, the estimated accuracy of the cross-timestamp in units of nanoseconds. Any value larger than 0xFFFFF is represented as 0xFFFFF." access="RO" offset="0x4.0" size="0x0.20" />
	<field name="second_clock_valid" descr="Indicate a successful reading of the first clock timestamp." access="RO" offset="0x4.30" size="0x0.1" />
	<field name="first_clock_valid" descr="Indicate a successful reading of the first clock timestamp." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="first_clock_timestamp" descr="A timestamp from the clock requested in first_clock_cross_timestamps_request\;Valid only when first_clock_valid flag is set." subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
	<field name="second_clock_timestamp" descr="A timestamp from the clock requested in second_clock_cross_timestamps_request\;Valid only when second_clock_valid flag is set." subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="mtdc_ext" descr="" size="0x20.0" >
	<field name="tracer_limit_en" descr="Tracer writing to PCI is limited.When this mode is enable, the hw tracer pointer cannot override the software read index pointer.If software will not update the read index pointer, new events will fall and will not be sent.\;0: NA - ignored, does not perform any operation \;1: Enable\;2: Disable" access="RW" offset="0x0.0" size="0x0.2" />
	<field name="tlb_addr_msb" descr="The lsb of the address for the cyclic buffer in the host memory." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="tlb_addr_lsb" descr="The lsb of the for the cyclic buffer address in the host memory." access="RW" offset="0xC.12" size="0x0.20" />
	<field name="hw_pointer" descr="Pointer of the current hw index the tracer is writing to.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="sw_pointer" descr="Pointer to the last tracer event index that the software consumed.\;" access="RW" offset="0x14.0" size="0x4.0" />
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
	<field name="sensor_index" descr="Sensors index\;0: current asic temp, FW exposes current max(all diode temp sensors)\;1..62: ambient, supported only for unmanaged switch, defined by ini\;64..255: modules 256..288: Gearbox\;[Retimer Only][DWIP][Internal]:\;289: Retimer Tsense, valid when i = 1\;290..297: Retimer BJT 0..7, valid when i = 1\;Others up to 704 are reserved" access="INDEX" offset="0x0.0" size="0x0.12" />
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

<node name="mtpps_reg_ext" descr="" size="0x38.0" >
	<field name="cap_max_num_of_pps_out_pins" descr="Maximum number of pps out pins supported on device." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="cap_max_num_of_pps_in_pins" descr="Maximum number of pps in pins supported on device." access="RO" offset="0x0.8" size="0x0.4" />
	<field name="cap_number_of_pps_pins" descr="Total number of pps pins supported on device.\;The virtual pins are not counted here" access="RO" offset="0x0.16" size="0x0.4" />
	<field name="cap_log_min_out_pulse_duration_ns" descr="log of the minimum supported out pulse duration in MTPPS.out_pulse_duration_ns. The value is in units of nanoseconds." access="RO" offset="0x4.0" size="0x0.5" />
	<field name="cap_log_min_npps_period" descr="log of the minimum supported npps_period in MTPPS. The value is in units of nanoseconds." access="RO" offset="0x4.8" size="0x0.5" />
	<field name="cap_pin_0_mode" descr="Capability of PPS pin #0\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.0" size="0x0.4" />
	<field name="cap_pin_1_mode" descr="Capability of PPS pin #1\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.8" size="0x0.4" />
	<field name="cap_pin_2_mode" descr="Capability of PPS pin #2\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.16" size="0x0.4" />
	<field name="cap_pin_3_mode" descr="Capability of PPS pin #3\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.24" size="0x0.4" />
	<field name="cap_pin_4_mode" descr="Capability of PPS pin #4\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xC.0" size="0x0.4" />
	<field name="cap_pin_5_mode" descr="Capability of PPS pin #5\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xC.8" size="0x0.4" />
	<field name="cap_pin_6_mode" descr="Capability of PPS pin #6\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xC.16" size="0x0.4" />
	<field name="cap_pin_7_mode" descr="Capability of PPS pin #7\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xC.24" size="0x0.4" />
	<field name="field_select" descr="Field select indicates which fields to modify in write operation to this register. This field selector supported only when MCAM.mtpps_fs==1. if MCAM.mtpps_fs==0 then SW should ensure that all the WO/RW fields are valid. \;Bit 0: enable\;Bit 1: Reserved\;\;Bit 2: pattern\;Bit 3: pin_mode\;Bit 4: time_stamp\;Bit 5: out_pulse_duration\;Bit 6: out_periodic_adjustment\;Bit 7: enhanced_out_periodic_adjustment\;Bit 9: npps_period\;Bit 10: out_pulse_duration_ns" access="WO" enum="enable=0x1,Reserved=0x2,pattern=0x4,pin_mode=0x8,time_stamp=0x10,out_pulse_duration=0x20,out_periodic_adjustment=0x40,enhanced_out_periodic_adjustment=0x80,npps_period=0x200,out_pulse_duration_ns=0x400" offset="0x10.0" size="0x4.0" />
	<field name="npps_period" descr="Period between periodical pps signal. The generated period depends on device capability and might be rounded.\;When &apos;0&apos;: the period is 1 sec\;Supported only when pin_mode = 0x01 and MCAM.mtpps_npps_period is set.\;Supported only when MTUTC.time_stamp_mode is REAL_TIME.\;The format of this field is real-time timestamp format\;The minimum supported period is reported at MTPPS.cap_log_min_npps_period" subnode="uint64" access="RW" offset="0x18.0" size="0x8.0" />
	<field name="pin" descr="Pin to be configured or queried out of the supported pins." access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="pin_mode" descr="Pin mode to be used. The mode must comply with the supported modes of the requested pin.\;0x0: pps_in\;0x1: pps_out\;0x2: virtual_pin\;0x3: pps_out_and_virtual_pin\;\;Operation will fail if pin does not support the required mode." access="RW" enum="pps_in=0x0,pps_out=0x1,virtual_pin=0x2,pps_out_and_virtual_pin=0x3" offset="0x20.8" size="0x0.4" />
	<field name="pattern" descr="When pin_mode = pps_in:\;0x0: Rising edge \;0x1: Falling edge \;\;When pin_mode = pps_out:\;0x0: Pulse - (one shot) The device will generate a pulse at time_stamp time with a duration of out_pulse_duration. \;0x1: Periodic - the device will generate periodical pulses with pulse duration  of  out_pulse_duration every  npps_period according to internal clock. The 1st pulse will be generated at time_stamp time.\;\;Reserved when pin_mode = 0x2 virtual_pin\;\;" access="RW" offset="0x20.16" size="0x0.4" />
	<field name="utc_mode" descr="UTC time:\;0x0: FREE_RUNNING - time_stamp is by free running clock\;0x1: UTC - time_stamp is UTC" access="RW" enum="FREE_RUNNING=0x0,UTC=0x1" offset="0x20.30" size="0x0.1" />
	<field name="enable" descr="Enables the PPS functionality the specific pin.\;0x0: Disable \;0x1: Enable" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x20.31" size="0x0.1" />
	<field name="out_pulse_duration_ns" descr="Output pulse duration in units of nSec. The generated duration depends on device capability and might be rounded.\;Default values will be used if set to 0.\;Reserved when pin_mode != ptp_out. This field is mutual exclusive with out_pulse_duration. Supported only when MCAM.out_pulse_duration_ns is set.\;the minimum supported pulse duration is reported at MTPPS.cap_log_min_out_pulse_duration_ns\;Range is 1..10^9" access="RW" offset="0x24.0" size="0x0.30" />
	<field name="time_stamp" descr="When pin_mode = pps_in, the latched device time when it was triggered from the external GPIO pin. \;When pin_mode = pps_out or virtual_pin or pps_out_and_virtual_pin, the target time to generate next output signal. \;\;When time_stamp_mode in MTUTC register is REAL_TIME, Bits 29:0 are nSec, bits 47:30 are Sec. \;Otherwise, time is in units of device clock. \;" subnode="uint64" access="RW" offset="0x28.0" size="0x8.0" />
	<field name="out_periodic_adjustment" descr="Frequency adjustment: Every PPS the HW frequency will be adjusted by this value. Units of HW clock, where HW counts 10^9 HW clocks for 1 HW second.\;Range is from -32768 to +32767\;The hardware does consecutive frequency adjustment \;Reserved when pin_mode != ptp_out\;Reserved when real time mode\;Reserved when switches\;" access="RW" offset="0x30.0" size="0x0.16" />
	<field name="out_pulse_duration" descr="Output pulse duration in units of mSec. \;Range is 1 to 1000. \;Reserved when pin_mode != ptp_out\;In case the set value is 0, device default will be used.\;This field is mutual exclusive with out_pulse_duration_ns" access="RW" offset="0x30.16" size="0x0.16" />
	<field name="enhanced_out_periodic_adjustment" descr="Same as out_periodic_adjustment field, but supports a wider range.\;supported only when MCAM.mtpps_enhanced_out_periodic_adjustment==1.\;mutual exclusive with out_periodic_adjustment, i.e. when enhanced_out_periodic_adjustment!=0,\;out_periodic_adjustment is invalid.\;Reserved when real time mode\;Reserved when switches" access="RW" offset="0x34.0" size="0x4.0" />
</node>

<node name="mtptm_reg_ext" descr="" size="0x10.0" >
	<field name="psta" descr="PTM source time available\;When this bit is set, MTCTR read with a request for PTM_ROOT_CLOCK time is allowed.  " access="RO" offset="0x0.15" size="0x0.1" />
	<field name="local_time_invalidation_to" descr="The period from validation of PTM context until a Local Time Invalidation event due to a timeout.\;\;0x0: The period for a Local Time Invalidation due to timeout will be according to the device default.\;0x1-0xFFFE: The period for a Local Time Invalidation due to timeout. Units of microseconds.\;0xFFFF: The period for a Local Time Invalidation due to timeout will be zero microseconds.\;\;Please note that if the specified value is not supported by the device it will be adjusted to the nearest timeout period which is &lt; requested timeout period." access="RW" offset="0x0.16" size="0x0.16" />
	<field name="trigger_event_mode" descr="Trigger Event mode\;0x0: DEVICE_DEFAULT - The trigger event mode will be according to the device default.\;0x1: CONTEXT_INVALIDATION - immediate trigger event after PTM context invalidation. The device will issue a new PTM request right after an invalidation.\;0x2: MTCTR - use MTCTR read with a request for PTM_ROOT_CLOCK time as a trigger event. It will be considered a trigger event only if the PTM context is invalid.\;0x3-0xF: reserved." access="RW" offset="0x4.28" size="0x0.4" />
</node>

<node name="mtrc_cap_reg_ext" descr="" size="0x84.0" >
	<field name="num_string_db" descr="Number of different string sections building the database" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="trc_ver" descr="Indicates the version of the tracing mechanism.\;See Section 29.3.4.1, &quot;Timestamp Event Traces&quot;, on page 1974\;0x0: VER_0\;0x1: VER_1\;Other values are reserved.\;Reserved in Switch" access="RO" offset="0x0.24" size="0x0.2" />
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

<node name="mtutc_reg_ext" descr="" size="0x1c.0" >
	<field name="operation" descr="Operation:\;\;1: SET_TIME_IMMEDIATE\;2: ADJUST_TIME\;3: ADJUST_FREQ_UTC  - On NIC: for Bluefield-4 and onwards update both UTC and FRC\;4: ADJUST_FREQ_FRC - Free Running Clock (DWIP and Switch only)\;5: ADJUST_FREQ_BOTH - (DWIP and Switch only)\;6: ADJUST_PHASE - Supported only if MCAM.mng_feature_cap_mask bit 54 is set." access="OP" enum="SET_TIME_IMMEDIATE=0x1,ADJUST_TIME=0x2,ADJUST_FREQ_UTC=0x3,ADJUST_FREQ_FRC=0x4,ADJUST_FREQ_BOTH=0x5,ADJUST_PHASE=0x6" offset="0x0.0" size="0x0.4" />
	<field name="log_max_phase_adjustment" descr="[DWIP]\;range is from -(2^ log_max_phase_adjustment) to +2^ log_max_phase_adjustment) in units of ns." access="RO" offset="0x0.5" size="0x0.6" />
	<field name="log_max_freq_adjustment" descr="If 0: Range is from -50,000,000 ppb to +50,000,000 ppb.\;Otherwise: range is from -(2^log_max_freq_adjustment) ppb to +2^log_max_freq_adjustment ppb.\;Note: This field does not change between FW resets" access="RO" offset="0x0.16" size="0x0.5" />
	<field name="freq_adj_units" descr="Updated when operation is ADJUST_FREQ.\;\;0: units_are_ppb - every PPS the HW frequency will be adjusted by this value\;1: units_are_parts_per_million - but with a 16 bit binary fractional field\;2: units_are_parts_per_billion - but with a 16 bit binary fractional field" access="RW" enum="units_are_ppb=0x0,units_are_parts_per_million=0x1,units_are_parts_per_billion=0x2" offset="0x0.24" size="0x0.3" />
	<field name="time_stamp_state" descr="nternal stamp state\;0: FREE_RUNNING\;1: SYNCED" access="RO" enum="FREE_RUNNING=0x0,SYNCED=0x1" offset="0x0.28" size="0x0.2" />
	<field name="time_stamp_mode" descr="Internal stamp mode\;0: INTERNAL_TIMER\;1: REAL_TIME\;\;Other values are reserved." access="RO" enum="INTERNAL_TIMER=0x0,REAL_TIME=0x1" offset="0x0.30" size="0x0.2" />
	<field name="freq_adjustment" descr="Units are per MTUTC.freq_adj_units value. Frequency adjustment: Every PPS the HW frequency will be adjusted by this value. \; field.\;Updated when operation is ADJUST_FREQ\;\;Range is from -50,000,000 ppb to +50,000,000 ppb" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="utc_sec" descr="UTC seconds\;Updated when operation is SET_TIME_IMMEDIATE" access="WO" offset="0x10.0" size="0x4.0" />
	<field name="utc_nsec" descr="UTC nSecs\;Range 0..(10^9-1)\;Updated when operation is SET_TIME_IMMEDIATE" access="WO" offset="0x14.0" size="0x0.30" />
	<field name="time_adjustment" descr="Time or phase adjustment\;Updated when operation is ADJUST_TIME or ADJUST_PHASE.\;\;When ADJUST_TIME:\;Time adjustment, Units of nSec, Range is from -32768 to 32768.\;If MCAM.time_adjust_range_extended==1, range is from -200,000 to +200,000.\;\;\;\;When ADJUST_PHASE:\;Phase adjustment, Units of nSec, Range is according to log_max_ phase_adjustment field.\;" access="WO" offset="0x18.0" size="0x4.0" />
</node>

<node name="mvcap_reg_ext" descr="" size="0x10.0" >
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Each bit represents a sensor. \;Sensor mapping is based on the sensor_map_type\;0: Not connected or not supported\;1: Supports voltage and current measurements" subnode="uint64" access="RO" offset="0x0.0" size="0x8.0" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x8.0" size="0x0.4" />
	<field name="sensor_map_type" descr="[DWIP]\;0: Sensors 0-63.\;1: Sensors 64-127.\;2: Sensors 128-191." access="INDEX" offset="0x8.28" size="0x0.2" />
</node>

<node name="mvcr_ext" descr="" size="0x18.0" >
	<field name="sensor_index" descr="Sensors:\;- 0..max_system_sensors-1 are ambient sensors on the system (max_system_sensors from INI)\;127: Total Power Consumption" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="parent_id" descr="[NIC_only]\;Parent id of the reading\;0: The device itself" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="slot_index" descr="Slot index\;0: Main board\;" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="pwr_cap" descr="0: Sensor does not support power reading\;1: Sensor supports power reading" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="curr_cap" descr="0: Sensor does not support current reading\;1: Sensor supports current reading" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="volt_cap" descr="0: Sensor does not support voltage reading\;1: Sensor supports voltage reading" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="i" descr="Used to query internal A2D voltage measurements." access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="voltage_sensor_value" descr="Voltage reading from the sensor. \;Voltage units are 0.01V." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="current_sensor_value" descr="Current reading from the sensor lsb.\;Current units are 0.01A.Current units are 0.01A." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="current_sensor_value_msb" descr="Current reading from the sensor msb.Current units are 0.01A.Current units are 0.01A." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="power_sensor_value" descr="Power reading from the sensor.\;Power units are 0.1W." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="sensor_name" descr="Sensor Name\;8 character long sensor name.\;" subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="mvts_reg_ext" descr="" size="0x14.0" >
	<field name="check_timestamp_flag" descr="A SET operation with this flag set will only check if the new timestamp can be configured without updating NVRAM" access="WO" offset="0x0.29" size="0x0.1" />
	<field name="running_flag" descr="A GET operation with this flag set, will return the running FW version instead" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="clear_all_ts_flag" descr="A SET operation with this flag on will clear the running and other bank timestamps" access="WO" offset="0x0.31" size="0x0.1" />
	<field name="fw_version_major" descr="fw version major" access="RW" offset="0x4.16" size="0x0.16" />
	<field name="fw_version_subminor" descr="fw version subnimor" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="fw_version_minor" descr="fw version minor" access="RW" offset="0x8.16" size="0x0.16" />
	<field name="ts_day" descr="Timestamp day - 2 packed BCD" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="ts_month" descr="Timestamp month - 2 packed BCD" access="RW" offset="0xC.8" size="0x0.8" />
	<field name="ts_year" descr="Timestamp year - 4 packed BCD" access="RW" offset="0xC.16" size="0x0.16" />
	<field name="ts_seconds" descr="Timestamp seconds- 2 packed BCD" access="RW" offset="0x10.8" size="0x0.8" />
	<field name="ts_minutes" descr="Timestamp minutes - 2 packed BCD" access="RW" offset="0x10.16" size="0x0.8" />
	<field name="ts_hour" descr="Timestamp hour - 2 packed BCD" access="RW" offset="0x10.24" size="0x0.8" />
</node>

<node name="ncfg_reg_ext" descr="" size="0x40.0" >
	<field name="field_select" descr="In Query, indicates which fields are supported.\;In Write, indicates which field to modify.\;Bit 0x0: roce_offload_disable" subnode="uint64" access="RW" offset="0x0.0" size="0x8.0" />
	<field name="roce_offload_disable" descr="If set, then ROCE is disabled for the PF and all VFs/SFs that belong to it." access="RW" offset="0x8.0" size="0x0.1" />
</node>

<node name="nic_cap_ext_dpa_cap_ext" descr="" size="0x70.0" >
	<field name="max_num_dpa_eug" descr="Maximal number of DPA EUGs" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="max_num_dpa_eu" descr="Maximal number of DPA EUs" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="max_num_dpa_eu_partition" descr="Maximal number of DPA EU partitions" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_num_dpa_eu_per_group" descr="Maximal number of DPA EUs in one DPA EUG" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="dpa_perf_sample_type" descr="Bitmask indicating the supported sampling types of DPA performance counters. Set bit indicates this type is supported:\;Bit 0: CUMMULATIVE_EVENT\;Bit 1: EVENT_TRACER\;Other bits are reserved" access="RO" enum="CUMMULATIVE_EVENT=0x1,EVENT_TRACER=0x2" offset="0x8.8" size="0x0.8" />
	<field name="max_num_partition_vhca_id" descr="Maximal number of VHCAs associated with a single DPA EU partition" access="RO" offset="0x8.16" size="0x0.9" />
	<field name="process_perf_cnt" descr="When set, DPA process performance counters can be activated using NIC_DPA_PERF_CTRL_REG" access="RO" offset="0x8.30" size="0x0.1" />
</node>

<node name="nic_cap_ext_reg_cap_data_auto_ext" descr="" attr_is_union="1" size="0x70.0" >
	<field name="nic_cap_ext_dpa_cap_ext" descr="" subnode="nic_cap_ext_dpa_cap_ext" offset="0x0.0" size="0x70.0" />
</node>

<node name="nic_cap_ext_reg_ext" descr="" size="0x80.0" >
	<field name="cap_group" descr="Indicates which capability group is accessed.\;0x1: DPA_CAP\;other values are reserved" access="INDEX" enum="DPA_CAP=0x1" offset="0x0.16" size="0x0.16" />
	<field name="cap_data" descr="Capability information according to cap_group.\;For DPA_CAP See Table  1843, &quot;DPA_CAP Capability Layout,&quot; on page  2149" subnode="nic_cap_ext_reg_cap_data_auto_ext" access="RO" offset="0x10.0" size="0x70.0" />
</node>

<node name="nic_cap_reg_ext" descr="" size="0x80.0" >
	<field name="ec_time" descr="If set, EC_TIME Register is supported." access="RO" offset="0x0.0" size="0x0.1" />
	<field name="ec_boot_options" descr="If set EC_BOOT_OPTIONS Register is supported" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="virtio_net_emu_tlv_enable_supported" descr="If set, virtio_net_emu_tlv_enable is supported." access="RO" offset="0x0.2" size="0x0.1" />
	<field name="rcr" descr="if set, RCR Register is supported." access="RO" offset="0x0.3" size="0x0.1" />
	<field name="cmd_encap_sync_steering" descr="When set, the command SYNC_STEERING may be executed by the ICMD interface, using HCA_CMD_ENCAP register." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="vhca_icm_ctrl" descr="If set, VHCA_ICM_CTRL register is supported." access="RO" offset="0x0.5" size="0x0.1" />
	<field name="vnet_rx_cq_dm_supported" descr="If set, vnet_rx_cq_dm_enabled is supported.\;" access="RO" offset="0x0.6" size="0x0.1" />
	<field name="fw_cpu_monitoring_supported" descr="If set, device support fw_cpu monitoring,\;To enabled it, SW should set fw_cpu_monitoring_enabled==1." access="RO" offset="0x0.7" size="0x0.1" />
	<field name="nic_cap_ext_reg" descr="When set, NIC_CAP_EXT Register is supported" access="RO" offset="0x0.8" size="0x0.1" />
	<field name="adp_retx_histogram" descr="If set, ADP_RETX_HISTOGRAM_CONFIG and ADP_RETX_HISTOGRAM registers are supported" access="RO" offset="0x0.17" size="0x0.1" />
	<field name="host_os_init_ctrl_reg" descr="If set, HOST_OS_INIT_CTRL register is supported" access="RW" offset="0x0.18" size="0x0.1" />
	<field name="virtio_net_emu_tlv_enable" descr="If set, NV_EMULATION_VIRTIO_NET_CAP.virtio_net_emu_supported will be set.\;Supported only when virtio_net_emu_tlv_enable_supported==1." access="RW" offset="0x4.0" size="0x0.1" />
	<field name="vnet_rx_cq_dm_enabled" descr="If set, virtio net rx queue event auto moderation enabled. i.e. it enabled dynamic event moderation for the virtio net RX queues. \;When this bit is clear all the RX VQs are scheduled immediately for RX packet processing." access="RW" offset="0x4.1" size="0x0.1" />
	<field name="fw_cpu_monitoring_enabled" descr="If set, fw_cpu monitoring is enabled.\;Supported only when fw_cpu_monitoring_supported==1." access="RW" offset="0x4.2" size="0x0.1" />
	<field name="total_icm" descr="Indicates the total amount of ICM on the device in granularity of 4KB. Value 2^32-1 represents infinity." access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="nic_dpa_eu_partition_reg_ext" descr="" size="0x300.0" >
	<field name="eu_partition_id" descr="DPA EU partition id\;For WRITE method with operation CREATE this field is RO and provides the newly created EU partition ID.\;For other method/operation, this field is an index to a valid EU partition" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="operation" descr="Operation performed for WRITE method:\;0x0: CRETAE - create a new partition\;0x1: MODIFY - change the parameters of an existing partition, absed on modify_field_select\;0x2: DESTROY - destroy an existing partition\;other values are reserved." access="WO" enum="CRETAE=0x0,MODIFY=0x1,DESTROY=0x2" offset="0x0.28" size="0x0.3" />
	<field name="modify_field_select" descr="Bitmask indicating which parameter is modified by MODIFY operation. Set bit indicates the field should be updated.\;bit 0: member_mask\;bit 1: max_num_eug\;bit 2: num_vhca_id_and_vhca_id\;other bits are reserved.\;For Query method, set bit indicates the relevant modification is supported" access="RW" enum="member_mask=0x1,max_num_eug=0x2,num_vhca_id_and_vhca_id=0x4" offset="0x4.0" size="0x4.0" />
	<field name="max_num_eug" descr="The maximal number of groups allowed for EUs in the partition" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="num_vhca_id" descr="The number of valid entries in vhca_id array. Value must not exceed DPA_CAP,max_num_partition_vhca_id" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="member_mask" descr="Bitmask indicating which EUs are members of the partition. Set bit indicates the respective EU is a member. EU partitions may not overlap, and EUs beyond DPA_CAP.max_num_dpa_eu are reserved." access="RW" high_bound="31" low_bound="0" offset="0x40.0" size="0x80.0" />
	<field name="vhca_id" descr="Array of VHCA IDs indicating which functions are allowed to use this partition. Array size is determined by num_vhca_id, entries with index num_vhca_id or higher are reserved. A vHCA may only belong to a single partition at a time." access="RW" high_bound="255" low_bound="0" offset="0xC0.16" size="0x200.0" />
</node>

<node name="nic_dpa_eug_reg_ext" descr="" size="0x100.0" >
	<field name="eug_id" descr="DPA EUG id\;For WRITE method with operation CREATE this field is RO and provides the newly created EUG.\;For other method/operation, this field is an index to a valid EUG" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="partition_id_valid" descr="If set, partition_id defines the Partition to which the members of the EUG belong. Otherwise, the Partition that holds the calling vHCA is assumed.\;Valid if NIC_CAP_EXT.dpa_partition_eug is set." access="INDEX" offset="0x0.27" size="0x0.1" />
	<field name="operation" descr="Operation performed for WRITE method:\;0x0: CREATE - create a new DPA EUG\;0x1: MODIFY - change the members of an existing DPA EUG\;0x2: DESTROY - destroy an existing DPA EUG\;other values are reserved." access="WO" enum="CREATE=0x0,MODIFY=0x1,DESTROY=0x2" offset="0x0.28" size="0x0.3" />
	<field name="modify_field_select" descr="Bitmask indicating which parameter is modified by MODIFY operation. Set bit indicates the field should be updated.\;bit 0: member_mask\;other bits are reserved.\;For Query method, set bit indicates the relevant modification is supported" access="RW" enum="member_mask=0x1" offset="0x4.0" size="0x4.0" />
	<field name="partition_id" descr="Defines the Partition to which the members of the EUG belong. Valid if partition_id_valid is set." access="INDEX" offset="0xC.0" size="0x0.16" />
	<field name="eug_name" descr="EUG name (ASCII string)" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="member_mask" descr="Bitmask indicating which EUs are members of the group. Set bit indicates the respective EU is a member. EUGs may not overlap, and EUs beyond NIC_CAP_EXT_REG.max_num_dpa_eu are reserved." access="RW" high_bound="31" low_bound="0" offset="0x40.0" size="0x80.0" />
</node>

<node name="nic_dpa_perf_ctrl_reg_ext" descr="" size="0x40.0" >
	<field name="dpa_process_id" descr="dpa_process object id.\;0xffffffff: Applies to all processes (all processes are not valid in read)" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="other_vhca_id" descr="vhca_id where the process is created" access="WO" offset="0x4.0" size="0x0.16" />
	<field name="sample_type" descr="Selects the sampling type. Supported types are indicated by NIC_CAP_EXT.dpa_perf_sample_type\;0x0: CUMMULATIVE_EVENT\;0x1: EVENT_TRACER\;Other values are reserved" access="RW" enum="CUMMULATIVE_EVENT=0x0,EVENT_TRACER=0x1" offset="0x4.24" size="0x0.3" />
	<field name="other_vhca_id_valid" descr="If set, other_vhca_id field is valid. Otherwise, use the process on my vhca_id" access="WO" offset="0x4.27" size="0x0.1" />
	<field name="count_state" descr="Process performance counting state.\;0x0: UNCHANGED\;0x1: ACTIVE\;0x2: INACTIVE\;0x3: RESET_COUNTERS - reset saved counters. After reset, sampler will switch to inactive state.\;Other values are reserved" access="RW" enum="UNCHANGED=0x0,ACTIVE=0x1,INACTIVE=0x2,RESET_COUNTERS=0x3" offset="0x4.30" size="0x0.2" />
</node>

<node name="nvmf_target_pacer_defaults_ext" descr="" size="0x40.0" >
	<field name="modify_field_select" descr="Bitmask indicates which in read which filed can be modifiable and in write which field to modify.\;Bit 0x0: enable\;Bit 0x1: pacer_tuner_factor\;Bit 0x2: max_inflight_threshold\;Bit 0x3: min_pacer_period\;Bit 0x4: max_pacer_period\;Bit 0x5: credit_limit\;Bit 0x6: max_credit_limit\;Bit 0x7: read_bypass_block_size\;Bit 0x8: write_bypass_block_size\;Bit 0x9: margin\;Bit 0xA: tuner_time\;Bit 0xB: log_num_pacers_per_port\;Bit 0xC: enable_max_bif_capping" access="RW" enum="enable=0x1,pacer_tuner_factor=0x2,max_inflight_threshold=0x4,min_pacer_period=0x8,max_pacer_period=0x10,credit_limit=0x20,max_credit_limit=0x40,read_bypass_block_size=0x80,write_bypass_block_size=0x100,margin=0x200,tuner_time=0x400,log_num_pacers_per_port=0x800,enable_max_bif_capping=0x1000" offset="0x0.0" size="0x4.0" />
	<field name="pacer_tuner_factor" descr="" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="log_num_pacers_per_port" descr="Log (base 2) of number of pacers per port.\;Must be &lt;= HCA_CAP.log_max_num_pacers_per_port." access="RW" offset="0x4.24" size="0x0.4" />
	<field name="enable_max_bif_capping" descr="Enable/Disable the amount of request to disk from pacer limited to the maximum allowed bytes. If this is enable then there is no further request to disk if current data requested is more than maximum allowed bytes.\;0x0: Disable - disable the capping of the request to disk to maximum allowed bytes.\;0x1: Enable - enable the capping of the request to disk to maximum allowed bytes." access="RW" offset="0x4.30" size="0x0.1" />
	<field name="pacer_mode" descr="0x0 : DEFAULT_PACER_DISABLED\;0x1 : DEFAULT_PACER_ENABLED\;Note that modifying this field must be done before creating XRQs." access="RW" offset="0x4.31" size="0x0.1" />
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

<node name="over_voltage_stressor_parameters_ext" descr="" size="0x8.0" >
	<field name="over_votlage_percentage_change" descr="The percentage change in 1% units\;If percentage change is over 1 percentage point or change from previous request, FW will return BAD PARAM" access="RW" offset="0x0.0" size="0x0.6" />
</node>

<node name="paos_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Port operational state:\;1: up\;2: down\;4: down_by_port_failure - (transitioned by the hardware)\;  \;" access="RO" enum="up=0x1,down=0x2,down_by_port_failure=0x4" offset="0x0.0" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="admin_status" descr="Port administrative state (the desired state of the interface):\;1: up\;2: down_by_configuration\;3: up_once - if the port goes up and then down, the operational status should go to &quot;down by port failure&quot; and can only go back up upon explicit command\;4: disabled_by_system - this mode cannot be set by the software, only by the hardware.\;6: sleep - can be configured only if sleep_cap is set. Note that a sleep setting will cause the port to transition immediately into sleep state regardless of previous admin_status.\;[Internal] - up_once shall not be used for GPU case. In order to define link down state set PLDS register" access="RW" enum="up=0x1,down_by_configuration=0x2,up_once=0x3,disabled_by_system=0x4,sleep=0x6" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.\;Switch partition ID with which to associate the port.\;Switch partitions are numbered from 0 to 7 inclusively.\;The swid field is only valid when the local_port is the router port. In this case, the swid indicates which of the router ports to configure/query." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="e" descr="Event generation on operational state change (oper_status):\;0: Do_not_generate_event\;1: Generate_Event \;2: Generate_Single_Event\;\;Not Supported for HCA." access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="physical_state_status" descr="IB Port Physical operational (actual) link state:\;0: N/A\;1: Sleep\;2: Polling\;3: Disabled\;4: PortConfigurationTraining\;5: LinkUp\;6: LinkErrorRecovery\;All others reserved\;Note that physical state of 1,2,3,4 will all be reflected as oper_status = down.\;Ethernet devices that support this field will use only bits 2,3,5." access="RO" enum="N_A=0x0,Sleep=0x1,Polling=0x2,Disabled=0x3,PortConfigurationTraining=0x4,LinkUp=0x5,LinkErrorRecovery=0x6" offset="0x4.4" size="0x0.4" />
	<field name="fd" descr="Force down.\;Supported only when indicated in PCAM\;Can be set only with admin_status = 2 (&apos;down_by_configuration&apos;), will force link to be down. \;" access="RW" offset="0x4.8" size="0x0.1" />
	<field name="sleep_cap" descr="Sleep capability:\;0: Sleep state is not supported\;1: Sleep state supported" access="RO" offset="0x4.9" size="0x0.1" />
	<field name="ps_e" descr="Event generation for physical state.\;On set operation, will be ignored if ee_ps is not set.\;When bit is set, will generate an event for transition into state.\;Bit 0: Sleep\;Bit 1: LinkUp \;Note - LinkUp for an Ethernet link refers to PhyUp state where local side is ready, but not necessarily that peer side is also ready.\;Bit 2: Disabled\;Bit 3: PortConfigurationTraining\;Not Supported for HCA." access="RW" enum="Sleep=0x1,LinkUp=0x2,Disabled=0x4,PortConfigurationTraining=0x8" offset="0x4.12" size="0x0.4" />
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
	<field name="buffer" descr="Configuring per-buffer parameters. i=0..9.\;See Table 2595, &quot;BufferX Register Layout,&quot; on page 2997" subnode="bufferx_reg_ext" access="RW" high_bound="9" low_bound="0" offset="0xC.0" size="0x50.0" />
	<field name="shared_headroom_pool" descr="Configuring shared headroom pool parameters. Using the same layout as in BufferX.\;Not supported in HCA (See PCAM shp_pbmc_pbsr_support bit).\;See Table 2595, &quot;BufferX Register Layout,&quot; on page 2997" subnode="bufferx_reg_ext" access="RW" offset="0x5C.0" size="0x8.0" />
	<field name="port_shared_buffer" descr="Configuring port shared buffer parameters. Using the same layout as in BufferX.\;Valid for HCA when pbmc_port_shared_buffer is set in PCAM.\;See Table 2595, &quot;BufferX Register Layout,&quot; on page 2997" subnode="bufferx_reg_ext" access="RW" offset="0x64.0" size="0x8.0" />
</node>

<node name="pbsr_reg_ext" descr="" size="0x64.0" >
	<field name="buffer_type" descr="Valid only for 8x port setting (see Table 1995, &quot;PMLP - Ports Module to Local Port Register Fields,&quot; on page 2349)\;0: One buffer - reserved index for non-8x ports\;1: Main buffer\;2: Secondary buffer" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clear_wm_buff_mask" descr="Each bit represents a stat_buffer\;per bit:\;0: do not clear watermark\;1: clear watermark\;Reserved when clear_wm = 1" access="OP" offset="0x4.0" size="0x0.10" />
	<field name="used_shared_headroom_buffer" descr="Number of currently used shared headroom buffer cells." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="clear_wm" descr="Clear watermarks for all PGs" access="OP" offset="0x8.31" size="0x0.1" />
	<field name="stat_buffer" descr="status per-buffer parameters. i=0..9\;" subnode="stat_bufferx_reg_ext" access="RO" high_bound="9" low_bound="0" offset="0xC.0" size="0x50.0" />
	<field name="stat_shared_headroom_pool" descr="status of shared headroom pool parameters. Using the same layout as in stat_BufferX, for details see Table 2610, &quot;stat_bufferX Register Layout,&quot; on page 3017.\;Not supported in HCA (See PCAM shp_pbmc_pbsr_support bit). \;Not supported in GPUNet" subnode="stat_bufferx_reg_ext" access="RO" offset="0x5C.0" size="0x8.0" />
</node>

<node name="pcam_feature_capability_mask_group0_ext" descr="" size="0x10.0" >
	<field name="feature_cap_mask" descr="Supported port&apos;s enhanced features. Based on feature_group index. When bit is set, The feature is supported in the device:\;Bit 0: PPCNT_counter_group_Phy_statistical_counter_group \;Bit 1 - PPCNT_counter_group_Discard_counter_group\;Bit 9: PFCC - support of stall mask and global rx,tx mask. \;Bit 10: PMCR - support of tx_disable override.\;Bit 11: PPCNT_counter_group - IB Extended port counter group\;Bit 12: PPCNT_Extended_Ethernet_group - tx packet size histograms\;Bit 13: PTYS_extended_Ethernet_support\;Bit 14: PMAOS_reset_toggle_support\;Bit 15: Set_Module_low_power_supported \;Bit 16: Module_power_optimization_is_supported_in_PPSC\;Bit 17: Support_of_IB_force_state_machine_in_PTYS - (an_disable)\;Bit 18: PPCNT_Extended_Ethernet_group_icrc_counter\;Bit 19: cm2_en_is_supported_in_PCAP\;Bit 20: time_tolink_up_is_supported_in_PDDR\;Bit 21: gearbox_die_num_field_is_supported_in_PMDR\;Bit 22: force_entropy_entropy_calc_entropy_gre_calc - and capability bits are supported in PCMR\;Bit 23: FEC_override_support_for_50G_per_lane_is_supported_in_PPLM\;Bit 25: PTYS_allow_both_extended_and_legacy_protocol_masks\;Bit 26: PPCNT_eth_per_tc_cong_group_supported\;Bit 27: pnat_sup_host - the device supports pnat = 2 (host) when set to &apos;1&apos;\;Bit 28: ppcnt_no_buffer_discard_uc - this counter is supported in PPCNT when set to &apos;1&apos;\;Bit 29: pbmc_port_shared_buffer - supported in PBMC.\;Bit 30: PLR_max_retry_window_support - PPCNT group 0x22 max retry per window\;Bit 32: PDDR_ext_eth_proto_support\;Bit 40: PAOS - support of admin_status opcode 5: &quot;up_lowest_rate&quot;\;Bit 41: PMAOS - support of &quot;opertional_notifcation&quot; field\;Bit 42: PRBS_polarity_support - support of polarity bits in PPTT and PPRT\;Bit 43: PDDR_register_is_supported\;Bit 44: pfcc_buffer_onwership - PFCC buffer ownership is supported.\;Bit 45: force_down - supported in PAOS reg.\;Bit 46: pmlp_lane_mapping_off - Support of m_lane_m field in PMLP.\;Bit 51: ppcnt_symobl_ber\;Bit 52: shp_pbmc_pbsr_support\;Bit 54: ppcnt_effective_error_counter\;Bit 55: FEC_override_support_for_100G_per_lane_is_supported_in_PPLM\;Bit 57: PMECR_option_to_not_generate_events_upon_PMLP_set\;Bit 64: Local_port_MSB - bits [9:8] supported\;Bit 65: PDDR_moule_latched_info_page_supported\;Bit 66: PDDR_module_info_ext_supported\;Bit 70: SLTP_tx_policy_supported\;Bit 71: pmcr_capability_bits_supported\;Bit 72: pmtu_max_admin_mtu_supported\;Bit 73: PPCNT_grp_profile_supported\;Bit 77: PPCNT.physical_layer_counters_RS_FEC_8_lanes_supported\;Bit 85: PPCNT.counters_cap\;Bit 86: SLTP.lane_broadcast_supported\;Bit 87: PMMP.apply_im_supported\;Bit 91: SLRG.all_lanes_supported\;Bit 92: PIPG.ipg_oper_ipg_cap_idx_supported\;Bit 93: PPBMP_clr_supported\;Bit 94: PIPG.dic1_1g_supported\;Bit 98: FEC_override_support_for_200G_per_lane_is_supported_in_PPLM\;Bit 99: PUDE.local_reason_opcode_supported\;Bit 101: PPCNT.physical_layer_counters.intentional_unintentional_link_down_events_supported\;Bit 102: PAOS.nmx_adminstate_status_fields_supported\;Bit 103: PFCC.cable_length_supported\;Bit 104: PDDR.link_up_info_page_1ch_to_2ch_counters_supported\;Bit 107: PFCC.packet_ratio_supported\;Bit 108: PPCC.target_app - if set, PPCC supports target_app field\;Bit 111: PPCNT.physical_layer_recovery_counters_supported\;Bit 112: PMLP.lane_label_mapping_supported\;Bit 113: PPCNT.physical_layer_counters.estimated_effective_ber_supported\;Bit 114 PPCNT.physical_layer_counters.ucr_ber_supported\;Bit 116: PMLP.mode_b_map_bit_supported\;Bit 117: PDDR.link_down_info_page.recovery_entry_reason_supported\;Bit 118: PAOS.last_oper_state_supported\;Bit 119: PPCNT.new_phy_recovery_counters_supported\;Bit 120: PDDR.operational_info_page.test_mode_fsm_state_supported\;Bit 121: PFCC.mlb_mask_supported\;Bit 122: PUDE.recoverable_down_supported\;Bit 123: PDDR.AMLock_aggregated_VLs_Supported\;Bit 124: PPCNT.physical_layer_recovery.successful_recovery_time_supported\;Bit 125: PPCNT.physical_layer_recovery.uncorrectable_during_recovery_supported\;Bit 126: SLRG.measurements_thresholds_supported\;Other bits are reserved" access="RO" enum="PPCNT_counter_group_Phy_statistical_counter_group=0x1,PFCC=0x200,PMCR=0x400,PPCNT_counter_group=0x800,PPCNT_Extended_Ethernet_group=0x1000,PTYS_extended_Ethernet_support=0x2000,PMAOS_reset_toggle_support=0x4000,Set_Module_low_power_supported=0x8000,Module_power_optimization_is_supported_in_PPSC=0x10000,Support_of_IB_force_state_machine_in_PTYS=0x20000,PPCNT_Extended_Ethernet_group_icrc_counter=0x40000,cm2_en_is_supported_in_PCAP=0x80000,time_tolink_up_is_supported_in_PDDR=0x100000,gearbox_die_num_field_is_supported_in_PMDR=0x200000,force_entropy_entropy_calc_entropy_gre_calc=0x400000,FEC_override_support_for_50G_per_lane_is_supported_in_PPLM=0x800000,PTYS_allow_both_extended_and_legacy_protocol_masks=0x2000000,PPCNT_eth_per_tc_cong_group_supported=0x4000000,pnat_sup_host=0x8000000,ppcnt_no_buffer_discard_uc=0x10000000,pbmc_port_shared_buffer=0x20000000,PLR_max_retry_window_support=0x40000000,PDDR_ext_eth_proto_support=0x1,PAOS=0x100,PMAOS=0x200,PRBS_polarity_support=0x400,PDDR_register_is_supported=0x800,pfcc_buffer_onwership=0x1000,force_down=0x2000,pmlp_lane_mapping_off=0x4000,ppcnt_symobl_ber=0x80000,shp_pbmc_pbsr_support=0x100000,ppcnt_effective_error_counter=0x400000,FEC_override_support_for_100G_per_lane_is_supported_in_PPLM=0x800000,PMECR_option_to_not_generate_events_upon_PMLP_set=0x2000000,Local_port_MSB=0x1,PDDR_moule_latched_info_page_supported=0x2,PDDR_module_info_ext_supported=0x4,SLTP_tx_policy_supported=0x40,pmcr_capability_bits_supported=0x80,pmtu_max_admin_mtu_supported=0x100,PPCNT_grp_profile_supported=0x200,PPCNT_physical_layer_counters_RS_FEC_8_lanes_supported=0x2000,PPCNT_counters_cap=0x200000,SLTP_lane_broadcast_supported=0x400000,PMMP_apply_im_supported=0x800000,SLRG_all_lanes_supported=0x8000000,PIPG_ipg_oper_ipg_cap_idx_supported=0x10000000,PPBMP_clr_supported=0x20000000,PIPG_dic1_1g_supported=0x40000000,FEC_override_support_for_200G_per_lane_is_supported_in_PPLM=0x4,PUDE_local_reason_opcode_supported=0x8,PPCNT_physical_layer_counters_intentional_unintentional_link_down_events_supported=0x20,PAOS_nmx_adminstate_status_fields_supported=0x40,PFCC_cable_length_supported=0x80,PDDR_link_up_info_page_1ch_to_2ch_counters_supported=0x100,PFCC_packet_ratio_supported=0x800,PPCC_target_app=0x1000,PPCNT_physical_layer_recovery_counters_supported=0x8000,PMLP_lane_label_mapping_supported=0x10000,PPCNT_physical_layer_counters_estimated_effective_ber_supported=0x20000,PMLP_mode_b_map_bit_supported=0x100000,PDDR_link_down_info_page_recovery_entry_reason_supported=0x200000,PAOS_last_oper_state_supported=0x400000,PPCNT_new_phy_recovery_counters_supported=0x800000,PDDR_operational_info_page_test_mode_fsm_state_supported=0x1000000,PFCC_mlb_mask_supported=0x2000000,PUDE_recoverable_down_supported=0x4000000,PDDR_AMLock_aggregated_VLs_Supported=0x8000000,PPCNT_physical_layer_recovery_successful_recovery_time_supported=0x10000000,PPCNT_physical_layer_recovery_uncorrectable_during_recovery_supported=0x20000000,SLRG_measurements_thresholds_supported=0x40000000" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
</node>

<node name="pcam_feature_capability_mask_group1_ext" descr="" size="0x10.0" >
	<field name="feature_cap_mask" descr="" access="RO" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
</node>

<node name="pcam_reg_ext" descr="" size="0x50.0" >
	<field name="access_reg_group" descr="Access Register ID groups\;0: RegID_0x5000_to_0x507F\;1: RegID_0x5080_to_50FF\;Values 2-255 are Reserved" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="pl_op" descr="Reserved for non-planarized port.\;Features and access regs will be presented according to:\;0: aggregated_port_access\;1: plane_port_access" access="OP" enum="aggregated_port_access=0x0,plane_port_access=0x1" offset="0x0.8" size="0x0.1" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features\;1: ext_group1_features\;Values 1 - 255 are Reserved" access="INDEX" enum="enhanced_features=0x0,ext_group1_features=0x1" offset="0x0.16" size="0x0.8" />
	<field name="port_access_reg_cap_mask" descr="Supported port&apos;s access register bitmaks. Based on access_reg_group index.\;When bit is set. The register is supported in the device. \;When access_reg_group == 0 :\;Bit_0: 0x5000 \;Bit_1: 0x5001 (PCAP)\;Bit_2: 0x5002 (PMLP)\;Bit_3: 0x5003 (PMTU)\;Bit_4: 0x5004 (PTYS)\;Bit_127: 0x507F (PCAM)" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="feature_cap_mask" descr="Table  1870, &quot;PCAM - Feature Capability Mask Group0 Layout,&quot; on page  2176\;Table  1872, &quot;PCAM - Feature Capability Mask Group1 Layout,&quot; on page  2178" subnode="pcam_reg_feature_cap_mask_auto_ext" access="RO" offset="0x28.0" size="0x10.0" union_selector="$(parent).feature_group" />
</node>

<node name="pcam_reg_feature_cap_mask_auto_ext" descr="" attr_is_union="1" size="0x10.0" >
	<field name="pcam_feature_capability_mask_group0_ext" descr="" subnode="pcam_feature_capability_mask_group0_ext" offset="0x0.0" selected_by="enhanced_features" size="0x10.0" />
	<field name="pcam_feature_capability_mask_group1_ext" descr="" subnode="pcam_feature_capability_mask_group1_ext" offset="0x0.0" selected_by="ext_group1_features" size="0x10.0" />
</node>

<node name="pcap_reg_ext" descr="" size="0x14.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cm2_en" descr="port_capability_mask[95:80] is supported if set to &apos;1&apos;." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="port_capability_mask" descr="Sets the PortInfoCapabilityMask:\;Specifies the supported capabilities of this node. A bit set to 1 for affirmation of supported capability.\;port_capability_mask[127:96] is mapped to CapabilityMask in PortInfo MAD.\;port_capability_mask[95:80] is mapped to CapabilityMask2 in PortInfo MAD.\;\;\;" access="RW" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
</node>

<node name="pcct_reg_ext" descr="" size="0x14.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM \;0: Network_port\;1: Near_End_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: Far_End_Port - (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" enum="Network_port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;1: IB_port_number" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="page_select" descr="page select index:\;0: plu_general_tracer_page" access="INDEX" enum="plu_general_tracer_page=0x0" offset="0x4.0" size="0x0.8" />
	<field name="page_data" descr="Table  2568, &quot;PLU General Tracer Page Layout,&quot; on page  2957" subnode="pcct_reg_page_data_auto_ext" access="RW" offset="0x8.0" size="0xc.0" union_selector="$(parent).page_select" />
</node>

<node name="pcct_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0xc.0" >
	<field name="plu_general_tracer_page_ext" descr="" subnode="plu_general_tracer_page_ext" offset="0x0.0" selected_by="plu_general_tracer_page" size="0xc.0" />
</node>

<node name="pcie_perf_counters2_ext" descr="" size="0xf8.0" >
	<field name="total_dwords_transmitted" descr="Total number of DWORDS sent by the PCIe link." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="total_dwords_received" descr="Total number of DWORDS receivedby the PCIe link." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="invalid_flit_counter" descr="Number of invalid flit blocks" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="outbound_read_tlps_count" descr="Number of read TLPs sent by the PCIe link" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="outbound_read_data_dword_high" descr="Number of DWORDS sent in outbound read TLPs - bits 63:32" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="outbound_read_data_dword_low" descr="Number of DWORDS sent in outbound read TLPs - bits 31:0" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="outbound_write_tlps_count" descr="Number of write TLPs sent by the PCIe link." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="outbound_write_data_dword_high" descr="Number of DWORDS sent in outbound write TLPs - bits 63:32" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="outbound_write_data_dword_low" descr="Number of DWORDS sent in outbound write TLPs - bits 31:0" access="RW" offset="0x20.0" size="0x4.0" />
	<field name="outbound_completion_tlps_count" descr="Number of completion TLPs sent by the PCIe link." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="outbound_completion_data_dwords_count" descr="Number of DWORDS sent in outbound completion TLPs" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="reads_req_dropped_due_missing_tag_count" descr="Number of read request dropped due to missing tag" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="reads_req_dropped_due_missing_cmpl_credits_count" descr="Number of read request dropped due to missing completion credits" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="reads_req_dropped_due_missing_np_credits_count" descr="Number of read request dropped due to missing non-posted credits" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="NAK_received_count" descr="Number of NAKs received" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="NAK_sent_count" descr="Number of NAKs sent" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="replay_cnt_rollover_count" descr="Number of replay count rollover" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="FC_error_count" descr="Number of Flow Control Errors" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="replay_count" descr="Number of TLPs replay" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="AER_correctable_errors_count" descr="Number of AER correctable errors count" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="AER_fatal_error_count" descr="Number of AER fatal errors count" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="AER_non_fatal_error_count" descr="Number of AER non fatal errors count" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="AER_unsupported_request" descr="Number of AER unsupported request" access="RO" offset="0x58.0" size="0x4.0" />
</node>

<node name="pcie_perf_counters_ext" descr="" size="0xf8.0" >
	<field name="rx_errors" descr="Number of transitions to recovery due to Framing errors and CRC (dlp and tlp) errors." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="tx_errors" descr="Number of transitions to recovery due to EIEOS and TS errors." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="crc_error_dllp" descr="Number of transitions to recovery due to identifying CRC DLLP errors" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="crc_error_tlp" descr="Number of transitions to recovery due to identifying CRC TLP errors" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="tx_overflow_buffer_pkt" descr="The number of packets dropped due to lack of PCIe buffers or receive path from NIC port toward the hosts." subnode="uint64" access="RO" offset="0x28.0" size="0x8.0" />
	<field name="outbound_stalled_reads" descr="The percentage of time within the last second that the NIC had outbound non-posted read requests but could not perform the operation due to insufficient non-posted credits.\;Supported only when MCAM.pcie_outbound_stalled ==1." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="outbound_stalled_writes" descr="The percentage of time within the last second that the NIC had outbound posted writes requests but could not perform the operation due to insufficient posted credits.\;Supported only when MCAM.pcie_outbound_stalled ==1." access="RO" offset="0x34.0" size="0x4.0" />
	<field name="outbound_stalled_reads_events" descr="The number of events where outbound_stalled_reads was above a threshold.\;The threshold is configured by outbound_stalled_reads_th in MPEGC.\;Supported only when MCAM.pcie_outbound_stalled ==1." access="RO" offset="0x38.0" size="0x4.0" />
	<field name="outbound_stalled_writes_events" descr="The number of events where outbound_stalled_writes was above a threshold.\;The threshold is configured by outbound_stalled_writes_th in MPEGC.\;Supported only when MCAM.pcie_outbound_stalled ==1." access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="tx_overflow_buffer_marked_pkt" descr="The number of packets marked due to lack of PCIe buffers or receive path from NIC port toward the hosts.\;Supported only if MCAM.mark_tx_action_cqe or MCAM.mark_tx_action_cnp are set to &apos;1&apos;." subnode="uint64" access="RO" offset="0x40.0" size="0x8.0" />
	<field name="effective_ber_coef" descr="Effective_BER = effective_ber_coef*10^(-effective_ber_magnitude)" access="RO" offset="0x48.0" size="0x0.4" />
	<field name="effective_ber_magnitude" descr="Effective_BER = effective_ber_coef*10^(-effective_ber_magnitude)" access="RO" offset="0x48.8" size="0x0.8" />
	<field name="fec_correctable_error_counter" descr="FEC correctable error counter when FLIT is enabled" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="fec_uncorrectable_error_counter" descr="FEC uncorrectable error counter when FLIT is enabled" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="l0_to_recovery" descr="total l0 to recovery - this is a sum of all the l0 to recovery specific causes- l0_to_recovery_eieos, l0_to_recovery_ts, l0_to_recovery_framing, l0_to_recovery_retrain" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="fber_coef" descr="FBER = fber_coef*10^(-fber_magnitude)" access="RO" offset="0x60.0" size="0x0.4" />
	<field name="fber_magnitude" descr="FBER = fber_coef*10^(-fber_magnitude)" access="RO" offset="0x60.8" size="0x0.8" />
</node>

<node name="pcie_physical_layer_ext" descr="" size="0x4.0" >
	<field name="eqlz_timeout_ph0" descr="" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="eqlz_timeout_ph1" descr="" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="eqlz_timeout_ph2" descr="" access="RO" offset="0x0.2" size="0x0.1" />
	<field name="eqlz_timeout_ph3" descr="" access="RO" offset="0x0.3" size="0x0.1" />
</node>

<node name="pcmr_reg_ext" descr="" size="0xc.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fcs_cap" descr="Specifies the check enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability: \;FCS check disable/enable capability" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="rx_ts_over_crc_cap" descr="Specifies the ingress timestamps enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability" access="RO" offset="0x4.13" size="0x0.1" />
	<field name="rx_fcs_drop_cap" descr="Specifies the ingress drop enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability" access="RO" offset="0x4.14" size="0x0.1" />
	<field name="tx_fcs_recalc_cap" descr="Specifies the egress drop enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability" access="RO" offset="0x4.15" size="0x0.1" />
	<field name="tx_ts_over_crc_cap" descr="Specifies the egress timestamps enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability" access="RO" offset="0x4.16" size="0x0.1" />
	<field name="vendor_specific_vlan_type_en_cap" descr="A bit set to 1 for affirmation of supported enable/disable capability of vendor specific VLAN tagging." access="RO" offset="0x4.22" size="0x0.1" />
	<field name="encap_replace_ipv4_id_en_cap" descr="Specifies if HW overrides the ip packet id field with a random value. A bit set to 1 for affirmation of supported enable/disable capability" access="RO" offset="0x4.25" size="0x0.1" />
	<field name="mpls_explicit_null_en_cap" descr="Specifies parser mpls null label. A bit set to 1 for affirmation of supported enable/disable capability" access="RO" offset="0x4.26" size="0x0.1" />
	<field name="entropy_gre_calc_cap" descr="Specifies the egress GRE tunnel protocol entropy calculation enable/disable capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.29" size="0x0.1" />
	<field name="entropy_calc_cap" descr="Specifies the egress tunnel protocol entropy calculation enable/disable capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.30" size="0x0.1" />
	<field name="force_entropy_cap" descr="Specifies the egress tunnel protocol entropy calculation force capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="fcs_chk" descr="FCS check\;Values:\;0: disable check. \;1: perform check\;Note: when disabling a check, it will also affects the relevant counters." access="RW" offset="0x8.1" size="0x0.1" />
	<field name="rx_ts_over_crc" descr="RX TimeStamp over FCS\;0: no TS over FCS\;1: TS over FCS\;Note: \;1. If this field is changed while traffic is passing then some packets may be dropped due to incorrect FCS.\;2. Default value is (1) - TS over FCS\;Reserved when GPUNet" access="RW" offset="0x8.13" size="0x0.1" />
	<field name="rx_fcs_drop" descr="RX FCS drop control:\;0: ingress port will drop a packet with bad FCS (Default)\;1: ingress port will not drop a packet with bad FCS\;NOTE: All FCS counters (PPCNT) are valid for both drop modes.\;NOTE: Reserved when PCMR.fcs_cap=1 &amp; PCMR.fcs_chk=0" access="RW" offset="0x8.14" size="0x0.1" />
	<field name="tx_fcs_recalc" descr="TX FCS recalculation:\;0: egress port will recalculate and overwrite FCS value (Default) \;1: egress port will not overwrite FCS value \;NOTE: when this bit is set, any modification of the packet will result in a bad FCS.\;Reserved when GPUNet" access="RW" offset="0x8.15" size="0x0.1" />
	<field name="tx_ts_over_crc" descr="TX TimeStamp over FCS\;0: no TS over FCS\;1: TS over FCS\;Reserved when tx_fcs_recalc is set\;Reserved when GPUNet" access="RW" offset="0x8.16" size="0x0.1" />
	<field name="vendor_specific_vlan_type_en" descr="Specifies if vendor specific VLAN tagging is used.\;When set, HW parser will use 0x9900 as VLAN vs-tag type value." access="RW" offset="0x8.22" size="0x0.1" />
	<field name="encap_replace_ipv4_id_en" descr="0: ENABLE - HW overrides the ipv4 packet id field with a random value.\;1: DISABLE - encap ipv4 packet id field remains." access="RW" enum="ENABLE=0x0,DISABLE=0x1" offset="0x8.25" size="0x0.1" />
	<field name="mpls_explicit_null_en" descr="0: ENABLE - mpls explicit null label is parsed (default behaviour). \;1: DISABLE - mpls explicit null label is skipped by parser." access="RW" enum="ENABLE=0x0,DISABLE=0x1" offset="0x8.26" size="0x0.1" />
	<field name="entropy_gre_calc" descr="0: DISABLE - entropy calculation is disabled for GRE tunneling protocol.\;1: ENABLE - entropy calculation is enabled for GRE tunneling protocol, if entropy_calc is enabled as well. valid only if force_entropy is activated.\;Reserved when GPUNet" access="RW" enum="DISABLE=0x0,ENABLE=0x1" offset="0x8.29" size="0x0.1" />
	<field name="entropy_calc" descr="0: DISABLE - entropy calculation is disabled for all supported tunneling protocols.\;1: ENABLE - entropy calculation is enabled for all supported tunneling protocols. GRE also depends on the entropy_gre_calc valid only if force_entropy is activated.\;Reserved when GPUNet" access="RW" enum="DISABLE=0x0,ENABLE=0x1" offset="0x8.30" size="0x0.1" />
	<field name="force_entropy" descr="0: DFLT - use device defaults for tunnel entropy calculation. This mode should be used if entropy calculation requirement is unknown.\;1: FORCE - force the entropy calculation according to entropy_calc and entropy_gre_calc.\;Reserved when GPUNet" access="RW" enum="DFLT=0x0,FORCE=0x1" offset="0x8.31" size="0x0.1" />
</node>

<node name="pcnr_reg_ext" descr="" size="0xc.0" >
	<field name="tuning_override" descr="When set, port will override tuning process upon following link-up command (PAOS.admin_status = UP).\;Cleared by FW once PAOS.admin_status = UP command is set.\;\;The tuning_override is recommended to be set when port operational status is UP (PAOS.oper_status=0x1).\;If the field is set while operational status is DOWN (PAOS.oper_status=0x2), port will do best effort of fast linkup on the possible parts of the link (that is, known internal links that cannot change)." access="WO" offset="0x0.0" size="0x0.1" />
	<field name="flua_cap" descr="When set, indicates if flua_en, flua_guar_sec, flua_polling_sec, flua_allowed_ber, flu_always_oper is supported and valid." access="RO" offset="0x0.2" size="0x0.1" />
	<field name="flua_we_mask" descr="Bitmask for all flua fiels. When bit is set in mask, the relevant field configuration is valid. Otherwise, field ignores the value.\;Bit 0: flua_en\;bit 1: flua_allowed_ber\;Bit 2: flua_polling_sec\;Bit 3: flua_guar_sec" access="WO" enum="flua_en=0x1,flua_allowed_ber=0x2,flua_polling_sec=0x4,flua_guar_sec=0x8" offset="0x0.3" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="keep_phy_setting" descr="When Set, The port will keep the same phy setting upon link down event that occurs only upon link down command of peer port. In the event of Down command/cable disconnect, entire link up flow will be initialized.\;\;NOTE: This mode can be configured only when PTYS.an_disable_admin is set (i.e. AN is disabled). \;NOTE: if physical environment was changed (i.e. replacement of module, temp change, etc) there is a possibility that link won&apos;t be established or will be established with high BER" access="WO" offset="0x4.0" size="0x0.1" />
	<field name="flua_en" descr="Get valid only if flua_cap is set.\;Set is valid only if flua_cap and flua_we are set.\;valid only if flua_cap is set\;0: device_default_behavior\;1: enable_fast_linkup_always\;2: disable_fast_linkup_always\;\;When enabled, fast linkup attempt will always be performed. On fast linkup failure, regular linkup flow will be performed.\;flu configuration is ignored when flu_always enabled" access="RW" enum="device_default_behavior=0x0,enable_fast_linkup_always=0x1,disable_fast_linkup_always=0x2" offset="0x4.4" size="0x0.2" />
	<field name="flua_oper" descr="Valid only if flua_cap is set.\;Fast link Up always operational satus\;0: fast_linkup_always_was_not_performed\;1: fast_linkup_always_was_performed" access="RO" enum="fast_linkup_always_was_not_performed=0x0,fast_linkup_always_was_performed=0x1" offset="0x4.6" size="0x0.2" />
	<field name="flua_allowed_ber" descr="BER exponent threshold for allowed ber during the guard period." access="RW" offset="0x4.8" size="0x0.8" />
	<field name="flua_polling_sec" descr="Get valid only if flua_cap is set.\;Set is valid only if flua_cap and flua_we are set.\;Polling allowed time in 2.5 sec granularity.\;When fast linkup always is enabled.\;Determines the amount of time to try fast-linkup during polling state. when timer expires in polling state, regular linkup will be performed" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="flua_guar_sec" descr="Get valid only if flua_cap is set.\;Set is valid only if flua_cap and flua_we are set.\;Guard peiod in sec.\;When fast linkup always is enabled, determines the amount of time after link is up that if the link drops or BER threshold is met, next linkup will not perform fast-linkup." access="RW" offset="0x4.24" size="0x0.5" />
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
	<field name="core_to_phy_link_nvlink_enabled" descr="NVLink protocols admin state\;see: Table  1890, &quot;PTYS - Extended Protocol NVLink - admin Layout,&quot; on page  2192" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_cable_cap_eth_ext" descr="" size="0x4.0" >
	<field name="cable_ext_eth_proto_cap" descr="Cable Ethernet protocols cap. If PTYS.ext_eth_proto_cap filed is supported, use for opcode definition PTYS.ext_eth_proto_capIf PTYS.ext_eth_proto_capability mask is empty, use For opcode definition PTYS.eth_proto_cap." access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_cable_cap_ib_ext" descr="" size="0x4.0" >
	<field name="cable_link_speed_cap" descr="Cable support IB speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="cable_link_width_cap" descr="Cable support IB width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_cable_cap_nvlink_ext" descr="" size="0x4.0" >
	<field name="cable_nvlink_proto_cap" descr="Cable NVLink protocols cap:\;See: Table  1888, &quot;PTYS - Extended Protocol NVLink - cap/oper Layout,&quot; on page  2191" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_link_active_eth_ext" descr="" size="0x4.0" >
	<field name="link_eth_active" descr="Ethernet protocols active: see PTYS.ext_eth_proto_oper" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_link_active_ib_ext" descr="" size="0x4.0" >
	<field name="link_speed_active" descr="IB link active speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="link_width_active" descr="IB link active width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_link_active_nvlink_ext" descr="" size="0x4.0" >
	<field name="link_nvlink_active" descr="NVLink protocols active\;See: Table  1888, &quot;PTYS - Extended Protocol NVLink - cap/oper Layout,&quot; on page  2191" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_link_down_info_page_ext" descr="" size="0xf4.0" >
	<field name="down_blame" descr="Which receiver caused last link down: \;0: Unknown\;1: Local_phy\;2: Remote_phy" access="RO" enum="Unknown=0x0,Local_phy=0x1,Remote_phy=0x2" offset="0x0.0" size="0x0.4" />
	<field name="down_intent" descr="For the last link down reason, indicates if the link drop was intentional (e.g port down command, cable unplug etc...) or unintentional (e.g Bad SI).\;down_intent is updated on the link drop according to local reason information and updated again on LinkUp according to local + peer down reason (only if negotiation took place during linkup flow)" access="RO" offset="0x0.4" size="0x0.4" />
	<field name="local_reason_opcode" descr="Opcode of link down reason for local / remote side / last successful recovery entry reason: \;Recovery entry reason supported only if PCAM.feature_cap_mask bit 117 is set\;0: No_link_down_indication\;1: Unknown_reason\;2: Hi_BER\;3: Block_Lock_loss\;4: Alignment_loss\;5: FEC_sync_loss\;6: PLL_lock_loss\;7: FIFO_overflow\;8: false_SKIP_condition\;9: Minor_Error_threshold_exceeded\;10: Physical_layer_retransmission_timeout\;11: Heartbeat_errors\;12: Link_Layer_credit_monitoring_watchdog\;13: Link_Layer_integrity_threshold_exceeded\;14: Link_Layer_buffer_overrun\;15: Down_by_outband_command_with_healthy_link\;16: Down_by_outband_command_for_link_with_hi_ber\;17: Down_by_inband_command_with_healthy_link\;18: Down_by_inband_command_for_link_with_hi_ber\;19: Down_by_verification_GW\;20: Received_Remote_Fault \;21: Received_TS1\;22: Down_by_management_command\;23: Cable_was_unplugged\;24: Cable_access_issue \;25: Cable_Thermal_shutdown \;26: Current_issue \;27: Power_budget\;28: Fast_recovery_raw_ber\;29: Fast_recovery_effective_ber\;30: Fast_recovery_symbol_ber\;31: Fast_recovery_credit_watchdog\;32: Peer_side_down_to_sleep_state\;33: Peer_side_down_to_disable_state\;34: Peer_side_down_to_disable_and_port_lock\;35: Peer_side_down_due_to_thermal_event\;36: Peer_side_down_due_to_force_event\;37: Peer_side_down_due_to_reset_event\;38: Reset_no_power_cycle\;39: Fast_recovery_tx_plr_trigger\;40: Down_due_to_HW_force_event\;42: L1_exit_failure\;43: too_many_link_error_recoveries\;44: Down_due_to_contain_mode\;45: BW_loss_threshold_exceeded\;46: ELS_laser_fault\;47: Hi_SER\;48: down_by_nmx_adminstate_cmd\;49: flua_ber_below_threshold_in_guard_time\;50: Received_Local_Fault \;51: Received_Link_Interruption\;52: Manual_debug_mode\;53: command_triggered_recovery\;58: Recovery_BW_loss_threshold_exceeded\;5" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="recovery_entry_reason" descr="Opcode of link down reason for local / remote side / last successful recovery entry reason: \;Recovery entry reason supported only if PCAM.feature_cap_mask bit 117 is set\;0: No_link_down_indication\;1: Unknown_reason\;2: Hi_BER\;3: Block_Lock_loss\;4: Alignment_loss\;5: FEC_sync_loss\;6: PLL_lock_loss\;7: FIFO_overflow\;8: false_SKIP_condition\;9: Minor_Error_threshold_exceeded\;10: Physical_layer_retransmission_timeout\;11: Heartbeat_errors\;12: Link_Layer_credit_monitoring_watchdog\;13: Link_Layer_integrity_threshold_exceeded\;14: Link_Layer_buffer_overrun\;15: Down_by_outband_command_with_healthy_link\;16: Down_by_outband_command_for_link_with_hi_ber\;17: Down_by_inband_command_with_healthy_link\;18: Down_by_inband_command_for_link_with_hi_ber\;19: Down_by_verification_GW\;20: Received_Remote_Fault \;21: Received_TS1\;22: Down_by_management_command\;23: Cable_was_unplugged\;24: Cable_access_issue \;25: Cable_Thermal_shutdown \;26: Current_issue \;27: Power_budget\;28: Fast_recovery_raw_ber\;29: Fast_recovery_effective_ber\;30: Fast_recovery_symbol_ber\;31: Fast_recovery_credit_watchdog\;32: Peer_side_down_to_sleep_state\;33: Peer_side_down_to_disable_state\;34: Peer_side_down_to_disable_and_port_lock\;35: Peer_side_down_due_to_thermal_event\;36: Peer_side_down_due_to_force_event\;37: Peer_side_down_due_to_reset_event\;38: Reset_no_power_cycle\;39: Fast_recovery_tx_plr_trigger\;40: Down_due_to_HW_force_event\;42: L1_exit_failure\;43: too_many_link_error_recoveries\;44: Down_due_to_contain_mode\;45: BW_loss_threshold_exceeded\;46: ELS_laser_fault\;47: Hi_SER\;48: down_by_nmx_adminstate_cmd\;49: flua_ber_below_threshold_in_guard_time\;50: Received_Local_Fault \;51: Received_Link_Interruption\;52: Manual_debug_mode\;53: command_triggered_recovery\;58: Recovery_BW_loss_threshold_exceeded\;5" access="RO" enum="No_link_down_indication=0x0,Unknown_reason=0x1,Hi_BER=0x2,Block_Lock_loss=0x3,Alignment_loss=0x4,FEC_sync_loss=0x5,PLL_lock_loss=0x6,FIFO_overflow=0x7,false_SKIP_condition=0x8,Minor_Error_threshold_exceeded=0x9,Physical_layer_retransmission_timeout=0xa,Heartbeat_errors=0xb,Link_Layer_credit_monitoring_watchdog=0xc,Link_Layer_integrity_threshold_exceeded=0xd,Link_Layer_buffer_overrun=0xe,Down_by_outband_command_with_healthy_link=0xf,Down_by_outband_command_for_link_with_hi_ber=0x10,Down_by_inband_command_with_healthy_link=0x11,Down_by_inband_command_for_link_with_hi_ber=0x12,Down_by_verification_GW=0x13,Received_Remote_Fault=0x14,Received_TS1=0x15,Down_by_management_command=0x16,Cable_was_unplugged=0x17,Cable_access_issue=0x18,Cable_Thermal_shutdown=0x19,Current_issue=0x1a,Power_budget=0x1b,Fast_recovery_raw_ber=0x1c,Fast_recovery_effective_ber=0x1d,Fast_recovery_symbol_ber=0x1e,Fast_recovery_credit_watchdog=0x1f,Peer_side_down_to_sleep_state=0x20,Peer_side_down_to_disable_state=0x21,Peer_side_down_to_disable_and_port_lock=0x22,Peer_side_down_due_to_thermal_event=0x23,Peer_side_down_due_to_force_event=0x24,Peer_side_down_due_to_reset_event=0x25,Reset_no_power_cycle=0x26,Fast_recovery_tx_plr_trigger=0x27,Down_due_to_HW_force_event=0x28,L1_exit_failure=0x2a,too_many_link_error_recoveries=0x2b,Down_due_to_contain_mode=0x2c,BW_loss_threshold_exceeded=0x2d,ELS_laser_fault=0x2e,Hi_SER=0x2f,down_by_nmx_adminstate_cmd=0x30,flua_ber_below_threshold_in_guard_time=0x31,Received_Local_Fault=0x32,Received_Link_Interruption=0x33,Manual_debug_mode=0x34,command_triggered_recovery=0x35,Recovery_BW_loss_threshold_exceeded=0x3a" offset="0x4.16" size="0x0.8" />
	<field name="remote_reason_opcode" descr="Opcode of link down reason for local / remote side / last successful recovery entry reason: \;Recovery entry reason supported only if PCAM.feature_cap_mask bit 117 is set\;0: No_link_down_indication\;1: Unknown_reason\;2: Hi_BER\;3: Block_Lock_loss\;4: Alignment_loss\;5: FEC_sync_loss\;6: PLL_lock_loss\;7: FIFO_overflow\;8: false_SKIP_condition\;9: Minor_Error_threshold_exceeded\;10: Physical_layer_retransmission_timeout\;11: Heartbeat_errors\;12: Link_Layer_credit_monitoring_watchdog\;13: Link_Layer_integrity_threshold_exceeded\;14: Link_Layer_buffer_overrun\;15: Down_by_outband_command_with_healthy_link\;16: Down_by_outband_command_for_link_with_hi_ber\;17: Down_by_inband_command_with_healthy_link\;18: Down_by_inband_command_for_link_with_hi_ber\;19: Down_by_verification_GW\;20: Received_Remote_Fault \;21: Received_TS1\;22: Down_by_management_command\;23: Cable_was_unplugged\;24: Cable_access_issue \;25: Cable_Thermal_shutdown \;26: Current_issue \;27: Power_budget\;28: Fast_recovery_raw_ber\;29: Fast_recovery_effective_ber\;30: Fast_recovery_symbol_ber\;31: Fast_recovery_credit_watchdog\;32: Peer_side_down_to_sleep_state\;33: Peer_side_down_to_disable_state\;34: Peer_side_down_to_disable_and_port_lock\;35: Peer_side_down_due_to_thermal_event\;36: Peer_side_down_due_to_force_event\;37: Peer_side_down_due_to_reset_event\;38: Reset_no_power_cycle\;39: Fast_recovery_tx_plr_trigger\;40: Down_due_to_HW_force_event\;42: L1_exit_failure\;43: too_many_link_error_recoveries\;44: Down_due_to_contain_mode\;45: BW_loss_threshold_exceeded\;46: ELS_laser_fault\;47: Hi_SER\;48: down_by_nmx_adminstate_cmd\;49: flua_ber_below_threshold_in_guard_time\;50: Received_Local_Fault \;51: Received_Link_Interruption\;52: Manual_debug_mode\;53: command_triggered_recovery\;58: Recovery_BW_loss_threshold_exceeded\;5" access="RO" offset="0x8.0" size="0x0.8" />
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
	<field name="pcs_phy_state_latched" descr="PCS HW state on link-down, latched:\;Bits 0-7: Block lock (one bit per lane) - No FEC mode\;Bits 8-15: AM lock (one bit per lane) - RS FEC mode\;Bits 16-23: FEC lock (one bit per lane) - FC FEC mode\;Bit 24: Align_status\;Bit 25: Hi_BER\;Bit 26: Hi_SER\;Bits 30:27: Reserved\;Bit 31: Active. When set the value of the pcs_phy_state_latched is valid" access="RO" offset="0x34.0" size="0x4.0" />
</node>

<node name="pddr_link_partner_info_ext" descr="" size="0x30.0" >
	<field name="info_supported_mask" descr="bitmask for supported info\;0 - field info is not valid.\;1 - field info is valid.\;\;Bit 0: partner_local_port_supported\;Bit 1: partner_module_type_supported\;Bit 2: partner_id_lsb_supported\;Bit 4: peer_ga_id" access="RO" enum="partner_local_port_supported=0x1,partner_module_type_supported=0x2,partner_id_lsb_supported=0x4,peer_ga_id=0x10" offset="0x0.0" size="0x0.16" />
	<field name="partner_local_port" descr="local_port of link partner\;Valid only if bit 0 is set in info_supported_mask" access="RO" offset="0x4.0" size="0x0.10" />
	<field name="partner_module_type" descr="module type of link partner.\;Module type connected:\;0: undefined\;1: Active_Optical_or_Copper_Cable\;2: Active_Optical_Transceiver\;3: Passive_Copper_cable\;5: Twisted_pair\;6: Far_End_Linear_Equalizer_Cable\;7: Linear_Optical_Transceiver - (Direct Drive)\;8: CPO\;9: Near_end_linear_equalizer_cable\;10: Fully_linear_equalizer_cable\;11: Half_retimed_tx_optical_transceiver\;\;Valid only if bit 1 is set in info_supported_mask" access="RO" enum="undefined=0x0,Active_Optical_or_Copper_Cable=0x1,Active_Optical_Transceiver=0x2,Passive_Copper_cable=0x3,Twisted_pair=0x5,Far_End_Linear_Equalizer_Cable=0x6,Linear_Optical_Transceiver=0x7,CPO=0x8,Near_end_linear_equalizer_cable=0x9,Fully_linear_equalizer_cable=0xa,Half_retimed_tx_optical_transceiver=0xb" offset="0x8.0" size="0x0.4" />
	<field name="peer_ga_id" descr="Valid only if Bit 4 is set in info_supported_mask.\;Indicates the peer port Geographical Adress (GA) OR Module ID in GPU case" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="partner_id_lsb" descr="24 lsb bits of link partner unique ID:\;GUID IB InfiniBand links\;MAC in Ethernet links\;Valid only if bit 2 is set in info_supported_mask" access="RO" offset="0x10.0" size="0x0.24" />
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

<node name="pddr_module_info_ext" descr="" size="0xd8.0" >
	<field name="ethernet_compliance_code" descr="QSFP:\;Ethernet Compliance Codes bit mask (10/40G/100G)\;Byte131 per SFF-8636 \;Bit 7 - Extended Specification Compliance valid\;Bit 6 - 10GBASE-LRM\;Bit 5 - 10GBASE-LR\;Bit 4 - 10GBASE-SR\;Bit 3 - 40GBASE-CR4\;Bit 2 - 40GBASE-SR4\;Bit 1 - 40GBASE-LR4\;Bit 0 - 40G Active Cable (XLPPI)\;\;SFP: \;10G Ethernet Compliance Codes\;Byte3 per SFF-8472:\;Bit 7 - 10G Base-ER \;Bit 6 - 10G Base-LRM \;Bit 5 - 10G Base-LR \;Bit 4 - 10G Base-SR\;\;CMIS based (QSFP-DD/ SFP-DD / OSFP/OE)\;Byte 87 - Module Media Interface" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="ext_ethernet_compliance_code" descr="Extended Specification Compliance Codes \;for SFP:\;byte 36 per SFF-8472\;\;for QSFP:\;byte192 per SFF-8636 (QSFP28) \;\;for CMIS (SFP-DD / QSFP-DD/ OSFP/OE):\;Byte 86 - Host Electrical Interface" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="cable_breakout" descr="Reserved for SFP. \;\;For QSFP:\;Byte113 per SFF-8636\;\;For CMIS based modules:\;\;XX naming is according to cable_identifier name\;For example: if cable_identifier = ,6 XX string is QSFP-DD\;\;0 - Unspecified\;1 - XX to XX\;2 - XX to 2xQSFP or 2xXX (depopulated / 4 lanes)\;3 - XX to 4xDSFP or 4xQSFP (depopulated / 2 lanes)\;4 - XX to 8xSFP\;5 - XX (depopulated / 4 lanes) to QSFP or XX (depopulated / 4 lanes)\;6 - XX (depopulated / 4 lanes) to 2xXX(depopulated / 2 lanes) or 2xSFP-DD\;7 - XX (depopulated / 4 lanes) to 4xSFP\;8 - XX(/ 2 lane module) to XX\;9 - XX(/ 2 lane module) to 2xSFP" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="cable_technology" descr="QSFP: \;Byte 147 per SFF-8636.\;\;SFP:\;SFP+ Cable Technology: \;byte8 per SFF-8472:\;Bit 3 - Active Cable\;Bit 2 - Passive Cable\;\;CMIS based (QSFP-DD / OSFP/ SFP-DD/OE):\;Byte 212\;\;0x00: VCSEL_850nm\;0x01: VCSEL_1310nm\;0x02: VCSEL_1550nm\;0x03: FP_laser_1310nm\;0x04: DFB_laser_1310nm\;0x05: DFB_laser_1550nm\;0x06: EML_1310nm\;0x07: EML_1550nm\;0x08: others\;0x09: DFB_laser_1490nm\;0x0a: Passive_copper_cable_unequalized\;0x0b: Passive_copper_cable_equalized\;0x0c: Copper_cable_near_end_and_far_end_limiting_active_equailizer\;0x0d: Copper_cable_far_end_limiting_active_equailizer\;0x0e: Copper_cable_near_end_limiting_active_equializer\;0x0f: Copper_cable_linear_active_equalizers\;0x10: c_band_tunable_laser\;0x11: l_band_tunable_laser\;0x12: Copper_cable_near_end_and_far_end_linear_active_equalizers\;0x13: Copper_cable_far_end_linear_active_equalizers\;0x14:Copper_cable_near_end_linear_active_equalizers\;\;note - passive copper = 0xb\;Linear coppers = 0xF or 0x12 or 0x13 or 0x14" access="RW" enum="VCSEL_850nm=0x0,VCSEL_1310nm=0x1,VCSEL_1550nm=0x2,FP_laser_1310nm=0x3,DFB_laser_1310nm=0x4,DFB_laser_1550nm=0x5,EML_1310nm=0x6,EML_1550nm=0x7,others=0x8,DFB_laser_1490nm=0x9,Passive_copper_cable_unequalized=0xa,Passive_copper_cable_equalized=0xb,Copper_cable_near_end_and_far_end_limiting_active_equailizer=0xc,Copper_cable_far_end_limiting_active_equailizer=0xd,Copper_cable_near_end_limiting_active_equializer=0xe,Copper_cable_linear_active_equalizers=0xf,c_band_tunable_laser=0x10,l_band_tunable_laser=0x11,Copper_cable_near_end_and_far_end_linear_active_equalizers=0x12,Copper_cable_far_end_linear_active_equalizers=0x13,Copper_cable_near_end_linear_active_equalizers=0x14" offset="0x0.24" size="0x0.8" />
	<field name="cable_power_class" descr="Module maximum power consumption for SFP/QSFP:\;0: Power_Class_0 - (1.0 W max)\;1: Power_Class_1 - (1.5 W max)\;2: Power_Class_2 - (2.0 W max)\;3: Power_Class_3 - (2.5 W max)\;4: Power_Class_4 - (3.5 W max)\;5: Power_Class_5 - (4.0 W max)\;6: Power_Class_6 - (4.5 W max)\;7: Power_Class_7 - (5.0 W max)\;8: Power_Class_8 - (power from max_power field)\;\;Module maximum power consumption for SFP-DD:\;0: Power_Class_0 - (0.5 W max)\;1: Power_Class_1 - (1.0 W max)\;2: Power_Class_2 - (1.5 W max)\;3: Power_Class_3 - (2.0 W max)\;4: Power_Class_4 - (3.5 W max)\;5: Power_Class_5 - (5.0 W max)\;6: reserved\;7: reserved\;8: Power_Class_8 - (power from max_power field)\;\;Module maximum power consumption for QSFP-DD/OSFP:\;1 - Power_Class_1 - (1.5 W max)\;2 - Power_Class_2 - (3.5 W max)\;3 - Power_Class_3 - (7.0 W max)\;4 - Power_Class_4 - (8.0 W max)\;5 - Power_Class_5 - (10 W max)\;6 - Power_Class_6 - (12 W max)\;7 - Power_Class_7 - (14 W max)\;8 - Power_Class_8 - (power from max_power field)" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="cable_identifier" descr="0: QSFP28\;1: QSFP_Plus\;2: SFP28_or_SFP_Plus\;3: QSA - (QSFP-&gt;SFP)\;4: Backplane\;5: SFP_DD\;6: QSFP_DD\;7: QSFP_CMIS\;8: OSFP\;9: C2C\;10: DSFP\;11: QSFP_Split_Cable\;12: CPO\;13: OE\;14: ELS\;\;identifiers that are CMIS compliant are: 5,6,7,8,10" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="cable_length" descr="Cable length in 1m units.\;\;For CMIS modules:\;bits 6:7 represent cable_length_multiplier for calculating cable length\;00 - 0.1 multiplier (0.1 to 6.3m)\;01- 1 multiplier (1 to 63m)\;10 - 10 multiplier (10 to 630m)\;11 - 100 multiplier (100 to 6300m)\;\;bits 0:5 represent cable_length_value for calculating cable length.\;length is calculated with cable_length_value * cable_length_multiplier" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="cable_vendor" descr="Cable vendor:\;0: Other\;1: Mellanox\;2: Known_OUI\;3: NVIDIA\;" access="RO" enum="Other=0x0,Mellanox=0x1,Known_OUI=0x2,NVIDIA=0x3" offset="0x4.24" size="0x0.4" />
	<field name="cable_type" descr="Cable/module type:\;0: Unidentified\;1: Active_cable - (active copper / optics)\;2: Optical_Module - (separated)\;3: Passive_copper_cable_or_linear_copper - for distinguishing passive copper and linear copper see cable_technology\;4: Cable_unplugged\;5: Twisted_pair\;6: CPO\;7: OE\;8: ELS\;" access="RO" enum="Unidentified=0x0,Active_cable=0x1,Optical_Module=0x2,Passive_copper_cable_or_linear_copper=0x3,Cable_unplugged=0x4,Twisted_pair=0x5,CPO=0x6,OE=0x7,ELS=0x8" offset="0x4.28" size="0x0.4" />
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
	<field name="voltage" descr="U16 Supply Voltage Monitor as defined in SFF-8636/CMIS.\;Internally measured supply voltage in 100uV" access="RO" offset="0x4C.00" size="0x0.16" />
	<field name="temperature" descr="S16 Module Temperature Monitor as defined in SFF-8636/CMIS.\;module temperature in 1/256 C\;Value of 0 may indicate not supported or real temperature value." access="RO" offset="0x4C.16" size="0x0.16" />
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
	<field name="error_code" descr="Relevant for CMIS modules only.\;Error Code response for ControlSet configuration of DataPath.\;0x0: ConfigUndefined\;0x1: ConfigSuccess\;0x2: ConfigRejected\;0x3: ConfigRejectedInvalidAppSel\;0x4: ConfigRejectedInvalidDataPath\;0x5: ConfigRejectedInvalidSI\;0x6: ConfigRejectedLanesInUse\;0x7: ConfigRejectedPartialDataPath\;0xC: ConfigInProgress\;0xD: ConfigRejectedInvalid_VS_SI - NVIDIA vendor only" access="RO" enum="ConfigUndefined=0x0,ConfigSuccess=0x1,ConfigRejected=0x2,ConfigRejectedInvalidAppSel=0x3,ConfigRejectedInvalidDataPath=0x4,ConfigRejectedInvalidSI=0x5,ConfigRejectedLanesInUse=0x6,ConfigRejectedPartialDataPath=0x7,ConfigInProgress=0xc,ConfigRejectedInvalid_VS_SI=0xd" offset="0xC0.0" size="0x0.4" />
	<field name="max_fiber_length" descr="Maximum length of allowed fiber in meters" access="RO" offset="0xC0.16" size="0x0.16" />
	<field name="els_laser2_fault_state" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. indicate the ELS laser fault:\;0: no_fault\;1: laser_fiber_contaminated\;2: laser_APC_fault\;3: laser_power_exceeded_allowed_range\;4: laser_power_subceeded_allowed_range\;5: laser_TEC_control_loop_fault\;6: laser_ramping_timeout_fault\;7: laser_power_tuning_fault" access="RO" enum="no_fault=0x0,laser_fiber_contaminated=0x1,laser_APC_fault=0x2,laser_power_exceeded_allowed_range=0x3,laser_power_subceeded_allowed_range=0x4,laser_TEC_control_loop_fault=0x5,laser_ramping_timeout_fault=0x6,laser_power_tuning_fault=0x7" offset="0xC4.10" size="0x0.3" />
	<field name="els_laser_fault_state" descr="indicate the ELS laser fault.\;0: no_fault\;1: laser_fiber_contaminated\;2: laser_APC_fault\;3: laser_power_exceeded_allowed_range\;4: laser_power_subceeded_allowed_range\;5: laser_TEC_control_loop_fault\;6: laser_ramping_timeout_fault\;7: laser_power_tuning_fault" access="RO" enum="no_fault=0x0,laser_fiber_contaminated=0x1,laser_APC_fault=0x2,laser_power_exceeded_allowed_range=0x3,laser_power_subceeded_allowed_range=0x4,laser_TEC_control_loop_fault=0x5,laser_ramping_timeout_fault=0x6,laser_power_tuning_fault=0x7" offset="0xC4.13" size="0x0.3" />
	<field name="els2_oper_state" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. Indicates the ELS laser operative state:\;0: laser_init\;1: laser_active\;2: laser_active_with_fault\;3: laser_down\;4: laser_down_with_fault" access="RO" enum="laser_init=0x0,laser_active=0x1,laser_active_with_fault=0x2,laser_down=0x3,laser_down_with_fault=0x4" offset="0xC4.16" size="0x0.4" />
	<field name="els_oper_state" descr="Indicates the ELS laser operative state:\;0: laser_init\;1: laser_active\;2: laser_active_with_fault\;3: laser_down\;4: laser_down_with_fault" access="RO" enum="laser_init=0x0,laser_active=0x1,laser_active_with_fault=0x2,laser_down=0x3,laser_down_with_fault=0x4" offset="0xC4.20" size="0x0.4" />
	<field name="laser2_restriction" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. Each bit represent the ELS&apos;s laser restriction. When restriction are on, the laser can operate only in restricted power mode, for the safety of the optical components. Restriction can be lifted only after fiber testing.\;0: laser2_restriction_on\;1: laser2_restriction_off" access="RO" enum="laser2_restriction_on=0x0,laser2_restriction_off=0x1" offset="0xC4.24" size="0x0.1" />
	<field name="laser_restriction" descr="Relevant for CPO product. Each bit represent the ELS&apos;s laser restriction. When restriction are on, the laser can operate only in restricted power mode, for the safety of the optical components. Restriction can be lifted only after fiber testing.\;0: laser_restriction_on\;1: laser_restriction_off" access="RO" enum="laser_restriction_on=0x0,laser_restriction_off=0x1" offset="0xC4.25" size="0x0.1" />
	<field name="laser2_status" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. Each bit represent the ELS&apos;s laser status CMIS name of field.\;0: laser2_off\;1: laser2_ramping\;2: laser2_on" access="RO" enum="laser2_on=0x2" offset="0xC4.26" size="0x0.2" />
	<field name="laser_status" descr="Relevant for CPO product. Each bit represent the ELS&apos;s laser status CMIS name of field.\;0: laser_off\;1: laser_ramping\;2: laser_on" access="RO" enum="laser_on=0x2" offset="0xC4.28" size="0x0.2" />
	<field name="laser2_enabled" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. Each bit represent the ELS&apos;s laser. \;0: laser2_disabled\;1: laser2_enabled" access="RO" enum="laser2_disabled=0x0,laser2_enabled=0x1" offset="0xC4.30" size="0x0.1" />
	<field name="laser_enabled" descr="Relevant for CPO product. Each bit represent the ELS&apos;s laser. \;0: laser_disabled\;1: laser_enabled" access="RO" enum="laser_disabled=0x0,laser_enabled=0x1" offset="0xC4.31" size="0x0.1" />
	<field name="module_production_test_revision_lsb" descr="Pluggable module production test version. Lower 32 bits." access="RO" offset="0xC8.0" size="0x4.0" />
	<field name="module_production_test_revision_msb" descr="Pluggable module production test version. Upper 8 bits." access="RO" offset="0xCC.24" size="0x0.8" />
	<field name="oe_sn" descr="Relevant for virtual modules based system. represent the OE SN" access="RO" offset="0xD0.0" size="0x4.0" />
	<field name="laser_source_sn" descr="Relevant for virtual modules based system. represent the ELS SN\;" access="RO" offset="0xD4.0" size="0x4.0" />
</node>

<node name="pddr_monitor_opcode_ext" descr="" size="0x4.0" >
	<field name="monitor_opcode" descr="Status opcode: \;\;PHY FW indication (0 - 1023):\;0 - No issue observed\;1 - Port is close by command (see PAOS).\;2,3,4,38,39,60 - AN failure \;5,6,7,8, 62,63,64,65,66 - Link training failure. \;9,10,11,12,13 - Logical mismatch between link partners\;14 - Remote fault received\;15,42,17,48,49,52, - Bad signal integrity \;16,24-32 - Cable compliance code mismatch (protocol mismatch between cable and port) \;23,22,19,18,50,55- Internal error\;34,35 - Speed degradation\;56 - module_lanes_frequency_not_synced\;57 - signal not detected\;60 - no partner detected for long time\;128 - Troubleshooting in process\;1023- Info not available\;\;MNG FW issues (1024 - 2047):\;1024 - Cable is unplugged\;1025 - Long Range for non Mellanox cable/module\;1026 - Bus stuck (I2C Data or clock shorted)\;1027 - Bad/unsupported EEPROM\;1028 - Part number list\;1029 - Unsupported cable\;1030 - Module temperature shutdown\;1031 - Shorted cable\;1032 - Power budget exceeded\;1033 - Management forced down the port\;1034 - Module is disabled by command\;1035 - System Power is Exceeded therefore the module is powered off.\;1036 - Module&apos;s PMD type is not enabled (see PMTPS).\;1040 - pcie system power slot Exceeded\;1042 - Module state machine fault\;1043,1044,1045,1046 - Module&apos;s stamping speed degeneration\;1047, 1048 - Modules DataPath FSM fault\;1050, 1051, 1052, 1053- Module Boot Error\;1054 - Module Forced to Low Power by command\;1055 - ELS laser fiber is contaminated\;1056 - ELS laser power control failure\;1057 - ELS unplugged\;1058 - ELS laser rampling timeout failure\;1059 - ELS laser power exceeded allowed power range\;1060 - ELS laser power subceeded allowed power range\;1061 - ELS TEC control loop failure\;1062 - ELS laser power tuning failure\;1063 - ELS laser wavelength tuning failure" access="RW" offset="0x0.0" size="0x0.16" />
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
	<field name="resilink_fec_ind" descr="Valid only for resilink link is operational, otherwise ignored.\;\;When cleared, fec_mode_active will represent the Ethernet equivalent FEC of the resilink protocol.\;\;When set, fec_mode_active will represent the Resilink FEC protocol" access="INDEX" offset="0x0.28" size="0x0.1" />
	<field name="ib_phy_fsm_state" descr="FW IB state machine:\;0x0: IB_AN_FSM_DISABLED\;0x1: IB_AN_FSM_INITIALY\;0x2: IB_AN_FSM_RCVR_CFG\;0x3: IB_AN_FSM_CFG_TEST\;0x4: IB_AN_FSM_WAIT_RMT_TEST\;0x5: IB_AN_FSM_WAIT_CFG_ENHANCED\;0x6: IB_AN_FSM_CFG_IDLE\;0x7: IB_AN_FSM_LINK_UP\;0x8: IB_AN_FSM_POLLING" access="RO" enum="IB_AN_FSM_DISABLED=0x0,IB_AN_FSM_INITIALY=0x1,IB_AN_FSM_RCVR_CFG=0x2,IB_AN_FSM_CFG_TEST=0x3,IB_AN_FSM_WAIT_RMT_TEST=0x4,IB_AN_FSM_WAIT_CFG_ENHANCED=0x5,IB_AN_FSM_CFG_IDLE=0x6,IB_AN_FSM_LINK_UP=0x7,IB_AN_FSM_POLLING=0x8" offset="0x4.8" size="0x0.8" />
	<field name="eth_an_fsm_state" descr="Ethernet (CL73) Auto-negotiation FSM state:\;0x0: ETH_AN_FSM_ENABLE\;0x1: ETH_AN_FSM_XMIT_DISABLE\;0x2: ETH_AN_FSM_ABILITY_DETECT\;0x3: ETH_AN_FSM_ACK_DETECT\;0x4: ETH_AN_FSM_COMPLETE_ACK\;0x5: ETH_AN_FSM_AN_GOOD_CHECK\;0x6: ETH_AN_FSM_AN_GOOD\;0x7: ETH_AN_FSM_NEXT_PAGE_WAIT" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="phy_mngr_fsm_state" descr="FW Phy Manager FSM state:\;0: Disabled \;1: Open_port\;2: Polling\;3: Active\;4: Close_port\;5: Phy_up\;6: Sleep\;7: Rx_disable\;8: Signal_detect\;9: Receiver_detect\;10: Sync_peer\;11: Negotiation\;12: Training\;13: SubFSM_active\;14: Protocol_Detect\;15: Unkown\;16: Force_linkup_debug" access="RO" enum="Disabled=0x0,Open_port=0x1,Polling=0x2,Active=0x3,Close_port=0x4,Phy_up=0x5,Sleep=0x6,Rx_disable=0x7,Signal_detect=0x8,Receiver_detect=0x9,Sync_peer=0xa,Negotiation=0xb,Training=0xc,SubFSM_active=0xd,Protocol_Detect=0xe,Unkown=0xf,Force_linkup_debug=0x10" offset="0x4.24" size="0x0.8" />
	<field name="phy_manager_link_enabled" descr="For IB: Table  2174, &quot;PDDR - Phy Manager Link Enabled IB Layout,&quot; on page  2556\;For Ethernet: Table  2176, &quot;PDDR - Phy Manager Link Enabled Eth Layout,&quot; on page  2556\;For NVLink: Table  2178, &quot;PDDR - Phy Manager Link Enable NVLink Layout,&quot; on page  2557" subnode="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" access="RO" offset="0x8.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="core_to_phy_link_enabled" descr="For IB: Table  2180, &quot;PDDR - Core2phy Link Enabled IB Layout,&quot; on page  2558\;For Ethernet: Table  2182, &quot;PDDR - Core2phy Link Enabled Eth Layout,&quot; on page  2559\;For NVLink: Table  2184, &quot;PDDR - Core2phy Link Enabled NVLink Layout,&quot; on page  2559" subnode="pddr_operation_info_page_core_to_phy_link_enabled_auto_ext" access="RO" offset="0xC.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="cable_proto_cap" descr="For IB: Table  2186, &quot;PDDR - Cable Cap IB Layout,&quot; on page  2560\;For Ethernet: Table  2188, &quot;PDDR - Cable Cap Eth Layout,&quot; on page  2561\;For NVLink: Table  2190, &quot;PDDR - Cable Cap NVLink Layout,&quot; on page  2561" subnode="pddr_operation_info_page_cable_proto_cap_auto_ext" access="RO" offset="0x10.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="link_active" descr="For IB: Table  2192, &quot;PDDR - Link Active IB Layout,&quot; on page  2562\;For Ethernet: Table  2194, &quot;PDDR - Link Active Eth Layout,&quot; on page  2562\;For NVLink: Table  2196, &quot;PDDR - Link Active NVLink Layout,&quot; on page  2563" subnode="pddr_operation_info_page_link_active_auto_ext" access="RO" offset="0x14.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="loopback_mode" descr="0: No_loopback_active\;1: Phy_remote_loopback \;2: Phy_local_loopback -When set the port&apos;s egress traffic is looped back to the receiver and the port transmitter is disabled. \;4: External_local_loopback -Enables the port&apos;s transmitter to link with the port&apos;s receiver using an external loopback connector." access="RO" enum="No_loopback_active=0x0,Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4" offset="0x18.0" size="0x0.12" />
	<field name="pri_or_sec" descr="Indicates for Mode B links if the port was chosen as primary or secondary during linkup.\;0: Not_supported_or_not_chosen_yet.\;1: Primary\;2: Secondary" access="RO" enum="Not_supported_or_not_chosen_yet_=0x0,Primary=0x1,Secondary=0x2" offset="0x18.14" size="0x0.2" />
	<field name="fec_mode_request" descr="FEC mode request.\;See fec_mode_active." access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="fec_mode_active" descr="FEC mode active\;0: No_FEC\;1: Firecode_FEC\;2: Standard_RS_FEC - RS(528,514)\;3: Standard_LL_RS_FEC - RS(271,257)\;4: Interleaved_Quad_RS_FEC - (544,514)   Quad_KP4_FEC\;5: Interleaved_Quad_RS_FEC_PLR - 546,516) Quad_KP4_FEC\;6: Interleaved_Standard_RS-FEC - (544,514)\;7: Standard_RS-FEC - (544,514)\;8: Interleaved_Octet_RS_FEC_PLR -(546,516) Octet_KP4_FEC\;9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - (272,257+1)\;11: Interleaved_Standard_RS_FEC_PLR - (544,514)\;12: RS-FEC - (544,514) + PLR- [Internal]\;13: LL-FEC - (271,257) + PLR- [Internal]\;14: Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal] \;15: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]" access="RO" enum="No_FEC=0x0,Firecode_FEC=0x1,Standard_RS_FEC=0x2,Standard_LL_RS_FEC=0x3,Interleaved_Quad_RS_FEC=0x4,Interleaved_Quad_RS_FEC_PLR=0x5,Interleaved_Standard_RS=0x6,Standard_RS=0x7,Interleaved_Octet_RS_FEC_PLR=0x8,Ethernet_Consortium_LL_50G_RS_FEC=0x9,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC=0xa,Interleaved_Standard_RS_FEC_PLR=0xb,RS=0xc,LL=0xd,Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xe,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xf" offset="0x1C.16" size="0x0.16" />
	<field name="eth_100g_fec_support" descr="FEC 100G (25Gb/s per lane) supported FEC include override masking, should reflect current phy configuration after link is up\;\;Bit 0 - No FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="eth_25g_50g_fec_support" descr="FEC 25G/50G (25Gb/s per lane) supported FEC include override masking, should reflect current phy configuration after link is up\;Bit 0 - No FEC\;Bit 1 - Firecode FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;" access="RO" offset="0x20.4" size="0x0.4" />
	<field name="profile_fec_in_use" descr="The profile that has been selected: \;Bit 0 - IB spec / legacy (See profiles description) \;Bit 1 - Internal ports (Backplane) \;Bit 2 - Passive copper - Short \;Bit 3 - Passive copper - Medium \;Bit 4 - Passive copper - Long \;Bit 5 - Active optics / copper short reach (&lt;20m) \;Bit 6 - Optics long reach (&gt;20m) \;Bit 7 - NO-FEC \;Bit 8 - FEC-ON" access="RO" offset="0x20.16" size="0x0.16" />
	<field name="pd_link_enabled" descr="For IB: Table  2198, &quot;PDDR - Parallel Detect Link Enabled IB Layout,&quot; on page  2564\;For Ethernet: Table  2200, &quot;PDDR - Parallel Detect Link Enabled Eth Layout,&quot; on page  2564" subnode="pddr_operation_info_page_pd_link_enabled_auto_ext" access="RO" offset="0x24.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="phy_hst_link_enabled" descr="For IB: Table  2202, &quot;PDDR - HST Link Enabled IB Layout,&quot; on page  2565\;For Ethernet: Table  2204, &quot;PDDR - HST Link Enabled Eth Layout,&quot; on page  2566\;For NVLink: Table  2206, &quot;PDDR - HST Link Enabled NVLink Layout,&quot; on page  2566" subnode="pddr_operation_info_page_phy_hst_link_enabled_auto_ext" access="RO" offset="0x28.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="eth_an_link_enabled" descr="Table  2208, &quot;PDDR - ETH AN Link Enabled Eth Layout,&quot; on page  2567" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="test_mode_fsm_state" descr="Test mode FSM state exposure is supported only if PCAM.feature_cap_mask bit 120 is set.\;Mode B links test mode FSM\;0: Disable - this state is shared by Mode A links and Mode B links test mode FSM\;1: Open_lane\;2: Idle_mode_b\;3: Close_lane\;- Mode A links test mode FSM\;4: Receiver_detect\;5: Idle_mode_a\;6: Signal_detect\;7: Auto_fix_reversal_polarity\;8: Tuning_in_progress" access="RO" enum="Disable=0x0,Open_lane=0x1,Idle_mode_b=0x2,Close_lane=0x3,Receiver_detect=0x4,Idle_mode_a=0x5,Signal_detect=0x6,Auto_fix_reversal_polarity=0x7,Tuning_in_progress=0x8" offset="0x38.24" size="0x0.8" />
	<field name="local_host_class" descr="Local host class - Insertion loss\;0: Unspecified\;1: Host nominal (HN) - 4.45 to 13.95 dB\;2: Host low (HL) - 4.45 to 8.95 dB\;3: Host high (HH) - 4.55 to 18.5 dB\;4-7: Reserved" access="RO" offset="0x3C.0" size="0x0.3" />
	<field name="remote_host_class" descr="Remote host class - Insertion loss\;0: Unspecified\;1: Host nominal (HN) - 4.45 to 13.95 dB\;2: Host low (HL) - 4.45 to 8.95 dB\;3: Host high (HH) - 4.55 to 18.5 dB\;4-7: Reserved" access="RO" offset="0x3C.4" size="0x0.3" />
	<field name="channel_diff_loss" descr="Channel differential loss in dB. The highest loss between receivers and transmitters." access="RO" offset="0x3C.8" size="0x0.5" />
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
	<field name="hst_link_nvlink_enabled_ext" descr="" subnode="hst_link_nvlink_enabled_ext" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_phy_manager_link_enabled_eth_ext" descr="" subnode="pddr_phy_manager_link_enabled_eth_ext" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="pddr_phy_manager_link_enabled_ib_ext" descr="" subnode="pddr_phy_manager_link_enabled_ib_ext" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="pddr_phy_manager_link_enabled_nvlink_ext" descr="" subnode="pddr_phy_manager_link_enabled_nvlink_ext" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pddr_phy_info_page_ext" descr="" size="0xf8.0" >
	<field name="port_notifications" descr="Port notifications bit mask\;Bit 0 - Link partner advertised capabilities \;Bit 1 - Speed degradation" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="negotiation_mask" descr="Bit 0: eth_base_page\;Bit 1: ib_base_page\;Bit 2: ib_base_page_rev2 - XDR onwards\;Bit 3: Consortium\;Bit 4: MLPN_rev0\;Bit 5: MLPN_rev1\;Bit 6: NLPN_rev2" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="remote_device_type" descr="Remote device type: \;0 - Unknown (3rd party, Force, legacy MLPN)\;1 - CX4\;2 - CX4_LX\;3 - CX5\;4 - CX5_LX\;5 - CX6\;6 - CX6_LX\;7 - CX6_DX\;8 - CX7\;9 - Bluefield-2\;10 - CX8\;11 - Bluefield-3\;12 - CX9\;13 - CX10\;14-99 Reserved\;\;100 - SwitchIB\;101 - Spectrum \;102 - SwitchIB-2\;103 - Quantum\;104 - Spectrum-2\;105 - Spectrum-3\;106 - Quantum-2\;107 - Spectrum-4\;108 -Quantum-3\;109 - Quantum-4\;\;\;112 - Quantum-5\;113 - Quantum-6\;114 - Spectrum-7\;115-199 -Reserved\;\;200 - GB100 (OR 102/200)\;201 - GR100\;202 - GR150\;203 - Feinmann\;204 - GB10 - fusion\;205-255 - Reserved" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="lp_ib_revision" descr="Link partner IB TS revision \;\;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="ib_revision" descr="IB TS revision \;" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="num_of_negotiation_attempts" descr="Negotiation attempt counter" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="phy_manager_disable_mask" descr="Phy manager disable bit mask: \;Bit 0 - Module not present (module absence/cage power off)\;Bit 1 - PAOS command\;Bit 2 - MAD IB PortInfo down command\;Bit 3 - Long range cable (Non Mellanox) \;Bit 4 - Verification command\;Bit 5 - ekey command\;Bit 6 - High power - cable require higher power than allowed.\;Bit 7 - Unknown Identifier (Module)\;Bit 8 - PAOS up once \;Bit 9 - Stamping failure\;Bit 10 - Calibration not done\;Bit 11 - Module Locking\;Bit 13 - Power budget exceeded\;Bit 14 - Interrupt Event / Module Temp\;Bit 15 - TEC flow / module bring up issue" access="RO" offset="0x8.0" size="0x0.24" />
	<field name="hw_link_phy_state" descr="IBP HW FSM Reflected State:\;0x10: sleeping_delay\;0x11: sleeping_quiet\;0x20: polling_active\;0x21: polling_quiet\;0x30: disable\;0x31: update_retimer\;0x40: config_debounce\;0x41: config_receiver\;0x42: config_wait_remote\;0x43: config_tx_reverse_lanes\;0x44: config_enhanced    \;0x45: config_test\;0x46: confg_wait_remote_test\;0x47: config_wait_cfg_enhanced\;0x48: config_idle\;0x50: linkup\;0x51: Linkup_Tx_Idle\;0x52: Linkup_Tx_Empty\;-Recovery\;0x60: recover_retrain\;0x61: recover_wait_remote\;0x62: recover_idle\;0x63: Local_down_cmd\;0x64: Remote_down_cmd\;0x65: uphy_recovery_send_ts1\;0x66: uphy_recovery_send_pam2\;0x67: uphy_recovery_send_pam4\;0x68: uphy_recovery_peq\;0x70: test\;- Force Modes\;0x80: Force_send_ts1 - command may be given only on disable state\;0x90: Force_send_ts2\;0xA0: Force_Sent_Idle\;0xB0: Force_send_ts_Mlnx\;0xC0: Force_send_ts3\;0xD0: Force_LinkUp\;- L1\;0xE0: Go_To_Quiet\;0xE1: Retimer_Align\;0xE2: Quiet_Entry\;0xE3: Quiet\;0xE4: Wake\;0xE5: Wake_Tx_Sleep0\;0xE6: Send_Announce\;0xE7: Tx_HS\;0xE8: Wait_For_Cdr_Lock" access="RO" enum="sleeping_delay=0x10,sleeping_quiet=0x11,polling_active=0x20,polling_quiet=0x21,disable=0x30,update_retimer=0x31,config_debounce=0x40,config_receiver=0x41,config_wait_remote=0x42,config_tx_reverse_lanes=0x43,config_enhanced=0x44,config_test=0x45,confg_wait_remote_test=0x46,config_wait_cfg_enhanced=0x47,config_idle=0x48,linkup=0x50,Linkup_Tx_Idle=0x51,Linkup_Tx_Empty=0x52,recover_retrain=0x60,recover_wait_remote=0x61,recover_idle=0x62,Local_down_cmd=0x63,Remote_down_cmd=0x64,uphy_recovery_send_ts1=0x65,uphy_recovery_send_pam2=0x66,uphy_recovery_send_pam4=0x67,uphy_recovery_peq=0x68,test=0x70,Force_send_ts1=0x80,Force_send_ts2=0x90,Force_Sent_Idle=0xa0,Force_send_ts_Mlnx=0xb0,Force_send_ts3=0xc0,Force_LinkUp=0xd0,Go_To_Quiet=0xe0,Retimer_Align=0xe1,Quiet_Entry=0xe2,Quiet=0xe3,Wake=0xe4,Wake_Tx_Sleep0=0xe5,Send_Announce=0xe6,Tx_HS=0xe7,Wait_For_Cdr_Lock=0xe8" offset="0x8.24" size="0x0.8" />
	<field name="pcs_phy_state" descr="PCS HW state:\;Bits 0-7: Block lock (one bit per lane)\;Bits 8-15: AM lock (one bit per lane)\;Bits 16-23: FEC lock (one bit per lane)\;Bits 24: Align_status\;Bits 25: Hi_BER\;Bits 26: Hi_SER" access="RO" offset="0xC.0" size="0x4.0" />
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
	<field name="plr_rtt_xdr_2x_ell_threshold" descr="rtt threshold in 1 ns units for XDR_2x speeds with ELL FEC" access="RO" offset="0xA8.16" size="0x0.16" />
	<field name="train_ctl_state" descr="The actual state of the Training control state diagram (IEEE 802.3dj Annex 178B Figure 178B-10).\;0: QUIET\;1: SEND_TRAINING\;2: TRAIN_START\;3: TRAIN_LOCAL\;4: TRAIN_REMOTE\;5: ISL_READY\;6: PATH_READY\;7: PATH_UP\;8: RECOVERY\;9: FAIL\;10: SEND_LOCAL\;11: RX_READY" access="RO" enum="QUIET=0x0,SEND_TRAINING=0x1,TRAIN_START=0x2,TRAIN_LOCAL=0x3,TRAIN_REMOTE=0x4,ISL_READY=0x5,PATH_READY=0x6,PATH_UP=0x7,RECOVERY=0x8,FAIL=0x9,SEND_LOCAL=0xa,RX_READY=0xb" offset="0xBC.0" size="0x0.4" />
	<field name="rts_update_state" descr="The actual state of the RTS update state diagram (IEEE 802.3dj Annex 178B Figure 178B-9).\;0: START\;1: WAIT_ADJACENT\;2: SWITCH_CLOCK\;3: TX_CLOCK_READY\;4: FORWARD_RTS" access="RO" offset="0xBC.5" size="0x0.3" />
	<field name="rts_status" descr="The status of the RTS function.\;0: FAIL: Any lane training failed\;1: OK: All lanes are OK\;2: READY: remote_rts is true and training_status is READY\;3: IN_PROGRESS: training_status is IN_PROGRESS or remote_rts is false and training_status is READY" access="RO" offset="0xBC.9" size="0x0.2" />
	<field name="training_status" descr="The status of the ILT function.\;0: FAIL: Any lane training failed\;1: OK: All lanes are OK\;2: READY: All lanes are TRAINED or OK with at least one lane being TRAINED\;3: IN_PROGRESS: At least one lane is being trained and no lanes training failed" access="RO" offset="0xBC.12" size="0x0.2" />
	<field name="tx_mode" descr="Indicates the content of the transmitter output of the lane when tx_disable = 0.\;0: Training\;1: local pattern being transmitted (for training_enable = 0)\;2: Normal data from PCS being transmitted" access="RO" offset="0xBC.15" size="0x0.2" />
	<field name="polarity_correction" descr="Indicates that an inverted LT frame marker has been detected" access="RO" offset="0xBC.18" size="0x0.1" />
	<field name="tx_disable" descr="Transmitter disabled (squelch). Used only if training_enable = 0" access="RO" offset="0xBC.19" size="0x0.1" />
	<field name="remote_rts" descr="Received in the LT frames to indicate that the remote interface is ready to send (Invert of the Continue Training bit in the LT frame)" access="RO" offset="0xBC.20" size="0x0.1" />
	<field name="local_rts" descr="Local interface ready to send" access="RO" offset="0xBC.21" size="0x0.1" />
	<field name="remote_rx_ready" descr="Received in the LT frames to indicate that the remote interface completed training" access="RO" offset="0xBC.22" size="0x0.1" />
	<field name="local_rx_ready" descr="Local interface completed training" access="RO" offset="0xBC.23" size="0x0.1" />
	<field name="remote_tf_lock" descr="The training frame marker position has been identified on a lane by the peer. Reflects the value of the receiver frame lock bit of the status field of the received training frame." access="RO" offset="0xBC.24" size="0x0.1" />
	<field name="local_tf_lock" descr="The training frame marker position has been identified on a lane of the interface." access="RO" offset="0xBC.25" size="0x0.1" />
	<field name="local_type" descr="Local type.\;001: CPO \;010: LPO \;011: FRO \;110: TRO \;111: Not supported" access="RO" offset="0xC4.0" size="0x0.3" />
	<field name="remote_type" descr="Peer type.\;100: Not detected\;001: CPO detected\;010: LPO detected\;011: FRO detected\;110: TRO detected\;111: Not supported" access="RO" offset="0xC4.4" size="0x0.3" />
	<field name="nvidia_peer" descr="Nvidia peer detected indication" access="RO" offset="0xC4.9" size="0x0.1" />
</node>

<node name="pddr_phy_manager_link_enabled_eth_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_eth_enabled" descr="Ethernet protocols admin state: see PTYS.ext_eth_proto_admin" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_phy_manager_link_enabled_ib_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_proto_enabled" descr="IB link enabled speed:\;Bit 0 - SDR\;Bit 1 - DDR\;Bit 2 - QDR\;Bit 3 - FDR10\;Bit 4 - FDR\;Bit 5 - EDR\;Bit 6 - HDR\;Bit 7 - NDR\;Bit 8 - XDR" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="phy_manager_link_width_enabled" descr="IB link enabled width:\;Bit 0 - 1x\;Bit 1 - 2x\;Bit 2 - 4x\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_phy_manager_link_enabled_nvlink_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_nvlink_enabled" descr="NVLink protocols admin state: \;see: Table  1890, &quot;PTYS - Extended Protocol NVLink - admin Layout,&quot; on page  2192" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_reg_ext" descr="" size="0x100.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM \;0: Network_port\;1: Near_End_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: Far_End_Port - (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" enum="Network_port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;1: IB_port_number\;3: Out_of_band_or_PCI" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band_or_PCI=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="module_ind_type" descr="Module index type selector:\;0: CPO_or_pluggable_modules\;1: OE\;2: ELS" access="INDEX" enum="CPO_or_pluggable_modules=0x0,OE=0x1,ELS=0x2" offset="0x0.24" size="0x0.2" />
	<field name="page_select" descr="page select index:\;0: Operational_info_page\;1: Troubleshooting_info_page\;2: Phy_info_page\;3: Module_info_page\;6: link_down_info\;8: Link_up_info\;9: Module_latched_flag_info_page\;11: link_partner_info_page" access="INDEX" enum="Operational_info_page=0x0,Troubleshooting_info_page=0x1,Phy_info_page=0x2,Module_info_page=0x3,link_down_info=0x6,Link_up_info=0x8,Module_latched_flag_info_page=0x9,link_partner_info_page=0xb" offset="0x4.0" size="0x0.8" />
	<field name="module_info_ext" descr="Module info extended configurations.\;resolution for rx_power, rx_power_high_th, rx_power_low_th tx_power, tx_power_high_th, tx_power_low_th in module info page\;0: dbm\;1: uW" access="OP" enum="dbm=0x0,uW=0x1" offset="0x4.29" size="0x0.2" />
	<field name="page_data" descr="Table  2172, &quot;Operation Info Page Layout,&quot; on page  2546\;Table  2218, &quot;Troubleshooting info Page layout,&quot; on page  2613\;Table  2210, &quot;Phy Info Page Layout,&quot; on page  2568\;Table  2216, &quot;Module Info Page Layout,&quot; on page  2596\;Table  2212, &quot;Link Down Info Page Layout,&quot; on page  2589\;Table  2228, &quot;Link Up Info Page Layout,&quot; on page  2626\;Table  2230, &quot;Module Latched Flag Info Page Layout,&quot; on page  2630\;Table 2240, &quot;Link Partner Info Page Layout,&quot; on page 2648\;" subnode="pddr_reg_page_data_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).page_select" />
</node>

<node name="pddr_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="module_latched_flag_info_ext" descr="" subnode="module_latched_flag_info_ext" offset="0x0.0" selected_by="Module_latched_flag_info_page" size="0x50.0" />
	<field name="pddr_link_down_info_page_ext" descr="" subnode="pddr_link_down_info_page_ext" offset="0x0.0" selected_by="link_down_info" size="0xf4.0" />
	<field name="pddr_link_partner_info_ext" descr="" subnode="pddr_link_partner_info_ext" offset="0x0.0" selected_by="link_partner_info_page" size="0x30.0" />
	<field name="pddr_link_up_info_page_ext" descr="" subnode="pddr_link_up_info_page_ext" offset="0x0.0" selected_by="Link_up_info" size="0xf8.0" />
	<field name="pddr_module_info_ext" descr="" subnode="pddr_module_info_ext" offset="0x0.0" selected_by="Module_info_page" size="0xd8.0" />
	<field name="pddr_operation_info_page_ext" descr="" subnode="pddr_operation_info_page_ext" offset="0x0.0" selected_by="Operational_info_page" size="0xf8.0" />
	<field name="pddr_phy_info_page_ext" descr="" subnode="pddr_phy_info_page_ext" offset="0x0.0" selected_by="Phy_info_page" size="0xf8.0" />
	<field name="pddr_troubleshooting_page_ext" descr="" subnode="pddr_troubleshooting_page_ext" offset="0x0.0" selected_by="Troubleshooting_info_page" size="0xf8.0" />
</node>

<node name="pddr_troubleshooting_page_ext" descr="" size="0xf8.0" >
	<field name="group_opcode" descr="0: Monitor_opcodes" access="INDEX" enum="Monitor_opcodes=0x0" offset="0x0.0" size="0x0.16" />
	<field name="status_opcode" descr="Status opcode described in:\;Table  2220, &quot;PDDR - Monitor opcodes layout,&quot; on page  2614" subnode="pddr_troubleshooting_page_status_opcode_auto_ext" access="RO" offset="0x4.0" size="0x4.0" union_selector="$(parent).group_opcode" />
	<field name="status_message" descr="ASCII code message\;All Messages are terminated by a Null character &apos;\0&apos;" access="RO" high_bound="58" low_bound="0" offset="0xC.0" size="0xec.0" />
</node>

<node name="pddr_troubleshooting_page_status_opcode_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_monitor_opcode_ext" descr="" subnode="pddr_monitor_opcode_ext" offset="0x0.0" selected_by="Monitor_opcodes" size="0x4.0" />
</node>

<node name="peir_reg_ext" descr="" size="0xc.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="error_count" descr="Error Count\;Number of times the port will generate the configured error.\;0 indicates not to generate error.\;Reading error_count will return the number of left errors to inject. When 0, all requested errors has been injected." access="RW" offset="0x4.16" size="0x0.4" />
	<field name="error_type" descr="Error Type to generate\;0 - No Error\;---- Physical Errors ----\;1 - 8/10 Symbol Error (per lane)\;2 - 8/10 Disparity Error (per lane)\;3:7 - Reserved\;8 - 64/66 Sync Header (per lane, with block count)\;9 - 64/66 Alignment Marker (per lane, with block count)\;10 - 64/66 Block Type (per lane, with block count)\;---- Packet Errors ----\;16 - EBP marking (with packet count)\;17 - Corrupt data packet ICRC\;18 - Corrupt data packet VCRC\;19 - Corrupt credit packet LPCRC\;" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="lane" descr="Bit vector for lane (bit 0, lane 0)\;Only relevant for specific errors at physical layer" access="RW" offset="0x8.16" size="0x0.4" />
</node>

<node name="pemi_Laser_Monitors_Properties_ext" descr="" size="0xf8.0" >
	<field name="optical_channel_temperature_cap" descr="Optical channel temperature capability" access="RO" offset="0x0.26" size="0x0.1" />
	<field name="els_input_power_cap" descr="ELS input power capability" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="cooled_laser_temperature_cap" descr="cooled laser temperature capability" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="laser_frequency_error_cap" descr="Laser frequency error capability" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="tec_current_cap" descr="TEC current capability" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="laser_age_cap" descr="Laser age capability" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="laser_age_high_warning" descr="Thresholds for the Laser age is presented in percentage." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="laser_age_high_alarm" descr="Thresholds for the Laser age is presented in percentage." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="tec_current_low_alarm" descr="Thresholds for the Thermo-electric Cooler (TEC) current.\;presented in percentage." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="tec_current_high_alarm" descr="Thresholds for the Thermo-electric Cooler (TEC) current.\;presented in percentage." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="tec_current_low_warning" descr="Thresholds for the Thermo-electric Cooler (TEC) current.\;presented in percentage." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="tec_current_high_warning" descr="Thresholds for the Thermo-electric Cooler (TEC) current.\;presented in percentage." access="RO" offset="0xC.16" size="0x0.16" />
	<field name="laser_frequency_error_high_warning" descr="Thresholds for the laser frequency error in unit scale of 10 MHz." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="laser_frequency_error_high_alarm" descr="Thresholds for the laser frequency error in unit scale of 10 MHz." access="RO" offset="0x10.16" size="0x0.16" />
	<field name="cooled_laser_temp_low_alarm" descr="Thresholds for the laser temperature. \;In unit scale of 1/256 Celsius degrees." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="cooled_laser_temp_high_alarm" descr="Thresholds for the laser temperature. \;In unit scale of 1/256 Celsius degrees." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="cooled_laser_temp_low_warning" descr="Thresholds for the laser temperature. \;In unit scale of 1/256 Celsius degrees." access="RO" offset="0x18.0" size="0x0.16" />
	<field name="cooled_laser_temp_high_warning" descr="Thresholds for the laser temperature. \;In unit scale of 1/256 Celsius degrees." access="RO" offset="0x18.16" size="0x0.16" />
</node>

<node name="pemi_Laser_Monitors_Samples_ext" descr="" size="0xf8.0" >
	<field name="laser_age_lane1" descr="Laser age is presented in percentage.\;0% BOL, 100% EOL." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="laser_age_lane0" descr="Laser age is presented in percentage.\;0% BOL, 100% EOL." access="RO" offset="0x0.16" size="0x0.16" />
	<field name="laser_age_lane3" descr="Laser age is presented in percentage.\;0% BOL, 100% EOL." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="laser_age_lane2" descr="Laser age is presented in percentage.\;0% BOL, 100% EOL." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="laser_age_lane5" descr="Laser age is presented in percentage.\;0% BOL, 100% EOL." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="laser_age_lane4" descr="Laser age is presented in percentage.\;0% BOL, 100% EOL." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="laser_age_lane7" descr="Laser age is presented in percentage.\;0% BOL, 100% EOL." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="laser_age_lane6" descr="Laser age is presented in percentage.\;0% BOL, 100% EOL." access="RO" offset="0xC.16" size="0x0.16" />
	<field name="tec_current_laser1" descr="Thermo-electric Cooler (TEC) current. Observes the amount of current flowing to the TEC of a cooled laser.\;TEC current presented in percentages: 100/32767 %.\;+32767 (100%) of the max current magnitude when heating\;-32767 is -100% of the max current magnitude when cooling\;" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="tec_current_laser0" descr="Thermo-electric Cooler (TEC) current. Observes the amount of current flowing to the TEC of a cooled laser.\;TEC current presented in percentages: 100/32767 %.\;+32767 (100%) of the max current magnitude when heating\;-32767 is -100% of the max current magnitude when cooling\;" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="tec_current_laser3" descr="Thermo-electric Cooler (TEC) current. Observes the amount of current flowing to the TEC of a cooled laser.\;TEC current presented in percentages: 100/32767 %.\;+32767 (100%) of the max current magnitude when heating\;-32767 is -100% of the max current magnitude when cooling\;" access="RO" offset="0x14.0" size="0x0.16" />
	<field name="tec_current_laser2" descr="Thermo-electric Cooler (TEC) current. Observes the amount of current flowing to the TEC of a cooled laser.\;TEC current presented in percentages: 100/32767 %.\;+32767 (100%) of the max current magnitude when heating\;-32767 is -100% of the max current magnitude when cooling\;" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="tec_current_laser5" descr="Thermo-electric Cooler (TEC) current. Observes the amount of current flowing to the TEC of a cooled laser.\;TEC current presented in percentages: 100/32767 %.\;+32767 (100%) of the max current magnitude when heating\;-32767 is -100% of the max current magnitude when cooling\;" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="tec_current_laser4" descr="Thermo-electric Cooler (TEC) current. Observes the amount of current flowing to the TEC of a cooled laser.\;TEC current presented in percentages: 100/32767 %.\;+32767 (100%) of the max current magnitude when heating\;-32767 is -100% of the max current magnitude when cooling\;" access="RO" offset="0x18.16" size="0x0.16" />
	<field name="tec_current_laser7" descr="Thermo-electric Cooler (TEC) current. Observes the amount of current flowing to the TEC of a cooled laser.\;TEC current presented in percentages: 100/32767 %.\;+32767 (100%) of the max current magnitude when heating\;-32767 is -100% of the max current magnitude when cooling\;" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="tec_current_laser6" descr="Thermo-electric Cooler (TEC) current. Observes the amount of current flowing to the TEC of a cooled laser.\;TEC current presented in percentages: 100/32767 %.\;+32767 (100%) of the max current magnitude when heating\;-32767 is -100% of the max current magnitude when cooling\;" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="els_input_power_lane1" descr="Laser power in OE input, in units of dBm.\;" access="RO" offset="0x20.0" size="0x0.16" />
	<field name="els_input_power_lane0" descr="Laser power in OE input, in units of dBm.\;" access="RO" offset="0x20.16" size="0x0.16" />
	<field name="els_input_power_lane3" descr="Laser power in OE input, in units of dBm.\;" access="RO" offset="0x24.0" size="0x0.16" />
	<field name="els_input_power_lane2" descr="Laser power in OE input, in units of dBm.\;" access="RO" offset="0x24.16" size="0x0.16" />
	<field name="els_input_power_lane5" descr="Laser power in OE input, in units of dBm.\;" access="RO" offset="0x28.0" size="0x0.16" />
	<field name="els_input_power_lane4" descr="Laser power in OE input, in units of dBm.\;" access="RO" offset="0x28.16" size="0x0.16" />
	<field name="els_input_power_lane7" descr="Laser power in OE input, in units of dBm.\;" access="RO" offset="0x2C.0" size="0x0.16" />
	<field name="els_input_power_lane6" descr="Laser power in OE input, in units of dBm.\;" access="RO" offset="0x2C.16" size="0x0.16" />
	<field name="laser_frequency_error_lane1" descr="Laser frequency error for media lane &lt;i&gt;, observes the difference between the target center frequency and the actual current center frequency.\;The laser frequency error is in unit scale of 10 MHz." access="RO" offset="0x30.0" size="0x0.16" />
	<field name="laser_frequency_error_lane0" descr="Laser frequency error for media lane &lt;i&gt;, observes the difference between the target center frequency and the actual current center frequency.\;The laser frequency error is in unit scale of 10 MHz." access="RO" offset="0x30.16" size="0x0.16" />
	<field name="laser_frequency_error_lane3" descr="Laser frequency error for media lane &lt;i&gt;, observes the difference between the target center frequency and the actual current center frequency.\;The laser frequency error is in unit scale of 10 MHz." access="RO" offset="0x34.0" size="0x0.16" />
	<field name="laser_frequency_error_lane2" descr="Laser frequency error for media lane &lt;i&gt;, observes the difference between the target center frequency and the actual current center frequency.\;The laser frequency error is in unit scale of 10 MHz." access="RO" offset="0x34.16" size="0x0.16" />
	<field name="laser_frequency_error_lane5" descr="Laser frequency error for media lane &lt;i&gt;, observes the difference between the target center frequency and the actual current center frequency.\;The laser frequency error is in unit scale of 10 MHz." access="RO" offset="0x38.0" size="0x0.16" />
	<field name="laser_frequency_error_lane4" descr="Laser frequency error for media lane &lt;i&gt;, observes the difference between the target center frequency and the actual current center frequency.\;The laser frequency error is in unit scale of 10 MHz." access="RO" offset="0x38.16" size="0x0.16" />
	<field name="laser_frequency_error_lane7" descr="Laser frequency error for media lane &lt;i&gt;, observes the difference between the target center frequency and the actual current center frequency.\;The laser frequency error is in unit scale of 10 MHz." access="RO" offset="0x3C.0" size="0x0.16" />
	<field name="laser_frequency_error_lane6" descr="Laser frequency error for media lane &lt;i&gt;, observes the difference between the target center frequency and the actual current center frequency.\;The laser frequency error is in unit scale of 10 MHz." access="RO" offset="0x3C.16" size="0x0.16" />
	<field name="cooled_laser_temperature_lane1" descr="The laser TEC temperature for media lane &lt;i&gt;, observes the difference between the target laser temperature for laser temperature.\;The laser temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x40.0" size="0x0.16" />
	<field name="cooled_laser_temperature_lane0" descr="The laser TEC temperature for media lane &lt;i&gt;, observes the difference between the target laser temperature for laser temperature.\;The laser temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x40.16" size="0x0.16" />
	<field name="cooled_laser_temperature_lane3" descr="The laser TEC temperature for media lane &lt;i&gt;, observes the difference between the target laser temperature for laser temperature.\;The laser temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x44.0" size="0x0.16" />
	<field name="cooled_laser_temperature_lane2" descr="The laser TEC temperature for media lane &lt;i&gt;, observes the difference between the target laser temperature for laser temperature.\;The laser temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x44.16" size="0x0.16" />
	<field name="cooled_laser_temperature_lane5" descr="The laser TEC temperature for media lane &lt;i&gt;, observes the difference between the target laser temperature for laser temperature.\;The laser temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x48.0" size="0x0.16" />
	<field name="cooled_laser_temperature_lane4" descr="The laser TEC temperature for media lane &lt;i&gt;, observes the difference between the target laser temperature for laser temperature.\;The laser temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x48.16" size="0x0.16" />
	<field name="cooled_laser_temperature_lane7" descr="The laser TEC temperature for media lane &lt;i&gt;, observes the difference between the target laser temperature for laser temperature.\;The laser temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x4C.0" size="0x0.16" />
	<field name="cooled_laser_temperature_lane6" descr="The laser TEC temperature for media lane &lt;i&gt;, observes the difference between the target laser temperature for laser temperature.\;The laser temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x4C.16" size="0x0.16" />
	<field name="optical_channel1_temperature" descr="The OE channels temperature for media lane &lt;i&gt;. channels temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x50.0" size="0x0.16" />
	<field name="optical_channel0_temperature" descr="The OE channels temperature for media lane &lt;i&gt;. channels temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x50.16" size="0x0.16" />
	<field name="optical_channel3_temperature" descr="The OE channels temperature for media lane &lt;i&gt;. channels temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x54.0" size="0x0.16" />
	<field name="optical_channel2_temperature" descr="The OE channels temperature for media lane &lt;i&gt;. channels temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x54.16" size="0x0.16" />
	<field name="optical_channel5_temperature" descr="The OE channels temperature for media lane &lt;i&gt;. channels temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x58.0" size="0x0.16" />
	<field name="optical_channel4_temperature" descr="The OE channels temperature for media lane &lt;i&gt;. channels temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x58.16" size="0x0.16" />
	<field name="optical_channel7_temperature" descr="The OE channels temperature for media lane &lt;i&gt;. channels temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x5C.0" size="0x0.16" />
	<field name="optical_channel6_temperature" descr="The OE channels temperature for media lane &lt;i&gt;. channels temperature value is in unit scale of 1/256 Celsius degrees." access="RO" offset="0x5C.16" size="0x0.16" />
</node>

<node name="pemi_Module_Status_Properties_ext" descr="" size="0xf8.0" >
	<field name="laser_source_module_temperature" descr="Laser source module temperatuire" access="RO" offset="0x0.25" size="0x0.1" />
	<field name="module_max_tec_power_cap" descr="Max TEC power capability" access="RO" offset="0x0.26" size="0x0.1" />
	<field name="module_temperature_cap" descr="Temperature capability" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="module_tx_bias_cap" descr="Tx bias capability\;" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="module_tx_power_cap" descr="Tx power capability\;" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="module_rx_power_cap" descr="Rx power capability" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="module_voltage_cap" descr="Voltage capability" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="voltage_low_alarm" descr="Thresholds for internal supply voltage monitor: 100   V increments" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="voltage_high_alarm" descr="Thresholds for internal supply voltage monitor: 100   V increments" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="voltage_low_warning" descr="Thresholds for internal supply voltage monitor: 100   V increments" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="voltage_high_warning" descr="Thresholds for internal supply voltage monitor: 100   V increments" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="rx_power_low_alarm" descr="Thresholds for Rx optical power monitor: \;0.1 uW increments Total measurement range of 0 to 6.5535 mW (~-40 dBm to +8.2 dBm for non-zero values)\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="rx_power_high_alarm" descr="Thresholds for Rx optical power monitor: \;0.1 uW increments Total measurement range of 0 to 6.5535 mW (~-40 dBm to +8.2 dBm for non-zero values)\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="rx_power_low_warning" descr="Thresholds for Rx optical power monitor: \;0.1 uW increments Total measurement range of 0 to 6.5535 mW (~-40 dBm to +8.2 dBm for non-zero values)\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="rx_power_high_warning" descr="Thresholds for Rx optical power monitor: \;0.1 uW increments Total measurement range of 0 to 6.5535 mW (~-40 dBm to +8.2 dBm for non-zero values)\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="tx_power_low_alarm" descr="Thresholds for Tx optical power monitor: \;in 0.1 uW increments Total measurement range of 0 to 6.5535 mW (or ~-40 dBm to +8.2 dBm for non-zero values)" access="RO" offset="0x14.0" size="0x0.16" />
	<field name="tx_power_high_alarm" descr="Thresholds for Tx optical power monitor: \;in 0.1 uW increments Total measurement range of 0 to 6.5535 mW (or ~-40 dBm to +8.2 dBm for non-zero values)" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="tx_power_low_warning" descr="Thresholds for Tx optical power monitor: \;in 0.1 uW increments Total measurement range of 0 to 6.5535 mW (or ~-40 dBm to +8.2 dBm for non-zero values)" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="tx_power_high_warning" descr="Thresholds for Tx optical power monitor: \;in 0.1 uW increments Total measurement range of 0 to 6.5535 mW (or ~-40 dBm to +8.2 dBm for non-zero values)" access="RO" offset="0x18.16" size="0x0.16" />
	<field name="tx_bias_high_alarm" descr="Thresholds for Tx laser bias monitor: 2 uA increments" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="tx_bias_low_alarm" descr="Thresholds for Tx laser bias monitor: 2 uA increments" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="tx_bias_high_warning" descr="Thresholds for Tx laser bias monitor: 2 uA increments" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="tx_bias_low_warning" descr="Thresholds for Tx laser bias monitor: 2 uA increments" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="temperature_low_alarm" descr="Thresholds for temperature: 1/256 Celsius degrees\;" access="RO" offset="0x2C.0" size="0x0.16" />
	<field name="temperature_high_alarm" descr="Thresholds for temperature: 1/256 Celsius degrees\;" access="RO" offset="0x2C.16" size="0x0.16" />
	<field name="temperature_low_warning" descr="Thresholds for temperature: 1/256 Celsius degrees\;" access="RO" offset="0x30.0" size="0x0.16" />
	<field name="temperature_high_warning" descr="Thresholds for temperature: 1/256 Celsius degrees\;" access="RO" offset="0x30.16" size="0x0.16" />
	<field name="max_tec_power_low_alarm" descr="Thresholds for max TEC power: 1 mW" access="RO" offset="0x34.0" size="0x0.16" />
	<field name="max_tec_power_high_alarm" descr="Thresholds for max TEC power: 1 mW" access="RO" offset="0x34.16" size="0x0.16" />
	<field name="max_tec_power_low_warning" descr="Thresholds for max TEC power: 1 mW" access="RO" offset="0x38.0" size="0x0.16" />
	<field name="max_tec_power_high_warning" descr="Thresholds for max TEC power: 1 mW" access="RO" offset="0x38.16" size="0x0.16" />
</node>

<node name="pemi_Pre_FEC_BER_Properties_ext" descr="" size="0xf8.0" >
	<field name="pre_fec_ber_cap" descr="Pre-FEC Bit Error Ratio represents the total number of bits that were corrected by the FEC during an interval divided by the total number of bits received in that interval.\;\;group capability mask:\;Bit 0: pre_fec_ber_min_media\;Bit 1: pre_fec_ber_min_host\;Bit 2: pre_fec_ber_max_media\;Bit 3: pre_fec_ber_max_host\;bit 4: pre_fec_ber_avg_media\;bit 5: pre_fec_ber_avg_host\;bit 6: pre_fec_ber_val_media\;bit 7: pre_fec_ber_val_host" access="RO" enum="pre_fec_ber_min_media=0x1,pre_fec_ber_min_host=0x2,pre_fec_ber_max_media=0x4,pre_fec_ber_max_host=0x8,pre_fec_ber_avg_media=0x10,pre_fec_ber_avg_host=0x20,pre_fec_ber_val_media=0x40,pre_fec_ber_val_host=0x80" offset="0x0.16" size="0x0.16" />
	<field name="pre_fec_ber_min_high_media_warning" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="pre_fec_ber_min_high_media_alarm" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="pre_fec_ber_min_high_host_warning" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="pre_fec_ber_min_high_host_alarm" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="pre_fec_ber_max_high_media_warning" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="pre_fec_ber_max_high_media_alarm" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0xC.16" size="0x0.16" />
	<field name="pre_fec_ber_max_high_host_warning" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="pre_fec_ber_max_high_host_alarm" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0x10.16" size="0x0.16" />
	<field name="pre_fec_ber_avg_high_media_warning" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="pre_fec_ber_avg_high_media_alarm" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="pre_fec_ber_avg_high_host_warning" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0x18.0" size="0x0.16" />
	<field name="pre_fec_ber_avg_high_host_alarm" descr="Thresholds for the pre-FEC BER values." access="RO" offset="0x18.16" size="0x0.16" />
</node>

<node name="pemi_Pre_FEC_BER_Samples_ext" descr="" size="0xf8.0" >
	<field name="pre_fec_ber_min_host" descr="The minimum statistical value of the Pre-FEC BER in the host input." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="pre_fec_ber_min_media" descr="The minimum statistical value of the Pre-FEC BER in the media input." access="RO" offset="0x0.16" size="0x0.16" />
	<field name="pre_fec_ber_max_host" descr="The maximum statistical value of the Pre-FEC BER in the host input." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="pre_fec_ber_max_media" descr="The maximum statistical value of the Pre-FEC BER in the media input." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="pre_fec_ber_avg_host" descr="The average statistical value of the Pre-FEC BER in the host input." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="pre_fec_ber_avg_media" descr="The average statistical value of the Pre-FEC BER in the media input." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="pre_fec_ber_val_host" descr="The sampled value of the Pre-FEC BER in the host input." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="pre_fec_ber_val_media" descr="The sampled value of the Pre-FEC BER in the media input." access="RO" offset="0xC.16" size="0x0.16" />
</node>

<node name="pemi_SNR_Properties_ext" descr="" size="0xf8.0" >
	<field name="snr_cap" descr="The SNR, represents the electrical signal-to-noise ratio on an optical lane, and it&apos;s defined as the minimum of the three individual eye SNR values.\;\;SNR group capability mask:\;Bit 0: snr_media\;Bit 1: snr_host" access="RO" enum="snr_media=0x1,snr_host=0x2" offset="0x0.16" size="0x0.16" />
	<field name="snr_media_low_warning" descr="Thresholds for the SNR value on the media lanes. \;In unit scale of 1/256 dB." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="snr_media_low_alarm" descr="Thresholds for the SNR value on the media lanes. \;In unit scale of 1/256 dB." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="snr_host_low_warning" descr="Thresholds for the SNR value on the media lanes. \;In unit scale of 1/256 dB." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="snr_host_low_alarm" descr="Thresholds for the SNR value on the media lanes. \;In unit scale of 1/256 dB." access="RO" offset="0x8.16" size="0x0.16" />
</node>

<node name="pemi_SNR_Samples_ext" descr="" size="0xf8.0" >
	<field name="snr_media_lane1" descr="SNR value on the media lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="snr_media_lane0" descr="SNR value on the media lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x0.16" size="0x0.16" />
	<field name="snr_media_lane3" descr="SNR value on the media lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="snr_media_lane2" descr="SNR value on the media lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="snr_media_lane5" descr="SNR value on the media lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="snr_media_lane4" descr="SNR value on the media lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="snr_media_lane7" descr="SNR value on the media lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="snr_media_lane6" descr="SNR value on the media lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0xC.16" size="0x0.16" />
	<field name="snr_host_lane1" descr="SNR value on the host lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="snr_host_lane0" descr="SNR value on the host lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x10.16" size="0x0.16" />
	<field name="snr_host_lane3" descr="SNR value on the host lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="snr_host_lane2" descr="SNR value on the host lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="snr_host_lane5" descr="SNR value on the host lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x18.0" size="0x0.16" />
	<field name="snr_host_lane4" descr="SNR value on the host lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x18.16" size="0x0.16" />
	<field name="snr_host_lane7" descr="SNR value on the host lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="snr_host_lane6" descr="SNR value on the host lane &lt;i&gt;. In unit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="RO" offset="0x1C.16" size="0x0.16" />
</node>

<node name="pemi_ext" descr="" size="0x100.0" >
	<field name="status" descr="The status of the page reading:\;0: READ_SUCCESSFUL - read operation was successful\;1: OPERATION_NOT_SUPPORTED\;2: NO_EEPROM_MODULE - no response from module&apos;s \;EEPROM.\;3: MODULE_NOT_CONNECTED - no module present indication.\;4: I2C_ERROR - an Error occurred while trying to access the module&apos;s EEPROM using I2C.\;5: MODULE_IN_PROGRESS - indicates that the module is still busy.\;6: CDB_STSATUS_FAILED - the CDB return status is FAILED." access="RO" enum="READ_SUCCESSFUL=0x0,OPERATION_NOT_SUPPORTED=0x1,NO_EEPROM_MODULE=0x2,MODULE_NOT_CONNECTED=0x3,I2C_ERROR=0x4,MODULE_IN_PROGRESS=0x5,CDB_STSATUS_FAILED=0x6" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="Local port number [9:8]\;\;For Retimer: reserved" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is \;interpreted:\;0: Local_port_number\;1: IB_port_number\;3: Out_of_band_or_PCI\;\;For Retimer: reserved" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;For Retimer: Data path number\;If module_index_cap is set, fields represent module index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="module_ind_type" descr="Module index type selector, for IB CPO switches only:\;0: CPO_or_pluggable_modules\;1: OE\;2: ELS" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="module_index_cap" descr="Indicates if local_port fields represent a local port of module index.\;0: local_port\;1: module_index" access="INDEX" enum="local_port=0x0,module_index=0x1" offset="0x0.26" size="0x0.1" />
	<field name="page_select" descr="The user can select to read a sampled data page or a properties page.\;\;0: Module_Status_Samples\;1: SNR_Samples\;2: Laser_Monitors_Samples\;4: Pre_FEC_BER_Samples\;7: Laser_Source_Module_Essential_Samples\;8: Laser_Source_Module_Advanced_Samples\;9: Optical_Engine_Debug_Parameters_Samples\;10: Laser_Source_Module_Status_Samples\;16: Module_Status_Properties\;17: SNR_Properties\;18: Laser_Monitors_Properties\;20: Pre_FEC_BER_Properties\;23: Laser_Source_Module_Essential_Properties\;24: Laser_Source_Module_Advanced_Properties\;25: Optical_Engine_Debug_Parameters_Properties\;26: Laser_Source_Module_Status_Properties\;All other values are reserved." access="INDEX" enum="Module_Status_Samples=0x0,SNR_Samples=0x1,Laser_Monitors_Samples=0x2,Pre_FEC_BER_Samples=0x4,Laser_Source_Module_Essential_Samples=0x7,Laser_Source_Module_Advanced_Samples=0x8,Optical_Engine_Debug_Parameters_Samples=0x9,Laser_Source_Module_Status_Samples=0xa,Module_Status_Properties=0x10,SNR_Properties=0x11,Laser_Monitors_Properties=0x12,Pre_FEC_BER_Properties=0x14,Laser_Source_Module_Essential_Properties=0x17,Laser_Source_Module_Advanced_Properties=0x18,Optical_Engine_Debug_Parameters_Properties=0x19,Laser_Source_Module_Status_Properties=0x1a" offset="0x4.0" size="0x0.5" />
	<field name="group_cap_mask" descr="Group capability mask:\;Bit 0: Module_Status\;Bit 1: SNR\;Bit 2: Laser_Monitors\;Bit 4: Pre_FEC_BER" access="RO" enum="Module_Status=0x1,SNR=0x2,Laser_Monitors=0x4,Pre_FEC_BER=0x10" offset="0x4.16" size="0x0.16" />
	<field name="page_data" descr="Page data:\;Table  2434, &quot;Module Status Samples Page- Layout,&quot; on page  2858\;Table  2436, &quot;SNR Samples page - Layout,&quot; on page  2861\;Table  2438, &quot;Laser Monitors Samples page - Layout,&quot; on page  2862\;Table  2442, &quot;Pre-FEC BER Samples Page - Layout,&quot; on page  2867\;Table  2448, &quot;Laser Source Module Essential Samples Page - Layout,&quot; on page  2870\;Table 2450, &quot;Laser Source Module Advanced Samples Page - Layout,&quot; on page 2873\;Table 2452, &quot;Optical Engine Debug Parameters Samples Page - Layout,&quot; on page 2875\;Table 2474, &quot;Laser Source Module Status Samples page - Layout,&quot; on page 2892\;Table  2454, &quot;Module Status Properties Page - Layout,&quot; on page  2880\;Table  2456, &quot;SNR Properties Page - Layout,&quot; on page  2882\;Table  2458, &quot;Laser Monitors Properties Page - Layout,&quot; on page  2883\;Table  2462, &quot;Pre-FEC BER Properties Page - Layout,&quot; on page  2886\;Table  2468, &quot;Laser Source Module Essential Properties page - Layout,&quot; on page  2889\;Table 2470, &quot;Laser Source Module Advanced Properties page - Layout,&quot; on page 2891\;Table 2472, &quot;Optical Engine Debug Parameters Properties page - Layout,&quot; on page 2892\;Table 2476, &quot;Laser Source Module Status Properties page - Layout,&quot; on page 2894" subnode="pemi_page_data_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).page_select" />
</node>

<node name="pemi_laser_source_module_advance_properties_ext" descr="" size="0xf8.0" >
	<field name="module_power_consumption_cap" descr="Module power consumption capability" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="tec_health_cap" descr="TEC health capability" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="laser_health_cap" descr="Laser health capability" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="tec_voltage_cap" descr="TEC voltage capability" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="laser_mpd_cap" descr="Laser MPD capability" access="RO" offset="0x0.31" size="0x0.1" />
</node>

<node name="pemi_laser_source_module_advanced_samples_ext" descr="" size="0xf8.0" >
	<field name="laser_mpd_lane1" descr="Laser MPD for lane &lt;i&gt;, in unit of 1   A.\;" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="laser_mpd_lane0" descr="Laser MPD for lane &lt;i&gt;, in unit of 1   A.\;" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="laser_mpd_lane3" descr="Laser MPD for lane &lt;i&gt;, in unit of 1   A.\;" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="laser_mpd_lane2" descr="Laser MPD for lane &lt;i&gt;, in unit of 1   A.\;" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="laser_mpd_lane5" descr="Laser MPD for lane &lt;i&gt;, in unit of 1   A.\;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="laser_mpd_lane4" descr="Laser MPD for lane &lt;i&gt;, in unit of 1   A.\;" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="laser_mpd_lane7" descr="Laser MPD for lane &lt;i&gt;, in unit of 1   A.\;" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="laser_mpd_lane6" descr="Laser MPD for lane &lt;i&gt;, in unit of 1   A.\;" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="tec_voltage_laser1" descr="TEC voltage for TEC that mapped to laser &lt;i&gt; , in unit of 1 mV.\;" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="tec_voltage_laser0" descr="TEC voltage for TEC that mapped to laser &lt;i&gt; , in unit of 1 mV.\;" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="tec_voltage_laser3" descr="TEC voltage for TEC that mapped to laser &lt;i&gt; , in unit of 1 mV.\;" access="RO" offset="0x14.0" size="0x0.16" />
	<field name="tec_voltage_laser2" descr="TEC voltage for TEC that mapped to laser &lt;i&gt; , in unit of 1 mV.\;" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="tec_voltage_laser5" descr="TEC voltage for TEC that mapped to laser &lt;i&gt; , in unit of 1 mV.\;" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="tec_voltage_laser4" descr="TEC voltage for TEC that mapped to laser &lt;i&gt; , in unit of 1 mV.\;" access="RO" offset="0x18.16" size="0x0.16" />
	<field name="tec_voltage_laser7" descr="TEC voltage for TEC that mapped to laser &lt;i&gt; , in unit of 1 mV.\;" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="tec_voltage_laser6" descr="TEC voltage for TEC that mapped to laser &lt;i&gt; , in unit of 1 mV.\;" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="health_value_tec3" descr="TEC health for TEC that mapped to laser&lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x20.0" size="0x0.8" />
	<field name="health_value_tec2" descr="TEC health for TEC that mapped to laser&lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x20.8" size="0x0.8" />
	<field name="health_value_tec1" descr="TEC health for TEC that mapped to laser&lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x20.16" size="0x0.8" />
	<field name="health_value_tec0" descr="TEC health for TEC that mapped to laser&lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x20.24" size="0x0.8" />
	<field name="health_value_tec7" descr="TEC health for TEC that mapped to laser&lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x24.0" size="0x0.8" />
	<field name="health_value_tec6" descr="TEC health for TEC that mapped to laser&lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x24.8" size="0x0.8" />
	<field name="health_value_tec5" descr="TEC health for TEC that mapped to laser&lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x24.16" size="0x0.8" />
	<field name="health_value_tec4" descr="TEC health for TEC that mapped to laser&lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x24.24" size="0x0.8" />
	<field name="health_value_laser3" descr="Laser health for lane &lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x28.0" size="0x0.8" />
	<field name="health_value_laser2" descr="Laser health for lane &lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x28.8" size="0x0.8" />
	<field name="health_value_laser1" descr="Laser health for lane &lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x28.16" size="0x0.8" />
	<field name="health_value_laser0" descr="Laser health for lane &lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x28.24" size="0x0.8" />
	<field name="health_value_laser7" descr="Laser health for lane &lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x2C.0" size="0x0.8" />
	<field name="health_value_laser6" descr="Laser health for lane &lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x2C.8" size="0x0.8" />
	<field name="health_value_laser5" descr="Laser health for lane &lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x2C.16" size="0x0.8" />
	<field name="health_value_laser4" descr="Laser health for lane &lt;i&gt;, in unit of 5mV.\;" access="RO" offset="0x2C.24" size="0x0.8" />
	<field name="power_consumption" descr="Laser souyrce module power consumption in unit of 0.1W" access="RO" offset="0x30.16" size="0x0.16" />
</node>

<node name="pemi_laser_source_module_essential_properties_ext" descr="" size="0xf8.0" >
	<field name="opt_power_setpoint_cap" descr="Optical power setpoint capability" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="icc_monitor_cap" descr="ICC monitor capability" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="laser_voltage_monitor_cap" descr="Laser voltage monitor capability" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="laser_optical_power_Cap" descr="Laser optical power monitor capability" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="laser_bias_cap" descr="Laser bias monitor capability\;" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="laser_bias_low_alarm" descr="Laser bias threshold in 100  A increaments" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="laser_bias_high_alarm" descr="Laser bias threshold in 100  A increaments" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="laser_bias_low_warning" descr="Laser bias threshold in 100  A increaments" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="laser_bias_high_warning" descr="Laser bias threshold in 100  A increaments" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="laser_optical_power_low_alarm" descr="Laser optical power threshold in 10  W increaments" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="laser_optical_power_high_alarm" descr="Laser optical power threshold in 10  W increaments" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="laser_optical_power_low_warning" descr="Laser optical power threshold in 10  W increaments" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="laser_optical_power_high_warning" descr="Laser optical power threshold in 10  W increaments" access="RO" offset="0x10.16" size="0x0.16" />
</node>

<node name="pemi_laser_source_module_essential_samples_ext" descr="" size="0xf8.0" >
	<field name="voltage_monitor3" descr="Laser voltage for laser &lt;i&gt;, in unit of 15 mV.\;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="voltage_monitor2" descr="Laser voltage for laser &lt;i&gt;, in unit of 15 mV.\;" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="voltage_monitor1" descr="Laser voltage for laser &lt;i&gt;, in unit of 15 mV.\;" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="voltage_monitor0" descr="Laser voltage for laser &lt;i&gt;, in unit of 15 mV.\;" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="voltage_monitor7" descr="Laser voltage for laser &lt;i&gt;, in unit of 15 mV.\;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="voltage_monitor6" descr="Laser voltage for laser &lt;i&gt;, in unit of 15 mV.\;" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="voltage_monitor5" descr="Laser voltage for laser &lt;i&gt;, in unit of 15 mV.\;" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="voltage_monitor4" descr="Laser voltage for laser &lt;i&gt;, in unit of 15 mV.\;" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="bias_current_monitor1" descr="Laser bias for laser &lt;i&gt;, in unit of 100 mA." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="bias_current_monitor0" descr="Laser bias for laser &lt;i&gt;, in unit of 100 mA." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="bias_current_monitor3" descr="Laser bias for laser &lt;i&gt;, in unit of 100 mA." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="bias_current_monitor2" descr="Laser bias for laser &lt;i&gt;, in unit of 100 mA." access="RO" offset="0xC.16" size="0x0.16" />
	<field name="bias_current_monitor5" descr="Laser bias for laser &lt;i&gt;, in unit of 100 mA." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="bias_current_monitor4" descr="Laser bias for laser &lt;i&gt;, in unit of 100 mA." access="RO" offset="0x10.16" size="0x0.16" />
	<field name="bias_current_monitor7" descr="Laser bias for laser &lt;i&gt;, in unit of 100 mA." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="bias_current_monitor6" descr="Laser bias for laser &lt;i&gt;, in unit of 100 mA." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="opt_power_monitor1" descr="Laser optical power for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="opt_power_monitor0" descr="Laser optical power for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x18.16" size="0x0.16" />
	<field name="opt_power_monitor3" descr="Laser optical power for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="opt_power_monitor2" descr="Laser optical power for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="opt_power_monitor5" descr="Laser optical power for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x20.0" size="0x0.16" />
	<field name="opt_power_monitor4" descr="Laser optical power for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x20.16" size="0x0.16" />
	<field name="opt_power_monitor7" descr="Laser optical power for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x24.0" size="0x0.16" />
	<field name="opt_power_monitor6" descr="Laser optical power for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x24.16" size="0x0.16" />
	<field name="icc_monitor" descr="VCC bias, in unit of 200   A." access="RW" offset="0x28.16" size="0x0.16" />
	<field name="opt_power_setpoint1" descr="Laser optical setpoint for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x2C.0" size="0x0.16" />
	<field name="opt_power_setpoint0" descr="Laser optical setpoint for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x2C.16" size="0x0.16" />
	<field name="opt_power_setpoint3" descr="Laser optical setpoint for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x30.0" size="0x0.16" />
	<field name="opt_power_setpoint2" descr="Laser optical setpoint for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x30.16" size="0x0.16" />
	<field name="opt_power_setpoint5" descr="Laser optical setpoint for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x34.0" size="0x0.16" />
	<field name="opt_power_setpoint4" descr="Laser optical setpoint for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x34.16" size="0x0.16" />
	<field name="opt_power_setpoint7" descr="Laser optical setpoint for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x38.0" size="0x0.16" />
	<field name="opt_power_setpoint6" descr="Laser optical setpoint for laser &lt;i&gt;, in unit of 10   W.\;" access="RO" offset="0x38.16" size="0x0.16" />
</node>

<node name="pemi_laser_source_module_status_properties_ext" descr="" size="0xf8.0" >
	<field name="els_laser_state_fault_cap" descr="Laser fault state capability" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="laser_status_cap" descr="Laser status capability" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="laser_restriction_cap" descr="Laser restriction capability" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="laser_enabled_cap" descr="Laser enabled capability" access="RO" offset="0x0.31" size="0x0.1" />
</node>

<node name="pemi_laser_source_module_status_samples_ext" descr="" size="0xf8.0" >
	<field name="laser_status" descr="Relevant for CPO product. Each 2 bit represent the ELS&apos;s laser status:\;0: laser_off\;1: laser_ramping\;2: laser_on" access="RO" enum="laser_on=0x2" offset="0x0.0" size="0x0.16" />
	<field name="laser_restriction" descr="Relevant for CPO product. Each bit represent the ELS&apos;s laser restriction. When restriction are on, the laser can operate only in restricted power mode, for the safety of the optical components. Restriction can be lifted only after fiber testing.\;0: laser_restriction_on\;1: laser_restriction_off" access="RO" enum="laser_restriction_on=0x0,laser_restriction_off=0x1" offset="0x0.16" size="0x0.8" />
	<field name="laser_enabled" descr="Relevant for CPO product. Each bit represent the ELS&apos;s laser. \;0: laser_disabled\;1: laser_enabled" access="RO" enum="laser_disabled=0x0,laser_enabled=0x1" offset="0x0.24" size="0x0.8" />
	<field name="els_laser7_state_fault" descr="indicate the ELS laser fault.\;0: no_fault\;1: laser_fiber_contaminated\;2: laser_APC_fault\;3: laser_power_exceeded_allowed_range\;4: laser_power_subceeded_allowed_range\;5: laser_TEC_control_loop_fault\;6: laser_ramping_timeout_fault\;7: laser_power_tuning_fault" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="els_laser6_state_fault" descr="indicate the ELS laser fault.\;0: no_fault\;1: laser_fiber_contaminated\;2: laser_APC_fault\;3: laser_power_exceeded_allowed_range\;4: laser_power_subceeded_allowed_range\;5: laser_TEC_control_loop_fault\;6: laser_ramping_timeout_fault\;7: laser_power_tuning_fault" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="els_laser5_state_fault" descr="indicate the ELS laser fault.\;0: no_fault\;1: laser_fiber_contaminated\;2: laser_APC_fault\;3: laser_power_exceeded_allowed_range\;4: laser_power_subceeded_allowed_range\;5: laser_TEC_control_loop_fault\;6: laser_ramping_timeout_fault\;7: laser_power_tuning_fault" access="RO" offset="0x4.8" size="0x0.4" />
	<field name="els_laser4_state_fault" descr="indicate the ELS laser fault.\;0: no_fault\;1: laser_fiber_contaminated\;2: laser_APC_fault\;3: laser_power_exceeded_allowed_range\;4: laser_power_subceeded_allowed_range\;5: laser_TEC_control_loop_fault\;6: laser_ramping_timeout_fault\;7: laser_power_tuning_fault" access="RO" offset="0x4.12" size="0x0.4" />
	<field name="els_laser3_state_fault" descr="indicate the ELS laser fault.\;0: no_fault\;1: laser_fiber_contaminated\;2: laser_APC_fault\;3: laser_power_exceeded_allowed_range\;4: laser_power_subceeded_allowed_range\;5: laser_TEC_control_loop_fault\;6: laser_ramping_timeout_fault\;7: laser_power_tuning_fault" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="els_laser2_state_fault" descr="indicate the ELS laser fault.\;0: no_fault\;1: laser_fiber_contaminated\;2: laser_APC_fault\;3: laser_power_exceeded_allowed_range\;4: laser_power_subceeded_allowed_range\;5: laser_TEC_control_loop_fault\;6: laser_ramping_timeout_fault\;7: laser_power_tuning_fault" access="RO" offset="0x4.20" size="0x0.4" />
	<field name="els_laser1_state_fault" descr="indicate the ELS laser fault.\;0: no_fault\;1: laser_fiber_contaminated\;2: laser_APC_fault\;3: laser_power_exceeded_allowed_range\;4: laser_power_subceeded_allowed_range\;5: laser_TEC_control_loop_fault\;6: laser_ramping_timeout_fault\;7: laser_power_tuning_fault" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="els_laser0_state_fault" descr="indicate the ELS laser fault.\;0: no_fault\;1: laser_fiber_contaminated\;2: laser_APC_fault\;3: laser_power_exceeded_allowed_range\;4: laser_power_subceeded_allowed_range\;5: laser_TEC_control_loop_fault\;6: laser_ramping_timeout_fault\;7: laser_power_tuning_fault" access="RO" enum="no_fault=0x0,laser_fiber_contaminated=0x1,laser_APC_fault=0x2,laser_power_exceeded_allowed_range=0x3,laser_power_subceeded_allowed_range=0x4,laser_TEC_control_loop_fault=0x5,laser_ramping_timeout_fault=0x6,laser_power_tuning_fault=0x7" offset="0x4.28" size="0x0.4" />
</node>

<node name="pemi_module_status_samples_ext" descr="" size="0xf8.0" >
	<field name="voltage" descr="Internally measured supply voltage in 100uV" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="temperature" descr="module temperature in unit of 1/256 C" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="rx_power_lane1" descr="RX measured power on lane &lt;i&gt;.\; measured in dBm or uW according to module_info_ext value" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="rx_power_lane0" descr="RX measured power on lane &lt;i&gt;.\; measured in dBm or uW according to module_info_ext value" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="rx_power_lane3" descr="RX measured power on lane &lt;i&gt;.\; measured in dBm or uW according to module_info_ext value" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="rx_power_lane2" descr="RX measured power on lane &lt;i&gt;.\; measured in dBm or uW according to module_info_ext value" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="rx_power_lane5" descr="RX measured power on lane &lt;i&gt;.\; measured in dBm or uW according to module_info_ext value" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="rx_power_lane4" descr="RX measured power on lane &lt;i&gt;.\; measured in dBm or uW according to module_info_ext value" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="rx_power_lane7" descr="RX measured power on lane &lt;i&gt;.\; measured in dBm or uW according to module_info_ext value" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="rx_power_lane6" descr="RX measured power on lane &lt;i&gt;.\; measured in dBm or uW according to module_info_ext value" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="tx_power_lane1" descr="TX measured power on lane &lt;i&gt;\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0x14.0" size="0x0.16" />
	<field name="tx_power_lane0" descr="TX measured power on lane &lt;i&gt;\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="tx_power_lane3" descr="TX measured power on lane &lt;i&gt;\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="tx_power_lane2" descr="TX measured power on lane &lt;i&gt;\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0x18.16" size="0x0.16" />
	<field name="tx_power_lane5" descr="TX measured power on lane &lt;i&gt;\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="tx_power_lane4" descr="TX measured power on lane &lt;i&gt;\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="tx_power_lane7" descr="TX measured power on lane &lt;i&gt;\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0x20.0" size="0x0.16" />
	<field name="tx_power_lane6" descr="TX measured power on lane &lt;i&gt;\;measured in dBm or uW according to module_info_ext value" access="RO" offset="0x20.16" size="0x0.16" />
	<field name="tx_bias_lane0" descr="TX measured bias current on lane &lt;i&gt; in 2uA" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="tx_bias_lane1" descr="TX measured bias current on lane &lt;i&gt; in 2uA" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="tx_bias_lane2" descr="TX measured bias current on lane &lt;i&gt; in 2uA" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="tx_bias_lane3" descr="TX measured bias current on lane &lt;i&gt; in 2uA" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="tx_bias_lane4" descr="TX measured bias current on lane &lt;i&gt; in 2uA" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="tx_bias_lane5" descr="TX measured bias current on lane &lt;i&gt; in 2uA" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="tx_bias_lane6" descr="TX measured bias current on lane &lt;i&gt; in 2uA" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="tx_bias_lane7" descr="TX measured bias current on lane &lt;i&gt; in 2uA" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="dp_st_lane6" descr="DataPath state for lane &lt;i&gt;\;1: DPDeactivated \;2: DPInit \;3: DPDeinit \;4: DPActivated \;5: DPTxTurnOn \;6: DPTxTurnOff \;7: DPInitialized" access="RO" offset="0x44.1" size="0x0.4" />
	<field name="dp_st_lane5" descr="DataPath state for lane &lt;i&gt;\;1: DPDeactivated \;2: DPInit \;3: DPDeinit \;4: DPActivated \;5: DPTxTurnOn \;6: DPTxTurnOff \;7: DPInitialized" access="RO" offset="0x44.5" size="0x0.4" />
	<field name="dp_st_lane4" descr="DataPath state for lane &lt;i&gt;\;1: DPDeactivated \;2: DPInit \;3: DPDeinit \;4: DPActivated \;5: DPTxTurnOn \;6: DPTxTurnOff \;7: DPInitialized" access="RO" offset="0x44.9" size="0x0.4" />
	<field name="dp_st_lane3" descr="DataPath state for lane &lt;i&gt;\;1: DPDeactivated \;2: DPInit \;3: DPDeinit \;4: DPActivated \;5: DPTxTurnOn \;6: DPTxTurnOff \;7: DPInitialized" access="RO" offset="0x44.13" size="0x0.4" />
	<field name="dp_st_lane2" descr="DataPath state for lane &lt;i&gt;\;1: DPDeactivated \;2: DPInit \;3: DPDeinit \;4: DPActivated \;5: DPTxTurnOn \;6: DPTxTurnOff \;7: DPInitialized" access="RO" offset="0x44.17" size="0x0.4" />
	<field name="dp_st_lane1" descr="DataPath state for lane &lt;i&gt;\;1: DPDeactivated \;2: DPInit \;3: DPDeinit \;4: DPActivated \;5: DPTxTurnOn \;6: DPTxTurnOff \;7: DPInitialized" access="RO" offset="0x44.21" size="0x0.4" />
	<field name="dp_st_lane0" descr="DataPath state for lane &lt;i&gt;\;1: DPDeactivated \;2: DPInit \;3: DPDeinit \;4: DPActivated \;5: DPTxTurnOn \;6: DPTxTurnOff \;7: DPInitialized" access="RO" offset="0x44.25" size="0x0.4" />
	<field name="module_st" descr="Valid for CMIS modules only. Module state:\; 0: reserved \;1: LowPwr_state \;2: PwrUp_state \;3: Ready_state \;4: PwrDn_state \;5: Fault_state" access="RO" offset="0x44.29" size="0x0.3" />
	<field name="max_tec_power" descr="Maximum power measure between all TECs in unit of 1mW" access="RO" offset="0x48.0" size="0x0.16" />
	<field name="dp_st_lane7" descr="DataPath state for lane &lt;i&gt;\;1: DPDeactivated \;2: DPInit \;3: DPDeinit \;4: DPActivated \;5: DPTxTurnOn \;6: DPTxTurnOff \;7: DPInitialized" access="RO" offset="0x48.28" size="0x0.4" />
	<field name="laser_source_temperature" descr="ELS source module TS1 temperature unit of 1/256 C. Relevant for CPO ETH switches." access="RO" offset="0x4C.16" size="0x0.16" />
</node>

<node name="pemi_optical_engine_debug_parameters_samples_ext" descr="" size="0xf8.0" >
	<field name="heater_voltage_lane1" descr="Optical Engine heater voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x0.0" size="0x0.16" />
	<field name="heater_voltage_lane0" descr="Optical Engine heater voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x0.16" size="0x0.16" />
	<field name="heater_voltage_lane3" descr="Optical Engine heater voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x4.0" size="0x0.16" />
	<field name="heater_voltage_lane2" descr="Optical Engine heater voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x4.16" size="0x0.16" />
	<field name="heater_voltage_lane5" descr="Optical Engine heater voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x8.0" size="0x0.16" />
	<field name="heater_voltage_lane4" descr="Optical Engine heater voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x8.16" size="0x0.16" />
	<field name="heater_voltage_lane7" descr="Optical Engine heater voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0xC.0" size="0x0.16" />
	<field name="heater_voltage_lane6" descr="Optical Engine heater voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0xC.16" size="0x0.16" />
	<field name="photocurrent_lane1" descr="Optical Engine photo current for lane &lt;i&gt; in unit of TBD" offset="0x10.0" size="0x0.16" />
	<field name="photocurrent_lane0" descr="Optical Engine photo current for lane &lt;i&gt; in unit of TBD" offset="0x10.16" size="0x0.16" />
	<field name="photocurrent_lane3" descr="Optical Engine photo current for lane &lt;i&gt; in unit of TBD" offset="0x14.0" size="0x0.16" />
	<field name="photocurrent_lane2" descr="Optical Engine photo current for lane &lt;i&gt; in unit of TBD" offset="0x14.16" size="0x0.16" />
	<field name="photocurrent_lane5" descr="Optical Engine photo current for lane &lt;i&gt; in unit of TBD" offset="0x18.0" size="0x0.16" />
	<field name="photocurrent_lane4" descr="Optical Engine photo current for lane &lt;i&gt; in unit of TBD" offset="0x18.16" size="0x0.16" />
	<field name="photocurrent_lane7" descr="Optical Engine photo current for lane &lt;i&gt; in unit of TBD" offset="0x1C.0" size="0x0.16" />
	<field name="photocurrent_lane6" descr="Optical Engine photo current for lane &lt;i&gt; in unit of TBD" offset="0x1C.16" size="0x0.16" />
	<field name="tx_cm_cathode_voltage_lane1" descr="Optical Engine Tx cathode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x20.0" size="0x0.16" />
	<field name="tx_cm_cathode_voltage_lane0" descr="Optical Engine Tx cathode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x20.16" size="0x0.16" />
	<field name="tx_cm_cathode_voltage_lane3" descr="Optical Engine Tx cathode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x24.0" size="0x0.16" />
	<field name="tx_cm_cathode_voltage_lane2" descr="Optical Engine Tx cathode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x24.16" size="0x0.16" />
	<field name="tx_cm_cathode_voltage_lane5" descr="Optical Engine Tx cathode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x28.0" size="0x0.16" />
	<field name="tx_cm_cathode_voltage_lane4" descr="Optical Engine Tx cathode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x28.16" size="0x0.16" />
	<field name="tx_cm_cathode_voltage_lane7" descr="Optical Engine Tx cathode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x2C.0" size="0x0.16" />
	<field name="tx_cm_cathode_voltage_lane6" descr="Optical Engine Tx cathode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x2C.16" size="0x0.16" />
	<field name="tx_cm_anode_voltage_lane1" descr="Optical Engine Tx anode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x30.0" size="0x0.16" />
	<field name="tx_cm_anode_voltage_lane0" descr="Optical Engine Tx anode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x30.16" size="0x0.16" />
	<field name="tx_cm_anode_voltage_lane3" descr="Optical Engine Tx anode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x34.0" size="0x0.16" />
	<field name="tx_cm_anode_voltage_lane2" descr="Optical Engine Tx anode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x34.16" size="0x0.16" />
	<field name="tx_cm_anode_voltage_lane5" descr="Optical Engine Tx anode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x38.0" size="0x0.16" />
	<field name="tx_cm_anode_voltage_lane4" descr="Optical Engine Tx anode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x38.16" size="0x0.16" />
	<field name="tx_cm_anode_voltage_lane7" descr="Optical Engine Tx anode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x3C.0" size="0x0.16" />
	<field name="tx_cm_anode_voltage_lane6" descr="Optical Engine Tx anode common mode voltage for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x3C.16" size="0x0.16" />
	<field name="rx_voa_xpol_voltage_lane1" descr="Optical Engine Rx XPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x40.0" size="0x0.16" />
	<field name="rx_voa_xpol_voltage_lane0" descr="Optical Engine Rx XPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x40.16" size="0x0.16" />
	<field name="rx_voa_xpol_voltage_lane3" descr="Optical Engine Rx XPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x44.0" size="0x0.16" />
	<field name="rx_voa_xpol_voltage_lane2" descr="Optical Engine Rx XPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x44.16" size="0x0.16" />
	<field name="rx_voa_xpol_voltage_lane5" descr="Optical Engine Rx XPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x48.0" size="0x0.16" />
	<field name="rx_voa_xpol_voltage_lane4" descr="Optical Engine Rx XPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x48.16" size="0x0.16" />
	<field name="rx_voa_xpol_voltage_lane7" descr="Optical Engine Rx XPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x4C.0" size="0x0.16" />
	<field name="rx_voa_xpol_voltage_lane6" descr="Optical Engine Rx XPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x4C.16" size="0x0.16" />
	<field name="rx_voa_ypol_voltage_lane1" descr="Optical Engine Rx YPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x50.0" size="0x0.16" />
	<field name="rx_voa_ypol_voltage_lane0" descr="Optical Engine Rx YPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x50.16" size="0x0.16" />
	<field name="rx_voa_ypol_voltage_lane3" descr="Optical Engine Rx YPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x54.0" size="0x0.16" />
	<field name="rx_voa_ypol_voltage_lane2" descr="Optical Engine Rx YPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x54.16" size="0x0.16" />
	<field name="rx_voa_ypol_voltage_lane5" descr="Optical Engine Rx YPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x58.0" size="0x0.16" />
	<field name="rx_voa_ypol_voltage_lane4" descr="Optical Engine Rx YPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x58.16" size="0x0.16" />
	<field name="rx_voa_ypol_voltage_lane7" descr="Optical Engine Rx YPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x5C.0" size="0x0.16" />
	<field name="rx_voa_ypol_voltage_lane6" descr="Optical Engine Rx YPOL VOA for lane &lt;i&gt; in unit of 1500 / 4095 mV" offset="0x5C.16" size="0x0.16" />
</node>

<node name="pemi_optical_engine_telemetry_properties_ext" descr="" size="0xf8.0" >
	<field name="rx_voa_ypol_voltage_cap" descr="Optical engine Rx VOA ypol voltage capability" access="RO" offset="0x0.26" size="0x0.1" />
	<field name="rx_voa_xpol_voltage_cap" descr="Optical engine Rx VOA xpol voltage capability" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="tx_cm_anode_voltage_cap" descr="Optical engine Tx common mode anode voltage capability" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="tx_cm_cathode_voltage_cap" descr="Optical engine Tx common mode cathode voltage capability" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="photocurrent_cap" descr="Optical engine photocurrent capability" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="heater_voltage_cap" descr="Optical engine heater voltage monitor capability" access="RO" offset="0x0.31" size="0x0.1" />
</node>

<node name="pemi_page_data_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="pemi_Laser_Monitors_Properties_ext" descr="" subnode="pemi_Laser_Monitors_Properties_ext" offset="0x0.0" selected_by="Laser_Monitors_Properties" size="0xf8.0" />
	<field name="pemi_Laser_Monitors_Samples_ext" descr="" subnode="pemi_Laser_Monitors_Samples_ext" offset="0x0.0" selected_by="Laser_Monitors_Samples" size="0xf8.0" />
	<field name="pemi_Module_Status_Properties_ext" descr="" subnode="pemi_Module_Status_Properties_ext" offset="0x0.0" selected_by="Module_Status_Properties" size="0xf8.0" />
	<field name="pemi_Pre_FEC_BER_Properties_ext" descr="" subnode="pemi_Pre_FEC_BER_Properties_ext" offset="0x0.0" selected_by="Pre_FEC_BER_Properties" size="0xf8.0" />
	<field name="pemi_Pre_FEC_BER_Samples_ext" descr="" subnode="pemi_Pre_FEC_BER_Samples_ext" offset="0x0.0" selected_by="Pre_FEC_BER_Samples" size="0xf8.0" />
	<field name="pemi_SNR_Properties_ext" descr="" subnode="pemi_SNR_Properties_ext" offset="0x0.0" selected_by="SNR_Properties" size="0xf8.0" />
	<field name="pemi_SNR_Samples_ext" descr="" subnode="pemi_SNR_Samples_ext" offset="0x0.0" selected_by="SNR_Samples" size="0xf8.0" />
	<field name="pemi_laser_source_module_advance_properties_ext" descr="" subnode="pemi_laser_source_module_advance_properties_ext" offset="0x0.0" selected_by="Laser_Source_Module_Advanced_Properties" size="0xf8.0" />
	<field name="pemi_laser_source_module_advanced_samples_ext" descr="" subnode="pemi_laser_source_module_advanced_samples_ext" offset="0x0.0" selected_by="Laser_Source_Module_Advanced_Samples" size="0xf8.0" />
	<field name="pemi_laser_source_module_essential_properties_ext" descr="" subnode="pemi_laser_source_module_essential_properties_ext" offset="0x0.0" selected_by="Laser_Source_Module_Essential_Properties" size="0xf8.0" />
	<field name="pemi_laser_source_module_essential_samples_ext" descr="" subnode="pemi_laser_source_module_essential_samples_ext" offset="0x0.0" selected_by="Laser_Source_Module_Essential_Samples" size="0xf8.0" />
	<field name="pemi_laser_source_module_status_properties_ext" descr="" subnode="pemi_laser_source_module_status_properties_ext" offset="0x0.0" selected_by="Laser_Source_Module_Status_Properties" size="0xf8.0" />
	<field name="pemi_laser_source_module_status_samples_ext" descr="" subnode="pemi_laser_source_module_status_samples_ext" offset="0x0.0" selected_by="Laser_Source_Module_Status_Samples" size="0xf8.0" />
	<field name="pemi_module_status_samples_ext" descr="" subnode="pemi_module_status_samples_ext" offset="0x0.0" selected_by="Module_Status_Samples" size="0xf8.0" />
	<field name="pemi_optical_engine_debug_parameters_samples_ext" descr="" subnode="pemi_optical_engine_debug_parameters_samples_ext" offset="0x0.0" selected_by="Optical_Engine_Debug_Parameters_Samples" size="0xf8.0" />
	<field name="pemi_optical_engine_telemetry_properties_ext" descr="" subnode="pemi_optical_engine_telemetry_properties_ext" offset="0x0.0" selected_by="Optical_Engine_Debug_Parameters_Properties" size="0xf8.0" />
</node>

<node name="pepc_reg_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="twisted_pair_an_mode" descr="twisted_pair operational mode in case of AN enabled: \;0x0: auto_Master_Slave_mode_for_AN_links\;0x1: Master_mode\;0x2: Slave_mode" access="RW" enum="auto_Master_Slave_mode_for_AN_links=0x0,Master_mode=0x1,Slave_mode=0x2" offset="0x4.0" size="0x0.2" />
	<field name="twisted_pair_force_mode" descr="twisted_pair operational mode in case of AN disabled: \;0x0: Master_mode\;0x1: Slave_mode" access="RW" enum="Master_mode=0x0,Slave_mode=0x1" offset="0x4.8" size="0x0.1" />
</node>

<node name="pfcc_reg_ext" descr="" size="0x20.0" >
	<field name="critical_stall_mask" descr="Valid only on HCAs.\;Mask bit indicating if device_stall_critical_watermark should be updated.\;If set to &quot;1&quot;, device_stall_critical_watermark will be updated" access="WO" offset="0x0.2" size="0x0.1" />
	<field name="minor_stall_mask" descr="Valid only on HCAs.\;Mask bit indicating if device_stall_minor_watermark should be updated.\;If set to &quot;1&quot;, device_stall_minor_watermark will be updated" access="WO" offset="0x0.3" size="0x0.1" />
	<field name="ppan_mask_n" descr="Valid only on HCAs.\;Mask bit (negative polarity) indicating if ppan should be updated.\;If set to &quot;0&quot;, ppan will be updated" access="WO" offset="0x0.4" size="0x0.1" />
	<field name="cable_length_mask" descr="Mask bit, indicating in cable_length shall be updated.\;Valid only on HCAs." access="WO" offset="0x0.5" size="0x0.1" />
	<field name="packet_ratio_mask" descr="Valid only on HCAs.\;Mask bit indicating if packet_ratio should be updated.\;If set to &quot;1&quot;, packet_ratio will be updated." access="WO" offset="0x0.6" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local port number\;1: IB / label port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="set_buf_ownership" descr="Supported by HCA only, see PCAM.feature_cap_mask bit 44.\;\;Buffer ownership configuration. when this bits are set to a value other than 0, device will ignore all other fields pfcc register\;0: unknown \;1: device owned, all buffer configuration will return to its defaults." access="WO" offset="0x0.24" size="0x0.2" />
	<field name="buf_ownership" descr="Supported by HCA only, see PCAM.feature_cap_mask bit 44.\;Current status of buffer ownership\;0: unknown\;1: device owned\;2: software owned\;3: partially software owned" access="RO" offset="0x0.26" size="0x0.2" />
	<field name="cap_remote_admin" descr="Indicates if operation of remote admin parameters (dcxb_operation_type 0x2) is supported. \;" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="cap_local_admin" descr="Indicates if operation of local admin parameters (dcxb_operation_type 0x1) is supported. \;" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="dcbx_operation_type" descr="The Operation type, valid only on HCAs.\;0: local_operative_parameters\;1: local_admin_parameters - supported only when cap_local_admin==1.\;2: remote_admin_parameters - supported only when cap_remote_admin==1.\;Only pfctx and pfcrx are supported on remote device" access="INDEX" enum="local_operative_parameters=0x0,local_admin_parameters=0x1,remote_admin_parameters=0x2" offset="0x0.30" size="0x0.2" />
	<field name="prio_mask_rx" descr="Bit per prio indicating if RX flow control policy should be updated based on bit pfcrx ." access="WO" offset="0x4.0" size="0x0.8" />
	<field name="prio_mask_tx" descr="Bit per prio indicating if TX flow control policy should be updated based on bit pfctx ." access="WO" offset="0x4.16" size="0x0.8" />
	<field name="mlb" descr="Valid only on HCAs.\;Multiple lossless buffers (MLB).\;Max lossless buffers to allocated by the device.\;0 - All lossless priorities use single lossless buffer.\;1-7 Defines the maximum number of lossless buffers the device can allocate.\;This field return the value set, to query the actual allocated buffers, see the PBMC or PPTB." access="RW" offset="0x4.24" size="0x0.3" />
	<field name="mlb_mask" descr="Valid only on HCAs.\;Mask bit indicating if MLB should be updated.\;If set to &quot;1&quot;, mlb will be updated." access="WO" offset="0x4.27" size="0x0.1" />
	<field name="ppan" descr="Pause policy auto negotiation\;0: disabled - generate and ignore pause frames based on pptx, pprx\;1: enabled - when auto-negotiation is performed, set the pause policy based on the auto-negotiation resolution.\;\;" access="RW" enum="disabled=0x0,enabled=0x1" offset="0x4.28" size="0x0.4" />
	<field name="fctx_disabled" descr="Valid only on HCAs.\;The bit is set if the device has passed the device_stall_critical_watermark ( for global flow control or any priority when using priority flow control) and has become stalled. \;When fctx_disabled is set, the device will not send flow control and priority flow control (PFC) packets." access="RO" offset="0x8.8" size="0x0.1" />
	<field name="pfctx" descr="Priority based flow control policy on TX[7:0]. Per priority bit mask:\;0: never generate pause frames on the specified priority (default)\;1: generate pause frames according to RX buffer threshold on the specified priority\;pfctx, pptx must be mutually exclusive (for example, only one of them at most can be set)." access="RW" offset="0x8.16" size="0x0.8" />
	<field name="patx" descr="Peer advertisement pause policy on Tx\;0: Unknown\;1: Peer supports pause on Tx\;2: Peer doesn&apos;t support pause on Tx\;\;" access="RO" offset="0x8.27" size="0x0.2" />
	<field name="pptx_mask_n" descr="Valid only on HCAs.\;Mask bit (negative polarity) indicating if pptx should be updated.\;If set to &quot;0&quot;, pptx will be updated" access="WO" offset="0x8.29" size="0x0.1" />
	<field name="aptx" descr="Active (operational) pause policy on TX\;0: do not generate pause frames\;1: generate pause frames according to RX buffer threshold" access="RO" offset="0x8.30" size="0x0.1" />
	<field name="pptx" descr="Admin pause policy on TX (see also pfctx):\;0: never generate pause frames (default)\;1: generate pause frames according to RX buffer threshold" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="pfcrx" descr="Priority based flow control policy on RX[7:0]. Per priority bit mask:\;0: ignore incoming pause frames on the specified priority (default)\;1: respect incoming pause frames on the specified priority" access="RW" offset="0xC.16" size="0x0.8" />
	<field name="parx" descr="Peer advertisement pause policy on Rx\;0: Unknown\;1: Peer supports pause on Rx\;2: Peer doesn&apos;t support pause on Rx\;\;" access="RO" offset="0xC.27" size="0x0.2" />
	<field name="pprx_mask_n" descr="Valid only on HCAs.\;Mask bit (negative polarity) indicating if pprx should be updated.\;If set to &quot;0&quot;, pprx will be updated" access="WO" offset="0xC.29" size="0x0.1" />
	<field name="aprx" descr="Active (operational) pause policy on RX\;0: ignore received pause frames\;1: respect received pause frames" access="RO" offset="0xC.30" size="0x0.1" />
	<field name="pprx" descr="Admin pause policy on RX (see also pfcrx):\;0: ignore received pause frames (default)\;1: respect received pause frames" access="RW" offset="0xC.31" size="0x0.1" />
	<field name="device_stall_critical_watermark" descr="Valid only on HCAs (When health_mon_rx_activity is set).\;The maximum period for a single received packet processing, if the packet was not processed during this time, the device will be declared as stalled and will increase the device_stall_critical_watermark_cnt (PPCNT) counter. Value given in mSec, The maximum period is 8 sec. \;The special value of 0, indicates that the device_stall_critical_watermark is inactive.\;Range: 0x0050 - 0x1F40 \;see also critical_stall_mask" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="device_stall_minor_watermark" descr="Valid only on HCAs (When health_mon_rx_activity is set).\;The maximum period for a single received packet processing, if the packet was not processed during this time, the device will increase the device_stall_minor_watermark_cnt (PPCNT). Value given in mSec, The maximum period is 8 sec. \;The special value of 0, indicates that the device_stall_minor_watermark is inactive.\;Range: 0x0050 - 0x1F40 \;see also critical_stall_mask" access="RW" offset="0x10.16" size="0x0.16" />
	<field name="cable_length" descr="Length of cable in units of 1m.\;Bits 6:7 represent cable_length_multiplier for calculating cable length.\;00 - multiply by 0.1 (10 cm to 6.3 m)\;01 - multiply by 1 (1 to 63 m)\;10 - multiply by 10 (10 to 630m)\;11 - multiply by 100 (100 to 6300m)\;Bits 5:0 cable length before multiplying.\;\;When the value 0 is set - reset to take the cable length from the device.\;If the set value is higher than device abilities, the maximum available length will be set instead.\;If user has set PPTB or PBMC or shared buffer manually (software ownership), this configuration will be ignored.\;\;Valid only on HCAs." access="RW" offset="0x14.0" size="0x0.8" />
	<field name="packet_ratio" descr="The percentage of packets larger than MTU/2.\;Values in 5% units (valid values are between 0-20).\;\;Valid only on HCAs." access="RW" offset="0x14.8" size="0x0.5" />
	<field name="device_auto_calculate" descr="Describes which functionality is controlled by the firmware when buf_ownership indicates partial software ownership.\;Bit 0: Device is responsible for updating shared buffer.\;Bit 1: Device is responsible for updating Xon/Xoff.\;\;Valid only on HCAs." access="RO" offset="0x14.24" size="0x0.8" />
</node>

<node name="pfldc_ext" descr="" size="0x20.0" >
	<field name="lane" descr="Logical lane number.\;\;Lane selection is relevant only if UPHY measurements are being conducted during debug mode entry.\;\;If uphy_measurement_admin == 0, then this field is ignored as all other actions are port specific, and not lane specific." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;1: IB_port_number\;3: Out_of_band_or_PCI" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band_or_PCI=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mps" descr="[DWIP]\;Multiple Port Set.\;Supported only if indicated in PMSCR.prm_support of PFLDC support, otherwise ignored.\;When set, local_port index is ignored and set command is given to all ports in mask given from PMSCR.local_port_mask field" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="debug_mode_oper" descr="Indicates if port is currently in debug mode.\;\;0: regular_operation - port is not in debug mode\;1: debug_mode" access="RO" enum="regular_operation=0x0,debug_mode=0x1" offset="0x4.0" size="0x0.1" />
	<field name="debug_mode_admin" descr="Sets the conditions to enter debug mode.\;Note: All unused bits are reserved\;\;Bit 0: force_debug_mode - Manually enter debug mode when set\;Bit 1: force_debug_mode_logic_up - Manually enter debug mode without dropping logic layer. Packets may still pass on the link, until port receives a link fault indication.\;Bit 2: arm_auto_debug_mode - Port will enter debug mode upon receiving a link fault indication. Valid until cleared\;Bit 3: arm_auto_debug_mode_once - Port will enter debug mode upon receiving a link fault indication. cleared after each debug mode entry (auto / manual)" access="RW" enum="force_debug_mode=0x1,force_debug_mode_logic_up=0x2,arm_auto_debug_mode=0x4,arm_auto_debug_mode_once=0x8" offset="0x4.8" size="0x0.8" />
	<field name="debug_mode_cap" descr="Indicates which debug mode entry conditions are supported.\;Note: All unused bits are reserved\;\;Bit 0: force_debug_mode\;Bit 1: force_debug_mode_logic_up\;Bit 2: auto_debug_mode - if set, port supports &quot;Bit 2: arm_auto_debug_mode&quot; &amp; &quot;Bit 3: arm_auto_debug_mode_once&quot; under debug_mode_admin field" access="RO" enum="force_debug_mode=0x1,force_debug_mode_logic_up=0x2,auto_debug_mode=0x4" offset="0x4.16" size="0x0.8" />
	<field name="disable_debug_mode_admin" descr="When set, port will disable debug mode, and resume regular port operations:\;1. If a link fault indication was raised, port will return to the configured default down state - Polling, Sleep or Disabled\;2. If no link fault indication was raised during debug mode, port will attempt a recovery flow in supported devices. If recovery is successful port will return to linkup, if not port will drop to default down state.  \;\;Note:\;When this field is set any other PFLDC configuration field is ignored.\;\;0: do_nothing\;1: disable_debug_mode" access="WO" enum="do_nothing=0x0,disable_debug_mode=0x1" offset="0x4.25" size="0x0.1" />
	<field name="change_recovery_flow_admin" descr="Valid only if debug mode auto entry has been configured by setting debug_mode_admin[2] or debug_mode_admin[3].\;\;Configures port recovery behavior when auto debug mode is set, and a link fault indication was raised.\;\;0: fw_default\;1: force_skip_recovery - port will not attempt recovery flow, and immediately enter debug mode\;2: force_recovery - if port supports recovery, it will attempt to conduct recovery flow prior to entering debug mode\;3: Reserved" access="RW" enum="fw_default=0x0,force_skip_recovery=0x1,force_recovery=0x2,Reserved=0x3" offset="0x4.26" size="0x0.2" />
	<field name="change_recovery_flow_cap" descr="Indicates if altering recovery default behavior when entering force linkup mode is supported.\;0: not_supported\;1: supported" access="RO" enum="not_supported=0x0,supported=0x1" offset="0x4.28" size="0x0.1" />
	<field name="all_ports_admin" descr="Set debug mode for all non-service ports in device\;0: single_port\;1: all_ports" access="RW" enum="single_port=0x0,all_ports=0x1" offset="0x4.29" size="0x0.1" />
	<field name="all_ports_cap" descr="Indicates if device supports capability to set debug mode on all non-service ports.\;0: not_supported\;1: supported" access="RO" enum="not_supported=0x0,supported=0x1" offset="0x4.30" size="0x0.1" />
	<field name="dc_cpl_allow" descr="Relevant only for DC couple ports, Ignored otherwise.\;Field must be set when entering force linkup debug mode, otherwise  command is ignored.\;When entering force linkup debug mode in DC couple system the following message must be presented to user:\;&quot;Warning: DC couple system must be powered on both sides of the physical link prior to enabling force linkup debug mode. System may be harmed and product lifetime may be  shortened if not ensured.&quot;" access="WO" offset="0x4.31" size="0x0.1" />
	<field name="debug_mode_timer_period" descr="Configures time period for port to remain in debug mode. Once period passes port will exit debug mode.\;\;Value is in units of 10 [sec]" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="debug_mode_timer_admin" descr="Enables device to disable debug mode in port after pre-defined time period set in debug_mode_timer_period\;0: no_timer\;1: set_timer" access="RW" enum="no_timer=0x0,set_timer=0x1" offset="0x8.22" size="0x0.1" />
	<field name="debug_mode_timer_cap" descr="Indicates if device supports capability to disable debug mode after the configured time period has passed.\;0: not_supported\;1: supported" access="RO" enum="not_supported=0x0,supported=0x1" offset="0x8.24" size="0x0.1" />
	<field name="detect_markers_admin" descr="Valid only if transmit_detect_markers_cap Bit 1 is set.\;\;Allows manually configuring port behavior regarding alignment markers detection, while in debug mode.\;\;0: fw_default\;1: enable_markers_detection\;2: disable_markers_detection\;3: reserved" access="RW" enum="fw_default=0x0,enable_markers_detection=0x1,disable_markers_detection=0x2,reserved=0x3" offset="0x8.26" size="0x0.2" />
	<field name="transmit_markers_admin" descr="Valid only if transmit_detect_markers_cap Bit 0 is set.\;\;Allows manually configuring port behavior regarding alignment markers transmission, while in debug mode.\;\;0: fw_default\;1: enable_markers_transmission\;2: disable_markers_transmission\;3: reserved" access="RW" enum="fw_default=0x0,enable_markers_transmission=0x1,disable_markers_transmission=0x2,reserved=0x3" offset="0x8.28" size="0x0.2" />
	<field name="transmit_detect_markers_cap" descr="Indicates if port supports capability to manually override alignment markers transmission &amp; detection while in debug mode.\;Bit 0: transmit_markers_override_supported\;Bit 1: detect_markers_override_supported" access="RO" enum="transmit_markers_override_supported=0x1,detect_markers_override_supported=0x2" offset="0x8.30" size="0x0.2" />
	<field name="uphy_measurement_admin" descr="Bitmask used to trigger which UPHY active measurements will be triggered upon force linkup mode entry.\;\;0: measurement_1 - (Internal) PRR\;1: measurement_2\;All others reserved" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="uphy_measurement_cap" descr="Bitmask indicating which UPHY active measurements can be triggered upon force linkup mode entry.\;\;0: measurement_1 - (Internal) PRR\;1: measurement_2\;All others reserved" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="uphy_measurement_params" descr="Field used to set parameters for the UPHY measurement configured to occur upon force linkup mode entry.\;\;If uphy_measruement_admin == 0 this field will be ignored." access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
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
	<field name="fc_zero_hist" descr="Valid for links with RS FEC histograms only.\;First histogram error with value of 0 while all higher errors are only with 0 value as well.\;0 - No histogram active / N/A value" access="RO" offset="0x60.16" size="0x0.10" />
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

<node name="pipg_reg_ext" descr="" size="0x8.0" >
	<field name="ipg_oper" descr="Inter Packet Gap operational value in ipg_res_cap Bytes units.\;For example, in case of &apos;ipg_oper&apos; =3 and &apos;ipg_res_cap&apos;=0: 4 Bytes- the IPG operational size is 12 Bytes (3*4).\;If there is a mismatch between the operational IPG capabilities and the &apos;ipg&apos; field, &apos;ipg_oper&apos; will be configured to the IPG default value of the device.\;\;Note: Supported only when indicated by PCAM Bit 92: PIPG.ipg_oper_ipg_cap_idx_supported." access="RO" offset="0x0.2" size="0x0.8" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ipg" descr="The Inter Packet Gap admin value for the port in &apos;ipg_res_cap&apos; Bytes units.\;For example, in case of &apos;ipg&apos; =4 and &apos;ipg_res_cap&apos;=0: 4 Bytes -the IPG size that will be configured will be 16 Bytes (4*4)\;\;Valid values for configuring the IPG field should meet to following two conditions:\;1. &apos;ipg&apos; = &apos;ipg_min_cap&apos; + &apos;ipg_res_cap&apos;*N. For N= 0,1,2, ..\;2. &apos;ipg&apos; must be in the range of ipg_min_cap and ipg_max_cap.\;\;The configured &apos;ipg&apos; value will take effect only after link negotiation and if there is no mismatch between the operational IPG capabilities and the configured value." access="RW" offset="0x4.2" size="0x0.8" />
	<field name="ipg_max_cap" descr="Maximum Inter Packet Gap supported on the port in &apos;ipg_res_cap&apos; bytes unit.\;The return value will be according the speed selected in the &apos;ipg_cap_index&quot;." access="RO" offset="0x4.10" size="0x0.8" />
	<field name="ipg_min_cap" descr="Minimum Inter Packet Gap supported on the port in &apos;ipg_res_cap&apos; bytes unit. \;The return value will be according the speed selected in the &apos;ipg_cap_index&quot;." access="RO" offset="0x4.18" size="0x0.4" />
	<field name="ipg_cap_index" descr="The &apos;ipg_min_cap&apos; and &apos;ipg_max_cap&apos; return value will be according to the selected speed index: \;\;0: The Minimum/Maximum capability of the device (Regardless of the operational link speed).\;1: SGMII_100M\;2: 1000BASE-X / SGMII\;4: 5GBASE-R\;5: XFI / XAUI-1 // 10G\;6: XLAUI-4/XLPPI-4 // 40G \;7: 25GAUI-1/ 25GBASE-CR / KR \;8: 50GAUI-2 / LAUI-2/ 50GBASE-CR2/KR2 \;9: 50GAUI-1 /50GBASE-CR / KR\;10: CAUI-4 / 100GBASE-CR4 / KR4\;11: 100GAUI-2 / 100GBASE-CR2 / KR2 \;12: 100GAUI-1 / 100GBASE-CR / KR\;13: 200GAUI-4 / 200GBASE-CR4/KR4\;14: 200GAUI-2 / 200GBASE-CR2/KR2\;15: 200GAUI-1 / 200GBASE-CR1/KR1\;16: 400GAUI-8/ 400GBASE-CR8\;17: 400GAUI-4/ 400GBASE-CR4\;18: 400GAUI-2 / 400GBASE-CR2/KR2\;19: Reserved [internal] Placeholder for 400GAUI-1\;20: 800GAUI-8 / 800GBASE-CR8 / KR8\;21: 800GAUI-4 / 800GBASE-CR4/KR4\;24: 1.6TAUI-8 /1.6TBASE-CR8/KR8\;32: SGMII_10M\;\;Note: Supported only when indicated by PCAM Bit 92: PIPG.ipg_oper_ipg_cap_idx_supported." access="INDEX" offset="0x4.22" size="0x0.6" />
	<field name="ipg_res_cap" descr="IPG configurable resolution of the device in Bytes granularity.\;0: bytes_4x\;1: bytes_8x" access="RO" enum="bytes_4x=0x0,bytes_8x=0x1" offset="0x4.28" size="0x0.1" />
</node>

<node name="plcc_reg_ext" descr="" size="0x10.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM \;0: Network_port\;1: Near_End_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: Far_End_Port - (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" enum="Network_port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;1: IB_port_number\;3: Out_of_band_or_PCI" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band_or_PCI=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="page_select" descr="page select index:\;0: High_symbol_error_rate_configuration_page\;1: High_bit_error_rate_configuration_page" access="INDEX" enum="High_symbol_error_rate_configuration_page=0x0,High_bit_error_rate_configuration_page=0x1" offset="0x4.0" size="0x0.8" />
	<field name="page_data" descr="Table  2562, &quot;High symbol error rate configuration Page Layout,&quot; on page  2955\;Table  2564, &quot;High bit error rate configuration Page Layout,&quot; on page  2955" subnode="plcc_reg_page_data_auto_ext" access="RW" offset="0x8.0" size="0x8.0" union_selector="$(parent).page_select" />
</node>

<node name="plcc_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x8.0" >
	<field name="High_bit_error_rate_configuration_page_ext" descr="" subnode="High_bit_error_rate_configuration_page_ext" offset="0x0.0" selected_by="High_bit_error_rate_configuration_page" size="0x4.0" />
	<field name="High_symbol_error_rate_configuration_page_ext" descr="" subnode="High_symbol_error_rate_configuration_page_ext" offset="0x0.0" selected_by="High_symbol_error_rate_configuration_page" size="0x8.0" />
</node>

<node name="plds_ext" descr="" size="0x18.0" >
	<field name="fec_uncor_cap" descr="When set, rs_fec_uncor_th is valid and configurable" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="plr_retry_cap" descr="When set, plr_csn_retry_th is valid and configurable" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="fec_uncor_force_cap" descr="For the link negotiation mechanism, does the host support forcing the threshold value of link drop trigger for number of uncorrectable FEC blocks - between the two connected ports.\;\;0 - Not supported\;1 - Supported" access="RO" offset="0x0.2" size="0x0.1" />
	<field name="plr_retry_force_cap" descr="For the link negotiation mechanism, does the host support forcing the threshold value of link drop trigger for number of PLR retry on same CSN - between the two connected ports.\;\;0 - Not supported\;1 - Supported" access="RO" offset="0x0.3" size="0x0.1" />
	<field name="fec_uncor_force" descr="If set, force the rs_fec_uncor_th value on the peer port" access="RW" offset="0x0.4" size="0x0.1" />
	<field name="plr_retry_force" descr="If set, force the plr_csn_retry_th value on the peer port" access="RW" offset="0x0.5" size="0x0.1" />
	<field name="delayed_recovery_force" descr="If set, force the delayed_recovery_admin value on the peer port" access="RW" offset="0x0.6" size="0x0.1" />
	<field name="delayed_recovery_cap" descr="When set, delayed_recovery fields are valid and configurable" access="RO" offset="0x0.7" size="0x0.1" />
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
	<field name="rs_fec_uncor_th" descr="Link drop trigger for number of uncorrectable FEC blocks in a 128 fec block window threshold.\;If threshold is crossed, link will be dropped or trigger recovery flow.\;0: FW_default\;\;If fec_uncor_force_cap is cleared: On Get, when link is down, shall return the admin value to be configured. When link is up, returns operational value.\;If fec_uncor_force_cap is set: On Get, shall return the admin value to be configured." access="RW" offset="0x10.0" size="0x0.7" />
	<field name="plr_csn_retry_th_oper" descr="Operational value for the Link drop trigger for number of uncorrectable FEC blocks in a 128 fec block window threshold.\;Valid only if fec_uncor_force_cap is set." access="RO" offset="0x10.7" size="0x0.9" />
	<field name="plr_csn_retry_th" descr="Link drop trigger for number of PLR retry on same CSN threshold.\;If threshold is crossed, link will be dropped or trigger recovery flow.\;0: FW_default\;\;If plr_retry_force_cap is cleared: On Get, when link is down, shall return the admin value to be configured. When link is up, returns operational value.\;If plr_retry_force_cap is set: On Get, shall return the admin value to be configured." access="RW" offset="0x10.16" size="0x0.9" />
	<field name="rs_fec_uncor_th_oper" descr="Operational value for the Link drop trigger for number of PLR retry on same CSN thresh.\;Valid only if plr_retry_force_cap is set." access="RO" offset="0x10.25" size="0x0.7" />
	<field name="delayed_recovery_oper" descr="0: not_supported\;1: delayed_recovery_enable\;2: delayed_recovery_disable" access="RO" offset="0x14.0" size="0x0.2" />
	<field name="delayed_recovery_admin" descr="0: Auto (based on FW default - INI)\;1: delayed_recovery_enable\;2: delayed_recovery_disable" access="RW" offset="0x14.2" size="0x0.2" />
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

<node name="plu_general_tracer_page_ext" descr="" size="0xc.0" >
	<field name="stop_condition_oper" descr="Configured stop condition for PLU general tracer. Admin value set with stop_condition field.\;0: Link Fail\;1: First Uncorrectable" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="stop_condition" descr="Configures stop condition for PLU general tracer. Once stop condition is met all fields are latched.\;0: Link Fail\;1: First Uncorrectable" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Clear all latched values. This bit can be set for both Set() and Get() operation\;0: Do nothing\;1: Clear" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="Previous_7_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="Previous_6_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="Previous_5_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x4.8" size="0x0.4" />
	<field name="Previous_4_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x4.12" size="0x0.4" />
	<field name="Previous_3_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="Previous_2_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x4.20" size="0x0.4" />
	<field name="Previous_1_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="Previous_0_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x4.28" size="0x0.4" />
	<field name="Previous_15_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x8.0" size="0x0.4" />
	<field name="Previous_14_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x8.4" size="0x0.4" />
	<field name="Previous_13_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x8.8" size="0x0.4" />
	<field name="Previous_12_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x8.12" size="0x0.4" />
	<field name="Previous_11_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x8.16" size="0x0.4" />
	<field name="Previous_10_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x8.20" size="0x0.4" />
	<field name="Previous_9_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x8.24" size="0x0.4" />
	<field name="Previous_8_FEC_block_histogram" descr="Histogram bin the i+1 previous FEC block belongs to. Latched when PLU general tracer stop condition is met" access="RO" offset="0x8.28" size="0x0.4" />
</node>

<node name="pmaos_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Module state (reserved while admin_status is disabled):\;0: initializing\;1: plugged_enabled\;2: unplugged\;3: module_plugged_with_error - (details in error_type).\;5: unknown" access="RO" enum="initializing=0x0,plugged_enabled=0x1,unplugged=0x2,module_plugged_with_error=0x3,unknown=0x5" offset="0x0.0" size="0x0.4" />
	<field name="admin_status" descr="Module administrative state (the desired state of the module):\;1: enabled\;2: disabled_by_configuration\;3: enabled_once - if the module is active and then unplugged, or module experienced an error event, the operational status should go to &quot;disabled&quot; and can only be enabled upon explicit enable command.\;0xe: disconnect_cable\;\;Note - To disable a module, all ports associated with the port must be disabled first. \;Note 2 - disconnect cable will shut down the optical module in ungraceful manner. \;" access="RW" enum="enabled=0x1,disabled_by_configuration=0x2,enabled_once=0x3,disconnect_cable=0xe" offset="0x0.8" size="0x0.4" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="rst" descr="Module Reset toggle\;NOTE: setting reset while module is plugged-in will result in transition of oper_status to initialization." access="OP" offset="0x0.31" size="0x0.1" />
	<field name="e" descr="Event Generation on operational state change:\;0: Do_not_generate_event\;1: Generate_Event\;2: Generate_Single_Event\;Not supported by secondary ASICs." access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="error_type" descr="Module error details:\;0x0: Power_Budget_Exceeded\;0x1: Long_Range_for_non_MLNX_cable_or_module\;0x2: Bus_stuck - (I2C Data or clock shorted)\;0x3: bad_or_unsupported_EEPROM\;0x4: Enforce_part_number_list\;0x5: unsupported_cable\;0x6: High_Temperature\;0x7: bad_cable - (Module/Cable is shorted)\;0x8: PMD_type_is_not_enabled - (see PMTPS)\;0xc: pcie_system_power_slot_Exceeded\;\;[DWIP] 0xf: Boot_error\;[DWIP] 0x10: Recovery_error\;[DWIP] 0x11: Submodule_failure\;\;[DWIP] 0x13: els_critical_indication\;Valid only when oper_status = 4&apos;b0011" access="RO" enum="Power_Budget_Exceeded=0x0,Long_Range_for_non_MLNX_cable_or_module=0x1,Bus_stuck=0x2,bad_or_unsupported_EEPROM=0x3,Enforce_part_number_list=0x4,unsupported_cable=0x5,High_Temperature=0x6,bad_cable=0x7,PMD_type_is_not_enabled=0x8,pcie_system_power_slot_Exceeded=0xc" offset="0x4.8" size="0x0.5" />
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
	<field name="media_type_override_value" descr="Valid only in case media_type_override_cntrl is configured to override mode.\;Configures module media type peer side for optimal performance\;0: Peer_is_retimed_module - [internal] &quot;Optical_retimed &quot; in CDB\;1: Peer_is_CPO_module - [internal] &quot;Optical_CPO&quot; in CDB\;2: reserved\;3: reserved" access="RW" offset="0x1C.8" size="0x0.2" />
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
	<field name="width_valid" descr="When set, port_width field value is valid. otherwise ignored" access="RO" offset="0x0.10" size="0x0.1" />
	<field name="mcm_tile_valid" descr="0 if there is no MCM tile arch" access="RO" offset="0x0.12" size="0x0.1" />
	<field name="gb_valid" descr="0 if there is no Gearbox/Retimer arch" access="RO" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="[7:0] bits for Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0 - 40nm products\;1 - 28nm products\;3 - 16nm products\;4 - 7nm products\;5 - 5nm products SerDes Gen7.0/ 7.5\;6 - 5nm products SerDes Gen8.0" access="RO" offset="0x0.24" size="0x0.4" />
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
	<field name="port_width" descr="Port width of logical lanes.\;According to number of port width, indicates how many lanes shall be considered in lane&lt;i&gt;_physical_tx/rx\;0 - port is unmapped" access="RO" offset="0xC.6" size="0x0.4" />
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
	<field name="sub_module" descr="Indicates start offset of rx_lane, tx_lane inside the modules lanes in 8x granularity. relevant for modules with more than 8 lanes. such as OE.\;0: lanes_0-7\;1: lanes_8_15\;2: lanes_16_23\;3: lanes_24_31" access="RO" offset="0x3C.28" size="0x0.4" />
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
	<field name="apply_im" descr="When set, override will be configured immediately without PMAOS toggle requirement if supported.\;For the list of supported overrides, see eeprom_override description.\;supported if PCAM.bit 87 set.\;Field is ignored when set_laser_state is set to a non-zero value." access="WO" offset="0x0.1" size="0x0.1" />
	<field name="els_trigger_mode" descr="Relevant for ELS module for IB CPO switches only. Relevant for User to configure the ELS module states: \;0: Do_not_generate_event\;1: Generate_Event\;" access="WO" offset="0x0.2" size="0x0.2" />
	<field name="laser_mask" descr="Relevant for ELS module for IB CPO switches only, ELS lasers bitmask. When set, only selected lasers, will follow the set_laser_operation field." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="override_target" descr="Relevant only for power_setpoint_lane[] override field. When set, the power setpoint parameters will be written into non-voletile memory in ELSFP module, instead of CMIS page." access="OP" offset="0x0.29" size="0x0.1" />
	<field name="eeprom_override" descr="Override/ignore EEPROM advertisement properties bitmask: \;Bit 0: Override_cable_protocols_and_technology_for_QSFP\;Bit 1: Override_cable_protocols_and_technology_for_SFP\;Bit 2: Ignore_Power_Class - set high power\;Bit 3: Override_Cable_Length \;Bit 4: Override_Attenuation\;Bit 8: Set_Module_to_Low_Power\;Bit 9: Override_cable_protocols_and_technology_for_CMIS - based modules QSFP-DD/ OSFP/ DSFP/ SFP-DD\;Bit 11: Override_module_type\;Bit 12: Override_ELS_lane_power\;Bit 13: Override_ELS_output_fiber_checked_flag\;Bit 14: Override_ELS_lane_enable\;Supported overrides with apply_im is bits 8, 12, 13, 14.\;rest of overrides will be applied only after PMAOS toggle.\;For bits 11-14, the override is done separately - each configuration at a time" access="RW" enum="Override_cable_protocols_and_technology_for_QSFP=0x1,Override_cable_protocols_and_technology_for_SFP=0x2,Ignore_Power_Class=0x4,Override_Cable_Length=0x8,Override_Attenuation=0x10,Set_Module_to_Low_Power=0x100,Override_cable_protocols_and_technology_for_CMIS=0x200,Override_module_type=0x800,Override_ELS_lane_power=0x1000,Override_ELS_output_fiber_checked_flag=0x2000,Override_ELS_lane_enable=0x4000" offset="0x4.0" size="0x0.16" />
	<field name="eeprom_override_mask" descr="Write Mask bit (negative polarity):\;0 - allow write\;1 - ignore write\;On write commands, indicates which of the bits from eeprom_override field are updated.\;Reserved on read operations." access="WO" offset="0x4.16" size="0x0.16" />
	<field name="qsfp_cable_protocol_technology" descr="Protocol technology override for QSFP cable or CMIS based cable (QSFP-DD/OSFP)\;Valid only when the protocols and technology for QSFP is overridden as indicated by eeprom_override\;Table  2012, &quot;PMMP - QSFP Protocol Bytes Override Layout,&quot; on page  2364\;Table  2016, &quot;PMMP - CMIS Protocol Bytes Override Layout,&quot; on page  2368" subnode="pmmp_reg_qsfp_cable_protocol_technology_auto_ext" access="RW" offset="0x8.0" size="0xc.0" union_selector="$(parent).eeprom_override" />
	<field name="sfp_cable_protocol_technology" descr="Valid only when the protocols and technology is overridden as indicated by eeprom_override\;Table  2014, &quot;PMMP - SFP Protocol Bytes Override Layout,&quot; on page  2367" subnode="pmmp_reg_sfp_cable_protocol_technology_auto_ext" access="RW" offset="0x14.0" size="0xc.0" union_selector="$(parent).eeprom_override" />
	<field name="cable_length" descr="Length of cable assembly, units of 1 m for non CMIS cables.\;\;for CMIS cables, represents cable length field:\;bits 6:7 represent cable_length_multiplier for calculating cable length\;00 - 0.1 multiplier (0.1 to 6.3m)\;01- 1 multiplier (1 to 63m)\;10 - 10 multiplier (10 to 630m)\;11 - 100 multiplier (100 to 6300m)\;\;Valid only when the cable length is overridden as indicated by eeprom_override." access="RW" offset="0x20.0" size="0x0.8" />
	<field name="module_type" descr="0: passive_copper_cable\;1: active_copper_cable\;2: Liner_far_end_equalized_copper\;3: Linear_full_equalized_copper\;4: Linear_optical_module - Direct Drive\;5: active_optical_module\;6: on_board_retimer_over_transceiver" access="RW" offset="0x20.8" size="0x0.4" />
	<field name="set_laser_operation" descr="Relevant for ELS module for IB CPO switches only. Set Laser operation:\;0: no_operation\;1: fiber_check\;2: laser_tuning\;3: laser_up\;6: laser_fine_tune\;7: laser_wavelength_tune" access="WO" offset="0x20.29" size="0x0.3" />
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

<node name="pmscr_reg_ext" descr="" size="0x48.0" >
	<field name="prm_index" descr="Register to get / set the local port mask configurations\;0: PREI\;1: PFLDC\;2: PEDCC" access="INDEX" enum="PREI=0x0,PFLDC=0x1,PEDCC=0x2" offset="0x0.0" size="0x0.4" />
	<field name="prm_support" descr="Bitmask of the register that supports the multiple port set configuration.\;Bit 0: PREI\;Bit 1: PFLDC\;Bit 2: PEDCC\;\;Note that if the selected register index is not supported, a bad status will be returned." access="RO" enum="PREI=0x1,PFLDC=0x2,PEDCC=0x4" offset="0x0.8" size="0x0.8" />
	<field name="local_port_mask" descr="Local port mask for applying the register configuration based on the prm_index selected.\;For unmapped local_ports command is ignored." access="RW" high_bound="16" low_bound="0" offset="0x4.0" size="0x44.0" />
</node>

<node name="pmtm_reg_ext" descr="" size="0x10.0" >
	<field name="module" descr="module number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="module_type" descr="module_type: \;0: Backplane_with_4_lanes\;1: QSFP\;2: SFP\;3: No_Cage - [Obsolete]\;4: Backplane_with_single_lane\;8: Backplane_with_two_lanes\;10: Chip2Chip4x\;11: Chip2Chip2x \;12: Chip2Chip1x\;14: QSFP_DD \;15: OSFP\;16: SFP_DD\;17: DSFP \;18: Chip2Chip8x\;19: Twisted_Pair\;20: Backplane_with_8_lanes\;21: Loopback \;22: OE_16x \;23: OSFP_ELS\;24: QSFP_2x\;25: CPO_32x" access="RW" enum="Backplane_with_4_lanes=0x0,QSFP=0x1,SFP=0x2,No_Cage=0x3,Backplane_with_single_lane=0x4,Backplane_with_two_lanes=0x8,Chip2Chip4x=0xa,Chip2Chip2x=0xb,Chip2Chip1x=0xc,QSFP_DD=0xe,OSFP=0xf,SFP_DD=0x10,DSFP=0x11,Chip2Chip8x=0x12,Twisted_Pair=0x13,Backplane_with_8_lanes=0x14,Loopback=0x15,OE_16x=0x16,OSFP_ELS=0x17,QSFP_2x=0x18,CPO_32x=0x19" offset="0x4.0" size="0x0.5" />
	<field name="module_width" descr="Number of module&apos;s electrical lanes\;\;NOTE: For SET command, this value should match the module type width in module_type field" access="RW" offset="0x4.8" size="0x0.5" />
</node>

<node name="pmtu_reg_ext" descr="" size="0x10.0" >
	<field name="itre" descr="Ingress Truncation enable, the admin_mtu is used as truncation:\;0: disable\;1: enable\;Reserved when NICs (NICs use only &apos;0&apos;)\;Reserved when IB Switches (use only &apos;0&apos;)\;Reserved when i_e = 0 or 2\;Reserved when GPUNet" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="i_e" descr="Ingress/Egress:\;0: applies for both ingress and for egress, read from egress\;1: applies only for ingress\;2: applies only for egress\;Reserved when NICs (NICs use only &apos;0&apos;)\;Reserved when IB Switches (use only &apos;0&apos;)\;Reserved when GPUNet" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number\;Not including CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="protocol" descr="[DWIP]:\;The protocol which the MTU is applied to. \;0: All protocols that are supported by the device. On get, it will return the value for IBg1\;1: IB (gen 1) \;2: NVLink\;3: IBg2\;4-15: Reserved\;Reserved when Eth switches\;Reserved when NIC\;Note: for GB100 IBg2 is not PoR, Nov 2023" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="max_mtu" descr="Maximum MTU supported on the port (Read Only).\;MTU depends on the port type. When port type (Eth/IB/FC) is configured, the relevant MTU is reported. When the port type is not configured, the minimum between the max_mtu for the different types (Eth/IB/FC) is reported.\;Informative:- For GPUNet: IB is used for MADs, thus max MTU is 768B\;- NVLink max MTU is 320B" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="admin_mtu" descr="Administratively configured MTU on the port. Must be smaller or equal to max_mtu.\;When IB: configuration is allowed only when port state is down.\;When itre=1 then must be at least 128B and granularity is 8B" access="RW" offset="0x8.16" size="0x0.16" />
	<field name="oper_mtu" descr="Operational MTU. This is the actual MTU configured on the ports. Packets exceeding this size will be dropped.\;Note: For NICs and for IB the actual operational MTU is reported which may be smaller than admin_mtu.\;For NICs: when PCAM.max_admin_mtu capability is set then oper_mtu will be the max of all admin_mtu" access="RO" offset="0xC.16" size="0x0.16" />
</node>

<node name="port_state_behavior_ext" descr="" size="0x10.0" >
	<field name="enforce_port_state_enabled" descr="0x0: DISABLED\;0x1: ENABLED - regular driver will be able to enforce physical port state." access="RW" enum="DISABLED=0x0,ENABLED=0x1" offset="0x0.31" size="0x0.1" />
</node>

<node name="ppad_reg_ext" descr="" size="0x10.0" >
	<field name="mac_47_32" descr="If single_base_mac = 0 - base MAC address\;For HCA mac[7:0] is reserved \;If single_base_mac = 1 - the per port MAC address" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="local_port" descr="Port number\;Reserved when single_base_mac = 0" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="single_base_mac" descr="0: base_mac - Switch global MAC address. FW will set incremental MAC per port starting from the base_mac.\;1: single_mac - mac of the local_port" access="OP" offset="0x0.28" size="0x0.1" />
	<field name="mac_31_0" descr="If single_base_mac = 0 - base MAC address\;For HCA mac[7:0] is reserved \;If single_base_mac = 1 - the per port MAC address" access="RW" offset="0x4.0" size="0x4.0" />
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
	<field name="primary_secondary_to_default" descr="When set, force default values setting into the following fields: primary_secondary, and primary_secondary_constant." access="RW" offset="0x4.18" size="0x0.1" />
	<field name="primary_secondary_oper" descr="Indicates for Mode B links if the port was chosen as primary or secondary during linkup.\;0: Not_supported_or_not_chosen_yet.\;1: Primary\;2: Secondary" access="RO" enum="Not_supported_or_not_chosen_yet_=0x0,Primary=0x1,Secondary=0x2" offset="0x4.20" size="0x0.2" />
	<field name="primary_secondary_constant" descr="Used to keep primary / secondary role constant between link toggles. If the field is set to &quot;1&quot; on local device and peer, both will keep their current role as primary or secondary.\;0: not_constant_role\;1: constant_role" access="RW" enum="not_constant_role=0x0,constant_role=0x1" offset="0x4.22" size="0x0.1" />
	<field name="primary_secondary" descr="This field can be configured when port is up, and configuration will be saved for next port toggle. The field functions as an admin field.\;\;The primary_secondary field will set the role of the port in the link negotiation state. \;\;0: Auto (based on AN resolution, will not change the existing configuration)\;1: Primary\;2: Secondary\;\;Notes:\;1. This field is applicable for Mode B links in test mode and operational mode.\;2. Each side of the connected ports should be configured with the opposite role.\;3. While working in test mode, this field should be configured with the same values as in the PPRT/PPTT.primary_secondary fields.\;4. When setting a non-test mode loopback with a Mode B rate, it is not required to set the port in a certain role. However, the port may not be configured as secondary.\;5. When setting a test mode loopback with a Mode B rate, port must be set as primary." access="RW" offset="0x4.25" size="0x0.2" />
	<field name="dc_cpl_port" descr="When set, indicates that ports trace is DC coupled.\;Enabling test mode in case of DC coupled port is allowed only when setting dc_cpl_allow and printing warning to user as specified in the description." access="RO" offset="0x4.28" size="0x0.1" />
	<field name="dc_cpl_allow" descr="Relevant only for DC couple ports, Ignored otherwise.\;Field must be set when entering test mode, otherwise command is ignored.\;When entering test mode in DC couple system the following message must be presented to user:\;&quot;Warning: DC couple system must be powered on both sides of the physical link prior to enabling test mode. System may be harmed and product lifetime may be shortened if not ensured.&quot;" access="WO" offset="0x4.29" size="0x0.1" />
</node>

<node name="ppbmc_reg_ext" descr="" size="0x10.0" >
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;4 - USR Main\;5 - USR Tile\;Other values are reserved.\;Configuration 4,5 should use the same clock" access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="monitor_type" descr="Operational monitor types enabled based on monitor_cntl setting and the operational mode of the link:\;Bit 0: Post_FEC_or_No_FEC_BER_monitoring\;Bit 1: Pre_FEC_BER_monitoring\;Bit 2: Symbol_BER_monitoring\;Bit 3: Estimated_Effective_BER_monitoring" access="RO" enum="Post_FEC_or_No_FEC_BER_monitoring=0x1,Pre_FEC_BER_monitoring=0x2,Symbol_BER_monitoring=0x4,Estimated_Effective_BER_monitoring=0x8" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="monitor_e_ctrl_ind" descr="Valid only when monitor_e_ctrl_ind_cap is set.\;Selects which monitors events control are applied - e, event_ctrl, and monitor_state fields.\;0: All_monitors\;1: Raw_BER_monitor\;2: Effective_BER_monitor\;3: Symbol_BER\;4: Estimated_Effective_BER_monitoring\;5: Tx_BW_loss -" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="monitor_state" descr="The monitor state of the port:\;0 - No BER Monitor support\;1 - Normal\;2 - Warning\;3 - Alarm\;* The init monitor state for each port upon link up is normal" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="est_ef_ber_cap" descr="Indicates Estimated Effective BER monitoring supported" access="RO" offset="0x4.8" size="0x0.1" />
	<field name="clr_stat" descr="clear statistics from PPDR. link_down_info page of selected monitor type" access="OP" offset="0x4.9" size="0x0.1" />
	<field name="monitor_e_ctrl_ind_cap" descr="When set monitor_e_ctrl_ind is valid" access="RO" offset="0x4.10" size="0x0.1" />
	<field name="monitor_type_ext" descr="Operational monitor types extenstion enabled based on monitor_cntl, monitor_cntl_ext setting and the operational mode of the link:\;Bit 0: UCR - Uncorrectable Codeword Ratio" access="RO" enum="UCR=0x1" offset="0x4.12" size="0x0.4" />
	<field name="monitor_cntl" descr="Bitmask - monitor options to enable monitoring:\;When multiple_monitor_cap is set, multiple bits can be set. Else, only 1 bit can be set\;Bit 0: Raw_BER_monitor - When set, a link with FEC active will monitor Pre-FEC BER.\;Bit 1: Effective_FEC_monitor\;Bit 2: Symbol_FEC_monitor\;Bit 3: Estimated_Effective_BER_monitoring" access="RW" enum="Raw_BER_monitor=0x1,Effective_FEC_monitor=0x2,Symbol_FEC_monitor=0x4,Estimated_Effective_BER_monitoring=0x8" offset="0x4.16" size="0x0.8" />
	<field name="event_ctrl" descr="Bitmask - event generation on operational state change:\;Bit 0 - Normal state\;Bit 1 - Warning state\;Bit 2 - Alarm state\;Bit 3 - Reserved\;\;Note: Normal state events can be generated only if either Alarm and/or Warning events are enabled." access="RW" offset="0x4.24" size="0x0.4" />
	<field name="multiple_monitor_cap" descr="When set, multiple monitoring groups are possible. Hence, monitor_cntl can be set with multiple bits.\;else, monitor_cntl can be set with only 1 bits" access="RO" offset="0x4.28" size="0x0.1" />
	<field name="ievent" descr="Invoke event\;0: Read only\;1: Does both reading and invoke an event of type PPBME_TRAP\;\;Note: setting this field invokes an event, regardless to e and event_ctl fields, it has no effect on the event state." access="OP" offset="0x4.29" size="0x0.1" />
	<field name="e" descr="Event generation on operational state change:\;0 - Do not generate event\;1 - Generate Event \;2 - Generate Single Event\;Not Supported for HCA." access="RW" offset="0x4.30" size="0x0.2" />
	<field name="monitor_type_ext2" descr="Operational monitor types extenstion enabled based on monitor_cntl, monitor_cntl_ext setting and the operational mode of the link:" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="monitor_type_cap" descr="Monitor type capability mask:\;Bit 0: plr_tx_bw_loss_lf\;Bit 3: Estimated_Effective_BER_monitoring\;Bit 4: UCR - Uncorrectable Codeword Ratio\;\;Note - raw BER, effective BER, symbol BER do not have capability" access="RO" enum="Estimated_Effective_BER_monitoring=0x8,UCR=0x10" offset="0x8.16" size="0x0.8" />
	<field name="monitor_cntl_ext" descr="Bitmask - monitor options to enable monitoring:\;When multiple_monitor_cap is set, multiple bits can be set. Else, only 1 bit can be set\;" access="RW" offset="0xC.16" size="0x0.8" />
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
	<field name="monitor_group" descr="Monitor Parameters Group\;0x0: Raw_BER_RS\;0x1: Raw_BER_FC\;0x2: Effective_BER\;0x4: Pre_FEC_BER\;0x5: Symbol_BER\;0x6: Estimated_Effective_BER_monitoring\;0x7: UCR - Uncorrectable Codeword Ratio\;0x8: Tx_BW_loss -" access="INDEX" enum="Raw_BER_RS=0x0,Raw_BER_FC=0x1,Effective_BER=0x2,Pre_FEC_BER=0x4,Symbol_BER=0x5,Estimated_Effective_BER_monitoring=0x6,UCR=0x7,Tx_BW_loss=0x8" offset="0x0.0" size="0x0.4" />
	<field name="grp_prf_set" descr="When set, grp_prf field will set local_port&apos;s group.\;Else, grp_prf field will be ignore in set operation" access="WO" offset="0x0.11" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="grp_prf" descr="Group profile port is mapped to.\;when group_profile is set," access="RW" offset="0x0.24" size="0x0.3" />
	<field name="grp_prf_cap" descr="When set grp_prf field is configurable.\;Note: supported only in IB/NVLink devices" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="admin_oper_sel" descr="On read operation, selects how monitor_parameters and time_window fields are represented.\;0: show_fields_as_admin (if no neg, also operational)\;1: show_fields_as_oper" access="INDEX" offset="0x0.28" size="0x0.1" />
	<field name="monitor_parameters_w_ignore" descr="&apos;monitor_parameters&apos; field ignore write. \;Relevant for set operation only, while this bit is set to &apos;1&apos;- \;ignore the &apos;monitor_parameters&apos; values." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="time_window_w_en" descr="&apos;time_window&apos; field write enable\;Relevant for set operation only, while this bit is set to &apos;0&apos;- \;ignore the &apos;time_window&apos; value." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Supported if PCAM.feature_cap_mask bit 93 is set.\;0: override_thresholds - thresholds set according to monitor_parameters values.\;1: set_fw_default_thresholds - thresholds set in monitor_parameters are ignored\;\;" access="RW" enum="override_thresholds=0x0,set_fw_default_thresholds=0x1" offset="0x0.31" size="0x0.1" />
	<field name="monitor_parameters" descr="Table 2290, &quot;PPBMP - BER Monitor Parameters Layout,&quot; on page 2725" subnode="ppbmp_reg_monitor_parameters_auto_ext" access="RW" offset="0x4.0" size="0x8.0" />
	<field name="time_window" descr="The time frame which the events are grouped. \;This is a tumbling window (not a sliding window), means that each window is uncorrelated to the adjacent windows events. \;For BER features the time window derived from \;the lowest threshold.\;Units of sampling_rate.\;Value of zero is means the BER monitor is not active or time window is unknown\;\;time window is adjustable only if time_window_set_cap is set" access="RW" offset="0xC.0" size="0x0.24" />
	<field name="time_window_set_cap" descr="The capability to adjust the time_window field" access="RO" offset="0xC.31" size="0x0.1" />
	<field name="sampling_rate" descr="Time frame to measure warning threshold and error threshold. \;Units of 10mSec, range 0..1Sec. \;Value of zero is means the BER monitor is not active or sampling rate is unknown" access="RO" offset="0x10.0" size="0x0.8" />
	<field name="monitor_parameters_cap" descr="The configured Monitor Parameters shall be within the ranges defined by this field.\;The returned value is according to the monitor_group index and the device capabilities.\;See Table 2294, &quot;PPBMP - Monitor Parameters Capabilities Layout,&quot; on page 2727" subnode="ppbmp_monitor_params_cap_ext" access="RO" offset="0x14.0" size="0x4.0" />
</node>

<node name="ppbmp_reg_monitor_parameters_auto_ext" descr="" attr_is_union="1" size="0x8.0" >
	<field name="ppbmp_monitor_parameters_ext" descr="" subnode="ppbmp_monitor_parameters_ext" offset="0x0.0" size="0x8.0" />
</node>

<node name="ppcc_reg_ext" descr="" size="0xfc.0" >
	<field name="cmd_type" descr="0x0 - get algo info\;0x1 - enable algo\;0x2 - disable algo\;0x3 - get algo enabling status\;0x4 - get num of params\;0x5 - get param info\;0x6 - get param\;0x7 - get &amp; clear param\;0x8 - set param\;\;0xA - bulk get. Reserved when method = Set\;0xB - bulk set. Reserved when method = Get\;0xC - bulk get counters. Reserved when method = Set\;0xD - bulk get and clear counters \;0xE - get num of counters. Reserved when method = Set\;0xF - get counter info. Reserved when method = Set\;0x10 - get algo info array\;0xF0 - get supported target apps\;" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. Determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="target_app" descr="0:PCC_RP\;1: PCC_NP\;2: MULTIPATH\;" access="INDEX" enum="PCC_RP=0x0,PCC_NP=0x1,MULTIPATH=0x2" offset="0x0.28" size="0x0.4" />
	<field name="algo_slot" descr="Selects the algo slot to operate on (0 - algo slot at bit #0, 1 - algo slot at bit #1, etc). \;For command types other than 0x10 (get algo info array), must point to a present algo slot (a slot index with a non-zero algo id - as returned via Command type 0x10)" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="algo_param_index" descr="Selects the specific param or counter to get/set (if applicable, 0 if not). Index is zero-based. Must be smaller than value returned in get_num_of_params / get_num_of_counters. \;Appliccable for commands 0x5-0x8, 0xA-0xD." access="INDEX" offset="0x4.16" size="0x0.16" />
	<field name="value" descr="The layout of this field varies based on command type:\;For cmd_type = 0x0: returns 32-bit algo_num or 0 if no algo is available at this index\;For cmd_type = 0x3: returns 1 if enabled, 0 otherwise\;For cmd_type = 0x4: returns num of params algo has\;For cmd_type = 0x6:: returns value of param (selected by param index)\;For cmd_type = 0x7: returns value of param (selected by param index) and clears param\;For cmd_type = 0x8: The value to write to param (selected by param index). Set by the user. Set command is silently ignored if value outside min..max values (comparison is unsigned) or if param permission is not read-write.\;For cmd_type = 0xE: returns the num of counters algo has.\;For cmd_type = 0xF0: returns a bit mask of supported apps\;All the rest: returns 0" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="param_value1" descr="For cmd_type = 0x5: return default value of param\;For cmd_type = 0xE: returns the max counter group ID available. Counter group IDs are 0-indexed, the max ID would be num_groups-1.\;\;\;\;Reserved for other commands" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="param_value2" descr="For cmd_type = 0x5: return min legal value of param\;\;\;\;Reserved for other commands" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="param_value3" descr="For cmd_type = 0x5: return max legal value of param\;For cmd_type = 0xF: return max legal value of counter; counter wraps-around to 0 when exceeding this value\;\;\;Reserved for other commands" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="sl_bitmask" descr="This field allows to apply to specific SLs based on the bitmask. When a bit is set, it&apos;s index SL shall be configured." access="RW" offset="0x18.0" size="0x0.16" />
	<field name="prm" descr="When cmd_type = 0x5 / 0xF:\;0-param / counter is read-only\;1-param / counter is read-write\;2-param / counter is read-only but may also be accessed and cleared via &quot;get &amp; clear&quot; command\;Reserved for other commands" access="RO" offset="0x1C.0" size="0x0.2" />
	<field name="sl_bitmask_support" descr="Indicates whether the device supports sl_bitmask logic" access="RO" offset="0x1C.2" size="0x0.1" />
	<field name="counter_en" descr="When set, enables PPC algorithm-specific counters, otherwise they are disabled.\;Each port supports multiple counter groups, up to the number returned by cmd_type=0xE.\;Each counter group is associated with a specific [algo_slot, sl_bitmask]." access="RW" offset="0x1C.3" size="0x0.1" />
	<field name="trace_en" descr="when set, indicates algorithm trace mechanism is enabled. Else, trace is disabled" access="RW" offset="0x1C.4" size="0x0.1" />
	<field name="text_length" descr="Length in bytes of text field\;Valid when cmd_type = 0x0 / 0x5  / 0xA/ 0xB/ 0xC/ 0xD/ 0xF/ 0x10\;Reserved for other commands" access="RW" offset="0x1C.8" size="0x0.8" />
	<field name="counter_group_id" descr="Counter Group ID associated with the algorithm slot.\;If cfg_counter_group_en set, this field assign the counter group ID to the algo_slot.\;The value must be in the range 0 to the value returned by cmd_type=0xE (max counter group ID).\;This field is only applicable if the counter_en bit is set; otherwise, counters are not enabled." access="RW" offset="0x1C.16" size="0x0.4" />
	<field name="cfg_counter_group_en" descr="Counter Group ID configuration enable.\;When set (1): the user configures the counter group ID when enabling the algorithm slot (via PPCC).\;When clear (0): allows the user&apos;s algorithm code to set the counter group ID or default (counter group 0)." access="OP" offset="0x1C.20" size="0x0.1" />
	<field name="text" descr="The layout of this field varies based on command type:\;0x0: algo name, comma,  algo description (ASCII string)\;0x5: param name, comma,  param description (ASCII string)\;0xA: Array of 32 bits parameters, starting from parameter index 0 up to (text_len/4 -1)\;0xB: Array of 32 bits parameters, starting from parameter index 0 up to (text_len/4 -1)\;0xC: Array of 32 bits counters, starting from parameter index 0 up to (text_len/4 -1)\;0xD: Array of 32 bits counters, starting from parameter index 0 up to (text_len/4 -1)\;0xF: counter name, comma,  counter description (ASCII string)\;0x10: array of 32bit Algo info, up to 16 entries, representing which algo id is present per slot. Zero value means algo id is irrelevant.\;Algo Info: algo_id[31:16], algo_major_ver[15:8] algo_minor_ver[7:0]\;All commands are limited by text_len" access="RW" high_bound="54" low_bound="0" offset="0x20.0" size="0xdc.0" />
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
	<field name="plr_outstanding_cells" descr="Number of outstanding cells in PLR buffer" access="RO" offset="0x50.24" size="0x0.8" />
	<field name="plr_rcv_good_codes_high" descr="Number of all the good none sync PLR codewords received.\;This counter provides information on the total number of codewords received by the higher link layer at the output of the PLR correction mechanism." access="RO" offset="0x54.0" size="0x4.0" />
	<field name="plr_rcv_good_codes_low" descr="Number of all the good none sync PLR codewords received.\;This counter provides information on the total number of codewords received by the higher link layer at the output of the PLR correction mechanism." access="RO" offset="0x58.0" size="0x4.0" />
	<field name="plr_tx_codes_loss_high" descr="Transmitted bandwidth loss due to codes retransmission. calculated in resolution of (plr_xmit_retry_codes /plr_xmit_codes)*10^10\;\;Tx BW Loss % = (plr_xmit_retry_codes / plr_xmit_codes)" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="plr_tx_codes_loss_low" descr="Transmitted bandwidth loss due to codes retransmission. calculated in resolution of (plr_xmit_retry_codes /plr_xmit_codes)*10^10\;\;Tx BW Loss % = (plr_xmit_retry_codes / plr_xmit_codes)" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="plr_tx_max_outstanding_cell_high" descr="Counts each time the buffer reaches its maximum size." access="RO" offset="0x64.0" size="0x4.0" />
	<field name="plr_tx_max_outstanding_cell_low" descr="Counts each time the buffer reaches its maximum size." access="RO" offset="0x68.0" size="0x4.0" />
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
	<field name="last_successful_recovery_time" descr="Time in ms of the last successful recovery flow event.\;\;Supported if PCAM.feature_cap_mask bit 124 is set" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="total_successful_recovery_time" descr="Total time in ms of each of the recovery types from all of the recovery flows that happened. \;Accumulative between link flaps\;\;Supported if PCAM.feature_cap_mask bit 124 is set" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="last_Successful_recovery_step_attempts" descr="Valid only when UPHY_recovery_steps enabled, counts number of steps triggered (step1 + step2)\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="last_rs_fec_uncorrectable_during_recovery_high" descr="Number of uncorrectable RS-FEC blocks received on port, during the last recovery flow event.\;\;Supported if PCAM.feature_cap_mask bit 125 is set" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="last_rs_fec_uncorrectable_during_recovery_low" descr="Number of uncorrectable RS-FEC blocks received on port, during the last recovery flow event.\;\;Supported if PCAM.feature_cap_mask bit 125 is set" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="total_rs_fec_uncorrectable_during_recovery_high" descr="Number of uncorrectable RS-FEC blocks received on port during recovery, accumulative on all recovery events between link flap.\;Supported if PCAM.feature_cap_mask bit 125 is set" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="total_rs_fec_uncorrectable_during_recovery_low" descr="Number of uncorrectable RS-FEC blocks received on port during recovery, accumulative on all recovery events between link flap.\;Supported if PCAM.feature_cap_mask bit 125 is set" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="wait_for_module_time" descr="time in ms, waited for module rx_output_valid" access="RO" offset="0x7C.0" size="0x4.0" />
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
	<field name="counter_set" descr="Counter set as described in\;Table  1898, &quot;Ethernet IEEE 802.3 Counters Group Data Layout,&quot; on page  2206\;Table  1900, &quot;Ethernet RFC 2863 Counter Group Data Layout,&quot; on page  2210\;Table  1902, &quot;Ethernet RFC 2819 Counter Group Data Layout,&quot; on page  2213\;Table  1904, &quot;Ethernet RFC 3635 Counter Group Data Layout,&quot; on page  2218\;Table  1906, &quot;Ethernet Extended Counter Group Data Layout,&quot; on page  2222\;Table  1909, &quot;Ethernet Discard Counter Group Fields,&quot; on page  2227\;Table  1910, &quot;Ethernet Per Priority Group Data Layout,&quot; on page  2229\;Table  1914, &quot;Ethernet Per Traffic Class Group data layout,&quot; on page  2237\;Table  1926, &quot;Physical Layer Counters Data Layout,&quot; on page  2248\;Table  1916, &quot;Ethernet Per Traffic Class Congestion Group data layout,&quot; on page  2238\;Table  1930, &quot;Physical Layer Statistical Counters Data Layout,&quot; on page  2257\;Table  1922, &quot;InfiniBand PortCounters Attribute Group Data Layout,&quot; on page  2242\;Table  1924, &quot;InfiniBand Extended PortCounters Attribute Group Data Layout,&quot; on page  2244\;Table  1932, &quot;PLR Counters Data Layout,&quot; on page  2263 \;Table  1934, &quot;RS-Histograms Data Layout,&quot; on page  2266\;Table  1938, &quot;InfiniBand Packets Counters Data Layout,&quot; on page  2268\;Table  1940, &quot;InfiniBand General Counters Data Layout,&quot; on page  2271\;Table  1958, &quot;Physical Layer Recovery Counters Group Data Layout,&quot; on page  2303\;Table  1960, &quot;NVLink Reduction Counters Group Layout,&quot; on page  2307" subnode="ppcnt_reg_counter_set_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).grp" />
</node>

<node name="ppcnt_rs_fec_histograms_counters_ext" descr="" size="0xf8.0" >
	<field name="hist" descr="Value of RS-hist\;In order to know bin errors distribution use PPHCR reg." subnode="uint64" access="RO" high_bound="20" low_bound="0" offset="0x0.0" size="0xa8.0" />
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
	<field name="bin_range" descr="Write to bin_range[x] is applicable only if we = 1 &amp; the corresponding bits in bin_range_write_mask is set.\;Mapping of measurement units to a bin.\;See Table  2268, &quot;PPHCR - Port Phy Bin Range Histogram Configuration Layout,&quot; on page  2696" subnode="pphcr_bin_range_ext" access="RW" high_bound="18" low_bound="0" offset="0x10.0" size="0x4c.0" />
</node>

<node name="pplm_nvl6_fec_ext" descr="" size="0x18.0" >
	<field name="nvlink_fec_override_admin_200g_1x_mode_a" descr="200G 1x (200G_1x_Simplex) Mode A - override admin bitmask (one-hot setting):\;0: auto_mode - no override\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x0.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_200g_1x_mode_a" descr="200G 1x (200G_1x_Simplex) Mode A - override capability bitmask:\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x0.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_400g_2x_mode_a" descr="400G 2x (400G_2x_Simplex) Mode A - override admin bitmask (one-hot set\;ting):\;0: auto_mode - no override\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x4.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_400g_2x_mode_a" descr="400G 2x (400G_2x_Simplex) Mode A - override capability bitmask:\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x4.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_400g_2x_mode_b" descr="400G 2x (375G_2x_Bidi) Mode B - override admin bitmask (one-hot setting):\;0: auto_mode - no override\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x8.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_400g_2x_mode_b" descr="400G 2x (375G_2x_Bidi) Mode B - override capability bitmask:\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x8.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_360g_2x_mode_b" descr="360G 2x (337p5G_2x_Bidi) Mode B - override admin bitmask (one-hot setting):\;0: auto_mode - no override\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0xC.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_360g_2x_mode_b" descr="360G 2x (337p5G_2x_Bidi) Mode B - override capability bitmask:\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0xC.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_328g_2x_mode_b" descr="328G 2x (307p5G_2x_Bidi) Mode B - override admin bitmask (one-hot setting):\;0: auto_mode - no override\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x10.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_328g_2x_mode_b" descr="328G 2x (307p5G_2x_Bidi) Mode B - override capability bitmask:\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x10.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_200g_2x_mode_a" descr="200G 2x (200G_2x_Simplex XDR 2x slow) Mode A - override admin bitmask (one-hot setting):\;0: auto_mode - no override\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x14.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_200g_2x_mode_a" descr="200G 2x (200G_2x_Simplex XDR 2x slow) Mode A - override capability bitmask:\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x14.16" size="0x0.16" />
</node>

<node name="pplm_reg_ext" descr="" size="0x80.0" >
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
	<field name="resilink_fec_ind" descr="Valid only for resilink link is operational, otherwise ignored.\;\;When cleared, fec_mode_active will represent the Ethernet equivalent FEC of the resilink protocol.\;\;When set, fec_mode_active will represent the Resilink FEC protocol" access="INDEX" offset="0x0.28" size="0x0.1" />
	<field name="fec_generation" descr="For protocol generations presented as an enum under this field, fec_override_cap &amp; fec_override_admin fields per each supported rate will appear under the fec_page_data field.\;0: NVL6" access="RO" enum="NVL6=0x0" offset="0x4.0" size="0x0.4" />
	<field name="plr_margin_th_support" descr="Supported PLR margin thresholds capability bitmask:\;Bit 0: PLR margin threshold 0 supported\;Bit 1: PLR margin threshold 1 supported\;Bit 2: PLR margin threshold 2 supported\;Bit 3: PLR margin threshold 3 supported\;Bit 4: PLR margin threshold 4 supported\;Bit 5: PLR margin threshold 5 supported\;Bit 6: PLR margin threshold 6 supported\;Bit 7: PLR margin threshold 7 supported\;" access="RO" offset="0x4.9" size="0x0.8" />
	<field name="tx_crc_plr_support" descr="Supported tx CRC over PLR capability\;0: not supported\;1: supported" access="RO" offset="0x4.18" size="0x0.1" />
	<field name="plr_reject_mode_support" descr="Supported PLR reject modes capability bitmask:\;Bit 0: rejection_based_on_plr_margin\;Bit 1: rejection_based_on_crc_and_cs\;Bit 2: rejection_based_on_CS\;Bit 3: reserved" access="RO" offset="0x4.19" size="0x0.4" />
	<field name="plr_reject_mode_oper" descr="This is the operational value:\;0: rejection_based_on_plr_margin\;1: rejection_based_on_crc_and_cs\;2: rejection_based_on_CS\;3: reserved" access="RO" offset="0x4.25" size="0x0.2" />
	<field name="tx_crc_plr_oper" descr="This is the operational value. When set tx CRC over PLR is enabled" access="RO" offset="0x4.27" size="0x0.1" />
	<field name="plr_margin_th_oper" descr="This is the operational value.\;PLR margin threshold in which a codeword is retransmitted" access="RO" offset="0x4.28" size="0x0.4" />
	<field name="fec_mode_active" descr="Active FEC (bitmask)\;For each enum, a short prefix for tools is presented in the row below.\;0: No_FEC \;1: Firecode_FEC\;FC_FEC\;2: Standard_RS_FEC - RS(528,514)\;KR4_FEC\;3: Standard_LL_RS_FEC - RS(271,257)\;LL_FEC\;4: Interleaved_Quad_RS_FEC - (544,514)  \;Quad_KP4_FEC\;5: Interleaved_Quad_RS_FEC_PLR - (546,516) \;Quad_KP4_FEC\;6: Interleaved_Standard_RS-FEC - (544,514)\;Int_KP4_FEC\;7: Standard_RS-FEC - (544,514)\;KP4_FEC\;8: Interleaved_Octet_RS_FEC_PLR - (546,516) \;Octet_KP4_FEC\;9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;ELL_FEC\;10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - (272,257+1)\;Int_ELL_FEC\;11: Interleaved_Standard_RS_FEC_PLR - (544,514) \;Int_KP4_FEC_PLR\;12: RS-FEC - (544,514) + PLR\;KP4_FEC_PLR\;13: LL-FEC - (271,257) + PLR\;LL_FEC_PLR\;14: Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal] \;ELL_FEC_PLR\;15: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]\;Int_ELL_FEC_PLR" access="RO" enum="No_FEC=0x0,Firecode_FEC=0x1,Standard_RS_FEC=0x2,Standard_LL_RS_FEC=0x3,Interleaved_Quad_RS_FEC=0x4,Interleaved_Quad_RS_FEC_PLR=0x5,Interleaved_Standard_RS=0x6,Standard_RS=0x7,Interleaved_Octet_RS_FEC_PLR=0x8,Ethernet_Consortium_LL_50G_RS_FEC=0x9,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC=0xa,Interleaved_Standard_RS_FEC_PLR=0xb,RS=0xc,LL=0xd,Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xe,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xf" offset="0xC.0" size="0x0.24" />
	<field name="plr_reject_mode" descr="This is the admin value:\;0: rejection_based_on_plr_margin\;1: rejection_based_on_crc_and_cs\;2: rejection_based_on_CS\;3: reserved\;set value is used only if both plr_vld and plr_reject_mode_vld are set, else configure to default value" access="RW" offset="0xC.24" size="0x0.2" />
	<field name="tx_crc_plr" descr="This is the admin value. When set, tx CRC over PLR is enabled.\;Set value is used only if both plr_vld and tx_crc_plr_vld are set, else configure to default value.\;In addition, the set value has to be &apos;1&apos; if the value in plr_reject_mode is rejection_based_on_crc_and_cs, and this is the only case where setting the value to &apos;1&apos; is valid." access="RW" offset="0xC.27" size="0x0.1" />
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
	<field name="fec_override_cap_800g_4x" descr="800GE, 4 lane FEC override capability bitmask:\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x58.0" size="0x0.16" />
	<field name="fec_override_cap_1600g_8x" descr="1600GE, 8 lane FEC override capability bitmask:\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x58.16" size="0x0.16" />
	<field name="fec_override_cap_200g_1x" descr="200GE, 1 lane FEC override capability bitmask:\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x5C.0" size="0x0.16" />
	<field name="fec_override_cap_400g_2x" descr="400GE, 2 lane FEC override capability bitmask:\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x5C.16" size="0x0.16" />
	<field name="fec_override_admin_800g_4x" descr="800GE, 4 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x60.0" size="0x0.16" />
	<field name="fec_override_admin_1600g_8x" descr="1600GE, 8 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x60.16" size="0x0.16" />
	<field name="fec_override_admin_200g_1x" descr="200GE, 1 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x64.0" size="0x0.16" />
	<field name="fec_override_admin_400g_2x" descr="400GE, 2 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x64.16" size="0x0.16" />
	<field name="fec_page_data" descr="Table  2062, &quot;PPLM - NVL6 Rates FEC Override Layout,&quot; on page  2444" subnode="pplm_reg_fec_page_data_auto_ext" access="RW" offset="0x68.0" size="0x18.0" union_selector="$(parent).fec_generation" />
</node>

<node name="pplm_reg_fec_page_data_auto_ext" descr="" attr_is_union="1" size="0x18.0" >
	<field name="pplm_nvl6_fec_ext" descr="" subnode="pplm_nvl6_fec_ext" offset="0x0.0" selected_by="NVL6" size="0x18.0" />
</node>

<node name="pplr_reg_ext" descr="" size="0x8.0" >
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: Near_End_Port- (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: Far_End_Port - (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" enum="Network_Port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="op_mod" descr="operational mode for link configurations for phy_ local_loopback mode.\;0 - link will operate in optimal latency performance mode\;1 - link will operate in same configurations as operational port.\;\;Note: for FEC override via PPLM register, chosen FEC will be according to the PPLM configuration that was set and this bit will be ignored for FEC purposes" access="OP" offset="0x0.8" size="0x0.1" />
	<field name="apply_im" descr="Apply immediate: When set, the enabled/disabled loopback will be set immediately even if link is active.\;Note: Currently supported only for Bit 7: LL_local_loopback. in other loopbacks will be ignored" access="OP" offset="0x0.9" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lb_en" descr="Loopback enable - only one bit shall be set.\;Bit 0: Phy_remote_loopback\;Bit 1: Phy_local_loopback\;Bit 2: External_local_loopback\;Bit 7: LL_local_loopback\;\;" access="RW" enum="Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4,LL_local_loopback=0x80" offset="0x4.0" size="0x0.12" />
	<field name="lb_cap" descr="Loopback capability - bitmask\;Bit 0: Phy_remote_loopback\;Bit 1: Phy_local_loopback - When set the port&apos;s egress traffic is looped back to the receiver and the port transmitter is disabled.\;Bit 2: External_local_loopback - Enables the port&apos;s transmitter to link with the port&apos;s receiver using an external loopback connector.\;Bit 4: Near_end_digital_loopback - [Internal]\;Bit 7: LL_local_loopback - When set the port&apos;s egress Link layer traffic is looped back to the receiver. Physical port in this loopback mode is down.\;\;Notes \;1. Phy remote loopback can be supported only for lane rate higher than 25Gbuad in the 16nm devices.\;3. In Ethernet, when LL_Local_loopback is set and physical link is not down, physical state may reach only up to Phy Up state and forced to send Local Faults. When released link may transition to LinkUp state.\;" access="RO" enum="Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4,LL_local_loopback=0x80" offset="0x4.16" size="0x0.12" />
	<field name="lb_cap_mode_idx" descr="Supported only when indicated by PCAM Bit 97:PPLR.lb_cap_mode_idx. The returned value of the &apos;lp_cap&apos; capability field will be according to the selected mode index:\;0: Operational_mode\;1: Test_mode" access="INDEX" enum="Operational_mode=0x0,Test_mode=0x1" offset="0x4.30" size="0x0.1" />
</node>

<node name="pprm_phy_steps_ext" descr="" size="0x68.0" >
	<field name="step1_preset_support_mask" descr="Bitmask of supported preset for step1/2\;\;Bit 0: PEQ_only\;Bit 1: CDR_toggle\;Bit 2: full_duplex_EQ\;Bit 3: Logic_lock_only" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="step2_preset_support_mask" descr="Bitmask of supported preset for step1/2\;\;Bit 0: PEQ_only\;Bit 1: CDR_toggle\;Bit 2: full_duplex_EQ\;Bit 3: Logic_lock_only" access="RO" enum="PEQ_only=0x1,CDR_toggle=0x2,full_duplex_EQ=0x4,Logic_lock_only=0x8" offset="0x0.12" size="0x0.8" />
	<field name="eff_align_aq_time" descr="64ns granularity\;time to stabilize effective align acquired\;0:" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="step1_preset_admin" descr="Admin for requested preset during negotiation for step1/2\;\;0: FW_default\;1: PEQ_only\;2: CDR_toggle\;3: full_duplex_EQ\;4: Logic_lock_only\;0xF: no_request - skip step" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="step2_preset_admin" descr="Admin for requested preset during negotiation for step1/2\;\;0: FW_default\;1: PEQ_only\;2: CDR_toggle\;3: full_duplex_EQ\;4: Logic_lock_only\;0xF: no_request - skip step" access="RW" enum="FW_default=0x0,PEQ_only=0x1,CDR_toggle=0x2,full_duplex_EQ=0x3,Logic_lock_only=0x4,no_request=0xf" offset="0x4.8" size="0x0.4" />
	<field name="step2_time_gran" descr="Affects granularity of all timers and timeouts of step2 fields:\;\;step2_state_65_to_66_time, step2_state_66_to_67_time, step2_state_67_to_68_time, step2_state_60_timeout, step2_state_61_timeout, step2_state_62_timeout, step2_state_60_to_linkup_timeout\;\;0: 1us\;1: 10us\;2: 100us" access="RO" offset="0x4.28" size="0x0.2" />
	<field name="step1_state_65_to_66_time_pre1" descr="1us / step2_time_gran granularity for preset 1 (PEQ only)\;Time for state transition 0x65  to 0x66\;0: FW_default" access="RW" offset="0x8.0" size="0x0.10" />
	<field name="step2_state_65_to_66_time_pre1" descr="1us / step2_time_gran granularity for preset 1 (PEQ only)\;Time for state transition 0x65  to 0x66\;0: FW_default" access="RW" offset="0x8.10" size="0x0.10" />
	<field name="step1_peq_n_retry_pre1" descr="Number of PEQ to do in state 0x68 for preset 1 (PEQ only)\;0: FW_default\;1-15: &lt;N&gt; PEQ retries\;16-30: reserved\;31: skip_state_0x68" access="RW" offset="0x8.20" size="0x0.5" />
	<field name="step2_peq_n_retry_pre1" descr="Number of PEQ to do in state 0x68 for preset 1 (PEQ only)\;0: FW_default\;1-15: &lt;N&gt; PEQ retries\;16-30: reserved\;31: skip_state_0x68" access="RW" offset="0x8.26" size="0x0.5" />
	<field name="step1_state_66_to_67_time_pre1" descr="1us / step2_time_gran granularity for preset 1 (PEQ only)\;Time for state transition 0x66to 0x67\;0: FW_default" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="step2_state_66_to_67_time_pre1" descr="1us / step2_time_gran granularity for preset 1 (PEQ only)\;Time for state transition 0x66to 0x67\;0: FW_default" access="RW" offset="0xC.16" size="0x0.16" />
	<field name="step1_state_67_to_68_time_pre1" descr="1us / step2_time_gran granularity for preset 1 (PEQ only)\;Time for state transition 0x66  to 0x67\;0: FW_default" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="step2_state_67_to_68_time_pre1" descr="1us / step2_time_gran granularity for preset 1 (PEQ only)\;Time for state transition 0x66  to 0x67\;0: FW_default" access="RW" offset="0x10.16" size="0x0.16" />
	<field name="step1_state_60_timeout" descr="1us / step2_time_gran granularity.\;Watchdog timeout for state 0x60 \;0: FW_default" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="step2_state_60_timeout" descr="1us / step2_time_gran granularity.\;Watchdog timeout for state 0x60 \;0: FW_default" access="RW" offset="0x14.16" size="0x0.16" />
	<field name="step1_state_61_timeout" descr="1us / step2_time_gran granularity. \;Watchdog timeout for state 0x61 \;0: FW_default\;" access="RW" offset="0x18.0" size="0x0.16" />
	<field name="step2_state_61_timeout" descr="1us / step2_time_gran granularity. \;Watchdog timeout for state 0x61 \;0: FW_default\;" access="RW" offset="0x18.16" size="0x0.16" />
	<field name="step1_state_62_timeout" descr="1us / step2_time_gran granularity. \;Watchdog timeout for state 0x62 \;0: FW_default\;" access="RW" offset="0x1C.0" size="0x0.16" />
	<field name="step2_state_62_timeout" descr="1us / step2_time_gran granularity. \;Watchdog timeout for state 0x62 \;0: FW_default\;" access="RW" offset="0x1C.16" size="0x0.16" />
	<field name="step2_state_60_to_linkup_timeout_oper" descr="10us granularity. \;Watchdog timeout for states 0x60 to 0x62 after negotiation agreement" access="RO" offset="0x20.0" size="0x0.16" />
	<field name="step2_state_60_to_linkup_timeout" descr="10us granularity. \;Watchdog timeout for states 0x60 to 0x62" access="RW" offset="0x20.16" size="0x0.16" />
	<field name="step1_preset_oper" descr="0x0: no_request - skip step\;1: PEQ_only\;2: CDR_toggle\;3: full_duplex_EQ\;4: Logic_lock_only" access="RO" offset="0x24.0" size="0x0.4" />
	<field name="step2_preset_oper" descr="0x0: no_request - skip step\;1: PEQ_only\;2: CDR_toggle\;3: full_duplex_EQ\;4: Logic_lock_only" access="RO" offset="0x24.8" size="0x0.4" />
	<field name="step1_peq_n_retry_oper" descr="Agreed peq N retry in state 0x68\;1-15: &lt;N&gt; PEQ retries\;16-30: reserved\;31: skip_state_0x68" access="RO" offset="0x24.16" size="0x0.5" />
	<field name="step2_peq_n_retry_oper" descr="Agreed peq N retry in state 0x68\;1-15: &lt;N&gt; PEQ retries\;16-30: reserved\;31: skip_state_0x68" access="RO" offset="0x24.24" size="0x0.5" />
	<field name="step1_state_65_to_66_time_oper" descr="1us / step2_time_gran granularity. \;Time for state transition 0x65  to 0x66\;0: FW_default" access="RO" offset="0x28.0" size="0x0.10" />
	<field name="step2_state_65_to_66_time_oper" descr="1us / step2_time_gran granularity. \;Time for state transition 0x65  to 0x66\;0: FW_default" access="RO" offset="0x28.10" size="0x0.10" />
	<field name="step1_state_66_to_67_time_oper" descr="1us / step2_time_gran granularity. \;Time for state transition 0x66to 0x67\;0: FW_default" access="RO" offset="0x2C.0" size="0x0.16" />
	<field name="step2_state_66_to_67_time_oper" descr="1us / step2_time_gran granularity. \;Time for state transition 0x66to 0x67\;0: FW_default" access="RO" offset="0x2C.16" size="0x0.16" />
	<field name="step1_state_67_to_68_time_oper" descr="1us / step2_time_gran granularity. \;Time for state transition 0x66  to 0x67\;0: FW_default" access="RO" offset="0x30.0" size="0x0.16" />
	<field name="step2_state_67_to_68_time_oper" descr="1us / step2_time_gran granularity. \;Time for state transition 0x66  to 0x67\;0: FW_default" access="RO" offset="0x30.16" size="0x0.16" />
	<field name="step1_state_60_timeout_oper" descr="1us / step2_time_gran granularity. \;Watchdog timeout for state 0x60 \;0: FW_default" access="RO" offset="0x34.0" size="0x0.16" />
	<field name="step2_state_60_timeout_oper" descr="1us / step2_time_gran granularity. \;Watchdog timeout for state 0x60 \;0: FW_default" access="RO" offset="0x34.16" size="0x0.16" />
	<field name="step1_state_61_timeout_oper" descr="1us / step2_time_gran granularity. \;Watchdog timeout for state 0x61 \;0: FW_default" access="RO" offset="0x38.0" size="0x0.16" />
	<field name="step2_state_61_timeout_oper" descr="1us / step2_time_gran granularity. \;Watchdog timeout for state 0x61 \;0: FW_default" access="RO" offset="0x38.16" size="0x0.16" />
	<field name="step1_state_62_timeout_oper" descr="1us / step2_time_gran granularity. \;Watchdog timeout for state 0x62 \;0: FW_default" access="RO" offset="0x3C.0" size="0x0.16" />
	<field name="step2_state_62_timeout_oper" descr="1us / step2_time_gran granularity. \;Watchdog timeout for state 0x62 \;0: FW_default" access="RO" offset="0x3C.16" size="0x0.16" />
	<field name="step1_state_65_to_66_time_pre2" descr="1us / step2_time_gran granularity for preset 2 (CDR toggle)\;Time for state transition 0x65  to 0x66\;0: FW_default" access="RW" offset="0x48.0" size="0x0.10" />
	<field name="step2_state_65_to_66_time_pre2" descr="1us / step2_time_gran granularity for preset 2 (CDR toggle)\;Time for state transition 0x65  to 0x66\;0: FW_default" access="RW" offset="0x48.10" size="0x0.10" />
	<field name="step1_peq_n_retry_pre2" descr="Number of PEQ to do in state 0x68 for preset 2 (CDR toggle)\;0: FW_default\;1-15: &lt;N&gt; PEQ retries\;16-30: reserved\;31: skip_state_0x68" access="RW" offset="0x48.20" size="0x0.5" />
	<field name="step2_peq_n_retry_pre2" descr="Number of PEQ to do in state 0x68 for preset 2 (CDR toggle)\;0: FW_default\;1-15: &lt;N&gt; PEQ retries\;16-30: reserved\;31: skip_state_0x68" access="RW" offset="0x48.26" size="0x0.5" />
	<field name="step1_state_66_to_67_time_pre2" descr="1us / step2_time_gran granularity for preset 2 (CDR toggle)\;Time for state transition 0x66to 0x67\;0: FW_default" access="RW" offset="0x4C.0" size="0x0.16" />
	<field name="step2_state_66_to_67_time_pre2" descr="1us / step2_time_gran granularity for preset 2 (CDR toggle)\;Time for state transition 0x66to 0x67\;0: FW_default" access="RW" offset="0x4C.16" size="0x0.16" />
	<field name="step1_state_67_to_68_time_pre2" descr="1us / step2_time_gran granularity for preset 2 (CDR toggle)\;Time for state transition 0x66  to 0x67\;0: FW_default" access="RW" offset="0x50.0" size="0x0.16" />
	<field name="step2_state_67_to_68_time_pre2" descr="1us / step2_time_gran granularity for preset 2 (CDR toggle)\;Time for state transition 0x66  to 0x67\;0: FW_default" access="RW" offset="0x50.16" size="0x0.16" />
	<field name="step1_state_65_to_66_time_pre3" descr="1us / step2_time_gran granularity for preset 3 (Full duplex)\;Time for state transition 0x65  to 0x66\;0: FW_default" access="RW" offset="0x54.0" size="0x0.10" />
	<field name="step2_state_65_to_66_time_pre3" descr="1us / step2_time_gran granularity for preset 3 (Full duplex)\;Time for state transition 0x65  to 0x66\;0: FW_default" access="RW" offset="0x54.10" size="0x0.10" />
	<field name="step1_peq_n_retry_pre3" descr="Number of PEQ to do in state 0x68 for preset 3 (Full duplex)\;0: FW_default\;1-15: &lt;N&gt; PEQ retries\;16-30: reserved\;31: skip_state_0x68" access="RW" offset="0x54.20" size="0x0.5" />
	<field name="step2_peq_n_retry_pre3" descr="Number of PEQ to do in state 0x68 for preset 3 (Full duplex)\;0: FW_default\;1-15: &lt;N&gt; PEQ retries\;16-30: reserved\;31: skip_state_0x68" access="RW" offset="0x54.26" size="0x0.5" />
	<field name="step1_state_66_to_67_time_pre3" descr="1us / step2_time_gran granularity for preset 3 (Full duplex)\;Time for state transition 0x66to 0x67\;0: FW_default" access="RW" offset="0x58.0" size="0x0.16" />
	<field name="step2_state_66_to_67_time_pre3" descr="1us / step2_time_gran granularity for preset 3 (Full duplex)\;Time for state transition 0x66to 0x67\;0: FW_default" access="RW" offset="0x58.16" size="0x0.16" />
	<field name="step1_state_67_to_68_time_pre3" descr="1us / step2_time_gran granularity for preset 3 (Full duplex)\;Time for state transition 0x66  to 0x67\;0: FW_default" access="RW" offset="0x5C.0" size="0x0.16" />
	<field name="step2_state_67_to_68_time_pre3" descr="1us / step2_time_gran granularity for preset 3 (Full duplex)\;Time for state transition 0x66  to 0x67\;0: FW_default" access="RW" offset="0x5C.16" size="0x0.16" />
</node>

<node name="pprm_reg_ext" descr="" size="0x94.0" >
	<field name="ovrd_no_neg_bhvr" descr="Defines the behavior of no_neg_bhvr field.\;0: ingore_no_neg_bhvr_field - stay with current configured behaivour\;1: no_neg_behavior_according_to_fw_defult - ignore no_neg_bhvr set, and set FW default for the behavior\;2: no_neg_behavior_according_to_no_neg_bhvr_field - set behavior according to configured no_neg_bhvr field" access="RW" offset="0x0.2" size="0x0.2" />
	<field name="wait_for_module_cap" descr="When set, wait_for_module supported " access="RO" offset="0x0.6" size="0x0.1" />
	<field name="recovery_go_once_cap" descr="When set, recovery_go_once is supported and configurable." access="RO" offset="0x0.7" size="0x0.1" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="recovery_go_once" descr="Valid only when recovery_go_once_cap is set.\;When set, will trigger recovery flow according to the configured recovery paramters set in this register." access="WO" offset="0x0.27" size="0x0.1" />
	<field name="param_select" descr="Selects which recovery parameters is selected in param_page_data.\;0: no_param_select\;1: phy_recovery_steps\;\;Note - valid only if recovery type is also supported in recovery_types_cap." access="INDEX" enum="no_param_select=0x0,phy_recovery_steps=0x1" offset="0x0.28" size="0x0.4" />
	<field name="recovery_types_cap" descr="Recovery types that are supported by device.\;Bit 0: host_logic_re_lock\;Bit 1: host_serdes_feq\;Bit 2: module_tx_disable\;Bit 3: module_datapath_full_toggle\;Bit 4: phy_recovery_steps" access="RO" enum="host_logic_re_lock=0x1,host_serdes_feq=0x2,module_tx_disable=0x4,module_datapath_full_toggle=0x8,phy_recovery_steps=0x10" offset="0x4.0" size="0x0.8" />
	<field name="no_neg_bhvr" descr="Relevant only if ovrd_no_neg_bhvr is set to &apos;2&apos;, ignored otherwise\;In case of no negotiation happened during link up flow, defines the behavior of enabled recovery types:\;Bit 0: host_logic_re_lock\;Bit 1: host_serdes_feq\;Bit 2-3: reserved\;\;0: Disaled\;1: Enabled" access="RW" enum="host_logic_re_lock=0x1,host_serdes_feq=0x2,Disaled=0x0,Enabled=0x1" offset="0x4.24" size="0x0.4" />
	<field name="wd_logic_re_lock_res" descr="time resolution for wd_time_host_logic_re_lock field.\;0: 1ms\;1: 10ms\;2: 100ms\;3: 1 sec" access="RW" offset="0x4.28" size="0x0.2" />
	<field name="oper_logic_re_lock_res" descr="time resolution for oper_time_host_logic_re_lock field.\;0: 1ms\;1: 10ms\;2: 100ms\;3: 1 sec" access="RO" offset="0x4.30" size="0x0.2" />
	<field name="module_datapath_full_toggle" descr="Admin Configurations per recovery type.\;Recovery types:\;1. Host Logic re_lock - Physical layer alignment re-lock\;2. Host SerDes Full EQ \;3. Module Tx Disable - Toggle module optical laser to off--&gt;on. supported only on optical modules that support TxDisable command\;4. Full module Toggle - Re-initialization of CMIS module DPSM.\;\;0: FW_default\;1: Enable\;2: Disable\;3: Disable_Support_in_Negotiation\;\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="module_tx_disable" descr="Admin Configurations per recovery type.\;Recovery types:\;1. Host Logic re_lock - Physical layer alignment re-lock\;2. Host SerDes Full EQ \;3. Module Tx Disable - Toggle module optical laser to off--&gt;on. supported only on optical modules that support TxDisable command\;4. Full module Toggle - Re-initialization of CMIS module DPSM.\;\;0: FW_default\;1: Enable\;2: Disable\;3: Disable_Support_in_Negotiation\;\;" access="RW" offset="0x8.4" size="0x0.4" />
	<field name="host_serdes_feq" descr="Admin Configurations per recovery type.\;Recovery types:\;1. Host Logic re_lock - Physical layer alignment re-lock\;2. Host SerDes Full EQ \;3. Module Tx Disable - Toggle module optical laser to off--&gt;on. supported only on optical modules that support TxDisable command\;4. Full module Toggle - Re-initialization of CMIS module DPSM.\;\;0: FW_default\;1: Enable\;2: Disable\;3: Disable_Support_in_Negotiation\;\;" access="RW" offset="0x8.8" size="0x0.4" />
	<field name="host_logic_re_lock" descr="Admin Configurations per recovery type.\;Recovery types:\;1. Host Logic re_lock - Physical layer alignment re-lock\;2. Host SerDes Full EQ \;3. Module Tx Disable - Toggle module optical laser to off--&gt;on. supported only on optical modules that support TxDisable command\;4. Full module Toggle - Re-initialization of CMIS module DPSM.\;\;0: FW_default\;1: Enable\;2: Disable\;3: Disable_Support_in_Negotiation\;\;" access="RW" offset="0x8.12" size="0x0.4" />
	<field name="phy_recovery_steps" descr="Admin Configurations per recovery type.\;Recovery types:\;1. Host Logic re_lock - Physical layer alignment re-lock\;2. Host SerDes Full EQ \;3. Module Tx Disable - Toggle module optical laser to off--&gt;on. supported only on optical modules that support TxDisable command\;4. Full module Toggle - Re-initialization of CMIS module DPSM.\;\;0: FW_default\;1: Enable\;2: Disable\;3: Disable_Support_in_Negotiation\;\;" access="RW" enum="FW_default=0x0,Enable=0x1,Disable=0x2,Disable_Support_in_Negotiation=0x3" offset="0x8.16" size="0x0.4" />
	<field name="link_down_timeout" descr="Desired time in 0 mSec granularity from start of the recovery process until port announces port down.\;value of 0, means that port will announce port down immediately, and will try &quot;recovery&quot; types when port is down.\;Value of 0xFFFFFF means all recovery types allowed will be tried (if agreed) before port announces down" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="link_down_timeout_oper" descr="operational time in 10 mSec granularity from start of the recovery process until port announces port down after negotiation agreed on both sides" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="draining_timeout" descr="Time in mSec from start of the recovery process until port draining starts (and if port is still in &quot;LinkUp&quot;). \;Value of 0 means draining is disabled.\;Default value of 100mSec" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="delay_on_module_read" descr="ms delay before module check, to allow module status update\;\;0: FW_default -" access="RW" offset="0x14.16" size="0x0.8" />
	<field name="wait_for_module" descr="When enabled, host waits with recovery algorithm until module electrical output towards host indicates valid output.\;When disabled, host starts recovery algorithm immediatly on trigger.\;\;0: FW_default\;1: wait_for_module_en\;2: wait_for_module_dis\;3: force_module_recovery_on_host_failure" access="RW" offset="0x14.26" size="0x0.2" />
	<field name="oper_recovery" descr="Bitmask of agreed and operational recovery modes.\;Prior to negotiation and linkup value will be 0.\;Bit 0: host_logic_re_lock\;Bit 1: host_serdes_feq\;Bit 2: module_tx_disable\;Bit 3: module_datapath_full_toggle\;Bit 4: phy_recovery_steps" access="RO" enum="host_logic_re_lock=0x1,host_serdes_feq=0x2,module_tx_disable=0x4,module_datapath_full_toggle=0x8,phy_recovery_steps=0x10" offset="0x18.0" size="0x0.8" />
	<field name="wd_module_full_toggle" descr="500ms granularity for watchdog timer in Module full toggle recovery\;0: FW default - valid for set only\;on GET operation, returns watchdog value requested" access="RW" offset="0x1C.0" size="0x0.8" />
	<field name="wd_module_tx_disable" descr="100ms granularity for watchdog timer in Module Tx Disable recovery\;0: FW default - valid for set only\;on GET operation, returns watchdog value requested" access="RW" offset="0x1C.8" size="0x0.8" />
	<field name="wd_host_serdes_feq" descr="10ms granularity for watchdog timer in host FEQ recovery\;0: FW default - valid for set only\;on GET operation, returns watchdog value requested" access="RW" offset="0x1C.16" size="0x0.8" />
	<field name="wd_host_logic_re_lock" descr="granularity of wd_logic_re_lock_res for watchdog timer in host re_lock recovery\;0: FW default - valid for set only\;on GET operation, returns watchdog value requested" access="RW" offset="0x1C.24" size="0x0.8" />
	<field name="oper_time_module_full_toggle" descr="500ms granularity for operational timer in Module full toggle recovery\;on GET operation, returns watchdog value requested" access="RO" offset="0x20.0" size="0x0.8" />
	<field name="oper_time_module_tx_disable" descr="100ms granularity for operational timer in Module Tx Disable recovery\;on GET operation, returns watchdog value requested" access="RO" offset="0x20.8" size="0x0.8" />
	<field name="oper_time_host_serdes_feq" descr="10ms granularity for operational timer in host FEQ recovery\;on GET operation, returns watchdog value requested" access="RO" offset="0x20.16" size="0x0.8" />
	<field name="oper_time_host_logic_re_lock" descr="granularity of oper_logic_re_lock_res for operational timer in host Re-lock recovery\;on GET operation, returns watchdog value requested" access="RO" offset="0x20.24" size="0x0.8" />
	<field name="param_page_data" descr="recovery parameters for read / write functionality\;see Table  1988, &quot;PPRM phy recovery steps params,&quot; on page  2340" subnode="pprm_reg_param_page_data_auto_ext" access="RW" offset="0x2C.0" size="0x68.0" union_selector="$(parent).param_select" />
</node>

<node name="pprm_reg_param_page_data_auto_ext" descr="" attr_is_union="1" size="0x68.0" >
	<field name="pprm_phy_steps_ext" descr="" subnode="pprm_phy_steps_ext" offset="0x0.0" selected_by="phy_recovery_steps" size="0x68.0" />
</node>

<node name="pprt_reg_ext" descr="" size="0x24.0" >
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):\;0 - No per lane configuration\;1 - Per lane configurations\;When le is cleared, lane index is reserved and all PPRT configurations are taking place on all lanes.\;When le is set, configurations are taking place per lane based on lane index" access="OP" offset="0x0.0" size="0x0.1" />
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
	<field name="s" descr="start tuning:\;1 - start RX_tuning based on PRBS pattern \;Notes:\;1) assuming peer transmitting PRBS. \;2) cannot be set when prbs_rx_tuning_status = 1 (during tuning).\;3) In Mode B rates, it is not required to set this bit in the first initialization of test mode after PAOS was set to down. For any re-tuning after initialization it is required to set this bit." access="OP" offset="0x0.30" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:\;0 - PRBS RX is disabled.\;1 - PRBS RX is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23A (x^23 + x^18 + 1)\;Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)\;Bit 13 - Square_wave : Non error based tune\;Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;Bit 21- SSPR\;Bit 22- SSPRQ\;Bit 23- LT frames (KR-startup frames)\;Bit 24 - PRBS15 - x^15 + x^14 + 1\;Bit 25 - PRBS28 - x^28 + x^25 + 1\;Bit 26 - Square wave3 (3ones, 3zeros)\;Bit 27 - Square wave13 (13ones, 13zeros)\;Bit 28 - Square wave30 (30ones, 30zeros)\;Bit 29 - PRBS58 (x^58+ x^39 + 1)\;Bit 30 - Default Pattern - Recommended for Mode B links for simplicity" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 13):\;0 - NRZ test pattern\;1 - PAM4 encoding [internal] with gray no precoding\;2 - PAM4 with precoding [internal] with gray\;3 - PAM4 without gray no precoding\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="otf_ch_cap" descr="When set, On the fly configuration change is supported.\;otherwise, change of any configuration requires PAOS toggle.\;Configurations that are supported when bit is set:\;S\;P ( PRBS polarity)\;SW (MSB &lt;-&gt; LSB swap)\;Prbs_mode_admin (pattern)\;msb_lsb_cnt\;Ph_p (physical polarity)\;Modulation (precoding, gray and modulation)\;prbs_hist_fec_int\;Prbs_hist_en" access="RO" offset="0x8.15" size="0x0.1" />
	<field name="primary_secondary_idx" descr="0: primary\;1: secondary \;\;\;" access="INDEX" enum="primary=0x0,secondary=0x1" offset="0x8.20" size="0x0.1" />
	<field name="mode_b_idx" descr="0: mode_a - [Internal] Simplex\;1: mode_b - [Internal] Bidirectional\;2: mode_b_loopback - must set this value when configuring a loopback with a mode B rate [Internal] Bidirectional loopback" access="INDEX" offset="0x8.22" size="0x0.2" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23A (x^23 + x^18 + 1)\;0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0xC - IDLEs using scramble58 (x^58+ x^39 + 1)\;0xD - Square_wave : Non error based tune \;0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;0x15 - SSPR\;0x16 - SSPRQ\;0x17 - LT frames (KR-startup frames)\;0x18 - PRBS15 - x^15 + x^14 + 1\;0x19 - PRBS28 - x^28 + x^25 + 1\;0x1A - Square wave3 (3ones, 3zeros)\;0x1B - Square wave13 (13ones, 13zeros)\;0x1C - Square wave30 (30ones, 30zeros)\;0x1D - PRBS58 (x^58+ x^39 + 1)\;0x1E - Default Pattern - Recommended for Mode B links for simplicity\;\;\;" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s) / Gen 1 PCIe (2.5 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) / Gen 2 PCIe (5 Gb/s)\;Bit 2 - XAUI/2.5GE (3.125 Gb/s) / Gen 3 PCIe (8 Gb/s)\;Bit 3- DDR (5 Gb/s) / Gen 4 PCIe (16 Gb/s)\;Bit 4- QDR (10 Gb/s) / Gen 5 PCIe (32 Gb/s)\;Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)\;Bit 6- FDR (14.0625 Gb/s) \;Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 8 - 50GE-KR4 (12.89 Gb/s) \;Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) \;Bit 10 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;Bit 11 - XDR / NVL6 / 200G_1x_simplex (106.25 Gbd / 212.5 Gb/s)\;Bit 12 - NVL6 / 360G_2x_bidi (90 Gbd / 180 Gb/s)\;Bit 13 - NVL6 / 400G_2x_bidi (100 Gbd / 200 Gb/s)\;Bit 14 - NVL6 / 328G_2x_bidi (82 Gbd / 164 Gb/s)\;Note: PCIe speeds are relevant when pnat = 3 only" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="lane_rate_oper" descr="Lane rate to be used in PRBS, see lane_rate_cap:\;0 - SDR (2.5 Gb/s) / Gen 1 PCIe (2.5 Gb/s)\;1 - DDR (5 Gb/s) / Gen 2 PCIe (5 Gb/s)\;2 - QDR (10 Gb/s)\;3 - FDR10 / 10GE/4 0GE (10.3125 Gb/s) / Gen 3 PCIe (8 Gb/s)\;4 - FDR (14.0625 Gb/s) / Gen 4 PCIe (16 Gb/s)\;5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) / Gen 5 PCIe (32 Gb/s)\;6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s) \;8 - XDR / NVL6 / 200G_1x_simplex (106.25 Gbd / 212.5 Gb/s)\;9 - NVL6 / 360G_2x_bidi (90 Gbd / 180 Gb/s)\;10 - 1GE (1.25 Gb/s)\;11 - XAUI/2.5GE (3.125 Gb/s)\;12 - 50GE-KR4 (12.89 Gb/s)\;13 - NVL6 / 400G_2x_bidi (100 Gbd / 200 Gb/s)\;14 - NVL6 / 328G_2x_bidi (82 Gbd / 164 Gb/s)\;\;Note: All lanes must be set to the same rate.\;Note: PCIe speeds are relevant when pnat = 3 only" access="RW" offset="0x10.16" size="0x0.16" />
	<field name="prbs_lock_status_ext" descr="PRBS lock on PRBS pattern status for lanes 7-4: \;0 - Not locked\;1 - Locked\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0 (Not locked)" access="RO" offset="0x14.20" size="0x0.4" />
	<field name="prbs_lock_status" descr="PRBS lock on PRBS pattern status for lanes 3-0: \;0 - Not locked\;1 - Locked\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0 (Not locked)" access="RO" offset="0x14.24" size="0x0.4" />
	<field name="prbs_rx_tuning_status" descr="Tuning status: \;0 - PRBS mode tuning was not performed.\;1 - Performing PRBS mode tuning.\;2 - PRBS mode tuning completed.\;3 - Signal Detect in progress\;4 - Secondary not detected - this could occur in test mode configured with a Mode B rate if the primary device is configured prior to the secondary\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0." access="RO" offset="0x14.28" size="0x0.4" />
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

<node name="pptb_reg_ext" descr="" size="0xc.0" >
	<field name="pm" descr="prioX_buff mask - enables update of the prioX_buff field.\;Bit i is a flag for updating the mapping for switch priority i." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="um" descr="untagged_buff mask - enables update of the untagged_buff field.\;Reserved for Spectrum family.\;Reserved for HCA devices." access="WO" offset="0x0.8" size="0x0.1" />
	<field name="cm" descr="ctrl_buff mask - enables update of the ctrl_buff field.\;NOTE: This field is ignored by the device, and control traffic is mapped to a pre-defined buffer (buffer - 9).\;Reserved for HCA devices" access="WO" offset="0x0.9" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mm" descr="Mapping mode\;0: Mapping both Unicast and Multicast packets to the same buffer\;In get operation, 0 means Unicast only.\;1: Mapping Unicast only\;2: Mapping Multicast only\;This field is reserved for HCA devices" access="INDEX" offset="0x0.28" size="0x0.2" />
	<field name="prio0buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="prio1buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.4" size="0x0.4" />
	<field name="prio2buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="prio3buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.12" size="0x0.4" />
	<field name="prio4buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.16" size="0x0.4" />
	<field name="prio5buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="prio6buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.24" size="0x0.4" />
	<field name="prio7buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.28" size="0x0.4" />
	<field name="untagged_buff" descr="Mapping of untagged frames to one of the allocated receive port buffers.\;Reserved for Spectrum. Spectrum maps untagged packets based on the Switch Priority.\;Reserved for HCA devices" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="ctrl_buff" descr="Mapping of control frames to one of the allocated receive port buffers.\;NOTE: This field is ignored by the device, and control traffic is mapped to a pre-defined buffer (buffer - 9).\;Reserved for HCA devices" access="RW" offset="0x8.4" size="0x0.4" />
	<field name="pm_msb" descr="prioX_buff mask - enables update of the prioX_buff field.\;Bit i is a flag for updating the mapping for switch priority i+8.\;Reserved for HCA device" access="WO" offset="0x8.24" size="0x0.8" />
</node>

<node name="pptt_reg_ext" descr="" size="0x1c.0" >
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):\;0 - No per lane configuration\;1 - Per lane configurations\;When le is cleared, lane index is reserved and all PPTT configurations are taking place on all lanes.\;When le is set, configurations are taking place per lane based on lane index" access="OP" offset="0x0.0" size="0x0.1" />
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
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23A (x^23 + x^18 + 1)\;Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)\;Bit 13 - Square_wave8 (8 ones, 8 zeros)\;Bit 14 - Square_wave4 (4 ones, 4zeros)\;Bit 15 - Square_wave2 (2 ones, 2zeros)\;Bit 16 - Square_wave1 (one, zero)\;Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;Bit 21- SSPR\;Bit 22- SSPRQ\;Bit 23- LT frames (KR-startup frames)\;Bit 24 - PRBS15 - x^15 + x^14 + 1\;Bit 25 - PRBS28 - x^28 + x^25 + 1\;Bit 26 - Square wave3 (3ones, 3zeros)\;Bit 27 - Square wave13 (13ones, 13zeros)\;Bit 28 - Square wave30 (30ones, 30zeros)\;Bit 29 - PRBS58 (x^58+ x^39 + 1)\;Bit 30 - Default Pattern - Recommended for Mode B links for simplicity\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 13):\;0 - NRZ test pattern\;1 - PAM4 encoding [internal] with gray no precoding\;2 - PAM4 with precoding [internal] with gray\;3 - PAM4 without gray no precoding\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="otf_ch_cap" descr="When set, On the fly configuration change is supported.\;otherwise, change of any configuration requires PAOS toggle.\;Configurations that are supported when bit is set:\;P ( PRBS polarity)\;SW (MSB &lt;-&gt; LSB swap)\;Prbs_mode_admin (PRBS pattern)\;msb_lsb_cnt\;Ph_p (physical polarity)\;Modulation (precoding, gray and modulation)" access="RO" offset="0x8.15" size="0x0.1" />
	<field name="primary_secondary_idx" descr="0: primary\;1: secondary \;" access="INDEX" enum="primary=0x0,secondary=0x1" offset="0x8.20" size="0x0.1" />
	<field name="mode_b_idx" descr="0: mode_a - [Internal] Simplex\;1: mode_b - [Internal] Bidirectional\;2: mode_b_loopback - must set this value when configuring a loopback with a Mode B rate [Internal] Bidirectional loopback" access="INDEX" enum="mode_a=0x0,mode_b=0x1,mode_b_loopback=0x2" offset="0x8.22" size="0x0.2" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23A (x^23 + x^18 + 1)\;0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0xC - IDLEs using scramble58 (x^58+ x^39 + 1)\;0xD - Square_wave8 (8 ones, 8 zeros)\;0xE - Square_wave4 (4 ones, 4zeros)\;0xF - Square_wave2 (2 ones, 2zeros)\;0x10 - Square_wave1 (one, zero)\;0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;0x15 - SSPR\;0x16 - SSPRQ\;0x17 - LT frames (KR-startup frames)\;0x18 - PRBS15 - x^15 + x^14 + 1\;0x19 - PRBS28 - x^28 + x^25 + 1\;0x1A - Square wave3 (3ones, 3zeros)\;0x1B - Square wave13 (13ones, 13zeros)\;0x1C - Square wave30 (30ones, 30zeros)\;0x1D - PRBS58 (x^58+ x^39 + 1)\;0x1E - Default Pattern - Recommended for Mode B links for simplicity\;" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="prbs_fec_cap" descr="When set, PRBS over FEC is supported.\;Note: Feature is enabled on all lanes of port" access="RO" offset="0xC.0" size="0x0.1" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s) / Gen 1 PCIe (2.5 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) / Gen 2 PCIe (5 Gb/s)\;Bit 2 - XAUI/2.5GE (3.125 Gb/s) / Gen 3 PCIe (8 Gb/s)\;Bit 3- DDR (5 Gb/s) / Gen 4 PCIe (16 Gb/s)\;Bit 4- QDR (10 Gb/s) / Gen 5 PCIe (32 Gb/s)\;Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)\;Bit 6- FDR (14.0625 Gb/s) \;Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 8 - 50GE-KR4 (12.89 Gb/s) \;Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) \;Bit 10 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;Bit 11 - XDR / NVL6 / 200G_1x_simplex (106.25Gbd / 212.5Gb/s)\;Bit 12 - NVL6 / 360G_2x_bidi (90 Gbd / 180Gb/s)\;Bit 13 - NVL6 / 400G_2x_bidi (100 Gbd / 200Gb/s)\;Bit 14 - NVL6 / 328G_2x_bidi (82 Gbd / 164 Gb/s)\;\;Note: PCIe speeds are relevant when pnat = 3 only\;" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="prbs_fec_admin" descr="When set, PRBS over FEC is enabled for port.\;For FEC configuration, set PPLM.test_mode" access="RW" offset="0x10.0" size="0x0.1" />
	<field name="lane_rate_admin" descr="Lane rate be used in PRBS, see lane_rate_cap:\;0 - SDR (2.5 Gb/s) / Gen 1 PCIe (2.5 Gb/s)\;1 - DDR (5 Gb/s) / Gen 2 PCIe (5 Gb/s)\;2 - QDR (10 Gb/s)\;3 - FDR10 / 10GE/4 0GE (10.3125 Gb/s) / Gen 3 PCIe (8 Gb/s)\;4 - FDR (14.0625 Gb/s) / Gen 4 PCIe (16 Gb/s)\;5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) / Gen 5 PCIe (32 Gb/s)\;6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;8 - XDR / NVL6 / 200G_1x_simplex (106.25 Gbd / 212.5 Gb/s)\;9 - NVL6 / 360G_2x_bidi (90 Gbd / 180 Gb/s)\;10 - 1GE (1.25 Gb/s)\;11 - XAUI/2.5GE (3.125 Gb/s)\;12 - 50GE-KR4 (12.89 Gb/s)\;13 - NVL6 / 400G_2x_bidi (100 Gbd / 200 Gb/s)\;14 - NVL6 / 328G_2x_bidi (82 Gbd / 164 Gb/s)\;\;Note: All lanes must be set to the same rate\;Note: PCIe speeds are relevant when pnat = 3 only" access="RW" offset="0x10.16" size="0x0.16" />
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
	<field name="lm_cap" descr="When set , lane_mask field is applicable" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="mps" descr="[DWIP]\;Multiple Port Set.\;Supported only if indicated in PMSCR.prm_support of PREI support, otherwise ignored.\;When set, local_port index is ignored and set command is given to all ports in mask given from PMSCR.local_port_mask field" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="error_type_admin" descr="Error Type to generate:\;0: No_Error ---- Physical Errors ---- \;Bit 0: mixer_offset_ctrl_set" access="RW" enum="mixer_offset_ctrl_set=0x1" offset="0x4.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilities:\;Bit 0: mixer_offset_ctrl" access="RO" enum="mixer_offset_ctrl=0x1" offset="0x4.8" size="0x0.8" />
	<field name="error_type_oper" descr="Error injection operational status:\; 0x0 - No error injection \; 0x1 - Performing error injection" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="lane_mask" descr="Valid only if lm_cap is set, otherwise ignored\;Sets the specific lanes to be applied from the error_type_admin that was selected.\;Relevant for error types that can be per lane: rx_reset.\;Bitmask per lane." access="RW" offset="0x8.0" size="0x0.8" />
	<field name="error_injection_time" descr="Duration in time_res the port will generate errors. Reading this field will return the time left for errors to inject in msec.\;0x0000 indicates no generation of errors. \;0xFFFF - No decremental operation, meaning the errors will be injected continuously without stop condition. \;" access="RW" offset="0x8.12" size="0x0.16" />
	<field name="page_data" descr="Table  1984, &quot;PREI - Port Receive Error Injection Register Layout for 28nm,&quot; on page  2333" subnode="prei_reg_28nm_ext" access="RW" offset="0x10.0" size="0x8.0" />
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

<node name="ptasv2_7nm_ext" descr="" size="0x3c.0" >
	<field name="max_recovery_events" descr="System parameter\;0: Disable. Default\;1:255: maximum allowed number of transitions into the RECOVERY state in the Training control state diagram" access="RW" offset="0x10.0" size="0x0.8" />
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
	<field name="max_wait_timer" descr="Maximum time to perform link training in 802.3dj in seconds. System parameter.\;0: Not limited\;Default: 30 for electrical interfaces, 60 for optical interfaces" access="RW" offset="0x2C.0" size="0x0.16" />
	<field name="apsu_cap" descr="APSU (ILT/RTS) capability supported" access="RO" offset="0x34.0" size="0x0.1" />
	<field name="hop_count_cap" descr="Hop count for TRO capability supported" access="RO" offset="0x34.3" size="0x0.1" />
	<field name="lt_peer_det_cap" descr="Link training based peer vendor and configuration detection capability supported" access="RO" offset="0x34.6" size="0x0.1" />
	<field name="nlut_cap" descr="nLUT training capability supported" access="RO" offset="0x34.9" size="0x0.1" />
	<field name="training_en_cap" descr="Disable training option capability. \;Note that when disabled the ASPU protocol is still active but without link training frames." access="RW" offset="0x34.12" size="0x0.1" />
	<field name="restart_training" descr="Set to restart APSU" access="WO" offset="0x34.31" size="0x0.1" />
	<field name="apsu_ctl" descr="Control the APSU (ILT/RTS) activation if apsu_cap = 1\;0: Use FW default. Default\;1: Enable\;2: Disable" access="RW" offset="0x38.0" size="0x0.2" />
	<field name="hop_count_ctl" descr="Control the hop count for TRO activation if hop_count_cap = 1\;0: Use FW default. Default\;1: Enable\;2: Disable" access="RW" offset="0x38.3" size="0x0.2" />
	<field name="lt_peer_det_ctl" descr="Control the Link Training peer detection activation if lt_peer_det_cap = 1\;0: Use FW default. Default\;1: Enable\;2: Disable" access="RW" offset="0x38.6" size="0x0.2" />
	<field name="nlut_ctl" descr="Control the nLUT activation if nlut_cap = 1\;0: Use FW default. Default\;1: Enable\;2: Disable" access="RW" offset="0x38.9" size="0x0.2" />
	<field name="training_en_ctl" descr="Control the training_en configuration if training_en_cap = 1\;0: Use FW default. Default\;1: Enable training\;2: Disable training" access="RW" offset="0x38.12" size="0x0.2" />
</node>

<node name="ptasv2_reg_ext" descr="" size="0x44.0" >
	<field name="xdr_lt_cap" descr="XDR LT capability.\;When set, xdr_lt_c2m_en and xdr_lt_c2c_en control is possible." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="ib_cfg_delaytimeout_cap" descr="Configuration of DelayTimeOut capability.\;When set ib_cfg_delaytimeout control is possible.\;\;[Note: This feature is currently available only for HDR switch]" access="RO" offset="0x0.10" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type.\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: products_40nm\;1: products_28nm\;4: products_7nm\;5: products_5nm" access="RO" enum="products_7nm=0x4,products_5nm=0x5" offset="0x0.24" size="0x0.4" />
	<field name="xdr_lt_c2c_en" descr="LT for C2C channel Vs peer XDR speeds (200G per lane)\;0 - Auto (FW default)\;1 - skip LT flow\;2 - do LT flow\;This bit will affect requested lt_xdr negotiation vs peer." access="RW" offset="0x4.0" size="0x0.2" />
	<field name="xdr_lt_c2m_en" descr="LT for C2M channel Vs Module XDR speeds (200G per lane)\;0 - Auto (FW default)\;1 - skip LT flow\;2 - do segmented LT flow" access="RW" offset="0x4.2" size="0x0.2" />
	<field name="lf_squelch_pol_cap" descr="When set, lf_squelch_pol_admin is configurable" access="RO" offset="0x4.12" size="0x0.1" />
	<field name="lf_squelch_pol_admin" descr="Defines behavior of ETH phy FSM on LF event (Rx fault)\;0: FW default\;1: Disable_Tx_squelch - keep Tx transmitting, no Tx Squelch\;2: Enable_Tx_squelch - Toggle Tx and module DP (if exists)" access="RW" offset="0x4.13" size="0x0.2" />
	<field name="kr_ext_oper" descr="Updated only after LT phase was performed.\;0: lt_is_disabled\;1: lt_enabled_regular_kr\;2: lt_enabled_ext_kr_async_mode" access="RO" offset="0x4.24" size="0x0.2" />
	<field name="kr_ext_req" descr="Extended KR request:\;\;0: Auto - (FW default)\;1: Disable_kr_ext\;2: Enable_kr_ext_in_async_mode\;\;While the KR extended is enabled- nonstandard KR training will occur. This will include pause periods between sending the KR frames and sending the PRBS pattern instead (to support BER grade calculations)" access="RW" enum="Disable_kr_ext=0x1,Enable_kr_ext_in_async_mode=0x2" offset="0x4.29" size="0x0.2" />
	<field name="kr_ext_cap" descr="Extended KR capability. Will return support for a nonstandard KR training flow (as explained in the fields below)." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="page_data" descr="Table  2130, &quot;PTASv2 - Phy Tuning Algorithm Settings Register Layout for 7nm and 5nm,&quot; on page  2510" subnode="ptasv2_reg_page_data_auto_ext" access="RW" condition="$(parent).version" offset="0x8.0" size="0x3c.0" />
</node>

<node name="ptasv2_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x3c.0" >
	<field name="ptasv2_7nm_ext" descr="" subnode="ptasv2_7nm_ext" condition="($(parent).version == products_7nm) | ($(parent).version == products_5nm)" offset="0x0.0" size="0x3c.0" />
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
	<field name="page_data" descr="error injection page data: \;Table  1978, &quot;PTER- Port Transmit Errors Register Phy Level Layout,&quot; on page  2329\;Table  1980, &quot;PTER- Port Transmit Errors Register Port Level Fields,&quot; on page  2330" subnode="pter_reg_page_data_auto_ext" access="RW" offset="0x4.0" size="0x1c.0" union_selector="$(parent).error_page" />
</node>

<node name="pter_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x1c.0" >
	<field name="pter_phy_page_reg_ext" descr="" subnode="pter_phy_page_reg_ext" offset="0x0.0" selected_by="Injection_of_Phy_Errors" size="0x1c.0" />
	<field name="pter_port_page_reg_ext" descr="" subnode="pter_port_page_reg_ext" offset="0x0.0" selected_by="Injection_of_Port_Errors" size="0x1c.0" />
</node>

<node name="ptys_ext_proto_ib_admin_ext" descr="" size="0x4.0" >
	<field name="ext_proto_ib" descr="IB bitmask:\;Bit 0: SDR_1x\;Bit 1: SDR_2x\;Bit 2: SDR_4x\;Bit 12: FDR_4x\;Bit 14: EDR_2x\;Bit 15: EDR_4x\;Bit 16: HDR_1x\;Bit 17: HDR_2x\;Bit 18: HDR_4x\;Bit 20: NDR_1x\;Bit 21: NDR_2x\;Bit 22: NDR_4x\;Bit 24: XDR_1x\;Bit 25: XDR_2x\;Bit 26: XDR_4x" access="RW" enum="SDR_1x=0x1,SDR_2x=0x2,SDR_4x=0x4,FDR_4x=0x1000,EDR_2x=0x4000,EDR_4x=0x8000,HDR_1x=0x10000,HDR_2x=0x20000,HDR_4x=0x40000,NDR_1x=0x100000,NDR_2x=0x200000,NDR_4x=0x400000,XDR_1x=0x1000000,XDR_2x=0x2000000,XDR_4x=0x4000000" offset="0x0.0" size="0x4.0" />
</node>

<node name="ptys_ext_proto_ib_cap_oper_ext" descr="" size="0x4.0" >
	<field name="ext_proto_ib" descr="IB bitmask:\;Bit 0: SDR_1x\;Bit 1: SDR_2x\;Bit 2: SDR_4x\;Bit 12: FDR_4x\;Bit 14: EDR_2x\;Bit 15: EDR_4x\;Bit 16: HDR_1x\;Bit 17: HDR_2x\;Bit 18: HDR_4x\;Bit 20: NDR_1x\;Bit 21: NDR_2x\;Bit 22: NDR_4x\;Bit 24: XDR_1x\;Bit 25: XDR_2x\;Bit 26: XDR_4x" access="RO" enum="SDR_1x=0x1,SDR_2x=0x2,SDR_4x=0x4,FDR_4x=0x1000,EDR_2x=0x4000,EDR_4x=0x8000,HDR_1x=0x10000,HDR_2x=0x20000,HDR_4x=0x40000,NDR_1x=0x100000,NDR_2x=0x200000,NDR_4x=0x400000,XDR_1x=0x1000000,XDR_2x=0x2000000,XDR_4x=0x4000000" offset="0x0.0" size="0x4.0" />
</node>

<node name="ptys_ext_proto_nvlink_admin_ext" descr="" size="0x4.0" >
	<field name="ext_proto_nvlink" descr="NVLink bitmask:\;Bit 0: 200G_1x_mode_a (200G_1x_Simplex)\;Bit 1: 400G_2x_mode_a (400G_2x_Simplex)\;Bit 2: 400G_2x_mode_b (375G_2x_Bidi)\;Bit 3: 360G_2x_mode_b (337p5G_2x_Bidi)\;Bit 4: 328G_2x_mode_b (307p5G_2x_Bidi)\;Bit 5: Reserved\;Bit 6: 200G_2x_mode_a (200G_2x_Simplex)\;Bit 6: 200G_2x_mode_a (200G_2x_Simplex)\;Bit 7: 200G_1x_mode_b \;Bit 8: 180G_1x_mode_b \;Bit 9: 164G_1x_mode_b \;Bit 10: 100G_1x_mode_a" access="RW" offset="0x0.0" size="0x4.0" />
</node>

<node name="ptys_ext_proto_nvlink_cap_oper_ext" descr="" size="0x4.0" >
	<field name="ext_proto_nvlink" descr="NVLink bitmask:\;Bit 0: 200G_1x_mode_a (200G_1x_Simplex)\;Bit 1: 400G_2x_mode_a (400G_2x_Simplex)\;Bit 2: 400G_2x_mode_b (375G_2x_Bidi)\;Bit 3: 360G_2x_mode_b (337p5G_2x_Bidi)\;Bit 4: 328G_2x_mode_b (307p5G_2x_Bidi)\;Bit 5: Reserved\;Bit 6: 200G_2x_mode_a (200G_2x_Simplex)\;Bit 7: 200G_1x_mode_b \;Bit 8: 180G_1x_mode_b \;Bit 9: 164G_1x_mode_b \;Bit 10: 100G_1x_mode_a" access="RO" offset="0x0.0" size="0x4.0" />
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
	<field name="ib_proto_admin" descr="InfiniBand port speed bitmask\;" access="RW" offset="0x1C.0" size="0x0.16" />
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
	<field name="ext_ib_proto_cap" descr="IB/NVlink port supported protocols and widths bit-mask.\;Valid if PCAM.feature_cap_mask bit 90 is set OR mask &lt;&gt;0.\;\;For IB: Table  1884, &quot;PTYS - Extended Protocol IB - cap/oper Layout,&quot; on page  2190\;For NVLink: Table  1888, &quot;PTYS - Extended Protocol NVLink - cap/oper Layout,&quot; on page  2191" subnode="ptys_reg_ext_ib_proto_cap_auto_ext" access="RO" offset="0x38.0" size="0x4.0" union_selector="$(parent).proto_mask" />
	<field name="ext_ib_proto_admin" descr="IB/NVLink port protocols admin values.\;\;For IB: Table  1886, &quot;PTYS - Extended Protocol IB - admin Layout,&quot; on page  2190\;For NVLink: Table  1890, &quot;PTYS - Extended Protocol NVLink - admin Layout,&quot; on page  2192\;\;NOTE: This field and &quot;ib_proto_admin&quot;, &quot;ib_link_width_admin&quot; are mutual exclusive, meaning that only one of the field can be set on write command." subnode="ptys_reg_ext_ib_proto_admin_auto_ext" access="RW" offset="0x3C.0" size="0x4.0" union_selector="$(parent).proto_mask" />
	<field name="ext_ib_proto_oper" descr="IB/NVLink port operational protocol.\;For IB: Table  1884, &quot;PTYS - Extended Protocol IB - cap/oper Layout,&quot; on page  2190\;For NVLink: Table  1888, &quot;PTYS - Extended Protocol NVLink - cap/oper Layout,&quot; on page  2191" subnode="ptys_reg_ext_ib_proto_oper_auto_ext" access="RO" offset="0x40.0" size="0x4.0" union_selector="$(parent).proto_mask" />
</node>

<node name="ptys_reg_ext_ib_proto_admin_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="ptys_ext_proto_ib_admin_ext" descr="" subnode="ptys_ext_proto_ib_admin_ext" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="ptys_ext_proto_nvlink_admin_ext" descr="" subnode="ptys_ext_proto_nvlink_admin_ext" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="ptys_reg_ext_ib_proto_cap_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="ptys_ext_proto_ib_cap_oper_ext" descr="" subnode="ptys_ext_proto_ib_cap_oper_ext" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="ptys_ext_proto_nvlink_cap_oper_ext" descr="" subnode="ptys_ext_proto_nvlink_cap_oper_ext" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="ptys_reg_ext_ib_proto_oper_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="ptys_ext_proto_ib_cap_oper_ext" descr="" subnode="ptys_ext_proto_ib_cap_oper_ext" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="ptys_ext_proto_nvlink_cap_oper_ext" descr="" subnode="ptys_ext_proto_nvlink_cap_oper_ext" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pvls_ext" descr="" size="0x20.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="vl_suspend" descr="VL suspend, bitmap per VL\;Per bit:\;0: VL enabled (default)\;1: VL disabled" access="RW" offset="0x4.0" size="0x0.16" />
</node>

<node name="qcam_ext" descr="" size="0x48.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: First 128 REG_ID" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index\;0: Enhanced features" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="qos_access_reg_cap_mask" descr="Supported QoS access register bitmasks. Based on access_reg_group index. \;When bit is set, the register is supported in the device. \;For example:\;Bit 1: QCAP (0x4001)\;Bit 2: QPTS (0x4002)\;Bit 3: QDPM (0x4003)" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="qos_feature_cap_mask" descr="Supported QoS enhanced features based on feature_group index.\;When bit is set, the feature is supported in the device\;Bit 0x0: QPTS_TRUST_BOTH - trust_both is supported in QPTS register\;Bit 0x1: QEEC supports max on port hierarchy\;Bit 0x2: QEEC supports max on dwrr on traffic class hierarchy\;Bit 0x3: QEEC supports max on tx hierarchy" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="qeec_ext" descr="" size="0x20.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;2: Host_port_number\;Reserved when Switches.\;" access="INDEX" enum="Local_port_number=0x0,Host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;CPU port supported." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="element_index" descr="The index of the element in the hierarchy." access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="element_hierarchy" descr="The hierarchy of the element\;0: Port - host1: Group\;2: Sub_Group - subgroup of queues. \;3: Traffic_Class - VoQ queue" access="INDEX" enum="Port=0x0,Sub_Group=0x2,Traffic_Class=0x3" offset="0x4.16" size="0x0.4" />
	<field name="next_element_index" descr="The index of the element in the lower hierarchy.\;Reserved when element_heirarchy  &apos;0&apos;." access="RW" offset="0x8.0" size="0x0.8" />
	<field name="max_shaper_rate" descr="Max shaper information rate\;Value of 0x7FFF_FFFF means &quot;all allowed&quot; or &quot;shaper disabled&quot;Supported according to QCAM features" access="RW" offset="0x10.0" size="0x0.31" />
	<field name="mase" descr="Max shaper configuration enable. Enables configuration of max_shaper_rate, max_shaper_bs on this ETS element.\;0: disable\;1: enable\;Reserved when element_hierarchy is 1\;Supported according to QCAM features" access="RW" enum="disable=0x0,enable=0x1" offset="0x10.31" size="0x0.1" />
	<field name="dwrr_weight" descr="DWRR weight on the link going down from the ETS element:\;The percentage of bandwidth guaranteed to a ETS within its hierarchy.\;The sum of dwrr_weight values across all ETS elements within one hierarchy should equal 100.\;This field is reserved when dwrr is set to strict priority.\;\;Supported according to QCAM features" access="RW" offset="0x18.0" size="0x0.8" />
	<field name="dwrr" descr="DWRR or strict priority on the link going down from the ETS element:\;0: strict priority\;1: DWRR" access="RW" offset="0x18.15" size="0x0.1" />
	<field name="de" descr="DWRR configuration enable. Enables configuration of the dwrr and dwrr_weight.\;0: disable\;1: enable\;Supported according to QCAM featuresReserved for QM switches." access="RW" offset="0x18.31" size="0x0.1" />
</node>

<node name="qhll_ext" descr="" size="0xc.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="hll_time" descr="HLL Time\;HLL Time = 4.096uSec * 2^hll_time\;Default is 17 (0.54Sec)\;Range is 0 ..19\;Values of 20-31 means infinite (no HLL)" access="RW" offset="0x4.0" size="0x0.5" />
	<field name="stall_cnt" descr="Stall count. Number of HLL discarded packets required to enter the Stall-State.\;Default is 7\;Range 1..7\;Reserved when stall_en = 0" access="RW" offset="0x8.0" size="0x0.3" />
	<field name="stall_en" descr="Stall enable\;0: Stall disabled\;1: Stall enabled (default)" access="RW" offset="0x8.31" size="0x0.1" />
</node>

<node name="qpdp_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port.\;Supported for data packets from CPU port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="switch_prio" descr="Default port Switch Priority (default 0)\;For NIC devices only 8 priorities are supported" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="color" descr="Default port color (default=0)\;0x0: GREEN\;0x1: YELLOW\;0x2: RED\;For Switch only, Reserved for NICs" access="RW" enum="GREEN=0x0,YELLOW=0x1,RED=0x2" offset="0x4.8" size="0x0.2" />
</node>

<node name="qpdpm_ext" descr="" size="0x84.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local Port.\;Supported for data packets from CPU port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="dscp" descr="DSCP entry is the DSCP to Switch Priority mapping. For more details refer to Table  1236, &quot;qpdpm_dscp Layout,&quot; on page  1592" access="RW" high_bound="63" low_bound="0" offset="0x4.16" size="0x80.0" />
</node>

<node name="qprt_ext" descr="" size="0x8.0" >
	<field name="pcp" descr="Packet&apos;s PCP value" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="dei" descr="Packet&apos;s DEI value." access="INDEX" offset="0x0.11" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port.\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rprio" descr="The default value for the table is: PCP i -&gt;Regeneration Priority i\; For NIC devices only 8 priorities are supported" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="color" descr="Packet Color.\;0: GREEN\;1: YELLOW\;2: RED\;For Switch only, Reserved for NICs" access="RW" enum="GREEN=0x0,YELLOW=0x1,RED=0x2" offset="0x4.8" size="0x0.2" />
</node>

<node name="qpts_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local Port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="trust_state" descr="0: TRUST_PORT - reserved for NIC devices\;1: TRUST_PCP - default\;2: TRUST_DSCP\;3: TRUST_BOTH - For NIC devices suported only when QCAM.QPTS_TRUST_BOTH == 1" access="RW" enum="TRUST_PCP=0x1,TRUST_DSCP=0x2,TRUST_BOTH=0x3" offset="0x4.0" size="0x0.3" />
</node>

<node name="qshr_ext" descr="" size="0x50.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fr" descr="Fast Response - the device will shape the rate to its minimum value upon receive of WQE LWM (Low WaterMark) event \;0: disable\;1: enable" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="ch" descr="Connected host:\;0: The configuration will be applied on the host calling QSHR. \;1: The configuration will be applied on the host connected to the function calling the QSHR." access="INDEX" offset="0x0.27" size="0x0.1" />
	<field name="global_configuration" descr="Global configuration. For details, refer to Table 1242, &quot;ETS Global Configuration Register Layout&quot;.\;On get, the actual returned values can differ from the set values." subnode="ets_global_ext" access="RW" offset="0x48.0" size="0x8.0" />
</node>

<node name="qspcp_ext" descr="" size="0xc.0" >
	<field name="switch_prio" descr="Switch Priority entry form mapping to Counting Priority.\;Switch Priority 15 maps for control packets (mapped to counting priority 7 by default).\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port\;No support for CPU port\;No support for router port\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rx_counting_prio" descr="The Rx Counting Priority value for the relevant Switch Priority value.\;default: \;for i=[0..7]: switch_prio i: rx_counting_prio i\;for i=[8..15]: switch_prio i: rx_counting_prio (i-8)" access="RW" offset="0x4.0" size="0x0.3" />
	<field name="tx_counting_prio" descr="The Tx Counting Priority value for the relevant Switch Priority value.\;default: \;for i=[0..7]: switch_prio i: tx_counting_prio i\;for i=[8..15]: switch_prio i: tx_counting_prio (i-8)" access="RW" offset="0x8.0" size="0x0.3" />
</node>

<node name="qspip_ext" descr="" size="0x8.0" >
	<field name="switch_prio" descr="Switch Priority entry form mapping to IEEE Priority" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="ieee_prio" descr="The new IEEE Priority value for the relevant Switch Priority value.\;default: \;for i=[0..7]: switch_prio i: ieee_prio i\;for i=[8..15]: switch_prio i: ieee_prio (i-8)\;Note: Different switch_prio values assigned to a given buffer (see PPTB) may be assigned to different ieee_prio values." access="RW" offset="0x4.0" size="0x0.3" />
</node>

<node name="qtct_ext" descr="" size="0x8.0" >
	<field name="switch_prio" descr="Switch Priority" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number (transmit port)" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cap_remote_admin" descr="Indicates if operation_type==remote_admin_parameters is supported." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="cap_local_admin" descr="Indicates if operation_type==local_admin_parameters is supported" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="operation_type" descr="Operation type.\;0x0: local_operative_parameters\;0x1: local_admin_parameters - Supported only when cap_local_admin==1\;0x2: remote_admin_parameters- Supported only when cap_remote_admin==1" access="INDEX" enum="local_operative_parameters=0x0,local_admin_parameters=0x1,remote_admin_parameters=0x2" offset="0x0.30" size="0x0.2" />
	<field name="tclass" descr="Traffic Class\;Default values are: \;- switch_prio=0: tclass=1 \;- switch_prio=1: tclass=0\;- switch_prio&gt;1: tclass = switch_prio\;\;Valid values: 0..HCA_CAP.max_tc" access="RW" offset="0x4.0" size="0x0.4" />
</node>

<node name="register_host_endianness_ext" descr="" size="0x10.0" >
	<field name="he" descr="0: LITTLE_ENDIAN\;1: BIG_ENDIAN" access="RW" enum="LITTLE_ENDIAN=0x0,BIG_ENDIAN=0x1" offset="0x0.31" size="0x0.1" />
</node>

<node name="register_loopback_control_ext" descr="" size="0x10.0" >
	<field name="port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="no_lb" descr="When set, the HCA will always send packets meant for the same port to wire, rather than perform internal loopback" access="RW" offset="0x0.31" size="0x0.1" />
</node>

<node name="register_misc_counters_ext" descr="" size="0x20.0" >
	<field name="counter_select" descr="When performing a WRITE operation - , the counter select bitmask determines which registers are set:\;Bit 0 - ECC\;Bit 1 - LDB silent drop" offset="0x4.0" size="0x4.0" />
	<field name="ecc" descr="Counts number of arrays which encountered a bit error" offset="0xC.0" size="0x4.0" />
	<field name="ldb_silent_drop" descr="Counts number of packets silently dropped due to LDB error" offset="0x10.0" size="0x4.0" />
</node>

<node name="register_power_settings_ext" descr="" size="0x10.0" >
	<field name="power_settings_level" descr="0x0 - minimum power (maximum latency penalty)\;0x1-0xfe - reserved\;0xff - maximum power (minimum latency penalty)" access="RW" offset="0x0.0" size="0x0.8" />
</node>

<node name="register_unit_perf_counters_cfg_ext" descr="" size="0x20.0" >
	<field name="cnt0_select" descr="Counter selector configuration.\;If set to 0 on even-numbered selectors, extends the consecutively (odd-numbered) counter to 64 bits.\;If set to 0 on odd numbered selectors, count core clock cycles on this counter.\;Otherwise selects a counter with specified ID." access="RW" offset="0x0.0" size="0x0.8" />
	<field name="cnt0_cmd" descr="On read: reserved.\;On write:\;0=SKIP: do not modify this counter selector\;1=SET: set this counter selector, and reset the counter" access="RW" offset="0x0.12" size="0x0.4" />
	<field name="cnt1_select" descr="Counter selector configuration.\;If set to 0 on even-numbered selectors, extends the consecutively (odd-numbered) counter to 64 bits.\;If set to 0 on odd numbered selectors, count core clock cycles on this counter.\;Otherwise selects a counter with specified ID." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="cnt1_cmd" descr="On read: reserved.\;On write:\;0=SKIP: do not modify this counter selector\;1=SET: set this counter selector, and reset the counter" access="RW" offset="0x4.12" size="0x0.4" />
	<field name="cnt2_select" descr="Counter selector configuration.\;If set to 0 on even-numbered selectors, extends the consecutively (odd-numbered) counter to 64 bits.\;If set to 0 on odd numbered selectors, count core clock cycles on this counter.\;Otherwise selects a counter with specified ID." access="RW" offset="0x8.0" size="0x0.8" />
	<field name="cnt2_cmd" descr="On read: reserved.\;On write:\;0=SKIP: do not modify this counter selector\;1=SET: set this counter selector, and reset the counter" access="RW" offset="0x8.12" size="0x0.4" />
	<field name="cnt3_select" descr="Counter selector configuration.\;If set to 0 on even-numbered selectors, extends the consecutively (odd-numbered) counter to 64 bits.\;If set to 0 on odd numbered selectors, count core clock cycles on this counter.\;Otherwise selects a counter with specified ID." access="RW" offset="0xC.0" size="0x0.8" />
	<field name="cnt3_cmd" descr="On read: reserved.\;On write:\;0=SKIP: do not modify this counter selector\;1=SET: set this counter selector, and reset the counter" access="RW" offset="0xC.12" size="0x0.4" />
	<field name="cnt4_select" descr="Counter selector configuration.\;If set to 0 on even-numbered selectors, extends the consecutively (odd-numbered) counter to 64 bits.\;If set to 0 on odd numbered selectors, count core clock cycles on this counter.\;Otherwise selects a counter with specified ID." access="RW" offset="0x10.0" size="0x0.8" />
	<field name="cnt4_cmd" descr="On read: reserved.\;On write:\;0=SKIP: do not modify this counter selector\;1=SET: set this counter selector, and reset the counter" access="RW" offset="0x10.12" size="0x0.4" />
	<field name="cnt5_select" descr="Counter selector configuration.\;If set to 0 on even-numbered selectors, extends the consecutively (odd-numbered) counter to 64 bits.\;If set to 0 on odd numbered selectors, count core clock cycles on this counter.\;Otherwise selects a counter with specified ID." access="RW" offset="0x14.0" size="0x0.8" />
	<field name="cnt5_cmd" descr="On read: reserved.\;On write:\;0=SKIP: do not modify this counter selector\;1=SET: set this counter selector, and reset the counter" access="RW" offset="0x14.12" size="0x0.4" />
	<field name="cnt6_select" descr="Counter selector configuration.\;If set to 0 on even-numbered selectors, extends the consecutively (odd-numbered) counter to 64 bits.\;If set to 0 on odd numbered selectors, count core clock cycles on this counter.\;Otherwise selects a counter with specified ID." access="RW" offset="0x18.0" size="0x0.8" />
	<field name="cnt6_cmd" descr="On read: reserved.\;On write:\;0=SKIP: do not modify this counter selector\;1=SET: set this counter selector, and reset the counter" access="RW" offset="0x18.12" size="0x0.4" />
	<field name="cnt7_select" descr="Counter selector configuration.\;If set to 0 on even-numbered selectors, extends the consecutively (odd-numbered) counter to 64 bits.\;If set to 0 on odd numbered selectors, count core clock cycles on this counter.\;Otherwise selects a counter with specified ID." access="RW" offset="0x1C.0" size="0x0.8" />
	<field name="cnt7_cmd" descr="On read: reserved.\;On write:\;0=SKIP: do not modify this counter selector\;1=SET: set this counter selector, and reset the counter" access="RW" offset="0x1C.12" size="0x0.4" />
</node>

<node name="register_unit_perf_counters_data_ext" descr="" size="0x20.0" >
	<field name="counter0" descr="Performance counter0 data" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="counter1" descr="Performance counter1 data" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="counter2" descr="Performance counter2 data" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="counter3" descr="Performance counter3 data" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="counter4" descr="Performance counter4 data" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="counter5" descr="Performance counter5 data" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="counter6" descr="Performance counter6 data" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="counter7" descr="Performance counter7 data" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="register_unti_perf_global_ctrl_ext" descr="" size="0x10.0" >
	<field name="cmd" descr="0x0 - stop counting in all performance counters\;0x1 - start counting in all performance counters \;Otherwise - reserved" access="WO" offset="0x0.0" size="0x0.8" />
</node>

<node name="resource_dump_ext" descr="" size="0x100.0" >
	<field name="segment_type" descr="See Section  29.11, &quot;Resource Dump,&quot; on page  2019." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="seq_num" descr="Sequence number. 0 on first call of dump and incremented on each more dump." access="RW" offset="0x0.16" size="0x0.4" />
	<field name="vhca_id_valid" descr="If set, then vhca_id field is valid. Otherwise dump resources on my vhca_id." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="inline_dump" descr="If set, data is dumped in the register in inline_data field. otherwise dump to mkey." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="more_dump" descr="If set, the device has additional information that has not been dumped yet." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="vhca_id" descr="vhca_id where the resource is allocated." access="WO" offset="0x4.0" size="0x0.16" />
	<field name="index1" descr="First object index to be dumped when supported by the object.\;SW shall read this field upon command done and shall provide it on the next call in case dump_more==1." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="index2" descr="Second object index to be dumped when supported by the object.\;SW shall read this field upon command done and shall provide it on the next call in case dump_more==1." access="RW" offset="0xC.0" size="0x4.0" />
	<field name="num_of_obj2" descr="The amount of objects to dump starting for index 2.\;SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. \;Range is 0..0xfff0. When the segment&apos;s num_of_obj2_supports_all is set, the special value of 0xffff represents &quot;all&quot;. When the segment&apos;s num_of_objx_supports_active is set, the special value of 0xfffe represents &quot;active&quot;. The  value of 0x0 and 0x1 are allowed even if the supported_num_of_obj2 is &quot;0&quot;." access="RW" offset="0x10.0" size="0x0.16" />
	<field name="num_of_obj1" descr="The amount of objects to dump starting for index 1\;SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. \;Range is 0..0xfff0. When the segment&apos;s num_of_obj1_supports_all is set, the special value of 0xffff represents &quot;all&quot;. When the segment&apos;s num_of_objx_supports_active is set, the special value of 0xfffe represents &quot;active&quot;. The  value of 0x0 and 0x1 are allowed even if the supported_num_of_obj1 is &quot;0&quot;." access="RW" offset="0x10.16" size="0x0.16" />
	<field name="device_opaque" descr="An opaque provided by the device. SW shall read the device_opaque upon command done and shall provide it on the next call in case dump_more==1. On first call, device_opaque shall be 0." subnode="uint64" access="RW" offset="0x18.0" size="0x8.0" />
	<field name="mkey" descr="Memory key to dump to. \;Valid when inline_dump==0." access="WO" offset="0x20.0" size="0x4.0" />
	<field name="size" descr="In write, the size of maximum allocated buffer that the device can use.\;In read, the actual written size.\;In granularity of Bytes." access="RW" offset="0x24.0" size="0x4.0" />
	<field name="address" descr="VA address (absolute address) of memory where to start dumping. \;Valid when inline_dump==0." subnode="uint64" access="WO" offset="0x28.0" size="0x8.0" />
	<field name="inline_data" descr="Data that is dumped in case of inline mode.\;Valid when inline_dump==1." access="RW" high_bound="51" low_bound="0" offset="0x30.0" size="0xd0.0" />
</node>

<node name="roce_accl_reg_ext" descr="" size="0x80.0" >
	<field name="roce_adp_retrans_field_select" descr="In Query, indicates if roce_tx_windo mode is configurable.\;In set, indicates roce_tx_window_en field is modified." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="roce_tx_window_field_select" descr="In Query, indicates whether roce_tx_window mode is configurable.\;In set, indicates roce_tx_window_en field is modified." access="RW" offset="0x0.1" size="0x0.1" />
	<field name="roce_slow_restart_field_select" descr="In Query, indicates whether roce_slow_restart mode is configurable.\;In set, indicates roce_slow_restart_en field is modified." access="RW" offset="0x0.2" size="0x0.1" />
	<field name="roce_slow_restart_idle_field_select" descr="In Query, indicates whether roce_slow_restart_idle mode is configurable. \;In set, indicates roce_slow_restart_idle_en field is modified" access="RW" offset="0x0.3" size="0x0.1" />
	<field name="min_ack_timeout_limit_disabled_field_select" descr="In Query, indicates whether min_ack_timeout_limit_disabled mode is configurable. In set, indicates min_ack_timeout_limit_disabled field is modified" access="RW" offset="0x0.4" size="0x0.1" />
	<field name="adaptive_routing_forced_en_field_select" descr="In Query, indicates whether adaptive_routing_forced mode is configurable. \;In set, indicates adaptive_routing_forced_en field is modified." access="RW" offset="0x0.5" size="0x0.1" />
	<field name="selective_repeat_forced_en_field_select" descr="In Query, indicates whether selective_repeat_forced mode is configurable. \;In set, indicates selective_repeat_forced_en field is modified" access="RW" offset="0x0.6" size="0x0.1" />
	<field name="dc_half_handshake_en_field_select" descr="In Query, indicates whether dc_half_handshake_en is supported. \;In Set, indicates selective_repeat_forced_en field is modified" access="RW" offset="0x0.7" size="0x0.1" />
	<field name="cc_per_plane_en_field_select" descr="In Query, indicates cc_per_plane_en is valid and is configurable.\;In Set, indicates cc_per_plane_en is modified." access="RW" offset="0x0.8" size="0x0.1" />
	<field name="ack_dscp_force_field_select" descr="In query, indicates whether force ack DSCP mode is configurable. \;In set, indicates ack_dscp and ack_dscp_force fields are modified." access="RW" offset="0x0.9" size="0x0.1" />
	<field name="cc_burst_size_select" descr="In query, indicates that cc_burst_size is supported and valid. \;In set, indicates that cc_burst_size is modified" access="RW" offset="0x0.10" size="0x0.1" />
	<field name="cc_probe_mp_mode_field_select" descr="In query, indicates that cc_probe_mp_mode is supported and valid.\;In set, indicates that cc_probe_mp_mode is modified." access="RW" offset="0x0.11" size="0x0.1" />
	<field name="ifa2_turn_around_select" descr="In query, indicates that ifa2_turn_around_en is supported and valid.\;In set, indicates that ifa2_turn_around_en is modified." access="RW" offset="0x0.27" size="0x0.1" />
	<field name="adp_retx_profile_select" descr="In query, indicates that adp_retx_profile_id and adp_retx_profile are supported and valid.\;In set, indicates that the profile indicated adp_retx_profile_id is modified with the parameters in adp_retx_profile." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="roce_adp_retrans_en" descr="If set, the adaptive retransmission window functionality is enabled.\;Valid only when roce_adp_retrans_field_select == 1." access="RW" offset="0x4.0" size="0x0.1" />
	<field name="roce_tx_window_en" descr="If set, the Transmission window functionality is enabled. \;Valid only when roce_tx_window_field_select == 1." access="RW" offset="0x4.1" size="0x0.1" />
	<field name="roce_slow_restart_en" descr="If set, the Slow restart functionality is enabled.\;When used, slow restart is initiated when congestion is identified on the network.\;Valid only when roce_slow_restart_field_select == 1." access="RW" offset="0x4.2" size="0x0.1" />
	<field name="roce_slow_restart_idle_en" descr="If set, the Slow restart after idle functionality is enabled. When used, slow restart is initiated when qp was idling. Valid only when roce_slow_restart_idle_field_select ==1" access="RW" offset="0x4.3" size="0x0.1" />
	<field name="min_ack_timeout_limit_disabled" descr="If set, min_ack_timeout_limit enforcement is disabled. \;Valid only when min_ack_timeout_limit_disabled_field_select ==1" access="RW" offset="0x4.4" size="0x0.1" />
	<field name="adaptive_routing_forced_en" descr="If adaptive_routing_forced_en = 1, all the QPs will be created with adaptive_routing enabled. \;If adaptive_routing_forced_en = 0, all the QPs will be created with adaptive_routing disabled. \;Valid only when adaptive_routing_forced_en_field_select ==1." access="RW" offset="0x4.5" size="0x0.1" />
	<field name="selective_repeat_forced_en" descr="If selective_repeat_forced_en= 1, all the QPs will be created with selective_repeat enabled. \;If selective_repeat_forced_en= 0, all the QPs will be created with selective_repeat disabled. \;Valid only when selective_repeat_forced_en_field_select ==1." access="RW" offset="0x4.6" size="0x0.1" />
	<field name="dc_half_handshake_en" descr="If dc_half_handshake_en = 1, all the QPs will be created with default half handshake. The full_handshake bit in QP context can override this setting. Valid only when dc_half_handshake_en_field_select ==1" access="RW" offset="0x4.7" size="0x0.1" />
	<field name="cc_per_plane_en" descr="If set, Congestion Control per plane is enabled. Valid if cc_per_plane_en_field_select is set." access="RW" offset="0x4.8" size="0x0.1" />
	<field name="ack_dscp_force" descr="If set, force DSCP value from ack_dscp field. valid only when ack_dscp_force_field_select == 1" access="RW" offset="0x4.9" size="0x0.1" />
	<field name="ack_dscp" descr="The DSCP value for ack packets on NP when ack_dscp_force is set. valid only when ack_dscp_force_field_select == 1" access="RW" offset="0x4.10" size="0x0.6" />
	<field name="cc_burst_size" descr="Congestion Control process gets a TX event every time a flow completes transmission of a cc_burst_size amount of data, since previous event.\;0x0: BURST_4KB\;0x1: BURST_8KB\;0x2: BURST_16KB\;0x7: BURST_1_5KB - 1.5KB\;Other values are reserved" access="RW" enum="BURST_4KB=0x0,BURST_8KB=0x1,BURST_16KB=0x2,BURST_1_5KB=0x7" offset="0x4.24" size="0x0.3" />
	<field name="ifa2_turn_around_en" descr="If set, IFA2 Turn Around is enabled.\;Valid if ifa2_turn_around_select is set." access="RW" offset="0x4.27" size="0x0.1" />
	<field name="adp_retx_profile_id" descr="The index of the adaptive-retransmission profile to query or to modify. Value 0 is reserved.\;Valid if adp_retrans_timeouts_profile_select is set.\;Must comply with adp_retx_profile_max_id." access="INDEX" offset="0x4.28" size="0x0.3" />
	<field name="adp_retx_base_timeout_min" descr="The minimal base-timeout value for adp_retx_profile, given in nano second units" access="RO" offset="0x8.0" size="0x0.20" />
	<field name="cc_probe_mp_mode" descr="CC-probe plane mismatch handling mode for multiplane.\;0x0: PROBE_ACCEPT\;0x1: PROBE_DISCARD\;Other values are reserved" access="RW" enum="PROBE_ACCEPT=0x0,PROBE_DISCARD=0x1" offset="0x8.20" size="0x0.2" />
	<field name="adp_retx_profile_max_id" descr="Maximal index supported for adp_retx_profile_id" access="RO" offset="0x8.24" size="0x0.3" />
	<field name="adp_retx_profile_max_range_num" descr="Maximal number of timeout ranges in adp_retx_profile" access="RO" offset="0x8.28" size="0x0.3" />
	<field name="adp_retx_profile" descr="Adaptive Retransmission profile" subnode="adp_retx_profile_ext" access="RW" offset="0x10.0" size="0x30.0" />
</node>

<node name="rom_version_ext" descr="" size="0x4.0" >
	<field name="build" descr="Build version" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="minor" descr="Minor version" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="major" descr="Major version" access="RO" offset="0x0.24" size="0x0.8" />
</node>

<node name="sbcam_ext" descr="" size="0x4c.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: First 128 REG_ID" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index\;0: Enhanced features" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sb_access_reg_cap_mask" descr="Supported Shared Buffer access register bitmasks. Based on access_reg_group index. \;When bit is set, the register is supported in the device. \;For example:\;Bit 1: SBPR_(0xB001)\;Bit 2: SBCM_(0xB002)\;Bit 3: SBPM_(0xB003)\;Bit 5: SBSR_(0xB005)" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="sb_feature_cap_mask" descr="Supported Shared Buffer enhanced features based on feature_group index.\;When bit is set, the feature is supported in the device\;Bit 0: descriptors_cap - (desc) is supported \;Bit 1: ext_buff_occupancy_cap - is supported \;Bit 2: exclude_cap - bit is supported\;Bit 3: sb_own_res - user can configure ePort per tc shared buffer configuration    \;Bit 4: sb_global_res - user can configure ePort, iPort and iPort per pg shared buffer configuration  " access="RO" enum="descriptors_cap=0x1,ext_buff_occupancy_cap=0x2,exclude_cap=0x4,sb_own_res=0x8,sb_global_res=0x10" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
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
	<field name="dir" descr="Direction\;0: Ingress port quota\;1: Egress port quota\;\;" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="lp_msb" descr="Local port[9:8]\;\;\;" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="pg_buff" descr="PG buffer - Port PG (dir=ingress) / traffic class (dir=egress)\;For PG buffer: range is 0..cap_max_pg_buffers - 1\;For traffic class: range is 0..cap_max_tclass_sb - 1\;\;For  traffic class to CPU port: range is 0..cap_max_cpu_ingress_tclass_sb - 1\;For traffic class to BMC port: range is 0..cap_max_bmc_tc_sb - 1\;\;\;\;\;\;" access="INDEX" offset="0x0.8" size="0x0.6" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;2: Host_port_number" access="INDEX" enum="Local_port_number=0x0,Host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;\;\;\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNS.status is RELEASED then the device will NACK the command" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;For NIC: Supported when descriptors_cap is set\;\;" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="exc" descr="Exclude - no accounting in the pool\;0: the tclass is accounted in the pool (default)\;1: the tclass is not accounted in the pool \;\;For NIC: Supported when descriptors_cap is set\;" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="buff_occupancy" descr="Current buffer occupancy.\;Units of cells.\;This includes cells at the pool and at the min_buff." access="RO" offset="0x10.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored.\;Units of cells.\;This includes cells at the pool and at the min_buff.\;Cleared by writing to the clr field.\;" access="RO" offset="0x14.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy.\;When this bit is set, the max_buff_occupancy field is cleared (and a new max value is tracked from the time the clear was performed)." access="OP" offset="0x14.31" size="0x0.1" />
	<field name="min_buff" descr="Minimum buffer size for the limiter.\;The minimum buffer is not part of the pool area.\;Units of cells." access="RW" offset="0x18.0" size="0x0.24" />
	<field name="max_buff" descr="The maximum buffer threshold in the pool area.\;When the pool that is associated to the port-pg/tclass is configured to static, then max_buff is configured in cells\;When the pool that is associated to the port-pg/tclass is configured to dynamic, then max_buff holds the &quot;alpha&quot; parameter, supporting the following values:\;0 : 0\;i : (1/128)*2^(i-1), for i=1..14\;0xFF: Infinity\;Reserved when infi_max = 1\;\;" access="RW" offset="0x1C.0" size="0x0.24" />
	<field name="infi_max" descr="Max buffer is infinite.\;When set, the max_buff field is reserved." access="RW" offset="0x1C.31" size="0x0.1" />
	<field name="pool" descr="Association of the port-priority to a pool\;Range 0 .. cap_num_pool_supported - 1." access="RW" offset="0x24.0" size="0x0.4" />
</node>

<node name="sbpr_ext" descr="" size="0x18.0" >
	<field name="pool" descr="Pool index\;Range 0 .. cap_num_pool_supported - 1." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="dir" descr="Direction\;0: Ingress pools\;1: Egress pools\;\;" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNS.status is RELEASED then the device will NACK with status = RESOURCE_NOT_AVAILABLE\;" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;For NIC: Supported when descriptors_cap is set\;\;" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="size" descr="Pool size in buffer cells\;Reserved when infi_size = 1\;" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="infi_size" descr="size is infinite\;When set, the size field is reserved" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="mode" descr="Pool quota calculation mode:\;0: Static\;1: Dynamic" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="buff_occupancy" descr="Current buffer occupancy" access="RO" offset="0xC.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. Cleared by writing to the clr field\;" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is cleared (and a new max value is tracked from the time the clear was performed)" access="OP" offset="0x10.31" size="0x0.1" />
	<field name="ext_buff_occupancy" descr="Extended current buffer occupancy\;Includes also all of the min_buff of the relevant PG buffer or traffic class associated to this pool\;Reserved when Spectrum, supported by Spectrum-2 and Quantum. For NIC: Supported when ext_buff_occupancy_cap is set\;" access="RO" offset="0x14.0" size="0x0.24" />
</node>

<node name="set_node_in_ext" descr="" size="0x40.0" >
	<field name="node_description" descr="Text describing the node" access="RW" high_bound="15" low_bound="0" offset="0x0.0" size="0x40.0" />
</node>

<node name="sllm_5nm_ext" descr="" size="0x2c.0" >
	<field name="peq_cap" descr="" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="is_peq_on" descr="" access="RO" offset="0x0.2" size="0x0.1" />
	<field name="peq_interval_period" descr="" access="RW" offset="0x4.0" size="0x0.12" />
	<field name="peq_interval_period_oper" descr="" access="RO" offset="0x8.0" size="0x0.12" />
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
	<field name="version" descr="3: prod_16nm\;4: prod_7nm\;5: prod_5nm - (Uphy 7.0/ 7.5)\;6: serdes_gen_8" access="RO" enum="prod_16nm=0x3,prod_7nm=0x4,prod_5nm=0x5,serdes_gen_8=0x6" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - invalid\;1 - valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="Table  2368, &quot;SLLM - SerDes Lane Link Maintenance Register Layout for 5nm and Serdes_gen_8,&quot; on page  2811" subnode="sllm_reg_page_data_auto_ext" access="RW" condition="$(parent).port_type AND $(parent).version" offset="0x4.0" size="0x2c.0" />
</node>

<node name="sllm_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x2c.0" >
	<field name="sllm_5nm_ext" descr="" subnode="sllm_5nm_ext" condition="(($(parent).port_type == Network_Port || $(parent).port_type == NearEnd_Port || $(parent).port_type == FarEnd_Port)) AND (($(parent).version == prod_5nm) OR $(parent).version == serdes_gen_8)" offset="0x0.0" size="0x2c.0" />
</node>

<node name="slprr_Extended_read_7_ext" descr="" size="0x58.0" >
	<field name="prr1_2" descr="" access="RO" offset="0x0.17" size="0x0.5" />
	<field name="prr1_1" descr="" access="RO" offset="0x0.24" size="0x0.2" />
	<field name="prr1_0" descr="" access="RO" offset="0x0.29" size="0x0.3" />
	<field name="prr2_m3" descr="" access="RO" offset="0x4.3" size="0x0.8" />
	<field name="prr2_m2" descr="" access="RO" offset="0x4.13" size="0x0.8" />
	<field name="prr2_m1" descr="" access="RO" offset="0x4.23" size="0x0.9" />
	<field name="prr2_2" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="prr2_1" descr="" access="RO" offset="0x8.9" size="0x0.8" />
	<field name="prr2_m5" descr="" access="RO" offset="0x8.19" size="0x0.5" />
	<field name="prr2_m4" descr="" access="RO" offset="0x8.26" size="0x0.6" />
	<field name="prr2_6" descr="" access="RO" offset="0xC.1" size="0x0.6" />
	<field name="prr2_5" descr="" access="RO" offset="0xC.8" size="0x0.7" />
	<field name="prr2_4" descr="" access="RO" offset="0xC.17" size="0x0.7" />
	<field name="prr2_3" descr="" access="RO" offset="0xC.25" size="0x0.7" />
	<field name="prr2_10" descr="" access="RO" offset="0x10.2" size="0x0.5" />
	<field name="prr2_9" descr="" access="RO" offset="0x10.9" size="0x0.6" />
	<field name="prr2_8" descr="" access="RO" offset="0x10.18" size="0x0.6" />
	<field name="prr2_7" descr="" access="RO" offset="0x10.26" size="0x0.6" />
	<field name="prr2_12" descr="" access="RO" offset="0x14.19" size="0x0.5" />
	<field name="prr2_11" descr="" access="RO" offset="0x14.27" size="0x0.5" />
	<field name="prr3_5" descr="" access="RO" offset="0x18.0" size="0x0.6" />
	<field name="prr3_4" descr="" access="RO" offset="0x18.6" size="0x0.4" />
	<field name="prr3_3" descr="" access="RO" offset="0x18.11" size="0x0.6" />
	<field name="prr3_2" descr="" access="RO" offset="0x18.17" size="0x0.4" />
	<field name="prr3_1" descr="" access="RO" offset="0x18.22" size="0x0.6" />
	<field name="prr3_0" descr="" access="RO" offset="0x18.28" size="0x0.4" />
	<field name="prr3_11" descr="" access="RO" offset="0x1C.0" size="0x0.6" />
	<field name="prr3_10" descr="" access="RO" offset="0x1C.6" size="0x0.4" />
	<field name="prr3_9" descr="" access="RO" offset="0x1C.11" size="0x0.6" />
	<field name="prr3_8" descr="" access="RO" offset="0x1C.17" size="0x0.4" />
	<field name="prr3_7" descr="" access="RO" offset="0x1C.22" size="0x0.6" />
	<field name="prr3_6" descr="" access="RO" offset="0x1C.28" size="0x0.4" />
	<field name="prr3_17" descr="" access="RO" offset="0x20.0" size="0x0.6" />
	<field name="prr3_16" descr="" access="RO" offset="0x20.6" size="0x0.4" />
	<field name="prr3_15" descr="" access="RO" offset="0x20.11" size="0x0.6" />
	<field name="prr3_14" descr="" access="RO" offset="0x20.17" size="0x0.4" />
	<field name="prr3_13" descr="" access="RO" offset="0x20.22" size="0x0.6" />
	<field name="prr3_12" descr="" access="RO" offset="0x20.28" size="0x0.4" />
	<field name="prr3_23" descr="" access="RO" offset="0x24.0" size="0x0.6" />
	<field name="prr3_22" descr="" access="RO" offset="0x24.6" size="0x0.4" />
	<field name="prr3_21" descr="" access="RO" offset="0x24.11" size="0x0.6" />
	<field name="prr3_20" descr="" access="RO" offset="0x24.17" size="0x0.4" />
	<field name="prr3_19" descr="" access="RO" offset="0x24.22" size="0x0.6" />
	<field name="prr3_18" descr="" access="RO" offset="0x24.28" size="0x0.4" />
	<field name="prr3_29" descr="" access="RO" offset="0x28.0" size="0x0.6" />
	<field name="prr3_28" descr="" access="RO" offset="0x28.6" size="0x0.4" />
	<field name="prr3_27" descr="" access="RO" offset="0x28.11" size="0x0.6" />
	<field name="prr3_26" descr="" access="RO" offset="0x28.17" size="0x0.4" />
	<field name="prr3_25" descr="" access="RO" offset="0x28.22" size="0x0.6" />
	<field name="prr3_24" descr="" access="RO" offset="0x28.28" size="0x0.4" />
	<field name="prr3_31" descr="" access="RO" offset="0x2C.0" size="0x0.6" />
	<field name="prr3_30" descr="" access="RO" offset="0x2C.6" size="0x0.4" />
	<field name="prr4_0" descr="" access="RO" offset="0x2C.11" size="0x0.10" />
	<field name="prr4_1" descr="" access="RO" offset="0x2C.22" size="0x0.10" />
	<field name="prr4_2" descr="" access="RO" offset="0x30.0" size="0x0.10" />
	<field name="prr4_3" descr="" access="RO" offset="0x30.11" size="0x0.10" />
	<field name="prr4_4" descr="" access="RO" offset="0x30.22" size="0x0.10" />
	<field name="prr4_5" descr="" access="RO" offset="0x34.0" size="0x0.10" />
	<field name="prr4_6" descr="" access="RO" offset="0x34.11" size="0x0.10" />
	<field name="prr4_7" descr="" access="RO" offset="0x34.22" size="0x0.10" />
	<field name="prr5_0" descr="" access="RO" offset="0x38.22" size="0x0.10" />
	<field name="prr5_1" descr="" access="RO" offset="0x3C.0" size="0x0.10" />
	<field name="prr5_2" descr="" access="RO" offset="0x3C.11" size="0x0.10" />
	<field name="prr5_3" descr="" access="RO" offset="0x3C.22" size="0x0.10" />
	<field name="prr5_4" descr="" access="RO" offset="0x40.0" size="0x0.10" />
	<field name="prr5_5" descr="" access="RO" offset="0x40.11" size="0x0.10" />
	<field name="prr5_6" descr="" access="RO" offset="0x40.22" size="0x0.10" />
	<field name="prr5_7" descr="" access="RO" offset="0x44.0" size="0x0.10" />
	<field name="prr5_8" descr="" access="RO" offset="0x44.11" size="0x0.10" />
	<field name="prr5_9" descr="" access="RO" offset="0x44.22" size="0x0.10" />
	<field name="prr5_10" descr="" access="RO" offset="0x48.0" size="0x0.10" />
	<field name="prr5_11" descr="" access="RO" offset="0x48.11" size="0x0.10" />
	<field name="prr5_12" descr="" access="RO" offset="0x48.22" size="0x0.10" />
	<field name="prr6_0" descr="" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="prr1_6" descr="" access="RO" offset="0x54.0" size="0x0.4" />
	<field name="prr1_5" descr="" access="RO" offset="0x54.6" size="0x0.4" />
	<field name="prr1_4" descr="" access="RO" offset="0x54.12" size="0x0.4" />
	<field name="prr1_3" descr="" access="RO" offset="0x54.18" size="0x0.4" />
</node>

<node name="slprr_reg_ext" descr="" size="0x150.0" >
	<field name="status" descr="0: no_measurement_enabled\;1: measurement_in_progress\;2: measurement_done\;3: measurement_error\;Note - only 1 measurement at a time can be done." access="RO" enum="no_measurement_enabled=0x0,measurement_in_progress=0x1,measurement_done=0x2,measurement_error=0x3" offset="0x0.0" size="0x0.3" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;3 - Far-End Port (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number to access" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number / DataPath number for Retimer\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.10" />
	<field name="mode_b_idx" descr="0: mode_a - [Internal] Simplex\;1: mode_b - [Internal] Bidirectional" access="RO" enum="mode_a=0x0,mode_b=0x1" offset="0x0.29" size="0x0.1" />
	<field name="stop_measure" descr="0: do nothing\;1:Stop measure- [Internal] turn on PEQ" access="WO" offset="0x0.30" size="0x0.1" />
	<field name="start_measure" descr="0: do nothing\;1: Enable measurement\;\;Note: The measurement is destructive, once done, the link can&apos;t be used and need to restart" access="WO" offset="0x0.31" size="0x0.1" />
	<field name="meas_type" descr="Measurement type parameters:\;0: Data_address_read_0\;1: Data_address_read_1\;2: Data_address_read_2\;3: Data_address_read_3\;4: Data_address_read_4\;5: Data_address_read_5\;6: Data_address_read_6\;7: Extended_read_7 - [Internal] uphy 7 - EQ dump)\;10: Data_address_read_10 - [Internal] tx-D\;11: Data_address_read_11 - [Internal] tx-D\;12: Data_address_read_12 - [Internal] tx-D\;13: Data_address_read_13 - [Internal] tx-D\;14: Data_address_read_14 - [Internal] tx-D\;15: Data_address_read_15 - [Internal] tx-D\;16: Data_address_read_16 - [Internal] tx-D" access="INDEX" enum="Data_address_read_0=0x0,Data_address_read_1=0x1,Data_address_read_2=0x2,Data_address_read_3=0x3,Data_address_read_4=0x4,Data_address_read_5=0x5,Data_address_read_6=0x6,Extended_read_7=0x7,Data_address_read_10=0xa,Data_address_read_11=0xb,Data_address_read_12=0xc,Data_address_read_13=0xd,Data_address_read_14=0xe,Data_address_read_15=0xf,Data_address_read_16=0x10" offset="0x4.0" size="0x0.8" />
	<field name="timestamp_0" descr="Time stamp 16 MSB\;" access="RO" offset="0x4.10" size="0x0.16" />
	<field name="timestamp_1" descr="Time stamp 16 LSB\;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="temperature" descr="Temperature. [Internal] 1 Celsius resolution" access="RO" offset="0x8.22" size="0x0.10" />
	<field name="start_offset" descr="" access="RO" offset="0xC.0" size="0x0.10" />
	<field name="end_offset" descr="" access="RO" offset="0xC.12" size="0x0.10" />
	<field name="meas_data" descr="Table  2508, &quot;SLPRR Data Address Read 0 Layout,&quot; on page  2926\;Table  2510, &quot;SLPRR Data Address Read 1 Layout,&quot; on page  2926\;Table  2512, &quot;SLPRR Data Address Read 2 Layout,&quot; on page  2927\;Table  2514, &quot;SLPRR Data Address Read 3 Layout,&quot; on page  2927\;Table  2516, &quot;SLPRR Data Address Read 4 Layout,&quot; on page  2928\;Table  2518, &quot;SLPRR Data Address Read 5 Layout,&quot; on page  2928\;Table  2520, &quot;SLPRR Data Address Read 6 Layout,&quot; on page  2929\;Table  2522, &quot;SLPRR Extended read 7 Layout,&quot; on page  2929\;Table  2528, &quot;SLPRR Data Address Read 10 Layout,&quot; on page  2943\;Table  2530, &quot;SLPRR Data Address Read 11 Layout,&quot; on page  2943\;Table  2532, &quot;SLPRR Data Address Read 12 Layout,&quot; on page  2944\;Table  2534, &quot;SLPRR Data Address Read 13 Layout,&quot; on page  2944\;Table  2536, &quot;SLPRR Data Address Read 14 Layout,&quot; on page  2945\;Table  2538, &quot;SLPRR Data Address Read 15 Layout,&quot; on page  2945\;Table  2540, &quot;SLPRR Data Address Read 16 Layout,&quot; on page  2946" subnode="slprr_reg_meas_data_auto_ext" access="RW" offset="0x10.0" size="0x140.0" union_selector="$(parent).meas_type" />
</node>

<node name="slprr_reg_meas_data_auto_ext" descr="" attr_is_union="1" size="0x140.0" >
	<field name="slprr_Extended_read_7_ext" descr="" subnode="slprr_Extended_read_7_ext" offset="0x0.0" selected_by="Extended_read_7" size="0x58.0" />
	<field name="slrpp_data_read_0_ext" descr="" subnode="slrpp_data_read_0_ext" offset="0x0.0" selected_by="Data_address_read_0" size="0x140.0" />
	<field name="slrpp_data_read_10_ext" descr="" subnode="slrpp_data_read_10_ext" offset="0x0.0" selected_by="Data_address_read_10" size="0x140.0" />
	<field name="slrpp_data_read_11_ext" descr="" subnode="slrpp_data_read_11_ext" offset="0x0.0" selected_by="Data_address_read_11" size="0x140.0" />
	<field name="slrpp_data_read_12_ext" descr="" subnode="slrpp_data_read_12_ext" offset="0x0.0" selected_by="Data_address_read_12" size="0x140.0" />
	<field name="slrpp_data_read_13_ext" descr="" subnode="slrpp_data_read_13_ext" offset="0x0.0" selected_by="Data_address_read_13" size="0x140.0" />
	<field name="slrpp_data_read_14_ext" descr="" subnode="slrpp_data_read_14_ext" offset="0x0.0" selected_by="Data_address_read_14" size="0x140.0" />
	<field name="slrpp_data_read_15_ext" descr="" subnode="slrpp_data_read_15_ext" offset="0x0.0" selected_by="Data_address_read_15" size="0x140.0" />
	<field name="slrpp_data_read_16_ext" descr="" subnode="slrpp_data_read_16_ext" offset="0x0.0" selected_by="Data_address_read_16" size="0x80.0" />
	<field name="slrpp_data_read_1_ext" descr="" subnode="slrpp_data_read_1_ext" offset="0x0.0" selected_by="Data_address_read_1" size="0x140.0" />
	<field name="slrpp_data_read_2_ext" descr="" subnode="slrpp_data_read_2_ext" offset="0x0.0" selected_by="Data_address_read_2" size="0x140.0" />
	<field name="slrpp_data_read_3_ext" descr="" subnode="slrpp_data_read_3_ext" offset="0x0.0" selected_by="Data_address_read_3" size="0x140.0" />
	<field name="slrpp_data_read_4_ext" descr="" subnode="slrpp_data_read_4_ext" offset="0x0.0" selected_by="Data_address_read_4" size="0x140.0" />
	<field name="slrpp_data_read_5_ext" descr="" subnode="slrpp_data_read_5_ext" offset="0x0.0" selected_by="Data_address_read_5" size="0x140.0" />
	<field name="slrpp_data_read_6_ext" descr="" subnode="slrpp_data_read_6_ext" offset="0x0.0" selected_by="Data_address_read_6" size="0x80.0" />
</node>

<node name="slred_info_page_ext" descr="" size="0x24.0" >
	<field name="mv_ticks_res" descr="resolution for each tick in the voltage axis in units of 0.1mV" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="ps_ticks_res" descr="resolution for each tick in the phase axis in units of 0.01ps" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="mv_center_pos" descr="center position of eye in 0.1mV" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="ps_center_pos" descr="center position of eye in 0.01ps" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="margin" descr="The margin that the lane received based on a specific configuration." access="RO" offset="0x8.0" size="0x0.24" />
	<field name="margin_version" descr="" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="height_eo_neg" descr="Voltage offset from eye center to the negative side of the upper eye in 0.1mV." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="height_eo_pos" descr="Voltage offset from eye center to the positive side of the upper eye in 0.1mV." access="RO" offset="0xC.16" size="0x0.16" />
	<field name="phase_eo_neg" descr="The offset from the eye center to the negative (left) side of the upper eye in 0.01ps." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="phase_eo_pos" descr="The offset from the eye center to the positive (right) side of the upper eye in 0.01ps." access="RO" offset="0x10.16" size="0x0.16" />
</node>

<node name="slred_page_data_ext" descr="" size="0xa0.0" >
	<field name="err_val" descr="Each err_val is 4 bits in ascending order. Each page contains 320 err values." access="RO" high_bound="319" low_bound="0" offset="0x0.28" size="0xa0.0" />
</node>

<node name="slred_reg_ext" descr="" size="0xa8.0" >
	<field name="page_data_sel" descr="select page data number to display.\;0 - info page data\;1 - page data 1 (indexes 0 to 319)\;2 - page data 2 (indexes 320 to 639)\;3 - page data 3 (indexes 640 to 959)\;4 - page data 4 (indexes 960 to 1279)\;5 - page data 5 (indexes 1280 to 1599)\;6 - page data 6 (indexes 1600 to 1919)\;7 - page data 7 (indexes 1920 to 2239)" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="1 - 28nm products\;3 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="eye scan status:\;0 - eye scan was not performed.\;1 - unsupported scan for current speed.\;2 - system busy.\;3 - Performing eye scan.\;4 - eye scan completed. \;5 - error, eye scan not completed." access="RO" offset="0x0.28" size="0x0.4" />
	<field name="lane_speed" descr="The lane speed on which the eye scan was measured\;0-1 - reserved\;2 - QDR (10 Gb/s) / Gen3 (PCIe)\;3 - FDR10 (10GE / 40GE) (10.3125 Gb/s) \;4 - FDR (56GE) (14.0625 Gb/s) / Gen4 (PCIe)\;5 - EDR (25GE / 50GE / 100GE) (25.78125 Gb/s) / Gen5 (PCIe)\;6 - HDR (50GE / 200GE / 400GE) (26.5625Gbd / 53.125Gb/s) \;7 - 15 - reserved" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="abort" descr="gracefully abort the scan process.\;abort and en bits cannot be set together." access="WO" offset="0x4.14" size="0x0.1" />
	<field name="err_res_base" descr="base value for calculating err_val legend. \;0 - err_res_base is 2\;1 - err_res_base is 3\;2 - err_res_base is 5\;3 - err_res_base is 1\;4-7 - reserved\;\;if err_res_scale is exponential:\;err value &gt; 0 will represent errors between err_res_base ^(err_val - 1) +1 to err_res_base^err_val\;\;For example if err_res_base is 2:\;0 err_value represents 0 errors\;1 err_value represents 1-2 errors\;2 err_value represents 3-4 errors\;3 err_value represents 5-8 errors\;...\;7 err_value represents 2^6+1 and above\;\;if err_res_scale is linear:\;err value &gt; 0 will represent errors between err_res_base *(err_val-1) + 1 to err_res_base *err_val\;\;For example if err_res_base is 2:\;0 err_value represents 0 errors\;1 err_value represents 1-2 errors\;2 err_value represents 3-4 errors\;3 err_value represents 5-6 errors\;...\;7 err_value represents 2*6 + 1 and above\;" access="RW" offset="0x4.15" size="0x0.3" />
	<field name="eye_sel" descr="eye selection for PAM4 signals.\;0 - up\;1 - mid\;2 - down\;Note: for NRZ field is ignored" access="RW" offset="0x4.18" size="0x0.2" />
	<field name="measure_time" descr="max measure time in seconds for single eye diagram.\;0 - 10 sec\;1 - 30 sec\;2 - 60 sec\;3 - 90 sec\;4 - 120 sec\;5 - 240 sec\;6 - 480 sec\;7 - 600 sec\;8 - 900 sec\;9-15 reserved\;each tic measure time will be measure_time / (height_dim x width_dim)" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="eye_diag_dim" descr="dimensions of eye scan matrix in the format of height_dim x width_dim\;0 - 16x16 (256 err val)\;1 - 32x32 (1024 err val)\;2 - 32x64 (1024 err val)\;3 - 64x32 (2048 err val)" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="err_res_scale" descr="error res multiplier for err_res_base field\;0 - exponential scale\;1 - linear scale\;2-3 - reserved" access="RW" offset="0x4.27" size="0x0.2" />
	<field name="destructive_ctrl" descr="0 - non destructive scan\;1 - destructive scan\;Note: if non destructive scan is not supported this field is ignored and a destructive scan will be operated" access="RW" offset="0x4.29" size="0x0.1" />
	<field name="last_scan" descr="set to &apos;1&apos; when performing last eye scan for lane.\;For example: when scanning 3 eyes in the order of up, mid, down. field should be set when scanning down eye.\;If scanning only 1 eye, field should be set." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="en" descr="start eye scan" access="WO" offset="0x4.31" size="0x0.1" />
	<field name="page_data" descr="page data for index page_data_sel\;page 0 will contain info page data.\;Table  2356, &quot;SLRED - SerDes Lane Receive Eye Diagram Register Layout for info page,&quot; on page  2803\;the page data 1-7 will contain the err_val for each index in ascending order.\;Table  2358, &quot;SLRED - SerDes Lane Receive Eye Diagram Register Layout for page_data,&quot; on page  2804\;Each err_val[i] represents the bit errors of row floor(i / width_dim)\;and column i mod width_dim.\;Matrix is built starting from the left bottom corner.\;each err_val indicates the number of bit errors for one tick" subnode="slred_reg_page_data_auto_ext" access="RO" offset="0x8.0" size="0xa0.0" />
</node>

<node name="slred_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0xa0.0" >
	<field name="slred_info_page_ext" descr="" subnode="slred_info_page_ext" offset="0x0.0" size="0x24.0" />
	<field name="slred_page_data_ext" descr="" subnode="slred_page_data_ext" offset="0x0.0" size="0xa0.0" />
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
	<field name="fom_mode" descr="FOM type measurement.\;0: SNR - bit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values.\;Returned SNR value is based on definition in CMIS spec.\;" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="fom_averaging_cap" descr="When set, Indicates averaging is supported for the measurement chosen in fom_mode. This can be used to stabilize returned values.\;The averaging capability is only relevant for periodic fom measurements, meaning the value in fom_update_period for the chosen fom is not zero." access="RO" offset="0x0.6" size="0x0.1" />
	<field name="fom_averaging_en" descr="Determines if returned measurement chosen in fom_mode will be a calculated average of previous measurements, or the latest single measurement of the chosen fom. Number of averaged measurements is set in fom_averaging_window.\;0: Latest measurement\;1: Averaged measurement" access="RW" offset="0x0.7" size="0x0.1" />
	<field name="fom_averaging_window" descr="Configures the number of measurements that will be averaged to calculate the returned fom measurement. Averaging window size will be &lt;fom_averaging_window&gt;+1." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="fom_update_period" descr="Returns the time period in which a new fom measurement will be available periodically, according to the measurement chosen in fom_mode. Value is in units of 1 [msec].\;\;If the value equals to &quot;0&quot;, the fom is on demand only, and a measurement will not occur unless requested." access="RO" offset="0x0.16" size="0x0.16" />
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
	<field name="all_lanes" descr="Set 1 for all lanes measurement page. For Retimer, will conduct measurement on all active lanes under the chosen side - Host / Line.\;Supported if PCAM.feature_cap_mask bit 91 is set.\;Mutually exclusive with measurements_thresholds index. Only one of measurements_thresholds index and all_lanes index can be set to &apos;1&apos; at the same time.\;Relevant only for 5nm.\;0: per_lane_measurement\;1: all_lane_measurement" access="INDEX" enum="per_lane_measurement=0x0,all_lane_measurement=0x1" offset="0x0.1" size="0x0.1" />
	<field name="measurements_thresholds" descr="Set 1 for measurements thresholds page.\;Supported if PCAM.feature_cap_mask bit 126 is set.\;Mutually exclusive with all_lanes index. Only one of measurements_thresholds index and all_lanes index can be set to &apos;1&apos; at the same time.\;Relevant only for 5nm.\;0: measurements_page\;1: measurements_threshold_page" access="INDEX" enum="measurements_page=0x0,measurements_threshold_page=0x1" offset="0x0.2" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: NearEnd_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: FarEnd_Port - (For Retimer/Gearbox - Line side)\;\;" access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number.\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: prod_40nm\;1: prod_28nm\;3: prod_16nm\;4: prod_7nm\;5: prod_5nm - (SerDes Gen7.0/ 7.5)\;6: serdes_gen_8" access="RO" enum="prod_40nm=0x0,prod_28nm=0x1,prod_16nm=0x3,prod_7nm=0x4,prod_5nm=0x5,serdes_gen_8=0x6" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid\;1 - Valid\;" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="Table  2108, &quot;SLRG - SerDes Lane Receive Grade Register Layout for 40nm and 28nm,&quot; on page  2490\;Section  2110, &quot;SLRG - SerDes Lane Receive Grade Register Layout for 16nm,&quot; on page  2491\;Section  2112, &quot;SLRG - SerDes Lane Receive Grade Register Layout for 7nm,&quot; on page  2493\;Section  2114, &quot;SLRG - SerDes Lane Receive Grade Register Layout for 5nm,&quot; on page  2495\;Section  2122, &quot;SLRG all lanes FOM for 5nm- Layout,&quot; on page  2499\;Section  2124, &quot;SLRG - SerDes Lane Receive Grade Register Layout for Serdes_gen_8,&quot; on page  2500\;Section  2126, &quot;SLRG Measurements Thresholds for 5nm- Layout,&quot; on page  2503" subnode="slrg_reg_page_data_auto_ext" access="RO" condition="$(parent).port_type AND $(parent).version AND $(parent).all_lanes AND $(parent).measurements_thresholds" offset="0x4.0" size="0x24.0" />
</node>

<node name="slrg_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x24.0" >
	<field name="slrg_16nm_ext" descr="" subnode="slrg_16nm_ext" condition="($(parent).port_type == Network_Port AND ($(parent).version == prod_16nm))" offset="0x0.0" size="0x24.0" />
	<field name="slrg_40nm_28nm_ext" descr="" subnode="slrg_40nm_28nm_ext" condition="($(parent).port_type == Network_Port AND ($(parent).version == prod_40nm | $(parent).version == prod_28nm))" offset="0x0.0" size="0x24.0" />
	<field name="slrg_5nm_ext" descr="" subnode="slrg_5nm_ext" condition="(($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm AND $(parent).all_lanes == per_lane_measurement AND $(parent).measurements_thresholds == measurements_page))" offset="0x0.0" size="0x18.0" />
	<field name="slrg_7nm_ext" descr="" subnode="slrg_7nm_ext" condition="(($(parent).port_type == Network_Port | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_7nm))" offset="0x0.0" size="0x18.0" />
	<field name="slrg_all_lanes_5nm_ext" descr="" subnode="slrg_all_lanes_5nm_ext" condition="(($(parent).port_type == Network_Port || $(parent).port_type == NearEnd_Port  || $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm AND $(parent).all_lanes == all_lane_measurement AND $(parent).measurements_thresholds == measurements_page))" offset="0x0.0" size="0x14.0" />
	<field name="slrg_serdes_gen_8_ext" descr="" subnode="slrg_serdes_gen_8_ext" condition="(($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == serdes_gen_8))" offset="0x0.0" size="0x18.0" />
	<field name="slrg_thresholds_5nm_ext" descr="" subnode="slrg_thresholds_5nm_ext" condition="(($(parent).port_type == Network_Port || $(parent).port_type == NearEnd_Port  || $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm AND $(parent).all_lanes == per_lane_measurement AND $(parent).measurements_thresholds == measurements_threshold_page))" offset="0x0.0" size="0x14.0" />
</node>

<node name="slrg_serdes_gen_8_ext" descr="" size="0x18.0" >
	<field name="fom_measurement" descr="Bitmask for measurement activation\;Bit 0 - Upper eye\;Bit 1 - Middle eye\;Bit 2 - Lower eye\;Bit 3- Composite eye\;Note: NRZ only Bit 3 is valid" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="initial_fom" descr="measured EOM status after FEQ.\;valid only when SLRG.status is &apos;1&apos;" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="fom_mode" descr="fom mode:\;FOM eye mode to search\;0x0: FOM_MODE_EYE_OPEN\;0x1: FOM_MODE_EYEO_SNR\;0x2: FOM_MODE_NORM_SNR\;0x3: FOM_MODE_EYE_LVLN\;0x4: FOM_MODE_EYE_LVLP\;0x5: FOM_MODE_THRES_NERR\;0x6: FOM_MODE_CDR_NERR\;0x7: FOM_MODE_CSDET_NERR\;0x8: FOM_MODE_MLSE_NERR\;0x9: FOM_MODE_SFEC_NERR\;\;\;" access="RW" enum="FOM_MODE_EYE_OPEN=0x0,FOM_MODE_EYEO_SNR=0x1,FOM_MODE_NORM_SNR=0x2,FOM_MODE_EYE_LVLN=0x3,FOM_MODE_EYE_LVLP=0x4,FOM_MODE_THRES_NERR=0x5,FOM_MODE_CDR_NERR=0x6,FOM_MODE_CSDET_NERR=0x7,FOM_MODE_MLSE_NERR=0x8,FOM_MODE_SFEC_NERR=0x9" offset="0x4.16" size="0x0.4" />
	<field name="fom_meas_type_read" descr="Indicate if the fom_measurement is of PAM4 or NRZ data\;\;0 - PAM4 (Upper, mid, low eye)\;1 - NRZ (Composite eye)" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="upper_eye" descr="last measured EOM-FOM status of upper eye.\;valid only if fom_measurement bit &apos;0&apos; is set" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="last_fom" descr="last measured EOM-FOM status of composite eye.\;valid only if fom_measurement bit &apos;3&apos; is set" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="lower_eye" descr="last measured EOM-FOM status of lower eye.\;valid only if fom_measurement bit &apos;2&apos; is set" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="mid_eye" descr="last measured EOM-FOM status of middle eye.\;valid only if fom_measurement bit &apos;1&apos; is set" access="RO" offset="0xC.16" size="0x0.16" />
</node>

<node name="slrg_thresholds_5nm_ext" descr="" size="0x14.0" >
	<field name="snr_thresholds_valid" descr="When set SNR alarm and warning threshold fields are valid\;0: not_valid\;1: valid" access="RO" enum="not_valid=0x0,valid=0x1" offset="0x0.31" size="0x0.1" />
	<field name="snr_line_low_warning" descr="Line side warning threshold for SNR value. If SNR value goes below this value, it should be considered as a warning" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="snr_line_low_alarm" descr="Line side alarm threshold for SNR value. If SNR value goes below this value, it should be considered as an alarm" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="snr_host_low_warning" descr="Host side warning threshold for SNR value. If SNR value goes below this value, it should be considered as a warning" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="snr_host_low_alarm" descr="Host side alarm threshold for SNR value. If SNR value goes below this value, it should be considered as an alarm" access="RO" offset="0x8.16" size="0x0.16" />
</node>

<node name="slrpp_data_read_0_ext" descr="" size="0x140.0" >
	<field name="dword_0" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_10_ext" descr="" size="0x140.0" >
	<field name="dword_0" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_11_ext" descr="" size="0x140.0" >
	<field name="dword_80" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_12_ext" descr="" size="0x140.0" >
	<field name="dword_160" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_13_ext" descr="" size="0x140.0" >
	<field name="dword_240" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_14_ext" descr="" size="0x140.0" >
	<field name="dword_320" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_15_ext" descr="" size="0x140.0" >
	<field name="dword_400" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_16_ext" descr="" size="0x80.0" >
	<field name="dword_480" descr="Data in DWORDS of stored measured data." access="RO" high_bound="31" low_bound="0" offset="0x0.0" size="0x80.0" />
</node>

<node name="slrpp_data_read_1_ext" descr="" size="0x140.0" >
	<field name="dword_80" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_2_ext" descr="" size="0x140.0" >
	<field name="dword_160" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_3_ext" descr="" size="0x140.0" >
	<field name="dword_240" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_4_ext" descr="" size="0x140.0" >
	<field name="dword_320" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_5_ext" descr="" size="0x140.0" >
	<field name="dword_400" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slrpp_data_read_6_ext" descr="" size="0x80.0" >
	<field name="dword_480" descr="Data in DWORDS of stored measured data." access="RO" high_bound="31" low_bound="0" offset="0x0.0" size="0x80.0" />
</node>

<node name="slsir_5nm_ext" descr="" size="0x24.0" >
	<field name="uphy_ver_minor" descr="UPHY version" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="uphy_ver_major" descr="UPHY version" access="RO" offset="0x20.4" size="0x0.4" />
	<field name="bkv_minor_dln" descr="BKV dln version" access="RO" offset="0x20.16" size="0x0.4" />
	<field name="bkv_major_dln" descr="BKV dln version" access="RO" offset="0x20.20" size="0x0.4" />
	<field name="bkv_minor_cln" descr="BKV cln version" access="RO" offset="0x20.24" size="0x0.4" />
	<field name="bkv_major_cln" descr="BKV cln version" access="RO" offset="0x20.28" size="0x0.4" />
</node>

<node name="slsir_7nm_ext" descr="" size="0x90.0" >
	<field name="uphy_rev_minor" descr="UPHY revision" access="RO" offset="0x18.0" size="0x0.4" />
	<field name="uphy_rev_major" descr="UPHY revision" access="RO" offset="0x18.4" size="0x0.4" />
	<field name="bkv_revision_rx" descr="DLN RX BKV revision\;For UPHY Rev 6.* and 7.* the format of BKV revision is\;Bits 7:4 - Major\;Bits 3:0 - Minor" access="RO" offset="0x18.8" size="0x0.8" />
	<field name="bkv_revision_cln" descr="CLN BKV revision\;For UPHY Rev 6.* and 7.* the format of BKV revision is\;Bits 7:4 - Major\;Bits 3:0 - Minor" access="RO" offset="0x18.16" size="0x0.8" />
	<field name="uphy_rev_subminor" descr="UPHY subminor revision.\;when 0, indicates no subminor revision" access="RO" offset="0x18.24" size="0x0.4" />
</node>

<node name="slsir_reg_ext" descr="" size="0x94.0" >
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;4 - USR Main\;5 - USR Tile\;Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="4: prod_7nm - \;5: prod_5nm - (Uphy 7.0/ 7.5)\;6: serdes_gen_8" access="RO" enum="prod_7nm=0x4,prod_5nm=0x5,serdes_gen_8=0x6" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - invalid\;1 - valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="Table 2392, &quot;SLSIR - SerDes Lane Status Info Register Layout for 7nm,&quot; on page 2825\;Table 2394, &quot;SLSIR - SerDes Lane Status Info Register Layout for 5nm,&quot; on page 2830\;Table 2396, &quot;SLSIR - SerDes Lane Status Info Register Layout for Serdes_gen_8,&quot; on page 2832" subnode="slsir_reg_page_data_auto_ext" access="RW" offset="0x4.0" size="0x90.0" union_selector="$(parent).version" />
</node>

<node name="slsir_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x90.0" >
	<field name="slsir_5nm_ext" descr="" subnode="slsir_5nm_ext" offset="0x0.0" selected_by="prod_5nm" size="0x24.0" />
	<field name="slsir_7nm_ext" descr="" subnode="slsir_7nm_ext" offset="0x0.0" selected_by="prod_7nm" size="0x90.0" />
	<field name="slsir_serdes_gen_8_ext" descr="" subnode="slsir_serdes_gen_8_ext" offset="0x0.0" selected_by="serdes_gen_8" size="0x24.0" />
</node>

<node name="slsir_serdes_gen_8_ext" descr="" size="0x24.0" >
	<field name="uphy_ver_minor" descr="UPHY version" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="uphy_ver_major" descr="UPHY version" access="RO" offset="0x20.4" size="0x0.4" />
	<field name="bkv_minor_dln" descr="BKV dln version" access="RO" offset="0x20.16" size="0x0.4" />
	<field name="bkv_major_dln" descr="BKV dln version" access="RO" offset="0x20.20" size="0x0.4" />
	<field name="bkv_minor_cln" descr="BKV cln version" access="RO" offset="0x20.24" size="0x0.4" />
	<field name="bkv_major_cln" descr="BKV cln version" access="RO" offset="0x20.28" size="0x0.4" />
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
	<field name="lane_speed" descr="Reserved for PCIe.\;The lane speed for TX settings:\;0 - SDR / Gen1 (PCIe)\;1 - DDR / Gen2 (PCIe) / 5GBASE-R\;2 - QDR / Gen3 (PCIe)\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE) / Gen4 (PCIe)\;5 - EDR (25GE / 50GE / 100GE) / Gen5 (PCIe)\;6 - HDR (50GE / 200GE / 400GE)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;8 - XDR / NVL6 / 200G_1x_simplex (106.25 Gbd / 212.5Gb/s)\;9 - Reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13 - NVL6 / 360G_2x_bidi (90 Gbd / 180Gb/s)\;14 - NVL6 / 400G_2x_bidi (100 Gbd / 200Gb/s)\;15 - NVL6 / 328G_2x_bidi (82 Gbd / 164 Gb/s)" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="conf_mod" descr="Set configuration mode for 7nm/5nm product.\;0: tx_linear - when set, tx taps are configured from\;for 7nm\;Table  2092, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 7nm,&quot; on page  2471\;For 5nm\;Table  2096, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 5nm,&quot; on page  2476\;LUT table fields are ignored\;1: tx_lut - when set, tx taps are configured from\;Table  2094, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for LUT 7nm,&quot; on page  2472\;7nm_fir_taps page fields are ignored." access="OP" enum="tx_linear=0x0,tx_lut=0x1" offset="0x0.12" size="0x0.1" />
	<field name="tx_policy" descr="Configures Tx parameter set policy\;0 - Tx parameters will be set according to best possible configuration chosen by the system\;1 - Tx parameters will be set according to Data Base only and will not be overridden by link training (e.g KR-Startup)" access="RW" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: prod_40nm\;1: prod_28nm\;3: prod_16nm\;4: prod_7nm\;5: prod_5nm - (UPHY 7.0/7.5)\;6: serdes_gen_8" access="RO" enum="prod_40nm=0x0,prod_28nm=0x1,prod_16nm=0x3,prod_7nm=0x4,prod_5nm=0x5,serdes_gen_8=0x6" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="Indicates that Tx setting readout is valid and active. In particular, for links that do AN/LT, valid will be set when link operational status is UP (PAOS.oper_status=0x1).\;For links without AN/LT, valid will be set when Tx is enabled.\;\;0 - Invalid\;1 - Valid\;\;Note: Get and Set operations can be set when status = invalid." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="page_data" descr="Table  2086, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 28nm and 40nm,&quot; on page  2468\;Table  2088, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 16nm,&quot; on page  2469\;Table  2092, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 7nm,&quot; on page  2471\;Table  2094, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for LUT 7nm,&quot; on page  2472\;Table  2096, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 5nm,&quot; on page  2476\;Table  2098, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for Serdes_gen_8,&quot; on page  2479" subnode="sltp_reg_page_data_auto_ext" access="RW" condition="$(parent).port_type AND $(parent).version" offset="0x4.0" size="0x48.0" />
</node>

<node name="sltp_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x48.0" >
	<field name="sltp_16nm_ext" descr="" subnode="sltp_16nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version == prod_16nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_28nm_40nm_ext" descr="" subnode="sltp_28nm_40nm_ext" condition="($(parent).port_type == Network_Port) AND ($(parent).version == prod_40nm | $(parent).version == prod_28nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_5nm_ext" descr="" subnode="sltp_5nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_7nm_ext" descr="" subnode="sltp_7nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version == prod_7nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_lut_7nm_ext" descr="" subnode="sltp_lut_7nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version == prod_7nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_serdes_gen_8_ext" descr="" subnode="sltp_serdes_gen_8_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version ==serdes_gen_8)" offset="0x0.0" size="0x48.0" />
</node>

<node name="sltp_serdes_gen_8_ext" descr="" size="0x48.0" >
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;Bit 0: tap0_is_out_of_range\;Bit 1: tap1_is_out_of_range\;Bit 2: tap2_is_out_of_range\;Bit 3: tap3_is_out_of_range\;Bit 4: tap4_is_out_of_range\;Bit 5: tap5_is_out_of_range\;Bit 6: tap6_is_out_of_range\;Bit 7: tap7_is_out_of_range\;Bit 8: tap8_is_out_of_range\;Bit 9: tap9_is_out_of_range\;Bit 10: tap10_is_out_of_range\;Bit 11: tap11_is_out_of_range\;Bit 9: sum_of_taps_is_out_of_range" access="RO" enum="tap0_is_out_of_range=0x1,tap1_is_out_of_range=0x2,tap2_is_out_of_range=0x4,tap3_is_out_of_range=0x8,tap4_is_out_of_range=0x10,tap5_is_out_of_range=0x20,tap6_is_out_of_range=0x40,tap7_is_out_of_range=0x80,tap8_is_out_of_range=0x100,tap9_is_out_of_range=0x200,tap10_is_out_of_range=0x400,tap11_is_out_of_range=0x800,sum_of_taps_is_out_of_range=0x200" offset="0x0.0" size="0x0.16" />
	<field name="mode_b_idx" descr="0: mode_a - [Internal] Simplex\;1: mode_b - [Internal] Bidirectional" access="RO" enum="mode_a=0x0,mode_b=0x1" offset="0x0.23" size="0x0.1" />
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
	<field name="lane_speed" descr="Reserved for PCIe.\;The lane speed for TX settings:\;0 - SDR / Gen1 (PCIe)\;1 - DDR / Gen2 (PCIe) / 5GBASE-R\;2 - QDR / Gen3 (PCIe)\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE) / Gen4 (PCIe)\;5 - EDR (25GE / 50GE / 100GE) / Gen5 (PCIe)\;6 - HDR (50GE / 200GE / 400GE)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;8 - XDR / NVL6 / 200G_1x_simplex (106.25 Gbd / 212.5Gb/s)\;9 - Reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13 - NVL6 / 360G_2x_bidi (90 Gbd / 180Gb/s)\;14 - NVL6 / 400G_2x_bidi (100 Gbd / 200Gb/s)\;15 - NVL6 / 328G_2x_bidi (82 Gbd / 164 Gb/s)" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="tx_policy" descr="Configures Tx parameter set policy\;0 - Tx parameters will be set according to best possible configuration chosen by the system\;1 - Tx parameters will be set according to Data Base only and will not be overridden by link training (e.g KR-Startup)" access="RW" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="5: prod_5nm\;6: serdes_gen_8" access="RO" enum="prod_5nm=0x5,serdes_gen_8=0x6" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="Indicates that Tx setting readout is valid and active. In particular, for links that do AN/LT, valid will be set when link operational status is UP (PAOS.oper_status=0x1).\;For links without AN/LT, valid will be set when Tx is enabled.\;\;0 - Invalid\;1 - Valid\;\;Note: Get and Set operations can be set when status = invalid." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="page_data" descr="Table  2102, &quot;SLTPv2 - SerDes Lane Transmit Parameters v2 Register Layout for LUT 5nm,&quot; on page  2484\;Table  2104, &quot;SLTPv2 - SerDes Lane Transmit Parameters v2 Register Layout for LUT Serdes_gen_8,&quot; on page  2486" subnode="sltpv2_reg_page_data_auto_ext" access="RW" condition="$(parent).port_type AND $(parent).version" offset="0x4.0" size="0x108.0" />
</node>

<node name="sltpv2_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x108.0" >
	<field name="sltpv2_lut_5nm_ext" descr="" subnode="sltpv2_lut_5nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm)" offset="0x0.0" size="0x108.0" />
	<field name="sltpv2_serdes_gen_8_ext" descr="" subnode="sltpv2_serdes_gen_8_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == serdes_gen_8)" offset="0x0.0" size="0x108.0" />
</node>

<node name="sltpv2_serdes_gen_8_ext" descr="" size="0x108.0" >
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;Bit 0:LUT_value_is_out_of_range\;Bit 1: delay_0_invalid\;Bit 2: delay_1_invalid\;Bit 3: delay_2_invalid" access="RO" enum="delay_2_invalid=0x8" offset="0x0.0" size="0x0.16" />
	<field name="lut_sel" descr="0: LUT_1 - taps 0-1 (16 entries), valid ranges per entry: [-16, 15]\;1: LUT_2 - taps 2-5 (256 entries), valid ranges per entry: [-64, 63]\;2: LUT_3 - taps 6-8 (64 entries), valid ranges per entry: [-16, 15]\;3: LUT_4 - taps 9-11 (64 entries), valid ranges per entry: [-16, 15]\;\;Note that only LUT_2 group has FW DB, hence c_db shall work only for LUT_2." access="INDEX" enum="LUT_1=0x0,LUT_2=0x1,LUT_3=0x2,LUT_4=0x3" offset="0x0.20" size="0x0.4" />
	<field name="mode_b_idx" descr="0: mode_a - [Internal] Simplex\;1: mode_b - [Internal] Bidirectional" access="RO" enum="mode_a=0x0,mode_b=0x1" offset="0x0.27" size="0x0.1" />
	<field name="vs_peer_db" descr="relevant for when c_db is set, else field is ignored.\;for when direct drive module connected:\;0 - db to override is for Did vs Did\;1 - db to override if for Did vs retimed module\;" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="no_db_set" descr="supported only if PCAM bit 96 in feature_cap_mask is set.\;When set, Tx DB will not be written into HW on linkup phase.\;When cleared, Tx DB is written into HW on linkup phase." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="delay0" descr="relevant for LUT3 (taps6-8), LUT4 (taps9-11). ignore otherwise.\;even taps (6, 8. 10) can get even values\;odd taps (7, 9, 11) cam get odd values." access="RW" offset="0x4.0" size="0x0.6" />
	<field name="delay1" descr="relevant for LUT3 (taps6-8), LUT4 (taps9-11). ignore otherwise.\;even taps (6, 8. 10) can get even values\;odd taps (7, 9, 11) cam get odd values." access="RW" offset="0x4.6" size="0x0.6" />
	<field name="delay2" descr="relevant for LUT3 (taps6-8), LUT4 (taps9-11). ignore otherwise.\;even taps (6, 8. 10) can get even values\;odd taps (7, 9, 11) cam get odd values." access="RW" offset="0x4.12" size="0x0.6" />
	<field name="lut" descr="Lookup Table values per entry" access="RW" high_bound="255" low_bound="0" offset="0x8.24" size="0x100.0" />
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

<node name="under_voltage_stressor_parameters_ext" descr="" size="0x4.0" >
	<field name="under_voltage_percentage_change" descr="The percentage change in 1% units\;If percentage change is over 1 percentage point or change from previous request, FW will return BAD PARAM" access="RW" offset="0x0.0" size="0x0.6" />
</node>

<node name="vhca_icm_ctrl_ext" descr="" size="0x40.0" >
	<field name="vhca_id" descr="vHCA Identifier. \;Valid only when vhca_id_valid" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="vhca_id_valid" descr="If set vhac_id field is valid. otherwise, own vhca_id is used." access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="rst_max_reached_alloc_icm" descr="If set, reset max_reached_alloc_icm field." access="WO" offset="0x4.29" size="0x0.1" />
	<field name="max_alloc_icm_th_mask" descr="If set, indicating max_alloc_icm_th is valid to be updated in write operation." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="max_alloc_icm_th" descr="This field sets the maximum allocated ICM for new allocations of specific vHCA in granularity of 4KB.\;Value 2^32-1 represents infinity.. The allocation must be equal or smaller than total_icm\;The allocation might be round up to next page size." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="cur_alloc_icm" descr="This field indicates the current allocated ICM in granularity of 4KB." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="max_reached_alloc_icm" descr="This field indicates the maximum allocated ICM in granularity 4KB." access="RO" offset="0x20.0" size="0x4.0" />
</node>

<node name="vhca_trust_level_ext" descr="" size="0x10.0" >
	<field name="vhca_id" descr="Valid only when all_vhca==0" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="all_vhca" descr="If set, set turst_level to all vHCAs that belong to this vport_group_manager.\;Supported for Set operation only." access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="trust_level" descr="Bitmask indicates trust levels supported for a vhca\;Bit 0: FULL_TRUST" access="RW" enum="FULL_TRUST=0x1" offset="0x4.0" size="0x4.0" />
</node>

<node name="ztt_ext" descr="" size="0x10.0" >
	<field name="operation" descr="0x0: DISABLE\;0x1: ENABLED\;0x2: RESET" access="WO" enum="DISABLE=0x0,ENABLED=0x1,RESET=0x2" offset="0x0.0" size="0x0.3" />
	<field name="status" descr="0x0: ZTT_DISABLED\;0x1: ZTT_ENABLED\;0x2: ZTT_ERROR" access="RO" enum="ZTT_DISABLED=0x0,ZTT_ENABLED=0x1,ZTT_ERROR=0x2" offset="0x0.8" size="0x0.3" />
</node>

<node name="root" size="0x300.0" descr="" >
	<field name="register_access_table_hca_ext_Nodes" offset="0x0.0" size="0x300.0" subnode="register_access_table_hca_ext_Nodes" descr="" />
</node>

<node name="register_access_table_hca_ext_Nodes" size="0x300.0" attr_is_union="1" descr="" >
	<field name="access_reg_summary_selector_ext" offset="0x0.0" size="0x300.0" subnode="access_reg_summary_selector_ext" descr="" />
</node>
</NodesDefinition>
