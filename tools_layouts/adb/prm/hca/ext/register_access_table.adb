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
<info source_doc_name="Mellanox &lt;Doc Name&gt;" source_doc_version="Rev 0.60" />
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

<node name="MRFV_CVB_ext" descr="" size="0x4.0" >
	<field name="cvb_data_index" descr="CVB Data\;Process Sigma = -4 + 0.5 * cvb_data_index\;cvb_data_index valid values 0 .. 15\;For Retimer\;Process Sigma &lt;-&gt; DVDD (mV)\;-4.0: 856.00\;-3.5: 847.75\;-3.0: 839.50\;-2.5: 831.25\;-2.0: 823.00\;-1.5: 814.75\;-1.0: 806.50\;-0.5: 798.25\;0 (nominal): 790.00\;0.5: 781.75\;1.0: 773.50\;1.5: 765.25\;2.0: 757.00\;2.5: 748.75\;3.0: 740.50\;3.5: 732.25\;4.0: 724.00" access="RO" offset="0x0.0" size="0x0.5" />
</node>

<node name="MRFV_PVS_MAIN_ext" descr="" size="0x4.0" >
	<field name="pvs_main_data" descr="PVS Data\;Range 0.675 - 0.75\;Vdd = 750mV - (fuse value - 1)*5mV" access="RO" offset="0x0.0" size="0x0.5" />
</node>

<node name="MRFV_PVS_TILE_ext" descr="" size="0x4.0" >
	<field name="pvs_tile_data" descr="PVS tile Data\;Range 0.675 - 0.72\;Vdd = 750mV - (fuse value - 1)*5mV" access="RO" offset="0x0.0" size="0x0.5" />
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
	<field name="MRFV_CVB_ext" descr="" subnode="MRFV_CVB_ext" offset="0x0.0" selected_by="cvb" size="0x4.0" />
	<field name="MRFV_ULT_ext" descr="" subnode="MRFV_ULT_ext" offset="0x0.0" selected_by="ULT" size="0xc.0" />
	<field name="MRFV_PVS_MAIN_ext" descr="" subnode="MRFV_PVS_MAIN_ext" offset="0x0.0" selected_by="pvs_main_die" size="0x4.0" />
	<field name="MRFV_PVS_TILE_ext" descr="" subnode="MRFV_PVS_TILE_ext" offset="0x0.0" selected_by="pvs_tile_0" size="0x4.0" />
</node>

<node name="MRFV_ext" descr="" size="0x40.0" >
	<field name="fuse_id" descr="Fuse Index\;0: cvb - CVB Main Die, used for Retimer\;1: ULT - used for Retimer\;2: pvs_main_die - (used for SPC-4)\;3: pvs_tile_0 - (used for SPC-4)\;4: pvs_tile_1 - (used for SPC-4)\;5: pvs_tile_2 - (used for SPC-4)\;6: pvs_tile_3 - (used for SPC-4)\;7: pvs_tile_4 - (used for SPC-4)\;8: pvs_tile_5 - (used for SPC-4)\;9: pvs_tile_6 - (used for SPC-4)\;10: pvs_tile_7 - (used for SPC-4)\;Other values reserved\;Reserved when fm = 1" access="INDEX" enum="cvb=0x0,ULT=0x1,pvs_main_die=0x2,pvs_tile_0=0x3,pvs_tile_1=0x4,pvs_tile_2=0x5,pvs_tile_3=0x6,pvs_tile_4=0x7,pvs_tile_5=0x8,pvs_tile_6=0x9,pvs_tile_7=0xa" offset="0x0.0" size="0x0.8" />
	<field name="fm" descr="Fuse Mismatch\;0: No fuse mismatch\;1: Fuse mismatch found\;2-3: Reserved" access="RO" offset="0x0.24" size="0x0.2" />
	<field name="v" descr="Valid bit\;0: Fuse reading is not supported for this system\;1: Response is valid\;2-3: Reserved\;Reserved when fm = 1" access="RO" offset="0x0.30" size="0x0.2" />
	<field name="data" descr="Data\;See Table 2464, &quot;MRFV entry - CVB Layout,&quot; on page 2752\;See Table 2466, &quot;MRFV entry - ULT Layout,&quot; on page 2753\;See Table 2468, &quot;MRFV entry - PVS_MAIN Layout,&quot; on page 2754\;See Table 2470, &quot;MRFV entry - PVS_Tile Layout,&quot; on page 2755\;Reserved when fm = 1" subnode="MRFV_data_auto_ext" access="RO" offset="0x10.0" size="0xc.0" union_selector="$(parent).fuse_id" />
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
	<field name="data" descr="Data\;See Table 2278, &quot;MRSV entry - BF-3 Straps Layout,&quot; on page 2603" subnode="MRSV_data_auto_ext" access="RO" offset="0x10.0" size="0x20.0" union_selector="$(parent).ssid" />
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
	<field name="failure_reason" descr="0: undefined error \;1: port down\;2: too high frequency_diff\;3: network synchronizer device error\;4: lack of resources for tracking \;5-255: reserved for future use \;\;Note: Reserved when oper_status is different than 4" access="RO" offset="0x8.0" size="0x0.9" />
	<field name="oper_freq_measure" descr="0: frequency_diff field is not valid\;1: frequency_diff field is valid" access="RO" offset="0x8.9" size="0x0.1" />
	<field name="admin_freq_measure" descr="0: don&apos;t measure frequency_diff\;1: measure frequency_diff" access="RW" offset="0x8.10" size="0x0.1" />
	<field name="ho_acq" descr="Holdover acquired.\;0: The device does not have enough data to go into holdover.\;1: The device has enough data to go into holdover." access="RO" offset="0x8.23" size="0x0.1" />
	<field name="oper_status" descr="0: free running - the device is using internal oscillator as timing source \;1: self track - the device is in sync with this timing source\;2: other track - the device is in sync with other timing source\;3: holdover - the device is using the internal oscillator and past information as a timing source.\;4: Holdover due to failure (see field failure_reason)\;5: Free running due to failure (see field failure_reason)." access="RO" offset="0x8.24" size="0x0.4" />
	<field name="admin_status" descr="0: holdover/free running - the device will use internal oscillator as timing source. \;Free running is the default value.\;Device holdover / free running will take place only if admin status = 0 across all other ports.\;1: track - the device will sync to this timing source. When writing admin status = 1 to a port, all other ports will move to admin status = 0." access="RW" offset="0x8.28" size="0x0.4" />
	<field name="frequency_diff" descr="The FFO (Fractional Frequency Offset) between the rx and tx symbol rate: (rx_frequency- tx_frequency) /rx_frequency.\;Value is in ppt (2&apos;s complement).\;Any value larger than 0x7FFFFFFF represented as 0x7FFFFFFF. \;Any value smaller than 0x80000000 represented as 0x80000000.\;\;Note: Reserved when oper_freq is different than &apos;1&apos;." access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="MSEM_ext" descr="" size="0x20.0" >
	<field name="sem_type" descr="0: Tools ICMD\;1: Flash Programming\;2: Software Reset\;3-31: Reserved" access="INDEX" offset="0x0.0" size="0x0.5" />
	<field name="sem_val" descr="On writes - request ownership by writing the unique Id\;On reads - 0x0 - GW is free, else GW is locked" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="op" descr="Operation\;0: NOP (No Operation)\;1: Allocate Unique Id (incrementing counter by one)S" access="OP" offset="0x8.0" size="0x0.2" />
	<field name="counter" descr="Self-Incrementing counter. \;Possible values are 0x1-0xffff. Never returns 0x0. \;Reserved when OP = 0" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="PBWS_reg_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Egress Local port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must be always 0.\;" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="bw_utilization" descr="The percentage of bw, in per-mille units to be used on the port. Must be in the range of min_bw_utilization to 1000.\;The special value of 0x0, means that no bandwidth enforcement is applied." access="RW" offset="0x4.0" size="0x0.10" />
	<field name="min_bw_utilization" descr="The minimum percentage bw" access="RO" offset="0x4.16" size="0x0.7" />
</node>

<node name="PPCR_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port[9:8]\;Reserved for HCA" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number.\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="aggregated_port" descr="Aggregated Port number to be reflected in MAD.\;0 means N/A\;\;Reserved for HCA" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="plane" descr="Plane number to be reflected in MAD.\;0 means N/A\;\;Reserved for HCA" access="RW" offset="0x8.16" size="0x0.3" />
	<field name="split" descr="When planarized  the FW shall respond to Hierarchy Info.Split with the following split value.\;\;In this use case it represents the split of the APort.\;\;When split = 0, the FW shall send Hierarchy Info without the split field. (meaning it is NA)\;\;When Non planarized (num_of_planes = 0), Hierarchy Info.Split will reflect the actual split value, when 2X- it&apos;ll hold the location within the 4x.\;\;0: NA\;1: Split 1.\;2: Split 2.\;3-7: Reserved\;Reserved for HCA" access="RW" offset="0x8.24" size="0x0.3" />
	<field name="num_of_planes" descr="The number of planes comprising this Aggregated port\;" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="p_type" descr="[DWIP]\;Planarization Type\;0: non planarized\;1: planirized_gen1\;2-7: Reserved" access="RO" offset="0xC.16" size="0x0.3" />
</node>

<node name="access_reg_summary_ctrl_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="id" descr="" subnode="enum_entry" enum="UNIT_PERF_COUNTERS_=0x100,MISC_COUNTERS=0x104,Loopback_Control_Register=0x700,DB_TRESHOLD=0x701,DCBX_PARAM=0x4020,DCBX_APPLICATION=0x4021,QPTS=0x4002,QPDPM=0x4013,QETCR=0x4005,QSHR=0x4030,QEEC=0x400d,QPDP=0x4007,QPRT=0x4008,QTCT=0x400a,QSPIP=0x400e,QSPCP=0x401e,QHLL=0x4016,QCAM=0x4019,ROCE_ACCL=0x402c,PCAM=0x507f,PCAP=0x5001,PTYS=0x5004,PAOS=0x5006,PLTC=0x5046,PPCNT=0x5008,PIPG=0x5017,PGMR=0x5039,PTER=0x5055,PREI=0x5058,PMLP=0x5002,PMPR=0x5013,PMMP=0x5044,PMCR=0x5045,PEPC=0x5056,PMPT=0x5064,PMPD=0x5065,PPSC=0x5011,PRTL=0x5014,PPLR=0x5018,PEIR=0x5019,PPLM=0x5023,SLTP=0x5027,SLTPv2=0x502f,SLRG=0x5028,PDDR=0x5031,PPTT=0x5036,PPRT=0x5037,PPHCR=0x503e,PPAOS=0x5040,PCNR=0x5050,SLRED=0x505a,PEMI=0x5075,PMTU=0x5003,PPAD=0x5005,PFCC=0x5007,PPTB=0x500b,PBMC=0x500c,PGUID=0x5066,PBSR=0x5038,PCMR=0x5041,PPCR=0x504c,PVLS=0x504b,PPCC=0x506e,PBWS=0x5101,SET_NODE=0x6001,POWER_SETTINGS=0x7001,FP_SL_MAP=0x7002,HOST_ENDIANNESS=0x7004,MPEIN=0x9050,MPCNT=0x9051,MPEGC=0x9056,MPIR=0x9059,MPECS=0x905b,MPEINJ=0x9057,MMDIO=0x9017,MLCR=0x902b,MGCR=0x903a,MJTAG=0x901f,MRSV=0x9164,MTPPS=0x9053,MTUTC=0x9055,MRTC=0x902d,MPGO=0x9058,MTPTM=0x9180,MTCTR=0x9181,MSECQ=0x9155,MSEES=0x9156,MCIA=0x9014,MCION=0x9052,PMAOS=0x5012,PMTM=0x5067,MTCAP=0x9009,MTMP=0x900a,MVCAP=0x902e,MVCR=0x900c,MFRL=0x9028,MRSI=0x912a,MCQS=0x9060,MCQI=0x9061,MCC=0x9062,MCDA=0x9063,MCDD=0x905c,MIRC=0x9162,MQIS=0x9064,MGIR=0x9020,MSGI=0x9021,MCGI=0x917c,MSCI=0x902a,MDIR=0x911a,MISOC=0x9026,MCAM=0x907f,MRFV=0x906d,MDSR=0x9110,MFSV=0x9115,MTCQ=0x9065,MQDIK=0x9116,MKDC=0x9066,MFCDR=0x9178,MNVDA=0x9024,MNVDI=0x9025,MNVQC=0x9030,MNVIA=0x9033,MNVGC=0x9034,MNVGN=0x9035,MGNLE=0x9036,MGLS=0x9068,MTRC_CAP=0x9040,MTRC_CONF=0x9041,MTRC_STDB=0x9042,MTRC_CTRL=0x9043,MTEIM=0x9118,MTIE=0x911b,MTIM=0x911c,MTDC=0x911d,MFPA=0x9010,MFBA=0x9011,MFBE=0x9012,MPCIR=0x905a,MERR=0x903c,MRPR=0x9117,MHMPR=0x905d,MSEM=0x906f,MMHI=0x904a,CWTP=0x2802,CWTPM=0x2803,CWCAM=0x281f,SBPR=0xb001,SBCM=0xb002,SBPM=0xb003,SBSR=0xb005,SBCAM=0xb01f,Resource_dump_registers=0xc000,NCFG=0xc001,CRYPTO_OPERATIONAL=0xc002,IMPORT_KEK_HANDLE=0xc004,CREDENTIAL_HANDLE=0xc005,ZTT=0xc006,VHCA_TRUST_LEVEL=0xc007,PORT_STATE_BEHAVIOR=0xc008,HCA_CMD_ENCAP=0xc009,NVMF_TARGET_PACER_DEFAULTS=0xc00a,DTOR=0xc00e,VHCA_ICM_CTRL=0xc010,NIC_CAP_EXT_REG=0xc011,NIC_DPA_EUG_REG=0xc012,NIC_DPA_PERF_CTRL_REG=0xc014,NIC_DPA_EU_PARTITION_REG=0xc015" offset="0x0.0" size="0x4.0" />
</node>

<node name="access_reg_summary_ext" descr="" attr_is_union="1" size="0x300" >
	<field name="register_unti_perf_global_ctrl" descr="" subnode="register_unti_perf_global_ctrl_ext" capability="0" offset="0x0.0" selected_by="UNIT_PERF_COUNTERS_" size="0x10" />
	<field name="register_misc_counters" descr="" subnode="register_misc_counters_ext" capability="0" offset="0x0.0" selected_by="MISC_COUNTERS" size="0x20" />
	<field name="register_loopback_control" descr="" subnode="register_loopback_control_ext" capability="0" offset="0x0.0" selected_by="Loopback_Control_Register" size="0x10" />
	<field name="db_threshold_register_layout" descr="" subnode="db_threshold_register_layout_ext" capability="0" offset="0x0.0" selected_by="DB_TRESHOLD" size="0x10" />
	<field name="dcbx_param_reg" descr="" subnode="dcbx_param_reg_ext" capability="0" offset="0x0.0" selected_by="DCBX_PARAM" size="0x40" />
	<field name="dcbx_app_reg" descr="" subnode="dcbx_app_reg_ext" capability="0" offset="0x0.0" selected_by="DCBX_APPLICATION" size="0x14" />
	<field name="qpts" descr="" subnode="qpts_ext" capability="0" offset="0x0.0" selected_by="QPTS" size="0x8" />
	<field name="qpdpm" descr="" subnode="qpdpm_ext" capability="0" offset="0x0.0" selected_by="QPDPM" size="0x84" />
	<field name="qetcr" descr="" subnode="qetcr_ext" capability="0" offset="0x0.0" selected_by="QETCR" size="0x50" />
	<field name="qshr" descr="" subnode="qshr_ext" capability="0" offset="0x0.0" selected_by="QSHR" size="0x50" />
	<field name="qeec" descr="" subnode="qeec_ext" capability="0" offset="0x0.0" selected_by="QEEC" size="0x20" />
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
	<field name="ptys_reg" descr="" subnode="ptys_reg_ext" capability="0" offset="0x0.0" selected_by="PTYS" size="0x44" />
	<field name="paos_reg" descr="" subnode="paos_reg_ext" capability="0" offset="0x0.0" selected_by="PAOS" size="0x10" />
	<field name="pltc_reg" descr="" subnode="pltc_reg_ext" capability="0" offset="0x0.0" selected_by="PLTC" size="0x10" />
	<field name="ppcnt_reg" descr="" subnode="ppcnt_reg_ext" capability="0" offset="0x0.0" selected_by="PPCNT" size="0x100" />
	<field name="pipg_reg" descr="" subnode="pipg_reg_ext" capability="0" offset="0x0.0" selected_by="PIPG" size="0x8" />
	<field name="pgmr" descr="" subnode="pgmr_ext" capability="0" offset="0x0.0" selected_by="PGMR" size="0x2c" />
	<field name="pter_reg" descr="" subnode="pter_reg_ext" capability="0" offset="0x0.0" selected_by="PTER" size="0x20" />
	<field name="prei_reg" descr="" subnode="prei_reg_ext" capability="0" offset="0x0.0" selected_by="PREI" size="0x18" />
	<field name="pmlp_reg" descr="" subnode="pmlp_reg_ext" capability="0" offset="0x0.0" selected_by="PMLP" size="0x40" />
	<field name="pmpr_reg" descr="" subnode="pmpr_reg_ext" capability="0" offset="0x0.0" selected_by="PMPR" size="0x10" />
	<field name="pmmp_reg" descr="" subnode="pmmp_reg_ext" capability="0" offset="0x0.0" selected_by="PMMP" size="0x2c" />
	<field name="pmcr_reg" descr="" subnode="pmcr_reg_ext" capability="0" offset="0x0.0" selected_by="PMCR" size="0x20" />
	<field name="pepc_reg" descr="" subnode="pepc_reg_ext" capability="0" offset="0x0.0" selected_by="PEPC" size="0x10" />
	<field name="pmpt_reg" descr="" subnode="pmpt_reg_ext" capability="0" offset="0x0.0" selected_by="PMPT" size="0x1c" />
	<field name="pmpd_reg" descr="" subnode="pmpd_reg_ext" capability="0" offset="0x0.0" selected_by="PMPD" size="0x30" />
	<field name="ppsc_reg" descr="" subnode="ppsc_reg_ext" capability="0" offset="0x0.0" selected_by="PPSC" size="0x30" />
	<field name="prtl_reg" descr="" subnode="prtl_reg_ext" capability="0" offset="0x0.0" selected_by="PRTL" size="0x20" />
	<field name="pplr_reg" descr="" subnode="pplr_reg_ext" capability="0" offset="0x0.0" selected_by="PPLR" size="0x8" />
	<field name="peir_reg" descr="" subnode="peir_reg_ext" capability="0" offset="0x0.0" selected_by="PEIR" size="0xc" />
	<field name="pplm_reg" descr="" subnode="pplm_reg_ext" capability="0" offset="0x0.0" selected_by="PPLM" size="0x50" />
	<field name="sltp_reg" descr="" subnode="sltp_reg_ext" capability="0" offset="0x0.0" selected_by="SLTP" size="0x4c" />
	<field name="sltpv2_reg" descr="" subnode="sltpv2_reg_ext" capability="0" offset="0x0.0" selected_by="SLTPv2" size="0x10c" />
	<field name="slrg_reg" descr="" subnode="slrg_reg_ext" capability="0" offset="0x0.0" selected_by="SLRG" size="0x28" />
	<field name="pddr_reg" descr="" subnode="pddr_reg_ext" capability="0" offset="0x0.0" selected_by="PDDR" size="0x100" />
	<field name="pptt_reg" descr="" subnode="pptt_reg_ext" capability="0" offset="0x0.0" selected_by="PPTT" size="0x1c" />
	<field name="pprt_reg" descr="" subnode="pprt_reg_ext" capability="0" offset="0x0.0" selected_by="PPRT" size="0x24" />
	<field name="pphcr" descr="" subnode="pphcr_ext" capability="0" offset="0x0.0" selected_by="PPHCR" size="0x50" />
	<field name="ppaos_reg" descr="" subnode="ppaos_reg_ext" capability="0" offset="0x0.0" selected_by="PPAOS" size="0x10" />
	<field name="pcnr_reg" descr="" subnode="pcnr_reg_ext" capability="0" offset="0x0.0" selected_by="PCNR" size="0xc" />
	<field name="slred_reg" descr="" subnode="slred_reg_ext" capability="0" offset="0x0.0" selected_by="SLRED" size="0xa8" />
	<field name="pemi" descr="" subnode="pemi_ext" capability="0" offset="0x0.0" selected_by="PEMI" size="0x100" />
	<field name="pmtu_reg" descr="" subnode="pmtu_reg_ext" capability="0" offset="0x0.0" selected_by="PMTU" size="0x10" />
	<field name="ppad_reg" descr="" subnode="ppad_reg_ext" capability="0" offset="0x0.0" selected_by="PPAD" size="0x10" />
	<field name="pfcc_reg" descr="" subnode="pfcc_reg_ext" capability="0" offset="0x0.0" selected_by="PFCC" size="0x20" />
	<field name="pptb_reg" descr="" subnode="pptb_reg_ext" capability="0" offset="0x0.0" selected_by="PPTB" size="0xc" />
	<field name="pbmc_reg" descr="" subnode="pbmc_reg_ext" capability="0" offset="0x0.0" selected_by="PBMC" size="0x6c" />
	<field name="pguid_reg" descr="" subnode="pguid_reg_ext" capability="0" offset="0x0.0" selected_by="PGUID" size="0x60" />
	<field name="pbsr_reg" descr="" subnode="pbsr_reg_ext" capability="0" offset="0x0.0" selected_by="PBSR" size="0x64" />
	<field name="pcmr_reg" descr="" subnode="pcmr_reg_ext" capability="0" offset="0x0.0" selected_by="PCMR" size="0xc" />
	<field name="PPCR" descr="" subnode="PPCR_ext" capability="0" offset="0x0.0" selected_by="PPCR" size="0x10" />
	<field name="pvls" descr="" subnode="pvls_ext" capability="0" offset="0x0.0" selected_by="PVLS" size="0x20" />
	<field name="ppcc_reg" descr="" subnode="ppcc_reg_ext" capability="0" offset="0x0.0" selected_by="PPCC" size="0xfc" />
	<field name="PBWS_reg" descr="" subnode="PBWS_reg_ext" capability="0" offset="0x0.0" selected_by="PBWS" size="0x8" />
	<field name="set_node_in" descr="" subnode="set_node_in_ext" capability="0" offset="0x0.0" selected_by="SET_NODE" size="0x40" />
	<field name="register_power_settings" descr="" subnode="register_power_settings_ext" capability="0" offset="0x0.0" selected_by="POWER_SETTINGS" size="0x10" />
	<field name="fp_sl_map_arg" descr="" subnode="fp_sl_map_arg_ext" capability="0" offset="0x0.0" selected_by="FP_SL_MAP" size="0x4" />
	<field name="register_host_endianness" descr="" subnode="register_host_endianness_ext" capability="0" offset="0x0.0" selected_by="HOST_ENDIANNESS" size="0x10" />
	<field name="mpein_reg" descr="" subnode="mpein_reg_ext" capability="0" offset="0x0.0" selected_by="MPEIN" size="0x30" />
	<field name="mpcnt_reg" descr="" subnode="mpcnt_reg_ext" capability="0" offset="0x0.0" selected_by="MPCNT" size="0x100" />
	<field name="mpegc_reg" descr="" subnode="mpegc_reg_ext" capability="0" offset="0x0.0" selected_by="MPEGC" size="0x2c" />
	<field name="mpir" descr="" subnode="mpir_ext" capability="0" offset="0x0.0" selected_by="MPIR" size="0x10" />
	<field name="mpecs_reg" descr="" subnode="mpecs_reg_ext" capability="0" offset="0x0.0" selected_by="MPECS" size="0x20" />
	<field name="mpeinj_reg" descr="" subnode="mpeinj_reg_ext" capability="0" offset="0x0.0" selected_by="MPEINJ" size="0x20" />
	<field name="mmdio" descr="" subnode="mmdio_ext" capability="0" offset="0x0.0" selected_by="MMDIO" size="0xc" />
	<field name="mlcr" descr="" subnode="mlcr_ext" capability="0" offset="0x0.0" selected_by="MLCR" size="0xc" />
	<field name="mgcr_reg" descr="" subnode="mgcr_reg_ext" capability="0" offset="0x0.0" selected_by="MGCR" size="0x20" />
	<field name="mjtag" descr="" subnode="mjtag_ext" capability="0" offset="0x0.0" selected_by="MJTAG" size="0x30" />
	<field name="MRSV" descr="" subnode="MRSV_ext" capability="0" offset="0x0.0" selected_by="MRSV" size="0x40" />
	<field name="mtpps_reg" descr="" subnode="mtpps_reg_ext" capability="0" offset="0x0.0" selected_by="MTPPS" size="0x38" />
	<field name="mtutc_reg" descr="" subnode="mtutc_reg_ext" capability="0" offset="0x0.0" selected_by="MTUTC" size="0x1c" />
	<field name="mrtc_reg" descr="" subnode="mrtc_reg_ext" capability="0" offset="0x0.0" selected_by="MRTC" size="0x10" />
	<field name="mpgo_reg" descr="" subnode="mpgo_reg_ext" capability="0" offset="0x0.0" selected_by="MPGO" size="0x14" />
	<field name="mtptm_reg" descr="" subnode="mtptm_reg_ext" capability="0" offset="0x0.0" selected_by="MTPTM" size="0x10" />
	<field name="mtctr_reg" descr="" subnode="mtctr_reg_ext" capability="0" offset="0x0.0" selected_by="MTCTR" size="0x18" />
	<field name="MSECQ_reg" descr="" subnode="MSECQ_reg_ext" capability="0" offset="0x0.0" selected_by="MSECQ" size="0x40" />
	<field name="MSEES_reg" descr="" subnode="MSEES_reg_ext" capability="0" offset="0x0.0" selected_by="MSEES" size="0x40" />
	<field name="mcia" descr="" subnode="mcia_ext" capability="0" offset="0x0.0" selected_by="MCIA" size="0x94" />
	<field name="mcion" descr="" subnode="mcion_ext" capability="0" offset="0x0.0" selected_by="MCION" size="0x10" />
	<field name="pmaos_reg" descr="" subnode="pmaos_reg_ext" capability="0" offset="0x0.0" selected_by="PMAOS" size="0x10" />
	<field name="pmtm_reg" descr="" subnode="pmtm_reg_ext" capability="0" offset="0x0.0" selected_by="PMTM" size="0x10" />
	<field name="mtcap" descr="" subnode="mtcap_ext" capability="0" offset="0x0.0" selected_by="MTCAP" size="0x10" />
	<field name="mtmp" descr="" subnode="mtmp_ext" capability="0" offset="0x0.0" selected_by="MTMP" size="0x20" />
	<field name="mvcap_reg" descr="" subnode="mvcap_reg_ext" capability="0" offset="0x0.0" selected_by="MVCAP" size="0x10" />
	<field name="mvcr" descr="" subnode="mvcr_ext" capability="0" offset="0x0.0" selected_by="MVCR" size="0x18" />
	<field name="mfrl_reg" descr="" subnode="mfrl_reg_ext" capability="0" offset="0x0.0" selected_by="MFRL" size="0x8" />
	<field name="mrsi" descr="" subnode="mrsi_ext" capability="0" offset="0x0.0" selected_by="MRSI" size="0x40" />
	<field name="mcqs_reg" descr="" subnode="mcqs_reg_ext" capability="0" offset="0x0.0" selected_by="MCQS" size="0x10" />
	<field name="mcqi_reg" descr="" subnode="mcqi_reg_ext" capability="0" offset="0x0.0" selected_by="MCQI" size="0x94" />
	<field name="mcc_reg" descr="" subnode="mcc_reg_ext" capability="0" offset="0x0.0" selected_by="MCC" size="0x20" />
	<field name="mcda_reg" descr="" subnode="mcda_reg_ext" capability="0" offset="0x0.0" selected_by="MCDA" size="0x90" />
	<field name="mcdd_reg" descr="" subnode="mcdd_reg_ext" capability="0" offset="0x0.0" selected_by="MCDD" size="0x20" />
	<field name="mirc_reg" descr="" subnode="mirc_reg_ext" capability="0" offset="0x0.0" selected_by="MIRC" size="0x8" />
	<field name="mqis_reg" descr="" subnode="mqis_reg_ext" capability="0" offset="0x0.0" selected_by="MQIS" size="0x18" />
	<field name="mgir" descr="" subnode="mgir_ext" capability="0" offset="0x0.0" selected_by="MGIR" size="0xa0" />
	<field name="msgi" descr="" subnode="msgi_ext" capability="0" offset="0x0.0" selected_by="MSGI" size="0x80" />
	<field name="mcgi" descr="" subnode="mcgi_ext" capability="0" offset="0x0.0" selected_by="MCGI" size="0x34" />
	<field name="msci" descr="" subnode="msci_ext" capability="0" offset="0x0.0" selected_by="MSCI" size="0xc" />
	<field name="mdir_reg" descr="" subnode="mdir_reg_ext" capability="0" offset="0x0.0" selected_by="MDIR" size="0x40" />
	<field name="misoc_reg" descr="" subnode="misoc_reg_ext" capability="0" offset="0x0.0" selected_by="MISOC" size="0x120" />
	<field name="mcam_reg" descr="" subnode="mcam_reg_ext" capability="0" offset="0x0.0" selected_by="MCAM" size="0x48" />
	<field name="MRFV" descr="" subnode="MRFV_ext" capability="0" offset="0x0.0" selected_by="MRFV" size="0x40" />
	<field name="mdsr_reg" descr="" subnode="mdsr_reg_ext" capability="0" offset="0x0.0" selected_by="MDSR" size="0x30" />
	<field name="mfsv_reg" descr="" subnode="mfsv_reg_ext" capability="0" offset="0x0.0" selected_by="MFSV" size="0x30" />
	<field name="mtcq_reg" descr="" subnode="mtcq_reg_ext" capability="0" offset="0x0.0" selected_by="MTCQ" size="0x70" />
	<field name="mqdik_reg" descr="" subnode="mqdik_reg_ext" capability="0" offset="0x0.0" selected_by="MQDIK" size="0x208" />
	<field name="mkdc_reg" descr="" subnode="mkdc_reg_ext" capability="0" offset="0x0.0" selected_by="MKDC" size="0x2c" />
	<field name="mfcdr_reg" descr="" subnode="mfcdr_reg_ext" capability="0" offset="0x0.0" selected_by="MFCDR" size="0x8" />
	<field name="mnvda_reg" descr="" subnode="mnvda_reg_ext" capability="0" offset="0x0.0" selected_by="MNVDA" size="0x10c" />
	<field name="mnvdi_reg" descr="" subnode="mnvdi_reg_ext" capability="0" offset="0x0.0" selected_by="MNVDI" size="0xc" />
	<field name="mnvqc_reg" descr="" subnode="mnvqc_reg_ext" capability="0" offset="0x0.0" selected_by="MNVQC" size="0x8" />
	<field name="mnvia_reg" descr="" subnode="mnvia_reg_ext" capability="0" offset="0x0.0" selected_by="MNVIA" size="0x8" />
	<field name="mnvgc_reg" descr="" subnode="mnvgc_reg_ext" capability="0" offset="0x0.0" selected_by="MNVGC" size="0x10" />
	<field name="mnvgn_reg" descr="" subnode="mnvgn_reg_ext" capability="0" offset="0x0.0" selected_by="MNVGN" size="0x20" />
	<field name="mgnle_reg" descr="" subnode="mgnle_reg_ext" capability="0" offset="0x0.0" selected_by="MGNLE" size="0x20" />
	<field name="mgls" descr="" subnode="mgls_ext" capability="0" offset="0x0.0" selected_by="MGLS" size="0xc" />
	<field name="mtrc_cap_reg" descr="" subnode="mtrc_cap_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CAP" size="0x84" />
	<field name="mtrc_conf_reg" descr="" subnode="mtrc_conf_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CONF" size="0x80" />
	<field name="mtrc_stdb_reg" descr="" subnode="mtrc_stdb_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_STDB" size="0xc" />
	<field name="mtrc_ctrl_reg" descr="" subnode="mtrc_ctrl_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CTRL" size="0x40" />
	<field name="mteim_reg" descr="" subnode="mteim_reg_ext" capability="0" offset="0x0.0" selected_by="MTEIM" size="0x30" />
	<field name="mtie" descr="" subnode="mtie_ext" capability="0" offset="0x0.0" selected_by="MTIE" size="0x30" />
	<field name="mtim" descr="" subnode="mtim_ext" capability="0" offset="0x0.0" selected_by="MTIM" size="0x10" />
	<field name="mtdc" descr="" subnode="mtdc_ext" capability="0" offset="0x0.0" selected_by="MTDC" size="0x20" />
	<field name="mfpa_reg" descr="" subnode="mfpa_reg_ext" capability="0" offset="0x0.0" selected_by="MFPA" size="0x20" />
	<field name="mfba_reg" descr="" subnode="mfba_reg_ext" capability="0" offset="0x0.0" selected_by="MFBA" size="0x10c" />
	<field name="mfbe_reg" descr="" subnode="mfbe_reg_ext" capability="0" offset="0x0.0" selected_by="MFBE" size="0xc" />
	<field name="mpcir" descr="" subnode="mpcir_ext" capability="0" offset="0x0.0" selected_by="MPCIR" size="0x10" />
	<field name="merr" descr="" subnode="merr_ext" capability="0" offset="0x0.0" selected_by="MERR" size="0x14" />
	<field name="mrpr_reg" descr="" subnode="mrpr_reg_ext" capability="0" offset="0x0.0" selected_by="MRPR" size="0x108" />
	<field name="mhmpr_reg" descr="" subnode="mhmpr_reg_ext" capability="0" offset="0x0.0" selected_by="MHMPR" size="0x14" />
	<field name="MSEM" descr="" subnode="MSEM_ext" capability="0" offset="0x0.0" selected_by="MSEM" size="0x20" />
	<field name="mmhi_reg" descr="" subnode="mmhi_reg_ext" capability="0" offset="0x0.0" selected_by="MMHI" size="0x80" />
	<field name="cwtp" descr="" subnode="cwtp_ext" capability="0" offset="0x0.0" selected_by="CWTP" size="0x40" />
	<field name="cwtpm" descr="" subnode="cwtpm_ext" capability="0" offset="0x0.0" selected_by="CWTPM" size="0x44" />
	<field name="cwcam" descr="" subnode="cwcam_ext" capability="0" offset="0x0.0" selected_by="CWCAM" size="0x50" />
	<field name="sbpr" descr="" subnode="sbpr_ext" capability="0" offset="0x0.0" selected_by="SBPR" size="0x18" />
	<field name="sbcm" descr="" subnode="sbcm_ext" capability="0" offset="0x0.0" selected_by="SBCM" size="0x28" />
	<field name="sbpm" descr="" subnode="sbpm_ext" capability="0" offset="0x0.0" selected_by="SBPM" size="0x20" />
	<field name="sbsr" descr="" subnode="sbsr_ext" capability="0" offset="0x0.0" selected_by="SBSR" size="0xfc" />
	<field name="sbcam" descr="" subnode="sbcam_ext" capability="0" offset="0x0.0" selected_by="SBCAM" size="0x4c" />
	<field name="resource_dump" descr="" subnode="resource_dump_ext" capability="0" offset="0x0.0" selected_by="Resource_dump_registers" size="0x100" />
	<field name="ncfg_reg" descr="" subnode="ncfg_reg_ext" capability="0" offset="0x0.0" selected_by="NCFG" size="0x40" />
	<field name="crypto_operational" descr="" subnode="crypto_operational_ext" capability="0" offset="0x0.0" selected_by="CRYPTO_OPERATIONAL" size="0x80" />
	<field name="import_kek_handle" descr="" subnode="import_kek_handle_ext" capability="0" offset="0x0.0" selected_by="IMPORT_KEK_HANDLE" size="0x300" />
	<field name="credential_handle" descr="" subnode="credential_handle_ext" capability="0" offset="0x0.0" selected_by="CREDENTIAL_HANDLE" size="0x300" />
	<field name="ztt" descr="" subnode="ztt_ext" capability="0" offset="0x0.0" selected_by="ZTT" size="0x10" />
	<field name="vhca_trust_level" descr="" subnode="vhca_trust_level_ext" capability="0" offset="0x0.0" selected_by="VHCA_TRUST_LEVEL" size="0x10" />
	<field name="port_state_behavior" descr="" subnode="port_state_behavior_ext" capability="0" offset="0x0.0" selected_by="PORT_STATE_BEHAVIOR" size="0x10" />
	<field name="hca_cap_encap" descr="" subnode="hca_cap_encap_ext" capability="0" offset="0x0.0" selected_by="HCA_CMD_ENCAP" size="0x60" />
	<field name="nvmf_target_pacer_defaults" descr="" subnode="nvmf_target_pacer_defaults_ext" capability="0" offset="0x0.0" selected_by="NVMF_TARGET_PACER_DEFAULTS" size="0x40" />
	<field name="dtor_reg" descr="" subnode="dtor_reg_ext" capability="0" offset="0x0.0" selected_by="DTOR" size="0x40" />
	<field name="vhca_icm_ctrl" descr="" subnode="vhca_icm_ctrl_ext" capability="0" offset="0x0.0" selected_by="VHCA_ICM_CTRL" size="0x40" />
	<field name="nic_cap_ext_reg" descr="" subnode="nic_cap_ext_reg_ext" capability="0" offset="0x0.0" selected_by="NIC_CAP_EXT_REG" size="0x80" />
	<field name="nic_dpa_eug_reg" descr="" subnode="nic_dpa_eug_reg_ext" capability="0" offset="0x0.0" selected_by="NIC_DPA_EUG_REG" size="0x100" />
	<field name="nic_dpa_perf_ctrl_reg" descr="" subnode="nic_dpa_perf_ctrl_reg_ext" capability="0" offset="0x0.0" selected_by="NIC_DPA_PERF_CTRL_REG" size="0x40" />
	<field name="nic_dpa_eu_partition_reg" descr="" subnode="nic_dpa_eu_partition_reg_ext" capability="0" offset="0x0.0" selected_by="NIC_DPA_EU_PARTITION_REG" size="0x300" />
</node>

<node name="access_reg_summary_selector_ext" descr="" attr_is_union="1" size="0x300" >
	<field name="access_reg_summary" descr="" subnode="access_reg_summary_ext" offset="0x0.0" size="0x300" union_selector="$(parent).ctrl.id" />
	<field name="ctrl" descr="" subnode="access_reg_summary_ctrl_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="application_prio_entry_ext" descr="" size="0x4.0" >
	<field name="protocol_id" descr="According to 802.1Q application priority TLV" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="sel" descr="According to 802.1Q application priority TLV" access="RO" offset="0x0.16" size="0x0.3" />
	<field name="priority" descr="" access="RO" offset="0x0.21" size="0x0.3" />
</node>

<node name="bufferx_reg_ext" descr="" size="0x8.0" >
	<field name="size" descr="The part of the packet buffer array is allocated for the specific buffer.\;Units are represented in cells.\;For shared_headroom_pool, this field represents the maximum load from the shared headroom pool and it can be set only when port_shared_buffer is enabled. \;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="epsb" descr="Eligible for Port Shared buffer.\;If epsb is set, packets assigned to bufferX are allowed to insert the port shared buffer.\;For port_shared_buffer, this field is reserved.\;For shared_headroom_pool, this field is reserved.\;When lossy==1 this field is reserved.\;The field is reserved for Switch-X/-2." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="lossy" descr="The field indicates if the buffer is lossy.\;0: Lossless\;1: Lossy\;\;The field is reserved for Switch-X/-2.\;For port_shared_buffer, this field is reserved.\;For shared_headroom_pool, this field is reserved.\;NOTE: This field does NOT affect the pause control. Pause control is configured using PFCC register." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="xon_threshold" descr="When the amount of data in the buffer goes below this value, device stops sending pause frames for the Prios associated with the buffer. Units are represented in cells.\;In Spectrum xon_threshold is reserved for buffer[9].\;For Spectrum, if lossy is set on, this field is reserved.\;For shared_headroom_pool, this field is reserved." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="xoff_threshold" descr="Once the amount of data in the buffer goes above this value, device starts sending Pause frames for all Prios associated with the buffer. Units are represented in cells.\;In Spectrum xoff_threshold is reserved for buffer[9].\;For Spectrum, if lossy is set on, this field is reserved.\;For shared_headroom_pool, this field is reserved." access="RW" offset="0x4.16" size="0x0.16" />
</node>

<node name="config_item_ext" descr="" size="0xc.0" >
	<field name="length" descr="Length of configuration item data in bytes (not including header). Must be between 0 and 256." access="RW" offset="0x0.0" size="0x0.9" />
	<field name="host_id_valid" descr="Host ID valid:\;1: the type_index.host_id field is valid\;Valid only when MNVGC.priv_nv_other_host=1 and the type_class is a Host" access="RO" offset="0x0.9" size="0x0.1" />
	<field name="version" descr="Configuration item version - defines the data structure following the header (together with the type field)." access="RW" offset="0x0.12" size="0x0.4" />
	<field name="writer_id" descr="The entity which configured this parameter\;0x0: UNSPECIFIED\;0x1: CHASSIS_BMC\;0x2: MAD\;0x3: BMC\;0x4: COMMAND_INTERFACE\;0x5: ICMD - with unspecified source\;0x6: ICMD_UEFI_HII - configured by the NIC&apos;s UEFI expansion ROM&quot;s HII menu.\;0x7: ICMD_UEFI_CLP - configured by the NIC&apos;s expansion ROM&quot;s CLP.\;0x8: ICMD_Flexboot - configured by the NIC&quot;s legacy expansion ROM.\;0x9: ICMD_mlxconfig - configured by Mellanox mlxconfig tool\;0xA: ICMD_USER1 - value available for customer created tools that uses the ICMD interface for writing TLVs.\;0xB: ICMD_USER2 - value available for customer created tools that uses the ICMD interface for writing TLVs.\;0xC: ICMD_MLXCONFIG_SET_RAW - configures by\;mlxconfig set raw operation.\;0xD: ICMD_FLEXBOOT_CLP - configured by Legacy Expansion ROM CLP\;0x10: BMC_APP1 - Configuration was done over the BMC by application #1 (application name is OEM specific)\;0x11: BMC_APP2 - Configuration was done over the BMC by application #2 (application name is OEM specific)\;0x12: BMP_APP3 - Configuration was done over the BMC by application #3 (application name is OEM specific)\;0x1F: OTHER - the parameter was written by the NIC due to other reasons. \;\;Note - This field is writeable only when using the ICMD interface. The only value that are valid for writes are 0x6 through 0xB. Other values will be replaced by 0x5ICMD." access="RO" enum="UNSPECIFIED=0x0,CHASSIS_BMC=0x1,MAD=0x2,BMC=0x3,COMMAND_INTERFACE=0x4,ICMD=0x5,ICMD_UEFI_HII=0x6,ICMD_UEFI_CLP=0x7,ICMD_Flexboot=0x8,ICMD_mlxconfig=0x9,ICMD_USER1=0xa,ICMD_USER2=0xb,ICMD_MLXCONFIG_SET_RAW=0xc,ICMD_FLEXBOOT_CLP=0xd,BMC_APP1=0x10,BMC_APP2=0x11,BMP_APP3=0x12,OTHER=0x1f" offset="0x0.16" size="0x0.5" />
	<field name="access_mode" descr="Defines which value of the Configuration Item will be accessed.\;0: NEXT - Next value to be applied\;1: CURRENT - Currently set values (only valid for Query operation) Supported only if NVGC.nvda_read_current_settings==1.\;2: FACTORY - Default factory values (only valid for Query operation). Supported only if NVGC.nvda_read_factory_settings==1." access="INDEX" enum="NEXT=0x0,CURRENT=0x1,FACTORY=0x2" offset="0x0.22" size="0x0.2" />
	<field name="rd_en" descr="Read Enable\;Controls the read operation during different life-cycle stages.\;0: TLV cannot be read by the subsequent life-cycle priorities.\;1: TLV can be read by the subsequent life-cycle priorities." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="ovr_en" descr="Override Enable\;0: Can only be overwritten by the current life-cycle priority.\;1: Allowed to be over-written by the subsequent life-cycle priorities." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="priority" descr="The life-cycle priority of this configuration.\;0x0: USER,\;0x1: OEM,\;0x2: Reserved  \;0x3: MLNX\;\;The priority is set by either:\;1. When using MNVDA, the TLV will have user priority\;2. When using NVCONFIG, each TLV has its own priority" access="RO" offset="0x0.28" size="0x0.2" />
	<field name="type" descr="Configuration item index according to its type_class. \;Table 2506, &quot;Configuration Item Data Type Class Global Layout,&quot; on page 2784\;Table 2508, &quot;Configuration Item Data Type Class Physical Port Layout,&quot; on page 2784\;Table 2510, &quot;Configuration Item Data Type Class Per Host-PF Layout,&quot; on page 2785\;Table 2512, &quot;Configuration Item Data Type Class Log Layout,&quot; on page 2785\;Table 2514, &quot;Configuration Item Data Type Class File Layout,&quot; on page 2786\;Table 2516, &quot;Configuration Item Data Type Class Host Layout,&quot; on page 2786\;\;Table 2518, &quot;Configuration Item Data Type Class Module Layout,&quot; on page 2787" subnode="config_item_type_auto_ext" access="INDEX" offset="0x4.0" size="0x4.0" />
</node>

<node name="config_item_type_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="configuration_item_type_class_global_ext" descr="" subnode="configuration_item_type_class_global_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_physical_port_ext" descr="" subnode="configuration_item_type_class_physical_port_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_per_host_pf_ext" descr="" subnode="configuration_item_type_class_per_host_pf_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_log_ext" descr="" subnode="configuration_item_type_class_log_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_file_ext" descr="" subnode="configuration_item_type_class_file_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_host_ext" descr="" subnode="configuration_item_type_class_host_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_module_ext" descr="" subnode="configuration_item_type_class_module_ext" offset="0x0.0" size="0x4.0" />
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

<node name="configuration_item_type_class_per_host_pf_ext" descr="" size="0x4.0" >
	<field name="parameter_index" descr="" access="INDEX" offset="0x0.0" size="0x0.10" />
	<field name="pci_bus_index" descr="" access="RW" offset="0x0.10" size="0x0.8" />
	<field name="pf_index" descr="" access="RW" offset="0x0.18" size="0x0.6" />
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

<node name="cwcam_ext" descr="" size="0x50.0" >
	<field name="access_reg_group" descr="Access Register ID groups\;0: RegID_0x2800_to_0x287F\;Values 1-255 are Reserved" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features \;Values 1 - 255 are Reserved" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="cw_access_reg_cap_mask" descr="Supported port&apos;s access register bitmaks. Based on access_reg_group index.\;7When bit is set, The register is supported in the device. \;When access_reg_group == 0 :\;Bit_2: 0x2802_CWTP\;Bit_3: 0x2803_CWTPM\;Bit_31: 0x281f_CWCAM" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="feature_cap_mask" descr="Supported port&apos;s enhanced features. Based on feature_group index.\;When bit is set, The feature is supported in the device: \;Bits 0-127 are Reserved" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="cwtp_ext" descr="" size="0x40.0" >
	<field name="pnat" descr="Port number access type. Determines the way local_port is interpreted:\;2: host_port_number" access="INDEX" enum="host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="traffic_class" descr="Traffic Class\;Range is 0..cap_max_tclass_sb-1" access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="mode" descr="Mode of thresholds for WRED and ECN:\;0: Fixed\;1: Percentage" access="RW" enum="Fixed=0x0,Percentage=0x1" offset="0x24.24" size="0x0.1" />
	<field name="profile1_min" descr="Minimum Average Queue Size of the profile number &lt;i&gt;\;When mode is Fixed:\;Cells. Valid inputs are 1..cap_total_buffer_size/cap_cell_size.\;For Spectrum: must be a multiple of 64\;Note: for Spectrum, must be larger than 2^aqs_weight cells, see Section 27.8.1, &quot;CWGCR - Congestion WRED ECN General Configuration Register&quot;, on page 2479\;When mode is Percentage:\;Percentage of the quota of local_port,traffic_class. Range is 0..100, units of integer percentage. When ECN Source Congestion Detection is enabled then congestion occurs when there are at least 256 cells in the buffer\;" access="RW" offset="0x28.0" size="0x0.20" />
	<field name="profile1_max" descr="Maximum Average Queue Size of the profile number &lt;i&gt;\;When mode is Fixed:\;Cells. Valid inputs are 1..cap_total_buffer_size/cap_cell_size\;For Spectrum: must be a multiple of 64\;When mode is Percentage:\;Percentage of the quota of local_port,traffic_class. Range is 0..100, units of integer percentage.\;profile&lt;i&gt;_max must always be equal or greater than profile&lt;i&gt;_min" access="RW" offset="0x2C.0" size="0x0.20" />
	<field name="profile1_percent" descr="Percentage of WRED and ECN marking for Maximum Average Queue Size of the profile number &lt;i&gt;\;Range is 0..100, units of integer percentage\;Default is 0" access="RW" offset="0x2C.24" size="0x0.7" />
	<field name="profile2_min" descr="Same as above." access="RW" offset="0x30.0" size="0x0.20" />
	<field name="profile2_max" descr="Same as above." access="RW" offset="0x34.0" size="0x0.20" />
	<field name="profile2_percent" descr="Same as above." access="RW" offset="0x34.24" size="0x0.7" />
	<field name="profile3_min" descr="Same as above." access="RW" offset="0x38.0" size="0x0.20" />
	<field name="profile3_max" descr="Same as above." access="RW" offset="0x3C.0" size="0x0.20" />
	<field name="profile3_percent" descr="Same as above." access="RW" offset="0x3C.24" size="0x0.7" />
</node>

<node name="cwtpm_ext" descr="" size="0x44.0" >
	<field name="pnat" descr="Port number access type. Determines the way local_port is interpreted:\;2: host_port_number" access="INDEX" enum="host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="traffic_class" descr="Traffic Class\;Range is 0..cap_max_tclass_sb-1" access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="ee" descr="Enable ECN on traffic class\;0: Disable\;1: Enable\;Default is 0\;Reserved when Quantum" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x24.0" size="0x0.1" />
	<field name="ew" descr="Enable WRED on traffic class:\;0: Disable\;1: Enable\;Default is 0\;Reserved when Quantum" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x24.1" size="0x0.1" />
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
	<field name="EMBEDDED_CPU_OS_SHUTDOWN_TO" descr="Maximum period for shutting down the embedded CPU OS. Relevant for DPU devices only.\;Valid only if the timeout value is not zero.\;" subnode="default_timeout_ext" access="RW" offset="0x3C.0" size="0x4.0" />
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
	<field name="if_in_discards_high" descr="The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;\;\;\;\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="if_in_discards_low" descr="The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;\;\;\;\;" access="RO" offset="0x14.0" size="0x4.0" />
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
	<field name="dot3stats_symbol_errors_high" descr="The number of times the receiving media is non-idle (a carrier event) for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate &quot;Receive Error&quot;.\;\;" access="RW" offset="0x60.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_low" descr="The number of times the receiving media is non-idle (a carrier event) for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate &quot;Receive Error&quot;.\;\;" access="RW" offset="0x64.0" size="0x4.0" />
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
	<field name="port_isolation_high" descr="Port isolation filter discards\;[IInternal] Not supported due to HW bug." access="RO" offset="0x48.0" size="0x4.0" />
	<field name="port_isolation_low" descr="Port isolation filter discards\;[IInternal] Not supported due to HW bug." access="RO" offset="0x4C.0" size="0x4.0" />
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
	<field name="port_transmit_wait_high" descr="The time (in 4ns resolution) during which the port selected had data to transmit but no data was sent.\;time = port_transmit_wait*4 [ns]\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="port_transmit_wait_low" descr="The time (in 4ns resolution) during which the port selected had data to transmit but no data was sent.\;time = port_transmit_wait*4 [ns]\;" access="RO" offset="0x4.0" size="0x4.0" />
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
	<field name="tx_frames_high" descr="The total number of packets transmitted.\;\;\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="tx_frames_low" descr="The total number of packets transmitted.\;\;\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="rx_pause_high" descr="The total number of PAUSE frames received from the far-end port.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="rx_pause_low" descr="The total number of PAUSE frames received from the far-end port.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="rx_pause_duration_high" descr="The total time in microseconds that transmission of packets to the far-end port have been paused.\;Note that if pause is global then tclass &quot;0&quot; will increment\;\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="rx_pause_duration_low" descr="The total time in microseconds that transmission of packets to the far-end port have been paused.\;Note that if pause is global then tclass &quot;0&quot; will increment\;\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="tx_pause_high" descr="The total number of PAUSE or PFC frames sent to the far-end port.\;\;\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="tx_pause_low" descr="The total number of PAUSE or PFC frames sent to the far-end port.\;\;\;" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="tx_pause_duration_high" descr="The total time in microseconds that the far-end port have been requested to pause.\;\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="tx_pause_duration_low" descr="The total time in microseconds that the far-end port have been requested to pause.\;\;" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="rx_pause_transition_high" descr="Counts the number of transitions from Xoff to Xon.\;\;" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="rx_pause_transition_low" descr="Counts the number of transitions from Xoff to Xon.\;\;" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="rx_discards_high" descr="The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;\;\;\;" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="rx_discards_low" descr="The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;\;\;\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="device_stall_minor_watermark_cnt_high" descr="The number of times the device detected a stalled state for a period longer than device_stall_minor_watermark\;The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="device_stall_minor_watermark_cnt_low" descr="The number of times the device detected a stalled state for a period longer than device_stall_minor_watermark\;The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause)." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="device_stall_critical_watermark_cnt_high" descr="The number of times the device detected a stalled state for a period longer than device_stall_critical_watermark\;The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause).\;" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="device_stall_critical_watermark_cnt_low" descr="The number of times the device detected a stalled state for a period longer than device_stall_critical_watermark\;The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause).\;" access="RO" offset="0x8C.0" size="0x4.0" />
</node>

<node name="eth_per_traffic_class_cong_layout_ext" descr="" size="0xf8.0" >
	<field name="wred_discard_high" descr="The number of packet that are dropped by the Weighted Random Early Detection (WRED) function.\;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt eth per tc cong group supported&quot; is set." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="wred_discard_low" descr="The number of packet that are dropped by the Weighted Random Early Detection (WRED) function.\;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt eth per tc cong group supported&quot; is set." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ecn_marked_tc_high" descr="A count of packets marked as ECN or potentially marked as ECN.\;ECN Counting enable/disable is configurable. \;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt eth per tc cong group supported&quot; is set.\;\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ecn_marked_tc_low" descr="A count of packets marked as ECN or potentially marked as ECN.\;ECN Counting enable/disable is configurable. \;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt eth per tc cong group supported&quot; is set.\;\;" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="eth_per_traffic_class_layout_ext" descr="" size="0xf8.0" >
	<field name="transmit_queue_high" descr="Contains the transmit queue depth in bytes on traffic class selected by traffic_class of the port selected by local_port.\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="transmit_queue_low" descr="Contains the transmit queue depth in bytes on traffic class selected by traffic_class of the port selected by local_port.\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_high" descr="The number of unicast packets dropped due to lack of shared buffer resources.\;Valid only for Spectrum.\;Valid for HCA when ppcnt_no_buffer_uc is set in PCAM." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_low" descr="The number of unicast packets dropped due to lack of shared buffer resources.\;Valid only for Spectrum.\;Valid for HCA when ppcnt_no_buffer_uc is set in PCAM." access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="ets_ext" descr="" size="0x8.0" >
	<field name="bw_allocation" descr="For NICs:\;The weight assigned to the TClass within its TClass Group.  \;The percentage of bandwidth guaranteed is calculated by the TClass weight divided by the sum of all weights of the TClasses in the group.\;Valid values are 1-100." access="RW" offset="0x0.0" size="0x0.7" />
	<field name="group" descr="TClass Group assigned to a TClass.\;Range 0..7\;" access="RW" offset="0x0.16" size="0x0.4" />
	<field name="r" descr="Rate limit update. Enables update of the rate limiter (with the max_bw_units, max_bw_value). If this bit is cleared, the rate limiter value will not change." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="b" descr="Bandwidth allocation update. Enables update of the ETS bandwidth allocation (with the bw_allocation). If this bit is cleared, the bandwidth allocation value will not change." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="g" descr="Group update. Enables update of the group assigned to the TClass. If this bit is cleared, the group value will not change." access="WO" offset="0x0.31" size="0x0.1" />
	<field name="max_bw_value" descr="The maximal bandwidth allowed for the use TClass\;Units according to max_bw_units\;Reserved when max_bw_units = 0" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="max_bw_units" descr="Encoding of max_bw_units:\;0x0: DISABLED - rate limiter disabled\;0x3: HUNDREDS_MBPS - max_bw_value is in 100 Mbps units\;0x4: GBPS - max_bw_value is in 1 Gbps units\;Note - Query response returns value in units that allow the most accurate number, not in the units configured using Set()." access="RW" enum="DISABLED=0x0,HUNDREDS_MBPS=0x3,GBPS=0x4" offset="0x4.16" size="0x0.4" />
</node>

<node name="ets_global_ext" descr="" size="0x8.0" >
	<field name="r" descr="Rate limit update. Enables update of the rate limiter (with the max_bw_units, max_bw_value). If this bit is cleared, the rate limiter value will not change." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="max_bw_value" descr="The maximal bandwidth allowed for the use for the port\;Encoding of max_bw_units:\;0x0: DISABLED - rate limiter disabled\;0x3: HUNDREDS_MBPS - max_bw_value is in 100 Mbps units\;0x4: GBPS - max_bw_value is in 1 Gbps units\;Note - Query response will return value in units that allow the most accurate number, not in the units configured using Set()." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="max_bw_units" descr="The maximal bandwidth allowed for the use for the port\;Encoding of max_bw_units:\;0x0: DISABLED - rate limiter disabled\;0x3: HUNDREDS_MBPS - max_bw_value is in 100 Mbps units\;0x4: GBPS - max_bw_value is in 1 Gbps units\;Note - Query response will return value in units that allow the most accurate number, not in the units configured using Set()." access="RW" enum="DISABLED=0x0,HUNDREDS_MBPS=0x3,GBPS=0x4" offset="0x4.16" size="0x0.4" />
</node>

<node name="fp_sl_map_arg_ext" descr="" size="0x4.0" >
	<field name="port" descr="0x0 - reserved\;0x1-0x2 - port number\;0x3-0xff - reserved" access="RW" offset="0x0.0" size="0x0.8" />
</node>

<node name="hca_cap_encap_ext" descr="" size="0x60.0" >
	<field name="cmd_data_offset" descr="Defines the start offset of the data (cmd_data_value and cmd_data_mask) that is needed to be set/queried by QUERY_HCA_CAP and SET_HCA_CAP) in granularity of 4Bytes.\;The offset starts from the beginning of the command. i.e. includes the command header.\;For other commands this field is reserved" access="INDEX" offset="0x0.16" size="0x0.16" />
	<field name="cmd_data_mask" descr="For set commands: Bitmask that indicates which bits in cmd_data_value should be written.\;An unset bit in this mask will leave the matching bit in the cmd_data_value unchanged. \;For query commands (QUERY_HCA_CAP): must be 0\;For other commands this field is reserved" access="INDEX" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="cmd_data_value" descr="For set commands: The value to apply starting from cmd_data_offset (in conjunction with the cmd_data_mask defined above). Set by the user.\;For query commands (QUERY_HCA_CAP): User should set to 0; will hold the value the device retrieved.\;For other commands this field is reserved" access="RW" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
	<field name="cmd_header" descr="Icommand_header_in and command_header_out (16 bytes) of QUERY_HCA_CAP or SET_HCA_CAP.\;command_header_in is set by user when issuing the register.\;command_header_out is returned by the device after executing the register." access="RW" high_bound="3" low_bound="0" offset="0x40.0" size="0x10.0" />
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
	<field name="key" descr="\;Actual size and layout of this field described in Table 344, &quot;IMPORT_KEK Field Construction Summary,&quot; on page 631 below. Note that the layout explained in following table should be used from the MSBs and on." high_bound="31" low_bound="0" offset="0x40.0" size="0x80.0" />
</node>

<node name="lane_2_module_mapping_ext" descr="" size="0x4.0" >
	<field name="module" descr="Module number" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA \;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="tx_lane" descr="TX lane. \;When m_lane_m field is set, this field is ignored (Reserved). \;When rxtx field is cleared, this field is used for RX as well." access="RW" offset="0x0.16" size="0x0.4" />
	<field name="rx_lane" descr="RX lane.\;When m_lane_m field is set, this field is ignored (Reserved). \;When rxtx field is cleared, this field is ignored and RX lane is equal to TX lane." access="RW" offset="0x0.24" size="0x0.4" />
</node>

<node name="mcam_reg_ext" descr="" size="0x48.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: First_128_REG_ID - Register IDs 0x9001 - 0x907F)\;1: Register_IDs_0x9080 - 0x90FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9080 while bit 127 represents register ID 0x90FF).\;2: Register_IDs_0x9100 - 0x917F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9100 while bit 127 represents register ID 0x917F).\;3: Register_IDs_0x9180 - 0x91FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9180 while bit 127 represents register ID 0x91FF)." access="INDEX" enum="First_128_REG_ID=0x0,Register_IDs_0x9080=0x1,Register_IDs_0x9100=0x2,Register_IDs_0x9180=0x3" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="mng_access_reg_cap_mask" descr="Supported management&apos;s access register bitmask. Based on access_reg_group index. \;When bit is set, the register is supported in the device. \;For example:\;Bit 1: MFCR_0x9001\;Bit 2: MFSC_0x9002\;Bit 3: MFSM_0x9003\;Bit 4: MFSL_0x9004\;Bit 58: MGCR_0x903A\;Bit 73: MPPF_0x9049\;Bit 127: MCAP_0x907F" access="RO" enum="MFCR_0x9001=0x2,MFSC_0x9002=0x4,MFSM_0x9003=0x8,MFSL_0x9004=0x10,MGCR_0x903A=0x4000000,MPPF_0x9049=0x200,MCAP_0x907F=0x80000000" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="mng_feature_cap_mask" descr="Supported port&apos;s enhanced features.Based on feature_group index.\;When bit is set, The feature is supported in the device: \;Bit 0: MPCNT counter group- PCIE performance counters supported\;Bit 1: mtpps_fs - If set, field_select field in MTPPS register is supported.\;Bit 2: mtpps_enhanced_out_periodic_adjustment - If set, enhanced_out_periodic_adjustment field in MTPPS register is supported.\;Bit 3: tx_lossy_overflow_oper - If set, tx_overflow_buffer_pkt counter in MPCNT register is supported.\;Bit 4: pcie_outbound_stalled - if set, outbound_stalled_reads, outbound_stalled_writes, outbound_stalled_reads_events and outbound_stalled_writes_events counters in MPCNT are supported.\;Bit 5: Management pass through is supported\;Bit 6: sensor_map - If set, sensor_map is supported in MTCAP register.\;Bit 7: if set, module_status bit 8 (Module Low Power) in MCION register is supported. \;Bit 8: beacon_capability_disable - If set, beacon feature, as appears in MLCR register, in not supported by the device. \;Bit 9: dynamic_tx_overflow - If set, tx_overflow_sense field is supported in MPEGC register. \;Bit 10: mark_tx_action_cqe is supported if set to &apos;1&apos;.\;Bit 11: mark_tx_action_cnp is supported if set to &apos;1&apos;.\;Bit 12: dev_info is supported in  register is set to &apos;1&apos;.\;Bit 13: sensor_count field is 12bit size in MTMP and MTBR\;Bit 14: cs_tokens_supported is supported \;Bit 15: debug_fw_tokens_supported\;Bit 16: long_keys is supported \;Bit 17: pwr_status and pci_power are supported in MPEIN\;Bit 18: If set, accessing through device_type and device_index is supported in MCC, MCQI and MCQS\;Bit 19: pcie_sync_for_fw_update_supported is set to &apos;1&apos;\;Bit 20: ptpCyc2Realtime_modify - If set, the cycle to realtime translation offload is supported\;Bit 21: If set to &apos;1&apos;, reset_state in MFRL is supported\;Bit 22: If set to &apos;1&apos;, link_peer_max_speed is supported in MPEIN Register\;Bit 23: If set to &apos;1&apos;, slot_index field is supported in: MCIA, MCAS, MCION, MQSP, MTCAP, MTECR, MTMP, MTEWE, MTBR, MVCAP, MVCR, MGPIR, MDDT, MDCR.\;Bit 24: If set, transceiver burn flow is supported in MCC, MCQI and MCQS.\;Bit 26: If set, progress field is supported in MCQS\;Bit 28: If set, number_of_slots field is supported in MGPIR.\;Bit 29: If set, virtual hot plug / unplug is supported in MPEGC.\;Bit 30: If set, my_pf_number is supported in MPPF.\;Bit 31: If set, sdee is supported in MTMP\;Bit 32: If set, npps_period is supported in MTPPS.\;Bit 33: If set, out_pulse_duration_ns is supported in MTPPS.\;Bit 34: If set, MCIA supports 32 D-words. Otherwise, 12 D-words.\;Bit 35: If set, MGIR.hw_info.technology is supported. \;Bit 37: If set, lp_msb is supported for MLCR, MPIR \;Bit 39: If set, MRCS and RMDT tokens are supported in MCQS\;Bit 40: If set, &apos;encryption&apos; field in MGIR is supported\;Bit 43: If set, MFCR supports tacho_active_msb field\;Bit 44: If set, FORE supports fan_under_limit_msb and fan_over_limit_msb fields\;Bit 45: If set, MFRL.pci_rescan_required is supported\;Bit 46: time_adjust_range_extended - if set, the MTUTC.time_adjustment range is extended to -200,000 to +200,000\;Bit 47: If set, MTUTC.freq_adj_units=1 is supported\;Bit 48: If set, MRSR.command=6 is supported\;Bit 49: If set, MCQS.identifier support CRCS and CRDT tokens\;Bit 51: If set, MTUTC.freq_adj_units=2 is supported\;Bit 53: If set, Mlx mlxfwreset with downstream port is supported by FW [Internal]: NIC only, FW rejects reset till user committed that traffic is disabled\;Bit 59: If set, MCC.component_specific_error_code is valid for LinkX devices\;Bit 60: If set, MGNLE.clr is supported\;Bit 61: If set, MGIR supports life_cycle_msb and pds fields in FW info and development field in HW info.\;\;\;Bit 65: If set, MVCR support current_sensor_value_msb" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="mcc_reg_ext" descr="" size="0x20.0" >
	<field name="instruction" descr="Command to be executed by the FSM\;0x1: LOCK_UPDATE_HANDLE\;0x2: RELEASE_UPDATE_HANDLE \;0x3: UPDATE_COMPONENT\;0x4: VERIFY_COMPONENT\;0x6: ACTIVATE\;0x7: READ_COMPONENT\;0x8: CANCEL\;0x9: CHECK_UPDATE_HANDLE\;0xA: FORCE_HANDLE_RELEASE\;0xB: READ_PENDING_COMPONENT\;0xC: DOWNSRTEAM_DEVICE_TRANSFER\;Other values are reserved. Applicable for write operation only." access="RW" enum="LOCK_UPDATE_HANDLE=0x1,RELEASE_UPDATE_HANDLE=0x2,UPDATE_COMPONENT=0x3,VERIFY_COMPONENT=0x4,ACTIVATE=0x6,READ_COMPONENT=0x7,CANCEL=0x8,CHECK_UPDATE_HANDLE=0x9,FORCE_HANDLE_RELEASE=0xa,READ_PENDING_COMPONENT=0xb,DOWNSRTEAM_DEVICE_TRANSFER=0xc" offset="0x0.0" size="0x0.8" />
	<field name="activation_delay_sec" descr="This is a configuration that delays the activation of the component in seconds. Relevant only for activate command.\;This configuration is volatile." access="RW" offset="0x0.8" size="0x0.8" />
	<field name="time_elapsed_since_last_cmd" descr="The number of seconds elapsed since the update_handle owner last issued a command. The time saturates at 0xFFF." access="RO" offset="0x0.16" size="0x0.12" />
	<field name="component_index" descr="Index of the accessed component. \;Value from MCQS.component_index\;Valid for \;UPDATE_COMPONENT, ACTIVATE_COMPONENET, READ_COMPONENT and READ_PENDING_COMPONENT instructions. Otherwise, this field is reserved." access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="update_handle" descr="Token representing the current flow executed by the FSM.\;See Section 10.2.1, &quot;Component Update State&quot;, on page 887." access="RW" offset="0x8.0" size="0x0.24" />
	<field name="auto_update" descr="Auto-update to all matching downstream devices is requested." access="WO" offset="0x8.31" size="0x0.1" />
	<field name="control_state" descr="Current Update FSM state, see Section  10.3.8, &quot;FSM States,&quot; on page  891\;0x0: IDLE\;0x1: LOCKED\;0x2: INITIALIZE\;0x3: DOWNLOAD\;0x4: VERIFY\;0x5: APPLY\;0x6: ACTIVATE\;0x7: UPLOAD\;0x8: UPLOAD_PENDING\;0x9: DOWNSRTEAM_DEVICE_TRANSFER\;Other values are reserved" access="RO" enum="IDLE=0x0,LOCKED=0x1,INITIALIZE=0x2,DOWNLOAD=0x3,VERIFY=0x4,APPLY=0x5,ACTIVATE=0x6,UPLOAD=0x7,UPLOAD_PENDING=0x8,DOWNSRTEAM_DEVICE_TRANSFER=0x9" offset="0xC.0" size="0x0.4" />
	<field name="error_code" descr="Indicates the successful completion of the instruction, or the reason it failed. See Section  10.3.7, &quot;Error Handling,&quot; on page  890\;0x0: OK\;0x1: ERROR\;0x2: REJECTED_DIGEST_ERR\;0x3: REJECTED_NOT_APPLICABLE\;0x4: REJECTED_UNKNOWN_KEY\;0x5: REJECTED_AUTH_FAILED\;0x6: REJECTED_UNSIGNED\;0x7: REJECTED_KEY_NOT_APPLICABLE\;0x8: REJECTED_BAD_FORMAT\;0x9: BLOCKED_PENDING_RESET\;0xA: REJECTED_NOT_A_SECURED_FW\;0xB: REJECTED_MFG_BASE_MAC_NOT_LISTED\;0xC: REJECTED_NO_DEBUG_TOKEN\;0xD: REJECTED_VERSION_NUM_MISMATCH\;0xE: REJECTED_USER_TIMESTAMP_MISMATCH\;0xF: REJECTED_FORBIDDEN_VERSION\;0x10: FLASH_ERASE_ERROR\;0x11: REJECTED_REBURN_RUNNING_AND_RETRY\;0x12: REJECTED_LINKX_TYPE_NOT_SUPPORTED\;0x13: REJECTED_HOST_STORAGE_IN_USE\;0x14: REJECTED_LINKX_TRANSFER (see module index in rejected_device_index)\;0x15: REJECTED_LINKX_ACTIVATE (see module index in rejected_device_index)\;0x16: REJECTED_INCOMPATIBLE_FLASH\;0x17: REJECTED_TOKEN_ALREADY_APPLIED\;0x18: REJECTED_FW_BURN_DRAM_NOT_AVAILABLE\;0x19: FW_BURN_REJECTED_INVALID_SECURITY_VERSION\;0x1A: FW_BURN_REJECTED_CERT_CER509 \;0x1B: FW_BURN_REJECTED_CERT_SIGNATURE\;0x1C: FW_BURN_REJECTED_CERT_METADATA\;0x1D: FW_BURN_REJECTED_CERT_INTERNAL_ERROR_0 \;0x1E: FW_BURN_REJECTED_CERT_NO_PLACE\;0x1F: FW_BURN_REJECTED_CERT_REMOVAL_NO_MATCH_CERT_UIDD\;0x20: FW_BURN_REJECTED_CERTI_INTERNAL_ERROR_1 \;0x21: FW_BURN_REJECTED_CERT_INTERNAL_ERROR_2 0x22: FW_BURN_REJECTED_CERT_OF_NUM_OF_SWAP\;0x23: FW_BURN_REJECTED_CERT_INTERNAL_ERROR_3 \;0x24: FW_BURN_REJECTED_CERT_INTERNAL_ERROR_4 \;0x25: FW_BURN_REJECTED_CERT_NOT_ALLOWED_SAME_CERT_UIDD \;0x26: FW_BURN_REJECTED_CERTIFICATE_INTERNAL_ERROR_5 \;0x27: FW_BURN_REJECTED_CERTIFICATE_INTERNAL_ERROR_6 \;0x28: REJECTED_FLASH_WP\;\;Other values should be treated as an unknown error." access="RO" offset="0xC.8" size="0x0.8" />
	<field name="control_progress" descr="Indicates the estimated progress status of the current operation executed by the FSM. Valid values are 0..100.\;101 indicates that progress reporting is not supported for this update state." access="RO" offset="0xC.16" size="0x0.7" />
	<field name="handle_owner_host_id" descr="For handle_owner_type BMC, command-interface and ICMD, indicates the identifier of the host of the handle owner.\;Otherwise reserved" access="RO" offset="0xC.24" size="0x0.4" />
	<field name="handle_owner_type" descr="Type of entity holding the update handle:\;0x0: unspecified\;0x1: Chassis BMC\;0x2: MAD\;0x3: BMC\;0x4: command interface\;0x5: ICMD \;Other values are reserved." access="RO" offset="0xC.28" size="0x0.4" />
	<field name="component_size" descr="Component size in bytes. \;Valid for UPDATE_COMPONENT instruction. Specifying the size may shorten the update time.\;Value 0x0 means that size is unspecified." access="WO" offset="0x10.0" size="0x4.0" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch_or_NIC\;1: Gearbox" access="INDEX" enum="Switch_or_NIC=0x0,Gearbox=0x1" offset="0x14.0" size="0x0.8" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die. \;For cables, the index represents the module index starting at index 1. Index 0 indicates the host device." access="INDEX" offset="0x14.16" size="0x0.12" />
	<field name="device_index_size" descr="In multiple downstream devices action, the action will be executed starting on device_index and ending on device_index + device_index_size - 1." access="RW" offset="0x18.0" size="0x0.12" />
	<field name="rejected_device_index" descr="The device index that the action has been rejected to." access="RO" offset="0x18.16" size="0x0.12" />
	<field name="component_specific_err_code" descr="[DWIP]:\;Component Specific Error Code\;Relevant only for Linkx failed updates" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mcda_reg_ext" descr="" size="0x90.0" >
	<field name="update_handle" descr="Update handle registered when the FSM was activated." access="RW" offset="0x0.0" size="0x0.24" />
	<field name="offset" descr="Offset of accessed address relative to component start. Accesses must be in accordance to log_mcda_word_size in Table 2407, &quot;MCQI CAPABILITIES Info Layout,&quot; on page 2710" access="RW" offset="0x4.0" size="0x4.0" />
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

<node name="mcgi_ext" descr="" size="0x34.0" >
	<field name="chassis_slot_index" descr="[DWIP]\;Slot index\;Info provided from the chassis EEPROM (FRU) if exists." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="tray_index" descr="Tray Index\;Info provided from the chassis EEPROM (FRU) if exists. \;In Oberon, valid values 0-8" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="cfiv" descr="Chassis Info Valid bit\;0: Info is not valid\;1: Info is valid" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="chassis_id" descr="Chassis Id" access="RO" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="chassis_topology_id" descr="Chassis Part Number" access="RO" offset="0x30.0" size="0x0.8" />
</node>

<node name="mcia_ext" descr="" size="0x94.0" >
	<field name="status" descr="Module Status\;0: SUCCESS\;1: NO_EEPROM_MODULE. No response from module&apos;s EEPROM.\;2: MODULE_NOT_SUPPORTED. Module type not supported by the device. 3: MODULE_NOT_CONNECTED. No module present indication. \;4: MODULE_TYPE_INVALID - module is not supported by INI. \;\;9: I2C_ERROR. Error occurred while trying to access the module&apos;s EEPROM using I2C.\;16: MODULE_DISABLED - module is disabled \;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number\;NIC: Range 0 .. MGPIR.num_of_modules -1 \;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="pnv" descr="[DWIP]:\;Page Number Valid\;0: write page number\;1: don&apos;t write page number\;Valid only if module is in SW control" access="OP" offset="0x0.29" size="0x0.1" />
	<field name="l" descr="Lock Page bit. \;When bit is set, FW can access the last accessed page.\;After boot and ISSU, default value is 0.\;\;" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="device_address" descr="Device address" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="page_number" descr="Page number\;Reserved when MCIA.l = 1 or when MCIA.pnv = 1" access="INDEX" offset="0x4.16" size="0x0.8" />
	<field name="i2c_device_address" descr="I2C device address\;" access="INDEX" offset="0x4.24" size="0x0.8" />
	<field name="size" descr="Number of bytes to read/write (up to 128 bytes)" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="bank_number" descr="Bank number" access="INDEX" offset="0x8.16" size="0x0.8" />
	<field name="passwd_length" descr="0: password length is 4B (password_msb is reserved)\;1: password length is 8B (password_msb is used)" access="OP" offset="0x8.28" size="0x0.1" />
	<field name="password" descr="The password that is written to the module password field.\;This field is reserved when passwd_cap is not set to 1. \;Reserved when module is in SW control." access="OP" offset="0xC.0" size="0x4.0" />
	<field name="dword" descr="Bytes to read/write\;Note: some FW versions support only 12*4B\;See MCAM bit34" access="RW" high_bound="31" low_bound="0" offset="0x10.0" size="0x80.0" />
	<field name="password_msb" descr="password msb\;Supported only when MCAM bit34 is set\;Supported only when passwd_cap is set\;Reserved when passwd_length = 0" access="RW" offset="0x90.0" size="0x4.0" />
</node>

<node name="mcion_ext" descr="" size="0x10.0" >
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number\;NIC: Range 0 .. MGPIR.num_of_modules -1 \;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="module_status_bits" descr="Module IO status, as defined by SFF and CMIS:\;Bit 0: Present\;Bit 1: RX_LOS\;Bit 2: TX_Fault\;Bit 6: LPMode\;[DWIP] Bit 7: Interrupt (IntL)\;Bit 8: Low Power Mode Status \;[DWIP] Bit 9: Power Good\;If bit 0 (Present) is clear, all other bits are reserved." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="module_inputs" descr="[DWIP][SwitchOnly]\;Module inputs: \;Bit 0: ResetL - low polarity\;Bit 1: LPMode\;Bit 2: Power Enable\;Reserved when module is controlled by FW" access="RW" offset="0xC.0" size="0x0.4" />
	<field name="module_status_bits_valid" descr="[DWIP][SwitchOnly]\;Module Inputs Valid Bitmask\;Bitmask which mentions the validity of module_inputs fields.\;For each bit, 0 means valid, 1 means not valid.\;For example:\;Bit 0: if set, present bit value is ignored. If cleared, value is valid.\;Bit 1: if set, rx loss value is ignored. when cleared, value is valid and so on for all bits mentioned in module_inputs.\;Reserved when module is controlled by FW" access="RO" offset="0xC.16" size="0x0.16" />
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
	<field name="supported_info_bitmask" descr="Bitmask indicating which info_type(s) are supported for this component. Set bit indicates the property set is supported\;bit 1: VERSION\;bit 5: ACTIVATION_METHOD\;Other bits are reserved. CAPABILITIES set is always supported.\;bit 6: LinkX\;bit 7: Clock Synchronizer\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="component_size" descr="The size of the component given in bytes. Value 0x0 indicates that the size in unknown.\;For some components, size may only be available in the READ_COMPONENT state." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="max_component_size" descr="Maximum size for this component, given in bytes." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="mcda_max_write_size" descr="Maximal write size for MCDA" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="log_mcda_word_size" descr="Log 2 of the access word size in bytes.\;Read and write access must be aligned to the word size. Write access must be done for an integer number of words." access="RO" offset="0xC.28" size="0x0.4" />
	<field name="match_base_guid_mac" descr="The device only accepts updates for this component that explicitly lists its base MAC and/or base GUID" access="RW" offset="0x10.26" size="0x0.1" />
	<field name="check_user_timestamp" descr="A user defined timestamp (MVTS) is active for this component." access="RW" offset="0x10.27" size="0x0.1" />
	<field name="match_psid" descr="PSID is validated for this component update." access="RW" offset="0x10.28" size="0x0.1" />
	<field name="match_chip_id" descr="Chip ID (device_hw_revision) is validated for this component update." access="RW" offset="0x10.29" size="0x0.1" />
	<field name="signed_updates_only" descr="Only signed components are accepted." access="RW" offset="0x10.30" size="0x0.1" />
	<field name="rd_en" descr="When set, this components may be read, see Section 10.3.4, &quot;Read Flow&quot;, on page 890." access="RO" offset="0x10.31" size="0x0.1" />
</node>

<node name="mcqi_clock_source_properties_ext" descr="" size="0x4.0" >
	<field name="image_version_minor" descr="Image Version Minor Number" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="image_version_major" descr="Image Version Major Number" access="RO" offset="0x0.4" size="0x0.4" />
	<field name="vendor_id" descr="Clock Source Device Vendor Id\;0: Renesas\;1: SiTime 148\;2: SiTime 348\;3: TI\;4-255: Reserved" access="RO" offset="0x0.16" size="0x0.8" />
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
	<field name="mcqi_cap_ext" descr="" subnode="mcqi_cap_ext" offset="0x0.0" selected_by="CAPABILITIES" size="0x7c.0" />
	<field name="mcqi_version_ext" descr="" subnode="mcqi_version_ext" offset="0x0.0" selected_by="VERSION" size="0x7c.0" />
	<field name="mcqi_activation_method_ext" descr="" subnode="mcqi_activation_method_ext" offset="0x0.0" selected_by="ACTIVATION_METHOD" size="0x7c.0" />
	<field name="mcqi_linkx_properties_ext" descr="" subnode="mcqi_linkx_properties_ext" offset="0x0.0" selected_by="LINKX_PROPERTIES" size="0x7c.0" />
	<field name="mcqi_clock_source_properties_ext" descr="" subnode="mcqi_clock_source_properties_ext" offset="0x0.0" selected_by="CLOCK_SOURCE_PROPERTIES" size="0x4.0" />
</node>

<node name="mcqi_reg_ext" descr="" size="0x94.0" >
	<field name="component_index" descr="Component index gathered by &quot;MCQS - Management Component Query Status&quot;" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die. \;For cables, the index represents the module index starting at index 1. Index 0 indicates the host device.\;\;For Clock Source EEPROM, the index represents the Clock Source Index, starting from 1" access="INDEX" offset="0x0.16" size="0x0.12" />
	<field name="read_pending_component" descr="When set, the register will return information about the pending component (if available)" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch / NIC\;1: Gearbox" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="info_type" descr="Component properties set.\;0x0: CAPABILITIES\;0x1: VERSION\;0x5: ACTIVATION_METHOD\;0x6: LINKX_PROPERTIES\;0x7: CLOCK_SOURCE_PROPERTIES\;Other values are reserved" access="RW" enum="CAPABILITIES=0x0,VERSION=0x1,ACTIVATION_METHOD=0x5,LINKX_PROPERTIES=0x6,CLOCK_SOURCE_PROPERTIES=0x7" offset="0x8.0" size="0x0.5" />
	<field name="info_size" descr="Properties set structure size, given in bytes." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="offset" descr="The requested/returned data offset from the section start, given in bytes.\;Must be DWORD aligned.\;If offset is invalid, FW will return an error." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="data_size" descr="The requested/returned data size, given in bytes.\;If data_size is not DWORD aligned, the last bytes are zero padded.\;If size is invalid, FW will return an error." access="RW" offset="0x14.0" size="0x0.16" />
	<field name="data" descr="Properties set structure according to info_type.\;CAPABILITIES - See Table 2407, &quot;MCQI CAPABILITIES Info Layout,&quot; on page 2710\;VERSION - See Table 2409, &quot;MCQI VERSION Info Layout,&quot; on page 2712\;ACTIVATION_METHOD - See Table 2413, &quot;MCQI ACTIVATION_METHOD Info Layout,&quot; on page 2714\;LINKX_PROPERTIES - See Table 2415, &quot;MCQI LINKX_PROPERTIES Info Layout,&quot; on page 2715\;CLOCK_SOURCE_PROPERTIES - See Table 2417, &quot;MCQI CLOCK_SOURCE_PROPERTIES Layout,&quot; on page 2717" subnode="mcqi_reg_data_auto_ext" access="RO" offset="0x18.0" size="0x7c.0" union_selector="$(parent).info_type" />
</node>

<node name="mcqi_version_ext" descr="" size="0x7c.0" >
	<field name="version_string_length" descr="" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="user_defined_time_valid" descr="When set, the component has a valid user-defined version time-stamp in user_defined_time" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="build_time_valid" descr="When set, the component has a valid creation time-stamp in build_time" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="version" descr="Version number" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="build_time" descr="Time of component creation. Valid only if build_time_valid is set. See Table 2411, &quot;Date-Time Layout,&quot; on page 2713" subnode="date_time_layout_ext" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="user_defined_time" descr="User-defined time assigned to the component version. Valid only if user_defined_time_valid is set. See Table 2411, &quot;Date-Time Layout,&quot; on page 2713" subnode="date_time_layout_ext" access="RW" offset="0x10.0" size="0x8.0" />
	<field name="build_tool_version" descr="Build tool version number.\;Valid only when not equal to 0" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="version_string" descr="NULL terminated string representing the version." access="RW" high_bound="91" low_bound="0" offset="0x20.24" size="0x5c.0" />
</node>

<node name="mcqs_reg_ext" descr="" size="0x10.0" >
	<field name="component_index" descr="Component Index. Values range from 0 to the last component indicated by last_index_flag." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die. \;For cables, the index represents the module index starting at index 1. Index 0 indicates the host device.\;For Clock synchronizer, index is used to represent the clock sync&apos; device index. Starting from 1." access="INDEX" offset="0x0.16" size="0x0.12" />
	<field name="last_index_flag" descr="When set, this component is the last component (highest component_index)." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="identifier" descr="This field uniquely identifies a specific component type. \;0x1: BOOT_IMG\;0x4: OEM_NVCONFIG\;0x5: MLNX_NVCONFIG\;0x6: CS_TOKEN\;0x7: DBG_TOKEN\;0xA: Gearbox\;0xB: CC_ALGO - Congestion Control Algorithm\;0xC: LINKX_IMG\;0xD: CRYPTO_TO_COMMISSIONING\;0xE: RMCS_TOKEN\;0xF: RMDT_TOKEN\;0x10: CRCS_TOKEN. \;0x11: CRDT_TOKEN. \;0x12: CLOCK_SYNC_EEPROM.  \;\;Other values are reserved" access="RO" enum="BOOT_IMG=0x1,OEM_NVCONFIG=0x4,MLNX_NVCONFIG=0x5,CS_TOKEN=0x6,DBG_TOKEN=0x7,Gearbox=0xa,CC_ALGO=0xb,LINKX_IMG=0xc,CRYPTO_TO_COMMISSIONING=0xd,RMCS_TOKEN=0xe,RMDT_TOKEN=0xf,CRCS_TOKEN_=0x10,CRDT_TOKEN_=0x11,CLOCK_SYNC_EEPROM_=0x12" offset="0x4.0" size="0x0.16" />
	<field name="component_update_state" descr="Component state in update flow, see Section  10.2.1, &quot;Component Update State,&quot; on page  887:\;0x0: IDLE\;0x1: IN_PROGRESS\;0x2: APPLIED\;0x3: ACTIVE \;0x4: ACTIVE_PENDING_RESET\;0x5: FAILED\;0x6: CANCELED\;0x7: BUSY\;\;Other values are reserved" access="RO" enum="IDLE=0x0,IN_PROGRESS=0x1,APPLIED=0x2,ACTIVE=0x3,ACTIVE_PENDING_RESET=0x4,FAILED=0x5,CANCELED=0x6,BUSY=0x7" offset="0x8.0" size="0x0.4" />
	<field name="component_status" descr="The status of the component:\;0x0: NOT_PRESENT - The component is supported by the device but, currently not present\;0x1: PRESENT - This component is present. For downstream devices link LinkX component, this is an indication that the binary image is present at the host device memory.\;0x2: IN_USE - The component is present and currently in use." access="RO" enum="NOT_PRESENT=0x0,PRESENT=0x1,IN_USE=0x2" offset="0x8.4" size="0x0.5" />
	<field name="progress" descr="Progress in percentage (from 0 to 100). This field is only relevant for cables." access="RO" offset="0x8.9" size="0x0.7" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch_or_NIC\;1: Gearbox" access="INDEX" offset="0xC.0" size="0x0.8" />
	<field name="last_update_state_changer_host_id" descr="For last_update_state_changer_type BMC, command-interface and ICMD, indicates the identifier of the host of the handle owner. Otherwise reserved." access="RO" offset="0xC.24" size="0x0.4" />
	<field name="last_update_state_changer_type" descr="Indicates which entity was the last to change the component_update_state of this component.\;0x0: unspecified\;0x1: Chassis_BMC\;0x2: MAD\;0x3: BMC\;0x4: command_interface\;0x5: ICMD\;\;Other values are reserved" access="RO" enum="unspecified=0x0,Chassis_BMC=0x1,MAD=0x2,BMC=0x3,command_interface=0x4,ICMD=0x5" offset="0xC.28" size="0x0.4" />
</node>

<node name="mdir_reg_ext" descr="" size="0x40.0" >
	<field name="device_id" descr="Device ID" access="RO" high_bound="7" low_bound="0" offset="0x0.0" size="0x20.0" />
</node>

<node name="mdsr_reg_ext" descr="" size="0x30.0" >
	<field name="status" descr="0: The debug session ended successfully\;1: Failed to execute the operation. See additional_info for more details.\;2: Debug session active. See type_of_token for more details.\;3: No token applied\;4: Challenge provided, no token installed yet, see type_of_token for details.\;5: Timeout before token installed, see type_of_token for details\;6: Timeout of active token.\;7-15: Reserved\;\;Note: Status might be &apos;0&apos; even when debug query is not allowed and additional_info field will expose the reason." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="additional_info" descr="0: No additional information available \;1: There is no debug session in progress\;2: FW is not secured, debug session cannot be ended\;3: Fail - Debug end request cannot be accepted. \;4: Fail - Host is not allowed to query debug session\;5: Debug session active" access="RO" offset="0x0.8" size="0x0.6" />
	<field name="type_of_token" descr="0: CS token \;1: Debug FW token \;2: FRC token \;3: RMCS token\;4: RMDT token \;5: CRCS token \;6: CRDT token" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="end" descr="Set to &apos;1&apos; to end debug session.\;Setting to &apos;0&apos; will not trigger any operation." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="time_left" descr="Time left in seconds.\;In case that status is 2 (debug session active) - time left for token operation\;In case that status is 4 (challenge provided, no token installed yet) - time left for token installation\;For any other status, field should be zero" access="RO" offset="0x8.0" size="0x4.0" />
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
	<field name="lp_msb" descr="port MSB" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="port" access="INDEX" offset="0x0.16" size="0x0.8" />
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
	<field name="reset_trigger" descr="The firmware reset trigger. \;Only a single bit may be set.\;Bit 0: TRIGGER0 (live-patch)\;Bit 1: TRIGGER1 (Immediate Reset)\;Bit 3: TRIGGER3 (PCIe link toggle)\;Bit 6: TRIGGER6 (PERST)\;Other bits are reserved." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="reset_type" descr="Each bit represents a chip reset type.\;If set to &apos;1&apos;, the reset is supported.\;Bit 0: Full chip reset\;Bit 1: Keep network port active during reset\;Bit 3: ARM only reset [DWIP]\;Bit 4: ARM OS shut down [DWIP]" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="reset_state" descr="Reset state.\;0: IDLE\;1: Negotiation in progress\;2: Reset in progress\;3: Error - Negotiation timeout\;4: Error - Negotiation dis-acknowledgment\;5: Error- driver unload timeout [DWIP]\;6: Error- ARM OS is up, please shut down\;7: ARM OS shut down in progress\;8-15: Reserved" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="pci_leaf_dsp_exist" descr="[DWIP]:\;Pcie Bridge has leaf DSP" access="RO" offset="0x4.20" size="0x0.1" />
	<field name="pci_leaf_dsp_traffic_dis_commited" descr="When set the host commits all drivers, traffic and flow through the Pcie-switch were removed, by the Host. This field is valid only at Single Host Topology." access="WO" offset="0x4.21" size="0x0.1" />
	<field name="rst_type_sel" descr="The requested reset type.\;When reset_trigger = Immediate (1), reset_type_sel valid values are: bit3 or bit4 (ARM only reset or ARM os shutdown)" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="pci_sync_for_fw_update_resp" descr="Response of the driver for the reset request.\;1: Acknowledgment\;2: Dis-acknowledgment\;3: Reserved" access="WO" enum="Acknowledgment=0x1,Dis=0x2,Reserved=0x3" offset="0x4.27" size="0x0.2" />
	<field name="pci_sync_for_fw_update_start" descr="Setting this bit to &apos;1&apos; will request a synced driver flow and &apos;0&apos; for the legacy flow.\;Synced driver flow will not require to issue MFRL command from other hosts (x86 / ARM for SoC)" access="WO" offset="0x4.29" size="0x0.1" />
	<field name="pci_rescan_required" descr="Setting this bit to 1 indicates a need of rescan for the corresponding PCI slot" access="RO" offset="0x4.31" size="0x0.1" />
</node>

<node name="mfsv_reg_ext" descr="" size="0x30.0" >
	<field name="efuses_prog_en" descr="When this bit is set, it indicates that it is allowed for the boot FW to program the FW security version related EFUSEs if needed. This bit is not relevant in case the FW operates in an automatically EFUSEs programming approach (set in the INI file). Once set to 1, this configuration will be relevant only for the upcoming boot, thus this configuration will be set back to 0 upon next boot.\;\;" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="fw_sec_ver_stat" descr="Firmware security version status.0: EFUSEs value is equal to the currently running FW image value. No change is needed.1: EFUSEs value is smaller than the currently running FW image value. An update to the EFUSEs is required.2: There is pending image, MFSV is rejected\;3: Reserved\;\;" access="RO" offset="0x0.1" size="0x0.2" />
	<field name="efuses_prog_method" descr="EFUSEs programming method.0: manually. Upon boot, if FW indicates that FW_sec_ver_stat is 1 and only if EFUSEs_prog_en is 1, it will program the EFUSEs as needed.1: automatically. Upon boot, if FW indicates that FW_sec_ver_stat is 1, it will program the EFUSEs as needed.\;\;" access="RO" offset="0x0.3" size="0x0.1" />
	<field name="revoke_efuse_prog" descr="0: EFUSEs value is equal to the currently running FW image value. No change is needed. \;1: EFUSEs value is smaller than the currently running FW image value. An update to the EFUSEs is required. \;" access="RW" offset="0x0.4" size="0x0.1" />
	<field name="pending_efuse_prog" descr="0: No pending EFUSE programming command \;1: There is pending MFSV command \;\;" access="RO" offset="0x0.5" size="0x0.1" />
	<field name="fuse_failure" descr="[NIC Only]\;0:N/A - No info about fuse failure\;1: No failure\;2: Failure identified\;3: Reserved" access="RO" offset="0x0.8" size="0x0.2" />
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
	<field name="hw_info" descr="Hardware Information, see Table 2431, &quot;Hardware Info Layout,&quot; on page 2729" subnode="mgir_hardware_info_ext" access="RW" offset="0x0.0" size="0x20.0" />
	<field name="fw_info" descr="Firmware Information, see Table 2434, &quot;Firmware Info Layout,&quot; on page 2732" subnode="mgir_fw_info_ext" access="RW" offset="0x20.0" size="0x40.0" />
	<field name="sw_info" descr="Software Information, see Table 2436, &quot;Software Info Layout,&quot; on page 2735\;This field indicates the oldest software version compatible with the current firmware" subnode="mgir_sw_info_ext" access="RW" offset="0x60.0" size="0x20.0" />
	<field name="dev_info" descr="Development Information, see Table 2440, &quot;Development Info Layout,&quot; on page 2739" subnode="mgir_dev_info_ext" access="RW" offset="0x80.0" size="0x1c.0" />
</node>

<node name="mgir_fw_info_ext" descr="" size="0x40.0" >
	<field name="sub_minor" descr="Sub-minor firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_sub_minor." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="minor" descr="Minor firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_minor." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="major" descr="Major firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_major." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="secured" descr="When set, the device is running firmware with secure-firmware updates capabilities." access="RO" offset="0x0.24" size="0x0.1" />
	<field name="signed_fw" descr="When set the device is running a signed FW binaries." access="RO" offset="0x0.25" size="0x0.1" />
	<field name="debug" descr="When set, the device is running a debug firmware. &apos;debug&apos; binary can only be installed on specific devices (identified by their &apos;Factory base MAC&apos;), which currently run a specific firmware version. These restrictions are expressed by a signed &apos;debug&apos; token that must be loaded to the device before installing the debug binary." access="RO" offset="0x0.26" size="0x0.1" />
	<field name="dev" descr="*NOTE* this field has diff meaning for Switch vs. NIC \;\;\;NIC:\;The device is running:\;0: a regular-secure firmware version\;1: a development-secure firmware version\;\;" access="RO" offset="0x0.27" size="0x0.1" />
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
	<field name="device_hw_revision" descr="See Table 2433, &quot;Device HW Revision Descriptions,&quot; on page 2731" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="pvs" descr="Process Voltage Scaling\;Supported nominal V_CORE voltage (in 50mV units) for the device." access="RO" offset="0x4.0" size="0x0.5" />
	<field name="technology" descr="Process technology\;0: N/A\;1: 40nm\;2: 28nm\;3: 16nm\;4: 7nm\;5: 5nm\;6-31: Reserved" access="RO" offset="0x4.11" size="0x0.5" />
	<field name="num_ports" descr="Number of physical port the device supports.\;For Retimer: returns the number of data path \;" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="ib_mad_gen" descr="[DWIP]\;IB MAD Protocol. Based on value from ConfigProfile\;0: IBg1\;1: IBg2\;2-7: Reserved" access="RO" offset="0x4.28" size="0x0.3" />
	<field name="hw_dev_id" descr="The PCI device-ID of the NIC/HCA in recovery (Livefish) mode." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="development" descr="[DWIP]\;The device is running:\;0: a regular-secure firmware version\;1: a development-secure firmware version\;\;Supported in QM3,CX8 and on." access="RO" offset="0xC.30" size="0x0.1" />
	<field name="manufacturing_base_mac_47_32" descr="MSB of the &quot;base&quot; MAC address of the NIC that was allocate during manufacturing. The NIC derives the MAC addresses for the different PCI PFs from this MAC address. This parameter can be used as a canonical unique identifier of the NIC.\;manufacturing_base_mac of value 0 means field is not supported." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="ga" descr="[DWIP]\;Geographical Address\;0: ASIC 0\;1: ASIC 1\;2: ASIC 2\;3: ASIC 3\;Valid for multi ASIC platforms only" access="RO" offset="0x10.16" size="0x0.6" />
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

<node name="mirc_reg_ext" descr="" size="0x8.0" >
	<field name="status_code" descr="Indicates the successful completion of the instruction, or the reason it failed. See Section  10.3.7, &quot;Error Handling,&quot; on page  890\;0x0: OK\;0x1: BUSY\;0x2: PROHIBITED_FW_VER_ERR\;0x3: FIRST_PAGE_COPY_FAILED\;0x4: FIRST_PAGE_ERASE_FAILED\;0x5: FIRST_PAGE_RESTORE_FAILED\;0x6: CANDIDATE_FW_DEACTIVATION_FAILED\;0x7: FW_ALREADY_ACTIVATED\;0x8: ERROR_DEVICE_RESET_REQUIRED\;0x9: ERROR_FW_PROGRAMMING_NEEDED\;Other values should be treated as an unknown error." access="RO" offset="0x0.0" size="0x0.8" />
</node>

<node name="misoc_reg_ext" descr="" size="0x120.0" >
	<field name="type" descr="0:ARM_ATF\;1:ARM_UEFI" access="INDEX" enum="ARM_ATF=0x0,ARM_UEFI=0x1" offset="0x0.0" size="0x0.4" />
	<field name="version" descr="The version as a null-terminated ASCII string\;Null termination will not be present if version takes up all of the field size" access="RO" high_bound="255" low_bound="0" offset="0x10.24" size="0x100.0" />
</node>

<node name="mjtag_ext" descr="" size="0x30.0" >
	<field name="size" descr="Size of operation - relevant for JTAG interface access commands only, indicating the number of transaction bytes to execute. Maximum size supported is 40.\;Note: when size=0, no operation is performed (clock is not toggled). The tdo is sampled and provided in the response at jtag_transaction_set_0." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="sequence_number" descr="Command sequence number - to prevent re-execution of the same command due to command retransmission, this command includes a sequence number.\;The enable and disable commands MUST be issues with sequence_number = 0 while any JTAG access command must increase the sequence_number by 1 (the first JTAG access command should start at sequence_number = 1)." access="WO" offset="0x0.24" size="0x0.4" />
	<field name="cmd" descr="Command\;0 - JTAG interface disable - JTAG interface is disabled\;1 - JTAG interface enable - enabling JTAG interface\;2 - JTAG interface access" access="RW" offset="0x0.30" size="0x0.2" />
	<field name="jtag_transaction_set" descr="See Table 2266, &quot;JTAG Transaction Set Byte Layout,&quot; on page 2596" access="RW" high_bound="43" low_bound="0" offset="0x4.24" size="0x2c.0" />
</node>

<node name="mkdc_reg_ext" descr="" size="0x2c.0" >
	<field name="error_code" descr="Indicates the successful completion of the instruction or the reason it failed:\;0: OK\;1: BAD_SESSION_ID\;2: BAD_KEEP_ALIVE_COUNTER\;3: BAD_SOURCE_ADDRESS\;4: SESSION_TIMEOUT\;Other values are Reserved." access="RO" enum="OK=0x0,BAD_SESSION_ID=0x1,BAD_KEEP_ALIVE_COUNTER=0x2,BAD_SOURCE_ADDRESS=0x3,SESSION_TIMEOUT=0x4" offset="0x0.0" size="0x0.4" />
	<field name="session_id" descr="Unique debug session identifier." access="INDEX" offset="0x0.16" size="0x0.16" />
	<field name="current_keep_alive_counter" descr="Running counter that states the current sequence number of each keep-alive session." access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="next_keep_alive_counter" descr="Running counter that states the expected next sequence number of each keep-alive session." access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mlcr_ext" descr="" size="0xc.0" >
	<field name="led_type" descr="Led type (only supported when cap_local_or_uid_only==1.)\;0: LOCALP_AND_UID - not supported\;1: UID \;2: LOCALP - local port" access="INDEX" enum="LOCALP_AND_UID=0x0,UID=0x1,LOCALP=0x2" offset="0x0.0" size="0x0.4" />
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
	<field name="writer_id" descr="The entity which perform the invalidate.\;The encoding same as writer_id in Configuration Item register (See Table 2504, &quot;Configuration Item Header Layout,&quot; on page 2780)." access="RW" offset="0x0.4" size="0x0.5" />
</node>

<node name="mnvqc_reg_ext" descr="" size="0x8.0" >
	<field name="type" descr="Configuration item type according to its class. \;Table 2506, &quot;Configuration Item Data Type Class Global Layout,&quot; on page 2784\;Table 2508, &quot;Configuration Item Data Type Class Physical Port Layout,&quot; on page 2784\;Table 2510, &quot;Configuration Item Data Type Class Per Host-PF Layout,&quot; on page 2785\;Table 2512, &quot;Configuration Item Data Type Class Log Layout,&quot; on page 2785\;Table 2514, &quot;Configuration Item Data Type Class File Layout,&quot; on page 2786\;Table 2516, &quot;Configuration Item Data Type Class Host Layout,&quot; on page 2786\;\;Table 2518, &quot;Configuration Item Data Type Class Module Layout,&quot; on page 2787" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="support_rd" descr="The configuration item is supported and can be read" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="support_wr" descr="The configuration item is supported and can be updated" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="version" descr="The maximal version of the configuration item supported by the device" access="RO" offset="0x4.4" size="0x0.4" />
</node>

<node name="module_latched_flag_info_ext" descr="" size="0xf8.0" >
	<field name="rx_los_cap" descr="when set, indicates modules supports rx los indication" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="dp_fw_fault" descr="Valid for CMIS based modules only\;Latched modules Datapath fw fault flag" access="RO" offset="0x0.22" size="0x0.1" />
	<field name="mod_fw_fault" descr="Valid for CMIS based modules only\;Latched module fw fault flag" access="RO" offset="0x0.23" size="0x0.1" />
	<field name="vcc_flags" descr="Latched VCC flags of module\;Bit 0: high_vcc_alarm\;Bit 1: low_vcc_alarm\;Bit 2: high_vcc_warning\;Bit 3: low_vcc_warning" access="RO" enum="high_vcc_alarm=0x1,low_vcc_alarm=0x2,high_vcc_warning=0x4,low_vcc_warning=0x8" offset="0x0.24" size="0x0.4" />
	<field name="temp_flags" descr="Latched temperature flags of module\;Bit 0: high_temp_alarm\;Bit 1: low_temp_alarm\;Bit 2: high_temp_warning\;Bit 3: low_temp_warning" access="RO" enum="high_temp_alarm=0x1,low_temp_alarm=0x2,high_temp_warning=0x4,low_temp_warning=0x8" offset="0x0.28" size="0x0.4" />
	<field name="tx_ad_eq_fault" descr="Reserved for SFP\;Bitmask for latched Tx adaptive equalization fault flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x4.0" size="0x0.8" />
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
</node>

<node name="mpcir_ext" descr="" size="0x10.0" >
	<field name="all" descr="If set to &apos;01&apos;, activates the flow of preparation for FW ISSU, on all services. The values in op-codes for &quot;per-service&quot; are ignored.\;If set to &apos;10&apos;, returns to operational state on all services. The values in op-codes for &quot;per-service&quot; are ignored.\;11 - Reserved" access="OP" offset="0x0.30" size="0x0.2" />
	<field name="ports" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding _stat fields." access="OP" offset="0x4.0" size="0x0.2" />
	<field name="ports_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done service handling [Internal]: busy with some other critical flow)." access="RO" offset="0xC.0" size="0x0.2" />
</node>

<node name="mpcnt_reg_counter_set_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="pcie_perf_counters_ext" descr="" subnode="pcie_perf_counters_ext" offset="0x0.0" selected_by="PCIE_performance_counters" size="0xf8.0" />
	<field name="pcie_physical_layer_ext" descr="" subnode="pcie_physical_layer_ext" offset="0x0.0" selected_by="PCIE_physical_layer_indications" size="0x4.0" />
</node>

<node name="mpcnt_reg_ext" descr="" size="0x100.0" >
	<field name="grp" descr="Performance counter group.\;0: PCIE_performance_counters\;3: PCIE_physical_layer_indications\; \;" access="INDEX" enum="PCIE_performance_counters=0x0,PCIE_physical_layer_indications=0x3" offset="0x0.0" size="0x0.6" />
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIe index number (Internal domain index)\;Reserved when access is from the host" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="clr" descr="Clear counters. Setting the clr bit will reset the counter value for all counters in the counter group. This bit can be set for both Set() and Get() operation." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="counter_set" descr="Counter set as described in\;Table 566, &quot;PCIe Performance Counters Data Layout,&quot; on page 864\;Table 572, &quot;PCIE Physical Layer Indication Layout,&quot; on page 870" subnode="mpcnt_reg_counter_set_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).grp" />
</node>

<node name="mpecs_reg_ext" descr="" size="0x20.0" >
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIE index number\;Reserved when access is from the host" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
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
	<field name="field_select" descr="Field select indicated which writable fields to modify.\;Bit 0: tx_lossy_overflow_oper\;Bit 1 : outbound_stalled_reads_th\;Bit 2 :outbound_stalled_writes_th\;Bit 3 : tx_overflow_sense\;Bit 4 : mark_tx_action_cqe\;Bit 5 : mark_tx_action_cnp\;Bit 6: virtual_hot_plug_unplug (supported only for internal host)" access="WO" offset="0x4.0" size="0x0.16" />
	<field name="tx_lossy_overflow_oper" descr="When overflow encountered for lossy packets, it will be dropped or marked and will be counted in &quot;tx_overflow_buffer_dropped_pkt&quot; or &quot;tx_overflow_buffer_marked_pkt&quot; counter.\;00 - Disabled\;01 - drop - overflow traffic will be dropped.  \;10 - mark - overflow traffic will be marked in the CE field in the CqE.  Supported only when MCAM.mark_tx_action_cqe or MCAM.mark_tx_action_cnp are &apos;1&apos;. \;" access="RW" offset="0x8.0" size="0x0.2" />
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
	<field name="link_speed_enabled" descr="Max Link Speed:\;Bit 0: 2.5G - (Gen1)\;Bit 1: 5G - (Gen2)\;Bit 2: 8G - (Gen3)\;Bit 4: 16G - (Gen4)\;Bit 5: 32G (Gen5)" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="link_width_enabled" descr="Maximum Link Width enabled:\;1: 1x\;2: 2x\;4: 4x\;8: 8x\;16: 16x" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="link_speed_active" descr="Current Link Speed:\;Bit 0: 2.5G (Gen1)\;Bit 1: 5G (Gen2)\;Bit 2: 8G (Gen3)\;Bit 4: 16G (Gen4)\;Bit 5: 32G (Gen5)" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="link_width_active" descr="Negotiated Link Width, pcie_link_width active:\;1: 1x\;2: 2x\;4: 4x\;8: 8x\;16: 16x" access="RO" offset="0xC.16" size="0x0.8" />
	<field name="lane0_physical_position" descr="The physical lane position of logical lane0" access="RO" offset="0xC.24" size="0x0.8" />
	<field name="num_of_vfs" descr="Number of Total Virtual Functions (for all PFs)" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="num_of_pfs" descr="Number of Physical Functions (PFs)" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="bdf0" descr="Bus Device Function - only for function0" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="lane_reversal" descr="Reversal mode of the link:\;0 - straight \;1 - reversal\;\;Note: together with lane0_physical_position provide the physical lane." access="RO" offset="0x18.0" size="0x0.1" />
	<field name="port_type" descr="Indicates the specific type of this PCI Express Function. Note that different Functions in a multi-Function device can generally be of different types.\;0 - PCI Express Endpoint port\;4 - Root Port of PCI Express Root Complex\;5 - PCI Express Upstream port\;6 - PCI Express Downstream port" access="RO" offset="0x18.12" size="0x0.4" />
	<field name="pwr_status" descr="Indicates the status of PCI power consumption limitations.\;0: PCI power report could not be read.\;1: Sufficient power reported.\;2: Insufficient power reported.\;3-7: Reserved" access="RO" offset="0x18.16" size="0x0.3" />
	<field name="max_payload_size" descr="Max payload size in bytes:\;0 - 128B\;1 - 256B\;2 - 512B\;3 - 1024B\;4 - 2048B\;5 - 4096B" access="RO" offset="0x18.24" size="0x0.4" />
	<field name="max_read_request_size" descr="Max read request size in bytes:\;0 - 128B\;1 - 256B\;2 - 512B\;3 - 1024B\;4 - 2048B\;5 - 4096B" access="RO" offset="0x18.28" size="0x0.4" />
	<field name="pci_power" descr="Power reported by the PCI device. The units are in Watts.\;0: Power is unknown." access="RO" offset="0x1C.0" size="0x0.12" />
	<field name="link_peer_max_speed" descr="Peer Max Link Speed:\;Bit 0: 2.5G - (Gen1)\;Bit 1: 5G - (Gen2)\;Bit 2: 8G - (Gen3)\;Bit 4: 16G - (Gen4)\;Bit 5: 32G (Gen5)" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="device_status" descr="device_status bit mask:\;Bit 0: Correctable_error\;Bit 1: Non_Fatal_Error_detection\;Bit 2: Fatal_Error_detected\;Bit 3: Unsupported_request_detected\;Bit 4: AUX_power \;Bit 5: Transaction_Pending" access="RO" enum="Correctable_error=0x1,Non_Fatal_Error_detection=0x2,Fatal_Error_detected=0x4,Unsupported_request_detected=0x8,AUX_power=0x10,Transaction_Pending=0x20" offset="0x24.16" size="0x0.16" />
</node>

<node name="mpeinj_reg_ext" descr="" size="0x20.0" >
	<field name="error_type" descr="Error type selector.\;See at Table 584, &quot;MPEINJ Error List and Params,&quot; on page 881 for error_index." access="RW" offset="0x0.0" size="0x0.8" />
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIE index number\;Reserved when access is from the host" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="error_duration" descr="Depending on the error type, can be either -    \;Number of packets or number of usecs to apply the error according to Table 584, &quot;MPEINJ Error List and Params,&quot; on page 881.\;For Read access, the current value is returned (how many errors/time are left to be executed), or 0 if no error is pending injection" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="start_delay" descr="Delay in usecs before the error is applied.\;For Read access, the current value of this timer is returned." access="RW" offset="0x8.0" size="0x0.24" />
	<field name="dest_bdf" descr="Destination BDF for applicable errors   ." access="RW" offset="0xC.0" size="0x0.16" />
	<field name="error_params_0" descr="Error specific parameters according to Table 584, &quot;MPEINJ Error List and Params,&quot; on page 881." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="error_params_1" descr="Error specific parameters according to Table 584, &quot;MPEINJ Error List and Params,&quot; on page 881." access="RW" offset="0x14.0" size="0x4.0" />
	<field name="error_params_2" descr="Error specific parameters according to Table 584, &quot;MPEINJ Error List and Params,&quot; on page 881." access="RW" offset="0x18.0" size="0x4.0" />
	<field name="error_params_3" descr="Error specific parameters according to Table 584, &quot;MPEINJ Error List and Params,&quot; on page 881." access="RW" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mpgo_reg_ext" descr="" size="0x14.0" >
	<field name="set_pd" descr="Set pulse duration" access="WO" offset="0x0.0" size="0x0.1" />
	<field name="next_pulse_time_stamp" descr="Next Pulse Time Stamp\;Start time of next trigger\;Units are device time units" subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="pulse_duration" descr="Pulse Duration\;Units are mSec\;Default is 100\;Set only when set_pd = &apos;1&apos;" access="RW" offset="0x10.0" size="0x0.10" />
</node>

<node name="mpir_ext" descr="" size="0x10.0" >
	<field name="host_buses" descr="Number of PCIe buses available for the host to connect ot the device.\;&apos;0&apos; when operating in non-Socket-Direct mode." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="Internal domain index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="sdm" descr="Socket-Direct mode indication.\;0: non-Socket-Direct mode (single host or multi-host)\;1: Socket-Direct mode, for querying host" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="subordinate_bus" descr="sunbordinate bus - the highest bus number that subordinates to switch.\;Default value of &apos;0&apos; in case it is not a switch port." access="RO" offset="0x4.0" size="0x0.8" />
	<field name="secondary_bus" descr="secondary bus - the internal logic bus in the switch. \;Default value of &apos;0&apos; in case it is not a switch port." access="RO" offset="0x4.8" size="0x0.8" />
	<field name="sd_group" descr="The Socket Direct group index of the matching PF. \;Value 0x0 indicates no grouping" access="RO" offset="0x8.0" size="0x0.3" />
	<field name="device" descr="PCIe device number." access="RO" offset="0x8.3" size="0x0.5" />
	<field name="lp_msb" descr="2-bit expansion of the local port. Represents the local_port[9:8] bits" access="RO" offset="0x8.12" size="0x0.2" />
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
	<field name="info_type" descr="Type of information string to be queried:\;0x0: VPD - Read the PCI Vital Product Data capability content.\;0x1: MODEL_NAME\;0x2: MODEL_DESCRIPTION\;0x3: IMAGE_VSD\;0x4: DEVICE_VSD\;0x5: ROM_INFO\;other values are reserved." access="INDEX" enum="MODEL_NAME=0x1,MODEL_DESCRIPTION=0x2,IMAGE_VSD=0x3,DEVICE_VSD=0x4,ROM_INFO=0x5" offset="0x0.0" size="0x0.8" />
	<field name="info_length" descr="Total size of the information string, according to info_type. Value given in bytes." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="read_length" descr="Number of bytes requested. The device returns the number of bytes actually read." access="RW" offset="0x8.0" size="0x0.16" />
	<field name="read_offset" descr="Offset in bytes of the first byte requested to read." access="INDEX" offset="0x8.16" size="0x0.16" />
	<field name="info_string" descr="Information string accessed, according to info_type. If the information is not available, a NULL string is returned." access="RO" high_bound="7" low_bound="0" offset="0x10.24" size="0x8.0" />
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

<node name="msci_ext" descr="" size="0xc.0" >
	<field name="index" descr="CPLD index" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="version" descr="CPLD version" access="RO" offset="0x4.0" size="0x4.0" />
</node>

<node name="msgi_ext" descr="" size="0x80.0" >
	<field name="serial_number" descr="ASIC serial number (ASCII string)" access="RO" high_bound="5" low_bound="0" offset="0x0.0" size="0x18.0" />
	<field name="part_number" descr="ASIC part number (ASCII string)" access="RO" high_bound="4" low_bound="0" offset="0x20.0" size="0x14.0" />
	<field name="revision" descr="Revision (ASCII string)" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="product_name" descr="Product Name (ASCII string)" access="RO" high_bound="15" low_bound="0" offset="0x40.0" size="0x40.0" />
</node>

<node name="mtcap_ext" descr="" size="0x10.0" >
	<field name="sensor_count" descr="Number of ASIC+platform sensors supported by the device \;This includes the ASIC and the ambient sensors. Module sensors are not included.\;This actually is equal to sum of all &apos;1&apos; in sensor_map\;Range 1..64\;\;Known sensors:\;0: current asic temp, FW exposes current max(all diode temp sensors)\;1..63: ambient, supported only for unmanaged switch, defined by ini\;64..127: modules (not exposed by this field)" access="RO" offset="0x0.0" size="0x0.7" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="internal_sensor_count" descr="Number of sensors supported by the device that are on the ASIC.\;Exposes how many ASIC diodes exist. \;The FW exposes all of them as sensor[0]" access="RO" offset="0x4.0" size="0x0.7" />
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Only ASIC and ambient sensors are supported. Each bit represents a sensor.\;Per bit:\;0: Not_connected_or_not_supported\;1: Supports_temperature_measurements" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="mtcq_reg_ext" descr="" size="0x70.0" >
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die.\;For cables, the index represents the module index starting at index 1 while index 0 indicates the host device." access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="status" descr="Indicates the status of the desired token we are generating the challenge for.\;0x0 - OK\;0x1 - TOKEN_ALREADY_APPLIED\;0x2 - TOKEN_NOT_SUPPORTED\;0x3 - NO_KEY_CONFIGURED (there is no public_key that can be used for this token) \;0x4 - INTERFACE_NOT_ALLOWED (asking for local token from remote interface, or remote token from local interface)" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="token_opcode" descr="The token which a challenge is generated for.\;0: RMCS\;1: RMDT\;2: CRCS - supported from Spectrum-4 and above\;3: CRDT - supported from Spectrum-4 and above\;Other: Reserved" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="keypair_uuid" descr="The UUID of the key used to generate the challenge." access="RO" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
	<field name="base_mac" descr="Device base MAC address / unique identifier." subnode="uint64" access="RO" offset="0x14.0" size="0x8.0" />
	<field name="psid" descr="Device PSID" access="RO" high_bound="3" low_bound="0" offset="0x1C.0" size="0x10.0" />
	<field name="fw_version_39_32" descr="Device FW version" access="RO" offset="0x2C.0" size="0x0.8" />
	<field name="fw_version_31_0" descr="Device FW version" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="source_address" descr="Source address of debug requester. DLID for Infiniband, ETH / IBg2 - TBD.\;Valid only for RMCS/RMDT." access="RO" high_bound="3" low_bound="0" offset="0x34.0" size="0x10.0" />
	<field name="session_id" descr="Unique debug session identifier. \;See details in REMOTE_DEBUG_KEEP_ALIVE.\;Valid only for RMCS." access="RO" offset="0x44.0" size="0x0.16" />
	<field name="challenge_version" descr="Version of the challenge format." access="RO" offset="0x44.24" size="0x0.8" />
	<field name="challenge" descr="Random generated field. Used for randomness and replay-protection." access="RO" high_bound="7" low_bound="0" offset="0x48.0" size="0x20.0" />
</node>

<node name="mtctr_reg_ext" descr="" size="0x18.0" >
	<field name="second_clock_cross_timestamp_request" descr="An index for the second clock to get cross-timestamps from:    \;0: NOP - no timestamp requested.   \;1: PTM_ROOT_CLOCK - request timestamp from the PTM root clock. Allowed only if MTPTM.ptsa is set.    \;2: FREE_RUNING - request timestamp from the device&apos;s Free-Running counter (AKA the internal timer). When requested in parallel to PTM root clock, this will return a PTM Requester timestamp from the FR counter.   \;3: REAL_TIME - request timestamp from the device&apos;s Real-Time clock. When requested in parallel to PTM root clock, this will return a PTM Requester timestamp from the RT clock. The return timestamp will be in RT format:   \;- The high 32 bits contain the seconds,    \;- The lower 32 bits contain nanoseconds (only 30 lsbits are used).   \;Other values are reserved.\;Must be different than first_clock_cross_timestamps_request." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="first_clock_cross_timestamp_request" descr="An index for the first clock to get cross-timestamps from:    \;0: NOP - no timestamp requested.   \;1: PTM_ROOT_CLOCK - request timestamp from the PTM root clock. Allowed only if MTPTM.ptsa is set.    \;2: FREE_RUNING - request timestamp from the device&apos;s Free-Running counter (AKA the internal timer). When requested in parallel to PTM root clock, this will return a PTM Requester timestamp from the FR counter.   \;3: REAL_TIME - request timestamp from the device&apos;s Real-Time clock. When requested in parallel to PTM root clock, this will return a PTM Requester timestamp from the RT clock. The return timestamp will be in RT format:   \;- The high 32 bits contain the seconds,    \;- The lower 32 bits contain nanoseconds (only 30 lsbits are used).   \;Other values are reserved." access="INDEX" offset="0x0.24" size="0x0.8" />
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
	<field name="cap_core_tile" descr="Number of processors per tile ASIC." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="cap_core_main" descr="Number of processors in the main ASIC." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="cap_core_dpa" descr="Number of processors in the DPA unit." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="cap_num_of_tile" descr="Number of tiles per device. For devices without tiles (only main ASIC), this field should be &apos;0&apos;." access="RO" offset="0x0.24" size="0x0.8" />
	<field name="type_core_tile" descr="Processor type.\;0: N/A\;1: IRISC\;2: RISC5\;Else: Reserved" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="type_core_main" descr="Processor type.\;0: N/A\;1: IRISC\;2: RISC5\;Else: Reserved" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="type_core_dpa" descr="Processor type.\;0: N/A\;1: IRISC\;2: RISC5\;Else: Reserved" access="RO" offset="0x4.8" size="0x0.4" />
	<field name="is_phy_uc_supported" descr="Indicates wether Phy_UC tracers mapping are supported by the device FW. \;When set, The event_id of the Phy UC of the instance will be calculated by first_tile/main _core _event_id[i] + cap_core_tile/main.\;When clear the Phy UC will be ignored." access="RO" offset="0x4.30" size="0x0.1" />
	<field name="is_dwsn_msb_supported" descr="When set to &apos;1&apos;, the device supports dwsn_msb bit within the FW trace layout." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="first_dpa_core_event_id" descr="The mapping for the rest of the DPA ASIC processors are sequential and the mapping is defined as:\;processor[x]=first_dpacore_event_id+x" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="first_main_core_event_id" descr="The mapping for the rest of the main ASIC processors are sequential and the mapping is defined as:\;processor[x]=first_main_core_event_id+x" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="first_tile_core_event_id" descr="The mapping for the rest of the tile[y] ASIC processors are sequential and the mapping is defined as:\;processor[x]=first_tile_core_event_id[y]+x" access="RO" high_bound="7" low_bound="0" offset="0xC.24" size="0x8.0" />
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
	<field name="temperature" descr="Temperature reading from the sensor. \;Units of 0.125 Celsius degrees.\;For negative values 2&apos;s complement is used (for example: -3.25 Celsius will read as 0xFFE6)" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_temperature" descr="The highest measured temperature from the sensor.\;Reserved when mte = 0\;Cleared by mtr = 1\;Valid only when i = 0\;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="sdme" descr="Shut Down Events Modify Set Enable:\;0: all fields are set\;1: only sdee field is set, all other fields reserved" access="OP" offset="0x8.28" size="0x0.1" />
	<field name="weme" descr="Warning Events Modify Set Enable:\;0: all fields are set\;1: only tee field is set, all other fields reserved" access="OP" offset="0x8.29" size="0x0.1" />
	<field name="mtr" descr="Max Temperature Reset:\;0: do not modify the value of the max temperature register\;1: clear the value of the max temperature register" access="OP" offset="0x8.30" size="0x0.1" />
	<field name="mte" descr="Max Temperature Enable:\;0: disable measuring the max temperature on a sensor\;1: enables measuring the max temperature on a sensor" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="temperature_threshold_hi" descr="temperature_threshold_hi refers to the high threshold of Warning Event. \;If the sensor temperature measurement is above the threshold (and events are enabled), an event will be generated.\;threshold_hi and threshold_lo implements hysteresis mechanism of the threshold preventing toggling of the indication.\;Note that temperature_threshold_hi must be equal or lower than the system requirement.\;System requirement for module is the module warning temperature.\;System requirement for board/silicon sensors is according to product information parameters\;Note that the temperature threshold can be used to generate an event message or an interrupt using GPIO" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="sdee" descr="Temperature Shut Down Event Enable (MTSDE Register)\;0: do_not_generate_event\;1: generate_event\;2: generate_single_event\;\;Supported in downstream devices (devices on slots)." access="RW" offset="0xC.28" size="0x0.2" />
	<field name="tee" descr="Temperature Warning Event Enable (MTEWE Register)\;0: do_not_generate_event\;1: generate_event\;2: generate_single_event\;\;" access="RW" enum="do_not_generate_event=0x0,generate_event=0x1,generate_single_event=0x2" offset="0xC.30" size="0x0.2" />
	<field name="temperature_threshold_lo" descr="temperature_threshold_lo refers to the low threshold of Warning Event. \;The offset threshold_lo implements the lower threshold for the hysteresis mechanism of over temperature alert. Once alert is set, if the temperature goes below this threshold, the alert is cleared.\;Note that temperature_threshold_lo must be at least 5 degrees lower than temperature_threshold_hi" access="RW" offset="0x10.0" size="0x0.16" />
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
	<field name="trc_ver" descr="Indicates the version of the tracing mechanism.\;See Section 26.3.4.1, &quot;Timestamp Event Traces&quot;, on page 1625\;0x0: VER_0\;0x1: VER_1\;Other values are reserved.\;Reserved in Switch" access="RO" offset="0x0.24" size="0x0.2" />
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
	<field name="operation" descr="Operation:\;\;1: SET_TIME_IMMEDIATE - reserved when Spectrum-1\;2: ADJUST_TIME\;3: ADJUST_FREQ_UTC  - On NIC: for Bluefield-4 and onwards update both UTC and FRC\;4: ADJUST_FREQ_FRC - Free Running Clock (DWIP and Switch only)\;5: ADJUST_FREQ_BOTH - (DWIP and Switch only)\;6: ADJUST_PHASE - Supported only if MCAM.mng_feature_cap_mask bit 54 is set." access="OP" enum="ADJUST_TIME=0x2,ADJUST_FREQ_UTC=0x3,ADJUST_FREQ_FRC=0x4,ADJUST_FREQ_BOTH=0x5,ADJUST_PHASE=0x6" offset="0x0.0" size="0x0.4" />
	<field name="log_max_phase_adjustment" descr="[DWIP]\;range is from -(2^ log_max_phase_adjustment) to +2^ log_max_phase_adjustment) in units of ns." access="RO" offset="0x0.5" size="0x0.6" />
	<field name="log_max_freq_adjustment" descr="If 0: Range is from -50,000,000 ppb to +50,000,000 ppb.\;Otherwise: range is from -(2^log_max_freq_adjustment) ppb to +2^log_max_freq_adjustment ppb.\;Note: This field does not change between FW resets" access="RO" offset="0x0.16" size="0x0.5" />
	<field name="freq_adj_units" descr="Updated when operation is ADJUST_FREQ.\;\;0: units_are_ppb - every PPS the HW frequency will be adjusted by this value\;1: units_are_parts_per_million - but with a 16 bit binary fractional field\;2: units_are_parts_per_billion - but with a 16 bit binary fractional field" access="RW" enum="units_are_ppb=0x0,units_are_parts_per_million=0x1,units_are_parts_per_billion=0x2" offset="0x0.24" size="0x0.3" />
	<field name="time_stamp_state" descr="nternal stamp state\;0: FREE_RUNNING\;1: SYNCED" access="RO" enum="FREE_RUNNING=0x0,SYNCED=0x1" offset="0x0.28" size="0x0.2" />
	<field name="time_stamp_mode" descr="Internal stamp mode\;0: INTERNAL_TIMER\;1: REAL_TIME\;\;Other values are reserved." access="RO" enum="INTERNAL_TIMER=0x0,REAL_TIME=0x1" offset="0x0.30" size="0x0.2" />
	<field name="freq_adjustment" descr="Units are per MTUTC.freq_adj_units value. Frequency adjustment: Every PPS the HW frequency will be adjusted by this value. \; field.\;Updated when operation is ADJUST_FREQ\;\;Range is from -50,000,000 ppb to +50,000,000 ppb" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="utc_sec" descr="UTC seconds\;Updated when operation is SET_TIME_IMMEDIATE" access="WO" offset="0x10.0" size="0x4.0" />
	<field name="utc_nsec" descr="UTC nSecs\;Range 0..(10^9-1)\;Updated when operation is SET_TIME_IMMEDIATE" access="WO" offset="0x14.0" size="0x0.30" />
	<field name="time_adjustment" descr="Time or phase adjustment\;Updated when operation is ADJUST_TIME or ADJUST_PHASE.\;\;When ADJUST_TIME:\;Time adjustment, Units of nSec, Range is from -32768 to 32768.\;If MCAM.time_adjust_range_extended==1, range is from -200,000 to +200,000.\;\;\;When ADJUST_PHASE:\;Phase adjustment, Units of nSec, Range is according to log_max_ phase_adjustment field.\;" access="WO" offset="0x18.0" size="0x4.0" />
</node>

<node name="mvcap_reg_ext" descr="" size="0x10.0" >
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Each bit represents a sensor. \;The bitmap refers only for ambient sensors, no module and no ASIC.\;0: Not connected or not supported\;1: Supports voltage and current measurements" subnode="uint64" access="RO" offset="0x0.0" size="0x8.0" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x8.0" size="0x0.4" />
</node>

<node name="mvcr_ext" descr="" size="0x18.0" >
	<field name="sensor_index" descr="Sensors:\;- 0..max_system_sensors-1 are ambient sensors on the system (max_system_sensors from INI)\;" access="INDEX" offset="0x0.0" size="0x0.7" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="voltage_sensor_value" descr="Voltage reading from the sensor. \;Voltage units are 0.01V." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="current_sensor_value" descr="Current reading from the sensor." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="current_sensor_value_msb" descr="Current reading from the sensor msb." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="sensor_name" descr="Sensor Name\;8 character long sensor name.\;Reserved for index 64 - 127 (modules sensors)" subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="ncfg_reg_ext" descr="" size="0x40.0" >
	<field name="field_select" descr="In Query, indicates which fields are supported.\;In Write, indicates which field to modify.\;Bit 0x0: roce_offload_disable" subnode="uint64" access="RW" offset="0x0.0" size="0x8.0" />
	<field name="roce_offload_disable" descr="If set, then ROCE is disabled for VFs/SFs belong to it." access="RW" offset="0x8.0" size="0x0.1" />
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
	<field name="cap_data" descr="Capability information according to cap_group.\;For DPA_CAP See Table 1537, &quot;DPA_CAP Capability Layout,&quot; on page 1786" subnode="nic_cap_ext_reg_cap_data_auto_ext" access="RO" offset="0x10.0" size="0x70.0" />
</node>

<node name="nic_dpa_eu_partition_reg_ext" descr="" size="0x300.0" >
	<field name="eu_partition_id" descr="DPA EU partition id\;For WRITE method with operation CREATE this field is RO and provides the newly created EU partition ID.\;For other method/operation, this field is an index to a valid EU partition" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="operation" descr="Operation performed for WRITE method:\;0x0: CRETAE - create a new partition\;0x1: MODIFY - change the parameters of an existing partition, absed on modify_field_select\;0x2: DESTROY - destroy an existing partition\;other values are reserved." access="WO" enum="CRETAE=0x0,MODIFY=0x1,DESTROY=0x2" offset="0x0.28" size="0x0.3" />
	<field name="modify_field_select" descr="Bitmask indicating which parameter is modified by MODIFY operation. Set bit indicates the field should be updated.\;bit 0: member_mask\;bit 1: max_num_eug\;bit 2: num_vhca_id_and_vhca_id\;other bits are reserved.\;For Query method, set bit indicates the relevant modification is supported" access="RW" enum="member_mask=0x1,max_num_eug=0x2,num_vhca_id_and_vhca_id=0x4" offset="0x4.0" size="0x4.0" />
	<field name="max_num_eug" descr="The maximal number of groups allowed for EUs in the partition" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="num_vhca_id" descr="The number of valid entries in vhca_id array. Value must not exceed DPA_CAP,max_num_partition_vhca_id" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="member_mask" descr="Bitmask indicating which EUs are members of the partition. Set bit indicates the respective EU is a member. EU partitions may not overlap, and EUs beyond DPA_CAP.max_num_dpa_eu are reserved." access="RW" high_bound="31" low_bound="0" offset="0x40.0" size="0x80.0" />
	<field name="vhca_id" descr="Array of VHCA IDs indicating which functions are allowed to use this partition. Array size is determined by num_vhca_id, entries with index num_vhca_id or higher are reserved." access="RW" high_bound="255" low_bound="0" offset="0xC0.16" size="0x200.0" />
</node>

<node name="nic_dpa_eug_reg_ext" descr="" size="0x100.0" >
	<field name="eug_id" descr="DPA EUG id\;For WRITE method with operation CREATE this field is RO and provides the newly created EUG.\;For other method/operation, this field is an index to a valid EUG" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="operation" descr="Operation performed for WRITE method:\;0x0: CRETAE - create a new DPA EUG\;0x1: MODIFY - change the members of an existing DPA EUG\;0x2: DESTROY - destroy an existing DPA EUG\;other values are reserved." access="WO" enum="CRETAE=0x0,MODIFY=0x1,DESTROY=0x2" offset="0x0.28" size="0x0.3" />
	<field name="modify_field_select" descr="Bitmask indicating which parameter is modified by MODIFY operation. Set bit indicates the field should be updated.\;bit 0: member_mask\;other bits are reserved.\;For Query method, set bit indicates the relevant modification is supported" access="RW" enum="member_mask=0x1" offset="0x4.0" size="0x4.0" />
	<field name="eug_name" descr="EUG name (ASCII string)" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="member_mask" descr="Bitmask indicating which EUs are members of the group. Set bit indicates the respective EU is a member. EUGs may not overlap, and EUs beyond NIC_CAP_EXT_REG.max_num_dpa_eu are reserved." access="RW" high_bound="31" low_bound="0" offset="0x40.0" size="0x80.0" />
</node>

<node name="nic_dpa_perf_ctrl_reg_ext" descr="" size="0x40.0" >
	<field name="dpa_process_id" descr="dpa_process object id.\;0xffffffff: Applies to all processes (all processes are not valid in read)" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="other_vhca_id" descr="vhca_id where the process is created" access="WO" offset="0x4.0" size="0x0.16" />
	<field name="sample_type" descr="Selects the sampling type. Supported types are indicated byNIC_CAP_EXT.dpa_perf_sample_type\;0x0: CUMMULATIVE_EVENT\;0x1: EVENT_TRACER\;Other values are reserved" access="RW" enum="CUMMULATIVE_EVENT=0x0,EVENT_TRACER=0x1" offset="0x4.24" size="0x0.3" />
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

<node name="paos_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Port operational state:\;1: up\;2: down\;4: down_by_port_failure - (transitioned by the hardware)\;  \;" access="RO" enum="up=0x1,down=0x2,down_by_port_failure=0x4" offset="0x0.0" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="admin_status" descr="Port administrative state (the desired state of the interface):\;1: up\;2: down_by_configuration\;3: up_once - if the port goes up and then down, the operational status should go to &quot;down by port failure&quot; and can only go back up upon explicit command\;4: disabled_by_system - this mode cannot be set by the software, only by the hardware.\;6: sleep - can be configured only if sleep_cap is set. Note that a sleep setting will cause the port to transition immediately into sleep state regardless of previous admin_status.\;[Internal] opcode 5 is used only in NIC, for fast link up drivers after device boot. For most usecase the rate will be SDR, lowest rate support in IB systems. \;\;\;[Internal] - up_once shall not be used for GPU case. In order to define link down state set PLDS register" access="RW" enum="up=0x1,down_by_configuration=0x2,up_once=0x3,disabled_by_system=0x4,sleep=0x6" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.\;Switch partition ID with which to associate the port.\;Switch partitions are numbered from 0 to 7 inclusively.\;The swid field is only valid when the local_port is the router port. In this case, the swid indicates which of the router ports to configure/query." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="e" descr="Event generation on operational state change (oper_status):\;0: Do_not_generate_event\;1: Generate_Event \;2: Generate_Single_Event\;\;Not Supported for HCA." access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="physical_state_status" descr="IB Port Physical link state:\;0: N/A\;1: Sleep\;2: Polling\;3: Disabled\;4: PortConfigurationTraining\;5: LinkUp\;6-15: reserved\;Note that physical state of 1,2,3,4 will all be reflected as oper_status = down.\;[internal] Note: Supported from XDR devices onwards\;Ethernet devices that support this field will use only bits 2,3,5." access="RO" enum="N_A=0x0,Sleep=0x1,Polling=0x2,Disabled=0x3,PortConfigurationTraining=0x4,LinkUp=0x5" offset="0x4.4" size="0x0.4" />
	<field name="fd" descr="Force down.\;Supported only when indicated in PCAM\;Can be set only with admin_status = 2 (&apos;down_by_configuration&apos;), will force link to be down. \;" access="RW" offset="0x4.8" size="0x0.1" />
	<field name="sleep_cap" descr="Sleep capability:\;0: Sleep state is not supported\;1: Sleep state supported" access="RO" offset="0x4.9" size="0x0.1" />
	<field name="ps_e" descr="Event generation for physical state.\;On set operation, will be ignored if ee_ps is not set.\;When bit is set, will generate an event for transition into state.\;Bit 0: Sleep\;Bit 1: LinkUp \;Note - LinkUp for an Ethernet link refers to PhyUp state where local side is ready, but not necessarily that peer side is also ready.\;Bit 2: Disabled\;Bit 3: PortConfigurationTraining\;Not Supported for HCA." access="RW" enum="Sleep=0x1,LinkUp=0x2,Disabled=0x4,PortConfigurationTraining=0x8" offset="0x4.12" size="0x0.4" />
	<field name="logical_state_status" descr="IB or NVLink Port Logical link state:\;0: N/A\;1: Down\;2: Init\;3: Arm\;4: Active" access="RO" enum="N_A=0x0,Down=0x1,Init=0x2,Arm=0x3,Active=0x4" offset="0x4.16" size="0x0.3" />
	<field name="ls_e" descr="event generation mask for logical state.\;On set operation, will be ignored when ee_ls is not set.\;When bit is set, will generate event for transition into state.\;Bit 0: Down\;Bit 1: Init\;Bit 2: Arm\;Bit 3: Active\;Not Supported for HCA." access="RW" enum="Down=0x1,Init=0x2,Arm=0x4,Active=0x8" offset="0x4.20" size="0x0.4" />
	<field name="ee_ps" descr="Event update enable for physical state. If this bit is set, event generation will be updated based on the ps_e field. Only relevant on Set operations.\;Not Supported for HCA." access="WO" offset="0x4.28" size="0x0.1" />
	<field name="ee_ls" descr="Event update enable for logical state. If this bit is set, event generation will be updated based on the ls_e field. Only relevant on Set operations.\;Not Supported for HCA." access="WO" offset="0x4.29" size="0x0.1" />
	<field name="ee" descr="Event update enable. If this bit is set, event generation will be updated based on the e field. Only relevant on Set operations.\;Not Supported for HCA." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="ase" descr="Admin state update enable. If this bit is set, admin state will be updated based on admin_state field. Only relevant on Set() operations." access="WO" offset="0x4.31" size="0x0.1" />
</node>

<node name="pbmc_reg_ext" descr="" size="0x6c.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="xoff_refresh" descr="The time before a new pause frame should be sent to refresh the pause state. Using the same units as xoff_timer_value above." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="xoff_timer_value" descr="When device generates a pause frame, it uses this value as the pause timer.\;The pause timer is measured in units of pause &quot;quanta&quot;, where each unit is equal to 512 bit times." access="RW" offset="0x4.16" size="0x0.16" />
	<field name="port_buffer_size" descr="Total packet buffer array available for the port. The sum of buffer array allocated to bufferX must not exceed port_buffer_size.\;In Spectrum and above- Max supported Headroom buffer for port. \;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="fullness_threshold" descr="Almost full threshold configuration.\;Percentage of buffer fullness which indicates &quot;almost full&quot; occurrence\;Range: 0-100%\;Reserved for Switches." access="RW" offset="0x8.16" size="0x0.7" />
	<field name="buffer" descr="Configuring per-buffer parameters. i=0..9" subnode="bufferx_reg_ext" access="RW" high_bound="9" low_bound="0" offset="0xC.0" size="0x50.0" />
	<field name="shared_headroom_pool" descr="Configuring shared haeadroom pool parameters. Using the same layout as in BufferX, for details see Table 2047, &quot;bufferX Register Layout,&quot; on page 2390.\;Not supported in SwitchX and SwitchX-2\;Not supported in HCA (See PCAM shp_pbmc_pbsr_support bit)." subnode="bufferx_reg_ext" access="RW" offset="0x5C.0" size="0x8.0" />
	<field name="port_shared_buffer" descr="Configuring port shared buffer parameters. Using the same layout as in BufferX, for details see Table 2047, &quot;bufferX Register Layout,&quot; on page 2390.\;Not supported in SwitchX and SwitchX-2\;Valid for HCA when pbmc_port_shared_buffer is set in PCAM." subnode="bufferx_reg_ext" access="RW" offset="0x64.0" size="0x8.0" />
</node>

<node name="pbsr_reg_ext" descr="" size="0x64.0" >
	<field name="buffer_type" descr="Valid only for 8x port setting (see PMLP): \;1: Main buffer\;2: Secondary buffer" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clear_wm_buff_mask" descr="Each bit represents a stat_buffer\;per bit:\;0: do not clear watermark\;1: clear watermark\;Reserved when clear_wm = 1" access="OP" offset="0x4.0" size="0x0.10" />
	<field name="used_shared_headroom_buffer" descr="Number of currently used shared headroom buffer cells." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="clear_wm" descr="Clear watermarks for all PGs" access="OP" offset="0x8.31" size="0x0.1" />
	<field name="stat_buffer" descr="status per-buffer parameters. i=0..9\;" subnode="stat_bufferx_reg_ext" access="RO" high_bound="9" low_bound="0" offset="0xC.0" size="0x50.0" />
	<field name="stat_shared_headroom_pool" descr="status of shared headroom pool parameters. Using the same layout as in stat_BufferX, for details see Table 2068, &quot;stat_bufferX Register Layout,&quot; on page 2417.\;Not supported in SwitchX and SwitchX-2\;Not supported in HCA (See PCAM shp_pbmc_pbsr_support bit). \;Not supported in GPUNet" subnode="stat_bufferx_reg_ext" access="RO" offset="0x5C.0" size="0x8.0" />
</node>

<node name="pcam_reg_ext" descr="" size="0x50.0" >
	<field name="access_reg_group" descr="Access Register ID groups\;0: RegID_0x5000_to_0x507F\;1: RegID_0x5080_to_50FF\;Values 2-255 are Reserved" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="pl_op" descr="Reserved for non-planarized port.\;Features and access regs will be presented according to:\;0: aggregated_port_access\;1: plane_port_access" access="OP" enum="aggregated_port_access=0x0,plane_port_access=0x1" offset="0x0.8" size="0x0.1" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features \;Values 1 - 255 are Reserved" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="port_access_reg_cap_mask" descr="Supported port&apos;s access register bitmaks. Based on access_reg_group index.\;When bit is set , The register is supported in the device. \;When access_reg_group == 0 :\;Bit_0: 0x5000 \;Bit_1: 0x5001 (PCAP)\;Bit_2: 0x5002 (PMLP)\;Bit_3: 0x5003 (PMTU)\;Bit_4: 0x5004 (PTYS)\;Bit_127: 0x507F (PCAM)\;" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="feature_cap_mask" descr="Supported port&apos;s enhanced features. Based on feature_group index.\;When bit is set, The feature is supported in the device: \;Bit 0: PPCNT_counter_group_Phy_statistical_counter_group \;Bit 1 - PPCNT_counter_group_Discard_counter_group\;Bit 9: PFCC - support of stall mask and global rx,tx mask. \;Bit 10: PMCR - support of tx_disable override.\;Bit 11: PPCNT_counter_group - IB Extended port counter group\;Bit 12: PPCNT_Extended_Ethernet_group - tx packet size histograms\;Bit 13: PTYS_extended_Ethernet_support\;Bit 14: PMAOS_reset_toggle_support\;Bit 15: Set_Module_low_power_supported \;Bit 16: Module_power_optimization_is_supported_in_PPSC\;Bit 17: Support_of_IB_force_state_machine_in_PTYS - (an_disable)\;Bit 18: PPCNT_Extended_Ethernet_group_icrc_counter\;Bit 19: cm2_en_is_supported_in_PCAP\;Bit 20: time_tolink_up_is_supported_in_PDDR\;Bit 21: gearbox_die_num_field_is_supported_in_PMDR\;Bit 22: force_entropy_entropy_calc_entropy_gre_calc - and capability bits are supported in PCMR\;Bit 23: FEC_override_support_for_50G_per_lane_is_supported_in_PPLM\;Bit 25: PTYS_allow_both_extended_and_legacy_protocol_masks\;Bit 26: PPCNT_eth_per_tc_cong_group_supported\;Bit 27: pnat_sup_host - the device supports pnat = 2 (host) when set to &apos;1&apos;\;Bit 28: ppcnt_no_buffer_discard_uc - this counter is supported in PPCNT when set to &apos;1&apos;\;Bit 29: pbmc_port_shared_buffer - supported in PBMC.\;Bit 30: PLR_max_retry_window_support - PPCNT group 0x22 max retry per window\;Bit 32: PDDR_ext_eth_proto_support\;Bit 40: PAOS - support of admin_status opcode 5: &quot;up_lowest_rate&quot;\;Bit 41: PMAOS - support of &quot;opertional_notifcation&quot; field\;Bit 42: PRBS_polarity_support - support of polarity bits in PPTT and PPRT\;Bit 43: PDDR_register_is_supported\;Bit 44: pfcc_buffer_onwership - PFCC buffer ownership is supported.\;Bit 45: force_down - supported in PAOS reg.\;Bit 46: pmlp_lane_mapping_off - Support of m_lane_m field in PMLP.\;Bit 51: ppcnt_symobl_ber\;Bit 52: shp_pbmc_pbsr_support\;Bit 54: ppcnt_effective_error_counter\;Bit 55: FEC_override_support_for_100G_per_lane_is_supported_in_PPLM\;Bit 57: PMECR_option_to_not_generate_events_upon_PMLP_set\;Bit 64: Local_port_MSB - bits [9:8] supported\;Bit 65: PDDR_moule_latched_info_page_supported\;Bit 66: PDDR_module_info_ext_supported\;Bit 70: SLTP_tx_policy_supported\;Bit 71: pmcr_capability_bits_supported\;Bit 72: pmtu_max_admin_mtu_supported\;Bit 73: PPCNT_grp_profile_supported\;Bit 77: PPCNT.physical_layer_counters_RS_FEC_8_lanes_supported\;Bit 85: PPCNT.counters_cap\;Bit 86: SLTP.lane_broadcast_supported\;Bit 87: PMMP.apply_im_supported\;Bit 91: SLRG.all_lanes_supported\;Bit 92: PIPG.ipg_oper_ipg_cap_idx_supported\;Other bits are reserved" access="RO" enum="PPCNT_counter_group_Phy_statistical_counter_group=0x1,PFCC=0x200,PMCR=0x400,PPCNT_counter_group=0x800,PPCNT_Extended_Ethernet_group=0x1000,PTYS_extended_Ethernet_support=0x2000,PMAOS_reset_toggle_support=0x4000,Set_Module_low_power_supported=0x8000,Module_power_optimization_is_supported_in_PPSC=0x10000,Support_of_IB_force_state_machine_in_PTYS=0x20000,PPCNT_Extended_Ethernet_group_icrc_counter=0x40000,cm2_en_is_supported_in_PCAP=0x80000,time_tolink_up_is_supported_in_PDDR=0x100000,gearbox_die_num_field_is_supported_in_PMDR=0x200000,force_entropy_entropy_calc_entropy_gre_calc=0x400000,FEC_override_support_for_50G_per_lane_is_supported_in_PPLM=0x800000,PTYS_allow_both_extended_and_legacy_protocol_masks=0x2000000,PPCNT_eth_per_tc_cong_group_supported=0x4000000,pnat_sup_host=0x8000000,ppcnt_no_buffer_discard_uc=0x10000000,pbmc_port_shared_buffer=0x20000000,PLR_max_retry_window_support=0x40000000,PDDR_ext_eth_proto_support=0x1,PAOS=0x100,PMAOS=0x200,PRBS_polarity_support=0x400,PDDR_register_is_supported=0x800,pfcc_buffer_onwership=0x1000,force_down=0x2000,pmlp_lane_mapping_off=0x4000,ppcnt_symobl_ber=0x80000,shp_pbmc_pbsr_support=0x100000,ppcnt_effective_error_counter=0x400000,FEC_override_support_for_100G_per_lane_is_supported_in_PPLM=0x800000,PMECR_option_to_not_generate_events_upon_PMLP_set=0x2000000,Local_port_MSB=0x1,PDDR_moule_latched_info_page_supported=0x2,PDDR_module_info_ext_supported=0x4,SLTP_tx_policy_supported=0x40,pmcr_capability_bits_supported=0x80,pmtu_max_admin_mtu_supported=0x100,PPCNT_grp_profile_supported=0x200,PPCNT_physical_layer_counters_RS_FEC_8_lanes_supported=0x2000,PPCNT_counters_cap=0x200000,SLTP_lane_broadcast_supported=0x400000,PMMP_apply_im_supported=0x800000,SLRG_all_lanes_supported=0x8000000,PIPG_ipg_oper_ipg_cap_idx_supported=0x10000000" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="pcap_reg_ext" descr="" size="0x14.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cm2_en" descr="port_capability_mask[95:80] is supported if set to &apos;1&apos;." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="port_capability_mask" descr="Sets the PortInfoCapabilityMask:\;Specifies the supported capabilities of this node. A bit set to 1 for affirmation of supported capability.\;port_capability_mask[127:96] is mapped to CapabilityMask in PortInfo MAD.\;port_capability_mask[95:80] is mapped to CapabilityMask2 in PortInfo MAD.\;\;\;" access="RW" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
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
	<field name="rx_ts_over_crc_cap" descr="Specifies the ingress timestamps enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.13" size="0x0.1" />
	<field name="rx_fcs_drop_cap" descr="Specifies the ingress drop enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.14" size="0x0.1" />
	<field name="tx_fcs_recalc_cap" descr="Specifies the egress drop enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.15" size="0x0.1" />
	<field name="tx_ts_over_crc_cap" descr="Specifies the egress timestamps enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.16" size="0x0.1" />
	<field name="entropy_gre_calc_cap" descr="Specifies the egress GRE tunnel protocol entropy calculation enable/disable capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.29" size="0x0.1" />
	<field name="entropy_calc_cap" descr="Specifies the egress tunnel protocol entropy calculation enable/disable capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.30" size="0x0.1" />
	<field name="force_entropy_cap" descr="Specifies the egress tunnel protocol entropy calculation force capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="fcs_chk" descr="FCS check\;Values:\;0: disable check. \;1: perform check\;Note: when disabling a check, it will also affects the relevant counters." access="RW" offset="0x8.1" size="0x0.1" />
	<field name="rx_ts_over_crc" descr="RX TimeStamp over FCS\;0: no TS over FCS\;1: TS over FCS\;Note: \;1. If this filed is changed while traffic is passing then some packets may be dropped due to incorrect FCS.\;2. Default value is (1) - TS over FCS\;Reserved when GPUNet" access="RW" offset="0x8.13" size="0x0.1" />
	<field name="rx_fcs_drop" descr="RX FCS drop control:\;0: ingress port will drop a packet with bad FCS (Default)\;1: ingress port will not drop a packet with bad FCS\;NOTE: All FCS counters (PPCNT) are valid for both drop modes.\;NOTE: Reserved when PCMR.fcs_cap=1 &amp; PCMR.fcs_chk=0" access="RW" offset="0x8.14" size="0x0.1" />
	<field name="tx_fcs_recalc" descr="TX FCS recalculation:\;0: egress port will recalculate and overwrite FCS value (Default) \;1: egress port will not overwrite FCS value \;NOTE: when this bit is set, any modification of the packet will result in a bad FCS.\;Reserved when GPUNet" access="RW" offset="0x8.15" size="0x0.1" />
	<field name="tx_ts_over_crc" descr="TX TimeStamp over FCS\;0: no TS over FCS\;1: TS over FCS\;Reserved when tx_fcs_recalc is set\;Reserved when GPUNet" access="RW" offset="0x8.16" size="0x0.1" />
	<field name="entropy_gre_calc" descr="0: DISABLE - entropy calculation is disabled for GRE tunneling protocol.\;1: ENABLE - entropy calculation is enabled for GRE tunneling protocol, if entropy_calc is enabled as well. valid only if force_entropy is activated.\;Reserved when GPUNet" access="RW" offset="0x8.29" size="0x0.1" />
	<field name="entropy_calc" descr="0: DISABLE - entropy calculation is disabled for all supported tunneling protocols.\;1: ENABLE - entropy calculation is enabled for all supported tunneling protocols. GRE also depends on the entropy_gre_calc valid only if force_entropy is activated.\;Reserved when GPUNet" access="RW" offset="0x8.30" size="0x0.1" />
	<field name="force_entropy" descr="0: DEFAULT - use device defaults for tunnel entropy calculation. This mode should be used if entropy calculation requirement is unknown.\;1: FORCE - force the entropy calculation according to entropy_calc and entropy_gre_calc.\;Reserved when GPUNet" access="RW" offset="0x8.31" size="0x0.1" />
</node>

<node name="pcnr_reg_ext" descr="" size="0xc.0" >
	<field name="tuning_override" descr="When set, port will override tuning process upon following link-up command (PAOS.admin_status = UP).\;Cleared by FW once PAOS.admin_status = UP command is set.\;\;The tuning_override is recommended to be set when port operational status is UP (PAOS.oper_status=0x1).\;If the field is set while operational status is DOWN (PAOS.oper_status=0x2), port will do best effort of fast linkup on the possible parts of the link (that is, known internal links that cannot change)." access="WO" offset="0x0.0" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="keep_phy_setting" descr="When Set, The port will keep the same phy setting upon link down event that occurs only upon link down command of peer port. In the event of Down command/cable disconnect, entire link up flow will be initialized.\;\;NOTE: This mode can be configured only when PTYS.an_disable_admin is set (i.e. AN is disabled). \;NOTE: if physical environment was changed (i.e. replacement of module, temp change, etc) there is a possibility that link won&apos;t be established or will be established with high BER" access="WO" offset="0x4.0" size="0x0.1" />
</node>

<node name="pddr_c2p_link_enabed_eth_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_eth_enabled" descr="Ethernet protocols admin state: see PTYS.ext_eth_proto_admin" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_c2p_link_enabed_ib_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_proto_enabled" descr="ib link enabled speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="core_to_phy_link_width_enabled" descr="ib link enabled width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_cable_cap_eth_ext" descr="" size="0x4.0" >
	<field name="cable_ext_eth_proto_cap" descr="Cable Ethernet protocols cap. If PTYS.ext_eth_proto_cap filed is supported, use for opcode definition PTYS.ext_eth_proto_capIf PTYS.ext_eth_proto_capability mask is empty, use For opcode definition PTYS.eth_proto_cap." access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_cable_cap_ib_ext" descr="" size="0x4.0" >
	<field name="cable_link_speed_cap" descr="Cable support IB speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="cable_link_width_cap" descr="Cable support IB width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_link_active_eth_ext" descr="" size="0x4.0" >
	<field name="link_eth_active" descr="Ethernet protocols active : see PTYS.ext_eth_proto_oper" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_link_active_ib_ext" descr="" size="0x4.0" >
	<field name="link_speed_active" descr="ib link active speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="link_width_active" descr="ib link active width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_link_down_info_page_ext" descr="" size="0xf4.0" >
	<field name="down_blame" descr="Which receiver caused last link down: \;0: Unknown\;1: Local_phy\;2: Remote_phy" access="RO" enum="Unknown=0x0,Local_phy=0x1,Remote_phy=0x2" offset="0x0.0" size="0x0.4" />
	<field name="local_reason_opcode" descr="Opcde of link down reason: \;0: No_link_down_indication\;1: Unknown_reason\;2: Hi_SER_or_Hi_BER\;3: Block_Lock_loss\;4: Alignment_loss\;5: FEC_sync_loss\;6: PLL_lock_loss\;7: FIFO_overflow\;8: false_SKIP_condition\;9: Minor_Error_threshold_exceeded\;10: Physical_layer_retransmission_timeout\;11: Heartbeat_errors\;12: Link_Layer_credit_monitoring_watchdog\;13: Link_Layer_integrity_threshold_exceeded\;14: Link_Layer_buffer_overrun\;15: Down_by_outband_command_with_healthy_link\;16: Down_by_outband_command_for_link_with_hi_ber\;17: Down_by_inband_command_with_healthy_link\;18: Down_by_inband_command_for_link_with_hi_ber\;19: Down_by_verification_GW\;20: Received_Remote_Fault \;21: Received_TS1\;22: Down_by_management_command\;23: Cable_was_unplugged\;24: Cable_access_issue \;25: Thermal_shutdown \;26: Current_issue \;27: Power_budget\;28: Fast_recovery_raw_ber\;29: Fast_recovery_effective_ber\;30: Fast_recovery_symbol_ber\;31: Fast_recovery_credit_watchdog\;32: Timeout" access="RO" enum="No_link_down_indication=0x0,Unknown_reason=0x1,Hi_SER_or_Hi_BER=0x2,Block_Lock_loss=0x3,Alignment_loss=0x4,FEC_sync_loss=0x5,PLL_lock_loss=0x6,FIFO_overflow=0x7,false_SKIP_condition=0x8,Minor_Error_threshold_exceeded=0x9,Physical_layer_retransmission_timeout=0xa,Heartbeat_errors=0xb,Link_Layer_credit_monitoring_watchdog=0xc,Link_Layer_integrity_threshold_exceeded=0xd,Link_Layer_buffer_overrun=0xe,Down_by_outband_command_with_healthy_link=0xf,Down_by_outband_command_for_link_with_hi_ber=0x10,Down_by_inband_command_with_healthy_link=0x11,Down_by_inband_command_for_link_with_hi_ber=0x12,Down_by_verification_GW=0x13,Received_Remote_Fault=0x14,Received_TS1=0x15,Down_by_management_command=0x16,Cable_was_unplugged=0x17,Cable_access_issue=0x18,Thermal_shutdown=0x19,Current_issue=0x1a,Power_budget=0x1b,Fast_recovery_raw_ber=0x1c,Fast_recovery_effective_ber=0x1d,Fast_recovery_symbol_ber=0x1e,Fast_recovery_credit_watchdog=0x1f,Timeout=0x20" offset="0x4.0" size="0x0.8" />
	<field name="remote_reason_opcode" descr="see local_reason_opcode" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="e2e_reason_opcode" descr="see local_reason_opcode for local reason opcode\;for remote reason opcode: local_reason_opcode+100" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="ts1_opcode" descr="TS1 opcode describes the reason the peer requested to ramp down the link:\;0x8: TS1.Sleep\;0x9: TS1.Disable\;0xA: TS1.PortLock\;0xB: TS1.Thermal\;0xC: TS1.Clean \;0xD  : TS1.Force\;0xE: TS1.reset_req\;\;Note: This field is valid in case the local_reason_opcode = 21:Received_TS1." access="RO" offset="0xC.12" size="0x0.4" />
	<field name="min_est_eff_ber_magnitude" descr="Minimal estimated effective BER window measured.\;\;Estimated_Effective_BER = min_est_eff_ber_coef*10^(-min_esteff_ber_magnitude)" access="RO" offset="0x30.0" size="0x0.8" />
	<field name="min_est_eff_ber_coef" descr="Minimal estimated effective BER window measured.\;\;Estimated_Effective_BER = min_est_eff_ber_coef*10^(-min_esteff_ber_magnitude)" access="RO" offset="0x30.8" size="0x0.4" />
	<field name="mean_est_eff_ber_magnitude" descr="Mean estimated effective BER window measured.\;\;Estimated_Effective_BER = mean_est_eff_ber_coef*10^(-mean_est_eff_ber_magnitude)" access="RO" offset="0x30.16" size="0x0.8" />
	<field name="mean_est_eff_ber_coef" descr="Mean estimated effective BER window measured.\;\;Estimated_Effective_BER = mean_est_eff_ber_coef*10^(-mean_est_eff_ber_magnitude)" access="RO" offset="0x30.24" size="0x0.4" />
	<field name="max_est_eff_ber_magnitude" descr="Maximal estimated effective BER window measured.\;\;Estimated_Effective_BER = max_est_eff_ber_coef*10^(-max_est_eff_ber_magnitude)" access="RO" offset="0x34.0" size="0x0.8" />
	<field name="max_est_eff_ber_coef" descr="Maximal estimated effective BER window measured.\;\;Estimated_Effective_BER = max_est_eff_ber_coef*10^(-max_est_eff_ber_magnitude)" access="RO" offset="0x34.8" size="0x0.4" />
	<field name="num_of_est_eff_ber_alarms" descr="Number of Estimated Effective BER Windows that crossed alarm threshold" access="RO" offset="0x38.0" size="0x0.16" />
	<field name="num_of_est_eff_ber_warnings" descr="Number of Estimated Effective BER Windows that crossed warning threshold\;" access="RO" offset="0x38.16" size="0x0.16" />
</node>

<node name="pddr_module_info_ext" descr="" size="0xd8.0" >
	<field name="ethernet_compliance_code" descr="QSFP:\;Ethernet Compliance Codes bit mask (10/40G/100G)\;Byte131 per SFF-8636 \;Bit 7 - Extended Specification Compliance valid\;Bit 6 - 10GBASE-LRM\;Bit 5 - 10GBASE-LR\;Bit 4 - 10GBASE-SR\;Bit 3 - 40GBASE-CR4\;Bit 2 - 40GBASE-SR4\;Bit 1 - 40GBASE-LR4\;Bit 0 - 40G Active Cable (XLPPI)\;\;SFP : \;10G Ethernet Compliance Codes\;Byte3 per SFF-8472:\;Bit 7 - 10G Base-ER \;Bit 6 - 10G Base-LRM \;Bit 5 - 10G Base-LR \;Bit 4 - 10G Base-SR\;\;CMIS based (QSFP-DD/ SFP-DD / OSFP)\;Byte 87 - Module Media Interface" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="ext_ethernet_compliance_code" descr="Extended Specification Compliance Codes \;for SFP:\;byte 36 per SFF-8472\;\;for QSFP:\;byte192 per SFF-8636 (QSFP28) \;\;for CMIS (SFP-DD / QSFP-DD/ OSFP):\;Byte 86 - Host Electrical Interface" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="cable_breakout" descr="Reserved for SFP. \;\;For QSFP:\;Byte113 per SFF-8636\;\;For CMIS based modules:\;\;XX naming is according to cable_identifier name\;For example: if cable_identifier = ,6 XX string is QSFP-DD\;\;0 - Unspecified\;1 - XX to XX\;2 - XX to 2xQSFP or 2xXX (depopulated / 4 lanes)\;3 - XX to 4xDSFP or 4xQSFP (depopulated / 2 lanes)\;4 - XX to 8xSFP\;5 - XX (depopulated / 4 lanes) to QSFP or XX (depopulated / 4 lanes)\;6 - XX (depopulated / 4 lanes) to 2xXX(depopulated / 2 lanes) or 2xSFP-DD\;7 - XX (depopulated / 4 lanes) to 4xSFP\;8 - XX(/ 2 lane module) to XX\;9 - XX(/ 2 lane module) to 2xSFP" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="cable_technology" descr="QSFP: \;Byte 147 per SFF-8636.\;\;SFP:\;SFP+ Cable Technology: \;byte8 per SFF-8472:\;Bit 3 - Active Cable\;Bit 2 - Passive Cable\;\;CMIS based (QSFP-DD / OSFP/ SFP-DD):\;Byte 212" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="cable_power_class" descr="Module maximum power consumption for SFP/QSFP:\;0: Power_Class_0 - (1.0 W max)\;1: Power_Class_1 - (1.5 W max)\;2: Power_Class_2 - (2.0 W max)\;3: Power_Class_3 - (2.5 W max)\;4: Power_Class_4 - (3.5 W max)\;5: Power_Class_5 - (4.0 W max)\;6: Power_Class_6 - (4.5 W max)\;7: Power_Class_7 - (5.0 W max)\;8: Power_Class_8 - (power from max_power field)\;\;Module maximum power consumption for SFP-DD:\;0: Power_Class_0 - (0.5 W max)\;1: Power_Class_1 - (1.0 W max)\;2: Power_Class_2 - (1.5 W max)\;3: Power_Class_3 - (2.0 W max)\;4: Power_Class_4 - (3.5 W max)\;5: Power_Class_5 - (5.0 W max)\;6: reserved\;7: reserved\;8: Power_Class_8 - (power from max_power field)\;\;Module maximum power consumption for QSFP-DD/OSFP:\;1 - Power_Class_1 - (1.5 W max)\;2 - Power_Class_2 - (3.5 W max)\;3 - Power_Class_3 - (7.0 W max)\;4 - Power_Class_4 - (8.0 W max)\;5 - Power_Class_5 - (10 W max)\;6 - Power_Class_6 - (12 W max)\;7 - Power_Class_7 - (14 W max)\;8 - Power_Class_8 - (power from max_power field)" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="cable_identifier" descr="0: QSFP28\;1: QSFP_Plus\;2: SFP28_or_SFP_Plus\;3: QSA - (QSFP-&gt;SFP)\;4: Backplane\;5: SFP_DD\;6: QSFP_DD\;7: QSFP_CMIS\;8: OSFP\;9: C2C\;10: DSFP\;11: QSFP_Split_Cable\;\;identifiers that are CMIS compliant are: 5,6,7,8,10" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="cable_length" descr="Cable length in 1m units.\;\;For CMIS modules:\;bits 6:7 represent cable_length_multiplier for calculating cable length\;00 - 0.1 multiplier (0.1 to 6.3m)\;01- 1 multiplier (1 to 63m)\;10 - 10 multiplier (10 to 630m)\;11 - 100 multiplier (100 to 6300m)\;\;bits 0:5 represent cable_length_value for calculating cable length.\;length is calculated with cable_length_value * cable_length_multiplier" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="cable_vendor" descr="Cable vendor:\;0: Other\;1: Mellanox\;2: Known_OUI\;3: NVIDIA\;" access="RO" enum="Other=0x0,Mellanox=0x1,Known_OUI=0x2,NVIDIA=0x3" offset="0x4.24" size="0x0.4" />
	<field name="cable_type" descr="Cable/module type:\;0: Unidentified\;1: Active_cable - (active copper / optics)\;2: Optical_Module - (separated)\;3: Passive_copper_cable\;4: Cable_unplugged\;5: Twisted_pair\;" access="RO" enum="Unidentified=0x0,Active_cable=0x1,Optical_Module=0x2,Passive_copper_cable=0x3,Cable_unplugged=0x4,Twisted_pair=0x5" offset="0x4.28" size="0x0.4" />
	<field name="cable_tx_equalization" descr="\;" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="cable_rx_emphasis" descr="\;For CMIS (QSFP-DD/ SFP-DD/ OSFP) field will represent Rx pre-emphasis." access="RO" offset="0x8.8" size="0x0.8" />
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
	<field name="rx_output_valid_cap" descr="when set, indicates rx_output_valid is supported by the module" access="RW" offset="0x94.26" size="0x0.1" />
	<field name="did_cap" descr="set in case of Linear Direct Drive module" access="RO" offset="0x94.27" size="0x0.1" />
	<field name="rx_power_type" descr="rx power measurement type\;0: OMA\;1: Average_power" access="RO" enum="OMA=0x0,Average_power=0x1" offset="0x94.28" size="0x0.1" />
	<field name="module_st" descr="Valid for CMIS modules only.\;Module state:\;0: reserved\;1: LowPwr_state\;2: PwrUp_state\;3: Ready_state\;4: PwrDn_state\;5: Fault_state" access="RO" enum="reserved=0x0,LowPwr_state=0x1,PwrUp_state=0x2,Ready_state=0x3,PwrDn_state=0x4,Fault_state=0x5" offset="0x94.29" size="0x0.3" />
	<field name="ib_compliance_code" descr="Byte 164 of SFF-8636\;For CMIS modules IB Protocols." access="RO" offset="0x98.0" size="0x0.8" />
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
	<field name="error_code" descr="Relevant for CMIS modules only\;Error Code response for ConrolSet configuration of DataPath.\;0x0: ConfigUndefined\;0x1: ConfigSuccess\;0x2: ConfigRejected\;0x3: ConfigRejectedInvalidAppSel\;0x4: ConfigRejectedInvalidDataPath\;0x5: ConfigRejectedInvalidSI\;0x6: ConfigRejectedLanesInUse\;0x7: ConfigRejectedPartialDataPath\;0xC: ConfigInProgress" access="RO" enum="ConfigUndefined=0x0,ConfigSuccess=0x1,ConfigRejected=0x2,ConfigRejectedInvalidAppSel=0x3,ConfigRejectedInvalidDataPath=0x4,ConfigRejectedInvalidSI=0x5,ConfigRejectedLanesInUse=0x6,ConfigRejectedPartialDataPath=0x7,ConfigInProgress=0xc" offset="0xC0.0" size="0x0.4" />
	<field name="max_fiber_length" descr="Maximum length of allowed fiber in meters" access="RO" offset="0xC0.16" size="0x0.16" />
</node>

<node name="pddr_monitor_opcode_ext" descr="" size="0x4.0" >
	<field name="monitor_opcode" descr="Status opcode: \;\;PHY FW indication (0 - 1023):\;0 - No issue observed\;1 - Port is close by command (see PAOS).\;2,3,4,38,39 - AN failure \;5,6,7,8 - Link training failure. \;9,10,11,12,13 - Logical mismatch between link partners\;14 - Remote fault received\;15,42,17,48,49,52, - Bad signal integrity \;16,24-32 - Cable compliance code mismatch (protocol mismatch between cable and port) \;23,22,19,18,50,55- Internal error\;34,35 - Speed degradation\;56 - module_lanes_frequency_not_synced\;57 - signal not detected\;60 - no partner detected for long time\;128 - Troubleshooting in process\;1023- Info not available\;\;MNG FW issues (1024 - 2047):\;1024 - Cable is unplugged\;1025 - Long Range for non Mellanox cable/module .\;1026 - Bus stuck (I2C Data or clock shorted) \;1027 - Bad/unsupported EEPROM \;1028 - Part number list\;1029 - Unsupported cable.\;1030 - Module temperature shutdown\;1031 - Shorted cable\;1032 - Power budget exceeded\;1033 - Management forced down the port\;1034 - Module is disabled by command\;1035 - System Power is Exceeded therefore the module is powered off.\;1036 - Module&apos;s PMD type is not enabled (see PMTPS).\;1040 - pcie system power slot Exceeded\;1042 - Module state machine fault\;1043,1044,1045,1046 - Module&apos;s stamping speed degeneration\;1047, 1048 - Modules DataPath FSM fault\;1050, 1051, 1052, 1053- Module Boot Error\;1054 - Module Forced to Low Power by command\;Core/Driver (2048 - 3071):" access="RW" offset="0x0.0" size="0x0.16" />
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
	<field name="neg_mode_active" descr="0: protocol_was_not_negotiated - (force mode)\;1: MLPN_rev0_negotiated\;2: CL73_Ethernet_negotiated\;3: Protocol_according_to_Parallel_detect - (remote port in force mode)\;4: Standard_IB_negotiated \;\;8: NLPN_rev2_negotiated\;9: HS_NLPN_rev2_negotiated_" access="RO" enum="protocol_was_not_negotiated=0x0,MLPN_rev0_negotiated=0x1,CL73_Ethernet_negotiated=0x2,Protocol_according_to_Parallel_detect=0x3,Standard_IB_negotiated=0x4,NLPN_rev2_negotiated=0x8,HS_NLPN_rev2_negotiated_=0x9" offset="0x0.16" size="0x0.4" />
	<field name="proto_active" descr="Active protocol:\;Bit 0: InfiniBand\;Bit 2: Ethernet" access="RO" enum="InfiniBand=0x1,Ethernet=0x4" offset="0x0.20" size="0x0.4" />
	<field name="ib_phy_fsm_state" descr="FW IB state machine:\;0x0: IB_AN_FSM_DISABLED\;0x1: IB_AN_FSM_INITIALY\;0x2: IB_AN_FSM_RCVR_CFG\;0x3: IB_AN_FSM_CFG_TEST\;0x4: IB_AN_FSM_WAIT_RMT_TEST\;0x5: IB_AN_FSM_WAIT_CFG_ENHANCED\;0x6: IB_AN_FSM_CFG_IDLE\;0x7: IB_AN_FSM_LINK_UP\;0x8: IB_AN_FSM_POLLING" access="RO" enum="IB_AN_FSM_DISABLED=0x0,IB_AN_FSM_INITIALY=0x1,IB_AN_FSM_RCVR_CFG=0x2,IB_AN_FSM_CFG_TEST=0x3,IB_AN_FSM_WAIT_RMT_TEST=0x4,IB_AN_FSM_WAIT_CFG_ENHANCED=0x5,IB_AN_FSM_CFG_IDLE=0x6,IB_AN_FSM_LINK_UP=0x7,IB_AN_FSM_POLLING=0x8" offset="0x4.8" size="0x0.8" />
	<field name="eth_an_fsm_state" descr="Ethernet (CL73) Auto-negotiation FSM state:\;0x0: ETH_AN_FSM_ENABLE\;0x1: ETH_AN_FSM_XMIT_DISABLE\;0x2: ETH_AN_FSM_ABILITY_DETECT\;0x3: ETH_AN_FSM_ACK_DETECT\;0x4: ETH_AN_FSM_COMPLETE_ACK\;0x5: ETH_AN_FSM_AN_GOOD_CHECK\;0x6: ETH_AN_FSM_AN_GOOD\;0x7: ETH_AN_FSM_NEXT_PAGE_WAIT" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="phy_mngr_fsm_state" descr="FW Phy Manager FSM state:\;0: Disabled \;1: Open_port\;2: Polling\;3: Active\;4: Close_port\;5: Phy_up\;6: Sleep\;7: Rx_disable\;8: Signal_detect\;9: Receiver_detect\;10: Sync_peer\;11: Negotiation\;12: Training\;13: SubFSM_active" access="RO" enum="Disabled=0x0,Open_port=0x1,Polling=0x2,Active=0x3,Close_port=0x4,Phy_up=0x5,Sleep=0x6,Rx_disable=0x7,Signal_detect=0x8,Receiver_detect=0x9,Sync_peer=0xa,Negotiation=0xb,Training=0xc,SubFSM_active=0xd" offset="0x4.24" size="0x0.8" />
	<field name="phy_manager_link_enabled" descr="For IB: Table 1798, &quot;PDDR - Phy manager link enabled IB layout,&quot; on page 2098\;For Ethernet: Table 1800, &quot;PDDR - Phy manager link enabled Eth layout,&quot; on page 2098\;" subnode="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="core_to_phy_link_enabled" descr="For IB: Table 1802, &quot;PDDR - core2phy link enabled IB layout,&quot; on page 2099\;For Ethernet: Table 1804, &quot;PDDR - Core2Phy link enabled Eth layout,&quot; on page 2100" subnode="pddr_operation_info_page_core_to_phy_link_enabled_auto_ext" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="cable_proto_cap" descr="For IB: Table 1806, &quot;PDDR - cable cap IB layout,&quot; on page 2101\;For Ethernet: Table 1808, &quot;PDDR - cable cap Eth layout,&quot; on page 2102\;" subnode="pddr_operation_info_page_cable_proto_cap_auto_ext" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="link_active" descr="For IB: Table 1810, &quot;PDDR - Link Active IB layout,&quot; on page 2103\;For Ethernet: Table 1812, &quot;PDDR - Link Active Eth layout,&quot; on page 2103" subnode="pddr_operation_info_page_link_active_auto_ext" access="RO" offset="0x14.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="loopback_mode" descr="0: No_loopback_active\;1: Phy_remote_loopback \;2: Phy_local_loopback -When set the port&apos;s egress traffic is looped back to the receiver and the port transmitter is disabled. \;4: External_local_loopback -Enables the port&apos;s transmitter to link with the port&apos;s receiver using an external loopback connector." access="RO" enum="No_loopback_active=0x0,Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4" offset="0x18.0" size="0x0.12" />
	<field name="fec_mode_request" descr="FEC mode request\;See fec_mode_active\;for supported retransmission mode see PPLM.fec_mode_capability" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="fec_mode_active" descr="FEC mode active\;0: No_FEC\;1: Firecode_FEC\;2: Standard_RS_FEC - RS(528,514)\;3: Standard_LL_RS_FEC - RS(271,257)\;6: Interleaved_Standard_RS-FEC - (544,514)\;7: Standard_RS-FEC - (544,514)\;9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - (272,257+1)\;For supported retransmission mode see PPLM.fec_mode_capability" access="RO" enum="No_FEC=0x0,Firecode_FEC=0x1,Standard_RS_FEC=0x2,Standard_LL_RS_FEC=0x3,Interleaved_Standard_RS=0x6,Standard_RS=0x7,Ethernet_Consortium_LL_50G_RS_FEC=0x9,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC=0xa" offset="0x1C.16" size="0x0.16" />
	<field name="eth_100g_fec_support" descr="FEC 100G (25Gb/s per lane) supported FEC include override masking , should reflect current phy configuration after link is up\;\;Bit 0 - No FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="eth_25g_50g_fec_support" descr="FEC 25G/50G (25Gb/s per lane) supported FEC include override masking , should reflect current phy configuration after link is up\;Bit 0 - No FEC\;Bit 1 - Firecode FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;" access="RO" offset="0x20.4" size="0x0.4" />
	<field name="eth_an_link_enabled" descr="For IB: Table 1822, &quot;PDDR - ETH AN Link Enabled Eth Layout,&quot; on page 2106" access="RO" offset="0x2C.0" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_link_active_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_link_active_ib_ext" descr="" subnode="pddr_link_active_ib_ext" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="pddr_link_active_eth_ext" descr="" subnode="pddr_link_active_eth_ext" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_phy_manager_link_enabed_ib_ext" descr="" subnode="pddr_phy_manager_link_enabed_ib_ext" offset="0x0.0" size="0x4.0" />
	<field name="pddr_phy_manager_link_enabed_eth_ext" descr="" subnode="pddr_phy_manager_link_enabed_eth_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_phy_info_page_ext" descr="" size="0xf8.0" >
	<field name="port_notifications" descr="Port notifications bit mask\;Bit 0 - Link partner advertised capabilities \;Bit 1 - Speed degradation" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="negotiation_mask" descr="Bit 0: eth_base_page\;Bit 1: ib_base_page\;Bit 2: ib_base_page_rev2 - XDR onwards\;Bit 3: Consurtium\;Bit 4: MLPN_rev0\;Bit 5: MLPN_rev1\;Bit 6: NLPN_rev2" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="remote_device_type" descr="Remote device type: \;0 - Unknown (3rd party , Force , legacy MLPN)  \;1 - CX4\;2 - CX4_LX\;3 - CX5\;4 - CX5_LX\;5 - CX6\;6 - CX6_LX\;7 - CX6_DX\;8 - CX7\;9 - Bluefield-2\;10 - CX8\;11 - Bluefield-3\;12-99 Reserved\;\;100 - SwitchIB\;101 - Spectrum \;102 - SwitchIB-2\;103 - Quantum\;104 - Spectrum-2\;105 - Spectrum-3\;106 - Quantum-2\;107 - Spectrum-4\;108 -Quantum-3\;109-199 -Reserved\;\;200 - GBxxx (GB100/102/200)\;201-255 - reserved" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="lp_ib_revision" descr="Link partner IB TS revision \;\;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="ib_revision" descr="IB TS revision \;" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="num_of_negotiation_attempts" descr="Negotiation attempt counter" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="phy_manager_disable_mask" descr="Phy manager disable bit mask: \;Bit 0 - Module not present (module absence/cage power off)\;Bit 1 - PAOS command\;Bit 2 - MAD IB PortInfo down command\;Bit 3 - Long range cable (Non Mellanox) \;Bit 4 - Verification command\;Bit 5 - ekey command\;Bit 6 - High power - cable require higher power than allowed.\;Bit 7 - Unknown Identifier (Module)\;Bit 8 - PAOS up once \;Bit 9 - Stamping failure\;Bit 10 - Calibration not done" access="RO" offset="0x8.0" size="0x0.24" />
	<field name="hw_link_phy_state" descr="IBP HW FSM Reflected State:\;0x10: sleeping_delay\;0x11: sleeping_quiet\;0x20: polling_active\;0x21: polling_quiet\;0x30: disable\;0x40: config_debounce\;0x41: config_receiver\;0x42: config_wait_remote\;0x43: config_tx_reverse_lanes\;0x44: config_enhanced    \;0x45: config_test\;0x46: confg_wait_remote_test\;0x47: config_wait_cfg_enhanced\;0x48: config_idle\;0x50: linkup\;0x51: Linkup_Tx_Idle\;0x52: Linkup_Tx_Empty\;0x60: recover_retrain\;0x61: recover_wait_remote\;0x62: recover_idle\;0x70: test\;- Force Modes\;0x80: Force_send_ts1 - command may be given only on disable state\;0x90: Force_send_ts2\;0xA0: Force_Sent_Idle\;0xB0: Force_send_ts_Mlnx\;0xC0: Force_send_ts3\;0xD0: Force_LinkUp\;- L1\;0xE0: Go_To_Quiet\;0xE1: Retimer_Align\;0xE2: Quiet_Entry\;0xE3: Quiet\;0xE4: Wake\;0xE5: Wake_Tx_Sleep0\;0xE6: Send_Announce\;0xE7: Tx_HS\;0xE8: Wait_For_Cdr_Lock" access="RO" enum="sleeping_delay=0x10,sleeping_quiet=0x11,polling_active=0x20,polling_quiet=0x21,disable=0x30,config_debounce=0x40,config_receiver=0x41,config_wait_remote=0x42,config_tx_reverse_lanes=0x43,config_enhanced=0x44,config_test=0x45,confg_wait_remote_test=0x46,config_wait_cfg_enhanced=0x47,config_idle=0x48,linkup=0x50,Linkup_Tx_Idle=0x51,Linkup_Tx_Empty=0x52,recover_retrain=0x60,recover_wait_remote=0x61,recover_idle=0x62,test=0x70,Force_send_ts1=0x80,Force_send_ts2=0x90,Force_Sent_Idle=0xa0,Force_send_ts_Mlnx=0xb0,Force_send_ts3=0xc0,Force_LinkUp=0xd0,Go_To_Quiet=0xe0,Retimer_Align=0xe1,Quiet_Entry=0xe2,Quiet=0xe3,Wake=0xe4,Wake_Tx_Sleep0=0xe5,Send_Announce=0xe6,Tx_HS=0xe7,Wait_For_Cdr_Lock=0xe8" offset="0x8.24" size="0x0.8" />
	<field name="pcs_phy_state" descr="PCS HW state:\;Bits 0-7: Block lock\;Bits 8-15: AM lock\;Bits 16-23: FEC lock\;Bits 24: Align_status\;Bits 25: Hi_BER\;Bits 26: Hi_SER" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="lp_proto_enabled" descr="IB ports : \;Link partner advertised speeds (first TS3)\;See ib_link_speed_enabled encoding.\;\;Ethernet ports:\;Link partner advertised Ethernet protocols active state: see PTYS.lp_advertise" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="lp_fec_mode_request" descr="Reserved when negotiation wasn&apos;t performed according to port_notifications.Link partner advertised capabilities value.\;Advertised link partner FEC mode request" access="RO" offset="0x14.0" size="0x0.16" />
	<field name="lp_fec_mode_support" descr="Reserved when negotiation wasn&apos;t performed according to port_notifications.Link partner advertised capabilities value.\;\;Advertised link partner FEC mode support\;Bit 0 - No FEC\;Bit 1 - Firecode FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;Bit 3 - Standard LL RS-FEC - RS(271,257)\;Bit 4 - Mellanox Strong RS-FEC - RS(277,257)\;Bit 5 - Mellanox LL RS-FEC - RS(163,155)\;Bit 7 - Standard RS-FEC (544,514)\;for supported retransmission mode see PPLM.fec_mode_capability" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="ib_last_link_down_reason" descr="Bit 0 - heartbeat_ack_received\;Bit 1 - heartbeat_send_received\;Bit 2 - heartbeat_err\;Bit 3 - tx_width_reduction_done_1x\;Bit 4 - tx_width_reduction_done_full\;Bit 5 - rx_width_reduction_done_1x\;Bit 6 - rx_width_reduction_done_full\;Bit 7 - width_reduction_timeout\;Bit 8 - ibl_link_retrain\;Bit 9 - rx_comskp_timeout\;Bit 10 - fifo_full_err\;Bit 11 - ts_at_linkup\;Bit 12 - minor_threshold_reached\;Bit 13 - link_fail\;Bit 14 - rx_eb_full_r\;Bit 15 - rx_8_10_lane_err\;Bit 16 - llr_link_retrain_set\;Bit 17 - fc_timeout\;Bit 18 - phy_error\;Bit 19 - lli_err\;Bit 20 - excessive_buffer_err\;Bit 21 - remote_init\;Bit 22 - plr_retry_expired\;Bit 23 - port_didnt_exit_plr_sync\;Bit 24 - eq_failed\;Bits 31-24 - Reserved" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="eth_last_link_down_lane" descr="Bit 0 - block_lock_failed\;Bit 1 - skip_detected\;Bit 2 - fec_sync_failed\;Bit 3 - fec_block_sync\;Bit 4 - fec_block_sync_lost" access="RO" high_bound="3" low_bound="0" offset="0x1C.24" size="0x4.0" />
	<field name="speed_deg_db" descr="Bit 0 - Speed degradation database Valid\;Bit 1 - Speed degradation Serdes Rx database valid\;BIts 3-2 - reserved\;Bit 4 - rx_reversal\;Bit 5 - tx_reversal\;Bit 7-6 - reserved\;Bits 11:8 - failed_qdr/fdr10 - bit per lane.\;Bits 15:12 - failed_fdr - bit per lane.\;Bits 19:16- failed_edr - bit per lane.\;Bits 24:20 - peer_failed_test\;Bits 26-25 - reserved\;Bit 27 - first_test_speed" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="degrade_grade_lane0" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x28.0" size="0x0.24" />
	<field name="degrade_grade_lane1" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x2C.0" size="0x0.24" />
	<field name="degrade_grade_lane2" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x30.0" size="0x0.24" />
	<field name="degrade_grade_lane3" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x34.0" size="0x0.24" />
	<field name="num_of_presets_tested_lane7" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x38.0" size="0x0.5" />
	<field name="num_of_presets_tested_lane6" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x38.8" size="0x0.5" />
	<field name="num_of_presets_tested_lane5" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x38.16" size="0x0.5" />
	<field name="num_of_presets_tested_lane4" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x38.24" size="0x0.5" />
	<field name="kr_startup_debug_indications_5" descr="kr_stratup_debug_indication_&lt;i&gt; bit mask:\;Bit 0 - Local_frame_lock\;Bit 1 - Remote_frame_lock\;Bit 2 - Local_Frame_lock_timer_expired\;Bit 3 - Remote_Frame_lock_timer_expired \;Bit 4 - Local_receiver_ready\;Bit 5 - Remote_receiver_ready\;Bit 6 - max_wait_timer_expired \;Bit 7 - Wait_timer_done\;Bit 8 - Hold_off_timer_expired\;Bit 9 - link_fail_inhibit_timer _expired" access="RO" offset="0x3C.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_4" descr="kr_stratup_debug_indication_&lt;i&gt; bit mask:\;Bit 0 - Local_frame_lock\;Bit 1 - Remote_frame_lock\;Bit 2 - Local_Frame_lock_timer_expired\;Bit 3 - Remote_Frame_lock_timer_expired \;Bit 4 - Local_receiver_ready\;Bit 5 - Remote_receiver_ready\;Bit 6 - max_wait_timer_expired \;Bit 7 - Wait_timer_done\;Bit 8 - Hold_off_timer_expired\;Bit 9 - link_fail_inhibit_timer _expired" access="RO" offset="0x3C.16" size="0x0.16" />
	<field name="kr_startup_debug_indications_7" descr="kr_stratup_debug_indication_&lt;i&gt; bit mask:\;Bit 0 - Local_frame_lock\;Bit 1 - Remote_frame_lock\;Bit 2 - Local_Frame_lock_timer_expired\;Bit 3 - Remote_Frame_lock_timer_expired \;Bit 4 - Local_receiver_ready\;Bit 5 - Remote_receiver_ready\;Bit 6 - max_wait_timer_expired \;Bit 7 - Wait_timer_done\;Bit 8 - Hold_off_timer_expired\;Bit 9 - link_fail_inhibit_timer _expired" access="RO" offset="0x40.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_6" descr="kr_stratup_debug_indication_&lt;i&gt; bit mask:\;Bit 0 - Local_frame_lock\;Bit 1 - Remote_frame_lock\;Bit 2 - Local_Frame_lock_timer_expired\;Bit 3 - Remote_Frame_lock_timer_expired \;Bit 4 - Local_receiver_ready\;Bit 5 - Remote_receiver_ready\;Bit 6 - max_wait_timer_expired \;Bit 7 - Wait_timer_done\;Bit 8 - Hold_off_timer_expired\;Bit 9 - link_fail_inhibit_timer _expired" access="RO" offset="0x40.16" size="0x0.16" />
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
	<field name="kr_startup_debug_indications_1" descr="kr_stratup_debug_indication_&lt;i&gt; bit mask:\;Bit 0 - Local_frame_lock\;Bit 1 - Remote_frame_lock\;Bit 2 - Local_Frame_lock_timer_expired\;Bit 3 - Remote_Frame_lock_timer_expired \;Bit 4 - Local_receiver_ready\;Bit 5 - Remote_receiver_ready\;Bit 6 - max_wait_timer_expired \;Bit 7 - Wait_timer_done\;Bit 8 - Hold_off_timer_expired\;Bit 9 - link_fail_inhibit_timer _expired" access="RO" offset="0x58.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_0" descr="kr_stratup_debug_indication_&lt;i&gt; bit mask:\;Bit 0 - Local_frame_lock\;Bit 1 - Remote_frame_lock\;Bit 2 - Local_Frame_lock_timer_expired\;Bit 3 - Remote_Frame_lock_timer_expired \;Bit 4 - Local_receiver_ready\;Bit 5 - Remote_receiver_ready\;Bit 6 - max_wait_timer_expired \;Bit 7 - Wait_timer_done\;Bit 8 - Hold_off_timer_expired\;Bit 9 - link_fail_inhibit_timer _expired" access="RO" offset="0x58.16" size="0x0.16" />
	<field name="kr_startup_debug_indications_3" descr="kr_stratup_debug_indication_&lt;i&gt; bit mask:\;Bit 0 - Local_frame_lock\;Bit 1 - Remote_frame_lock\;Bit 2 - Local_Frame_lock_timer_expired\;Bit 3 - Remote_Frame_lock_timer_expired \;Bit 4 - Local_receiver_ready\;Bit 5 - Remote_receiver_ready\;Bit 6 - max_wait_timer_expired \;Bit 7 - Wait_timer_done\;Bit 8 - Hold_off_timer_expired\;Bit 9 - link_fail_inhibit_timer _expired" access="RO" offset="0x5C.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_2" descr="kr_stratup_debug_indication_&lt;i&gt; bit mask:\;Bit 0 - Local_frame_lock\;Bit 1 - Remote_frame_lock\;Bit 2 - Local_Frame_lock_timer_expired\;Bit 3 - Remote_Frame_lock_timer_expired \;Bit 4 - Local_receiver_ready\;Bit 5 - Remote_receiver_ready\;Bit 6 - max_wait_timer_expired \;Bit 7 - Wait_timer_done\;Bit 8 - Hold_off_timer_expired\;Bit 9 - link_fail_inhibit_timer _expired" access="RO" offset="0x5C.16" size="0x0.16" />
	<field name="tx_tuning_stages_lane" descr="Stages mask per lane:\;Bit 0 - Single preset stage\;Bit 1 - multiple preset stage\;Bit 2 - LMS" access="RO" high_bound="7" low_bound="0" offset="0x60.28" size="0x4.0" />
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
	<field name="stamping_reason" descr="Bit 0 - com_codes_is_zero \;Bit 1- rx_cdr_check_force_mode \;Bit 2- com_code_complaince \;Bit 3- eth_56g_stamped\;Bit 4- non_mlx_qsfp_tranciver\;Bit 5- non_mlx_sfp_tranciver\;Bit 6-ib_comp_codes\;Bit 7-edr_comp\;Bit 8-fdr_comp" access="RO" offset="0x6C.0" size="0x4.0" />
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
	<field name="phy2mod_speed_req" descr="phy 2 module requested speed, aka speed_apsel_value\;bitmask according to PTYS.ext_ethernet_protocl for ETH speeds\;or ib_ext_protocols for IB speeds" access="RO" offset="0x8C.0" size="0x4.0" />
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
	<field name="plr_rtt_ndr_threshold" descr="rtt threshold in 1 ns units for NDR speeds\;" access="RO" offset="0x98.0" size="0x0.16" />
	<field name="plr_rtt_hdr_threshold" descr="rtt threshold in 1 ns units for HDR speeds" access="RO" offset="0x98.16" size="0x0.16" />
	<field name="plr_rtt_xdr_threshold" descr="rtt threshold in 1 ns units for XDR speeds\;" access="RO" offset="0x9C.16" size="0x0.16" />
</node>

<node name="pddr_phy_manager_link_enabed_eth_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_eth_enabled" descr="Ethernet protocols admin state: see PTYS.ext_eth_proto_admin" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_phy_manager_link_enabed_ib_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_proto_enabled" descr="ib link enabled speed:\;Bit 0 - SDR\;Bit 1 - DDR\;Bit 2 - QDR\;Bit 3 - FDR10\;Bit 4 - FDR\;Bit 5 - EDR\;Bit 6 - HDR\;Bit 7 - NDR\;Bit 8 - XDR" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="phy_manager_link_width_enabled" descr="ib link enabled width:\;Bit 0 - 1x\;Bit 1 - 2x\;Bit 2 - 4x\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_reg_ext" descr="" size="0x100.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM \;0: Network_port\;1: Near_End_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: Far_End_Port - (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" enum="Network_port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;1: IB_port_number\;" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="page_select" descr="page select index:\;0: Operational_info_page\;1: Troubleshooting_info_page\;2: Phy_info_page\;3: Module_info_page\;6: link_down_info\;9: Module_latched_flag_info_page" access="INDEX" enum="Operational_info_page=0x0,Troubleshooting_info_page=0x1,Phy_info_page=0x2,Module_info_page=0x3,link_down_info=0x6,Module_latched_flag_info_page=0x9" offset="0x4.0" size="0x0.8" />
	<field name="module_info_ext" descr="Module info extended configurations.\;resolution for rx_power, rx_power_high_th, rx_power_low_th tx_power, tx_power_high_th, tx_power_low_th in module info page\;0: dbm\;1: uW" access="OP" enum="dbm=0x0,uW=0x1" offset="0x4.29" size="0x0.2" />
	<field name="page_data" descr="Table 1796, &quot;Operation Info Page Layout,&quot; on page 2089\;Table 1832, &quot;Troubleshooting info Page layout,&quot; on page 2141\;Table 1824, &quot;Phy Info Page Layout,&quot; on page 2107\;Table 1830, &quot;Module Info Page Layout,&quot; on page 2128\;Table 1826, &quot;Link Down Info Page layout,&quot; on page 2122\;Table 1844, &quot;Module Latched Flag Info Page Layout,&quot; on page 2159\;" subnode="pddr_reg_page_data_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).page_select" />
</node>

<node name="pddr_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="pddr_operation_info_page_ext" descr="" subnode="pddr_operation_info_page_ext" offset="0x0.0" selected_by="Operational_info_page" size="0xf8.0" />
	<field name="pddr_troubleshooting_page_ext" descr="" subnode="pddr_troubleshooting_page_ext" offset="0x0.0" selected_by="Troubleshooting_info_page" size="0xf8.0" />
	<field name="pddr_phy_info_page_ext" descr="" subnode="pddr_phy_info_page_ext" offset="0x0.0" selected_by="Phy_info_page" size="0xf8.0" />
	<field name="pddr_module_info_ext" descr="" subnode="pddr_module_info_ext" offset="0x0.0" selected_by="Module_info_page" size="0xd8.0" />
	<field name="pddr_link_down_info_page_ext" descr="" subnode="pddr_link_down_info_page_ext" offset="0x0.0" selected_by="link_down_info" size="0xf4.0" />
	<field name="module_latched_flag_info_ext" descr="" subnode="module_latched_flag_info_ext" offset="0x0.0" selected_by="Module_latched_flag_info_page" size="0xf8.0" />
</node>

<node name="pddr_troubleshooting_page_ext" descr="" size="0xf8.0" >
	<field name="group_opcode" descr="0: Monitor_opcodes" access="INDEX" enum="Monitor_opcodes=0x0" offset="0x0.0" size="0x0.16" />
	<field name="status_opcode" descr="Status opcode described in:\;Table 1834, &quot;PDDR - Monitor opcodes layout,&quot; on page 2142" subnode="pddr_troubleshooting_page_status_opcode_auto_ext" access="RO" offset="0x4.0" size="0x4.0" union_selector="$(parent).group_opcode" />
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
	<field name="lp_msb" descr="Local port number [9:8]\;\;for Retimer: reserved" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is \;interpreted:\;0: Local_port_number\;1: IB_port_number\;\;for Retimer: reserved" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;for Retimer: Data path number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="page_select" descr="The user can select to read a sampled data page or a properties page.\;\;1: SNR_Samples\;16: Module_Status_Properties" access="INDEX" enum="SNR_Samples=0x1" offset="0x4.0" size="0x0.5" />
	<field name="group_cap_mask" descr="Group capability mask:\;Bit 1: SNR" access="RO" enum="SNR=0x2" offset="0x4.16" size="0x0.16" />
	<field name="page_data" descr="Page data:\;Table 1984, &quot;SNR Samples page - Layout,&quot; on page 2320" subnode="pemi_page_data_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).page_select" />
</node>

<node name="pemi_page_data_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="pemi_SNR_Samples_ext" descr="" subnode="pemi_SNR_Samples_ext" offset="0x0.0" selected_by="SNR_Samples" size="0xf8.0" />
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
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local port number\;1: IB / label port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="set_buf_ownership" descr="Supported by HCA only, see PCAM.feature_cap_mask bit 44.\;\;Buffer ownership configuration. when this bits are set to a value other than 0, device will ignore all other fields pfcc register\;0: unknown \;1: device owned, all buffer configuration will return to its defaults." access="WO" offset="0x0.24" size="0x0.2" />
	<field name="buf_ownership" descr="Supported by HCA only, see PCAM.feature_cap_mask bit 44.\;Current status of buffer ownership\;0: unknown\;1: device owned\;2: software owned" access="RO" offset="0x0.26" size="0x0.2" />
	<field name="cap_remote_admin" descr="Indicates if operation of remote admin parameters (dcxb_operation_type 0x2) is supported. \;" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="cap_local_admin" descr="Indicates if operation of local admin parameters (dcxb_operation_type 0x1) is supported. \;" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="dcbx_operation_type" descr="The Operation type, valid only on HCAs.\;0: local_operative_parameters\;1: local_admin_parameters - supported only when cap_local_admin==1.\;2: remote_admin_parameters - supported only when cap_remote_admin==1.\;Only pfctx and pfcrx are supported on remote device" access="INDEX" enum="local_operative_parameters=0x0,local_admin_parameters=0x1,remote_admin_parameters=0x2" offset="0x0.30" size="0x0.2" />
	<field name="prio_mask_rx" descr="Bit per prio indicating if RX flow control policy should be updated based on bit pfcrx ." access="WO" offset="0x4.0" size="0x0.8" />
	<field name="prio_mask_tx" descr="Bit per prio indicating if TX flow control policy should be updated based on bit pfctx ." access="WO" offset="0x4.16" size="0x0.8" />
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
	<field name="group_of_port" descr="The corresponding group number for the local_port" access="RW" offset="0x4.4" size="0x0.4" />
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
	<field name="link_down_events" descr="Perf.PortCounters(LinkDownedCounter)" access="RO" offset="0xC0.0" size="0x4.0" />
	<field name="successful_recovery_events" descr="Perf.PortCounters(LinkErrorRecoveryCounter)\;Note: This counter is valid only for IB." access="RO" offset="0xC4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane4_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane4)" access="RO" offset="0xC8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane4_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane4)" access="RO" offset="0xCC.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane5_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane5)" access="RO" offset="0xD0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane5_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane5)" access="RO" offset="0xD4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane6_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane6)" access="RO" offset="0xD8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane6_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane6)" access="RO" offset="0xDC.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane7_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane7)" access="RO" offset="0xE0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane7_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane7)" access="RO" offset="0xE4.0" size="0x4.0" />
</node>

<node name="phys_layer_stat_cntrs_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear event in msec.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="The time passed since the last counters clear event in msec.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="phy_received_bits_high" descr="This counter provides information on the total amount of traffic (bits) received.\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="phy_received_bits_low" descr="This counter provides information on the total amount of traffic (bits) received.\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="phy_symbol_errors_high" descr="This counter provides information on error bits that were not corrected by phy correction mechanisms. (FEC + PLR)\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="phy_symbol_errors_low" descr="This counter provides information on error bits that were not corrected by phy correction mechanisms. (FEC + PLR)\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="phy_corrected_bits_high" descr="Corrected bits by FEC engine. \;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="phy_corrected_bits_low" descr="Corrected bits by FEC engine. \;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane0_high" descr="This counter provides information on error bits that were identified on lane 0. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 0\;\;\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="phy_raw_errors_lane0_low" descr="This counter provides information on error bits that were identified on lane 0. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 0\;\;\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="phy_raw_errors_lane1_high" descr="This counter provides information on error bits that were identified on lane 1. \;When FEC is enabled this induction corresponds to corrected errors\;In PRBS test mode, indicates the number of PRBS errors\;on lane 1\;\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="phy_raw_errors_lane1_low" descr="This counter provides information on error bits that were identified on lane 1. \;When FEC is enabled this induction corresponds to corrected errors\;In PRBS test mode, indicates the number of PRBS errors\;on lane 1\;\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane2_high" descr="This counter provides information on error bits that were identified on lane 2. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 2\;\;\;\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="phy_raw_errors_lane2_low" descr="This counter provides information on error bits that were identified on lane 2. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 2\;\;\;\;" access="RO" offset="0x34.0" size="0x4.0" />
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
	<field name="estimated_effective_ber_coef" descr="estimated_effective_fec_BER = estimated_effective_fec_ber_coef estimated_effective_ber_coef_float*10^(-effective_fec_ber_magnitude)\;" access="RO" offset="0x64.16" size="0x0.4" />
	<field name="estimated_effective_ber_coef_float" descr="estimated_effective_fec_BER = estimated_effective_fec_ber_coef estimated_effective_ber_coef_float*10^(-effective_fec_ber_magnitude)\;" access="RO" offset="0x64.20" size="0x0.4" />
	<field name="estimated_effective_ber_magnitude" descr="estimated_effective_fec_BER = estimated_effective_fec_ber_coef estimated_effective_ber_coef_float*10^(-effective_fec_ber_magnitude)\;" access="RO" offset="0x64.24" size="0x0.8" />
	<field name="symbol_ber_coef" descr="Symbol_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x68.0" size="0x0.4" />
	<field name="symbol_ber_magnitude" descr="Symbol_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x68.8" size="0x0.8" />
	<field name="phy_effective_errors_high" descr="This counter provides information on error bits that were not corrected by FEC correction algorithm or that FEC is not active.\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="phy_effective_errors_low" descr="This counter provides information on error bits that were not corrected by FEC correction algorithm or that FEC is not active.\;" access="RO" offset="0x80.0" size="0x4.0" />
</node>

<node name="pipg_reg_ext" descr="" size="0x8.0" >
	<field name="ipg_oper" descr="Inter Packet Gap operational value in ipg_res_cap Bytes units.\;For example, in case of &apos;ipg_oper&apos; =3 and &apos;ipg_res_cap&apos;=0: 4 Bytes- the IPG operational size is 12 Bytes (3*4).\;If there is a miss-match between the operational IPG capabilities and the &apos;ipg&apos; field, &apos;ipg_oper&apos; will be 12 Bytes.\;\;Note: For HCA supported only when indicated by PCAM." access="RO" offset="0x0.2" size="0x0.8" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ipg" descr="The Inter Packet Gap admin value for the port in &apos;ipg_res_cap&apos; Bytes units.\;\;For example, in case of &apos;ipg&apos; =4 and &apos;ipg_res_cap&apos;=0: 4 Bytes -the IPG size that will be configured will be 16 Bytes (4*4)\;\;Valid values for configuring the IPG field should meet to following two conditions:\;1. &apos;ipg&apos; = &apos;ipg_min_cap&apos; + &apos;ipg_res_cap&apos;*N. For N= 0,1,2, ..\;2. &apos;ipg&apos; must be in the range of ipg_min_cap and ipg_max_cap." access="RW" offset="0x4.2" size="0x0.8" />
	<field name="ipg_max_cap" descr="Maximum Inter Packet Gap supported on the port in &apos;ipg_res_cap&apos; bytes unit.\;The return value will be according the speed selected in the &apos;ipg_cap_index&quot;." access="RO" offset="0x4.10" size="0x0.8" />
	<field name="ipg_min_cap" descr="Minimum Inter Packet Gap supported on the port in &apos;ipg_res_cap&apos; bytes unit. \;The return value will be according the speed selected in the &apos;ipg_cap_index&quot;." access="RO" offset="0x4.18" size="0x0.4" />
	<field name="ipg_cap_index" descr="The &apos;ipg_min_cap&apos; and &apos;ipg_max_cap&apos; return value will be according to the selected speed index: \;\;0: The Minimum/Maximum capability of the device (Regardless of the operational link speed).\;1: SGMII_100M\;2: 1000BASE-X / SGMII\;4: 5GBASE-R\;5: XFI / XAUI-1 // 10G\;6: XLAUI-4/XLPPI-4 // 40G \;7: 25GAUI-1/ 25GBASE-CR / KR \;8: 50GAUI-2 / LAUI-2/ 50GBASE-CR2/KR2 \;9: 50GAUI-1 /50GBASE-CR / KR\;10: CAUI-4 / 100GBASE-CR4 / KR4\;11: 100GAUI-2 / 100GBASE-CR2 / KR2 \;12: 100GAUI-1 / 100GBASE-CR / KR\;13: 200GAUI-4 / 200GBASE-CR4/KR4\;14: 200GAUI-2 / 200GBASE-CR2/KR2\;15: Reserved [internal] Placeholder for 200GAUI-1\;16: 400GAUI-8/ 400GBASE-CR8\;17: 400GAUI-4/ 400GBASE-CR4\;18: Reserved [internal] Placeholder for 400GAUI-2\;19: Reserved [internal] Placeholder for 400GAUI-1\;20: 800GAUI-8 / 800GBASE-CR8 / KR8\;32: SGMII_10M\;\;Note: For HCA supported only when indicated by PCAM." access="INDEX" offset="0x4.22" size="0x0.6" />
	<field name="ipg_res_cap" descr="IPG configurable resolution of the device.\;0: 4 Bytes\;1: Reserved" access="RO" offset="0x4.28" size="0x0.1" />
</node>

<node name="pltc_reg_ext" descr="" size="0x10.0" >
	<field name="lane_mask" descr="for set operation, lane bitmask\;for query operation, one-hot key" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;1: IB_port_number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="precoding_cap_mask" descr="0x0 - no tx precoding available / no override capabilty\;\;Bit 0- tx precoding override possible via local_tx_precoding_admin field\;Bit 1- rx precoding override possible via local_rx_precoding_admin field" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="local_tx_precoding_admin" descr="0 - auto\;1 - force Tx precoding\;2 - force Tx without precoding" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="local_rx_precoding_admin" descr="Rx configuration override for 100g Pam4 per lane protocols.\;0 - auto\;1 - Rx precoding enabled. \;if negotiated, request Tx precoding from peer.\;2 - Rx precoding disabled. \;if negotiated, request no Tx precoding from peer" access="RW" offset="0x8.16" size="0x0.2" />
	<field name="local_tx_precoding_oper" descr="0 - unknown / no active link\;1 - Tx precoding enabled.\;2 - Tx precoding disabled." access="RO" offset="0xC.0" size="0x0.2" />
	<field name="local_rx_precoding_oper" descr="Rx precoding operational mode\;0 - unknown / no active link\;1 - Rx precoding enabled. \;2 - Rx precoding disabled." access="RO" offset="0xC.16" size="0x0.2" />
</node>

<node name="pmaos_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Module state (reserved while admin_status is disabled):\;0: initializing\;1: plugged_enabled\;2: unplugged\;3: module_plugged_with_error - (details in error_type).\;5: unknown" access="RO" enum="initializing=0x0,plugged_enabled=0x1,unplugged=0x2,module_plugged_with_error=0x3,unknown=0x5" offset="0x0.0" size="0x0.4" />
	<field name="admin_status" descr="Module administrative state (the desired state of the module):\;1: enabled\;2: disabled_by_configuration\;3: enabled_once - if the module is active and then unplugged, or module experienced an error event, the operational status should go to &quot;disabled&quot; and can only be enabled upon explicit enable command.\;\;Note - To disable a module, all ports associated with the port must be disabled first.\;" access="RW" enum="enabled=0x1,disabled_by_configuration=0x2,enabled_once=0x3" offset="0x0.8" size="0x0.4" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="rst" descr="Module Reset toggle\;NOTE: setting reset while module is plugged-in will result in transition of oper_status to initialization." access="OP" offset="0x0.31" size="0x0.1" />
	<field name="e" descr="Event Generation on operational state change:\;0: Do_not_generate_event\;1: Generate_Event\;2: Generate_Single_Event\;Not supported by secondary ASICs." access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="error_type" descr="Module error details:\;0x0: Power_Budget_Exceeded\;0x1: Long_Range_for_non_MLNX_cable_or_module\;0x2: Bus_stuck - (I2C Data or clock shorted)\;0x3: bad_or_unsupported_EEPROM\;0x4: Enforce_part_number_list\;0x5: unsupported_cable\;0x6: High_Temperature\;0x7: bad_cable - (Module/Cable is shorted)\;0x8: PMD_type_is_not_enabled - (see PMTPS)\;0xc: pcie_system_power_slot_Exceeded\;\;[DWIP] 0xf: Boot_error\;[DWIP] 0x10: Recovery_error\;[DWIP] 0x11: Submodule_failure\;Valid only when oper_status = 4&apos;b0011" access="RO" enum="Power_Budget_Exceeded=0x0,Long_Range_for_non_MLNX_cable_or_module=0x1,Bus_stuck=0x2,bad_or_unsupported_EEPROM=0x3,Enforce_part_number_list=0x4,unsupported_cable=0x5,High_Temperature=0x6,bad_cable=0x7,PMD_type_is_not_enabled=0x8,pcie_system_power_slot_Exceeded=0xc" offset="0x4.8" size="0x0.5" />
	<field name="operational_notification" descr="This notification can occur only if module passed initialization process\;0x0: No notifications.\;0x1: Speed degradation - the module is not enabled in its full speed due to incompatible transceiver/cable \;Valid only when oper_status = 4&apos;b0001." access="RO" offset="0x4.16" size="0x0.4" />
	<field name="rev_incompatible" descr="When in multi ASIC module sharing systems,\;This flag will be asserted in case primary and secondary FW versions are not compatible." access="RO" offset="0x4.28" size="0x0.1" />
	<field name="secondary" descr="Indicates whether the ASIC serves as a the modules secondary (=1) or primary (=0) device." access="RO" offset="0x4.29" size="0x0.1" />
	<field name="ee" descr="Event update enable. If this bit is set, event generation will be updated based on the e field. Only relevant on Set operations.\;Not supported by secondary ASICs." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="ase" descr="Admin state update enable. If this bit is set, admin state will be updated based on admin_state field. Only relevant on Set() operations." access="WO" offset="0x4.31" size="0x0.1" />
</node>

<node name="pmcr_reg_ext" descr="" size="0x20.0" >
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="error_code_response" descr="Valid for CMIS modules.\;error code response on override values.\;0x0: ConfigUndefined\;0x1: ConfigSuccess\;0x2: ConfigRejected\;0x3: ConfigRejectedInvalidAppSel\;0x4: ConfigRejectedInvalidDataPath\;0x5: ConfigRejectedInvalidSI\;0x6: ConfigRejectedLanesInUse\;0x7: ConfigRejectedPartialDataPath\;0xC: ConfigInProgress" access="RO" enum="ConfigUndefined=0x0,ConfigSuccess=0x1,ConfigRejected=0x2,ConfigRejectedInvalidAppSel=0x3,ConfigRejectedInvalidDataPath=0x4,ConfigRejectedInvalidSI=0x5,ConfigRejectedLanesInUse=0x6,ConfigRejectedPartialDataPath=0x7,ConfigInProgress=0xc" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cs_sel" descr="Valid only for CMIS (QSFP-DD / SFP-DD / OSFP) compliant modules.\;If Control Set 1 not implemented or non CMIS module ignore field.\;0 - Auto (default)\;1 - Use Control Set 0\;2 - Use Control Set 1" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="cdr_override_cntl" descr="Module CDR override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="cdr_override_cap" descr="Module TX and RX override control capability.\;Bit 0 - RX CDR control is possible\;Bit 0 - TX CDR control is possible" access="RO" offset="0x4.2" size="0x0.2" />
	<field name="cdr_override_value" descr="Valid only in case CDR is configured to override mode by cdr_override_cntl: \;0 - RX OFF, TX OFF\;1 - RX ON , TX OFF\;2 - RX OFF, TX ON\;3 - RX ON, TX ON" access="RW" offset="0x4.8" size="0x0.4" />
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
	<field name="tx_adaptive_override_value" descr="0 - disable adaptive Tx Equailization\;1 - enable adaptive Tx equalization\;Valid only in case TX equalization is configured to override mode by tx_adaptive_override_cntrl." access="RW" offset="0x10.17" size="0x0.1" />
	<field name="tx_adaptive_override_cntrl" descr="Module adaptive tuning flow override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - override" access="RW" offset="0x10.24" size="0x0.2" />
	<field name="tx_adaptive_override_cap" descr="Module TX adaptive tuning flow override control capability." access="RO" offset="0x10.26" size="0x0.1" />
	<field name="ap_sel_override_cntrl" descr="Module Application select override control:\;0 - Auto (default)\;1 - Use Module&apos;s Default application value\;2 - Override" access="RW" offset="0x18.0" size="0x0.2" />
	<field name="ap_sel_override_value" descr="Application Select from the applications list advertised by the module. Up to 15 applications available.\;\;Values range from 1 to 15.\;\;Note: application can be set with default SI values defined by the module or SI defined by the host" access="RW" offset="0x18.8" size="0x0.4" />
</node>

<node name="pmlp_reg_ext" descr="" size="0x40.0" >
	<field name="width" descr="0: unmap_local_port\;1: x1 - lane 0 is used\;2: x2 - lanes 0,1 are used\;4: x4 - lanes 0,1,2 and 3 are used\;8: x8 - lanes 0-7 are used\;\;Other - reserved" access="RW" enum="unmap_local_port=0x0,x1=0x1,x2=0x2,x4=0x4,x8=0x8" offset="0x0.0" size="0x0.8" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="m_lane_m" descr="Module lane mapping: \;0 - Local to Module mapping include module lanes mapping\;1 - Local to Module mapping only, without lane mapping\;\;When this operational is set (&apos;1&apos;), the following fields are ignored in SET command and should return the value &quot;0&quot; in GET commands: \;PMLP.rxtx\;PMLP.lane&lt;i&gt;_module_mapping.tx_lane\;PMLP.lane&lt;i&gt;_module_mapping.rx_lane" access="OP" offset="0x0.28" size="0x0.1" />
	<field name="rxtx" descr="Use different configuration for RX and TX.\;If this bit is cleared, the TX value is used for both RX and TX. When set, the RX configuration is taken from the separate field. This is to enable backward compatible implementation." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="lane_module_mapping" descr="Module SerDes for lane &lt;i&gt;\;Up to 8 SerDeses in a module can be mapped to a local port." subnode="lane_2_module_mapping_ext" access="RW" high_bound="7" low_bound="0" offset="0x4.0" size="0x20.0" />
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

<node name="pmmp_reg_ext" descr="" size="0x2c.0" >
	<field name="sticky" descr="When set will keep eeprom_override values after plug out event" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="apply_im" descr="When set, override will be configured immediately without PMAOS toggle requirement if supported.\;for list supported overrides see eeprom_override description.\;supported if PCAM.bit 87 set" access="WO" offset="0x0.1" size="0x0.1" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="eeprom_override" descr="Override/ignore EEPROM advertisement properties bitmask: \;Bit 0: Override_cable_protocols_and_technology_for_QSFP\;Bit 1: Override_cable_protocols_and_technology_for_SFP\;Bit 2: Ignore_Power_Class - set high power\;Bit 3: Override_Cable_Length \;Bit 4: Override_Attenuation\;Bit 8: Set_Module_to_Low_Power\;Bit 9: Override_cable_protocols_and_technology_for_CMIS - based modules QSFP-DD/ OSFP/ DSFP/ SFP-DD\;Bit 11: Override_module_type\;\;Supported overrides with apply_im is Bit 8.\;rest of overrides will be applied only after PMAOS toggle." access="RW" enum="Override_cable_protocols_and_technology_for_QSFP=0x1,Override_cable_protocols_and_technology_for_SFP=0x2,Ignore_Power_Class=0x4,Override_Cable_Length=0x8,Override_Attenuation=0x10,Set_Module_to_Low_Power=0x100,Override_cable_protocols_and_technology_for_CMIS=0x200,Override_module_type=0x800" offset="0x4.0" size="0x0.16" />
	<field name="eeprom_override_mask" descr="Write Mask bit (negative polarity):\;0 - allow write\;1 - ignore write\;On write commands, indicates which of the bits from eeprom_override field are updated.\;Reserved on read operations." access="WO" offset="0x4.16" size="0x0.16" />
	<field name="qsfp_cable_protocol_technology" descr="Protocol technology override for QSFP cable or CMIS based cable (QSFP-DD/OSFP)\;Valid only when the protocols and technology for QSFP is overridden as indicated by eeprom_override\;Table 1656, &quot;PMMP - QSFP Protocol Bytes Override Layout,&quot; on page 1939\;Table 1660, &quot;PMMP - CMIS Protocol Bytes Override Layout,&quot; on page 1944" subnode="pmmp_reg_qsfp_cable_protocol_technology_auto_ext" access="RW" offset="0x8.0" size="0xc.0" union_selector="$(parent).eeprom_override" />
	<field name="sfp_cable_protocol_technology" descr="Valid only when the protocols and technology is overridden as indicated by eeprom_override\;Table 1658, &quot;PMMP - SFP Protocol Bytes Override Layout,&quot; on page 1942" subnode="pmmp_reg_sfp_cable_protocol_technology_auto_ext" access="RW" offset="0x14.0" size="0xc.0" union_selector="$(parent).eeprom_override" />
	<field name="cable_length" descr="Length of cable assembly, units of 1 m for non CMIS cables.\;\;for CMIS cables, represents cable length field:\;bits 6:7 represent cable_length_multiplier for calculating cable length\;00 - 0.1 multiplier (0.1 to 6.3m)\;01- 1 multiplier (1 to 63m)\;10 - 10 multiplier (10 to 630m)\;11 - 100 multiplier (100 to 6300m)\;\;Valid only when the cable length is overridden as indicated by eeprom_override." access="RW" offset="0x20.0" size="0x0.8" />
	<field name="module_type" descr="0: passive_copper_cable\;1: active_copper_cable\;2: Liner_far_end_equlized_copper\;3: Linear_full_equlized_copper\;4: Linear_optical_module - Direct Drive\;5: active_optical_module\;6: on_board_retimer_over_transceiver" access="RW" offset="0x20.8" size="0x0.4" />
	<field name="attenuation_5g" descr="Valid only when the attenuation is overridden as indicated by eeprom_override.\;Attenuation - total channel attenuation @ 5GHz in db." access="RW" offset="0x24.0" size="0x0.8" />
	<field name="attenuation_7g" descr="Valid only when the attenuation is overridden as indicated by eeprom_override.\;Attenuation - total channel attenuation @ 7GHz in db." access="RW" offset="0x24.8" size="0x0.8" />
	<field name="attenuation_12g" descr="Valid only when the attenuation is overridden as indicated by eeprom_override.\;Attenuation - total channel attenuation @ 12GHz in db." access="RW" offset="0x24.16" size="0x0.8" />
	<field name="attenuation_25g" descr="Valid only when the attenuation is overridden as indicated by eeprom_override.\;Attenuation - total channel attenuation @ 25GHz in db." access="RW" offset="0x24.24" size="0x0.8" />
	<field name="attenuation_53g" descr="Valid only when the attenuation is overridden as indicated by eeprom_override.\;Attenuation - total channel attenuation @ 53GHz in db." access="RW" offset="0x28.8" size="0x0.8" />
</node>

<node name="pmmp_reg_qsfp_cable_protocol_technology_auto_ext" descr="" attr_is_union="1" size="0xc.0" >
	<field name="pmmp_qsfp_protocol_override_layout_ext" descr="" subnode="pmmp_qsfp_protocol_override_layout_ext" offset="0x0.0" selected_by="Override_cable_protocols_and_technology_for_QSFP" size="0xc.0" />
	<field name="pmmp_cmis_protocol_override_layout_ext" descr="" subnode="pmmp_cmis_protocol_override_layout_ext" offset="0x0.0" selected_by="Override_cable_protocols_and_technology_for_CMIS" size="0xc.0" />
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
	<field name="lane_mask" descr="Reserved when (le=0 or ls = 0)\;Logical lane number mask.\;For Get operation One-Hot key (Only one bit set)" access="INDEX" offset="0x0.4" size="0x0.8" />
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
	<field name="module_type" descr="module_type: \;0: Backplane_with_4_lanes\;1: QSFP\;2: SFP\;3: No_Cage\;4: Backplane_with_single_lane\;8: Backplane_with_two_lanes\;10: Chip2Chip4x\;11: Chip2Chip2x \;12: Chip2Chip1x\;14: QSFP_DD \;15: OSFP\;16: SFP_DD\;17: DSFP \;18: Chip2Chip8x\;19: Twisted_Pair\;20: Backplane_with_8_lanes" access="RW" enum="Backplane_with_4_lanes=0x0,QSFP=0x1,SFP=0x2,No_Cage=0x3,Backplane_with_single_lane=0x4,Backplane_with_two_lanes=0x8,Chip2Chip4x=0xa,Chip2Chip2x=0xb,Chip2Chip1x=0xc,QSFP_DD=0xe,OSFP=0xf,SFP_DD=0x10,DSFP=0x11,Chip2Chip8x=0x12,Twisted_Pair=0x13,Backplane_with_8_lanes=0x14" offset="0x4.0" size="0x0.5" />
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

<node name="port_state_behavior_ext" descr="" size="0x10.0" >
	<field name="enforce_port_state_enabled" descr="0x0: DISABLED\;0x1: ENABLED - regular driver will be able to enforce physical port state." access="RW" enum="DISABLED=0x0,ENABLED=0x1" offset="0x0.31" size="0x0.1" />
</node>

<node name="ppad_reg_ext" descr="" size="0x10.0" >
	<field name="mac_47_32" descr="If single_base_mac = 0 - base MAC address\;For HCA mac[7:0] is reserved \;If single_base_mac = 1 - the per port MAC address" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="local_port" descr="Port number\;Reserved when single_base_mac = 0" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="single_base_mac" descr="0: base_mac - Switch global MAC address. FW will set incremental MAC per port starting from the base_mac.\;1: single_mac - mac of the local_port\;Reserved for SwitchX/-2." access="OP" offset="0x0.28" size="0x0.1" />
	<field name="mac_31_0" descr="If single_base_mac = 0 - base MAC address\;For HCA mac[7:0] is reserved \;If single_base_mac = 1 - the per port MAC address" access="RW" offset="0x4.0" size="0x4.0" />
</node>

<node name="ppaos_reg_ext" descr="" size="0x10.0" >
	<field name="phy_test_mode_status" descr="Port extended down status:\;0: regular_operation - (port down/up according to PAOS) \;1: phy_test_mode\;phy test mode can be valid only when PAOS.admin_status=2 and PAOS.oper_status=2 (i.e port is down)." access="RO" enum="regular_operation=0x0,phy_test_mode=0x1" offset="0x0.0" size="0x0.4" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="phy_test_mode_admin" descr="Port extended administrative down status:\;0: regular_operation (port down/up according to PAOS) \;1: phy_test_mode \;\;The phy test mode (1) can be set only when PAOS.admin_status=2 (i.e port configuration is down)." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.\;Switch partition ID with which to associate the port.\;Switch partitions are numbered from 0 to 7 inclusively.\;The swid field is only valid when the local_port is the router port. In this case, the swid indicates which of the router ports to configure/query." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="phy_status" descr="rx phy status:\;0: rx_phy_down\;1: rx_phy_up\;2: rx_phy_down_by_command\;\;Note: The phy up indication is according to protocol (up == align_status=true)\;i.g. In PRBS test mode phy up is when PRB is lock (up== prbs lock)" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x4.4" size="0x0.4" />
	<field name="phy_status_admin" descr="rx phy port admin. Controls phy entities operational port status.\;valid for port_type &lt;&gt; &apos;0&apos;.\;to operate link status for port_type &apos;0&apos; use PAOS.admin_status.\;0: rx_phy_down\;1: rx_phy_up\;" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="dc_cpl_port" descr="When set, indicates that ports trace is DC coupled.\;Enabling test mode in case of DC coupled port is allowed only when setting dc_cpl_allow and printing warning to user as specified in the description." access="RO" offset="0x4.28" size="0x0.1" />
	<field name="dc_cpl_allow" descr="Relevant only for DC couple ports, Ignored otherwise.\;Field must be set when entering test mode, otherwise command is ignored.\;When entering test mode in DC couple system the following message must be presented to user:\;&quot;Warning: DC couple system must be powered on both sides of the physical link prior to enabling test mode. System may be harmed and product lifetime may be shortened if not ensured.&quot;" access="WO" offset="0x4.29" size="0x0.1" />
</node>

<node name="ppcc_reg_ext" descr="" size="0xfc.0" >
	<field name="cmd_type" descr="0x0- get algo info\;0x1- enable algo\;0x2- disable algo\;0x3- get algo enabling status\;0x4- get num of params\;0x5- get param info\;0x6- get param\;0x7- get &amp; clear param\;0x8- set param\;\;0xA- bulk get. Reserved when method = Set\;0xB- bulk set. Reserved when method = Get\;0xC- bulk get counters. Reserved when method = Set\;0xD- bulk get and clear counters \;0xE- get num of counters. Reserved when method = Set\;0xF- get counter info. Reserved when method = Set\;0x10 - get algo info array" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. Determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="algo_slot" descr="Selects the algo slot to operate on (0 - algo slot at bit #0, 1 - algo slot at bit #1, etc). \;For command types other than 0x10 (get algo info array), must point to a present algo slot (a slot index with a non-zero algo id - as returned via Command type 0x10)" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="algo_param_index" descr="Selects the specific param to get/set (if applicable, 0 if not). Index is zero-based. Must be smaller than value returned in get_num_of_params / get_num_of_counters. \;\;Reserved when command type != 0x5, 0x6, 0x7, 0x8, 0xF" access="INDEX" offset="0x4.16" size="0x0.16" />
	<field name="value" descr="The layout of this field varies based on command type:\;For cmd_type = 0x0: returns 32-bit algo_num or 0 if no algo is available at this index\;For cmd_type = 0x3: returns 1 if enabled, 0 otherwise\;For cmd_type = 0x4: returns num of params algo has\;For cmd_type = 0x6:: returns value of param (selected by param index)\;For cmd_type = 0x7: returns value of param (selected by param index) and clears param\;For cmd_type = 0x8: The value to write to param (selected by param index). Set by the user. Set command is silently ignored if value outside min..max values (comparison is unsigned) or if param permission is not read-write.\;For cmd_type = 0xE: returns num of counters algo has\;\;All the rest: returns 0" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="param_value1" descr="For cmd_type = 0x5: return default value of param\;\;\;\;Reserved for other commands" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="param_value2" descr="For cmd_type = 0x5: return min legal value of param\;\;\;\;Reserved for other commands" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="param_value3" descr="For cmd_type = 0x5: return max legal value of param\;For cmd_type = 0xF: return max legal value of counter; counter wraps-around to 0 when exceeding this value\;\;\;Reserved for other commands" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="sl_bitmask" descr="This field allows to apply to specific SLs based on the bitmask. When a bit is set, it&apos;s index SL shall be configured." access="RW" offset="0x18.0" size="0x0.16" />
	<field name="prm" descr="When cmd_type = 0x5 / 0xF:\;0-param / counter is read-only\;1-param / counter is read-write\;2-param / counter is read-only but may also be accessed and cleared via &quot;get &amp; clear&quot; command\;Reserved for other commands" access="RO" offset="0x1C.0" size="0x0.2" />
	<field name="sl_bitmask_support" descr="Indicates whether the device supports sl_bitmask logic" access="RO" offset="0x1C.2" size="0x0.1" />
	<field name="counter_en" descr="when set, enables PPC algo specific counters, else disabled.\;Each port supports one set of counters, e.g The counters are supported only on one specific set of [algo_slot, sl_bitmap],\;" access="RW" offset="0x1C.3" size="0x0.1" />
	<field name="trace_en" descr="when set, indicates algorithm trace mechanism is enabled. Else, trace is disabled" access="RW" offset="0x1C.4" size="0x0.1" />
	<field name="text_length" descr="Length in bytes of text field\;Valid when cmd_type = 0x0 / 0x5  / 0xA/ 0xB/ 0xC/ 0xD/ 0xF/ 0x10\;Reserved for other commands" access="RW" offset="0x1C.8" size="0x0.8" />
	<field name="text" descr="The layout of this field varies based on command type:\;0x0: algo name, comma,  algo description (ASCII string) [Internal] e.g &quot;RPG_time_reset, the time between RPG resets&quot;\;0x5: param name, comma,  param description (ASCII string)\;[Internal]0x9: algo-specific binary diagnostics data\;0xA: Array of 32 bits parameters, starting from parameter index 0 up to (text_len/4 -1)\;0xB: Array of 32 bits parameters, starting from parameter index 0 up to (text_len/4 -1)\;0xC: Array of 32 bits counters, starting from parameter index 0 up to (text_len/4 -1)\;0xD: Array of 32 bits counters, starting from parameter index 0 up to (text_len/4 -1)\;0xF: counter name, comma,  counter description (ASCII string)\;0x10: array of 32bit Algo info, up to 16 entries, representing which algo id is present per slot. Zero value means algo id is irrelevant.\;Algo Info: algo_id[31:16], algo_major_ver[15:8] algo_minor_ver[7:0]\;All commands are limited by text_len" access="RW" high_bound="54" low_bound="0" offset="0x20.0" size="0xdc.0" />
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
	<field name="plr_codes_loss_high" descr="Recieved bandwidth loss due to codes retransmission. calculated in resolution of \;(plr_rcv_code_err / plr_rcv_codes) * 10^10\;\;BW Loss % = (plr_codes_loss / 10^10 ) *100" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="plr_codes_loss_low" descr="Recieved bandwidth loss due to codes retransmission. calculated in resolution of \;(plr_rcv_code_err / plr_rcv_codes) * 10^10\;\;BW Loss % = (plr_codes_loss / 10^10 ) *100" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_within_t_sec_max_high" descr="The maximum number of retransmitted events in t sec window\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_within_t_sec_max_low" descr="The maximum number of retransmitted events in t sec window\;" access="RO" offset="0x44.0" size="0x4.0" />
</node>

<node name="ppcnt_reg_counter_set_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="eth_802_3_cntrs_grp_data_layout_ext" descr="" subnode="eth_802_3_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="IEEE_802_3_Counters" size="0xf8.0" />
	<field name="eth_2863_cntrs_grp_data_layout_ext" descr="" subnode="eth_2863_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="RFC_2863_Counters" size="0xf8.0" />
	<field name="eth_2819_cntrs_grp_data_layout_ext" descr="" subnode="eth_2819_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="RFC_2819_Counters" size="0xf8.0" />
	<field name="eth_3635_cntrs_grp_data_layout_ext" descr="" subnode="eth_3635_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="RFC_3635_Counters" size="0xf8.0" />
	<field name="eth_extended_cntrs_grp_data_layout_ext" descr="" subnode="eth_extended_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="Ethernet_Extended_Counters" size="0xf8.0" />
	<field name="eth_discard_cntrs_grp_ext" descr="" subnode="eth_discard_cntrs_grp_ext" offset="0x0.0" selected_by="Ethernet_Discard_Counters" size="0xf8.0" />
	<field name="eth_per_prio_grp_data_layout_ext" descr="" subnode="eth_per_prio_grp_data_layout_ext" offset="0x0.0" selected_by="Per_Priority_Counters" size="0xf8.0" />
	<field name="eth_per_traffic_class_layout_ext" descr="" subnode="eth_per_traffic_class_layout_ext" offset="0x0.0" selected_by="Per_Traffic_Class_Counters" size="0xf8.0" />
	<field name="phys_layer_cntrs_ext" descr="" subnode="phys_layer_cntrs_ext" offset="0x0.0" selected_by="Physical_Layer_Counters" size="0xf8.0" />
	<field name="eth_per_traffic_class_cong_layout_ext" descr="" subnode="eth_per_traffic_class_cong_layout_ext" offset="0x0.0" selected_by="Per_Traffic_Class_Congestion_Counters" size="0xf8.0" />
	<field name="phys_layer_stat_cntrs_ext" descr="" subnode="phys_layer_stat_cntrs_ext" offset="0x0.0" selected_by="Physical_Layer_Statistical_Counters" size="0xf8.0" />
	<field name="IB_portcntrs_attribute_grp_data_ext" descr="" subnode="IB_portcntrs_attribute_grp_data_ext" offset="0x0.0" selected_by="InfiniBand_Port_Counters" size="0xf8.0" />
	<field name="IB_long_portcntrs_attribute_grp_data_ext" descr="" subnode="IB_long_portcntrs_attribute_grp_data_ext" offset="0x0.0" selected_by="InfiniBand_Extended_Port_Counters" size="0xf8.0" />
	<field name="ppcnt_plr_counters_ext" descr="" subnode="ppcnt_plr_counters_ext" offset="0x0.0" selected_by="PLR_counters_group" size="0xf8.0" />
	<field name="ppcnt_rs_fec_histograms_counters_ext" descr="" subnode="ppcnt_rs_fec_histograms_counters_ext" offset="0x0.0" selected_by="RS_FEC_Histogram_group" size="0xf8.0" />
	<field name="ppcnt_infiniband_packets_counter_ext" descr="" subnode="ppcnt_infiniband_packets_counter_ext" offset="0x0.0" selected_by="InfiniBand_pkts_counters" size="0xf8.0" />
	<field name="ppcnt_infiniband_general_counter_ext" descr="" subnode="ppcnt_infiniband_general_counter_ext" offset="0x0.0" selected_by="InfiniBand_General_Counters" size="0xf8.0" />
</node>

<node name="ppcnt_reg_ext" descr="" size="0x100.0" >
	<field name="grp" descr="Performance counter group.\;Group 63 indicates all groups (include all per priority/TC/Receive Buffer counters). Only valid on Set() operation with clr bit set.\;0x0: IEEE_802_3_Counters\;0x1: RFC_2863_Counters\;0x2: RFC_2819_Counters\;0x3: RFC_3635_Counters\;0x5: Ethernet_Extended_Counters\;0x6: Ethernet_Discard_Counters \;0x10: Per_Priority_Counters - \;0x11: Per_Traffic_Class_Counters - \;0x12: Physical_Layer_Counters\;0x13: Per_Traffic_Class_Congestion_Counters\;0x16: Physical_Layer_Statistical_Counters\;0x20: InfiniBand_Port_Counters\;0x21: InfiniBand_Extended_Port_Counters\;0x22: PLR_counters_group\;0x23: RS_FEC_Histogram_group\;0x25: InfiniBand_pkts_counters\;0x26: InfiniBand_General_Counters\;0x27: L1_General_Counters" access="INDEX" enum="IEEE_802_3_Counters=0x0,RFC_2863_Counters=0x1,RFC_2819_Counters=0x2,RFC_3635_Counters=0x3,Ethernet_Extended_Counters=0x5,Ethernet_Discard_Counters=0x6,Per_Priority_Counters=0x10,Per_Traffic_Class_Counters=0x11,Physical_Layer_Counters=0x12,Per_Traffic_Class_Congestion_Counters=0x13,Physical_Layer_Statistical_Counters=0x16,InfiniBand_Port_Counters=0x20,InfiniBand_Extended_Port_Counters=0x21,PLR_counters_group=0x22,RS_FEC_Histogram_group=0x23,InfiniBand_pkts_counters=0x25,InfiniBand_General_Counters=0x26" offset="0x0.0" size="0x0.6" />
	<field name="port_type" descr="Supported only when indicated by PCAM on FPGA based NICs:\;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;1: IB_port_number\;2: host_port_number\;\;Note - pnat=2 is supported for &quot;Per Traffic Class Congestion Counters&quot; and &quot;Per Traffic Class Counters&quot; groups." access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must be always 0.\;Switch partition ID to associate port with.\;Switch partitions are numbered from 0 to 7 inclusively.\;Switch partition 254 indicates stacking ports.\;Switch partition 255 indicates all switch partitions.\;Only valid on Set() operation with local_port=255." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="prio_tc" descr="Priority index for per priority counter sets, valid values: 0-7\;For Spectrum-2 and on at tx side range can be 0 .. cap_max_tclass_data-1, see QGCR.tx_cnt_tclass\;\;Traffic class index for per traffic class counter set, valid values: \;For Switches, valid values: 0 .. cap_max_tclass_data-1 \;\;For HCA, valid values: 0.. HCA_CAP.max_tc\;\;Otherwise must be 0.\;" access="INDEX" offset="0x4.0" size="0x0.5" />
	<field name="grp_profile" descr="Supported only when indicated by PCAM: PPCNT_grp_profile_supported (bit 73).\;The group profile index. Relevant only if the clr bit is set.\;0: Will reset the counter value for all counters in the counter group.\;Else: Will point to the corresponding bit-map profile in the PPCGP register. The bit map will return the specific counters that will be reset in the group.\;\;NOTE: The grp_profile index is not supported for the following counters groups:\;1. 0x12: Physical_Layer_Counters\;2. 0x16: Physical_Layer_Statistical_Counters\;3. 0x22: PLR_counters_group\;" access="INDEX" offset="0x4.5" size="0x0.3" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x4.8" size="0x0.4" />
	<field name="counters_cap" descr="counters_cap is supported if PCAM.feature_cap_mask bit 85 is set.\;When set, each counter in the group will show in bit 0 if the counter is supported.\;&apos;0&apos; - not supported\;&apos;1&apos; - supported\;Note: To know which PPCNT groups are supported per device, listed in table TBD or PCAM fields with PPCNT can be queried." access="OP" offset="0x4.29" size="0x0.1" />
	<field name="clr" descr="Clear counters. Setting the clr bit will reset the counter value for all counters in the counter group. This bit can be set for both Set() and Get() operation.\;\;NOTE: Clearing a certain group&apos;s counters can influence another group&apos;s counters value." access="OP" offset="0x4.31" size="0x0.1" />
	<field name="counter_set" descr="Counter set as described in\;Table 1568, &quot;Ethernet IEEE 802.3 Counters Group Data Layout,&quot; on page 1832\;Table 1570, &quot;Ethernet RFC 2863 Counter Group Data Layout,&quot; on page 1837\;Table 1572, &quot;Ethernet RFC 2819 Counter Group Data Layout,&quot; on page 1840\;Table 1574, &quot;Ethernet RFC 3635 Counter Group Data Layout,&quot; on page 1845\;Table 1576, &quot;Ethernet Extended Counter Group Data Layout,&quot; on page 1849\;Table 1579, &quot;Ethernet Discard Counter Group Fields,&quot; on page 1854\;Table 1580, &quot;Ethernet Per Priority Group Data Layout,&quot; on page 1856\;Table 1584, &quot;Ethernet Per Traffic Class Group data layout,&quot; on page 1864\;Table 1596, &quot;Physical Layer Counters Data Layout,&quot; on page 1875\;Table 1586, &quot;Ethernet Per Traffic Class Congestion Group data layout,&quot; on page 1865\;Table 1600, &quot;Physical Layer Statistical Counters Data Layout,&quot; on page 1885\;Table 1592, &quot;InfiniBand PortCounters Attribute Group Data Layout,&quot; on page 1869\;Table 1594, &quot;InfiniBand Extended PortCounters Attribute Group Data Layout,&quot; on page 1871\;Table 1602, &quot;PLR Counters Data Layout,&quot; on page 1890 \;Table 1604, &quot;RS-Histograms Data Layout,&quot; on page 1892\;Table 1606, &quot;InfiniBand Packets Counters Data Layout,&quot; on page 1893\;Table 1608, &quot;InfiniBand General Counters Data Layout,&quot; on page 1896" subnode="ppcnt_reg_counter_set_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).grp" />
</node>

<node name="ppcnt_rs_fec_histograms_counters_ext" descr="" size="0xf8.0" >
	<field name="hist" descr="Value of RS-hist\;In order to know bin errors distribution use PPHCR reg." subnode="uint64" access="RO" high_bound="20" low_bound="0" offset="0x0.0" size="0xa8.0" />
</node>

<node name="pphcr_bin_range_ext" descr="" size="0x4.0" >
	<field name="low_val" descr="low range of bin&apos;s measurement" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="high_val" descr="high range of bin&apos;s measurement" access="RW" offset="0x0.16" size="0x0.4" />
</node>

<node name="pphcr_ext" descr="" size="0x50.0" >
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
	<field name="bin_range" descr="Write to bin_range[x] is applicable only if we = 1 &amp; the corresponding bits in bin_range_write_mask is set.\;Mapping of measurement units to a bin.\;See Table 1880, &quot;PPHCR - Port Phy Bin Range Histogram Configuration Layout,&quot; on page 2220" subnode="pphcr_bin_range_ext" access="RW" high_bound="15" low_bound="0" offset="0x10.0" size="0x40.0" />
</node>

<node name="pplm_reg_ext" descr="" size="0x50.0" >
	<field name="test_mode" descr="0: Mission_mode_configuration_and_capabilities\;1: Test_mode_configuration_and_capabilities" access="INDEX" enum="Mission_mode_configuration_and_capabilities=0x0,Test_mode_configuration_and_capabilities=0x1" offset="0x0.1" size="0x0.1" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="port_type" descr="Supported only when indicated by PCAM \;0: Network_Port\;1: Near_End_Port - For Gearbox - Host side\;2: Internal_IC_Port \;3: Far_End_Port - For Gearbox - Line side\;\;Other values are reserved.\;\;Using port_type &apos;0&apos; will override all different parts of the link structure.\;Using port_type &apos;1&apos; will configure also port_type &apos;2&apos; accordingly and vise versa." access="INDEX" enum="Network_Port=0x0,Near_End_Port=0x1,Internal_IC_Port=0x2,Far_End_Port=0x3" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0: Local_port_number\;1: IB_port_number" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fec_mode_active" descr="Active FEC (bitmask)\;For each enum, a short prefix for tools is presented in the row below.\;0: No_FEC \;1: Firecode_FEC\;FC_FEC\;2: Standard_RS_FEC - RS(528,514)\;KR4_FEC\;3: Standard_LL_RS_FEC - RS(271,257)\;LL_FEC\;5: reserved - [Internal]\;6: Interleaved_Standard_RS-FEC - (544,514)\;Int_KP4_FEC\;7: Standard_RS-FEC - (544,514)\;KP4_FEC\;9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;ELL_FEC\;10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - (272,257+1)\;Int_ELL_FEC\;12: RS-FEC - (544,514) + PLR\;13: LL-FEC - (271,257) + PLR\;14: Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal] \;15: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]\;" access="RO" enum="No_FEC=0x0,Firecode_FEC=0x1,Standard_RS_FEC=0x2,Standard_LL_RS_FEC=0x3,Interleaved_Standard_RS=0x6,Standard_RS=0x7,Ethernet_Consortium_LL_50G_RS_FEC=0x9,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC=0xa" offset="0xC.0" size="0x0.24" />
	<field name="fec_override_cap_10g_40g" descr="10GE/40GE Ethernet FEC override capability bitmask:\;Bit 0: No-FEC\;Bit 1: Firecode_FEC\;Bit 2: Reserved2\;Bit 3: Reserved3\;\;" access="RO" enum="No=0x1,Firecode_FEC=0x2,Reserved2=0x4,Reserved3=0x8" offset="0x10.0" size="0x0.4" />
	<field name="fec_override_cap_25g" descr="25GE Ethernet FEC override capability bitmask:\;Bit 0: No-FEC\;Bit 1: Firecode_FEC\;Bit 2: RS-FEC\;Bit 3: Reserved" access="RO" enum="No=0x1,Firecode_FEC=0x2,RS=0x4,Reserved=0x8" offset="0x10.4" size="0x0.4" />
	<field name="fec_override_cap_50g" descr="50GE (2 lanes) Ethernet FEC override capability bitmask:\;Bit 0: No-FEC\;Bit 1: Firecode_FEC\;Bit 2: RS-FEC\;Bit 3: Reserved" access="RO" enum="No=0x1,Firecode_FEC=0x2,RS=0x4,Reserved=0x8" offset="0x10.8" size="0x0.4" />
	<field name="fec_override_cap_100g" descr="100GE (4 lanes) Ethernet FEC override capability bitmask:\;Bit 0: No-FEC\;Bit 1: Reserved1\;Bit 2: RS-FEC - (528,514)\;Bit 3: Reserved3" access="RO" enum="No=0x1,Reserved1=0x2,RS=0x4,Reserved3=0x8" offset="0x10.12" size="0x0.4" />
	<field name="fec_override_cap_56g" descr="56GE Ethernet FEC override capability bitmask:\;Bit 0: No-FEC\;Bit 1: Firecode_FEC\;Bit 2: Reserved2\;Bit 3: Reserved3" access="RO" enum="No=0x1,Firecode_FEC=0x2,Reserved2=0x4,Reserved3=0x8" offset="0x10.16" size="0x0.4" />
	<field name="rs_fec_correction_bypass_cap" descr="RS-FEC correction bypass override capability:\;0: NO_correction_bypass\;1: RS-FEC_correction_bypass" access="RO" enum="NO_correction_bypass=0x0,RS=0x1" offset="0x10.28" size="0x0.4" />
	<field name="fec_override_admin_10g_40g" descr="10GE/40GE Ethernet FEC override admin, see 10g_40g_fec_override_cap.\;(one-hot setting): \;0: auto_mode - no override\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;\;" access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2" offset="0x14.0" size="0x0.4" />
	<field name="fec_override_admin_25g" descr="25GE Ethernet FEC override admin, see 25g_fec_override_cap. (one-hot setting): \;0: auto_mode - no override\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;Bit 2: RS-FEC\;\;Note - 25g_fec_override_admin and 50g_fec_override_admin must be set with the same value." access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2,RS=0x4" offset="0x14.4" size="0x0.4" />
	<field name="fec_override_admin_50g" descr="50GE Ethernet FEC override admin, see 50g_fec_override_cap. (one-hot setting): \;0: auto_mode - no override\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;Bit 2: RS-FEC\;\;Note - 25g_fec_override_admin and 50g_fec_override_admin must be set with the same value." access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2,RS=0x4" offset="0x14.8" size="0x0.4" />
	<field name="fec_override_admin_100g" descr="100GE Ethernet FEC override admin, see 100g_fec_override_cap. (one-hot setting): \;0: auto_mode - no override\;Bit 0: No_FEC\;Bit 2: RS-FEC" access="RW" enum="No_FEC=0x1,RS=0x4" offset="0x14.12" size="0x0.4" />
	<field name="fec_override_admin_56g" descr="56GE Ethernet FEC override admin, see 56g_fec_override_cap. (one-hot setting): \;0: auto_mode - no override\;Bit 0: No_FEC\;Bit 1: Firecode_FEC" access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2" offset="0x14.16" size="0x0.4" />
	<field name="rs_fec_correction_bypass_admin" descr="RS-FEC correction bypass override admin: (one-hot setting): \;0: auto_mode - no override \;1: NO_correction_bypass\;2: RS-FEC_correction_bypass" access="RW" enum="auto_mode=0x0,NO_correction_bypass=0x1,RS=0x2" offset="0x14.28" size="0x0.4" />
	<field name="fec_override_cap_200g_4x" descr="200GE FEC override capability bitmask:\;Bit 8: Zero_Latency_FEC\;Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1\;Others bits reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x18.0" size="0x0.16" />
	<field name="fec_override_cap_400g_8x" descr="400GE FEC override capability bitmask:\;Bit 8: Zero_Latency_FEC\;Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1\;All others are reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x18.16" size="0x0.16" />
	<field name="fec_override_cap_50g_1x" descr="50GE single lane override capability bitmask:\;Bit 8: Zero_Latency_FEC\;Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1\;All others are reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x1C.0" size="0x0.16" />
	<field name="fec_override_cap_100g_2x" descr="100GE over 2 lanes, FEC override capability bitmask:\;Bit 8: Zero_Latency_FEC\;Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1\;All others are reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x1C.16" size="0x0.16" />
	<field name="fec_override_admin_200g_4x" descr="200GE FEC override admin bitmask (one-hot setting) \;0: Auto_mode\;Bit 7: RS_FEC_544_514 - (544,514)\;Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x20.0" size="0x0.16" />
	<field name="fec_override_admin_400g_8x" descr="400GE FEC override admin bitmast (one-hot setting): \;0: Auto_mode\;Bit7: RS_FEC_544_514\;Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x20.16" size="0x0.16" />
	<field name="fec_override_admin_50g_1x" descr="50GE, 1lanes FEC override admin bitmask (one-hot setting)\;0: Auto_mode\;Bit 7: RS_FEC_544_514 - (544,514)\;Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x24.0" size="0x0.16" />
	<field name="fec_override_admin_100g_2x" descr="100GE, 2 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 7: RS_FEC_544_514 - (544,514)\;Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x24.16" size="0x0.16" />
	<field name="fec_override_cap_400g_4x" descr="400GE, 4 lanes FEC override capability bitmask:\;Bit 7: RS_FEC_544_514 - (544,514)\;Bit 9: Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1 - (272,257+1)\;Other bits Reserved" access="RO" enum="RS_FEC_544_514=0x80,Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x200" offset="0x28.0" size="0x0.16" />
	<field name="fec_override_cap_800g_8x" descr="800GE, 8 lanes FEC override capability bitmask:\;Bit 7: RS_FEC_544_514 - RS-FEC (544,514)\;Bit 8: Reserved\;Bit 9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;Other bits Reserved" access="RO" enum="RS_FEC_544_514=0x80,Reserved=0x100,Ethernet_Consortium_LL_50G_RS_FEC=0x200" offset="0x28.16" size="0x0.16" />
	<field name="fec_override_cap_100g_1x" descr="100GE, 1 lane FEC override capability bitmask:\;Bit 6: Interleaved_RS_FEC_544_514\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1\;Bit 10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1\;Other bits reserved" access="RO" enum="Interleaved_RS_FEC_544_514=0x40,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1=0x200,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x400" offset="0x2C.0" size="0x0.16" />
	<field name="fec_override_cap_200g_2x" descr="200GE, 2 lanes FEC override capability bitmask:\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1\;Other bits Reserved" access="RO" enum="RS_FEC_544_514=0x80,Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x200" offset="0x2C.16" size="0x0.16" />
	<field name="fec_override_admin_400g_4x" descr="400GE, 4 lanes FEC override admin bitmask (one-hot setting):\;Bit 0: Auto_mode\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1\;Other bits Reserved" access="RW" enum="Auto_mode=0x1,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1=0x200" offset="0x44.0" size="0x0.16" />
	<field name="fec_override_admin_800g_8x" descr="800GE, 8 lanes FEC override admin bitmask (one-hot setting):\;Bit 0: Auto_mode\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1\;Other bits Reserved" access="RW" enum="Auto_mode=0x1,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1=0x200" offset="0x44.16" size="0x0.16" />
	<field name="fec_override_admin_100g_1x" descr="100GE, 1 lane FEC override admin bitmask (one-hot setting):\;Bit 0: Auto_mode\;Bit 6: Interleaved_RS_FEC_544_514\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_50G_Low_Latency_RS_FEC_272_257_plus_1\;Bit 10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1\;Other bits Reserved" access="RW" enum="Auto_mode=0x1,Interleaved_RS_FEC_544_514=0x40,RS_FEC_544_514=0x80,Ethernet_Consortium_50G_Low_Latency_RS_FEC_272_257_plus_1=0x200,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x400" offset="0x48.0" size="0x0.16" />
	<field name="fec_override_admin_200g_2x" descr="200GE, 2 lanes FEC override admin bitmask (one-hot setting):\;Bit 0: Auto_mode\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1\;Other bits Reserved" access="RW" enum="Auto_mode=0x1,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1=0x200" offset="0x48.16" size="0x0.16" />
</node>

<node name="pplr_reg_ext" descr="" size="0x8.0" >
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: Near-End_Port- (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: Far-End_Port - (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" enum="Network_Port=0x0,Near=0x1,Internal_IC_LR_Port=0x2,Far=0x3" offset="0x0.4" size="0x0.4" />
	<field name="op_mod" descr="operational mode for link configurations for phy_ local_loopback mode.\;0 - link will operate in optimal latency performance mode\;1 - link will operate in same configurations as operational port.\;\;Note: for FEC override via PPLM register, chosen FEC will be according to the PPLM configuration that was set and this bit will be ignored for FEC purposes" access="OP" offset="0x0.8" size="0x0.1" />
	<field name="apply_im" descr="Apply immediate: When set, the enabled/disabled loopback will be set immediately even if link is active.\;Note: Currently supported only for Bit 7: LL_local_loopback. in other loopbacks will be ignored" access="OP" offset="0x0.9" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lb_en" descr="Loopback enable - One-hot key.\;Bit 0: Phy_remote_loopback\;Bit 1: Phy_local_loopback\;Bit 2: External_local_loopback\;Bit 7: LL_local_loopback\;\;\;" access="RW" enum="Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4,LL_local_loopback=0x80" offset="0x4.0" size="0x0.12" />
	<field name="lb_cap" descr="Loopback capability - bitmask\;Bit 0: Phy_remote_loopback\;Bit 1: Phy_local_loopback - When set the port&apos;s egress traffic is looped back to the receiver and the port transmitter is disabled.\;Bit 2: External_local_loopback - Enables the port&apos;s transmitter to link with the port&apos;s receiver using an external loopback connector.\;Bit 4: Near_end_digital_loopback - [Internal]\;Bit 7: LL_local_loopback - When set the port&apos;s egress Link layer traffic is looped back to the receiver. Physical port in this loopback mode is down.\;\;Note - Phy remote loopback can be supported only for lane rate higher than 25Gbuad in the 16nm devices.\;\;In Ethernet, when LL_Local_loopback is set and physical link is not down, physical state may reach only up to Phy Up state and forced to send Local Faults. When released link may transition to LinkUp state" access="RO" enum="Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4,LL_local_loopback=0x80" offset="0x4.16" size="0x0.12" />
</node>

<node name="pprt_reg_ext" descr="" size="0x24.0" >
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):\;0 - No per lane configuration\;1 - Per lane configurations\;When le is cleared, lane index is reserved and all PPRT configurations are taking place on all lanes.\;When le is set, configurations are taking place per lane based on lane index\;Affects lane indexing for set operations only, ignored for get operations." access="OP" offset="0x0.0" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support: \;0 - No support of per lane configuration\;1 - Support of per lane configuration" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="port_type" descr="Supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;Other values are reserved.\;" access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Reserved when (le=0 or ls = 0)\;Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sw_c" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols support\;if this bit is cleared - bit 25 (&apos;s&apos;) is ignored" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="sw" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols\;0 - No Swap.\;1 - Swap MSB &lt;-&gt; LSB." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dm_ig" descr="disable mask ignore\;If set to 1, the port&quot;s and the cable&quot;s capabilities won&quot;t affect tuning" access="OP" offset="0x0.26" size="0x0.1" />
	<field name="p_c" descr="PRBS RX polarity support indication\;if this bit is cleared - bit 28 (&apos;p&apos;) is ignored" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="p" descr="PRBS RX polarity - NOT gate in PRBS (not Physical lane Polarity)\;\;0 - No polarity inversion.\;1 - PRBS RX polarity inversion." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="tun_ovr" descr="" access="OP" offset="0x0.29" size="0x0.1" />
	<field name="s" descr="start tuning:\;1 - start RX_tuning based on PRBS pattern \;Note: assuming peer transmitting PRBS. \;cannot be set when prbs_rx_tuning_status = 1 (during tuning)" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:\;0 - PRBS RX is disabled.\;1 - PRBS RX is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23A (x^23 + x^18 + 1)\;Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)\;Bit 13 - Square_wave : Non error based tune\;Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;Bit 21- SSPR\;Bit 22- SSPRQ\;Bit 23- LT frames (KR-startup frames)\;Bit 24 - PRBS15 - x^15 + x^14 + 1\;Bit 25 - PRBS28 - x^28 + x^25 + 1\;Bit 26 - Square wave3 (3ones, 3zeros)\;Bit 27 - Square wave13 (13ones, 13zeros)\;Bit 28 - Square wave30 (30ones, 30zeros)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 13):\;0 - NRZ test pattern\;1 - PAM4 encoding [interlnal] with gray no precoding\;2 - PAM4 with precoding [internal] with gray\;3 - PAM4 without gray no precoding\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23A (x^23 + x^18 + 1)\;0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0xC - IDLEs using scramble58 (x^58+ x^39 + 1)\;0xD - Square_wave : Non error based tune \;0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;0x15 - SSPR\;0x16 - SSPRQ\;0x17 - LT frames (KR-startup frames)\;0x18 - PRBS15 - x^15 + x^14 + 1\;0x19 - PRBS28 - x^28 + x^25 + 1\;0x1A - Square wave3 (3ones, 3zeros)\;0x1B - Square wave13 (13ones, 13zeros)\;0x1C - Square wave30 (30ones, 30zeros)" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) \;Bit 2 - XAUI/2.5GE (3.125 Gb/s)\;Bit 3- DDR (5 Gb/s) \;Bit 4- QDR (10 Gb/s) \;Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) \;Bit 6- FDR (14.0625 Gb/s) \;Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 8 - 50GE-KR4 (12.89 Gb/s) \;Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) \;Bit 10 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;Bit 11 - XDR (106.25Gbd / 212.5Gb/s)" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="lane_rate_oper" descr="Lane rate to be used in PRBS, see lane_rate_cap:\;0 - SDR (2.5 Gb/s)\;1 - DDR (5 Gb/s) \;2 - QDR (10 Gb/s)\;3 - FDR10 / 10GE/4 0GE (10.3125 Gb/s)\;4 - FDR (14.0625 Gb/s) \;5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)\;6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s) \;8 - XDR (106.25Gbd / 212.5Gb/s)\;9 - reserved\;10 - 1GE (1.25 Gb/s)\;11 - XAUI/2.5GE (3.125 Gb/s)\;12 - 50GE-KR4 (12.89 Gb/s) \;\;Note: All lanes must be set to the same rate" access="RW" offset="0x10.16" size="0x0.16" />
	<field name="prbs_lock_status_ext" descr="PRBS lock on PRBS pattern status for lanes 7-4: \;0 - Not locked\;1 - Locked\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0 (Not locked)" access="RO" offset="0x14.20" size="0x0.4" />
	<field name="prbs_lock_status" descr="PRBS lock on PRBS pattern status for lanes 3-0: \;0 - Not locked\;1 - Locked\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0 (Not locked)" access="RO" offset="0x14.24" size="0x0.4" />
	<field name="prbs_rx_tuning_status" descr="Tuning status: \;0 - PRBS mode tuning was not performed.\;1 - Performing PRBS mode tuning.\;2 - PRBS mode tuning completed.\;3 - Signal Detect in progress\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0." access="RO" offset="0x14.28" size="0x0.4" />
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
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sw_c" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols support\;if this bit is cleared - bit 25 (&apos;s&apos;) is ignored" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="sw" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols\;0 - No Swap.\;1 - Swap MSB &lt;-&gt; LSB." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dm_ig" descr="disable mask ignore\;If set to 1, the port&quot;s and the cable&quot;s capabilities won&quot;t affect tuning" access="OP" offset="0x0.26" size="0x0.1" />
	<field name="p_c" descr="PRBS TX polarity support indication.\;if this bit is cleared - bit 28 (&apos;p&apos;) is been ignored" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="p" descr="PRBS TX polarity - NOT gate in PRBS (not Physical lane Polarity)\;0 - No polarity inversion.\;1 - PRBS TX polarity inversion." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:\;0 - PRBS TX is disabled.\;1 - PRBS TX is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23A (x^23 + x^18 + 1)\;Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)\;Bit 13 - Square_wave8 (8 ones , 8 zeros)\;Bit 14 - Square_wave4 (4 ones , 4zeros)\;Bit 15 - Square_wave2 (2 ones , 2zeros)\;Bit 16 - Square_wave1 (one , zero)\;Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;Bit 21- SSPR\;Bit 22- SSPRQ\;Bit 23- LT frames (KR-startup frames)\;Bit 24 - PRBS15 - x^15 + x^14 + 1\;Bit 25 - PRBS28 - x^28 + x^25 + 1\;Bit 26 - Square wave3 (3ones, 3zeros)\;Bit 27 - Square wave13 (13ones, 13zeros)\;Bit 28 - Square wave30 (30ones, 30zeros)\;Bit 29 - PRBS58 (x^58+ x^39 + 1)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 13):\;0 - NRZ test pattern\;1 - PAM4 encoding [interlnal] with gray no precoding\;2 - PAM4 with precoding [internal] with gray\;3 - PAM4 without gray no precoding\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23A (x^23 + x^18 + 1)\;0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0xC - IDLEs using scramble58 (x^58+ x^39 + 1)\;0xD - Square_wave8 (8 ones , 8 zeros)\;0xE - Square_wave4 (4 ones , 4zeros)\;0xF - Square_wave2 (2 ones , 2zeros)\;0x10 - Square_wave1 (one , zero)\;0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;0x15 - SSPR\;0x16 - SSPRQ\;0x17 - LT frames (KR-startup frames)\;0x18 - PRBS15 - x^15 + x^14 + 1\;0x19 - PRBS28 - x^28 + x^25 + 1\;0x1A - Square wave3 (3ones, 3zeros)\;0x1B - Square wave13 (13ones, 13zeros)\;0x1C - Square wave30 (30ones, 30zeros)\;0x1D - PRBS58 (x^58+ x^39 + 1)" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="prbs_fec_cap" descr="When set, PRBS over FEC is supported.\;Note: Feature is enabled on all lanes of port" access="RO" offset="0xC.0" size="0x0.1" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) \;Bit 2 - XAUI/2.5GE (3.125 Gb/s)\;Bit 3- DDR (5 Gb/s) \;Bit 4- QDR (10 Gb/s) \;Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) \;Bit 6- FDR (14.0625 Gb/s) \;Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 8 - 50GE-KR4 (12.89 Gb/s) \;Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) \;Bit 10 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;Bit 11 - XDR (106.25Gbd / 212.5Gb/s)\;" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="prbs_fec_admin" descr="When set, PRBS over FEC is enabled for port.\;For FEC configuration, set PPLM.test_mode" access="RW" offset="0x10.0" size="0x0.1" />
	<field name="lane_rate_admin" descr="Lane rate be used in PRBS, see lane_rate_cap:\;0 - SDR (2.5 Gb/s)\;1 - DDR (5 Gb/s) \;2 - QDR (10 Gb/s)\;3 - FDR10 / 10GE/40GE (10.3125 Gb/s)\;4 - FDR (14.0625 Gb/s) \;5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)\;6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;8 - XDR (106.25Gbd / 212.5Gb/s)\;9 - reserved\;10 - 1GE (1.25 Gb/s)\;11 - XAUI/2.5GE (3.125 Gb/s)\;12 - 50GE-KR4 (12.89 Gb/s)\;\;Note: All lanes must be set to the same rate" access="RW" offset="0x10.16" size="0x0.16" />
</node>

<node name="prei_reg_28nm_ext" descr="" size="0x8.0" >
	<field name="mixer_offset1" descr="eye centering control.\;may cause link degradation when set." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="mixer_offset0" descr="eye centering control.\;may cause link degradation when set." access="RW" offset="0x0.16" size="0x0.16" />
</node>

<node name="prei_reg_ext" descr="" size="0x18.0" >
	<field name="status" descr="Error injection status:  \;     0x0 -Good status \;     0x2 - No available sources for Error injection \;     0x3 - Error injection configuration when port is in non opera tional state (port is neither in UP or TEST MODE)" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="time_res" descr="0: 10ms" access="OP" offset="0x0.4" size="0x0.2" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="1 - 28nm products\;3 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="error_type_admin" descr="Error Type to generate \;0: No_Error ---- Physical Errors ---- \;Bit 0: mixer_offset_ctrl_set\; -" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilities  \;Bit 0: mixer_offset_ctrl\;" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="error_type_oper" descr="Error injection opertional status \; 0x0 - No error injection \; 0x1 - Performing error injection" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="error_injection_time" descr="Duration in time_res the port will generate errors. Reading this field will return the time left for errors to inject in msec.\;0x0000 indicates no generation of errors. \;0xFFFF - No decremental operation, meaning the  errors will be injected continuously without stop condition. \;" access="RW" offset="0x8.12" size="0x0.16" />
	<field name="page_data" descr="Table 1634, &quot;PREI - Port Receive Error Injection Register Layout for 28nm,&quot; on page 1925" subnode="prei_reg_28nm_ext" access="RW" offset="0x10.0" size="0x8.0" />
</node>

<node name="prtl_reg_ext" descr="" size="0x20.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;1: IB_port_number\;3: Out_of_band" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rtt_support" descr="Support of RTT measurement" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="latency_accuracy" descr="Latency measurement accuracy (i,e. max error size). \;accuracy is relative to specific device implementation. \;This field returns the accuracy in nsec resolution. \;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="latency_res" descr="Latency resolution in nsec of round_trip_latency \;" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="local_phy_latency" descr="Shall be 0 if not implemented (rtt_support = 0). \;This value represents the intra-ASIC pipeline latency of the physical layer. It is an unsigned 16-bit integer in nsec." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="local_mod_dp_latency" descr="Shall be 0 if not implemented (rtt_support = 0), if the module is not plugged in or if the information is not available on the plugged module. \;This value represents the module&apos;s Datapath pipeline latency.It It is an unsigned 16-bit integer in nsec." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="round_trip_latency" descr="Shall be 0 if not implemented (rtt_support = 0). \;This value represents a measurement of the round-trip latency of the link attached to this port. \;It is an unsigned 24-bit integer counting latency_res nsec. \;intervals. \;This value might not be accurate to better than +/- latency_accuracy nsec. \;A value of 0 is valid when implemented, and indicates a latency of up to latency_accuracy nsec. \;round_trip_latency is reset to 0xFFFFFF whenever this port transitions to PAOS.Oper_status = Down." access="RO" offset="0x10.0" size="0x0.24" />
</node>

<node name="pter_phy_page_reg_ext" descr="" size="0x1c.0" >
	<field name="error_type_admin" descr="Error Type to generate\;0 - No Error\;---- Physical Errors ----\;1 - Raw BER\;2 - Effective BER\;16 - PCS link fault" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilities \;Bit 0 - Raw BER\;Bit 1 - Effective BER\;\;Bit 4 - PCS link fault" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="error_type_oper" descr="Error injection opertional status\;0x0 - No error injection\;0x1 - Performing error injection" access="RO" offset="0x0.24" size="0x0.4" />
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
	<field name="page_data" descr="error injection page data: \;Table 1628, &quot;PTER- Port Transmit Errors Register Phy Level Layout,&quot; on page 1921\;Table 1630, &quot;PTER- Port Transmit Errors Register Port Level Fields,&quot; on page 1922" subnode="pter_reg_page_data_auto_ext" access="RW" offset="0x4.0" size="0x1c.0" union_selector="$(parent).error_page" />
</node>

<node name="pter_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x1c.0" >
	<field name="pter_phy_page_reg_ext" descr="" subnode="pter_phy_page_reg_ext" offset="0x0.0" selected_by="Injection_of_Phy_Errors" size="0x1c.0" />
	<field name="pter_port_page_reg_ext" descr="" subnode="pter_port_page_reg_ext" offset="0x0.0" selected_by="Injection_of_Port_Errors" size="0x1c.0" />
</node>

<node name="ptys_reg_ext" descr="" size="0x44.0" >
	<field name="proto_mask" descr="Protocol Mask. Indicates which of the protocol data is valid\;Bit 0: InfiniBand\;Bit 2: Ethernet" access="INDEX" enum="InfiniBand=0x1,Ethernet=0x4" offset="0x0.0" size="0x0.3" />
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
	<field name="ext_eth_proto_capability" descr="For HCA: See also PCAM.feature_cap_mask bit 13 for Extended Ethernet protocol support.\;Extended Ethernet port speed/protocols supported (bitmask):\;Bit 0: SGMII_100M\;Bit 1: 1000BASE-X / SGMII\;Bit 3: 5GBASE-R\;Bit 4: XFI / XAUI-1 // 10G\;Bit 5: XLAUI-4/XLPPI-4 // 40G \;Bit 6: 25GAUI-1/ 25GBASE-CR / KR \;Bit 7: 50GAUI-2 / LAUI-2/ 50GBASE-CR2/KR2 \;Bit 8: 50GAUI-1 /50GBASE-CR / KR\;Bit 9: CAUI-4 / 100GBASE-CR4 / KR4\;Bit 10: 100GAUI-2 / 100GBASE-CR2 / KR2 \;Bit 11: 100GAUI-1 / 100GBASE-CR / KR\;Bit 12: 200GAUI-4 / 200GBASE-CR4/KR4\;Bit 13: 200GAUI-2 / 200GBASE-CR2/KR2\;Bit 14: Reserved [internal] Placeholder for 200GAUI-1\;Bit 15: 400GAUI-8/ 400GBASE-CR8\;Bit 16: 400GAUI-4/ 400GBASE-CR4\;Bit 17: Reserved [internal] Placeholder for 400GAUI-2\;Bit 18: Reserved [internal] Placeholder for 400GAUI-1\;Bit 19: 800GAUI-8 / 800GBASE-CR8 / KR8\;Bit 31: SGMII_10M\;Other - Reserved" access="RO" offset="0x8.0" size="0x4.0" />
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
	<field name="element_hierarchy" descr="The hierarchy of the element\;0: Port- host\;1: Group\;2: Sub_Group - subgroup of queues. Supported from ConnectX-8/BlueField-4\;3: Traffic_Class- VoQ queue" access="INDEX" enum="Port=0x0,Group=0x1,Sub_Group=0x2,Traffic_Class=0x3" offset="0x4.16" size="0x0.4" />
	<field name="next_element_index" descr="The index of the element in the lower hierarchy.\;reserved when element_heirarchy  &apos;0&apos;" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="max_shaper_rate" descr="Max shaper information rate\;\;Value of 0x7FFF_FFFF means &quot;all allowed&quot; or &quot;shaper disabled&quot;\;Supported according to QCAM features" access="RW" offset="0x10.0" size="0x0.31" />
	<field name="mase" descr="Max shaper configuration enable. Enables configuration of max_shaper_rate, max_shaper_bs on this ETS element\;0: disable\;1: enable\;Reserved when element_hierarchy is 1\;Supported according to QCAM features" access="RW" enum="disable=0x0,enable=0x1" offset="0x10.31" size="0x0.1" />
	<field name="dwrr_weight" descr="dwrr weight on the link going down from the ETS element:\;The percentage of bandwidth guaranteed to a ETS within its hierarchy.\;The sum of dwrr_weight value across all ETS elements within one hierarchy should equal 100.\;This field is reserved when dwrr is strict priority.\;Supported according to QCAM features" access="RW" offset="0x18.0" size="0x0.8" />
	<field name="dwrr" descr="dwrr or strict priority on the link going down from the ETS element:\;0: strict priority\;1: DWRR" access="RW" offset="0x18.15" size="0x0.1" />
	<field name="de" descr="DWRR configuration enable. Enables configuration of the dwrr and dwrr_weight.\;0: disable\;1: enable\;Supported according to QCAM features" access="RW" offset="0x18.31" size="0x0.1" />
</node>

<node name="qetcr_ext" descr="" size="0x50.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cap_remote_admin" descr="Indicates if operation_type==remote_admin_parameters is supported\;NIC only, Reserved for Switches" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="cap_local_admin" descr="Indicates if operation_type==local_admin_parameters is supported\;NIC only, Reserved for Switches" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="operation_type" descr="Operation type.\;0x0: local operative parameters.\;0x1: local admin parameters. Supported only when cap_local_admin==1.\;0x2: remote admin parameters. Supported only when cap_remote_admin==1. \;NIC only, Reserved for Switches" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="tc_configuration" descr="Per-tclass configuration. For details, refer to Table 981, &quot;ETS tcN Configuration Register Layout&quot;." subnode="ets_ext" access="RW" high_bound="7" low_bound="0" offset="0x8.0" size="0x40.0" />
	<field name="global_configuration" descr="Global configuration. For details, refer to Table 983, &quot;ETS Global Configuration Register Layout&quot;.\;Reserved for NICs" subnode="ets_global_ext" access="RW" offset="0x48.0" size="0x8.0" />
</node>

<node name="qhll_ext" descr="" size="0xc.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port\;" access="INDEX" offset="0x0.16" size="0x0.8" />
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
	<field name="dscp" descr="DSCP entry is the DSCP to Switch Priority mapping. For more details refer to Table  977, &quot;qpdpm_dscp Layout,&quot; on page  1274" access="RW" high_bound="63" low_bound="0" offset="0x4.16" size="0x80.0" />
</node>

<node name="qprt_ext" descr="" size="0x8.0" >
	<field name="pcp" descr="Packet&apos;s PCP value" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="dei" descr="Packet&apos;s DEI value.\;when" access="INDEX" offset="0x0.11" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port.\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rprio" descr="For SwitchX/-2: Regeneration Priority.\;For Spectrum family: Switch Priority\;The default value for the table is: PCP i -&gt;Regeneration Priority i\; For NIC devices only 8 priorities are supported" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="color" descr="Packet Color.\;0: GREEN\;1: YELLOW\;2: RED\;For Switch only, Reserved for NICs" access="RW" enum="GREEN=0x0,YELLOW=0x1,RED=0x2" offset="0x4.8" size="0x0.2" />
</node>

<node name="qpts_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local Port\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="trust_state" descr="0: TRUST_PORT - reserved for NIC devices\;1: TRUST_PCP - default\;2: TRUST_DSCP\;3: TRUST_BOTH - For NIC devices suported only when QCAM.QPTS_TRUST_BOTH == 1" access="RW" enum="TRUST_PCP=0x1,TRUST_DSCP=0x2,TRUST_BOTH=0x3" offset="0x4.0" size="0x0.3" />
</node>

<node name="qshr_ext" descr="" size="0x50.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fr" descr="Fast Response - the device will shape the rate to its minimum value upon receive of WQE LWM (Low WaterMark) event \;0: disable\;1: enable" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="ch" descr="Connected host:\;0: The configuration will be applied on the host calling QSHR. \;1: The configuration will be applied on the host connected to the function calling the QSHR." access="INDEX" offset="0x0.27" size="0x0.1" />
	<field name="global_configuration" descr="Global configuration. For details, refer to Table 983, &quot;ETS Global Configuration Register Layout&quot;.\;On get, the actual returned values can differ from the set values." subnode="ets_global_ext" access="RW" offset="0x48.0" size="0x8.0" />
</node>

<node name="qspcp_ext" descr="" size="0xc.0" >
	<field name="switch_prio" descr="Switch Priority entry form mapping to Counting Priority.\;[DWIP] Switch Priority 15 maps for control packets (mapped to counting priority 7 by default).\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port\;No support for CPU port\;No support for router port\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rx_counting_prio" descr="The Rx Counting Priority value for the relevant Switch Priority value.\;default: \;for i=[0..7]: switch_prio i: rx_counting_prio i\;for i=[8..15]: switch_prio i: rx_counting_prio (i-8)" access="RW" offset="0x4.0" size="0x0.3" />
	<field name="tx_counting_prio" descr="The Tx Counting Priority value for the relevant Switch Priority value.\;default: \;for i=[0..7]: switch_prio i: tx_counting_prio i\;for i=[8..15]: switch_prio i: tx_counting_prio (i-8)\;[Spectrum2] This field is reserved when QGCR.tx_cnt_tclass is set" access="RW" offset="0x8.0" size="0x0.3" />
</node>

<node name="qspip_ext" descr="" size="0x8.0" >
	<field name="switch_prio" descr="Switch Priority entry form mapping to IEEE Priority" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="ieee_prio" descr="The new IEEE Priority value for the relevant Switch Priority value.\;default: \;for i=[0..7]: switch_prio i: ieee_prio i\;for i=[8..15]: switch_prio i: ieee_prio (i-8)\;Note: Different switch_prio values assigned to a given buffer (see PPTB) may be assigned to different ieee_prio values." access="RW" offset="0x4.0" size="0x0.3" />
</node>

<node name="qtct_ext" descr="" size="0x8.0" >
	<field name="switch_prio" descr="Switch Priority" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number (transmit port)\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cap_remote_admin" descr="Indicates if operation_type==remote_admin_parameters is supported.\;For NIC only, Reserved when Switches" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="cap_local_admin" descr="Indicates if operation_type==local_admin_parameters is supported\;For NIC only, Reserved when Switches" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="operation_type" descr="Operation type.\;0x0: local_operative_parameters\;0x1: local_admin_parameters - Supported only when cap_local_admin==1\;0x2: remote_admin_parameters- Supported only when cap_remote_admin==1\;For NIC only, Reserved when Switches" access="INDEX" enum="local_operative_parameters=0x0,local_admin_parameters=0x1,remote_admin_parameters=0x2" offset="0x0.30" size="0x0.2" />
	<field name="tclass" descr="Traffic Class\;Default values are: \;- switch_prio=0: tclass=1 \;- switch_prio=1: tclass=0\;- switch_prio&gt;1: tclass = switch_prio\;\;When MC aware mode is enabled, setting values greater or equal to (cap_max_tclass_data)/2) is not allowed" access="RW" offset="0x4.0" size="0x0.4" />
</node>

<node name="register_host_endianness_ext" descr="" size="0x10.0" >
	<field name="he" descr="0: LITTLE_ENDIAN\;1: BIG_ENDIAN" access="RW" enum="LITTLE_ENDIAN=0x0,BIG_ENDIAN=0x1" offset="0x0.31" size="0x0.1" />
</node>

<node name="register_loopback_control_ext" descr="" size="0x10.0" >
	<field name="port" descr="Local port number" offset="0x0.16" size="0x0.8" />
	<field name="no_lb" descr="When set, the HCA will always send packets meant for the same port to wire, rather than perform internal loopback" offset="0x0.31" size="0x0.1" />
</node>

<node name="register_misc_counters_ext" descr="" size="0x20.0" >
	<field name="counter_select" descr="When performing a WRITE operation - , the counter select bitmask determines which registers are set:\;Bit 0 - ECC\;Bit 1 - LDB silent drop" offset="0x4.0" size="0x4.0" />
	<field name="ecc" descr="Counts number of arrays which encountered a bit error" offset="0xC.0" size="0x4.0" />
	<field name="ldb_silent_drop" descr="Counts number of packets silently dropped due to LDB error" offset="0x10.0" size="0x4.0" />
</node>

<node name="register_power_settings_ext" descr="" size="0x10.0" >
	<field name="power_settings_level" descr="0x0 - minimum power (maximum latency penalty)\;0x1-0xfe - reserved\;0xff - maximum power (minimum latency penalty)" access="RW" offset="0x0.0" size="0x0.8" />
</node>

<node name="register_unti_perf_global_ctrl_ext" descr="" size="0x10.0" >
	<field name="cmd" descr="0x0 - stop counting in all performance counters\;0x1 - start counting in all performance counters \;Otherwise - reserved" access="WO" offset="0x0.0" size="0x0.8" />
</node>

<node name="resource_dump_ext" descr="" size="0x100.0" >
	<field name="segment_type" descr="See Section 26.10, &quot;Resource Dump&quot;, on page 1663." access="INDEX" offset="0x0.0" size="0x0.16" />
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

<node name="roce_accl_reg_ext" descr="" size="0x40.0" >
	<field name="roce_adp_retrans_field_select" descr="In Query, indicates if roce_tx_windo mode is configurable.\;If set, indicates roce_tx_window_en field is valid." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="roce_tx_window_field_select" descr="In Query, indicates whether roce_tx_window mode is configurable.\;If set, indicates roce_tx_window_enfield is valid." access="RW" offset="0x0.1" size="0x0.1" />
	<field name="roce_slow_restart_field_select" descr="In Query, indicates whether roce_slow_restart mode is configurable.\;If set, indicates roce_slow_restart_en field is valid." access="RW" offset="0x0.2" size="0x0.1" />
	<field name="roce_slow_restart_idle_field_select" descr="In Query, indicates whether roce_slow_restart_idle mode is configurable. If set, indicates roce_slow_restart_idle_en field is valid" access="RW" offset="0x0.3" size="0x0.1" />
	<field name="min_ack_timeout_limit_disabled_field_select" descr="In Query, indicates whether min_ack_timeout_limit_disabled mode is configurable. If set, indicates min_ack_timeout_limit_disabled field is valid" access="RW" offset="0x0.4" size="0x0.1" />
	<field name="adaptive_routing_forced_en_field_select" descr="In Query, indicates whether adaptive_routing_forced mode is configurable. If set, indicates adaptive_routing_forced_en field is valid." access="RW" offset="0x0.5" size="0x0.1" />
	<field name="selective_repeat_forced_en_field_select" descr="In Query, indicates whether selective_repeat_forced mode is configurable. \;If set, indicates selective_repeat_forced_en field is valid" access="RW" offset="0x0.6" size="0x0.1" />
	<field name="dc_half_handshake_en_field_select" descr="In Query, indicates whether dc_half_handshake_en is supported. If set, indicates selective_repeat_forced_en field is valid" access="RW" offset="0x0.7" size="0x0.1" />
	<field name="ack_dscp_force_field_select" descr="In query, indicates whether force ack DSCP mode is configurable. if set, indicates ack_dscp and ack_dscp_force fields are valid." access="RW" offset="0x0.9" size="0x0.1" />
	<field name="roce_adp_retrans_en" descr="If set, the adaptive retransmission window functionality is enabled.\;Valid only when roce_adp_retrans_field_select == 1." access="RW" offset="0x4.0" size="0x0.1" />
	<field name="roce_tx_window_en" descr="If set, the Transmission window functionality is enabled. \;Valid only when roce_tx_window_field_select == 1." access="RW" offset="0x4.1" size="0x0.1" />
	<field name="roce_slow_restart_en" descr="If set, the Slow restart functionality is enabled.\;When used, slow restart is initiated when congestion is identified on the network.\;Valid only when roce_slow_restart_field_select == 1." access="RW" offset="0x4.2" size="0x0.1" />
	<field name="roce_slow_restart_idle_en" descr="If set, the Slow restart after idle functionality is enabled. When used, slow restart is initiated when qp was idling. Valid only when roce_slow_restart_idle_field_select ==1" access="RW" offset="0x4.3" size="0x0.1" />
	<field name="min_ack_timeout_limit_disabled" descr="If set, min_ack_timeout_limit enforcement is disabled. \;Valid only when min_ack_timeout_limit_disabled_field_select ==1" access="RW" offset="0x4.4" size="0x0.1" />
	<field name="adaptive_routing_forced_en" descr="If adaptive_routing_forced_en = 1, all the QPs will be created with adaptive_routing enabled. \;If adaptive_routing_forced_en = 0, all the QPs will be created with adaptive_routing disabled. \;Valid only when adaptive_routing_forced_en_field_select ==1." access="RW" offset="0x4.5" size="0x0.1" />
	<field name="selective_repeat_forced_en" descr="If selective_repeat_forced_en= 1, all the QPs will be created with selective_repeat enabled. \;If selective_repeat_forced_en= 0, all the QPs will be created with selective_repeat disabled. \;Valid only when selective_repeat_forced_en_field_select ==1." access="RW" offset="0x4.6" size="0x0.1" />
	<field name="dc_half_handshake_en" descr="If dc_half_handshake_en = 1, all the QPs will be created with default half handshake. The full_handshake bit in QP context can override this setting. Valid only when dc_half_handshake_en_field_select ==1" access="RW" offset="0x4.7" size="0x0.1" />
	<field name="ack_dscp_force" descr="If set, force DSCP value from ack_dscp field. valid only when ack_dscp_force_field_select == 1" access="RW" offset="0x4.9" size="0x0.1" />
	<field name="ack_dscp" descr="The DSCP value for ack packets on NP when ack_dscp_force is set. valid only when ack_dscp_force_field_select == 1" access="RW" offset="0x4.10" size="0x0.6" />
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
	<field name="dir" descr="Direction\;0: Ingress port quota\;1: Egress port quota" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="pg_buff" descr="PG buffer - Port PG (dir=ingress) / traffic class (dir=egress)\;For PG buffer: range is 0..cap_max_pg_buffers - 1\;For traffic class: range is 0..cap_max_tclass_sb - 1\;For  traffic class to CPU port: range is 0..cap_max_cpu_ingress_tclass_sb - 1\;For traffic class to BMC port: range is 0..cap_max_bmc_tc_sb - 1\;" access="INDEX" offset="0x0.8" size="0x0.6" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;2: Host_port_number" access="INDEX" enum="Local_port_number=0x0,Host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will NACK the command\;" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;For NIC: Supported when descriptors_cap is set" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="exc" descr="Exclude - no accounting in the pool\;0: the tclass is accounted in the pool (default)\;1: the tclass is not accounted in the pool\;For NIC: Supported when descriptors_cap is set\;" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="buff_occupancy" descr="Current buffer occupancy\;This includes cells at the pool and at the min_buff" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. \;This includes cells at the pool and at the min_buff\;Cleared by writing to the clr field" access="RO" offset="0x14.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is cleared (and a new max value is tracked from the time the clear was performed)" access="OP" offset="0x14.31" size="0x0.1" />
	<field name="min_buff" descr="Minimum buffer size for the limiter\;The minimum buffer is not part of the pool area.\;Units of cells" access="RW" offset="0x18.0" size="0x0.24" />
	<field name="max_buff" descr="The maximum buffer threshold in the pool area.\;When the pool that is associated to the port-pg/tclass is configured to static, then max_buff is configured in cells\;When the pool that is associated to the port-pg/tclass is configured to dynamic, then max_buff holds the &quot;alpha&quot; parameter, supporting the following values:\;0 : 0\;i : (1/128)*2^(i-1), for i=1..14\;0xFF: Infinity\;Reserved when infi_max = 1\;" access="RW" offset="0x1C.0" size="0x0.24" />
	<field name="infi_max" descr="Max buffer is infinite\;When set, the max_buff field is reserved" access="RW" offset="0x1C.31" size="0x0.1" />
	<field name="pool" descr="Association of the port-priority to a pool\;Range 0 .. cap_num_pool_supported - 1\;" access="RW" offset="0x24.0" size="0x0.4" />
</node>

<node name="sbpm_ext" descr="" size="0x20.0" >
	<field name="dir" descr="Direction\;0: Ingress port quota\;1: Egress port quota" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="pool" descr="The pool associated to quota counting on the local_port\;Range 0 .. cap_num_pool_supported - 1\;" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;2: Host_port_number" access="INDEX" enum="Local_port_number=0x0,Host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;For Ingress: excludes CPU port\;For Egress: includes CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will NACK the command\;" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;For NIC: Supported when descriptors_cap is set" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="buff_occupancy" descr="Current buffer occupancy of the port.pool \;This includes cells at the pool and at the min_buff" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. \;This includes cells at the pool and at the min_buff\;Cleared by writing to the clr field" access="RO" offset="0x14.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, max_buff_occupancy field is cleared (and a new max value is tracked from the time the clear was performed)" access="OP" offset="0x14.31" size="0x0.1" />
	<field name="min_buff" descr="Minimum buffer size\;The minimum buffer is not part of the pool area.\;Units of cells" access="RW" offset="0x18.0" size="0x0.24" />
	<field name="max_buff" descr="The maximum buffer threshold in the pool area.\;When the pool is configured to static, then max_buf is configured in cells.\;When the pool is configured to dynamic, then max_buff holds the &quot;alpha&quot; parameter, supporting the following values:\;0 : 0\;i : (1/128)*2^(i-1), for i=1..14\;0xFF: Infinity\;Reserved when infi_max = 1\;" access="RW" offset="0x1C.0" size="0x0.24" />
	<field name="infi_max" descr="Max buffer is infinite\;When set, the max_buff field is reserved" access="RW" offset="0x1C.31" size="0x0.1" />
</node>

<node name="sbpr_ext" descr="" size="0x18.0" >
	<field name="pool" descr="Pool index\;Range 0 .. cap_num_pool_supported - 1\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="dir" descr="Direction\;0: Ingress pools\;1: Egress pools" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will NACK the command\;" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;For Spectrum-1: Total 84960 descriptors\;For NIC: Supported when descriptors_cap is set" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="size" descr="Pool size in buffer cells\;Reserved when infi_size = 1\;" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="infi_size" descr="size is infinite\;When set, the size field is reserved" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="mode" descr="Pool quota calculation mode:\;0: Static\;1: Dynamic" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="buff_occupancy" descr="Current buffer occupancy" access="RO" offset="0xC.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. Cleared by writing to the clr field" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is cleared (and a new max value is tracked from the time the clear was performed)" access="OP" offset="0x10.31" size="0x0.1" />
	<field name="ext_buff_occupancy" descr="Extended current buffer occupancy\;Includes also all of the min_buff of the relevant PG buffer or traffic class associated to this pool\;Reserved when Spectrum-1, supported by Spectrum-2 and Quantum. Note: currenty not supported by Switch FW\;For NIC: Supported when ext_buff_occupancy_cap is set" access="RO" offset="0x14.0" size="0x0.24" />
</node>

<node name="sbsr_ext" descr="" size="0xfc.0" >
	<field name="ports" descr="Ports:\;0: read per pg_buff and/or tclass\;1: ports, read per port\;" access="INDEX" offset="0x0.0" size="0x0.1" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;2: Host_port_number" access="INDEX" enum="Local_port_number=0x0,Host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="snap" descr="Read the snapshot gauge\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will NACK the command\;" access="INDEX" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is cleared (and a new max value is tracked from the time the clear was performed)" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;For NIC: Supported when descriptors_cap is set" access="INDEX" offset="0x4.31" size="0x0.1" />
	<field name="ingress_port_mask" descr="Bit vector for all ingress network port.\;Indicates which of the ports (for which the relevant bit is set) are affected by the set operation. Configuration of any other port does not change." access="INDEX" high_bound="7" low_bound="0" offset="0x10.0" size="0x20.0" />
	<field name="pg_buff_mask" descr="Bit vector for all priority groups.\;Indicates which of the priorities (for which the relevant bit is set) are affected by the set operation. Configuration of any other priority does not change.\;Range is 0..cap_max_pg_buffers - 1\;Reserved when ports = 1" access="INDEX" offset="0x30.0" size="0x0.10" />
	<field name="egress_port_mask" descr="Bit vector for all egress network port.\;Indicates which of the ports (for which the relevant bit is set) are affected by the set operation. Configuration of any other port does not change." access="INDEX" high_bound="7" low_bound="0" offset="0x34.0" size="0x20.0" />
	<field name="tclass_mask" descr="Bit vector for all traffic classes.\;Indicates which of the traffic classes (for which the relevant bit is set) are affected by the set operation. Configuration of any other priority does not change.\;Range is 0..cap_max_tclass - 1\;For traffic class to CPU port: range is 0..cap_max_cpu_ingress_tclass- 1\;Reserved when ports = 1" subnode="uint64" access="INDEX" offset="0x54.0" size="0x8.0" />
	<field name="shared_buffer_status" descr="Shared Buffer Properties, see Table 2171, &quot;Shared Buffer Status Fields,&quot; on page 2523\;This field is a collection of all the statuses of the requested quotas, while i=0..min{requested quotas, cap_sbsr_stat_size-1}\;The ith status refers a quota as follows;\;The occurrences of the masked ingress quotas are written before the masked egress quotas.\;All the occurrences associated to port are written together from the smallest masked port index. In each port, the occurrences of the masked priority groups/ traffic classes are written from the lowest to the highest." subnode="shared_buffer_status_ext" access="RO" high_bound="19" low_bound="0" offset="0x5C.0" size="0xa0.0" />
</node>

<node name="set_node_in_ext" descr="" size="0x40.0" >
	<field name="node_description" descr="Text describing the node" access="RW" high_bound="15" low_bound="0" offset="0x0.0" size="0x40.0" />
</node>

<node name="shared_buffer_status_ext" descr="" size="0x8.0" >
	<field name="buff_occupancy" descr="Current buffer occupancy" access="RO" offset="0x0.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. Cleared by writing to the clr field" access="RO" offset="0x4.0" size="0x0.24" />
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
	<field name="measure_time" descr="max measure time in seconds for single eye diagram.\;0 - 10 sec\;1 - 30 sec\;2 - 60 sec\;3 - 90 sec\;4 - 120 sec\;5 - 240 sec\;6 - 480 sec\;7 - 600 sec\;8 - 900 sec\;9-15 reserved\;each tic measure time will be measure_time / (hight_dim x width_dim)" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="eye_diag_dim" descr="dimensions of eye scan matrix in the format of hight_dim x width_dim\;0 - 16x16 (256 err val)\;1 - 32x32 (1024 err val)\;2 - 32x64 (1024 err val)\;3 - 64x32 (2048 err val)" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="err_res_scale" descr="error res multiplier for err_res_base field\;0 - exponential scale\;1 - linear scale\;2-3 - reserved" access="RW" offset="0x4.27" size="0x0.2" />
	<field name="destructive_ctrl" descr="0 - non destructive scan\;1 - destructive scan\;Note: if non destructive scan is not supported this field is ignored and a destructive scan will be operated" access="RW" offset="0x4.29" size="0x0.1" />
	<field name="last_scan" descr="set to &apos;1&apos; when performing last eye scan for lane.\;For example: when scanning 3 eyes in the order of up, mid, down. field should be set when scanning down eye.\;If scanning only 1 eye, field should be set." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="en" descr="start eye scan" access="WO" offset="0x4.31" size="0x0.1" />
	<field name="page_data" descr="page data for index page_data_sel\;page 0 will contain info page data.\;Table 1918, &quot;SLRED - Serdes Lane Receive Eye Diagram Register Layout for info page,&quot; on page 2264\;the page data 1-7 will contain the err_val for each index in ascending order.\;Table 1920, &quot;SLRED - Serdes Lane Receive Eye Diagram Register Layout for page_data,&quot; on page 2266\;Each err_val[i] represents the bit errors of row floor(i / width_dim)\;and column i mod width_dim.\;Matrix is built starting from the left bottom corner.\;each err_val indicates the number of bit errors for one tick" subnode="slred_reg_page_data_auto_ext" access="RO" offset="0x8.0" size="0xa0.0" />
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
	<field name="grade" descr="" access="RO" offset="0x4.0" size="0x0.24" />
	<field name="grade_version" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="height_eo_neg" descr="Voltage offset from eye center to the negative side." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="height_eo_pos" descr="Voltage offset from eye center to the positive side." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="phase_eo_neg" descr="The offset from the eye center to the negative side." access="RO" offset="0x1C.0" size="0x0.8" />
	<field name="phase_eo_pos" descr="The offset from the eye center to the positive side." access="RO" offset="0x1C.16" size="0x0.8" />
</node>

<node name="slrg_5nm_ext" descr="" size="0x18.0" >
	<field name="fom_measurment" descr="Bitmask for measurement activation\;Bit 0 - Upper eye\;Bit 1 - Middle eye\;Bit 2 - Lower eye\;Bit 3- Composite eye\;Note: NRZ only Bit 3 is valid" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="initial_fom" descr="measured EOM status after FEQ.\;valid only when SLRG.status is &apos;1&apos;" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="fom_mode" descr="fom mode:\;FOM eye mode to search\;0x0: FOM_MODE_EYE_OPEN\;0x1: FOM_MODE_EYEO_SNR\;0x2: FOM_MODE_NORM_SNR\;0x3: FOM_MODE_EYE_LVLN\;0x4: FOM_MODE_EYE_LVLP\;0x5: FOM_MODE_THRES_NERR\;0x6: FOM_MODE_CDR_NERR\;0x7: FOM_MODE_CSDET_NERR\;0x8: FOM_MODE_MLSE_NERR\;0x9: FOM_MODE_SFEC_NERR\;\;\;" access="RW" enum="FOM_MODE_EYE_OPEN=0x0,FOM_MODE_EYEO_SNR=0x1,FOM_MODE_NORM_SNR=0x2,FOM_MODE_EYE_LVLN=0x3,FOM_MODE_EYE_LVLP=0x4,FOM_MODE_THRES_NERR=0x5,FOM_MODE_CDR_NERR=0x6,FOM_MODE_CSDET_NERR=0x7,FOM_MODE_MLSE_NERR=0x8,FOM_MODE_SFEC_NERR=0x9" offset="0x4.16" size="0x0.4" />
	<field name="upper_eye" descr="last measured EOM-FOM status of upper eye.\;valid only if fom_measurment bit &apos;0&apos; is set" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="last_fom" descr="last measured EOM-FOM status of composite eye.\;valid only if fom_measurment bit &apos;3&apos; is set" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="lower_eye" descr="last measured EOM-FOM status of lower eye.\;valid only if fom_measurment bit &apos;2&apos; is set" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="mid_eye" descr="last measured EOM-FOM status of middle eye.\;valid only if fom_measurment bit &apos;1&apos; is set" access="RO" offset="0xC.16" size="0x0.16" />
</node>

<node name="slrg_7nm_ext" descr="" size="0x18.0" >
	<field name="fom_measurment" descr="Bitmask for measurement activation\;Bit 0 - Upper eye\;Bit 1 - Middle eye\;Bit 2 - Lower eye\;Bit 3- Composite eye\;Note: NRZ only Bit 3 is valid" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="initial_fom" descr="measured EOM status after FEQ.\;valid only when SLRG.status is &apos;1&apos;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="fom_mode" descr="fom mode:\;FOM eye mode to search\;0x0: FOM_MODE_EYEC\;0x1: FOM_MODE_EYEO\;0x2: FOM_MODE_EYEM\;0x3: FOM_MODE_BER\;0x4:FOM_MODE_EYEC_VN\;0x5:FOM_MODE_EYEC_VP\;0x6:FOM_MODE_EYEM_VN\;0x7:FOM_MODE_EYEM_VP\;\;" access="RW" enum="FOM_MODE_EYEC=0x0,FOM_MODE_EYEO=0x1,FOM_MODE_EYEM=0x2,FOM_MODE_BER=0x3,FOM_MODE_EYEC_VN=0x4,FOM_MODE_EYEC_VP=0x5,FOM_MODE_EYEM_VN=0x6,FOM_MODE_EYEM_VP=0x7" offset="0x4.16" size="0x0.3" />
	<field name="lower_eye" descr="last measured EOM-FOM status of lower eye.\;valid only if fom_measurment bit &apos;2&apos; is set" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="mid_eye" descr="last measured EOM-FOM status of middle eye.\;valid only if fom_measurment bit &apos;1&apos; is set" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="upper_eye" descr="last measured EOM-FOM status of upper eye.\;valid only if fom_measurment bit &apos;0&apos; is set" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="last_fom" descr="last measured EOM-FOM status of composite eye.\;valid only if fom_measurment bit &apos;3&apos; is set" access="RO" offset="0x8.24" size="0x0.8" />
</node>

<node name="slrg_all_lanes_5nm_ext" descr="" size="0x14.0" >
	<field name="fom_mode" descr="FOM type measurement\;0: SNR - bit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="OP" offset="0x0.0" size="0x0.4" />
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
	<field name="all_lanes" descr="set 1 all lanes measurement page\;Supported if PCAM.feature_cap_mask bit 91 is set. \;Relevant only for 5nm\;0: per_lane_measurement\;1: all_lane_measurement" access="INDEX" enum="per_lane_measurement=0x0,all_lane_measurement=0x1" offset="0x0.1" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: NearEnd_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: FarEnd_Port - (For Retimer/Gearbox - Line side)\;\;" access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0 - Local port number\;1 - IB port number\;" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number.\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: prod_40nm\;1: prod_28nm\;3: prod_16nm\;4: prod_7nm\;5: prod_5nm" access="RO" enum="prod_40nm=0x0,prod_28nm=0x1,prod_16nm=0x3,prod_7nm=0x4,prod_5nm=0x5" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid\;1 - Valid\;" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="Table 1740, &quot;SLRG - Serdes Lane Receive Grade Register Layout for 40nm and 28nm,&quot; on page 2046\;Table 1742, &quot;SLRG - Serdes Lane Receive Grade Register Layout for 16nm,&quot; on page 2048\;Table 1744, &quot;SLRG - Serdes Lane Receive Grade Register Layout for 7nm,&quot; on page 2050\;Table 1746, &quot;SLRG - Serdes Lane Receive Grade Register Layout for 5nm,&quot; on page 2051\;Table 1754, &quot;SLRG all lanes FOM for 5nm- Layout,&quot; on page 2055" subnode="slrg_reg_page_data_auto_ext" access="RO" condition="$(parent).all_lanes" offset="0x4.0" size="0x24.0" />
</node>

<node name="slrg_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x24.0" >
	<field name="slrg_40nm_28nm_ext" descr="" subnode="slrg_40nm_28nm_ext" condition="($(parent).port_type == Network_Port AND ($(parent).version == prod_40nm | $(parent).version == prod_28nm)" offset="0x0.0" size="0x24.0" />
	<field name="slrg_16nm_ext" descr="" subnode="slrg_16nm_ext" condition="($(parent).port_type == Network_Port AND ($(parent).version == prod_16nm)" offset="0x0.0" size="0x24.0" />
	<field name="slrg_7nm_ext" descr="" subnode="slrg_7nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND (($(parent).version == prod_7nm)" offset="0x0.0" size="0x18.0" />
	<field name="slrg_5nm_ext" descr="" subnode="slrg_5nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm)" offset="0x0.0" size="0x18.0" />
	<field name="slrg_all_lanes_5nm_ext" descr="" subnode="slrg_all_lanes_5nm_ext" condition="($(parent).port_type == (Network_Port || $(parent).port_type == NearEnd_Port  || $(parent).port_type == FarEnd_Port) AND ( ($(parent).version == prod_5nm AND $(parent).all_lanes == all_lane_measurement))" offset="0x0.0" size="0x14.0" />
</node>

<node name="sltp_16nm_ext" descr="" size="0x48.0" >
	<field name="post_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or smaller.\;" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="main_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or smaller.\;" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="pre_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or smaller.\;" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="pre_2_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or smaller.\;" access="RW" offset="0x4.24" size="0x0.8" />
	<field name="ob_alev_out" descr="Output common mode. Values can be set in the range of (0-30)" access="RW" offset="0x8.0" size="0x0.5" />
	<field name="ob_amp" descr="Output amplitude. Values can be set in the range of (10-100)." access="RW" offset="0x8.8" size="0x0.7" />
	<field name="ob_m2lp" descr="MSB to LSB proportion. \;Values can be set between -10 to 50. \;\;MSB emphasis achieved when value is between -10 to -1 \;LSB emphasis achieved when value is between 1 to 50. \;When set to 0 - equal proportion." access="RW" offset="0x8.25" size="0x0.7" />
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;0: configuration_warning - taps values can&apos;t be set to serdes due to internal limitations. Actual TX configuration is modify internally with the same sum of taps weight.\;11: Illegal_ob_combination - ob_m2lp, ob_amp and ob_alev is in legal range each, but the total combination can&apos;t be set to serdes due to internal limitations, the Set command is ignored.\;12: Illegal_ob_m2lp\;13: Illegal_ob_amp\;14: Illegal_ob_alev_out\;15: Illegal_taps\;\;Bit 12-0 - Reserved /Unknown" access="RO" enum="configuration_warning=0x0,Illegal_ob_combination=0xb,Illegal_ob_m2lp=0xc,Illegal_ob_amp=0xd,Illegal_ob_alev_out=0xe,Illegal_taps=0xf" offset="0xC.16" size="0x0.16" />
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
	<field name="tap0" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="tap1" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x4.8" size="0x0.8" />
	<field name="tap2" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x4.16" size="0x0.8" />
	<field name="tap3" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="tap4" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x8.0" size="0x0.8" />
	<field name="tap5" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x8.8" size="0x0.8" />
	<field name="tap6" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x8.16" size="0x0.8" />
	<field name="tap7" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x8.24" size="0x0.8" />
	<field name="tap8" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0xC.0" size="0x0.8" />
	<field name="tap9" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0xC.8" size="0x0.8" />
	<field name="tap10" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0xC.16" size="0x0.8" />
	<field name="tap11" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;For 200G per lane 12 taps. taps0-3 -&gt; pre; tap4 -&gt; main tap; \;taps5-11 -&gt; post\;\;Valid values for taps:\;main [32,63]\;pre [-8,8]\;post [-8,8]\;\;for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )\;For 50G per lane 4 taps are used (no pre3)\;For 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0xC.24" size="0x0.8" />
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

<node name="sltp_reg_ext" descr="" size="0x4c.0" >
	<field name="c_db" descr="copy transmitter parameters to Data Base. \;" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: NearEnd_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: FarEnd_Port - (For Retimer/Gearbox - Line side)" access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3" offset="0x0.1" size="0x0.3" />
	<field name="lane_speed" descr="Reserved for PCIe.\;The lane speed for TX settings:\;0 - SDR / Gen1 (PCIe)\;1 - DDR / Gen2 (PCIe) / 5GBASE-R\;2 - QDR / Gen3 (PCIe)\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE) / Gen4 (PCIe)\;5 - EDR (25GE / 50GE / 100GE) / Gen5 (PCIe)\;6 - HDR (50GE / 200GE / 400GE)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;8 - XDR (106.25 Gbd / 212.5Gb/s)\;9 - Reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13-15 - Reserved" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="tx_policy" descr="Configures Tx parameter set policy\;0 - Tx parameters will be set according to best possible configuration chosen by the system\;1 - Tx parameters will be set according to Data Base only and will not be overridden by link training (e.g KR-Startup)" access="RW" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: prod_40nm\;1: prod_28nm\;3: prod_16nm\;4: prod_7nm\;5: prod_5nm" access="RO" enum="prod_40nm=0x0,prod_28nm=0x1,prod_16nm=0x3,prod_7nm=0x4,prod_5nm=0x5" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="Indicates that Tx setting readout is valid and active. In particular, for links that do AN/LT, valid will be set when link operational status is UP (PAOS.oper_status=0x1).\;For links without AN/LT, valid will be set when Tx is enabled.\;\;0 - Invalid\;1 - Valid\;\;Note: Get and Set operations can be set when status = invalid." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="page_data" descr="Table 1722, &quot;SLTP - Serdes Lane Transmit Parameters Register Layout for 28nm and 40nm,&quot; on page 2031\;Table 1724, &quot;SLTP - Serdes Lane Transmit Parameters Register Layout for 16nm,&quot; on page 2032\;Table 1728, &quot;SLTP - Serdes Lane Transmit Parameters Register Layout for 7nm,&quot; on page 2034\;Table 1732, &quot;SLTP - Serdes Lane Transmit Parameters Register Layout for 5nm,&quot; on page 2039" subnode="sltp_reg_page_data_auto_ext" access="RW" condition="$(parent).version" offset="0x4.0" size="0x48.0" />
</node>

<node name="sltp_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x48.0" >
	<field name="sltp_28nm_40nm_ext" descr="" subnode="sltp_28nm_40nm_ext" condition="($(parent).port_type == Network_Port) AND ($(parent).version == prod_40nm | $(parent).version == prod_28nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_16nm_ext" descr="" subnode="sltp_16nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version == prod_16nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_7nm_ext" descr="" subnode="sltp_7nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version == prod_7nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_5nm_ext" descr="" subnode="sltp_5nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm)" offset="0x0.0" size="0x48.0" />
</node>

<node name="sltpv2_lut_5nm_ext" descr="" size="0x108.0" >
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;Bit 0:LUT_value_is_out_of_range\;Bit 1: delay_0_invalid\;Bit 2: delay_1_invalid\;Bit 3: delay_2_invalid" access="RO" enum="delay_2_invalid=0x8" offset="0x0.0" size="0x0.16" />
	<field name="lut_sel" descr="0: LUT_1 - taps 0-1 (16 entries)\;1: LUT_2 - taps 2-5 (256 entries)\;2: LUT_3 - taps 6-8 (64 entries)\;3: LUT_4 - taps 9-11 (64 entries)" access="INDEX" enum="LUT_1=0x0,LUT_2=0x1,LUT_3=0x2,LUT_4=0x3" offset="0x0.20" size="0x0.4" />
	<field name="delay0" descr="relevant for LUT3 (taps6-8), LUT4 (taps9-11). ignore otherwise.\;even taps (6, 8. 10) can get even values\;odd taps (7, 9, 11) cam get odd values.\;" access="RW" offset="0x4.0" size="0x0.6" />
	<field name="delay1" descr="relevant for LUT3 (taps6-8), LUT4 (taps9-11). ignore otherwise.\;even taps (6, 8. 10) can get even values\;odd taps (7, 9, 11) cam get odd values.\;" access="RW" offset="0x4.6" size="0x0.6" />
	<field name="delay2" descr="relevant for LUT3 (taps6-8), LUT4 (taps9-11). ignore otherwise.\;even taps (6, 8. 10) can get even values\;odd taps (7, 9, 11) cam get odd values.\;" access="RW" offset="0x4.12" size="0x0.6" />
	<field name="lut" descr="Lookup Table values per entry" access="RW" high_bound="255" low_bound="0" offset="0x8.24" size="0x100.0" />
</node>

<node name="sltpv2_reg_ext" descr="" size="0x10c.0" >
	<field name="c_db" descr="Copy transmitter parameters to Data Base. \;" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: NearEnd_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: FarEnd_Port - (For Retimer/Gearbox - Line side)\;\;" access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3" offset="0x0.1" size="0x0.3" />
	<field name="lane_speed" descr="Reserved for PCIe.\;The lane speed for TX settings:\;0 - SDR / Gen1 (PCIe)\;1 - DDR / Gen2 (PCIe) / 5GBASE-R\;2 - QDR / Gen3 (PCIe)\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE) / Gen4 (PCIe)\;5 - EDR (25GE / 50GE / 100GE) / Gen5 (PCIe)\;6 - HDR (50GE / 200GE / 400GE)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;8 - XDR (106.25 Gbd / 212.5Gb/s)\;9 - Reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13-15 - Reserved" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="tx_policy" descr="Configures Tx parameter set policy\;0 - Tx parameters will be set according to best possible configuration chosen by the system\;1 - Tx parameters will be set according to Data Base only and will not be overridden by link training (e.g KR-Startup)" access="RW" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="5: prod_5nm" access="RO" enum="prod_5nm=0x5" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="Indicates that Tx setting readout is valid and active. In particular, for links that do AN/LT, valid will be set when link operational status is UP (PAOS.oper_status=0x1).\;For links without AN/LT, valid will be set when Tx is enabled.\;\;0 - Invalid\;1 - Valid\;\;Note: Get and Set operations can be set when status = invalid." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="page_data" descr="Table 1736, &quot;SLTPv2 - Serdes Lane Transmit Parameters v2 Register Layout for LUT 5nm,&quot; on page 2044" subnode="sltpv2_reg_page_data_auto_ext" access="RW" condition="$(parent).version" offset="0x4.0" size="0x108.0" />
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

<node name="vhca_icm_ctrl_ext" descr="" size="0x40.0" >
	<field name="vhca_id" descr="vHCA Identifier. \;Valid only when vhca_id_valid" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="vhca_id_valid" descr="If set vhac_id field is valid. otherwise, own vhca_id is used." access="WO" offset="0x0.31" size="0x0.1" />
	<field name="rst_max_reached_alloc_icm" descr="If set, reset max_reached_alloc_icm field." access="WO" offset="0x4.29" size="0x0.1" />
	<field name="max_alloc_icm_th_mask" descr="If set, indicating max_alloc_icm_th is valid to be updated in write operation." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="max_alloc_icm_th" descr="This field sets the maximum allocated ICM for new allocations of specific vHCA in granularity of 4KB.\;Value 2^32-1 represents infinity.. The allocation must be equal or smaller than total_icm\;The allocation might be round up to next page size." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="cur_alloc_icm" descr="This field indicates the current allocated ICM in granularity of 4KB." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="max_reached_alloc_icm" descr="This field indicates the maximum allocated ICM in granularity 4KB." access="RO" offset="0x20.0" size="0x4.0" />
</node>

<node name="vhca_trust_level_ext" descr="" size="0x10.0" >
	<field name="vhca_id" descr="Valid only when all_vhca==0" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="all_vhca" descr="If set, set turst_level to all vHCAs that belong to this vport_group_manager.\;Supported for Set operation only." access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="trust_level" descr="Bitmask indicates trust levels supported for a vhca\;Bit 0x0: FULL_TRUST" access="RW" enum="FULL_TRUST=0x1" offset="0x4.0" size="0x4.0" />
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
