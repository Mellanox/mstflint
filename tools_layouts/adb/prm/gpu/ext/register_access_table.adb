<NodesDefinition>
<config  field_mand="name, descr, size" />
<config  field_attr="name" type="ascii" />
<config  field_attr="descr" type="ascii" />
<config  field_attr="size" type="hexa" />
<config  field_attr="field_type" type="ascii" />
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
<config  field_attr="mlxconfig_name" type="ascii" />
<config  field_attr="mlxconfig_desc" type="ascii" />
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
<info source_doc_name="GPUNet_PRM" source_doc_version="0.10.063" />
<node name="High_bit_error_rate_configuration_page_ext" descr="" size="0x10.0" >
	<field name="en" descr="enable hi_ber monitoring" access="RW" offset="0x0.31" size="0x0.1" />
</node>

<node name="High_symbol_error_rate_configuration_page_ext" descr="" size="0x10.0" >
	<field name="hi_ser_cap" descr="hi_ser monitoring capability supported" access="RW" offset="0x0.26" size="0x0.1" />
	<field name="symbol_err_thr" descr="Number of errored symbols in 8192 codewords window to declare hi_ser" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="hi_ser_ctl" descr="Control the hi_ser configuration if hi_ser_cap = 10: Use FW default. Default1: Enable hi_ser detection2: Disable Disable hi_ser detection" access="RW" offset="0x4.26" size="0x0.2" />
	<field name="error_mark_on_hi_ser_en" descr="Enable marking as invalid sync bits on 66b blocks force on hi_ser\;detection" access="RW" offset="0x4.29" size="0x0.1" />
	<field name="align_loss_on_hi_ser_en" descr="Enable alignment loss force on hi_ser detection" access="RW" offset="0x4.30" size="0x0.1" />
</node>

<node name="IB_long_portcntrs_attribute_grp_data_ext" descr="" size="0xf8.0" >
	<field name="symbol_error_counter_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="symbol_error_counter_low" descr="(see above)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="link_error_recovery_counter_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="link_error_recovery_counter_low" descr="(see above)" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="link_downed_counter_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="link_downed_counter_low" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="port_rcv_errors_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="port_rcv_errors_low" descr="(see above)" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="port_rcv_remote_physical_errors_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="port_rcv_remote_physical_errors_low" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="port_rcv_switch_relay_errors_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="port_rcv_switch_relay_errors_low" descr="(see above)" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="port_xmit_discards_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="port_xmit_discards_low" descr="(see above)" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="port_xmit_constraint_errors_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="port_xmit_constraint_errors_low" descr="(see above)" access="RO" offset="0x3c.0" size="0x4.0" />
	<field name="port_rcv_constraint_errors_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="port_rcv_constraint_errors_low" descr="(see above)" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="local_link_integrity_errors_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="local_link_integrity_errors_low" descr="(see above)" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="excessive_buffer_overrun_errors_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="excessive_buffer_overrun_errors_low" descr="(see above)" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="vl_15_dropped_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="vl_15_dropped_low" descr="(see above)" access="RO" offset="0x5c.0" size="0x4.0" />
	<field name="port_xmit_data_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="port_xmit_data_low" descr="(see above)" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="port_rcv_data_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="port_rcv_data_low" descr="(see above)" access="RO" offset="0x6c.0" size="0x4.0" />
	<field name="port_xmit_pkts_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="port_xmit_pkts_low" descr="(see above)" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="port_rcv_pkts_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="port_rcv_pkts_low" descr="(see above)" access="RO" offset="0x7c.0" size="0x4.0" />
	<field name="port_xmit_wait_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="port_xmit_wait_low" descr="(see above)" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="qp1_dropped_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="qp1_dropped_low" descr="(see above)" access="RO" offset="0x8c.0" size="0x4.0" />
	<field name="port_unicast_xmit_pkts_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x90.0" size="0x4.0" />
	<field name="port_unicast_xmit_pkts_low" descr="(see above)" access="RO" offset="0x94.0" size="0x4.0" />
	<field name="port_multicast_xmit_pkts_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x98.0" size="0x4.0" />
	<field name="port_multicast_xmit_pkts_low" descr="(see above)" access="RO" offset="0x9c.0" size="0x4.0" />
	<field name="port_unicast_rcv_pkts_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0xa0.0" size="0x4.0" />
	<field name="port_unicast_rcv_pkts_low" descr="(see above)" access="RO" offset="0xa4.0" size="0x4.0" />
	<field name="port_multicast_rcv_pkts_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0xa8.0" size="0x4.0" />
	<field name="port_multicast_rcv_pkts_low" descr="(see above)" access="RO" offset="0xac.0" size="0x4.0" />
</node>

<node name="IB_portcntrs_attribute_grp_data_ext" descr="" size="0xf8.0" >
	<field name="link_downed_counter" descr="(see above)" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="link_error_recovery_counter" descr="(see above)" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="symbol_error_counter" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="port_rcv_remote_physical_errors" descr="(see above)" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="port_rcv_errors" descr="(see above)" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="port_xmit_discards" descr="(see above)" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="port_rcv_switch_relay_errors" descr="(see above)" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="excessive_buffer_overrun_errors" descr="(see above)" access="RO" offset="0xc.0" size="0x0.4" />
	<field name="local_link_integrity_errors" descr="(see above)" access="RO" offset="0xc.4" size="0x0.4" />
	<field name="port_rcv_constraint_errors" descr="(see above)" access="RO" offset="0xc.16" size="0x0.8" />
	<field name="port_xmit_constraint_errors" descr="(see above)" access="RO" offset="0xc.24" size="0x0.8" />
	<field name="vl_15_dropped" descr="(see above)" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="qp1_dropped" descr="(see above)" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="port_xmit_data" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="port_rcv_data" descr="(see above)" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="port_xmit_pkts" descr="(see above)" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="port_rcv_pkts" descr="(see above)" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="port_xmit_wait" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
</node>

<node name="MLPC_ext" descr="" attr_required_tlvs="index:s" size="0x40.0" >
	<field name="lp_msb" descr="port MSBUsed to identify the L1 controller associated to the desired HW\;counters." access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="portUsed to identify the L1 controller associated to the desired HW\;counters." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cnt_64bit" descr="Bit mask to configure extended 64 bits long counters.Bit per even HW counter. When bit [i] is set, counter[2i] and\;counter[2i+1] will be used to form a 64-bit counter.The odd counter cnt_sel[2i+1], will serve as the selector to configure\;the 64 bit counter.The odd counter cnt_val[2i+1], will serve as the LSB of the counter.The even counter cnt_val[2i], will serve as the MSB of the counter." access="RW" offset="0x4.0" size="0x0.4" />
	<field name="stop_at_ff" descr="When set, when one of the perf counters reaches FFs, all the counters\;will stop counting." access="RW" offset="0x4.29" size="0x0.1" />
	<field name="counter_rst" descr="Force reset for all the counters.Must be 0 for Get operation." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="counter_en" descr="Enable for the HW counters" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="cnt_type_hi" descr="[DWIP]HW counter type - high bits." access="RW" high_bound="7" low_bound="0" offset="0x8.28" size="0x4.0" />
	<field name="force_count_mask" descr="Force count bit mask, when bit[i] is set, pref_counter&lt;i&gt; will count\;with no consideration of any enable/reset/stop signals." access="RW" offset="0xc.0" size="0x0.8" />
	<field name="cnt_type" descr="HW counter type - low bits.[DWIP] See\;L1 Performance Counter Type" access="RW" high_bound="7" low_bound="0" offset="0x10.28" size="0x4.0" />
	<field name="cnt_val" descr="HW counter value.The counter value can be configured to an initial value before enabling\;the feature." access="RW" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
</node>

<node name="MRFV_CVB_ext" descr="" size="0x8.0" >
	<field name="cvb_data_index" descr="[Arcus2]: Index of LUT entry.[ArcusE]:CVB Voltage = -4 + 0.5 * cvb_data_indexcvb_data_index valid values 0 .. 15Process Sigma &lt;-&gt; DVDD (mV)-4.0: 856.00-3.5: 847.75-3.0: 839.50-2.5: 831.25-2.0: 823.00-1.5: 814.75-1.0: 806.50-0.5: 798.250 (nominal): 790.000.5: 781.751.0: 773.501.5: 765.252.0: 757.002.5: 748.753.0: 740.503.5: 732.254.0: 724.00Reserved when selector = 1" access="RO" offset="0x0.0" size="0x0.5" />
	<field name="cnt_out" descr="[DWIP][Internal]Valid only if selector = 0.The minimum value of ISM cnt_out value, normalized by VDD value, which\;is used to determine the selected LUT entry index." access="RO" offset="0x0.6" size="0x0.20" />
	<field name="tav_cvb_voltage_msb" descr="MSB bits of the TAV voltage" access="RO" offset="0x0.26" size="0x0.4" />
	<field name="selector_cause" descr="[DWIP] [Internal]If selector = 0:0: LUT used.1: Default fuse value used.If selector = 1:0: Fuses are valid (either non-default or default value).1: Fuses are invalid but LUT entry not located." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="selector" descr="[Arcus]:0: cvb_data_index is valid1: cvb_voltage is valid[Arcus2]:0: cvb_data_index is valid, and cvb_voltage exposes the value in LUT or\;the default fuse values.1: cvb_data_index is not valid, and cvb_voltage exposes non-default\;values from fuses (if selector_cause = 0)." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="cvb_voltage" descr="CVB VoltageReturns required CVB voltage in mV.Reserved when selector = 0" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="voltage_type" descr="The voltage type of the cvb_voltage0: DVDD1: AVDD2: VDD" access="INDEX" offset="0x4.16" size="0x0.3" />
	<field name="tav_cvb_voltage" descr="TAV CVB VoltageReturns required TAV CVB voltage in mV.Used in Retimer only.Value of 0 means not valid voltage, host should ignore this value." access="RO" offset="0x4.20" size="0x0.12" />
</node>

<node name="MRFV_PVS_MAIN_ext" descr="" size="0x4.0" >
	<field name="pvs_main_data" descr="VDD Main Data. “PVS” prefix in name exists due to historical reasons.Range 0.675 - 0.75Vdd = 750mV - (fuse value - 1)*5mV" access="RO" offset="0x0.0" size="0x0.7" />
</node>

<node name="MRFV_PVS_TILE_ext" descr="" size="0x4.0" >
	<field name="pvs_tile_data" descr="VDD tile Data. PVS” prefix in name exists due to historical reasons.Range 0.675 - 0.72Vdd = 750mV - (fuse value - 1)*5mV" access="RO" offset="0x0.0" size="0x0.7" />
</node>

<node name="MRFV_RAW_AND_VALUE_ext" descr="" size="0xc.0" >
	<field name="raw_fuses_highest_bit" descr="Raw Fuses Highest bit. Indicates the highest bit in raw_fuses field\;which is part of the fuse data.For example, if raw_fuses [15:0] contains the fuse data, this field’s\;value is 15." access="RO" offset="0x0.0" size="0x0.5" />
	<field name="value_valid" descr="Value valid.0: value_base and value_exponent are NOT valid.1: value_base and value_exponent are valid." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="raw_fuses" descr="Raw fuses.The only valid bits are bits 0 to &lt;raw_fuses_highest_bit&gt;." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="value_exponent" descr="The exponent part of the value.This field is signed, and negative values are represented using 2’s\;complement." access="RO" offset="0x8.0" size="0x0.6" />
	<field name="value_base" descr="The base part of the value.This field is signed, and negative values are represented using 2’s\;complement.The value is:value_base x 10 ^ value_exponent.Units:Power: [W].Voltage: [V].Time: [Sec].Current: [A].Capacitance: [F]." access="RO" offset="0x8.6" size="0x0.26" />
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

<node name="MRFV_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0xc.0" >
	<field name="MRFV_CVB_ext" descr="" subnode="MRFV_CVB_ext" access="RW" condition="($(parent).fuse_id == cvb)" offset="0x0.0" size="0x8.0" />
	<field name="MRFV_PVS_MAIN_ext" descr="" subnode="MRFV_PVS_MAIN_ext" access="RW" condition="($(parent).fuse_id == vdd_main_die)" offset="0x0.0" size="0x4.0" />
	<field name="MRFV_PVS_TILE_ext" descr="" subnode="MRFV_PVS_TILE_ext" access="RW" condition="($(parent).fuse_id == vdd_tile_0 | $(parent).fuse_id == vdd_tile_1 | $(parent).fuse_id == vdd_tile_2 | $(parent).fuse_id == vdd_tile_3 | $(parent).fuse_id == vdd_tile_4 | $(parent).fuse_id == vdd_tile_5 | $(parent).fuse_id == vdd_tile_6 | $(parent).fuse_id == vdd_tile_7)" offset="0x0.0" size="0x4.0" />
	<field name="MRFV_RAW_AND_VALUE_ext" descr="" subnode="MRFV_RAW_AND_VALUE_ext" access="RW" condition="($(parent).fuse_id == raw_and_value_vdd | $(parent).fuse_id == raw_and_value_pl_avdd | $(parent).fuse_id == raw_and_value_pl_dvdd | $(parent).fuse_id == raw_and_value_opt_fuse_rev | $(parent).fuse_id == raw_and_value_dvdd_sg | $(parent).fuse_id == raw_and_value_opt_lot_code_0 | $(parent).fuse_id == raw_and_value_opt_lot_code_1 | $(parent).fuse_id == raw_and_value_opt_ops_reserved | $(parent).fuse_id == raw_and_value_opt_vendor_code | $(parent).fuse_id == raw_and_value_opt_wafer_id | $(parent).fuse_id == raw_and_value_opt_x_coordinate | $(parent).fuse_id == raw_and_value_opt_y_coordinate | $(parent).fuse_id == raw_and_value_opt_fab_code | $(parent).fuse_id == raw_and_value_ws_tp_version_0_31 | $(parent).fuse_id == raw_and_value_ft_tp_version_0_31 | $(parent).fuse_id == raw_and_value_fuse_ver_0_3 | $(parent).fuse_id == raw_and_value_fuse_ver_4_7 | $(parent).fuse_id == raw_and_value_dvdd_avdd_version | $(parent).fuse_id == raw_and_value_dvdd | $(parent).fuse_id == raw_and_value_vddp)" offset="0x0.0" size="0xc.0" />
	<field name="MRFV_ULT_ext" descr="" subnode="MRFV_ULT_ext" access="RW" condition="($(parent).fuse_id == ULT)" offset="0x0.0" size="0xc.0" />
</node>

<node name="MRFV_ext" descr="" size="0x40.0" >
	<field name="fuse_id" descr="Fuse Index0: cvb - CVB Main Die, used for Retimer1: ULT2: vdd_main_die - (used in SPC-4, SPC-5)3: vdd_tile_0 - (used in SPC-4, SPC-5)4: vdd_tile_1 - (used in SPC-4, SPC-5)5: vdd_tile_2 - (used in SPC-4, SPC-5)6: vdd_tile_3 - (used in SPC-4, SPC-5)7: vdd_tile_4 - (used in SPC-4, SPC-5)8: vdd_tile_5 - (used in SPC-4, SPC-5)9: vdd_tile_6 - (used in SPC-4, SPC-5)10: vdd_tile_7 - (used in SPC-4, SPC-5)[SwitchOnly][DWIP]:11: raw_and_value_vdd - Use instance_id for the specific instance. Valid on SPC6.12: raw_and_value_pl_avdd - Use instance_id for the specific instance. Valid on SPC6.13: raw_and_value_pl_dvdd - Use instance_id for the specific instance. Valid on SPC6.15: raw_and_value_opt_fuse_rev - Valid on SPC6 CPO.16: raw_and_value_dvdd_sg - Use instance_id for the specific instance. Valid on SPC6 CPO.17: raw_and_value_opt_lot_code_0 - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.18: raw_and_value_opt_lot_code_1 - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.19: raw_and_value_opt_ops_reserved - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.20: raw_and_value_opt_vendor_code - Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.21: raw_and_value_opt_wafer_id Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.22: raw_and_value_opt_x_coordinate Use entity_index to specify the Optical Engine index Valid on SPC6 CPO.23: raw_and_value_opt_y_coordinate Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO.24: raw_and_value_opt_fab_code\;Use entity_index to specify the Optical Engine index. Valid on SPC6 CPO. -\; -\; -\;\;[NIC_only][DWIP]:30: raw_and_value_dvdd[NIC_only][DWIP]:31: raw_and_value_vddpOther values reserved." access="INDEX" enum="cvb=0x0,ULT=0x1,vdd_main_die=0x2,vdd_tile_0=0x3,vdd_tile_1=0x4,vdd_tile_2=0x5,vdd_tile_3=0x6,vdd_tile_4=0x7,vdd_tile_5=0x8,vdd_tile_6=0x9,vdd_tile_7=0xa,raw_and_value_vdd=0xb,raw_and_value_pl_avdd=0xc,raw_and_value_pl_dvdd=0xd,raw_and_value_opt_fuse_rev=0xf,raw_and_value_dvdd_sg=0x10,raw_and_value_opt_lot_code_0=0x11,raw_and_value_opt_lot_code_1=0x12,raw_and_value_opt_ops_reserved=0x13,raw_and_value_opt_vendor_code=0x14,raw_and_value_opt_wafer_id=0x15,raw_and_value_opt_x_coordinate=0x16,raw_and_value_opt_y_coordinate=0x17,raw_and_value_opt_fab_code=0x18,raw_and_value_ws_tp_version_0_31=0x19,raw_and_value_ft_tp_version_0_31=0x1a,raw_and_value_fuse_ver_4_7=0x1c,raw_and_value_dvdd=0x1e,raw_and_value_vddp=0x1f" offset="0x0.0" size="0x0.8" />
	<field name="instance_id" descr="[DWIP]:Instance ID. For a fuse that has multiple instances, this field provides\;the Instance ID.For the common case where it’s a single instance per asic, instance ID 0\;denotes the main/die [0] instance, and subsequent instance ID X denotes\;the instance of tile [X-1] / die [X].For a given fuse_id, if an invalid instance_id is provided, fm field\;will have a value of 1 (“Fuse mismatch found”)." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="fm" descr="Fuse Mismatch0: No fuse mismatch1: Fuse mismatch found2-3: Reserved" access="RO" offset="0x0.24" size="0x0.2" />
	<field name="module_index_valid" descr="[DWIP]1: module_index_msb and module_index fields contain a valid index." access="INDEX" offset="0x0.29" size="0x0.1" />
	<field name="v" descr="Valid bit0: Fuse reading is not supported for this system1: Response is valid2-3: ReservedReserved (0) when fm = 1" access="RO" offset="0x0.30" size="0x0.2" />
	<field name="module_index" descr="[DWIP]:&lt;module_index_msb, module_index&gt; specifies the element in which the fuse\;resides, if not part of the ASIC itself." access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="module_index_msb" descr="[DWIP]:&lt;module_index_msb, module_index&gt; specifies the element in which the fuse\;resides, if not part of the ASIC itself.Currently only valid elements are Optical Engines." access="INDEX" offset="0x4.8" size="0x0.8" />
	<field name="data" descr="DataSee \;MRFV entry - CVB LayoutSee \;MRFV entry - ULT LayoutSee \;MRFV entry - VDD_MAIN LayoutSee\;\;MRFV entry - VDD_Tile LayoutSee\;\;MRFV entry - RAW_AND_VALUE LayoutReserved when fm = 1" subnode="MRFV_data_auto_ext" access="RO" condition="$(parent).fuse_id" offset="0x10.0" size="0xc.0" />
</node>

<node name="MSECQ_reg_ext" descr="" size="0x40.0" >
	<field name="local_enhanced_ssm_code" descr="The enhanced SSM code to be delivered when on holdover." access="RO" offset="0x4.0" size="0x0.8" />
	<field name="local_ssm_code" descr="The SSM code to be delivered when on holdover." access="RO" offset="0x4.8" size="0x0.4" />
	<field name="network_option" descr="The network option of this device (as defined in ITU-T G.781).1: Network option 12: Network option 2" access="RO" offset="0x4.12" size="0x0.2" />
	<field name="local_clock_identity" descr="The SyncE clock identity of the device." subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="MSEES_reg_ext" descr="" size="0x40.0" >
	<field name="lp_msb" descr="2-bit expansion of the local port. Represents the local_port[9:8] bits" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type, determines the way local_port is interpreted:0: Local port number1: Label port number3: Out of band or PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port numberNot supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="field_select" descr="Field select indicates which fields to modify in write operation to this\;register.Bit 0: enable field_selectBit 1: admin_statusBit 2: admin_freq_measureBits 3-31: Reserved" access="WO" offset="0x4.0" size="0x4.0" />
	<field name="failure_reason" descr="0: undefined error1: port down2: too high frequency_diff3: network synchronizer device error4: lack of resources for tracking 5-255: reserved for future useNote: Reserved when oper_status is different than 4 or 5" access="RO" offset="0x8.0" size="0x0.9" />
	<field name="oper_freq_measure" descr="0: frequency_diff field is not valid1: frequency_diff field is valid" access="RO" offset="0x8.9" size="0x0.1" />
	<field name="admin_freq_measure" descr="0: don’t measure frequency_diff1: measure frequency_diff" access="RW" offset="0x8.10" size="0x0.1" />
	<field name="ho_acq" descr="Holdover acquired.0: The device does not have enough data to go into holdover.1: The device has enough data to go into holdover." access="RO" offset="0x8.23" size="0x0.1" />
	<field name="oper_status" descr="0: free running – the device is using internal oscillator as timing\;source1: self track – the device is in sync with this timing source2: other track - the device is in sync with other timing source3: holdover – the device is using the internal oscillator and past\;information as a timing source.4: Holdover due to failure (see field failure_reason)5: Free running due to failure (see field failure_reason)." access="RO" offset="0x8.24" size="0x0.4" />
	<field name="admin_status" descr="0: holdover/free running – the device will use internal oscillator as\;timing source.Free running is the default value.Device holdover / free running will take place only if admin status = 0\;across all other ports.1: track - the device will sync to this timing source. When writing\;admin status = 1 to a port, all other ports will move to admin status =\;0." access="RW" offset="0x8.28" size="0x0.4" />
	<field name="frequency_diff" descr="The FFO (Fractional Frequency Offset) between the rx and tx symbol rate:\;(rx_frequency- tx_frequency) /rx_frequency.Value is in ppt (2’s complement).Any value larger than 0x7FFFFFFF represented as 0x7FFFFFFF.Any value smaller than 0x80000000 represented as 0x80000000.Note: Reserved when oper_freq is different than ‘1’." access="RO" offset="0xc.0" size="0x4.0" />
</node>

<node name="MTSR_ext" descr="" size="0x10.0" >
	<field name="mode" descr="0: Normal1: Warning2: Critical3-7: Reserved" access="RO" offset="0x0.0" size="0x0.3" />
	<field name="normal_events_cnt" descr="Num of normal thermal events triggered counter" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="warning_events_cnt" descr="Num of warning thermal events triggered counter" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="critical_events_cnt" descr="Num of critical thermal events triggered counter" access="RO" offset="0xc.0" size="0x0.8" />
</node>

<node name="PPCR_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port[9:8]Reserved for HCA" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="asymmetry_enable" descr="Indicate whether asymmetry is enabled or not.0: DISABLED1: ENABLEDFor HCA, reserved if PPCR.asymmetry_enable_supported=0" access="RO" enum="DISABLED=0x0,ENABLED=0x1" offset="0x4.30" size="0x0.1" />
	<field name="asymmetry_enable_supported" descr="Indicate whether asymmetry_enable supported or not.Reserved for switch.0: NOT_SUPPORTED1: SUPPORTED" access="RO" enum="NOT_SUPPORTED=0x0,SUPPORTED=0x1" offset="0x4.31" size="0x0.1" />
	<field name="aggregated_port" descr="Aggregated Port number to be reflected in MAD.0 means N/A" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="plane" descr="Plane number to be reflected in MAD.0 means N/A" access="RW" offset="0x8.16" size="0x0.3" />
	<field name="split" descr="When planarized  the FW\;shall respond to Hierarchy Info.Split with the following split value.In this use case it represents the split of the APort.When split = 0, the FW shall send Hierarchy Info without the split\;field. (meaning it is NA)When Non planarized (num_of_planes = 0), Hierarchy Info.Split will\;reflect the actual split value, when 2X- it’ll hold the location within\;the 4x.0: NA1: Split 1.2: Split 2.3-7: ReservedReserved for HCA" access="RW" offset="0x8.24" size="0x0.3" />
	<field name="num_of_planes" descr="The number of planes comprising this Aggregated port" access="RW" offset="0xc.0" size="0x0.8" />
	<field name="p_type" descr="Planarization Type0: non planarized1: planirized_gen12-7: Reserved" access="RW" offset="0xc.16" size="0x0.3" />
</node>

<node name="PPIR_ext" descr="" size="0x8.0" >
	<field name="lcnf_pln" descr="Last Core Negotiation Failed due to Planarized.When there is no match between local and remote fields compared to local\;config by PPCR" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="lpnf_phy" descr="Last Phy Negotiation Failed due to PhyNo partner detected for a long period" access="RO" offset="0x0.8" size="0x0.1" />
	<field name="lpnf_no_hcd" descr="Last Phy Negotiation Failed due to Highest Common Denominator mismatch." access="RO" offset="0x0.9" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="peer_num_of_planes" descr="The number of planes comprising the peer Aggregated port" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="peer_p_type" descr="Peer Planarization Type0: non planarized1: planirized_gen12-7: Reserved" access="RO" offset="0x4.16" size="0x0.3" />
</node>

<node name="SLTR_reg_ext" descr="" attr_required_tlvs="index:s" size="0x138.0" >
	<field name="meas_type" descr="Measurement type parameters:0: Periodic_non_destructive1: Periodic_non_destructive_part22: non_periodic_non_destructive3: cause_list4: Periodic_non_destructive_part3" access="INDEX" enum="Periodic_non_destructive=0x0,Periodic_non_destructive_part2=0x1,non_periodic_non_destructive=0x2,cause_list=0x3,Periodic_non_destructive_part3=0x4" offset="0x0.0" size="0x0.4" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0 - Network Port1 - Near-End Port (For Retimer/Gearbox - Host side)2 - internal IC LR Port3 - Far-End Port (For Retimer/Gearbox - Line side)4 - USR Main5 - USR TileOther values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type:0 - Local port number1 - IB Port number3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.10" />
	<field name="status" descr="0 - Invalid1 - Valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="group_cap_mask" descr="Supported pagesBit 0 - Periodic and Non-destructiveBit 1 - Periodic and Non-destructive_part2Bit 2- Non-Periodic and Non-destructiveBit 3- Periodic and Non-destructive_part3Bit 4- Non-Periodic and Non-destructive_7_5" access="RO" offset="0x4.0" size="0x0.9" />
	<field name="version" descr="5: prod_5nm - (Uphy 7.0)6: serdes_gen_87: prod_3nm_serdes_gen_7p5" access="RO" enum="prod_5nm=0x5,serdes_gen_8=0x6,prod_3nm_serdes_gen_7p5=0x7" offset="0x4.24" size="0x0.4" />
	<field name="aux" descr="" access="RO" offset="0x4.28" size="0x0.3" />
	<field name="page_data" descr="SLTR - Periodic Non Destructive Layout\;SLTR - Periodic Non Destructive part2 Layout\;SLTR - Periodic Non Destructive part3 Layout\;SLTR - Periodic Non Destructive 7_5 Layout\;SLTR - Non Periodic Non Destructive Layout\;SLTR - Non Periodic Non Destructive 7_5 Layout\;SLTR - Cause List UPHY8 Layout\;SLTR - Cause List UPHY7.5 Layout\;SLTR - Cause List UPHY7 Layout" subnode="SLTR_reg_page_data_auto_ext" access="RO" condition="$(parent).meas_type AND $(parent).version" offset="0x8.0" size="0x130.0" />
</node>

<node name="SLTR_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x130.0" >
	<field name="sltr_cause_list_uphy7_5_ext" descr="" subnode="sltr_cause_list_uphy7_5_ext" access="RW" condition="($(parent).meas_type == cause_list) AND ($(parent).version == prod_3nm_serdes_gen_7p5)" offset="0x0.0" size="0x14.0" />
	<field name="sltr_cause_list_uphy7_ext" descr="" subnode="sltr_cause_list_uphy7_ext" access="RW" condition="($(parent).meas_type == cause_list) AND ($(parent).version == prod_5nm)" offset="0x0.0" size="0x10.0" />
	<field name="sltr_cause_list_uphy8_ext" descr="" subnode="sltr_cause_list_uphy8_ext" access="RW" condition="($(parent).meas_type == cause_list) AND ($(parent).version == serdes_gen_8)" offset="0x0.0" size="0x14.0" />
	<field name="sltr_non_periodic_non_destructive_7_5_ext" descr="" subnode="sltr_non_periodic_non_destructive_7_5_ext" access="RW" condition="($(parent).meas_type == non_periodic_non_destructive) AND ($(parent).version == prod_3nm_serdes_gen_7p5)" offset="0x0.0" size="0x10.0" />
	<field name="sltr_non_periodic_non_destructive_ext" descr="" subnode="sltr_non_periodic_non_destructive_ext" access="RW" condition="($(parent).meas_type == non_periodic_non_destructive) AND ($(parent).version == serdes_gen_8)" offset="0x0.0" size="0x18.0" />
	<field name="sltr_periodic_non_destructive_7_5_ext" descr="" subnode="sltr_periodic_non_destructive_7_5_ext" access="RW" condition="($(parent).meas_type == Periodic_non_destructive_part3) AND ($(parent).version == prod_3nm_serdes_gen_7p5)" offset="0x0.0" size="0xd8.0" />
	<field name="sltr_periodic_non_destructive_ext" descr="" subnode="sltr_periodic_non_destructive_ext" access="RW" condition="($(parent).meas_type == Periodic_non_destructive) AND ($(parent).version == serdes_gen_8)" offset="0x0.0" size="0x124.0" />
	<field name="sltr_periodic_non_destructive_part2_ext" descr="" subnode="sltr_periodic_non_destructive_part2_ext" access="RW" condition="($(parent).meas_type == Periodic_non_destructive_part2) AND ($(parent).version == serdes_gen_8)" offset="0x0.0" size="0x130.0" />
	<field name="sltr_periodic_non_destructive_part3_ext" descr="" subnode="sltr_periodic_non_destructive_part3_ext" access="RW" condition="($(parent).meas_type == Periodic_non_destructive) AND ($(parent).version == prod_3nm_serdes_gen_7p5)" offset="0x0.0" size="0xc4.0" />
</node>

<node name="access_reg_summary_ctrl_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="id" descr="" subnode="enum_entry" access="RW" enum="MMDIO=0x9017,MLCR=0x902b,MGCR=0x903a,MJTAG=0x901f,MTPPS=0x9053,MTUTC=0x9055,MSECQ=0x9155,MSEES=0x9156,MCIA=0x9014,MCION=0x9052,PMAOS=0x5012,MMTA=0x9113,PMTM=0x5067,PMPC=0x501f,PMPE=0x5024,MELSRC=0x9046,MELSEQ=0x9047,MGPIR=0x9100,MILAQ=0x9187,MDRCR=0x9102,MTCAP=0x9009,MTECR=0x9109,MTMP=0x900a,MTWE=0x900b,MTEWE=0x910b,MTBR_V2=0x9167,MTDTH=0x9111,MVCAP=0x902e,MVCR=0x900c,MPSCR=0x910f,MTSR=0x9121,MLPC=0x9166,MSLCG=0x902c,MCQS=0x9060,MCQI=0x9061,MCC=0x9062,MCDA=0x9063,MCDD=0x905c,MIRC=0x9162,MQIS=0x9064,MGIR=0x9020,MSGI=0x9021,MSCI=0x902a,MDIR=0x911a,MIDFV=0x9018,MCAM=0x907f,MRFV=0x906d,MTEIR=0x9190,MDTR=0x9073,MDSR=0x9110,MFSV=0x9115,MTCQ=0x9065,MQDIK=0x9116,MKDC=0x9066,MFCDR=0x9178,MSGCR=0x9179,MNVDA=0x9024,MNVDI=0x9025,MNVQC=0x9030,MNVIA=0x9033,MNVGC=0x9034,MNVGN=0x9035,MGNLE=0x9036,MTRC_CAP=0x9040,MTRC_CONF=0x9041,MTRC_STDB=0x9042,MTRC_CTRL=0x9043,MTEIM=0x9118,MTIE=0x911b,MTIM=0x911c,MTDC=0x911d,MFPA=0x9010,MFBA=0x9011,MFBE=0x9012,MPCIR=0x905a,MERR=0x903c,MRPR=0x9117,MHMPR=0x905d,MISSUV=0x9191,PCAM=0x507f,PCAP=0x5001,PTYS=0x5004,PAOS=0x5006,PLTC=0x5046,PPCNT=0x5008,PUDE=0x5009,PGMR=0x5039,PTER=0x5055,PREI=0x5058,PPRM=0x5059,PMLP=0x5002,PMPR=0x5013,PMMP=0x5044,PMCR=0x5045,PMPT=0x5064,PMPD=0x5065,PMLR=0x506d,PMAC=0x507e,PLDS=0x5076,PPSC=0x5011,PRTL=0x5014,PPLR=0x5018,PPLM=0x5023,SLTP=0x5027,SLTPv2=0x502f,SLRG=0x5028,PTASv2=0x502e,SLSIR=0x502c,PDDR=0x5031,PPTT=0x5036,PPRT=0x5037,PMDR=0x503c,PPHCR=0x503e,PPAOS=0x5040,PPBMP=0x5051,PPBMC=0x5052,PPBME=0x5053,PGLF=0x5091,SLLM=0x505b,SLPRR=0x507b,PLCC=0x505e,PCCT=0x5086,SLTR=0x5081,PFLDC=0x5083,SLMTRD=0x5095,PEDCC=0x5087,PMTU=0x5003,PPAD=0x5005,PFCC=0x5007,PPFCG=0x50f1,PPWCC=0x50f2,PPWPT=0x50f3,PPWE=0x50f4,PPWDC=0x50f5,PPTB=0x500b,PBMC=0x500c,PGUID=0x5066,PVLC=0x500f,PHBR=0x5034,PHRR=0x5035,PBSR=0x5038,PCMR=0x5041,PFSC=0x5043,PPCR=0x504c,PPIR=0x50eb,PTSR=0x5400,PRTSR=0x5402,PTSB=0x5401,PLIB=0x500a,PLIBDB=0x50e1,PPSLC=0x50e2,PPSLS=0x50e3,PPSLD=0x50e4,PEVNT=0x50e6,PBWC=0x50e7,PBWR=0x50e8,PPDFD=0x50e9,PGCB=0x5103,PGRRS=0x5104,PRCCT=0x5400,MODCR=0x9099,MFDE=0x9200,MOFDE=0x9152,MORD=0x9153,MORD_V2=0x915b,MISG=0x915d,GNDR=0x6801,GHPKT=0x6802,GSGUID=0x6803,GPLID=0x6805,GFER=0x6808,UNWKM=0x6501,UNRSA=0x6502,UNRC=0x6503,UNDRI=0x6504,UKDRI=0x6506,UNDFD=0x6505" offset="0x0.0" size="0x4.0" />
</node>

<node name="access_reg_summary_ext" descr="" attr_is_union="1" size="0x410.0" >
	<field name="MLPC" descr="" subnode="MLPC_ext" access="RW" offset="0x0.0" selected_by="MLPC" size="0x40.0" />
	<field name="MRFV" descr="" subnode="MRFV_ext" access="RW" offset="0x0.0" selected_by="MRFV" size="0x40.0" />
	<field name="MSECQ_reg" descr="" subnode="MSECQ_reg_ext" access="RW" offset="0x0.0" selected_by="MSECQ" size="0x40.0" />
	<field name="MSEES_reg" descr="" subnode="MSEES_reg_ext" access="RW" offset="0x0.0" selected_by="MSEES" size="0x40.0" />
	<field name="MTSR" descr="" subnode="MTSR_ext" access="RW" offset="0x0.0" selected_by="MTSR" size="0x10.0" />
	<field name="PPCR" descr="" subnode="PPCR_ext" access="RW" offset="0x0.0" selected_by="PPCR" size="0x10.0" />
	<field name="PPIR" descr="" subnode="PPIR_ext" access="RW" offset="0x0.0" selected_by="PPIR" size="0x8.0" />
	<field name="SLTR_reg" descr="" subnode="SLTR_reg_ext" access="RW" offset="0x0.0" selected_by="SLTR" size="0x138.0" />
	<field name="gfer" descr="" subnode="gfer_ext" access="RW" offset="0x0.0" selected_by="GFER" size="0xcc.0" />
	<field name="ghpkt" descr="" subnode="ghpkt_ext" access="RW" offset="0x0.0" selected_by="GHPKT" size="0x10.0" />
	<field name="gndr" descr="" subnode="gndr_ext" access="RW" offset="0x0.0" selected_by="GNDR" size="0x40.0" />
	<field name="gplid" descr="" subnode="gplid_ext" access="RW" offset="0x0.0" selected_by="GPLID" size="0x10.0" />
	<field name="gsguid" descr="" subnode="gsguid_ext" access="RW" offset="0x0.0" selected_by="GSGUID" size="0x10.0" />
	<field name="mcam_reg" descr="" subnode="mcam_reg_ext" access="RW" offset="0x0.0" selected_by="MCAM" size="0x48.0" />
	<field name="mcc_reg" descr="" subnode="mcc_reg_ext" access="RW" offset="0x0.0" selected_by="MCC" size="0x20.0" />
	<field name="mcda_reg" descr="" subnode="mcda_reg_ext" access="RW" offset="0x0.0" selected_by="MCDA" size="0x90.0" />
	<field name="mcdd_reg" descr="" subnode="mcdd_reg_ext" access="RW" offset="0x0.0" selected_by="MCDD" size="0x20.0" />
	<field name="mcia" descr="" subnode="mcia_ext" access="RW" offset="0x0.0" selected_by="MCIA" size="0x94.0" />
	<field name="mcion" descr="" subnode="mcion_ext" access="RW" offset="0x0.0" selected_by="MCION" size="0x10.0" />
	<field name="mcqi_reg" descr="" subnode="mcqi_reg_ext" access="RW" offset="0x0.0" selected_by="MCQI" size="0x94.0" />
	<field name="mcqs_reg" descr="" subnode="mcqs_reg_ext" access="RW" offset="0x0.0" selected_by="MCQS" size="0x10.0" />
	<field name="mdir_reg" descr="" subnode="mdir_reg_ext" access="RW" offset="0x0.0" selected_by="MDIR" size="0x40.0" />
	<field name="mdrcr" descr="" subnode="mdrcr_ext" access="RW" offset="0x0.0" selected_by="MDRCR" size="0x30.0" />
	<field name="mdsr_reg" descr="" subnode="mdsr_reg_ext" access="RW" offset="0x0.0" selected_by="MDSR" size="0x30.0" />
	<field name="mdtr_reg" descr="" subnode="mdtr_reg_ext" access="RW" offset="0x0.0" selected_by="MDTR" size="0xb0.0" />
	<field name="melseq_reg" descr="" subnode="melseq_reg_ext" access="RW" offset="0x0.0" selected_by="MELSEQ" size="0x30.0" />
	<field name="melsrc_reg" descr="" subnode="melsrc_reg_ext" access="RW" offset="0x0.0" selected_by="MELSRC" size="0x1c.0" />
	<field name="merr" descr="" subnode="merr_ext" access="RW" offset="0x0.0" selected_by="MERR" size="0x14.0" />
	<field name="mfba_reg" descr="" subnode="mfba_reg_ext" access="RW" offset="0x0.0" selected_by="MFBA" size="0x10c.0" />
	<field name="mfbe_reg" descr="" subnode="mfbe_reg_ext" access="RW" offset="0x0.0" selected_by="MFBE" size="0xc.0" />
	<field name="mfcdr_reg" descr="" subnode="mfcdr_reg_ext" access="RW" offset="0x0.0" selected_by="MFCDR" size="0x8.0" />
	<field name="mfde" descr="" subnode="mfde_ext" access="RW" offset="0x0.0" selected_by="MFDE" size="0xb0.0" />
	<field name="mfpa_reg" descr="" subnode="mfpa_reg_ext" access="RW" offset="0x0.0" selected_by="MFPA" size="0x20.0" />
	<field name="mfsv_reg" descr="" subnode="mfsv_reg_ext" access="RW" offset="0x0.0" selected_by="MFSV" size="0x30.0" />
	<field name="mgcr_reg" descr="" subnode="mgcr_reg_ext" access="RW" offset="0x0.0" selected_by="MGCR" size="0x20.0" />
	<field name="mgir" descr="" subnode="mgir_ext" access="RW" offset="0x0.0" selected_by="MGIR" size="0xa0.0" />
	<field name="mgnle_reg" descr="" subnode="mgnle_reg_ext" access="RW" offset="0x0.0" selected_by="MGNLE" size="0x20.0" />
	<field name="mgpir" descr="" subnode="mgpir_ext" access="RW" offset="0x0.0" selected_by="MGPIR" size="0xa0.0" />
	<field name="mhmpr_reg" descr="" subnode="mhmpr_reg_ext" access="RW" offset="0x0.0" selected_by="MHMPR" size="0x14.0" />
	<field name="midfv_reg" descr="" subnode="midfv_reg_ext" access="RW" offset="0x0.0" selected_by="MIDFV" size="0x80.0" />
	<field name="milaq" descr="" subnode="milaq_ext" access="RW" offset="0x0.0" selected_by="MILAQ" size="0x24.0" />
	<field name="mirc_reg" descr="" subnode="mirc_reg_ext" access="RW" offset="0x0.0" selected_by="MIRC" size="0x8.0" />
	<field name="misg" descr="" subnode="misg_ext" access="RW" offset="0x0.0" selected_by="MISG" size="0x10.0" />
	<field name="missuv" descr="" subnode="missuv_ext" access="RW" offset="0x0.0" selected_by="MISSUV" size="0x20.0" />
	<field name="mjtag" descr="" subnode="mjtag_ext" access="RW" offset="0x0.0" selected_by="MJTAG" size="0x30.0" />
	<field name="mkdc_reg" descr="" subnode="mkdc_reg_ext" access="RW" offset="0x0.0" selected_by="MKDC" size="0x2c.0" />
	<field name="mlcr" descr="" subnode="mlcr_ext" access="RW" offset="0x0.0" selected_by="MLCR" size="0xc.0" />
	<field name="mmdio" descr="" subnode="mmdio_ext" access="RW" offset="0x0.0" selected_by="MMDIO" size="0xc.0" />
	<field name="mmta_reg" descr="" subnode="mmta_reg_ext" access="RW" offset="0x0.0" selected_by="MMTA" size="0x90.0" />
	<field name="mnvda_reg" descr="" subnode="mnvda_reg_ext" access="RW" offset="0x0.0" selected_by="MNVDA" size="0x10c.0" />
	<field name="mnvdi_reg" descr="" subnode="mnvdi_reg_ext" access="RW" offset="0x0.0" selected_by="MNVDI" size="0xc.0" />
	<field name="mnvgc_reg" descr="" subnode="mnvgc_reg_ext" access="RW" offset="0x0.0" selected_by="MNVGC" size="0x10.0" />
	<field name="mnvgn_reg" descr="" subnode="mnvgn_reg_ext" access="RW" offset="0x0.0" selected_by="MNVGN" size="0x20.0" />
	<field name="mnvia_reg" descr="" subnode="mnvia_reg_ext" access="RW" offset="0x0.0" selected_by="MNVIA" size="0x8.0" />
	<field name="mnvqc_reg" descr="" subnode="mnvqc_reg_ext" access="RW" offset="0x0.0" selected_by="MNVQC" size="0x8.0" />
	<field name="modcr" descr="" subnode="modcr_ext" access="RW" offset="0x0.0" selected_by="MODCR" size="0x14.0" />
	<field name="mofde" descr="" subnode="mofde_ext" access="RW" offset="0x0.0" selected_by="MOFDE" size="0x4.0" />
	<field name="mord_v2" descr="" subnode="mord_v2_ext" access="RW" offset="0x0.0" selected_by="MORD_V2" size="0x34.0" />
	<field name="mpcir" descr="" subnode="mpcir_ext" access="RW" offset="0x0.0" selected_by="MPCIR" size="0xa0.0" />
	<field name="mpscr" descr="" subnode="mpscr_ext" access="RW" offset="0x0.0" selected_by="MPSCR" size="0x20.0" />
	<field name="mqdik_reg" descr="" subnode="mqdik_reg_ext" access="RW" offset="0x0.0" selected_by="MQDIK" size="0x208.0" />
	<field name="mqis_reg" descr="" subnode="mqis_reg_ext" access="RW" offset="0x0.0" selected_by="MQIS" size="0x18.0" />
	<field name="mrpr_reg" descr="" subnode="mrpr_reg_ext" access="RW" offset="0x0.0" selected_by="MRPR" size="0x108.0" />
	<field name="msci" descr="" subnode="msci_ext" access="RW" offset="0x0.0" selected_by="MSCI" size="0xc.0" />
	<field name="msgcr_reg" descr="" subnode="msgcr_reg_ext" access="RW" offset="0x0.0" selected_by="MSGCR" size="0x8.0" />
	<field name="msgi" descr="" subnode="msgi_ext" access="RW" offset="0x0.0" selected_by="MSGI" size="0x80.0" />
	<field name="mslcg" descr="" subnode="mslcg_ext" access="RW" offset="0x0.0" selected_by="MSLCG" size="0x110.0" />
	<field name="mtbr_v2" descr="" subnode="mtbr_v2_ext" access="RW" offset="0x0.0" selected_by="MTBR_V2" size="0x90.0" />
	<field name="mtcap" descr="" subnode="mtcap_ext" access="RW" offset="0x0.0" selected_by="MTCAP" size="0x10.0" />
	<field name="mtcq_reg" descr="" subnode="mtcq_reg_ext" access="RW" offset="0x0.0" selected_by="MTCQ" size="0x70.0" />
	<field name="mtdc" descr="" subnode="mtdc_ext" access="RW" offset="0x0.0" selected_by="MTDC" size="0x20.0" />
	<field name="mtdth" descr="" subnode="mtdth_ext" access="RW" offset="0x0.0" selected_by="MTDTH" size="0x18.0" />
	<field name="mtecr" descr="" subnode="mtecr_ext" access="RW" offset="0x0.0" selected_by="MTECR" size="0x60.0" />
	<field name="mteim_reg" descr="" subnode="mteim_reg_ext" access="RW" offset="0x0.0" selected_by="MTEIM" size="0x30.0" />
	<field name="mteir_reg" descr="" subnode="mteir_reg_ext" access="RW" offset="0x0.0" selected_by="MTEIR" size="0xc.0" />
	<field name="mtewe" descr="" subnode="mtewe_ext" access="RW" offset="0x0.0" selected_by="MTEWE" size="0x10c.0" />
	<field name="mtie" descr="" subnode="mtie_ext" access="RW" offset="0x0.0" selected_by="MTIE" size="0x30.0" />
	<field name="mtim" descr="" subnode="mtim_ext" access="RW" offset="0x0.0" selected_by="MTIM" size="0x10.0" />
	<field name="mtmp" descr="" subnode="mtmp_ext" access="RW" offset="0x0.0" selected_by="MTMP" size="0x20.0" />
	<field name="mtpps_reg" descr="" subnode="mtpps_reg_ext" access="RW" offset="0x0.0" selected_by="MTPPS" size="0x38.0" />
	<field name="mtrc_cap_reg" descr="" subnode="mtrc_cap_reg_ext" access="RW" offset="0x0.0" selected_by="MTRC_CAP" size="0x84.0" />
	<field name="mtrc_conf_reg" descr="" subnode="mtrc_conf_reg_ext" access="RW" offset="0x0.0" selected_by="MTRC_CONF" size="0x80.0" />
	<field name="mtrc_ctrl_reg" descr="" subnode="mtrc_ctrl_reg_ext" access="RW" offset="0x0.0" selected_by="MTRC_CTRL" size="0x40.0" />
	<field name="mtrc_stdb_reg" descr="" subnode="mtrc_stdb_reg_ext" access="RW" offset="0x0.0" selected_by="MTRC_STDB" size="0xc.0" />
	<field name="mtutc_reg" descr="" subnode="mtutc_reg_ext" access="RW" offset="0x0.0" selected_by="MTUTC" size="0x1c.0" />
	<field name="mtwe" descr="" subnode="mtwe_ext" access="RW" offset="0x0.0" selected_by="MTWE" size="0x10.0" />
	<field name="mvcap_reg" descr="" subnode="mvcap_reg_ext" access="RW" offset="0x0.0" selected_by="MVCAP" size="0x10.0" />
	<field name="mvcr" descr="" subnode="mvcr_ext" access="RW" offset="0x0.0" selected_by="MVCR" size="0x18.0" />
	<field name="paos_reg" descr="" subnode="paos_reg_ext" access="RW" offset="0x0.0" selected_by="PAOS" size="0x10.0" />
	<field name="pbmc_reg" descr="" subnode="pbmc_reg_ext" access="RW" offset="0x0.0" selected_by="PBMC" size="0x6c.0" />
	<field name="pbsr_reg" descr="" subnode="pbsr_reg_ext" access="RW" offset="0x0.0" selected_by="PBSR" size="0x64.0" />
	<field name="pbwc" descr="" subnode="pbwc_ext" access="RW" offset="0x0.0" selected_by="PBWC" size="0x8.0" />
	<field name="pbwr" descr="" subnode="pbwr_ext" access="RW" offset="0x0.0" selected_by="PBWR" size="0x94.0" />
	<field name="pcam_reg" descr="" subnode="pcam_reg_ext" access="RW" offset="0x0.0" selected_by="PCAM" size="0x50.0" />
	<field name="pcap_reg" descr="" subnode="pcap_reg_ext" access="RW" offset="0x0.0" selected_by="PCAP" size="0x14.0" />
	<field name="pcct_reg" descr="" subnode="pcct_reg_ext" access="RW" offset="0x0.0" selected_by="PCCT" size="0x20.0" />
	<field name="pcmr_reg" descr="" subnode="pcmr_reg_ext" access="RW" offset="0x0.0" selected_by="PCMR" size="0xc.0" />
	<field name="pddr_reg" descr="" subnode="pddr_reg_ext" access="RW" offset="0x0.0" selected_by="PDDR" size="0x100.0" />
	<field name="pedcc_reg" descr="" subnode="pedcc_reg_ext" access="RW" offset="0x0.0" selected_by="PEDCC" size="0x64.0" />
	<field name="pevnt" descr="" subnode="pevnt_ext" access="RW" offset="0x0.0" selected_by="PEVNT" size="0x8.0" />
	<field name="pfcc_reg" descr="" subnode="pfcc_reg_ext" access="RW" offset="0x0.0" selected_by="PFCC" size="0x20.0" />
	<field name="pfldc" descr="" subnode="pfldc_ext" access="RW" offset="0x0.0" selected_by="PFLDC" size="0x24.0" />
	<field name="pfsc_reg" descr="" subnode="pfsc_reg_ext" access="RW" offset="0x0.0" selected_by="PFSC" size="0x10.0" />
	<field name="pgcb" descr="" subnode="pgcb_ext" access="RW" offset="0x0.0" selected_by="PGCB" size="0x2a0.0" />
	<field name="pglf_reg" descr="" subnode="pglf_reg_ext" access="RW" offset="0x0.0" selected_by="PGLF" size="0x2c.0" />
	<field name="pgmr" descr="" subnode="pgmr_ext" access="RW" offset="0x0.0" selected_by="PGMR" size="0x2c.0" />
	<field name="pgrrs" descr="" subnode="pgrrs_ext" access="RW" offset="0x0.0" selected_by="PGRRS" size="0x90.0" />
	<field name="pguid_reg" descr="" subnode="pguid_reg_ext" access="RW" offset="0x0.0" selected_by="PGUID" size="0x60.0" />
	<field name="phbr" descr="" subnode="phbr_ext" access="RW" offset="0x0.0" selected_by="PHBR" size="0x1c.0" />
	<field name="phrr_reg" descr="" subnode="phrr_reg_ext" access="RW" offset="0x0.0" selected_by="PHRR" size="0x68.0" />
	<field name="plcc_reg" descr="" subnode="plcc_reg_ext" access="RW" offset="0x0.0" selected_by="PLCC" size="0x18.0" />
	<field name="plds" descr="" subnode="plds_ext" access="RW" offset="0x0.0" selected_by="PLDS" size="0x18.0" />
	<field name="plib_reg" descr="" subnode="plib_reg_ext" access="RW" offset="0x0.0" selected_by="PLIB" size="0x10.0" />
	<field name="plibdb" descr="" subnode="plibdb_ext" access="RW" offset="0x0.0" selected_by="PLIBDB" size="0x10.0" />
	<field name="pltc_reg" descr="" subnode="pltc_reg_ext" access="RW" offset="0x0.0" selected_by="PLTC" size="0x10.0" />
	<field name="pmac_reg" descr="" subnode="pmac_reg_ext" access="RW" offset="0x0.0" selected_by="PMAC" size="0x28.0" />
	<field name="pmaos_reg" descr="" subnode="pmaos_reg_ext" access="RW" offset="0x0.0" selected_by="PMAOS" size="0x10.0" />
	<field name="pmcr_reg" descr="" subnode="pmcr_reg_ext" access="RW" offset="0x0.0" selected_by="PMCR" size="0x2c.0" />
	<field name="pmdr_reg" descr="" subnode="pmdr_reg_ext" access="RW" offset="0x0.0" selected_by="PMDR" size="0x48.0" />
	<field name="pmlp_reg" descr="" subnode="pmlp_reg_ext" access="RW" offset="0x0.0" selected_by="PMLP" size="0x40.0" />
	<field name="pmlr_reg" descr="" subnode="pmlr_reg_ext" access="RW" offset="0x0.0" selected_by="PMLR" size="0x28.0" />
	<field name="pmmp_reg" descr="" subnode="pmmp_reg_ext" access="RW" offset="0x0.0" selected_by="PMMP" size="0x40.0" />
	<field name="pmpc_reg" descr="" subnode="pmpc_reg_ext" access="RW" offset="0x0.0" selected_by="PMPC" size="0x20.0" />
	<field name="pmpd_reg" descr="" subnode="pmpd_reg_ext" access="RW" offset="0x0.0" selected_by="PMPD" size="0x30.0" />
	<field name="pmpe_reg" descr="" subnode="pmpe_reg_ext" access="RW" offset="0x0.0" selected_by="PMPE" size="0x28.0" />
	<field name="pmpr_reg" descr="" subnode="pmpr_reg_ext" access="RW" offset="0x0.0" selected_by="PMPR" size="0x10.0" />
	<field name="pmpt_reg" descr="" subnode="pmpt_reg_ext" access="RW" offset="0x0.0" selected_by="PMPT" size="0x1c.0" />
	<field name="pmtm_reg" descr="" subnode="pmtm_reg_ext" access="RW" offset="0x0.0" selected_by="PMTM" size="0x10.0" />
	<field name="pmtu_reg" descr="" subnode="pmtu_reg_ext" access="RW" offset="0x0.0" selected_by="PMTU" size="0x10.0" />
	<field name="ppad_reg" descr="" subnode="ppad_reg_ext" access="RW" offset="0x0.0" selected_by="PPAD" size="0x10.0" />
	<field name="ppaos_reg" descr="" subnode="ppaos_reg_ext" access="RW" offset="0x0.0" selected_by="PPAOS" size="0x10.0" />
	<field name="ppbmc_reg" descr="" subnode="ppbmc_reg_ext" access="RW" offset="0x0.0" selected_by="PPBMC" size="0x10.0" />
	<field name="ppbme_reg" descr="" subnode="ppbme_reg_ext" access="RW" offset="0x0.0" selected_by="PPBME" size="0x10.0" />
	<field name="ppbmp_reg" descr="" subnode="ppbmp_reg_ext" access="RW" offset="0x0.0" selected_by="PPBMP" size="0x30.0" />
	<field name="ppcnt_reg" descr="" subnode="ppcnt_reg_ext" access="RW" offset="0x0.0" selected_by="PPCNT" size="0x100.0" />
	<field name="ppdfd" descr="" subnode="ppdfd_ext" access="RW" offset="0x0.0" selected_by="PPDFD" size="0xc.0" />
	<field name="ppfcg" descr="" subnode="ppfcg_ext" access="RW" offset="0x0.0" selected_by="PPFCG" size="0x8.0" />
	<field name="pphcr" descr="" subnode="pphcr_ext" access="RW" offset="0x0.0" selected_by="PPHCR" size="0x5c.0" />
	<field name="pplm_reg" descr="" subnode="pplm_reg_ext" access="RW" offset="0x0.0" selected_by="PPLM" size="0x80.0" />
	<field name="pplr_reg" descr="" subnode="pplr_reg_ext" access="RW" offset="0x0.0" selected_by="PPLR" size="0x8.0" />
	<field name="pprm_reg" descr="" subnode="pprm_reg_ext" access="RW" offset="0x0.0" selected_by="PPRM" size="0x94.0" />
	<field name="pprt_reg" descr="" subnode="pprt_reg_ext" access="RW" offset="0x0.0" selected_by="PPRT" size="0x24.0" />
	<field name="ppsc_reg" descr="" subnode="ppsc_reg_ext" access="RW" offset="0x0.0" selected_by="PPSC" size="0x30.0" />
	<field name="ppslc" descr="" subnode="ppslc_ext" access="RW" offset="0x0.0" selected_by="PPSLC" size="0x34.0" />
	<field name="ppsld" descr="" subnode="ppsld_ext" access="RW" offset="0x0.0" selected_by="PPSLD" size="0x14.0" />
	<field name="ppsls" descr="" subnode="ppsls_ext" access="RW" offset="0x0.0" selected_by="PPSLS" size="0x8.0" />
	<field name="pptb_reg" descr="" subnode="pptb_reg_ext" access="RW" offset="0x0.0" selected_by="PPTB" size="0xc.0" />
	<field name="pptt_reg" descr="" subnode="pptt_reg_ext" access="RW" offset="0x0.0" selected_by="PPTT" size="0x1c.0" />
	<field name="ppwcc" descr="" subnode="ppwcc_ext" access="RW" offset="0x0.0" selected_by="PPWCC" size="0x20.0" />
	<field name="ppwdc" descr="" subnode="ppwdc_ext" access="RW" offset="0x0.0" selected_by="PPWDC" size="0xc.0" />
	<field name="ppwe" descr="" subnode="ppwe_ext" access="RW" offset="0x0.0" selected_by="PPWE" size="0xc.0" />
	<field name="ppwpt" descr="" subnode="ppwpt_ext" access="RW" offset="0x0.0" selected_by="PPWPT" size="0x410.0" />
	<field name="prcct" descr="" subnode="prcct_ext" access="RW" offset="0x0.0" selected_by="PRCCT" size="0x4.0" />
	<field name="prei_reg" descr="" subnode="prei_reg_ext" access="RW" offset="0x0.0" selected_by="PREI" size="0x18.0" />
	<field name="prtl_reg" descr="" subnode="prtl_reg_ext" access="RW" offset="0x0.0" selected_by="PRTL" size="0x20.0" />
	<field name="prtsr" descr="" subnode="prtsr_ext" access="RW" offset="0x0.0" selected_by="PRTSR" size="0x10.0" />
	<field name="ptasv2_reg" descr="" subnode="ptasv2_reg_ext" access="RW" offset="0x0.0" selected_by="PTASv2" size="0x4c.0" />
	<field name="pter_reg" descr="" subnode="pter_reg_ext" access="RW" offset="0x0.0" selected_by="PTER" size="0x20.0" />
	<field name="ptsb" descr="" subnode="ptsb_ext" access="RW" offset="0x0.0" selected_by="PTSB" size="0x20.0" />
	<field name="ptsr" descr="" subnode="ptsr_ext" access="RW" offset="0x0.0" selected_by="PTSR" size="0x20.0" />
	<field name="ptys_reg" descr="" subnode="ptys_reg_ext" access="RW" offset="0x0.0" selected_by="PTYS" size="0x44.0" />
	<field name="pude_reg" descr="" subnode="pude_reg_ext" access="RW" offset="0x0.0" selected_by="PUDE" size="0x10.0" />
	<field name="pvlc_reg" descr="" subnode="pvlc_reg_ext" access="RW" offset="0x0.0" selected_by="PVLC" size="0x10.0" />
	<field name="resource_dump" descr="" subnode="resource_dump_ext" access="RW" offset="0x0.0" selected_by="MORD" size="0xc8.0" />
	<field name="sllm_reg" descr="" subnode="sllm_reg_ext" access="RW" offset="0x0.0" selected_by="SLLM" size="0x30.0" />
	<field name="slmtrd_reg" descr="" subnode="slmtrd_reg_ext" access="RW" offset="0x0.0" selected_by="SLMTRD" size="0x10.0" />
	<field name="slprr_reg" descr="" subnode="slprr_reg_ext" access="RW" offset="0x0.0" selected_by="SLPRR" size="0x150.0" />
	<field name="slrg_reg" descr="" subnode="slrg_reg_ext" access="RW" offset="0x0.0" selected_by="SLRG" size="0x28.0" />
	<field name="slsir_reg" descr="" subnode="slsir_reg_ext" access="RW" offset="0x0.0" selected_by="SLSIR" size="0x94.0" />
	<field name="sltp_reg" descr="" subnode="sltp_reg_ext" access="RW" offset="0x0.0" selected_by="SLTP" size="0x4c.0" />
	<field name="sltpv2_reg" descr="" subnode="sltpv2_reg_ext" access="RW" offset="0x0.0" selected_by="SLTPv2" size="0x10c.0" />
	<field name="ukdri" descr="" subnode="ukdri_ext" access="RW" offset="0x0.0" selected_by="UKDRI" size="0x10.0" />
	<field name="undfd" descr="" subnode="undfd_ext" access="RW" offset="0x0.0" selected_by="UNDFD" size="0x8.0" />
	<field name="undri" descr="" subnode="undri_ext" access="RW" offset="0x0.0" selected_by="UNDRI" size="0x10.0" />
	<field name="unrc" descr="" subnode="unrc_ext" access="RW" offset="0x0.0" selected_by="UNRC" size="0x40.0" />
	<field name="unrsa" descr="" subnode="unrsa_ext" access="RW" offset="0x0.0" selected_by="UNRSA" size="0x18.0" />
	<field name="unwkm" descr="" subnode="unwkm_ext" access="RW" offset="0x0.0" selected_by="UNWKM" size="0x8c.0" />
</node>

<node name="access_reg_summary_selector_ext" descr="" attr_is_union="1" size="0x410.0" >
	<field name="access_reg_summary" descr="" subnode="access_reg_summary_ext" access="RW" offset="0x0.0" size="0x410.0" union_selector="$(parent).ctrl.id" />
	<field name="ctrl" descr="" subnode="access_reg_summary_ctrl_ext" access="RW" offset="0x0.0" size="0x4.0" />
</node>

<node name="bufferx_lossless_thresholds_ext" descr="" size="0x4.0" >
	<field name="xon_threshold" descr="When the amount of data in the buffer goes below this value, device\;stops sending pause frames for the Prios associated with the buffer.\;Units are represented in cells.For shared_headroom_pool, this field is reserved." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="xoff_threshold" descr="Once the amount of data in the buffer goes above this value, device\;starts sending Pause frames for all Prios associated with the buffer.\;Units are represented in cells.For shared_headroom_pool, this field is reserved." access="RW" offset="0x0.16" size="0x0.16" />
</node>

<node name="bufferx_reg_ext" descr="" size="0x8.0" >
	<field name="size" descr="The part of the packet buffer array is allocated for the specific\;buffer.Units are represented in cells.For shared_headroom_pool, this field represents the maximum loan from\;the shared headroom pool and it can be set only when port_shared_buffer\;is enabled.Range is" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="epsb" descr="Eligible for Port Shared buffer.If epsb is set, packets assigned to bufferX are allowed to insert the\;port shared buffer.For port_shared_buffer, this field is reserved.For shared_headroom_pool, this field is reserved.When lossy==1 this field is reserved.The field is reserved for Switch-X/-2." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="lossy" descr="The field indicates if the buffer is lossy.0: Lossless1: LossyThe field is reserved for Switch-X/-2.For port_shared_buffer, this field is reserved.For shared_headroom_pool, this field is reserved.NOTE: This field does NOT affect the pause control. Pause control is configured using PFCC register." access="RW" enum="Lossless=0x0,Lossy=0x1" offset="0x0.25" size="0x0.1" />
	<field name="drop_over_max_mask" descr="Write drop_over_mask for lossy buffers.Reserved on Query or when lossy=0.Supported only on Spectrum switches from Spectrum-3." access="OP" offset="0x0.26" size="0x0.1" />
	<field name="thresholds" descr="For lossless (lossy=0) see\;BufferX Lossless Thresholds Layout." subnode="bufferx_reg_thresholds_auto_ext" access="RW" offset="0x4.0" size="0x4.0" union_selector="$(parent).lossy" />
</node>

<node name="bufferx_reg_thresholds_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="bufferx_lossless_thresholds_ext" descr="" subnode="bufferx_lossless_thresholds_ext" access="RW" offset="0x0.0" selected_by="Lossless" size="0x4.0" />
</node>

<node name="config_item_ext" descr="" size="0xc.0" >
	<field name="length" descr="Length of configuration item data in bytes (not including header). Must\;be between 0 and 256." access="RW" offset="0x0.0" size="0x0.9" />
	<field name="host_id_valid" descr="Host ID valid:1: the type_index.host_id field is validValid only when MNVGC.priv_nv_other_host=1 and the type_class is a Host\;or Host-PF" access="INDEX" offset="0x0.9" size="0x0.1" />
	<field name="version" descr="Configuration item version – defines the data structure following the\;header (together with the type field)." access="RW" offset="0x0.12" size="0x0.4" />
	<field name="writer_id" descr="The entity which configured this parameter0x0: UNSPECIFIED0x1: CHASSIS_BMC0x2: MAD0x3: BMC0x4: COMMAND_INTERFACE0x5: ICMD - with unspecified source0x6: ICMD_UEFI_HII - configured by the NIC’s UEFI expansion ROM’s HII\;menu.0x7: ICMD_UEFI_CLP - configured by the NIC’s expansion ROM’s CLP.0x8: ICMD_Flexboot - configured by the NIC’s legacy expansion ROM.0x9: ICMD_mlxconfig - configured by Mellanox mlxconfig tool0xA: ICMD_USER1 - value available for customer created tools that\;uses the ICMD interface for writing TLVs.0xB: ICMD_USER2 - value available for customer created tools that\;uses the ICMD interface for writing TLVs.0xC: ICMD_MLXCONFIG_SET_RAW - configures bymlxconfig set raw operation.0xD: ICMD_FLEXBOOT_CLP - configured by Legacy Expansion ROM CLP0xE: CMIS_CDB - configured by VMOD CMIS CDB I/F0x10: BMC_APP1 - Configuration was done over the BMC0x11: BMC_APP2 - Configuration was done over the BMC0x12: BMP_APP3 - Configuration was done over the BMC0x1F: OTHER - the parameter was written by the NIC due to other\;reasons.Note - This field is writeable only when using the ICMD interface.\;The only value that are valid for writes are 0x6 through 0xB. Other\;values will be replaced by 0x5ICMD." access="RO" enum="UNSPECIFIED=0x0,CHASSIS_BMC=0x1,MAD=0x2,BMC=0x3,COMMAND_INTERFACE=0x4,ICMD=0x5,ICMD_UEFI_HII=0x6,ICMD_UEFI_CLP=0x7,ICMD_Flexboot=0x8,ICMD_mlxconfig=0x9,ICMD_USER1=0xa,ICMD_USER2=0xb,ICMD_MLXCONFIG_SET_RAW=0xc,ICMD_FLEXBOOT_CLP=0xd,CMIS_CDB=0xe,BMC_APP1=0x10,BMC_APP2=0x11,BMP_APP3=0x12,OTHER=0x1f" offset="0x0.16" size="0x0.5" />
	<field name="access_mode" descr="Defines which value of the Configuration Item will be accessed.0: NEXT - Next value to be applied1: CURRENT - Currently set values (only valid for Query\;operation)Supported only if NVGC.nvda_read_current_settings==1.2: FACTORY - Default factory values (only valid for Query operation).\;Supported only if NVGC.nvda_read_factory_settings==1." access="INDEX" enum="NEXT=0x0,CURRENT=0x1,FACTORY=0x2" offset="0x0.22" size="0x0.2" />
	<field name="rd_en" descr="Read EnableControls the read operation during different life-cycle stages.0: TLV cannot be read by the subsequent life-cycle priorities.1: TLV can be read by the subsequent life-cycle priorities." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="ovr_en" descr="Override Enable0: Can only be overwritten by the current life-cycle priority.1: Allowed to be over-written by the subsequent life-cycle priorities." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="priority" descr="The life-cycle priority of this configuration.0x0: USER,0x1: OEM,0x2: Reserved 0x3: MLNXThe priority is set by either:When using MNVDA, the TLV will have user priorityWhen using NVCONFIG, each TLV has its own priority" access="RO" offset="0x0.28" size="0x0.2" />
	<field name="type" descr="Configuration item index according to its type_class.Configuration Item Data Type Class Global LayoutConfiguration Item Data Type Class Physical Port LayoutConfiguration Item Data Type Class Per Host-PF LayoutConfiguration Item Data Type Class Log LayoutConfiguration Item Data Type Class File LayoutConfiguration Item Data Type Class Module LayoutConfiguration Item Data Type Class Multi Instance Layout" subnode="config_item_type_auto_ext" access="INDEX" offset="0x4.0" size="0x4.0" />
</node>

<node name="config_item_type_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="configuration_item_type_class_file_ext" descr="" subnode="configuration_item_type_class_file_ext" access="RW" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_global_ext" descr="" subnode="configuration_item_type_class_global_ext" access="RW" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_log_ext" descr="" subnode="configuration_item_type_class_log_ext" access="RW" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_module_ext" descr="" subnode="configuration_item_type_class_module_ext" access="RW" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_multi_instance_ext" descr="" subnode="configuration_item_type_class_multi_instance_ext" access="RW" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_per_host_pf_ext" descr="" subnode="configuration_item_type_class_per_host_pf_ext" access="RW" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_physical_port_ext" descr="" subnode="configuration_item_type_class_physical_port_ext" access="RW" offset="0x0.0" size="0x4.0" />
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
	<field name="pf_index" descr="If host_id_valid is set, indicates the PF ID, otherwise reserved." access="INDEX" offset="0x0.10" size="0x0.8" />
	<field name="host_id" descr="If host_id_valid is set, indicates the host ID, otherwise reserved." access="INDEX" offset="0x0.18" size="0x0.6" />
	<field name="type_class" descr="type_class = 0x3" access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="configuration_item_type_class_physical_port_ext" descr="" size="0x4.0" >
	<field name="parameter_index" descr="" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="port" descr="" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="type_class" descr="type_class = 0x1" access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="crspace_timeout_ext" descr="" size="0xa0.0" >
	<field name="log_address" descr="crspace address accessed, which resulted in timeout" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="log_id" descr="which irisc triggered the timeout" access="RO" offset="0x4.0" size="0x0.5" />
	<field name="error_type" descr="Crspace Error Type:0: timeout1: unmmaped_address2: pat_priv_error3: gmt_error4: terminate5: pri_error6: external_protocol_error" access="RO" enum="timeout=0x0,unmmaped_address=0x1,pat_priv_error=0x2,gmt_error=0x3,terminate=0x4,pri_error=0x5,external_protocol_error=0x6" offset="0x4.8" size="0x0.4" />
	<field name="trans_type" descr="Transaction Type0: unknown - (in ASICs that this indication do not exist)1: read2: non_posted_write3: posted_write" access="RW" enum="unknown=0x0,read=0x1,non_posted_write=0x2,posted_write=0x3" offset="0x4.13" size="0x0.3" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the timeout.[DWIP] Superseded by top level tile_v and tile_index. Kept for\;backwards compatibility." access="RO" offset="0x4.16" size="0x0.6" />
	<field name="tile_v" descr="Tile valid:0: The timeout was from main1: The timeout was from a tile[DWIP] Superseded by top level tile_v and tile_index. Kept for\;backwards compatibility." access="RO" offset="0x4.23" size="0x0.1" />
	<field name="oe" descr="Old Event:0: New event1: Old event, found during MFGD activation" access="RO" offset="0x4.24" size="0x0.1" />
	<field name="is_yu" descr="Timeout came from YU" access="RW" offset="0x4.29" size="0x0.1" />
	<field name="is_iron" descr="Timeout came from IRON" access="RW" offset="0x4.30" size="0x0.1" />
	<field name="is_main_farm" descr="timeout came from Main Fram" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="log_ip" descr="IP (instruction pointer) that triggered the timeout" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="cvb_config_error_ext" descr="" size="0xa0.0" >
	<field name="cvb_error_type" descr="0x0: VDD configuration error0x1: DVDD configuration error0x2: AVDD configuration error0xF: Other configuration error" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the timeout." access="RO" offset="0x4.0" size="0x0.4" />
	<field name="tile_v" descr="Tile valid:0: The cvb configuration is main related1: The cvb configuration is tile related" access="RO" offset="0x4.31" size="0x0.1" />
</node>

<node name="date_time_layout_ext" descr="" size="0x8.0" >
	<field name="hours" descr="hour (UTC) - 2 packed BCD digits" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="minutes" descr="minutes - 2 packed BCD digits" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="seconds" descr="seconds - 2 packed BCD digits" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="day" descr="day - 2 packed BCD digits" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="month" descr="month - 2 packed BCD digits" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="year" descr="year - 4 packed BCD digits" access="RW" offset="0x4.16" size="0x0.16" />
</node>

<node name="ef_afe_snap_v1_ext" descr="" size="0x8.0" >
	<field name="term_attn_ctrl" descr="" access="RO" offset="0x0.0" size="0x0.3" />
	<field name="dc_gain" descr="" access="RO" offset="0x0.3" size="0x0.3" />
	<field name="hf_gain" descr="" access="RO" offset="0x0.6" size="0x0.8" />
	<field name="lf_gain" descr="" access="RO" offset="0x0.14" size="0x0.2" />
	<field name="lf_pole" descr="" access="RO" offset="0x0.16" size="0x0.2" />
	<field name="mf_gain" descr="" access="RO" offset="0x0.18" size="0x0.2" />
	<field name="mf_pole" descr="" access="RO" offset="0x0.20" size="0x0.2" />
	<field name="tah_amp_gain" descr="" access="RO" offset="0x0.22" size="0x0.4" />
	<field name="adc_vref_val" descr="" access="RO" offset="0x0.26" size="0x0.6" />
	<field name="cdr_offset" descr="" access="RO" offset="0x4.0" size="0x0.8" />
</node>

<node name="ef_lt_x_feq_ber_db_v1_ext" descr="" size="0x44.0" >
	<field name="iter_table" descr="Iteration results table. Array of 5 96-bit elements, 3 DWORDs\;each (iter_table[0] at 00h–08h, iter_table[4] at 30h–38h)." subnode="ef_lt_x_feq_ber_entry_v1_ext" access="RO" high_bound="4" low_bound="0" offset="0x0.0" size="0x3c.0" />
	<field name="stores_done" descr="Debug mirror of PHY lt_x_index (last stored count)." access="RO" offset="0x3c.0" size="0x0.4" />
	<field name="winner_idx" descr="Index of the entry with the best BER." access="RO" offset="0x3c.4" size="0x0.4" />
	<field name="protocol_violation" descr="Stamp mismatch detected during validation." access="RO" offset="0x40.0" size="0x0.1" />
	<field name="violation_idx" descr="Which entry had the stamp violation." access="RO" offset="0x40.1" size="0x0.4" />
	<field name="violation_type" descr="Which stamp was missing during validation.0: none1: no_serdes_stamp2: no_phy_stamp3: both" access="RO" enum="none=0x0,no_serdes_stamp=0x1,no_phy_stamp=0x2,both=0x3" offset="0x40.5" size="0x0.2" />
	<field name="force_applied" descr="force_best_afe_values was called." access="RO" offset="0x40.7" size="0x0.1" />
	<field name="last_fail_stage" descr="Last failure point in the LT-X store/force flow.0: ok1: reserved_12: phy_update_rejected3: force_no_valid_entry4: reserved_45: phy_bad_index_overflow" access="RO" enum="ok=0x0,reserved_1=0x1,phy_update_rejected=0x2,force_no_valid_entry=0x3,reserved_4=0x4,phy_bad_index_overflow=0x5" offset="0x40.8" size="0x0.4" />
</node>

<node name="ef_lt_x_feq_ber_entry_v1_ext" descr="" size="0xc.0" >
	<field name="afe_snap" descr="AFE (Analog Front End) configuration snapshot, 2 DWORDs." subnode="ef_afe_snap_v1_ext" access="RO" offset="0x0.0" size="0x8.0" />
	<field name="ber_magnitude" descr="BER exponent; BER = ber_coeff.ber_coeff_float × 10^(−ber_magnitude)." access="RO" offset="0x8.0" size="0x0.8" />
	<field name="ber_coeff" descr="BER coefficient integer part." access="RO" offset="0x8.8" size="0x0.4" />
	<field name="ber_coeff_float" descr="BER coefficient fractional digit." access="RO" offset="0x8.12" size="0x0.4" />
	<field name="serdes_valid" descr="Set by SerDes after storing the AFE snap." access="RO" offset="0x8.16" size="0x0.1" />
	<field name="phy_valid" descr="Set by PHY after writing the BER fields." access="RO" offset="0x8.17" size="0x0.1" />
	<field name="meas_invalid" descr="PHY-set flag: BER measurement is invalid (no PCS lock at measurement\;start, or alignment lost mid-window). The picker must skip this entry." access="RO" offset="0x8.18" size="0x0.1" />
</node>

<node name="ef_lt_x_port_info_v1_ext" descr="" size="0x4.0" >
	<field name="ltx_restore_count" descr="LTX_EN_RESTORE retries this bringup (0–63)." access="RO" offset="0x0.0" size="0x0.6" />
	<field name="ltx_total_rounds_cnt" descr="Complete LT-X cycles; saturates at 7." access="RO" offset="0x0.6" size="0x0.3" />
	<field name="num_ber_meas_done" descr="BER iterations done." access="RO" offset="0x0.9" size="0x0.4" />
	<field name="auto_reversals_applied" descr="Auto-fix-reversals swapped lanes." access="RO" offset="0x0.13" size="0x0.1" />
	<field name="ltx_limiter_allow" descr="Round count is below lt_x_full_cycle_limit." access="RO" offset="0x0.14" size="0x0.1" />
	<field name="ltx_reached_max_retry" descr="Sticky: load_best hit retry cap." access="RO" offset="0x0.15" size="0x0.1" />
	<field name="entered_ltx_flow" descr="LT-X flow was entered." access="RO" offset="0x0.16" size="0x0.1" />
	<field name="ber_based_in_progress" descr="BER-based flow in progress at snapshot." access="RO" offset="0x0.17" size="0x0.1" />
</node>

<node name="ef_ptasv2_3nm_apsu_ctrl_v1_ext" descr="" size="0x18.0" >
	<field name="apsu_cap" descr="Set if APSU (ILT/RTS) capability is supported" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="apsu_ctl" descr="Control the APSU (ILT/RTS) activation if apsu_cap = 10: Default. Default = 11: Enable2: Disable" access="RW" offset="0x0.1" size="0x0.2" />
	<field name="apsu_oper" descr="APSU (ILT/RTS) operational mode.1: APSU enabled2: APSU disabled" access="RO" offset="0x0.3" size="0x0.2" />
	<field name="hop_count_cap" descr="Set if hop count capability is supported" access="RO" offset="0x0.5" size="0x0.1" />
	<field name="hop_count_ctl" descr="Control the hop count for TRO activation if hop_count_cap = 10: Default. Default = 1 for TRO, 0 otherwise1: Enable2: Disable" access="RW" offset="0x0.6" size="0x0.2" />
	<field name="hop_count_oper" descr="Hop count operational mode.1: Hop count enabled2: Hop count disabled" access="RO" offset="0x0.8" size="0x0.2" />
	<field name="peer_det_cap" descr="Set if peer detection capability is supported" access="RO" offset="0x0.10" size="0x0.1" />
	<field name="lt_peer_det_ctl" descr="Control the Link Training peer detection activation if lt_peer_det_cap = 10: Default. Default= 11: Enable2: Disable" access="RW" offset="0x0.11" size="0x0.2" />
	<field name="lt_peer_det_oper" descr="Peer detection operational mode.1: Peer detection enabled2: Peer detection disabled" access="RO" offset="0x0.13" size="0x0.2" />
	<field name="nlut_cap" descr="Set if nLUTn capability is supported" access="RO" offset="0x0.15" size="0x0.1" />
	<field name="nlut_ctl" descr="Control the nLUT activation if nlut_cap = 10: Default. Default = 0 for electrical interfaces, 1 for optical interfaces1: Enable2: Disable" access="RW" offset="0x0.16" size="0x0.2" />
	<field name="nlut_oper" descr="nLUTn operational mode.1: nLUT enabled2: nLUT disabled" access="RO" offset="0x0.18" size="0x0.2" />
	<field name="mr_training_enable_cap" descr="Set if training_enable can be clear when apsu_oper = 1" access="RO" offset="0x0.20" size="0x0.1" />
	<field name="training_en_ctl" descr="Control the training_en configuration if training_en_cap = 10: Default. Default = 11: Enable training2: Disable training" access="RW" offset="0x0.21" size="0x0.2" />
	<field name="training_en_oper" descr="APSU training  operational mode.1: Training enabled2: Training disabled" access="RO" offset="0x0.23" size="0x0.2" />
	<field name="restart_training" descr="Set to restart APSU" access="WO" offset="0x0.31" size="0x0.1" />
	<field name="recovery_timer" descr="Time to recover from a loss of training frame sync event. System parameter0: Disable.1:255: Number of milliseconds" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="max_recovery_events" descr="Number os times that training frames can be lost before fail. Syatme parameter0: Disable.1:255: maximum allowed number of transitions into the RECOVERY state in the Training control state diagram" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="max_wait_timer" descr="Maximum time to perform link training in 802.3dj in seconds. System parameter.Default: 30 for electrical interfaces, 60 for optical interfaces" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="propagation_timer" descr="Time to wait before moving from training to data forwarding. Used to guarantee that the whiole path is ready. System parameter.0: Disabled.1 - 31: 10 msec to 310 msec timer in 10 msec granularity.Default = 10" access="RW" offset="0x8.22" size="0x0.5" />
	<field name="quiet_timer" descr="Squelch time before restarting APSU. System parameter.0: Disable.1 - 31: 10 msec to 310 msec timer in 10 msec granularity.Default = 20" access="RW" offset="0x8.28" size="0x0.4" />
	<field name="invert_to" descr="Invert to timer. System parameter.0: Disable.1 - 15: Number of millisecondsDefault = 5" access="RW" offset="0xc.0" size="0x0.4" />
	<field name="tf_detect_timer" descr="This timer limits the time synchronization on link training frames is searched after modulation_detect becomes true. Per system timer.0: Disable1-15: Number of milliseconds allowed to detect link train frames." access="RW" offset="0xc.6" size="0x0.4" />
	<field name="fail_timer" descr="This timer limits the allowed failure time before an APSU restart is forced. It is started when modulation_detect = false is detected in any lane of the port. Per system timer.0: Disable1-255: of 10’s of milliseconds before restarting due to signal fail.Default = 100" access="RW" offset="0xc.16" size="0x0.8" />
	<field name="validation_timer" descr="This timer limits the time local_tf_lock shall be true before APSU restart is forced. Relevant only if validation_en = 1. Per system timer.0: Disable.1-15: Number of 10’s of milliseconds local_tf_lock shall be stable.Default = 1" access="RW" offset="0xc.26" size="0x0.4" />
	<field name="local_pattern_tx" descr="Select local pattern for APSU. System parameter.0: PRBS311: PCS data0: Default. Default = 0" access="RW" offset="0xc.31" size="0x0.1" />
	<field name="restart_on_los" descr="Select the behavior under signal los. System parameter0: Do not restart on signal los1: Restart on signal los2: Restart only on long signal losDefault = 1" access="RW" offset="0x10.6" size="0x0.2" />
	<field name="validation_en" descr="Allow received ILT frames validation timer. Relevant only if rx_fail_on_los = 0. System parameter.0: Validation disabled1: Validation enabled0: Default. Default = 0" access="RW" offset="0x10.9" size="0x0.1" />
	<field name="bcnl_pages_retransmissions" descr="Number of times the nLUT backchannel pages are sent. System parameter.1-255: Retransmit each page timesDefault = 95" access="RW" offset="0x14.0" size="0x0.8" />
</node>

<node name="ef_ptasv2_3nm_prbs_v1_ext" descr="" size="0x30.0" >
	<field name="lane0_seed_prbs31" descr="PRBS31 training sequence seed for lane 0." access="RW" offset="0x0.0" size="0x0.31" />
	<field name="lane1_seed_prbs31" descr="PRBS31 training sequence seed for lane 1." access="RW" offset="0x4.0" size="0x0.31" />
	<field name="lane2_seed_prbs31" descr="PRBS31 training sequence seed for lane 2." access="RW" offset="0x8.0" size="0x0.31" />
	<field name="lane3_seed_prbs31" descr="PRBS31 training sequence seed for lane 3." access="RW" offset="0xc.0" size="0x0.31" />
	<field name="lane4_seed_prbs31" descr="PRBS31 training sequence seed for lane 4." access="RW" offset="0x10.0" size="0x0.31" />
	<field name="lane5_seed_prbs31" descr="PRBS31 training sequence seed for lane 5." access="RW" offset="0x14.0" size="0x0.31" />
	<field name="lane6_seed_prbs31" descr="PRBS31 training sequence seed for lane 6." access="RW" offset="0x18.0" size="0x0.31" />
	<field name="lane7_seed_prbs31" descr="PRBS31 training sequence seed for lane 7." access="RW" offset="0x1c.0" size="0x0.31" />
	<field name="lane1_seed_prbs13" descr="PRBS13 training sequence seed for lane 1." access="RW" offset="0x20.0" size="0x0.13" />
	<field name="lane0_seed_prbs13" descr="PRBS13 training sequence seed for lane 0." access="RW" offset="0x20.16" size="0x0.13" />
	<field name="lane3_seed_prbs13" descr="PRBS13 training sequence seed for lane 3." access="RW" offset="0x24.0" size="0x0.13" />
	<field name="lane2_seed_prbs13" descr="PRBS13 training sequence seed for lane 2." access="RW" offset="0x24.16" size="0x0.13" />
	<field name="lane5_seed_prbs13" descr="PRBS13 training sequence seed for lane 5." access="RW" offset="0x28.0" size="0x0.13" />
	<field name="lane4_seed_prbs13" descr="PRBS13 training sequence seed for lane 4." access="RW" offset="0x28.16" size="0x0.13" />
	<field name="lane7_seed_prbs13" descr="PRBS13 training sequence seed for lane 7." access="RW" offset="0x2c.0" size="0x0.13" />
	<field name="lane6_seed_prbs13" descr="PRBS13 training sequence seed for lane 6." access="RW" offset="0x2c.16" size="0x0.13" />
</node>

<node name="enum_entry" descr="" size="0x4.0" >
</node>

<node name="eth_2819_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="ether_stats_drop_events_high" descr="The total number of events in which packets were dropped by the probe\;due to lack of resources." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="ether_stats_drop_events_low" descr="(see above)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ether_stats_octets_high" descr="The total number of octets of data (including those in bad packets)\;received (excluding framing bits but including FCS octets)." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ether_stats_octets_low" descr="(see above)" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="ether_stats_pkts_high" descr="The total number of packets (including bad packets, broadcast packets,\;and multicast packets) received." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="ether_stats_pkts_low" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="ether_stats_broadcast_pkts_high" descr="The total number of good packets received that were directed to the\;broadcast address.Note: This does not include multicast packets." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="ether_stats_broadcast_pkts_low" descr="(see above)" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="ether_stats_multicast_pkts_high" descr="The total number of good packets received that were directed to a\;multicast MAC address.Note: This number does not include packets directed to the broadcast\;address." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="ether_stats_multicast_pkts_low" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_high" descr="The total number of packets received that had a length (excluding\;framing bits, but including FCS octets) of between 64 and\;MTU octets, inclusive, but had either\;a bad frame check sequence (FCS) with an integral number of octets (FCS\;error) or a bad FCS with a non-integral number of octets (alignment\;error)." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_low" descr="(see above)" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_high" descr="The total number of packets received that were less than 64 octets long\;(excluding framing bits, but including FCS octets) and were otherwise\;well formed." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_low" descr="(see above)" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_high" descr="The total number of packets received that were longer than MTU octets\;(excluding framing bits, but including FCS octets) but were otherwise\;well formed." access="RO" offset="0x38.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_low" descr="(see above)" access="RO" offset="0x3c.0" size="0x4.0" />
	<field name="ether_stats_fragments_high" descr="The total number of packets received that were less than 64 octets in\;length (excluding framing bits but including FCS octets) and had either\;a bad FCS with an integral number of octets (FCS error) or a bad FCS\;with a non-integral number of octets (alignment error)." access="RO" offset="0x40.0" size="0x4.0" />
	<field name="ether_stats_fragments_low" descr="(see above)" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="ether_stats_jabbers_high" descr="The total number of packets received that were longer than MTU octets\;(excluding framing bits, but including FCS octets), and had either a bad\;FCS with an integral number of octets (FCS error) or a bad FCS with a\;non-integral number of octets (alignment error)." access="RO" offset="0x48.0" size="0x4.0" />
	<field name="ether_stats_jabbers_low" descr="(see above)" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="ether_stats_collisions_high" descr="The best estimate of the total number of collisions on this Ethernet\;segment." access="RO" offset="0x50.0" size="0x4.0" />
	<field name="ether_stats_collisions_low" descr="(see above)" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="ether_stats_pkts64octets_high" descr="The total number of packets (including bad packets) received that were\;64 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x58.0" size="0x4.0" />
	<field name="ether_stats_pkts64octets_low" descr="(see above)" access="RO" offset="0x5c.0" size="0x4.0" />
	<field name="ether_stats_pkts65to127octets_high" descr="The total number of packets (including bad packets) received that were\;between 65 and 127 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="ether_stats_pkts65to127octets_low" descr="(see above)" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="ether_stats_pkts128to255octets_high" descr="The total number of packets (including bad packets) received that were\;between 128 and 255 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="ether_stats_pkts128to255octets_low" descr="(see above)" access="RO" offset="0x6c.0" size="0x4.0" />
	<field name="ether_stats_pkts256to511octets_high" descr="The total number of packets (including bad packets) received that were\;between 256 and 511 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="ether_stats_pkts256to511octets_low" descr="(see above)" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="ether_stats_pkts512to1023octets_high" descr="The total number of packets (including bad packets) received that were\;between 512 and 1023 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x78.0" size="0x4.0" />
	<field name="ether_stats_pkts512to1023octets_low" descr="(see above)" access="RO" offset="0x7c.0" size="0x4.0" />
	<field name="ether_stats_pkts1024to1518octets_high" descr="The total number of packets (including bad packets) received that were\;between 1024 and 1518 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="ether_stats_pkts1024to1518octets_low" descr="(see above)" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="ether_stats_pkts1519to2047octets_high" descr="The total number of packets (including bad packets) received that were\;between 1519 and 2047 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="ether_stats_pkts1519to2047octets_low" descr="(see above)" access="RO" offset="0x8c.0" size="0x4.0" />
	<field name="ether_stats_pkts2048to4095octets_high" descr="The total number of packets (including bad packets) received that were\;between 2048 and 4095 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x90.0" size="0x4.0" />
	<field name="ether_stats_pkts2048to4095octets_low" descr="(see above)" access="RO" offset="0x94.0" size="0x4.0" />
	<field name="ether_stats_pkts4096to8191octets_high" descr="The total number of packets (including bad packets) received that were\;between 4096 and 8191 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x98.0" size="0x4.0" />
	<field name="ether_stats_pkts4096to8191octets_low" descr="(see above)" access="RO" offset="0x9c.0" size="0x4.0" />
	<field name="ether_stats_pkts8192to10239octets_high" descr="The total number of packets (including bad packets) received that were\;between 8192 and 10239 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0xa0.0" size="0x4.0" />
	<field name="ether_stats_pkts8192to10239octets_low" descr="(see above)" access="RO" offset="0xa4.0" size="0x4.0" />
</node>

<node name="eth_2863_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="if_in_octets_high" descr="The total number of octets received, including framing characters.\;Including MAC control frames." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="if_in_octets_low" descr="(see above)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="if_in_ucast_pkts_high" descr="The number of packets successfully received, which were not addressed to\;a multicast or broadcast MAC address." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="if_in_ucast_pkts_low" descr="(see above)" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="if_in_discards_high" descr="The number of inbound packets which were chosen to be discarded even\;though no errors had been detected to prevent their being deliverable to\;a higher-layer protocol." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="if_in_discards_low" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="if_in_errors_high" descr="The number of inbound packets that contained errors preventing them from\;being deliverable to a higher-layer protocol." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="if_in_errors_low" descr="(see above)" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="if_in_unknown_protos_high" descr="The number of packets received via the interface which were discarded\;because of an unknown or unsupported protocol." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="if_in_unknown_protos_low" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="if_out_octets_high" descr="The total number of octets transmitted out of the interface, including\;framing characters." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="if_out_octets_low" descr="(see above)" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_high" descr="The total number of packets that higher-level protocols requested be\;transmitted and were not addressed to a multicast or broadcast MAC\;address, including those that were discarded or not sent." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_low" descr="(see above)" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="if_out_discards_high" descr="The number of outbound packets which were chosen to be discarded, even\;though no errors had been detected to prevent their being transmitted." access="RO" offset="0x38.0" size="0x4.0" />
	<field name="if_out_discards_low" descr="(see above)" access="RO" offset="0x3c.0" size="0x4.0" />
	<field name="if_out_errors_high" descr="The number of outbound packets that could not be transmitted because of\;errors." access="RO" offset="0x40.0" size="0x4.0" />
	<field name="if_out_errors_low" descr="(see above)" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="if_in_multicast_pkts_high" descr="The number of packets successfully received, which were addressed to a\;multicast MAC address." access="RO" offset="0x48.0" size="0x4.0" />
	<field name="if_in_multicast_pkts_low" descr="(see above)" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="if_in_broadcast_pkts_high" descr="The number of packets successfully received, which were addressed to a\;broadcast MAC address." access="RO" offset="0x50.0" size="0x4.0" />
	<field name="if_in_broadcast_pkts_low" descr="(see above)" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="if_out_multicast_pkts_high" descr="The total number of packets that higher-level protocols requested be\;transmitted, and which were addressed to a multicast MAC address,\;including those that were discarded or not sent." access="RO" offset="0x58.0" size="0x4.0" />
	<field name="if_out_multicast_pkts_low" descr="(see above)" access="RO" offset="0x5c.0" size="0x4.0" />
	<field name="if_out_broadcast_pkts_high" descr="The total number of packets that higher-level protocols requested be\;transmitted, and which were addressed to a broadcast MAC address,\;including those that were discarded or not sent." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="if_out_broadcast_pkts_low" descr="(see above)" access="RO" offset="0x64.0" size="0x4.0" />
</node>

<node name="eth_3635_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="dot3stats_alignment_errors_high" descr="A count of frames received that are not an integral number of octets in\;length and do not pass the FCS check." access="RW" offset="0x0.0" size="0x4.0" />
	<field name="dot3stats_alignment_errors_low" descr="(see above)" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="dot3stats_fcs_errors_high" descr="A count of frames received that are an integral number of octets in\;length but do not pass the FCS check. This count does not include frames\;received with frame-too-long or frame-too-short errors." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="dot3stats_fcs_errors_low" descr="(see above)" access="RW" offset="0xc.0" size="0x4.0" />
	<field name="dot3stats_single_collision_frames_high" descr="A count of frames that are involved in a single collision, and are\;subsequently transmitted successfully.This counter does not increment when the interface is operating in\;full-duplex mode." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="dot3stats_single_collision_frames_low" descr="(see above)" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="dot3stats_multiple_collision_frames_high" descr="A count of frames that are involved in more than one collision and are\;subsequently transmitted successfully.This counter does not increment when the interface is operating in\;full-duplex mode." access="RW" offset="0x18.0" size="0x4.0" />
	<field name="dot3stats_multiple_collision_frames_low" descr="(see above)" access="RW" offset="0x1c.0" size="0x4.0" />
	<field name="dot3stats_sqe_test_errors_high" descr="A count of times that the SQE TEST ERROR is received on a particular\;interface.This counter does not increment on interfaces operating at speeds\;greater than 10 Mb/s, or on interfaces operating in full-duplex mode." access="RW" offset="0x20.0" size="0x4.0" />
	<field name="dot3stats_sqe_test_errors_low" descr="(see above)" access="RW" offset="0x24.0" size="0x4.0" />
	<field name="dot3stats_deferred_transmissions_high" descr="A count of frames for which the first transmission attempt on a\;particular interface is delayed because the medium is busy.This counter does not increment when the interface is operating in\;full-duplex mode." access="RW" offset="0x28.0" size="0x4.0" />
	<field name="dot3stats_deferred_transmissions_low" descr="(see above)" access="RW" offset="0x2c.0" size="0x4.0" />
	<field name="dot3stats_late_collisions_high" descr="The number of times that a collision is detected on a particular\;interface later than one slotTime into the transmission of a packet.This counter does not increment when the interface is operating in\;full-duplex mode." access="RW" offset="0x30.0" size="0x4.0" />
	<field name="dot3stats_late_collisions_low" descr="(see above)" access="RW" offset="0x34.0" size="0x4.0" />
	<field name="dot3stats_excessive_collisions_high" descr="A count of frames for which transmission on a particular interface fails\;due to excessive collisions.This counter does not increment when the interface is operating in\;full-duplex mode." access="RW" offset="0x38.0" size="0x4.0" />
	<field name="dot3stats_excessive_collisions_low" descr="(see above)" access="RW" offset="0x3c.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_transmit_errors_high" descr="A count of frames for which transmission failed and were discarded even\;though no errors had been detected to prevent their being deliverable to\;a higher-layer protocol." access="RW" offset="0x40.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_transmit_errors_low" descr="(see above)" access="RW" offset="0x44.0" size="0x4.0" />
	<field name="dot3stats_carrier_sense_errors_high" descr="The number of times that the carrier sense condition was lost or never\;asserted when attempting to transmit a frame on a particular interface.This counter does not increment when the interface is operating in\;full-duplex mode." access="RW" offset="0x48.0" size="0x4.0" />
	<field name="dot3stats_carrier_sense_errors_low" descr="(see above)" access="RW" offset="0x4c.0" size="0x4.0" />
	<field name="dot3stats_frame_too_longs_high" descr="A count of frames received that exceed the maximum permitted frame size." access="RW" offset="0x50.0" size="0x4.0" />
	<field name="dot3stats_frame_too_longs_low" descr="(see above)" access="RW" offset="0x54.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_receive_errors_high" descr="A count of frames for which reception failed and were discarded even\;though no errors had been detected to prevent their being deliverable to\;a higher-layer protocol." access="RW" offset="0x58.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_receive_errors_low" descr="(see above)" access="RW" offset="0x5c.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_high" descr="The number of times the receiving media is non-idle (a carrier event)\;for a period of time equal to or greater than minFrameSize, and during\;which there was at least one occurrence of an event that causes the PHY\;to indicate ‘Receive Error’." access="RW" offset="0x60.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_low" descr="(see above)" access="RW" offset="0x64.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_high" descr="A count of MAC Control frames received that contain an opcode that is\;not supported." access="RW" offset="0x68.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_low" descr="(see above)" access="RW" offset="0x6c.0" size="0x4.0" />
	<field name="dot3in_pause_frames_high" descr="A count of MAC Control frames received with an opcode indicating the\;PAUSE operation." access="RW" offset="0x70.0" size="0x4.0" />
	<field name="dot3in_pause_frames_low" descr="(see above)" access="RW" offset="0x74.0" size="0x4.0" />
	<field name="dot3out_pause_frames_high" descr="A count of MAC Control frames transmitted with an opcode indicating the\;PAUSE operation." access="RW" offset="0x78.0" size="0x4.0" />
	<field name="dot3out_pause_frames_low" descr="(see above)" access="RW" offset="0x7c.0" size="0x4.0" />
</node>

<node name="eth_discard_cntrs_grp_ext" descr="" size="0xf8.0" >
	<field name="ingress_general_high" descr="Ingress general" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="ingress_general_low" descr="(see above)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ingress_policy_engine_high" descr="Ingress policy engine discards" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ingress_policy_engine_low" descr="(see above)" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="ingress_vlan_membership_high" descr="Ingress VLAN membership filter discards" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="ingress_vlan_membership_low" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="ingress_tag_frame_type_high" descr="Ingress VLAN tag allowance (tagged, untagged and prio-tagged) filter\;discards" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="ingress_tag_frame_type_low" descr="(see above)" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="egress_vlan_membership_high" descr="Egress VLAN membership filter discards" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="egress_vlan_membership_low" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="loopback_filter_high" descr="Loop-back filter discards" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="loopback_filter_low" descr="(see above)" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="egress_general_high" descr="Egress general discards" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="egress_general_low" descr="(see above)" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="egress_link_down_high" descr="Egress link down discardsNote: Not supported on SPC1" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="egress_link_down_low" descr="(see above)" access="RO" offset="0x3c.0" size="0x4.0" />
	<field name="egress_hoq_high" descr="Head-of-Queue time-out discards" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="egress_hoq_low" descr="(see above)" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="port_isolation_high" descr="Port isolation filter discards" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="port_isolation_low" descr="(see above)" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="egress_policy_engine_high" descr="Egress policy engine discards" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="egress_policy_engine_low" descr="(see above)" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="egress_stp_filter_high" descr="Egress spanning tree filter" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="egress_stp_filter_low" descr="(see above)" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="egress_hoq_stall_high" descr="Number of sequential packets dropped, due to Head-Of-Queue Lifetime\;Limit, that causes the port to enter the Stall stateReserved for Switches" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="egress_hoq_stall_low" descr="(see above)" access="RO" offset="0x6c.0" size="0x4.0" />
	<field name="egress_sll_high" descr="Number of packets dropped, because the Switch Lifetime Limit was\;exceeded.Applies for switches only. Reserved for HCAs" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="egress_sll_low" descr="(see above)" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="ingress_discard_all_high" descr="Number of packets dropped for of any reason.Note: see description in the description area for limitations of this\;counter.Applies for switches only. Reserved for HCAsNote: deprecated for all Ethernet devices" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="ingress_discard_all_low" descr="(see above)" access="RO" offset="0x7c.0" size="0x4.0" />
	<field name="ingress_no_tx_high" descr="[Draft] Number of packets dropped at ingress for lack of TX list.Triggered by DISCARD_LOOKUP_SWITCH or more specifically\;DISCARD_LOOKUP_SWITCH_UC, DISCARD_LOOKUP_SWITCH_MC_NULL or\;DISCARD_LOOKUP_SWITCH_NO_PORTS. See 12413.Supported on switches only from Spectrum-4." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="ingress_no_tx_low" descr="(see above)" access="RO" offset="0x84.0" size="0x4.0" />
</node>

<node name="eth_extended_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="port_transmit_wait_high" descr="The number of wire speed one-byte period(s) during which the port had\;data to transmit but no data was sent" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="port_transmit_wait_low" descr="(see above)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ecn_marked_high" descr="A count of packets marked as ECN or potentially marked as ECN.ECN Counting enable/disable is configurable.Valid only for Spectrum family." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ecn_marked_low" descr="(see above)" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="no_buffer_discard_mc_high" descr="The number of multicast packets dropped due to lack of egress buffer\;resources.Valid only for Spectrum." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="no_buffer_discard_mc_low" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="rx_ebp_high" descr="The number of received EBP packets." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="rx_ebp_low" descr="(see above)" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="tx_ebp_high" descr="The number of transmitted EBP packets." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="tx_ebp_low" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="rx_buffer_almost_full_high" descr="The number of events where the port rx buffer has passed a fullness\;thresholdReserved for Switches." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="rx_buffer_almost_full_low" descr="(see above)" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="rx_buffer_full_high" descr="The number of events where the port rx buffer has reached 100% fullnessReserved for Switches." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="rx_buffer_full_low" descr="(see above)" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="rx_icrc_encapsulated_high" descr="The number of roce packets with ICRC errorReserved for Switches." access="RO" offset="0x38.0" size="0x4.0" />
	<field name="rx_icrc_encapsulated_low" descr="(see above)" access="RO" offset="0x3c.0" size="0x4.0" />
	<field name="tx_stats_pkts64octets_high" descr="The total number of packets (including bad packets) transmitted that\;were 64 octets in length (excluding framing bits but including FCS\;octets)." access="RO" offset="0x50.0" size="0x4.0" />
	<field name="tx_stats_pkts64octets_low" descr="(see above)" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="tx_stats_pkts65to127octets_high" descr="The total number of packets (including bad packets) transmitted that\;were between 65 and 127 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x58.0" size="0x4.0" />
	<field name="tx_stats_pkts65to127octets_low" descr="(see above)" access="RO" offset="0x5c.0" size="0x4.0" />
	<field name="tx_stats_pkts128to255octets_high" descr="The total number of packets (including bad packets) transmitted that\;were between 128 and 255 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="tx_stats_pkts128to255octets_low" descr="(see above)" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="tx_stats_pkts256to511octets_high" descr="The total number of packets (including bad packets) transmitted that\;were between 256 and 511 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="tx_stats_pkts256to511octets_low" descr="(see above)" access="RO" offset="0x6c.0" size="0x4.0" />
	<field name="tx_stats_pkts512to1023octets_high" descr="The total number of packets (including bad packets) transmitted that\;were between 512 and 1023 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="tx_stats_pkts512to1023octets_low" descr="(see above)" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="tx_stats_pkts1024to1518octets_high" descr="The total number of packets (including bad packets) transmitted that\;were between 1024 and 1518 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x78.0" size="0x4.0" />
	<field name="tx_stats_pkts1024to1518octets_low" descr="(see above)" access="RO" offset="0x7c.0" size="0x4.0" />
	<field name="tx_stats_pkts1519to2047octets_high" descr="The total number of packets (including bad packets) transmitted that\;were between 1519 and 2047 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="tx_stats_pkts1519to2047octets_low" descr="(see above)" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="tx_stats_pkts2048to4095octets_high" descr="The total number of packets (including bad packets) transmitted that\;were between 2048 and 4095 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="tx_stats_pkts2048to4095octets_low" descr="(see above)" access="RO" offset="0x8c.0" size="0x4.0" />
	<field name="tx_stats_pkts4096to8191octets_high" descr="The total number of packets (including bad packets) transmitted that\;were between 4096 and 8191 octets in length (excluding framing bits but\;including FCS octets)." access="RO" offset="0x90.0" size="0x4.0" />
	<field name="tx_stats_pkts4096to8191octets_low" descr="(see above)" access="RO" offset="0x94.0" size="0x4.0" />
	<field name="tx_stats_pkts8192to10239octets_high" descr="The total number of packets (including bad packets) transmitted that\;were between 8192 and 10239 octets in length (excluding framing bits but\;including FCS octets).transmitted" access="RO" offset="0x98.0" size="0x4.0" />
	<field name="tx_stats_pkts8192to10239octets_low" descr="(see above)" access="RO" offset="0x9c.0" size="0x4.0" />
	<field name="ece_marked_high" descr="A count of packets marked as ECE or potentially marked as ECE." access="RO" offset="0xa0.0" size="0x4.0" />
	<field name="ece_marked_low" descr="(see above)" access="RO" offset="0xa4.0" size="0x4.0" />
	<field name="tx_int_cksm_err_high" descr="Counter is incremented upon packet payload internal checksum error" access="RO" offset="0xa8.0" size="0x4.0" />
	<field name="tx_int_cksm_err_low" descr="(see above)" access="RO" offset="0xac.0" size="0x4.0" />
</node>

<node name="eth_per_prio_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="rx_octets_high" descr="The total number of octets received, including framing characters." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="rx_octets_low" descr="(see above)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="rx_frames_high" descr="The total number of packets received for this priority (not including\;pause frames)." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="rx_frames_low" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="tx_octets_high" descr="The total number of octets transmitted, including framing characters." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="tx_octets_low" descr="(see above)" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="tx_frames_high" descr="The total number of packets transmitted." access="RO" offset="0x48.0" size="0x4.0" />
	<field name="tx_frames_low" descr="(see above)" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="rx_pause_high" descr="The total number of PAUSE frames received from the far-end\;port." access="RO" offset="0x50.0" size="0x4.0" />
	<field name="rx_pause_low" descr="(see above)" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="rx_pause_duration_high" descr="The total time in microseconds that transmission of packets to the\;far-end port have been paused.Note that if pause is global then tclass ‘0’ will increment" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="rx_pause_duration_low" descr="(see above)" access="RO" offset="0x5c.0" size="0x4.0" />
	<field name="tx_pause_high" descr="The total number of PAUSE or PFC frames sent to the far-end port." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="tx_pause_low" descr="(see above)" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="tx_pause_duration_high" descr="The total time in microseconds that the far-end port have been requested\;to pause." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="tx_pause_duration_low" descr="(see above)" access="RO" offset="0x6c.0" size="0x4.0" />
	<field name="rx_pause_transition_high" descr="Counts the number of transitions from Xoff to Xon." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="rx_pause_transition_low" descr="(see above)" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="rx_discards_high" descr="The number of inbound packets which were chosen to be discarded even\;though no errors had been detected to prevent their being deliverable to\;a higher-layer protocol." access="RO" offset="0x78.0" size="0x4.0" />
	<field name="rx_discards_low" descr="(see above)" access="RO" offset="0x7c.0" size="0x4.0" />
	<field name="device_stall_minor_watermark_cnt_high" descr="The number of times the device detected a stalled state for a period\;longer than device_stall_minor_watermarkThe counter is presented in priority 0, but is a sum of all events on\;all priorities (including global pause)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="device_stall_minor_watermark_cnt_low" descr="(see above)" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="device_stall_critical_watermark_cnt_high" descr="The number of times the device detected a stalled state for a period\;longer than device_stall_critical_watermark.The counter is presented in priority 0, but is a sum of all events on\;all priorities (including global pause)." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="device_stall_critical_watermark_cnt_low" descr="(see above)" access="RO" offset="0x8c.0" size="0x4.0" />
</node>

<node name="eth_per_traffic_class_layout_ext" descr="" size="0xf8.0" >
	<field name="transmit_queue_high" descr="Contains the transmit queue depth in bytes on traffic class selected by\;traffic_class of the port selected by local_port." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="transmit_queue_low" descr="(see above)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_high" descr="The number of unicast packets dropped due to lack of shared buffer\;resources.Valid only for Spectrum.Valid for HCA when ppcnt_no_buffer_uc is set in PCAM." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_low" descr="(see above)" access="RO" offset="0xc.0" size="0x4.0" />
</node>

<node name="fatal_cause_ext" descr="" size="0xa0.0" >
	<field name="cause_id" descr="HW / FW cause IDFW Causes (When fw_cause = 1):1: Core PLL lock failureWhen test = 1 AND fw_cause = 0, cause ID = 0xCAFE" access="RO" offset="0x0.0" size="0x0.20" />
	<field name="fw_cause" descr="0: cause_id reflects HW cause ID1: cause_id reflects FW cause (event)" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="test" descr="Test:0: real cause ID1: test cause ID" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the assert.[DWIP] Superseded by top level tile_v and tile_index. Kept for\;backwards compatibility." access="RO" offset="0x4.16" size="0x0.6" />
	<field name="tile_v" descr="Tile valid:0: The assert was from main1: The assert was from a tile[DWIP] Superseded by top level tile_v and tile_index. Kept for\;backwards compatibility." access="RO" offset="0x4.23" size="0x0.1" />
</node>

<node name="fw_assert_ext" descr="" size="0xa0.0" >
	<field name="assert_var0" descr="This is the 1st variable passed to assert" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="assert_var1" descr="This is the 2nd variable passed to assert" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="assert_var2" descr="This is the 3rd variable passed to assert" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="assert_var3" descr="This is the 4th variable passed to assert" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="assert_var4" descr="This is the 5th variable passed to assert" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="assert_exinstptr" descr="this is instruction pointer when assert was triggered" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="assert_callra" descr="This is the next return address after triggering assert" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="ext_synd" descr="Extended syndrome" access="RO" offset="0x1c.0" size="0x0.16" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the assert.[DWIP] Superseded by top level tile_v and tile_index. Kept for\;backwards compatibility." access="RO" offset="0x1c.16" size="0x0.6" />
	<field name="tile_v" descr="Tile valid:0: The assert was from main1: The assert was from a tile[DWIP] Superseded by top level tile_v and tile_index. Kept for\;backwards compatibility." access="RO" offset="0x1c.23" size="0x0.1" />
	<field name="oe" descr="Old Event:0: New event1: Old event, found during MFGD activation" access="RO" offset="0x1c.24" size="0x0.1" />
	<field name="test" descr="Test:0: real cause ID1: test cause ID (cause ID = 0xCAFE)" access="RO" offset="0x1c.31" size="0x0.1" />
	<field name="assert_string" descr="String provided by the deviceEndianity:Offset 04h[31:24] - byte0Offset 04h[23:16] - byte1Offset 04h[15:8] - byte2Offset 04h[7:0] - byte3Offset 08h[31:24] - byte4etc." access="RO" high_bound="31" low_bound="0" offset="0x20.0" size="0x80.0" />
</node>

<node name="gfer_ext" descr="" size="0xcc.0" >
	<field name="data_length" descr="The data length in DWORD (4B) granularity.Value of 0 means message contains only the event_sequence_number.The max value is 49 (up to 204B including first two DWORDs)." access="RW" offset="0x0.20" size="0x0.8" />
	<field name="version" descr="Events message version." access="RW" offset="0x0.28" size="0x0.4" />
	<field name="event_seqeunce_number" descr="Event’s sequence number as indicated by the sender.Sender could either be NMX-C and then its is the partition’s event\;sequence number, or could be the FW." access="RW" offset="0x4.0" size="0x4.0" />
	<field name="data" descr="Opaque data." access="RW" high_bound="48" low_bound="0" offset="0x8.0" size="0xc4.0" />
</node>

<node name="ghpkt_ext" descr="" size="0x10.0" >
	<field name="trap_id" descr="Trap IDsSee section 31.1.2.1 - GPUNet Trap IDs" access="INDEX" offset="0x0.0" size="0x0.10" />
	<field name="action" descr="Action to perform on trap_id0: NOP1: TRAP" access="RW" enum="NOP=0x0,TRAP=0x1" offset="0x0.20" size="0x0.4" />
</node>

<node name="gndr_ext" descr="" size="0x40.0" >
	<field name="node_description" descr="UTF-8 encoded string that describes the node in text format." access="RW" high_bound="15" low_bound="0" offset="0x0.0" size="0x40.0" />
</node>

<node name="gplid_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local Port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lid" descr="The Port LID configured to the GPU Port.[internal] Notice: the port LID has 20 bits for future compatibility,\;but only the 16 LSBs are being used." access="RO" offset="0x4.0" size="0x0.20" />
</node>

<node name="gsguid_ext" descr="" size="0x10.0" >
	<field name="system_guid_h" descr="The system GUID of the device." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="system_guid_l" descr="The system GUID of the device." access="RW" offset="0xc.0" size="0x4.0" />
</node>

<node name="hst_link_eth_enabled_ext" descr="" size="0x4.0" >
	<field name="link_eth_active" descr="Ethernet protocols active: see PTYS.ext_eth_proto_oper" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="hst_link_ib_enabled_ext" descr="" size="0x4.0" >
	<field name="link_speed_active" descr="IB link active speed:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="link_width_active" descr="IB link active width:Bit 0: 1xBit 1: 2xBit 2: 4xOther - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="hst_link_nvlink_enabled_ext" descr="" size="0x4.0" >
	<field name="link_nvlink_active" descr="NVLink protocols activeSee:\;PTYS - Extended Protocol NVLink - cap/oper Layout" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="kvd_im_stop_ext" descr="" size="0xa0.0" >
	<field name="pipes_mask" descr="Bit per kvh pipe" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="oe" descr="Old Event:0: New event1: Old event, found during MFGD activation" access="RO" offset="0x0.24" size="0x0.1" />
</node>

<node name="lane_2_module_mapping_ext" descr="" size="0x4.0" >
	<field name="module" descr="Module number" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA.Slot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="tx_lane" descr="TX lane.When m_lane_m field is set, this field is ignored (Reserved).When rxtx field is cleared, this field is used for RX as well." access="RW" offset="0x0.16" size="0x0.4" />
	<field name="rx_lane" descr="RX lane.When m_lane_m field is set, this field is ignored (Reserved).When rxtx field is clreared, for set operation this field is ignored and\;for get operation may return invalid value, Rx mapping for get should be\;taken from tx_lane." access="RW" offset="0x0.24" size="0x0.4" />
	<field name="mode_b_map" descr="Supported if PCAM.feature_cap_mask bit 116 is set, otherwise field is\;not valid.Relevant for Mode B port only, Mode A port should ignore.indicates if module lane Tx or Rx is used.0: module_rx_lane_valid - Mode B lane uses module rx lane.tx lane value is not valid should be ignored1: module_tx_lane_valid - Mode B lane uses module tx lane.rx lane value is not valid should be ignored" access="RO" offset="0x0.30" size="0x0.1" />
</node>

<node name="ltx_logger_ext" descr="" size="0x8.0" >
	<field name="ltx_status" descr="" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="ltx_fail_reason" descr="" access="RO" offset="0x0.1" size="0x0.5" />
	<field name="ltx_retry_count" descr="Number of times the link quality by fec measure re-checked for the\;current itteration" access="RO" offset="0x0.6" size="0x0.5" />
	<field name="effective_errors" descr="" access="RO" offset="0x0.11" size="0x0.1" />
	<field name="highest_non_zero_hist" descr="" access="RO" offset="0x0.12" size="0x0.5" />
	<field name="raw_ber_magnitude" descr="" access="RO" offset="0x0.17" size="0x0.8" />
	<field name="prbs_ber_magnitude" descr="" access="RO" offset="0x0.25" size="0x0.5" />
	<field name="ltx_retry_fail_count" descr="Number of times the link quality by fec measure failed for the current\;itteration" access="RO" offset="0x4.6" size="0x0.5" />
	<field name="raw_ber_mantissa" descr="" access="RO" offset="0x4.17" size="0x0.4" />
	<field name="raw_ber_mantissa_float" descr="" access="RO" offset="0x4.21" size="0x0.4" />
</node>

<node name="mcam_reg_ext" descr="" size="0x48.0" >
	<field name="access_reg_group" descr="Access Register ID groups0: First_128_REG_ID - Register IDs 0x9001 - 0x907F)1: Register_IDs_0x9080 - 0x90FF (bit 0 in mng_access_reg_cap_mask\;represent register ID 0x9080 while bit 127 represents register ID\;0x90FF).2: Register_IDs_0x9100 - 0x917F (bit 0 in mng_access_reg_cap_mask\;represent register ID 0x9100 while bit 127 represents register ID\;0x917F).3: Register_IDs_0x9180 - 0x91FF (bit 0 in mng_access_reg_cap_mask\;represent register ID 0x9180 while bit 127 represents register ID\;0x91FF)." access="INDEX" enum="First_128_REG_ID=0x0,Register_IDs_0x9080=0x1,Register_IDs_0x9100=0x2,Register_IDs_0x9180=0x3" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index:0: enhanced_features" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="mng_access_reg_cap_mask" descr="Supported management’s access register bitmask. Based on\;access_reg_group index.When bit is set, the register is supported in the device.For example:Bit 1: MFCR_0x9001Bit 2: MFSC_0x9002Bit 3: MFSM_0x9003Bit 4: MFSL_0x9004Bit 58: MGCR_0x903ABit 73: MPPF_0x9049Bit 127: MCAP_0x907F" access="RO" enum="MFCR_0x9001=0x2,MFSC_0x9002=0x4,MFSM_0x9003=0x8,MFSL_0x9004=0x10,MGCR_0x903A=0x4000000,MPPF_0x9049=0x200,MCAP_0x907F=0x80000000" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="mng_feature_cap_mask" descr="Supported port’s enhanced features.Based on feature_group index.When bit is set, The feature is supported in the deviceBit 0: MPCNT counter group- PCIE performance counters supportedBit 1: mtpps_fs - If set, field_select field in MTPPS register is\;supported.Bit 2: mtpps_enhanced_out_periodic_adjustment - If set,\;enhanced_out_periodic_adjustment field in MTPPS register is supported.Bit 3: tx_lossy_overflow_oper - If set, tx_overflow_buffer_pkt counter\;in MPCNT register is supported.Bit 4: pcie_outbound_stalled - if set, outbound_stalled_reads,\;outbound_stalled_writes, outbound_stalled_reads_events and\;outbound_stalled_writes_events counters in MPCNT are supported.Bit 5: Management pass through is supportedBit 6: sensor_map - If set, sensor_map is supported in MTCAP register.Bit 7: if set, module_status bit 8 (Module Low Power) in MCION register\;is supported.Bit 8: beacon_capability_disable - If set, beacon feature, as appears in\;MLCR register, in not supported by the device.Bit 9: dynamic_tx_overflow - If set, tx_overflow_sense field is\;supported in MPEGC register.Bit 10: mark_tx_action_cqe is supported if set to ‘1’.Bit 11: mark_tx_action_cnp is supported if set to ‘1’.Bit 12: dev_info is supported in register is set to ‘1’.Bit 13: sensor_count field is 12bit size in MTMP and MTBRBit 14: cs_tokens_supported is supportedBit 15: debug_fw_tokens_supportedBit 16: long_keys is supportedBit 17: pwr_status and pci_power are supported in MPEINBit 18: If set, accessing through device_type and device_index is\;supported in MCC, MCQI and MCQSBit 19: pcie_sync_for_fw_update_supported is set to ‘1’Bit 20: ptpCyc2Realtime_modify - If set, the cycle to realtime\;translation offload is supportedBit 21: If set to ‘1’, reset_state in MFRL is supportedBit 22: If set to ‘1’, link_peer_max_speed is supported in MPEIN\;RegisterBit 23: If set to ‘1’, slot_index field is supported in: MCIA, MCAS,\;MCION, MQSP, MTCAP, MTECR, MTMP, MTEWE, MTBR, MVCAP, MVCR, MGPIR,\;MDDT.Bit 24: If set, transceiver burn flow is supported in MCC, MCQI and\;MCQS.Bit 26: If set, progress field is supported in MCQSBit 28: If set, number_of_slots field is supported in MGPIR.Bit 29: If set, virtual hot plug / unplug is supported in MPEGC.Bit 30: If set, my_pf_number is supported in MPPF.Bit 31: If set, sdee is supported in MTMPBit 34: If set, MCIA supports 32 D-words. Otherwise, 12 D-words.Bit 35: If set, MGIR.hw_info.technology is supported.Bit 37: If set, lp_msb is supported for MLCR, MPIR\;Bit 39: If set, MRCS and RMDT tokens are supported in MCQSBit 40: If set, ‘encryption’ field in MGIR is supportedBit 43: If set, MFCR supports tacho_active_msb fieldBit 44: If set, FORE supports fan_under_limit_msb and fan_over_limit_msb\;fieldsBit 45: If set, MFRL.pci_rescan_required is supportedBit 46: time_adjust_range_extended - if set, the MTUTC.time_adjustment\;range is extended to -\;Bit 47: If set, MTUTC.freq_adj_units=1 is supportedBit 48: If set, MRSRFT/MRSR.command=6 is supportedBit 49: If set, MCQS.identifier support CRCS and CRDT tokensBit 51: If set, MTUTC.freq_adj_units=2 is supported\;Bit 59: If set, MCC.component_specific_error_code is valid for LinkX\;devicesBit 60: If set, MGNLE.clr is supportedBit 61: If set, MGIR supports life_cycle_msb and pds fields in FW\;info and development field in HW info.\;\;Bit 65: If set, MVCR support current_sensor_value_msbBit 66: If set. MFRL supports pci_reset_req_method, pci_switch_exist\;fields. [DWIP]Bit 67: If set, MRSR.cmd = 6 works with SBRBit 70: If set, supports MTCAP support 8 bit internal_sensor_count\;[DWIP]Bit 71: If set, supports MVCAP supports sensor_map_type [DWIP]Bit 75: If set, PLLP supports oe_identifier and resource_labe_port\;[switch_internal][DWIP]bit 76: If set, MCQS supports the component_not_supported field\;[DWIP]Bit 77: If set, host_id field in MPIR is supportedBit 78: If set, MGIR supports 12 bit num_ports fieldbit 80: If set, MCQS,identifier supports the DPA_COMPONENT, DPA\;_COMPONENT_REMOVAL fields and MCQI supports DPA apps infoBit 81: If set, MFCDR supports module and query_type fields [DWIP]Bit 82: If set, MCIA supports async mode [DWIP][switch_internal]Bit 85: If set, MTDT token is supported Bit 88: If set, the following are supported:\;PEMI.laser_source_essential, PEMI.laser_source_advance, PEMI.module\;status, PEMI.optical_engine_telemetry_parameters, PEMI.cpo_module,\;PEMI.last_sub_module.Bit 89: If set, supports minimum temperatures, as well as alerts for low\;critical and high critical thresholds, in the following registers: MTMP,\;MTEWE, MTBR, MTBR_v2.Bit 91: If set, CPO Combined Model is supported.Bit 93: If set, MGIR.hw_info.board_ga is supported; ignore otherwise." access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="mcc_reg_ext" descr="" size="0x20.0" >
	<field name="instruction" descr="Command to be executed by the FSM0x1: LOCK_UPDATE_HANDLE0x2: RELEASE_UPDATE_HANDLE0x3: UPDATE_COMPONENT0x4: VERIFY_COMPONENT0x6: ACTIVATE0x7: READ_COMPONENT0x8: CANCEL0x9: CHECK_UPDATE_HANDLE0xA: FORCE_HANDLE_RELEASE0xB: READ_PENDING_COMPONENT0xC: DOWNSRTEAM_DEVICE_TRANSFEROther values are reserved. Applicable for write operation only." access="RW" enum="LOCK_UPDATE_HANDLE=0x1,RELEASE_UPDATE_HANDLE=0x2,UPDATE_COMPONENT=0x3,VERIFY_COMPONENT=0x4,ACTIVATE=0x6,READ_COMPONENT=0x7,CANCEL=0x8,CHECK_UPDATE_HANDLE=0x9,FORCE_HANDLE_RELEASE=0xa,READ_PENDING_COMPONENT=0xb,DOWNSRTEAM_DEVICE_TRANSFER=0xc" offset="0x0.0" size="0x0.8" />
	<field name="activation_delay_sec" descr="This is a configuration that delays the activation of the component in\;seconds. Relevant only for activate command.This configuration is volatile." access="RW" offset="0x0.8" size="0x0.8" />
	<field name="time_elapsed_since_last_cmd" descr="The number of seconds elapsed since the update_handle owner last issued\;a command. The time saturates at 0xFFF." access="RO" offset="0x0.16" size="0x0.12" />
	<field name="component_index" descr="Index of the accessed component.Value from MCQS.component_indexValid forUPDATE_COMPONENT, ACTIVATE_COMPONENT, READ_COMPONENT and\;READ_PENDING_COMPONENT instructions. Otherwise, this field is reserved." access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="update_handle" descr="Token representing the current flow executed by the FSM." access="RW" offset="0x8.0" size="0x0.24" />
	<field name="auto_update" descr="Auto-update to all matching downstream devices is requested." access="WO" offset="0x8.31" size="0x0.1" />
	<field name="control_state" descr="Current Update FSM state0x0: IDLE0x1: LOCKED0x2: INITIALIZE0x3: DOWNLOAD0x4: VERIFY0x5: APPLY0x6: ACTIVATE0x7: UPLOAD0x8: UPLOAD_PENDING0x9: DOWNSRTEAM_DEVICE_TRANSFEROther values are reserved" access="RO" enum="IDLE=0x0,LOCKED=0x1,INITIALIZE=0x2,DOWNLOAD=0x3,VERIFY=0x4,APPLY=0x5,ACTIVATE=0x6,UPLOAD=0x7,UPLOAD_PENDING=0x8,DOWNSRTEAM_DEVICE_TRANSFER=0x9" offset="0xc.0" size="0x0.4" />
	<field name="error_code" descr="Indicates the successful completion of the instruction, or the reason it\;failed.0x0: OK0x1: ERROR0x2: REJECTED_DIGEST_ERR0x3: REJECTED_NOT_APPLICABLE0x4: REJECTED_UNKNOWN_KEY0x5: REJECTED_AUTH_FAILED0x6: REJECTED_UNSIGNED0x7: REJECTED_KEY_NOT_APPLICABLE0x8: REJECTED_BAD_FORMAT0x9: BLOCKED_PENDING_RESET0xA: REJECTED_NOT_A_SECURED_FW0xB: REJECTED_MFG_BASE_MAC_NOT_LISTED0xC: REJECTED_NO_DEBUG_TOKEN0xD: REJECTED_VERSION_NUM_MISMATCH0xE: REJECTED_USER_TIMESTAMP_MISMATCH0xF: REJECTED_FORBIDDEN_VERSION0x10: FLASH_ERASE_ERROR0x11: REJECTED_REBURN_RUNNING_AND_RETRY0x12: REJECTED_LINKX_TYPE_NOT_SUPPORTED0x13: REJECTED_HOST_STORAGE_IN_USE0x14: REJECTED_LINKX_TRANSFER (see module index in\;rejected_device_index)0x15: REJECTED_LINKX_ACTIVATE (see module index in\;rejected_device_index)0x16: REJECTED_INCOMPATIBLE_FLASH0x17: REJECTED_TOKEN_ALREADY_APPLIED0x18: REJECTED_FW_BURN_DRAM_NOT_AVAILABLE0x19: FW_BURN_REJECTED_INVALID_SECURITY_VERSION0x1A: FW_BURN_REJECTED_CERT_CER5090x1B: FW_BURN_REJECTED_CERT_SIGNATURE0x1C: FW_BURN_REJECTED_CERT_METADATA0x1D: FW_BURN_REJECTED_INTERNAL_ERROR_0\;0x1E: FW_BURN_REJECTED_NO_PLACE0x1F: FW_BURN_REJECTED_REMOVAL_NO_MATCH_UIDD0x20: FW_BURN_REJECTED_INTERNAL_ERROR_1\;0x21: FW_BURN_REJECTED_INTERNAL_ERROR_2\;0x22: FW_BURN_REJECTED_NUM_OF_SWAP0x23: FW_BURN_REJECTED_INTERNAL_ERROR_3\;0x24: FW_BURN_REJECTED_INTERNAL_ERROR_4\;0x25: FW_BURN_REJECTED_NOT_ALLOWED_SAME_UIDD0x26: FW_BURN_REJECTED_INTERNAL_ERROR_5\;0x27: FW_BURN_REJECTED_INTERNAL_ERROR_6\;0x28: FW_BURN_REJECTED_FLASH_WRITE_PROTECTED0x29: FW_BURN_REJECTED_INTERNAL_ERROR_7\;0x2A: FW_BURN_REJECTED_INTERNAL_ERROR_8\;0x2B: FW_BURN_REJECTED_INTERNAL_ERROR_90x2C: FW_BURN_REJECTED_DPA_ELF0x2D: FW_BURN_REJECTED_DPA_CRYPTO_BLOB0x2E: FW_BURN_REJECTED_DPA_APP_METADATA0x2F: FW_BURN_REJECTED_DPA_REMOVAL_SIGNATURE0x30: FW_BURN_REJECTED_DPA_CONTAINER_VERIFY0x31: FW_BURN_REJECTED_INTERNAL_ERROR_10\;0x32: REJECTED_DEV_IMAGE_ON_PROD_DEVICE0x33: FW_BURN_REJECTED_DPA_APP_MANIFESTOther values should be treated as an unknown error." access="RO" offset="0xc.8" size="0x0.8" />
	<field name="control_progress" descr="Indicates the estimated progress status of the current operation\;executed by the FSM. Valid values are 0..100.101 indicates that progress reporting is not supported for this update\;state." access="RO" offset="0xc.16" size="0x0.7" />
	<field name="handle_owner_host_id" descr="For handle_owner_type BMC, command-interface and ICMD, indicates the\;identifier of the host of the handle owner.Otherwise reserved" access="RO" offset="0xc.24" size="0x0.4" />
	<field name="handle_owner_type" descr="Type of entity holding the update handle:0x0: unspecified0x1: Chassis BMC0x2: MAD0x3: BMC0x4: command interface0x5: ICMDOther values are reserved." access="RO" offset="0xc.28" size="0x0.4" />
	<field name="component_size" descr="Component size in bytes.Valid for UPDATE_COMPONENT instruction. Specifying the size may shorten\;the update time.Value 0x0 means that size is unspecified." access="WO" offset="0x10.0" size="0x4.0" />
	<field name="device_type" descr="Peripheral device type:0: Switch_or_NIC1: Gearbox" access="INDEX" enum="Switch_or_NIC=0x0,Gearbox=0x1" offset="0x14.0" size="0x0.8" />
	<field name="warning_code" descr="Indicates warnings reported during the completion that did not prevent\;successful completion of the instruction0x0: OK0x1: WARNING_DPA_API_OS_INCOMPATIBLE0x2: WARNING_DPA_API_FW_INCOMPATIBLE" access="RO" offset="0x14.8" size="0x0.8" />
	<field name="device_index" descr="Device number, bits [11:0].For gearboxes, the index represents the gearbox die.For cables, the index represents the module index starting at index 1.\;Index 0 indicates the host device." access="INDEX" offset="0x14.16" size="0x0.12" />
	<field name="device_index_msb" descr="[Switch][DWIP]Device number, bits [15:12].For gearboxes, the index represents the gearbox die.For cables, the index represents the module index starting at index 1.\;Index 0 indicates the host device." access="INDEX" offset="0x14.28" size="0x0.4" />
	<field name="device_index_size" descr="In multiple downstream devices action, the action will be executed\;starting on device_index and ending on &lt;device_index_msb, device_index&gt;\;+ &lt;device_index_size_msb, device_index_size&gt; - 1." access="RW" offset="0x18.0" size="0x0.12" />
	<field name="device_index_size_msb" descr="[Switch][DWIP]In multiple downstream devices action, the action will be executed\;starting on device_index and ending on &lt;device_index_msb, device_index&gt;\;+ &lt;device_index_size_msb, device_index_size&gt; - 1." access="RW" offset="0x18.12" size="0x0.4" />
	<field name="rejected_device_index" descr="The device index that the action has been rejected to." access="RO" offset="0x18.16" size="0x0.12" />
	<field name="component_specific_err_code" descr="[DWIP]:Component Specific Error CodeRelevant only for Linkx failed updates" access="RO" offset="0x1c.0" size="0x4.0" />
</node>

<node name="mcda_reg_ext" descr="" size="0x90.0" >
	<field name="update_handle" descr="Update handle registered when the FSM was activated." access="RW" offset="0x0.0" size="0x0.24" />
	<field name="offset" descr="Offset of accessed address relative to component start. Accesses must be\;in accordance to log_mcda_word_size in\;MCQI CAPABILITIES Info Layout" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="size" descr="Size of the data accessed, given in bytes" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="data" descr="Data block accessed" access="RW" high_bound="31" low_bound="0" offset="0x10.0" size="0x80.0" />
</node>

<node name="mcdd_reg_ext" descr="" size="0x20.0" >
	<field name="update_handle" descr="Update handle registered when the FSM was activated." access="RW" offset="0x0.0" size="0x0.24" />
	<field name="offset" descr="Offset of accessed address relative to component start." access="RW" offset="0x4.0" size="0x4.0" />
	<field name="size" descr="Size of the data accessed, given in bytes" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="data_page_phys_addr_msb" descr="Physical address of the FW component data page." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="data_page_phys_addr_lsb" descr="(see above)" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="mailbox_page_phys_addr_msb" descr="Physical address of the mailbox page." access="RW" offset="0x18.0" size="0x4.0" />
	<field name="mailbox_page_phys_addr_lsb" descr="(see above)" access="RW" offset="0x1c.0" size="0x4.0" />
</node>

<node name="mcia_ext" descr="" size="0x94.0" >
	<field name="status" descr="Module Status0: SUCCESS1: NO_EEPROM_MODULE. No response from module’s EEPROM.2: MODULE_NOT_SUPPORTED. Module type not supported by the device.\;3: MODULE_NOT_CONNECTED. No module present indication.4: MODULE_TYPE_INVALID - module is not supported by INI.9: I2C_ERROR. Error occurred while trying to access the module’s EEPROM\;using I2C.16: MODULE_DISABLED - module is disabled" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="module_bits_11_8" descr="[Switch][DWIP]:Module number, bits [11:8]." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="slot_index" descr="Slot index0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number, bits [7:0]." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="module_bits_14_12" descr="[Switch][DWIP]:Module number, bits [14:12]." access="INDEX" offset="0x0.26" size="0x0.3" />
	<field name="pnv" descr="[DWIP]:Page Number Valid0: write page number1: don’t write page numberValid only if module is in SW control" access="OP" offset="0x0.29" size="0x0.1" />
	<field name="l" descr="Lock Page bit.When bit is set, FW can access the last accessed page.After boot and ISSU, default value is 0." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="device_address" descr="Device address" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="page_number" descr="Page numberReserved when MCIA.l = 1 or when MCIA.pnv = 1" access="INDEX" offset="0x4.16" size="0x0.8" />
	<field name="i2c_device_address" descr="I2C device address" access="INDEX" offset="0x4.24" size="0x0.8" />
	<field name="size" descr="Number of bytes to read/write (up to 128 bytes)" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="bank_number" descr="Bank number" access="INDEX" offset="0x8.16" size="0x0.8" />
	<field name="module_bit_15" descr="[Switch][DWIP]:Module number, bit [15]." access="INDEX" offset="0x8.24" size="0x0.1" />
	<field name="bg_mode" descr="[DWIP][switch_internal]Background operation0: Foreground mode (legacy)1: Background modeWhen working on background mode, FW shall return STS_OK immediately and\;return the transaction data via MCIA trap." access="OP" offset="0x8.27" size="0x0.1" />
	<field name="passwd_length" descr="0: password length is 4B (password_msb is reserved)1: password length is 8B (password_msb is used)" access="OP" offset="0x8.28" size="0x0.1" />
	<field name="password" descr="The password that is written to the module password field.This field is reserved when passwd_cap is not set to 1.Reserved when module is in SW control." access="OP" offset="0xc.0" size="0x4.0" />
	<field name="dword" descr="Bytes to read/writeNote: some FW versions support only 12*4BSee MCAM bit34" access="RW" high_bound="31" low_bound="0" offset="0x10.0" size="0x80.0" />
	<field name="password_msb" descr="password msbSupported only when MCAM bit34 is setSupported only when passwd_cap is setReserved when passwd_length = 0" access="RW" offset="0x90.0" size="0x4.0" />
</node>

<node name="mcion_ext" descr="" size="0x10.0" >
	<field name="slot_index" descr="Slot index0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number bits [7:0]." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="module_msb" descr="[Switch][DWIP]Module number bits [15:8]." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="module_status_bits" descr="Module IO status, as defined by SFF and CMIS:Bit 0: PresentBit 1: RX_LOSBit 2: TX_FaultBit 6: LPModeBit 7: Interrupt (IntL)Bit 8: Low Power Mode Status Bit 9: Power GoodIf bit 0 (Present) is clear, all other bits are reserved." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="module_inputs" descr="Module inputs:Bit 0: ResetL - low polarityBit 1: LPModeBit 2: Power EnableReserved when module is controlled by FW" access="RW" offset="0xc.0" size="0x0.4" />
	<field name="module_status_bits_valid" descr="Module Inputs Valid BitmaskBitmask which mentions the validity of module_inputs fields.For each bit, 0 means valid, 1 means not valid.For example:Bit 0: if set, present bit value is ignored. If cleared, value is valid.Bit 1: if set, rx loss value is ignored. when cleared, value is valid\;and so on for all bits mentioned in module_inputs.Reserved when module is controlled by FW" access="RO" offset="0xc.16" size="0x0.16" />
</node>

<node name="mcqi_activation_method_ext" descr="" size="0x7c.0" >
	<field name="all_hosts_sync" descr="When set, the operation needed to move the component form\;ACTIVE_PENDING_RESET to ACTIVE should happen simultaneously on all\;hosts." access="RO" offset="0x0.0" size="0x0.1" />
	<field name="auto_activate" descr="This component will be ACTIVE or ACTIVE_PENDING_RESET after the APPLY\;state." access="RO" offset="0x0.1" size="0x0.1" />
	<field name="pending_fw_reset" descr="This component goes to ACTIVE_PENDING_RESET after activation.A FW reset will move it to ACTIVE state." access="RO" offset="0x0.2" size="0x0.1" />
	<field name="pending_server_reboot" descr="This component goes to ACTIVE_PENDING_RESET state after activation." access="RO" offset="0x0.3" size="0x0.1" />
	<field name="pending_server_dc_power_cycle" descr="This component goes to ACTIVE_PENDING_RESET state after activation.DC power cycle (power cycle of PCI power rails), will move it ACTIVE\;state." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="pending_server_ac_power_cycle" descr="This component goes to ACTIVE_PENDING_RESET state after activation.AC power cycle (power cycle for both PCI power rails and AUX power),\;will move it ACTIVE state." access="RO" offset="0x0.5" size="0x0.1" />
	<field name="self_activation" descr="When set, the component supports self activation. For cables, please\;refer to activation_type in LINKX_PROPERTIES data for more details." access="RO" offset="0x0.6" size="0x0.1" />
</node>

<node name="mcqi_cap_ext" descr="" size="0x7c.0" >
	<field name="supported_info_bitmask" descr="Bitmask indicating which info_type(s) are supported for this component.\;Set bit indicates the property set is supportedbit 1: VERSIONbit 5: ACTIVATION_METHODOther bits are reserved. CAPABILITIES set is always supported.bit 6: LinkXbit 7: Clock Synchronizerbit 9: DPA_APPS_INFOOther bits are reserved" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="component_size" descr="The size of the component given in bytes. Value 0x0 indicates that the\;size in unknown.For some components, size may only be available in the READ_COMPONENT\;state." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="max_component_size" descr="Maximum size for this component, given in bytes." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="mcda_max_write_size" descr="Maximal write size for MCDA" access="RO" offset="0xc.0" size="0x0.16" />
	<field name="log_mcda_word_size" descr="Log 2 of the access word size in bytes.Read and write access must be aligned to the word size. Write access\;must be done for an integer number of words." access="RO" offset="0xc.28" size="0x0.4" />
	<field name="match_base_guid_mac" descr="The device only accepts updates for this component that explicitly lists\;its base MAC and/or base GUID" access="RW" offset="0x10.26" size="0x0.1" />
	<field name="check_user_timestamp" descr="A user defined timestamp (MVTS) is active for this component." access="RW" offset="0x10.27" size="0x0.1" />
	<field name="match_psid" descr="PSID is validated for this component update." access="RW" offset="0x10.28" size="0x0.1" />
	<field name="match_chip_id" descr="Chip ID (device_hw_revision) is validated for this component update." access="RW" offset="0x10.29" size="0x0.1" />
	<field name="signed_updates_only" descr="Only signed components are accepted." access="RW" offset="0x10.30" size="0x0.1" />
	<field name="rd_en" descr="When set, this components may be read" access="RO" offset="0x10.31" size="0x0.1" />
</node>

<node name="mcqi_clock_source_properties_ext" descr="" size="0x4.0" >
	<field name="image_version_minor" descr="Image Version Minor Number" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="image_version_major" descr="Image Version Major Number" access="RO" offset="0x0.4" size="0x0.4" />
	<field name="vendor_id" descr="Clock Source Device Vendor Id0: Renesas1: SiTime 1482: SiTime 3483: TI4-255: Reserved" access="RO" offset="0x0.16" size="0x0.8" />
</node>

<node name="mcqi_dpa_apps_info_ext" descr="" size="0x70.0" >
	<field name="total_number_of_entries" descr="Provides the number of DPA apps in the active DPA_APPS partition.If there are no DPA apps, this field is equal to 0 and all the\;DPA_APP_METADATA fields will be 0." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="DPA_APPS_INFO version." access="RO" offset="0x0.24" size="0x0.8" />
	<field name="dpa_app_metadata" descr="DPA metadata, see\;MCQI DPA_APP_METADATA Layout" subnode="mcqi_dpa_metadata_ext" access="RO" offset="0x8.0" size="0x68.0" />
</node>

<node name="mcqi_dpa_metadata_ext" descr="" size="0x68.0" >
	<field name="subtype" descr="The subtype of the section" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="type" descr="The type of the section. Should be used to identify “twin” applications,\;e.g. - CCProg coming from a 3rd party versus “native” application.Enumeration details:0 - APU_APP_EXTERNAL,1 - 3 - Reserved,4 - APU_APP_PCC,5 - APU_APP_DLL,6 - APU_APP_KERNEL,7-255 - Reserved" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="version" descr="Version of App Metadata structure" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="length" descr="Structure length" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="dpa_app_version" descr="DPA application version" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="dpa_os_api_version" descr="Version of the DPA API to OS" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="dpa_fw_api_version" descr="Version of the DPA API to other DPA FW modules" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="dpa_app_uuid" descr="DPA application UUID, updated with a change in application version" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
	<field name="dpa_app_description_string" descr="Application description ASCII string" access="RO" high_bound="7" low_bound="0" offset="0x40.0" size="0x20.0" />
</node>

<node name="mcqi_linkx_properties_ext" descr="" size="0x7c.0" >
	<field name="fw_image_status_bitmap" descr="Bit 0: Image A is runningBit 1: Image A is committed, module boots from image ABit 2: Image A is erased / emptyBit 3: ReservedBit 4: Image B is runningBit 5: Image B is committed, module boots from image BBit 6: Image B is erased / emptyBit 7: Reserved" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="fw_image_info_bitmap" descr="Bit 0: FW image A is presentBit 1: FW image B is presentBit 2: Factory / boot image is presentBits 3-7: Reserved" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="image_a_minor" descr="Image A FW minor version" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="image_a_major" descr="Image A FW major version" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="image_a_subminor" descr="Image A FW subminor number" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="image_b_minor" descr="Image B FW minor version" access="RO" offset="0xc.0" size="0x0.8" />
	<field name="image_b_major" descr="Image B FW major version" access="RO" offset="0xc.8" size="0x0.8" />
	<field name="image_b_subminor" descr="Image B FW subminor number" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="factory_image_minor" descr="Factory / boot image FW minor version" access="RO" offset="0x14.0" size="0x0.8" />
	<field name="factory_image_major" descr="Factory / boot image FW major version" access="RO" offset="0x14.8" size="0x0.8" />
	<field name="factory_image_subminor" descr="Factory / boot image FW subminor number" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="management_interface_protocol" descr="0: Does not support either one of the FW update procedures defined below1: SFF-8636 management interface and pseudo-CMIS FW. Update is supported2: CMIS 4.0 is implemented3: CMIS 5.0 is implemented4: CMIS 5.2 is implemented5: CMIS 5.3 is implemented6: CMIS 5.4 is implemented7: CMIS 5.5 is implemented" access="RO" offset="0x1c.0" size="0x0.6" />
	<field name="activation_type" descr="0: HW reset is required. Host should be prepared to power cycle a cable\;after sending a RunFWImage command.1: Self-activation with HW reset contained in the RunFWImage command. No\;additional actions required from the host.2:Self-activation with hitless reset contained in the RunFWImage\;command. No additional actions required from the host.3-15: Reserved" access="RO" offset="0x1c.10" size="0x0.4" />
	<field name="abnormal_fw_indication" descr="Flag indicating that the currently running Firmware content deviates from\;the Load identified by the active firmware version information." access="RO" offset="0x1c.15" size="0x0.1" />
	<field name="vendor_sn" descr="Vendor Serial Number" access="RO" offset="0x20.0" size="0x0.16" />
	<field name="fw_support_options" descr="Bit 7: FixedFirmwareFallback — 1b: A fixed firmware load with basic\;firmware download capabilities is available.Bits 6:0: Reserved." access="RO" offset="0x24.0" size="0x0.8" />
	<field name="fw_support_details" descr="Bit 7: UniqueLoadVersionSupported — 1b: Version information is\;characteristic of entire load.Bit 6: DualBankSupported — 1b: Banks A and B are supported.Bit 5: FirmwareLoadTagSupported — 1b: Persistent Firmware Load Tag is\;supported.Bit 4: AbnormalIndicationSupported — 1b: Abnormal Firmware Indication\;is supported.Bit 3: TransferIsHarmless — 1b: Transfer does not impact mission\;integrity and quality.Bit 2: RejectUnsupportedActivation — 1b: Module rejects if activation\;has unwanted side effects.Bits 1:0: Reserved." access="RO" offset="0x24.8" size="0x0.8" />
	<field name="load_management_compliance" descr="bits 7:4: OptionsProfileCompliance: 0: undefined, unknown;\;1: noncompliant; 2: partially compliant, with exceptions; 3: fully\;compliant.\;bits 3:0: RequirementsCompliance: 0: undefined, unknown;\;1: noncompliant; 2: partially compliant, with exceptions; 3: fully\;compliant." access="RO" offset="0x24.16" size="0x0.8" />
	<field name="load_management_feature_support" descr="Byte 0 — FeatureSupport (bits 7:0): 0: Feature is not supported; &gt;0:\;CmisRevision of the feature definition (U4 major, U4 minor)." access="RO" offset="0x24.24" size="0x0.8" />
</node>

<node name="mcqi_reg_data_auto_ext" descr="" attr_is_union="1" size="0x7c.0" >
	<field name="mcqi_activation_method_ext" descr="" subnode="mcqi_activation_method_ext" access="RW" offset="0x0.0" selected_by="ACTIVATION_METHOD" size="0x7c.0" />
	<field name="mcqi_cap_ext" descr="" subnode="mcqi_cap_ext" access="RW" offset="0x0.0" selected_by="CAPABILITIES" size="0x7c.0" />
	<field name="mcqi_clock_source_properties_ext" descr="" subnode="mcqi_clock_source_properties_ext" access="RW" offset="0x0.0" selected_by="CLOCK_SOURCE_PROPERTIES" size="0x4.0" />
	<field name="mcqi_dpa_apps_info_ext" descr="" subnode="mcqi_dpa_apps_info_ext" access="RW" offset="0x0.0" selected_by="DPA_APPS_INFO" size="0x70.0" />
	<field name="mcqi_linkx_properties_ext" descr="" subnode="mcqi_linkx_properties_ext" access="RW" offset="0x0.0" selected_by="LINKX_PROPERTIES" size="0x7c.0" />
	<field name="mcqi_version_ext" descr="" subnode="mcqi_version_ext" access="RW" offset="0x0.0" selected_by="VERSION" size="0x7c.0" />
</node>

<node name="mcqi_reg_ext" descr="" size="0x94.0" >
	<field name="component_index" descr="Component index gathered by\;section 13.1 - MCQS - Management Component Query Status" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="device_index" descr="Device number.For gearboxes, the index represents the gearbox die.For cables, the index represents the module index starting at index 1.\;Index 0 indicates the host device.For Clock Source EEPROM, the index represents the Clock Source Index,\;starting from 1For DPA_APPS_INFO, the index represents the index of the DPA app to\;query, starting from 0" access="INDEX" offset="0x0.16" size="0x0.12" />
	<field name="read_pending_component" descr="When set, the register will return information about the pending\;component (if available)" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="device_type" descr="Peripheral device type:0: Switch / NIC1: Gearbox" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="info_type" descr="Component properties set.0x0: CAPABILITIES0x1: VERSION0x5: ACTIVATION_METHOD0x6: LINKX_PROPERTIES0x7: CLOCK_SOURCE_PROPERTIES0x9: DPA_APPS_INFOOther values are reserved" access="INDEX" enum="CAPABILITIES=0x0,VERSION=0x1,ACTIVATION_METHOD=0x5,LINKX_PROPERTIES=0x6,CLOCK_SOURCE_PROPERTIES=0x7,DPA_APPS_INFO=0x9" offset="0x8.0" size="0x0.5" />
	<field name="info_size" descr="Properties set structure size, given in bytes." access="RO" offset="0xc.0" size="0x4.0" />
	<field name="offset" descr="The requested/returned data offset from the section start, given in\;bytes.Must be DWORD aligned.If offset is invalid, FW will return an error." access="INDEX" offset="0x10.0" size="0x4.0" />
	<field name="data_size" descr="The requested/returned data size, given in bytes.If data_size is not DWORD aligned, the last bytes are zero padded.If size is invalid, FW will return an error." access="INDEX" offset="0x14.0" size="0x0.16" />
	<field name="data" descr="Properties set structure according to info_type.CAPABILITIES - See\;MCQI CAPABILITIES Info LayoutVERSION - See\;MCQI VERSION Info LayoutACTIVATION_METHOD - See\;MCQI ACTIVATION_METHOD Info LayoutLINKX_PROPERTIES - See\;MCQI LINKX_PROPERTIES Info LayoutCLOCK_SOURCE_PROPERTIES - See\;MCQI CLOCK_SOURCE_PROPERTIES LayoutDPA_APPS_INFO - See\;MCQI DPA_APPS_INFO Layout" subnode="mcqi_reg_data_auto_ext" access="RO" offset="0x18.0" size="0x7c.0" union_selector="$(parent).info_type" />
</node>

<node name="mcqi_version_ext" descr="" size="0x7c.0" >
	<field name="version_string_length" descr="" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="user_defined_time_valid" descr="When set, the component has a valid user-defined version time-stamp in\;user_defined_time" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="build_time_valid" descr="When set, the component has a valid creation time-stamp in build_time" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="version" descr="Version number" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="build_time" descr="Time of component creation. Valid only if build_time_valid is set. See\;Date-Time Layout" subnode="date_time_layout_ext" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="user_defined_time" descr="User-defined time assigned to the component version. Valid only if\;user_defined_time_valid is set. See\;Date-Time Layout" subnode="date_time_layout_ext" access="RW" offset="0x10.0" size="0x8.0" />
	<field name="build_tool_version" descr="Build tool version number.Valid only when not equal to 0" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="version_string" descr="NULL terminated string representing the version." access="RW" high_bound="91" low_bound="0" offset="0x20.24" size="0x5c.0" />
</node>

<node name="mcqs_reg_ext" descr="" size="0x10.0" >
	<field name="component_index" descr="Component Index. Values range from 0 to the last component indicated by\;last_index_flag." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="device_index" descr="Device number.For gearboxes, the index represents the gearbox die.For cables, the index represents the module index starting at index 1.\;Index 0 indicates the host device.For Clock synchronizer, index is used to represent the clock sync’\;device index. Starting from 1." access="INDEX" offset="0x0.16" size="0x0.12" />
	<field name="component_not_supported" descr="When set, this component not supported." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="last_index_flag" descr="When set, this component is the last component (highest\;component_index)." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="identifier" descr="This field uniquely identifies a specific component type.0x1: BOOT_IMG0x4: OEM_NVCONFIG0x5: MLNX_NVCONFIG0x6: CS_TOKEN0x7: DBG_TOKEN0xA: Gearbox0xB: CC_ALGO - Congestion Control Algorithm0xC: LINKX_IMG0xD: CRYPTO_TO_COMMISSIONING0xE: RMCS_TOKEN0xF: RMDT_TOKEN0x10: CRCS_TOKEN\;0x11: CRDT_TOKEN 0x12: CLOCK_SYNC_EEPROM  \;0x15: DIGITAL_CACERT - Certificate to be trusted by the device0x17: DIGITAL_CACERT_REMOVAL0x1A: LINKX_FW_ELS0x1C: DPA_COMPONENT0x1D: DPA_COMPONENT_REMOVAL0x1E: MTDT_TOKEN[DWIP]: 0x1F: CPO_VMOD_FW0x20: PSC_TOKEN[DWIP]: 0x22: CPLD_IMG[DWIP]: 0x23: HBI_IMGOther values are reserved" access="RO" enum="BOOT_IMG=0x1,OEM_NVCONFIG=0x4,MLNX_NVCONFIG=0x5,CS_TOKEN=0x6,DBG_TOKEN=0x7,Gearbox=0xa,CC_ALGO=0xb,LINKX_IMG=0xc,CRYPTO_TO_COMMISSIONING=0xd,RMCS_TOKEN=0xe,RMDT_TOKEN=0xf,CRCS_TOKEN=0x10,CRDT_TOKEN=0x11,CLOCK_SYNC_EEPROM=0x12,DIGITAL_CACERT=0x15,DIGITAL_CACERT_REMOVAL=0x17,LINKX_FW_ELS=0x1a,DPA_COMPONENT=0x1c,DPA_COMPONENT_REMOVAL=0x1d,MTDT_TOKEN=0x1e,PSC_TOKEN=0x20" offset="0x4.0" size="0x0.16" />
	<field name="component_update_state" descr="0x0: IDLE0x1: IN_PROGRESS0x2: APPLIED0x3: ACTIVE0x4: ACTIVE_PENDING_RESET0x5: FAILED0x6: CANCELED0x7: BUSYOther values are reserved" access="RO" enum="IDLE=0x0,IN_PROGRESS=0x1,APPLIED=0x2,ACTIVE=0x3,ACTIVE_PENDING_RESET=0x4,FAILED=0x5,CANCELED=0x6,BUSY=0x7" offset="0x8.0" size="0x0.4" />
	<field name="component_status" descr="The status of the component:0x0: NOT_PRESENT - The component is supported by the device but,\;currently not present0x1: PRESENT - This component is present. For downstream devices link\;LinkX component, this is an indication that the binary image is\;present at the host device memory.0x2: IN_USE - The component is present and currently in use." access="RO" enum="NOT_PRESENT=0x0,PRESENT=0x1,IN_USE=0x2" offset="0x8.4" size="0x0.5" />
	<field name="progress" descr="Progress in percentage (from 0 to 100). This field is only relevant for\;cables." access="RO" offset="0x8.9" size="0x0.7" />
	<field name="device_type" descr="Peripheral device type:0: Switch_or_NIC1: Gearbox" access="INDEX" offset="0xc.0" size="0x0.8" />
	<field name="last_update_state_changer_host_id" descr="For last_update_state_changer_type BMC, command-interface and ICMD,\;indicates the identifier of the host of the handle owner. Otherwise\;reserved." access="RO" offset="0xc.24" size="0x0.4" />
	<field name="last_update_state_changer_type" descr="Indicates which entity was the last to change the component_update_state\;of this component.0x0: unspecified0x1: Chassis_BMC0x2: MAD0x3: BMC0x4: command_interface0x5: ICMDOther values are reserved" access="RO" enum="unspecified=0x0,Chassis_BMC=0x1,MAD=0x2,BMC=0x3,command_interface=0x4,ICMD=0x5" offset="0xc.28" size="0x0.4" />
</node>

<node name="mdir_reg_ext" descr="" size="0x40.0" >
	<field name="device_id" descr="Device ID" access="RO" high_bound="7" low_bound="0" offset="0x0.0" size="0x20.0" />
</node>

<node name="mdrcr_ext" descr="" size="0x30.0" >
	<field name="device_type" descr="Peripheral device type1: Gearbox" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="device_index" descr="Device numberFor gearboxes, the index represents the gearbox die." access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="all" descr="All devices are selected and device_index is ignoredWhen set to ‘1’, the rst_status should represent the worst case of any\;of the devices." access="INDEX" offset="0x4.31" size="0x0.1" />
	<field name="rst_op" descr="Reset Operation.0: Query of the reset status which is displayed through rst_status.1: Full Reset of the selected device(s).2-8: Reserved." access="RW" offset="0xc.0" size="0x0.3" />
	<field name="rst_status" descr="Reset status.0: Reset completed successfully. 1: Reset operation has not finished yet." access="RO" offset="0xc.16" size="0x0.4" />
</node>

<node name="mdsr_reg_ext" descr="" size="0x30.0" >
	<field name="status" descr="0: The debug session ended successfully1: Failed to execute the operation. See additional_info for more\;details.2: Debug session active. See type_of_token for more details.3: No token applied4: Challenge provided, no token installed yet, see type_of_token for\;details.5: Timeout before token installed, see type_of_token for details6: Timeout of active token.7-15: ReservedNote: Status might be ‘0’ even when debug query is not allowed and\;additional_info field will expose the reason." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="additional_info" descr="0: No additional information available1: There is no debug session in progress2: FW is not secured, debug session cannot be ended3: Fail - Debug end request cannot be accepted.\;4: Fail - Host is not allowed to query debug session5: Debug session active6: Debug FW is running, cannot remove CRDT token" access="RO" offset="0x0.8" size="0x0.6" />
	<field name="type_of_token" descr="0: CS token 1: Debug FW token 2: FRC token3: RMCS token4: RMDT token5: CRCS token6: CRDT token8: MTFA token0xFF: All tokens. Relevant only when end=1" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="revoke_version" descr="Set to ‘1’ to end debug session.Setting to ‘0’ will not trigger any operation." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="end" descr="Used to revoke token version from device. Relevant only when end=1." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="time_left" descr="Time left in seconds.In case that status is 2 (debug session active) - time left for token\;operationIn case that status is 4 (challenge provided, no token installed yet) -\;time left for token installationFor any other status, field should be zero" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="token_config" descr="First DW of token config TLV value, set to 0 if no token config." access="RO" offset="0xc.0" size="0x4.0" />
</node>

<node name="mdtr_reg_event_params_auto_ext" descr="" attr_is_union="1" size="0xa0.0" >
	<field name="cvb_config_error_ext" descr="" subnode="cvb_config_error_ext" access="RW" offset="0x0.0" selected_by="cvb_config_error" size="0xa0.0" />
</node>

<node name="mdtr_reg_ext" descr="" size="0xb0.0" >
	<field name="event_id" descr="1: cvb_config_error" access="RO" enum="cvb_config_error=0x1" offset="0x0.0" size="0x0.16" />
	<field name="severity" descr="Severity:2: FATL - (fatal) Unrecoverable switch behavior3: NRML - (normal) Unexpected state with possible systemic Failure5: INTR - (debug) Unexpected state without systemic Failure" access="RO" enum="FATL=0x2,NRML=0x3,INTR=0x5" offset="0x0.16" size="0x0.8" />
	<field name="irisc_id" descr="Which RISC triggered the event" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="tile_v" descr="Tile valid:0: The error was from main1: The error was from a tile" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the error." access="RO" offset="0x8.0" size="0x0.4" />
	<field name="event_params" descr="event parameters - layout is according to event_id value:See\;Event_params cvb_config_error Layout" subnode="mdtr_reg_event_params_auto_ext" access="RW" offset="0x10.0" size="0xa0.0" union_selector="$(parent).event_id" />
</node>

<node name="melseq_reg_ext" descr="" size="0x30.0" >
	<field name="module" descr="Module number bits [7:0].Taipan: The PRM is supported for module type OSFP_ELS.Post-Taipan:" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="module_msb" descr="Module number bits [15:8]." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="err_type" descr="Error type:1: laser_fiber_contaminated2: laser_APC_fault3: laser_power_exceeded_allowed_range4: laser_power_subceeded_allowed_range5: laser_TEC_control_loop_fault6: laser_ramping_timeout_fault7: laser_power_tuning_fault" access="INDEX" enum="laser_fiber_contaminated=0x1,laser_APC_fault=0x2,laser_power_exceeded_allowed_range=0x3,laser_power_subceeded_allowed_range=0x4,laser_TEC_control_loop_fault=0x5,laser_ramping_timeout_fault=0x6,laser_power_tuning_fault=0x7" offset="0x0.16" size="0x0.8" />
	<field name="cc" descr="Clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="laser_warn_cnt" descr="Number of warning events occurred for the error typeStuck in 0xFF, cleared with cc field" access="RO" high_bound="7" low_bound="0" offset="0x10.24" size="0x8.0" />
	<field name="laser_alarm_cnt" descr="Number of alarm events occurred for the error typeStuck in 0xFF, cleared with cc field" access="RO" high_bound="7" low_bound="0" offset="0x20.24" size="0x8.0" />
</node>

<node name="melsr_laser_error_recovery_control_ext" descr="" size="0x10.0" >
	<field name="num_of_recovery_retries" descr="Number of laser recovery retriesRelevant only when recovery_en is set" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="th_units" descr="Units of the error_warning_th and error_alarm_th0: mW1: Seconds2: CelsiusOther values are reserved" access="RO" offset="0x0.8" size="0x0.2" />
	<field name="err_type" descr="Error type:0: laser ramping time1: automatic power control2: laser high power3: laser low power4: TEC control loop" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="recovery_en" descr="When set, FW will do laser recovery flowOtherwise, FW will be just\;monitoring and notifyingReserved for fiber check, high power and laser tuning errors" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="laser_relaxtion_time" descr="Specifies the mandatory wait duration between disabling and re-enabling\;the laser during the recovery flowUnits of seconds, minimum value of 1Relevant only when recovery_en is set" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="error_alarm_th" descr="Laser high power alarm thresholdCannot be set for laser high power" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="error_warning_th" descr="Laser high power warning thresholdCannot be set for laser high power" access="RW" offset="0x8.16" size="0x0.16" />
	<field name="alarm_error_grouping_time" descr="Specifies the time in which events are grouped together to decide if to\;continue the recoveriesUnits of seconds, minimum value of 1Relevant only when recovery_en is set" access="RW" offset="0xc.0" size="0x4.0" />
</node>

<node name="melsrc_reg_ext" descr="" size="0x1c.0" >
	<field name="module" descr="Module number bits [7:0]." access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="laser_error" descr="see\;Laser Error Recovery Control Layout)" subnode="melsr_laser_error_recovery_control_ext" access="RW" offset="0xc.0" size="0x10.0" />
</node>

<node name="merr_ext" descr="" size="0x14.0" >
	<field name="ent_type" descr="Entity type.0: Reserved1: QSFP Module (the relevant signals are: present, reset, interrupt,\;power enable, low power mode, power good, modsel, QSFP LEDs)" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="current_index" descr="Current entity index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="target_index" descr="Entity number to be mapped to." access="RW" offset="0x4.0" size="0x0.8" />
</node>

<node name="mfba_reg_ext" descr="" size="0x10c.0" >
	<field name="fs" descr="Flash select - selects the flash device.Only zero is supported for NICs with a single flash deviceRange between 0 .. MFPA.flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="add_cap_32b" descr="Capability bit - If set to ‘1’, address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="size" descr="The size of the data to be written or read in bytesShould comply with block_size and block_alignment fields in MFPA." access="OP" offset="0x4.0" size="0x0.9" />
	<field name="address" descr="The start address of this read or write access in bytes. Should comply\;with block_size and block_alignment fields in MFPA." access="INDEX" offset="0x8.0" size="0x4.0" />
	<field name="data" descr="The data to be written or read data." access="RW" high_bound="63" low_bound="0" offset="0xc.0" size="0x100.0" />
</node>

<node name="mfbe_reg_ext" descr="" size="0xc.0" >
	<field name="fs" descr="Flash select - selects the flash device.Only zero is supported for NICs with a single flash device.Range between 0 .. MFPA.flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="bulk_64kb_erase" descr="Erase a 64KB flash area in one bulk operation." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="bulk_32kb_erase" descr="Erase a 32KB flash area in one bulk operation." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="add_cap_32b" descr="Capability bit - If set to ‘1’, address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="address" descr="The start address (in bytes) of this erase operation. Must be aligned\;with the selected erase size (sector, 32KB or 64KB)." access="INDEX" offset="0x8.0" size="0x4.0" />
</node>

<node name="mfcdr_reg_ext" descr="" size="0x8.0" >
	<field name="module" descr="Module numberValid when query_type = 1, else this field is ignored" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="Local port MSBValid when query_type = 0, else this field is ignored" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local portValid when query_type = 0, else this field is ignored" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="query_type" descr="Selector of query type0: local_port based query1: module based query" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="status" descr="0: N/A1: Fake cable detected2: NVIDIA Cable detected3: Non-Nvidia Cable detected" access="RO" offset="0x4.0" size="0x0.2" />
</node>

<node name="mfde_event_params_auto_ext" descr="" attr_is_union="1" size="0xa0.0" >
	<field name="crspace_timeout_ext" descr="" subnode="crspace_timeout_ext" access="RW" offset="0x0.0" selected_by="crspace_timeout" size="0xa0.0" />
	<field name="fatal_cause_ext" descr="" subnode="fatal_cause_ext" access="RW" offset="0x0.0" selected_by="fatal_cause" size="0xa0.0" />
	<field name="fw_assert_ext" descr="" subnode="fw_assert_ext" access="RW" offset="0x0.0" selected_by="fw_assert" size="0xa0.0" />
	<field name="kvd_im_stop_ext" descr="" subnode="kvd_im_stop_ext" access="RW" offset="0x0.0" selected_by="kvd_im_stop" size="0xa0.0" />
	<field name="riscv_exception_ext" descr="" subnode="riscv_exception_ext" access="RW" offset="0x0.0" selected_by="riscv_exception" size="0x18.0" />
</node>

<node name="mfde_ext" descr="" size="0xb0.0" >
	<field name="event_id" descr="1: crspace_timeout2: kvd_im_stop - KVD insertion machine stopped3: test4: fw_assert5: fatal_cause6: long_cmd_timeout7: riscv_exception" access="RO" enum="crspace_timeout=0x1,kvd_im_stop=0x2,test=0x3,fw_assert=0x4,fatal_cause=0x5,long_cmd_timeout=0x6,riscv_exception=0x7" offset="0x0.0" size="0x0.16" />
	<field name="severity" descr="Severity:2: FATL - (fatal) Unrecoverable switch behavior3: NRML - (normal) Unexpected state with possible systemic Failure5: INTR - (debug) Unexpected state without systemic Failure" access="RO" enum="FATL=0x2,NRML=0x3,INTR=0x5" offset="0x0.16" size="0x0.8" />
	<field name="irisc_id" descr="Which RISC triggered the event" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="reg_attr_id" descr="For access register flows: register idFor MAD flow: attribute idFor command interface other flows: opcode" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="mgmt_class" descr="Reserved when packet_cmd_type ≠1 (mad)0: access register over mad" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="packet_state" descr="Packet stateCurrent packet state:0: idle1: retry2: long processElse, reserved." access="RO" offset="0x4.27" size="0x0.2" />
	<field name="method" descr="0: Query1: Write" access="RO" enum="Query=0x0,Write=0x1" offset="0x4.29" size="0x0.1" />
	<field name="notify_fw_dump_completion" descr="When set, SDK should notify FW once upon completion of the FW dump taken\;due to this event." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="packet_interface" descr="Packet interface identification used internally in the firmware, e.g.,\;PCI, C MDIF_DRIVER, CMDIF_TOOLS, ICMD, INBAND RX0, INBAND RX1, etc…0: Buffer_OOB0 1: Buffer_OOB1 2: Buffer_RX0 3: Buffer_RX1 4: ICMD5: Buffer_PC0 6: CMD_IF_Driver 7: CMD_IF_Tools 8: Buffer_IPR0_QP0 9: Buffer_IPR0_QP1 10: Buffer_IPR0_N2N 11: Buffer_IPR0_HW_Traps 12: Buffer_IPR1_HW_Traps 13: Buffer_SMA_Traps_PBG 14: BMC 100: Buffer_MNG_SL_Q0 101: Buffer_MNG_SL_Q1 102: Buffer_MNG_SL_Q2 103: Buffer_MNG_SL_Q3 104: MNOC0 105: MNOC1 106: Buffer_MNG_SL_Q4 107: Buffer_MNG_SL_Q5" access="RO" enum="Buffer_OOB0=0x0,Buffer_OOB1=0x1,Buffer_RX0=0x2,Buffer_RX1=0x3,ICMD=0x4,Buffer_PC0=0x5,CMD_IF_Driver=0x6,CMD_IF_Tools=0x7,Buffer_IPR0_QP0=0x8,Buffer_IPR0_QP1=0x9,Buffer_IPR0_N2N=0xa,Buffer_IPR0_HW_Traps=0xb,Buffer_IPR1_HW_Traps=0xc,Buffer_SMA_Traps_PBG=0xd,BMC=0xe,Buffer_MNG_SL_Q0=0x64,Buffer_MNG_SL_Q1=0x65,Buffer_MNG_SL_Q2=0x66,Buffer_MNG_SL_Q3=0x67,MNOC0=0x68,MNOC1=0x69,Buffer_MNG_SL_Q4=0x6a,Buffer_MNG_SL_Q5=0x6b" offset="0x8.0" size="0x0.8" />
	<field name="packet_cmd_type" descr="Packet command type:0: access_register1: mad2: otherElse, reserved." access="RO" offset="0x8.8" size="0x0.2" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the timeout.Note: Supersedes event params’ tile_index" access="RO" offset="0x8.16" size="0x0.6" />
	<field name="tile_v" descr="Tile valid:0: The timeout was from main1: The timeout was from a tileNote: Supersedes event params’ tile_v" access="RO" offset="0x8.23" size="0x0.1" />
	<field name="packet_state_sticky" descr="sticky indication of previous packet state (if at some point it was\;different then idle it will stick to that value):0: idle1: retry2: long processElse, reserved." access="RO" offset="0x8.27" size="0x0.2" />
	<field name="event_params" descr="event parameters - layout is according to event_id value:See\;Event_params crspace_timeout LayoutSee\;Event_params kvd_im_stop LayoutSee\;Event_params fw_assert LayoutSee\;Event_params fatal_cause LayoutSee\;RiscV Exception Layout" subnode="mfde_event_params_auto_ext" access="RW" offset="0x10.0" size="0xa0.0" union_selector="$(parent).event_id" />
</node>

<node name="mfpa_reg_ext" descr="" size="0x20.0" >
	<field name="fs" descr="Flash select - selects the flash device.Only zero is supported for NICs with a single flash device.Range between 0 .. flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="add_cap_32b" descr="Capability bit - If set to ‘1’, boot_address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="boot_address" descr="The flash address from which the firmware will boot in the next reset\;(warm start)." access="RW" offset="0x4.0" size="0x4.0" />
	<field name="flash_num" descr="The number of flash devices1: there is 1 flash device, etc." access="RO" offset="0x10.0" size="0x0.4" />
	<field name="sub_sector_wrp_en" descr="If set, MFMC register supports setting write protect with sub-sector-\;blocksSub-sector block size is available in MFMC.sub_sector_protect_size" access="RO" offset="0x10.16" size="0x0.1" />
	<field name="sector_wrp_en" descr="If set, MFMC register supports setting write protect with sector blocks.Sector block size is available in MFMC.sector_protect_size" access="RO" offset="0x10.17" size="0x0.1" />
	<field name="bulk_64kb_erase_en" descr="If set, MFBE register supports 64KB bulk erase operation." access="RO" offset="0x10.29" size="0x0.1" />
	<field name="bulk_32kb_erase_en" descr="If set, MFBE register supports 32KB bulk erase operation." access="RO" offset="0x10.30" size="0x0.1" />
	<field name="wip" descr="Work In Progress. Indicates that the flash is currently busy." access="RO" offset="0x10.31" size="0x0.1" />
	<field name="jedec_id" descr="Return the flash JEDEC ID value returned by the standard Read JEDEC ID\;command that is available in most flash devices." access="RO" offset="0x14.0" size="0x0.24" />
	<field name="sector_size" descr="The minimal unit that can be erased with and MFBE command (in bytes)." access="RO" offset="0x18.0" size="0x0.10" />
	<field name="block_alignment" descr="Log 2 of the requested write alignment in bytes. Write access to the\;flashmust not cross this alignment.Read and write access must be aligned to this value." access="RO" offset="0x18.16" size="0x0.8" />
	<field name="block_size" descr="The block size in byes of the flash device, max read size for MFBA\;(typically 128 bytes)." access="RO" offset="0x18.24" size="0x0.8" />
	<field name="capability_mask" descr="Bitmask indicates which capabilities are supported.Bit 15..0: reserved Bit 16: Set write protect supported (register MFMC supports setting\;write protection)Bit 17: quad enable read write is supported (register MFMC supports\;setting quad enable)Bit 18: set dummy cycle supported (register MFMC supports setting dummy\;cycles)" access="RO" offset="0x1c.0" size="0x4.0" />
</node>

<node name="mfsv_reg_ext" descr="" size="0x30.0" >
	<field name="efuses_prog_en" descr="When this bit is set, it indicates that it is allowed for the boot FW to\;program the FW security version related EFUSEs if needed. This bit is\;not relevant in case the FW operates in an automatically EFUSEs\;programming approach (set in the INI file). Once set to 1, this\;configuration will be relevant only for the upcoming boot, thus this\;configuration will be set back to 0 upon next boot." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="fw_sec_ver_stat" descr="Firmware security version status.0: EFUSEs value is equal to the\;currently running FW image value. No change is needed.1: EFUSEs value is\;smaller than the currently running FW image value. An update to the\;EFUSEs is required.2: There is pending image, MFSV is rejected3: Reserved" access="RO" offset="0x0.1" size="0x0.2" />
	<field name="efuses_prog_method" descr="EFUSEs programming method.0: manually. Upon boot, if FW indicates that\;FW_sec_ver_stat is 1 and only if EFUSEs_prog_en is 1, it will program\;the EFUSEs as needed.1: automatically. Upon boot, if FW indicates that\;FW_sec_ver_stat is 1, it will program the EFUSEs as needed." access="RO" offset="0x0.3" size="0x0.1" />
	<field name="revoke_efuse_prog" descr="0: Do not revoke EFUSE programming (no-op).1: Revoke pending EFUSE programming. This command is possible only if\;reset did not occur from EFUSE programming request, and the EFUSE\;programming revocation request" access="RW" offset="0x0.4" size="0x0.1" />
	<field name="pending_efuse_prog" descr="0: No pending EFUSE programming command1: There is pending MFSV command" access="RO" offset="0x0.5" size="0x0.1" />
	<field name="fuse_failure" descr="" access="RO" offset="0x0.8" size="0x0.2" />
	<field name="index" descr="Index0: NCORE FW1: PSC_BL12: PSC_FW3: BCT4: reserved2_field_ratchet5: vMod6: HBI7: Caliptra8-15: Reserved" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="img_sec_ver" descr="Image security version value" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="efuses_sec_ver" descr="EFUSEs security version value" access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mgcr_reg_ext" descr="" size="0x20.0" >
	<field name="segment" descr="The GPIO segment which the command’s parameters apply" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="segments_count" descr="Ceiling function of total number of GPIOs / 32 in the system." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="GPIO_data_in" descr="Input value of accessible GPIO[i] signals.When GPIO_access_en[i] = 0, GPIO_data_in[i] always returns 0" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="GPIO_data_out" descr="Output value of accessible GPIO signals.When GPIO_access_en[i] = 0, GPIO_data_out[i] always returns 0" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="GPIO_set" descr="These 2 fields are used together to control GPIO signals in the\;following manner:GPIO_set[i]=0, GPIO_clear[i]=0 : GPIO_data_out[i] = No ChangeGPIO_set[i]=0, GPIO_clear[i]=1 : GPIO_data_out[i] = 0GPIO_set[i]=1, GPIO_clear[i]=0 : GPIO_data_out[i] = 1GPIO_set[i]=1, GPIO_clear[i]=1 : GPIO_data_out[i] =\;not(GPIO_data_out[i])Ignored for non-controllable GPIO signals." access="WO" offset="0xc.0" size="0x4.0" />
	<field name="GPIO_clear" descr="(see above)" access="WO" offset="0x10.0" size="0x4.0" />
	<field name="GPIO_access_en" descr="Access allowance to the corresponding GPIO signal.0: GPIO[i] is not observable / controllable by the host SW.1: GPIO[i] is observable / controllable by the host SW." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="direction" descr="0: GPIO[i] is an input only signal1: GPIO[i] is an output signal. Data out can be updates by the host SW\;and data in can be queried by the host SW.For non-accessible GPIOs, the corresponding value is 0." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="drive_type" descr="0: GPIO[i] is an open drain output. The device can only drive the\;GPIO[i] output pin low when GPIO_data_out[i] is 0. When GPIO_data_out[i]\;is 1, GPIO[i] is in HighZ.1: GPIO[i] is a full-drive output pinWhen GPIO_access_en[i] =0, direction[i] and drive_type[i] are always\;read as 0." access="RO" offset="0x1c.0" size="0x4.0" />
</node>

<node name="mgir_dev_info_ext" descr="" size="0x1c.0" >
	<field name="dev_branch_tag" descr="The format of the string represented by ASCII." access="RO" high_bound="27" low_bound="0" offset="0x0.24" size="0x1c.0" />
</node>

<node name="mgir_ext" descr="" size="0xa0.0" >
	<field name="hw_info" descr="Hardware Information, see\;Hardware Info Layout" subnode="mgir_hardware_info_ext" access="RW" offset="0x0.0" size="0x20.0" />
	<field name="fw_info" descr="Firmware Information, see\;Firmware Info Layout" subnode="mgir_fw_info_ext" access="RW" offset="0x20.0" size="0x40.0" />
	<field name="sw_info" descr="Software Information, see\;Software Info LayoutThis field indicates the oldest software version compatible with the\;current firmware" subnode="mgir_sw_info_ext" access="RW" offset="0x60.0" size="0x20.0" />
	<field name="dev_info" descr="Development Information, see\;Development Info Layout" subnode="mgir_dev_info_ext" access="RW" offset="0x80.0" size="0x1c.0" />
</node>

<node name="mgir_fw_info_ext" descr="" size="0x40.0" >
	<field name="sub_minor" descr="Sub-minor firmware version number.Deprecated and returns ‘0’.Refer to extended_sub_minor." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="minor" descr="Minor firmware version number.Deprecated and returns ‘0’.Refer to extended_minor." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="major" descr="Major firmware version number.Deprecated and returns ‘0’.Refer to extended_major." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="secured" descr="When set, the device is running firmware with secure-firmware updates\;capabilities." access="RO" offset="0x0.24" size="0x0.1" />
	<field name="signed_fw" descr="When set the device is running a signed FW binaries." access="RO" offset="0x0.25" size="0x0.1" />
	<field name="debug" descr="When set, the device is running a debug firmware. ‘debug’ binary can\;only be installed on specific devices (identified by their ‘Factory base\;MAC’), which currently run a specific firmware version. These\;restrictions are expressed by a signed ‘debug’ token that must be loaded\;to the device before installing the debug binary." access="RO" offset="0x0.26" size="0x0.1" />
	<field name="dev" descr="*NOTE* this field has diff meaning for Switch vs. NIC" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="string_tlv" descr="When set, string-TLV is supported.For Retimer - always return 0 (not supported)." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="dev_sc" descr="*NOTE* for NICs same as dev fieldDevelopment-secure:The device is running:0: a regular-secure firmware version1: a development-secure firmware version" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="index_tlv" descr="[DWIP] When set, port indexation using Index TLV and Multi Index TLV are\;required." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="build_id" descr="Firmware Build ID. Optional.Note: Deprecated for switches and returns ‘0’." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="year" descr="(see above)" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="day" descr="(see above)" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="month" descr="Firmware installation date.For example: 3 May 2004 will be coded as Month= 0x05, Day= 0x03, and\;Year= 0x04" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="hour" descr="Firmware installation hour.For example 17:43 will be coded as 0x1743" access="RO" offset="0xc.0" size="0x0.16" />
	<field name="BKV_sub_minor" descr="(see above)" access="RO" offset="0xc.16" size="0x0.4" />
	<field name="BKV_minor" descr="(see above)" access="RO" offset="0xc.20" size="0x0.4" />
	<field name="BKV_major" descr="Data lane 21Best Known Values (BKV) version for uPHY." access="RO" offset="0xc.24" size="0x0.4" />
	<field name="psid" descr="FW PSID" access="RO" high_bound="15" low_bound="0" offset="0x10.24" size="0x10.0" />
	<field name="ini_file_version" descr="User-configured version number of the current INI file." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="extended_major" descr="FW version’s Major field in extended (32b) format." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="extended_minor" descr="FW version’s Minor field in extended (32b) format." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="extended_sub_minor" descr="FW version’s SubMinor field in extended (32b) format." access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="isfu_major" descr="incremented by one when version is not ISSUable" access="RO" offset="0x30.0" size="0x0.16" />
	<field name="disabled_tiles_bitmap" descr="Bitmap representing the disabled tiles in the ASIC. Tile ‘0’ is\;represented by the msb bit.0: tile is enabled1: tile is disabledThe total number of tiles can be derived through MGPIR register." access="RO" offset="0x30.16" size="0x0.16" />
	<field name="life_cycle" descr="Note: has also msb bits in life_cycle_msb. Following values are a\;combination of both fields.0: Production1: GA Secured2: GA Non-Secured3: RMA4: Pre Production" access="RO" offset="0x34.0" size="0x0.2" />
	<field name="sec_boot" descr="0: Disable1: Enable" access="RO" offset="0x34.2" size="0x0.1" />
	<field name="encryption" descr="0: Disable1: Enable" access="RO" offset="0x34.3" size="0x0.1" />
	<field name="life_cycle_msb" descr="[DWIP]MSB of the life cycle.Supported in QM3, CX8 and on.See life_cycle field for full value descriptions." access="RO" offset="0x34.4" size="0x0.3" />
	<field name="dev_state" descr="0: device is in prod mode1: device is in dev mode" access="RO" offset="0x34.11" size="0x0.1" />
	<field name="issu_able" descr="[DWIP]ISSU-able:0: not ISSUable1: ISSUableSupported from Quantum-3, Spectrum-6 and onSupported for RetimersBased on FW decisions: fuse, INI, NV and version on flash vs. running\;version" access="RO" offset="0x34.13" size="0x0.1" />
	<field name="pds" descr="[DWIP]0: PSC is not PDS mode1: PSC in PDS modeSupported in QM3,CX8 and on." access="RO" offset="0x34.14" size="0x0.1" />
	<field name="dev_counter" descr="Counter indication of dev fuse value" access="RO" offset="0x34.16" size="0x0.5" />
	<field name="uphy_version_sub_minor" descr="(see above)" access="RO" offset="0x38.0" size="0x0.4" />
	<field name="uphy_version_minor" descr="(see above)" access="RO" offset="0x38.4" size="0x0.4" />
	<field name="uphy_version_major" descr="uPHY version patch, read at runtime from SerDes." access="RO" offset="0x38.8" size="0x0.4" />
	<field name="BKV_clm_sub_minor" descr="(see above)" access="RO" offset="0x38.16" size="0x0.4" />
	<field name="BKV_clm_minor" descr="(see above)" access="RO" offset="0x38.20" size="0x0.4" />
	<field name="BKV_clm_major" descr="Clock-lane (CLM) BKV versions from flashed BKV init package" access="RO" offset="0x38.24" size="0x0.4" />
</node>

<node name="mgir_hardware_info_ext" descr="" size="0x20.0" >
	<field name="device_id" descr="PCI device ID." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="device_hw_revision" descr="See\;Device HW Revision Descriptions" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="pvs" descr="Process Voltage ScalingSupported nominal V_CORE voltage (in 50mV units) for the device." access="RO" offset="0x4.0" size="0x0.5" />
	<field name="technology" descr="Process technology0: N/A1: 40nm2: 28nm3: 16nm4: 7nm5: 5nm6: 3nm7-31: Reserved" access="RO" offset="0x4.11" size="0x0.5" />
	<field name="num_ports" descr="Number of ports the device supports." access="RO" offset="0x4.16" size="0x0.12" />
	<field name="hw_dev_id" descr="The PCI device-ID of the NIC/HCA in recovery (Livefish) mode." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="vbios_variant" descr="[GPUNet]0: boards prior to C051: boards 05 and later3-4: ReservedSupported in GB100." access="RO" offset="0xc.0" size="0x0.2" />
	<field name="module_master_fw_default" descr="Module Master FW Default0: FW is in control over modules management by default1: SW is in control over modules management by default2: Standalone ASIC (no I2C connectivity). Note: Relevant only for Spectrum-3 and above" access="RO" offset="0xc.16" size="0x0.2" />
	<field name="board_ga" descr="Board Geographical Address6 bits for board index" access="RO" offset="0xc.18" size="0x0.6" />
	<field name="cpo_indication" descr="[DWIP][switch_internal]When set, this bit indicates that this system contains CPO modules\;(possibly in addition to others)." access="RO" offset="0xc.27" size="0x0.1" />
	<field name="ga_valid" descr="GA Valid bit0: MGIR.HW Info.ga is reserved1: MGIR.HW Info.ga is validSupported in CX7, QM3 and on." access="RO" offset="0xc.28" size="0x0.1" />
	<field name="development" descr="[DWIP]The device is running:0: a regular-secure firmware version1: a development-secure firmware versionSupported in QM3,CX8 and on." access="RO" offset="0xc.30" size="0x0.1" />
	<field name="manufacturing_base_mac_47_32" descr="MSB of the ‘base’ MAC address of the NIC that was allocate during\;manufacturing. The NIC derives the MAC addresses for the different PCI\;PFs from this MAC address. This parameter can be used as a canonical\;unique identifier of the NIC.manufacturing_base_mac of value 0 means field is not supported." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="ga" descr="Geographical AddressASIC index.Valid for multi ASIC platforms onlyDescribes the device index for the compute node." access="RO" offset="0x10.16" size="0x0.6" />
	<field name="chip_type" descr="[DWIP]Chip Type0: Real chip1: Emulation2: ChipSim3: SimXSupported from Quantum-3 and ArcusE" access="RO" offset="0x10.24" size="0x0.4" />
	<field name="manufacturing_base_mac_31_0" descr="LSB of the ‘base’ MAC address of the NIC that was allocate during\;manufacturing. The NIC derives the MAC addresses for the different PCI\;PFs from this MAC address. This parameter can be used as a canonical\;unique identifier of the NIC.manufacturing_base_mac of value 0 means field is not supported." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="device_ticks_per_msec" descr="Device Ticks per msecReserved when chip_type = Real chip (0)" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="uptime" descr="Time (in secs.) since last reset0" access="RO" offset="0x1c.0" size="0x4.0" />
</node>

<node name="mgir_sw_info_ext" descr="" size="0x20.0" >
	<field name="sub_minor" descr="Sub-minor Driver version number." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="minor" descr="Minor Driver version number." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="major" descr="Major Driver version number." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="rom3_type" descr="ROM 3 type:0x0: none0x1: Flexboot0x2: UEFI0x3: UEFI-CLP0x4: NVME0x5: FCODE0x6: UEFI Virtio net0x7: UEFI Virtio blk0x8: PXE Virtio net0x9-0xF: Reserved" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="rom3_arch" descr="Arch type of ROM 3:0x0: unspecified0x1: AMD64 - x86 64bit architecture0x2: AARCH64 - ARM Architecture 64 bits0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64\;architectures0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="rom2_type" descr="ROM 2type:0x0: none0x1: Flexboot0x2: UEFI0x3: UEFI-CLP0x4: NVME0x5: FCODE0x6: UEFI Virtio net0x7: UEFI Virtio blk0x8: PXE Virtio net0x9-0xF: Reserved" access="RO" offset="0x4.8" size="0x0.4" />
	<field name="rom2_arch" descr="Arch type of ROM 2:0x0: unspecified0x1: AMD64 - x86 64bit architecture0x2: AARCH64 - ARM Architecture 64 bits0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64\;architectures0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.12" size="0x0.4" />
	<field name="rom1_type" descr="ROM 1type:0x0: none0x1: Flexboot0x2: UEFI0x3: UEFI-CLP0x4: NVME0x5: FCODE0x6: UEFI Virtio net0x7: UEFI Virtio blk0x8: PXE Virtio net0x9-0xF: Reserved" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="rom1_arch" descr="Arch type of ROM 1:0x0: unspecified0x1: AMD64 - x86 64bit architecture0x2: AARCH64 - ARM Architecture 64 bits0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64\;architectures0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.20" size="0x0.4" />
	<field name="rom0_type" descr="ROM 0 type:0x0: none0x1: Flexboot0x2: UEFI0x3: UEFI-CLP0x4: NVME0x5: FCODE0x6: UEFI Virtio net0x7: UEFI Virtio blk0x8: PXE Virtio net0x9-0xF: Reserved" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="rom0_arch" descr="Arch type of ROM 0:0x0: unspecified0x1: AMD64 - x86 64bit architecture0x2: AARCH64 - ARM Architecture 64 bits0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64\;architectures0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.28" size="0x0.4" />
	<field name="rom0_version" descr="ROM 0 version." subnode="rom_version_ext" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="rom1_version" descr="ROM 1 version." subnode="rom_version_ext" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="rom2_version" descr="ROM 2version." subnode="rom_version_ext" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="rom3_version" descr="ROM 3 version." subnode="rom_version_ext" access="RO" offset="0x14.0" size="0x4.0" />
</node>

<node name="mgnle_reg_ext" descr="" size="0x20.0" >
	<field name="le_pointer" descr="Pointer to the log entry (see description above for more information)" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="clr" descr="Clears the log entry after read.Supported only if MCAM.mng_feature_cap_mask bit 60 is set." access="OP" offset="0x4.0" size="0x0.1" />
	<field name="lost_events" descr="The number of events that the system failed to log since the previous\;log entry.15 should be interpreted as ‘15 or more events were lost’" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="synced_time" descr="0x0: Boot - time is measured since NIC bootup.0x1: Synced - time was synced by the host." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="time_h" descr="The 32 MSB of the 64bit timestamp. In microsecondsWhen ‘time_synced’ bit is set this is the time passed since the 1/1/1970\;epoch.When ‘time_synced’ is cleared this is the NIC uptime." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="time_l" descr="The 32 LSB of the 64bit timestamp. In microseconds" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="configuration_item_header" descr="" subnode="config_item_ext" access="RO" offset="0x10.0" size="0xc.0" />
	<field name="log_data" descr="The logged data. Format is different per the according to the log type." access="RO" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x1c.0" size="0x4.0" size_condition="$(parent).configuration_item_header.length" />
</node>

<node name="mgpir_ext" descr="" size="0xa0.0" >
	<field name="hw_info" descr="Hardware Information, see\;Hardware Info Layout" subnode="mgpir_hw_info_ext" access="RW" offset="0x0.0" size="0x20.0" />
	<field name="hw_metadata" descr="[Switch][DWIP]Hardware meta-data, see\;Hardware Metadata Layout" subnode="mgpir_hw_metadata_ext" access="RW" offset="0x20.0" size="0x20.0" />
</node>

<node name="mgpir_hw_info_ext" descr="" size="0x20.0" >
	<field name="slot_index" descr="Slot index0: Main board" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="max_modules_per_slot" descr="Maximum number of modules that can be connected per slot, bits [7:0].\;Includes internal and external modules." access="RO" offset="0x4.16" size="0x0.8" />
	<field name="total_num_of_module_i2c_bus" descr="Total number of module i2c bus" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="num_lanes_per_sub_module" descr="Maximum lane count per submodule" access="RO" offset="0x8.16" size="0x0.4" />
	<field name="max_sub_modules_index" descr="The maximum submodule index.0: Only one submodule 3: Four submodulesOther values are reserved" access="RO" offset="0x8.24" size="0x0.4" />
	<field name="num_of_modules_msb" descr="[Switch][DWIP]Bits [15:8] of number of all modules on ASIC (chip/package)." access="RO" offset="0xc.0" size="0x0.8" />
	<field name="num_of_modules_per_system_msb" descr="[Switch][DWIP]Bits [15:8] of number of all modules on system (tray)." access="RO" offset="0xc.8" size="0x0.8" />
	<field name="max_modules_per_slot_msb" descr="[Switch][DWIP]Bits [15:8] of number of top-level modules (e.g not including OEs and\;ELSes) on ASIC (chip/package)." access="RO" offset="0xc.16" size="0x0.8" />
	<field name="els_count_local" descr="[Switch][DWIP]Number of ELSes connected to ASIC (chip/package)." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="oe_count_local" descr="[Switch][DWIP]Number of Optical Engines on ASIC (chip/package)." access="RO" offset="0x10.16" size="0x0.16" />
	<field name="els_count_global" descr="[Switch][DWIP]Number of ELSes connected to system (tray)." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="oe_count_global" descr="[Switch][DWIP]Number of Optical Engines on system (tray)." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="tl_module_non_mission_count_local" descr="[Switch][DWIP]Number of top-level non-mission modules on ASIC (chip/package).." access="RO" offset="0x18.0" size="0x0.16" />
</node>

<node name="mgpir_hw_metadata_ext" descr="" size="0x20.0" >
	<field name="tl_module_mission_base_index_local" descr="[DWIP]Top Level Mission Modules base index for ASIC (chip/package)." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="tl_module_mission_base_index_global" descr="[DWIP]Top Level Mission Modules base index for system (tray)." access="RO" offset="0x0.16" size="0x0.16" />
	<field name="tl_module_non_mission_base_index_local" descr="[DWIP]Top Level Non-Mission Modules base index for ASIC (chip/package)." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="tl_module_non_mission_base_index_global" descr="[DWIP]Top Level Non-Mission Modules base index for system (tray)." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="els_base_index_local" descr="[DWIP]ELS base index for ASIC (chip/package)." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="els_base_index_global" descr="[DWIP]ELS base index for system (tray)." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="oe_base_index_local" descr="[DWIP]Optical Engines base index for ASIC (chip/package)." access="RO" offset="0xc.0" size="0x0.16" />
	<field name="oe_base_index_global" descr="[DWIP]Optical Engines base index for system (tray)." access="RO" offset="0xc.16" size="0x0.16" />
</node>

<node name="mhmpr_reg_ext" descr="" size="0x14.0" >
	<field name="upm" descr="‘0’ - if the ports are managed by host.‘1’ - if the ports are not managed by host" access="RW" offset="0x0.0" size="0x0.1" />
</node>

<node name="midfv_reg_ext" descr="" size="0x80.0" >
	<field name="dev_branch_tag" descr="The format of the string represented by ASCII." access="RO" high_bound="63" low_bound="0" offset="0x4.24" size="0x40.0" />
</node>

<node name="milaq_ext" descr="" size="0x24.0" >
	<field name="entity_input_type" descr="0: Top-Level module.1: Optical Engine.2: ELS." access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="entity_input_format" descr="0: asic_scope_separate_namespaces.1: asic_scope_shared_module_namespace. Only relevant for top-level\;modules, OEs, ELSes.2: module_scope_separate_namespaces. Only relevant for top-level\;modules, OEs, ELSes." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="entity_instance_input_count" descr="Currently only a value of 1 is supported." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="entity_sub_instance_input_count" descr="If entity_input_format is other than module_scope_seperate_namespaces,\;must be 0.If entity_input_format is module_scope_seperate_namespaces, currently\;only a value of 1 is supported." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="entity_instance_input_index_base" descr="Entity instance input index base." access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="entity_sub_instance_input_index_base" descr="Entity instance input subindex base.If entity_sub_instance_input_count is 0, this field is ignored." access="INDEX" offset="0x4.16" size="0x0.16" />
	<field name="entity_output_type" descr="0: Top-Level module.1: Optical Engine.2: ELS." access="INDEX" offset="0x8.0" size="0x0.8" />
	<field name="entity_output_format" descr="0: asic_scope_separate_namespaces.1: asic_scope_shared_module_namespace. Only relevant for top-level\;modules, OEs, ELSes.2: module_scope_separate_namespaces. Only relevant for top-level\;modules, OEs, ELSes." access="INDEX" offset="0x8.8" size="0x0.8" />
	<field name="entity_instance_output_count" descr="Number of indexes starting from entity_intsance_output_base_index." access="RO" offset="0x8.16" size="0x0.8" />
	<field name="entity_sub_instance_output_count" descr="Number of indexes starting from entity_intsance_output_base_index. If entity_output_format is other than module_scope_seperate_namespaces,\;will be 0." access="RO" offset="0x8.24" size="0x0.8" />
	<field name="entity_instance_output_base_index" descr="Entity instance output index base." access="RO" offset="0xc.0" size="0x0.16" />
	<field name="entity_sub_instance_output_base_index" descr="Entity instance output subindex base.If entity_sub_instance_input_count is 0, this field is invalid." access="RO" offset="0xc.16" size="0x0.16" />
	<field name="session_current_valid" descr="1: session_current_handle is valid.Currently only 0 is supported." access="OP" offset="0x10.0" size="0x0.1" />
	<field name="session_current_status" descr="0: Invalid session handle." access="RO" offset="0x10.30" size="0x0.1" />
	<field name="session_next_valid" descr="1: session_next_handle is valid.Currently only 0 is supported." access="RO" offset="0x10.31" size="0x0.1" />
	<field name="session_current_handle" descr="Session current handle." access="OP" offset="0x14.0" size="0x4.0" />
	<field name="session_next_handle" descr="Session next handle." access="RO" offset="0x18.0" size="0x4.0" />
</node>

<node name="mirc_reg_ext" descr="" size="0x8.0" >
	<field name="status_code" descr="Indicates the successful completion of the instruction, or the reason it\;failed.0x0: OK0x1: BUSY0x2: PROHIBITED_FW_VER_ERR0x3: FIRST_PAGE_COPY_FAILED0x4: FIRST_PAGE_ERASE_FAILED0x5: FIRST_PAGE_RESTORE_FAILED0x6: CANDIDATE_FW_DEACTIVATION_FAILED0x7: FW_ALREADY_ACTIVATED0x8: ERROR_DEVICE_RESET_REQUIRED0x9: ERROR_FW_PROGRAMMING_NEEDEDOther values should be treated as an unknown error." access="RO" offset="0x0.0" size="0x0.8" />
</node>

<node name="misg_ext" descr="" size="0x10.0" >
	<field name="issu_error_code" descr="Last abort reason (most recent non-zero abort). Same encoding as Issu_Mem\;issu_error_code (bits [11:4])." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="issu_status" descr="Live mirror of Issu_Mem issu_status (bits [3:0])." access="RO" offset="0x0.8" size="0x0.4" />
	<field name="issu_start_times" descr="Number of ISSU attempts initiated. Saturates at 31." access="RO" offset="0x0.16" size="0x0.5" />
	<field name="issu_done_times" descr="Number of ISSU completions. Saturates at 31." access="RO" offset="0x0.21" size="0x0.5" />
	<field name="issu_abort_times" descr="Number of aborted ISSU attempts (any non-zero issu_error_code). Saturates at 31." access="RO" offset="0x0.26" size="0x0.5" />
	<field name="clear_counters" descr="Write 1 to clear the ISSU counters: issu_start_times, issu_done_times,\;issu_abort_times and issu_abort_reason_histogram. issu_status and issu_error_code\;are not affected. Write 0: no effect." access="OP" offset="0x0.31" size="0x0.1" />
	<field name="issu_abort_reason_histogram" descr="Per-reason abort counters, indexed by issu_error_code; each element saturates at\;0xFF. Array of 12 8-bit elements, packed 4 per DWORD\;(issu_abort_reason_histogram[0] at bits 7:0 of 04h,\;issu_abort_reason_histogram[11] at bits 31:24 of 0Ch). Element i counts aborts with\;issu_error_code = i; elements [1] to [10] are active, [0] and [11] are reserved." access="RO" high_bound="11" low_bound="0" offset="0x4.24" size="0xc.0" />
</node>

<node name="missuv_ext" descr="" size="0x20.0" >
	<field name="target_issu_minor" descr="Target ISSU Minor version" access="RO" offset="0x1c.0" size="0x0.16" />
	<field name="target_issu_major" descr="Target ISSU Major version (compare to MGIR.isfu_major)" access="RO" offset="0x1c.16" size="0x0.16" />
</node>

<node name="mjtag_ext" descr="" size="0x30.0" >
	<field name="size" descr="Size of operation – relevant for JTAG interface access commands only,\;indicating the number of transaction bytes to execute. Maximum size\;supported is 40.Note: when size=0, no operation is performed (clock is not toggled). The\;tdo is sampled and provided in the response at jtag_transaction_set_0." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="sequence_number" descr="Command sequence number – to prevent re-execution of the same command\;due to command retransmission, this command includes a sequence number.The enable and disable commands MUST be issues with sequence_number = 0\;while any JTAG access command must increase the sequence_number by 1\;(the first JTAG access command should start at sequence_number = 1)." access="WO" offset="0x0.24" size="0x0.4" />
	<field name="cmd" descr="Command0 – JTAG interface disable – JTAG interface is disabled1 – JTAG interface enable – enabling JTAG interface2 – JTAG interface access" access="RW" offset="0x0.30" size="0x0.2" />
	<field name="jtag_transaction_set" descr="See JTAG Transaction Set Byte Layout" access="RW" high_bound="43" low_bound="0" offset="0x4.24" size="0x2c.0" />
</node>

<node name="mkdc_reg_ext" descr="" size="0x2c.0" >
	<field name="error_code" descr="Indicates the successful completion of the instruction or the reason it\;failed:0: OK1: BAD_SESSION_ID2: BAD_KEEP_ALIVE_COUNTER3: BAD_SOURCE_ADDRESS4: SESSION_TIMEOUTOther values are Reserved." access="RO" enum="OK=0x0,BAD_SESSION_ID=0x1,BAD_KEEP_ALIVE_COUNTER=0x2,BAD_SOURCE_ADDRESS=0x3,SESSION_TIMEOUT=0x4" offset="0x0.0" size="0x0.4" />
	<field name="session_id" descr="Unique debug session identifier." access="INDEX" offset="0x0.16" size="0x0.16" />
	<field name="current_keep_alive_counter" descr="Running counter that states the current sequence number of each\;keep-alive session." access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="next_keep_alive_counter" descr="Running counter that states the expected next sequence number of each\;keep-alive session." access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mlcr_ext" descr="" attr_required_tlvs="index:s" size="0xc.0" >
	<field name="led_type" descr="Led type (only supported when cap_local_or_uid_only==1.)0: LOCALP_AND_UID - not supported1: UID 2: LOCALP - local port" access="INDEX" enum="LOCALP_AND_UID=0x0,UID=0x1,LOCALP=0x2" offset="0x0.0" size="0x0.4" />
	<field name="cap_local_or_uid_only" descr="If set, led_type of type UID and LOCAL Port only are supported." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="operation_cap" descr="If set to ‘1’, operation field is supported." access="RO" offset="0x0.5" size="0x0.1" />
	<field name="operation" descr="0: Controlled by HW / Beacon1: LED on -2: LED off - PHY and Logic LEDs are offOthers: Reserved" access="RW" offset="0x0.12" size="0x0.4" />
	<field name="local_port" descr="Local port numberNot supported for CPU portValid only when led_type = LOCALP (2)" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lp_msb" descr="2-bit expansion of the local port. Represents the local_port[9:8] bitsValid only when led_type = LOCALP (2)" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="beacon_duration" descr="Duration of the beacon to be active, units of secondsThe value of 0x0 will turn off the beaconThe value of 0xffff will set the beacon to infinity" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="beacon_remain" descr="Remaining duration of the beacon, units of secondsThe value of 0xffff means infinity" access="RO" offset="0x8.0" size="0x0.16" />
</node>

<node name="mmdio_ext" descr="" size="0xc.0" >
	<field name="operation" descr="0 - NOP1 - Address (reserved for Clause 22)2 - Read3 - Write4 - Post Read Increment Address (reserved for Clause 22)6 - Address + Read - Generates Address cycle and then Read cycle in\;Clause 45 (reserved for Clause 22)7 - Address + Write - Generates Address cycle and then Write cycle in\;Clause 45 (reserved for Clause 22)" access="WO" offset="0x0.0" size="0x0.3" />
	<field name="clause" descr="MDIO Definition:0 - Clause 221 - Clause 45" access="WO" offset="0x0.8" size="0x0.2" />
	<field name="mdio_index" descr="Selection of the MDIO interface" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="reg_adr" descr="Reg Address (Clause 22) / Dev Type (Clause 45)" access="RW" offset="0x4.0" size="0x0.5" />
	<field name="phy_adr" descr="PHY Address (PHYAD)" access="RW" offset="0x4.8" size="0x0.5" />
	<field name="data" descr="Data (Clause 22) / Address/Data (Clause 45)" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="address" descr="Address (Clause 45)This field is only valid for Address + Read and Address + Write\;operations, providing the address. For other Clause 45 operations the\;data field provides the address when appropriate." access="RW" offset="0x8.16" size="0x0.16" />
</node>

<node name="mmta_reg_ext" descr="" size="0x90.0" >
	<field name="module" descr="module number bits [7:0]." access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="module_msb" descr="module number bits [15:8].Switch: Local module indexes.For read operation, supported concatenated module number ranges are -Range 1 base: MGPIR.tl_module_mission_base_index_localRange 1 count: &lt;MGPIR.max_modules_per_slot_msb, MGPIR.max_modules_per_slot&gt; - MGPIR.tl_module_non_mission_count_localRange 2 base: MGPIR.tl_module_non_mission_base_index_localRange 2 count: MGPIR.tl_module_non_mission_count_localRange 3 base: MGPIR.els_base_index_localRange 3 count: MGPIR.els_count_localRange 4 base: MGPIR.oe_base_index_localRange 4 count: MGPIR.oe_count_localFor write operation, only ranges 1 and 2 above are supported." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="supported_measurements" descr="Supported measurements bit maskBit 0: Temperature - ELS. Only set if the concatenation of &lt;module_msb,\;module&gt; refers to the index of a top-level module or ELS.Bit 1: TEC Power. Only set if the concatenation of &lt;module_msb, module&gt;\;refers to the index of a top-level module.Bit 2: Second Temperature - Optical Engines. Only set if the\;concatenation of &lt;module_msb, module&gt; refers to the index of a top-level\;module or OE.Other are reserved." access="RO" offset="0x0.24" size="0x0.4" />
	<field name="module_name_hi" descr="8 characters long module name" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="module_name_lo" descr="(see above)" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="module_temperature" descr="Temperature, see Module Temperature Layout" subnode="mmta_temprature_ext" access="RW" offset="0xc.0" size="0x18.0" />
	<field name="module_tec_power" descr="TEC Power, see Module TEC Power Layout" subnode="mmta_tec_power_ext" access="RW" offset="0x24.0" size="0x20.0" />
	<field name="module_second_temperature" descr="Second Temperature, see\;Module Temperature Layout.Note: When there is more than one Optical Engine:1) The “temperature” field shall be populated by the highest of the\;current OE temperatures.2) The “max_temperature” field shall be populated by the highest of any\;temperatures that had been measured, over all OEs." subnode="mmta_temprature_ext" access="RW" offset="0x44.0" size="0x18.0" />
</node>

<node name="mmta_tec_power_ext" descr="" size="0x20.0" >
	<field name="cooling_level" descr="The required cooling level based on TEC power and Set Point.Cooling Level units are % i.e percentage.0% (no need to cool down) to 100% (max cooling resource, e.g fan, to\;cool down the module)." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="temp_unit" descr="Temperature measurement units0: units of 0.125 Celsius degrees1: units of 1/256 Celsius degreesFor negative values 2’s complement is used" access="INDEX" offset="0x0.29" size="0x0.1" />
	<field name="mtpr" descr="Max TEC Power Reset:0: do not modify the value of the max temperature register1: clear the value of the max TEC Power and max Setpoint register" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="mtpe" descr="Max TEC Power Enable:0: disable measuring the max TEC Power and set point on a module1: enables measuring the max TEC Power and set point on a module" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="tec_power" descr="TEC power reading from the module. Units of 1mW." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_tec_power" descr="The highest measured TEC power from the module.Reserved when mtece = 0Cleared by mtecr = 1" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="tec_power_warning_low" descr="Refers to module TEC Power low warning threshold. Units of 1mW." access="RW" offset="0x8.0" size="0x0.16" />
	<field name="tec_power_warning_high" descr="Refers to module TEC Power high warning threshold. Units of 1mW." access="RW" offset="0x8.16" size="0x0.16" />
	<field name="tec_power_alarm_low" descr="Refers to module TEC Power low alarm threshold. Units of 1mW." access="RW" offset="0xc.0" size="0x0.16" />
	<field name="tec_power_alarm_high" descr="Refers to module TEC Power high alarm threshold. Units of 1mW." access="RW" offset="0xc.16" size="0x0.16" />
	<field name="set_point_temperature" descr="Laser set point measured from the laserUnits defined at temp_unit field" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="max_set_point_temperature" descr="The highest measured set point from the module.Reserved when mtece = 0Cleared by mtecr = 1" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="set_point_temperature_warning_low" descr="Refers to module set point low warning threshold Units defined at\;temp_unit field" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="set_point_temperature_warning_high" descr="Refers to module TEC Power high warning threshold Units defined at\;temp_unit field" access="RW" offset="0x14.16" size="0x0.16" />
	<field name="set_point_temperature_alarm_low" descr="Refers to module set point low alarm thresholdUnits defined at temp_unit field" access="RW" offset="0x18.0" size="0x0.16" />
	<field name="set_point_temperature_alarm_high" descr="Refers to module set point high alarm thresholdUnits defined at temp_unit field" access="RW" offset="0x18.16" size="0x0.16" />
	<field name="min_cooling_level" descr="The minimum allowed cooling level" access="RO" offset="0x1c.0" size="0x0.16" />
	<field name="max_cooling_level" descr="The maximum allowed cooling level" access="RO" offset="0x1c.16" size="0x0.16" />
</node>

<node name="mmta_temprature_ext" descr="" size="0x18.0" >
	<field name="ref_module_valid" descr="1: ref_module field valid.This bit is set only when the &lt;module_msb, module&gt; concatenation refers\;to the index of a top-level module. In such a case, the ref_module field\;refers to the index of the component with the highest current\;temperature of that component type." access="RO" offset="0x0.25" size="0x0.1" />
	<field name="temp_unit" descr="Temperature measurement units0: units of 0.125 Celsius degrees1: units of 1/256 Celsius degreesFor negative values 2’s complement is used" access="INDEX" offset="0x0.26" size="0x0.1" />
	<field name="twee" descr="Temperature Warning Event Enable (MMTA Trap)0: do_not_generate_event1: generate_events2: generate_single_event" access="RW" enum="do_not_generate_event=0x0,generate_events=0x1,generate_single_event=0x2" offset="0x0.27" size="0x0.2" />
	<field name="twe" descr="Temperature Warning Enable:0: all fields are set1: only twee field is set, all other fields reserved" access="OP" offset="0x0.29" size="0x0.1" />
	<field name="mtr" descr="Max Temperature Reset:0: do not modify the value of the max temperature register1: clear the value of the max temperature register" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="mte" descr="Max Temperature Enable:0: disable measuring the max temperature on a sensor1: enables measuring the max temperature on a sensor" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="temperature" descr="Temperature reading from the moduleUnits defined at temp_unit field" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_temperature" descr="The highest measured temperature from the module.Reserved when mte = 0Cleared by mtr = 1" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="temperature_warning_low" descr="Refers to module temperature low warning thresholdUnits defined at temp_unit field" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="temperature_warning_high" descr="Refers to module temperature high warning thresholdUnits defined at temp_unit field" access="RW" offset="0x8.16" size="0x0.16" />
	<field name="temperature_alarm_low" descr="Refers to module temperature low alarm thresholdUnits defined at temp_unit field" access="RW" offset="0xc.0" size="0x0.16" />
	<field name="temperature_alarm_high" descr="Refers to module temperature high alarm thresholdUnits defined at temp_unit field" access="RW" offset="0xc.16" size="0x0.16" />
	<field name="ref_module" descr="Indicates the index of the OE or ELS component, whose information is\;reflected in this structure." access="RO" offset="0x10.0" size="0x0.16" />
</node>

<node name="mnvda_reg_ext" descr="" size="0x10c.0" >
	<field name="configuration_item_header" descr="Configuration Item Header" subnode="config_item_ext" access="RW" offset="0x0.0" size="0xc.0" />
	<field name="configuration_item_data" descr="Configuration Item Data" access="RW" high_bound="63" low_bound="0" offset="0xc.0" size="0x100.0" />
</node>

<node name="mnvdi_reg_ext" descr="" size="0xc.0" >
	<field name="configuration_item_header" descr="" subnode="config_item_ext" access="RW" offset="0x0.0" size="0xc.0" />
</node>

<node name="mnvgc_reg_ext" descr="" size="0x10.0" >
	<field name="nvda_read_factory_settings" descr="NVDA Read factory settings. Indicates if\;reading the factory settings by NVDA is supported.0:unsupported1: supported" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="nvda_read_current_settings" descr="NVDA Read current settings. Indicates if reading the current settings by\;NVDA is supported.0: unsupported1: supported" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="priv_nv_other_host" descr="When set, TLVs of other hosts may be modified." access="RO" offset="0x0.2" size="0x0.1" />
</node>

<node name="mnvgn_reg_ext" descr="" size="0x20.0" >
	<field name="nv_pointer" descr="Pointer to the NV parameter (see description above for more information)" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_header" descr="" subnode="config_item_ext" access="RW" offset="0x10.0" size="0xc.0" />
	<field name="configuration_item_data" descr="Configuration Item Data" access="RW" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x1c.0" size="0x4.0" size_condition="$(parent).configuration_item_header.length" />
</node>

<node name="mnvia_reg_ext" descr="" size="0x8.0" >
	<field name="target" descr="Information targeted for invalidation0: ALL - all NVRAM parameters.All other values are reserved." access="WO" offset="0x0.0" size="0x0.3" />
	<field name="writer_id" descr="The entity which perform the invalidate.The encoding same as writer_id in Configuration Item register (See\;Configuration Item Header Layout)." access="RW" offset="0x0.4" size="0x0.5" />
</node>

<node name="mnvqc_reg_ext" descr="" size="0x8.0" >
	<field name="type" descr="Configuration item type according to its class.Configuration Item Data Type Class Global LayoutConfiguration Item Data Type Class Physical Port LayoutConfiguration Item Data Type Class Per Host-PF LayoutConfiguration Item Data Type Class Log LayoutConfiguration Item Data Type Class File LayoutConfiguration Item Data Type Class Multi Instance Layout" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="support_rd" descr="The configuration item is supported and can be read" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="support_wr" descr="The configuration item is supported and can be updated" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="version" descr="The maximal version of the configuration item supported by the device" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="host_id_valid" descr="Host ID valid:1: the type_index.host_id field is validValid only when MNVGC.priv_nv_other_host=1 and the type_class is a Host\;or Host-PF." access="INDEX" offset="0x4.9" size="0x0.1" />
</node>

<node name="modcr_ext" descr="" size="0x14.0" >
	<field name="clear" descr="Clear the coutners" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="fatal_asserts" descr="Count number of fatal asserts" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="normal_asserts" descr="Count number of normal asserts" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="debug_asserts" descr="Count number of debug asserts" access="RO" offset="0x10.0" size="0x4.0" />
</node>

<node name="module_latched_flag_info_ext" descr="" size="0x50.0" >
	<field name="rx_los_cap" descr="when set, indicates modules supports rx los indication" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="dp_fw_fault" descr="Valid for CMIS based modules onlyLatched modules Datapath fw fault flag" access="RO" offset="0x0.22" size="0x0.1" />
	<field name="mod_fw_fault" descr="Valid for CMIS based modules onlyLatched module fw fault flag" access="RO" offset="0x0.23" size="0x0.1" />
	<field name="vcc_flags" descr="Latched VCC flags of moduleBit 0: high_vcc_alarmBit 1: low_vcc_alarmBit 2: high_vcc_warningBit 3: low_vcc_warning" access="RO" enum="high_vcc_alarm=0x1,low_vcc_alarm=0x2,high_vcc_warning=0x4,low_vcc_warning=0x8" offset="0x0.24" size="0x0.4" />
	<field name="temp_flags" descr="Latched temperature flags of moduleBit 0: high_temp_alarmBit 1: low_temp_alarmBit 2: high_temp_warningBit 3: low_temp_warning" access="RO" enum="high_temp_alarm=0x1,low_temp_alarm=0x2,high_temp_warning=0x4,low_temp_warning=0x8" offset="0x0.28" size="0x0.4" />
	<field name="tx_ad_eq_fault" descr="Reserved for SFPBitmask for latched Tx adaptive equalization fault flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="tx_cdr_lol" descr="Bitmask for latched Tx cdr loss of lock flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="tx_los" descr="Reserved for SFPBitmask for latched Tx loss of signal flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="tx_fault" descr="Bitmask for latched Tx fault flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="tx_power_lo_war" descr="Bitmask for latched Tx power low warning flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="tx_power_hi_war" descr="Bitmask for latched Tx power high warning flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="tx_power_lo_al" descr="Bitmask for latched Tx power low alarm flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="tx_power_hi_al" descr="Bitmask for latched Tx power high alarm flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="tx_bias_lo_war" descr="Bitmask for latched Tx bias low warning flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0xc.0" size="0x0.8" />
	<field name="tx_bias_hi_war" descr="Bitmask for latched Tx bias high warning flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0xc.8" size="0x0.8" />
	<field name="tx_bias_lo_al" descr="Bitmask for latched Tx bias low alarm flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0xc.16" size="0x0.8" />
	<field name="tx_bias_hi_al" descr="Bitmask for latched Tx bias high alarm flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0xc.24" size="0x0.8" />
	<field name="rx_cdr_lol" descr="Bitmask for latched Rx cir loss of lock flag per lane.Bit 0 - lane 0 .. Bit 7 - lane 7" access="RO" offset="0x10.16" size="0x0.8" />
	<field name="rx_los" descr="Bitmask for latched Rx loss of signal flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x10.24" size="0x0.8" />
	<field name="rx_power_lo_war" descr="Bitmask for latched Rx power low warning flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x14.0" size="0x0.8" />
	<field name="rx_power_hi_war" descr="Bitmask for latched Rx power high warning flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x14.8" size="0x0.8" />
	<field name="rx_power_lo_al" descr="Bitmask for latched Rx power low alarm flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x14.16" size="0x0.8" />
	<field name="rx_power_hi_al" descr="Bitmask for latched Rx power high alarm flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x14.24" size="0x0.8" />
	<field name="rx_output_valid_change" descr="Bitmask for latched rx output valid change per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x18.0" size="0x0.8" />
	<field name="laser_source_flag_in_use_msb" descr="Bitmask per flag type in ELS module.When bit is set, indicates that FW reads flag from module.In order to get reliable latched flag information for that flag, it’s\;recommended to set event for module flags via trap.Bit 0: laser2_temp_hi_alBit 1: laser2_temp_lo_alBit 2: laser2_temp_hi_warBit 3: laser2_temp_lo_war" access="RO" offset="0x18.24" size="0x0.4" />
	<field name="laser2_warning_flag" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;ELS laser2 warning indication" access="RO" offset="0x18.28" size="0x0.1" />
	<field name="laser_warning_flag" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;ELS laser warning indication" access="RO" offset="0x18.29" size="0x0.1" />
	<field name="laser2_fault_flag" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;ELS laser2 fault indication" access="RO" offset="0x18.30" size="0x0.1" />
	<field name="laser_fault_flag" descr="ELS laser fault indication" access="RO" offset="0x18.31" size="0x0.1" />
	<field name="laser2_bias_lo_war" descr="ELS laser bias low warning" access="RO" offset="0x20.0" size="0x0.1" />
	<field name="laser_bias_lo_war" descr="ELS laser bias low warning" access="RO" offset="0x20.1" size="0x0.1" />
	<field name="laser2_bias_hi_war" descr="ELS laser bias high warning" access="RO" offset="0x20.2" size="0x0.1" />
	<field name="laser_bias_hi_war" descr="ELS laser bias high warning" access="RO" offset="0x20.3" size="0x0.1" />
	<field name="laser2_bias_lo_al" descr="ELS laser bias low alarm" access="RO" offset="0x20.4" size="0x0.1" />
	<field name="laser_bias_lo_al" descr="ELS laser bias low alarm" access="RO" offset="0x20.5" size="0x0.1" />
	<field name="laser2_bias_hi_al" descr="ELS laser bias high alarm" access="RO" offset="0x20.6" size="0x0.1" />
	<field name="laser_bias_hi_al" descr="ELS laser bias high alarm" access="RO" offset="0x20.7" size="0x0.1" />
	<field name="laser_source_flag_in_use" descr="Bitmask per flag type in ELS module.When bit is set, indicates that FW reads flag from module.In order to get reliable latched flag information for that flag, it’s\;recommended to set event for module flags via trap.Bit 0: global_alarm_for_laserBit 1: global_warning_for_laserBit 2: laser_bias_hi_al_capBit 3: laser_bias_lo_al_capBit 4: laser_bias_hi_war_capBit 5: laser_bias_lo_war_capBit 6: laser_opt_pwr_hi_al_capBit 7: laser_opt_pwr_lo_al_capBit 8: laser_opt_pwr_hi_war_capBit 9: laser_opt_pwr_lo_war_capBit 10: laser_temp_hi_alBit 11: laser_temp_lo_alBit 12: laser_temp_hi_warBit 13: laser_temp_lo_warBit 14: global_alarm_for_laser2Bit 15: global_warning_for_laser2Bit 16: laser2_bias_hi_al_capBit 17: laser2_bias_lo_al_capBit 18: laser2_bias_hi_war_capBit 19: laser2_bias_lo_war_capBit 20: laser2_opt_pwr_hi_al_capBit 21: laser2_opt_pwr_lo_al_capBit 22: laser2_opt_pwr_hi_war_capBit 23: laser2_opt_pwr_lo_war_cap" access="RO" enum="global_alarm_for_laser=0x1,global_warning_for_laser=0x2,laser_bias_hi_al_cap=0x4,laser_bias_lo_al_cap=0x8,laser_bias_hi_war_cap=0x10,laser_bias_lo_war_cap=0x20,laser_opt_pwr_hi_al_cap=0x40,laser_opt_pwr_lo_al_cap=0x80,laser_opt_pwr_hi_war_cap=0x100,laser_opt_pwr_lo_war_cap=0x200,laser_temp_hi_al=0x400,laser_temp_lo_al=0x800,laser_temp_hi_war=0x1000,laser_temp_lo_war=0x2000,global_alarm_for_laser2=0x4000,global_warning_for_laser2=0x8000,laser2_bias_hi_al_cap=0x10000,laser2_bias_lo_al_cap=0x20000,laser2_bias_hi_war_cap=0x40000,laser2_bias_lo_war_cap=0x80000,laser2_opt_pwr_hi_al_cap=0x100000,laser2_opt_pwr_lo_al_cap=0x200000,laser2_opt_pwr_hi_war_cap=0x400000,laser2_opt_pwr_lo_war_cap=0x800000" offset="0x20.8" size="0x0.24" />
	<field name="optical_engine_flag_in_use" descr="Bitmask per flag type in Optical engine module.When bit is set, indicates that FW reads flag from module.In order to get reliable latched flag information for that flag, it’s\;recommended to set event for module flags via trap.Bit 0: els_input_power_hi_alBit 1: els_input_power_lo_alBit 2: els_input_power_hi_warBit 3: els_input_power_lo_warBit 4: lane_temp_hi_alBit 5: lane_temp_lo_alBit 6: lane_temp_hi_warBit 7: lane_temp_lo_war" access="RO" enum="els_input_power_hi_al=0x1,els_input_power_lo_al=0x2,els_input_power_hi_war=0x4,els_input_power_lo_war=0x8,lane_temp_hi_al=0x10,lane_temp_lo_al=0x20,lane_temp_hi_war=0x40,lane_temp_lo_war=0x80" offset="0x24.0" size="0x0.16" />
	<field name="laser2_temp_lo_war" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;ELS laser temperature low warning" access="RO" offset="0x24.16" size="0x0.1" />
	<field name="laser_temp_lo_war" descr="ELS laser temperature low warning" access="RO" offset="0x24.17" size="0x0.1" />
	<field name="laser2_temp_hi_war" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;ELS laser temperature high warning" access="RO" offset="0x24.18" size="0x0.1" />
	<field name="laser_temp_hi_war" descr="ELS laser temperature high warning" access="RO" offset="0x24.19" size="0x0.1" />
	<field name="laser2_temp_lo_al" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;ELS laser temperature low alarm" access="RO" offset="0x24.20" size="0x0.1" />
	<field name="laser_temp_lo_al" descr="ELS laser temperature low alarm" access="RO" offset="0x24.21" size="0x0.1" />
	<field name="laser2_temp_hi_al" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;ELS laser temperature high alarm" access="RO" offset="0x24.22" size="0x0.1" />
	<field name="laser_temp_hi_al" descr="ELS laser temperature high alarm" access="RO" offset="0x24.23" size="0x0.1" />
	<field name="laser2_opt_pwr_lo_war" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;ELS laser optical power low warning" access="RO" offset="0x24.24" size="0x0.1" />
	<field name="laser_opt_pwr_lo_war" descr="ELS laser optical power low warning" access="RO" offset="0x24.25" size="0x0.1" />
	<field name="laser2_opt_pwr_hi_war" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;ELS laser optical power high warning" access="RO" offset="0x24.26" size="0x0.1" />
	<field name="laser_opt_pwr_hi_war" descr="ELS laser optical power high warning" access="RO" offset="0x24.27" size="0x0.1" />
	<field name="laser2_opt_pwr_lo_al" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;ELS laser optical power low alarm" access="RO" offset="0x24.28" size="0x0.1" />
	<field name="laser_opt_pwr_lo_al" descr="ELS laser optical power low alarm" access="RO" offset="0x24.29" size="0x0.1" />
	<field name="laser2_opt_pwr_hi_al" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;ELS laser optical power high alarm" access="RO" offset="0x24.30" size="0x0.1" />
	<field name="laser_opt_pwr_hi_al" descr="ELS laser optical power high alarm" access="RO" offset="0x24.31" size="0x0.1" />
	<field name="els_input_power_lo_war" descr="Bitmask for latched ELS input power low warning flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x28.0" size="0x0.8" />
	<field name="els_input_power_hi_war" descr="Bitmask for latched ELS input power high warning flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x28.8" size="0x0.8" />
	<field name="els_input_power_lo_al" descr="Bitmask for latched ELS input power low alarm flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x28.16" size="0x0.8" />
	<field name="els_input_power_hi_al" descr="Bitmask for latched ELS input power high alarm flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x28.24" size="0x0.8" />
	<field name="lane_temp_lo_war" descr="Bitmask for latched OE lane temperature low warning flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x2c.0" size="0x0.8" />
	<field name="lane_temp_hi_war" descr="Bitmask for latched OE lane temperature high warning flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x2c.8" size="0x0.8" />
	<field name="lane_temp_lo_al" descr="Bitmask for latched OE lane temperature low alarm flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x2c.16" size="0x0.8" />
	<field name="lane_temp_hi_al" descr="Bitmask for latched OE lane temperature high alarm flag per lane.Bit 0 - lane 0… Bit 7 - lane 7" access="RO" offset="0x2c.24" size="0x0.8" />
</node>

<node name="mofde_ext" descr="" size="0x4.0" >
	<field name="status" descr="Status of Flash Erasing:0: No data to erase1: Flash Storage is erased (after this status is returned, status will\;be changed to 0).2: Erase in progress.7: Fail to erase - Iron cannot access flash." access="RO" offset="0x0.0" size="0x0.3" />
	<field name="erase_log" descr="Erase Logged dump from flash.0: do nothing - shouldn’t happen, FW will return BAT_STATUS1: erase dump from flash" access="OP" offset="0x0.28" size="0x0.4" />
</node>

<node name="mord_v2_ext" descr="" size="0x34.0" >
	<field name="segment_type" descr="See Resource Dump section in the Adapters PRM." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="seq_num" descr="Sequence number. 0 on first call of dump and incremented on each more\;dump." access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="vhca_id_valid" descr="If set, then vhca_id field is valid. Otherwise dump resources on my\;vhca_id.Not supported in Switch." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="inline_dump" descr="If set, data is dumped in the register in inline_data field. otherwise\;dump to mkey.Supports only inline dump = 1" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="more_dump" descr="If set, the device has additional information that has not been dumped\;yet." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="vhca_id" descr="vhca_id where the resource is allocated.Not supported in Switch." access="WO" offset="0x4.0" size="0x0.16" />
	<field name="data_size" descr="Number of data records." access="OP" offset="0x4.16" size="0x0.13" />
	<field name="index1" descr="First object index to be dumped when supported by the object.SW shall read this field upon command done and shall provide it on the\;next call in case dump_more==1." access="INDEX" offset="0x8.0" size="0x4.0" />
	<field name="index2" descr="Second object index to be dumped when supported by the object.SW shall read this field upon command done and shall provide it on the\;next call in case dump_more==1." access="INDEX" offset="0xc.0" size="0x4.0" />
	<field name="num_of_obj2" descr="The amount of objects to dump starting for index 2.SW shall read this field upon command done and shall provide it on the\;next call in case dump_more==1.Range is 0..0xfff0. When the segment’s num_of_obj2_supports_all is set,\;the special value of 0xffff represents “all”. When the segment’s\;num_of_objx_supports_active is set, the special value of 0xfffe\;represents “active”. The value of 0x0 and 0x1 are allowed even if the\;supported_num_of_obj2 is “0”." access="INDEX" offset="0x10.0" size="0x0.16" />
	<field name="num_of_obj1" descr="The amount of objects to dump starting for index 1SW shall read this field upon command done and shall provide it on the\;next call in case dump_more==1.Range is 0..0xfff0. When the segment’s num_of_obj1_supports_all is set,\;the special value of 0xffff represents “all”. When the segment’s\;num_of_objx_supports_active is set, the special value of 0xfffe\;represents “active”. The value of 0x0 and 0x1 are allowed even if the\;supported_num_of_obj1 is “0”." access="INDEX" offset="0x10.16" size="0x0.16" />
	<field name="device_opaque" descr="An opaque provided by the device. SW shall read the device_opaque upon\;command done and shall provide it on the next call in case dump_more==1.\;On first call, device_opaque shall be 0." subnode="uint64" access="INDEX" offset="0x18.0" size="0x8.0" />
	<field name="mkey" descr="Memory key to dump to.Valid when inline_dump==0.Not supported in Switch." access="WO" offset="0x20.0" size="0x4.0" />
	<field name="size" descr="In write, the size of maximum allocated buffer that the device can use.In read, the actual written size.In granularity of Bytes.Not supported in Switch." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="address" descr="VA address (absolute address) of memory where to start dumping.Valid when inline_dump==0.Not supported in Switch." subnode="uint64" access="WO" offset="0x28.0" size="0x8.0" />
	<field name="inline_data" descr="Data that is dumped in case of inline mode.Valid when inline_dump==1." access="RO" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x30.0" size="0x4.0" size_condition="$(parent).data_size" />
</node>

<node name="mpcir_ext" descr="" size="0xa0.0" >
	<field name="instance" descr="Bitmask of which instance to select.Relevant only to vmod.0: update vmod 01: update vmod 1…" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="fw_entity" descr="Bitmask of which FW entity to select.0: switch_fw1: virtual_modulenote - if all bits are zero fw_entity will be switch_fw (legacy)If more than one bit is set instance field will be ignored - update\;all instances." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="all" descr="If set to ‘01’, activates the flow of preparation for FW ISSU, on all\;services. The values in op-codes for “per-service” are ignored.If set to ‘10’, returns to operational state on all services. The values\;in op-codes for “per-service” are ignored.11 - get_status for all services" access="OP" offset="0x0.30" size="0x0.2" />
	<field name="ports" descr="For each of the services, the following operations are available:0: N/A (no action)1: start preparation flow for FW ISSU2: return to operational service (end of FW ISSU flow)3: get statusWhen set to ‘3’, the current status will appear in corresponding _stat\;fields." access="OP" offset="0x4.0" size="0x0.2" />
	<field name="ports_stat" descr="Status for each of the services.0: not in FW ISSU flow state (FW ISSU flow is not initiated)1: done with preparations for FW ISSU flow2: Preparation for FW ISSU flow started but FW still not done service\;handling" access="RO" offset="0xc.0" size="0x0.2" />
</node>

<node name="mpscr_ext" descr="" size="0x20.0" >
	<field name="warning_inactive_time" descr="Thermal Throttling (FW mode) warning inactive timeEach unit is equivalent to 100uSecReserved for Switch." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="warning_active_time" descr="Thermal Throttling (FW mode) warning active timeEach unit is equivalent to 100uSecReserved for Switch." access="RW" offset="0x4.16" size="0x0.8" />
	<field name="critical_inactive_time" descr="Thermal Throttling (FW mode) critical inactive timeEach unit is equivalent to 100uSecReserved for Switch." access="RW" offset="0x8.0" size="0x0.8" />
	<field name="critical_active_time" descr="Thermal Throttling (FW mode) critical active timeEach unit is equivalent to 100uSecReserved for Switch." access="RW" offset="0x8.16" size="0x0.8" />
	<field name="l0_all_queues_are_import" descr="[DWIP]If set, L0 controller (HW) requires all queues to be empty before moving\;to L0 state. Global parameter in Switch project.Reserved for GPU." access="RW" offset="0xc.0" size="0x0.1" />
	<field name="tav_enable" descr="[SWITCH][RETIMER][DWIP]0: TAV disabled1: TAV enabledNote: This setting reverts to default after ASIC reset." access="RW" offset="0xc.31" size="0x0.1" />
	<field name="cc" descr="Clear Counters0: Don’t clear MTSR counters1: Clear MTSR countersReserved for Switch." access="OP" offset="0x10.0" size="0x0.1" />
</node>

<node name="mqdik_reg_ext" descr="" size="0x208.0" >
	<field name="algorithm" descr="0: ECC. Used for any of the P256, P385, P521 curves.1: RSA. Used for 2048 or 4096 keys." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="key_size" descr="Number of Bytes in the public_key" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="status" descr="0: Key is not ready for query1: Key is provided in the response" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="key_index" descr="Type of key used:0: public key of identity key1: serial number of identity keyAll other values reserved." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="public_key" descr="public-key value, per the specific algorithm.For key_index=0, it will be a public key.For key_index=1, it will be a serial number." access="RO" high_bound="127" low_bound="0" offset="0x8.0" size="0x200.0" />
</node>

<node name="mqis_reg_ext" descr="" size="0x18.0" >
	<field name="info_type" descr="Type of information string to be queried:0x0: VPD - Read the PCI Vital Product Data capability content.0x1: MODEL_NAME0x2: MODEL_DESCRIPTION0x3: IMAGE_VSD0x4: DEVICE_VSD0x5: ROM_INFO0x6: VMOD_VSDother values are reserved." access="INDEX" enum="MODEL_NAME=0x1,MODEL_DESCRIPTION=0x2,IMAGE_VSD=0x3,DEVICE_VSD=0x4,ROM_INFO=0x5,VMOD_VSD=0x6" offset="0x0.0" size="0x0.8" />
	<field name="info_length" descr="Total size of the information string, according to info_type. Value\;given in bytes." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="read_length" descr="Number of bytes requested. The device returns the number of bytes\;actually read." access="RW" offset="0x8.0" size="0x0.16" />
	<field name="read_offset" descr="Offset in bytes of the first byte requested to read." access="INDEX" offset="0x8.16" size="0x0.16" />
	<field name="info_string" descr="Information string accessed, according to info_type. If the information\;is not available, a NULL string is returned." access="RO" high_bound="7" low_bound="0" offset="0x10.24" size="0x8.0" />
</node>

<node name="mrpr_reg_ext" descr="" size="0x108.0" >
	<field name="type" descr="Runtime parameter to access or query" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="status" descr="0: Parameter is not supported1: Parameter is supported but is not ready for read2: Successful read3: Successful writeElse - Reserved" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="length" descr="Number of Bytes in the parameter data section.When reading an unsupported /unavailable parameter, this field is 0 and\;there is no data field in the read response." access="RW" offset="0x0.24" size="0x0.8" />
	<field name="data" descr="Parameter data.Writing to this field for read-only parameter has no effect.Reading this field for a write-only parameter returns unpredicted value." access="RW" high_bound="63" low_bound="0" offset="0x8.0" size="0x100.0" />
</node>

<node name="msci_ext" descr="" size="0xc.0" >
	<field name="index" descr="CPLD index" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="version" descr="CPLD version" access="RO" offset="0x4.0" size="0x4.0" />
</node>

<node name="msgcr_reg_ext" descr="" size="0x8.0" >
	<field name="support_perst_gpio" descr="[DWIP]:0: PERST GPIO assertion will NOT trigger ASIC reset1: PERST GPIO assertion will trigger ASIC reset" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="support_inter_asic_block" descr="[DWIP]:Support inter ASIC blocking0: Disable_Link GPIO assertion will NOT trigger Inter ASIC communication\;blocking1: Disable_Link GPIO assertion will trigger Inter ASIC communication\;blocking" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="support_error_injection" descr="[DWIP]:Support Error injection0: Deny any error injection operation (Thermal/Link/PCI)1: Allow error injection trigger" access="RO" offset="0x4.8" size="0x0.1" />
</node>

<node name="msgi_ext" descr="" size="0x80.0" >
	<field name="serial_number" descr="ASIC serial number (ASCII string)" access="RO" high_bound="5" low_bound="0" offset="0x0.0" size="0x18.0" />
	<field name="part_number" descr="ASIC part number (ASCII string)" access="RO" high_bound="4" low_bound="0" offset="0x20.0" size="0x14.0" />
	<field name="revision" descr="Revision (ASCII string)" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="product_name" descr="Product Name (ASCII string)" access="RO" high_bound="15" low_bound="0" offset="0x40.0" size="0x40.0" />
</node>

<node name="mslcg_ext" descr="" size="0x110.0" >
	<field name="cap_num_clock_gates" descr="Number of System Level Clock Gates" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="global" descr="Global config:0: Not Global1: Global When global=1 mode, then state[0] is used" access="INDEX" offset="0x4.0" size="0x0.1" />
	<field name="clock_gate_type" descr="System Level Clock Gating type:0: SLCG (Secondary Level Clock Gating)1: BLCG (Block Level Clock Gating)" access="INDEX" offset="0x4.8" size="0x0.2" />
	<field name="slcg_base" descr="Clock gating base indexUnits of 1024e.g. when clock_gate_type = 0 and slgc_base=1 then state[3] applies to\;SLCG [1024+3]Reserved when global = 1" access="INDEX" offset="0x8.0" size="0x0.8" />
	<field name="slcg_base_offset_start" descr="Clock gating base index offset starting location0: No offset from slgc_base1-1023: Offset from slgc_basee.g. when clock_gate_type = 0 and slgc_base=1 and\;slgc_base_offset_start=45 then\;state[3] applies to SLCG [1024+45+3]Reserved when global = 1" access="INDEX" offset="0x8.16" size="0x0.10" />
	<field name="state" descr="State per each Clock Gate (CG)0: CG disabled 1: CG enabled2: apply production setting (FW configuration according to production\;info). Note that this opcode (apply) is write only.Note: when reading only values 0 or 1 will be returned.States over cap_num_clock_gates are reserved (will return 0).3: Do nothing. Note that this opcode (apply) is write only.Note: when reading only values 0 or 1 will be returned.Reserved when global = 1" access="RW" high_bound="1023" low_bound="0" offset="0x10.30" size="0x100.0" />
</node>

<node name="mtbr_temp_record_ext" descr="" size="0x4.0" >
	<field name="temperature" descr="Temperature reading from the sensor. Units of 0.125 Celsius degrees.For virtual sensors, it is the highest or lowest temperature, as\;determined by MTBR.tmp_type.If no ambient sensor is present then the value is ‘0’. Also for a\;passive copper case.0x8000:NO_CONN- No cable or device’s sensor is connected.0x8001: NO_TEMP_SENS - In case a cable or device is connected but the\;temperature sensing is not supported.0x8002: INDX_NA- No such cable or device’s sensor index. Bigger than the\;number of modules.0x8003: INCORRECT_SENS_INFO - Sensor information is incorrect." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="max_temperature" descr="The highest measured temperature from the sensor.For virtual sensors, it is the highest or lowest temperature, as\;determined by MTBR.tmp_type.When the bit relevant MTMP.mte is cleared, the field max_temperature is\;reserved.The value will be ‘0’ for any of the ‘800X’ temperature values and for\;‘0’ value." access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="mtbr_v2_ext" descr="" size="0x90.0" >
	<field name="base_sensor_index" descr="Base sensor indexSensors are read starting from base_sensor_indexSensor 0 is the ASIC sensor, sensors 1-63 are ambient sensors and\;sensors 64-127 are mapped to the SFP+/QSFP modules sequentially (module\;0 is mapped to sensor 64, module 1 to sensor 65 and so on). Gearbox\;sensors starts from 256 index." access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="tmp_type" descr="Temperature Type0: Maximum1: Minimum" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="num_rec" descr="Number of records to readRange 1..32" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="temperature_record" descr="Temperature recordSee MTBR - Temperature Record Layout" subnode="mtbr_temp_record_ext" access="RO" high_bound="31" low_bound="0" offset="0x10.0" size="0x80.0" />
</node>

<node name="mtcap_ext" descr="" size="0x10.0" >
	<field name="sensor_count" descr="Number of ASIC+platform sensors supported by the deviceThis includes the ASIC and the ambient sensors. Module sensors are not\;included.This actually is equal to sum of all ‘1’ in sensor_mapRange 1..64Known sensors:0: current asic temp, FW exposes current max(all diode temp sensors)1..63: ambient, supported only for unmanaged switch, defined by ini64..127: modules (not exposed by this field)" access="RO" offset="0x0.0" size="0x0.7" />
	<field name="slot_index" descr="Slot index0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="internal_sensor_count" descr="Number of sensors supported by the device that are on the ASIC.Exposes how many ASIC diodes exist.The FW exposes all of them as sensor[0]" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Only ASIC and ambient\;sensors are supported. Each bit represents a sensor.Per bit:0: Not_connected_or_not_supported1: Supports_temperature_measurements" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="mtcq_reg_ext" descr="" size="0x70.0" >
	<field name="device_index" descr="Device number.For gearboxes, the index represents the gearbox die.For cables, the index represents the module index starting at index 1\;while index 0 indicates the host device." access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="status" descr="Indicates the status of the desired token we are generating the\;challenge for.0x0 - OK0x1 - TOKEN_ALREADY_APPLIED0x2 - TOKEN_NOT_SUPPORTED0x3 - NO_KEY_CONFIGURED (there is no public_key that can be used for\;this token)0x4 - INTERFACE_NOT_ALLOWED (asking for local token from remote\;interface, or remote token from local interface)0x5 - TOKEN_APPLY_TIMEOUT_EXPIRED" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="token_opcode" descr="The token which a challenge is generated for.0: RMCS - (ReMote Customer Support)1: RMDT - (ReMote Debug Token)2: CRCS - (Challenge-Response Customer Support) - supported from\;Spectrum-4 and above3: CRDT - (Challenge-Response Debug Token) - supported from Spectrum-4\;and above5: MTDT6: FRC - (Factory ReCustomization)7: MTFAOther: Reserved" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="keypair_uuid" descr="The UUID of the key used to generate the challenge." access="RO" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
	<field name="base_mac" descr="Device base MAC address / unique identifier." subnode="uint64" access="RO" offset="0x14.0" size="0x8.0" />
	<field name="psid" descr="Device PSID" access="RO" high_bound="3" low_bound="0" offset="0x1c.0" size="0x10.0" />
	<field name="fw_version_39_32" descr="Device FW version" access="RO" offset="0x2c.0" size="0x0.8" />
	<field name="fw_version_31_0" descr="(see above)" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="source_address" descr="Source address of debug requester. DLID for\;InfinibandValid only for RMCS/RMDT." access="RO" high_bound="3" low_bound="0" offset="0x34.0" size="0x10.0" />
	<field name="session_id" descr="Unique debug session identifier.See details in REMOTE_DEBUG_KEEP_ALIVE.Valid only for RMCS." access="RO" offset="0x44.0" size="0x0.16" />
	<field name="challenge_version" descr="Version of the challenge format." access="RO" offset="0x44.24" size="0x0.8" />
	<field name="challenge" descr="Random generated field. Used for randomness and replay-protection." access="RO" high_bound="7" low_bound="0" offset="0x48.0" size="0x20.0" />
	<field name="token_ratchet" descr="Current device’s token rachet value." subnode="uint64" access="RO" offset="0x68.0" size="0x8.0" />
</node>

<node name="mtdc_ext" descr="" size="0x20.0" >
	<field name="tracer_limit_en" descr="Tracer writing to PCI is limited.When this mode is enable, the hw tracer\;pointer cannot override the software read index pointer.If software will\;not update the read index pointer, new events will fall and will not be\;sent.0: NA - ignored, does not perform any operation1: Enable2: Disable" access="RW" offset="0x0.0" size="0x0.2" />
	<field name="tlb_addr_msb" descr="The lsb of the address for the cyclic buffer in the host memory." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="tlb_addr_lsb" descr="The lsb of the for the cyclic buffer address in the host memory." access="RW" offset="0xc.12" size="0x0.20" />
	<field name="hw_pointer" descr="Pointer of the current hw index the tracer is writing to." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="sw_pointer" descr="Pointer to the last tracer event index that the software consumed." access="RW" offset="0x14.0" size="0x4.0" />
</node>

<node name="mtdth_ext" descr="" size="0x18.0" >
</node>

<node name="mtecr_ext" descr="" size="0x60.0" >
	<field name="sensor_count" descr="Number of sensors supported by the ASIC+platformThis includes the ASIC, ambient sensors, module sensors, Gearboxes etc.This actually is equal to sum of all ‘1’ in sensor_mapKnown sensors:See MTMP.sensor_index description." access="RO" offset="0x0.0" size="0x0.12" />
	<field name="last_sensor" descr="Last sensor index that is available in the system to read from.e.g. when 32modules: 64+32-1 = 95" access="RO" offset="0x0.16" size="0x0.12" />
	<field name="internal_sensor_count" descr="Number of sensors supported by the device that are on the ASIC.Exposes how many ASIC diodes exist.The FW exposes all of them as sensor[0]" access="RO" offset="0x4.0" size="0x0.7" />
	<field name="slot_index" descr="Slot index0: Main board" access="INDEX" offset="0x4.28" size="0x0.4" />
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Each bit represents a\;sensor.This field is size variable based on the last_sensor field and in\;granularity of 32bits.Per bit:0: Not connected or not supported1: Supports temperature measurementsIn case of last_sensor = 704 (22*32):sensor_warning[0] bit31 is sensor_warning[703]sensor_warning[0] bit0 is sensor_warning[703-31]sensor_warning[21] bit31 is sensor_warning[31]sensor_warning[21] bit0 is sensor_warning[0]In case if last_sensor = 259 (22*32):Note: roundup(259,32)=288sensor_warning[0] bit31 is sensor_warning[287]sensor_warning[0] bit0 is sensor_warning[287-31=256]sensor_warning[8] bit31 is sensor_warning[31]sensor_warning[8] bit0 is sensor_warning[0]sensor_warning[9..21] are not used64-192 of sensor_index are mapped to the modules sequentially (module 0\;is mapped to sensor_index 64, module 1 to sensor_index 65 and so on)." access="RO" high_bound="21" low_bound="0" offset="0x8.0" size="0x58.0" />
</node>

<node name="mteim_reg_ext" descr="" size="0x30.0" >
	<field name="cap_core_tile" descr="Number of processors per tile ASIC." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="cap_core_main" descr="Number of processors in the main ASIC." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="cap_core_dpa" descr="Number of processors in the DPA unit." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="cap_num_of_tile" descr="Number of tiles per device. For devices without tiles (only main ASIC),\;this field should be ‘0’." access="RO" offset="0x0.24" size="0x0.8" />
	<field name="type_core_tile" descr="Processor type.0: N/A1: IRISC2: RISC5Else: Reserved" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="type_core_main" descr="Processor type.0: N/A1: IRISC2: RISC5Else: Reserved" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="type_core_dpa" descr="Processor type.0: N/A1: IRISC2: RISC5Else: Reserved" access="RO" offset="0x4.8" size="0x0.4" />
	<field name="is_phy_uc_supported" descr="Indicates wether Phy_UC tracers mapping are supported by the device FW.When set, The event_id of the Phy UC of the instance will be calculated\;by first_tile/main _core _event_id[i] + cap_core_tile/main.When clear the Phy UC will be ignored." access="RO" offset="0x4.30" size="0x0.1" />
	<field name="is_dwsn_msb_supported" descr="When set to ‘1’, the device supports dwsn_msb bit within the FW trace\;layout." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="first_dpa_core_event_id" descr="The mapping for the rest of the DPA ASIC processors are sequential and\;the mapping is defined as:processor[x]=first_dpacore_event_id+x" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="first_main_core_event_id" descr="The mapping for the rest of the main ASIC processors are sequential and\;the mapping is defined as:processor[x]=first_main_core_event_id+x" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="first_tile_core_event_id" descr="The mapping for the rest of the tile[y] ASIC processors are sequential\;and the mapping is defined as:processor[x]=first_tile_core_event_id[y]+x" access="RO" high_bound="7" low_bound="0" offset="0xc.24" size="0x8.0" />
</node>

<node name="mteir_reg_ext" descr="" size="0xc.0" >
	<field name="thermal_error_mode" descr="Error type Injected0: No thermal error injection1: Warning2: Critical3: Fatal4: Force the device into normal temperature rangeDefault is no thermal error injectionNote: Change to critical/fatal may cause the ASIC to reset." access="RW" offset="0x0.0" size="0x0.3" />
</node>

<node name="mtewe_ext" descr="" size="0x10c.0" >
	<field name="sensor_count" descr="Number of sensors supported by the deviceThis includes the ASIC, ambient sensors, Gearboxes etc.Known sensors:See MTMP.sensor_index description." access="RO" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="last_sensor" descr="Last sensor index that is available in the system to read from." access="RO" offset="0x0.16" size="0x0.12" />
	<field name="sensor_warning" descr="Bit vector indicating which of the sensor reading is above threshold.This field is size dependent and based on last_sensor field and in\;granularity of 32bits.In case of last_sensor = 704 (22*32):sensor_warning[0] bit31 is sensor_warning[703]sensor_warning[0] bit0 is sensor_warning[703-31]sensor_warning[21] bit31 is sensor_warning[31]sensor_warning[21] bit0 is sensor_warning[0]In case if last_sensor = 259 (22*32):Note: roundup(259,32)=288sensor_warning[0] bit31 is sensor_warning[287]sensor_warning[0] bit0 is sensor_warning[287-31=256]sensor_warning[8] bit31 is sensor_warning[31]sensor_warning[8] bit0 is sensor_warning[0]sensor_warning[9..21] are not used" access="RO" high_bound="21" low_bound="0" offset="0x4.0" size="0x58.0" />
</node>

<node name="mtie_ext" descr="" size="0x30.0" >
	<field name="enable_all" descr="Enable/Disable all FW tracer initiator and ignore mask.Starts from bit 0.0: Use bit mask1: Enable all2: Disable all" access="OP" offset="0x0.0" size="0x0.2" />
	<field name="log_delay" descr="Adding delay to log events in usecs" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="source_id_bitmask" descr="Bit mask of all the possible tracer initiators.Reserved when enable_all ≠ 0.The mapping of source id to HW unit is unique per device and can be\;fetched from FW code." access="RW" high_bound="7" low_bound="0" offset="0x10.0" size="0x20.0" />
</node>

<node name="mtim_ext" descr="" size="0x10.0" >
	<field name="log_level" descr="The verbosity of the log.0: LOG_DEBUG1: LOG_INFO2: LOG_WARNING3: LOG_ERRORThe lower value reflects higher verbosity than higher value.e.g: LOG_INFO contains LOG_WARNING and LOG_ERROR" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="log_bit_mask" descr="Bit mask of the different FW units that can be activated for the FW log.The mapping of source id to FW unit is unique per device and can be\;fetched from FW code." access="RW" offset="0x4.0" size="0x4.0" />
</node>

<node name="mtmp_ext" descr="" size="0x20.0" >
	<field name="sensor_index" descr="Sensors index (when i = 0, unless mentioned otherwise)0: Current ASIC temp - virtual sensor of entire ASIC. FW exposes the\;current max and min over all diode temp sensors.1..62: ambient, supported only for unmanaged switch, defined by ini64..255: modules 256..288: Gearbox[DWIP]: 289: For ig=0, mapped to same virtual sensor as of ig=1,\;sensor_index=0. This mapping allows support by the MTEWE/TMPW event\;mechanism.[DWIP]: 290..305: For ig=0, mapped to same virtual sensor as of ig=2,\;asic_index = sensor_index-289, sensor_index=0. This mapping allows\;support by the MTEWE/TMPW event mechanism." access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="asic_index" descr="ASIC index. See ig field for more details." access="INDEX" offset="0x0.25" size="0x0.4" />
	<field name="ig" descr="internal granularity.Used to query the internal diodes of the switch main ASIC and tiles.0: the ‘i’ field may be used to query the entire ASIC internal diodes.\;Main + tile.1: The ‘i’ field is ignored (considered as 0) and only the main ASIC\;diodes are available to query and sensor_index is the index of the main\;ASIC diodes. (The only valid value of sensor_index is 0).2: The ‘i’ field is ignored (considered as 0) and only the tile ASIC\;diodes are available to query and sensor_index is the index of the tile\;ASIC diodes. To query a specific tile, asic_index field should be used.\;(The only valid value of sensor_index is 0).3: Reserved." access="INDEX" offset="0x0.29" size="0x0.2" />
	<field name="i" descr="Used to query the internal diodes of the switch ASIC; for i=1,\;sensor_index is the index of the ASIC diode." access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="temperature" descr="Current temperature reading from the sensor. In case of a virtual\;sensor, this field reflects the maximum over all real sensors that it\;represents.Units of 0.125 Celsius degrees.For negative values 2’s complement is used (for example: -3.25 Celsius\;will read as 0xFFE6)" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_temperature" descr="The highest historic measured temperature from the sensor.Reserved when mte = 0Cleared by mtr = 1Valid only when i = 0For negative values 2’s complement is used (for example: -3.25 Celsius\;will read as 0xFFE6)" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="sdme" descr="Shut Down Events Modify Set Enable:0: all fields are set1: only sdee field is set, all other fields reserved.Note: It is invalid to set both weme and sdme in the same operation." access="OP" offset="0x8.28" size="0x0.1" />
	<field name="weme" descr="Warning Events Modify Set Enable:0: all fields are set1: only set tee. All other fields reserved.Note: It is invalid to set both weme and sdme in the same operation." access="OP" offset="0x8.29" size="0x0.1" />
	<field name="mtr" descr="Max Temperature Reset:0: do not modify the value of the max temperature register1: clear the value of the max temperature register" access="OP" offset="0x8.30" size="0x0.1" />
	<field name="mte" descr="Max Temperature Enable:0: disable measuring the max temperature on a sensor1: enables measuring the max temperature on a sensor" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="temperature_threshold_hi" descr="temperature_threshold_hi refers to the high threshold of Warning Event.\;Units of 0.125 Celsius degrees.For negative values 2’s complement is used (for example: -3.25 Celsius\;will read as 0xFFE6)If the sensor temperature measurement is above the threshold (and events\;are enabled), an event will be generated.threshold_hi and threshold_lo implements hysteresis mechanism of the\;threshold preventing toggling of the indication.Note that temperature_threshold_hi must be equal or lower than the\;system requirement. Where register MTDTH is supported, this value is\;specified in MTDTH.warning_high.System requirement for module is the module warning temperature.System requirement for board/silicon sensors is according to product\;information parametersNote that the temperature threshold can be used to generate an event\;message or an interrupt using GPIO" access="RW" offset="0xc.0" size="0x0.16" />
	<field name="sdee" descr="Temperature Shut Down Event Enable (MTSDE Register)0: do_not_generate_event1: generate_event2: generate_single_eventSupported in downstream devices (devices on slots)." access="RW" enum="do_not_generate_event=0x0,generate_event=0x1,generate_single_event=0x2" offset="0xc.28" size="0x0.2" />
	<field name="tee" descr="Temperature Warning Event Enable (MTEWE Register)0: do_not_generate_event1: generate_event2: generate_single_eventNote: Events may be delayed by up to 60 Seconds from “generate event” or “generate single event”Supported Only for switch and Retimer devices. For HCA devices, SW should register Temperature Warning Event to an EQ." access="RW" enum="do_not_generate_event=0x0,generate_event=0x1,generate_single_event=0x2" offset="0xc.30" size="0x0.2" />
	<field name="temperature_threshold_lo" descr="temperature_threshold_lo refers to the low threshold of Warning\;Event.Units of 0.125 Celsius degrees.For negative values 2’s complement is used (for example: -3.25 Celsius\;will read as 0xFFE6)The offset threshold_lo implements the lower threshold for the\;hysteresis mechanism of over temperature alert. Once alert is set, if\;the temperature goes below this threshold, the alert is cleared.Note that temperature_threshold_lo must be at least 5 degrees lower than\;temperature_threshold_hi" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="sensor_name_hi" descr="Sensor Name8 character long sensor name" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="sensor_name_lo" descr="(see above)" access="RO" offset="0x1c.0" size="0x4.0" />
</node>

<node name="mtpps_reg_ext" descr="" size="0x38.0" >
	<field name="cap_max_num_of_pps_out_pins" descr="Maximum number of pps out pins supported on device." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="cap_max_num_of_pps_in_pins" descr="Maximum number of pps in pins supported on device." access="RO" offset="0x0.8" size="0x0.4" />
	<field name="cap_number_of_pps_pins" descr="Total number of pps pins supported on device.The virtual pins are not counted here" access="RO" offset="0x0.16" size="0x0.4" />
	<field name="cap_pin_0_mode" descr="Bit0: support_pps_inBit1: support_pps_outBit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.0" size="0x0.4" />
	<field name="cap_pin_1_mode" descr="Bit0: support_pps_inBit1: support_pps_outBit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.8" size="0x0.4" />
	<field name="cap_pin_2_mode" descr="Bit0: support_pps_inBit1: support_pps_outBit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.16" size="0x0.4" />
	<field name="cap_pin_3_mode" descr="Bit0: support_pps_inBit1: support_pps_outBit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.24" size="0x0.4" />
	<field name="cap_pin_4_mode" descr="Bit0: support_pps_inBit1: support_pps_outBit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xc.0" size="0x0.4" />
	<field name="cap_pin_5_mode" descr="Bit0: support_pps_inBit1: support_pps_outBit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xc.8" size="0x0.4" />
	<field name="cap_pin_6_mode" descr="Bit0: support_pps_inBit1: support_pps_outBit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xc.16" size="0x0.4" />
	<field name="cap_pin_7_mode" descr="Bit0: support_pps_inBit1: support_pps_outBit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xc.24" size="0x0.4" />
	<field name="field_select" descr="Field select indicates which fields to modify in write operation to this\;register. This field selector supported only when MCAM.mtpps_fs==1. if\;MCAM.mtpps_fs==0 then SW should ensure that all the WO/RW fields are\;valid.Bit 0: enableBit 2: patternBit 3: pin_modeBit 4: time_stampBit 5: out_pulse_duration" access="WO" enum="enable=0x1,pattern=0x4,pin_mode=0x8,time_stamp=0x10,out_pulse_duration=0x20" offset="0x10.0" size="0x4.0" />
	<field name="pin" descr="Pin to be configured or queried out of the supported pins." access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="pin_mode" descr="Pin mode to be used. The mode must comply with the supported modes of\;the requested pin.0x0: pps_in0x1: pps_out0x2: virtual_pin0x3: pps_out_and_virtual_pinOperation will fail if pin does not support the required mode." access="RW" enum="pps_in=0x0,pps_out=0x1,virtual_pin=0x2,pps_out_and_virtual_pin=0x3" offset="0x20.8" size="0x0.4" />
	<field name="pattern" descr="When pin_mode = pps_in:0x0: Rising edge0x1: Falling edgeWhen pin_mode = pps_out:0x0: Pulse – (one shot) The device will generate a pulse at time_stamp\;time with a duration ofout_pulse_duration.0x1: Periodic – the device will generate periodical pulses with pulse\;duration of out_pulse_duration every   according to\;internal clock. The 1st pulse will be generated at time_stamp time.Reserved when pin_mode = 0x2 virtual_pin" access="RW" offset="0x20.16" size="0x0.4" />
	<field name="utc_mode" descr="UTC time:0x0: FREE_RUNNING - time_stamp is by free running clock0x1: UTC - time_stamp is UTC" access="RW" enum="FREE_RUNNING=0x0,UTC=0x1" offset="0x20.30" size="0x0.1" />
	<field name="enable" descr="Enables the PPS functionality the specific pin.0x0: Disable0x1: Enable" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x20.31" size="0x0.1" />
	<field name="time_stamp" descr="When pin_mode = pps_in, the latched device time when it was triggered\;from the external GPIO pin.When pin_mode = pps_out or virtual_pin or pps_out_and_virtual_pin, the\;target time to generate next output signal." subnode="uint64" access="RW" offset="0x28.0" size="0x8.0" />
	<field name="out_pulse_duration" descr="Output pulse duration in units of mSec.Range is 1 to 1000.Reserved when pin_mode ≠ ptp_outIn case the set value is 0, device default will be used." access="RW" offset="0x30.16" size="0x0.16" />
</node>

<node name="mtrc_cap_reg_ext" descr="" size="0x84.0" >
	<field name="num_string_db" descr="Number of different string sections building the database" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="trc_ver" descr="Indicates the version of the tracing mechanism.0x0: VER_00x1: VER_1Other values are reserved.Reserved in Switch" access="RO" offset="0x0.24" size="0x0.2" />
	<field name="trace_to_memory" descr="When set the device supports logging traces to memory0: FIFO Mode1: Host Memory Mode" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="trace_owner" descr="Write 0x1 to register for tracer ownership, write 0x0 to de-register.Read value 0x1 indicates tracer ownership is granted." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="num_string_trace" descr="The number of consecutive event_id that should be interpreted as a\;string trace" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="first_string_trace" descr="The lowest event_id that should be interpreted as a string trace" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="log_max_trace_buffer_size" descr="Log 2 of the maximal size of the trace buffer given in units of 4KB" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="tracer_capabilities" descr="Tracer suppported capbailities bitmask:0: FIFO.1: MEM mode.else, reserved." access="RO" offset="0x8.30" size="0x0.2" />
	<field name="string_db_param" descr="String DB section parameters." subnode="string_db_parameters_ext" access="RO" high_bound="7" low_bound="0" offset="0x10.0" size="0x40.0" />
</node>

<node name="mtrc_conf_reg_ext" descr="" size="0x80.0" >
	<field name="trace_mode" descr="Tracing mode0x0: FIFO0x1: TRACE_TO_MEMORYOther values are reserved." access="RW" offset="0x0.0" size="0x0.4" />
	<field name="log_trace_buffer_size" descr="Log 2 of the Size of the trace buffer, given in units of 4KB.Value should not exceed log_max_trace_buffer_size.Valid only for trace_mode TRACE_TO_MEMORY.Modifying this parameter after the tracer was active may cause loss of\;sync regarding the location of the next trace." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="trace_mkey" descr="MKey registered for the trace buffer access.Valid only for trace_mode TRACE_TO_MEMORY.Modifying this parameter after the tracer was active may cause loss of\;sync regarding the location of the next trace.Reserved for Switches." access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="mtrc_ctrl_reg_ext" descr="" size="0x40.0" >
	<field name="modify_field_select" descr="Field select indicated which writable fields to modifybit 0: trace_statusbit 1: slcg_cmdOther bits are reserved." access="WO" offset="0x0.0" size="0x0.16" />
	<field name="slcg_cmd" descr="SLCG Command:0: RETURN_TO_DEFAULT - return to default g_trc slcg configurations1: ENABLE - enable all g_trcsNote: By default, all g_trc are clock-gated except for selected ones (fw\;trc)." access="OP" offset="0x0.16" size="0x0.2" />
	<field name="arm_event" descr="When set, an event will be generated if new Tracer events were logged\;since last event.Reserved in Switches." access="WO" offset="0x0.27" size="0x0.1" />
	<field name="trace_status" descr="Current status of the tracer0x0: DISABLED - logging traces is stopped0x1: ACTIVE - logging traces is active" access="RW" offset="0x0.30" size="0x0.2" />
	<field name="current_timestamp_52_32" descr="MSB of the current timesatmp counter" access="RO" offset="0x8.0" size="0x0.21" />
	<field name="current_timestamp_31_0" descr="LSB of the current timesatmp counter" access="RO" offset="0xc.0" size="0x4.0" />
</node>

<node name="mtrc_stdb_reg_ext" descr="" size="0xc.0" >
	<field name="read_size" descr="The number of bytes to read from the String DB. The number of bytes\;must:Be a multiple of 64BNot exceed the String DB section (with start_offset)Not exceed the limitations defined by the medium carrying the\;Register." access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="string_db_index" descr="The section of the String DB being accessed" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="start_offset" descr="The offset in the String DB to read from, given in Bytes. The offset\;must:Be a multiple of 64BNot exceed the String DB section (with read_size)" access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="string_db_data" descr=":AdbCondition:``\;Strings from the database. The size of this field is defined by\;read_size" access="RO" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x8.0" size="0x4.0" size_condition="$(parent).read_size" />
</node>

<node name="mtutc_reg_ext" descr="" size="0x1c.0" >
	<field name="operation" descr="Operation:1: SET_TIME_IMMEDIATE2: ADJUST_TIME3: ADJUST_FREQ_UTC 4: ADJUST_FREQ_FRC - Free Running Clock (dwip and Switch only)5: ADJUST_FREQ_BOTH - (dwip and Switch only)6: ADJUST_PHASE - Supported only if MCAM.mng_feature_cap_mask bit 54\;is set." access="OP" enum="SET_TIME_IMMEDIATE=0x1,ADJUST_TIME=0x2,ADJUST_FREQ_UTC=0x3,ADJUST_FREQ_FRC=0x4,ADJUST_FREQ_BOTH=0x5,ADJUST_PHASE=0x6" offset="0x0.0" size="0x0.4" />
	<field name="log_max_phase_adjustment" descr="[DWIP]range is from -(2^ log_max_phase_adjustment) to +2^\;log_max_phase_adjustment) in units of ns." access="RO" offset="0x0.5" size="0x0.6" />
	<field name="log_max_freq_adjustment" descr="If 0: Range is from -50,000,000 ppb to +50,000,000 ppb.Otherwise: range is from -(2^log_max_freq_adjustment) ppb to\;+2^log_max_freq_adjustment ppb." access="RO" offset="0x0.16" size="0x0.5" />
	<field name="freq_adj_units" descr="Updated when operation is ADJUST_FREQ.0: units_are_ppb - every PPS the HW frequency will be adjusted by\;this value1: units_are_parts_per_million - but with a 16 bit binary fractional\;field2: units_are_parts_per_billion - but with a 16 bit binary fractional\;field" access="RW" enum="units_are_ppb=0x0,units_are_parts_per_million=0x1,units_are_parts_per_billion=0x2" offset="0x0.24" size="0x0.3" />
	<field name="freq_adjustment" descr="Units are per MTUTC.freq_adj_units value.Frequency adjustment: Every PPS the HW frequency will be adjusted by\;this value.\;field.Updated when operation is ADJUST_FREQRange is from -50,000,000 ppb to +50,000,000 ppb" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="utc_sec" descr="UTC seconds\;Updated when operation is SET_TIME_IMMEDIATE" access="WO" offset="0x10.0" size="0x4.0" />
	<field name="utc_nsec" descr="UTC nSecs\;Range 0..(10^9-1)\;Updated when operation is SET_TIME_IMMEDIATE" access="WO" offset="0x14.0" size="0x0.30" />
	<field name="time_adjustment" descr="Time or phase adjustment\;Updated when operation is ADJUST_TIME or ADJUST_PHASE.\;When ADJUST_TIME:\;Time adjustment, Units of nSec, Range is from -32768 to 32768.\;If MCAM.time_adjust_range_extended==1, range is from\;When ADJUST_PHASE:\;Phase adjustment, Units of nSec, Range is according to log_max_phase_adjustment field." access="WO" offset="0x18.0" size="0x4.0" />
</node>

<node name="mtwe_ext" descr="" size="0x10.0" >
	<field name="sensor_warning" descr="Bit vector indicating which of the sensor reading is above threshold.Address 00h bit31 is sensor_warning[127]Address 0Ch bit0 is sensor_warning[0]" access="RO" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
</node>

<node name="mvcap_reg_ext" descr="" size="0x10.0" >
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Each bit represents a\;sensor.Sensor mapping is based on the sensor_map_type0: Not connected or not supported1: Supports voltage and current measurements" subnode="uint64" access="RO" offset="0x0.0" size="0x8.0" />
	<field name="slot_index" descr="Slot index0: Main board" access="INDEX" offset="0x8.0" size="0x0.4" />
	<field name="sensor_map_type" descr="[DWIP]0: Sensors 0-63.1: Sensors 64-127.2: Sensors 128-191." access="INDEX" offset="0x8.28" size="0x0.2" />
</node>

<node name="mvcr_ext" descr="" size="0x18.0" >
	<field name="sensor_index" descr="Sensors:- 0..max_system_sensors-1 are ambient sensors on the system\;(max_system_sensors from INI)" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="curr_cap" descr="0: Sensor does not support current reading1: Sensor supports current reading" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="volt_cap" descr="0: Sensor does not support voltage reading1: Sensor supports voltage reading" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="i" descr="Used to query internal A2D voltage measurements." access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="voltage_sensor_value" descr="Voltage reading from the sensor.Voltage units are 0.01V." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="current_sensor_value" descr="Current reading from the sensor lsb.Current units are\;0.01A." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="current_sensor_value_msb" descr="Current reading from the sensor msb.Current units are\;0.01A." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="sensor_name" descr="Sensor Name8 character long sensor name." subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="paos_reg_ext" descr="" attr_required_tlvs="index:s" size="0x10.0" >
	<field name="oper_status" descr="Port operational state:1: up2: down4: down_by_port_failure - (transitioned by the hardware)" access="RO" enum="up=0x1,down=0x2,down_by_port_failure=0x4" offset="0x0.0" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="admin_status" descr="Port administrative state (the desired state of the interface):1: up2: down_by_configuration4: disabled_by_system - this mode cannot be set by the software, only\;by the hardware.6: sleep - can be configured only if sleep_cap is set. Note that a\;sleep setting will cause the port to transition immediately into\;sleep state regardless of previous admin_status." access="RW" enum="up=0x1,down_by_configuration=0x2,disabled_by_system=0x4,sleep=0x6" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.Switch partition ID with which to associate the port.Switch partitions are numbered from 0 to 7 inclusively.The swid field is only valid when the local_port is the router port. In\;this case, the swid indicates which of the router ports to\;configure/query." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="e" descr="Event generation on operational state change (oper_status):0: Do_not_generate_event1: Generate_Event2: Generate_Single_EventNot Supported for HCA." access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="physical_state_status" descr="IB Port Physical operational (actual) link state:0: N/A1: Sleep2: Polling3: Disabled4: PortConfigurationTraining5: LinkUp6: LinkErrorRecoveryAll others reservedNote that physical state of 1,2,3,4 will all be reflected as\;oper_status = down." access="RO" enum="N_A=0x0,Sleep=0x1,Polling=0x2,Disabled=0x3,PortConfigurationTraining=0x4,LinkUp=0x5,LinkErrorRecovery=0x6" offset="0x4.4" size="0x0.4" />
	<field name="fd" descr="Force down.Supported only when indicated in PCAMCan be set only with admin_status = 2 (‘down_by_configuration’), will\;force link to be down." access="RW" offset="0x4.8" size="0x0.1" />
	<field name="sleep_cap" descr="Sleep capability:0: Sleep state is not supported1: Sleep state supported" access="RO" offset="0x4.9" size="0x0.1" />
	<field name="ps_e" descr="Event generation for physical state.On set operation, will be ignored if ee_ps is not set.When bit is set, will generate an event for transition into state.Bit 0: SleepBit 2: DisabledBit 3: PortConfigurationTrainingNot Supported for HCA." access="RW" enum="Sleep=0x1,Disabled=0x4,PortConfigurationTraining=0x8" offset="0x4.12" size="0x0.4" />
	<field name="logical_state_status" descr="IB or NVLink Port Logical link state:0: N/A1: Down2: Init3: Arm4: Active" access="RO" enum="N_A=0x0,Down=0x1,Init=0x2,Arm=0x3,Active=0x4" offset="0x4.16" size="0x0.3" />
	<field name="ls_e" descr="event generation mask for logical state.On set operation, will be ignored when ee_ls is not set.When bit is set, will generate event for transition into state.Bit 0: DownBit 1: InitBit 2: ArmBit 3: ActiveNot Supported for HCA." access="RW" enum="Down=0x1,Init=0x2,Arm=0x4,Active=0x8" offset="0x4.20" size="0x0.4" />
	<field name="ee_nmxas" descr="Event update enable for NMX AdminState. If this bit is set, event\;generation will be updated based on the nmxas_e field. Only relevant on\;Set operations.Not Supported for HCA." access="WO" offset="0x4.27" size="0x0.1" />
	<field name="ee_ps" descr="Event update enable for physical state. If this bit is set, event\;generation will be updated based on the ps_e field. Only relevant on Set\;operations.Not Supported for HCA." access="WO" offset="0x4.28" size="0x0.1" />
	<field name="ee_ls" descr="Event update enable for logical state. If this bit is set, event\;generation will be updated based on the ls_e field. Only relevant on Set\;operations.Not Supported for HCA." access="WO" offset="0x4.29" size="0x0.1" />
	<field name="ee" descr="Event update enable. If this bit is set, event generation will be\;updated based on the e field. Only relevant on Set operations.Not Supported for HCA." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="ase" descr="Admin state update enable. If this bit is set, admin state will be\;updated based on admin_state field. Only relevant on Set() operations." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="nmx_adminstate_status" descr="NVLink Port NMX AdminState current state:0: N/A1: Up2: Down3: Diag" access="RO" enum="N_A=0x0,Up=0x1,Down=0x2,Diag=0x3" offset="0x8.0" size="0x0.3" />
	<field name="nmxas_e" descr="Event generation mask for NMX AdminState status.On set operation, will be ignored when ee_nmxas is not set.When bit is set, will generate event for transition into state.Bit 0: UpBit 1: DownBit 2: Diag" access="RW" enum="Up=0x1,Down=0x2,Diag=0x4" offset="0x8.4" size="0x0.4" />
	<field name="ps_e_ext" descr="Extension of ps_e field. Event generation for physical state.On set operation, will be ignored if ee_ps is not set.When bit is set, will generate an event for transition into state.Bit 0: PollingBit 1: Reserved" access="RW" enum="Polling=0x1,Reserved=0x2" offset="0x8.12" size="0x0.2" />
	<field name="last_oper_status" descr="Supported if PCAM.feature_cap_mask bit 118 is setLast reported oper state in PUDE:0: no_info1: up2: down4: down_by_port_failure - (transitioned by the hardware)" access="RO" enum="up=0x1,down=0x2,down_by_port_failure=0x4" offset="0x8.16" size="0x0.3" />
	<field name="phy_force_linkup_mode" descr="Indicates physical link entered forced linkup debug mode" access="RO" offset="0x8.31" size="0x0.1" />
</node>

<node name="pbmc_reg_ext" descr="" size="0x6c.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="xoff_refresh" descr="The time before a new pause frame should be sent to refresh the pause\;state. Using the same units as xoff_timer_value above.See PFCC.pfc_rx_timer_value for RX side.Fixed in\;Spectrum-6." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="xoff_timer_value" descr="When device generates a pause frame, it uses this value as the pause\;timer.The pause timer is measured in units of pause “quanta”, where each unit\;is equal to 512 bit times." access="RW" offset="0x4.16" size="0x0.16" />
	<field name="port_buffer_size" descr="Total packet buffer array available for the port. The sum of buffer\;array allocated to bufferX must not exceed port_buffer_size.In Spectrum and above- Max supported Headroom buffer for port." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="fullness_threshold" descr="Almost full threshold configuration.Percentage of buffer fullness which indicates “almost full” occurrenceRange: 0-100%Reserved for Switches." access="RW" offset="0x8.16" size="0x0.7" />
	<field name="buffer" descr="Configuring per-buffer parameters. i=0..9.See BufferX Register Layout" subnode="bufferx_reg_ext" access="RW" high_bound="9" low_bound="0" offset="0xc.0" size="0x50.0" />
	<field name="shared_headroom_pool" descr="Configuring shared headroom pool parameters. Using the same layout as in\;BufferX.Not supported in HCA (See PCAM shp_pbmc_pbsr_support bit).See BufferX Register Layout" subnode="bufferx_reg_ext" access="RW" offset="0x5c.0" size="0x8.0" />
	<field name="port_shared_buffer" descr="Configuring port shared buffer parameters. Using the same layout as in\;BufferX.Valid for HCA when pbmc_port_shared_buffer is set in PCAM.See BufferX Register Layout" subnode="bufferx_reg_ext" access="RW" offset="0x64.0" size="0x8.0" />
</node>

<node name="pbsr_reg_ext" descr="" attr_required_tlvs="index:s" size="0x64.0" >
	<field name="buffer_type" descr="Valid only for 8x port setting (see\;PMLP - Ports Module to Local Port Register Fields)0: One buffer - reserved index for non-8x ports1: Main buffer2: Secondary buffer" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clear_wm_buff_mask" descr="Each bit represents a stat_bufferper bit:0: do not clear watermark1: clear watermarkReserved when clear_wm = 1" access="OP" offset="0x4.0" size="0x0.10" />
	<field name="used_shared_headroom_buffer" descr="Number of currently used shared headroom buffer cells." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="clear_wm" descr="Clear watermarks for all PGs" access="OP" offset="0x8.31" size="0x0.1" />
	<field name="stat_buffer" descr="status per-buffer parameters. i=0..9" subnode="stat_bufferx_reg_ext" access="RO" high_bound="9" low_bound="0" offset="0xc.0" size="0x50.0" />
	<field name="stat_shared_headroom_pool" descr="status of shared headroom pool parameters. Using the same layout as in\;stat_BufferX, for details see\;stat_bufferX Register Layout.Not supported in HCA (See PCAM shp_pbmc_pbsr_support bit).Not supported in GPUNet" subnode="stat_bufferx_reg_ext" access="RO" offset="0x5c.0" size="0x8.0" />
</node>

<node name="pbwc_ext" descr="" size="0x8.0" >
	<field name="log_time_interval" descr="Log time interval.This field determine the time between measurements T:T = (2^log_time_interval) * 64uSecDefault is 7, means that T = (2^7) * 64uSec = 8mSec.For SPC4, and SPC5, the range is dependent on the port’s rate:800Gbps: 0..10400Gbps: 0..10200Gbps: 0..11100Gbps: 0..1250Gbps: 0..1325Gbps: 0..1410Gbps: 0..15" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="alpha_factor" descr="Alpha for the exponential moving average formula.Alpha = 1/(2^alpha_factor)Range 0..7Default is 2" access="RW" offset="0x4.0" size="0x0.3" />
</node>

<node name="pbwr_ext" descr="" attr_required_tlvs="index:m" size="0x94.0" >
	<field name="local_port_bitmap" descr="Local portEach bit represents a local port.[DWIP] Bit &lt;i&gt; represents local port &lt;base_port+i&gt;.Ports order in the bitmask is from bottom to top.E.g, given\;base_port=0, for setting local port 1, bit 1\;in the last DWORD (offset 0x7Ch) should be set.CPU port is not supported.Router port is not supported.For GPU: above 36 ports set, there is not enough space to provide the\;bw_records; hence the query should be split into 36 ports masks. In\;case more than 36 ports were set, the operation will not be fulfilled\;and an error status will be returned." access="INDEX" high_bound="31" low_bound="0" offset="0x0.0" size="0x80.0" />
	<field name="dir" descr="Direction:0: ingress1: egress" access="INDEX" enum="ingress=0x0,egress=0x1" offset="0x80.31" size="0x0.1" />
	<field name="base_port" descr="[DWIP]Base local port for the local port bitmap.local_port_bitmap represents local ports from base_port to\;base_port+1023.bw_record[0] corresponds to base_port." access="INDEX" offset="0x84.0" size="0x0.16" />
	<field name="bw_record" descr="BW of the corresponding local port.Valid only if the corresponding bit at local_port_bitmap is set (1).[DWIP] bw_record[i] corresponds to bit i in local_port_bitmap, which\;corresponds to local port base_port+i.The units of the BW are determined by\;PBWC - Port BW Configuration Register Layout." access="RO" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x90.0" size="0x4.0" size_condition="$(parent).num_rec" />
</node>

<node name="pcam_feature_capability_mask_group0_ext" descr="" size="0x10.0" >
	<field name="feature_cap_mask" descr="Supported port’s enhanced features. Based on feature_group index. When\;bit is set, The feature is supported in the device:Bit 0: PPCNT_counter_group_Phy_statistical_counter_groupBit 1 - PPCNT_counter_group_Discard_counter_groupBit 9: PFCC - support of stall mask and global rx,tx mask.Bit 10: PMCR - support of tx_disable override.Bit 11: PPCNT_counter_group - IB Extended port counter groupBit 12: PPCNT_Extended_Ethernet_group - tx packet size histogramsBit 13: PTYS_extended_Ethernet_supportBit 14: PMAOS_reset_toggle_supportBit 15: Set_Module_low_power_supportedBit 16: Module_power_optimization_is_supported_in_PPSCBit 17: Support_of_IB_force_state_machine_in_PTYS - (an_disable)Bit 18: PPCNT_Extended_Ethernet_group_icrc_counterBit 19: cm2_en_is_supported_in_PCAPBit 20: time_tolink_up_is_supported_in_PDDRBit 21: gearbox_die_num_field_is_supported_in_PMDRBit 22: force_entropy_entropy_calc_entropy_gre_calc - and capability\;bits are supported in PCMRBit 23: FEC_override_support_for_50G_per_lane_is_supported_in_PPLMBit 25: PTYS_allow_both_extended_and_legacy_protocol_masksBit 26: PPCNT_eth_per_tc_cong_group_supportedBit 27: pnat_sup_host - the device supports pnat = 2 (host) when set\;to ‘1’Bit 28: ppcnt_no_buffer_discard_uc - this counter is supported in\;PPCNT when set to ‘1’Bit 29: pbmc_port_shared_buffer - supported in PBMC.Bit 30: PLR_max_retry_window_support - PPCNT group 0x22 max retry per\;windowBit 32: PDDR_ext_eth_proto_supportBit 41: PMAOS - support of “opertional_notifcation” fieldBit 42: PRBS_polarity_support - support of polarity bits in PPTT and\;PPRTBit 43: PDDR_register_is_supportedBit 44: pfcc_buffer_onwership - PFCC buffer ownership is supported.Bit 45: force_down - supported in PAOS reg.Bit 46: pmlp_lane_mapping_off - Support of m_lane_m field in PMLP.Bit 51: ppcnt_symobl_berBit 52: shp_pbmc_pbsr_supportBit 54: ppcnt_effective_error_counterBit 55: FEC_override_support_for_100G_per_lane_is_supported_in_PPLMBit 57: PMECR_option_to_not_generate_events_upon_PMLP_setBit 64: Local_port_MSB - bits [9:8] supportedBit 65: PDDR_moule_latched_info_page_supportedBit 66: PDDR_module_info_ext_supportedBit 70: SLTP_tx_policy_supportedBit 71: pmcr_capability_bits_supportedBit 72: pmtu_max_admin_mtu_supportedBit 73: PPCNT_grp_profile_supportedBit 77: PPCNT.physical_layer_counters_RS_FEC_8_lanes_supportedBit 85: PPCNT.counters_capBit 86: SLTP.lane_broadcast_supportedBit 87: PMMP.apply_im_supportedBit 91: SLRG.all_lanes_supportedBit 92: PIPG.ipg_oper_ipg_cap_idx_supportedBit 93: PPBMP_clr_supportedBit 94: PIPG.dic1_1g_supportedBit 98: FEC_override_support_for_200G_per_lane_is_supported_in_PPLMBit 99: PUDE.local_reason_opcode_supportedBit 101: PPCNT.physical_layer_counters.intentional_unintentional_link_down_events_supportedBit 102: PAOS.nmx_adminstate_status_fields_supportedBit 103: PFCC.cable_length_supportedBit 104: PDDR.link_up_info_page_1ch_to_2ch_counters_supportedBit 107: PFCC.packet_ratio_supportedBit 111: PPCNT.physical_layer_recovery_counters_supportedBit 112: PMLP.lane_label_mapping_supportedBit 113: PPCNT.physical_layer_counters.estimated_effective_ber_supportedBit 114 PPCNT.physical_layer_counters.ucr_ber_supportedBit 116: PMLP.mode_b_map_bit_supportedBit 117: PDDR.link_down_info_page.recovery_entry_reason_supportedBit 118: PAOS.last_oper_state_supportedBit 119: PPCNT.new_phy_recovery_counters_supportedBit 120: PDDR.operational_info_page.test_mode_fsm_state_supportedBit 121: PFCC.mlb_mask_supportedBit 122: PUDE.recoverable_down_supportedBit 123: PDDR.AMLock_aggregated_VLs_SupportedBit 124: PPCNT.physical_layer_recovery.successful_recovery_time_supportedBit 125: PPCNT.physical_layer_recovery.uncorrectable_during_recovery_supportedBit 126: SLRG.measurements_thresholds_supportedOther bits are reserved" access="RO" enum="PPCNT_counter_group_Phy_statistical_counter_group=0x1,PFCC=0x200,PMCR=0x400,PPCNT_counter_group=0x800,PPCNT_Extended_Ethernet_group=0x1000,PTYS_extended_Ethernet_support=0x2000,PMAOS_reset_toggle_support=0x4000,Set_Module_low_power_supported=0x8000,Module_power_optimization_is_supported_in_PPSC=0x10000,Support_of_IB_force_state_machine_in_PTYS=0x20000,PPCNT_Extended_Ethernet_group_icrc_counter=0x40000,cm2_en_is_supported_in_PCAP=0x80000,time_tolink_up_is_supported_in_PDDR=0x100000,gearbox_die_num_field_is_supported_in_PMDR=0x200000,force_entropy_entropy_calc_entropy_gre_calc=0x400000,FEC_override_support_for_50G_per_lane_is_supported_in_PPLM=0x800000,PTYS_allow_both_extended_and_legacy_protocol_masks=0x2000000,PPCNT_eth_per_tc_cong_group_supported=0x4000000,pnat_sup_host=0x8000000,ppcnt_no_buffer_discard_uc=0x10000000,pbmc_port_shared_buffer=0x20000000,PLR_max_retry_window_support=0x40000000,PDDR_ext_eth_proto_support=0x1,PMAOS=0x200,PRBS_polarity_support=0x400,PDDR_register_is_supported=0x800,pfcc_buffer_onwership=0x1000,force_down=0x2000,pmlp_lane_mapping_off=0x4000,ppcnt_symobl_ber=0x80000,shp_pbmc_pbsr_support=0x100000,ppcnt_effective_error_counter=0x400000,FEC_override_support_for_100G_per_lane_is_supported_in_PPLM=0x800000,PMECR_option_to_not_generate_events_upon_PMLP_set=0x2000000,Local_port_MSB=0x1,PDDR_moule_latched_info_page_supported=0x2,PDDR_module_info_ext_supported=0x4,SLTP_tx_policy_supported=0x40,pmcr_capability_bits_supported=0x80,pmtu_max_admin_mtu_supported=0x100,PPCNT_grp_profile_supported=0x200,PPCNT_physical_layer_counters_RS_FEC_8_lanes_supported=0x2000,PPCNT_counters_cap=0x200000,SLTP_lane_broadcast_supported=0x400000,PMMP_apply_im_supported=0x800000,SLRG_all_lanes_supported=0x8000000,PIPG_ipg_oper_ipg_cap_idx_supported=0x10000000,PPBMP_clr_supported=0x20000000,PIPG_dic1_1g_supported=0x40000000,FEC_override_support_for_200G_per_lane_is_supported_in_PPLM=0x4,PUDE_local_reason_opcode_supported=0x8,PPCNT_physical_layer_counters_intentional_unintentional_link_down_events_supported=0x20,PAOS_nmx_adminstate_status_fields_supported=0x40,PFCC_cable_length_supported=0x80,PDDR_link_up_info_page_1ch_to_2ch_counters_supported=0x100,PFCC_packet_ratio_supported=0x800,PPCNT_physical_layer_recovery_counters_supported=0x8000,PMLP_lane_label_mapping_supported=0x10000,PPCNT_physical_layer_counters_estimated_effective_ber_supported=0x20000,PMLP_mode_b_map_bit_supported=0x100000,PDDR_link_down_info_page_recovery_entry_reason_supported=0x200000,PAOS_last_oper_state_supported=0x400000,PPCNT_new_phy_recovery_counters_supported=0x800000,PDDR_operational_info_page_test_mode_fsm_state_supported=0x1000000,PFCC_mlb_mask_supported=0x2000000,PUDE_recoverable_down_supported=0x4000000,PDDR_AMLock_aggregated_VLs_Supported=0x8000000,PPCNT_physical_layer_recovery_successful_recovery_time_supported=0x10000000,PPCNT_physical_layer_recovery_uncorrectable_during_recovery_supported=0x20000000,SLRG_measurements_thresholds_supported=0x40000000" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
</node>

<node name="pcam_feature_capability_mask_group1_ext" descr="" size="0x10.0" >
	<field name="feature_cap_mask" descr="Bit 5: PPRM.link_down_timeout_default_supportedBit 6: PMDR.active_module_lane_mask_supportedBit 7: PPBMC.plr_bw_loss_negotation_supportedBit 8: PPCNT.port_up_time_supportedBit 9: PPCNT.IB_Routing_counters_supportedBit 10: PPLM.plr_to_default_read_supportBit 11: Uneven_port_split_is_supported (Note: even port split is\;mandatory within a 4x)Bit 12: PPCNT.recovery_counters_group_new_steps_counters_supportedBit 13: PPCNT.excessive_recoveries_counters_supportedBit 14: GMGDT,supportedBit 17: PPRM.phy_mode_idx_supportedBit 19: PPCNT.plr_rx_block_cs_on_demand_activated_supportedBit 20: SLTPv2.tx_policy_supportedBit 21: PPCNT.plr_nack_csn_counters_supported" access="RO" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
</node>

<node name="pcam_reg_ext" descr="" size="0x50.0" >
	<field name="access_reg_group" descr="Access Register ID groups0: RegID_0x5000_to_0x507F1: RegID_0x5080_to_50FFValues 2-255 are Reserved" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="pl_op" descr="Reserved for non-planarized port.Features and access regs will be presented according to:0: aggregated_port_access1: plane_port_access" access="OP" enum="aggregated_port_access=0x0,plane_port_access=0x1" offset="0x0.8" size="0x0.1" />
	<field name="feature_group" descr="Feature list mask index:0: enhanced_features1: ext_group1_featuresValues 1 - 255 are Reserved" access="INDEX" enum="enhanced_features=0x0,ext_group1_features=0x1" offset="0x0.16" size="0x0.8" />
	<field name="port_access_reg_cap_mask" descr="Supported port’s access register bitmaks. Based on access_reg_group\;index.When bit is set. The register is supported in the device.When access_reg_group == 0 :Bit_0: 0x5000Bit_1: 0x5001 (PCAP)Bit_2: 0x5002 (PMLP)Bit_3: 0x5003 (PMTU)Bit_4: 0x5004 (PTYS)Bit_127: 0x507F (PCAM)" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="feature_cap_mask" descr="PCAM - Feature Capability Mask Group0 LayoutPCAM - Feature Capability Mask Group1 Layout" subnode="pcam_reg_feature_cap_mask_auto_ext" access="RO" offset="0x28.0" size="0x10.0" union_selector="$(parent).feature_group" />
</node>

<node name="pcam_reg_feature_cap_mask_auto_ext" descr="" attr_is_union="1" size="0x10.0" >
	<field name="pcam_feature_capability_mask_group0_ext" descr="" subnode="pcam_feature_capability_mask_group0_ext" access="RW" offset="0x0.0" selected_by="enhanced_features" size="0x10.0" />
	<field name="pcam_feature_capability_mask_group1_ext" descr="" subnode="pcam_feature_capability_mask_group1_ext" access="RW" offset="0x0.0" selected_by="ext_group1_features" size="0x10.0" />
</node>

<node name="pcap_reg_ext" descr="" attr_required_tlvs="index:s" size="0x14.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cm2_en" descr="port_capability_mask[95:80] is supported if set to ‘1’." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="port_capability_mask" descr="Sets the PortInfoCapabilityMask:Specifies the supported capabilities of this node. A bit set to 1 for\;affirmation of supported capability.port_capability_mask[127:96] is mapped to CapabilityMask in PortInfo\;MAD.port_capability_mask[95:80] is mapped to CapabilityMask2 in PortInfo\;MAD." access="RW" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
</node>

<node name="pcct_reg_ext" descr="" attr_required_tlvs="index:s" size="0x20.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM0: Network_port1: Near_End_Port - (For Retimer/Gearbox - Host side)2: Internal_IC_LR_Port3: Far_End_Port - (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" enum="Network_port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0: Local_port_number1: IB_port_number" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="page_select" descr="page select index:0: plu_general_tracer_page1: plu_latched_counters_page" access="INDEX" enum="plu_general_tracer_page=0x0,plu_latched_counters_page=0x1" offset="0x4.0" size="0x0.8" />
	<field name="page_data" descr="PLU General Tracer Page LayoutPLU Latched Counters Page Layout" subnode="pcct_reg_page_data_auto_ext" access="RW" offset="0x8.0" size="0x18.0" union_selector="$(parent).page_select" />
</node>

<node name="pcct_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x18.0" >
	<field name="plu_general_tracer_page_ext" descr="" subnode="plu_general_tracer_page_ext" access="RW" offset="0x0.0" selected_by="plu_general_tracer_page" size="0x18.0" />
	<field name="plu_latched_counters_page_ext" descr="" subnode="plu_latched_counters_page_ext" access="RW" offset="0x0.0" selected_by="plu_latched_counters_page" size="0x18.0" />
</node>

<node name="pcmr_reg_ext" descr="" size="0xc.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fcs_cap" descr="Specifies the check enable/disable capabilities of the local port. A bit\;set to 1 for affirmation of supported enable/disable capability:FCS check disable/enable\;capability" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="rx_ts_over_crc_cap" descr="Specifies the ingress timestamps enable/disable capabilities of the\;local port. A bit set to 1 for affirmation of supported enable/disable\;capability" access="RO" offset="0x4.13" size="0x0.1" />
	<field name="rx_fcs_drop_cap" descr="Specifies the ingress drop enable/disable capabilities of the local\;port. A bit set to 1 for affirmation of supported enable/disable\;capability" access="RO" offset="0x4.14" size="0x0.1" />
	<field name="tx_fcs_recalc_cap" descr="Specifies the egress drop enable/disable capabilities of the local port.\;A bit set to 1 for affirmation of supported enable/disable capability" access="RO" offset="0x4.15" size="0x0.1" />
	<field name="tx_ts_over_crc_cap" descr="Specifies the egress timestamps enable/disable capabilities of the local\;port. A bit set to 1 for affirmation of supported enable/disable\;capability" access="RO" offset="0x4.16" size="0x0.1" />
	<field name="fcs_chk" descr="FCS checkValues:0: disable check.1: perform checkNote: when disabling a check, it will also affects the relevant\;counters." access="RW" offset="0x8.1" size="0x0.1" />
	<field name="rx_ts_over_crc" descr="RX TimeStamp over FCS0: no TS over FCS1: TS over FCSNote:1. If this field is changed while traffic is passing then some packets\;may be dropped due to incorrect FCS.Default value is (1) - TS over FCSReserved when GPUNet" access="RW" offset="0x8.13" size="0x0.1" />
	<field name="rx_fcs_drop" descr="RX FCS drop control:0: ingress port will drop a packet with bad FCS (Default)1: ingress port will not drop a packet with bad FCSNOTE: All FCS counters (PPCNT) are valid for both drop modes.NOTE: Reserved when PCMR.fcs_cap=1 &amp; PCMR.fcs_chk=0" access="RW" offset="0x8.14" size="0x0.1" />
	<field name="tx_fcs_recalc" descr="TX FCS recalculation:0: egress port will recalculate and overwrite FCS value (Default)\;1: egress port will not overwrite FCS value\;NOTE: when this bit is set, any modification of the packet will result\;in a bad FCS.Reserved when GPUNet" access="RW" offset="0x8.15" size="0x0.1" />
	<field name="tx_ts_over_crc" descr="TX TimeStamp over FCS0: no TS over FCS1: TS over FCSReserved when tx_fcs_recalc is setReserved when GPUNet" access="RW" offset="0x8.16" size="0x0.1" />
</node>

<node name="pd_link_eth_enabled_ext" descr="" size="0x4.0" >
	<field name="link_eth_active" descr="Ethernet protocols active: see PTYS.ext_eth_proto_oper" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pd_link_ib_enabled_ext" descr="" size="0x4.0" >
	<field name="link_speed_active" descr="IB link active speed:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="link_width_active" descr="IB link active width:Bit 0: 1xBit 1: 2xBit 2: 4xOther - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_apsu_info_page_ext" descr="" size="0xf8.0" >
	<field name="rts_update_state" descr="The actual state of the RTS update state diagram (IEEE 802.3dj Annex 178B Figure 178B-9).0: START1: WAIT_ADJACENT2: SWITCH_CLOCK3: TX_CLOCK_READY4: FORWARD_RTS" access="RO" offset="0x0.5" size="0x0.3" />
	<field name="training_status" descr="The status of the RTS function. Valid only if apsu_oper = Enabled.0: FAIL: Any lane training failed1: OK: All lanes are OK2: READY: remote_rts is true and training_status is READY3: IN_PROGRESS: training_status is IN_PROGRESS or remote_rts is false and training_status is READY" access="RO" offset="0x0.12" size="0x0.2" />
	<field name="rts_status" descr="The status of the RTS function.0: FAIL: Any lane training failed1: TRAINED: training_status is IN_PROGRESS or remote_rts isfalse and training_status is READY2: READY: remote_rts is true and training_status is READY3: OK: All lanes are OK" access="RO" offset="0x0.15" size="0x0.2" />
	<field name="isl_ready" descr="Set when ln_local_rx_ready and ln_remote_rx_ready are true for all lanes of the port" access="RO" offset="0x0.18" size="0x0.1" />
	<field name="remote_type" descr="Peer type. Can be written by the FW in FW control mode and by the SW in independent mode.4: Not detected1: CPO detected2: LPO detected3: FRO detected6: TRO detected7: Not supported" access="RO" offset="0x4.4" size="0x0.3" />
	<field name="peer_detected" descr="Set if the remote peer is an Nvidia device." access="RO" offset="0x4.9" size="0x0.1" />
	<field name="rts_rx_all" descr="Set if the Not ready to send bit in the ILT received frame is clear for all lanes in the port" access="RO" offset="0x4.10" size="0x0.1" />
	<field name="rts_tx_all" descr="Set when all lanes in the port are ready to send PCS data" access="RO" offset="0x4.11" size="0x0.1" />
	<field name="remote_host_iud" descr="Remote host. Can be written by the FW in FW control mode and by the SW in independent mode.0: Spectrum1: ConnectX" access="RO" offset="0x4.25" size="0x0.3" />
	<field name="uses_recovered_clock" descr="Indicates that interafce uses recovered clock for transmission.0: For hosts: Spectrum, Quantum, ConnectX1: For retimers: Arcus" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="lane_data" descr="Per-lane APSU status. Array of 8 96-bit elements, 3 DWORDs each\;(lane_data[0] at 08h-10h, lane_data[7] at 5Ch-64h).\;See APSU Info Page Lane Data Fields." access="RW" high_bound="2" low_bound="0" offset="0x8.0" size="0xc.0" />
</node>

<node name="pddr_c2p_link_enabled_eth_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_eth_enabled" descr="Ethernet protocols admin state: see PTYS.ext_eth_proto_admin" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_c2p_link_enabled_ib_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_proto_enabled" descr="bi link enabled speed:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="core_to_phy_link_width_enabled" descr="IB link enabled width:Bit 0: 1xBit 1: 2xBit 2: 4xOther - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_c2p_link_enabled_nvlink_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_nvlink_enabled" descr="NVLink protocols admin statesee:\;PTYS - Extended Protocol NVLink - admin Layout" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_cable_cap_eth_ext" descr="" size="0x4.0" >
	<field name="cable_ext_eth_proto_cap" descr="Cable Ethernet protocols cap. If PTYS.ext_eth_proto_cap filed is\;supported, use for opcode definition PTYS.ext_eth_proto_capIf\;PTYS.ext_eth_proto_capability mask is empty, use For opcode definition\;PTYS.eth_proto_cap." access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_cable_cap_ib_ext" descr="" size="0x4.0" >
	<field name="cable_link_speed_cap" descr="Cable support IB speed:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="cable_link_width_cap" descr="Cable support IB width:Bit 0: 1xBit 1: 2xBit 2: 4xOther - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_cable_cap_nvlink_ext" descr="" size="0x4.0" >
	<field name="cable_nvlink_proto_cap" descr="Cable NVLink protocols cap:See:\;PTYS - Extended Protocol NVLink - cap/oper Layout" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_cpo_module_page_ext" descr="" size="0xa8.0" >
	<field name="oe_sn" descr="Represent the OE SN, which matched to the sub module or local port" access="RO" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
	<field name="laser_source_sn" descr="Represent the ELS SN, which matched to the sub module or local port" access="RO" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="laser_source_fw_version" descr="Relevant for virtual modules based system. represent the ELS FW version." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="els_laser_index" descr="ELS laser index, relevant when no 8x split." access="RO" offset="0x24.0" size="0x0.6" />
	<field name="sub_module" descr="Sub module" access="RO" offset="0x24.8" size="0x0.4" />
	<field name="oe_index" descr="OE index" access="RO" offset="0x24.16" size="0x0.8" />
	<field name="els_index" descr="ELS index" access="RO" offset="0x24.24" size="0x0.8" />
	<field name="oe_lane7_to_els_logical_laser" descr="(see above)" access="RO" offset="0x28.0" size="0x0.4" />
	<field name="oe_lane6_to_els_logical_laser" descr="(see above)" access="RO" offset="0x28.4" size="0x0.4" />
	<field name="oe_lane5_to_els_logical_laser" descr="(see above)" access="RO" offset="0x28.8" size="0x0.4" />
	<field name="oe_lane4_to_els_logical_laser" descr="(see above)" access="RO" offset="0x28.12" size="0x0.4" />
	<field name="oe_lane3_to_els_logical_laser" descr="(see above)" access="RO" offset="0x28.16" size="0x0.4" />
	<field name="oe_lane2_to_els_logical_laser" descr="(see above)" access="RO" offset="0x28.20" size="0x0.4" />
	<field name="oe_lane1_to_els_logical_laser" descr="(see above)" access="RO" offset="0x28.24" size="0x0.4" />
	<field name="oe_lane0_to_els_logical_laser" descr="OE optical lane to ELS logical laser mapping" access="RO" offset="0x28.28" size="0x0.4" />
	<field name="module_lane_mask" descr="Bit mask of valid lanes." access="RO" offset="0x2c.24" size="0x0.8" />
</node>

<node name="pddr_fec_measure_ltx_nvl5_ext" descr="" size="0x8c.0" >
	<field name="lane_lt_x_feq_ber" descr="Per-lane LT-X FEQ BER iteration database. Array of 2 544-bit\;elements, 17 DWORDs each (lane_lt_x_feq_ber[0] at 00h–40h,\;lane_lt_x_feq_ber[1] at 44h–84h)." subnode="ef_lt_x_feq_ber_db_v1_ext" access="RO" high_bound="1" low_bound="0" offset="0x0.0" size="0x88.0" />
	<field name="port_info" descr="Per-port LT-X state and counters." subnode="ef_lt_x_port_info_v1_ext" access="RO" offset="0x88.0" size="0x4.0" />
</node>

<node name="pddr_link_active_eth_ext" descr="" size="0x4.0" >
	<field name="link_eth_active" descr="Ethernet protocols active: see PTYS.ext_eth_proto_oper" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_link_active_ib_ext" descr="" size="0x4.0" >
	<field name="link_speed_active" descr="IB link active speed:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="link_width_active" descr="IB link active width:Bit 0: 1xBit 1: 2xBit 2: 4xOther - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_link_active_nvlink_ext" descr="" size="0x4.0" >
	<field name="link_nvlink_active" descr="NVLink protocols activeSee:\;PTYS - Extended Protocol NVLink - cap/oper Layout" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_link_down_info_page_ext" descr="" size="0xf4.0" >
	<field name="down_blame" descr="Which receiver caused last link down:0: Unknown1: Local_phy2: Remote_phy" access="RO" enum="Unknown=0x0,Local_phy=0x1,Remote_phy=0x2" offset="0x0.0" size="0x0.4" />
	<field name="down_intent" descr="For the last link down reason, indicates if the link drop was\;intentional (e.g port down command, cable unplug etc…) or\;unintentional (e.g Bad SI).down_intent is updated on the link drop according to local reason\;information and updated again on LinkUp according to local + peer down\;reason (only if negotiation took place during linkup flow)0: Unknown1: intentional2: unintentional" access="RO" enum="Unknown=0x0,intentional=0x1,unintentional=0x2" offset="0x0.4" size="0x0.4" />
	<field name="local_reason_opcode" descr="(see above)" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="recovery_entry_reason" descr="Opcode of link down reason for local / remote side / last successful\;recovery entry reason:Recovery entry reason supported only if PCAM.feature_cap_mask bit 117 is\;set0: No_link_down_indication1: Unknown_reason2: Hi_BER3: Block_Lock_loss4: Alignment_loss5: FEC_sync_loss6: PLL_lock_loss7: FIFO_overflow8: false_SKIP_condition9: Minor_Error_threshold_exceeded10: Physical_layer_retransmission_timeout11: Heartbeat_errors12: Link_Layer_credit_monitoring_watchdog13: Link_Layer_integrity_threshold_exceeded14: Link_Layer_buffer_overrun15: Down_by_outband_command_with_healthy_link16: Down_by_outband_command_for_link_with_hi_ber17: Down_by_inband_command_with_healthy_link18: Down_by_inband_command_for_link_with_hi_ber19: Down_by_verification_GW20: Received_Remote_Fault21: Received_TS122: Down_by_management_command23: Cable_was_unplugged24: Cable_access_issue25: Cable_Thermal_shutdown26: Current_issue27: Power_budget28: Fast_recovery_raw_ber29: Fast_recovery_effective_ber30: Fast_recovery_symbol_ber31: Fast_recovery_credit_watchdog32: Peer_side_down_to_sleep_state33: Peer_side_down_to_disable_state34: Peer_side_down_to_disable_and_port_lock35: Peer_side_down_due_to_thermal_event36: Peer_side_down_due_to_force_event37: Peer_side_down_due_to_reset_event38: Reset_no_power_cycle39: Fast_recovery_tx_plr_trigger40: Down_due_to_HW_force_event42: L1_exit_failure43: too_many_link_error_recoveries44: Down_due_to_contain_mode45: BW_loss_threshold_exceeded46: ELS_laser_fault47: Hi_SER48: down_by_nmx_adminstate_cmd49: flua_ber_below_threshold_in_guard_time50: Received_Local_Fault51: Received_Link_Interruption52: Manual_debug_mode53: command_triggered_recovery58: Recovery_BW_loss_threshold_exceeded59: Peer_side_down_due_to_contain_mode60: module_unexpected_reset_or_low_power61: Down_due_to_contain_mode_rx62: Down_due_to_contain_mode_tx" access="RO" enum="No_link_down_indication=0x0,Unknown_reason=0x1,Hi_BER=0x2,Block_Lock_loss=0x3,Alignment_loss=0x4,FEC_sync_loss=0x5,PLL_lock_loss=0x6,FIFO_overflow=0x7,false_SKIP_condition=0x8,Minor_Error_threshold_exceeded=0x9,Physical_layer_retransmission_timeout=0xa,Heartbeat_errors=0xb,Link_Layer_credit_monitoring_watchdog=0xc,Link_Layer_integrity_threshold_exceeded=0xd,Link_Layer_buffer_overrun=0xe,Down_by_outband_command_with_healthy_link=0xf,Down_by_outband_command_for_link_with_hi_ber=0x10,Down_by_inband_command_with_healthy_link=0x11,Down_by_inband_command_for_link_with_hi_ber=0x12,Down_by_verification_GW=0x13,Received_Remote_Fault=0x14,Received_TS1=0x15,Down_by_management_command=0x16,Cable_was_unplugged=0x17,Cable_access_issue=0x18,Cable_Thermal_shutdown=0x19,Current_issue=0x1a,Power_budget=0x1b,Fast_recovery_raw_ber=0x1c,Fast_recovery_effective_ber=0x1d,Fast_recovery_symbol_ber=0x1e,Fast_recovery_credit_watchdog=0x1f,Peer_side_down_to_sleep_state=0x20,Peer_side_down_to_disable_state=0x21,Peer_side_down_to_disable_and_port_lock=0x22,Peer_side_down_due_to_thermal_event=0x23,Peer_side_down_due_to_force_event=0x24,Peer_side_down_due_to_reset_event=0x25,Reset_no_power_cycle=0x26,Fast_recovery_tx_plr_trigger=0x27,Down_due_to_HW_force_event=0x28,L1_exit_failure=0x2a,too_many_link_error_recoveries=0x2b,Down_due_to_contain_mode=0x2c,BW_loss_threshold_exceeded=0x2d,ELS_laser_fault=0x2e,Hi_SER=0x2f,down_by_nmx_adminstate_cmd=0x30,flua_ber_below_threshold_in_guard_time=0x31,Received_Local_Fault=0x32,Received_Link_Interruption=0x33,Manual_debug_mode=0x34,command_triggered_recovery=0x35,Recovery_BW_loss_threshold_exceeded=0x3a,Peer_side_down_due_to_contain_mode=0x3b,module_unexpected_reset_or_low_power=0x3c,Down_due_to_contain_mode_rx=0x3d,Down_due_to_contain_mode_tx=0x3e" offset="0x4.16" size="0x0.8" />
	<field name="remote_reason_opcode" descr="(see above)" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="e2e_reason_opcode" descr="see local_reason_opcode for local reason opcodefor remote reason opcode: local_reason_opcode+100" access="RO" offset="0xc.0" size="0x0.8" />
	<field name="ts1_opcode" descr="TS1 opcode describes the reason the peer requested to ramp down the\;link:0x8: TS1.Sleep0x9: TS1.Disable0xA: TS1.PortLock0xB: TS1.Thermal0xC: TS1.Clean0xD : TS1.Force0xE: TS1.reset_reqNote: This field is valid in case the local_reason_opcode = 21 or 32-38" access="RO" offset="0xc.12" size="0x0.4" />
	<field name="l1_failure_reason" descr="0: no_info_or_no_l1_failure1: HW_timeout2: FW_timeout3: Recovery_failure" access="RO" offset="0xc.16" size="0x0.4" />
	<field name="last_recovery_state" descr="last unsuccessful recovery event state0: no_info1: Retrain - no local receiver lock2: WaitRMT - local receiver locked, peer not locked3: IDLE - both local and remote transmitter locked" access="RO" offset="0xc.20" size="0x0.4" />
	<field name="num_of_symbol_ber_alarms" descr="Number of Symbol BER Windows that crossed alarm threshold" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="last_raw_ber_magnitude" descr="(see above)" access="RO" offset="0x10.16" size="0x0.8" />
	<field name="last_raw_ber_coef" descr="Last raw BER window calculated.Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude)" access="RO" offset="0x10.24" size="0x0.4" />
	<field name="cons_raw_norm_ber" descr="Number of last consecutive normal Raw BER windows" access="RO" offset="0x10.28" size="0x0.4" />
	<field name="max_raw_ber_magnitude" descr="(see above)" access="RO" offset="0x14.0" size="0x0.8" />
	<field name="max_raw_ber_coef" descr="Maximal raw BER window calculated.Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude)" access="RO" offset="0x14.8" size="0x0.4" />
	<field name="min_raw_ber_magnitude" descr="(see above)" access="RO" offset="0x14.16" size="0x0.8" />
	<field name="min_raw_ber_coef" descr="Minimal raw BER window calculated.Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude)" access="RO" offset="0x14.24" size="0x0.4" />
	<field name="num_of_raw_ber_alarms" descr="Number of Raw BER Windows that crossed alarm threshold" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="num_of_eff_ber_alarms" descr="Number of Effective BER Windows that crossed alarm threshold" access="RO" offset="0x18.16" size="0x0.16" />
	<field name="time_to_link_down_to_disable" descr="Time in msec to link down to disable state, once a paos down is set or a\;link down event occurs.If the phy manager state is different then disable the timer will return\;0." access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="time_to_link_down_to_rx_loss" descr="Time in msec to link down to rx disable state, once a link down event\;occurs.If the phy manager state is different then rx disable the timer will\;return 0." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="min_eff_ber_magnitude" descr="(see above)" access="RO" offset="0x24.0" size="0x0.8" />
	<field name="min_eff_ber_coef" descr="Minimal effective BER window calculated.Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude)" access="RO" offset="0x24.8" size="0x0.4" />
	<field name="last_eff_ber_magnitude" descr="(see above)" access="RO" offset="0x24.16" size="0x0.8" />
	<field name="last_eff_ber_coef" descr="Last effective BER window calculated.Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude)" access="RO" offset="0x24.24" size="0x0.4" />
	<field name="cons_eff_norm_ber" descr="Number of last consecutive normal Effective BER windows" access="RO" offset="0x24.28" size="0x0.4" />
	<field name="max_eff_ber_magnitude" descr="(see above)" access="RO" offset="0x28.0" size="0x0.8" />
	<field name="max_eff_ber_coef" descr="Maximal effective BER window calculated.Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude)" access="RO" offset="0x28.8" size="0x0.4" />
	<field name="max_symbol_ber_magnitude" descr="(see above)" access="RO" offset="0x28.16" size="0x0.8" />
	<field name="max_symbol_ber_coef" descr="Maximal symbol BER window calculated.Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x28.24" size="0x0.4" />
	<field name="cons_symbol_norm_ber" descr="Number of last consecutive normal Symbol BER windows" access="RO" offset="0x28.28" size="0x0.4" />
	<field name="min_symbol_ber_magnitude" descr="(see above)" access="RO" offset="0x2c.0" size="0x0.8" />
	<field name="min_symbol_ber_coef" descr="Minimal symbol BER window calculated.Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x2c.8" size="0x0.4" />
	<field name="last_symbol_ber_magnitude" descr="(see above)" access="RO" offset="0x2c.16" size="0x0.8" />
	<field name="last_symbol_ber_coef" descr="Last symbol BER window calculated.Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x2c.24" size="0x0.4" />
	<field name="hi_ser_counter" descr="Number of hi_ser events since last clear" access="RO" offset="0x30.0" size="0x0.8" />
	<field name="pcs_phy_state_latched" descr="PCS HW state on link-down, latched:Bits 0-7: Block lock (one bit per lane) - No FEC modeBits 8-15: AM lock (one bit per lane) - RS FEC modeBits 16-23: FEC lock (one bit per lane) - FC FEC modeBit 24: Align_statusBit 25: Hi_BERBit 26: Hi_SERBits 30:27: ReservedBit 31: Active. When set the value of the pcs_phy_state_latched is valid" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="apsu_restart_reason_opcode" descr="Opcode for APSU restart reason.0: apsu_restarted_due_to_fail1: apsu_restarted_due_to_link_fail" access="RO" enum="apsu_restarted_due_to_fail=0x0,apsu_restarted_due_to_link_fail=0x1" offset="0x38.0" size="0x0.8" />
</node>

<node name="pddr_link_health_page_ext" descr="" size="0xb0.0" >
	<field name="ltx_status_lane0" descr="0: PASS1: FAIL" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="ltx_fail_reason_lane0" descr="0: NONE1: EFFECTIVE2: HISTOGRAM3: EFFECTIVE_HISTOGRAM4: RAW5: EFFECTIVE_RAW6: HISTOGRAM_RAW7: EFFECTIVE_HISTOGRAM_RAW8: PRBS9: EFFECTIVE_PRBS10: HISTOGRAM_PRBS11: EFFECTIVE_HISTOGRAM_PRBS12: RAW_PRBS13: EFFECTIVE_RAW_PRBS14: HISTOGRAM_RAW_PRBS15: EFFECTIVE_HISTOGRAM_RAW_PRBS" access="RO" offset="0x0.1" size="0x0.5" />
	<field name="ltx_retry_count_lane0" descr="Number of times the link quality by fec measure re-checked before the\;link came up for lane0.A value of 0 means the link was ready after the first check.A value of 1 means the link needed to be checked twice, and so on." access="RO" offset="0x0.6" size="0x0.5" />
	<field name="ltx_retry_count_max_lane0" descr="" access="RO" offset="0x0.11" size="0x0.5" />
	<field name="hist_target_lane0" descr="" access="RO" offset="0x0.19" size="0x0.5" />
	<field name="raw_ber_mag_target_lane0" descr="" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="raw_ber_mant_target_lane0" descr="" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="ltx_logger_index_lane0" descr="" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="ltx_retry_fail_count_lane0" descr="Number of times the link quality by fec measure failed before the link\;came up for lane0." access="RO" offset="0x4.8" size="0x0.5" />
	<field name="raw_ber_mant_float_target_lane0" descr="" access="RO" offset="0x4.13" size="0x0.4" />
	<field name="fec_measure_retry_count" descr="Number of times the link quality by fec measure re-checked before the\;link came up per port.A value of 0 means the link was ready after the first check.A value of 1 means the link needed to be checked twice, and so on." access="RO" offset="0x4.24" size="0x0.4" />
	<field name="ltx_status_lane1" descr="0: PASS1: FAIL" access="RO" offset="0x8.0" size="0x0.1" />
	<field name="ltx_fail_reason_lane1" descr="0: NONE1: EFFECTIVE2: HISTOGRAM3: EFFECTIVE_HISTOGRAM4: RAW5: EFFECTIVE_RAW6: HISTOGRAM_RAW7: EFFECTIVE_HISTOGRAM_RAW8: PRBS9: EFFECTIVE_PRBS10: HISTOGRAM_PRBS11: EFFECTIVE_HISTOGRAM_PRBS12: RAW_PRBS13: EFFECTIVE_RAW_PRBS14: HISTOGRAM_RAW_PRBS15: EFFECTIVE_HISTOGRAM_RAW_PRBS" access="RO" offset="0x8.1" size="0x0.5" />
	<field name="ltx_retry_count_lane1" descr="" access="RO" offset="0x8.6" size="0x0.5" />
	<field name="ltx_retry_count_max_lane1" descr="" access="RO" offset="0x8.11" size="0x0.5" />
	<field name="hist_target_lane1" descr="" access="RO" offset="0x8.19" size="0x0.5" />
	<field name="raw_ber_mag_target_lane1" descr="" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="raw_ber_mant_target_lane1" descr="" access="RO" offset="0xc.0" size="0x0.4" />
	<field name="ltx_logger_index_lane1" descr="" access="RO" offset="0xc.4" size="0x0.4" />
	<field name="ltx_retry_fail_count_lane1" descr="Number of times the link quality by fec measure failed before the link\;came up for lane0." access="RO" offset="0xc.8" size="0x0.5" />
	<field name="raw_ber_mant_float_target_lane1" descr="" access="RO" offset="0xc.13" size="0x0.4" />
	<field name="fec_measure_retry_fail_count" descr="Number of times the link quality by fec measure failed before the link\;came up per port." access="RO" offset="0xc.24" size="0x0.4" />
	<field name="ltx_logger_lane0" descr="Ltx Logger Page Layout" subnode="ltx_logger_ext" access="RO" high_bound="9" low_bound="0" offset="0x10.0" size="0x50.0" />
	<field name="ltx_logger_lane1" descr="Ltx Logger Page Layout" subnode="ltx_logger_ext" access="RO" high_bound="9" low_bound="0" offset="0x60.0" size="0x50.0" />
</node>

<node name="pddr_link_partner_info_ext" descr="" size="0x30.0" >
	<field name="info_supported_mask" descr="bitmask for supported info0 - field info is not valid.1 - field info is valid.Bit 0: partner_local_port_supportedBit 1: partner_module_type_supportedBit 2: partner_id_lsb_supportedBit 4: peer_ga_idBit 5: partner_id_39_25_supported" access="RO" enum="partner_local_port_supported=0x1,partner_module_type_supported=0x2,partner_id_lsb_supported=0x4,peer_ga_id=0x10,partner_id_39_25_supported=0x20" offset="0x0.0" size="0x0.16" />
	<field name="partner_local_port" descr="local_port of link partnerValid only if bit 0 is set in info_supported_mask" access="RO" offset="0x4.0" size="0x0.10" />
	<field name="partner_module_type" descr="module type of link partner.Module type connected:0: undefined1: Active_Optical_or_Copper_Cable2: Active_Optical_Transceiver3: Passive_Copper_cable5: Twisted_pair6: Far_End_Linear_Equalizer_Cable7: Linear_Optical_Transceiver - (Direct Drive)8: CPO9: Near_end_linear_equalizer_cable10: Fully_linear_equalizer_cable11: Half_retimed_tx_optical_transceiverValid only if bit 1 is set in info_supported_mask" access="RO" enum="undefined=0x0,Active_Optical_or_Copper_Cable=0x1,Active_Optical_Transceiver=0x2,Passive_Copper_cable=0x3,Twisted_pair=0x5,Far_End_Linear_Equalizer_Cable=0x6,Linear_Optical_Transceiver=0x7,CPO=0x8,Near_end_linear_equalizer_cable=0x9,Fully_linear_equalizer_cable=0xa,Half_retimed_tx_optical_transceiver=0xb" offset="0x8.0" size="0x0.4" />
	<field name="peer_ga_id" descr="Valid only if Bit 4 is set in info_supported_mask.Indicates the peer port Geographical Adress (GA) OR Module ID in GPU\;case" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="partner_id_39_25" descr="bits 39 to 25 bits of link partner unique ID:GUID IB InfiniBand linksMAC in Ethernet linksValid only if bit 5 is set in info_supported_mask" access="RO" offset="0xc.0" size="0x0.16" />
	<field name="partner_id_lsb" descr="24 lsb bits of link partner unique ID:GUID IB InfiniBand linksMAC in Ethernet linksValid only if bit 2 is set in info_supported_mask" access="RO" offset="0x10.0" size="0x0.24" />
</node>

<node name="pddr_link_up_info_page_ext" descr="" size="0xf8.0" >
	<field name="up_reason_mng" descr="invalid port access severity0 - No down command / unknown1 - BMC force linkup2 - WOL force linkup3 - ASN.1 force link up" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="up_reason_drv" descr="invalid port access severity0 - No down command / unknown1 - Up by at least one of the hosts" access="RO" offset="0x0.8" size="0x0.4" />
	<field name="up_reason_pwr" descr="invalid port access severity0 - No down command / unknown1 - Keep link up on boot2 - Keep link up Eth/IB3 - Keep link up on standby" access="RO" offset="0x0.16" size="0x0.4" />
	<field name="time_to_link_up" descr="Time in msec to link up from disable until phy up state.While the phy manager did not reach phy up state the timer will return\;0.The timer resets to 0 in one of the following cases:When moving to disable or rx disable state.2. When moving from active or phy up to polling state, while working at\;force mode." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="fast_link_up_status" descr="Indicates if fast link-up was performed in the link:0: Unknown1: Fast Link-UP was performed.2: Regular link-up flow was performed due to changes in cable3: Regular link-up flow was performed due to changes in protocol (speed\;or FEC)4: Regular link-up flow was performed due to a non-fastbootable FW\;version (PCNR is not supported)5: Regular link-up performed due to MLPN flow6: Regular link-up performed due to PCNR.tuning_override configuration\;while port was in “down” state.7: Invalid fastboot data struct (0xCAFECAFE magic value is not present.\;For example, SW reset was executed before finish saving data during PCNR\;flow)8: fast link-up timeout9: fast link-up flaps issue10: fast link-up failed during link-up" access="RO" offset="0x8.0" size="0x0.4" />
	<field name="time_to_link_up_phy_up_to_active" descr="Ethernet:Time in msec to link up from phy up until active state.While the phy manager did not reach active state the timer will return\;0.The timer resets to 0 in one of the following cases:When moving to disable or rx disable state.2. When moving from active or phy up to polling state, while working at\;force mode.IB:Time in msec from entering recovery state until back to Active state in\;case of successful recovery" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="time_to_link_up_sd_to_phy_up" descr="Ethernet onlyTime in msec to link up from signal detect until phy up state.While the phy manager did not reach phy up state the timer will return\;0.The timer resets to 0 in one of the following cases:When moving to disable or rx disable state.2. When moving from active or phy up to polling state, while working at\;force mode." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="time_to_link_up_disable_to_sd" descr="Ethernet:Time in msec to link up from disable until signal detect state.While the phy manager did not reach signal detect state the timer will\;return 0.The timer resets to 0 in one of the following cases:When moving to disable or rx disable state.2. When moving from active or phy up to polling state, while working at\;force mode. IB:Time in msec to link up from disable until partner is detected (exit of\;Signal detect/receiver detect states)." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="time_to_link_up_disable_to_pd" descr="Ethernet onlyTime in msec to link up from disable until protocol detect state.While the phy manager did not reach protocol detect state the timer will\;return 0.The timer resets to 0 in one of the following cases:When moving to disable or rx disable state.2. When moving from active or phy up to polling state, while working at\;force mode." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="time_of_module_conf_done_up" descr="Time in msec of phy2mod command response of module conf done in port up\;case" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="time_of_module_conf_done_down" descr="Time in msec of phy2mod command response of module conf done in port\;down case" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="time_logical_init_to_active" descr="Time in mSec that it takes for the port logical state to transition from\;init to an active state.The timer reset to 0 ONLY when the logical port state goes down." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="total_time_pcs_local_fault" descr="Total time in sec of PCS state of Local Fault" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="total_time_pcs_remote_fault" descr="Total time in sec of PCS state of Remote Fault" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="time_on_last_hi_ser" descr="Time duration of last hi_ser event.value reset every new hi_ser event." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="last_phy_data_groups_collection_time" descr="Duration of last phy data collection period conducted by FW Phy\;following a single timeline event trigger. This indicates the overall\;duration it took to complete the FW Phy data collection thread.Value is reset every new data collection trigger. If in the last trigger\;there was no requirement to collect FW Phy data field should return 0.Value is in units of 1 [msec]" access="RO" offset="0x34.0" size="0x0.16" />
	<field name="last_data_groups_collection_time" descr="Duration of last data collection period conducted by FW Phy following a\;single timeline event trigger. This indicates the overall duration it\;took to complete all different collection threads.Value is reset every new data collection trigger.Value is in units of 1 [msec]" access="RO" offset="0x34.16" size="0x0.16" />
	<field name="last_module_data_groups_collection_time" descr="Duration of last module data collection period conducted by FW Phy\;following a single timeline event trigger. This indicates the overall\;duration it took to complete the System Module data collection thread.Value is reset every new data collection trigger. If in the last trigger\;there was no requirement to collect module data field should return 0.Value is in units of 1 [msec]" access="RO" offset="0x38.0" size="0x0.16" />
	<field name="last_serdes_data_groups_collection_time" descr="Duration of last SerDes data collection period conducted by FW Phy\;following a single timeline event trigger. This indicates the overall\;duration it took to complete the FW Serdes data collection thread.Value is reset every new data collection trigger. If in the last trigger\;there was no requirement to collect UPHY data field should return 0.Value is in units of 1 [msec]" access="RO" offset="0x38.16" size="0x0.16" />
	<field name="apsu_total_time" descr="Duration of the last APSU until data is transmitted in seconds" access="RO" offset="0x40.0" size="0x0.12" />
	<field name="apsu_ilt_time" descr="Duration of the last link training function of APSU in seconds" access="RO" offset="0x40.16" size="0x0.12" />
</node>

<node name="pddr_module_info_ext" descr="" size="0xd0.0" >
	<field name="ethernet_compliance_code" descr="QSFP:Ethernet Compliance Codes bit mask (10/40G/100G)Byte131 per SFF-8636Bit 7 - Extended Specification Compliance validBit 6 - 10GBASE-LRMBit 5 - 10GBASE-LRBit 4 - 10GBASE-SRBit 3 - 40GBASE-CR4Bit 2 - 40GBASE-SR4Bit 1 - 40GBASE-LR4Bit 0 - 40G Active Cable (XLPPI)SFP:10G Ethernet Compliance CodesByte3 per SFF-8472:Bit 7 - 10G Base-ERBit 6 - 10G Base-LRMBit 5 - 10G Base-LRBit 4 - 10G Base-SRCMIS based (QSFP-DD/ SFP-DD / OSFP/OE)Byte 87 - Module Media Interface" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="ext_ethernet_compliance_code" descr="Extended Specification Compliance Codesfor SFP:byte 36 per SFF-8472for QSFP:byte192 per SFF-8636 (QSFP28)for CMIS (SFP-DD / QSFP-DD/ OSFP/OE):Byte 86 - Host Electrical Interface" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="cable_breakout" descr="Reserved for SFP.For QSFP:Byte113 per SFF-8636For CMIS based modules:XX naming is according to cable_identifier nameFor example: if cable_identifier = ,6 XX string is QSFP-DD0 - Unspecified1 - XX to XX2 - XX to 2xQSFP or 2xXX (depopulated / 4 lanes)3 - XX to 4xDSFP or 4xQSFP (depopulated / 2 lanes)4 - XX to 8xSFP5 - XX (depopulated / 4 lanes) to QSFP or XX (depopulated / 4 lanes)6 - XX (depopulated / 4 lanes) to 2xXX(depopulated / 2 lanes) or\;2xSFP-DD7 - XX (depopulated / 4 lanes) to 4xSFP8 - XX(/ 2 lane module) to XX9 - XX(/ 2 lane module) to 2xSFP" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="cable_technology" descr="QSFP:Byte 147 per SFF-8636.SFP:SFP+ Cable Technology:byte8 per SFF-8472:Bit 3 - Active CableBit 2 - Passive CableCMIS based (QSFP-DD / OSFP/ SFP-DD/OE):Byte 2120x00: VCSEL_850nm0x01: VCSEL_1310nm0x02: VCSEL_1550nm0x03: FP_laser_1310nm0x04: DFB_laser_1310nm0x05: DFB_laser_1550nm0x06: EML_1310nm0x07: EML_1550nm0x08: others0x09: DFB_laser_1490nm0x0a: Passive_copper_cable_unequalized0x0b: Passive_copper_cable_equalized0x0c: Copper_cable_near_end_and_far_end_limiting_active_equailizer0x0d: Copper_cable_far_end_limiting_active_equailizer0x0e: Copper_cable_near_end_limiting_active_equializer0x0f: Copper_cable_linear_active_equalizers0x10: c_band_tunable_laser0x11: l_band_tunable_laser0x12: Copper_cable_near_end_and_far_end_linear_active_equalizers0x13: Copper_cable_far_end_linear_active_equalizers0x14:Copper_cable_near_end_linear_active_equalizersnote - passive copper = 0xbLinear coppers = 0xF or 0x12 or 0x13 or 0x14" access="RW" enum="VCSEL_850nm=0x0,VCSEL_1310nm=0x1,VCSEL_1550nm=0x2,FP_laser_1310nm=0x3,DFB_laser_1310nm=0x4,DFB_laser_1550nm=0x5,EML_1310nm=0x6,EML_1550nm=0x7,others=0x8,DFB_laser_1490nm=0x9,Passive_copper_cable_unequalized=0xa,Passive_copper_cable_equalized=0xb,Copper_cable_near_end_and_far_end_limiting_active_equailizer=0xc,Copper_cable_far_end_limiting_active_equailizer=0xd,Copper_cable_near_end_limiting_active_equializer=0xe,Copper_cable_linear_active_equalizers=0xf,c_band_tunable_laser=0x10,l_band_tunable_laser=0x11,Copper_cable_near_end_and_far_end_linear_active_equalizers=0x12,Copper_cable_far_end_linear_active_equalizers=0x13,Copper_cable_near_end_linear_active_equalizers=0x14" offset="0x0.24" size="0x0.8" />
	<field name="cable_power_class" descr="Module maximum power consumption for SFP/QSFP:0: Power_Class_0 - (1.0 W max)1: Power_Class_1 - (1.5 W max)2: Power_Class_2 - (2.0 W max)3: Power_Class_3 - (2.5 W max)4: Power_Class_4 - (3.5 W max)5: Power_Class_5 - (4.0 W max)6: Power_Class_6 - (4.5 W max)7: Power_Class_7 - (5.0 W max)8: Power_Class_8 - (power from max_power field)Module maximum power consumption for SFP-DD:0: Power_Class_0 - (0.5 W max)1: Power_Class_1 - (1.0 W max)2: Power_Class_2 - (1.5 W max)3: Power_Class_3 - (2.0 W max)4: Power_Class_4 - (3.5 W max)5: Power_Class_5 - (5.0 W max)6: reserved7: reserved8: Power_Class_8 - (power from max_power field)Module maximum power consumption for QSFP-DD/OSFP:1 - Power_Class_1 - (1.5 W max)2 - Power_Class_2 - (3.5 W max)3 - Power_Class_3 - (7.0 W max)4 - Power_Class_4 - (8.0 W max)5 - Power_Class_5 - (10 W max)6 - Power_Class_6 - (12 W max)7 - Power_Class_7 - (14 W max)8 - Power_Class_8 - (power from max_power field)" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="cable_identifier" descr="0: QSFP281: QSFP_Plus2: SFP28_or_SFP_Plus3: QSA - (QSFP-&gt;SFP)4: Backplane5: SFP_DD6: QSFP_DD7: QSFP_CMIS8: OSFP9: C2C10: DSFP11: QSFP_Split_Cable12: CPO13: OE14: ELS15: NPOidentifiers that are compliant to CMIS : 5,6,7,8,10,12,14,15" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="cable_length" descr="Cable length in 1m units.For CMIS modules:bits 6:7 represent cable_length_multiplier for calculating cable length00 - 0.1 multiplier (0.1 to 6.3m)01- 1 multiplier (1 to 63m)10 - 10 multiplier (10 to 630m)11 - 100 multiplier (100 to 6300m)bits 0:5 represent cable_length_value for calculating cable length.length is calculated with cable_length_value * cable_length_multiplier" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="cable_vendor" descr="Cable vendor:0: Other1: Mellanox2: Known_OUI3: NVIDIA" access="RO" enum="Other=0x0,Mellanox=0x1,Known_OUI=0x2,NVIDIA=0x3" offset="0x4.24" size="0x0.4" />
	<field name="cable_type" descr="Cable/module type:0: Unidentified1: Active_cable - (active copper / optics)2: Optical_Module - (separated)3: Passive_copper_cable_or_linear_copper - for distinguishing passive\;copper and linear copper see cable_technology4: Cable_unplugged5: Twisted_pair6: CPO7: OE8: ELS" access="RO" enum="Unidentified=0x0,Active_cable=0x1,Optical_Module=0x2,Passive_copper_cable_or_linear_copper=0x3,Cable_unplugged=0x4,Twisted_pair=0x5,CPO=0x6,OE=0x7,ELS=0x8" offset="0x4.28" size="0x0.4" />
	<field name="cable_tx_equalization" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="cable_rx_emphasis" descr="For CMIS (QSFP-DD/ SFP-DD/ OSFP) field will represent Rx pre-emphasis." access="RO" offset="0x8.8" size="0x0.8" />
	<field name="cable_rx_amp" descr="Reserved for SFP" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="max_power" descr="Reserved for SFP, QSFPByte 201 for CMIS (QSFP-DD/ SFP-DD/\;OSFP/ELS/OE)Other Cable ignore field." access="RO" offset="0x8.24" size="0x0.8" />
	<field name="cable_attenuation_5g" descr="Reserved for SFP" access="RO" offset="0xc.0" size="0x0.8" />
	<field name="cable_attenuation_7g" descr="Reserved for SFP" access="RO" offset="0xc.8" size="0x0.8" />
	<field name="cable_attenuation_12g" descr="Reserved for SFP" access="RO" offset="0xc.16" size="0x0.8" />
	<field name="cable_attenuation_25g" descr="Valid only for CMIS (QSFP-DD/ SFP-DD/ OSFP)Other Cable ignore field." access="RO" offset="0xc.24" size="0x0.8" />
	<field name="tx_cdr_state" descr="Reserved for SFPBit 0 - TX CDR on/off on channel 0Bit 1 - TX CDR on/off on channel 1Bit 2 - TX CDR on/off on channel 2Bit 3 - TX CDR on/off on channel 3Bit 4 - TX CDR on/off on channel 4Bit 5 - TX CDR on/off on channel 5Bit 6 - TX CDR on/off on channel 6Bit 7 - TX CDR on/off on channel 7CDR on - when bit is set.CDR off - when bit is clear." access="RO" offset="0x10.0" size="0x0.8" />
	<field name="rx_cdr_state" descr="Reserved for SFPBit 0 - RX CDR on/off on channel 0Bit 1 - RX CDR on/off on channel 1Bit 2 - RX CDR on/off on channel 2Bit 3 - RX CDR on/off on channel 3Bit 4 - RX CDR on/off on channel 4Bit 5 - RX CDR on/off on channel 5Bit 6 - RX CDR on/off on channel 6Bit 7 - RX CDR on/off on channel 7CDR on - when bit is set.CDR off - when bit is clear." access="RO" offset="0x10.8" size="0x0.8" />
	<field name="tx_cdr_cap" descr="0 - No CDR1 - Build-in CDR with on/off control2 - Build-in CDR without on/off control" access="RO" offset="0x10.16" size="0x0.4" />
	<field name="rx_cdr_cap" descr="0 - No CDR1 - Build-in CDR with on/off control2 - Build-in CDR without on/off control" access="RO" offset="0x10.20" size="0x0.4" />
	<field name="cable_rx_post_emphasis" descr="Valid only for CMIS (QSFP-DD/ SFP-DD/ OSFP)Rx post-emphasis." access="RO" offset="0x10.24" size="0x0.8" />
	<field name="vendor_name" descr="ASCII Vendor name left-aligned and padded on the right withASCII spaces (20h)" access="RO" high_bound="3" low_bound="0" offset="0x14.0" size="0x10.0" />
	<field name="vendor_pn" descr="Vendor Part Number left-aligned and padded on the right with ASCII\;spaces (20h)" access="RO" high_bound="3" low_bound="0" offset="0x24.0" size="0x10.0" />
	<field name="vendor_rev" descr="ASCII Vendor revision aligned to right padded with 0h on the left" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="fw_version" descr="If information is not available by the module: set to 0" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="vendor_sn" descr="Vendor Serial Number" access="RO" high_bound="3" low_bound="0" offset="0x3c.0" size="0x10.0" />
	<field name="voltage" descr="U16 Supply Voltage Monitor as defined in SFF-8636/CMIS.Internally measured supply voltage in 100uV" access="RO" offset="0x4c.0" size="0x0.16" />
	<field name="temperature" descr="S16 Module Temperature Monitor as defined in SFF-8636/CMIS.module temperature in 1/256 CValue of 0 may indicate not supported or real temperature value." access="RO" offset="0x4c.16" size="0x0.16" />
	<field name="rx_power_lane1" descr="RX measured power channel 1.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x50.0" size="0x0.16" />
	<field name="rx_power_lane0" descr="RX measured power channel 0.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x50.16" size="0x0.16" />
	<field name="rx_power_lane3" descr="RX measured power channel 3.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x54.0" size="0x0.16" />
	<field name="rx_power_lane2" descr="RX measured power channel 2.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x54.16" size="0x0.16" />
	<field name="rx_power_lane5" descr="RX measured power channel 5.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x58.0" size="0x0.16" />
	<field name="rx_power_lane4" descr="RX measured power channel 4.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x58.16" size="0x0.16" />
	<field name="rx_power_lane7" descr="RX measured power channel 7.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x5c.0" size="0x0.16" />
	<field name="rx_power_lane6" descr="RX measured power channel 6.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x5c.16" size="0x0.16" />
	<field name="tx_power_lane1" descr="TX measured power channel 1.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x60.0" size="0x0.16" />
	<field name="tx_power_lane0" descr="TX measured power channel 0.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x60.16" size="0x0.16" />
	<field name="tx_power_lane3" descr="TX measured power channel 3.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x64.0" size="0x0.16" />
	<field name="tx_power_lane2" descr="TX measured power channel 2.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x64.16" size="0x0.16" />
	<field name="tx_power_lane5" descr="TX measured power channel 5.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x68.0" size="0x0.16" />
	<field name="tx_power_lane4" descr="TX measured power channel 4.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x68.16" size="0x0.16" />
	<field name="tx_power_lane7" descr="TX measured power channel 7.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x6c.0" size="0x0.16" />
	<field name="tx_power_lane6" descr="TX measured power channel 6.measured in dBm/uW according to module_info_ext value" access="RO" offset="0x6c.16" size="0x0.16" />
	<field name="tx_bias_lane1" descr="(see above)" access="RO" offset="0x70.0" size="0x0.16" />
	<field name="tx_bias_lane0" descr="TX measured bias current on channel [i] in 2uA unit.The real sample value in uA units should be calculated as follows:tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x70.16" size="0x0.16" />
	<field name="tx_bias_lane3" descr="(see above)" access="RO" offset="0x74.0" size="0x0.16" />
	<field name="tx_bias_lane2" descr="TX measured bias current on channel [i] in 2uA unit.The real sample value in uA units should be calculated as follows:tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x74.16" size="0x0.16" />
	<field name="tx_bias_lane5" descr="(see above)" access="RO" offset="0x78.0" size="0x0.16" />
	<field name="tx_bias_lane4" descr="TX measured bias current on channel [i] in 2uA unit.The real sample value in uA units should be calculated as follows:tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x78.16" size="0x0.16" />
	<field name="tx_bias_lane7" descr="(see above)" access="RO" offset="0x7c.0" size="0x0.16" />
	<field name="tx_bias_lane6" descr="TX measured bias current on channel [i] in 2uA unit.The real sample value in uA units should be calculated as follows:tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x7c.16" size="0x0.16" />
	<field name="temperature_low_th" descr="Alarm low temperature threshold in 1/256 C" access="RO" offset="0x80.0" size="0x0.16" />
	<field name="temperature_high_th" descr="Alarm high temperature threshold in 1/256 C" access="RO" offset="0x80.16" size="0x0.16" />
	<field name="voltage_low_th" descr="Alarm low Voltage threshold in 100uV" access="RO" offset="0x84.0" size="0x0.16" />
	<field name="voltage_high_th" descr="Alarm high Voltage threshold in 100uV" access="RO" offset="0x84.16" size="0x0.16" />
	<field name="rx_power_low_th" descr="Alarm low RX Power threshold in dBm.Taking only from channel 0." access="RO" offset="0x88.0" size="0x0.16" />
	<field name="rx_power_high_th" descr="Alarm high RX Power threshold in dBm.Taking only from channel 0." access="RO" offset="0x88.16" size="0x0.16" />
	<field name="tx_power_low_th" descr="Alarm low TX Power threshold in dBm.Taking only from channel 0." access="RO" offset="0x8c.0" size="0x0.16" />
	<field name="tx_power_high_th" descr="Alarm high TX Power threshold in dBm.Taking only from channel 0." access="RO" offset="0x8c.16" size="0x0.16" />
	<field name="tx_bias_low_th" descr="Alarm low TX Bias current threshold in 2 uA.The real threshold value in uA units should be calculated as follows:tx_bias_high_th * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x90.0" size="0x0.16" />
	<field name="tx_bias_high_th" descr="Alarm high TX Bias current threshold in 2 uA.The real threshold value in uA units should be calculated as follows:tx_bias_high_th * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x90.16" size="0x0.16" />
	<field name="wavelength" descr="Nominal laser wavelength in nm" access="RO" offset="0x94.0" size="0x0.16" />
	<field name="smf_length" descr="SMF link lengthSFP per byte 14,15.QSFP per byte 142for CMIS based modules, per byte 132bit 9:8 - 00 length base in 1 km unitsbit 9:8 - 01 length base in 100m unitsbits 7:0 - length base" access="RO" offset="0x94.16" size="0x0.10" />
	<field name="rx_output_valid_cap" descr="when set, indicates rx_output_valid is supported by the module" access="RW" offset="0x94.26" size="0x0.1" />
	<field name="did_cap" descr="set in case of Linear Direct Drive module" access="RO" offset="0x94.27" size="0x0.1" />
	<field name="rx_power_type" descr="rx power measurement type0: OMA1: Average_power" access="RO" enum="OMA=0x0,Average_power=0x1" offset="0x94.28" size="0x0.1" />
	<field name="module_st" descr="Valid for CMIS modules only.Module state:0: reserved1: LowPwr_state2: PwrUp_state3: Ready_state4: PwrDn_state5: Fault_state" access="RO" enum="reserved=0x0,LowPwr_state=0x1,PwrUp_state=0x2,Ready_state=0x3,PwrDn_state=0x4,Fault_state=0x5" offset="0x94.29" size="0x0.3" />
	<field name="ib_compliance_code" descr="Byte 164 of SFF-8636For CMIS modules IB Protocols:Bit 0: SDRBit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x98.0" size="0x0.10" />
	<field name="tx_bias_scaling_factor" descr="Valid for CMIS modules only.This field is relevant for the following fields: tx_bias_lane[7:0],\;tx_bias_high_th and tx_bias_low_th.The value of the above fields should be multiplied according to the\;tx_bias_scaling_factor value.0: multiply_1x1: multiply_2x2: multiply_4x" access="RO" enum="multiply_1x=0x0,multiply_2x=0x1,multiply_4x=0x2" offset="0x98.10" size="0x0.2" />
	<field name="active_set_media_compliance_code" descr="Valid for CMIS modules only.According to current Active set, value of Module Media Interface byte" access="RO" offset="0x98.16" size="0x0.8" />
	<field name="active_set_host_compliance_code" descr="Valid for CMIS modules only.According to current Active set, value of Host Electrical Interface byte" access="RO" offset="0x98.24" size="0x0.8" />
	<field name="ib_width" descr="Bitmask of width of IB Protocols" access="RO" offset="0x9c.0" size="0x0.6" />
	<field name="monitor_cap_mask" descr="monitoring capabilities maskBit 0 - temperature monitoring implementedBit 1 - voltage monitoring implementedBit 2 - tx power monitoring implementedBit 3 - rx power monitoring implementedBit 4 - tx bias monitoring implemented" access="RO" offset="0x9c.8" size="0x0.8" />
	<field name="nbr100" descr="Nominal bit rate in units of 100Mb/s" access="RO" offset="0x9c.16" size="0x0.8" />
	<field name="nbr250" descr="Nominal bit rate in units of 250Mb/s" access="RO" offset="0x9c.24" size="0x0.8" />
	<field name="dp_st_lane" descr="DataPath state for lane&lt;i&gt;1: DPDeactivated2: DPInit3: DPDeinit4: DPActivated5: DPTxTurnOn6: DPTxTurnOff7: DPInitialized" access="RO" enum="DPDeactivated=0x1,DPInit=0x2,DPDeinit=0x3,DPActivated=0x4,DPTxTurnOn=0x5,DPTxTurnOff=0x6,DPInitialized=0x7" high_bound="7" low_bound="0" offset="0xa0.28" size="0x4.0" />
	<field name="length_om5" descr="OM5 fiber length supported in units of 2m" access="RO" offset="0xa4.0" size="0x0.8" />
	<field name="length_om4" descr="OM4 fiber length supported in units of 2mSFP in units of 10m" access="RO" offset="0xa4.8" size="0x0.8" />
	<field name="length_om3" descr="OM3 fiber length supported in units of 2mSFP in units of 10m" access="RO" offset="0xa4.16" size="0x0.8" />
	<field name="length_om2" descr="OM2 fiber length supported in units of 1mSFP in units of 10m" access="RO" offset="0xa4.24" size="0x0.8" />
	<field name="memory_map_rev" descr="memory map revision" access="RO" offset="0xa8.0" size="0x0.8" />
	<field name="wavelength_tolerance" descr="16-bit integer value for the laser wavelength tolerance in nm divided by\;200 (units of 0.005nm)." access="RO" offset="0xa8.8" size="0x0.16" />
	<field name="length_om1" descr="OM1 fiber length supported in units of 10m" access="RO" offset="0xa8.24" size="0x0.8" />
	<field name="memory_map_compliance" descr="memory map compliance in ASCII.SFF-8472 / SFF-8636/ CMIS" access="RO" offset="0xac.0" size="0x4.0" />
	<field name="date_code" descr="ASCII code for vendor’s date code.63:48- 2 digit for date code year, 00 = year 200047:32 - 2 digit for date code month.31:16 - 2 digit for day of the month code.15:0 - 2 digit LOT code." subnode="uint64" access="RO" offset="0xb0.0" size="0x8.0" />
	<field name="vendor_oui" descr="vendor oui" access="RO" offset="0xb8.0" size="0x0.24" />
	<field name="connector_type" descr="connector type based on SFF-8024" access="RO" offset="0xb8.24" size="0x0.8" />
	<field name="rx_output_valid" descr="Rx output status indication per lane" access="RO" offset="0xbc.0" size="0x0.8" />
	<field name="cable_attenuation_53g" descr="cable attenuation at 53GHz" access="RO" offset="0xbc.8" size="0x0.8" />
	<field name="tx_input_freq_sync" descr="Defines which Tx input lanes must be frequency synchronous.0: Tx_input_lanes_1_81: Tx_input_lanes_1_4_and_5-82: Tx_input_lanes_1_2_and_3_4_and_5_6_and_7_83: Lanes_may_be_asynchronous_in_frequency" access="RO" enum="Tx_input_lanes_1_8=0x0,Tx_input_lanes_1_4_and_5_8=0x1,Tx_input_lanes_1_2_and_3_4_and_5_6_and_7_8=0x2,Lanes_may_be_asynchronous_in_frequency=0x3" offset="0xbc.16" size="0x0.2" />
	<field name="event_logger_cap" descr="Module advertisement for NVDA event data collection logger" access="RO" offset="0xbc.19" size="0x0.1" />
	<field name="error_code" descr="Relevant for CMIS modules only.Error Code response for ControlSet configuration of DataPath.0x0: ConfigUndefined0x1: ConfigSuccess0x2: ConfigRejected0x3: ConfigRejectedInvalidAppSel0x4: ConfigRejectedInvalidDataPath0x5: ConfigRejectedInvalidSI0x6: ConfigRejectedLanesInUse0x7: ConfigRejectedPartialDataPath0xC: ConfigInProgress0xD: ConfigRejectedInvalid_VS_SI - NVIDIA vendor only" access="RO" enum="ConfigUndefined=0x0,ConfigSuccess=0x1,ConfigRejected=0x2,ConfigRejectedInvalidAppSel=0x3,ConfigRejectedInvalidDataPath=0x4,ConfigRejectedInvalidSI=0x5,ConfigRejectedLanesInUse=0x6,ConfigRejectedPartialDataPath=0x7,ConfigInProgress=0xc,ConfigRejectedInvalid_VS_SI=0xd" offset="0xc0.0" size="0x0.4" />
	<field name="cdr_vendor" descr="Relevant for CMIS modules only0x0: Unknown_or_no_CDR0x1: Inphy_gen1_polaris0x2: Inphy_gen2_Atlas0x3: Marvell_Spica_Plus0x4: Brdcm_Portofino_or_gemera0x5: Nvidia_ArcusE0x6: Marvell_nova2or_ara0x7: Macom_linear_equalizer0x8: Semec_linear_equalizer0x9: Marvel_linear_equalizer0xA: Marvel_spica_5nm0xB: luxic_linear_equalizer0xC: Broadcom_sian2_or_30xD: Arcus2" access="RO" enum="Unknown_or_no_CDR=0x0,Inphy_gen1_polaris=0x1,Inphy_gen2_Atlas=0x2,Marvell_Spica_Plus=0x3,Brdcm_Portofino_or_gemera=0x4,Nvidia_ArcusE=0x5,Marvell_nova2or_ara=0x6,Macom_linear_equalizer=0x7,Semec_linear_equalizer=0x8,Marvel_linear_equalizer=0x9,Marvel_spica_5nm=0xa,luxic_linear_equalizer=0xb,Broadcom_sian2_or_3=0xc,Arcus2=0xd" offset="0xc0.4" size="0x0.4" />
	<field name="oe_fuse_rev" descr="Fuse revition for Optical Engine. Relevant for Taipan" access="RO" offset="0xc0.13" size="0x0.3" />
	<field name="max_fiber_length" descr="Maximum length of allowed fiber in meters" access="RO" offset="0xc0.16" size="0x0.16" />
	<field name="els_laser2_fault_state" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;indicate the ELS laser fault:0: no_fault1: laser_fiber_contaminated2: laser_APC_fault3: laser_power_exceeded_allowed_range4: laser_power_subceeded_allowed_range5: laser_TEC_control_loop_fault6: laser_ramping_timeout_fault7: laser_power_tuning_fault" access="RO" enum="no_fault=0x0,laser_fiber_contaminated=0x1,laser_APC_fault=0x2,laser_power_exceeded_allowed_range=0x3,laser_power_subceeded_allowed_range=0x4,laser_TEC_control_loop_fault=0x5,laser_ramping_timeout_fault=0x6,laser_power_tuning_fault=0x7" offset="0xc4.10" size="0x0.3" />
	<field name="els_laser_fault_state" descr="Indicate the ELS laser fault.0: no_fault1: laser_fiber_contaminated2: laser_APC_fault3: laser_power_exceeded_allowed_range4: laser_power_subceeded_allowed_range5: laser_TEC_control_loop_fault6: laser_ramping_timeout_fault7: laser_power_tuning_fault" access="RO" enum="no_fault=0x0,laser_fiber_contaminated=0x1,laser_APC_fault=0x2,laser_power_exceeded_allowed_range=0x3,laser_power_subceeded_allowed_range=0x4,laser_TEC_control_loop_fault=0x5,laser_ramping_timeout_fault=0x6,laser_power_tuning_fault=0x7" offset="0xc4.13" size="0x0.3" />
	<field name="els2_oper_state" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;Indicates the ELS laser operative state:0: laser_init1: laser_active2: laser_active_with_fault3: laser_down4: laser_down_with_fault" access="RO" enum="laser_init=0x0,laser_active=0x1,laser_active_with_fault=0x2,laser_down=0x3,laser_down_with_fault=0x4" offset="0xc4.16" size="0x0.4" />
	<field name="els_oper_state" descr="Indicates the ELS laser operative state:0: laser_init1: laser_active2: laser_active_with_fault3: laser_down4: laser_down_with_fault" access="RO" enum="laser_init=0x0,laser_active=0x1,laser_active_with_fault=0x2,laser_down=0x3,laser_down_with_fault=0x4" offset="0xc4.20" size="0x0.4" />
	<field name="laser2_restriction" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;Each bit represent the ELS’s laser restriction. When restriction are on,\;the laser can operate only in restricted power mode, for the safety of\;the optical components. Restriction can be lifted only after fiber\;testing.0: laser2_restriction_on1: laser2_restriction_off" access="RO" enum="laser2_restriction_on=0x0,laser2_restriction_off=0x1" offset="0xc4.24" size="0x0.1" />
	<field name="laser_restriction" descr="Relevant for CPO product. Each bit represent the ELS’s laser\;restriction. When restriction are on, the laser can operate only in\;restricted power mode, for the safety of the optical components.\;Restriction can be lifted only after fiber testing.0: laser_restriction_on1: laser_restriction_off" access="RO" enum="laser_restriction_on=0x0,laser_restriction_off=0x1" offset="0xc4.25" size="0x0.1" />
	<field name="laser2_status" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;Each bit represent the ELS’s laser status CMIS name of field.0: laser2_off1: laser2_ramping2: laser2_on" access="RO" enum="laser2_off=0x0,laser2_ramping=0x1,laser2_on=0x2" offset="0xc4.26" size="0x0.2" />
	<field name="laser_status" descr="Relevant for CPO product. Each bit represent the ELS’s laser status CMIS\;name of field.0: laser_off1: laser_ramping2: laser_on" access="RO" enum="laser_off=0x0,laser_ramping=0x1,laser_on=0x2" offset="0xc4.28" size="0x0.2" />
	<field name="laser2_enabled" descr="Relevant for CPO ETH switches. when 8x port split is applied, this\;fields represent the ELS laser with the higher logical mapping index.\;Each bit represent the ELS’s laser.0: laser2_disabled1: laser2_enabled" access="RO" enum="laser2_disabled=0x0,laser2_enabled=0x1" offset="0xc4.30" size="0x0.1" />
	<field name="laser_enabled" descr="Relevant for CPO product. Each bit represent the ELS’s laser.0: laser_disabled1: laser_enabled" access="RO" enum="laser_disabled=0x0,laser_enabled=0x1" offset="0xc4.31" size="0x0.1" />
	<field name="module_production_test_revision_lsb" descr="Pluggable module production test version. Lower 32 bits." access="RO" offset="0xc8.0" size="0x4.0" />
	<field name="module_hw_revision_minor" descr="Module Hardware Revision Minor" access="RO" offset="0xcc.0" size="0x0.8" />
	<field name="module_hw_revision_major" descr="Module Hardware Revision Major" access="RO" offset="0xcc.8" size="0x0.8" />
	<field name="module_production_test_revision_msb" descr="Pluggable module production test version. Upper 8 bits." access="RO" offset="0xcc.24" size="0x0.8" />
</node>

<node name="pddr_monitor_opcode_ext" descr="" size="0x4.0" >
	<field name="monitor_opcode" descr="Status opcode:PHY FW indication (0 - 1023):0 - No issue observed1 - Port is close by command (see PAOS).2,3,4,38,39,60,69 - AN failure5,6,7,8, 62,63,64,65,66 - Link training failure.9,10,11,12,13 - Logical mismatch between link partners14 - Remote fault received15,42,17,48,49,52, - Bad signal integrity16,24-32 - Cable compliance code mismatch (protocol mismatch between\;cable and port) 23,22,19,18,50,55- internal error34,35 - Speed degradation56 - module_lanes_frequency_not_synced57 - signal not detected60 - no partner detected for long time68 - reserved70- link not healthy, BER doesn’t meet criteria128 - Troubleshooting in process1023- Info not availableMNG FW issues (1024 - 2047):1024 - Cable is unplugged1025 - Long Range for non Mellanox cable/module1026 - Bus stuck (I2C Data or clock shorted)1027 - Bad/unsupported EEPROM1028 - Part number list1029 - Unsupported cable1030 - Module temperature shutdown1031 - Shorted cable1032 - Power budget exceeded1033 - Management forced down the port1034 - Module is disabled by command1035 - System Power is Exceeded therefore the module is powered off.1036 - Module’s PMD type is not enabled (see PMTPS).1040 - pcie system power slot Exceeded1042 - Module state machine fault1043,1044,1045,1046 - Module’s stamping speed degeneration1047, 1048 - Modules DataPath FSM fault1050, 1051, 1052, 1053- Module Boot Error1054 - Module Forced to Low Power by command1055 - ELS laser fiber is contaminated1056 - ELS laser power control failure1057 - ELS unplugged1058 - ELS laser rampling timeout failure1059 - ELS laser power exceeded allowed power range1060 - ELS laser power subceeded allowed power range1061 - ELS TEC control loop failure1062 - ELS laser power tuning failure1063 - ELS laser wavelength tuning failure1064 - ELS laser health indication - high path loss1065 - ELS laser high loss power drop" access="RW" offset="0x0.0" size="0x0.16" />
</node>

<node name="pddr_operation_info_page_cable_proto_cap_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_cable_cap_eth_ext" descr="" subnode="pddr_cable_cap_eth_ext" access="RW" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="pddr_cable_cap_ib_ext" descr="" subnode="pddr_cable_cap_ib_ext" access="RW" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="pddr_cable_cap_nvlink_ext" descr="" subnode="pddr_cable_cap_nvlink_ext" access="RW" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_core_to_phy_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_c2p_link_enabled_eth_ext" descr="" subnode="pddr_c2p_link_enabled_eth_ext" access="RW" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="pddr_c2p_link_enabled_ib_ext" descr="" subnode="pddr_c2p_link_enabled_ib_ext" access="RW" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="pddr_c2p_link_enabled_nvlink_ext" descr="" subnode="pddr_c2p_link_enabled_nvlink_ext" access="RW" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_ext" descr="" size="0xf8.0" >
	<field name="neg_mode_active" descr="0: protocol_was_not_negotiated - (force mode)1: MLPN_rev0_negotiated2: CL73_Ethernet_negotiated3: Protocol_according_to_Parallel_detect - (remote port in force\;mode)4: Standard_IB_negotiated" access="RO" enum="protocol_was_not_negotiated=0x0,MLPN_rev0_negotiated=0x1,CL73_Ethernet_negotiated=0x2,Protocol_according_to_Parallel_detect=0x3,Standard_IB_negotiated=0x4" offset="0x0.16" size="0x0.4" />
	<field name="proto_active" descr="Active protocol:Bit 0: InfiniBandBit 2: EthernetBit 3: NVLink" access="RO" enum="InfiniBand=0x1,Ethernet=0x4,NVLink=0x8" offset="0x0.20" size="0x0.4" />
	<field name="resilink_fec_ind" descr="Valid only for resilink link is operational, otherwise ignored.When cleared, fec_mode_active will represent the Ethernet equivalent FEC\;of the resilink protocol.When set, fec_mode_active will represent the Resilink FEC protocol" access="INDEX" offset="0x0.28" size="0x0.1" />
	<field name="ib_phy_fsm_state" descr="FW IB state machine:0x0: IB_AN_FSM_DISABLED0x1: IB_AN_FSM_INITIALY0x2: IB_AN_FSM_RCVR_CFG0x3: IB_AN_FSM_CFG_TEST0x4: IB_AN_FSM_WAIT_RMT_TEST0x5: IB_AN_FSM_WAIT_CFG_ENHANCED0x6: IB_AN_FSM_CFG_IDLE0x7: IB_AN_FSM_LINK_UP0x8: IB_AN_FSM_POLLING" access="RO" enum="IB_AN_FSM_DISABLED=0x0,IB_AN_FSM_INITIALY=0x1,IB_AN_FSM_RCVR_CFG=0x2,IB_AN_FSM_CFG_TEST=0x3,IB_AN_FSM_WAIT_RMT_TEST=0x4,IB_AN_FSM_WAIT_CFG_ENHANCED=0x5,IB_AN_FSM_CFG_IDLE=0x6,IB_AN_FSM_LINK_UP=0x7,IB_AN_FSM_POLLING=0x8" offset="0x4.8" size="0x0.8" />
	<field name="eth_an_fsm_state" descr="Ethernet (CL73) Auto-negotiation FSM state:0x0: ETH_AN_FSM_ENABLE0x1: ETH_AN_FSM_XMIT_DISABLE0x2: ETH_AN_FSM_ABILITY_DETECT0x3: ETH_AN_FSM_ACK_DETECT0x4: ETH_AN_FSM_COMPLETE_ACK0x5: ETH_AN_FSM_AN_GOOD_CHECK0x6: ETH_AN_FSM_AN_GOOD0x7: ETH_AN_FSM_NEXT_PAGE_WAIT" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="phy_mngr_fsm_state" descr="FW Phy Manager FSM state:0: Disabled1: Open_port2: Polling3: Active4: Close_port5: Phy_up6: Sleep7: Rx_disable8: Signal_detect9: Receiver_detect10: Sync_peer11: Negotiation12: Training13: SubFSM_active14: Protocol_Detect15: Unkown16: Reserved17: Waiting_state" access="RO" enum="Disabled=0x0,Open_port=0x1,Polling=0x2,Active=0x3,Close_port=0x4,Phy_up=0x5,Sleep=0x6,Rx_disable=0x7,Signal_detect=0x8,Receiver_detect=0x9,Sync_peer=0xa,Negotiation=0xb,Training=0xc,SubFSM_active=0xd,Protocol_Detect=0xe,Unkown=0xf,Reserved=0x10,Waiting_state=0x11" offset="0x4.24" size="0x0.8" />
	<field name="phy_manager_link_enabled" descr="For IB:\;PDDR - Phy Manager Link Enabled IB LayoutFor Ethernet:\;PDDR - Phy Manager Link Enabled Eth LayoutFor NVLink:\;PDDR - Phy Manager Link Enable NVLink Layout" subnode="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" access="RO" offset="0x8.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="core_to_phy_link_enabled" descr="For IB:\;PDDR - Core2phy Link Enabled IB LayoutFor Ethernet:\;PDDR - Core2phy Link Enabled Eth LayoutFor NVLink:\;PDDR - Core2phy Link Enabled NVLink Layout" subnode="pddr_operation_info_page_core_to_phy_link_enabled_auto_ext" access="RO" offset="0xc.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="cable_proto_cap" descr="For IB:\;PDDR - Cable Cap IB LayoutFor Ethernet:\;PDDR - Cable Cap Eth LayoutFor NVLink:\;PDDR - Cable Cap NVLink Layout" subnode="pddr_operation_info_page_cable_proto_cap_auto_ext" access="RO" offset="0x10.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="link_active" descr="For IB:\;PDDR - Link Active IB LayoutFor Ethernet:\;PDDR - Link Active Eth LayoutFor NVLink:\;PDDR - Link Active NVLink Layout" subnode="pddr_operation_info_page_link_active_auto_ext" access="RO" offset="0x14.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="loopback_mode" descr="0: No_loopback_active1: Phy_remote_loopback2: Phy_local_loopback -When set the port’s egress traffic is looped\;back to the receiver and the port transmitter is disabled.4: External_local_loopback -Enables the port’s transmitter to link\;with the port’s receiver using an external loopback connector." access="RO" enum="No_loopback_active=0x0,Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4" offset="0x18.0" size="0x0.12" />
	<field name="pri_or_sec" descr="Indicates for Mode B links if the port was chosen as primary or\;secondary during linkup.0: Not_supported_or_not_chosen_yet.1: Primary2: Secondary" access="RO" enum="Not_supported_or_not_chosen_yet=0x0,Primary=0x1,Secondary=0x2" offset="0x18.14" size="0x0.2" />
	<field name="fec_mode_request" descr="FEC mode request.See ." access="RO" offset="0x1c.0" size="0x0.16" />
	<field name="fec_mode_active" descr="FEC mode active0: No_FEC1: Firecode_FEC2: Standard_RS_FEC - RS(528,514)3: Standard_LL_RS_FEC - RS(271,257)4: Interleaved_Quad_RS_FEC - (544,514)   Quad_KP4_FEC5: Interleaved_Quad_RS_FEC_PLR - 546,516) Quad_KP4_FEC6: Interleaved_Standard_RS-FEC - (544,514)7: Standard_RS_KP4_FEC - (544,514)8: Interleaved_Octet_RS_FEC_PLR -(546,516) Octet_KP4_FEC9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - (272,257+1)11: Interleaved_Standard_RS_FEC_PLR - (544,514)12: RS-FEC - (544,514) + PLR- [Internal]13: LL-FEC - (271,257) + PLR- [Internal]14: Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]15: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]16: Interleaved_Double_RS_Half_KP4_FEC_PLR - (288,258)17: Interleaved_Quad_RS_Half_KP4_FEC_PLR - (288,258)18: Interleaved_Octet_RS_Half_KP4_FEC_PLR - (288,258)" access="RO" enum="No_FEC=0x0,Firecode_FEC=0x1,Standard_RS_FEC=0x2,Standard_LL_RS_FEC=0x3,Interleaved_Quad_RS_FEC=0x4,Interleaved_Quad_RS_FEC_PLR=0x5,Interleaved_Standard_RS_FEC=0x6,Standard_RS_KP4_FEC=0x7,Interleaved_Octet_RS_FEC_PLR=0x8,Ethernet_Consortium_LL_50G_RS_FEC=0x9,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC=0xa,Interleaved_Standard_RS_FEC_PLR=0xb,RS_FEC=0xc,LL_FEC=0xd,Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xe,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xf,Interleaved_Double_RS_Half_KP4_FEC_PLR=0x10,Interleaved_Quad_RS_Half_KP4_FEC_PLR=0x11,Interleaved_Octet_RS_Half_KP4_FEC_PLR=0x12" offset="0x1c.16" size="0x0.16" />
	<field name="eth_100g_fec_support" descr="FEC 100G (25Gb/s per lane) supported FEC include override masking,\;should reflect current phy configuration after link is upBit 0 - No FECBit 2 - Standard RS-FEC - RS(528,514)" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="eth_25g_50g_fec_support" descr="FEC 25G/50G (25Gb/s per lane) supported FEC include override masking,\;should reflect current phy configuration after link is upBit 0 - No FECBit 1 - Firecode FECBit 2 - Standard RS-FEC - RS(528,514)" access="RO" offset="0x20.4" size="0x0.4" />
	<field name="profile_fec_in_use" descr="The profile that has been selected:Bit 0 - IB spec / legacy (See profiles description)Bit 1 - internal ports (Backplane)Bit 2 - Passive copper - ShortBit 3 - Passive copper - MediumBit 4 - Passive copper - LongBit 5 - Active optics / copper short reach (&lt;20m)Bit 6 - Optics long reach (&gt;20m)Bit 7 - NO-FECBit 8 - FEC-ON" access="RO" offset="0x20.16" size="0x0.16" />
	<field name="pd_link_enabled" descr="For IB:\;PDDR - Parallel Detect Link Enabled IB LayoutFor Ethernet:\;PDDR - Parallel Detect Link Enabled Eth Layout" subnode="pddr_operation_info_page_pd_link_enabled_auto_ext" access="RO" offset="0x24.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="phy_hst_link_enabled" descr="For IB:\;PDDR - HST Link Enabled IB LayoutFor Ethernet:\;PDDR - HST Link Enabled Eth LayoutFor NVLink:\;PDDR - HST Link Enabled NVLink Layout" subnode="pddr_operation_info_page_phy_hst_link_enabled_auto_ext" access="RO" offset="0x28.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="eth_an_link_enabled" descr="PDDR - ETH AN Link Enabled Eth Layout" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="link_health" descr="0: N/A - not supported or not enabled1: Attention2: Healthy" access="RO" offset="0x38.0" size="0x0.4" />
	<field name="attention_trigger" descr="Indicates the reason that caused the link health status to transition to\;Attention. This field is sticky - it retains its value until the link\;health status is cleared by the next link-up event resets it. Valid only\;when link_health = 1 (Attention)." access="RO" offset="0x38.5" size="0x0.8" />
	<field name="test_mode_fsm_state" descr="Test mode FSM state exposure is supported only if PCAM.feature_cap_mask\;bit 120 is set.Mode B links test mode FSM0: Disable - this state is shared by Mode A links and Mode B links\;test mode FSM1: Open_lane2: Idle_mode_b3: Close_lane- Mode A links test mode FSM4: Receiver_detect5: Idle_mode_a6: Signal_detect7: Auto_fix_reversal_polarity8: Tuning_in_progress" access="RO" enum="Disable=0x0,Open_lane=0x1,Idle_mode_b=0x2,Close_lane=0x3,Receiver_detect=0x4,Idle_mode_a=0x5,Signal_detect=0x6,Auto_fix_reversal_polarity=0x7,Tuning_in_progress=0x8" offset="0x38.24" size="0x0.8" />
	<field name="local_host_class" descr="Local host class - Insertion loss0: Unspecified1: Host nominal (HN) - 4.45 to 13.95 dB2: Host low (HL) - 4.45 to 8.95 dB3: Host high (HH) - 4.55 to 18.5 dB4-7: Reserved" access="RO" offset="0x3c.0" size="0x0.3" />
	<field name="remote_host_class" descr="Remote host class - Insertion loss0: Unspecified1: Host nominal (HN) - 4.45 to 13.95 dB2: Host low (HL) - 4.45 to 8.95 dB3: Host high (HH) - 4.55 to 18.5 dB4-7: Reserved" access="RO" offset="0x3c.4" size="0x0.3" />
	<field name="channel_diff_loss" descr="Channel differential loss in dB. The highest loss between receivers and\;transmitters." access="RO" offset="0x3c.8" size="0x0.5" />
</node>

<node name="pddr_operation_info_page_link_active_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_link_active_eth_ext" descr="" subnode="pddr_link_active_eth_ext" access="RW" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="pddr_link_active_ib_ext" descr="" subnode="pddr_link_active_ib_ext" access="RW" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="pddr_link_active_nvlink_ext" descr="" subnode="pddr_link_active_nvlink_ext" access="RW" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_pd_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pd_link_eth_enabled_ext" descr="" subnode="pd_link_eth_enabled_ext" access="RW" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="pd_link_ib_enabled_ext" descr="" subnode="pd_link_ib_enabled_ext" access="RW" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_phy_hst_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="hst_link_eth_enabled_ext" descr="" subnode="hst_link_eth_enabled_ext" access="RW" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="hst_link_ib_enabled_ext" descr="" subnode="hst_link_ib_enabled_ext" access="RW" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="hst_link_nvlink_enabled_ext" descr="" subnode="hst_link_nvlink_enabled_ext" access="RW" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_phy_manager_link_enabled_eth_ext" descr="" subnode="pddr_phy_manager_link_enabled_eth_ext" access="RW" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="pddr_phy_manager_link_enabled_ib_ext" descr="" subnode="pddr_phy_manager_link_enabled_ib_ext" access="RW" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="pddr_phy_manager_link_enabled_nvlink_ext" descr="" subnode="pddr_phy_manager_link_enabled_nvlink_ext" access="RW" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pddr_phy_info_page_ext" descr="" size="0xf8.0" >
	<field name="port_notifications" descr="Port notifications bit maskBit 0 - Link partner advertised capabilitiesBit 1 - Speed degradation" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="negotiation_mask" descr="Bit 0: eth_base_pageBit 1: ib_base_pageBit 2: ib_base_page_rev2 - XDR onwardsBit 3: ConsortiumBit 4: MLPN_rev0Bit 5: MLPN_rev1Bit 6: NLPN_rev2" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="remote_device_type" descr="Remote device type:0 - Unknown (3rd party, Force, legacy MLPN)1 - CX42 - CX4_LX3 - CX54 - CX5_LX5 - CX66 - CX6_LX7 - CX6_DX8 - CX79 - Bluefield-210 - CX811 - Bluefield-312 - CX913 - CX1014-99 Reserved100 - SwitchIB101 - Spectrum102 - SwitchIB-2103 - Quantum104 - Spectrum-2105 - Spectrum-3106 - Quantum-2107 - Spectrum-4108 -Quantum-3109 - Quantum-4112 - Quantum-5113 - Quantum-6114 - Spectrum-7115-199 -Reserved200 - GB100 (OR 102/200)201 - GR100202 - GR150203 - Feinmann204 - GB10 - fusion205 - Rubin - fusion206-255 - Reserved" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="lp_ib_revision" descr="Link partner IB TS revision" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="ib_revision" descr="IB TS revision" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="num_of_negotiation_attempts" descr="Negotiation attempt counter" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="phy_manager_disable_mask" descr="Phy manager disable bit mask:Bit 0 - Module not present (module absence/cage power off)Bit 1 - PAOS commandBit 2 - MAD IB PortInfo down commandBit 3 - Long range cable (Non Mellanox)Bit 4 - Verification commandBit 5 - ekey commandBit 6 - High power - cable require higher power than allowed.Bit 7 - Unknown Identifier (Module)Bit 8 - PAOS up onceBit 9 - Stamping failureBit 10 - Calibration not doneBit 11 - Module LockingBit 12 - Cable lockingBit 13 - Power budget exceededBit 14 - Interrupt Event / Module TempBit 15 - TEC flow / module bring up issueBit 17 - SerDes task abort failedBit 18 - Default state is disable" access="RO" offset="0x8.0" size="0x0.24" />
	<field name="hw_link_phy_state" descr="IBP HW FSM Reflected State:0x10: sleeping_delay0x11: sleeping_quiet0x20: polling_active0x21: polling_quiet0x30: disable0x31: update_retimer0x40: config_debounce0x41: config_receiver0x42: config_wait_remote0x43: config_tx_reverse_lanes0x44: config_enhanced0x45: config_test0x46: confg_wait_remote_test0x47: config_wait_cfg_enhanced0x48: config_idle0x50: linkup0x51: Linkup_Tx_Idle0x52: Linkup_Tx_Empty-Recovery0x60: recover_retrain0x61: recover_wait_remote0x62: recover_idle0x63: Local_down_cmd0x64: Remote_down_cmd0x65: uphy_recovery_send_ts10x66: uphy_recovery_send_pam20x67: uphy_recovery_send_pam40x68: uphy_recovery_peq0x70: test- Force Modes0x80: Force_send_ts1 - command may be given only on disable state0x90: Force_send_ts20xA0: Force_Sent_Idle0xB0: Force_send_ts_Mlnx0xC0: Force_send_ts30xD0: Force_LinkUp- L10xE0: Go_To_Quiet0xE1: Retimer_Align0xE2: Quiet_Entry0xE3: Quiet0xE4: Wake0xE5: Wake_Tx_Sleep00xE6: Send_Announce0xE7: Tx_HS0xE8: Wait_For_Cdr_Lock" access="RO" enum="sleeping_delay=0x10,sleeping_quiet=0x11,polling_active=0x20,polling_quiet=0x21,disable=0x30,update_retimer=0x31,config_debounce=0x40,config_receiver=0x41,config_wait_remote=0x42,config_tx_reverse_lanes=0x43,config_enhanced=0x44,config_test=0x45,confg_wait_remote_test=0x46,config_wait_cfg_enhanced=0x47,config_idle=0x48,linkup=0x50,Linkup_Tx_Idle=0x51,Linkup_Tx_Empty=0x52,recover_retrain=0x60,recover_wait_remote=0x61,recover_idle=0x62,Local_down_cmd=0x63,Remote_down_cmd=0x64,uphy_recovery_send_ts1=0x65,uphy_recovery_send_pam2=0x66,uphy_recovery_send_pam4=0x67,uphy_recovery_peq=0x68,test=0x70,Force_send_ts1=0x80,Force_send_ts2=0x90,Force_Sent_Idle=0xa0,Force_send_ts_Mlnx=0xb0,Force_send_ts3=0xc0,Force_LinkUp=0xd0,Go_To_Quiet=0xe0,Retimer_Align=0xe1,Quiet_Entry=0xe2,Quiet=0xe3,Wake=0xe4,Wake_Tx_Sleep0=0xe5,Send_Announce=0xe6,Tx_HS=0xe7,Wait_For_Cdr_Lock=0xe8" offset="0x8.24" size="0x0.8" />
	<field name="pcs_phy_state" descr="PCS HW state:Bits 0-7: Block lock (one bit per lane)Bits 8-15: AM lock (one bit per lane)Bits 16-23: FEC lock (one bit per lane)Bits 24: Align_statusBits 25: Hi_BERBits 26: Hi_SER" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="lp_proto_enabled" descr="IB ports:Link partner advertised speeds (first TS3)See ib_link_speed_enabled encoding.Ethernet ports:Link partner advertised Ethernet protocols active state: see\;PTYS.lp_advertise" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="lp_fec_mode_request" descr="Reserved when negotiation wasn’t performed according to\;port_notifications.Link partner advertised capabilities value.Advertised link partner FEC mode request" access="RO" offset="0x14.0" size="0x0.16" />
	<field name="lp_fec_mode_support" descr="Reserved when negotiation wasn’t performed according to\;port_notifications.Link partner advertised capabilities value.Advertised link partner FEC mode supportBit 0 - No FECBit 1 - Firecode FECBit 2 - Standard RS-FEC - RS(528,514)Bit 3 - Standard LL RS-FEC - RS(271,257)Bit 4 - Mellanox Strong RS-FEC - RS(277,257)Bit 5 - Mellanox LL RS-FEC - RS(163,155)Bit 6 - ReservedBit 7 - Standard RS-FEC (544,514)Bit 8 - Zero Latency FECBit 12 - RS-FEC (544,514) + PLRBit 13 - LL-FEC (271,257) + PLR" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="ib_last_link_down_reason" descr="Bit 0 - heartbeat_ack_receivedBit 1 - heartbeat_send_receivedBit 2 - heartbeat_errBit 3 - tx_width_reduction_done_1xBit 4 - tx_width_reduction_done_fullBit 5 - rx_width_reduction_done_1xBit 6 - rx_width_reduction_done_fullBit 7 - width_reduction_timeoutBit 8 - ibl_link_retrainBit 9 - rx_comskp_timeoutBit 10 - fifo_full_errBit 11 - ts_at_linkupBit 12 - minor_threshold_reachedBit 13 - link_failBit 14 - rx_eb_full_rBit 15 - rx_8_10_lane_errBit 16 - llr_link_retrain_setBit 17 - fc_timeoutBit 18 - phy_errorBit 19 - lli_errBit 20 - excessive_buffer_errBit 21 - remote_initBit 22 - plr_retry_expiredBit 23 - port_didnt_exit_plr_syncBit 24 - eq_failedBits 31-24 - Reserved" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="eth_last_link_down_lane" descr="Bit 0 - block_lock_failedBit 1 - skip_detectedBit 2 - fec_sync_failedBit 3 - fec_block_syncBit 4 - fec_block_sync_lost" access="RO" high_bound="3" low_bound="0" offset="0x1c.24" size="0x4.0" />
	<field name="speed_deg_db" descr="Bit 0 - Speed degradation database ValidBit 1 - Speed degradation SerDes Rx database validBIts 3-2 - reservedBit 4 - rx_reversalBit 5 - tx_reversalBit 7-6 - reservedBits 11:8 - failed_qdr/fdr10 - bit per lane.Bits 15:12 - failed_fdr - bit per lane.Bits 19:16- failed_edr - bit per lane.Bits 24:20 - peer_failed_testBits 26-25 - reservedBit 27 - first_test_speed" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="degrade_grade_lane0" descr="Valid only when port_notifications.Speed degradation is asserted" access="RO" offset="0x28.0" size="0x0.24" />
	<field name="degrade_grade_lane1" descr="(see above)" access="RO" offset="0x2c.0" size="0x0.24" />
	<field name="degrade_grade_lane2" descr="(see above)" access="RO" offset="0x30.0" size="0x0.24" />
	<field name="degrade_grade_lane3" descr="(see above)" access="RO" offset="0x34.0" size="0x0.24" />
	<field name="num_of_presets_tested_lane7" descr="(see above)" access="RO" offset="0x38.0" size="0x0.5" />
	<field name="num_of_presets_tested_lane6" descr="(see above)" access="RO" offset="0x38.8" size="0x0.5" />
	<field name="num_of_presets_tested_lane5" descr="(see above)" access="RO" offset="0x38.16" size="0x0.5" />
	<field name="num_of_presets_tested_lane4" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x38.24" size="0x0.5" />
	<field name="kr_startup_debug_indications_5" descr="(see above)" access="RO" offset="0x3c.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_4" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:Bit 0: Local_frame_lockBit 1: Remote_frame_lockBit 2: Local_Frame_lock_timer_expiredBit 3: Remote_Frame_lock_timer_expiredBit 4: Local_receiver_readyBit 5: Remote_receiver_readyBit 6: max_wait_timer_expiredBit 7: Wait_timer_doneBit 8: Hold_off_timer_expiredBit 9: link_fail_inhibit_timer_expired" access="RO" enum="Local_frame_lock=0x1,Remote_frame_lock=0x2,Local_Frame_lock_timer_expired=0x4,Remote_Frame_lock_timer_expired=0x8,Local_receiver_ready=0x10,Remote_receiver_ready=0x20,max_wait_timer_expired=0x40,Wait_timer_done=0x80,Hold_off_timer_expired=0x100,link_fail_inhibit_timer_expired=0x200" offset="0x3c.16" size="0x0.16" />
	<field name="kr_startup_debug_indications_7" descr="(see above)" access="RO" offset="0x40.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_6" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:Bit 0: Local_frame_lockBit 1: Remote_frame_lockBit 2: Local_Frame_lock_timer_expiredBit 3: Remote_Frame_lock_timer_expiredBit 4: Local_receiver_readyBit 5: Remote_receiver_readyBit 6: max_wait_timer_expiredBit 7: Wait_timer_doneBit 8: Hold_off_timer_expiredBit 9: link_fail_inhibit_timer_expired" access="RO" enum="Local_frame_lock=0x1,Remote_frame_lock=0x2,Local_Frame_lock_timer_expired=0x4,Remote_Frame_lock_timer_expired=0x8,Local_receiver_ready=0x10,Remote_receiver_ready=0x20,max_wait_timer_expired=0x40,Wait_timer_done=0x80,Hold_off_timer_expired=0x100,link_fail_inhibit_timer_expired=0x200" offset="0x40.16" size="0x0.16" />
	<field name="num_of_presets_tested_lane3" descr="(see above)" access="RO" offset="0x44.0" size="0x0.5" />
	<field name="num_of_presets_tested_lane2" descr="(see above)" access="RO" offset="0x44.8" size="0x0.5" />
	<field name="num_of_presets_tested_lane1" descr="(see above)" access="RO" offset="0x44.16" size="0x0.5" />
	<field name="num_of_presets_tested_lane0" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x44.24" size="0x0.5" />
	<field name="kr_startup_fsm_lane" descr="Per lane KR startup state:0: KR_FSM_INITIALIZE1: KR_FSM_SEND_TRAINING2: KR_FSM_TRAIN_LOCAL_TX3: KR_FSM_TRAIN_LOCAL_RX4: KR_FSM_TRAIN_REMOTE5: KR_FSM_LINK_READY6: KR_FSM_SEND_DATA7: KR_FSM_NVLT8: KR_ABORT9: KR_TIMEOUT10: KR_FSM_IN_IDLE" access="RO" enum="KR_FSM_INITIALIZE=0x0,KR_FSM_SEND_TRAINING=0x1,KR_FSM_TRAIN_LOCAL_TX=0x2,KR_FSM_TRAIN_LOCAL_RX=0x3,KR_FSM_TRAIN_REMOTE=0x4,KR_FSM_LINK_READY=0x5,KR_FSM_SEND_DATA=0x6,KR_FSM_NVLT=0x7,KR_ABORT=0x8,KR_TIMEOUT=0x9,KR_FSM_IN_IDLE=0xa" high_bound="7" low_bound="0" offset="0x48.24" size="0x8.0" />
	<field name="eth_an_debug_indication" descr="eth_an_debug bit mask:Bit 0 - Force link upBit 1 - No HCDBit 2 - Entered ACK_detectBit 3 - Entered GoodBit 4 - Entered Good_CheckBit 5 - Entered Extra_tuneBit 6 - Entered Fix_ReversalsBit 7 - Entered Next_PageBit 8 - Entered Sub-FSM FailBit 9 - Tuning timeoutBit 10 - No markers detected (during Good check)Bit 11 - Do KR-startupBits 15:18 - KR startup failure mask" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="ib_phy_fsm_state_trace" descr="FW IB state machine:HDR GenBit 0 - entered IB_AN_FSM_DISABLEDBit 1 - entered IB_AN_FSM_INITIALYBit 2 - entered IB_AN_FSM_RCVR_CFGBit 3 - entered IB_AN_FSM_CFG_TESTBit 4 - entered IB_AN_FSM_WAIT_RMT_TESTBit 5 - entered IB_AN_FSM_WAIT_CFG_ENHANCEDBit 6 - entered IB_AN_FSM_CFG_IDLEBit 7 - entered IB_AN_FSM_LINK_UPBit 8 - Failed from CFG_IDLENDR Gen:Bit 0 - entered IB_AN_FSM_DISABLEDBit 1 - entered IB_AN_FSM_POLLINGBit 2 - entered IB_AN_FSM_INITIALYBit 3 - entered IB_AN_FSM_CFG_TESTBit 4 - entered IB_AN_FSM_WAIT_RMT_TESTBit 5 - entered IB_AN_FSM_WAIT_CFG_ENHANCEDBit 6 - entered IB_AN_FSM_CFG_IDLEBit 7 - entered IB_AN_FSM_SYNC_CHECKBit 8 - entered IB_AN_FSM_LINK_UPBit 9 - Failed from CFG_IDLEBit 10 - peer requested KRBit 11 - speed degradation needed - “best_grade” didn’t reach threshold" access="RO" offset="0x54.0" size="0x0.16" />
	<field name="rounds_waited_for_peer_to_end_test" descr="" access="RO" offset="0x54.16" size="0x0.5" />
	<field name="eth_an_watchdog_cnt" descr="counts ETH Watchdog was performed (and closed the IB fsm)." access="RO" offset="0x54.21" size="0x0.2" />
	<field name="fall_from_cfg_idle_cdr_cnt" descr="count falls from Cfg_idle (before linkup) due cdr not lock" access="RO" offset="0x54.23" size="0x0.3" />
	<field name="fall_from_cfg_idle_cnt" descr="count falls from Cfg_idle (before linkup) due amps lock on PLU" access="RO" offset="0x54.26" size="0x0.3" />
	<field name="cdr_not_locked_cnt" descr="count the cdr not locked after EQ" access="RO" offset="0x54.29" size="0x0.3" />
	<field name="kr_startup_debug_indications_1" descr="(see above)" access="RO" offset="0x58.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_0" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:Bit 0: Local_frame_lockBit 1: Remote_frame_lockBit 2: Local_Frame_lock_timer_expiredBit 3: Remote_Frame_lock_timer_expiredBit 4: Local_receiver_readyBit 5: Remote_receiver_readyBit 6: max_wait_timer_expiredBit 7: Wait_timer_doneBit 8: Hold_off_timer_expiredBit 9: link_fail_inhibit_timer_expired" access="RO" enum="Local_frame_lock=0x1,Remote_frame_lock=0x2,Local_Frame_lock_timer_expired=0x4,Remote_Frame_lock_timer_expired=0x8,Local_receiver_ready=0x10,Remote_receiver_ready=0x20,max_wait_timer_expired=0x40,Wait_timer_done=0x80,Hold_off_timer_expired=0x100,link_fail_inhibit_timer_expired=0x200" offset="0x58.16" size="0x0.16" />
	<field name="kr_startup_debug_indications_3" descr="(see above)" access="RO" offset="0x5c.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_2" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:Bit 0: Local_frame_lockBit 1: Remote_frame_lockBit 2: Local_Frame_lock_timer_expiredBit 3: Remote_Frame_lock_timer_expiredBit 4: Local_receiver_readyBit 5: Remote_receiver_readyBit 6: max_wait_timer_expiredBit 7: Wait_timer_doneBit 8: Hold_off_timer_expiredBit 9: link_fail_inhibit_timer_expired" access="RO" enum="Local_frame_lock=0x1,Remote_frame_lock=0x2,Local_Frame_lock_timer_expired=0x4,Remote_Frame_lock_timer_expired=0x8,Local_receiver_ready=0x10,Remote_receiver_ready=0x20,max_wait_timer_expired=0x40,Wait_timer_done=0x80,Hold_off_timer_expired=0x100,link_fail_inhibit_timer_expired=0x200" offset="0x5c.16" size="0x0.16" />
	<field name="tx_tuning_stages_lane" descr="Stages mask per lane:Bit 0: Single_preset_stageBit 1: multiple_preset_stageBit 2: LMS" access="RO" enum="Single_preset_stage=0x1,multiple_preset_stage=0x2,LMS=0x4" high_bound="7" low_bound="0" offset="0x60.28" size="0x4.0" />
	<field name="plu_tx_pwrup" descr="(see above)" access="RO" offset="0x64.0" size="0x0.8" />
	<field name="plu_rx_pwrup" descr="PLU power up status per lane" access="RO" offset="0x64.8" size="0x0.8" />
	<field name="plu_tx_polarity" descr="(see above)" access="RO" offset="0x64.16" size="0x0.8" />
	<field name="plu_rx_polarity" descr="Configured PLU polarity per lane" access="RO" offset="0x64.24" size="0x0.8" />
	<field name="irisc_status" descr="" access="RO" offset="0x68.0" size="0x0.4" />
	<field name="ib_cfg_delay_timeout" descr="0 - Default as defined in IB Spec.1 - Override default with 64msec timeout for all speeds.2 - Reserved3 - Reserved" access="RO" offset="0x68.4" size="0x0.2" />
	<field name="sd_valid" descr="when set, signal_detected has valid value." access="RO" offset="0x68.6" size="0x0.1" />
	<field name="plu_tx_speed" descr="(see above)" access="RO" offset="0x68.8" size="0x0.4" />
	<field name="plu_rx_speed" descr="PLU configured speed:" access="RO" offset="0x68.12" size="0x0.4" />
	<field name="signal_detected" descr="valid only when sd_valid is setBitmask per lane.When set signal has been detected on the lane" access="RO" offset="0x68.24" size="0x0.8" />
	<field name="stamping_reason" descr="Bit 0: com_codes_is_zeroBit 1: rx_cdr_check_force_modeBit 2: com_code_complianceBit 3: eth_56g_stampedBit 4: non_mlx_qsfp_transceiverBit 5: non_mlx_sfp_transceiverBit 6: ib_comp_codesBit 7: edr_compBit 8: fdr_comp" access="RO" enum="com_codes_is_zero=0x1,rx_cdr_check_force_mode=0x2,com_code_compliance=0x4,eth_56g_stamped=0x8,non_mlx_qsfp_transceiver=0x10,non_mlx_sfp_transceiver=0x20,ib_comp_codes=0x40,edr_comp=0x80,fdr_comp=0x100" offset="0x6c.0" size="0x4.0" />
	<field name="kr_frame_lock_tuning_failure_events_count" descr="Number of times that fast tuning (50ms) for KR lock failed to achieve\;frame lock." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="kr_full_tuning_failure_count" descr="Number of times that full tuning (0.5sec/3sec) for KR full tuning flow\;failed to achieve desire SI performance" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="pm_debug_indication" descr="Bit 0: phy_test_modeBit 1: force_mode_en" access="RO" enum="phy_test_mode=0x1,force_mode_en=0x2" offset="0x78.0" size="0x0.16" />
	<field name="ib_debug_indication" descr="Bit 0: cause_plr_tx_max_outstanding_cells" access="RO" enum="cause_plr_tx_max_outstanding_cells=0x1" offset="0x78.16" size="0x0.16" />
	<field name="pm_catastrophic_enum" descr="Phy Manager catastrophic enum" access="RO" offset="0x7c.0" size="0x0.7" />
	<field name="pm_cat_val" descr="When set, indicates the pm_catastrophic_enum is valid" access="RO" offset="0x7c.7" size="0x0.1" />
	<field name="an_catastrophic_enum" descr="Auto-neg catastrophic enum" access="RO" offset="0x7c.8" size="0x0.7" />
	<field name="an_cat_val" descr="When set, indicates the an_catastrophic_enum is valid" access="RO" offset="0x7c.15" size="0x0.1" />
	<field name="hst_catastrophic_enum" descr="HST catastrophic enum" access="RO" offset="0x7c.16" size="0x0.7" />
	<field name="hst_cat_val" descr="When set, indicates the hst_catastrophic_enum is valid" access="RO" offset="0x7c.23" size="0x0.1" />
	<field name="pd_catastrophic_enum" descr="Parallel Detect catastrophic enum" access="RO" offset="0x7c.24" size="0x0.7" />
	<field name="pd_cat_val" descr="When set, indicates the pd_catastrophic_enum is valid" access="RO" offset="0x7c.31" size="0x0.1" />
	<field name="pd_debug_indication" descr="Bit 0: speed_change_high_speed_moduleBit 1: False_positive_signal_detectBit 2: Nv2nv_forceBit 3: bad_kr_maskBit 4: kr_mlx_peerBit 5: entered_signal_detectBit 6: entered_rate_configBit 7: entered_activate_sunfsmBit 8: entered_doneBit 9: entered_subfsm_fail" access="RO" enum="speed_change_high_speed_module=0x1,False_positive_signal_detect=0x2,Nv2nv_force=0x4,bad_kr_mask=0x8,kr_mlx_peer=0x10,entered_signal_detect=0x20,entered_rate_config=0x40,entered_activate_sunfsm=0x80,entered_done=0x100,entered_subfsm_fail=0x200" offset="0x80.0" size="0x4.0" />
	<field name="pd_count" descr="Parallel detect cycles counter" access="RO" offset="0x84.0" size="0x0.6" />
	<field name="fp_signal_detect_count" descr="False Positive signal detect count" access="RO" offset="0x84.8" size="0x0.6" />
	<field name="hst_mismatch_reason" descr="0: speed1: FEC2: precoding3: Gray coding" access="RO" offset="0x84.16" size="0x0.2" />
	<field name="psi_collision2" descr="FSM 2 to call sub fsm of PSI that caused collisionsee fsm_mask in debug page for FSM numbering" access="RO" offset="0x84.22" size="0x0.5" />
	<field name="psi_collision1" descr="FSM 1 to call sub fsm of PSI that caused collisionsee fsm_mask in debug page for FSM numbering" access="RO" offset="0x84.27" size="0x0.5" />
	<field name="nlpn_debug_ind_mask" descr="Bit 0: nonce_match_failBit 1: timeout - rst cause idle in nplnBit 2: hs_negBit 3: dme_neg" access="RO" enum="nonce_match_fail=0x1,timeout=0x2,hs_neg=0x4,dme_neg=0x8" offset="0x88.0" size="0x0.8" />
	<field name="phy2mod_speed_req" descr="phy 2 module requested speed, aka speed_apsel_valuebitmask according to PTYS.ext_ethernet_protocol for ETH speedsor ib_ext_protocols for IB speeds" access="RO" offset="0x8c.0" size="0x4.0" />
	<field name="phy2mod_deactivate_lanes" descr="Bitmask per lane for phy2mod deactivate request status.0 - allow DP activation1 - Deactivate module DP" access="RO" offset="0x90.0" size="0x0.8" />
	<field name="phy2mod_ack_lanes" descr="Bitmask per lane for phy2mod request status.0 - ack1 - nack" access="RO" offset="0x90.8" size="0x0.8" />
	<field name="one_pll_mod" descr="indicates module has one pll for all lanes of the module." access="RO" offset="0x90.29" size="0x0.1" />
	<field name="no_dme_mod" descr="no_dme_module indicates module doesn’t support low speed signaling such\;as 312.5 MB/s for DME ETH AN signaling or SDR (2.5 GB/s) for IB low\;speed AN." access="RO" offset="0x90.30" size="0x0.1" />
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
	<field name="plr_rtt_ndr_4x_kp4_threshold" descr="rtt threshold in 1 ns units for NDR_4x speeds with KP4 FEC" access="RO" offset="0x98.0" size="0x0.16" />
	<field name="plr_rtt_hdr_threshold" descr="rtt threshold in 1 ns units for HDR speeds" access="RO" offset="0x98.16" size="0x0.16" />
	<field name="plr_rtt_ndr_2x_kp4_threshold" descr="rtt threshold in 1 ns units for NDR_2x speeds with KP4 FEC" access="RO" offset="0x9c.0" size="0x0.16" />
	<field name="plr_rtt_xdr_1x_kp4_threshold" descr="rtt threshold in 1 ns units for XDR_1x speeds with KP4 FEC" access="RO" offset="0x9c.16" size="0x0.16" />
	<field name="plr_rtt_ndr_2x_ell_threshold" descr="rtt threshold in 1 ns units for NDR_2x speeds with ELL FEC" access="RO" offset="0xa0.0" size="0x0.16" />
	<field name="plr_rtt_ndr_4x_ell_threshold" descr="rtt threshold in 1 ns units for NDR_4x speeds with ELL FEC" access="RO" offset="0xa0.16" size="0x0.16" />
	<field name="plr_rtt_xdr_1x_ell_threshold" descr="rtt threshold in 1 ns units for XDR_1x speeds with ELL FEC" access="RO" offset="0xa4.0" size="0x0.16" />
	<field name="plr_rtt_xdr_2x_kp4_threshold" descr="rtt threshold in 1 ns units for XDR_2x speeds with KP4 FEC" access="RO" offset="0xa4.16" size="0x0.16" />
	<field name="nv_link_generation" descr="Device NV-Link Generation:0: nv_link_51: nv_link_62: nv_link_73: nv_link_8" access="RO" enum="nv_link_5=0x0,nv_link_6=0x1,nv_link_7=0x2,nv_link_8=0x3" offset="0xa8.0" size="0x0.5" />
	<field name="plr_rtt_xdr_2x_ell_threshold" descr="rtt threshold in 1 ns units for XDR_2x speeds with ELL FEC" access="RO" offset="0xa8.16" size="0x0.16" />
	<field name="mode_b_fsm_state_lane_0" descr="(see above)" access="RO" offset="0xc0.0" size="0x0.4" />
	<field name="mode_b_fsm_state_lane_1" descr="Mode B FSM state for lane[i]:0: STATE_0 1: STATE_1 2: STATE_2 3: STATE_3 4: STATE_4 Note: this FSM is applicable only to mode B links." access="RO" offset="0xc0.4" size="0x0.4" />
	<field name="apsu_oper" descr="APSU (ILT/RTS) operational mode1: APSU enabled2: APSU disabled" access="RO" offset="0xcc.0" size="0x0.2" />
	<field name="hop_count_oper" descr="Hop count for TRO operational mode1: Hop count enabled2: Hop count disabled" access="RO" offset="0xcc.3" size="0x0.2" />
	<field name="lt_peer_det_oper" descr="Link Training peer detection operation mode1: Peer detection enabled2: Peer detection disabled" access="RO" offset="0xcc.6" size="0x0.2" />
	<field name="nlut_oper" descr="nLUT operational mode.1: nLUT enabled2: nLUT disabled" access="RO" offset="0xcc.9" size="0x0.2" />
	<field name="training_en_oper" descr="Control the training_en coperational mode1: Training enabled2: Training disabled" access="RO" offset="0xcc.12" size="0x0.2" />
</node>

<node name="pddr_phy_manager_link_enabled_eth_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_eth_enabled" descr="Ethernet protocols admin state: see PTYS.ext_eth_proto_admin" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_phy_manager_link_enabled_ib_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_proto_enabled" descr="IB link enabled speed:Bit 0 - SDRBit 1 - DDRBit 2 - QDRBit 3 - FDR10Bit 4 - FDRBit 5 - EDRBit 6 - HDRBit 7 - NDRBit 8 - XDR" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="phy_manager_link_width_enabled" descr="IB link enabled width:Bit 0 - 1xBit 1 - 2xBit 2 - 4xOther - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_phy_manager_link_enabled_nvlink_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_nvlink_enabled" descr="NVLink protocols admin state:see:\;PTYS - Extended Protocol NVLink - admin Layout" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_reg_ext" descr="" attr_required_tlvs="index:s" size="0x100.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM0: Network_port1: Near_End_Port - (For Retimer/Gearbox - Host side)2: Internal_IC_LR_Port3: Far_End_Port - (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" enum="Network_port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0: Local_port_number1: IB_port_number3: Out_of_band_or_PCI" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band_or_PCI=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number.:" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="module_ind_type" descr="Module index type selector:0: CPO_or_pluggable_modules1: OE2: ELS" access="INDEX" enum="CPO_or_pluggable_modules=0x0,OE=0x1,ELS=0x2" offset="0x0.24" size="0x0.2" />
	<field name="page_select" descr="page select index:0: Operational_info_page1: Troubleshooting_info_page2: Phy_info_page3: Module_info_page6: link_down_info8: Link_up_info9: Module_latched_flag_info_page11: link_partner_info_page14: cpo_module_info_page15: link_health_fec_measure_info_page16: APSU_info_page17: link_health_fec_measure_nvl5_page" access="INDEX" enum="Operational_info_page=0x0,Troubleshooting_info_page=0x1,Phy_info_page=0x2,Module_info_page=0x3,link_down_info=0x6,Link_up_info=0x8,Module_latched_flag_info_page=0x9,link_partner_info_page=0xb,cpo_module_info_page=0xe,link_health_fec_measure_info_page=0xf,APSU_info_page=0x10,link_health_fec_measure_nvl5_page=0x11" offset="0x4.0" size="0x0.8" />
	<field name="module_info_ext" descr="Module info extended configurations.resolution for rx_power, rx_power_high_th, rx_power_low_th tx_power,\;tx_power_high_th, tx_power_low_th in module info page0: dbm1: uW" access="OP" enum="dbm=0x0,uW=0x1" offset="0x4.29" size="0x0.2" />
	<field name="page_data" descr="Operation Info Page LayoutTroubleshooting info Page layoutPhy Info Page LayoutModule Info Page LayoutLink Down Info Page LayoutLink Up Info Page LayoutModule Latched Flag Info Page LayoutLink Partner Info Page LayoutCPO Module Page LayoutLink Health FEC Measure Info Page LayoutAPSU Info Page LayoutLink Health FEC Measure NVL5 Page Layout" subnode="pddr_reg_page_data_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).page_select" />
</node>

<node name="pddr_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="module_latched_flag_info_ext" descr="" subnode="module_latched_flag_info_ext" access="RW" offset="0x0.0" selected_by="Module_latched_flag_info_page" size="0x50.0" />
	<field name="pddr_apsu_info_page_ext" descr="" subnode="pddr_apsu_info_page_ext" access="RW" offset="0x0.0" selected_by="APSU_info_page" size="0xf8.0" />
	<field name="pddr_cpo_module_page_ext" descr="" subnode="pddr_cpo_module_page_ext" access="RW" offset="0x0.0" selected_by="cpo_module_info_page" size="0xa8.0" />
	<field name="pddr_fec_measure_ltx_nvl5_ext" descr="" subnode="pddr_fec_measure_ltx_nvl5_ext" access="RW" offset="0x0.0" selected_by="link_health_fec_measure_nvl5_page" size="0x8c.0" />
	<field name="pddr_link_down_info_page_ext" descr="" subnode="pddr_link_down_info_page_ext" access="RW" offset="0x0.0" selected_by="link_down_info" size="0xf4.0" />
	<field name="pddr_link_health_page_ext" descr="" subnode="pddr_link_health_page_ext" access="RW" offset="0x0.0" selected_by="link_health_fec_measure_info_page" size="0xb0.0" />
	<field name="pddr_link_partner_info_ext" descr="" subnode="pddr_link_partner_info_ext" access="RW" offset="0x0.0" selected_by="link_partner_info_page" size="0x30.0" />
	<field name="pddr_link_up_info_page_ext" descr="" subnode="pddr_link_up_info_page_ext" access="RW" offset="0x0.0" selected_by="Link_up_info" size="0xf8.0" />
	<field name="pddr_module_info_ext" descr="" subnode="pddr_module_info_ext" access="RW" offset="0x0.0" selected_by="Module_info_page" size="0xd0.0" />
	<field name="pddr_operation_info_page_ext" descr="" subnode="pddr_operation_info_page_ext" access="RW" offset="0x0.0" selected_by="Operational_info_page" size="0xf8.0" />
	<field name="pddr_phy_info_page_ext" descr="" subnode="pddr_phy_info_page_ext" access="RW" offset="0x0.0" selected_by="Phy_info_page" size="0xf8.0" />
	<field name="pddr_troubleshooting_page_ext" descr="" subnode="pddr_troubleshooting_page_ext" access="RW" offset="0x0.0" selected_by="Troubleshooting_info_page" size="0xf8.0" />
</node>

<node name="pddr_troubleshooting_page_ext" descr="" size="0xf8.0" >
	<field name="group_opcode" descr="0: Monitor_opcodes" access="INDEX" enum="Monitor_opcodes=0x0" offset="0x0.0" size="0x0.16" />
	<field name="status_opcode" descr="Status opcode described in:PDDR - Monitor opcodes layout" subnode="pddr_troubleshooting_page_status_opcode_auto_ext" access="RO" offset="0x4.0" size="0x4.0" union_selector="$(parent).group_opcode" />
	<field name="status_message" descr="ASCII code messageAll Messages are terminated by a Null character ‘\0’" access="RO" high_bound="58" low_bound="0" offset="0xc.0" size="0xec.0" />
</node>

<node name="pddr_troubleshooting_page_status_opcode_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_monitor_opcode_ext" descr="" subnode="pddr_monitor_opcode_ext" access="RW" offset="0x0.0" selected_by="Monitor_opcodes" size="0x4.0" />
</node>

<node name="pedcc_data_collection_configuration_ext" descr="" size="0xc.0" >
	<field name="tx_force_open_timeout_oper" descr="Indicates the Tx force open period WD timeout that was agreed upon after\;negotiation.During this period port Tx will keep transmitting, delaying the link\;drop even if required by usual behavior. This will be used in case there\;was a trigger to collect data when we entered recovery, and the recovery\;flow failed.If the timeout expired and collection was not completed, FW Phy will\;pass data collected so far, and any fields collection that hasn’t\;completed will be marked as invalid when passed to FW Core.Value is in units of 10 [msec]" access="RO" offset="0x8.0" size="0x0.12" />
	<field name="tx_force_open_timeout_admin" descr="Configures the Tx force open period WD timeout.During this period port Tx will keep transmitting, delaying the link\;drop even if required by usual behavior. This will be used in case there\;was a trigger to collect data when we entered recovery, and the recovery\;flow failed.Configuration is set only after a port re-toggle.Value is in unit of 10 [msec]" access="RW" offset="0x8.16" size="0x0.12" />
</node>

<node name="pedcc_events_data_groups_ext" descr="" size="0x58.0" >
	<field name="event_bitmask_cap" descr="Bitmask indicating which events returned data groups selection can be\;configured.If an event can’t occur on the port, it’s value should be ‘0’.See\;Single Timeline Phy Port Events - cap/oper Layout" access="RO" high_bound="7" low_bound="0" offset="0x0.0" size="0x20.0" />
	<field name="event_bitmask_admin" descr="Bitmask to chose which events returned data groups would be\;reconfigured.See\;Single Timeline Phy Port Events - admin Layout" access="RW" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
	<field name="data_group_bitmask_cap" descr="Bitmask indicating which data groups are available in the device and can\;be configured to collect.See\;Single Timeline Phy Data Groups - cap/oper Layout" access="RO" high_bound="2" low_bound="0" offset="0x40.0" size="0xc.0" />
	<field name="data_group_bitmask_admin" descr="Field used to configure which data groups will be collected for the\;chosen events in event_bitmask.If non of the bits are set, no additional data will be collected,\;besides the usual header as defined in MECR.See\;Single Timeline Phy Data Groups - admin Layout" access="RW" high_bound="2" low_bound="0" offset="0x4c.0" size="0xc.0" />
</node>

<node name="pedcc_link_metrics_collection_configuration_ext" descr="" size="0x24.0" >
	<field name="link_metric_8_stel_reporting_oper" descr="(see above)" access="RO" offset="0x0.1" size="0x0.3" />
	<field name="link_metric_7_stel_reporting_oper" descr="(see above)" access="RO" offset="0x0.5" size="0x0.3" />
	<field name="link_metric_6_stel_reporting_oper" descr="(see above)" access="RO" offset="0x0.9" size="0x0.3" />
	<field name="link_metric_5_stel_reporting_oper" descr="(see above)" access="RO" offset="0x0.13" size="0x0.3" />
	<field name="link_metric_4_stel_reporting_oper" descr="(see above)" access="RO" offset="0x0.17" size="0x0.3" />
	<field name="link_metric_3_stel_reporting_oper" descr="(see above)" access="RO" offset="0x0.21" size="0x0.3" />
	<field name="link_metric_2_stel_reporting_oper" descr="(see above)" access="RO" offset="0x0.25" size="0x0.3" />
	<field name="link_metric_1_stel_reporting_oper" descr="Indicates for link metric 1 on which threshold crossing it will report\;a trigger in STEL. For a trigger to actually appear, it requires the\;relevant threshold to be configured in the link metrics infrastructure\;for the metric, and for the metric to be enabled.Bit 0: normal_threshold_passedBit 1: warning_threshold_passedBit 2: alarm_threshold_passed" access="RO" enum="normal_threshold_passed=0x1,warning_threshold_passed=0x2,alarm_threshold_passed=0x4" offset="0x0.29" size="0x0.3" />
	<field name="link_metric_override_default_cap" descr="When set, it’s possible to overwrite the default behavior of link\;metrics event creation in STEL." access="RO" offset="0x4.0" size="0x0.1" />
	<field name="link_metric_15_stel_reporting_oper" descr="(see above)" access="RO" offset="0x4.5" size="0x0.3" />
	<field name="link_metric_14_stel_reporting_oper" descr="(see above)" access="RO" offset="0x4.9" size="0x0.3" />
	<field name="link_metric_13_stel_reporting_oper" descr="(see above)" access="RO" offset="0x4.13" size="0x0.3" />
	<field name="link_metric_12_stel_reporting_oper" descr="(see above)" access="RO" offset="0x4.17" size="0x0.3" />
	<field name="link_metric_11_stel_reporting_oper" descr="(see above)" access="RO" offset="0x4.21" size="0x0.3" />
	<field name="link_metric_10_stel_reporting_oper" descr="(see above)" access="RO" offset="0x4.25" size="0x0.3" />
	<field name="link_metric_9_stel_reporting_oper" descr="(see above)" access="RO" offset="0x4.29" size="0x0.3" />
	<field name="link_metric_15_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.2" size="0x0.2" />
	<field name="link_metric_14_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.4" size="0x0.2" />
	<field name="link_metric_13_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.6" size="0x0.2" />
	<field name="link_metric_12_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.8" size="0x0.2" />
	<field name="link_metric_11_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.10" size="0x0.2" />
	<field name="link_metric_10_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.12" size="0x0.2" />
	<field name="link_metric_9_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.14" size="0x0.2" />
	<field name="link_metric_8_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.16" size="0x0.2" />
	<field name="link_metric_7_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.18" size="0x0.2" />
	<field name="link_metric_6_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.20" size="0x0.2" />
	<field name="link_metric_5_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.22" size="0x0.2" />
	<field name="link_metric_4_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.24" size="0x0.2" />
	<field name="link_metric_3_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.26" size="0x0.2" />
	<field name="link_metric_2_stel_report_normal_trigger" descr="(see above)" access="RW" offset="0x8.28" size="0x0.2" />
	<field name="link_metric_1_stel_report_normal_trigger" descr="Controls the metric behavior when it’s enabled and its normal threshold\;has passed.Field configuration is valid only if link_metric_override_default_cap is set to ‘1’.0: fw_default1: report_normal_threshold_trigger2: do_not_report_normal_threshold_trigger" access="RW" enum="fw_default=0x0,report_normal_threshold_trigger=0x1,do_not_report_normal_threshold_trigger=0x2" offset="0x8.30" size="0x0.2" />
	<field name="link_metric_15_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.2" size="0x0.2" />
	<field name="link_metric_14_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.4" size="0x0.2" />
	<field name="link_metric_13_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.6" size="0x0.2" />
	<field name="link_metric_12_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.8" size="0x0.2" />
	<field name="link_metric_11_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.10" size="0x0.2" />
	<field name="link_metric_10_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.12" size="0x0.2" />
	<field name="link_metric_9_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.14" size="0x0.2" />
	<field name="link_metric_8_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.16" size="0x0.2" />
	<field name="link_metric_7_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.18" size="0x0.2" />
	<field name="link_metric_6_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.20" size="0x0.2" />
	<field name="link_metric_5_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.22" size="0x0.2" />
	<field name="link_metric_4_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.24" size="0x0.2" />
	<field name="link_metric_3_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.26" size="0x0.2" />
	<field name="link_metric_2_stel_report_warning_trigger" descr="(see above)" access="RW" offset="0xc.28" size="0x0.2" />
	<field name="link_metric_1_stel_report_warning_trigger" descr="Controls the metric behavior when it’s enabled and its warning threshold\;has passed.\;Field configuration is valid only if link_metric_override_default_cap is set to ‘1’.0: fw_default1: report_warning_threshold_trigger2: do_not_report_warning_threshold_trigger" access="RW" enum="fw_default=0x0,report_warning_threshold_trigger=0x1,do_not_report_warning_threshold_trigger=0x2" offset="0xc.30" size="0x0.2" />
	<field name="link_metric_15_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.2" size="0x0.2" />
	<field name="link_metric_14_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.4" size="0x0.2" />
	<field name="link_metric_13_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.6" size="0x0.2" />
	<field name="link_metric_12_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.8" size="0x0.2" />
	<field name="link_metric_11_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.10" size="0x0.2" />
	<field name="link_metric_10_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.12" size="0x0.2" />
	<field name="link_metric_9_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.14" size="0x0.2" />
	<field name="link_metric_8_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.16" size="0x0.2" />
	<field name="link_metric_7_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.18" size="0x0.2" />
	<field name="link_metric_6_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.20" size="0x0.2" />
	<field name="link_metric_5_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.22" size="0x0.2" />
	<field name="link_metric_4_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.24" size="0x0.2" />
	<field name="link_metric_3_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.26" size="0x0.2" />
	<field name="link_metric_2_stel_report_alarm_trigger" descr="(see above)" access="RW" offset="0x10.28" size="0x0.2" />
	<field name="link_metric_1_stel_report_alarm_trigger" descr="Controls the metric behavior when it’s enabled and its alarm threshold\;has passed.\;Field configuration is valid only if link_metric_override_default_cap is set to ‘1’.0: fw_default1: report_alarm_threshold_trigger2: do_not_report_alarm_threshold_trigger" access="RW" enum="fw_default=0x0,report_alarm_threshold_trigger=0x1,do_not_report_alarm_threshold_trigger=0x2" offset="0x10.30" size="0x0.2" />
</node>

<node name="pedcc_port_group_profile_config_ext" descr="" size="0x8.0" >
	<field name="grp_prf_id" descr="Sets which group profile ID data collection behavior will be overridden.On set command will assign port set in local_port to the currently\;chosen group profile ID. Port event triggers will behave based on the\;selected profile.On get command will return configured grp_prd_id of chosen local_port.if mps is set to ‘1’ setting group profile will affect all chosen ports,\;get command returned value is not valid." access="RW" offset="0x0.0" size="0x0.8" />
	<field name="grp_prf_id_max" descr="Indicates the highest group profile ID in the device that is available\;for allocation.If value is ‘0’, all ports must be assigned to the same group profile ID\;- ‘0’." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="grp_prf_default_set" descr="When set, will return local_port profile group to FW default value." access="WO" offset="0x0.31" size="0x0.1" />
</node>

<node name="pedcc_reg_ext" descr="" attr_required_tlvs="index:s" size="0x64.0" >
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0: Local_port_number1: IB_port_number3: Out_of_band_or_PCI" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band_or_PCI=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mps" descr="[DWIP]Multiple Port Set.Supported only if indicated in PMSCR.prm_support of PFLDC support,\;otherwise ignored.When set, local_port index is ignored and set command is given to all\;ports in mask given from PMSCR.local_port_mask field" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="module_type" descr="0: no_module1: pluggable_with_logger2: pluggable_without_logger3: CPO" access="RO" enum="no_module=0x0,pluggable_with_logger=0x1,pluggable_without_logger=0x2,CPO=0x3" offset="0x4.0" size="0x0.4" />
	<field name="uphy_version" descr="0: prod_5nm - (Uphy 7.0)1: prod_3nm_serdes_gen_7p52: prod_5nm_serdes_gen_8" access="RO" enum="prod_5nm=0x0,prod_3nm_serdes_gen_7p5=0x1,prod_5nm_serdes_gen_8=0x2" offset="0x4.8" size="0x0.4" />
	<field name="phy_version" descr="0: IB_XDR_NVL51: NVL6" access="RO" enum="IB_XDR_NVL5=0x0,NVL6=0x1" offset="0x4.16" size="0x0.4" />
	<field name="group_prf_id" descr="Selects the group profile to access for profile-indexed pages." access="INDEX" offset="0x4.23" size="0x0.5" />
	<field name="page_selector" descr="Page select index:0: events_data_groups1: collection_configuration2: port_group_profile3: link_metrics_collection" access="INDEX" enum="events_data_groups=0x0,collection_configuration=0x1,port_group_profile=0x2,link_metrics_collection=0x3" offset="0x4.28" size="0x0.4" />
	<field name="page_data" descr="PEDCC - Events Data Groups Configuration Page LayoutPEDCC - Data Collection Configuration Page LayoutPEDCC - Port Group Profile Configuration Page LayoutPEDCC - Link Metrics Collection Configuration Page Layout" subnode="pedcc_reg_page_data_auto_ext" access="RW" offset="0xc.0" size="0x58.0" union_selector="$(parent).page_selector" />
</node>

<node name="pedcc_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x58.0" >
	<field name="pedcc_data_collection_configuration_ext" descr="" subnode="pedcc_data_collection_configuration_ext" access="RW" offset="0x0.0" selected_by="collection_configuration" size="0xc.0" />
	<field name="pedcc_events_data_groups_ext" descr="" subnode="pedcc_events_data_groups_ext" access="RW" offset="0x0.0" selected_by="events_data_groups" size="0x58.0" />
	<field name="pedcc_link_metrics_collection_configuration_ext" descr="" subnode="pedcc_link_metrics_collection_configuration_ext" access="RW" offset="0x0.0" selected_by="link_metrics_collection" size="0x24.0" />
	<field name="pedcc_port_group_profile_config_ext" descr="" subnode="pedcc_port_group_profile_config_ext" access="RW" offset="0x0.0" selected_by="port_group_profile" size="0x8.0" />
</node>

<node name="pevnt_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rx_cont" descr="The local_port RX is contained.RX containd - When a packet had a corruption, and is discarded. the port\;which detect the error ‘contains’ it by stopping the traffic." access="RO" offset="0x4.0" size="0x0.1" />
	<field name="tx_cont" descr="The local_port TX is contained.TX containd - When a packet had a corruption, and is discarded. the port\;which detect the error ‘contains’ it by stopping the traffic." access="RO" offset="0x4.1" size="0x0.1" />
</node>

<node name="pfcc_reg_ext" descr="" size="0x20.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0: Local port number1: IB / label port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="prio_mask_rx" descr="Bit per prio indicating if RX flow control policy should be updated\;based on bit pfcrx ." access="OP" offset="0x4.0" size="0x0.8" />
	<field name="prio_mask_tx" descr="Bit per prio indicating if TX flow control policy should be updated\;based on bit pfctx ." access="OP" offset="0x4.16" size="0x0.8" />
	<field name="ppan" descr="Pause policy auto negotiation0: disabled - generate and ignore pause frames based on pptx, pprx1: enabled - when auto-negotiation is performed, set the pause policy\;based on the auto-negotiation resolution.Note: The auto-negotiation advertisement is set according to pptx, pprx.Note: When PFC is set on the TX / RX ppan must be set to 0." access="RW" enum="disabled=0x0,enabled=0x1" offset="0x4.28" size="0x0.4" />
	<field name="pfctx" descr="Priority based flow control policy on TX[7:0]. Per priority bit mask:0: never generate pause frames on the specified priority (default)1: generate pause frames according to RX buffer threshold on the\;specified prioritypfctx, pptx must be mutually\;exclusive (for example, only one of them at most can be set)." access="RW" offset="0x8.16" size="0x0.8" />
	<field name="patx" descr="Peer advertisement pause policy on Tx0: Unknown1: Peer supports pause on Tx2: Peer doesn’t support pause on Tx" access="RO" offset="0x8.27" size="0x0.2" />
	<field name="aptx" descr="Active (operational) pause policy on TX0: do not generate pause frames1: generate pause frames according to RX buffer threshold" access="RO" offset="0x8.30" size="0x0.1" />
	<field name="pptx" descr="Admin pause policy on TX (see also pfctx):0: never generate pause frames (default)1: generate pause frames according to RX buffer threshold" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="pfcrx" descr="Priority based flow control policy on RX[7:0]. Per priority bit mask:0: ignore incoming pause frames on the specified priority (default)1: respect incoming pause frames on the specified priority" access="RW" offset="0xc.16" size="0x0.8" />
	<field name="parx" descr="Peer advertisement pause policy on Rx0: Unknown1: Peer supports pause on Rx2: Peer doesn’t support pause on Rx" access="RO" offset="0xc.27" size="0x0.2" />
	<field name="aprx" descr="Active (operational) pause policy on RX0: ignore received pause frames1: respect received pause frames" access="RO" offset="0xc.30" size="0x0.1" />
	<field name="pprx" descr="Admin pause policy on RX (see also pfcrx):0: ignore received pause frames (default)1: respect received pause frames" access="RW" offset="0xc.31" size="0x0.1" />
	<field name="pfc_rx_timer_value" descr="[DWIP] Preconfigured PFC wait timeUnit of 512 BitTimeValid range is 1..65535Reserved when pfc_rx_timer_mode ≠ 1" access="RW" offset="0x18.0" size="0x0.16" />
	<field name="pfc_rx_timer_mode" descr="[DWIP] PFC RX timer mode0: TIMER - timer from packet.1: FIXED_VALUE - override value, take value of\;pfc_rx_timer_value2: DOUBLE_TIMER - double timer from packet. Supported from\;Spectrum-6Supported only from Spectrum-4.This field can be changed on the fly" access="RW" enum="TIMER=0x0,FIXED_VALUE=0x1,DOUBLE_TIMER=0x2" offset="0x18.16" size="0x0.2" />
</node>

<node name="pfldc_ext" descr="" attr_required_tlvs="index:s" size="0x24.0" >
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0: Local_port_number1: IB_port_number3: Out_of_band_or_PCI" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band_or_PCI=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mps" descr="[DWIP]Multiple Port Set.Supported only if indicated in PMSCR.prm_support of PFLDC support,\;otherwise ignored.When set, local_port index is ignored and set command is given to all\;ports in mask given from PMSCR.local_port_mask field" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="debug_mode_oper" descr="Indicates if port is currently in debug mode.0: regular_operation - port is not in debug mode1: debug_mode2: debug_mode_linkup 3: debug_mode_armed" access="RO" enum="regular_operation=0x0,debug_mode=0x1,debug_mode_linkup=0x2,debug_mode_armed=0x3" offset="0x4.0" size="0x0.2" />
	<field name="debug_mode_admin" descr="Sets the conditions to enter debug mode.Port may enter debug mode only after linkup flow completed.\;Once debug_mode_admin has been set to a non zero value, to switch to another value (i.e. another entry reason), debug mode must be first disabled by setting disable_debug_mode_admin == “0”, and then configuring a new debug_mode_admin setting.Note: All unused bits are reservedBit 0: force_debug_mode Bit 1: force_debug_mode_logic_up\;Bit 2: arm_auto_debug_mode Bit 3: arm_auto_debug_mode_once" access="RW" enum="force_debug_mode=0x1,force_debug_mode_logic_up=0x2,arm_auto_debug_mode=0x4,arm_auto_debug_mode_once=0x8" offset="0x4.8" size="0x0.8" />
	<field name="debug_mode_cap" descr="Indicates which debug mode entry conditions are supported.Note: All unused bits are reservedBit 0: force_debug_modeBit 1: force_debug_mode_logic_upBit 2: auto_debug_mode - if set, port supports “Bit 2:\;arm_auto_debug_mode” &amp; “Bit 3: arm_auto_debug_mode_once” under\;debug_mode_admin field" access="RO" enum="force_debug_mode=0x1,force_debug_mode_logic_up=0x2,auto_debug_mode=0x4" offset="0x4.16" size="0x0.8" />
	<field name="disable_debug_mode_admin" descr="When set, port will disable debug mode, and resume regular port\;operations.Note:When this field is set any other PFLDC configuration field is ignored.0: do_nothing1: disable_debug_mode" access="WO" enum="do_nothing=0x0,disable_debug_mode=0x1" offset="0x4.25" size="0x0.1" />
	<field name="change_recovery_flow_admin" descr="Valid only if debug mode auto entry has been configured by setting\;debug_mode_admin[2] or debug_mode_admin[3].Configures port recovery behavior when auto debug mode is set, and a\;link fault indication was raised.0: fw_default1: force_skip_recovery - port will not attempt recovery flow, and\;immediately enter debug mode2: force_recovery - if port supports recovery, it will attempt to\;conduct recovery flow prior to entering debug mode3: Reserved" access="RW" enum="fw_default=0x0,force_skip_recovery=0x1,force_recovery=0x2,Reserved=0x3" offset="0x4.26" size="0x0.2" />
	<field name="change_recovery_flow_cap" descr="Indicates if altering recovery default behavior when entering force\;linkup mode is supported.0: not_supported1: supported" access="RO" enum="not_supported=0x0,supported=0x1" offset="0x4.28" size="0x0.1" />
	<field name="all_ports_admin" descr="Set debug mode for all non-service ports in device0: single_port1: all_ports" access="RW" enum="single_port=0x0,all_ports=0x1" offset="0x4.29" size="0x0.1" />
	<field name="all_ports_cap" descr="Indicates if device supports capability to set debug mode on all\;non-service ports.0: not_supported1: supported" access="RO" enum="not_supported=0x0,supported=0x1" offset="0x4.30" size="0x0.1" />
	<field name="dc_cpl_allow" descr="Relevant only for DC couple ports, Ignored otherwise.Field must be set when entering force linkup debug mode, otherwise\;command is ignored.When entering force linkup debug mode in DC couple system the following\;message must be presented to user:“Warning: DC couple system must be powered on both sides of the physical\;link prior to enabling force linkup debug mode, and at all times when\;debug mode is active. System may be harmed and product lifetime may be\;shortened if not ensured.”" access="WO" offset="0x4.31" size="0x0.1" />
	<field name="debug_mode_timer_period" descr="Configures time period for port to remain in debug mode. Once period\;passes port will exit debug mode.Value is in units of 10 [sec]" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="debug_mode_timer_admin" descr="Enables device to disable debug mode in port after pre-defined time\;period set in debug_mode_timer_period0: no_timer1: set_timer" access="RW" enum="no_timer=0x0,set_timer=0x1" offset="0x8.22" size="0x0.1" />
	<field name="debug_mode_timer_cap" descr="Indicates if device supports capability to disable debug mode after the\;configured time period has passed.0: not_supported1: supported" access="RO" enum="not_supported=0x0,supported=0x1" offset="0x8.24" size="0x0.1" />
	<field name="detect_markers_admin" descr="Valid only if transmit_detect_markers_cap Bit 1 is set.Allows manually configuring port behavior regarding alignment markers\;detection, while in debug mode.0: fw_default1: enable_markers_detection2: disable_markers_detection3: reserved" access="RW" enum="fw_default=0x0,enable_markers_detection=0x1,disable_markers_detection=0x2,reserved=0x3" offset="0x8.26" size="0x0.2" />
	<field name="transmit_markers_admin" descr="Valid only if transmit_detect_markers_cap Bit 0 is set.Allows manually configuring port behavior regarding alignment markers\;transmission, while in debug mode.0: fw_default1: enable_markers_transmission2: disable_markers_transmission3: reserved" access="RW" enum="fw_default=0x0,enable_markers_transmission=0x1,disable_markers_transmission=0x2,reserved=0x3" offset="0x8.28" size="0x0.2" />
	<field name="transmit_detect_markers_cap" descr="Indicates if port supports\;capability to manually override alignment markers transmission &amp;\;detection while in debug mode.Bit 0: transmit_markers_override_supportedBit 1: detect_markers_override_supported" access="RO" enum="transmit_markers_override_supported=0x1,detect_markers_override_supported=0x2" offset="0x8.30" size="0x0.2" />
	<field name="uphy_measurement_admin" descr="Bitmask used to trigger which UPHY active measurements will be triggered\;upon force linkup mode entry.Bit 0: measurement_1 Bits 1-7 - ReservedNote: Measurements are considered destructive, once done, the link can’t\;be used and needs to be re-toggled." access="RW" offset="0xc.8" size="0x0.8" />
	<field name="uphy_measurement_cap" descr="Bitmask indicating which UPHY active measurements can be triggered upon\;force linkup mode entry.Bit 0: measurement_1 Bits 1-7 - Reserved" access="RO" offset="0xc.24" size="0x0.8" />
	<field name="lane_bitmask" descr="Logical lane bitmask.If lane_bitmask == 0, UPHY action is set on all lanesLane selection is relevant only if UPHY measurements are being conducted\;during debug mode entry.If uphy_measurement_admin == 0, then this field is ignored as all other\;actions are port specific, and not lane specific." access="INDEX" offset="0x10.0" size="0x0.8" />
	<field name="ignore_down_command_oper" descr="Returns current ignore behavior of FW for force linkup disabling.0: regular_disable - force linkup may be disabled through PFLDC\;configurations, or through usual flows, for example PAOS down.1: pfldc_disable_only - force linkup may be disabled only by setting\;disable_debug_mode_admin or after the timer in\;debug_mode_timer_period reaches ‘0’." access="RO" enum="regular_disable=0x0,pfldc_disable_only=0x1" offset="0x10.20" size="0x0.1" />
	<field name="ignore_down_command_admin" descr="Configures FW behavior to allow disabling of force linkup only through\;PFLDC configuration.Field is configurable only if ignore_down_command_cap is set to ‘1’.0: fw_default1: regular_disable - force linkup may be disabled through PFLDC\;configurations, or through usual flows, for example PAOS down.2: pfldc_disable_only - force linkup may be disabled only by setting\;disable_debug_mode_admin or after the timer in\;debug_mode_timer_period reaches ‘0’." access="RW" enum="fw_default=0x0,regular_disable=0x1,pfldc_disable_only=0x2" offset="0x10.21" size="0x0.2" />
	<field name="ignore_down_command_cap" descr="When set, indicates FW support capability to disable force linkup only\;through PFLDC configuration. For example - setting PAOS down will not\;affect the link." access="RO" offset="0x10.23" size="0x0.1" />
	<field name="uphy_measurement_status" descr="Returns status of UPHY measurement after port entered force linkup.\;Field is valid only if debug_mode_oper == ‘1’.0: no_measurement_attempted1: measurement_success2: measurement_failed3: measurement_failed_no_available_resource4: measurement_in_progress" access="RO" enum="no_measurement_attempted=0x0,measurement_success=0x1,measurement_failed=0x2,measurement_failed_no_available_resource=0x3,measurement_in_progress=0x4" offset="0x10.28" size="0x0.4" />
	<field name="debug_mode_active_time" descr="Time since port entered debug mode. Resets following link re-toggle or\;debug mode re-entry.Value is in units of 10 [sec]" access="RO" offset="0x14.0" size="0x0.18" />
</node>

<node name="pfsc_reg_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fwd_admin" descr="Administratively configured of Forward switching for Egress:0: Allow cut-through forwarding1: Always Store and Forward" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="fwd_oper" descr="Operational Egress Forward switching:0: Cut-Through forwarding operation is allowed1: Only Store and Forward operation" access="RO" offset="0x8.0" size="0x0.4" />
</node>

<node name="pgcb_ext" descr="" size="0x2a0.0" >
	<field name="cfg_buffer_num" descr="The configuration buffer indexValid values: 0..72" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="first" descr="Set to indicate this is the first chunk of the bufferReserved on query." access="OP" offset="0x0.29" size="0x0.1" />
	<field name="last" descr="Set to indicate this is the last chunk of the buffer." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Set to clear the buffer and the ports mapping.All fields other than cfg_buf_num are reserved when this is set.This resets buffer_offset to 0.Reserved on query." access="OP" offset="0x0.31" size="0x0.1" />
	<field name="buffer_size" descr="Size of buffer data in units of bytes, MUST be in 4 bytes granularity,\;0,4,8,12, etc…Maximum buffer size supported in FW is 1024B.On get, FW returns the number of valid bytes written to the buffer\;starting from buffer_offset." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="version_major" descr="The buffer content major version.This will use to identify the content" access="RW" offset="0x4.16" size="0x0.16" />
	<field name="buffer_offset" descr="Offset to write the data to or read the data from.Units of bytes.Reserved on set, valid only on get opertation." access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="version_minor" descr="The buffer content minor version." access="RW" offset="0x8.16" size="0x0.16" />
	<field name="ports_bitmap" descr="ports mask indicating on which ports the configuration buffer should be\;sent to the peer GPUValid on when first=1, reserved otherwise." access="RW" high_bound="31" low_bound="0" offset="0x20.0" size="0x80.0" />
	<field name="buffer" descr="The configuration buffer data." access="RW" high_bound="127" low_bound="0" offset="0xa0.0" size="0x200.0" />
</node>

<node name="pglf_capabilities_page_ext" descr="" size="0x20.0" >
	<field name="sampling_rate" descr="The FW sampling interval in milliseconds at which metrics are\;collected" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="metric_events_cap" descr="When set, the device supports General Link-Metrics Feature event\;generation. The following fields are only valid when this capability is\;indicated:normal_event_ctrl, warning_event_ctrl, alarm_event_ctrl in\;profile_metrics_parameters_configuration_pageevent_ctrl_admin, event_ctrl_oper in\;port_metrics_control_configuration_pageThe PGLFE (Port General Link-Metrics Feature Event) registerWhen not set, no metric events are generated regardless of the\;individual event control configurations." access="RO" offset="0x0.21" size="0x0.1" />
	<field name="window_data_validation_cap" descr="When set, the device supports the window data validation feature. The\;window_data_validation_thr and window_data_validation_en fields in\;profile_metrics_parameters_configuration_page are only valid when this\;capability is indicated." access="RO" offset="0x0.23" size="0x0.1" />
	<field name="number_of_metrics" descr="Returns the total number of supported general link metrics. If the\;returned value is x, then metrics 1 through x are available for\;configuration." access="RO" offset="0x0.25" size="0x0.5" />
	<field name="supported_metric_types" descr="The field bitmask returns the supported metric types by the device:Bit 1: Raw_BERBit 2: Effective_BERBit 3: Symbol_BERBit 4: PLR_Tx_BW_LossBit 5: PLR_Rx_BW_LossBit 6: Recovery_BW_LossBit 7: Port_total_BW_LossBit 8: Link_down_countBit 9: symbol_error_count" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="thr_crossing_action_cap" descr="Bitmask indicating which threshold crossing FW actions are supported by\;the device. The bit encoding maps to the warning_thr_crossing_action /\;alarm_thr_crossing_action valuesBit 1: Link_down_default_state (According to the\;PLDS.link_dwn_local_error_cfg link state)Bit 2: Recover_the_physical_link (Recovery state)Bit 3: Toggle_the_physical_link (Polling state).Bit 4: Close_the_physical_link (Disable state)" access="RO" offset="0x8.0" size="0x0.8" />
</node>

<node name="pglf_group_profile_metrics_parameters_page_ext" descr="" size="0x20.0" >
	<field name="metric_type" descr="1: Raw_BER2: Effective_BER3: Symbol_BER4: PLR_Tx_BW_Loss5: PLR_Rx_BW_Loss6: Recovery_BW_Loss7: Port_total_BW_Loss8: Link_down_count9: symbol_error_count" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="set_to_default" descr="when enabled, all metric parameters are reset to their default values\;for the selected metric number." access="RW" offset="0x0.23" size="0x0.1" />
	<field name="metric_index" descr="1: metric12: metric23: metric34: metric45: metric56: metric67: metric78: metric89: metric910: metric1011: metric1112: metric1213: metric1314: metric1415: metric15" access="INDEX" offset="0x0.25" size="0x0.5" />
	<field name="time_window" descr="The time frame which the events are grouped. This is a tumbling window\;(not a sliding window), means that each window is uncorrelated to the\;adjacent windows events.the time_window is specified in multiples of the sampling_rate\;(PGLF.capabilities_page.sampling_rate returned value)." access="RW" offset="0x4.0" size="0x0.20" />
	<field name="single_window_sampling" descr="Selects the sampling mode for the metric window.0: continuous_sampling - the metric is calculated at every\;sampling_rate interval throughout the window. Threshold evaluation\;occurs at the end of the window based on the accumulated delta.1: single_window_sampling - counters are sampled only at the start and\;end of the time window. A single threshold evaluation is performed at\;window end, based on the delta between those two points only." access="RW" offset="0x4.22" size="0x0.1" />
	<field name="warning_threshold" descr="(see above)" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="normal_threshold" descr="Threshold values of the metric:For BER metric types: The threshold is calculated out of 2 values:bits 11:8- mantissabits 7:0 - exponentthreshold value = mantissa * 10^(-exponent)2. For BW loss metric types: the BW loss threshold in 0.01 granularity\;of percentage valid range[0,10000].3. For Counter metrics: The threshold is evaluated as a direct decimal\;integer." access="RW" offset="0x8.16" size="0x0.16" />
	<field name="alarm_threshold" descr="(see above)" access="RW" offset="0xc.0" size="0x0.16" />
	<field name="alarm_event_ctrl" descr="(see above)" access="RW" offset="0x10.13" size="0x0.2" />
	<field name="warning_event_ctrl" descr="(see above)" access="RW" offset="0x10.16" size="0x0.2" />
	<field name="normal_event_ctrl" descr="Event generation control for threshold crossings:0 - Do not generate event1 - Generate Event2 - Generate Single Event”" access="RW" offset="0x10.19" size="0x0.2" />
	<field name="alarm_th_crossing_action" descr="(see above)" access="RW" offset="0x10.22" size="0x0.3" />
	<field name="warning_th_crossing_action" descr="FW action required when exceeding warning or alarmthresholds:0: Do_nothing1: Link_down_default_state (According to PLDS.link_dwn_local_error_cfg\;link state)2: Recover_the_physical_link (Recovery state)3: Toggle_the_physical_link (Polling state).4: Close_the_physical_link (Disable state)”" access="RW" offset="0x10.27" size="0x0.3" />
	<field name="window_data_validation_thr" descr="Window data validation threshold - represents the minimum percentage of\;the time window during which data must be transmitted over the link for\;the window to be considered valid for monitoring event triggering.This threshold is specified as a percentage [%] of the total time_window\;size and in 1 [%] percentage units.Valid range is between [1,..,100]If the data usage within the current window falls below this threshold,\;the window is unreliable and will not trigger a monitoring event or an\;action." access="RW" offset="0x14.0" size="0x0.7" />
	<field name="window_data_validation_en" descr="When enabled, FW will validate the percentage of the time window during\;which data must be transmitted.0: do_not_validate1: validate" access="RW" offset="0x14.9" size="0x0.1" />
</node>

<node name="pglf_group_profile_status_page_ext" descr="" size="0x20.0" >
	<field name="metrics_configured_indication_mask" descr="Bitmask indicating which general link metrics are currently configured\;with valid parameters. If Bit[i] is set, metric[i] is configured and in\;use.Bit 1: metric_1 is configuredBit 2: metric_2 is configured …Bit 15: metric_15 is configuredBit 0: reserved" access="RO" offset="0x0.0" size="0x0.16" />
</node>

<node name="pglf_port_metrics_control_configuration_ext" descr="" size="0x20.0" >
	<field name="enable_ctrl_metric9" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x0.0" size="0x0.2" />
	<field name="enable_ctrl_metric8" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x0.3" size="0x0.2" />
	<field name="enable_ctrl_metric7" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x0.6" size="0x0.2" />
	<field name="enable_ctrl_metric6" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x0.9" size="0x0.2" />
	<field name="enable_ctrl_metric5" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x0.12" size="0x0.2" />
	<field name="enable_ctrl_metric4" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x0.15" size="0x0.2" />
	<field name="enable_ctrl_metric3" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x0.18" size="0x0.2" />
	<field name="enable_ctrl_metric2" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x0.21" size="0x0.2" />
	<field name="enable_ctrl_metric1" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x0.24" size="0x0.2" />
	<field name="event_ctrl_admin" descr="This field serves for enabling or disabling event generation for the\;General Link-Metrics Feature per port.When Set: Event generation is globally enabled for the port. The system\;will generate Port General Link-Metrics Feature Events (PGLFE) based on\;the individual threshold event settings configured for each active\;metric in the PGLF.metrics_parameters_configuration_page.When Cleared: Event generation is globally disabled for the port. No\;PGLFE events will be generated, regardless of the individual metric\;configurations or threshold crossings.0 - FW_default1 - events_enable2 - events_disable" access="RW" offset="0x0.27" size="0x0.2" />
	<field name="event_ctrl_oper" descr="Return the operational value of the event_ctrl0 - events_disable1 - events_enable" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="enable_ctrl_metric15" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x4.12" size="0x0.2" />
	<field name="enable_ctrl_metric14" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x4.15" size="0x0.2" />
	<field name="enable_ctrl_metric13" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x4.18" size="0x0.2" />
	<field name="enable_ctrl_metric12" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x4.21" size="0x0.2" />
	<field name="enable_ctrl_metric11" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x4.24" size="0x0.2" />
	<field name="enable_ctrl_metric10" descr="Controls whether this metric’s evaluation and logic is active\;for this port.0 - FW_default1 - enable2 - disable" access="RW" offset="0x4.27" size="0x0.2" />
	<field name="state_of_metric8" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0x8.0" size="0x0.3" />
	<field name="state_of_metric7" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0x8.4" size="0x0.3" />
	<field name="state_of_metric6" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0x8.8" size="0x0.3" />
	<field name="state_of_metric5" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0x8.12" size="0x0.3" />
	<field name="state_of_metric4" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0x8.16" size="0x0.3" />
	<field name="state_of_metric3" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0x8.20" size="0x0.3" />
	<field name="state_of_metric2" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0x8.24" size="0x0.3" />
	<field name="state_of_metric1" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0x8.28" size="0x0.3" />
	<field name="state_of_metric15" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0xc.4" size="0x0.3" />
	<field name="state_of_metric14" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0xc.8" size="0x0.3" />
	<field name="state_of_metric13" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0xc.12" size="0x0.3" />
	<field name="state_of_metric12" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0xc.16" size="0x0.3" />
	<field name="state_of_metric11" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0xc.20" size="0x0.3" />
	<field name="state_of_metric10" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0xc.24" size="0x0.3" />
	<field name="state_of_metric9" descr="The state of the port metric during the last time window.0 - N/A - not supported or not enabled1 - Normal (Default state upon link-up)2 - Warning3 - Alarm" access="RO" offset="0xc.28" size="0x0.3" />
</node>

<node name="pglf_reg_ext" descr="" size="0x2c.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM0: Network_port1: Near_End_Port - (For Retimer/Gearbox - Host side)2: Internal_IC_LR_Port3: Far_End_Port - (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" enum="Network_port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0: Local_port_number1: IB_port_number3: Out_of_band_or_PCI" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band_or_PCI=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="page_select" descr="page select index:0: capabilities_page1: group_profile_status_page2: group_profile_metrics_parameters_page3: port_metrics_control_configuration_page" access="INDEX" enum="capabilities_page=0x0,group_profile_status_page=0x1,group_profile_metrics_parameters_page=0x2,port_metrics_control_configuration_page=0x3" offset="0x4.0" size="0x0.4" />
	<field name="group_profile_number" descr="Selects the group profile to access for profile-indexed pages.1 - group_12 - group_23 - group_34 - group_45 - group_56 - group_67 - group_78 - group_8relvant for the following pages:1: profile_status_page2: profile_metrics_parameters_configuration_page" access="INDEX" offset="0x4.25" size="0x0.5" />
	<field name="page_data" descr="PGLF - Capabilities Page LayoutPGLF - Group Profile Status Page LayoutPGLF - Group Profile Metrics Parameters Page LayoutPGLF - Port Metrics Control Configuration Layout" subnode="pglf_reg_page_data_auto_ext" access="RW" offset="0xc.0" size="0x20.0" union_selector="$(parent).page_select" />
</node>

<node name="pglf_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x20.0" >
	<field name="pglf_capabilities_page_ext" descr="" subnode="pglf_capabilities_page_ext" access="RW" offset="0x0.0" selected_by="capabilities_page" size="0x20.0" />
	<field name="pglf_group_profile_metrics_parameters_page_ext" descr="" subnode="pglf_group_profile_metrics_parameters_page_ext" access="RW" offset="0x0.0" selected_by="group_profile_metrics_parameters_page" size="0x20.0" />
	<field name="pglf_group_profile_status_page_ext" descr="" subnode="pglf_group_profile_status_page_ext" access="RW" offset="0x0.0" selected_by="group_profile_status_page" size="0x20.0" />
	<field name="pglf_port_metrics_control_configuration_ext" descr="" subnode="pglf_port_metrics_control_configuration_ext" access="RW" offset="0x0.0" selected_by="port_metrics_control_configuration_page" size="0x20.0" />
</node>

<node name="pgmr_ext" descr="" attr_required_tlvs="index:s" size="0x2c.0" >
	<field name="pg_sel" descr="Selection between an operation on a local port or a group, for ‘set’ and\;‘get’ operations.0 - local port (group field is neglected even if set)1 - group (local_port field is neglected even if set)" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0 - Network Port1 - Near-End Port (For Retimer/Gearbox - Host side)2 - internal IC LR Port3 - Far-End Port (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="group" descr="Group number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. Determines the way local_port is interpreted:0 - Local port number1 - IB port number3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid1 - Valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="group_of_port" descr="The corresponding group number for the\;local_port" access="RW" offset="0x4.4" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x4.8" size="0x0.4" />
	<field name="ports_mapping_of_group" descr="A bit map of all available local ports in the system (each bit\;represents a local port).The corresponding bits which represent the local ports for the specific\;group in the group field, are set to ‘1’.If set to ‘0’ - not in that specific group or not available.Bit 0 - local_port 1Bit 1 - local_port 2…" access="RW" high_bound="8" low_bound="0" offset="0x8.0" size="0x24.0" />
</node>

<node name="pgrrs_ext" descr="" size="0x90.0" >
	<field name="lp_msb" descr="Local port number MSB." access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="nldf_status" descr="0: success1: failed" access="RO" offset="0x0.29" size="0x0.3" />
	<field name="reg_status_entry" descr="See Register Return Status Layout Layout" subnode="reg_return_status_ext" access="RO" high_bound="31" low_bound="0" offset="0x10.0" size="0x80.0" />
</node>

<node name="pguid_reg_ext" descr="" size="0x60.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sys_guid" descr="System GUID.Only 64 LSB are used. 64 MSB are reserved." access="RO" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
	<field name="node_guid" descr="Node GUID.Only 64 LSB are used. 64 MSB are reserved." access="RO" high_bound="3" low_bound="0" offset="0x14.0" size="0x10.0" />
	<field name="port_guid" descr="Port GUID.Only 64 LSB are used. 64 MSB are reserved." access="RO" high_bound="3" low_bound="0" offset="0x24.0" size="0x10.0" />
	<field name="allocated_guid" descr="Allocated GUID.Only 64 LSB are used. 64 MSB are reserved." access="RO" high_bound="3" low_bound="0" offset="0x34.0" size="0x10.0" />
</node>

<node name="phbr_ext" descr="" size="0x1c.0" >
	<field name="lp_msb" descr="Local port[9:8]Reserved when hist_type = rdq_wqe_occupancy." access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="local_portWhen hist_type = rdq_wqe_occupancy: carries rdq_id (0-63) instead of a\;local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="hist_id" descr="Histogram id to bindfrom 0 to cap_max_port_hist_id - 1" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="hist_type" descr="Histogram Type.See Histogram Types" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="mode" descr="Mode:0: Linear1: Exponential" access="RW" enum="Linear=0x0,Exponential=0x1" offset="0x8.28" size="0x0.3" />
	<field name="first_bin_thr" descr="First Bin Threshold.All values that are under this threshold will be counted in the first\;bin.Units according to the units of the hist_type.Range 1…(2^28) - 1" access="RW" offset="0xc.0" size="0x4.0" />
	<field name="bin_size" descr="Bin Size.bin_0 size will be first_bin_thr.If mode = 0, the size of bin 1-8 will be bin_size.If mode = 1, the size of bin_i will be 2^(i-1) * bin_size when 1 &lt; i &lt;\;8.Range 1…(2^25) - 1Units according to the units of the hist_type" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="hist_repeat_num" descr="Histogram Repeat Number.When this field equal to 0 the histogram will stop.When this field equal to 0xffffff the histogram will run infinite times.On other values the histogram will run hist_repeat_num times.Range 1…2^24 - 1Reserved when hist_type = rdq_wqe_occupancy." access="RW" offset="0x14.0" size="0x0.24" />
	<field name="sample_time" descr="Sample time interval.Allowed range for Spectrum:time = 2^sample_time * 128nSecsample_time range is 0..cap_max_sample_time-1Reserved when hist_type = rdq_wqe_occupancy." access="RW" offset="0x18.0" size="0x0.6" />
</node>

<node name="phrr_reg_ext" descr="" size="0x68.0" >
	<field name="lp_msb" descr="Local port[9:8]Reserved when hist_type = rdq_wqe_occupancy." access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="local_portWhen hist_type = rdq_wqe_occupancy: carries rdq_id (0-63) instead of a\;local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clr" descr="Clear:1: Clear the data in the histogram agent" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="hist_id" descr="see PHBR - Port Histogram Binding Register Layout" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="bin" descr="Value of binUnits according to the units of the hist_type which is used for the\;hist_id" subnode="uint64" access="RO" high_bound="9" low_bound="0" offset="0x10.0" size="0x50.0" />
	<field name="min_watermark" descr="Min value while the histogram was working." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="max_watermark" descr="Max value while the histogram was working." access="RO" offset="0x64.0" size="0x4.0" />
</node>

<node name="phys_layer_cntrs_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear event in msec." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="(see above)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="symbol_errors_high" descr="Perf.PortCounters(SymbolErrorCounter) = Perf.PortCounters(UnknownSymbol)" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="symbol_errors_low" descr="(see above)" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="sync_headers_errors_high" descr="Perf.PortExtendedSpeedsCounters(SynchHeaderErrorCounter)" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="sync_headers_errors_low" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane0_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane0Counter) / BIP\;error counter, lane 0In PRBS test mode, indicates the number of PRBS errorson lane 0" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane0_low" descr="(see above)" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane1_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane1Counter) / BIP\;error counter, lane 1In PRBS test mode, indicates the number of PRBS errorson lane 1" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane1_low" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane2_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane2Counter) / BIP\;error counter, lane 2In PRBS test mode, indicates the number of PRBS errorson lane 2" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane2_low" descr="(see above)" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane3_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane3Counter) / BIP\;error counter, lane 3In PRBS test mode, indicates the number of PRBS errorson lane 3" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane3_low" descr="(see above)" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane0)" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_low" descr="(see above)" access="RO" offset="0x3c.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane1)" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_low" descr="(see above)" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane2)" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_low" descr="(see above)" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane3)" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_low" descr="(see above)" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane0)" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_low" descr="(see above)" access="RO" offset="0x5c.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane1)" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_low" descr="(see above)" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane2)" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_low" descr="(see above)" access="RO" offset="0x6c.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane3)" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_low" descr="(see above)" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="rs_fec_corrected_blocks_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrecableBlockCounter)" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="rs_fec_corrected_blocks_low" descr="(see above)" access="RO" offset="0x7c.0" size="0x4.0" />
	<field name="rs_fec_uncorrectable_blocks_high" descr="Perf.PortExtendedSpeedsCounters(FEUncorrecableBlockCounter)" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="rs_fec_uncorrectable_blocks_low" descr="(see above)" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="rs_fec_no_errors_blocks_high" descr="The number of RS-FEC blocks received that had no errors.Note: Total rs_fec blocks received = rs_fec_corrected_blocks +\;rs_fec_uncorrectable_blocks + rs_fec_no_errors_blocks" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="rs_fec_no_errors_blocks_low" descr="(see above)" access="RO" offset="0x8c.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_total_high" descr="Perf.PortExtendedSpeedCounters(PortFECCorrectedSymbolCounter)" access="RO" offset="0x98.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_total_low" descr="(see above)" access="RO" offset="0x9c.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane0_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane0)" access="RO" offset="0xa0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane0_low" descr="(see above)" access="RO" offset="0xa4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane1_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane1)" access="RO" offset="0xa8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane1_low" descr="(see above)" access="RO" offset="0xac.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane2_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane2)" access="RO" offset="0xb0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane2_low" descr="(see above)" access="RO" offset="0xb4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane3_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane3)" access="RO" offset="0xb8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane3_low" descr="(see above)" access="RO" offset="0xbc.0" size="0x4.0" />
	<field name="link_down_events" descr="Counts local unintentional drops (no remote consideration)Perf.PortCounters(LinkDownedCounter)" access="RO" offset="0xc0.0" size="0x4.0" />
	<field name="successful_recovery_events" descr="Counts successful recovery events per active link. clears on new link up" access="RO" offset="0xc4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane4_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane4)" access="RO" offset="0xc8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane4_low" descr="(see above)" access="RO" offset="0xcc.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane5_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane5)" access="RO" offset="0xd0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane5_low" descr="(see above)" access="RO" offset="0xd4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane6_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane6)" access="RO" offset="0xd8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane6_low" descr="(see above)" access="RO" offset="0xdc.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane7_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane7)" access="RO" offset="0xe0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane7_low" descr="(see above)" access="RO" offset="0xe4.0" size="0x4.0" />
	<field name="unintentional_link_down_events" descr="Counts Local &amp; remote unintentional drops (remote intentional are not\;counted)Updated on link drop only" access="RO" offset="0xf0.0" size="0x4.0" />
	<field name="intentional_link_down_events" descr="Counts Local &amp; remote intentional drops (remote intentional counted)Updated on link drop only" access="RO" offset="0xf4.0" size="0x4.0" />
</node>

<node name="phys_layer_stat_cntrs_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear event in msec." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="(see above)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="phy_received_bits_high" descr="This counter provides information on the totalamount of bits received by the PHY FEC decoder." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="phy_received_bits_low" descr="(see above)" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="phy_symbol_errors_high" descr="This counter provides information on error bits that were not corrected\;by phy correction mechanisms." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="phy_symbol_errors_low" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="phy_corrected_bits_high" descr="Corrected bits by FEC engine." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="phy_corrected_bits_low" descr="(see above)" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="phy_raw_errors_lane0_high" descr="This counter provides information on error bits that were identified on\;lane 0.When FEC is enabled this induction corresponds to corrected errors.In PRBS test mode, indicates the number of PRBS errorson lane 0" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="phy_raw_errors_lane0_low" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="phy_raw_errors_lane1_high" descr="This counter provides information on error bits that were identified on\;lane 1.When FEC is enabled this induction corresponds to corrected errorsIn PRBS test mode, indicates the number of PRBS errorson lane 1" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="phy_raw_errors_lane1_low" descr="(see above)" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="phy_raw_errors_lane2_high" descr="This counter provides information on error bits that were identified on\;lane 2.When FEC is enabled this induction corresponds to corrected errors.In PRBS test mode, indicates the number of PRBS errorson lane 2" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="phy_raw_errors_lane2_low" descr="(see above)" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="phy_raw_errors_lane3_high" descr="This counter provides information on error bits that were identified on\;lane 3.When FEC is enabled this induction corresponds to corrected errors.In PRBS test mode, indicates the number of PRBS errorson lane 3" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="phy_raw_errors_lane3_low" descr="(see above)" access="RO" offset="0x3c.0" size="0x4.0" />
	<field name="phy_raw_errors_lane4_high" descr="This counter provides information on error bits that were identified on\;lane 4.When FEC is enabled this induction corresponds to corrected errors.In PRBS test mode, indicates the number of PRBS errorson lane 4" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="phy_raw_errors_lane4_low" descr="(see above)" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="phy_raw_errors_lane5_high" descr="This counter provides information on error bits that were identified on\;lane 5.When FEC is enabled this induction corresponds to corrected errorsIn PRBS test mode, indicates the number of PRBS errorson lane 5" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="phy_raw_errors_lane5_low" descr="(see above)" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="phy_raw_errors_lane6_high" descr="This counter provides information on error bits that were identified on\;lane 6.When FEC is enabled this induction corresponds to corrected errors.In PRBS test mode, indicates the number of PRBS errorson lane 6" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="phy_raw_errors_lane6_low" descr="(see above)" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="phy_raw_errors_lane7_high" descr="This counter provides information on error bits that were identified on\;lane 7.When FEC is enabled this induction corresponds to corrected errors.In PRBS test mode, indicates the number of PRBS errorson lane 7" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="phy_raw_errors_lane7_low" descr="(see above)" access="RO" offset="0x5c.0" size="0x4.0" />
	<field name="raw_ber_coef" descr="(see above)" access="RO" offset="0x60.0" size="0x0.4" />
	<field name="raw_ber_magnitude" descr="Raw_BER = raw_ber_coef \;*10^(-raw_ber_magnitude)" access="RO" offset="0x60.8" size="0x0.8" />
	<field name="fc_zero_hist" descr="Valid for links with RS FEC histograms only.First histogram error with value of 0 while all higher errors are only\;with 0 value as well.0 - No histogram active / N/A value" access="RO" offset="0x60.16" size="0x0.10" />
	<field name="effective_ber_coef" descr="(see above)" access="RO" offset="0x64.0" size="0x0.4" />
	<field name="effective_ber_magnitude" descr="effective_fec_BER = effective_fec_ber_coef\;\;*10^(-effective_fec_ber_magnitude)" access="RO" offset="0x64.8" size="0x0.8" />
	<field name="estimated_effective_ber_coef" descr="(see above)" access="RO" offset="0x64.16" size="0x0.4" />
	<field name="estimated_effective_ber_coef_float" descr="(see above)" access="RO" offset="0x64.20" size="0x0.4" />
	<field name="estimated_effective_ber_magnitude" descr="Supported if PCAM.feature_cap_mask bit 105 setestimated_effective_fec_BER = estimated_effective_fec_ber_coef\;estimated_effective_ber_coef_float\;*10^(-effective_fec_ber_magnitude)" access="RO" offset="0x64.24" size="0x0.8" />
	<field name="symbol_ber_coef" descr="(see above)" access="RO" offset="0x68.0" size="0x0.4" />
	<field name="symbol_ber_magnitude" descr="Symbol_BER =\;symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x68.8" size="0x0.8" />
	<field name="ucr_ber_coef" descr="(see above)" access="RO" offset="0x68.16" size="0x0.4" />
	<field name="ucr_ber_coef_float" descr="(see above)" access="RO" offset="0x68.20" size="0x0.4" />
	<field name="ucr_ber_magnitude" descr="Supported if PCAM.feature_cap_mask bit 106 setucr_fec_BER = ucr_fec_ber_coef\;ucr_ber_coef_float\;*10^(-ucr_ber_magnitude)" access="RO" offset="0x68.24" size="0x0.8" />
	<field name="raw_ber_coef_lane1" descr="(see above)" access="RO" offset="0x6c.0" size="0x0.4" />
	<field name="raw_ber_magnitude_lane1" descr="Raw_BER_lan0 = raw_ber_coef_lane1*10^(-raw_ber_magnitude_lane1)" access="RO" offset="0x6c.8" size="0x0.8" />
	<field name="raw_ber_coef_lane0" descr="(see above)" access="RO" offset="0x6c.16" size="0x0.4" />
	<field name="raw_ber_magnitude_lane0" descr="Raw_BER_lan0 = raw_ber_coef_lane0*10^(-raw_ber_magnitude_lane0)" access="RO" offset="0x6c.24" size="0x0.8" />
	<field name="raw_ber_coef_lane3" descr="(see above)" access="RO" offset="0x70.0" size="0x0.4" />
	<field name="raw_ber_magnitude_lane3" descr="Raw_BER_lan0 = raw_ber_coef_lane3*10^(-raw_ber_magnitude_lane3)" access="RO" offset="0x70.8" size="0x0.8" />
	<field name="raw_ber_coef_lane2" descr="(see above)" access="RO" offset="0x70.16" size="0x0.4" />
	<field name="raw_ber_magnitude_lane2" descr="Raw_BER_lan0 = raw_ber_coef_lane2*10^(-raw_ber_magnitude_lane2)" access="RO" offset="0x70.24" size="0x0.8" />
	<field name="raw_ber_coef_lane5" descr="(see above)" access="RO" offset="0x74.0" size="0x0.4" />
	<field name="raw_ber_magnitude_lane5" descr="Raw_BER_lan0 = raw_ber_coef_lane5*10^(-raw_ber_magnitude_lane5)" access="RO" offset="0x74.8" size="0x0.8" />
	<field name="raw_ber_coef_lane4" descr="(see above)" access="RO" offset="0x74.16" size="0x0.4" />
	<field name="raw_ber_magnitude_lane4" descr="Raw_BER_lan0 = raw_ber_coef_lane4*10^(-raw_ber_magnitude_lane4)" access="RO" offset="0x74.24" size="0x0.8" />
	<field name="raw_ber_coef_lane7" descr="(see above)" access="RO" offset="0x78.0" size="0x0.4" />
	<field name="raw_ber_magnitude_lane7" descr="Raw_BER_lan0 = raw_ber_coef_lane7*10^(-raw_ber_magnitude_lane7)" access="RO" offset="0x78.8" size="0x0.8" />
	<field name="raw_ber_coef_lane6" descr="(see above)" access="RO" offset="0x78.16" size="0x0.4" />
	<field name="raw_ber_magnitude_lane6" descr="Raw_BER_lan0 = raw_ber_coef_lane6*10^(-raw_ber_magnitude_lane6)" access="RO" offset="0x78.24" size="0x0.8" />
	<field name="phy_effective_errors_high" descr="This counter provides information on error bits that were not corrected\;by FEC correction algorithm or that FEC is not active." access="RO" offset="0x7c.0" size="0x4.0" />
	<field name="phy_effective_errors_low" descr="(see above)" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="time_since_last_link_up" descr="The total elapsed time, in 128 msec units, that the port has been in an\;active state since the last link up event.Notes:The counter does not clear when using the PPCNT.clr opcode.2. The counter is supported when indicated by PCAM Bit\;8:PPCNT.port_up_time_supported" access="RO" offset="0x94.0" size="0x4.0" />
	<field name="port_up_time" descr="The total elapsed time, in 128 msec units, that the port has been in\;active state since the last device reset event.Notes:The counter does not clear when using the PPCNT.clr opcode.The counter does not clear on a new link-up event.3. The counter is supported when indicated by PCAM Bit\;8:PPCNT.port_up_time_supported" access="RO" offset="0x98.0" size="0x4.0" />
</node>

<node name="plcc_reg_ext" descr="" attr_required_tlvs="index:s" size="0x18.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM0: Network_port1: Near_End_Port - (For Retimer/Gearbox - Host side)2: Internal_IC_LR_Port3: Far_End_Port - (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" enum="Network_port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0: Local_port_number1: IB_port_number3: Out_of_band_or_PCI" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band_or_PCI=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number.:" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="page_select" descr="page select index:0: High_symbol_error_rate_configuration_page1: High_bit_error_rate_configuration_page2: RS_FEC_link_fail_configuration_page" access="INDEX" enum="High_symbol_error_rate_configuration_page=0x0,High_bit_error_rate_configuration_page=0x1,RS_FEC_link_fail_configuration_page=0x2" offset="0x4.0" size="0x0.4" />
	<field name="page_cap" descr="Page capability bit-mask:Bit 0: High_symbol_error_rate_configuration_pageBit 1: High_bit_error_rate_configuration_pageBit 2: RS_FEC_link_fail_configuration_page" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="page_data" descr="High symbol error rate configuration Page LayoutHigh bit error rate configuration Page LayoutRS FEC Link Fail Configuration Page Layout" subnode="plcc_reg_page_data_auto_ext" access="RW" offset="0x8.0" size="0x10.0" union_selector="$(parent).page_select" />
</node>

<node name="plcc_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x10.0" >
	<field name="High_bit_error_rate_configuration_page_ext" descr="" subnode="High_bit_error_rate_configuration_page_ext" access="RW" offset="0x0.0" selected_by="High_bit_error_rate_configuration_page" size="0x10.0" />
	<field name="High_symbol_error_rate_configuration_page_ext" descr="" subnode="High_symbol_error_rate_configuration_page_ext" access="RW" offset="0x0.0" selected_by="High_symbol_error_rate_configuration_page" size="0x10.0" />
	<field name="plcc_rs_fec_link_fail_configuraion_page_ext" descr="" subnode="plcc_rs_fec_link_fail_configuraion_page_ext" access="RW" offset="0x0.0" selected_by="RS_FEC_link_fail_configuration_page" size="0x10.0" />
</node>

<node name="plcc_rs_fec_link_fail_configuraion_page_ext" descr="" size="0x10.0" >
	<field name="rs_fec_consec_bad_cw_link_fail_th_oper" descr="Returns the currently active threshold value (in consecutive FEC\;codewords) used to trigger link failure. Valid only when\;rs_fec_consec_bad_cw_link_fail_en_oper = 1." access="RO" offset="0x0.0" size="0x0.7" />
	<field name="rs_fec_consec_bad_cw_link_fail_th_admin" descr="Configures the number of consecutive uncorrectable RS FEC codewords\;required to trigger a link failure.0: FW DefaultValid range: 1-126 consecutive FEC codewords" access="RW" offset="0x0.11" size="0x0.7" />
	<field name="rs_fec_consec_bad_cw_link_fail_en_oper" descr="Returns the currently active enablement state of the RS FEC consecutive\;bad codeword link-fail mechanism.0: Disabled1: Enabled" access="RO" offset="0x0.22" size="0x0.1" />
	<field name="rs_fec_consec_bad_cw_link_fail_en_admin" descr="Configures the enablement of the RS FEC consecutive bad codeword\;link-fail mechanism.0: FW Default1: Enable - link will drop after the number of consecutive uncorrectable\;RS FEC codewords reaches the threshold set in\;rs_fec_consec_bad_cw_link_fail_th_oper2: Disable - link will not drop due to consecutive uncorrectable RS FEC\;codewords." access="RW" offset="0x0.24" size="0x0.2" />
</node>

<node name="plds_ext" descr="" attr_required_tlvs="index:s" size="0x18.0" >
	<field name="fec_uncor_cap" descr="When set, rs_fec_uncor_th is valid and configurable" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="plr_retry_cap" descr="When set, plr_csn_retry_th is valid and configurable" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="fec_uncor_force_cap" descr="For the link negotiation mechanism, does the host support forcing the\;threshold value of link drop trigger for number of uncorrectable FEC\;blocks - between the two connected ports.0 - Not supported1 - Supported" access="RO" offset="0x0.2" size="0x0.1" />
	<field name="plr_retry_force_cap" descr="For the link negotiation mechanism, does the host support forcing the\;threshold value of link drop trigger for number of PLR retry on same CSN\;- between the two connected ports.0 - Not supported1 - Supported" access="RO" offset="0x0.3" size="0x0.1" />
	<field name="fec_uncor_force" descr="If set, force the rs_fec_uncor_th value on the peer port" access="RW" offset="0x0.4" size="0x0.1" />
	<field name="plr_retry_force" descr="If set, force the plr_csn_retry_th value on the peer port" access="RW" offset="0x0.5" size="0x0.1" />
	<field name="delayed_recovery_force" descr="If set, force the delayed_recovery_admin value on the peer port" access="RW" offset="0x0.6" size="0x0.1" />
	<field name="delayed_recovery_cap" descr="When set, delayed_recovery fields are valid and configurable" access="RO" offset="0x0.7" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]." access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type, determines the way local_port is interpreted:0 - Local port number.1 - IB port number." access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="neg_res" descr="The negotiation result capability bit.Indicates the negotiation results for supporting the transition of the\;down request opcodes between the link partners.0: The device doesn’t support receiving remote down request opcodes.1: The device support receiving remote down request opcodes.Note: While this bit is set to ‘0’, the link-down default states\;configurations will not be operational.This bit will be set to ‘1’ in case the following 2 conditions are met:- Both the link partners are NVIDIA devices.- Both the link partners are XDR devices and above." access="RO" offset="0x4.0" size="0x0.1" />
	<field name="link_dwn_default_state_cfg" descr="The user can configure or retrieve the LinkDownDefaultState:0: Polling1: Sleep2: Disable" access="RW" offset="0x4.4" size="0x0.4" />
	<field name="link_down_cap" descr="The link-down states capability mask:Bit 0: LinkDownDefaultStateBit 1: PollingBit 2: SleepBit 3: Disable" access="RO" enum="LinkDownDefaultState=0x1,Polling=0x2,Sleep=0x4,Disable=0x8" offset="0x4.10" size="0x0.8" />
	<field name="config_down_cap" descr="Capability mask for the supported reasons for link-down request:Bit 0: LinkLocalErrorDefaultStateBit 1: LinkRemoteErrorDefaultStateBit 2: RemoteDownCMD2DisableBit 3: RemoteDownCMD2SleepBit 4: RemoteDownDueToResetBit 5: RemoteDownDueToUpperLayerDPBit 6: RemoteDownDueToPortLockBit 7: RemoteDownDueToThermalBit 8: RemoteDownDueToCintainMode" access="RO" enum="LinkLocalErrorDefaultState=0x1,LinkRemoteErrorDefaultState=0x2,RemoteDownCMD2Disable=0x4,RemoteDownCMD2Sleep=0x8,RemoteDownDueToReset=0x10,RemoteDownDueToUpperLayerDP=0x20,RemoteDownDueToPortLock=0x40,RemoteDownDueToThermal=0x80,RemoteDownDueToCintainMode=0x100" offset="0x4.21" size="0x0.11" />
	<field name="link_dwn_rmt_thermal_cfg" descr="The user can configure or retrieve the link-down default state for the\;RemoteDownDueToThermal down request:0: LinkDownDefaultState1: Polling2: Sleep3: DisableNote: TS1.PortLock opcode will be mapped to RemoteDownDueToThermal." access="RW" offset="0x8.1" size="0x0.3" />
	<field name="link_dwn_rmt_port_lock_cfg" descr="The user can configure or retrieve the link-down default state for the\;RemoteDownDueToPortLock down request:0: LinkDownDefaultState1: Polling2: Sleep3: DisableNote: TS1.PortLock opcode will be mapped to RemoteDownDueToPortLock." access="RW" offset="0x8.5" size="0x0.3" />
	<field name="link_dwn_rmt_up_layer_cfg" descr="The user can configure or retrieve the link-down default state for the\;RemoteDownDueToUpperLayerDP down request:0: LinkDownDefaultState1: Polling2: Sleep3: DisableNote: TS1.Force opcode will be mapped to RemoteDownDueToUpperLayerDP." access="RW" offset="0x8.9" size="0x0.3" />
	<field name="link_dwn_rmt_reset_cfg" descr="The user can configure or retrieve the link-down default state for the\;RemoteDownDueToReset down request:0: LinkDownDefaultState1: Polling2: Sleep3: DisableNote: TS1.reset_req opcode will be mapped to RemoteDownDueToReset." access="RW" offset="0x8.13" size="0x0.3" />
	<field name="link_dwn_rmt_sleep_cfg" descr="The user can configure or retrieve the link-down default state for the\;RemoteDownCMD2Sleep down request:0: LinkDownDefaultState1: Polling2: Sleep3: DisableNote: TS1.Sleep opcode will be mapped to RemoteDownCMD2Sleep." access="RW" offset="0x8.17" size="0x0.3" />
	<field name="link_dwn_rmt_disable_cfg" descr="The user can configure or retrieve the link-down default state for the\;RemoteDownCMD2Disable down request:0: LinkDownDefaultState1: Polling2: Sleep3: DisableNote: TS1.Disable opcode will be mapped to RemoteDownCMD2Disable." access="RW" offset="0x8.21" size="0x0.3" />
	<field name="link_dwn_rmt_error_cfg" descr="The user can configure or retrieve the link-down default state for the\;LinkRemoteErrorDefaultState down request:0: LinkDownDefaultState1: Polling2: Sleep3: DisableNote: TS1.Thermal opcode will be mapped to LinkRemoteErrorDefaultState." access="RW" offset="0x8.25" size="0x0.3" />
	<field name="link_dwn_local_error_cfg" descr="The user can configure or retrieve the link-down default state for the\;LinkLocalErrorDefaultState down request:0: LinkDownDefaultState1: Polling2: Sleep3: Disable" access="RW" offset="0x8.29" size="0x0.3" />
	<field name="set_mask" descr="The set bit mask allows the user to configure which fields to modify and\;which will not be changed on a set operation.Bit 0: LinkLocalErrorDefaultState_enBit 1: LinkRemoteErrorDefaultState_enBit 2: RemoteDownCMD2Disable_enBit 3: RemoteDownCMD2Sleep_enBit 4: RemoteDownDueToReset_enBit 5: RemoteDownDueToUpperLayerDP_enBit 6: RemoteDownDueToPortLock_enBit 7: RemoteDownDueToThermal_enBit 8: RemoteDownDueToContainMode" access="WO" enum="LinkLocalErrorDefaultState_en=0x1,LinkRemoteErrorDefaultState_en=0x2,RemoteDownCMD2Disable_en=0x4,RemoteDownCMD2Sleep_en=0x8,RemoteDownDueToReset_en=0x10,RemoteDownDueToUpperLayerDP_en=0x20,RemoteDownDueToPortLock_en=0x40,RemoteDownDueToThermal_en=0x80,RemoteDownDueToContainMode=0x100" offset="0xc.0" size="0x0.11" />
	<field name="link_dwn_rmt_contain_mode" descr="The user can configure or retrieve the link-down default state for the\;RemoteDownDueToContainMode down request:0: LinkDownDefaultState1: Polling2: Sleep3: DisableNote: TS1.PortLock opcode will be mapped to RemoteDownDueToContainMode." access="RW" offset="0xc.12" size="0x0.3" />
	<field name="linkup_retry_iterations" descr="Number of retry ‘N’ iterations allowed for linkup tries before going to\;link down default state.Valid only when link link_dwn_default_state_cfg is set to Sleep or\;Disabled states, ignored otherwise.0 - FW_default1-255 - ‘N’ retriesNote:Counter will iterate +1 only when exiting polling state (after peer side\;is detected)." access="RW" offset="0xc.24" size="0x0.8" />
	<field name="rs_fec_uncor_th" descr="Link drop trigger for number of uncorrectable FEC blocks in a 128 fec\;block window threshold.If threshold is crossed, link will be dropped or trigger recovery flow.0: FW_defaultIf fec_uncor_force_cap is cleared: On Get, when\;link is down, shall return the admin value to be configured. When link\;is up, returns operational value.If fec_uncor_force_cap is set: On Get,\;shall return the admin value to be configured." access="RW" offset="0x10.0" size="0x0.7" />
	<field name="plr_csn_retry_th_oper" descr="Operational value for the Link drop trigger for number of uncorrectable\;FEC blocks in a 128 fec block window threshold.Valid only if fec_uncor_force_cap is set." access="RO" offset="0x10.7" size="0x0.9" />
	<field name="plr_csn_retry_th" descr="Link drop trigger for number of PLR retry on same CSN threshold.If threshold is crossed, link will be dropped or trigger recovery flow.0: FW_defaultIf plr_retry_force_cap is cleared: On Get, when\;link is down, shall return the admin value to be configured. When link\;is up, returns operational value.If plr_retry_force_cap is set: On Get, shall return the admin value\;to be configured." access="RW" offset="0x10.16" size="0x0.9" />
	<field name="rs_fec_uncor_th_oper" descr="Operational value for the Link drop trigger for number of PLR retry on\;same CSN thresh.Valid only if plr_retry_force_cap is set." access="RO" offset="0x10.25" size="0x0.7" />
	<field name="delayed_recovery_oper" descr="0: not_supported1: delayed_recovery_enable2: delayed_recovery_disable" access="RO" offset="0x14.0" size="0x0.2" />
	<field name="delayed_recovery_admin" descr="0: Auto (based on FW default - INI)1: delayed_recovery_enable2: delayed_recovery_disable" access="RW" offset="0x14.2" size="0x0.2" />
</node>

<node name="plib_reg_ext" descr="" size="0x10.0" >
	<field name="ib_port" descr="In IB port: InfiniBand port remapping for local_portIn Ethernet port: Label port remapping for local_portNote: ib_port number can only be updated when a port admin state is\;DISABLED." access="RW" offset="0x0.0" size="0x0.10" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="split_num" descr="Valid only for Ethernet Switches.Label split mapping for local_portValid values:For Spectrum 1 to 4: 1, 2, 4, 8For Spectrum 5, 6: 1…6, 8" access="RW" offset="0x4.0" size="0x0.4" />
</node>

<node name="plibdb_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ib_port_1x" descr="IB port remapping for local port when port is configured in width of 1x.Note: This value is theoretical and not the actual configurationRange: 1.. cap_max_switch_portsValue of 0 means port is unmapped." access="RO" offset="0x4.0" size="0x0.10" />
	<field name="ib_port_2x" descr="IB port remapping for local port when port is configured in width of 2x.Note: This value is theoretical and not the actual configurationRange: 1.. cap_max_switch_portsValue of 0 means port is unmapped" access="RO" offset="0x8.0" size="0x0.10" />
	<field name="ib_port_4x" descr="IB port remapping for local port when port is configured in width of 4x.Note: This value is theoretical and not the actual configurationRange: 1.. cap_max_switch_portsValue of 0 means port is unmapped" access="RO" offset="0xc.0" size="0x0.10" />
</node>

<node name="pltc_reg_ext" descr="" attr_required_tlvs="index:s" size="0x10.0" >
	<field name="lane_mask" descr="for set operation, lane bitmaskfor query operation, only one bit shall be set" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0: Local_port_number1: IB_port_number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="precoding_cap_mask" descr="0x0 - no tx precoding available / no override capabilityBit 0- tx precoding override possible via local_tx_precoding_admin fieldBit 1- rx precoding override possible via local_rx_precoding_admin field" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="local_tx_precoding_admin" descr="Relevant only if active link speed is PAM4 (&gt;50G), otherwise ignoredTx configuration override per lane.0 - auto1 - force Tx precoding2 - force Tx without precoding" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="precoding_mask" descr="0 - Default: All fields in PLTC should be reconfigured1 - Only PLTC.local_rx_precoding_admin should be configured2 - Only PLTC.local_tx_precoding_admin should be configured3 - Only PLTC.local_rx_precoding_admin and PLTC.local_tx_precoding_admin\;should be configured" access="RW" offset="0x8.8" size="0x0.2" />
	<field name="local_rx_precoding_admin" descr="Relevant only if active link speed is PAM4 (&gt;50G), otherwise ignoredRx configuration override per lane.0 - auto1 - Rx precoding enabled.if negotiated, request Tx precoding from peer.2 - Rx precoding disabled.if negotiated, request no Tx precoding from peer" access="RW" offset="0x8.16" size="0x0.2" />
	<field name="local_tx_precoding_oper" descr="0 - unknown / no active link1 - Tx precoding enabled.2 - Tx precoding disabled." access="RO" offset="0xc.0" size="0x0.2" />
	<field name="local_rx_precoding_oper" descr="Rx precoding operational mode0 - unknown / no active link1 - Rx precoding enabled.2 - Rx precoding disabled." access="RO" offset="0xc.16" size="0x0.2" />
</node>

<node name="plu_general_tracer_page_ext" descr="" size="0x18.0" >
	<field name="cw_bad_cap" descr="Indicates the number of FEC engines in the port that report valid values\;in the max_consec_cw_bad_cnt_fec_i fields. This depends on the number of\;FEC engines used in the port.0: non_valid1: fec0_valid2: fec0_to_fec1_valid3: fec0_to_fec3_valid" access="RO" enum="non_valid=0x0,fec0_valid=0x1,fec0_to_fec1_valid=0x2,fec0_to_fec3_valid=0x3" offset="0x0.0" size="0x0.2" />
	<field name="hist_cap" descr="Indicates the number of FEC engines in the port that report valid values\;in the Previous_i_FEC_block_histogram fields. This depends on the number\;of FEC engines used in the port.0: non_valid1: fec0_valid2: fec0_to_fec1_valid" access="RO" enum="non_valid=0x0,fec0_valid=0x1,fec0_to_fec1_valid=0x2" offset="0x0.3" size="0x0.2" />
	<field name="clear_on_read_admin" descr="Configures FW behavior for clearing fields.0: fw_default1: clear_on_read - FW will always clear latched values on get\;requests2: no_clear_on_read" access="RW" enum="fw_default=0x0,clear_on_read=0x1,no_clear_on_read=0x2" offset="0x0.10" size="0x0.2" />
	<field name="clear_on_recovery_success_admin" descr="Configures FW behavior for clearing fields on end of recovery success.\;If recovery failed link drops and values are latched until manually\;cleared with link toggle.Field is relevant only if recovery is enabled.0: fw_default1: clear_on_success - FW will clear values after recovery success2: no_clear_on_success" access="RW" enum="fw_default=0x0,clear_on_success=0x1,no_clear_on_success=0x2" offset="0x0.13" size="0x0.2" />
	<field name="cw_bad_stop_condition_cap" descr="Indicates which stop conditions are supported in the port for\;max_consec_cw_bad_cnt_fec_i fields.Bit 0: Link FailBit 1: First UncorrectableNote: field is valid only if cw_bad_cap is non zero." access="RO" offset="0x0.17" size="0x0.2" />
	<field name="hist_stop_condition_cap" descr="Indicates which stop conditions are supported in the port for\;Previous_i_FEC_block_histogram fields.Bit 0: Link FailBit 1: First UncorrectableNote: field is valid only if hist_cap is non zero." access="RO" offset="0x0.21" size="0x0.2" />
	<field name="cw_bad_stop_condition_oper" descr="Configured stop condition for max_consec_cw_bad_cnt_fec_i fields. Admin\;value set with stop_condition_hist field.0: Link Fail1: First Uncorrectable" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="hist_stop_condition_oper" descr="Configured stop condition for Previous_i_FEC_block_histogram fields.\;Admin value set with stop_condition_hist field.0: Link Fail1: First Uncorrectable" access="RO" offset="0x0.26" size="0x0.1" />
	<field name="cw_bad_stop_condition" descr="Sets stop condition for max_consec_cw_bad_cnt_fec_i fields. Once stop\;condition is met relevant fields are latched.0: Link Fail1: First Uncorrectable" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="hist_stop_condition" descr="Sets stop condition for Previous_i_FEC_block_histogram fields. Once stop\;condition is met relevant fields are latched.0: Link Fail1: First Uncorrectable" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Clear all latched values in page. This bit can be set for both Set() and\;Get() operation0: Do nothing1: Clear" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="Previous_7_FEC_block_histogram_fec0" descr="(see above)" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="Previous_6_FEC_block_histogram_fec0" descr="(see above)" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="Previous_5_FEC_block_histogram_fec0" descr="(see above)" access="RO" offset="0x4.8" size="0x0.4" />
	<field name="Previous_4_FEC_block_histogram_fec0" descr="(see above)" access="RO" offset="0x4.12" size="0x0.4" />
	<field name="Previous_3_FEC_block_histogram_fec0" descr="(see above)" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="Previous_2_FEC_block_histogram_fec0" descr="(see above)" access="RO" offset="0x4.20" size="0x0.4" />
	<field name="Previous_1_FEC_block_histogram_fec0" descr="(see above)" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="Previous_0_FEC_block_histogram_fec0" descr="Histogram bin the i+1 previous FEC block belongs to in FEC engine 0.\;Latched when PLU general tracer stop condition is met" access="RO" offset="0x4.28" size="0x0.4" />
	<field name="Previous_7_FEC_block_histogram_fec1" descr="(see above)" access="RO" offset="0x8.0" size="0x0.4" />
	<field name="Previous_6_FEC_block_histogram_fec1" descr="(see above)" access="RO" offset="0x8.4" size="0x0.4" />
	<field name="Previous_5_FEC_block_histogram_fec1" descr="(see above)" access="RO" offset="0x8.8" size="0x0.4" />
	<field name="Previous_4_FEC_block_histogram_fec1" descr="(see above)" access="RO" offset="0x8.12" size="0x0.4" />
	<field name="Previous_3_FEC_block_histogram_fec1" descr="(see above)" access="RO" offset="0x8.16" size="0x0.4" />
	<field name="Previous_2_FEC_block_histogram_fec1" descr="(see above)" access="RO" offset="0x8.20" size="0x0.4" />
	<field name="Previous_1_FEC_block_histogram_fec1" descr="(see above)" access="RO" offset="0x8.24" size="0x0.4" />
	<field name="Previous_0_FEC_block_histogram_fec1" descr="Histogram bin the i+1 previous FEC block belongs to in FEC engine 1.\;Latched when PLU general tracer stop condition is met" access="RO" offset="0x8.28" size="0x0.4" />
	<field name="max_consec_cw_bad_cnt_fec3" descr="Holds the maximum number of consecutive uncorrectable FEC codewords (FEC\;blocks) that were received in FEC engine 3." access="RO" offset="0xc.4" size="0x0.7" />
	<field name="max_consec_cw_bad_cnt_fec2" descr="Holds the maximum number of consecutive uncorrectable FEC codewords (FEC\;blocks) that were received in FEC engine 2." access="RO" offset="0xc.11" size="0x0.7" />
	<field name="max_consec_cw_bad_cnt_fec1" descr="Holds the maximum number of consecutive uncorrectable FEC codewords (FEC\;blocks) that were received in FEC engine 1." access="RO" offset="0xc.18" size="0x0.7" />
	<field name="max_consec_cw_bad_cnt_fec0" descr="Holds the maximum number of consecutive uncorrectable FEC codewords (FEC\;blocks) that were received in FEC engine 0." access="RO" offset="0xc.25" size="0x0.7" />
</node>

<node name="plu_latched_counters_page_ext" descr="" size="0x18.0" >
	<field name="max_plr_retry_cnt_cap" descr="When set, indicates port supports max_retry_cnt_latch counter and the\;value is valid." access="RO" offset="0x0.0" size="0x0.1" />
	<field name="clear_on_read_admin" descr="Configures FW behavior for clearing fields.0: fw_default1: clear_on_read - FW will always clear latched values on get\;requests2: no_clear_on_read" access="RW" enum="fw_default=0x0,clear_on_read=0x1,no_clear_on_read=0x2" offset="0x0.10" size="0x0.2" />
	<field name="clear_on_recovery_success_admin" descr="Configures FW behavior for clearing fields on end of recovery success.\;If recovery failed link drops and values are latched until manually\;cleared with link toggle.Field is relevant only if recovery is enabled.0: fw_default1: clear_on_success - FW will clear values after recovery success2: no_clear_on_success" access="RW" enum="fw_default=0x0,clear_on_success=0x1,no_clear_on_success=0x2" offset="0x0.13" size="0x0.2" />
	<field name="clr" descr="Clear all latched values in page. This bit can be set for both Set() and\;Get() operation0: Do nothing1: Clear" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="max_plr_retry_cnt_latch" descr="Holds the maximum number of consecutive retransmissions conducted on a\;single FEC codeword by PLR" access="RO" offset="0x4.16" size="0x0.16" />
</node>

<node name="pmac_reg_ext" descr="" attr_required_tlvs="index:s" size="0x28.0" >
	<field name="lp_msb" descr="not relevant for port_module = module indexLocal port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port isinterpreted:0: Local_port_number1: IB_port_number3: Out_of_band_or_PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="if port_module = local port-&gt; Local port numberif port_module = module index -&gt; Module number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="apsu_cap" descr="APSU (ILT/RTS) capability supported. for the all data path" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="apsu_ctl" descr="Control the APSU (ILT/RTS) activation if apsu_cap = 1. Single value for\;both sides.0: Use FW default. Default1: Enable2: Disable" access="RW" offset="0x4.2" size="0x0.2" />
	<field name="training_en_cap_host" descr="Disable training option capability. on the host sideNote that when disabled the ASPU protocol is still active but without\;link training frames." access="RW" offset="0x8.0" size="0x0.1" />
	<field name="training_en_ctl_host" descr="Control the training_en configuration if training_en_cap_host = 10: Use FW default. Default1: Enable training2: Disable training" access="RO" offset="0x8.2" size="0x0.2" />
	<field name="restart_training_host" descr="Set to restart APSU on the host side" access="WO" offset="0x8.31" size="0x0.1" />
	<field name="training_en_cap_line" descr="Disable training option capability. on the line sideNote that when disabled the ASPU protocol is still active but without\;link training frames." access="RW" offset="0xc.0" size="0x0.1" />
	<field name="training_en_ctl_line" descr="Control the training_en configuration if training_en_cap_line = 10: Use FW default. Default1: Enable training2: Disable training" access="RO" offset="0xc.2" size="0x0.2" />
	<field name="restart_training_line" descr="Set to restart APSU on the line side" access="WO" offset="0xc.31" size="0x0.1" />
</node>

<node name="pmaos_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Module state (reserved while admin_status is disabled):0: initializing 1: plugged_enabled2: unplugged3: module_plugged_with_error - (details in error_type).5: unknown" access="RO" enum="initializing=0x0,plugged_enabled=0x1,unplugged=0x2,module_plugged_with_error=0x3,unknown=0x5" offset="0x0.0" size="0x0.4" />
	<field name="admin_status" descr="Module administrative state (the desired state of the module):1: enabled2: disabled_by_configuration3: enabled_once - if the module is active and then unplugged, or\;module experienced an error event, the operational status should go\;to “disabled” and can only be enabled upon explicit enable command.0xe: disconnect_cableNote - To disable a module, all ports associated with the port must\;be disabled first.Note 2 - disconnect cable will shut down the optical module in\;ungraceful manner." access="RW" enum="enabled=0x1,disabled_by_configuration=0x2,enabled_once=0x3,disconnect_cable=0xe" offset="0x0.8" size="0x0.4" />
	<field name="module" descr="Module number bits [7:0]." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="rst" descr="Module Reset toggleNOTE: setting reset while module is plugged-in will result in transition\;of oper_status to initialization." access="OP" offset="0x0.31" size="0x0.1" />
	<field name="e" descr="Event Generation on operational state change:0: Do_not_generate_event1: Generate_Event2: Generate_Single_EventNot supported by secondary ASICs." access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="ref_module_valid" descr="[Switch][DWIP]1: ref_module field valid." access="RO" offset="0x4.2" size="0x0.1" />
	<field name="error_type" descr="Module error details:0x0: Power_Budget_Exceeded0x1: Long_Range_for_non_MLNX_cable_or_module0x2: Bus_stuck - (I2C Data or clock shorted)0x3: bad_or_unsupported_EEPROM0x4: Enforce_part_number_list0x5: unsupported_cable0x6: High_Temperature0x7: bad_cable - (Module/Cable is shorted)0x8: PMD_type_is_not_enabled - (see PMTPS)\;\;\;0xc: pcie_system_power_slot_Exceeded\;\;\;[DWIP] 0xf: Boot_error\;[DWIP] 0x10: Recovery_error\;[DWIP] 0x11: Submodule_failure\;[DWIP] 0x12: serbi_check_failure\;[DWIP] 0x13: els_critical_indication\;Valid only when oper_status = 4’b0011" access="RO" enum="Power_Budget_Exceeded=0x0,Long_Range_for_non_MLNX_cable_or_module=0x1,Bus_stuck=0x2,bad_or_unsupported_EEPROM=0x3,Enforce_part_number_list=0x4,unsupported_cable=0x5,High_Temperature=0x6,bad_cable=0x7,PMD_type_is_not_enabled=0x8,pcie_system_power_slot_Exceeded=0xc" offset="0x4.8" size="0x0.5" />
	<field name="operational_notification" descr="This notification can occur only if module passed initialization process0x0: No notifications.0x1: Speed degradation – the module is not enabled in its full speed due\;to incompatible transceiver/cableValid only when oper_status = 4’b0001." access="RO" offset="0x4.16" size="0x0.4" />
	<field name="module_msb" descr="[Switch][DWIP]Module number bits [15:8]." access="INDEX" offset="0x4.20" size="0x0.8" />
	<field name="rev_incompatible" descr="When in multi ASIC module sharing systems,This flag will be asserted in case primary and secondary FW versions are\;not compatible." access="RO" offset="0x4.28" size="0x0.1" />
	<field name="secondary" descr="Indicates whether the ASIC serves as a the modules secondary (=1) or\;primary (=0) device." access="RO" offset="0x4.29" size="0x0.1" />
	<field name="ee" descr="Event update enable. If this bit is set, event generation will be\;updated based on the e field. Only relevant on Set operations.Not supported by secondary ASICs." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="ase" descr="Admin status update enable. If this bit is set, admin state will be\;updated based on admin_state field. Only relevant on Set() operations." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="ref_module" descr="[Switch][DWIP]Reference module index." access="RO" offset="0x8.0" size="0x0.16" />
</node>

<node name="pmcr_reg_ext" descr="" attr_required_tlvs="index:s" size="0x2c.0" >
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="error_code_response" descr="Valid for CMIS modules.error code response on override values.0x0: ConfigUndefined0x1: ConfigSuccess0x2: ConfigRejected0x3: ConfigRejectedInvalidAppSel0x4: ConfigRejectedInvalidDataPath0x5: ConfigRejectedInvalidSI0x6: ConfigRejectedLanesInUse0x7: ConfigRejectedPartialDataPath0xC: ConfigInProgress" access="RO" enum="ConfigUndefined=0x0,ConfigSuccess=0x1,ConfigRejected=0x2,ConfigRejectedInvalidAppSel=0x3,ConfigRejectedInvalidDataPath=0x4,ConfigRejectedInvalidSI=0x5,ConfigRejectedLanesInUse=0x6,ConfigRejectedPartialDataPath=0x7,ConfigInProgress=0xc" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cdr_override_cntl" descr="Module CDR override control:0 - Auto (default)1 - Keep the module configuration2 - Override" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="cdr_override_cap" descr="Module TX and RX override control capability.Bit 0 - RX CDR control is possibleBit 0 - TX CDR control is possible" access="RO" offset="0x4.2" size="0x0.2" />
	<field name="cdr_override_value" descr="Valid only in case CDR is configured to override mode by\;cdr_override_cntl:0 - RX OFF, TX OFF1 - RX ON, TX OFF2 - RX OFF, TX ON3 - RX ON, TX ON" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="tx_disable_override_cntl" descr="In HCA, valid based on PCAM feature capabilities.Module TX_DISABLE override control:0 - Auto (default)1 - Keep the module configuration2 - Override" access="RW" offset="0x4.16" size="0x0.2" />
	<field name="tx_disable_override_value" descr="Valid only in case TX_DISABLE is configured to override mode by\;tx_disable_override_cntl:0 - TX_DISABLE is low (i.e. TX is enabled)1 - TX_DISABLE is high (i.e. TX is disabled)" access="RW" offset="0x4.24" size="0x0.2" />
	<field name="rx_amp_override_cntl" descr="Module RX amplitude override control:0 - Auto (default)1 - Keep the module configuration2 - Override" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="rx_amp_override_cap" descr="Module rx_amp override control capability." access="RO" offset="0x8.2" size="0x0.1" />
	<field name="rx_amp_override_value" descr="Valid only in case RX amplitude is configured to override mode by\;rx_amp_override_cntl" access="RW" offset="0x8.8" size="0x0.4" />
	<field name="rx_amp_override_value_cap" descr="Module rx_amp bitmask of allowed values." access="RO" offset="0x8.12" size="0x0.4" />
	<field name="rx_los_override_cntl" descr="Valid only in case RX_LOS is configured to override mode by\;rx_los_override_admin" access="RW" offset="0x8.16" size="0x0.2" />
	<field name="rx_los_override_cap" descr="Module RX_LOS override control capability." access="RO" offset="0x8.18" size="0x0.1" />
	<field name="rx_los_override_admin" descr="Module RX_LOS override control:0 - Auto (default)1 - Keep the module configuration2 - Override" access="RW" offset="0x8.24" size="0x0.2" />
	<field name="rx_emp_override_cntl" descr="Module RX emphasis override control:0 - Auto (default)1 - Keep the module configuration2 - Override" access="RW" offset="0xc.0" size="0x0.2" />
	<field name="rx_emp_override_cap" descr="Module rx_emp override control capability." access="RO" offset="0xc.2" size="0x0.1" />
	<field name="rx_emp_override_value" descr="For CMIS modules, pre emphasis equalization value.For SFF modules, emphasis equalization value.Valid only in case RX emphasis is configured to override mode by\;rx_emp_override_cntl" access="RW" offset="0xc.8" size="0x0.4" />
	<field name="rx_emp_override_value_cap" descr="Module rx_emp max allowed values." access="RO" offset="0xc.12" size="0x0.4" />
	<field name="rx_post_emp_override_cntl" descr="Module RX emphasis override control:0 - Auto (default)1 - Keep the module configuration2 - Override" access="RW" offset="0xc.16" size="0x0.2" />
	<field name="rx_post_emp_override_cap" descr="Module rx_post_emp override control capability." access="RO" offset="0xc.18" size="0x0.1" />
	<field name="rx_post_emp_override_value" descr="Valid for CMIS modules only.Post emphasis equalization value.Valid only in case RX emphasis is configured to override mode by\;rx_post_emp_override_cntl" access="RW" offset="0xc.24" size="0x0.4" />
	<field name="rx_post_emp_override_value_cap" descr="Module rx_post_emp max allowed values." access="RO" offset="0xc.28" size="0x0.4" />
	<field name="tx_equ_override_cntl" descr="Module TX equalization override control:0 - Auto (default)1 - Keep the module configuration2 - Override" access="RW" offset="0x10.0" size="0x0.2" />
	<field name="tx_equ_override_cap" descr="Module TX equalization override control capability." access="RO" offset="0x10.2" size="0x0.1" />
	<field name="tx_equ_override_value" descr="Valid only in case TX equalization is configured to override mode by\;tx_equ_override_cntl." access="RW" offset="0x10.8" size="0x0.4" />
	<field name="tx_equ_override_value_cap" descr="Module tx_eq max allowed values." access="RO" offset="0x10.12" size="0x0.4" />
	<field name="tx_adaptive_override_value" descr="0 - disable adaptive Tx Equalization1 - enable adaptive Tx equalizationValid only in case TX equalization is configured to override mode by\;tx_adaptive_override_cntrl." access="RW" offset="0x10.17" size="0x0.1" />
	<field name="tx_adaptive_override_cntrl" descr="Module adaptive tuning flow override control:\;0 - Auto (default)\;1 - Keep the module configuration2 - override" access="RW" offset="0x10.24" size="0x0.2" />
	<field name="tx_adaptive_override_cap" descr="Module TX adaptive tuning flow override control capability." access="RO" offset="0x10.26" size="0x0.1" />
	<field name="ap_sel_override_cntrl" descr="Module Application select override control:\;0 - Auto (default)\;1 - Use Module’s Default application value\;2 - Override" access="RW" offset="0x18.0" size="0x0.2" />
	<field name="ap_sel_override_value" descr="Application Select from the applications list advertised by the module.\;Up to 15 applications available.\;Values range from 1 to 15.\;Note: application can be set with default SI values defined by the\;module or SI defined by the host" access="RW" offset="0x18.8" size="0x0.4" />
	<field name="dr_cap" descr="capabilities of the module 200g per lane SMF DR applications (Bitmask):\;Bit 0 - DR\;Bit 1 - DR-2" access="RO" offset="0x18.24" size="0x0.2" />
	<field name="dr_admin" descr="When using PTYS and selecting an application, for the host, there could\;be a situation where the module support more then one option for the\;same host electrical application.this field is used to set the default application in the module for the\;Ethernet 200G generation, and distinguish between DR and DR-2 option.the module capability can be observed on dr_capthis field uses for setting the default option to choose between DR and\;DR-2.NOTE: relevant only when dr_cap have more than 1 options. if only one of\;them is supported, this is will be the selected application0x0 - FW default0x1 - DR0x2 - DR-2" access="RW" offset="0x18.28" size="0x0.2" />
	<field name="media_type_override_cntl" descr="Module media type override control:0 - Auto (default)1 - Keep the module configuration2 - Override" access="RW" offset="0x1c.0" size="0x0.2" />
	<field name="media_type_override_cap" descr="Media type override capability is possible via media_type_override_cntrl\;field" access="RO" offset="0x1c.2" size="0x0.1" />
	<field name="media_type_override_value" descr="Valid only in case media_type_override_cntrl is configured to override\;mode.Configures module media type peer side for optimal performance0: Peer_is_retimed_module1: Peer_is_CPO_module 2: reserved3: reserved" access="RW" offset="0x1c.8" size="0x0.2" />
	<field name="prec_host_tx_override_cntl" descr="Precoding host Tx override control.0 - Auto (FW default)1 - Keep the module configuration - module read2 - Override - overrides according to prec_host_tx_override_valNote:According to configured value above,get operation prec_host_tx_override_val reads the value which is indexed\;to." access="RW" offset="0x20.0" size="0x0.2" />
	<field name="prec_host_rx_override_cntl" descr="Precoding host Rx override control.0 - Auto (FW default)1 - Keep the module configuration - module read2 - Override - overrides according to prec_host_rx_override_valNote:According to configured value above,get operation prec_host_rx_override_val reads the value which is indexed\;to." access="RW" offset="0x20.2" size="0x0.2" />
	<field name="prec_host_cap" descr="Precoding host override is supported" access="RO" offset="0x20.7" size="0x0.1" />
	<field name="prec_host_tx_override_val" descr="Precoding host Tx override value.Set is valid only in case prec_host_tx_override_cntl is configured to\;override mode.0: precoding_line_tx_disabled1: precoding_line_tx_enabled" access="RW" offset="0x20.8" size="0x0.1" />
	<field name="prec_host_rx_override_val" descr="Precoding host Rx override value.Set is valid only in case prec_host_rx_override_cntl is configured to\;override mode.0: precoding_host_rx_disabled1: precoding_host_rx_enabled" access="RW" offset="0x20.9" size="0x0.1" />
	<field name="prec_line_tx_override_cntl" descr="Precoding line Tx override control.0 - Auto (FW default)1 - Keep the module configuration - module read2 - Override - overrides according to prec_line_tx_override_valNote:According to configured value above,get operation prec_line_tx_override_val reads the value which is indexed\;to." access="RW" offset="0x20.16" size="0x0.2" />
	<field name="prec_line_rx_override_cntl" descr="Precoding line Rx override control.0 - Auto (FW default)1 - Keep the module configuration - module read2 - Override - overrides according to prec_line_rx_override_valNote:According to configured value above,get operation prec_line_rx_override_val reads the value which is indexed\;to." access="RW" offset="0x20.18" size="0x0.2" />
	<field name="prec_line_cap" descr="Precoding line override is supported" access="RO" offset="0x20.23" size="0x0.1" />
	<field name="prec_line_tx_override_val" descr="Precoding line Tx override value.Set is valid only in case prec_line_tx_override_cntl is configured to\;override mode.0: precoding_line_tx_disabled1: precoding_line_tx_enabled" access="RW" offset="0x20.24" size="0x0.1" />
	<field name="prec_line_rx_override_val" descr="Precoding line Rx override value.Set is valid only in case prec_line_rx_override_cntl is configured to\;override mode.0: precoding_line_rx_disabled1: precoding_line_rx_enabled" access="RW" offset="0x20.25" size="0x0.1" />
</node>

<node name="pmdr_reg_ext" descr="" attr_required_tlvs="index:s" size="0x48.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="width_valid" descr="When set, port_width field value is valid. otherwise ignored" access="RO" offset="0x0.10" size="0x0.1" />
	<field name="mcm_tile_valid" descr="0 if there is no MCM tile arch" access="RO" offset="0x0.12" size="0x0.1" />
	<field name="gb_valid" descr="0 if there is no Gearbox/Retimer arch" access="RO" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="[7:0] bits for Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0 - 40nm products1 - 28nm products3 - 16nm products4 - 7nm products5 - 5nm products SerDes Gen7.0/ 7.56 - 5nm products SerDes Gen8.0" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid1 - Valid2 - Bad Param (Values are not ready yet - during polling)3 - Invalid index of local_port or label_port" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="pport_msb" descr="[9:8] pport bits" access="RO" offset="0x4.6" size="0x0.2" />
	<field name="cluster" descr="Logical cluster number" access="RO" offset="0x4.8" size="0x0.7" />
	<field name="module" descr="" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="pport" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="ib_port" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="module_lane_mask" descr="lane mask of active lanes on moduleBit 0: Lane 0Bit 1: Lane 1Bit 2: Lane 2Bit 3: Lane 3Bit 4: Lane 4Bit 5: Lane 5Bit 6: Lane 6Bit 7: Lane 7" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="swid" descr="" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="split" descr="Number of ports the label port is split to.0 - split to 11 - split to 22 - split to 43 - split to 84 - split to 35 - split to 56 - split to 67 - split to 7" access="RO" offset="0x8.24" size="0x0.3" />
	<field name="gb_dp_num" descr="DataPath number in GB/Retimer of the port" access="RO" offset="0x8.27" size="0x0.5" />
	<field name="lp_query_msb" descr="MSB Local port bits [9:8] index for the label port chosen (in case pnat\;field is ‘1’)." access="RO" offset="0xc.0" size="0x0.2" />
	<field name="lbp_query_msb" descr="MSB Label port bits [9:8] index." access="RO" offset="0xc.2" size="0x0.2" />
	<field name="tile_pport_msb" descr="MSB tile_pport bits [7:6] index." access="RO" offset="0xc.4" size="0x0.2" />
	<field name="port_width" descr="Port width of logical lanes.According to number of port width, indicates how many lanes shall be\;considered in lane&lt;i&gt;_physical_tx/rx0 - port is unmapped" access="RO" offset="0xc.6" size="0x0.4" />
	<field name="local_port_query" descr="LSB Local port bits [7:0] index for the label port chosen (in case pnat\;field is ‘1’)." access="RO" offset="0xc.16" size="0x0.8" />
	<field name="label_port_query" descr="Label port index for the local port chosen (in case pnat field is ‘0’)." access="RO" offset="0xc.24" size="0x0.8" />
	<field name="gearbox_die_num" descr="Number of the Gearbox/Retimer the local_port is related to.valid only when gb_valid is 1" access="RO" offset="0x10.0" size="0x0.7" />
	<field name="tile_pport" descr="" access="RO" offset="0x10.8" size="0x0.5" />
	<field name="pll_cnt_rx" descr="Number of common PLLs mapped to port rx lanes." access="RO" offset="0x10.13" size="0x0.3" />
	<field name="mcm_tile_num" descr="Number of the MCM Tile the local_port is related to.valid only when mcm_tile_valid is 1" access="RO" offset="0x10.16" size="0x0.8" />
	<field name="tile_cluster" descr="" access="RO" offset="0x10.24" size="0x0.4" />
	<field name="slot_index" descr="Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available." access="RO" offset="0x10.28" size="0x0.4" />
	<field name="lane0_physical_rx" descr="(see above)" access="RO" offset="0x14.0" size="0x0.3" />
	<field name="lane1_physical_rx" descr="(see above)" access="RO" offset="0x14.3" size="0x0.3" />
	<field name="lane2_physical_rx" descr="(see above)" access="RO" offset="0x14.6" size="0x0.3" />
	<field name="lane3_physical_rx" descr="(see above)" access="RO" offset="0x14.9" size="0x0.3" />
	<field name="lane4_physical_rx" descr="(see above)" access="RO" offset="0x14.12" size="0x0.3" />
	<field name="lane5_physical_rx" descr="(see above)" access="RO" offset="0x14.15" size="0x0.3" />
	<field name="lane6_physical_rx" descr="(see above)" access="RO" offset="0x14.18" size="0x0.3" />
	<field name="lane7_physical_rx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical rx lane mapping" access="RO" offset="0x14.21" size="0x0.3" />
	<field name="pll_cnt_tx" descr="Number of common PLLs mapped to port for tx lanes." access="RO" offset="0x14.24" size="0x0.3" />
	<field name="vl_num" descr="largest VL number of the port.for e.g if vl_num = 3VL&lt;0-3&gt;_lane_map are only valid" access="RO" offset="0x14.27" size="0x0.5" />
	<field name="lane0_physical_tx" descr="(see above)" access="RO" offset="0x18.0" size="0x0.3" />
	<field name="lane1_physical_tx" descr="(see above)" access="RO" offset="0x18.3" size="0x0.3" />
	<field name="lane2_physical_tx" descr="(see above)" access="RO" offset="0x18.6" size="0x0.3" />
	<field name="lane3_physical_tx" descr="(see above)" access="RO" offset="0x18.9" size="0x0.3" />
	<field name="lane4_physical_tx" descr="(see above)" access="RO" offset="0x18.12" size="0x0.3" />
	<field name="lane5_physical_tx" descr="(see above)" access="RO" offset="0x18.15" size="0x0.3" />
	<field name="lane6_physical_tx" descr="(see above)" access="RO" offset="0x18.18" size="0x0.3" />
	<field name="lane7_physical_tx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical tx lane mapping" access="RO" offset="0x18.21" size="0x0.3" />
	<field name="pll_index" descr="minimal index of pll group of pll that port uses for tx lanes.For all common pll’s that are mapped to the port: [pll_index, pll_index+\;1, … pll_index + pll_cnt]" access="RO" offset="0x18.24" size="0x0.8" />
	<field name="VL0_lane_map" descr="(see above)" access="RO" offset="0x1c.0" size="0x0.4" />
	<field name="VL1_lane_map" descr="(see above)" access="RO" offset="0x1c.4" size="0x0.4" />
	<field name="VL2_lane_map" descr="(see above)" access="RO" offset="0x1c.8" size="0x0.4" />
	<field name="VL3_lane_map" descr="(see above)" access="RO" offset="0x1c.12" size="0x0.4" />
	<field name="VL4_lane_map" descr="(see above)" access="RO" offset="0x1c.16" size="0x0.4" />
	<field name="VL5_lane_map" descr="(see above)" access="RO" offset="0x1c.20" size="0x0.4" />
	<field name="VL6_lane_map" descr="(see above)" access="RO" offset="0x1c.24" size="0x0.4" />
	<field name="VL7_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x1c.28" size="0x0.4" />
	<field name="VL8_lane_map" descr="(see above)" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="VL9_lane_map" descr="(see above)" access="RO" offset="0x20.4" size="0x0.4" />
	<field name="VL10_lane_map" descr="(see above)" access="RO" offset="0x20.8" size="0x0.4" />
	<field name="VL11_lane_map" descr="(see above)" access="RO" offset="0x20.12" size="0x0.4" />
	<field name="VL12_lane_map" descr="(see above)" access="RO" offset="0x20.16" size="0x0.4" />
	<field name="VL13_lane_map" descr="(see above)" access="RO" offset="0x20.20" size="0x0.4" />
	<field name="VL14_lane_map" descr="(see above)" access="RO" offset="0x20.24" size="0x0.4" />
	<field name="VL15_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x20.28" size="0x0.4" />
	<field name="VL16_lane_map" descr="(see above)" access="RO" offset="0x24.0" size="0x0.4" />
	<field name="VL17_lane_map" descr="(see above)" access="RO" offset="0x24.4" size="0x0.4" />
	<field name="VL18_lane_map" descr="(see above)" access="RO" offset="0x24.8" size="0x0.4" />
	<field name="VL19_lane_map" descr="(see above)" access="RO" offset="0x24.12" size="0x0.4" />
	<field name="VL20_lane_map" descr="(see above)" access="RO" offset="0x24.16" size="0x0.4" />
	<field name="VL21_lane_map" descr="(see above)" access="RO" offset="0x24.20" size="0x0.4" />
	<field name="VL22_lane_map" descr="(see above)" access="RO" offset="0x24.24" size="0x0.4" />
	<field name="VL23_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x24.28" size="0x0.4" />
	<field name="VL24_lane_map" descr="(see above)" access="RO" offset="0x28.0" size="0x0.4" />
	<field name="VL25_lane_map" descr="(see above)" access="RO" offset="0x28.4" size="0x0.4" />
	<field name="VL26_lane_map" descr="(see above)" access="RO" offset="0x28.8" size="0x0.4" />
	<field name="VL27_lane_map" descr="(see above)" access="RO" offset="0x28.12" size="0x0.4" />
	<field name="VL28_lane_map" descr="(see above)" access="RO" offset="0x28.16" size="0x0.4" />
	<field name="VL29_lane_map" descr="(see above)" access="RO" offset="0x28.20" size="0x0.4" />
	<field name="VL30_lane_map" descr="(see above)" access="RO" offset="0x28.24" size="0x0.4" />
	<field name="VL31_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x28.28" size="0x0.4" />
	<field name="fiber_connector_index" descr="For SP5. Represent the fiber connector index on front panel" access="RO" offset="0x3c.16" size="0x0.8" />
	<field name="sub_module" descr="Indicates start offset of rx_lane, tx_lane inside the modules lanes in\;8x granularity. relevant for modules with more than 8 lanes. such as OE.0: lanes_0-71: lanes_8_152: lanes_16_233: lanes_24_31" access="RO" offset="0x3c.28" size="0x0.4" />
	<field name="oe_lane7_to_els_logical_laser" descr="(see above)" access="RO" offset="0x40.0" size="0x0.4" />
	<field name="oe_lane6_to_els_logical_laser" descr="(see above)" access="RO" offset="0x40.4" size="0x0.4" />
	<field name="oe_lane5_to_els_logical_laser" descr="(see above)" access="RO" offset="0x40.8" size="0x0.4" />
	<field name="oe_lane4_to_els_logical_laser" descr="(see above)" access="RO" offset="0x40.12" size="0x0.4" />
	<field name="oe_lane3_to_els_logical_laser" descr="(see above)" access="RO" offset="0x40.16" size="0x0.4" />
	<field name="oe_lane2_to_els_logical_laser" descr="(see above)" access="RO" offset="0x40.20" size="0x0.4" />
	<field name="oe_lane1_to_els_logical_laser" descr="(see above)" access="RO" offset="0x40.24" size="0x0.4" />
	<field name="oe_lane0_to_els_logical_laser" descr="OE optical lane to ELS logical laser mapping" access="RO" offset="0x40.28" size="0x0.4" />
	<field name="els_module_index" descr="ELS module index" access="RO" offset="0x44.0" size="0x0.8" />
	<field name="els_index" descr="ELS label index" access="RO" offset="0x44.10" size="0x0.6" />
	<field name="active_module_lane_mask" descr="Lane mask representing the active lanes associated with the local port\;as determined by the agreed link protocol during link up.0: N/A (not supported or link is down)Bit 0: Lane 0Bit 1: Lane 1Bit 2: Lane 2Bit 3: Lane 3Bit 4: Lane 4Bit 5: Lane 5Bit 6: Lane 6Bit 7: Lane 7Note: supported only if indication by PCAM.feature_group=1.bit 6." access="RO" offset="0x44.16" size="0x0.8" />
	<field name="oe_mcu_index" descr="Optical engine MCU index. If system has no MCU on the OE, this field\;represent the OE index." access="RO" offset="0x44.24" size="0x0.7" />
	<field name="cpo_indication" descr="CPO indication:0 - not CPO1 - CPO" access="RO" offset="0x44.31" size="0x0.1" />
</node>

<node name="pmlp_reg_ext" descr="" attr_required_tlvs="index:s" size="0x40.0" >
	<field name="width" descr="0: unmap_local_port1: x1 - lane 0 is used2: x2 - lanes 0,1 are used4: x4 - lanes 0,1,2 and 3 are used8: x8 - lanes 0-7 are usedOther - reserved" access="RW" enum="unmap_local_port=0x0,x1=0x1,x2=0x2,x4=0x4,x8=0x8" offset="0x0.0" size="0x0.8" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="m_lane_m" descr="Module lane mapping:0 - Local to Module mapping include module lanes mapping1 - Local to Module mapping only, without lane mappingWhen this operational is set (‘1’), the following fields are ignored in\;SET command and should return the value “0” in GET commands:PMLP.rxtxPMLP.lane&lt;i&gt;_module_mapping.tx_lanePMLP.lane&lt;i&gt;_module_mapping.rx_lane" access="OP" offset="0x0.28" size="0x0.1" />
	<field name="rxtx" descr="Use different configuration for RX and TX.If this bit is cleared, the TX value is used for both RX and TX. When\;set, the RX configuration is taken from the separate field. This is to\;enable backward compatible implementation." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="lane_module_mapping" descr="Module SerDes for lane iUp to 8 SerDes in a module can be mapped to a local port.\;." subnode="lane_2_module_mapping_ext" access="RW" high_bound="7" low_bound="0" offset="0x4.0" size="0x20.0" />
</node>

<node name="pmlr_reg_ext" descr="" attr_required_tlvs="index:s" size="0x28.0" >
	<field name="status" descr="0- Normal mission mode.1- Module is disabled/not connected.2- unsupported configuration setting3- input loopback is enabled4- output loopback is enabled" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="lane_mask" descr="not relevant for port_module = local portLogical lanes of module to configure or readFor set function bitmask of lanes to setFor read only one bit shall be set.Note:Media side may be different number of lanes than host side,\;configuration is done by logical lane of media side corresponding to\;port number" access="INDEX" offset="0x0.4" size="0x0.8" />
	<field name="lp_msb" descr="not relevant for port_module = module indexLocal port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port isinterpreted:0: Local_port_number1: IB_port_number3: Out_of_band_or_PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="if port_module = local port-&gt; Local port numberif port_module = module index -&gt; Module number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="host_media" descr="Host or Media lanes0 - Media lanes1 - Host lanes" access="INDEX" offset="0x0.30" size="0x0.1" />
	<field name="lb_cap" descr="Modules Loopback capabilities - bitmask0x00: loopback not supportedBit 0: Simultaneous Host and Media side LoopbacksBit 1: Per Lane Loopback supportedBit 2: Output LoopbackBit 3: Input loopbackNote: See CMIS spec for input/output loopback definition" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="lb_en" descr="Modules Loopback enable only one bit shall be set.According to host_media field index0x0 disable all loopbacksBit 0: Enable Input LoopbackBit 1: Enable Output LoopbackNote:For Configuration that is not supported by capability it will be\;rejected." access="RW" offset="0x4.16" size="0x0.8" />
</node>

<node name="pmmp_cmis_protocol_override_layout_ext" descr="" size="0xc.0" >
	<field name="host_electrical_compliance" descr="Host Electrical compliance code per CMIS byte 86 based on SFF-8024 table\;4-50 - unspecified1- 1000BASE - CX2 - XAUI3 - XFI4 - SFI5 - 25GAUI C2M6 - XLAUI C2M7 - XLPPI8 - LAUI-2 C2M9 - 50GAUI-2 C2M10 - 50GAUI-1 C2M11 - CAUI-4 C2M13 - 100GAUI-2 C2M15 - 200GAUI-4 C2M17 - 400GAUI-8 C2M20 - 25GBASE-CR CA-L21 - 25GBASE-CR CA-S22 - 25GBASE-CR CA-N23 - 40GBASE-CR424 - 50GBASE-CR26 - 100GBASE-CR427 - 100GBASE-CR228 - 200GBASE-CR429 - 400GBASE-CR865 - CAUI-4 C2M no FEC66 - CAUI-4 C2M RS FEC67 - 50GBASE-CR2 RS FEC68 - 50GBASE-CR2 FC FEC69 - 50GBASE-CR2 no FEC" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="cable_breakout" descr="bits 7-0 as per byte 210 in CMIS, Near-End implementationBit 0 - Channel 1 implementationBit 1 - Channel 2 implementationBit 2 - Channel 3 implementationBit 3 - Channel 4 implementationBit 4- Channel 5 implementationBit 5- Channel 6 implementationBit 6- Channel 7 implementationBit 7- Channel 8 implementationfor each channel:0 - Channel implemented1 - Channel not - implementedbit 12-8 as per byte 211 4-0 in CMIS, Far-End implementation" access="RW" offset="0x0.8" size="0x0.13" />
	<field name="media_type_encoding" descr="Byte 85 in CMIS. Media type encoding override0: undefined1: Optical_MMF2: Optical_SMF3: Passive_copper4: Active_cables5: BASE_T" access="RW" offset="0x0.21" size="0x0.4" />
	<field name="mod_pwrup_maxduration" descr="Module transition to high power maximum duration. coded according to\;table 8-29 of CMIS." access="RW" offset="0x0.28" size="0x0.4" />
	<field name="media_compliance" descr="Module media interface compliance for CMIS, per byte 87.Values taken according to module_media_type from SFF-8024:If MMF - SFF-8024 table 4-6, MM media interface codesIf SMF - SFF-8024 table 4-7, SM media interface codeIf Active cable- SFF-8024 table 4-9 Active cable assembly code:0 -unspecified1 - Active cable assembly with BER &lt; 1e-122 - Active cable assembly with BER &lt; 5e-53 - Active cable assembly with BER &lt; 2.6e-44 - Active cable assembly with BER &lt; 1e-6" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="module_media_type" descr="Module media type encoding, per byte 85 of CMIS:0 - undefined1 - MMF2 - SMF3 - passive Copper4 - Active cables5 - Base-T" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="dp_tx_off_maxduration" descr="Data path turn off maximum duration. coded according to table 8-29 of\;CMIS 4.0." access="RW" offset="0x4.16" size="0x0.4" />
	<field name="dp_tx_on_maxduration" descr="Data path turn on maximum duration. coded according to table 8-29 of\;CMIS 4.0." access="RW" offset="0x4.20" size="0x0.4" />
	<field name="dp_init_maxduration" descr="Data path init maximum duration. coded according to table 8-29 of CMIS\;4.0." access="RW" offset="0x4.28" size="0x0.4" />
	<field name="cmis_override_mask" descr="bitmask of override from CMIS protocol bytes page.Relevant only when Bit 9 is set in eeprom_override field.inverse polarity.0 - override1 - don’t overrideBit 0 - cable_breakoutBit 1 -host_electrical_complianceBit 2 - module_media_typeBit 3 - media_complianceBit 4 - mod_pwrup_maxDurationBit 5 - dp_init_maxDurationBit 6 - dp_tx_on_maxDurationBit 7 - dp_tx_off_maxDurationBit 9 - media_type_encoding" access="RW" offset="0x8.0" size="0x0.16" />
</node>

<node name="pmmp_qsfp_protocol_override_layout_ext" descr="" size="0xc.0" >
	<field name="ethernet_compliance_code" descr="Ethernet Compliance Codes bit mask (10/40G/100G)Override byte131 per SFF-8636:Bit 7 - Extended Specification Compliance validBit 6 - 10GBASE-LRMBit 5 - 10GBASE-LRBit 4 - 10GBASE-SRBit 3 - 40GBASE-CR4Bit 2 - 40GBASE-SR4Bit 1 - 40GBASE-LR4Bit 0 - 40G Active Cable (XLPPI)" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="cable_breakout" descr="Override of byte113 per SFF-8636:Bit 6-4 (Far End):0 - Far end is unspecified1 - Cable with single far end with 4 channels implemented, or separable\;module with 4-channel connector2 - Cable with single far end with 2 channels implemented, or separable\;module with 2-channel connector3 - Cable with single far end with 1 channel implemented, or separable\;module with 1-channel connector4 - 4 far ends with 1 channel implemented in each (i.e. 4x1 break out)5 - 2 far ends with 2 channels implemented in each (i.e. 2x2 break out)6 - 2 far ends with 1 channel implemented in each (i.e. 2x1 break out)Bit 3-0 (Near End)Bit 0 - Channel 1 implementationBit 1 - Channel 2 implementationBit 2 - Channel 3 implementationBit 3 - Channel 4 implementationfor each channel:0 - Channel implemented1 - Channel not - implemented" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="giga_ethernet_compliance_code" descr="Gigabit Ethernet Compliance CodesOverride byte134 per SFF-8636:Bit 3 - 1000BASE-TBit 2 - 1000BASE-CXBit 1 - 1000BASE-LXBit 0 - 1000BASE-SX" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ext_ethernet_compliance_code" descr="Extended Specification Compliance CodesOverride byte192 per SFF-8636:0 - Unspecified1 - 100G AOC (Active Optical Cable) or 25GAUI C2M AOC with FEC2 - 100GBASE-SR4 or 25GBASE-SR3 - 100GBASE-LR4 or 25GBASE-LR4 - 100GBASE-ER4 or 25GBASE-ER5 - 100GBASE-SR106 - 100G CWDM47 - 100G PSM4 Parallel SMF8 - 100G ACC (Active Copper Cable) or 25GAUI C2M ACC. with FEC11 - 100GBASE-CR4 or 25GBASE-CR CA-L12 - 25GBASE-CR CA-S13 - 25GBASE-CR CA-N16 - 40GBASE-ER417 - 4 x 10GBASE-SR18 - 40G PSM4 Parallel SMF19 - G959.1 profile P1I1-2D1 (10709 MBd, 2km, 1310nm SM)20 - G959.1 profile P1S1-2D2 (10709 MBd, 40km, 1550nm SM)21 - G959.1 profile P1L1-2D2 (10709 MBd, 80km, 1550nm SM)22 - 10GBASE-T with SFI electrical interface23 - 100G CLR424 - 100G AOC or 25GAUI C2M AOC. No FEC25 - 100G ACC or 25GAUI C2M ACC. No FEC" access="RW" offset="0x4.8" size="0x0.8" />
</node>

<node name="pmmp_reg_ext" descr="" size="0x40.0" >
	<field name="sticky" descr="When set will keep eeprom_override values after plug out event" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="apply_im" descr="When set, override will be configured immediately without PMAOS toggle\;requirement if supported.For the list of supported overrides, see eeprom_override description.supported if PCAM.bit 87 set.Field is ignored when set_laser_state is set to a non-zero value." access="WO" offset="0x0.1" size="0x0.1" />
	<field name="els_trigger_mode" descr="Relevant for ELS module for IB CPO switches only. Relevant for User to\;configure the ELS module states:0: Do_not_generate_event1: Generate_Event" access="WO" offset="0x0.2" size="0x0.2" />
	<field name="laser_mask" descr="Relevant for ELS module for IB CPO switches only, ELS lasers bitmask.\;When set, only selected lasers, will follow the set_laser_operation\;field." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="override_target" descr="Relevant only for power_setpoint_lane[] override field. When set, the\;power setpoint parameters will be written into non-voletile memory in\;ELSFP module, instead of CMIS page." access="OP" offset="0x0.29" size="0x0.1" />
	<field name="eeprom_override" descr="Override/ignore EEPROM advertisement properties bitmask:Bit 0: Override_cable_protocols_and_technology_for_QSFPBit 1: Override_cable_protocols_and_technology_for_SFPBit 2: Ignore_Power_Class - set high powerBit 3: Override_Cable_LengthBit 4: Override_AttenuationBit 8: Set_Module_to_Low_PowerBit 9: Override_cable_protocols_and_technology_for_CMIS - based\;modules QSFP-DD/ OSFP/ DSFP/ SFP-DDBit 11: Override_module_typeBit 12: Override_ELS_lane_powerBit 13: Override_ELS_output_fiber_checked_flagBit 14: Override_ELS_lane_enableSupported overrides with apply_im is bits 8, 12, 13, 14.rest of overrides will be applied only after PMAOS toggle.For bits 11-14, the override is done separately - each configuration at a time" access="RW" enum="Override_cable_protocols_and_technology_for_QSFP=0x1,Override_cable_protocols_and_technology_for_SFP=0x2,Ignore_Power_Class=0x4,Override_Cable_Length=0x8,Override_Attenuation=0x10,Set_Module_to_Low_Power=0x100,Override_cable_protocols_and_technology_for_CMIS=0x200,Override_module_type=0x800,Override_ELS_lane_power=0x1000,Override_ELS_output_fiber_checked_flag=0x2000,Override_ELS_lane_enable=0x4000" offset="0x4.0" size="0x0.16" />
	<field name="eeprom_override_mask" descr="Write Mask bit (negative polarity):0 - allow write1 - ignore writeOn write commands, indicates which of the bits from eeprom_override\;field are updated.Reserved on read operations." access="WO" offset="0x4.16" size="0x0.16" />
	<field name="qsfp_cable_protocol_technology" descr="Protocol technology override for QSFP cable or CMIS based cable\;(QSFP-DD/OSFP)Valid only when the protocols and technology for QSFP is overridden as\;indicated by eeprom_overridePMMP - QSFP Protocol Bytes Override LayoutPMMP - CMIS Protocol Bytes Override Layout" subnode="pmmp_reg_qsfp_cable_protocol_technology_auto_ext" access="RW" offset="0x8.0" size="0xc.0" union_selector="$(parent).eeprom_override" />
	<field name="sfp_cable_protocol_technology" descr="Valid only when the protocols and technology is overridden as indicated\;by eeprom_overridePMMP - SFP Protocol Bytes Override Layout" subnode="pmmp_reg_sfp_cable_protocol_technology_auto_ext" access="RW" offset="0x14.0" size="0xc.0" union_selector="$(parent).eeprom_override" />
	<field name="cable_length" descr="Length of cable assembly, units of 1 m for non CMIS cables.for CMIS cables, represents cable length field:bits 6:7 represent cable_length_multiplier for calculating cable length00 - 0.1 multiplier (0.1 to 6.3m)01- 1 multiplier (1 to 63m)10 - 10 multiplier (10 to 630m)11 - 100 multiplier (100 to 6300m)Valid only when the cable length is overridden as indicated by\;eeprom_override." access="RW" offset="0x20.0" size="0x0.8" />
	<field name="module_type" descr="0: Unidentified_Cable_unplugged1: Active_cable - (active copper / optics)2: Full_Retimed_Optical_Module3: Passive_copper_cable6: Linear_copper_cable8: CPO10: Linear_Pluggable_Optical_Module11: Half_Retimed_Tx_Optical_Module12: Half_Retimed_Rx_Optical_Module" access="RW" enum="Unidentified_Cable_unplugged=0x0,Active_cable=0x1,Full_Retimed_Optical_Module=0x2,Passive_copper_cable=0x3,Linear_copper_cable=0x6,CPO=0x8,Linear_Pluggable_Optical_Module=0xa,Half_Retimed_Tx_Optical_Module=0xb,Half_Retimed_Rx_Optical_Module=0xc" offset="0x20.8" size="0x0.5" />
	<field name="sub_module" descr="Indicates start offset of lanes (or lasers) inside the modules lanes in\;8x granularity. relevant for modules with more than 8 lanes. such as OE.0: lanes_0-71: lanes_8_152: lanes_16_233: lanes_24_31" access="INDEX" offset="0x20.24" size="0x0.4" />
	<field name="set_laser_operation" descr="Relevant for ELS module for IB CPO switches only. Set Laser operation:0: no_operation1: fiber_check2: laser_tuning3: laser_up6: laser_fine_tune_once7: laser_wavelength_tune" access="WO" offset="0x20.29" size="0x0.3" />
	<field name="attenuation_5g" descr="Valid only when the attenuation is overridden as indicated by\;eeprom_override.Attenuation - total channel attenuation @ 5GHz in db." access="RW" offset="0x24.0" size="0x0.8" />
	<field name="attenuation_7g" descr="Valid only when the attenuation is overridden as indicated by\;eeprom_override.Attenuation - total channel attenuation @ 7GHz in db." access="RW" offset="0x24.8" size="0x0.8" />
	<field name="attenuation_12g" descr="Valid only when the attenuation is overridden as indicated by\;eeprom_override.Attenuation - total channel attenuation @ 12GHz in db." access="RW" offset="0x24.16" size="0x0.8" />
	<field name="attenuation_25g" descr="Valid only when the attenuation is overridden as indicated by\;eeprom_override.Attenuation - total channel attenuation @ 25GHz in db." access="RW" offset="0x24.24" size="0x0.8" />
	<field name="attenuation_53g" descr="Valid only when the attenuation is overridden as indicated by\;eeprom_override.Attenuation - total channel attenuation @ 53GHz in db." access="RW" offset="0x28.8" size="0x0.8" />
	<field name="lane_enable" descr="Laser Enable. Valid only when\;override_ELS_lane_enable_and_ELS_putput_fiber_checked_flag is overridden\;as indicated by eeprom_override. Bit mask for ELS laser, should be same\;bitmask as output_fiber_checked_flag, The lane_enable will be masked\;according to the laser_mask index.:0 – disable laser1 – enable laser" access="RW" offset="0x28.16" size="0x0.8" />
	<field name="output_fiber_checked_flag" descr="Set power restriction for ELS laser. Valid only when\;override_ELS_lane_enable is overridden as indicated by eeprom_override.\;This bit mask, should be same bitmask as lane_enable, The\;output_fiber_checked_flag will be masked according to the laser_mask\;index:0 – set restriction on1 – set restriction off" access="RW" offset="0x28.24" size="0x0.8" />
	<field name="power_setpoint_lane" descr="Laser optical power for laser &lt;i&gt;, in unit of 10 µW. Valid only when\;override_ELS_lanepower is overridden as indicated by eeprom_override.\;The power setpoints will be masked according to the laser_mask index." access="RW" high_bound="7" low_bound="0" offset="0x30.16" size="0x10.0" />
</node>

<node name="pmmp_reg_qsfp_cable_protocol_technology_auto_ext" descr="" attr_is_union="1" size="0xc.0" >
	<field name="pmmp_cmis_protocol_override_layout_ext" descr="" subnode="pmmp_cmis_protocol_override_layout_ext" access="RW" offset="0x0.0" selected_by="Override_cable_protocols_and_technology_for_CMIS" size="0xc.0" />
	<field name="pmmp_qsfp_protocol_override_layout_ext" descr="" subnode="pmmp_qsfp_protocol_override_layout_ext" access="RW" offset="0x0.0" selected_by="Override_cable_protocols_and_technology_for_QSFP" size="0xc.0" />
</node>

<node name="pmmp_reg_sfp_cable_protocol_technology_auto_ext" descr="" attr_is_union="1" size="0xc.0" >
	<field name="pmmp_sfp_protocol_bytes_override_ext" descr="" subnode="pmmp_sfp_protocol_bytes_override_ext" access="RW" offset="0x0.0" selected_by="Override_cable_protocols_and_technology_for_SFP" size="0xc.0" />
</node>

<node name="pmmp_sfp_protocol_bytes_override_ext" descr="" size="0xc.0" >
	<field name="tengig_ethernet_compliance_code" descr="10G Ethernet Compliance CodesOverride byte3 per SFF-8472:Bit 7 - 10G Base-ERBit 6 - 10G Base-LRMBit 5 - 10G Base-LRBit 4 - 10G Base-SR" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="cable_technology" descr="SFP+ Cable TechnologyOverride byte8 per SFF-8472:Bit 3 - Active CableBit 2 - Passive Cable" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="bit_rate" descr="Override byte12 per SFF-8472The nominal bit (signaling) rate (BR, nominal) is specified in units of\;100 MBd, rounded off to the nearest 100 MBd.A value of FFh indicates the bit rate is greater than 25.0Gb/s" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="ethernet_compliance_code" descr="Ethernet Compliance CodesOverride byte6 per SFF-8472:Bit 7 - BASE-PXBit 6 - BASE-BX10Bit 5 - 100BASE-FXBit 4 - 100BASE-LX/LX10Bit 3 - 1000BASE-TBit 2 - 1000BASE-CXBit 1 - 1000BASE-LXBit 0 - 1000BASE-SX" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ext_ethernet_compliance_code" descr="Extended Specification Compliance Codes (25GE)Override byte36 per SFF-8472:0 - Unspecified1 - 100G AOC (Active Optical Cable) or 25GAUI C2M AOC with FEC2 - 100GBASE-SR4 or 25GBASE-SR3 - 100GBASE-LR4 or 25GBASE-LR4 - 100GBASE-ER4 or 25GBASE-ER5 - 100GBASE-SR106 - 100G CWDM47 - 100G PSM4 Parallel SMF8 - 100G ACC (Active Copper Cable) or 25GAUI C2M ACC. with FEC11 - 100GBASE-CR4 or 25GBASE-CR CA-L12 - 25GBASE-CR CA-S13 - 25GBASE-CR CA-N16 - 40GBASE-ER417 - 4 x 10GBASE-SR18 - 40G PSM4 Parallel SMF19 - G959.1 profile P1I1-2D1 (10709 MBd, 2km, 1310nm SM)20 - G959.1 profile P1S1-2D2 (10709 MBd, 40km, 1550nm SM)21 - G959.1 profile P1L1-2D2 (10709 MBd, 80km, 1550nm SM)22 - 10GBASE-T with SFI electrical interface23 - 100G CLR424 - 100G AOC or 25GAUI C2M AOC. No FEC25 - 100G ACC or 25GAUI C2M ACC. No FEC" access="RW" offset="0x4.8" size="0x0.8" />
</node>

<node name="pmpc_reg_ext" descr="" size="0x20.0" >
	<field name="module_state_updated" descr="On read operation:A bit vector where each bit represents a module (bit 0 represents module\;0 etc). A set bit indicates one or more changes in the module state\;(plugged/unplugged/unknown) has happened since the last time the bit was\;cleared. The default is 1 in all relevant bits.On write operation:Used to clear the module_status_updated bits. Writing a set bit clears\;the relevant bit in the module_status_updated vector. Cleared bits in\;this field preserve the value of the relevant bit in the bit vector. The\;software cannot set a bit in the module_status_updated vector.Note: To prevent a case where an update is missed by the software, it is\;recommended to use the flow below:Read the module_status_updated vectorFind a bit(s) relevant to a module(s) the software would like to\;handleClear the relevant bit(s)Handle the module (e.g. read the module parameters using MCIA\;register)Read module_status_updated again to make sure the status did not change\;after reading the cable information." access="RW" high_bound="7" low_bound="0" offset="0x0.0" size="0x20.0" />
</node>

<node name="pmpd_reg_ext" descr="" size="0x30.0" >
	<field name="status" descr="0 - Diagnostic data not supported1 - Normal mission mode.2 - PRBS checker is not locked.3 - PRBS checker is locked." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="cl" descr="clear counters" access="OP" offset="0x0.4" size="0x0.1" />
	<field name="lane" descr="Module lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="host_media" descr="Host or Media lanes0 - Media lanes1 - Host lanes" access="INDEX" offset="0x0.12" size="0x0.1" />
	<field name="module" descr="module to access" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="errors_cap" descr="Bits Errors count capability" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="ber_cap" descr="BER measure capability" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="snr_cap" descr="SNR measure capability" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="prbs_bits_high" descr="This counter provides information on the total amount of prbs traffic\;(bits) received on module’s side." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="prbs_bits_low" descr="(see above)" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="prbs_errors_high" descr="This counter provides information on the total amount of prbs errors\;detected on module’s side." access="RO" offset="0xc.0" size="0x4.0" />
	<field name="prbs_errors_low" descr="(see above)" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="measured_snr" descr="SNR in dB0 - not supported." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="ber_coef" descr="(see above)" access="RO" offset="0x18.0" size="0x0.4" />
	<field name="ber_magnitude" descr="BER = raw_ber_coef*10^(-raw_ber_magnitude)" access="RO" offset="0x18.8" size="0x0.8" />
</node>

<node name="pmpe_reg_ext" descr="" size="0x28.0" >
	<field name="module_status" descr="Module operational state:1: plugged_enabled2: unplugged3: module_plugged_error - details in error_type5: unknown" access="RO" enum="plugged_enabled=0x1,unplugged=0x2,module_plugged_error=0x3,unknown=0x5" offset="0x0.0" size="0x0.4" />
	<field name="module_msb" descr="[DWIP] Module number bits [15:8]." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="module" descr="Module number bits [7:0]." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="error_type" descr="Module error details:0x0: Power_Budget_Exceeded0x1: Long_Range_for_non_MLNX_cable_or_module0x2: Bus_stuck - (I2C Data or clock shorted)0x3: bad_or_unsupported_EEPROM0x4: Enforce_part_number_list0x5: unsupported_cable0x6: High_Temperature0x7: bad_cable - (Module/Cable is shorted)0x8: PMD_type_is_not_enabled - (see PMTPS).0xc: pcie_system_power_slot_Exceeded0xf: Boot_error - [DWIP]0x10: Recovery_error - [DWIP]0x11: Submodule_failure/fault - [DWIP]0x12: SeRBI_check_failure - [DWIP]0x13: els_critical_indication - [DWIP]0x15: Submodule_unplugged_or_missing - [DWIP]Valid only when (oper_status = 0x3)." access="RO" enum="Power_Budget_Exceeded=0x0,Long_Range_for_non_MLNX_cable_or_module=0x1,Bus_stuck=0x2,bad_or_unsupported_EEPROM=0x3,Enforce_part_number_list=0x4,unsupported_cable=0x5,High_Temperature=0x6,bad_cable=0x7,PMD_type_is_not_enabled=0x8,pcie_system_power_slot_Exceeded=0xc,Boot_error=0xf,Recovery_error=0x10,Submodule_failure_fault=0x11,SeRBI_check_failure=0x12,els_critical_indication=0x13,Submodule_unplugged_or_missing=0x15" offset="0x4.8" size="0x0.5" />
	<field name="ref_module_valid" descr="[DWIP]0: ref_module field not valid1: ref_module field is valid" access="RO" offset="0x4.15" size="0x0.1" />
	<field name="ref_module" descr="[DWIP]If concatenation of module_msb + module indicate a virtual module (types\;CPOxx), and module_status is module_plugged_error where the error\;originates in any of the submodules, this field will be valid and\;contain the index of one such submodule." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="els_laser_oper_state" descr="[DWIP]If either of the following conditions is true:Concatenation of module_msb+module fields indicates an ELS index.2) ref_module_valid field is set to 1, and ref_module field indicates an\;ELS index.Then this field contains the operational state of upto 32 lasers of that\;ELS. For each laser:0: no_laser1: laser_init2: laser_active3: laser_active_with_fault4: laser_down5: laser_down_with_fault" access="RO" enum="no_laser=0x0,laser_init=0x1,laser_active=0x2,laser_active_with_fault=0x3,laser_down=0x4,laser_down_with_fault=0x5" high_bound="31" low_bound="0" offset="0x8.28" size="0x10.0" />
	<field name="els_laser_fault" descr="[DWIP]If either of the following conditions is true:Concatenation of module_msb+module fields indicates an ELS index.2) ref_module_valid field is set to 1, and ref_module field indicates an\;ELS index.Then for each laser upto 32 lasers, this field contains the fault\;information:0: no_fault1: laser_fiber_contaminated2: laser_APC_fault3: laser_power_exceeded_allowed_range4: laser_power_subceeded_allowed_range5: laser_TEC_control_loop_fault6: laser_ramping_timeout_fault7: laser_power_tuning_fault8: laser_wavelength_tuning_fault9: els_input_power_drop" access="RO" enum="no_fault=0x0,laser_fiber_contaminated=0x1,laser_APC_fault=0x2,laser_power_exceeded_allowed_range=0x3,laser_power_subceeded_allowed_range=0x4,laser_TEC_control_loop_fault=0x5,laser_ramping_timeout_fault=0x6,laser_power_tuning_fault=0x7,laser_wavelength_tuning_fault=0x8,els_input_power_drop=0x9" high_bound="31" low_bound="0" offset="0x18.28" size="0x10.0" />
</node>

<node name="pmpr_reg_ext" descr="" size="0x10.0" >
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="attenuation_5g" descr="Attenuation - total channel attenuation @ 5GHz in db." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="attenuation_7g" descr="Attenuation - total channel attenuation @ 7GHz in db.A 0 value implies that attenuation_5g is used also for 7GHz" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="attenuation_53g" descr="Attenuation - total channel attenuation @ 53GHz in db.A 0 value implies that attenuation_5g is used also for 25GHz" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="attenuation_12g" descr="Attenuation - total channel attenuation @ 12GHz in db.A 0 value implies that attenuation_5g is used also for 12GHz" access="RW" offset="0xc.0" size="0x0.8" />
	<field name="attenuation_25g" descr="Attenuation - total channel attenuation @ 25GHz in db.A 0 value implies that attenuation_5g is used also for 25GHz" access="RW" offset="0xc.16" size="0x0.8" />
</node>

<node name="pmpt_reg_ext" descr="" size="0x1c.0" >
	<field name="status" descr="0 - Normal mission mode.1 - Module is not connected OR module doesn’t support PRBS and\;diagnostics data2 - unsupported configuration setting3 - PRBS Generator only4 - PRBS Checker only5 - PRBS traffic both Checker and GeneratorNote: For lock status on PRBS data see PMPD.status" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="lane_mask" descr="Reserved when (le=0 or ls = 0)Logical lane number mask.For Get operation only one bit shall be set" access="INDEX" offset="0x0.4" size="0x0.8" />
	<field name="host_media" descr="Host or Media lanes0 - Media lanes1 - Host lanes" access="INDEX" offset="0x0.12" size="0x0.1" />
	<field name="invt_cap" descr="PRBS inversion is supported" access="RO" offset="0x0.13" size="0x0.1" />
	<field name="swap_cap" descr="PAM4 MSB&lt;-&gt; LSB swapping is supported by the module" access="RO" offset="0x0.14" size="0x0.1" />
	<field name="module" descr="module index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):0 - No per lane configuration1 - Per lane configurationsWhen le is cleared, lane index is reserved and all PMPT configurations\;are taking place on all lanes.When le is set, configurations are taking place per lane based on lane\;indexAffects lane indexing for set operations only, ignored for get\;operations" access="OP" offset="0x0.29" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support/capability:0 - No support of per lane configuration1 - Support of per lane configuration" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:0 - PRBS is disabled.1 - PRBS is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="Supported module’s PRBS capability (bitmask)Bit 0 - PRBS31 (x^31 + x^28 + 1)Bit 1 - PRBS23 (x^23 + x^18 + 1)Bit 5 - PRBS7 (x^7 + x^6 + 1)Bit 6 - PRBS11 (x^11 + x^9 + 1)Bit 11 - PRBS9 (x^9 + x^5 + 1)Bit 17 - PRBS13 (x^13 + x^12 + x^2+ x + 1)Bit 21 - SSPRBit 22 - SSPRQ" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 7):0 - NRZ test pattern1 - PAM4 encoding" access="INDEX" offset="0x8.0" size="0x0.4" />
	<field name="ch_ge" descr="0 - Access is for both Checker and Generator (Can be used for Set\;operations only)1 - Access is for Generator2 - Access if for CheckerNote: Checker and Generator must be in same rate" access="INDEX" offset="0x8.4" size="0x0.2" />
	<field name="invt_admin" descr="PRBS inversion enable bit, see ivnt_cap:0 - NO PRBS inversion1 - PRBS inversion" access="RW" offset="0x8.8" size="0x0.1" />
	<field name="swap_admin" descr="PAM4 MSB&lt;-&gt; LSB swapping enable bit, see swap_cap.0 - NO MSB&lt;-&gt; LSB swapping1 - MSB &lt;-&gt; LSB swapping" access="RW" offset="0x8.9" size="0x0.1" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap:0x0 - PRBS31 (x^31 + x^28 + 1)0x1 - PRBS23 (x^23 + x^18 + 1)0x5 - PRBS7 (x^7 + x^6 + 1)0x6 - PRBS11 (x^11 + x^9 + 1)0xB - PRBS9 (x^9 + x^5 + 1)0x11 - PRBS13 (x^13 + x^12 + x^2+ x + 1)0x15 - SSPR0x16 - SSPRQ" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)Bit 0 - 1GE (1.25 Gb/s)Bit 1 - SDR (2.5 Gb/s)Bit 2 - ReservedBit 3- 10GE/40GE (10.3125 Gb/s)Bit 4- FDR (14.0625 Gb/s)Bit 5- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)Bit 6- Reserved Bit 7- HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s)Bit 8- NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)Bit 9 - XDR (106.25 Gbd / 212.5Gb/s)" access="RO" offset="0xc.16" size="0x0.16" />
	<field name="lane_rate_admin" descr="Lane rate be used in PRBS, see lane_rate_cap:0 - Non selected.1 - 1GE (1.25 Gb/s)2 - SDR (2.5 Gb/s)8 - 10GE/40GE (10.3125 Gb/s)16 - FDR (14.0625 Gb/s)32 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)128 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s)256 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)512 - XDR (106.25 Gbd / 212.5Gb/s)" access="RW" offset="0x10.16" size="0x0.16" />
</node>

<node name="pmtm_reg_ext" descr="" size="0x10.0" >
	<field name="module" descr="module number bits [7:0]." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCASlot_indexSlot_index = 0 represent the onboard (motherboard).In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="module_type" descr="module_type:0: Backplane_with_4_lanes1: QSFP2: SFP3: No_Cage - [Obsolete]4: Backplane_with_single_lane8: Backplane_with_two_lanes10: Chip2Chip4x11: Chip2Chip2x12: Chip2Chip1x14: QSFP_DD15: OSFP16: SFP_DD17: DSFP18: Chip2Chip8x19: Twisted_Pair20: Backplane_with_8_lanes21: Loopback 22: OE_16x 23: OSFP_ELS24: QSFP_2x25: CPO_32x26: ELS_1627: CPO_64x" access="RW" enum="Backplane_with_4_lanes=0x0,QSFP=0x1,SFP=0x2,No_Cage=0x3,Backplane_with_single_lane=0x4,Backplane_with_two_lanes=0x8,Chip2Chip4x=0xa,Chip2Chip2x=0xb,Chip2Chip1x=0xc,QSFP_DD=0xe,OSFP=0xf,SFP_DD=0x10,DSFP=0x11,Chip2Chip8x=0x12,Twisted_Pair=0x13,Backplane_with_8_lanes=0x14,Loopback=0x15,OE_16x=0x16,OSFP_ELS=0x17,QSFP_2x=0x18,CPO_32x=0x19,ELS_16=0x1a,CPO_64x=0x1b" offset="0x4.0" size="0x0.5" />
	<field name="module_width" descr="Number of module’s electrical lanes (in conjunction with\;module_width_hi).NOTE: For SET command, this value (in conjunction with module_width_hi)\;should match the module type width in module_type field" access="RW" offset="0x4.8" size="0x0.5" />
	<field name="module_width_hi" descr="Number of module’s electrical lanes (in conjunction with module_width).NOTE: For SET command, this value (in conjunction with module_width)\;should match the module type width in module_type field" access="RW" offset="0x4.13" size="0x0.3" />
	<field name="module_msb" descr="[Switch][DWIP]module number bits [15:8]." access="INDEX" offset="0x4.24" size="0x0.8" />
</node>

<node name="pmtu_reg_ext" descr="" attr_required_tlvs="index:s" size="0x10.0" >
	<field name="itre" descr="Ingress Truncation enable, the admin_mtu is used as truncation:0: disable1: enableReserved when NICs (NICs use only ‘0’)Reserved when IB Switches (use only ‘0’)Reserved when i_e = 0 or 2Reserved when GPUNet" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="i_e" descr="Ingress/Egress:0: applies for both ingress and for egress, read from egress1: applies only for ingress2: applies only for egressReserved when NICs (NICs use only ‘0’)Reserved when IB Switches (use only ‘0’)Reserved when GPUNet" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port numberNot including CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="protocol" descr="[DWIP]:The protocol which the MTU is applied to.0: All protocols that are supported by the device. On get, it will\;return the value for IBg11: IB (gen 1)2: NVLink3: IBg24-15: ReservedReserved when Eth switchesReserved when NICNote: for GB100 IBg2 is not PoR, Nov 2023" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="max_mtu" descr="Maximum MTU supported on the port (Read Only).MTU depends on the port type. When port type (Eth/IB/FC) is configured,\;the relevant MTU is reported. When the port type is not configured, the\;minimum between the max_mtu for the different types (Eth/IB/FC) is\;reported.Informative:- For GPUNet: IB is used for MADs, thus max MTU is 768B- NVLink max MTU is 320B" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="admin_mtu" descr="Administratively configured MTU on the port. Must be smaller or equal to\;max_mtu.When IB: configuration is allowed only when port state is down.When itre=1 then must be at least 128B and granularity is 8B" access="RW" offset="0x8.16" size="0x0.16" />
	<field name="oper_mtu" descr="Operational MTU. This is the actual MTU configured on the ports. Packets\;exceeding this size will be dropped.Note: For NICs and for IB the actual operational MTU is reported which\;may be smaller than admin_mtu.For NICs: when PCAM.max_admin_mtu capability is set then oper_mtu will\;be the max of all admin_mtu" access="RO" offset="0xc.16" size="0x0.16" />
</node>

<node name="ppad_reg_ext" descr="" size="0x10.0" >
	<field name="mac_47_32" descr="If single_base_mac = 0 - base MAC addressIf single_base_mac = 1 - the per port MAC address" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="local_port" descr="Port numberReserved when single_base_mac = 0" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="single_base_mac" descr="0: base_mac - Switch global MAC address. FW will set incremental MAC per\;port starting from the base_mac.1: single_mac - mac of the local_port" access="OP" offset="0x0.28" size="0x0.1" />
	<field name="mac_31_0" descr="(see above)" access="RW" offset="0x4.0" size="0x4.0" />
</node>

<node name="ppaos_reg_ext" descr="" attr_required_tlvs="index:s" size="0x10.0" >
	<field name="phy_test_mode_status" descr="Port extended down status:0: regular_operation - (port down/up according to PAOS)1: phy_test_modephy test mode can be valid only when PAOS.admin_status=2 and\;PAOS.oper_status=2 (i.e port is down)." access="RO" enum="regular_operation=0x0,phy_test_mode=0x1" offset="0x0.0" size="0x0.4" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0 - Network Port1 - Near-End Port (For Retimer/Gearbox - Host side)2 - internal IC LR Port3 - Far-End Port (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="phy_test_mode_admin" descr="Port extended administrative down status:0: regular_operation - (port down/up according to PAOS)1: phy_test_modeThe phy test mode (1) can be set only when PAOS.admin_status=2 (i.e\;port configuration is down)." access="RW" enum="regular_operation=0x0,phy_test_mode=0x1" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.Switch partition ID with which to associate the port.Switch partitions are numbered from 0 to 7 inclusively.The swid field is only valid when the local_port is the router port. In\;this case, the swid indicates which of the router ports to\;configure/query." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="phy_status" descr="rx phy status:0: rx_phy_down1: rx_phy_up2: rx_phy_down_by_commandNote: The phy up indication is according to protocol (up ==\;align_status=true)i.g. In PRBS test mode phy up is when PRB is lock (up== prbs lock)" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x4.4" size="0x0.4" />
	<field name="phy_status_admin" descr="rx phy port admin. Controls phy entities operational port status.valid for port_type &lt;&gt; ‘0’.to operate link status for port_type ‘0’ use PAOS.admin_status.0: rx_phy_down1: rx_phy_up" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="primary_secondary_oper" descr="Indicates for Mode B links if the port was chosen as primary or\;secondary during linkup.0: Not_supported_or_not_chosen_yet1: Primary2: Secondary" access="RO" enum="Not_supported_or_not_chosen_yet=0x0,Primary=0x1,Secondary=0x2" offset="0x4.20" size="0x0.2" />
	<field name="primary_secondary_constant" descr="Used to keep primary / secondary role constant between link toggles. If\;the field is set to ‘1’ on local device and peer, both will keep their\;current role as primary or secondary.0: not_constant_role1: constant_role" access="RW" enum="not_constant_role=0x0,constant_role=0x1" offset="0x4.22" size="0x0.1" />
	<field name="primary_secondary" descr="This field can be configured when port is up, and configuration will be\;saved for next port toggle. The field functions as an admin field.The primary_secondary field will set the role of the port in the link\;negotiation state.0: fw_default1: primary2: secondary3: random_negotiation - (Auto - based on AN resolution)Notes:This field is applicable for Mode B links in test mode and operational mode.Each side of the connected ports should be configured with the opposite role.While working in test mode, this field should be configured with the same values as in the PPRT/PPTT.primary_secondary fields.When setting a non-test mode loopback with a Mode B rate, it is not required to set the port in a certain role. However, the port may not be configured as secondary.When setting a test mode loopback with a Mode B rate, port must be set as primary." access="RW" enum="fw_default=0x0,primary=0x1,secondary=0x2,random_negotiation=0x3" offset="0x4.25" size="0x0.2" />
	<field name="dc_cpl_port" descr="When set, indicates that ports trace is DC coupled.Enabling test mode in case of DC coupled port is allowed only when\;setting dc_cpl_allow and printing warning to user as specified in the\;description." access="RO" offset="0x4.28" size="0x0.1" />
	<field name="dc_cpl_allow" descr="Relevant only for DC couple ports of backplane media, Ignored otherwise.Field must be set when entering test mode, otherwise command is ignored.When entering test mode in DC couple system the following message must\;be presented to user:“Warning: DC couple system must be powered on both sides of the physical\;link prior to enabling test mode. System may be harmed and product\;lifetime may be shortened if not ensured.”" access="WO" offset="0x4.29" size="0x0.1" />
</node>

<node name="ppbmc_reg_ext" descr="" attr_required_tlvs="index:s" size="0x10.0" >
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0 - Network Port1 - Near-End Port (For Retimer/Gearbox - Host side)2 - internal IC LR Port3 - Far-End Port (For Retimer/Gearbox - Line side)4 - USR Main5 - USR TileOther values are reserved.Configuration 4,5 should use the same clock" access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="monitor_type" descr="Operational monitor types enabled based on monitor_cntl setting and the\;operational mode of the link:Bit 0: Post_FEC_or_No_FEC_BER_monitoringBit 1: Pre_FEC_BER_monitoringBit 2: Symbol_BER_monitoring" access="RO" enum="Post_FEC_or_No_FEC_BER_monitoring=0x1,Pre_FEC_BER_monitoring=0x2,Symbol_BER_monitoring=0x4" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="monitor_e_ctrl_ind" descr="Valid only when monitor_e_ctrl_ind_cap is set.The index is applied to the following fields: clr_cap, clr, event_ctrl,\;and monitor_state fields.0: All_monitors6: recovery_BW_loss - excessive recoveriesAll other reserved" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="event_generation_cooldown_cap" descr="When set indicates support of event generation cooldown for the monitor\;chosen under the monitor_e_ctrl_ind field." access="RO" offset="0x0.29" size="0x0.1" />
	<field name="clr_cap" descr="This field indicates whether the ‘clr’ option is supported for the\;monitor specified by the monitor_e_ctrl_ind." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="This field allows the monitor control settings to restored to the\;default values for the monitor specified by the monitor_e_ctrl_ind. When\;‘clr’ is set, the following fields will revert to the FW defaults values\;for the selected monitor: monitor_ctrl/monitor_ctrl_ext, e, event_ctrl &amp;\;event_generation_cooldown_admin." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="monitor_state" descr="The monitor state of the port:0 - No BER Monitor support1 - Normal2 - Warning3 - Alarm* The init monitor state for each port upon link up is normal" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="clr_stat" descr="clear statistics from PPDR. link_down_info page of selected monitor type" access="OP" offset="0x4.9" size="0x0.1" />
	<field name="monitor_e_ctrl_ind_cap" descr="When set monitor_e_ctrl_ind is valid" access="RO" offset="0x4.10" size="0x0.1" />
	<field name="monitor_type_ext" descr="Operational monitor types extenstion enabled based on monitor_cntl,\;monitor_cntl_ext setting and the operational mode of the link:Bit 2: recovery_BW_loss - excessive recoveries" access="RO" offset="0x4.12" size="0x0.4" />
	<field name="monitor_cntl" descr="Bitmask - monitor options to enable monitoring:When multiple_monitor_cap is set, multiple bits can be set. Else, only 1\;bit can be setBit 0: Raw_BER_monitor - When set, a link with FEC active will\;monitor Pre-FEC BER.Bit 1: Effective_FEC_monitorBit 2: Symbol_FEC_monitorBit 6: recovery_BW_loss - excessive recoveries" access="RW" enum="Raw_BER_monitor=0x1,Effective_FEC_monitor=0x2,Symbol_FEC_monitor=0x4,recovery_BW_loss=0x40" offset="0x4.16" size="0x0.8" />
	<field name="event_ctrl" descr="Bitmask - event generation on operational state change:Bit 0 - Normal stateBit 1 - Warning stateBit 2 - Alarm stateBit 3 - ReservedNote: Normal state events can be generated only if either Alarm and/or\;Warning events are enabled." access="RW" offset="0x4.24" size="0x0.4" />
	<field name="multiple_monitor_cap" descr="When set, multiple monitoring groups are possible. Hence, monitor_cntl\;can be set with multiple bits.else, monitor_cntl can be set with only 1 bits" access="RO" offset="0x4.28" size="0x0.1" />
	<field name="ievent" descr="Invoke event0: Read only1: Does both reading and invoke an event of type PPBME_TRAPNote: setting this field invokes an event, regardless to e and event_ctl\;fields, it has no effect on the event state." access="OP" offset="0x4.29" size="0x0.1" />
	<field name="e" descr="Event generation on operational state change:0 - Do not generate event1 - Generate Event2 - Generate Single EventNot Supported for HCA." access="RW" offset="0x4.30" size="0x0.2" />
	<field name="monitor_type_cap" descr="Monitor type capability mask:Bit 6: recovery_BW_loss - excessive recoveriesNote - raw BER, effective BER, symbol BER do not have capability" access="RO" enum="recovery_BW_loss=0x40" offset="0x8.16" size="0x0.8" />
	<field name="event_generation_cooldown_admin" descr="Field sets cooldown for PPBME event generation of monitor chosen in\;monitor_e_ctrl_ind. If a PPBME event is generated, FW will not generate\;another event until cooldown has passed, even if the condition for a\;second event occurred.Time granularity in 100 mS.Note: Field is supported only when event_generation_cooldown_cap is set" access="RW" offset="0xc.0" size="0x0.10" />
	<field name="event_generation_cooldown_oper" descr="Field reports cooldown timer for PPBME event generation of monitor\;chosen in monitor_e_ctrl_ind.Time granularity in 100 mS.Note: Field is supported only when event_generation_cooldown_cap is set" access="RO" offset="0xc.12" size="0x0.10" />
	<field name="monitor_force_peer_fields" descr="Determines monitor settings that will be forced on peer.Bit 0: enable_monitor - when set to ‘1’, host will attempt to force\;chosen peer monitor to be enabled. When set to ‘0’, host will attempt\;to force chosen peer monitor to be disabled.Other bits are reserved." access="RW" offset="0xc.25" size="0x0.2" />
	<field name="monitor_force_peer_oper" descr="Indicates the operational status of the force mechanism applied to the\;chosen monitor settings under monitor_force_peer_fields, during the last\;link negotiation:0: no_force_applied1: peer_settings_forced2: local_settings_forced" access="RO" enum="no_force_applied=0x0,peer_settings_forced=0x1,local_settings_forced=0x2" offset="0xc.27" size="0x0.2" />
	<field name="monitor_force_peer_admin" descr="Controls whether the local port forces monitor settings on the peer port\;for the chosen monitor.0: fw_default1: do_not_force2: force_peer" access="RW" enum="fw_default=0x0,do_not_force=0x1,force_peer=0x2" offset="0xc.29" size="0x0.2" />
	<field name="monitor_force_peer_cap" descr="Indicates if there is support in setting monitor settings on peer side,\;based on chosen monitor in monitor_e_ctrl_ind. Monitor settings to be\;forced on peer are chosen in monitor_force_peer_fields." access="RO" offset="0xc.31" size="0x0.1" />
</node>

<node name="ppbme_reg_ext" descr="" attr_required_tlvs="index:s" size="0x10.0" >
	<field name="monitor_type" descr="Monitor type based on monitor_options setting and the operational mode\;of the link:0: Post_FEC_or_No_FEC_BER_monitoring1: Pre_FEC_BER_monitoring2: Symbol_BER_monitoring6: recovery_BW_loss" access="RO" enum="Post_FEC_or_No_FEC_BER_monitoring=0x0,Pre_FEC_BER_monitoring=0x1,Symbol_BER_monitoring=0x2,recovery_BW_loss=0x6" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="monitor_state" descr="The monitor state of the port:0 - No BER Monitor on the port1 - Normal2 - Warning3 - Alarm" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="ievent" descr="Invoke event0: Read only1: Does both reading and invoke an event of type PPBME_TRAPNote: setting this field invokes an event, regardless to e and event_ctl\;fields, it has no effect on the event state." access="OP" offset="0x4.29" size="0x0.1" />
</node>

<node name="ppbmp_monitor_parameters_ext" descr="" size="0x8.0" >
	<field name="warning_th_exp" descr="(see above)" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="warning_th_mantissa" descr="BER threshold for warning state, when the monitor state is normal and\;the monitored BER crosses above the warning_threshold, the monitor state\;will is set to warningwarning_threshold = warning_th_mantissa * 10^(-warning_th_exp)The warning_threshold shall be within the supported range for the\;monitor type" access="RW" offset="0x0.8" size="0x0.4" />
	<field name="alarm_th_exp" descr="(see above)" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="alarm_th_mantissa" descr="BER threshold for alarm state, when the monitored BER crosses above the\;alarm_threshold, the monitor state is set to alarm.alarm_threshold = alarm_th_mantissa * 10^(-alarm_th_exp)The alarm_threshold shall be within the supported range for the monitor\;type" access="RW" offset="0x0.24" size="0x0.4" />
	<field name="normal_th_exp" descr="(see above)" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="normal_th_mantissa" descr="BER threshold for normal state, when the monitored BER crosses below the\;normal_threshold, the monitor state is set to normal.normal_threshold = normal_th_mantissa * 10^(-normal_th_exp)The warning_threshold shall be within the supported range for the\;monitor type" access="RW" offset="0x4.24" size="0x0.4" />
</node>

<node name="ppbmp_monitor_params_cap_ext" descr="" size="0x4.0" >
	<field name="th_cap_exp_min" descr="The minimum value that could be configured for the [*]_th_exp fields of\;the Monitor Parameters." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="th_cap_exp_max" descr="The maximum value that could be configured for the [*]_th_exp fields of\;the Monitor Parameters." access="RO" offset="0x0.8" size="0x0.8" />
</node>

<node name="ppbmp_reg_ext" descr="" attr_required_tlvs="index:s" size="0x30.0" >
	<field name="monitor_group" descr="Monitor Parameters Group0x0: Raw_BER_RS0x1: Raw_BER_FC0x2: Effective_BER0x4: Pre_FEC_BER0x5: Symbol_BER0x9: recovery_BW_loss - excessive recoveries" access="INDEX" enum="Raw_BER_RS=0x0,Raw_BER_FC=0x1,Effective_BER=0x2,Pre_FEC_BER=0x4,Symbol_BER=0x5,recovery_BW_loss=0x9" offset="0x0.0" size="0x0.4" />
	<field name="grp_prf_set" descr="When set, grp_prf field will set local_port’s group.Else, grp_prf field will be ignore in set operation" access="WO" offset="0x0.11" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="grp_prf" descr="Group profile port is mapped to.when group_profile is set," access="RW" offset="0x0.24" size="0x0.3" />
	<field name="grp_prf_cap" descr="When set grp_prf field is configurable.Note: supported only in IB/NVLink devices" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="admin_oper_sel" descr="On read operation, selects how monitor_parameters and time_window fields\;are represented.0: show_fields_as_admin (if no neg, also operational)1: show_fields_as_oper" access="INDEX" offset="0x0.28" size="0x0.1" />
	<field name="monitor_parameters_w_ignore" descr="‘monitor_parameters’ field ignore write.Relevant for set operation only, while this bit is set to ‘1’-ignore the ‘monitor_parameters’ values." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="time_window_w_en" descr="‘time_window’ field write enableRelevant for set operation only, while this bit is set to ‘0’-ignore the ‘time_window’ value." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Supported if PCAM.feature_cap_mask bit 93 is set.0: override_thresholds - thresholds set according to\;monitor_parameters values.1: set_fw_default_thresholds - thresholds set in monitor_parameters\;are ignored" access="RW" enum="override_thresholds=0x0,set_fw_default_thresholds=0x1" offset="0x0.31" size="0x0.1" />
	<field name="monitor_parameters" descr="Monitor parameters layout, selected by monitor_group.\;PPBMP - BER Monitor Parameters Layout" subnode="ppbmp_reg_monitor_parameters_auto_ext" access="RW" condition="$(parent).monitor_group" offset="0x4.0" size="0x8.0" />
	<field name="time_window" descr="The time frame which the events are grouped.This is a tumbling window (not a sliding window), means that each window\;is uncorrelated to the adjacent windows events.For BER features the time window derived fromthe lowest threshold.The field units are as follows:1. For monitors 0x1 to 0x5: the time_window is specified in units of 1\;msec.2. For monitors 0x8 to 0xD: the time_window is specified in units of the\;PPBMP.sampling_rate returned value.Notes:1. Value of zero is means the BER monitor is not active or time window\;is unknown.\;2. The time window is adjustable only if time_window_set_cap\;is set." access="RW" offset="0xc.0" size="0x0.24" />
	<field name="time_window_set_cap" descr="The capability to adjust the time_window field" access="RO" offset="0xc.31" size="0x0.1" />
	<field name="sampling_rate" descr="Time frame to measure warning threshold and error threshold.Units of 10mSec, range 0..1Sec.Value of zero is means the BER monitor is not active or sampling rate is\;unknown" access="RO" offset="0x10.0" size="0x0.8" />
	<field name="monitor_parameters_cap" descr="The configured Monitor Parameters shall be within the ranges defined by\;this field.The returned value is according to the monitor_group index and the\;device capabilities.See\;PPBMP - Monitor Parameters Capabilities Layout" subnode="ppbmp_monitor_params_cap_ext" access="RO" offset="0x14.0" size="0x4.0" />
</node>

<node name="ppbmp_reg_monitor_parameters_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x8.0" >
	<field name="ppbmp_monitor_parameters_ext" descr="" subnode="ppbmp_monitor_parameters_ext" access="RW" condition="($(parent).monitor_group == Raw_BER_RS | $(parent).monitor_group == Raw_BER_FC | $(parent).monitor_group == Effective_BER | $(parent).monitor_group == Pre_FEC_BER | $(parent).monitor_group == Symbol_BER)" offset="0x0.0" size="0x8.0" />
</node>

<node name="ppcnt_infiniband_general_counter_ext" descr="" size="0xf8.0" >
	<field name="rq_general_error_high" descr="The total number of packets that were dropped since it contained errors.\;Reasons for this include:dropped due to MPR mismatch.Supported only when indicated by PCAM." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="rq_general_error_low" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
</node>

<node name="ppcnt_infiniband_packets_counter_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear event in msec." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="(see above)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="port_unicast_xmit_pkts_high" descr="For counter description please refer to the InfiniBand Specification" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="port_unicast_xmit_pkts_low" descr="(see above)" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="port_unicast_rcv_pkts_high" descr="For counter description please refer to the InfiniBand Specification" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="port_unicast_rcv_pkts_low" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="sync_header_error_counter_high" descr="For counter description please refer to the InfiniBand Specification" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="sync_header_error_counter_low" descr="(see above)" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="port_local_physical_errors_high" descr="For counter description please refer to the InfiniBand Specification" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="port_local_physical_errors_low" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="port_malformed_packet_errors_high" descr="For counter description please refer to the InfiniBand Specification" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="port_malformed_packet_errors_low" descr="(see above)" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="port_buffer_overrun_errors_high" descr="For counter description please refer to the InfiniBand Specification" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="port_buffer_overrun_errors_low" descr="(see above)" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="port_dlid_mapping_errors_high" descr="For counter description please refer to the InfiniBand Specification" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="port_dlid_mapping_errors_low" descr="(see above)" access="RO" offset="0x3c.0" size="0x4.0" />
	<field name="port_vl_mapping_errors_high" descr="For counter description please refer to the InfiniBand Specification" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="port_vl_mapping_errors_low" descr="(see above)" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="port_looping_errors_high" descr="For counter description please refer to the InfiniBand Specification" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="port_looping_errors_low" descr="(see above)" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="port_inactive_discards_high" descr="For counter description please refer to the InfiniBand Specification" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="port_inactive_discards_low" descr="(see above)" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="port_neighbor_mtu_discards_high" descr="For counter description please refer to the InfiniBand Specification" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="port_neighbor_mtu_discards_low" descr="(see above)" access="RO" offset="0x5c.0" size="0x4.0" />
	<field name="port_llu_rx_icrc_error_high" descr="Total number of packets received on the port with ICRC error." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="port_llu_rx_icrc_error_low" descr="(see above)" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="port_tx_parity_error_high" descr="Total number of packets with parity error detected on the switch." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="port_tx_parity_error_low" descr="(see above)" access="RO" offset="0x6c.0" size="0x4.0" />
</node>

<node name="ppcnt_nvlink_reduction_mlid_ext" descr="" size="0xf8.0" >
	<field name="mlid_0" descr="The MLID associated with this counter block." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="incoming_good_mc_req_pkt_0_high" descr="Incoming good MC requests (read+write) packets associated with this\;MLID." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="incoming_good_mc_req_pkt_0_low" descr="(see above)" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_0_high" descr="Incoming good MC responses (read+write) packets associated with this\;MLID." access="RO" offset="0xc.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_0_low" descr="(see above)" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="dropped_pkt_0" descr="Dropped packets (low 32 bits only) associated with this MLID." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="generated_mc_read_resp_pkt_0" descr="Generated MC read responses packets (low 32 bits only) associated with\;this MLID." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="mlid_1" descr="The MLID associated with this counter block." access="RO" offset="0x1c.0" size="0x0.16" />
	<field name="incoming_good_mc_req_pkt_1_high" descr="Incoming good MC requests (read+write) packets associated with this\;MLID." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="incoming_good_mc_req_pkt_1_low" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_1_high" descr="Incoming good MC responses (read+write) packets associated with this\;MLID." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_1_low" descr="(see above)" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="dropped_pkt_1" descr="Dropped packets (low 32 bits only) associated with this MLID." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="generated_mc_read_resp_pkt_1" descr="Generated MC read responses packets (low 32 bits only) associated with\;this MLID." access="RO" offset="0x34.0" size="0x4.0" />
	<field name="mlid_2" descr="The MLID associated with this counter block." access="RO" offset="0x38.0" size="0x0.16" />
	<field name="incoming_good_mc_req_pkt_2_high" descr="Incoming good MC requests (read+write) packets associated with this\;MLID." access="RO" offset="0x3c.0" size="0x4.0" />
	<field name="incoming_good_mc_req_pkt_2_low" descr="(see above)" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_2_high" descr="Incoming good MC responses (read+write) packets associated with this\;MLID." access="RO" offset="0x44.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_2_low" descr="(see above)" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="dropped_pkt_2" descr="Dropped packets (low 32 bits only) associated with this MLID." access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="generated_mc_read_resp_pkt_2" descr="Generated MC read responses packets (low 32 bits only) associated with\;this MLID." access="RO" offset="0x50.0" size="0x4.0" />
	<field name="mlid_3" descr="The MLID associated with this counter block." access="RO" offset="0x54.0" size="0x0.16" />
	<field name="incoming_good_mc_req_pkt_3_high" descr="Incoming good MC requests (read+write) packets associated with this\;MLID." access="RO" offset="0x58.0" size="0x4.0" />
	<field name="incoming_good_mc_req_pkt_3_low" descr="(see above)" access="RO" offset="0x5c.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_3_high" descr="Incoming good MC responses (read+write) packets associated with this\;MLID." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_3_low" descr="(see above)" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="dropped_pkt_3" descr="Dropped packets (low 32 bits only) associated with this MLID." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="generated_mc_read_resp_pkt_3" descr="Generated MC read responses packets (low 32 bits only) associated with\;this MLID." access="RO" offset="0x6c.0" size="0x4.0" />
	<field name="mlid_4" descr="The MLID associated with this counter block." access="RO" offset="0x70.0" size="0x0.16" />
	<field name="incoming_good_mc_req_pkt_4_high" descr="Incoming good MC requests (read+write) packets associated with this\;MLID." access="RO" offset="0x74.0" size="0x4.0" />
	<field name="incoming_good_mc_req_pkt_4_low" descr="(see above)" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_4_high" descr="Incoming good MC responses (read+write) packets associated with this\;MLID." access="RO" offset="0x7c.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_4_low" descr="(see above)" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="dropped_pkt_4" descr="Dropped packets (low 32 bits only) associated with this MLID." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="generated_mc_read_resp_pkt_4" descr="Generated MC read responses packets (low 32 bits only) associated with\;this MLID." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="mlid_5" descr="The MLID associated with this counter block." access="RO" offset="0x8c.0" size="0x0.16" />
	<field name="incoming_good_mc_req_pkt_5_high" descr="Incoming good MC requests (read+write) packets associated with this\;MLID." access="RO" offset="0x90.0" size="0x4.0" />
	<field name="incoming_good_mc_req_pkt_5_low" descr="(see above)" access="RO" offset="0x94.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_5_high" descr="Incoming good MC responses (read+write) packets associated with this\;MLID." access="RO" offset="0x98.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_5_low" descr="(see above)" access="RO" offset="0x9c.0" size="0x4.0" />
	<field name="dropped_pkt_5" descr="Dropped packets (low 32 bits only) associated with this MLID." access="RO" offset="0xa0.0" size="0x4.0" />
	<field name="generated_mc_read_resp_pkt_5" descr="Generated MC read responses packets (low 32 bits only) associated with\;this MLID." access="RO" offset="0xa4.0" size="0x4.0" />
	<field name="mlid_6" descr="The MLID associated with this counter block." access="RO" offset="0xa8.0" size="0x0.16" />
	<field name="incoming_good_mc_req_pkt_6_high" descr="Incoming good MC requests (read+write) packets associated with this\;MLID." access="RO" offset="0xac.0" size="0x4.0" />
	<field name="incoming_good_mc_req_pkt_6_low" descr="(see above)" access="RO" offset="0xb0.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_6_high" descr="Incoming good MC responses (read+write) packets associated with this\;MLID." access="RO" offset="0xb4.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_6_low" descr="(see above)" access="RO" offset="0xb8.0" size="0x4.0" />
	<field name="dropped_pkt_6" descr="Dropped packets (low 32 bits only) associated with this MLID." access="RO" offset="0xbc.0" size="0x4.0" />
	<field name="generated_mc_read_resp_pkt_6" descr="Generated MC read responses packets (low 32 bits only) associated with\;this MLID." access="RO" offset="0xc0.0" size="0x4.0" />
	<field name="mlid_7" descr="The MLID associated with this counter block." access="RO" offset="0xc4.0" size="0x0.16" />
	<field name="incoming_good_mc_req_pkt_7_high" descr="Incoming good MC requests (read+write) packets associated with this\;MLID." access="RO" offset="0xc8.0" size="0x4.0" />
	<field name="incoming_good_mc_req_pkt_7_low" descr="(see above)" access="RO" offset="0xcc.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_7_high" descr="Incoming good MC responses (read+write) packets associated with this\;MLID." access="RO" offset="0xd0.0" size="0x4.0" />
	<field name="incoming_good_mc_resp_pkt_7_low" descr="(see above)" access="RO" offset="0xd4.0" size="0x4.0" />
	<field name="dropped_pkt_7" descr="Dropped packets (low 32 bits only) associated with this MLID." access="RO" offset="0xd8.0" size="0x4.0" />
	<field name="generated_mc_read_resp_pkt_7" descr="Generated MC read responses packets (low 32 bits only) associated with\;this MLID." access="RO" offset="0xdc.0" size="0x4.0" />
	<field name="nvl_reduction_errors_high" descr="Number of reduction configuration errors for all MLIDs." access="RO" offset="0xe0.0" size="0x4.0" />
	<field name="nvl_reduction_errors_low" descr="(see above)" access="RO" offset="0xe4.0" size="0x4.0" />
	<field name="nvl_reduction_penalty_box_errors_high" descr="Number of reduction penalty-box errors for all MLIDs (requests +\;responses)." access="RO" offset="0xe8.0" size="0x4.0" />
	<field name="nvl_reduction_penalty_box_errors_low" descr="(see above)" access="RO" offset="0xec.0" size="0x4.0" />
</node>

<node name="ppcnt_plr_counters_ext" descr="" size="0xf8.0" >
	<field name="plr_rcv_codes_high" descr="Number of received PLR codewords" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="plr_rcv_codes_low" descr="(see above)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="plr_rcv_code_err_high" descr="The total number of rejected codewords received" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="plr_rcv_code_err_low" descr="(see above)" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="plr_rcv_uncorrectable_code_high" descr="The number of uncorrectable codewords received" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="plr_rcv_uncorrectable_code_low" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="plr_xmit_codes_high" descr="Number of transmitted PLR codewords" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="plr_xmit_codes_low" descr="(see above)" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="plr_xmit_retry_codes_high" descr="The total number of codewords retransmitted." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="plr_xmit_retry_codes_low" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_high" descr="The total number of retransmitted event." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_low" descr="(see above)" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="plr_sync_events_high" descr="The number of sync events" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="plr_sync_events_low" descr="(see above)" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="plr_codes_loss_high" descr="Received bandwidth loss due to codes retransmission. calculated in\;resolution of(plr_rcv_code_err / plr_rcv_codes) * 10^10BW Loss % = (plr_codes_loss / 10^10 ) *100" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="plr_codes_loss_low" descr="(see above)" access="RO" offset="0x3c.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_within_t_sec_max_high" descr="The maximum number of retransmitted events in t sec window" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_within_t_sec_max_low" descr="(see above)" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="plr_outstanding_cells" descr="Number of outstanding cells in PLR buffer" access="RO" offset="0x50.24" size="0x0.8" />
	<field name="plr_rcv_good_codes_high" descr="Number of all the good none sync PLR codewords received.This counter provides information on the total number of codewords\;received by the higher link layer at the output of the PLR correction\;mechanism." access="RO" offset="0x54.0" size="0x4.0" />
	<field name="plr_rcv_good_codes_low" descr="(see above)" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="plr_tx_codes_loss_high" descr="Transmitted bandwidth loss due to codes retransmission. calculated in\;resolution of (plr_xmit_retry_codes /plr_xmit_codes)*10^10Tx BW Loss % = (plr_xmit_retry_codes / plr_xmit_codes)" access="RO" offset="0x5c.0" size="0x4.0" />
	<field name="plr_tx_codes_loss_low" descr="(see above)" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="plr_tx_max_outstanding_cell_high" descr="Counts each time the buffer reaches its maximum size." access="RO" offset="0x64.0" size="0x4.0" />
	<field name="plr_tx_max_outstanding_cell_low" descr="(see above)" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="plr_rx_block_cs_on_demand_activated_high" descr="Number of codewords that waited for CS decision, instead of being forwarded after KES.\;Counter is accumulative between link toggles.Counter is supported when indicated by PCAM.feature_cap_mask Bit 19 in group 1 is set." access="RO" offset="0x6c.0" size="0x4.0" />
	<field name="plr_rx_block_cs_on_demand_activated_low" descr="(see above)" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="plr_rx_new_nack_received_high" descr="Number of NACKs received by the RX side, requesting remote retry of a\;lost block.Counter is supported when indicated by PCAM.feature_cap_mask Bit 21 in\;group 1 is set." access="RO" offset="0x74.0" size="0x4.0" />
	<field name="plr_rx_new_nack_received_low" descr="(see above)" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="plr_tx_new_nack_sent_high" descr="Number of NACKs sent by the TX side, requesting retry from the remote\;sender.Counter is supported when indicated by PCAM.feature_cap_mask Bit 21 in\;group 1 is set." access="RO" offset="0x7c.0" size="0x4.0" />
	<field name="plr_tx_new_nack_sent_low" descr="(see above)" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="plr_rx_block_flushed_due_to_csn_high" descr="Number of RX blocks flushed because the Cell Sequence Number (CSN)\;indicated an out-of-order or stale condition.Counter is supported when indicated by PCAM.feature_cap_mask Bit 21 in\;group 1 is set." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="plr_rx_block_flushed_due_to_csn_low" descr="(see above)" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="plr_rx_block_uncorrectable_by_prev_high" descr="Number of RX blocks determined uncorrectable because the preceding retry\;block (RLEC) could not repair them.Counter is supported when indicated by PCAM.feature_cap_mask Bit 21 in\;group 1 is set." access="RO" offset="0x8c.0" size="0x4.0" />
	<field name="plr_rx_block_uncorrectable_by_prev_low" descr="(see above)" access="RO" offset="0x90.0" size="0x4.0" />
</node>

<node name="ppcnt_recovery_counters_ext" descr="" size="0xf4.0" >
	<field name="total_successful_recovery_events" descr="Number of total successful recovery events of any of the recovery types\;during ports reset cycle (does not clear on link down)" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="unintentional_link_down_events" descr="Counts Local &amp; remote unintentional drops (remote intentional are not\;counted)Updated on link drop only" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="intentional_link_down_events" descr="Counts Local &amp; remote intentional drops (remote intentional counted)Updated on link drop only" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="time_in_last_host_logical_recovery" descr="Time in ms of each of the recovery types from last recovery flow event." access="RO" offset="0xc.0" size="0x4.0" />
	<field name="time_in_last_host_serdes_feq_recovery" descr="(see above)" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="time_in_last_module_tx_disable_recovery" descr="(see above)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="time_in_last_module_datapath_full_toggle_recovery" descr="(see above)" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="total_time_in_host_logical_recovery" descr="Total time in ms of each of the recovery types from all of the recovery\;flows that happened. Accumulative between link flaps" access="RO" offset="0x1c.0" size="0x4.0" />
	<field name="total_time_in_host_serdes_feq_recovery" descr="(see above)" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="total_time_in_module_tx_disable_recovery" descr="(see above)" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="total_time_in_module_datapath_full_toggle_recovery" descr="(see above)" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="total_host_logical_recovery_count" descr="Counter of the total times each recovery type flow happened.\;Accumulative between link flaps" access="RO" offset="0x2c.0" size="0x4.0" />
	<field name="total_host_serdes_feq_recovery_count" descr="(see above)" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="total_module_tx_disable_recovery_count" descr="(see above)" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="total_module_datapath_full_toggle_recovery_count" descr="(see above)" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="total_host_logical_succesful_recovery_count" descr="Counter of the total times each recovery type flow happened and\;succeeded to recover. Accumulative between link flaps" access="RO" offset="0x3c.0" size="0x4.0" />
	<field name="total_host_serdes_feq_succesful_recovery_count" descr="(see above)" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="total_module_tx_disable_succesful_recovery_count" descr="(see above)" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="total_module_datapath_full_toggle_succesful_recovery_count" descr="(see above)" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="time_since_last_recovery" descr="Time since last successful recovery1 sec granularity.valid only if total_successful_recoveries OR successful_recovery_event ≥\;1" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="last_host_logical_recovery_attempts_count" descr="number of lock attempts counts. lock attempt is defined as 500uS cycle\;lock attempt to linkup​" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="last_host_serdes_feq_attempts_count" descr="number PHY algorithm cycles counts." access="RO" offset="0x54.0" size="0x4.0" />
	<field name="time_between_last_2_recoveries" descr="time in msec between 2 last consecutive recoveries (success or fail)\;from exit of first to entry of second. When value ss in 0xFFFF, time is\;more than 1min ​valid only if (total_successful_recoveries OR successful_recovery_event)\;+ link_down_counter ≥ 2" access="RO" offset="0x58.0" size="0x0.16" />
	<field name="excessive_recoveries_events_since_link_up" descr="Number of excessive recovery events since linkup. Clears between link\;toggles.Note: Field is valid only when PCAM.feature_group=1.feature_cap_mask\;- bit 13 is set" access="RO" offset="0x58.16" size="0x0.16" />
	<field name="last_successful_recovery_time" descr="Time in ms of the last successful recovery flow event.Supported if PCAM.feature_cap_mask bit 124 is set" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="total_successful_recovery_time" descr="Total time in ms of each of the recovery types from all of the recovery\;flows that happened.Accumulative between link flapsSupported if PCAM.feature_cap_mask bit 124 is set" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="last_Successful_recovery_step_attempts" descr="Valid only when UPHY_recovery_steps enabled, counts number of steps\;triggered (step1 + step2) considering number of iterations per step.For example, step 1 = 1 cycle, step 2 = 3 cycles;recovery_step_attempts\;= 4." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="last_rs_fec_uncorrectable_during_recovery_high" descr="Number of uncorrectable RS-FEC blocks received on port, during the last\;recovery flow event.Supported if PCAM.feature_cap_mask bit 125 is set" access="RO" offset="0x6c.0" size="0x4.0" />
	<field name="last_rs_fec_uncorrectable_during_recovery_low" descr="(see above)" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="total_rs_fec_uncorrectable_during_recovery_high" descr="Number of uncorrectable RS-FEC blocks received on port during recovery,\;accumulative on all recovery events between link flap.Supported if PCAM.feature_cap_mask bit 125 is set" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="total_rs_fec_uncorrectable_during_recovery_low" descr="(see above)" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="wait_for_module_time" descr="time in ms, waited for module rx_output_valid" access="RO" offset="0x7c.0" size="0x4.0" />
	<field name="time_in_last_step1" descr="Valid only if PPRM.oper_recovery = phy_recovery_steps and\;PCAM.feature_cap_mask Bit 12 in group 1 is setTime in ms of each of the recovery step of last recovery flow event" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="time_in_last_step2" descr="(see above)" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="total_time_in_step1" descr="Valid only if PPRM.oper_recovery = phy_recovery_steps and\;PCAM.feature_cap_mask Bit 12 in group 1 is setTotal time in ms of each of the recovery steps from all of the recovery\;flows that happened.Accumulative between link flaps" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="total_time_in_step2" descr="(see above)" access="RO" offset="0x8c.0" size="0x4.0" />
	<field name="total_step1_count" descr="Valid only if PPRM.oper_recovery = phy_recovery_steps and\;PCAM.feature_cap_mask Bit 12 in group 1 is setCounter of the total times each recovery type flow happened and\;succeeded to recovery.Accumulative between link flaps" access="RO" offset="0x90.0" size="0x4.0" />
	<field name="total_step2_count" descr="(see above)" access="RO" offset="0x94.0" size="0x4.0" />
	<field name="excessive_recoveries_events_since_device_reset" descr="Number of excessive recovery events since last device reset.Note: Field is valid only when PCAM.feature_group=1.feature_cap_mask\;- bit 13 is set" access="RO" offset="0x98.0" size="0x0.16" />
</node>

<node name="ppcnt_reg_counter_set_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="IB_long_portcntrs_attribute_grp_data_ext" descr="" subnode="IB_long_portcntrs_attribute_grp_data_ext" access="RW" offset="0x0.0" selected_by="InfiniBand_Extended_Port_Counters" size="0xf8.0" />
	<field name="IB_portcntrs_attribute_grp_data_ext" descr="" subnode="IB_portcntrs_attribute_grp_data_ext" access="RW" offset="0x0.0" selected_by="InfiniBand_Port_Counters" size="0xf8.0" />
	<field name="eth_2819_cntrs_grp_data_layout_ext" descr="" subnode="eth_2819_cntrs_grp_data_layout_ext" access="RW" offset="0x0.0" selected_by="RFC_2819_Counters" size="0xf8.0" />
	<field name="eth_2863_cntrs_grp_data_layout_ext" descr="" subnode="eth_2863_cntrs_grp_data_layout_ext" access="RW" offset="0x0.0" selected_by="RFC_2863_Counters" size="0xf8.0" />
	<field name="eth_3635_cntrs_grp_data_layout_ext" descr="" subnode="eth_3635_cntrs_grp_data_layout_ext" access="RW" offset="0x0.0" selected_by="RFC_3635_Counters" size="0xf8.0" />
	<field name="eth_discard_cntrs_grp_ext" descr="" subnode="eth_discard_cntrs_grp_ext" access="RW" offset="0x0.0" selected_by="Ethernet_Discard_Counters" size="0xf8.0" />
	<field name="eth_extended_cntrs_grp_data_layout_ext" descr="" subnode="eth_extended_cntrs_grp_data_layout_ext" access="RW" offset="0x0.0" selected_by="Ethernet_Extended_Counters" size="0xf8.0" />
	<field name="eth_per_prio_grp_data_layout_ext" descr="" subnode="eth_per_prio_grp_data_layout_ext" access="RW" offset="0x0.0" selected_by="Per_Priority_Counters" size="0xf8.0" />
	<field name="eth_per_traffic_class_layout_ext" descr="" subnode="eth_per_traffic_class_layout_ext" access="RW" offset="0x0.0" selected_by="Per_Traffic_Class_Counters" size="0xf8.0" />
	<field name="phys_layer_cntrs_ext" descr="" subnode="phys_layer_cntrs_ext" access="RW" offset="0x0.0" selected_by="Physical_Layer_Counters" size="0xf8.0" />
	<field name="phys_layer_stat_cntrs_ext" descr="" subnode="phys_layer_stat_cntrs_ext" access="RW" offset="0x0.0" selected_by="Physical_Layer_Statistical_Counters" size="0xf8.0" />
	<field name="ppcnt_infiniband_general_counter_ext" descr="" subnode="ppcnt_infiniband_general_counter_ext" access="RW" offset="0x0.0" selected_by="InfiniBand_General_Counters" size="0xf8.0" />
	<field name="ppcnt_infiniband_packets_counter_ext" descr="" subnode="ppcnt_infiniband_packets_counter_ext" access="RW" offset="0x0.0" selected_by="InfiniBand_pkts_counters" size="0xf8.0" />
	<field name="ppcnt_nvlink_reduction_mlid_ext" descr="" subnode="ppcnt_nvlink_reduction_mlid_ext" access="RW" offset="0x0.0" selected_by="Nvlink_Reduction_Counters" size="0xf8.0" />
	<field name="ppcnt_plr_counters_ext" descr="" subnode="ppcnt_plr_counters_ext" access="RW" offset="0x0.0" selected_by="PLR_counters_group" size="0xf8.0" />
	<field name="ppcnt_recovery_counters_ext" descr="" subnode="ppcnt_recovery_counters_ext" access="RW" offset="0x0.0" selected_by="physical_layer_recovery_counters" size="0xf4.0" />
	<field name="ppcnt_rs_fec_histograms_counters_ext" descr="" subnode="ppcnt_rs_fec_histograms_counters_ext" access="RW" offset="0x0.0" selected_by="RS_FEC_Histogram_group" size="0xf8.0" />
</node>

<node name="ppcnt_reg_ext" descr="" attr_required_tlvs="index:s,index:g" size="0x100.0" >
	<field name="grp" descr="Performance counter group.Group 63 indicates all groups (include all per priority/TC/Receive\;Buffer counters). Only valid on Set() operation with clr bit set.0x1: RFC_2863_Counters0x2: RFC_2819_Counters0x3: RFC_3635_Counters0x5: Ethernet_Extended_Counters0x6: Ethernet_Discard_Counters0x10: Per_Priority_Counters - 0x11: Per_Traffic_Class_Counters - 0x12: Physical_Layer_Counters0x16: Physical_Layer_Statistical_Counters0x1A: physical_layer_recovery_counters0x20: InfiniBand_Port_Counters0x21: InfiniBand_Extended_Port_Counters0x22: PLR_counters_group0x23: RS_FEC_Histogram_group0x25: InfiniBand_pkts_counters0x26: InfiniBand_General_Counters0x2C: Nvlink_Reduction_Counters" access="INDEX" enum="RFC_2863_Counters=0x1,RFC_2819_Counters=0x2,RFC_3635_Counters=0x3,Ethernet_Extended_Counters=0x5,Ethernet_Discard_Counters=0x6,Per_Priority_Counters=0x10,Per_Traffic_Class_Counters=0x11,Physical_Layer_Counters=0x12,Physical_Layer_Statistical_Counters=0x16,physical_layer_recovery_counters=0x1a,InfiniBand_Port_Counters=0x20,InfiniBand_Extended_Port_Counters=0x21,PLR_counters_group=0x22,RS_FEC_Histogram_group=0x23,InfiniBand_pkts_counters=0x25,InfiniBand_General_Counters=0x26,Nvlink_Reduction_Counters=0x2c" offset="0x0.0" size="0x0.6" />
	<field name="port_type" descr="Supported only when indicated by PCAM on FPGA based NICs:0 - Network Port1 - Near-End Port (For Retimer/Gearbox - Host side)2 - internal IC LR Port3 - Far-End Port (For Retimer/Gearbox - Line side)" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type:0: Local_port_number1: IB_port_number2: host_port_numberNote - pnat=2 is supported for “Per Traffic Class Congestion\;Counters” and “Per Traffic Class Counters” groups." access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number.Note:when lp_gl = 0, 255 indicates all ports on the device, and is only\;allowed for Set() operation.when lp_gl = 1, the index is a local port numberNote: for HCA this bit is not supported, ignored by device" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="Switch partition ID to associate port with.Switch partitions are numbered from 0 to 7 inclusively.Switch partition 254 indicates stacking ports.Switch partition 255 indicates all switch partitions.Valid for IB router port.Valid on Set() operation with local_port=255." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="prio_tc" descr="Priority index for per priority counter sets, valid values: 0-7\;For Spectrum-2 and on at tx side range can be 0..cap_max_tclass_data-1,\;cap_control_tclass, see QGCR.tx_cnt_tclass.\;Traffic class index for per traffic class counter set, valid values:\;For Switches, valid values: 0 .. cap_max_tclass_data-1\;For HCA, valid values: 0.. HCA_CAP.max_tcOtherwise must be 0.For “NVLink Reduction Counters” group index of MLID and lean pipe." access="INDEX" offset="0x4.0" size="0x0.5" />
	<field name="grp_profile" descr="Supported only when indicated by PCAM: PPCNT_grp_profile_supported (bit\;73).The group profile index. Relevant only if the clr bit is set.0: Will reset the counter value for all counters in the counter group.Else: Will point to the corresponding bit-map profile in the PPCGP\;register. The bit map will return the specific counters that will be\;reset in the group.NOTE: The grp_profile index is not supported for the following counters\;groups:0x12: Physical_Layer_Counters0x16: Physical_Layer_Statistical_Counters0x22: PLR_counters_group" access="INDEX" offset="0x4.5" size="0x0.3" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x4.8" size="0x0.4" />
	<field name="counters_cap" descr="counters_cap is supported if PCAM.feature_cap_mask bit 85 is set.When set, each counter in the group will show in bit 0 if the counter is\;supported.‘0’ - not supported‘1’ - supportedNote: To know which PPCNT groups are supported per device, listed in\;table TBD or PCAM fields with PPCNT can be queried." access="OP" offset="0x4.29" size="0x0.1" />
	<field name="lp_gl" descr="Local Port global variable0: local_port port 255 = all ports of the device.1: local_port index indicates Local port number.for HCA this bit is not supported, ignored by device" access="INDEX" offset="0x4.30" size="0x0.1" />
	<field name="clr" descr="Clear counters. Setting the clr bit will reset the counter value for all\;counters in the counter group. This bit can be set for both Set() and\;Get() operation.NOTE: Clearing a certain group’s counters can influence another group’s\;counters value." access="OP" offset="0x4.31" size="0x0.1" />
	<field name="counter_set" descr="Counter set as described in/;Ethernet RFC 2863 Counter Group Data LayoutEthernet RFC 2819 Counter Group Data LayoutEthernet RFC 3635 Counter Group Data LayoutEthernet Extended Counter Group Data LayoutEthernet Discard Counters Group Data LayoutEthernet Per Priority Group Data LayoutEthernet Per Traffic Class Group data layoutPhysical Layer Counters Data LayoutPhysical Layer Statistical Counters Data LayoutInfiniBand PortCounters Attribute Group Data LayoutInfiniBand Extended PortCounters Attribute Group Data LayoutPLR Counters Data LayoutRS-Histograms Data LayoutInfiniBand Packets Counters Data LayoutInfiniBand General Counters Data LayoutPhysical Layer Recovery Counters Group Data LayoutNVLink Reduction MLID Counters Data Layout" subnode="ppcnt_reg_counter_set_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).grp" />
</node>

<node name="ppcnt_rs_fec_histograms_counters_ext" descr="" size="0xf8.0" >
	<field name="hist" descr="Value of RS-histIn order to know bin errors distribution use PPHCR reg." subnode="uint64" access="RO" high_bound="20" low_bound="0" offset="0x0.0" size="0xa8.0" />
</node>

<node name="ppdfd_ext" descr="" size="0xc.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ntimes" descr="Number of times to transmit the errorNote that by HW the event is triggered 1 time. So FW will trigger the\;event again and again as fast as possible (roughly every 1uSec).On a read access, the FW should return ntimes originally configured." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="poison_en" descr="Poison will set a Phy EBP signal (different type than stomp).Reserved when stomp_en = 1.On a read access, FW should return poison_en originally configured." access="RW" offset="0x8.0" size="0x0.1" />
	<field name="stomp_en" descr="Stomp will set a Phy EBP signal.On a read access, FW should return stomp_en originally configured." access="RW" offset="0x8.1" size="0x0.1" />
</node>

<node name="ppfcg_ext" descr="" size="0x8.0" >
	<field name="event_config" descr="Event Configuration:0 - on each storm detection, send only one event (and stop monitoring\;this port.tc until SW enables it).1 - on each storm detection, send event (keep monitoring the port.tc).note - when 1, FW will notify after polling_interval*detect_num.Default value - 1" access="RW" offset="0x0.31" size="0x0.1" />
</node>

<node name="pphcr_bin_range_ext" descr="" size="0x4.0" >
	<field name="low_val" descr="Low range of bin’s measurement" access="RW" offset="0x0.0" size="0x0.6" />
	<field name="high_val" descr="High range of bin’s measurement" access="RW" offset="0x0.16" size="0x0.6" />
</node>

<node name="pphcr_ext" descr="" attr_required_tlvs="index:s" size="0x5c.0" >
	<field name="we" descr="Support of histogram bins configuration.In case this bit is cleared, the port doesn’t support configuration of\;the histogram bins, for the specific hist_type." access="RO" offset="0x0.0" size="0x0.1" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="port_type" descr="0 - Network Port1 - Near-End Port (For Retimer/Gearbox - Host side)3 - Far-End Port (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type:0: Local_port_number1: IB_port_number" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port or DataPath number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="active_hist_type" descr="0 - Invalid (Link down / unsupported)1 - KP4 RS-FEC (544,514) errors2 - LL RS-FEC (271,257) / (272,257+1) errors3 - KR4 RS-FEC (528,514) errors" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="hist_type" descr="0: According to active link" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="num_of_bins" descr="Available number of bins" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="hist_min_measurement" descr="Lowest measurement/low limit of the histogramExample:In case of hist_type = 1, represent KP4 RS FEC symbol errors(= 0)In case of hist_type = 2, represent LL RS FEC symbol errors ( = 0)" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="hist_max_measurement" descr="Highest measurement/high limit of the histogram:Example:In case of hist_type = 1, represent KP4 RS FEC symbol errors ( = 15)In case of hist_type = 2, represent LL RS FEC symbol errors ( = 7)" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="bin_range_write_mask" descr="Valid only if we (write enable) = 1Ignored on GETWrite mask for the bin_range array.If bit X is set, bin_range [X] write should be executeElse if bit X is clear, ignored value in written to bin_range [X]" access="WO" offset="0xc.0" size="0x0.16" />
	<field name="bin_range" descr="Write to bin_range[x] is applicable only if we = 1 &amp; the corresponding\;bits in bin_range_write_mask is set.Mapping of measurement units to a bin.See\;PPHCR - Port Phy Bin Range Histogram Configuration Layout" subnode="pphcr_bin_range_ext" access="RW" high_bound="18" low_bound="0" offset="0x10.0" size="0x4c.0" />
</node>

<node name="pplm_nvl6_fec_ext" descr="" size="0x18.0" >
	<field name="nvlink_fec_override_admin_200g_1x_mode_a" descr="200G 1x  Mode\;A - override admin bitmask (one-hot setting):0: auto_mode - no overrideBit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x0.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_200g_1x_mode_a" descr="200G 1x  Mode\;A - override capability bitmask:Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x0.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_400g_2x_mode_a" descr="400G 2x  Mode\;A - override admin bitmask (one-hot setting):0: auto_mode - no overrideBit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x4.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_400g_2x_mode_a" descr="400G 2x  Mode\;A - override capability bitmask:Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x4.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_400g_2x_mode_b" descr="400G 2x  Mode B\;- override admin bitmask (one-hot setting):0: auto_mode - no overrideBit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x8.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_400g_2x_mode_b" descr="400G 2x  Mode B\;- override capability bitmask:Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x8.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_360g_2x_mode_b" descr="360G 2x and 378G Mode B - override admin bitmask (one-hot setting):0: auto_mode - no overrideBit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0xc.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_360g_2x_mode_b" descr="360G 2x and 378G 2x Mode B - override capability bitmask:Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0xc.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_328g_2x_mode_b" descr="328G 2x and 345G 2x Mode B - override admin bitmask (one-hot setting):0: auto_mode - no overrideBit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x10.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_328g_2x_mode_b" descr="328G 2x and 345G Mode B - override capability bitmask:Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x10.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_200g_2x_mode_a" descr="200G 2x  Mode A - override admin bitmask (one-hot setting):0: auto_mode - no overrideBit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x14.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_200g_2x_mode_a" descr="200G 2x  Mode A - override capability bitmask:Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 11: RS_FEC_546_516_plus_PLR_Double_FEC_EngineAll others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x14.16" size="0x0.16" />
</node>

<node name="pplm_nvl7_rates_fec_ext" descr="" size="0x18.0" >
	<field name="nvlink_fec_override_admin_169g_1x_mode_a" descr="169G 1x, 176G 1x and 187G 1x Mode A - override admin bitmask (one-hot\;setting):0: auto_mode - no overrideBit 1: RS_FEC_546_516_plus_PLR_Double_FEC_EngineBit 2: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 3: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 4: RS_FEC_288_258_plus_PLR_Double_FEC_EngineBit 5: RS_FEC_288_258_plus_PLR_Quad_FEC_EngineBit 6: RS_FEC_288_258_plus_PLR_Octet_FEC_EngineAll others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x2,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x4,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x8,RS_FEC_288_258_plus_PLR_Double_FEC_Engine=0x10,RS_FEC_288_258_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_288_258_plus_PLR_Octet_FEC_Engine=0x40" offset="0x0.0" size="0x0.8" />
	<field name="nvlink_fec_override_cap_169g_1x_mode_a" descr="169G 1x, 176G 1x and 187G 1x Mode A - override capability bitmask:Bit 1: RS_FEC_546_516_plus_PLR_Double_FEC_EngineBit 2: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 3: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 4: RS_FEC_288_258_plus_PLR_Double_FEC_EngineBit 5: RS_FEC_288_258_plus_PLR_Quad_FEC_EngineBit 6: RS_FEC_288_258_plus_PLR_Octet_FEC_EngineAll others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x2,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x4,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x8,RS_FEC_288_258_plus_PLR_Double_FEC_Engine=0x10,RS_FEC_288_258_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_288_258_plus_PLR_Octet_FEC_Engine=0x40" offset="0x0.8" size="0x0.8" />
	<field name="nvlink_fec_override_admin_200g_1x_mode_a" descr="200G 1x Mode A - override admin bitmask (one-hot setting):0: auto_mode - no overrideBit 1: RS_FEC_546_516_plus_PLR_Double_FEC_EngineBit 2: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 3: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 4: RS_FEC_288_258_plus_PLR_Double_FEC_EngineBit 5: RS_FEC_288_258_plus_PLR_Quad_FEC_EngineBit 6: RS_FEC_288_258_plus_PLR_Octet_FEC_EngineAll others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x2,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x4,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x8,RS_FEC_288_258_plus_PLR_Double_FEC_Engine=0x10,RS_FEC_288_258_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_288_258_plus_PLR_Octet_FEC_Engine=0x40" offset="0x0.16" size="0x0.8" />
	<field name="nvlink_fec_override_cap_200g_1x_mode_a" descr="200G 1x Mode A - override capability bitmask:Bit 1: RS_FEC_546_516_plus_PLR_Double_FEC_EngineBit 2: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 3: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 4: RS_FEC_288_258_plus_PLR_Double_FEC_EngineBit 5: RS_FEC_288_258_plus_PLR_Quad_FEC_EngineBit 6: RS_FEC_288_258_plus_PLR_Octet_FEC_EngineAll others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x2,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x4,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x8,RS_FEC_288_258_plus_PLR_Double_FEC_Engine=0x10,RS_FEC_288_258_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_288_258_plus_PLR_Octet_FEC_Engine=0x40" offset="0x0.24" size="0x0.8" />
	<field name="nvlink_fec_override_admin_100g_1x_mode_a" descr="100G 1x Mode A - override admin bitmask (one-hot setting):0: auto_mode - no overrideBit 1: RS_FEC_546_516_plus_PLR_Double_FEC_EngineBit 2: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 3: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 4: RS_FEC_288_258_plus_PLR_Double_FEC_EngineBit 5: RS_FEC_288_258_plus_PLR_Quad_FEC_EngineBit 6: RS_FEC_288_258_plus_PLR_Octet_FEC_EngineBit 7: RS_FEC_546_516_Double_FEC_EngineAll others Reserved" access="RW" enum="auto_mode=0x0,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x2,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x4,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x8,RS_FEC_288_258_plus_PLR_Double_FEC_Engine=0x10,RS_FEC_288_258_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_288_258_plus_PLR_Octet_FEC_Engine=0x40,RS_FEC_546_516_Double_FEC_Engine=0x80" offset="0x4.16" size="0x0.8" />
	<field name="nvlink_fec_override_cap_100g_1x_mode_a" descr="100G 1x Mode A - override capability bitmask:Bit 1: RS_FEC_546_516_plus_PLR_Double_FEC_EngineBit 2: RS_FEC_546_516_plus_PLR_Quad_FEC_EngineBit 3: RS_FEC_546_516_plus_PLR_Octet_FEC_EngineBit 4: RS_FEC_288_258_plus_PLR_Double_FEC_EngineBit 5: RS_FEC_288_258_plus_PLR_Quad_FEC_EngineBit 6: RS_FEC_288_258_plus_PLR_Octet_FEC_EngineBit 7: RS_FEC_546_516_Double_FEC_EngineAll others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x2,RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x4,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x8,RS_FEC_288_258_plus_PLR_Double_FEC_Engine=0x10,RS_FEC_288_258_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_288_258_plus_PLR_Octet_FEC_Engine=0x40,RS_FEC_546_516_Double_FEC_Engine=0x80" offset="0x4.24" size="0x0.8" />
</node>

<node name="pplm_reg_ext" descr="" attr_required_tlvs="index:s" size="0x80.0" >
	<field name="plr_vld" descr="When set, PLR set configurations are valid, otherwise ignored.relevant fields for PLR configurations are: plr_margin_th, tx_crc_plr,\;plr_reject_mode.Feature is supported when PCAM bit 95 is set" access="WO" offset="0x0.2" size="0x0.1" />
	<field name="tx_crc_plr_vld" descr="Valid only when plr_vld is set. When set, PLR configuration for\;tx_crc_plr is used , otherwise ignored." access="WO" offset="0x0.3" size="0x0.1" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="port_type" descr="Supported only when indicated by PCAM0: Network_Port1: Near_End_Port - For Gearbox - Host side2: Internal_IC_Port3: Far_End_Port - For Gearbox - Line sideOther values are reserved.Using port_type ‘0’ will override all different parts of the link\;structure.Using port_type ‘1’ will configure also port_type ‘2’ accordingly and\;vise versa." access="INDEX" enum="Network_Port=0x0,Near_End_Port=0x1,Internal_IC_Port=0x2,Far_End_Port=0x3" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type.0: Local_port_number1: IB_port_number" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="plr_reject_mode_vld" descr="Valid only when plr_vld is set. When set, PLR configuration for\;plr_reject_mode is used, otherwise ignored." access="WO" offset="0x0.24" size="0x0.1" />
	<field name="plr_margin_th_override_to_default" descr="Valid only if plr_vld is not set. When set, force default value into the\;plr_margin_thNote: Read access is supported only when\;PCAM.feature_group=1.feature_cap_mask - bit 9 is set" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="tx_crc_plr_override_to_default" descr="Valid only if plr_vld is not set. When set, force default value into the\;tx_crc_plrNote: Read access is supported only when\;PCAM.feature_group=1.feature_cap_mask - bit 9 is set" access="RW" offset="0x0.26" size="0x0.1" />
	<field name="plr_reject_mode_override_to_default" descr="Valid only if plr_vld is not set. When set, force default value into the\;plr_reject_modeNote: Read access is supported only when\;PCAM.feature_group=1.feature_cap_mask - bit 9 is set" access="RW" offset="0x0.27" size="0x0.1" />
	<field name="resilink_fec_ind" descr="Valid only for resilink link is operational, otherwise ignored.When cleared, will represent the Ethernet equivalent FEC of the resilink\;protocol.When set, will represent the Resilink FEC protocol" access="INDEX" offset="0x0.28" size="0x0.1" />
	<field name="plr_force_peer_oper" descr="Indicates the operational status of the force mechanism applied to the\;PLR settings between the two ports during the last link negotiation:0 - No_force_applied1 - Peer_settings_forced2 - Local_settings_forced" access="RO" offset="0x0.30" size="0x0.2" />
	<field name="fec_generation" descr="For protocol generations presented as an enum under this field,\;fec_override_cap &amp; fec_override_admin fields per each supported rate\;will appear under the fec_page_data field.0: NVL61: NVL7" access="RO" enum="NVL6=0x0,NVL7=0x1" offset="0x4.0" size="0x0.4" />
	<field name="plr_force_peer_cap" descr="Indicates whether the host supports forcing the PLR configuration\;between the two connected ports during link negotiation." access="RO" offset="0x4.6" size="0x0.1" />
	<field name="plr_force_peer_admin" descr="Controls whether the local port forces the PLR settings onto the peer\;port.0 - FW_default1 - Do_not_force2 - Force_peer" access="RW" offset="0x4.7" size="0x0.2" />
	<field name="plr_margin_th_support" descr="Supported PLR margin thresholds capability bitmask:Bit 0: PLR margin threshold 0 supportedBit 1: PLR margin threshold 1 supportedBit 2: PLR margin threshold 2 supportedBit 3: PLR margin threshold 3 supportedBit 4: PLR margin threshold 4 supportedBit 5: PLR margin threshold 5 supportedBit 6: PLR margin threshold 6 supportedBit 7: PLR margin threshold 7 supported" access="RO" offset="0x4.9" size="0x0.8" />
	<field name="tx_crc_plr_support" descr="Supported tx CRC over PLR capability0: not supported1: supported" access="RO" offset="0x4.18" size="0x0.1" />
	<field name="plr_reject_mode_support" descr="Supported PLR reject modes capability bitmask:Bit 0: rejection_based_on_plr_marginBit 1: rejection_based_on_crc_and_csBit 2: rejection_based_on_CSBit 3: rejection_based_on_CS_on_demand" access="RO" offset="0x4.19" size="0x0.4" />
	<field name="plr_reject_mode_oper" descr="This is the operational value:0: rejection_based_on_plr_margin1: rejection_based_on_crc_and_cs2: rejection_based_on_CS3: rejection_based_on_CS_on_demand" access="RO" offset="0x4.25" size="0x0.2" />
	<field name="tx_crc_plr_oper" descr="This is the operational value. When set tx CRC over PLR is enabled" access="RO" offset="0x4.27" size="0x0.1" />
	<field name="plr_margin_th_oper" descr="This is the operational value.PLR margin threshold in which a codeword is retransmitted" access="RO" offset="0x4.28" size="0x0.4" />
	<field name="fec_mode_active" descr="Active FEC (bitmask)For each enum, a short prefix for tools is presented in the row below.0: No_FEC1: Firecode_FECFC_FEC2: Standard_RS_FEC - RS(528,514)KR4_FEC3: Standard_LL_RS_FEC - RS(271,257)LL_FEC4: Interleaved_Quad_RS_FEC - (544,514)  Quad_KP4_FEC5: Interleaved_Quad_RS_FEC_PLR - (546,516)Quad_KP4_FEC6: Interleaved_Standard_RS-FEC - (544,514)Int_KP4_FEC7: Standard_RS_KP4_FEC - (544,514)KP4_FEC8: Interleaved_Octet_RS_FEC_PLR - (546,516)Octet_KP4_FEC9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)ELL_FEC10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - (272,257+1)Int_ELL_FEC11: Interleaved_Standard_RS_FEC_PLR - (544,514)Int_KP4_FEC_PLR12: RS-FEC - (544,514) + PLRKP4_FEC_PLR13: LL-FEC - (271,257) + PLRLL_FEC_PLR14: Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]ELL_FEC_PLR15: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]Int_ELL_FEC_PLR16: RS_FEC_288_258_plus_PLR_Double_FEC_Engine17: RS_FEC_288_258_plus_PLR_Quad_FEC_Engine18: RS_FEC_288_258_plus_PLR_Octet_FEC_Engine" access="RO" enum="No_FEC=0x0,Firecode_FEC=0x1,Standard_RS_FEC=0x2,Standard_LL_RS_FEC=0x3,Interleaved_Quad_RS_FEC=0x4,Interleaved_Quad_RS_FEC_PLR=0x5,Interleaved_Standard_RS_FEC=0x6,Standard_RS_KP4_FEC=0x7,Interleaved_Octet_RS_FEC_PLR=0x8,Ethernet_Consortium_LL_50G_RS_FEC=0x9,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC=0xa,Interleaved_Standard_RS_FEC_PLR=0xb,RS_FEC=0xc,LL_FEC=0xd,Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xe,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xf,RS_FEC_288_258_plus_PLR_Double_FEC_Engine=0x10,RS_FEC_288_258_plus_PLR_Quad_FEC_Engine=0x11,RS_FEC_288_258_plus_PLR_Octet_FEC_Engine=0x12" offset="0xc.0" size="0x0.24" />
	<field name="plr_reject_mode" descr="This is the admin value:0: rejection_based_on_plr_margin1: rejection_based_on_crc_and_cs2: rejection_based_on_CS3: rejection_based_on_CS_on_demandset value is used only if both plr_vld and plr_reject_mode_vld are set,\;else configure to default value" access="RW" offset="0xc.24" size="0x0.2" />
	<field name="tx_crc_plr" descr="This is the admin value. When set, tx CRC over PLR is enabled.Set value is used only if both plr_vld and tx_crc_plr_vld are set, else\;configure to default value.In addition, the set value has to be ‘1’ if the value in plr_reject_mode\;is rejection_based_on_crc_and_cs, and this is the only case where\;setting the value to ‘1’ is valid." access="RW" offset="0xc.27" size="0x0.1" />
	<field name="plr_margin_th" descr="This is the admin value.PLR margin threshold in which a codeword is retransmittedset value is used only if plr_vld is set to high, else configure to\;default value" access="RW" offset="0xc.28" size="0x0.4" />
	<field name="fec_override_cap_10g_40g" descr="10GE/40GE Ethernet FEC override capability bitmask:Bit 0: No_FECBit 1: Firecode_FECBit 2: Reserved2Bit 3: Reserved3" access="RO" enum="No_FEC=0x1,Firecode_FEC=0x2,Reserved2=0x4,Reserved3=0x8" offset="0x10.0" size="0x0.4" />
	<field name="fec_override_cap_25g" descr="25GE Ethernet FEC override capability bitmask:Bit 0: No_FECBit 1: Firecode_FECBit 2: RS_FECBit 3: Reserved" access="RO" enum="No_FEC=0x1,Firecode_FEC=0x2,RS_FEC=0x4,Reserved=0x8" offset="0x10.4" size="0x0.4" />
	<field name="fec_override_cap_50g" descr="50GE (2 lanes) Ethernet FEC override capability bitmask:Bit 0: No_FECBit 1: Firecode_FECBit 2: RS_FECBit 3: Reserved" access="RO" enum="No_FEC=0x1,Firecode_FEC=0x2,RS_FEC=0x4,Reserved=0x8" offset="0x10.8" size="0x0.4" />
	<field name="fec_override_cap_100g" descr="100GE (4 lanes) Ethernet FEC override capability bitmask:Bit 0: No_FECBit 1: Reserved1Bit 2: RS_FEC - (528,514)Bit 3: Reserved3" access="RO" enum="No_FEC=0x1,Reserved1=0x2,RS_FEC=0x4,Reserved3=0x8" offset="0x10.12" size="0x0.4" />
	<field name="fec_override_cap_56g" descr="56GE Ethernet FEC override capability bitmask:Bit 0: No_FECBit 1: Firecode_FECBit 2: Reserved2Bit 3: Reserved3" access="RO" enum="No_FEC=0x1,Firecode_FEC=0x2,Reserved2=0x4,Reserved3=0x8" offset="0x10.16" size="0x0.4" />
	<field name="rs_fec_correction_bypass_cap" descr="RS-FEC correction bypass override capability:0: NO_correction_bypass1: RS_FEC_correction_bypass" access="RO" enum="NO_correction_bypass=0x0,RS_FEC_correction_bypass=0x1" offset="0x10.28" size="0x0.4" />
	<field name="fec_override_admin_10g_40g" descr="10GE/40GE Ethernet FEC override admin, see 10g_40g_fec_override_cap.(one-hot setting):0: auto_mode - no overrideBit 0: No_FECBit 1: Firecode_FEC" access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2" offset="0x14.0" size="0x0.4" />
	<field name="fec_override_admin_25g" descr="25GE Ethernet FEC override admin, see 25g_fec_override_cap. (one-hot\;setting):0: auto_mode - no overrideBit 0: No_FECBit 1: Firecode_FECBit 2: RS_FECNote - 25g_fec_override_admin and 50g_fec_override_admin must be set\;with the same value." access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2,RS_FEC=0x4" offset="0x14.4" size="0x0.4" />
	<field name="fec_override_admin_50g" descr="50GE Ethernet FEC override admin, see 50g_fec_override_cap. (one-hot\;setting):0: auto_mode - no overrideBit 0: No_FECBit 1: Firecode_FECBit 2: RS_FECNote - 25g_fec_override_admin and 50g_fec_override_admin must be set\;with the same value." access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2,RS_FEC=0x4" offset="0x14.8" size="0x0.4" />
	<field name="fec_override_admin_100g" descr="100GE Ethernet FEC override admin, see 100g_fec_override_cap. (one-hot\;setting):0: auto_mode - no overrideBit 0: No_FECBit 2: RS_FEC" access="RW" enum="No_FEC=0x1,RS_FEC=0x4" offset="0x14.12" size="0x0.4" />
	<field name="fec_override_admin_56g" descr="56GE Ethernet FEC override admin, see 56g_fec_override_cap. (one-hot\;setting):0: auto_mode - no overrideBit 0: No_FECBit 1: Firecode_FEC" access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2" offset="0x14.16" size="0x0.4" />
	<field name="rs_fec_correction_bypass_admin" descr="RS-FEC correction bypass override admin: (one-hot setting):0: auto_mode - no override1: NO_correction_bypass2: RS_FEC_correction_bypass" access="RW" enum="auto_mode=0x0,NO_correction_bypass=0x1,RS_FEC_correction_bypass=0x2" offset="0x14.28" size="0x0.4" />
	<field name="fec_override_cap_200g_4x" descr="200GE FEC override capability bitmask:Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1Others bits reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x18.0" size="0x0.16" />
	<field name="fec_override_cap_400g_8x" descr="400GE FEC override capability bitmask:Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1All others are reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x18.16" size="0x0.16" />
	<field name="fec_override_cap_50g_1x" descr="50GE single lane override capability bitmask:Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1All others are reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x1c.0" size="0x0.16" />
	<field name="fec_override_cap_100g_2x" descr="100GE over 2 lanes, FEC override capability bitmask:Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1All others are reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x1c.16" size="0x0.16" />
	<field name="fec_override_admin_200g_4x" descr="200GE FEC override admin bitmask (one-hot setting)0: Auto_modeBit 7: RS_FEC_544_514 - (544,514)Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x20.0" size="0x0.16" />
	<field name="fec_override_admin_400g_8x" descr="400GE FEC override admin bitmask (one-hot setting):0: Auto_modeBit7: RS_FEC_544_514Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x20.16" size="0x0.16" />
	<field name="fec_override_admin_50g_1x" descr="50GE, 1lanes FEC override admin bitmask (one-hot setting)0: Auto_modeBit 7: RS_FEC_544_514 - (544,514)Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x24.0" size="0x0.16" />
	<field name="fec_override_admin_100g_2x" descr="100GE, 2 lanes FEC override admin bitmask (one-hot setting):0: Auto_modeBit 7: RS_FEC_544_514 - (544,514)Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x24.16" size="0x0.16" />
	<field name="fec_override_cap_400g_4x" descr="400GE, 4 lanes FEC override capability bitmask:Bit 7: RS_FEC_544_514 - (544,514)Bit 9: Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1 - (272,257+1)Other bits Reserved" access="RO" enum="RS_FEC_544_514=0x80,Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x200" offset="0x28.0" size="0x0.16" />
	<field name="fec_override_cap_800g_8x" descr="800GE, 8 lanes FEC override capability bitmask:Bit 7: RS_FEC_544_514 - RS-FEC (544,514)Bit 8: ReservedBit 9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)Other bits Reserved" access="RO" enum="RS_FEC_544_514=0x80,Reserved=0x100,Ethernet_Consortium_LL_50G_RS_FEC=0x200" offset="0x28.16" size="0x0.16" />
	<field name="fec_override_cap_100g_1x" descr="100GE, 1 lane FEC override capability bitmask:Bit 6: Interleaved_RS_FEC_544_514Bit 7: RS_FEC_544_514Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1Bit 10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1Other bits reserved" access="RO" enum="Interleaved_RS_FEC_544_514=0x40,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1=0x200,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x400" offset="0x2c.0" size="0x0.16" />
	<field name="fec_override_cap_200g_2x" descr="200GE, 2 lanes FEC override capability bitmask:Bit 7: RS_FEC_544_514Bit 9: Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1Other bits Reserved" access="RO" enum="RS_FEC_544_514=0x80,Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x200" offset="0x2c.16" size="0x0.16" />
	<field name="fec_override_admin_400g_4x" descr="400GE, 4 lanes FEC override admin bitmask (one-hot setting):0: Auto_modeBit 7: RS_FEC_544_514Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1=0x200" offset="0x44.0" size="0x0.16" />
	<field name="fec_override_admin_800g_8x" descr="800GE, 8 lanes FEC override admin bitmask (one-hot setting):0: Auto_modeBit 7: RS_FEC_544_514Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1=0x200" offset="0x44.16" size="0x0.16" />
	<field name="fec_override_admin_100g_1x" descr="100GE, 1 lane FEC override admin bitmask (one-hot setting):0: Auto_modeBit 6: Interleaved_RS_FEC_544_514Bit 7: RS_FEC_544_514Bit 9: Ethernet_Consortium_50G_Low_Latency_RS_FEC_272_257_plus_1Bit 10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1Other bits Reserved" access="RW" enum="Auto_mode=0x0,Interleaved_RS_FEC_544_514=0x40,RS_FEC_544_514=0x80,Ethernet_Consortium_50G_Low_Latency_RS_FEC_272_257_plus_1=0x200,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x400" offset="0x48.0" size="0x0.16" />
	<field name="fec_override_admin_200g_2x" descr="200GE, 2 lanes FEC override admin bitmask (one-hot setting):0: Auto_modeBit 7: RS_FEC_544_514Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1=0x200" offset="0x48.16" size="0x0.16" />
	<field name="fec_override_cap_800g_4x" descr="800GE, 4 lane FEC override capability bitmask:Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x58.0" size="0x0.16" />
	<field name="fec_override_cap_1600g_8x" descr="1600GE, 8 lane FEC override capability bitmask:Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x58.16" size="0x0.16" />
	<field name="fec_override_cap_200g_1x" descr="200GE, 1 lane FEC override capability bitmask:Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x5c.0" size="0x0.16" />
	<field name="fec_override_cap_400g_2x" descr="400GE, 2 lane FEC override capability bitmask:Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x5c.16" size="0x0.16" />
	<field name="fec_override_admin_800g_4x" descr="800GE, 4 lanes FEC override admin bitmask (one-hot setting):0: Auto_modeBit 4: RS_FEC_544_514_Quad_FEC_EngineOther bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x60.0" size="0x0.16" />
	<field name="fec_override_admin_1600g_8x" descr="1600GE, 8 lanes FEC override admin bitmask (one-hot setting):0: Auto_modeBit 4: RS_FEC_544_514_Quad_FEC_EngineOther bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x60.16" size="0x0.16" />
	<field name="fec_override_admin_200g_1x" descr="200GE, 1 lanes FEC override admin bitmask (one-hot setting):0: Auto_modeBit 4: RS_FEC_544_514_Quad_FEC_EngineOther bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x64.0" size="0x0.16" />
	<field name="fec_override_admin_400g_2x" descr="400GE, 2 lanes FEC override admin bitmask (one-hot setting):0: Auto_modeBit 4: RS_FEC_544_514_Quad_FEC_EngineOther bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x64.16" size="0x0.16" />
	<field name="fec_page_data" descr="PPLM - NVL6 Rates FEC Override LayoutPPLM - NVL7 Rates FEC Override Layout" subnode="pplm_reg_fec_page_data_auto_ext" access="RW" offset="0x68.0" size="0x18.0" union_selector="$(parent).fec_generation" />
</node>

<node name="pplm_reg_fec_page_data_auto_ext" descr="" attr_is_union="1" size="0x18.0" >
	<field name="pplm_nvl6_fec_ext" descr="" subnode="pplm_nvl6_fec_ext" access="RW" offset="0x0.0" selected_by="NVL6" size="0x18.0" />
	<field name="pplm_nvl7_rates_fec_ext" descr="" subnode="pplm_nvl7_rates_fec_ext" access="RW" offset="0x0.0" selected_by="NVL7" size="0x18.0" />
</node>

<node name="pplr_reg_ext" descr="" attr_required_tlvs="index:s" size="0x8.0" >
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0: Network_Port1: Near_End_Port- (For Retimer/Gearbox - Host side)2: Internal_IC_LR_Port3: Far_End_Port - (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" enum="Network_Port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="op_mod" descr="operational mode for link configurations for phy_ local_loopback mode.0 - link will operate in optimal latency performance mode1 - link will operate in same configurations as operational port.Note: for FEC override via PPLM register, chosen FEC will be according\;to the PPLM configuration that was set and this bit will be ignored for\;FEC purposes" access="OP" offset="0x0.8" size="0x0.1" />
	<field name="apply_im" descr="Apply immediate: When set, the enabled/disabled loopback will be set\;immediately even if link is active.Note: Currently supported only for Bit 7: LL_local_loopback. in other\;loopbacks will be ignored" access="OP" offset="0x0.9" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lb_en" descr="Loopback enable - only one bit shall be set.Bit 0: Phy_remote_loopbackBit 1: Phy_local_loopbackBit 2: External_local_loopbackBit 7: LL_local_loopback" access="RW" enum="Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4,LL_local_loopback=0x80" offset="0x4.0" size="0x0.12" />
	<field name="lb_cap" descr="Loopback capability - bitmaskBit 0: Phy_remote_loopbackBit 1: Phy_local_loopback - When set the port’s egress traffic is\;looped back to the receiver and the port transmitter is disabled.Bit 2: External_local_loopback - Enables the port’s transmitter to\;link with the port’s receiver using an external loopback connector.Bit 7: LL_local_loopback - When set the port’s egress Link layer\;traffic is looped back to the receiver. Physical port in this\;loopback mode is down.Notes1. Phy remote loopback can be supported only for lane rate higher\;than 25Gbuad in the 16nm devices.When in NEA/NED\;loopbacks, peer transmitting may still interfere wtih local receiver\;and cause link performance degradation" access="RO" enum="Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4,LL_local_loopback=0x80" offset="0x4.16" size="0x0.12" />
	<field name="lb_cap_mode_idx" descr="Supported only when indicated by PCAM Bit 97:PPLR.lb_cap_mode_idx. The\;returned value of the ‘lp_cap’ capability field will be according to the\;selected mode index:0: Operational_mode1: Test_mode" access="INDEX" enum="Operational_mode=0x0,Test_mode=0x1" offset="0x4.30" size="0x0.1" />
</node>

<node name="pprm_phy_steps_ext" descr="" size="0x68.0" >
	<field name="step1_preset_support_mask" descr="(see above)" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="step2_preset_support_mask" descr="Bitmask of supported preset for step1/2Bit 0: PEQ_onlyBit 1: CDR_toggleBit 2: full_duplex_EQBit 3: Logic_lock_onlyBit 5: redo_link_trainingBit 6: mode_a_recovery Bit 7: cpo_recovery" access="RO" enum="PEQ_only=0x1,CDR_toggle=0x2,full_duplex_EQ=0x4,Logic_lock_only=0x8,redo_link_training=0x20,mode_a_recovery=0x40,cpo_recovery=0x80" offset="0x0.12" size="0x0.8" />
	<field name="eff_align_aq_time" descr="64ns granularitytime to stabilize effective align acquired0: FW_default" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="step1_preset_admin" descr="(see above)" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="step2_preset_admin" descr="Admin for requested preset during negotiation for step1/20: FW_default1: PEQ_only2: CDR_toggle3: full_duplex_EQ4: Logic_lock_only6: redo_link_training7: mode_a_recovery 8: cpo_recovery0xF: no_request - skip step" access="RW" enum="FW_default=0x0,PEQ_only=0x1,CDR_toggle=0x2,full_duplex_EQ=0x3,Logic_lock_only=0x4,redo_link_training=0x6,mode_a_recovery=0x7,cpo_recovery=0x8,no_request=0xf" offset="0x4.8" size="0x0.4" />
	<field name="eff_align_aq_time_oper" descr="64ns granularitytime to stabilize effective align acquired operational fields." access="RO" offset="0x4.13" size="0x0.8" />
	<field name="step2_time_gran" descr="Affects granularity of all timers and timeouts of step2 fields:step2_state_65_to_66_time, step2_state_66_to_67_time,\;step2_state_67_to_68_time, step2_state_60_timeout,\;step2_state_61_timeout, step2_state_62_timeout,\;step2_state_60_to_linkup_timeout0: 1us1: 10us2: 100us" access="RO" offset="0x4.28" size="0x0.2" />
	<field name="step1_state_65_to_66_time_pre1" descr="(see above)" access="RW" offset="0x8.0" size="0x0.10" />
	<field name="step2_state_65_to_66_time_pre1" descr="1us / step2_time_gran granularity for preset 1 (PEQ only)Time for state transition 0x65\; to\;0x660: FW_default" access="RW" offset="0x8.10" size="0x0.10" />
	<field name="step1_peq_n_retry_pre1" descr="(see above)" access="RW" offset="0x8.20" size="0x0.5" />
	<field name="step2_peq_n_retry_pre1" descr="Number of PEQ to do in state 0x68 for preset 1 (PEQ only)0: FW_default1-15: &lt;N&gt; PEQ retries16-30: reserved31: skip_state_0x68" access="RW" offset="0x8.26" size="0x0.5" />
	<field name="step1_state_66_to_67_time_pre1" descr="(see above)" access="RW" offset="0xc.0" size="0x0.16" />
	<field name="step2_state_66_to_67_time_pre1" descr="1us / step2_time_gran granularity for preset 1 (PEQ only)Time for state transition 0x66 to\;0x670: FW_default" access="RW" offset="0xc.16" size="0x0.16" />
	<field name="step1_state_67_to_68_time_pre1" descr="(see above)" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="step2_state_67_to_68_time_pre1" descr="1us / step2_time_gran granularity for preset 1 (PEQ only)Time for state transition 0x66\; to\;0x670: FW_default" access="RW" offset="0x10.16" size="0x0.16" />
	<field name="step1_state_60_timeout" descr="(see above)" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="step2_state_60_timeout" descr="1us / step2_time_gran granularity.Watchdog timeout for state 0x60\;0: FW_defaultNote - Field is ignored by FW in NVL7 devices, timeout is set by\;step2_state_60_to_linkup_timeout" access="RW" offset="0x14.16" size="0x0.16" />
	<field name="step1_state_61_timeout" descr="(see above)" access="RW" offset="0x18.0" size="0x0.16" />
	<field name="step2_state_61_timeout" descr="1us / step2_time_gran granularity.Watchdog timeout for state 0x61\;0: FW_defaultNote - Field is ignored by FW in NVL7 devices, timeout is set by\;step2_state_60_to_linkup_timeout" access="RW" offset="0x18.16" size="0x0.16" />
	<field name="step1_state_62_timeout" descr="(see above)" access="RW" offset="0x1c.0" size="0x0.16" />
	<field name="step2_state_62_timeout" descr="1us / step2_time_gran granularity.Watchdog timeout for state 0x62\;0: FW_defaultNote - Field is ignored by FW in NVL7 devices, timeout is set by\;step2_state_60_to_linkup_timeout" access="RW" offset="0x1c.16" size="0x0.16" />
	<field name="step2_state_60_to_linkup_timeout_oper" descr="10us granularity.Watchdog timeout for states 0x60 to 0x62 after negotiation agreement" access="RO" offset="0x20.0" size="0x0.16" />
	<field name="step2_state_60_to_linkup_timeout" descr="10us granularity.Watchdog timeout for states 0x60 to 0x620: FW_default" access="RW" offset="0x20.16" size="0x0.16" />
	<field name="step1_preset_oper" descr="(see above)" access="RO" offset="0x24.0" size="0x0.4" />
	<field name="step2_preset_oper" descr="0x0: no_request - skip step1: PEQ_only2: CDR_toggle3: full_duplex_EQ4: Logic_lock_only6: mode_a_recovery 7: cpo_recovery" access="RO" offset="0x24.8" size="0x0.4" />
	<field name="step1_peq_n_retry_oper" descr="(see above)" access="RO" offset="0x24.16" size="0x0.5" />
	<field name="step2_peq_n_retry_oper" descr="Agreed peq N retry in state 0x681-15: &lt;N&gt; PEQ retries16-30: reserved31: skip_state_0x68" access="RO" offset="0x24.24" size="0x0.5" />
	<field name="step1_state_65_to_66_time_oper" descr="(see above)" access="RO" offset="0x28.0" size="0x0.10" />
	<field name="step2_state_65_to_66_time_oper" descr="1us / step2_time_gran granularity.Time for state transition 0x65\; to\;0x660: FW_default" access="RO" offset="0x28.10" size="0x0.10" />
	<field name="step1_state_66_to_67_time_oper" descr="(see above)" access="RO" offset="0x2c.0" size="0x0.16" />
	<field name="step2_state_66_to_67_time_oper" descr="1us / step2_time_gran granularity.Time for state transition 0x66 to\;0x670: FW_default" access="RO" offset="0x2c.16" size="0x0.16" />
	<field name="step1_state_67_to_68_time_oper" descr="(see above)" access="RO" offset="0x30.0" size="0x0.16" />
	<field name="step2_state_67_to_68_time_oper" descr="1us / step2_time_gran granularity.Time for state transition 0x66\; to\;0x670: FW_default" access="RO" offset="0x30.16" size="0x0.16" />
	<field name="step1_state_60_timeout_oper" descr="(see above)" access="RO" offset="0x34.0" size="0x0.16" />
	<field name="step2_state_60_timeout_oper" descr="1us / step2_time_gran granularity.Watchdog timeout for state 0x60\;0: FW_default" access="RO" offset="0x34.16" size="0x0.16" />
	<field name="step1_state_61_timeout_oper" descr="(see above)" access="RO" offset="0x38.0" size="0x0.16" />
	<field name="step2_state_61_timeout_oper" descr="1us / step2_time_gran granularity.Watchdog timeout for state 0x61\;0: FW_default" access="RO" offset="0x38.16" size="0x0.16" />
	<field name="step1_state_62_timeout_oper" descr="(see above)" access="RO" offset="0x3c.0" size="0x0.16" />
	<field name="step2_state_62_timeout_oper" descr="1us / step2_time_gran granularity.Watchdog timeout for state 0x62\;0: FW_default" access="RO" offset="0x3c.16" size="0x0.16" />
	<field name="step1_state_65_to_66_time_pre2" descr="(see above)" access="RW" offset="0x48.0" size="0x0.10" />
	<field name="step2_state_65_to_66_time_pre2" descr="1us / step2_time_gran granularity for preset 2 (CDR toggle)Time for state transition 0x65\; to\;0x660: FW_default" access="RW" offset="0x48.10" size="0x0.10" />
	<field name="step1_peq_n_retry_pre2" descr="(see above)" access="RW" offset="0x48.20" size="0x0.5" />
	<field name="step2_peq_n_retry_pre2" descr="Number of PEQ to do in state 0x68 for preset 2 (CDR toggle)0: FW_default1-15: &lt;N&gt; PEQ retries16-30: reserved31: skip_state_0x68" access="RW" offset="0x48.26" size="0x0.5" />
	<field name="step1_state_66_to_67_time_pre2" descr="(see above)" access="RW" offset="0x4c.0" size="0x0.16" />
	<field name="step2_state_66_to_67_time_pre2" descr="1us / step2_time_gran granularity for preset 2 (CDR toggle)Time for state transition 0x66 to\;0x670: FW_default" access="RW" offset="0x4c.16" size="0x0.16" />
	<field name="step1_state_67_to_68_time_pre2" descr="(see above)" access="RW" offset="0x50.0" size="0x0.16" />
	<field name="step2_state_67_to_68_time_pre2" descr="1us / step2_time_gran granularity for preset 2 (CDR toggle)Time for state transition 0x66\; to\;0x670: FW_default" access="RW" offset="0x50.16" size="0x0.16" />
	<field name="step1_state_65_to_66_time_pre3" descr="(see above)" access="RW" offset="0x54.0" size="0x0.10" />
	<field name="step2_state_65_to_66_time_pre3" descr="1us / step2_time_gran granularity for preset 3 (Full duplex)Time for state transition 0x65\; to\;0x660: FW_default" access="RW" offset="0x54.10" size="0x0.10" />
	<field name="step1_peq_n_retry_pre3" descr="(see above)" access="RW" offset="0x54.20" size="0x0.5" />
	<field name="step2_peq_n_retry_pre3" descr="Number of PEQ to do in state 0x68 for preset 3 (Full duplex)0: FW_default1-15: &lt;N&gt; PEQ retries16-30: reserved31: skip_state_0x68" access="RW" offset="0x54.26" size="0x0.5" />
	<field name="step1_state_66_to_67_time_pre3" descr="(see above)" access="RW" offset="0x58.0" size="0x0.16" />
	<field name="step2_state_66_to_67_time_pre3" descr="1us / step2_time_gran granularity for preset 3 (Full duplex)Time for state transition 0x66 to\;0x670: FW_default" access="RW" offset="0x58.16" size="0x0.16" />
	<field name="step1_state_67_to_68_time_pre3" descr="(see above)" access="RW" offset="0x5c.0" size="0x0.16" />
	<field name="step2_state_67_to_68_time_pre3" descr="1us / step2_time_gran granularity for preset 3 (Full duplex)Time for state transition 0x66\; to\;0x670: FW_default" access="RW" offset="0x5c.16" size="0x0.16" />
</node>

<node name="pprm_phy_steps_extended_ext" descr="" size="0x68.0" >
	<field name="step1_consec_recovery_window_oper_pre1" descr="Agreed time for step 1 recovery window. Used for preset 1 (PEQ only).\;Granularity 1 us." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="step1_iterations_oper_pre1" descr="Agreed number of step 1 recovery iterations conducted by HW before\;transitioning to step 2 FW recovery. Used for preset 1 (PEQ only)." access="RO" offset="0x0.24" size="0x0.8" />
	<field name="step1_consec_recovery_window_cap_pre1" descr="Max supported time for step 1 recovery window. Used for preset 1\;(PEQ only). Granularity 1 us. If value is 0, recovery window is not\;supported." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="step1_iterations_cap_pre1" descr="Max number of supported step 1 recovery iterations. If value is 0,\;multiple step 1 iterations are not supported. Used for preset 1 (PEQ only)." access="RO" offset="0x4.24" size="0x0.8" />
	<field name="step1_consec_recovery_window_admin_pre1" descr="Admin field for step 1 recovery window time. Used for preset 1\;(PEQ only). Granularity 1 us. Applicable only if\;step1_consec_recovery_window_cap_pre1 is non-zero. 0: fw_default." access="RW" offset="0x8.0" size="0x0.16" />
	<field name="step1_iterations_admin_pre1" descr="Admin field for requested number of step 1 recovery iterations during\;negotiation. Used for preset 1 (PEQ only). Applicable only if\;step1_iterations_cap_pre1 is non-zero. 0: fw_default." access="RW" offset="0x8.24" size="0x0.8" />
	<field name="step1_consec_recovery_window_oper_pre2" descr="Agreed time for step 1 recovery window. Used for preset 2 (CDR toggle).\;Granularity 1 us." access="RO" offset="0xc.0" size="0x0.16" />
	<field name="step1_iterations_oper_pre2" descr="Agreed number of step 1 recovery iterations conducted by HW before\;transitioning to step 2 FW recovery. Used for preset 2 (CDR toggle)." access="RO" offset="0xc.24" size="0x0.8" />
	<field name="step1_consec_recovery_window_cap_pre2" descr="Max supported time for step 1 recovery window. Used for preset 2\;(CDR toggle). Granularity 1 us. If value is 0, recovery window is not\;supported." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="step1_iterations_cap_pre2" descr="Max number of supported step 1 recovery iterations. If value is 0,\;multiple step 1 iterations are not supported. Used for preset 2\;(CDR toggle)." access="RO" offset="0x10.24" size="0x0.8" />
	<field name="step1_consec_recovery_window_admin_pre2" descr="Admin field for step 1 recovery window time. Used for preset 2\;(CDR toggle). Granularity 1 us. Applicable only if\;step1_consec_recovery_window_cap_pre2 is non-zero. 0: fw_default." access="RW" offset="0x14.0" size="0x0.16" />
	<field name="step1_iterations_admin_pre2" descr="Admin field for requested number of step 1 recovery iterations during\;negotiation. Used for preset 2 (CDR toggle). Applicable only if\;step1_iterations_cap_pre2 is non-zero. 0: fw_default." access="RW" offset="0x14.24" size="0x0.8" />
	<field name="step1_consec_recovery_window_oper_pre3" descr="Agreed time for step 1 recovery window. Used for preset 3\;(Full duplex EQ). Granularity 1 us." access="RO" offset="0x18.0" size="0x0.16" />
	<field name="step1_iterations_oper_pre3" descr="Agreed number of step 1 recovery iterations conducted by HW before\;transitioning to step 2 FW recovery. Used for preset 3 (Full duplex EQ)." access="RO" offset="0x18.24" size="0x0.8" />
	<field name="step1_consec_recovery_window_cap_pre3" descr="Max supported time for step 1 recovery window. Used for preset 3\;(Full duplex EQ). Granularity 1 us. If value is 0, recovery window is\;not supported." access="RO" offset="0x1c.0" size="0x0.16" />
	<field name="step1_iterations_cap_pre3" descr="Max number of supported step 1 recovery iterations. If value is 0,\;multiple step 1 iterations are not supported. Used for preset 3\;(Full duplex EQ)." access="RO" offset="0x1c.24" size="0x0.8" />
	<field name="step1_consec_recovery_window_admin_pre3" descr="Admin field for step 1 recovery window time. Used for preset 3\;(Full duplex EQ). Granularity 1 us. Applicable only if\;step1_consec_recovery_window_cap_pre3 is non-zero. 0: fw_default." access="RW" offset="0x20.0" size="0x0.16" />
	<field name="step1_iterations_admin_pre3" descr="Admin field for requested number of step 1 recovery iterations during\;negotiation. Used for preset 3 (Full duplex EQ). Applicable only if\;step1_iterations_cap_pre3 is non-zero. 0: fw_default." access="RW" offset="0x20.24" size="0x0.8" />
</node>

<node name="pprm_reg_ext" descr="" attr_required_tlvs="index:s" size="0x94.0" >
	<field name="ovrd_no_neg_bhvr" descr="Defines the behavior of no_neg_bhvr field.0: ingore_no_neg_bhvr_field - stay with current configured behaivour1: no_neg_behavior_according_to_fw_defult - ignore no_neg_bhvr set, and\;set FW default for the behavior2: no_neg_behavior_according_to_no_neg_bhvr_field - set behavior\;according to configured no_neg_bhvr field" access="RW" offset="0x0.2" size="0x0.2" />
	<field name="wait_for_module_cap" descr="When set, wait_for_module supported" access="RO" offset="0x0.6" size="0x0.1" />
	<field name="recovery_go_once_cap" descr="When set, recovery_go_once is supported and configurable." access="RO" offset="0x0.7" size="0x0.1" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type.0 - Local port number1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="recovery_go_once" descr="Valid only when recovery_go_once_cap is set &amp; oper_recovery ≠ 0When set, will trigger recovery flow according to the configured\;recovery paramters set in this register." access="WO" offset="0x0.27" size="0x0.1" />
	<field name="param_select" descr="Selects which recovery parameters is selected in param_page_data.0: no_param_select1: phy_recovery_steps2: phy_recovery_steps_extendedNote - valid only if recovery type is also supported in\;recovery_types_cap." access="INDEX" enum="no_param_select=0x0,phy_recovery_steps=0x1,phy_recovery_steps_extended=0x2" offset="0x0.28" size="0x0.4" />
	<field name="recovery_types_cap" descr="Recovery types that are supported per local port.Bit 0: host_logic_re_lockBit 1: host_serdes_feqBit 2: module_tx_disableBit 3: module_datapath_full_toggleBit 4: phy_recovery_steps" access="RO" enum="host_logic_re_lock=0x1,host_serdes_feq=0x2,module_tx_disable=0x4,module_datapath_full_toggle=0x8,phy_recovery_steps=0x10" offset="0x4.0" size="0x0.8" />
	<field name="recovery_policy_cap" descr="When set, recovery_policy_config is supported and configurable,\;otherwise ignored." access="RO" offset="0x4.14" size="0x0.1" />
	<field name="recovery_rx_tx_timers_cap" descr="when set, recovery_tx_toggle_delay, recovery_tx_toggle_delay,\;recovery_rx_algo_time, recovery_tx_re_iter" access="RO" offset="0x4.15" size="0x0.1" />
	<field name="no_neg_bhvr" descr="Relevant only if ovrd_no_neg_bhvr is set to ‘2’, ignored otherwiseIn case of no negotiation happened during link up flow, defines the\;behavior of enabled recovery types:Bit 0: host_logic_re_lockBit 1: host_serdes_feqBit 2-3: reserved0: Disaled1: Enabled" access="RW" enum="host_logic_re_lock=0x1,host_serdes_feq=0x2,Disaled=0x0,Enabled=0x1" offset="0x4.24" size="0x0.4" />
	<field name="wd_logic_re_lock_res" descr="time resolution for wd_time_host_logic_re_lock field.0: 1ms1: 10ms2: 100ms3: 1 sec" access="RW" offset="0x4.28" size="0x0.2" />
	<field name="oper_logic_re_lock_res" descr="time resolution for oper_time_host_logic_re_lock field.0: 1ms1: 10ms2: 100ms3: 1 sec" access="RO" offset="0x4.30" size="0x0.2" />
	<field name="module_datapath_full_toggle" descr="(see above)" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="module_tx_disable" descr="(see above)" access="RW" offset="0x8.4" size="0x0.4" />
	<field name="host_serdes_feq" descr="(see above)" access="RW" offset="0x8.8" size="0x0.4" />
	<field name="host_logic_re_lock" descr="(see above)" access="RW" offset="0x8.12" size="0x0.4" />
	<field name="phy_recovery_steps" descr="Admin Configurations per recovery type.Recovery types:Host Logic re_lock - Physical layer alignment re-lockHost SerDes Full EQ3. Module Tx Disable - Toggle module optical laser to off–&gt;on.\;supported only on optical modules that support TxDisable commandFull module Toggle - Re-initialization of CMIS module DPSM.PHY recovery steps0: FW_default1: Enable2: Disable3: Disable_Support_in_NegotiationNote - when phy_recovery_steps are enabled, all step1/step2 configuration fields are valid" access="RW" enum="FW_default=0x0,Enable=0x1,Disable=0x2,Disable_Support_in_Negotiation=0x3" offset="0x8.16" size="0x0.4" />
	<field name="phy_mode_idx" descr="When supported, setting this bit will update supported recovery\;capabilities.0: mode_b 1: mode_a If field is set to ‘1’, FW will only accept configurations of following\;fields under phy_recovery_steps page - step2_preset_admin,\;step2_state_62_timeout, step2_state_60_to_linkup_timeoutNote: Field is supported only whenPCAM.feature_group=1.feature_cap_mask - bit 17 is set" access="INDEX" offset="0x8.27" size="0x0.1" />
	<field name="link_down_timeout_override_to_default" descr="When set, force default value into the link_down_timeout field.Note: This field is supported only when indicated by\;PCAM.feature_group=1.Bit 5." access="RW" offset="0x8.31" size="0x0.1" />
	<field name="link_down_timeout" descr="Desired time in 1 mSec granularity from start of the recovery process\;until port announces port down.1. 0x0 - Means that port will announce port down immediately, and will\;try “recovery” types when port is down.2. 0xFFFF - Means all recovery types allowed will be tried (if agreed)\;before port announces down.Note: For QM4 and GR100, the values 0x0 and 0xFFFF are not supported. If\;these values are set, they will be ignored." access="RW" offset="0xc.0" size="0x0.16" />
	<field name="link_down_timeout_oper" descr="operational time in 1 mSec granularity from start of the recovery\;process until port announces port down after negotiation agreed on both\;sides" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="draining_timeout" descr="Time in mSec from start of the recovery process until port draining\;starts (and if port is still in “LinkUp”).Value of 0 means draining is disabled.Default value of 100mSec" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="delay_on_module_read" descr="ms delay before module check, to allow module status update0: FW_default -" access="RW" offset="0x14.16" size="0x0.8" />
	<field name="wait_for_module" descr="When enabled, host waits with recovery algorithm until module electrical\;output towards host indicates valid output.When disabled, host starts recovery algorithm immediatly on trigger.0: FW_default1: wait_for_module_en2: wait_for_module_dis3: force_module_recovery_on_host_failure" access="RW" offset="0x14.26" size="0x0.2" />
	<field name="oper_recovery" descr="Bitmask of agreed and operational recovery modes.Prior to negotiation and linkup value will be 0.Bit 0: host_logic_re_lockBit 1: host_serdes_feqBit 2: module_tx_disableBit 3: module_datapath_full_toggleBit 4: phy_recovery_steps" access="RO" enum="host_logic_re_lock=0x1,host_serdes_feq=0x2,module_tx_disable=0x4,module_datapath_full_toggle=0x8,phy_recovery_steps=0x10" offset="0x18.0" size="0x0.8" />
	<field name="recovery_policy_config" descr="Valid only if recovery_policy_cap is set otherwise ignoredSelects a pre-defined recovery policy preset.When set to a non-zero value, the following fields are overridden and\;ignored: Host_logic_re_lock, Host_serdes_feq, phy_recovery_steps0: explicit_config_controls - based on the config fields mentioned\;above.setting this enum, with all other control fields (Host_logic_re_lock,\;Host_serdes_feq, phy_recovery_steps) at 0 will set FW default1: recovery_off2: robust_optimized - Uses the most robust recovery algorithm within the\;allowed time window. May improve link performance, but takes longer to\;complete.3: gradual_recovery - Runs shorter algorithms first, escalating to more\;robust ones only if needed. Faster to succeed, but may not improve link\;performance." access="RW" offset="0x18.22" size="0x0.2" />
	<field name="wd_module_full_toggle" descr="500ms granularity for watchdog timer in Module full toggle recovery0: FW default - valid for set onlyon GET operation, returns watchdog value requested" access="RW" offset="0x1c.0" size="0x0.8" />
	<field name="wd_module_tx_disable" descr="100ms granularity for watchdog timer in Module Tx Disable recovery0: FW default - valid for set onlyon GET operation, returns watchdog value requested" access="RW" offset="0x1c.8" size="0x0.8" />
	<field name="wd_host_serdes_feq" descr="10ms granularity for watchdog timer in host FEQ recovery0: FW default - valid for set onlyon GET operation, returns watchdog value requested" access="RW" offset="0x1c.16" size="0x0.8" />
	<field name="wd_host_logic_re_lock" descr="granularity of wd_logic_re_lock_res for watchdog timer in host re_lock\;recovery0: FW default - valid for set onlyon GET operation, returns watchdog value requested" access="RW" offset="0x1c.24" size="0x0.8" />
	<field name="oper_time_module_full_toggle" descr="500ms granularity for operational timer in Module full toggle recoveryon GET operation, returns watchdog value requested" access="RO" offset="0x20.0" size="0x0.8" />
	<field name="oper_time_module_tx_disable" descr="100ms granularity for operational timer in Module Tx Disable recoveryon GET operation, returns watchdog value requested" access="RO" offset="0x20.8" size="0x0.8" />
	<field name="oper_time_host_serdes_feq" descr="10ms granularity for operational timer in host FEQ recoveryon GET operation, returns watchdog value requested" access="RO" offset="0x20.16" size="0x0.8" />
	<field name="oper_time_host_logic_re_lock" descr="granularity of oper_logic_re_lock_res for operational timer in host\;Re-lock recoveryon GET operation, returns watchdog value requested" access="RO" offset="0x20.24" size="0x0.8" />
	<field name="recovery_rx_algo_time" descr="Duration in ms of Rx algorithm phase (t2 to t3) during UPHY SerDes FEQ\;recovery. Passed to the SerDes recovery API as part of the recovery\;sequence. Controls how long the Rx re-equalization algorithm is allowed\;to run per recovery attempt.0 - FW default" access="RW" offset="0x24.0" size="0x0.8" />
	<field name="recovery_tx_toggle_time" descr="Duration in ms of Tx toggle phase (t1 to t2) during UPHY Tx+Rx recovery.\;Defines how long the Tx signal is toggled before Rx algorithm starts.\;Valid only when Tx recovery is agreed.0: FW default" access="RW" offset="0x24.8" size="0x0.8" />
	<field name="recovery_tx_toggle_delay" descr="Time in ms from recovery entry trigger (t0) to start of Tx toggle (t1)\;during UPHY Tx+Rx recovery. Valid only when Tx recovery is agreed\;(recovery_tx_re_iter_agreed).0: FW default" access="RW" offset="0x24.16" size="0x0.8" />
	<field name="recovery_tx_re_iter" descr="Controls whether Tx toggle is included in second and subsequent UPHY\;recovery iteration cycles.0: FW default / unkown1: No Tx toggle from second iteration onwards (Rx-only recovery for\;iterations 2+)2: Include Tx toggle in second iteration onwards (full Tx+Rx recovery\;for all cycles)" access="RW" offset="0x24.24" size="0x0.2" />
	<field name="recovery_rx_algo_time_oper" descr="operational status of recovery_rx_algo_time after negotiation agreement.\;value of 0 before negotiation or linkup." access="RO" offset="0x28.0" size="0x0.8" />
	<field name="recovery_tx_toggle_time_oper" descr="operational status of recovery_tx_toggle_time after negotiation\;agreement. value of 0 before negotiation or linkup." access="RO" offset="0x28.8" size="0x0.8" />
	<field name="recovery_tx_toggle_delay_oper" descr="operational status of recovery_tx_toggle_delay after negotiation\;agreement. value of 0 before negotiation or linkup." access="RO" offset="0x28.16" size="0x0.8" />
	<field name="recovery_tx_re_iter_oper" descr="operational status of recovery_tx_re_iter after negotiation agreement.\;value of 0 before negotiation or linkup." access="RO" offset="0x28.24" size="0x0.2" />
	<field name="param_page_data" descr="recovery parameters for read / write functionalitysee\;PPRM phy recovery steps paramssee\;PPRM Phy Recovery Steps Params Extended Page" subnode="pprm_reg_param_page_data_auto_ext" access="RW" offset="0x2c.0" size="0x68.0" union_selector="$(parent).param_select" />
</node>

<node name="pprm_reg_param_page_data_auto_ext" descr="" attr_is_union="1" size="0x68.0" >
	<field name="pprm_phy_steps_ext" descr="" subnode="pprm_phy_steps_ext" access="RW" offset="0x0.0" selected_by="phy_recovery_steps" size="0x68.0" />
	<field name="pprm_phy_steps_extended_ext" descr="" subnode="pprm_phy_steps_extended_ext" access="RW" offset="0x0.0" selected_by="phy_recovery_steps_extended" size="0x68.0" />
</node>

<node name="pprt_reg_ext" descr="" attr_required_tlvs="index:s" size="0x24.0" >
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):0 - No per lane configuration1 - Per lane configurationsWhen le is cleared, lane index is reserved and all PPRT configurations\;are taking place on all lanes.When le is set, configurations are taking place per lane based on lane\;index" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support:0 - No support of per lane configuration1 - Support of per lane configuration" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="port_type" descr="Supported only when indicated by PCAM0 - Network Port1 - Near-End Port (For Retimer/Gearbox - Host side)2 - internal IC LR Port3 - Far-End Port (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Reserved when (le=0 or ls = 0)Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sw_c" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols supportif this bit is cleared - bit 25 (‘s’) is ignored" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="sw" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols0 - No Swap.1 - Swap MSB &lt;-&gt; LSB." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dm_ig" descr="disable mask ignoreIf set to 1, the port’s and the cable’s capabilities won’t affect tuning" access="OP" offset="0x0.26" size="0x0.1" />
	<field name="p_c" descr="PRBS RX polarity support indicationif this bit is cleared - bit 28 (‘p’) is ignored" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="p" descr="PRBS RX polarity - NOT gate in PRBS (not Physical lane Polarity)0 - No polarity inversion.1 - PRBS RX polarity inversion." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="s" descr="start tuning:1 - start RX_tuning based on PRBS patternNotes:assuming peer transmitting PRBS.cannot be set when prbs_rx_tuning_status = 1 (during tuning).3) In Mode B rates, it is not required to set this bit in the first\;initialization of test mode after PAOS was set to down. For any\;re-tuning after initialization it is required to set this bit." access="OP" offset="0x0.30" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:0 - PRBS RX is disabled.1 - PRBS RX is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)Bit 0 - PRBS31 (x^31 + x^28 + 1)Bit 1 - PRBS23A (x^23 + x^18 + 1)Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)Bit 5 - PRBS7 (x^7 + x^6 + 1)Bit 6 - PRBS11 (x^11 + x^9 + 1)Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)Bit 11 - PRBS9 (x^9 + x^5 + 1)Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)Bit 13 - Square_wave : Non error based tuneBit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)Bit 21- SSPRBit 22- SSPRQBit 23- LT frames (KR-startup frames)Bit 24 - PRBS15 - x^15 + x^14 + 1Bit 25 - PRBS28 - x^28 + x^25 + 1Bit 26 - Square wave3 (3ones, 3zeros)Bit 27 - Square wave13 (13ones, 13zeros)Bit 28 - Square wave30 (30ones, 30zeros)Bit 29 - PRBS58 (x^58+ x^39 + 1)Bit 30 - Default Pattern - Recommended for Mode B links for simplicity" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 13):0 - NRZ test pattern1 - PAM4 encoding 2 - PAM4 with precoding 3 - PAM4 without gray no precoding" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="otf_ch_cap" descr="When set, On the fly configuration change is supported.otherwise, change of any configuration requires PAOS toggle.Configurations that are supported when bit is set:SP ( PRBS polarity)SW (MSB &lt;-&gt; LSB swap)Prbs_mode_admin (pattern)msb_lsb_cntPh_p (physical polarity)Modulation (precoding, gray and modulation)prbs_hist_fec_intPrbs_hist_en" access="RO" offset="0x8.15" size="0x0.1" />
	<field name="primary_secondary_idx" descr="0: primary1: secondary" access="INDEX" enum="primary=0x0,secondary=0x1" offset="0x8.20" size="0x0.1" />
	<field name="mode_b_idx" descr="0: mode_a 1: mode_b 2: mode_b_loopback - must set this value when configuring a loopback\;with a mode B rate" access="INDEX" offset="0x8.22" size="0x0.2" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap:0x0 - PRBS31 (x^31 + x^28 + 1)0x1 - PRBS23A (x^23 + x^18 + 1)0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)0x5 - PRBS7 (x^7 + x^6 + 1)0x6 - PRBS11 (x^11 + x^9 + 1)0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)0xB - PRBS9 (x^9 + x^5 + 1)0xC - IDLEs using scramble58 (x^58+ x^39 + 1)0xD - Square_wave : Non error based tune0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)0x15 - SSPR0x16 - SSPRQ0x17 - LT frames (KR-startup frames)0x18 - PRBS15 - x^15 + x^14 + 10x19 - PRBS28 - x^28 + x^25 + 10x1A - Square wave3 (3ones, 3zeros)0x1B - Square wave13 (13ones, 13zeros)0x1C - Square wave30 (30ones, 30zeros)0x1D - PRBS58 (x^58+ x^39 + 1)0x1E - Default Pattern - Recommended for Mode B links for simplicity" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="enc_mode_index" descr="Encoding mode for selecting the PRBS table.0x0: Default/legacy table which is the result of And between the NRZ and\;the PAM4 PRBS tables0x1: Use the NRZ table0x2: Use the PAM4 table" access="INDEX" offset="0xc.13" size="0x0.3" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)Bit 0 - 1GE (1.25 Gb/s) / Gen 1 PCIe (2.5 Gb/s)Bit 1 - SDR (2.5 Gb/s) / Gen 2 PCIe (5 Gb/s)Bit 2 - XAUI/2.5GE (3.125 Gb/s) / Gen 3 PCIe (8 Gb/s)Bit 3- DDR (5 Gb/s) / Gen 4 PCIe (16 Gb/s)Bit 4- QDR (10 Gb/s) / Gen 5 PCIe (32 Gb/s)Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) / Gen 5 PCIe (64 Gb/s PAM4,\;32Gbd)Bit 6- FDR (14.0625 Gb/s)Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)Bit 8 - 50GE-KR4 (12.89 Gb/s)Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s)Bit 10 - NDR / 100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)Bit 11 - XDR / 200G_1x_mode_a (106.25 Gbd / 212.5 Gb/s)Bit 12 - 180G_Mode_B (90 Gbd\;/ 180 Gb/s)Bit 13 - 200G_Mode_B (100 Gbd / 200 Gb/s)Bit 14 - 164G_Mode_B (82 Gbd / 164 Gb/s)Bit 15 - 189G_Mode_B (94.5 Gbd / 189 Gb/s)Note: PCIe speeds are relevant when pnat = 3 only" access="RO" offset="0xc.16" size="0x0.16" />
	<field name="lane_rate_oper" descr="Lane rate to be used in PRBS, see lane_rate_cap:0 - SDR (2.5 Gb/s) / Gen 1 PCIe (2.5 Gb/s)1 - DDR (5 Gb/s) / Gen 2 PCIe (5 Gb/s)2 - QDR (10 Gb/s)3 - FDR10 / 10GE/4 0GE (10.3125 Gb/s) / Gen 3 PCIe (8 Gb/s)4 - FDR (14.0625 Gb/s) / Gen 4 PCIe (16 Gb/s)5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) / Gen 5 PCIe (32 Gb/s)6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s / Gen 5\;PCIe (64 Gb/s PAM4, 32Gbd)7 - NDR /100GE\;/ 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)8 - XDR / 200G_1x_mode_a (106.25 Gbd / 212.5\;Gb/s)9 - 180G_Mode_B (90 Gbd /\;180 Gb/s10 - 1GE (1.25 Gb/s)11 - XAUI/2.5GE (3.125 Gb/s)12 - 50GE-KR4 (12.89 Gb/s)13 – 200G_Mode_B (100 Gbd / 200 Gb/s)14 – 164G_Mode_B (82 Gbd / 164 Gb/s)15 - 189G_Mode_B (94.5 Gbd / 189 Gb/s)16 - 172p5G_Mode_B (86.25 Gbd / 172.5 Gb/s)17 - 187G_Mode_A (93.5 Gbd / 187 Gb/s)18 - 176G_Mode_A (88 Gbd / 176 Gb/s)19 - 169G_Mode_A (84.5 Gbd / 169 Gb/s)Note: All lanes must be set to the same rate.Note: PCIe speeds are relevant when pnat = 3 only" access="RW" offset="0x10.16" size="0x0.16" />
	<field name="prbs_lock_status_ext" descr="PRBS lock on PRBS pattern status for lanes 7-4:0 - Not locked1 - LockedNote: Once exiting prbs test mode the prbs_rx_tuning_status will return\;to 0 (Not locked)" access="RO" offset="0x14.20" size="0x0.4" />
	<field name="prbs_lock_status" descr="PRBS lock on PRBS pattern status for lanes 3-0:0 - Not locked1 - LockedNote: Once exiting prbs test mode the prbs_rx_tuning_status will return\;to 0 (Not locked)" access="RO" offset="0x14.24" size="0x0.4" />
	<field name="prbs_rx_tuning_status" descr="Tuning status:0 - PRBS mode tuning was not performed.1 - Performing PRBS mode tuning.2 - PRBS mode tuning completed.3 - Signal Detect in progress4 - Secondary not detected - this could occur in test mode configured\;with a Mode B rate if the primary device is configured prior to the\;secondaryNote: Once exiting prbs test mode the prbs_rx_tuning_status will return\;to 0." access="RO" offset="0x14.28" size="0x0.4" />
	<field name="lane_rate_cap_ext" descr="An extension for the lane_rate_cap field, providing additional per lane\;rate capability (bitmask)Bit 0 - 172p5G_Mode_B (86.25 Gbd / 172.5 Gb/s)Bit 1 - 187G_Mode_A (93.5 Gbd / 187 Gb/s)Bit 2 - 176G_Mode_A (88 Gbd / 176 Gb/s)Bit 3 - 169G_Mode_A (84.5 Gbd / 169 Gb/s)Note: PCIe speeds are relevant when pnat = 3 only." access="RO" offset="0x20.13" size="0x0.15" />
</node>

<node name="ppsc_reg_ext" descr="" attr_required_tlvs="index:s" size="0x30.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mod_pwr_opt" descr="See PCAM.feature_cap_mask bit 16 for support indication:Transceiver power optimization:0 - Disable1 - Enable" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="wrps_admin" descr="Width reduction power save admin state:0000: Disable Width Reduction - Force link to full width (Default)0001: Force Width Reduction - Force link to single lane0010: Auto - Automatic Width Reduction (based on traffic)." access="RW" offset="0x10.0" size="0x0.4" />
	<field name="wrps_status" descr="Link actual width:0000: Full width0001: Single lane1111: In transition" access="RO" offset="0x14.0" size="0x0.4" />
	<field name="down_threshold" descr="Link width down threshold, Values: 1%-100%The BW (In percent) before the link width is moved to single lane" access="RW" offset="0x18.0" size="0x0.8" />
	<field name="up_threshold" descr="Link width up threshold, Values: 1-5 (default 3)how aggressive/smoothed in response to high BW.1 – means aggressive response to every BW increase5 – means smoothened response to every BW increase" access="RW" offset="0x18.16" size="0x0.8" />
	<field name="down_th_vld" descr="Valid bit to update the down thresholdif ‘1’ update down_threshold" access="WO" offset="0x18.30" size="0x0.1" />
	<field name="up_th_vld" descr="Valid bit to update the up thresholdif ‘1’ update up_threshold" access="WO" offset="0x18.31" size="0x0.1" />
	<field name="srps_admin" descr="Speed reduction power save admin state:0000: Disable Speed Reduction - force link to full speed (Default)0001: Force Speed Reduction - force link to low speed" access="RW" offset="0x20.0" size="0x0.4" />
</node>

<node name="ppslc_ext" descr="" attr_required_tlvs="index:s" size="0x34.0" >
	<field name="l1_cap" descr="[SWITCH][DWIP]L1 Capability.0: Device does not support L1.1: Device supports L1." access="RO" offset="0x0.0" size="0x0.1" />
	<field name="l1_admin" descr="[SWITCH][DWIP]L1 Admin.0: Auto, keep normal operation.1: Enable L1.2: Disable L1.Note: The setting will be applied to current port on the next link-up\;event." access="RW" offset="0x0.1" size="0x0.2" />
	<field name="l1_oper" descr="[SWITCH][DWIP]L1 Operation.0: Current port and peer port did not agree on L1 activation.1: Current port and peer port agreed on L1 activation." access="RO" offset="0x0.3" size="0x0.1" />
	<field name="l0i_cap" descr="[SWITCH][DWIP]L0-Idle Capability.0: Device does not support L0-Idle.1: Device supports L0-Idle." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="l0i_admin" descr="[SWITCH][DWIP]L0-Idle Admin.0: Auto, keep normal operation.1: Enable L0-Idle.2: Disable L0-Idle.Note: The setting will be applied to current port on the next link-up\;event." access="RW" offset="0x0.5" size="0x0.2" />
	<field name="l0i_oper" descr="[SWITCH][DWIP]L0-Idle Operation.0: Current port and peer port did not agree on L0-Idle activation.1: Current port and peer port agreed on L0-Idle activation." access="RO" offset="0x0.7" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="l1_consider_rx_traffic" descr="[DWIP]:0: For L1, don’t consider Rx traffic for idleness (backwards-compatible\;value).1: For L1, consider Rx traffic for idlenessSPC: Supported starting from SPC6.QM: Supported starting from QM5.GPU: Supported starting from Feynman." access="INDEX" offset="0x0.30" size="0x0.1" />
	<field name="l0i_consider_rx_traffic" descr="[DWIP]:0: For L0-idle, don’t consider Rx traffic for idleness\;(backwards-compatible value).1: For L0-idle, consider Rx traffic for idlenessSPC: Supported starting from SPC6.QM: Supported starting from QM5.GPU: Supported starting from Feynman." access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="l1_req_en" descr="Enable L1 Request0: L1 Request is disabled on this port1: L1 Request is enabled on this port" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="l1_fw_req_en" descr="Enable L1 FW Request0: Only L1 HW mode is supported (thermal throttling is disabled)\;1: support thermal throttling on this port\;Reserved for Switch." access="RW" offset="0x8.0" size="0x0.1" />
	<field name="l1_cap_adv" descr="L1 Capability Advertisement0: Port doesn’t support L11: Port supports L1 advertisement" access="RW" offset="0x8.4" size="0x0.1" />
	<field name="l1_tmp_dis" descr="[DWIP]:L1 Temporary Disable0: L1 is not temporary disabled on this port1: L1 is temporary disabled on this portWhen L1 has been negotiated successfully, this field can be used to\;temporarily disable L1 and later re-enable it for various purposes,\;without requiring a link toggle in order to take effect." access="RW" offset="0x8.5" size="0x0.1" />
	<field name="l1_fw_cap_adv" descr="L1 FW Capability Advertisement0: Port doesn’t support L1 FW1: Port supports L1 FW advertisementReserved for Switch." access="RW" offset="0x8.8" size="0x0.1" />
	<field name="l0i_rx_cap_adv" descr="[DWIP]:Rx L0-Idle Capability Advertisement0: Port Rx lane doesn’t support L0-Idle.1: Port Rx lane supports L0-Idle.Note: Mirrors value of field l0i_tx_cap_adv.GPU: Supported starting GR100.Quantum: Supported starting QM4.Spectrum: Supported starting SPC6." access="RO" offset="0x8.16" size="0x0.1" />
	<field name="l0i_rx_req_en" descr="[DWIP]:Rx Enable L0-Idle Request0: Port Rx lane doesn’t support L0-Idle.1: Port Rx lane supports L0-Idle.Note: Mirrors value of field l0i_tx_cap_adv.GPU: Supported starting GR100.Quantum: Supported starting QM4.Spectrum: Supported starting SPC6." access="RO" offset="0x8.17" size="0x0.1" />
	<field name="l0i_tx_cap_adv" descr="[DWIP]:Tx L0-Idle Capability Advertisement0: Port Tx lane doesn’t support L0-Idle.1: Port Tx lane supports L0-Idle.GPU: Supported starting GR100.Quantum: Supported starting QM4.Spectrum: Supported starting SPC6." access="RW" offset="0x8.18" size="0x0.1" />
	<field name="l0i_tx_req_en" descr="[DWIP]:Tx Enable L0-Idle Request0: Port Tx lane doesn’t support L0-Idle.1: Port Tx lane supports L0-Idle.Note: Mirrors value of field l0i_tx_cap_adv.GPU: Supported starting Rubin.Quantum: Supported starting QM4.Spectrum: Supported starting SPC6." access="RO" offset="0x8.19" size="0x0.1" />
	<field name="l0i_all_queues_are_import" descr="[DWIP]If set, L0 controller (HW) requires all queues to be empty before moving\;to L0-Idle state. Per port parameter.GPU: Supported starting GR100.Quantum: Supported starting QM4.Spectrum: Supported starting SPC6." access="RW" offset="0x8.20" size="0x0.1" />
	<field name="l0i_tx_tmp_dis" descr="[DWIP]:L0-Idle Temporary Disable for Tx lane0: L0-Idle is not temporary disabled on this port’s Tx lane1: L0-Idle is temporary disabled on this port’s Tx laneWhen l0i has been negotiated successfully on Tx lane, this field can be\;used to temporarily disable L0-Idle on Tx lane, and later re-enable it\;for various purposes, without requiring a link toggle in order to take\;effect.GPU: Supported starting GR100.Quantum: Supported starting QM4.Spectrum: Supported starting SPC6." access="RW" offset="0x8.21" size="0x0.1" />
	<field name="ignore_pred_pm" descr="[DWIP] [SwitchOnly]:Ignore Predictor Post MistakeIf the predictor decision is to move to L1 idle, but no traffic arrives,\;we will ignore the predictor until traffic arrives again0: don’t ignore predictor1: ignore predictor" access="RW" offset="0xc.30" size="0x0.1" />
	<field name="pred_algo_en" descr="[DWIP] [SwitchOnly]:Predictive Algo Enable0: Predictive Algo’ is disabled1: Predictive Algo’ is enabledRelevant for Switch Only" access="RW" offset="0xc.31" size="0x0.1" />
	<field name="hp_queues_bitmap" descr="High Priority Queues Bitmapfor each queue,0: Normal queue1: High priority queueNote: High priority queues can move to L1 active only when queue is\;fully empty. Normal queues can move to L1 active as long as the number\;of bytes within the queue is lower than MPSCR.queue_depth_thbits 17-31 are reserved" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="l1_hw_active_time" descr="units of 50 usec minimum value of 50 usec" access="RW" offset="0x18.0" size="0x0.10" />
	<field name="l0i_hw_inactive_time_admin" descr="[DWIP][Switch]0: L0-idle HW inactive time setting NOT controlled or reflected through\;this field.Any other value: L0-idle HW inactive time setting controlled and\;reflected through this field.Units:QM4: 64 nsec.QM5: 10 usec.All other products: 50 nsec.Applying a change in this value will require link toggle.Valid starting QM4.Default field value: 0" access="RW" offset="0x18.16" size="0x0.10" />
	<field name="l1_hw_inactive_time" descr="units of 50 usec. minimum value of 50 usec" access="RW" offset="0x1c.0" size="0x0.10" />
	<field name="l0i_hw_inactive_time" descr="[DWIP]Note for QM NVOS: Do not use this field for writes. Instead use field\;l0i_hw_inactive_time_admin.Units:QM4: 64 nsec.QM5: 10 usec.All other products: 50 nsec.Valid only for GR100, QM-4, SPC-6 and aboveApplying a change in this value will require link toggle." access="RW" offset="0x1c.16" size="0x0.10" />
	<field name="qem" descr="Queue Desire (state) Exit Mode upon traffic arrival0: Move to L1 Idle immediately1: Wait for desire window completion before moving to L1 idle2: Ignore traffic arrival Note:For GB1xx and GR1xx, only index 0-7 are valid.For Quantum-3 and Quantum-4, only index 0-16 are valid.Must be 0 for queues defined in hp_queues_bitmap as high priority." access="RW" high_bound="19" low_bound="0" offset="0x20.24" size="0x14.0" />
</node>

<node name="ppsld_ext" descr="" attr_required_tlvs="index:s" size="0x14.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fw_mode" descr="FW Mode0: Trigger Once - 1: Infinite L1 Idle 2: Infinite L1 Desire 3: Toggle Always 4: Disabled 5: Infinite L0 Force 6: Infinite L1 Force Note: can be changed only when device in not under thermal event. During\;thermal event, FW will override the use debug configuration." access="RW" offset="0x4.0" size="0x0.3" />
	<field name="trigger" descr="Trigger port to move to force mode one time0: No trigger1: Trigger port to move to force modeValid only when fw_mode = Trigger Once" access="OP" offset="0x8.0" size="0x0.1" />
	<field name="ehld" descr="Exposed HW L1 desireThe state of the controller2plu_l1_desire bit that controller publishes" access="RO" offset="0xc.0" size="0x0.2" />
	<field name="fw_idle_window_time" descr="FW Idle Window timeunits of 100uSecRelevant only for fw_mode = Toggle always (3)." access="RW" offset="0x10.0" size="0x0.8" />
	<field name="fw_desire_window_time" descr="FW Desire Window timeunits of 100uSecRelevant only for fw_mode = Trigger once (0) or Toggle always (3)." access="RW" offset="0x10.16" size="0x0.8" />
</node>

<node name="ppsls_ext" descr="" attr_required_tlvs="index:s" size="0x8.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="l1_fw_mode_cap" descr="0: Port doesn’t support L1 fw mode1: Port supports L1 fw mode" access="RO" offset="0x4.16" size="0x0.1" />
	<field name="l1_cap" descr="0: Port doesn’t support L11: Port supports L1" access="RO" offset="0x4.18" size="0x0.1" />
	<field name="l0i_neg_rx_status" descr="[DWIP]L0-Idle RX lane negotiation status0: L0-Idle RX lane negotiation failed (L1 is not supported by both\;sides)1: L0-Idle RX lane negotiation succeeded (supported on both sides)N/A when link is down" access="RO" offset="0x4.19" size="0x0.1" />
	<field name="l0i_neg_tx_status" descr="[DWIP]L0-Idle TX lane negotiation status0: L0-Idle TX lane negotiation failed (L1 is not supported by both\;sides)1: L0-Idle TX lane negotiation succeeded (supported on both sides)N/A when link is down" access="RO" offset="0x4.20" size="0x0.1" />
	<field name="fw_mode_remote" descr="FW mode remote indication0: N/A1: L1 fw mode remote capability is set2: L1 fw mode remote request is set3: L1 fw mode remote request and capability are setValid only is l1_neg_status = 1Reserved when link is down" access="RO" offset="0x4.27" size="0x0.2" />
	<field name="fw_mode_act" descr="Actual Mode0: HW mode1: FW modeValid only is l1_neg_status = 1Reserved when link is downReserved for Switch." access="RO" offset="0x4.29" size="0x0.1" />
	<field name="fw_mode_neg_status" descr="FW mode negotiation status0: L1 fw mode negotiation failed1: L1 fw mode negotiation succeeded Valid only if l1_neg_status = 1Reserved when link is down" access="RO" offset="0x4.30" size="0x0.1" />
	<field name="l1_neg_status" descr="L1 negotiation status0: L1 negotiation failed (L1 is not supported by both sides)1: L1 negotiation succeeded (supported on both sides)Reserved when link is down" access="RO" offset="0x4.31" size="0x0.1" />
</node>

<node name="pptb_reg_ext" descr="" size="0xc.0" >
	<field name="pm" descr="prioX_buff mask - enables update of the prioX_buff field.Bit i is a flag for updating the mapping for switch priority i." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="um" descr="untagged_buff mask - enables update of the untagged_buff field.Reserved for Spectrum family.Reserved for HCA devices." access="WO" offset="0x0.8" size="0x0.1" />
	<field name="cm" descr="ctrl_buff mask - enables update of the ctrl_buff field.NOTE: This field is ignored by the device, and control traffic is mapped\;to a pre-defined buffer (buffer - 9).Reserved for HCA devices" access="WO" offset="0x0.9" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mm" descr="Mapping mode0: Mapping both Unicast and Multicast packets to the same bufferIn get operation, 0 means Unicast only.1: Mapping Unicast only2: Mapping Multicast onlyThis field is reserved for HCA devices" access="INDEX" offset="0x0.28" size="0x0.2" />
	<field name="prio0buff" descr="(see above)" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="prio1buff" descr="(see above)" access="RW" offset="0x4.4" size="0x0.4" />
	<field name="prio2buff" descr="(see above)" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="prio3buff" descr="(see above)" access="RW" offset="0x4.12" size="0x0.4" />
	<field name="prio4buff" descr="(see above)" access="RW" offset="0x4.16" size="0x0.4" />
	<field name="prio5buff" descr="(see above)" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="prio6buff" descr="(see above)" access="RW" offset="0x4.24" size="0x0.4" />
	<field name="prio7buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port\;buffers.&lt;X&gt; = 0..7" access="RW" offset="0x4.28" size="0x0.4" />
	<field name="untagged_buff" descr="Mapping of untagged frames to one of the allocated receive port buffers.Reserved for Spectrum. Spectrum maps untagged packets based on the\;Switch Priority.Reserved for HCA devices" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="ctrl_buff" descr="Mapping of control frames to one of the allocated receive port buffers.NOTE: This field is ignored by the device, and control traffic is mapped\;to a pre-defined buffer (buffer - 9).Reserved for HCA devices" access="RW" offset="0x8.4" size="0x0.4" />
	<field name="pm_msb" descr="prioX_buff mask - enables update of the prioX_buff field.Bit i is a flag for updating the mapping for switch priority i+8.Reserved for HCA device" access="WO" offset="0x8.24" size="0x0.8" />
</node>

<node name="pptt_reg_ext" descr="" attr_required_tlvs="index:s" size="0x1c.0" >
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):0 - No per lane configuration1 - Per lane configurationsWhen le is cleared, lane index is reserved and all PPTT configurations\;are taking place on all lanes.When le is set, configurations are taking place per lane based on lane\;index" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support/capability:0 - No support of per lane configuration1 - Support of per lane configuration" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0 - Network Port1 - Near-End Port (For Retimer/Gearbox - Host side)2 - internal IC LR Port3 - Far-End Port (For Retimer/Gearbox - Line side)Other values are reserved.Note: PRBS can be enabled only for two entities that directly connected\;to each other.For non MCM and no Retimer/Gearbox only 0 allowed.For non MCM and with Retimer/Gearbox 2-1 or 3 or 0.For MCM without Retimer/Gearbox  2 or 0.For MCM with Retimer/Gearbox  2-1 or 3 or 0.all the port will be in test mode when PRBS is enabled." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Reserved when (le=0 or ls = 0)Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sw_c" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols supportif this bit is cleared - bit 25 (‘s’) is ignored" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="sw" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols0 - No Swap.1 - Swap MSB &lt;-&gt; LSB." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dm_ig" descr="disable mask ignoreIf set to 1, the port’s and the cable’s capabilities won’t affect tuning" access="OP" offset="0x0.26" size="0x0.1" />
	<field name="p_c" descr="PRBS TX polarity support indication.if this bit is cleared - bit 28 (‘p’) is been ignored" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="p" descr="PRBS TX polarity - NOT gate in PRBS (not Physical lane Polarity)0 - No polarity inversion.1 - PRBS TX polarity inversion." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:0 - PRBS TX is disabled.1 - PRBS TX is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)Bit 0 - PRBS31 (x^31 + x^28 + 1)Bit 1 - PRBS23A (x^23 + x^18 + 1)Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)Bit 5 - PRBS7 (x^7 + x^6 + 1)Bit 6 - PRBS11 (x^11 + x^9 + 1)Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)Bit 11 - PRBS9 (x^9 + x^5 + 1)Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)Bit 13 - Square_wave8 (8 ones, 8 zeros)Bit 14 - Square_wave4 (4 ones, 4zeros)Bit 15 - Square_wave2 (2 ones, 2zeros)Bit 16 - Square_wave1 (one, zero)Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)Bit 21- SSPRBit 22- SSPRQBit 23- LT frames (KR-startup frames)Bit 24 - PRBS15 - x^15 + x^14 + 1Bit 25 - PRBS28 - x^28 + x^25 + 1Bit 26 - Square wave3 (3ones, 3zeros)Bit 27 - Square wave13 (13ones, 13zeros)Bit 28 - Square wave30 (30ones, 30zeros)Bit 29 - PRBS58 (x^58+ x^39 + 1)Bit 30 - Default Pattern - Recommended for Mode B links for simplicity" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 13):0 - NRZ test pattern1 - PAM4 encoding 2 - PAM4 with precoding3 - PAM4 without gray no precoding" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="otf_ch_cap" descr="When set, On the fly configuration change is supported.otherwise, change of any configuration requires PAOS toggle.Configurations that are supported when bit is set:P ( PRBS polarity)SW (MSB &lt;-&gt; LSB swap)Prbs_mode_admin (PRBS pattern)msb_lsb_cntPh_p (physical polarity)Modulation (precoding, gray and modulation)" access="RO" offset="0x8.15" size="0x0.1" />
	<field name="enc_mode_index" descr="Encoding mode for selecting the PRBS table.0x0: Default/legacy table which is the result of And between the NRZ and\;the PAM4 PRBS tables0x1: Use the NRZ table0x2: Use the PAM4 table" access="INDEX" offset="0x8.16" size="0x0.3" />
	<field name="primary_secondary_idx" descr="0: primary1: secondary" access="INDEX" enum="primary=0x0,secondary=0x1" offset="0x8.20" size="0x0.1" />
	<field name="mode_b_idx" descr="0: mode_a 1: mode_b 2: mode_b_loopback - must set this value when configuring a loopback\;with a Mode B rate" access="INDEX" enum="mode_a=0x0,mode_b=0x1,mode_b_loopback=0x2" offset="0x8.22" size="0x0.2" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap:0x0 - PRBS31 (x^31 + x^28 + 1)0x1 - PRBS23A (x^23 + x^18 + 1)0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)0x5 - PRBS7 (x^7 + x^6 + 1)0x6 - PRBS11 (x^11 + x^9 + 1)0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)0xB - PRBS9 (x^9 + x^5 + 1)0xC - IDLEs using scramble58 (x^58+ x^39 + 1)0xD - Square_wave8 (8 ones, 8 zeros)0xE - Square_wave4 (4 ones, 4zeros)0xF - Square_wave2 (2 ones, 2zeros)0x10 - Square_wave1 (one, zero)0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)0x15 - SSPR0x16 - SSPRQ0x17 - LT frames (KR-startup frames)0x18 - PRBS15 - x^15 + x^14 + 10x19 - PRBS28 - x^28 + x^25 + 10x1A - Square wave3 (3ones, 3zeros)0x1B - Square wave13 (13ones, 13zeros)0x1C - Square wave30 (30ones, 30zeros)0x1D - PRBS58 (x^58+ x^39 + 1)0x1E - Default Pattern - Recommended for Mode B links for simplicity" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lane_rate_cap_ext" descr="An extension for the lane_rate_cap field, providing additional per lane\;rate capability (bitmask)Bit 0 - 172p5G_Mode_B (86.25 Gbd / 172.5 Gb/s)Bit 1 - 187G_Mode_A (93.5 Gbd / 187 Gb/s)Bit 2 - 176G_Mode_A (88 Gbd / 176 Gb/s)Bit 3 - 169G_Mode_A (84.5 Gbd / 169 Gb/s)Note: PCIe speeds are relevant when pnat = 3 only" access="RO" offset="0xc.1" size="0x0.15" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)Bit 0 - 1GE (1.25 Gb/s) / Gen 1 PCIe (2.5 Gb/s)Bit 1 - SDR (2.5 Gb/s) / Gen 2 PCIe (5 Gb/s)Bit 2 - XAUI/2.5GE (3.125 Gb/s) / Gen 3 PCIe (8 Gb/s)Bit 3- DDR (5 Gb/s) / Gen 4 PCIe (16 Gb/s)Bit 4- QDR (10 Gb/s) / Gen 5 PCIe (32 Gb/s)Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) / Gen 5 PCIe (64 Gb/s PAM4,\;32Gbd)Bit 6- FDR (14.0625 Gb/s)Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)Bit 8 - 50GE-KR4 (12.89 Gb/s)Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s)Bit 10 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)Bit 11 - XDR / 200G (106.25Gbd / 212.5Gb/s)Bit 12 - 180G_Mode_B (90 Gbd / 180 Gb/s)Bit 13 - 200G_Mode_B (100 Gbd / 200 Gb/s)Bit 14 - 164G_Mode_B (82 Gbd / 164 Gb/s)Bit 15 - 189G_Mode_B (94.5 Gbd / 189 Gb/s)Note: PCIe speeds are relevant when pnat = 3 only" access="RO" offset="0xc.16" size="0x0.16" />
	<field name="lane_rate_admin" descr="Lane rate be used in PRBS, see lane_rate_cap:0 - SDR (2.5 Gb/s) / Gen 1 PCIe (2.5 Gb/s)1 - DDR (5 Gb/s) / Gen 2 PCIe (5 Gb/s)2 - QDR (10 Gb/s)3 - FDR10 / 10GE/4 0GE (10.3125 Gb/s) / Gen 3 PCIe (8 Gb/s)4 - FDR (14.0625 Gb/s) / Gen 4 PCIe (16 Gb/s)5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) / Gen 5 PCIe (32 Gb/s)6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s / Gen 5\;PCIe (64 Gb/s PAM4, 32Gbd)7 - NDR /100GE\;/ 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)8 - XDR / 200G (106.25Gbd / 212.5Gb/s)9 - 180G_Mode_B (90 Gbd / 180 Gb/s)10 - 1GE (1.25 Gb/s)11 - XAUI/2.5GE (3.125 Gb/s)12 - 50GE-KR4 (12.89 Gb/s)13 – 200G_Mode_B (100 Gbd / 200 Gb/s)14 – 164G_Mode_B (82 Gbd / 164 Gb/s)15 - 189G_Mode_B (94.5 Gbd / 189 Gb/s)16 - 172p5G_Mode_B (86.25 Gbd / 172.5 Gb/s)17 - 187G_Mode_A (93.5 Gbd / 187 Gb/s)18 - 176G_Mode_A (88 Gbd / 176 Gb/s)19 - 169G_Mode_A (84.5 Gbd / 169 Gb/s)Note: All lanes must be set to the same rateNote: PCIe speeds are relevant when pnat = 3 only" access="RW" offset="0x10.16" size="0x0.16" />
</node>

<node name="ppwcc_ext" descr="" size="0x20.0" >
	<field name="profile_index" descr="Profile Index.Range 0…cap_num_pfc_wd_profiles-1" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="polling_interval" descr="Polling Interval for PFC WD.Every polling_interval, the configured criteria will be checked.Units of 100uSec.Spectrum-4,5: granularity is 10mSecSpectrum-6,7 granularity is 100uSec.Min values defined in the table in the PPWCC description.note - all profiles that are enabled must hold the minimum polling\;interval described in the table.max value = 500mSecWhen polling interval=0, profile is disabled." access="RW" offset="0x0.16" size="0x0.16" />
	<field name="cnt_bitmask" descr="Counters Bitmask.every counter that is set, will be checked against its threshold.bit0: rx pause duration (described in PPCNT.per_priority_counters)bit1: tx_frame (described in PPCNT.per_priority_counters), counter index\;according to QGCR.bit2: transmit_queue (described in PPCNT.Traffic_class)bit3: tx_octets (described in PPCNT.per_priority_counters)If counter is not set in the bitmask, it’s threshold is reserved.tx_frame (bit 1) and tx_octets (bit 3) cannot be used simultaneously\;(global for the chip and not only per profile)." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="detect_num" descr="Detect Interval Number.Range 1…15Defines the number of consecutive polling interval that the criteria\;match before notifying the port is in storm." access="RW" offset="0x4.16" size="0x0.4" />
	<field name="pause_dura_thr" descr="Pause Duration Threshold.Used in the equation in the description of the register.Units of 1uSec." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="tx_frame_thr" descr="Tx Frame Threshold.Used in the equation in the description of the register.Units of packets." access="RW" offset="0x14.0" size="0x0.4" />
	<field name="transmit_queue_thr" descr="Transmit Queue Threshold.Used in the equation in the description of the register.Units of Cells." access="RW" offset="0x18.0" size="0x4.0" />
	<field name="tx_octets_thr" descr="Tx Octets Threshold.Used in the equation in the description of the register.Units of Bytes." access="RW" offset="0x1c.0" size="0x0.4" />
</node>

<node name="ppwdc_ext" descr="" size="0xc.0" >
	<field name="profile_index" descr="Profile Index.Range 0…cap_num_pfc_wd_profiles-1" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="clr" descr="When set counter is cleared." access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="num_detections" descr="Number of detections.detection means that port.tc is in storm. if multiple TCs on the same\;port, it is counted as multiple detections.This counter will not wrap around - stop at 0xFFFF_FFFF" access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="ppwe_ext" descr="" size="0xc.0" >
	<field name="num_rec" descr="Number of valid records.Each valid record describe a port and which tclasses in this ports are\;in storm condition.On write - filled by user.On query - filled by FW." access="RO" offset="0x0.0" size="0x0.12" />
	<field name="record" descr="PFC WD Record Layout" subnode="ppwpt_pfc_wd_record_ext" access="RW" high_bound="VARIABLE" low_bound="0" offset="0x8.0" size="0x4.0" />
</node>

<node name="ppwpt_ext" descr="" size="0x410.0" >
	<field name="profile_index" descr="Profile Index.Range 0…cap_num_pfc_wd_profiles-1" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="num_records" descr="Number of Records.Indicate the number of valid records in record[] arrayRange 1…256" access="RW" offset="0x4.0" size="0x0.9" />
	<field name="cmd" descr="Command.0: set - define which port,tc to monitor (overwrite current\;configuration). when port,tc=1 it will be monitored, when port,tc=0\;it will not be monitored.1: update - add selected port,tc to monitoring flow.2: clear - stop monitor selected port,tc.Reserved when method=query." access="OP" enum="set=0x0,update=0x1,clear=0x2" offset="0x4.16" size="0x0.2" />
	<field name="pfc_wd_record" descr="Record List.PFC WD Record LayoutOn write - User will provide local_port and it’s tc_bitmask per record.On query - not all ports can be reported in single query:User will provide the first local port to read it’s status in record[0].FW will write the next monitored local_port in record[1] and on\;(record[2], record[3]…record[256]).If in the response num_rec == 256, User will send another query while\;setting in record[0] the next port index that was reported in\;record[256] on the last response.When num_req &lt; 256, all the ports from the selected profile reported -\;query is done." subnode="ppwpt_pfc_wd_record_ext" access="RW" high_bound="255" low_bound="0" offset="0x10.0" size="0x400.0" />
</node>

<node name="ppwpt_pfc_wd_record_ext" descr="" size="0x4.0" >
	<field name="tc_bitmask" descr="Tclass Bitmask.On write - monitor/not_monitor according to cmd fieldOn read - return the status per port.tc (1 - monitored, 0 - not\;monitored)Control TC is not supported." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="local_port" descr="Local Port" access="RW" offset="0x0.16" size="0x0.16" />
</node>

<node name="prcct_ext" descr="" size="0x4.0" >
	<field name="local_port" descr="Local port number." access="RO" offset="0x0.0" size="0x0.16" />
</node>

<node name="prei_reg_28nm_ext" descr="" size="0x8.0" >
	<field name="mixer_offset1" descr="(see above)" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="mixer_offset0" descr="eye centering control.may cause link degradation when set." access="RW" offset="0x0.16" size="0x0.16" />
</node>

<node name="prei_reg_ext" descr="" attr_required_tlvs="index:s" size="0x18.0" >
	<field name="status" descr="Error injection status:0x0 -Good status0x2 - No available sources for Error injection0x3 - Error injection configuration when port is in non operational\;state (port is neither in UP or TEST MODE)" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="time_res" descr="0: 10ms" access="OP" offset="0x0.4" size="0x0.2" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type.0 - Local port number1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="1 - 28nm products3 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="lm_cap" descr="When set , lane_mask field is applicable" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="mps" descr="[DWIP]Multiple Port Set.Supported only if indicated in PMSCR.prm_support of PREI support,\;otherwise ignored.When set, local_port index is ignored and set command is given to all\;ports in mask given from PMSCR.local_port_mask field" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="error_type_admin" descr="Error Type to generate:0: No_Error —- Physical Errors —-Bit 0: mixer_offset_ctrl_setBit 5: serdes_rx_reset" access="RW" enum="mixer_offset_ctrl_set=0x1,serdes_rx_reset=0x20" offset="0x4.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilities:Bit 0: mixer_offset_ctrlBit 5: serdes_rx_reset" access="RO" enum="mixer_offset_ctrl=0x1,serdes_rx_reset=0x20" offset="0x4.8" size="0x0.8" />
	<field name="error_type_oper" descr="Error injection operational status:0x0 - No error injection0x1 - Performing error injection" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="lane_mask" descr="Valid only if lm_cap is set, otherwise ignoredSets the specific lanes to be applied from the error_type_admin that was\;selected.Relevant for error types that can be per lane: rx_reset.Bitmask per lane." access="RW" offset="0x8.0" size="0x0.8" />
	<field name="error_injection_time" descr="Duration in time_res the port will generate errors. Reading this field\;will return the time left for errors to inject in msec.0x0000 indicates no generation of errors.0xFFFF - No decremental operation, meaning the errors will be injected\;continuously without stop condition." access="RW" offset="0x8.12" size="0x0.16" />
	<field name="page_data" descr="PREI - Port Receive Error Injection Register Layout for 28nm" subnode="prei_reg_28nm_ext" access="RW" offset="0x10.0" size="0x8.0" />
</node>

<node name="prod_3nm_serdes_gen_7p5_ext" descr="" size="0x48.0" >
	<field name="ob_bad_stat" descr="Bitmask for bad ‘set’ status:Bit 0: tap0_is_out_of_rangeBit 1: tap1_is_out_of_rangeBit 2: tap2_is_out_of_rangeBit 3: tap3_is_out_of_rangeBit 4: tap4_is_out_of_rangeBit 5: tap5_is_out_of_rangeBit 6: tap6_is_out_of_rangeBit 7: tap7_is_out_of_rangeBit 8: tap8_is_out_of_rangeBit 9: tap9_is_out_of_rangeBit 10: tap10_is_out_of_rangeBit 11: tap11_is_out_of_rangeBit 12: sum_of_taps_is_out_of_range" access="RO" enum="tap0_is_out_of_range=0x1,tap1_is_out_of_range=0x2,tap2_is_out_of_range=0x4,tap3_is_out_of_range=0x8,tap4_is_out_of_range=0x10,tap5_is_out_of_range=0x20,tap6_is_out_of_range=0x40,tap7_is_out_of_range=0x80,tap8_is_out_of_range=0x100,tap9_is_out_of_range=0x200,tap10_is_out_of_range=0x400,tap11_is_out_of_range=0x800,sum_of_taps_is_out_of_range=0x1000" offset="0x0.0" size="0x0.16" />
	<field name="mode_b_idx" descr="0: mode_a 1: mode_b" access="RO" enum="mode_a=0x0,mode_b=0x1" offset="0x0.23" size="0x0.1" />
	<field name="lt_preset_sel" descr="Valid only when lt_preset_sel_cap is set, otherwise ignored0: no_preset_selected - changes Tx DB according to cable1-7: LT_index_preset_select - Tx will get / set LT preset" access="RW" offset="0x0.24" size="0x0.3" />
	<field name="vs_peer_db" descr="relevant for when c_db is set, else field is ignored.for when direct drive module connected:0 - db to override is for Did vs Did1 - db to override if for Did vs retimed module" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="lt_preset_sel_cap" descr="When set, lt_preset_sel field is valid." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="no_db_set" descr="supported only if PCAM bit 96 in feature_cap_mask is set.When set, Tx DB will not be written into HW on linkup phase.When cleared, Tx DB is written into HW on linkup phase." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="tap0" descr="(see above)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="tap1" descr="(see above)" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="tap2" descr="(see above)" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="tap3" descr="Signed value for TX FIR taps.tap scaling = fir_tap/63.Taps value must be under the following rules:The taps are 1-to-1 mapped as follow:Tap0- pre3Tap1 -pre2Tap2- pre1Tap3 -MainTap4- Post1Tap5- Post2taps [0-1, 6-11] valid ranges are [-8,8]And Also:|tap0| + | tap1| &lt;8|tap6| + | tap7| + | tap8|&lt;8|tap9| + | tap10| + | tap11| &lt;8taps [2-5] valid ranges are [-63, 63]For PAM4 links need to guarantee that the sum of the coefficient\;magnitude equals sum |c(i)| ≤ 63.For NRZ links must guarantee sum|c(i)| = 63Note: Configured taps may get effective value of +/-1 from the value\;that has been set." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="tap4" descr="(see above)" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="tap5" descr="(see above)" access="RW" offset="0x8.8" size="0x0.8" />
</node>

<node name="prtl_reg_ext" descr="" attr_required_tlvs="index:s" size="0x20.0" >
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0: Local_port_number1: IB_port_number3: Out_of_band" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rtt_support" descr="Support of RTT measurement" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="latency_accuracy" descr="Latency measurement accuracy (i,e. max error size).accuracy is relative to specific device implementation.This field returns the accuracy in nsec resolution." access="RO" offset="0x4.0" size="0x0.8" />
	<field name="latency_res" descr="Latency resolution in nsec of round_trip_latency" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="local_phy_latency" descr="Shall be 0 if not implemented (rtt_support = 0).This value represents the intra-ASIC pipeline latency of the physical\;layer. It is an unsigned 16-bit integer in nsec." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="local_mod_dp_latency" descr="Shall be 0 if not implemented (rtt_support = 0), if the module is not\;plugged in or if the information is not available on the plugged module.This value represents the module’s Datapath pipeline latency.It It is an\;unsigned 16-bit integer in nsec." access="RO" offset="0xc.0" size="0x0.16" />
	<field name="round_trip_latency" descr="Shall be 0 if not implemented (rtt_support = 0).This value represents a measurement of the round-trip latency of the\;link attached to this port.It is an unsigned 24-bit integer counting latency_res nsec.intervals.This value might not be accurate to better than +/- latency_accuracy\;nsec.A value of 0 is valid when implemented, and indicates a latency of up to\;latency_accuracy nsec.round_trip_latency is reset to 0xFFFFFF whenever this port transitions\;to PAOS.Oper_status = Down." access="RO" offset="0x10.0" size="0x0.24" />
</node>

<node name="prtsr_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="gl" descr="Global:0: per port1: global, all portsWhen reading and gl=1, read from local_port ‘1’" access="INDEX" offset="0x0.28" size="0x0.1" />
	<field name="prio_bitmask" descr="Prio bitmaskWhen IB: VLsWhen read: only 1 bit must be setWhen IB: valid bits: 0..7RW" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="ts" descr="Transmit Suspend:0: Off (transmit enabled)1: On (transmit suspended)2: Cycle_Based 3: Pulse_based" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="cycle_time" descr="Cycle time for cycle based ts, reserved when ts ≠ 2Cycle time will be 2^cycle_time*clk_timeclk_time (nSec) = 1000/QUERY_FW.core_clk (Mhz)" access="RW" offset="0xc.0" size="0x0.6" />
</node>

<node name="ptasv2_3nm_ext" descr="" size="0x34.0" >
	<field name="page_select" descr="Page select index.0: prbs_seeds1: APSU_control" access="INDEX" enum="prbs_seeds=0x0,APSU_control=0x1" offset="0x0.0" size="0x0.1" />
	<field name="page_data" descr="PTASv2 3nm PRBS Seeds Page Fields PTASv2 3nm APSU Control Page Fields" subnode="ptasv2_3nm_page_data_auto_ext" access="RW" offset="0x4.0" size="0x30.0" union_selector="$(parent).page_select" />
</node>

<node name="ptasv2_3nm_page_data_auto_ext" descr="" attr_is_union="1" size="0x30.0" >
	<field name="ef_ptasv2_3nm_apsu_ctrl_v1_ext" descr="" subnode="ef_ptasv2_3nm_apsu_ctrl_v1_ext" access="RW" offset="0x0.0" selected_by="APSU_control" size="0x18.0" />
	<field name="ef_ptasv2_3nm_prbs_v1_ext" descr="" subnode="ef_ptasv2_3nm_prbs_v1_ext" access="RW" offset="0x0.0" selected_by="prbs_seeds" size="0x30.0" />
</node>

<node name="ptasv2_7nm_ext" descr="" size="0x44.0" >
	<field name="max_recovery_events" descr="System parameter0: Disable. Default1:255: maximum allowed number of transitions into the RECOVERY state in\;the Training control state diagram" access="RW" offset="0x10.0" size="0x0.8" />
	<field name="lt_ext_neg_type" descr="affects negotiation type for lt_ext fields: iter_time_admin,\;num_of_iter_admin, prbs_type_admin, lt_ext_timeout_admin,\;ber_target_admin0: neg_agreed_function - oper fields will be applied by agreed function\;of negotiation1: force_params_to_peer - negotiation will force peer side to choose the\;local parameters. if both sides try to force parameters, agreed function\;will be applied2: ignore_neg - set support in negotiation to 0 and set local config to\;HW. this bit may result in an asymmetrical training between sides.\;Applicable only for hybrid lt ext only" access="RW" offset="0x10.16" size="0x0.2" />
	<field name="kr_extra_tune_fine_srch_cap" descr="When set, kr_extra_tune_fine_srch_en is supported" access="RO" offset="0x10.26" size="0x0.1" />
	<field name="ber_cnt_mlsd_dis_cap" descr="When set, ber_cnt_mlsd_dis is supported." access="RO" offset="0x10.27" size="0x0.1" />
	<field name="ber_target_cap" descr="When set, ber_target_coef_admin/oper and ber_target_magnitude_admin/oper\;are supported" access="RO" offset="0x10.28" size="0x0.1" />
	<field name="lt_ext_timeout_cap" descr="When set, lt_ext_timeout_admin/oper is supported" access="RO" offset="0x10.29" size="0x0.1" />
	<field name="prbs_type_cap" descr="When set, prbs_type_admin/oper is supported" access="RO" offset="0x10.30" size="0x0.1" />
	<field name="iterations_cap" descr="When set, iter_time_admin/oper and num_of_iter_admin/oper are supported" access="RO" offset="0x10.31" size="0x0.1" />
	<field name="lt_ext_timeout_admin" descr="requested value of The maximum time that the transmitter can transmit\;the requested PRBS type.Minimum required 60 secs. Granularity 1 secNote that: transmitted iterations x transmitted iteration time + 10\;msec, shall be less or equal to Maximum extended link training time." access="RW" offset="0x14.0" size="0x0.8" />
	<field name="prbs_type_admin" descr="0: PRBS_131: PRBS_31" access="RW" offset="0x14.8" size="0x0.2" />
	<field name="ber_cnt_mlsd_dis" descr="When set, Disables mlsd during ber count" access="RW" offset="0x14.10" size="0x0.1" />
	<field name="kr_extra_tune_fine_srch_en" descr="When set, Enables fine search algorithm" access="RW" offset="0x14.11" size="0x0.1" />
	<field name="num_of_iter_admin" descr="requested value of The number of required iterations. This parameter is\;required only for Async mode.The range is 1 to 16." access="RW" offset="0x14.16" size="0x0.4" />
	<field name="iter_time_admin" descr="requested value of the time that each iteration will use. An iteration\;is defined as a the time of the BER measurement that comes after the\;equalization.10 msec granularity." access="RW" offset="0x14.22" size="0x0.10" />
	<field name="ber_target_coef_admin" descr="(see above)" access="RW" offset="0x18.0" size="0x0.4" />
	<field name="ber_target_magnitude_admin" descr="requested value of BER target value.exit condition if BER target is met prior to end of all iterations,\;finish the algorithmBER_target = ber_target_coef *10^(-ber_target_magnitude)" access="RW" offset="0x18.8" size="0x0.8" />
	<field name="lt_ext_timeout_oper" descr="operational value of The maximum time that the transmitter can transmit\;the requested PRBS type.Minimum required 60 secs. Granularity 1 secNote that: transmitted iterations x transmitted iteration time + 10\;msec, shall be less or equal to Maximum extended link training time." access="RO" offset="0x1c.0" size="0x0.8" />
	<field name="prbs_type_oper" descr="operational value of prbs type0: PRBS_131: PRBS_31" access="RO" offset="0x1c.8" size="0x0.2" />
	<field name="num_of_iter_oper" descr="operational value of The number of required iterations. This parameter\;is required only for Async mode.The range is 1 to 16." access="RO" offset="0x1c.16" size="0x0.4" />
	<field name="iter_time_oper" descr="operational value of the time that each iteration will use. An iteration\;is defined as a the time of the BER measurement that comes after the\;equalization.10 msec granularity." access="RO" offset="0x1c.22" size="0x0.10" />
	<field name="ber_target_coef_oper" descr="(see above)" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="ber_target_magnitude_oper" descr="operational value of BER target value.exit condition if BER target is met prior to end of all iterations,\;finish the algorithmBER_target = ber_target_coef *10^(-ber_target_magnitude)" access="RO" offset="0x20.8" size="0x0.8" />
	<field name="fec_measure_retry_local_fail_count" descr="Number of times the link quality by fec measure failed locally.A value of 0 means the link quality check didn’t fail locally.A value of 1 means the link quality check failed locally once, and so\;on." access="RO" offset="0x30.28" size="0x0.4" />
	<field name="fec_measure_cap" descr="Set to 1 if fec measure cap feature is supported andfec_measure_retry_count, max_fec_measure_retry_count, fec_measure_time,\;fec_measure_en, fec_measure_fail_policy are valid." access="RO" offset="0x34.13" size="0x0.1" />
	<field name="max_fec_measure_retry_count" descr="Maximum number of times the link quality by fec measure can be\;re-checked before applying fail_action_policy0: FW default" access="RW" offset="0x34.16" size="0x0.4" />
	<field name="fec_measure_retry_count" descr="Number of times the link quality by fec measure re-checked before the\;link came up.A value of 0 means the link was ready after the first check.A value of 1 means the link needed to be checked twice, and so on." access="RO" offset="0x34.24" size="0x0.4" />
	<field name="fec_measure_time" descr="0: FW_default1-1023 - Sets in 10ms granularity the FEC measure time" access="RW" offset="0x38.16" size="0x0.10" />
	<field name="mask_enable" descr="bit 0 - when set, configure only apsu_ctl" access="RW" offset="0x38.27" size="0x0.1" />
	<field name="fec_measure_en" descr="0: FW_default1: Enable_fec_measure_after_lt2: Disable_fec_measure_after_lt" access="RW" enum="FW_default=0x0,Enable_fec_measure_after_lt=0x1,Disable_fec_measure_after_lt=0x2" offset="0x38.30" size="0x0.2" />
	<field name="fec_measure_force_neg" descr="0: neg_agreed_function - oper fields will be applied by agreedfunction\;of negotiation1: force_params_to_peer - negotiation will force peer side tochoose the\;local parameters. if both sides try to forceparameters, agreed function\;will be applied2: ignore_neg - set support in negotiation to 0 and set localconfig to\;HW. this bit may result in an asymmetrical trainingbetween sides." access="RW" offset="0x3c.0" size="0x0.2" />
	<field name="max_fec_measure_retry_count_oper" descr="agreed negotiation for maximum retry iteration to measure FEC.If retry counter exceeds the limit, link will continue to up with latest\;result of LT" access="RO" offset="0x3c.4" size="0x0.4" />
	<field name="fec_measure_fail_action" descr="0 - FW default1 - link up after after max retry expired2 - go to polling3 - go to disable only." access="RW" offset="0x3c.10" size="0x0.2" />
	<field name="fec_measure_fail_action_oper" descr="1 - link up after after max retry expired2 - go to polling3 - go to disable only." access="RO" offset="0x3c.13" size="0x0.2" />
	<field name="fec_measure_time_oper" descr="agreed operational fec measurement time.0: not_supported1-1023 - Sets in 10ms granularity the FEC measure time" access="RO" offset="0x3c.16" size="0x0.10" />
	<field name="fec_measure_oper" descr="0: fec_measure_disabled1: fec_measure_enabled" access="RO" offset="0x3c.30" size="0x0.1" />
</node>

<node name="ptasv2_reg_ext" descr="" attr_required_tlvs="index:s" size="0x4c.0" >
	<field name="xdr_lt_cap" descr="XDR LT capability.When set, xdr_lt_c2m_en and xdr_lt_c2c_en control is possible." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="ib_cfg_delaytimeout_cap" descr="Configuration of DelayTimeOut capability.When set ib_cfg_delaytimeout control is possible.[Note: This feature is currently available only for HDR switch]" access="RO" offset="0x0.10" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type.0 - Local port number1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: products_40nm4: products_7nm5: products_5nm6: products_3nm" access="RO" enum="products_7nm=0x4,products_5nm=0x5,products_3nm=0x6" offset="0x0.24" size="0x0.4" />
	<field name="xdr_lt_c2c_en" descr="LT for C2C channel Vs peer XDR speeds (200G per lane)0 - Auto (FW default)1 - skip LT flow2 - do LT flowThis bit will affect requested lt_xdr negotiation vs peer." access="RW" offset="0x4.0" size="0x0.2" />
	<field name="xdr_lt_c2m_en" descr="LT for C2M channel Vs Module XDR speeds (200G per lane)0 - Auto (FW default)1 - skip LT flow2 - do segmented LT flow" access="RW" offset="0x4.2" size="0x0.2" />
	<field name="lf_squelch_pol_cap" descr="When set, lf_squelch_pol_admin is configurable" access="RO" offset="0x4.12" size="0x0.1" />
	<field name="lf_squelch_pol_admin" descr="Defines behavior of ETH phy FSM on LF event (Rx fault)0: FW default1: Disable_Tx_squelch - keep Tx transmitting, no Tx Squelch2: Enable_Tx_squelch - Toggle Tx and module DP (if exists)" access="RW" offset="0x4.13" size="0x0.2" />
	<field name="kr_ext_oper" descr="Updated only after LT phase was performed.0: lt_is_disabled1: lt_enabled_regular_kr2: lt_enabled_ext_kr_async_mode" access="RO" offset="0x4.24" size="0x0.2" />
	<field name="kr_ext_req" descr="Extended KR request:0: Auto - (FW default)1: Disable_kr_ext2: Enable_kr_ext_in_async_modeWhile the KR extended is enabled- nonstandard KR training will occur.\;This will include pause periods between sending the KR frames and\;sending the PRBS pattern instead (to support BER grade calculations)" access="RW" enum="Disable_kr_ext=0x1,Enable_kr_ext_in_async_mode=0x2" offset="0x4.29" size="0x0.2" />
	<field name="kr_ext_cap" descr="Extended KR capability. Will return support for a nonstandard KR\;training flow (as explained in the fields below)." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="page_data" descr="PTASv2 - Phy Tuning Algorithm Settings Register Layout for 7nm and 5nm\;PTASv2 - Phy Tuning Algorithm Settings Register Layout for 3nm" subnode="ptasv2_reg_page_data_auto_ext" access="RW" condition="$(parent).version" offset="0x8.0" size="0x44.0" />
</node>

<node name="ptasv2_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x44.0" >
	<field name="ptasv2_3nm_ext" descr="" subnode="ptasv2_3nm_ext" access="RW" condition="($(parent).version == products_3nm)" offset="0x0.0" size="0x34.0" />
	<field name="ptasv2_7nm_ext" descr="" subnode="ptasv2_7nm_ext" access="RW" condition="($(parent).version == products_7nm) | ($(parent).version == products_5nm)" offset="0x0.0" size="0x44.0" />
</node>

<node name="pter_phy_page_reg_ext" descr="" size="0x1c.0" >
	<field name="error_type_admin" descr="Error Type to generate0: No_Error1: Raw_BER2: Effective_BER4: Symbol_errors - all transmitted 66/64 bit symbols will be\;erroneous for the configured time period in error_injection_time128: tx_polarity_flip" access="RW" enum="No_Error=0x0,Raw_BER=0x1,Effective_BER=0x2,Symbol_errors=0x4,tx_polarity_flip=0x80" offset="0x0.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilitiesBit 0: Raw_BERBit 1: Effective_BERBit 2 : Symbol_errorsBit 7: tx_polarity_flip" access="RO" enum="Raw_BER=0x1,Effective_BER=0x2,Symbol_errors=0x4,tx_polarity_flip=0x80" offset="0x0.8" size="0x0.8" />
	<field name="error_type_oper" descr="Error injection operational status0x0 - No error injection0x1 - Performing error injection" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="lm_cap" descr="When set, lane_mask field is applicable." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="ber_exp" descr="(see above)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ber_mantissa" descr="BER for injection.BER = ber_mantissa * 10^(-ber_exp)" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="error_injection_time" descr="Duration in 10 msec the port will generate errors.Reading this field will return the time left for errors to inject in\;msec0x0000 indicates no generation of errors.When set to 0xFFFF - No decremental operation, meaning the errors will\;be injected continuously without stop condition." access="RW" offset="0x4.12" size="0x0.16" />
	<field name="lane_mask" descr="Valid only if lm_cap is set, otherwise ignored. Sets the specific lanes\;to be applied from the error_type that was selected. Relevant for error\;types that can be per lane: 6: tx_reset, 7: tx_polarity_flip.Bitmask per lane." access="RW" offset="0x8.22" size="0x0.8" />
</node>

<node name="pter_port_page_reg_ext" descr="" size="0x1c.0" >
	<field name="error_type_admin" descr="Error Type to generate0 - No Error—- Port Errors —-1 - Corrupt data packet ICRC2 - Corrupt data packet VCRC4- Corrupt credit packet LPCRC" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilitiesBit 0- Corrupt data packet ICRCBit 1- Corrupt data packet VCRCBit 2- Corrupt credit packet LPCRC" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="error_count" descr="Error CountNumber of times the port will generate the configured error.0 indicates not to generate error.Reading error_count will return the number of left errors to inject.\;When 0, all requested errors has been injected." access="RW" offset="0x4.12" size="0x0.5" />
</node>

<node name="pter_reg_ext" descr="" attr_required_tlvs="index:s" size="0x20.0" >
	<field name="status" descr="Error injection status:0x0 -Good status0x2 - No available sources for Error injection0x3 - Error injection configuration when port is in non operational\;state (port is neither in UP or TEST MODE)0x4 - out of range BER setting" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="error_page" descr="Error_page selection:0: Injection_of_Phy_Errors1: Injection_of_Port_Errors" access="INDEX" enum="Injection_of_Phy_Errors=0x0,Injection_of_Port_Errors=0x1" offset="0x0.24" size="0x0.4" />
	<field name="page_data" descr="error injection page data:PTER- Port Transmit Errors Register Phy Level LayoutPTER- Port Transmit Errors Register Port Level Fields" subnode="pter_reg_page_data_auto_ext" access="RW" offset="0x4.0" size="0x1c.0" union_selector="$(parent).error_page" />
</node>

<node name="pter_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x1c.0" >
	<field name="pter_phy_page_reg_ext" descr="" subnode="pter_phy_page_reg_ext" access="RW" offset="0x0.0" selected_by="Injection_of_Phy_Errors" size="0x1c.0" />
	<field name="pter_port_page_reg_ext" descr="" subnode="pter_port_page_reg_ext" access="RW" offset="0x0.0" selected_by="Injection_of_Port_Errors" size="0x1c.0" />
</node>

<node name="ptsb_ext" descr="" size="0x20.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sl" descr="SLFor Blackwell: allowed 0..3.For Rubin-Ultra: allowed 0..5.Reserved when type = 0" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="vc" descr="VC (Virtual Channel)For Blackwell: allowed 0,1.For Rubin-Ultra: allowed 0,1,2,3.Reserved when type = 1" access="INDEX" offset="0x4.4" size="0x0.4" />
	<field name="pipe" descr="PipeFor Blackwell: allowed 0,1.Reserved when type = 1" access="INDEX" offset="0x4.8" size="0x0.4" />
	<field name="type" descr="Type:0: NVLink1: IB" access="INDEX" offset="0x4.12" size="0x0.4" />
	<field name="burst_send" descr="Burst send:Send up to burst_send consecutive packets.Value of 0 is not supported.FW will send 1 packet after each other, typically time of 100’s of nSec\;between every 2 packets.Note that this “allows sending”. If there are no packets or no credits\;then the packets will not be transmitted but the counter will be\;incremented" access="OP" offset="0x8.0" size="0x0.10" />
</node>

<node name="ptsr_ext" descr="" size="0x20.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ts" descr="Tx suspend:0: Tx enabled (default)1: Tx disabled" access="RW" offset="0x4.0" size="0x0.1" />
</node>

<node name="ptys_ext_proto_ib_admin_ext" descr="" size="0x4.0" >
	<field name="ext_proto_ib" descr="IB bitmask:Bit 0: SDR_1xBit 1: SDR_2xBit 2: SDR_4xBit 12: FDR_4xBit 14: EDR_2xBit 15: EDR_4xBit 16: HDR_1xBit 17: HDR_2xBit 18: HDR_4xBit 20: NDR_1xBit 21: NDR_2xBit 22: NDR_4xBit 24: XDR_1xBit 25: XDR_2xBit 26: XDR_4x" access="RW" enum="SDR_1x=0x1,SDR_2x=0x2,SDR_4x=0x4,FDR_4x=0x1000,EDR_2x=0x4000,EDR_4x=0x8000,HDR_1x=0x10000,HDR_2x=0x20000,HDR_4x=0x40000,NDR_1x=0x100000,NDR_2x=0x200000,NDR_4x=0x400000,XDR_1x=0x1000000,XDR_2x=0x2000000,XDR_4x=0x4000000" offset="0x0.0" size="0x4.0" />
</node>

<node name="ptys_ext_proto_ib_cap_oper_ext" descr="" size="0x4.0" >
	<field name="ext_proto_ib" descr="IB bitmask:Bit 0: SDR_1xBit 1: SDR_2xBit 2: SDR_4xBit 12: FDR_4xBit 14: EDR_2xBit 15: EDR_4xBit 16: HDR_1xBit 17: HDR_2xBit 18: HDR_4xBit 20: NDR_1xBit 21: NDR_2xBit 22: NDR_4xBit 24: XDR_1xBit 25: XDR_2xBit 26: XDR_4x" access="RO" enum="SDR_1x=0x1,SDR_2x=0x2,SDR_4x=0x4,FDR_4x=0x1000,EDR_2x=0x4000,EDR_4x=0x8000,HDR_1x=0x10000,HDR_2x=0x20000,HDR_4x=0x40000,NDR_1x=0x100000,NDR_2x=0x200000,NDR_4x=0x400000,XDR_1x=0x1000000,XDR_2x=0x2000000,XDR_4x=0x4000000" offset="0x0.0" size="0x4.0" />
</node>

<node name="ptys_ext_proto_nvlink_admin_ext" descr="" size="0x4.0" >
	<field name="ext_proto_nvlink" descr="NVLink bitmask:Bit 0: 200G_1x_mode_a -\;Bit 1: 400G_2x_mode_a Bit 2: 400G_2x_mode_b Bit 3: 360G_2x_mode_b Bit 4: 328G_2x_mode_b Bit 5: 378_2x_mode_b \;Bit 6: 200G_2x_mode_a \;Bit 7: 187G_1x_mode_a Bit 8: 176G_1x_mode_a Bit 9: 169G_1x_mode_a Bit 10: 100G_1x_mode_a Bit 11: 345G_2x_mode_b" access="RW" offset="0x0.0" size="0x4.0" />
</node>

<node name="ptys_ext_proto_nvlink_cap_oper_ext" descr="" size="0x4.0" >
	<field name="ext_proto_nvlink" descr="NVLink bitmask:Bit 0: 200G_1x_mode_a -\;Bit 1: 400G_2x_mode_a Bit 2: 400G_2x_mode_b Bit 3: 360G_2x_mode_b Bit 4: 328G_2x_mode_b Bit 5: 378_2x_mode_b \;Bit 6: 200G_2x_mode_a \;Bit 7: 187G_1x_mode_a Bit 8: 176G_1x_mode_a Bit 9: 169G_1x_mode_a Bit 10: 100G_1x_mode_a Bit 11: 345G_2x_mode_b" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="ptys_reg_ext" descr="" attr_required_tlvs="index:s" size="0x44.0" >
	<field name="proto_mask" descr="Protocol Mask. Indicates which of the protocol data is validBit 0: InfiniBandBit 1: NVLinkBit 2: Ethernet" access="INDEX" enum="InfiniBand=0x1,NVLink=0x2,Ethernet=0x4" offset="0x0.0" size="0x0.3" />
	<field name="transmit_allowed" descr="Valid only when port is mapped to SW controlled module, otherwise\;ignored. module control can be queried via MMCR register.0: transmit_not_allowed - Transmitter is not allowed to transmit\;signal on output1: transmit_allowed - Transmitter is allowed to transmit signal on\;output. for enabling transmitter, PAOS.admin_status must be up as\;well." access="RW" enum="transmit_not_allowed=0x0,transmit_allowed=0x1" offset="0x0.3" size="0x0.1" />
	<field name="plane_ind" descr="Reserved for non-planarized port.Plane port index of the aggregated port. A value of 0 refers to the\;aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="port_type" descr="Supported only when indicated by PCAM0: Network_Port1: Near_End_Port - (For Gearbox - Host side)2: Internal_IC_Port3: Far_End_Port - (For Gearbox - Line side)Other values are reserved." access="INDEX" enum="Network_Port=0x0,Near_End_Port=0x1,Internal_IC_Port=0x2,Far_End_Port=0x3" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="tx_ready_e" descr="Valid only when ee_tx_ready is set, otherwise field is ignored.0: do_not_generate_eventBit 0: generate_tx_ready_event - When set, PTSE register will generate\;event when Transmitter is generating valid signal on the lineBit 1: generate_tx_not_ready_event - when set, PTSE will generate event\;when the transmitter stopped transmitting after Tx_ready was set.Note: if both tx_not_ready and tx_ready are set, one toggle event may be\;received instead of 2 consecutive events of not ready –&gt; ready." access="RW" offset="0x0.26" size="0x0.2" />
	<field name="ee_tx_ready" descr="Event Enable for tx_ready_e.when bit is not set, tx_teady_e write value will be ignored" access="WO" offset="0x0.28" size="0x0.1" />
	<field name="an_disable_cap" descr="Auto Negotiation disable capability:0 - Device does not support AN disable1 - Device Supports AN disable" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="an_disable_admin" descr="Auto Negotiation disable:0 - Normal operation1 - Disable AN.Note: In Ethernet port, when Disabling AN, the “eth_proto_admin” bit\;mask must comply to single speed rate set.In IB port, when Disabling AN, the “ib_proto_admin” bit mask must comply\;to single speed rate set.It’s recommended to validate the FEC override bits in PPLM when\;operating with AN." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="data_rate_oper" descr="Port data rate in resolution of 100 Mb/s (data_rate_oper * 100 Mb/s)Value 0x0 indicates this field is not supported." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_port_rate" descr="Port maxium data rate in resolution of 1 Gb/s (data_rate_oper * 1 Gb/s)Value 0x0 indicates this field is not supported." access="RO" offset="0x4.16" size="0x0.12" />
	<field name="an_status" descr="Auto Negotiation status:0: Status_is_unavailable1: AN_completed_successfully2: AN_performed_but_failed3: AN_was_not_performed_link_is_up4: AN_was_not_performed_link_is_down" access="RO" enum="Status_is_unavailable=0x0,AN_completed_successfully=0x1,AN_performed_but_failed=0x2,AN_was_not_performed_link_is_up=0x3,AN_was_not_performed_link_is_down=0x4" offset="0x4.28" size="0x0.4" />
	<field name="ext_eth_proto_capability" descr="For HCA: See also PCAM.feature_cap_mask bit 13 for Extended Ethernet\;protocol support.Extended Ethernet port speed/protocols supported (bitmask):Bit 0: SGMII_100MBit 1: 1000BASE-X / SGMIIBit 3: 5GBASE-RBit 4: XFI / XAUI-1 // 10GBit 5: XLAUI-4/XLPPI-4 // 40GBit 6: 25GAUI-1/ 25GBASE-CR / KRBit 7: 50GAUI-2 / LAUI-2/ 50GBASE-CR2/KR2Bit 8: 50GAUI-1 /50GBASE-CR / KRBit 9: CAUI-4 / 100GBASE-CR4 / KR4Bit 10: 100GAUI-2 / 100GBASE-CR2 / KR2Bit 11: 100GAUI-1 / 100GBASE-CR / KRBit 12: 200GAUI-4 / 200GBASE-CR4/KR4Bit 13: 200GAUI-2 / 200GBASE-CR2/KR2Bit 14: 200GAUI-1 / 200GBASE-CR1/KR1Bit 15: 400GAUI-8/ 400GBASE-CR8Bit 16: 400GAUI-4/ 400GBASE-CR4Bit 17: 400GAUI-2 / 400GBASE-CR2/KR2Bit 18: Reserved Bit 19: 800GAUI-8 / 800GBASE-CR8 / KR8 Bit 20: 800GAUI-4 / 800GBASE-CR4/KR4Bit 23: 1.6TAUI-8 /1.6TBASE-CR8/KR8Bit 31: SGMII_10MOther - Reserved" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="eth_proto_capability" descr="Ethernet port speed/protocols supported (bitmask)Bit 31 - 50GBase-KR2Bit 30 - 50GBase-CR2Bit 29 - 25GBase-SRBit 28 - 25GBase-KRBit 27 - 25GBase-CRBit 26 - 10GBase-TBit 25 - 1000Base-TBit 24 - 100Base-TX Bit 23 - 100GBase LR4/ER4Bit 22 - 100GBase KR4Bit 21 - 100GBase SR4Bit 20 - 100GBase CR4Bit 18 - 50GBase-SR2Bit 16 - 40GBase LR4/ER4Bit 15 - 40GBase SR4Bit 14 - 10GBase ER/LRBit 13 - 10GBase SRBit 12 - 10GBase CRBit 10 - 10Base-TBit 9 - SGMII_100BaseBit 7 - 40GBase KR4Bit 6 - 40GBase CR4Bit 4 - 10GBase KRBit 3 - 10GBase KX4Bit 2 - 10GBase-CX4Bit 1 - 1000Base KXBit 0 - SGMII" access="RO" offset="0xc.0" size="0x4.0" />
	<field name="ib_proto_capability" descr="InfiniBand port speed supported (bitmask)Bit 0: SDR Bit 1: DDRBit 2: QDRBit 3: FDR10Bit 4: FDRBit 5: EDRBit 6: HDRBit 7: NDRBit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x10.0" size="0x0.16" />
	<field name="ib_link_width_capability" descr="ib_link_width ≤ ib_proto_capabilityBit 0 - 1x Bit 1 - 2xBit 2 - 4x" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="ext_eth_proto_admin" descr="Ethernet port extended speed/protocols bitmaskNOTE: This field and “eth_proto_admin” are mutual exclusive, meaning\;that only one of the field can be set on write command." access="RW" offset="0x14.0" size="0x4.0" />
	<field name="eth_proto_admin" descr="Ethernet port speed/protocols bitmask" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="ib_proto_admin" descr="InfiniBand port speed bitmask" access="RW" offset="0x1c.0" size="0x0.16" />
	<field name="ib_link_width_admin" descr="InfiniBand port link width bitmask" access="RW" offset="0x1c.16" size="0x0.16" />
	<field name="ext_eth_proto_oper" descr="Ethernet port extended speed/protocols bitmask" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="eth_proto_oper" descr="Ethernet port speed/protocols bitmask" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="ib_proto_oper" descr="InfiniBand port speed bitmask" access="RO" offset="0x28.0" size="0x0.16" />
	<field name="ib_link_width_oper" descr="InfiniBand port link width bitmask" access="RO" offset="0x28.16" size="0x0.16" />
	<field name="connector_type" descr="Connector type indication0: No_connector_or_unknown1: PORT_NONE - None2: PORT_TP - Twisted Pair3: PORT_AUI - AUI4: PORT_BNC - BNC5: PORT_MII - MII6: PORT_FIBRE - FIBRE7: PORT_DA - Direct Attach Copper8: PORT_OTHER - Other" access="RO" enum="No_connector_or_unknown=0x0,PORT_NONE=0x1,PORT_TP=0x2,PORT_AUI=0x3,PORT_BNC=0x4,PORT_MII=0x5,PORT_FIBRE=0x6,PORT_DA=0x7,PORT_OTHER=0x8" offset="0x2c.0" size="0x0.4" />
	<field name="lane_rate_oper" descr="For active link, Indicates the lane data rate passed per physical lane\;including the overhead due to FEC.resolution of 10 Mb/s (lane_rate_oper * 10Mb/s)." access="RO" offset="0x2c.4" size="0x0.20" />
	<field name="xdr_2x_slow_active" descr="When set and link active, indicates link speed is xdr_2x slow." access="RO" offset="0x2c.24" size="0x0.1" />
	<field name="xdr_2x_slow_admin" descr="When set, along with ib protocol xdr_2x, XDR_2x slow will be allowed\;instead of xdr_2x.Note: in GB100, set by default only with ini and cannot be changed." access="RW" offset="0x2c.25" size="0x0.1" />
	<field name="force_lt_frames_admin" descr="Ethernet Force mode options when AN disable is set.0 - auto, keep normal operation1 - Do Force LT (KR Startup) flow2 - Do not do LT (KR Startup) flowNote: Ignored when an_disable_admin is not setIn Ethernet port, when setting force LT flow, the “eth_proto_ext_admin”\;bit mask must comply to single speed rate set." access="RW" offset="0x2c.28" size="0x0.2" />
	<field name="force_lt_frames_cap" descr="0 - device does not support Force LT (KR Startup) flow1 - device supports Force LT (KR Startup) flowNote: Ignored when an_disable_admin is not set" access="RO" offset="0x2c.30" size="0x0.1" />
	<field name="xdr_2x_slow_cap" descr="capability for XDR_2x slow is support (200G)" access="RO" offset="0x2c.31" size="0x0.1" />
	<field name="ext_ib_proto_cap" descr="IB/NVlink port supported protocols and widths bit-mask.Valid if PCAM.feature_cap_mask bit 90 is set OR mask &lt;&gt;0.For IB:\;PTYS - Extended Protocol IB - cap/oper LayoutFor NVLink:\;PTYS - Extended Protocol NVLink - cap/oper Layout" subnode="ptys_reg_ext_ib_proto_cap_auto_ext" access="RO" offset="0x38.0" size="0x4.0" union_selector="$(parent).proto_mask" />
	<field name="ext_ib_proto_admin" descr="IB/NVLink port protocols admin values.For IB:\;PTYS - Extended Protocol IB - admin LayoutFor NVLink:\;PTYS - Extended Protocol NVLink - admin LayoutNOTE: This field and “ib_proto_admin”, “ib_link_width_admin” are mutual\;exclusive, meaning that only one of the field can be set on write\;command." subnode="ptys_reg_ext_ib_proto_admin_auto_ext" access="RW" offset="0x3c.0" size="0x4.0" union_selector="$(parent).proto_mask" />
	<field name="ext_ib_proto_oper" descr="IB/NVLink port operational protocol.For IB:\;PTYS - Extended Protocol IB - cap/oper LayoutFor NVLink:\;PTYS - Extended Protocol NVLink - cap/oper Layout" subnode="ptys_reg_ext_ib_proto_oper_auto_ext" access="RO" offset="0x40.0" size="0x4.0" union_selector="$(parent).proto_mask" />
</node>

<node name="ptys_reg_ext_ib_proto_admin_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="ptys_ext_proto_ib_admin_ext" descr="" subnode="ptys_ext_proto_ib_admin_ext" access="RW" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="ptys_ext_proto_nvlink_admin_ext" descr="" subnode="ptys_ext_proto_nvlink_admin_ext" access="RW" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="ptys_reg_ext_ib_proto_cap_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="ptys_ext_proto_ib_cap_oper_ext" descr="" subnode="ptys_ext_proto_ib_cap_oper_ext" access="RW" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="ptys_ext_proto_nvlink_cap_oper_ext" descr="" subnode="ptys_ext_proto_nvlink_cap_oper_ext" access="RW" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="ptys_reg_ext_ib_proto_oper_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="ptys_ext_proto_ib_cap_oper_ext" descr="" subnode="ptys_ext_proto_ib_cap_oper_ext" access="RW" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="ptys_ext_proto_nvlink_cap_oper_ext" descr="" subnode="ptys_ext_proto_nvlink_cap_oper_ext" access="RW" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pude_reg_ext" descr="" attr_required_tlvs="index:s" size="0x10.0" >
	<field name="oper_status" descr="Port operational state:0001 - up0010 - down0100 - down by port failure (transitioned by the hardware)" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="admin_status" descr="Port administrative state (the desired state of the interface):0001 - up0010 - down by configuration0011 - up once - if the port goes up and then down, the operational\;status should go to “down by port failure” and can only go back up\;upon explicit command0100 - disabled by system0110 - sleep" access="RO" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.Switch partition ID with which to associate the port.Switch partitions are numbered from 0 to 7 inclusively.Switch partition 254 indicates stacking ports.Switch partition 255 indicates all switch partitions.Note: While external ports uses unique local port numbers (and thus swid\;is redundant), router ports use the same local port number where swid is\;the only indication for the relevant port." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="nmx_adminstate_status" descr="NVLink Port NMX AdminState current state:0: NA1: Up2: Down3: DiagAll others reserved" access="RO" enum="NA=0x0,Up=0x1,Down=0x2,Diag=0x3" offset="0x4.0" size="0x0.3" />
	<field name="physical_state_status" descr="IB Port Physical link state:0: N/A1: Sleep2: Polling3: Disabled4: PortConfigurationTraining5: LinkUp6: LinkErrorRecoveryAll others reserved" access="RO" enum="N_A=0x0,Sleep=0x1,Polling=0x2,Disabled=0x3,PortConfigurationTraining=0x4,LinkUp=0x5,LinkErrorRecovery=0x6" offset="0x4.4" size="0x0.4" />
	<field name="logical_state_status" descr="IB or NVLink Port Logical link state:0: N/A1: Down2: Init3: Arm4: ActiveNote: Logical Link State shall be ignored in case physical oper state is\;not UP." access="RO" offset="0x4.16" size="0x0.3" />
	<field name="recoverable_down" descr="Valid only for GPU when PCAM.feature_cap_mask 122 is set, otherwise\;ignored0: Link Down state is not recoverable1: recoverable" access="RO" offset="0x4.19" size="0x0.1" />
	<field name="phy_force_linkup_mode" descr="Indicates physical link entered forced linkup debug mode" access="RO" offset="0x4.20" size="0x0.1" />
	<field name="local_reason_opcode" descr="Opcode of link down reason for local0: No_link_down_indication1: Unknown_reason2: Hi_BER3: Block_Lock_loss4: Alignment_loss5: FEC_sync_loss6: PLL_lock_loss7: FIFO_overflow8: false_SKIP_condition9: Minor_Error_threshold_exceeded10: Physical_layer_retransmission_timeout11: Heartbeat_errors12: Link_Layer_credit_monitoring_watchdog13: Link_Layer_integrity_threshold_exceeded14: Link_Layer_buffer_overrun15: Down_by_outband_command_with_healthy_link16: Down_by_outband_command_for_link_with_hi_ber17: Down_by_inband_command_with_healthy_link18: Down_by_inband_command_for_link_with_hi_ber19: Down_by_verification_GW20: Received_Remote_Fault21: Received_TS122: Down_by_management_command23: Cable_was_unplugged24: Cable_access_issue25: Cable_Thermal_shutdown26: Current_issue27: Power_budget28: Fast_recovery_raw_ber29: Fast_recovery_effective_ber30: Fast_recovery_symbol_ber31: Fast_recovery_credit_watchdog32: Peer_side_down_to_sleep_state33: Peer_side_down_to_disable_state34: Peer_side_down_to_disable_and_port_lock35: Peer_side_down_due_to_thermal_event36: Peer_side_down_due_to_force_event37: Peer_side_down_due_to_reset_event38: Reset_no_power_cycle39: Fast_recovery_tx_plr_trigger40: Down_due_to_HW_force_event41: Down_due_to_thermal_event42: L1_exit_failure43: too_many_link_error_recoveries44: Down_due_to_contain_mode45: BW_loss_threshold_exceeded - Tx PLR BW loss46: ELS_laser_fault47: Hi_SER48: down_by_nmx_adminstate_cmd49: flua_ber_below_threshold_in_guard_time50: Received_Local_Fault51: Received_Link_Interruption52: Manual_debug_mode53: command_triggered_recovery58: Recovery_BW_loss_threshold_exceeded59: Peer_side_down_due_to_contain_mode60: module_unexpected_reset_or_low_power61: Down_due_to_contain_mode_rx62: Down_due_to_contain_mode_txNote -\;reasons that have long propogation delay may not be reflected on the link down event cause. These events can be queried in PDDR.link_down_info_page.local_reason_opcode once they are updated.example for such an event is “23: Cable_was_unplugged”, 46: ELS_laser_fault" access="RO" enum="No_link_down_indication=0x0,Unknown_reason=0x1,Hi_BER=0x2,Block_Lock_loss=0x3,Alignment_loss=0x4,FEC_sync_loss=0x5,PLL_lock_loss=0x6,FIFO_overflow=0x7,false_SKIP_condition=0x8,Minor_Error_threshold_exceeded=0x9,Physical_layer_retransmission_timeout=0xa,Heartbeat_errors=0xb,Link_Layer_credit_monitoring_watchdog=0xc,Link_Layer_integrity_threshold_exceeded=0xd,Link_Layer_buffer_overrun=0xe,Down_by_outband_command_with_healthy_link=0xf,Down_by_outband_command_for_link_with_hi_ber=0x10,Down_by_inband_command_with_healthy_link=0x11,Down_by_inband_command_for_link_with_hi_ber=0x12,Down_by_verification_GW=0x13,Received_Remote_Fault=0x14,Received_TS1=0x15,Down_by_management_command=0x16,Cable_was_unplugged=0x17,Cable_access_issue=0x18,Cable_Thermal_shutdown=0x19,Current_issue=0x1a,Power_budget=0x1b,Fast_recovery_raw_ber=0x1c,Fast_recovery_effective_ber=0x1d,Fast_recovery_symbol_ber=0x1e,Fast_recovery_credit_watchdog=0x1f,Peer_side_down_to_sleep_state=0x20,Peer_side_down_to_disable_state=0x21,Peer_side_down_to_disable_and_port_lock=0x22,Peer_side_down_due_to_thermal_event=0x23,Peer_side_down_due_to_force_event=0x24,Peer_side_down_due_to_reset_event=0x25,Reset_no_power_cycle=0x26,Fast_recovery_tx_plr_trigger=0x27,Down_due_to_HW_force_event=0x28,Down_due_to_thermal_event=0x29,L1_exit_failure=0x2a,too_many_link_error_recoveries=0x2b,Down_due_to_contain_mode=0x2c,BW_loss_threshold_exceeded=0x2d,ELS_laser_fault=0x2e,Hi_SER=0x2f,down_by_nmx_adminstate_cmd=0x30,flua_ber_below_threshold_in_guard_time=0x31,Received_Local_Fault=0x32,Received_Link_Interruption=0x33,Manual_debug_mode=0x34,command_triggered_recovery=0x35,Recovery_BW_loss_threshold_exceeded=0x3a,Peer_side_down_due_to_contain_mode=0x3b,module_unexpected_reset_or_low_power=0x3c,Down_due_to_contain_mode_rx=0x3d,Down_due_to_contain_mode_tx=0x3e" offset="0x4.24" size="0x0.8" />
</node>

<node name="pvlc_reg_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="vl_hw_cap" descr="Virtual Lanes supported on this port.0 - Reserved1: VL02: VL0, VL14: VL0 - VL38: VL0 - VL715: VL0 - VL14" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="vl_admin" descr="Virtual Lanes enabled by the local admin on this port.0: No change; valid only on Set()1: VL02: VL0, VL14: VL0 - VL38: VL0 - VL715: VL0 - VL14" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="vl_operational" descr="Operational VLs as configured by the SM on this port:0: No change; valid only on Set()1: VL02: VL0, VL14: VL0 - VL38: VL0 - VL715: VL0 - VL14Changing vl_operational in certain PortStates may cause in flow control\;update errors which may initiate Link/PHY retraining.vl_operational value is valid only when link state is UP." access="RO" offset="0xc.0" size="0x0.4" />
</node>

<node name="reg_return_status_ext" descr="" size="0x4.0" >
	<field name="reg_id" descr="The register ID0 to indicate the entry isn’t valid" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="return_status" descr="The PRM register return status as defined in\;EMAD Frame Format Layout - OPERATION TLV\;status field" access="RO" offset="0x0.24" size="0x0.7" />
</node>

<node name="resource_dump_ext" descr="" size="0xc8.0" >
	<field name="segment_type" descr="See Resource Dump section in the Adapters PRM." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="seq_num" descr="Sequence number. 0 on first call of dump and incremented on each more\;dump." access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="vhca_id_valid" descr="If set, then vhca_id field is valid. Otherwise dump resources on my\;vhca_id.Not supported in Switch." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="inline_dump" descr="If set, data is dumped in the register in inline_data field. otherwise\;dump to mkey.Supports only inline dump = 1" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="more_dump" descr="If set, the device has additional information that has not been dumped\;yet." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="vhca_id" descr="vhca_id where the resource is allocated.Not supported in Switch." access="WO" offset="0x4.0" size="0x0.16" />
	<field name="index1" descr="First object index to be dumped when supported by the object.SW shall read this field upon command done and shall provide it on the\;next call in case dump_more==1." access="INDEX" offset="0x8.0" size="0x4.0" />
	<field name="index2" descr="Second object index to be dumped when supported by the object.SW shall read this field upon command done and shall provide it on the\;next call in case dump_more==1." access="INDEX" offset="0xc.0" size="0x4.0" />
	<field name="num_of_obj2" descr="The amount of objects to dump starting for index 2.SW shall read this field upon command done and shall provide it on the\;next call in case dump_more==1.Range is 0..0xfff0. When the segment’s num_of_obj2_supports_all is set,\;the special value of 0xffff represents “all”. When the segment’s\;num_of_objx_supports_active is set, the special value of 0xfffe\;represents “active”. The value of 0x0 and 0x1 are allowed even if the\;supported_num_of_obj2 is “0”." access="INDEX" offset="0x10.0" size="0x0.16" />
	<field name="num_of_obj1" descr="The amount of objects to dump starting for index 1SW shall read this field upon command done and shall provide it on the\;next call in case dump_more==1.Range is 0..0xfff0. When the segment’s num_of_obj1_supports_all is set,\;the special value of 0xffff represents “all”. When the segment’s\;num_of_objx_supports_active is set, the special value of 0xfffe\;represents “active”. The value of 0x0 and 0x1 are allowed even if the\;supported_num_of_obj1 is “0”." access="INDEX" offset="0x10.16" size="0x0.16" />
	<field name="device_opaque" descr="An opaque provided by the device. SW shall read the device_opaque upon\;command done and shall provide it on the next call in case dump_more==1.\;On first call, device_opaque shall be 0." subnode="uint64" access="INDEX" offset="0x18.0" size="0x8.0" />
	<field name="mkey" descr="Memory key to dump to.Valid when inline_dump==0.Not supported in Switch." access="WO" offset="0x20.0" size="0x4.0" />
	<field name="size" descr="In write, the size of maximum allocated buffer that the device can use.In read, the actual written size.In granularity of Bytes.Not supported in Switch." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="address" descr="VA address (absolute address) of memory where to start dumping.Valid when inline_dump==0.Not supported in Switch." subnode="uint64" access="WO" offset="0x28.0" size="0x8.0" />
	<field name="inline_data" descr="Data that is dumped in case of inline mode.Valid when inline_dump==1." access="RO" high_bound="37" low_bound="0" offset="0x30.0" size="0x98.0" />
</node>

<node name="riscv_exception_ext" descr="" size="0x18.0" >
	<field name="mepc" descr="Machine Exception Program Counter (mepc)." subnode="uint64" access="RO" offset="0x0.0" size="0x8.0" />
	<field name="mcause" descr="Machine Cause Register (mcause).RiscV exception code." subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
	<field name="mtval" descr="Machine Trap Value (mtval) Register.Holds exception-specific information\;to assist software in handling the trap." subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="rom_version_ext" descr="" size="0x4.0" >
	<field name="build" descr="Build version" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="minor" descr="Minor version" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="major" descr="Major version" access="RO" offset="0x0.24" size="0x0.8" />
</node>

<node name="sllm_5nm_ext" descr="" size="0x2c.0" >
	<field name="peq_cap" descr="" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="is_peq_on" descr="" access="RO" offset="0x0.2" size="0x0.1" />
	<field name="peq_interval_period" descr="" access="RW" offset="0x4.0" size="0x0.12" />
	<field name="peq_interval_period_oper" descr="" access="RO" offset="0x8.0" size="0x0.12" />
</node>

<node name="sllm_reg_ext" descr="" attr_required_tlvs="index:s" size="0x30.0" >
	<field name="c_db" descr="copy to FW Data-Base." access="OP" offset="0x0.0" size="0x0.1" />
	<field name="br_lanes" descr="When set, configuration will be applied to all port lanes" access="WO" offset="0x0.1" size="0x0.1" />
	<field name="br_lanes_cap" descr="When set, br_lanes config is valid. otherwise, field ignores config" access="RO" offset="0x0.2" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0: Network_Port1: NearEnd_Port - (For Retimer/Gearbox - Host side)2: Internal_IC_LR_Port3: FarEnd_Port - (For Retimer/Gearbox - Line side)4: USR_Main5: USR_TileOther values are reserved." access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3,USR_Main=0x4,USR_Tile=0x5" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="3: prod_16nm4: prod_7nm5: prod_5nm - (Uphy 7.0/ 7.5)6: serdes_gen_8" access="RO" enum="prod_16nm=0x3,prod_7nm=0x4,prod_5nm=0x5,serdes_gen_8=0x6" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - invalid1 - valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="SLLM - SerDes Lane Link Maintenance Register Layout for 5nm and Serdes_gen_8" subnode="sllm_reg_page_data_auto_ext" access="RO" condition="$(parent).port_type AND $(parent).version" offset="0x4.0" size="0x2c.0" />
</node>

<node name="sllm_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x2c.0" >
	<field name="sllm_5nm_ext" descr="" subnode="sllm_5nm_ext" access="RW" condition="(($(parent).port_type == Network_Port || $(parent).port_type == NearEnd_Port || $(parent).port_type == FarEnd_Port)) AND (($(parent).version == prod_5nm) OR $(parent).version == serdes_gen_8)" offset="0x0.0" size="0x2c.0" />
</node>

<node name="slmtrd_reg_ext" descr="" attr_required_tlvs="index:s" size="0x10.0" >
	<field name="status" descr="0: no_measurement_enabled1: measurement_in_progress2: measurement_done3: measurement_errorNote - only 1 measurement at a time can be done" access="RO" enum="no_measurement_enabled=0x0,measurement_in_progress=0x1,measurement_done=0x2,measurement_error=0x3" offset="0x0.0" size="0x0.3" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0 - Network Port1 - Near-End Port (For Retimer/Gearbox - Host side)3 - Far-End Port (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number to access" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number / DataPath number for Retimer1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.10" />
	<field name="deallocate_memory" descr="For NIC only (CX-9).When set, triggers release of previously allocated shared memory upon\;completion of the user operation.0 - do noting1 - release memory" access="WO" offset="0x0.28" size="0x0.1" />
	<field name="mode_b_idx" descr="0: mode_a 1: mode_b" access="RO" enum="mode_a=0x0,mode_b=0x1" offset="0x0.29" size="0x0.1" />
	<field name="stop_measure" descr="0: do nothing1:Stop measure" access="WO" offset="0x0.30" size="0x0.1" />
	<field name="start_measure" descr="0: do nothing1: Enable measurementNote: The measurement is destructive, once done, the link can’t be used\;and need to restart" access="WO" offset="0x0.31" size="0x0.1" />
	<field name="trigger_type" descr="set flow type0: SLPRR" access="INDEX" enum="SLPRR=0x0" offset="0x4.22" size="0x0.5" />
	<field name="version" descr="5: prod_5nm - (Uphy 7.0)6: serdes_gen_87: prod_3nm_serdes_gen_7p5" access="RO" enum="prod_5nm=0x5,serdes_gen_8=0x6,prod_3nm_serdes_gen_7p5=0x7" offset="0x4.28" size="0x0.4" />
</node>

<node name="slprr_Extended_read_7_1_ext" descr="" size="0x58.0" >
	<field name="prr6_1" descr="" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="prr2_m8" descr="" access="RO" offset="0x0.7" size="0x0.4" />
	<field name="prr2_m9" descr="" access="RO" offset="0x0.12" size="0x0.3" />
	<field name="prr1_2" descr="" access="RO" offset="0x0.17" size="0x0.5" />
	<field name="prr1_1" descr="" access="RO" offset="0x0.24" size="0x0.2" />
	<field name="prr1_0" descr="" access="RO" offset="0x0.29" size="0x0.3" />
	<field name="prr2_m3" descr="" access="RO" offset="0x4.3" size="0x0.8" />
	<field name="prr2_m2" descr="" access="RO" offset="0x4.13" size="0x0.8" />
	<field name="prr2_m1" descr="" access="RO" offset="0x4.23" size="0x0.9" />
	<field name="prr2_2" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="prr2_1" descr="" access="RO" offset="0x8.9" size="0x0.8" />
	<field name="prr2_m5" descr="" access="RO" offset="0x8.17" size="0x0.7" />
	<field name="prr2_m4" descr="" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="prr2_6" descr="" access="RO" offset="0xc.1" size="0x0.6" />
	<field name="prr2_5" descr="" access="RO" offset="0xc.8" size="0x0.7" />
	<field name="prr2_4" descr="" access="RO" offset="0xc.17" size="0x0.7" />
	<field name="prr2_3" descr="" access="RO" offset="0xc.25" size="0x0.7" />
	<field name="prr2_10" descr="" access="RO" offset="0x10.2" size="0x0.5" />
	<field name="prr2_9" descr="" access="RO" offset="0x10.9" size="0x0.6" />
	<field name="prr2_8" descr="" access="RO" offset="0x10.18" size="0x0.6" />
	<field name="prr2_7" descr="" access="RO" offset="0x10.26" size="0x0.6" />
	<field name="prr2_m7" descr="" access="RO" offset="0x14.0" size="0x0.6" />
	<field name="prr2_m6" descr="" access="RO" offset="0x14.8" size="0x0.7" />
	<field name="prr2_12" descr="" access="RO" offset="0x14.19" size="0x0.5" />
	<field name="prr2_11" descr="" access="RO" offset="0x14.27" size="0x0.5" />
	<field name="prr3_5" descr="" access="RO" offset="0x18.0" size="0x0.6" />
	<field name="prr3_4" descr="" access="RO" offset="0x18.6" size="0x0.4" />
	<field name="prr3_3" descr="" access="RO" offset="0x18.11" size="0x0.6" />
	<field name="prr3_2" descr="" access="RO" offset="0x18.17" size="0x0.4" />
	<field name="prr3_1" descr="" access="RO" offset="0x18.22" size="0x0.6" />
	<field name="prr3_0" descr="" access="RO" offset="0x18.28" size="0x0.4" />
	<field name="prr3_11" descr="" access="RO" offset="0x1c.0" size="0x0.6" />
	<field name="prr3_10" descr="" access="RO" offset="0x1c.6" size="0x0.4" />
	<field name="prr3_9" descr="" access="RO" offset="0x1c.11" size="0x0.6" />
	<field name="prr3_8" descr="" access="RO" offset="0x1c.17" size="0x0.4" />
	<field name="prr3_7" descr="" access="RO" offset="0x1c.22" size="0x0.6" />
	<field name="prr3_6" descr="" access="RO" offset="0x1c.28" size="0x0.4" />
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
	<field name="prr3_31" descr="" access="RO" offset="0x2c.0" size="0x0.6" />
	<field name="prr3_30" descr="" access="RO" offset="0x2c.6" size="0x0.4" />
	<field name="prr4_0" descr="" access="RO" offset="0x2c.11" size="0x0.10" />
	<field name="prr4_1" descr="" access="RO" offset="0x2c.22" size="0x0.10" />
	<field name="prr4_2" descr="" access="RO" offset="0x30.0" size="0x0.10" />
	<field name="prr4_3" descr="" access="RO" offset="0x30.11" size="0x0.10" />
	<field name="prr4_4" descr="" access="RO" offset="0x30.22" size="0x0.10" />
	<field name="prr4_5" descr="" access="RO" offset="0x34.0" size="0x0.10" />
	<field name="prr4_6" descr="" access="RO" offset="0x34.11" size="0x0.10" />
	<field name="prr4_7" descr="" access="RO" offset="0x34.22" size="0x0.10" />
	<field name="prr5_0" descr="" access="RO" offset="0x38.22" size="0x0.10" />
	<field name="prr5_1" descr="" access="RO" offset="0x3c.0" size="0x0.10" />
	<field name="prr5_2" descr="" access="RO" offset="0x3c.11" size="0x0.10" />
	<field name="prr5_3" descr="" access="RO" offset="0x3c.22" size="0x0.10" />
	<field name="prr5_4" descr="" access="RO" offset="0x40.0" size="0x0.10" />
	<field name="prr5_5" descr="" access="RO" offset="0x40.11" size="0x0.10" />
	<field name="prr5_6" descr="" access="RO" offset="0x40.22" size="0x0.10" />
	<field name="prr5_7" descr="" access="RO" offset="0x44.0" size="0x0.10" />
	<field name="prr5_8" descr="" access="RO" offset="0x44.11" size="0x0.10" />
	<field name="prr5_9" descr="" access="RO" offset="0x44.22" size="0x0.10" />
	<field name="prr5_10" descr="" access="RO" offset="0x48.0" size="0x0.10" />
	<field name="prr5_11" descr="" access="RO" offset="0x48.11" size="0x0.10" />
	<field name="prr5_12" descr="" access="RO" offset="0x48.22" size="0x0.10" />
	<field name="prr6_0" descr="" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="prr1_6" descr="" access="RO" offset="0x54.0" size="0x0.4" />
	<field name="prr1_5" descr="" access="RO" offset="0x54.6" size="0x0.4" />
	<field name="prr1_4" descr="" access="RO" offset="0x54.12" size="0x0.4" />
	<field name="prr1_3" descr="" access="RO" offset="0x54.18" size="0x0.4" />
</node>

<node name="slprr_Extended_read_7_5_ext" descr="" size="0x5c.0" >
	<field name="prr18_3" descr="" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="prr18_2" descr="" access="RO" offset="0x0.17" size="0x0.5" />
	<field name="prr18_1" descr="" access="RO" offset="0x0.24" size="0x0.2" />
	<field name="prr18_0" descr="" access="RO" offset="0x0.29" size="0x0.3" />
	<field name="prr12_m3" descr="" access="RO" offset="0x4.3" size="0x0.8" />
	<field name="prr12_m2" descr="" access="RO" offset="0x4.13" size="0x0.8" />
	<field name="prr12_m1" descr="" access="RO" offset="0x4.23" size="0x0.9" />
	<field name="prr12_2" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="prr12_1" descr="" access="RO" offset="0x8.9" size="0x0.8" />
	<field name="prr12_m5" descr="" access="RO" offset="0x8.17" size="0x0.7" />
	<field name="prr12_m4" descr="" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="prr12_6" descr="" access="RO" offset="0xc.1" size="0x0.6" />
	<field name="prr12_5" descr="" access="RO" offset="0xc.8" size="0x0.7" />
	<field name="prr12_4" descr="" access="RO" offset="0xc.17" size="0x0.7" />
	<field name="prr12_3" descr="" access="RO" offset="0xc.25" size="0x0.7" />
	<field name="prr12_10" descr="" access="RO" offset="0x10.2" size="0x0.5" />
	<field name="prr12_9" descr="" access="RO" offset="0x10.9" size="0x0.6" />
	<field name="prr12_8" descr="" access="RO" offset="0x10.18" size="0x0.6" />
	<field name="prr12_7" descr="" access="RO" offset="0x10.26" size="0x0.6" />
	<field name="prr12_12" descr="" access="RO" offset="0x14.19" size="0x0.5" />
	<field name="prr12_11" descr="" access="RO" offset="0x14.27" size="0x0.5" />
	<field name="prr13_5" descr="" access="RO" offset="0x18.0" size="0x0.6" />
	<field name="prr13_4" descr="" access="RO" offset="0x18.6" size="0x0.4" />
	<field name="prr13_3" descr="" access="RO" offset="0x18.11" size="0x0.6" />
	<field name="prr13_2" descr="" access="RO" offset="0x18.17" size="0x0.4" />
	<field name="prr13_1" descr="" access="RO" offset="0x18.22" size="0x0.6" />
	<field name="prr13_0" descr="" access="RO" offset="0x18.28" size="0x0.4" />
	<field name="prr13_11" descr="" access="RO" offset="0x1c.0" size="0x0.6" />
	<field name="prr13_10" descr="" access="RO" offset="0x1c.6" size="0x0.4" />
	<field name="prr13_9" descr="" access="RO" offset="0x1c.11" size="0x0.6" />
	<field name="prr13_8" descr="" access="RO" offset="0x1c.17" size="0x0.4" />
	<field name="prr13_7" descr="" access="RO" offset="0x1c.22" size="0x0.6" />
	<field name="prr13_6" descr="" access="RO" offset="0x1c.28" size="0x0.4" />
	<field name="prr13_17" descr="" access="RO" offset="0x20.0" size="0x0.6" />
	<field name="prr13_16" descr="" access="RO" offset="0x20.6" size="0x0.4" />
	<field name="prr13_15" descr="" access="RO" offset="0x20.11" size="0x0.6" />
	<field name="prr13_14" descr="" access="RO" offset="0x20.17" size="0x0.4" />
	<field name="prr13_13" descr="" access="RO" offset="0x20.22" size="0x0.6" />
	<field name="prr13_12" descr="" access="RO" offset="0x20.28" size="0x0.4" />
	<field name="prr13_23" descr="" access="RO" offset="0x24.0" size="0x0.6" />
	<field name="prr13_22" descr="" access="RO" offset="0x24.6" size="0x0.4" />
	<field name="prr13_21" descr="" access="RO" offset="0x24.11" size="0x0.6" />
	<field name="prr13_20" descr="" access="RO" offset="0x24.17" size="0x0.4" />
	<field name="prr13_19" descr="" access="RO" offset="0x24.22" size="0x0.6" />
	<field name="prr13_18" descr="" access="RO" offset="0x24.28" size="0x0.4" />
	<field name="prr13_29" descr="" access="RO" offset="0x28.0" size="0x0.6" />
	<field name="prr13_28" descr="" access="RO" offset="0x28.6" size="0x0.4" />
	<field name="prr13_27" descr="" access="RO" offset="0x28.11" size="0x0.6" />
	<field name="prr13_26" descr="" access="RO" offset="0x28.17" size="0x0.4" />
	<field name="prr13_25" descr="" access="RO" offset="0x28.22" size="0x0.6" />
	<field name="prr13_24" descr="" access="RO" offset="0x28.28" size="0x0.4" />
	<field name="prr13_31" descr="" access="RO" offset="0x2c.0" size="0x0.6" />
	<field name="prr13_30" descr="" access="RO" offset="0x2c.6" size="0x0.4" />
	<field name="prr14_0" descr="" access="RO" offset="0x2c.11" size="0x0.10" />
	<field name="prr14_1" descr="" access="RO" offset="0x2c.22" size="0x0.10" />
	<field name="prr14_2" descr="" access="RO" offset="0x30.0" size="0x0.10" />
	<field name="prr14_3" descr="" access="RO" offset="0x30.11" size="0x0.10" />
	<field name="prr14_4" descr="" access="RO" offset="0x30.22" size="0x0.10" />
	<field name="prr14_5" descr="" access="RO" offset="0x34.0" size="0x0.10" />
	<field name="prr14_6" descr="" access="RO" offset="0x34.11" size="0x0.10" />
	<field name="prr14_7" descr="" access="RO" offset="0x34.22" size="0x0.10" />
	<field name="prr15_0" descr="" access="RO" offset="0x38.22" size="0x0.10" />
	<field name="prr15_1" descr="" access="RO" offset="0x3c.0" size="0x0.10" />
	<field name="prr15_2" descr="" access="RO" offset="0x3c.11" size="0x0.10" />
	<field name="prr15_3" descr="" access="RO" offset="0x3c.22" size="0x0.10" />
	<field name="prr15_4" descr="" access="RO" offset="0x40.0" size="0x0.10" />
	<field name="prr15_5" descr="" access="RO" offset="0x40.11" size="0x0.10" />
	<field name="prr15_6" descr="" access="RO" offset="0x40.22" size="0x0.10" />
	<field name="prr15_7" descr="" access="RO" offset="0x44.0" size="0x0.10" />
	<field name="prr15_8" descr="" access="RO" offset="0x44.11" size="0x0.10" />
	<field name="prr15_9" descr="" access="RO" offset="0x44.22" size="0x0.10" />
	<field name="prr15_10" descr="" access="RO" offset="0x48.0" size="0x0.10" />
	<field name="prr15_11" descr="" access="RO" offset="0x48.11" size="0x0.10" />
	<field name="prr15_12" descr="" access="RO" offset="0x48.22" size="0x0.10" />
	<field name="prr16_0" descr="" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="prr18_7" descr="" access="RO" offset="0x50.0" size="0x0.4" />
	<field name="prr18_6" descr="" access="RO" offset="0x50.6" size="0x0.4" />
	<field name="prr18_5" descr="" access="RO" offset="0x50.12" size="0x0.4" />
	<field name="prr18_4" descr="" access="RO" offset="0x50.18" size="0x0.4" />
	<field name="prr12_16" descr="" access="RO" offset="0x54.0" size="0x0.4" />
	<field name="prr12_15" descr="" access="RO" offset="0x54.6" size="0x0.4" />
	<field name="prr12_14" descr="" access="RO" offset="0x54.12" size="0x0.4" />
	<field name="prr12_13" descr="" access="RO" offset="0x54.18" size="0x0.4" />
	<field name="prr12_20" descr="" access="RO" offset="0x58.0" size="0x0.3" />
	<field name="prr12_19" descr="" access="RO" offset="0x58.5" size="0x0.4" />
	<field name="prr12_18" descr="" access="RO" offset="0x58.11" size="0x0.6" />
	<field name="prr12_17" descr="" access="RO" offset="0x58.19" size="0x0.7" />
</node>

<node name="slprr_Extended_read_7_ext" descr="" size="0x58.0" >
	<field name="prr6_1" descr="" access="RO" offset="0x0.0" size="0x0.1" />
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
	<field name="prr2_6" descr="" access="RO" offset="0xc.1" size="0x0.6" />
	<field name="prr2_5" descr="" access="RO" offset="0xc.8" size="0x0.7" />
	<field name="prr2_4" descr="" access="RO" offset="0xc.17" size="0x0.7" />
	<field name="prr2_3" descr="" access="RO" offset="0xc.25" size="0x0.7" />
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
	<field name="prr3_11" descr="" access="RO" offset="0x1c.0" size="0x0.6" />
	<field name="prr3_10" descr="" access="RO" offset="0x1c.6" size="0x0.4" />
	<field name="prr3_9" descr="" access="RO" offset="0x1c.11" size="0x0.6" />
	<field name="prr3_8" descr="" access="RO" offset="0x1c.17" size="0x0.4" />
	<field name="prr3_7" descr="" access="RO" offset="0x1c.22" size="0x0.6" />
	<field name="prr3_6" descr="" access="RO" offset="0x1c.28" size="0x0.4" />
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
	<field name="prr3_31" descr="" access="RO" offset="0x2c.0" size="0x0.6" />
	<field name="prr3_30" descr="" access="RO" offset="0x2c.6" size="0x0.4" />
	<field name="prr4_0" descr="" access="RO" offset="0x2c.11" size="0x0.10" />
	<field name="prr4_1" descr="" access="RO" offset="0x2c.22" size="0x0.10" />
	<field name="prr4_2" descr="" access="RO" offset="0x30.0" size="0x0.10" />
	<field name="prr4_3" descr="" access="RO" offset="0x30.11" size="0x0.10" />
	<field name="prr4_4" descr="" access="RO" offset="0x30.22" size="0x0.10" />
	<field name="prr4_5" descr="" access="RO" offset="0x34.0" size="0x0.10" />
	<field name="prr4_6" descr="" access="RO" offset="0x34.11" size="0x0.10" />
	<field name="prr4_7" descr="" access="RO" offset="0x34.22" size="0x0.10" />
	<field name="prr5_0" descr="" access="RO" offset="0x38.22" size="0x0.10" />
	<field name="prr5_1" descr="" access="RO" offset="0x3c.0" size="0x0.10" />
	<field name="prr5_2" descr="" access="RO" offset="0x3c.11" size="0x0.10" />
	<field name="prr5_3" descr="" access="RO" offset="0x3c.22" size="0x0.10" />
	<field name="prr5_4" descr="" access="RO" offset="0x40.0" size="0x0.10" />
	<field name="prr5_5" descr="" access="RO" offset="0x40.11" size="0x0.10" />
	<field name="prr5_6" descr="" access="RO" offset="0x40.22" size="0x0.10" />
	<field name="prr5_7" descr="" access="RO" offset="0x44.0" size="0x0.10" />
	<field name="prr5_8" descr="" access="RO" offset="0x44.11" size="0x0.10" />
	<field name="prr5_9" descr="" access="RO" offset="0x44.22" size="0x0.10" />
	<field name="prr5_10" descr="" access="RO" offset="0x48.0" size="0x0.10" />
	<field name="prr5_11" descr="" access="RO" offset="0x48.11" size="0x0.10" />
	<field name="prr5_12" descr="" access="RO" offset="0x48.22" size="0x0.10" />
	<field name="prr6_0" descr="" access="RO" offset="0x4c.0" size="0x4.0" />
	<field name="prr1_6" descr="" access="RO" offset="0x54.0" size="0x0.4" />
	<field name="prr1_5" descr="" access="RO" offset="0x54.6" size="0x0.4" />
	<field name="prr1_4" descr="" access="RO" offset="0x54.12" size="0x0.4" />
	<field name="prr1_3" descr="" access="RO" offset="0x54.18" size="0x0.4" />
</node>

<node name="slprr_Extended_read_8_ext" descr="" size="0x10.0" >
	<field name="prr11_exist" descr="" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="prr10_exist" descr="" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="prr9_exist" descr="" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="prr8_exist" descr="" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="prr7_exist" descr="" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="prr8_2" descr="" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="prr8_1" descr="" access="RO" offset="0x4.8" size="0x0.1" />
	<field name="prr8_0" descr="" access="RO" offset="0x4.9" size="0x0.3" />
	<field name="prr7_2" descr="" access="RO" offset="0x4.14" size="0x0.2" />
	<field name="prr7_1" descr="" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="prr7_0" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="prr9_3" descr="" access="RO" offset="0x8.9" size="0x0.8" />
	<field name="prr9_2" descr="" access="RO" offset="0x8.17" size="0x0.6" />
	<field name="prr9_1" descr="" access="RO" offset="0x8.23" size="0x0.7" />
	<field name="prr9_0" descr="" access="RO" offset="0x8.30" size="0x0.2" />
	<field name="prr11_1" descr="" access="RO" offset="0xc.11" size="0x0.7" />
	<field name="prr11_0" descr="" access="RO" offset="0xc.18" size="0x0.4" />
	<field name="prr10_2" descr="" access="RO" offset="0xc.23" size="0x0.3" />
	<field name="prr10_1" descr="" access="RO" offset="0xc.26" size="0x0.3" />
	<field name="prr10_0" descr="" access="RO" offset="0xc.29" size="0x0.3" />
</node>

<node name="slprr_data_read_0_ext" descr="" size="0x140.0" >
	<field name="dword_0" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_10_ext" descr="" size="0x140.0" >
	<field name="dword_0" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_11_ext" descr="" size="0x140.0" >
	<field name="dword_80" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_12_ext" descr="" size="0x140.0" >
	<field name="dword_160" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_13_ext" descr="" size="0x140.0" >
	<field name="dword_240" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_14_ext" descr="" size="0x140.0" >
	<field name="dword_320" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_15_ext" descr="" size="0x140.0" >
	<field name="dword_400" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_16_ext" descr="" size="0x80.0" >
	<field name="dword_480" descr="Data in DWORDS of stored measured data." access="RO" high_bound="31" low_bound="0" offset="0x0.0" size="0x80.0" />
</node>

<node name="slprr_data_read_1_ext" descr="" size="0x140.0" >
	<field name="dword_80" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_2_ext" descr="" size="0x140.0" >
	<field name="dword_160" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_3_ext" descr="" size="0x140.0" >
	<field name="dword_240" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_4_ext" descr="" size="0x140.0" >
	<field name="dword_320" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_5_ext" descr="" size="0x140.0" >
	<field name="dword_400" descr="Data in DWORDS of stored measured data." access="RO" high_bound="79" low_bound="0" offset="0x0.0" size="0x140.0" />
</node>

<node name="slprr_data_read_6_ext" descr="" size="0x80.0" >
	<field name="dword_480" descr="Data in DWORDS of stored measured data." access="RO" high_bound="31" low_bound="0" offset="0x0.0" size="0x80.0" />
</node>

<node name="slprr_reg_ext" descr="" attr_required_tlvs="index:s" size="0x150.0" >
	<field name="status" descr="0: no_measurement_enabled1: measurement_in_progress2: measurement_done3: measurement_errorNote - only 1 measurement at a time can be done." access="RO" enum="no_measurement_enabled=0x0,measurement_in_progress=0x1,measurement_done=0x2,measurement_error=0x3" offset="0x0.0" size="0x0.3" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0 - Network Port1 - Near-End Port (For Retimer/Gearbox - Host side)3 - Far-End Port (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number to access" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number / DataPath number for Retimer1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.10" />
	<field name="deallocate_memory" descr="For NIC only (CX-9).When set, triggers release of previously allocated shared memory upon\;completion of the user operation.0 - do noting1 - release memory" access="WO" offset="0x0.28" size="0x0.1" />
	<field name="mode_b_idx" descr="0: mode_a 1: mode_b" access="RO" enum="mode_a=0x0,mode_b=0x1" offset="0x0.29" size="0x0.1" />
	<field name="stop_measure" descr="0: do nothing1:Stop measure" access="WO" offset="0x0.30" size="0x0.1" />
	<field name="start_measure" descr="0: do nothing1: Enable measurementNote: The measurement is destructive, once done, the link can’t be used\;and need to restart" access="WO" offset="0x0.31" size="0x0.1" />
	<field name="meas_type" descr="Measurement type parameters:0: Data_address_read_01: Data_address_read_12: Data_address_read_23: Data_address_read_34: Data_address_read_45: Data_address_read_56: Data_address_read_67: Extended_read_7 - 8: Extended_read_810: Data_address_read_10 -\;11: Data_address_read_11 12: Data_address_read_12 13: Data_address_read_13 14: Data_address_read_14 15: Data_address_read_15 16: Data_address_read_16 17: Extended_read_7_5 -\;18: Extended_read_7_1 -" access="INDEX" enum="Data_address_read_0=0x0,Data_address_read_1=0x1,Data_address_read_2=0x2,Data_address_read_3=0x3,Data_address_read_4=0x4,Data_address_read_5=0x5,Data_address_read_6=0x6,Extended_read_7=0x7,Extended_read_8=0x8,Data_address_read_10=0xa,Data_address_read_11=0xb,Data_address_read_12=0xc,Data_address_read_13=0xd,Data_address_read_14=0xe,Data_address_read_15=0xf,Data_address_read_16=0x10,Extended_read_7_5=0x11,Extended_read_7_1=0x12" offset="0x4.0" size="0x0.8" />
	<field name="timestamp_0" descr="Time stamp 16 MSB" access="RO" offset="0x4.10" size="0x0.16" />
	<field name="version" descr="5: prod_5nm - (Uphy 7.0)6: serdes_gen_87: prod_3nm_serdes_gen_7p5" access="RO" enum="prod_5nm=0x5,serdes_gen_8=0x6,prod_3nm_serdes_gen_7p5=0x7" offset="0x4.28" size="0x0.4" />
	<field name="timestamp_1" descr="Time stamp 16 LSB" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="temperature" descr="Temperature." access="RO" offset="0x8.22" size="0x0.10" />
	<field name="start_offset" descr="" access="RO" offset="0xc.0" size="0x0.10" />
	<field name="end_offset" descr="" access="RO" offset="0xc.12" size="0x0.10" />
	<field name="meas_width" descr="Bitmask - which lanes will be recorded. Default 0 = single lane (the lane\;is selected by the lane field). When meas_width is non-zero (multi-lane\;recording), the lane field must be set to 0." access="RW" offset="0xc.24" size="0x0.4" />
	<field name="width_cap" descr="Bitmask - how many and which lanes can be recorded in parallel.\;0 = single lane." access="RO" offset="0xc.28" size="0x0.4" />
	<field name="meas_data" descr="SLPRR Data Address Read 0 LayoutSLPRR Data Address Read 1 LayoutSLPRR Data Address Read 2 LayoutSLPRR Data Address Read 3 LayoutSLPRR Data Address Read 4 LayoutSLPRR Data Address Read 5 LayoutSLPRR Data Address Read 6 LayoutSLPRR Extended read 7 LayoutSLPRR Extended read 8 LayoutSLPRR Data Address Read 10 LayoutSLPRR Data Address Read 11 LayoutSLPRR Data Address Read 12 LayoutSLPRR Data Address Read 13 LayoutSLPRR Data Address Read 14 LayoutSLPRR Data Address Read 15 LayoutSLPRR Data Address Read 16 LayoutSLPRR Extended read 7_5 LayoutSLPRR Extended read 7_1 Layout" subnode="slprr_reg_meas_data_auto_ext" access="RW" offset="0x10.0" size="0x140.0" union_selector="$(parent).meas_type" />
</node>

<node name="slprr_reg_meas_data_auto_ext" descr="" attr_is_union="1" size="0x140.0" >
	<field name="slprr_Extended_read_7_1_ext" descr="" subnode="slprr_Extended_read_7_1_ext" access="RW" offset="0x0.0" selected_by="Extended_read_7_1" size="0x58.0" />
	<field name="slprr_Extended_read_7_5_ext" descr="" subnode="slprr_Extended_read_7_5_ext" access="RW" offset="0x0.0" selected_by="Extended_read_7_5" size="0x5c.0" />
	<field name="slprr_Extended_read_7_ext" descr="" subnode="slprr_Extended_read_7_ext" access="RW" offset="0x0.0" selected_by="Extended_read_7" size="0x58.0" />
	<field name="slprr_Extended_read_8_ext" descr="" subnode="slprr_Extended_read_8_ext" access="RW" offset="0x0.0" selected_by="Extended_read_8" size="0x10.0" />
	<field name="slprr_data_read_0_ext" descr="" subnode="slprr_data_read_0_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_0" size="0x140.0" />
	<field name="slprr_data_read_10_ext" descr="" subnode="slprr_data_read_10_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_10" size="0x140.0" />
	<field name="slprr_data_read_11_ext" descr="" subnode="slprr_data_read_11_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_11" size="0x140.0" />
	<field name="slprr_data_read_12_ext" descr="" subnode="slprr_data_read_12_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_12" size="0x140.0" />
	<field name="slprr_data_read_13_ext" descr="" subnode="slprr_data_read_13_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_13" size="0x140.0" />
	<field name="slprr_data_read_14_ext" descr="" subnode="slprr_data_read_14_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_14" size="0x140.0" />
	<field name="slprr_data_read_15_ext" descr="" subnode="slprr_data_read_15_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_15" size="0x140.0" />
	<field name="slprr_data_read_16_ext" descr="" subnode="slprr_data_read_16_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_16" size="0x80.0" />
	<field name="slprr_data_read_1_ext" descr="" subnode="slprr_data_read_1_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_1" size="0x140.0" />
	<field name="slprr_data_read_2_ext" descr="" subnode="slprr_data_read_2_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_2" size="0x140.0" />
	<field name="slprr_data_read_3_ext" descr="" subnode="slprr_data_read_3_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_3" size="0x140.0" />
	<field name="slprr_data_read_4_ext" descr="" subnode="slprr_data_read_4_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_4" size="0x140.0" />
	<field name="slprr_data_read_5_ext" descr="" subnode="slprr_data_read_5_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_5" size="0x140.0" />
	<field name="slprr_data_read_6_ext" descr="" subnode="slprr_data_read_6_ext" access="RW" offset="0x0.0" selected_by="Data_address_read_6" size="0x80.0" />
</node>

<node name="slrg_16nm_ext" descr="" size="0x24.0" >
	<field name="grade_lane_speed" descr="The lane speed on which the grade was measured:0 - SDR / PCIe Gen 11 - DDR / PCIe Gen 22 - QDR / PCIe Gen 33 - FDR10 (10GE / 40GE)4 - FDR (56GE) / PCIe Gen 45 - EDR (25GE / 50GE / 100GE) / PCIe Gen 56 - HDR (50GE / 200GE / 400GE)7- 9 - reserved10 - 1GE11 - 2.5GE (XAUI)12 - 50GE-KR413 - 15 - reserved" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="grade" descr="The grade that the lane received based on a specific configuration." access="RO" offset="0x4.0" size="0x0.24" />
	<field name="grade_version" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="height_eo_neg_up" descr="Voltage offset from eye center to the negative side of the upper eye.\;Only applicable for PAM4 signal." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="height_eo_pos_up" descr="Voltage offset from eye center to the positive side of the upper eye.Only applicable for PAM4 signal." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="height_eo_pos_mid" descr="Voltage offset from eye center to the positive side of the middle eye." access="RO" offset="0xc.0" size="0x0.16" />
	<field name="phase_eo_neg_up" descr="The offset from the eye center to the negative (left) side of the upper\;eye. Only applicable for PAM4 signal." access="RO" offset="0xc.16" size="0x0.8" />
	<field name="phase_eo_pos_up" descr="The offset from the eye center to the positive (right) side of the upper\;eye. Only applicable for PAM4 signal." access="RO" offset="0xc.24" size="0x0.8" />
	<field name="phase_eo_neg_mid" descr="The offset from the eye center to the negative (left) side of the middle\;eye." access="RO" offset="0x10.0" size="0x0.8" />
	<field name="phase_eo_pos_mid" descr="The offset from the eye center to the positive (right) side of the\;middle eye." access="RO" offset="0x10.8" size="0x0.8" />
	<field name="height_eo_neg_mid" descr="Voltage offset from eye center to the negative side of the middle eye." access="RO" offset="0x10.16" size="0x0.16" />
	<field name="height_eo_neg_low" descr="Voltage offset from eye center to the negative side of the lower eye.\;Only applicable for PAM4 signal." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="height_eo_pos_low" descr="Voltage offset from eye center to the positive side of the lower eye.\;Only applicable for PAM4 signal." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="phase_eo_neg_low" descr="The offset from the eye center to the negative (left) side of the lower\;eye. Only applicable for PAM4 signal." access="RO" offset="0x18.16" size="0x0.8" />
	<field name="phase_eo_pos_low" descr="The offset from the eye center to the positive (right) side of the lower\;eye. Only applicable for PAM4 signal." access="RO" offset="0x18.24" size="0x0.8" />
	<field name="up_eye_grade" descr="upper eye grade" access="RO" offset="0x1c.0" size="0x0.16" />
	<field name="mid_eye_grade" descr="middle eye grade" access="RO" offset="0x1c.16" size="0x0.16" />
	<field name="dn_eye_grade" descr="lower eye grade" access="RO" offset="0x20.0" size="0x0.16" />
</node>

<node name="slrg_40nm_28nm_ext" descr="" size="0x24.0" >
	<field name="grade_lane_speed" descr="The lane speed on which the grade was measured:0 - SDR1 - DDR2 - QDR3 - FDR10 (10GE / 40GE)4 - FDR (56GE)5 - EDR (25GE / 50GE / 100GE)6 - 9 - reserved10 - 1GE11 - 2.5GE (XAUI)12 - 50GE-KR413 - 15 - reserved" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="time_to_link_up" descr="The time that took took to bring up the link in msec." access="RO" offset="0x0.16" size="0x0.16" />
	<field name="grade" descr="" access="RO" offset="0x4.0" size="0x0.24" />
	<field name="grade_version" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="height_eo_neg" descr="Voltage offset from eye center to the negative side." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="height_eo_pos" descr="Voltage offset from eye center to the positive side." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="phase_eo_neg" descr="The offset from the eye center to the negative side." access="RO" offset="0x1c.0" size="0x0.16" />
	<field name="phase_eo_pos" descr="The offset from the eye center to the positive side." access="RO" offset="0x1c.16" size="0x0.16" />
</node>

<node name="slrg_5nm_ext" descr="" size="0x18.0" >
	<field name="fom_measurement" descr="Bitmask for measurement activationBit 0 - Upper eyeBit 1 - Middle eyeBit 2 - Lower eyeBit 3- Composite eyeNote: NRZ only Bit 3 is valid" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="initial_fom" descr="measured EOM status after FEQ.valid only when SLRG.status is ‘1’" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="fom_mode" descr="fom mode:FOM eye mode to search0x0: FOM_MODE_EYE_OPEN0x1: FOM_MODE_EYEO_SNR0x2: FOM_MODE_NORM_SNR0x3: FOM_MODE_EYE_LVLN0x4: FOM_MODE_EYE_LVLP0x5: FOM_MODE_THRES_NERR0x6: FOM_MODE_CDR_NERR0x7: FOM_MODE_CSDET_NERR0x8: FOM_MODE_MLSE_NERR0x9: FOM_MODE_SFEC_NERR" access="RW" enum="FOM_MODE_EYE_OPEN=0x0,FOM_MODE_EYEO_SNR=0x1,FOM_MODE_NORM_SNR=0x2,FOM_MODE_EYE_LVLN=0x3,FOM_MODE_EYE_LVLP=0x4,FOM_MODE_THRES_NERR=0x5,FOM_MODE_CDR_NERR=0x6,FOM_MODE_CSDET_NERR=0x7,FOM_MODE_MLSE_NERR=0x8,FOM_MODE_SFEC_NERR=0x9" offset="0x4.16" size="0x0.4" />
	<field name="fom_meas_type_read" descr="Indicate if the fom_measurement is of PAM4 or NRZ data0 - PAM4 (Upper, mid, low eye)1 - NRZ (Composite eye)" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="upper_eye" descr="last measured EOM-FOM status of upper eye.valid only if fom_measurement bit ‘0’ is set" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="last_fom" descr="last measured EOM-FOM status of composite eye.valid only if fom_measurement bit ‘3’ is set" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="lower_eye" descr="last measured EOM-FOM status of lower eye.valid only if fom_measurement bit ‘2’ is set" access="RO" offset="0xc.0" size="0x0.16" />
	<field name="mid_eye" descr="last measured EOM-FOM status of middle eye.valid only if fom_measurement bit ‘1’ is set" access="RO" offset="0xc.16" size="0x0.16" />
</node>

<node name="slrg_7nm_ext" descr="" size="0x18.0" >
	<field name="fom_measurement" descr="Bitmask for measurement activationBit 0 - Upper eyeBit 1 - Middle eyeBit 2 - Lower eyeBit 3- Composite eyeNote: NRZ only Bit 3 is valid" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="initial_fom" descr="measured EOM status after FEQ.valid only when SLRG.status is ‘1’" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="fom_mode" descr="fom mode:FOM eye mode to search0x0: FOM_MODE_EYEC0x1: FOM_MODE_EYEO0x2: FOM_MODE_EYEM0x3: FOM_MODE_BER0x4: FOM_MODE_EYEC_VN0x5: FOM_MODE_EYEC_VP0x6: FOM_MODE_EYEM_VN0x7: FOM_MODE_EYEM_VP" access="RW" enum="FOM_MODE_EYEC=0x0,FOM_MODE_EYEO=0x1,FOM_MODE_EYEM=0x2,FOM_MODE_BER=0x3,FOM_MODE_EYEC_VN=0x4,FOM_MODE_EYEC_VP=0x5,FOM_MODE_EYEM_VN=0x6,FOM_MODE_EYEM_VP=0x7" offset="0x4.16" size="0x0.3" />
	<field name="fom_meas_type_read" descr="Indicate if the fom_measurement is of PAM4 or NRZ data0 - PAM4 (Upper, mid, low eye)1 - NRZ (Composite eye)" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="lower_eye" descr="last measured EOM-FOM status of lower eye.valid only if fom_measurement bit ‘2’ is set" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="mid_eye" descr="last measured EOM-FOM status of middle eye.valid only if fom_measurement bit ‘1’ is set" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="upper_eye" descr="last measured EOM-FOM status of upper eye.valid only if fom_measurement bit ‘0’ is set" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="last_fom" descr="last measured EOM-FOM status of composite eye.valid only if fom_measurement bit ‘3’ is set" access="RO" offset="0x8.24" size="0x0.8" />
</node>

<node name="slrg_all_lanes_5nm_ext" descr="" size="0x14.0" >
	<field name="fom_mode" descr="FOM type measurement.0: SNR - bit scale of 1/256 dB.The SNR value represents the electrical signal-to-noise ratio on an\;optical lane, and is defined as the minimum of the three individual eye\;SNR values.Returned SNR value is based on definition in CMIS spec." access="OP" offset="0x0.0" size="0x0.4" />
	<field name="fom_averaging_override_admin" descr="Valid only if fom_averaging_cap is set. When set allows overriding\;averaging configuration of FOM.0: do_nothing1: override_value" access="WO" offset="0x0.5" size="0x0.1" />
	<field name="fom_averaging_cap" descr="When set, Indicates averaging is supported for the measurement chosen in\;fom_mode. This can be used to stabilize returned values.The averaging capability is only relevant for periodic fom measurements,\;meaning the value in fom_update_period for the chosen fom is not zero." access="RO" offset="0x0.6" size="0x0.1" />
	<field name="fom_averaging_en" descr="Field is ignored if fom_averaging_override_admin equals ‘0’.Determines if returned measurement chosen in fom_mode will be a\;calculated average of previous measurements, or the latest single\;measurement of the chosen fom. Number of averaged measurements is set in\;fom_averaging_window.0: Latest measurement1: Averaged measurement" access="RW" offset="0x0.7" size="0x0.1" />
	<field name="fom_averaging_window" descr="Field is ignored if fom_averaging_override_admin equals ‘0’.Configures the number of measurements that will be averaged to calculate\;the returned fom measurement. Averaging window size will be\;&lt;fom_averaging_window&gt;+1." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="fom_update_period" descr="Returns the time period in which a new fom measurement will be available\;periodically, according to the measurement chosen in fom_mode. Value is\;in units of 1 [msec].If the value equals to ‘0’, the fom is on demand only, and a measurement\;will not occur unless requested." access="RO" offset="0x0.16" size="0x0.16" />
	<field name="fom_lane1" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="fom_lane0" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="fom_lane3" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="fom_lane2" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="fom_lane5" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0xc.0" size="0x0.16" />
	<field name="fom_lane4" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0xc.16" size="0x0.16" />
	<field name="fom_lane7" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="fom_lane6" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x10.16" size="0x0.16" />
</node>

<node name="slrg_reg_ext" descr="" attr_required_tlvs="index:s" size="0x28.0" >
	<field name="all_lanes" descr="Set 1 for all lanes measurement page. For Retimer, will conduct\;measurement on all active lanes under the chosen side - Host / Line.Supported if PCAM.feature_cap_mask bit 91 is set.Mutually exclusive with measurements_thresholds index. Only one of\;measurements_thresholds index and all_lanes index can be set to ‘1’\;at the same time.Relevant only for 5nm.0: per_lane_measurement1: all_lane_measurement" access="INDEX" enum="per_lane_measurement=0x0,all_lane_measurement=0x1" offset="0x0.1" size="0x0.1" />
	<field name="measurements_thresholds" descr="Set 1 for measurements thresholds page.Supported if PCAM.feature_cap_mask bit 126 is set.Mutually exclusive with all_lanes index. Only one of\;measurements_thresholds index and all_lanes index can be set to ‘1’ at\;the same time.Relevant only for 5nm.0: measurements_page1: measurements_threshold_page" access="INDEX" enum="measurements_page=0x0,measurements_threshold_page=0x1" offset="0x0.2" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0: Network_Port1: NearEnd_Port - (For Retimer/Gearbox - Host side)2: Internal_IC_LR_Port3: FarEnd_Port - (For Retimer/Gearbox - Line side) -\;Other values are reserved." access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3,Main_Die_to_Die=0x4" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type.0 - Local port number1 - IB port number3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: prod_40nm1: prod_28nm3: prod_16nm4: prod_7nm5: prod_5nm - (SerDes Gen7.0/ 7.5)6: serdes_gen_8" access="RO" enum="prod_40nm=0x0,prod_28nm=0x1,prod_16nm=0x3,prod_7nm=0x4,prod_5nm=0x5,serdes_gen_8=0x6" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid1 - Valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="SLRG - SerDes Lane Receive Grade Register Layout for 40nm and 28nm\;SLRG - SerDes Lane Receive Grade Register Layout for 16nm\;SLRG - SerDes Lane Receive Grade Register Layout for 7nm\;SLRG - SerDes Lane Receive Grade Register Layout for 5nm\;SLRG all lanes FOM for 5nm- Layout\;SLRG - SerDes Lane Receive Grade Register Layout for Serdes_gen_8\;SLRG Measurements Thresholds for 5nm- Layout" subnode="slrg_reg_page_data_auto_ext" access="RO" condition="$(parent).port_type AND $(parent).version AND $(parent).all_lanes AND $(parent).measurements_thresholds" offset="0x4.0" size="0x24.0" />
</node>

<node name="slrg_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x24.0" >
	<field name="slrg_16nm_ext" descr="" subnode="slrg_16nm_ext" access="RW" condition="($(parent).port_type == Network_Port AND ($(parent).version == prod_16nm))" offset="0x0.0" size="0x24.0" />
	<field name="slrg_40nm_28nm_ext" descr="" subnode="slrg_40nm_28nm_ext" access="RW" condition="($(parent).port_type == Network_Port AND ($(parent).version == prod_40nm | $(parent).version == prod_28nm))" offset="0x0.0" size="0x24.0" />
	<field name="slrg_5nm_ext" descr="" subnode="slrg_5nm_ext" access="RW" condition="(($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm AND $(parent).all_lanes == per_lane_measurement AND $(parent).measurements_thresholds == measurements_page))" offset="0x0.0" size="0x18.0" />
	<field name="slrg_7nm_ext" descr="" subnode="slrg_7nm_ext" access="RW" condition="(($(parent).port_type == Network_Port | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_7nm))" offset="0x0.0" size="0x18.0" />
	<field name="slrg_all_lanes_5nm_ext" descr="" subnode="slrg_all_lanes_5nm_ext" access="RW" condition="(($(parent).port_type == Network_Port || $(parent).port_type == NearEnd_Port  || $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm AND $(parent).all_lanes == all_lane_measurement AND $(parent).measurements_thresholds == measurements_page))" offset="0x0.0" size="0x14.0" />
	<field name="slrg_serdes_gen_8_ext" descr="" subnode="slrg_serdes_gen_8_ext" access="RW" condition="(($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == serdes_gen_8))" offset="0x0.0" size="0x18.0" />
	<field name="slrg_thresholds_5nm_ext" descr="" subnode="slrg_thresholds_5nm_ext" access="RW" condition="(($(parent).port_type == Network_Port || $(parent).port_type == NearEnd_Port  || $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm AND $(parent).all_lanes == per_lane_measurement AND $(parent).measurements_thresholds == measurements_threshold_page))" offset="0x0.0" size="0x14.0" />
</node>

<node name="slrg_serdes_gen_8_ext" descr="" size="0x18.0" >
	<field name="fom_measurement" descr="Bitmask for measurement activationBit 0 - Upper eyeBit 1 - Middle eyeBit 2 - Lower eyeBit 3- Composite eyeNote: NRZ only Bit 3 is valid" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="initial_fom" descr="measured EOM status after FEQ.valid only when SLRG.status is ‘1’" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="fom_mode" descr="fom mode:FOM eye mode to search0x0: FOM_MODE_EYE_OPEN0x1: FOM_MODE_EYEO_SNR0x2: FOM_MODE_NORM_SNR0x3: FOM_MODE_EYE_LVLN0x4: FOM_MODE_EYE_LVLP0x5: FOM_MODE_THRES_NERR0x6: FOM_MODE_CDR_NERR0x7: FOM_MODE_CSDET_NERR0x8: FOM_MODE_MLSE_NERR0x9: FOM_MODE_SFEC_NERR" access="RW" enum="FOM_MODE_EYE_OPEN=0x0,FOM_MODE_EYEO_SNR=0x1,FOM_MODE_NORM_SNR=0x2,FOM_MODE_EYE_LVLN=0x3,FOM_MODE_EYE_LVLP=0x4,FOM_MODE_THRES_NERR=0x5,FOM_MODE_CDR_NERR=0x6,FOM_MODE_CSDET_NERR=0x7,FOM_MODE_MLSE_NERR=0x8,FOM_MODE_SFEC_NERR=0x9" offset="0x4.16" size="0x0.4" />
	<field name="fom_meas_type_read" descr="Indicate if the fom_measurement is of PAM4 or NRZ data0 - PAM4 (Upper, mid, low eye)1 - NRZ (Composite eye)" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="upper_eye" descr="last measured EOM-FOM status of upper eye.valid only if fom_measurement bit ‘0’ is set" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="last_fom" descr="last measured EOM-FOM status of composite eye.valid only if fom_measurement bit ‘3’ is set" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="lower_eye" descr="last measured EOM-FOM status of lower eye.valid only if fom_measurement bit ‘2’ is set" access="RO" offset="0xc.0" size="0x0.16" />
	<field name="mid_eye" descr="last measured EOM-FOM status of middle eye.valid only if fom_measurement bit ‘1’ is set" access="RO" offset="0xc.16" size="0x0.16" />
</node>

<node name="slrg_thresholds_5nm_ext" descr="" size="0x14.0" >
	<field name="snr_thresholds_valid" descr="When set SNR alarm and warning threshold fields are valid0: not_valid1: valid" access="RO" enum="not_valid=0x0,valid=0x1" offset="0x0.31" size="0x0.1" />
	<field name="snr_line_low_warning" descr="Line side warning threshold for SNR value. If SNR value goes below this\;value, it should be considered as a warning" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="snr_line_low_alarm" descr="Line side alarm threshold for SNR value. If SNR value goes below this\;value, it should be considered as an alarm" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="snr_host_low_warning" descr="Host side warning threshold for SNR value. If SNR value goes below this\;value, it should be considered as a warning" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="snr_host_low_alarm" descr="Host side alarm threshold for SNR value. If SNR value goes below this\;value, it should be considered as an alarm" access="RO" offset="0x8.16" size="0x0.16" />
</node>

<node name="slsir_5nm_ext" descr="" size="0x24.0" >
	<field name="uphy_ver_minor" descr="(see above)" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="uphy_ver_major" descr="UPHY version" access="RO" offset="0x20.4" size="0x0.4" />
	<field name="bkv_minor_dln" descr="(see above)" access="RO" offset="0x20.16" size="0x0.4" />
	<field name="bkv_major_dln" descr="BKV dln version" access="RO" offset="0x20.20" size="0x0.4" />
	<field name="bkv_minor_cln" descr="(see above)" access="RO" offset="0x20.24" size="0x0.4" />
	<field name="bkv_major_cln" descr="BKV cln version" access="RO" offset="0x20.28" size="0x0.4" />
</node>

<node name="slsir_7nm_ext" descr="" size="0x90.0" >
	<field name="uphy_rev_minor" descr="(see above)" access="RO" offset="0x18.0" size="0x0.4" />
	<field name="uphy_rev_major" descr="UPHY revision" access="RO" offset="0x18.4" size="0x0.4" />
	<field name="bkv_revision_rx" descr="DLN RX BKV revisionFor UPHY Rev 6.* and 7.* the format of BKV revision isBits 7:4 - MajorBits 3:0 - Minor" access="RO" offset="0x18.8" size="0x0.8" />
	<field name="bkv_revision_cln" descr="CLN BKV revisionFor UPHY Rev 6.* and 7.* the format of BKV revision isBits 7:4 - MajorBits 3:0 - Minor" access="RO" offset="0x18.16" size="0x0.8" />
	<field name="uphy_rev_subminor" descr="UPHY subminor revision.when 0, indicates no subminor revision" access="RO" offset="0x18.24" size="0x0.4" />
</node>

<node name="slsir_reg_ext" descr="" attr_required_tlvs="index:s" size="0x94.0" >
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0 - Network Port1 - Near-End Port (For Retimer/Gearbox - Host side)2 - internal IC LR Port3 - Far-End Port (For Retimer/Gearbox - Line side)4 - USR Main5 - USR TileOther values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="4: prod_7nm - 5: prod_5nm - (Uphy 7.0/ 7.5)6: serdes_gen_8" access="RO" enum="prod_7nm=0x4,prod_5nm=0x5,serdes_gen_8=0x6" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - invalid1 - valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="SLSIR - SerDes Lane Status Info Register Layout for 7nmSLSIR - SerDes Lane Status Info Register Layout for 5nmSLSIR - SerDes Lane Status Info Register Layout for Serdes_gen_8" subnode="slsir_reg_page_data_auto_ext" access="RW" offset="0x4.0" size="0x90.0" union_selector="$(parent).version" />
</node>

<node name="slsir_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x90.0" >
	<field name="slsir_5nm_ext" descr="" subnode="slsir_5nm_ext" access="RW" offset="0x0.0" selected_by="prod_5nm" size="0x24.0" />
	<field name="slsir_7nm_ext" descr="" subnode="slsir_7nm_ext" access="RW" offset="0x0.0" selected_by="prod_7nm" size="0x90.0" />
	<field name="slsir_serdes_gen_8_ext" descr="" subnode="slsir_serdes_gen_8_ext" access="RW" offset="0x0.0" selected_by="serdes_gen_8" size="0x24.0" />
</node>

<node name="slsir_serdes_gen_8_ext" descr="" size="0x24.0" >
	<field name="uphy_ver_minor" descr="(see above)" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="uphy_ver_major" descr="UPHY version" access="RO" offset="0x20.4" size="0x0.4" />
	<field name="bkv_minor_dln" descr="(see above)" access="RO" offset="0x20.16" size="0x0.4" />
	<field name="bkv_major_dln" descr="BKV dln version" access="RO" offset="0x20.20" size="0x0.4" />
	<field name="bkv_minor_cln" descr="(see above)" access="RO" offset="0x20.24" size="0x0.4" />
	<field name="bkv_major_cln" descr="BKV cln version" access="RO" offset="0x20.28" size="0x0.4" />
</node>

<node name="sltp_16nm_ext" descr="" size="0x48.0" >
	<field name="post_tap" descr="(see above)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="main_tap" descr="(see above)" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="pre_tap" descr="(see above)" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="pre_2_tap" descr="Value of each tap is between -96 to 96NOTE: The total sum of all absolute taps values should be 96 or smaller." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="ob_alev_out" descr="Output common mode. Values can be set in the range of (0-30)" access="RW" offset="0x8.0" size="0x0.5" />
	<field name="ob_amp" descr="Output amplitude. Values can be set in the range of (10-100)." access="RW" offset="0x8.8" size="0x0.7" />
	<field name="ob_m2lp" descr="MSB to LSB proportion.Values can be set between -10 to 50.MSB emphasis achieved when value is between -10 to -1LSB emphasis achieved when value is between 1 to 50.When set to 0 - equal proportion." access="RW" offset="0x8.25" size="0x0.7" />
	<field name="ob_bad_stat" descr="Bitmask for bad ‘set’ status:0: configuration_warning - taps values can’t be set to SerDes due to\;internal limitations. Actual TX configuration is modify internally\;with the same sum of taps weight.11: Illegal_ob_combination - ob_m2lp, ob_amp and ob_alev is in legal\;range each, but the total combination can’t be set to SerDes due to\;internal limitations, the Set command is ignored.12: Illegal_ob_m2lp13: Illegal_ob_amp14: Illegal_ob_alev_out15: Illegal_tapsBit 12-0 - Reserved /Unknown" access="RO" enum="configuration_warning=0x0,Illegal_ob_combination=0xb,Illegal_ob_m2lp=0xc,Illegal_ob_amp=0xd,Illegal_ob_alev_out=0xe,Illegal_taps=0xf" offset="0xc.16" size="0x0.16" />
	<field name="regp_bfm1n" descr="Values can be set in the range of (0-200)." access="RW" offset="0x10.0" size="0x0.8" />
	<field name="regn_bfm1p" descr="Values can be set in the range of (0-200)." access="RW" offset="0x10.8" size="0x0.8" />
	<field name="obnlev" descr="Values can be set in the range of (0-200)." access="RW" offset="0x10.16" size="0x0.8" />
	<field name="obplev" descr="Values can be set in the range of (0-200)." access="RW" offset="0x10.24" size="0x0.8" />
</node>

<node name="sltp_28nm_40nm_ext" descr="" size="0x48.0" >
	<field name="ob_tap2" descr="(see above)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ob_tap1" descr="(see above)" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="ob_tap0" descr="" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="polarity" descr="Tx lane polarity" access="RW" offset="0x4.24" size="0x0.1" />
	<field name="ob_bias" descr="" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="ob_reg" descr="(ref_txcml100_reg)" access="RW" offset="0x8.8" size="0x0.8" />
	<field name="ob_preemp_mode" descr="Concatenation of taps polarity + preemp_sel" access="RW" offset="0x8.16" size="0x0.4" />
	<field name="ob_leva" descr="" access="RW" offset="0x8.20" size="0x0.4" />
	<field name="ob_bad_stat" descr="Bitmask for bad SET status:Bit 0 - Illegal ob_bais valueBit 1 - Illegal ob taps polarity (distance between taps)" access="RO" offset="0xc.29" size="0x0.2" />
	<field name="ob_norm" descr="OB Normalization status:0 - No Normalization was done1 - Normalization performed" access="RO" offset="0xc.31" size="0x0.1" />
</node>

<node name="sltp_5nm_ext" descr="" size="0x48.0" >
	<field name="ob_bad_stat" descr="Bitmask for bad ‘set’ status:Bit 0: tap0_is_out_of_rangeBit 1: tap1_is_out_of_rangeBit 2: tap2_is_out_of_rangeBit 3: tap3_is_out_of_rangeBit 4: tap4_is_out_of_rangeBit 5: tap5_is_out_of_rangeBit 6: tap6_is_out_of_rangeBit 7: tap7_is_out_of_rangeBit 8: tap8_is_out_of_rangeBit 9: tap9_is_out_of_rangeBit 10: tap10_is_out_of_rangeBit 11: tap11_is_out_of_rangeBit 12: sum_of_taps_is_out_of_range" access="RO" enum="tap0_is_out_of_range=0x1,tap1_is_out_of_range=0x2,tap2_is_out_of_range=0x4,tap3_is_out_of_range=0x8,tap4_is_out_of_range=0x10,tap5_is_out_of_range=0x20,tap6_is_out_of_range=0x40,tap7_is_out_of_range=0x80,tap8_is_out_of_range=0x100,tap9_is_out_of_range=0x200,tap10_is_out_of_range=0x400,tap11_is_out_of_range=0x800,sum_of_taps_is_out_of_range=0x1000" offset="0x0.0" size="0x0.16" />
	<field name="lt_preset_sel" descr="Valid only when lt_preset_sel_cap is set, otherwise ignored0: no_preset_selected - changes Tx DB according to cable1-7: LT_index_preset_select - Tx will get / set LT preset" access="RW" offset="0x0.24" size="0x0.3" />
	<field name="vs_peer_db" descr="relevant for when c_db is set, else field is ignored.for when direct drive module connected:0 - db to override is for Did vs Did1 - db to override if for Did vs retimed module" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="lt_preset_sel_cap" descr="When set, lt_preset_sel field is valid." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="no_db_set" descr="supported only if PCAM bit 96 in feature_cap_mask is set.When set, Tx DB will not be written into HW on linkup phase.When cleared, Tx DB is written into HW on linkup phase." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="tap0" descr="(see above)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="tap1" descr="(see above)" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="tap2" descr="(see above)" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="tap3" descr="Signed value for TX FIR taps.tap scaling = fir_tap/63.Taps value must be under the following rules:taps [0-1, 6-11] valid ranges are [-8,8]And Also:|tap0| + | tap1| &lt;8|tap6| + | tap7| + | tap8|&lt;8|tap9| + | tap10| + | tap11| &lt;8taps [2-5] valid ranges are [-63, 63]Tap mapping for uphy 7 and 7.5:Tap1- pre3Tap2 -pre2Tap3- pre1Tap4 -MainTap5- Post1For PAM4 links need to guarantee that the sum of the coefficient\;magnitude equals sum |c(i)| ≤ 63.For NRZ links must guarantee sum|c(i)| = 63Note: Configured taps may get effective value of +/-1 from the value\;that has been set." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="tap4" descr="(see above)" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="tap5" descr="(see above)" access="RW" offset="0x8.8" size="0x0.8" />
	<field name="tap6" descr="(see above)" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="tap7" descr="(see above)" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="tap8" descr="(see above)" access="RW" offset="0xc.0" size="0x0.8" />
	<field name="tap9" descr="(see above)" access="RW" offset="0xc.8" size="0x0.8" />
	<field name="tap10" descr="(see above)" access="RW" offset="0xc.16" size="0x0.8" />
	<field name="tap11" descr="(see above)" access="RW" offset="0xc.24" size="0x0.8" />
	<field name="drv_amp" descr="High speed output driver amplitude settings, default = 6’d63.Amplitude scaling = (drv_amp+1)/64It should be noted there are two limitations for changing drv_amp in\;5nm:1) The value can be configured if only taps 2-5 are being used. If any\;other taps are being used (0-1,6-11), meaning they have a non-zero\;value, drv_amp will be ignored, and set to default value.2) Setting to any value other then the default one will reduce the valid\;ranges of taps 2-5. The maximum valid range is [-63,63] when drv_amp =\;6’d63. If drv_amp=X, then the valid range will be [-X,X]." access="RW" offset="0x10.26" size="0x0.6" />
	<field name="gen_speed" descr="only applicable for out of band/PCI portsthis field defines the speed for local and remote preset fields0 - current speed link speed1 - Gen3 speed2 - Gen4 speed3 - Gen5 speed4 - Gen6 speedothers - reserved" access="INDEX" offset="0x14.0" size="0x0.4" />
	<field name="local_preset" descr="only applicable for out of band/PCI portsif local_preset_valid is set this field holds the local preset for the\;gen_speedelse - reserved" access="RO" offset="0x14.8" size="0x0.4" />
	<field name="local_preset_valid" descr="only applicable for out of band/PCI portswhen set the local preset field is valid" access="RO" offset="0x14.15" size="0x0.1" />
	<field name="remote_preset" descr="only applicable for out of band/PCI portsif remote_preset_valid is set this field holds the remote preset for the\;gen_speedelse - reserved" access="RO" offset="0x14.16" size="0x0.4" />
	<field name="remote_preset_valid" descr="only applicable for out of band/PCI portswhen set the remote preset field is valid" access="RO" offset="0x14.23" size="0x0.1" />
	<field name="get_main_location" descr="Indicates the current index of the Main tap during a read operation." access="RO" offset="0x14.29" size="0x0.1" />
	<field name="set_main_location" descr="Indicates the current index of the Main tap during a read operation." access="WO" offset="0x14.30" size="0x0.1" />
</node>

<node name="sltp_7nm_ext" descr="" size="0x48.0" >
	<field name="fir_pre2" descr="(see above)" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="fir_pre3" descr="Signed value for TX FIR taps.tap scaling = fir_tap/63.for 100G per lane 5 taps,for 50G per lane 4 taps are used (no pre3),or 25G per lane 3 taps are used (no pre3,pre2)Valid values for taps:fir_main [34,63]fir_pre1 [-23,0]fir_pre2 [0,8]fir_pre3 [-5,0]fir_post1 [-21,0]Need to guarantee that the sum of the coefficient magnitude equals sum\;|c(i)| ≤ 63.NRZ speeds must guarantee sum|c(i)| = 63Note: Configured taps may get effective value of +/-1 from the value\;that has been set." access="RW" offset="0x0.8" size="0x0.8" />
	<field name="ob_bad_stat" descr="Bitmask for bad ‘set’ status:Bit 0: pre3_is_out_of_rangeBit 1: pre2_is_out_of_rangeBit 2: pre1_is_out_of_rangeBit 3: main_tap_is_out_of_rangeBit 4: post1_is_out_of_rangeBit 5: sum_of_taps_is_out_of_rangeBit 6: taps_not_alinged_with_speed" access="RO" enum="pre3_is_out_of_range=0x1,pre2_is_out_of_range=0x2,pre1_is_out_of_range=0x4,main_tap_is_out_of_range=0x8,post1_is_out_of_range=0x10,sum_of_taps_is_out_of_range=0x20,taps_not_alinged_with_speed=0x40" offset="0x0.16" size="0x0.8" />
	<field name="drv_amp" descr="High speed output driver amplitude settings, default = 6’d63.amplitude scaling = (AMP+1) / 64" access="RW" offset="0x0.24" size="0x0.6" />
	<field name="gen_speed" descr="only applicable for out of band/PCI portsthis field defines the speed for local and remote preset fields0 - current speed link speed1 - Gen3 speed2 - Gen4 speed3 - Gen5 speed4 - Gen6 speedothers - reserved" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="fir_post1" descr="(see above)" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="fir_main" descr="(see above)" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="fir_pre1" descr="(see above)" access="RW" offset="0x4.24" size="0x0.8" />
	<field name="local_preset" descr="only applicable for out of band/PCI portsif local_preset_valid is set this field holds the local preset for the\;gen_speedelse - reserved" access="RO" offset="0x8.0" size="0x0.4" />
	<field name="local_preset_valid" descr="only applicable for out of band/PCI portswhen set the local preset field is valid" access="RO" offset="0x8.7" size="0x0.1" />
	<field name="remote_preset" descr="only applicable for out of band/PCI portsif remote_preset_valid is set this field holds the remote preset for the\;gen_speedelse - reserved" access="RO" offset="0x8.8" size="0x0.4" />
	<field name="remote_preset_valid" descr="only applicable for out of band/PCI portswhen set the remote preset field is valid" access="RO" offset="0x8.15" size="0x0.1" />
</node>

<node name="sltp_lut_7nm_ext" descr="" size="0x48.0" >
	<field name="fir_pre2" descr="(see above)" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="fir_pre3" descr="Signed value for TX FIR taps.tap scaling = fir_tap/63.Valid values for taps:fir_pre2 [0,8]fir_pre3 [-5,0]" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="ob_bad_stat" descr="Bitmask for bad ‘set’ status:Bit 0: pre3_is_out_of_rangeBit 1: pre2_is_out_of_rangeBit 7: LUT_value_is_out_of_range" access="RO" enum="pre3_is_out_of_range=0x1,pre2_is_out_of_range=0x2,LUT_value_is_out_of_range=0x80" offset="0x0.16" size="0x0.8" />
	<field name="drv_amp" descr="High speed output driver amplitude settings, default = 6’d63.amplitude scaling = (AMP+1) / 64" access="RW" offset="0x0.24" size="0x0.6" />
	<field name="lut0" descr="(see above)" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="lut1" descr="(see above)" access="RW" offset="0x8.8" size="0x0.8" />
	<field name="lut2" descr="(see above)" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="lut3" descr="Lookup Table values per entry" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lut4" descr="(see above)" access="RW" offset="0xc.0" size="0x0.8" />
	<field name="lut5" descr="(see above)" access="RW" offset="0xc.8" size="0x0.8" />
	<field name="lut6" descr="(see above)" access="RW" offset="0xc.16" size="0x0.8" />
	<field name="lut7" descr="(see above)" access="RW" offset="0xc.24" size="0x0.8" />
	<field name="lut8" descr="(see above)" access="RW" offset="0x10.0" size="0x0.8" />
	<field name="lut9" descr="(see above)" access="RW" offset="0x10.8" size="0x0.8" />
	<field name="lut10" descr="(see above)" access="RW" offset="0x10.16" size="0x0.8" />
	<field name="lut11" descr="(see above)" access="RW" offset="0x10.24" size="0x0.8" />
	<field name="lut12" descr="(see above)" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="lut13" descr="(see above)" access="RW" offset="0x14.8" size="0x0.8" />
	<field name="lut14" descr="(see above)" access="RW" offset="0x14.16" size="0x0.8" />
	<field name="lut15" descr="(see above)" access="RW" offset="0x14.24" size="0x0.8" />
	<field name="lut16" descr="(see above)" access="RW" offset="0x18.0" size="0x0.8" />
	<field name="lut17" descr="(see above)" access="RW" offset="0x18.8" size="0x0.8" />
	<field name="lut18" descr="(see above)" access="RW" offset="0x18.16" size="0x0.8" />
	<field name="lut19" descr="Lookup Table values per entry" access="RW" offset="0x18.24" size="0x0.8" />
	<field name="lut20" descr="(see above)" access="RW" offset="0x1c.0" size="0x0.8" />
	<field name="lut21" descr="(see above)" access="RW" offset="0x1c.8" size="0x0.8" />
	<field name="lut22" descr="(see above)" access="RW" offset="0x1c.16" size="0x0.8" />
	<field name="lut23" descr="(see above)" access="RW" offset="0x1c.24" size="0x0.8" />
	<field name="lut24" descr="(see above)" access="RW" offset="0x20.0" size="0x0.8" />
	<field name="lut25" descr="(see above)" access="RW" offset="0x20.8" size="0x0.8" />
	<field name="lut26" descr="(see above)" access="RW" offset="0x20.16" size="0x0.8" />
	<field name="lut27" descr="(see above)" access="RW" offset="0x20.24" size="0x0.8" />
	<field name="lut28" descr="(see above)" access="RW" offset="0x24.0" size="0x0.8" />
	<field name="lut29" descr="(see above)" access="RW" offset="0x24.8" size="0x0.8" />
	<field name="lut30" descr="(see above)" access="RW" offset="0x24.16" size="0x0.8" />
	<field name="lut31" descr="(see above)" access="RW" offset="0x24.24" size="0x0.8" />
	<field name="lut32" descr="(see above)" access="RW" offset="0x28.0" size="0x0.8" />
	<field name="lut33" descr="(see above)" access="RW" offset="0x28.8" size="0x0.8" />
	<field name="lut34" descr="(see above)" access="RW" offset="0x28.16" size="0x0.8" />
	<field name="lut35" descr="(see above)" access="RW" offset="0x28.24" size="0x0.8" />
	<field name="lut36" descr="(see above)" access="RW" offset="0x2c.0" size="0x0.8" />
	<field name="lut37" descr="(see above)" access="RW" offset="0x2c.8" size="0x0.8" />
	<field name="lut38" descr="(see above)" access="RW" offset="0x2c.16" size="0x0.8" />
	<field name="lut39" descr="(see above)" access="RW" offset="0x2c.24" size="0x0.8" />
	<field name="lut40" descr="(see above)" access="RW" offset="0x30.0" size="0x0.8" />
	<field name="lut41" descr="(see above)" access="RW" offset="0x30.8" size="0x0.8" />
	<field name="lut42" descr="(see above)" access="RW" offset="0x30.16" size="0x0.8" />
	<field name="lut43" descr="(see above)" access="RW" offset="0x30.24" size="0x0.8" />
	<field name="lut44" descr="" access="RW" offset="0x34.0" size="0x0.8" />
	<field name="lut45" descr="(see above)" access="RW" offset="0x34.8" size="0x0.8" />
	<field name="lut46" descr="(see above)" access="RW" offset="0x34.16" size="0x0.8" />
	<field name="lut47" descr="(see above)" access="RW" offset="0x34.24" size="0x0.8" />
	<field name="lut48" descr="(see above)" access="RW" offset="0x38.0" size="0x0.8" />
	<field name="lut49" descr="(see above)" access="RW" offset="0x38.8" size="0x0.8" />
	<field name="lut50" descr="(see above)" access="RW" offset="0x38.16" size="0x0.8" />
	<field name="lut51" descr="Lookup Table values per entry" access="RW" offset="0x38.24" size="0x0.8" />
	<field name="lut52" descr="(see above)" access="RW" offset="0x3c.0" size="0x0.8" />
	<field name="lut53" descr="(see above)" access="RW" offset="0x3c.8" size="0x0.8" />
	<field name="lut54" descr="(see above)" access="RW" offset="0x3c.16" size="0x0.8" />
	<field name="lut55" descr="(see above)" access="RW" offset="0x3c.24" size="0x0.8" />
	<field name="lut56" descr="(see above)" access="RW" offset="0x40.0" size="0x0.8" />
	<field name="lut57" descr="(see above)" access="RW" offset="0x40.8" size="0x0.8" />
	<field name="lut58" descr="(see above)" access="RW" offset="0x40.16" size="0x0.8" />
	<field name="lut59" descr="(see above)" access="RW" offset="0x40.24" size="0x0.8" />
	<field name="lut60" descr="(see above)" access="RW" offset="0x44.0" size="0x0.8" />
	<field name="lut61" descr="(see above)" access="RW" offset="0x44.8" size="0x0.8" />
	<field name="lut62" descr="(see above)" access="RW" offset="0x44.16" size="0x0.8" />
	<field name="lut63" descr="(see above)" access="RW" offset="0x44.24" size="0x0.8" />
</node>

<node name="sltp_reg_ext" descr="" attr_required_tlvs="index:s" size="0x4c.0" >
	<field name="c_db" descr="copy transmitter parameters to Data Base." access="OP" offset="0x0.0" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0: Network_Port1: NearEnd_Port - (For Retimer/Gearbox - Host side)2: Internal_IC_LR_Port3: FarEnd_Port - (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3" offset="0x0.1" size="0x0.3" />
	<field name="lane_speed" descr="Reserved for PCIe.The lane speed for TX settings:0 - SDR / Gen1 (PCIe)1 - DDR / Gen2 (PCIe) / 5GBASE-R2 - QDR / Gen3 (PCIe)3 - FDR10 (10GE / 40GE)4 - FDR (56GE) / Gen4 (PCIe)5 - EDR (25GE / 50GE / 100GE) / Gen5 (PCIe)6 - HDR (50GE / 200GE / 400GE)7 - NDR /  100GE /\;200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)8 - XDR  /\;200G_1x (106.25 Gbd\;/ 212.5Gb/s)9 - Reserved10 - 1GE11 - 2.5GE (XAUI)12 - 50GE-KR413 - Reserved14 - \;400G_2x (100 Gbd /\;200Gb/s)15 - Reserved" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="conf_mod" descr="Set configuration mode for 7nm/5nm/3nm product.0: tx_linear - when set, tx taps are configured fromfor 7nm:SLTP - SerDes Lane Transmit Parameters Register Layout for 7nmFor 5nmSLTP - SerDes Lane Transmit Parameters Register Layout for 5nmFor 3nmSLTP - SerDes Lane Transmit Parameters Register Layout for 3nm_gen_7p5LUT table fields are ignored1: tx_lut - when set, tx taps are configured fromfor 7nm:SLTP - SerDes Lane Transmit Parameters Register Layout for LUT 7nm7nm_fir_taps page fields are ignored." access="OP" offset="0x0.12" size="0x0.1" />
	<field name="tx_policy" descr="Configures Tx parameter set policy0 - Tx parameters will be set according to best possible configuration\;chosen by the system1 - Tx parameters will be set according to Data Base only and will not\;be overridden by link training (e.g KR-Startup)Only supported when indicated by PCAM.ext_group0_features Bit 70:\;SLTP_tx_policy_supported" access="RW" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: prod_40nm1: prod_28nm3: prod_16nm4: prod_7nm5: prod_5nm - (UPHY 7.0/7.5)6: serdes_gen_87: prod_3nm_serdes_gen_7p5" access="RO" enum="prod_40nm=0x0,prod_28nm=0x1,prod_16nm=0x3,prod_7nm=0x4,prod_5nm=0x5,serdes_gen_8=0x6,prod_3nm_serdes_gen_7p5=0x7" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="Indicates that Tx setting readout is valid and active. In particular,for links that do AN/LT, valid will be set when link operational status\;is UP (PAOS.oper_status=0x1).For links without AN/LT, valid will be set when Tx is enabled.0 - Invalid1 - ValidNote: Get and Set operations can be set when status = invalid." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="page_data" descr="SLTP - SerDes Lane Transmit Parameters Register Layout for 28nm and 40nm\;SLTP - SerDes Lane Transmit Parameters Register Layout for 16nm\;SLTP - SerDes Lane Transmit Parameters Register Layout for 7nm\;SLTP - SerDes Lane Transmit Parameters Register Layout for LUT 7nm\;SLTP - SerDes Lane Transmit Parameters Register Layout for 5nm\;SLTP - SerDes Lane Transmit Parameters Register Layout for 3nm_gen_7p5\;SLTP - SerDes Lane Transmit Parameters Register Layout for Serdes_gen_8" subnode="sltp_reg_page_data_auto_ext" access="RW" condition="$(parent).port_type AND $(parent).version" offset="0x4.0" size="0x48.0" />
</node>

<node name="sltp_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x48.0" >
	<field name="prod_3nm_serdes_gen_7p5_ext" descr="" subnode="prod_3nm_serdes_gen_7p5_ext" access="RW" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_3nm_serdes_gen_7p5)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_16nm_ext" descr="" subnode="sltp_16nm_ext" access="RW" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version == prod_16nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_28nm_40nm_ext" descr="" subnode="sltp_28nm_40nm_ext" access="RW" condition="($(parent).port_type == Network_Port) AND ($(parent).version == prod_40nm | $(parent).version == prod_28nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_5nm_ext" descr="" subnode="sltp_5nm_ext" access="RW" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_7nm_ext" descr="" subnode="sltp_7nm_ext" access="RW" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version == prod_7nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_lut_7nm_ext" descr="" subnode="sltp_lut_7nm_ext" access="RW" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version == prod_7nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_serdes_gen_8_ext" descr="" subnode="sltp_serdes_gen_8_ext" access="RW" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version ==serdes_gen_8)" offset="0x0.0" size="0x48.0" />
</node>

<node name="sltp_serdes_gen_8_ext" descr="" size="0x48.0" >
	<field name="ob_bad_stat" descr="Bitmask for bad ‘set’ status:Bit 0: tap0_is_out_of_rangeBit 1: tap1_is_out_of_rangeBit 2: tap2_is_out_of_rangeBit 3: tap3_is_out_of_rangeBit 4: tap4_is_out_of_rangeBit 5: tap5_is_out_of_rangeBit 6: tap6_is_out_of_rangeBit 7: tap7_is_out_of_rangeBit 8: tap8_is_out_of_rangeBit 9: tap9_is_out_of_rangeBit 10: tap10_is_out_of_rangeBit 11: tap11_is_out_of_rangeBit 9: sum_of_taps_is_out_of_range" access="RO" enum="tap0_is_out_of_range=0x1,tap1_is_out_of_range=0x2,tap2_is_out_of_range=0x4,tap3_is_out_of_range=0x8,tap4_is_out_of_range=0x10,tap5_is_out_of_range=0x20,tap6_is_out_of_range=0x40,tap7_is_out_of_range=0x80,tap8_is_out_of_range=0x100,tap9_is_out_of_range=0x200,tap10_is_out_of_range=0x400,tap11_is_out_of_range=0x800,sum_of_taps_is_out_of_range=0x200" offset="0x0.0" size="0x0.16" />
	<field name="mode_b_idx" descr="0: mode_a 1: mode_b" access="RO" enum="mode_a=0x0,mode_b=0x1" offset="0x0.23" size="0x0.1" />
	<field name="lt_preset_sel" descr="Valid only when lt_preset_sel_cap is set, otherwise ignored0: no_preset_selected - changes Tx DB according to cable1-7: LT_index_preset_select - Tx will get / set LT preset" access="RW" offset="0x0.24" size="0x0.3" />
	<field name="vs_peer_db" descr="relevant for when c_db is set, else field is ignored.for when direct drive module connected:0 - db to override is for Did vs Did1 - db to override if for Did vs retimed module" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="lt_preset_sel_cap" descr="When set, lt_preset_sel field is valid." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="no_db_set" descr="supported only if PCAM bit 96 in feature_cap_mask is set.When set, Tx DB will not be written into HW on linkup phase.When cleared, Tx DB is written into HW on linkup phase." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="tap0" descr="(see above)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="tap1" descr="(see above)" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="tap2" descr="(see above)" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="tap3" descr="Signed value for TX FIR taps.tap scaling = fir_tap/63.Taps value must be under the following rules:taps [0-1, 6-11] valid ranges are [-8,8]And Also:|tap0| + | tap1| &lt;8|tap6| + | tap7| + | tap8|&lt;8|tap9| + | tap10| + | tap11| &lt;8taps [2-5] valid ranges are [-63, 63]For PAM4 links need to guarantee that the sum of the coefficient\;magnitude equals sum |c(i)| ≤ 63.For NRZ links must guarantee sum|c(i)| = 63Note: Configured taps may get effective value of +/-1 from the value\;that has been set." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="tap4" descr="(see above)" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="tap5" descr="(see above)" access="RW" offset="0x8.8" size="0x0.8" />
	<field name="tap6" descr="(see above)" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="tap7" descr="(see above)" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="tap8" descr="(see above)" access="RW" offset="0xc.0" size="0x0.8" />
	<field name="tap9" descr="(see above)" access="RW" offset="0xc.8" size="0x0.8" />
	<field name="tap10" descr="(see above)" access="RW" offset="0xc.16" size="0x0.8" />
	<field name="tap11" descr="(see above)" access="RW" offset="0xc.24" size="0x0.8" />
	<field name="drv_amp" descr="High speed output driver amplitude settings, default = 6’d63.Amplitude scaling = (drv_amp+1)/64It should be noted there are two limitations for changing drv_amp in\;5nm:1) The value can be configured if only taps 2-5 are being used. If any\;other taps are being used (0-1,6-11), meaning they have a non-zero\;value, drv_amp will be ignored, and set to default value.2) Setting to any value other then the default one will reduce the valid\;ranges of taps 2-5. The maximum valid range is [-63,63] when drv_amp =\;6’d63. If drv_amp=X, then the valid range will be [-X,X]." access="RW" offset="0x10.26" size="0x0.6" />
</node>

<node name="sltpv2_lut_5nm_ext" descr="" size="0x108.0" >
	<field name="ob_bad_stat" descr="Bitmask for bad ‘set’ status:Bit 0:LUT_value_is_out_of_rangeBit 1: delay_0_invalidBit 2: delay_1_invalidBit 3: delay_2_invalid" access="RO" enum="LUT_value_is_out_of_range=0x1,delay_0_invalid=0x2,delay_1_invalid=0x4,delay_2_invalid=0x8" offset="0x0.0" size="0x0.16" />
	<field name="lut_sel" descr="0: LUT_1 - taps 0-1 (16 entries), valid ranges per entry: [-16, 15]1: LUT_2 - taps 2-5 (256 entries), valid ranges per entry: [-64, 63]2: LUT_3 - taps 6-8 (64 entries), valid ranges per entry: [-16, 15]3: LUT_4 - taps 9-11 (64 entries), valid ranges per entry: [-16, 15]Note that only LUT_2 group has FW DB, hence c_db shall work only for\;LUT_2." access="INDEX" enum="LUT_1=0x0,LUT_2=0x1,LUT_3=0x2,LUT_4=0x3" offset="0x0.20" size="0x0.4" />
	<field name="vs_peer_db" descr="relevant for when c_db is set, else field is ignored.for when direct drive module connected:0 - db to override is for Did vs Did1 - db to override if for Did vs retimed module" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="no_db_set" descr="supported only if PCAM bit 96 in feature_cap_mask is set.When set, Tx DB will not be written into HW on linkup phase.When cleared, Tx DB is written into HW on linkup phase." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="delay0" descr="(see above)" access="RW" offset="0x4.0" size="0x0.6" />
	<field name="delay1" descr="(see above)" access="RW" offset="0x4.6" size="0x0.6" />
	<field name="delay2" descr="relevant for LUT3 (taps6-8), LUT4 (taps9-11). ignore otherwise.even taps (6, 8. 10) can get even valuesodd taps (7, 9, 11) cam get odd values." access="RW" offset="0x4.12" size="0x0.6" />
	<field name="lut" descr="Lookup Table values per entry" access="RW" high_bound="255" low_bound="0" offset="0x8.24" size="0x100.0" />
</node>

<node name="sltpv2_reg_ext" descr="" attr_required_tlvs="index:s" size="0x10c.0" >
	<field name="c_db" descr="Copy transmitter parameters to Data Base.When set, for get operation shall return Data Base valuesotherwise will be written to HW directly." access="OP" offset="0x0.0" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM0: Network_Port1: NearEnd_Port - (For Retimer/Gearbox - Host side)2: Internal_IC_LR_Port3: FarEnd_Port - (For Retimer/Gearbox - Line side)Other values are reserved." access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3" offset="0x0.1" size="0x0.3" />
	<field name="lane_speed" descr="Reserved for PCIe. Relevant only if c_db=1.The lane speed for TX settings:0 - SDR / Gen1 (PCIe)1 - DDR / Gen2 (PCIe) / 5GBASE-R2 - QDR / Gen3 (PCIe)3 - FDR10 (10GE / 40GE)4 - FDR (56GE) / Gen4 (PCIe)5 - EDR (25GE / 50GE / 100GE) / Gen5 (PCIe)6 - HDR (50GE / 200GE / 400GE)7 - NDR /  100GE /\;200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)8 - XDR  /\;200G_1x (106.25 Gbd\;/ 212.5Gb/s)9 - Reserved10 - 1GE11 - 2.5GE (XAUI)12 - 50GE-KR413 - Reserved14 - \;400G_2x (100 Gbd /\;200Gb/s)15 - Reserved" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="tx_policy" descr="Configures Tx parameter set policy0 - Tx parameters will be set according to best possible configuration\;chosen by the system1 - Tx parameters will be set according to Data Base only and will not\;be overridden by link training (e.g KR-Startup)Only supported when indicated by PCAM.ext_group1_features Bit 20:\;SLTPv2.tx_policy_supported" access="RW" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:0 - Local port number1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="5: prod_5nm6: serdes_gen_87: prod_3nm_serdes_gen_7p5" access="RO" enum="prod_5nm=0x5,serdes_gen_8=0x6,prod_3nm_serdes_gen_7p5=0x7" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="Indicates that Tx setting readout is valid and active. In particular,\;for links that do AN/LT, valid will be set when link operational status\;is UP (PAOS.oper_status=0x1).For links without AN/LT, valid will be set when Tx is enabled.0 - Invalid1 - ValidNote: Get and Set operations can be set when status = invalid." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="page_data" descr="SLTPv2 - SerDes Lane Transmit Parameters v2 Register Layout for LUT 5nm and 3nm\;SLTPv2 - SerDes Lane Transmit Parameters v2 Register Layout for LUT Serdes_gen_8" subnode="sltpv2_reg_page_data_auto_ext" access="RW" condition="$(parent).port_type AND $(parent).version" offset="0x4.0" size="0x108.0" />
</node>

<node name="sltpv2_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x108.0" >
	<field name="sltpv2_lut_5nm_ext" descr="" subnode="sltpv2_lut_5nm_ext" access="RW" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm | $(parent).version == prod_3nm_serdes_gen_7p5)" offset="0x0.0" size="0x108.0" />
	<field name="sltpv2_serdes_gen_8_ext" descr="" subnode="sltpv2_serdes_gen_8_ext" access="RW" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == serdes_gen_8)" offset="0x0.0" size="0x108.0" />
</node>

<node name="sltpv2_serdes_gen_8_ext" descr="" size="0x108.0" >
	<field name="ob_bad_stat" descr="Bitmask for bad ‘set’ status:Bit 0:LUT_value_is_out_of_rangeBit 1: delay_0_invalidBit 2: delay_1_invalidBit 3: delay_2_invalid" access="RO" enum="LUT_value_is_out_of_range=0x1,delay_0_invalid=0x2,delay_1_invalid=0x4,delay_2_invalid=0x8" offset="0x0.0" size="0x0.16" />
	<field name="lut_sel" descr="0: LUT_1 - taps 0-1 (16 entries), valid ranges per entry: [-16, 15]1: LUT_2 - taps 2-5 (256 entries), valid ranges per entry: [-64, 63]2: LUT_3 - taps 6-8 (64 entries), valid ranges per entry: [-16, 15]3: LUT_4 - taps 9-11 (64 entries), valid ranges per entry: [-16, 15]Note that only LUT_2 group has FW DB, hence c_db shall work only for\;LUT_2." access="INDEX" enum="LUT_1=0x0,LUT_2=0x1,LUT_3=0x2,LUT_4=0x3" offset="0x0.20" size="0x0.4" />
	<field name="mode_b_idx" descr="0: mode_a 1: mode_b" access="RO" enum="mode_a=0x0,mode_b=0x1" offset="0x0.27" size="0x0.1" />
	<field name="vs_peer_db" descr="relevant for when c_db is set, else field is ignored.for when direct drive module connected:0 - db to override is for Did vs Did1 - db to override if for Did vs retimed module" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="no_db_set" descr="supported only if PCAM bit 96 in feature_cap_mask is set.When set, Tx DB will not be written into HW on linkup phase.When cleared, Tx DB is written into HW on linkup phase." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="delay0" descr="(see above)" access="RW" offset="0x4.0" size="0x0.6" />
	<field name="delay1" descr="(see above)" access="RW" offset="0x4.6" size="0x0.6" />
	<field name="delay2" descr="relevant for LUT3 (taps6-8), LUT4 (taps9-11). ignore otherwise.even taps (6, 8. 10) can get even valuesodd taps (7, 9, 11) cam get odd values." access="RW" offset="0x4.12" size="0x0.6" />
	<field name="lut" descr="Lookup Table values per entry" access="RW" high_bound="255" low_bound="0" offset="0x8.24" size="0x100.0" />
</node>

<node name="sltr_cause_list_uphy7_5_ext" descr="" size="0x14.0" >
	<field name="p0csrg0_21" descr="" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="p0csrg0_22" descr="" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="p0csrg0_23" descr="" access="RO" offset="0x0.2" size="0x0.1" />
	<field name="p0csrg0_24" descr="" access="RO" offset="0x0.3" size="0x0.1" />
	<field name="p0csrg0_25" descr="" access="RO" offset="0x0.4" size="0x0.1" />
	<field name="p0csrg0_26" descr="" access="RO" offset="0x0.5" size="0x0.1" />
	<field name="p0csrg0_27" descr="" access="RO" offset="0x0.6" size="0x0.1" />
	<field name="p0csrg0_28" descr="" access="RO" offset="0x0.7" size="0x0.1" />
	<field name="p0csrg0_29" descr="" access="RO" offset="0x0.8" size="0x0.1" />
	<field name="p0csrg0_30" descr="" access="RO" offset="0x0.9" size="0x0.1" />
	<field name="p0csrg0_31" descr="" access="RO" offset="0x0.10" size="0x0.1" />
	<field name="p0csrg1_0" descr="" access="RO" offset="0x0.11" size="0x0.1" />
	<field name="p0csrg1_1" descr="" access="RO" offset="0x0.12" size="0x0.1" />
	<field name="p0csrg1_2" descr="" access="RO" offset="0x0.13" size="0x0.1" />
	<field name="p1csrg0_21" descr="" access="RO" offset="0x0.14" size="0x0.1" />
	<field name="p1csrg0_22" descr="" access="RO" offset="0x0.15" size="0x0.1" />
	<field name="p1csrg0_23" descr="" access="RO" offset="0x0.16" size="0x0.1" />
	<field name="p1csrg0_24" descr="" access="RO" offset="0x0.17" size="0x0.1" />
	<field name="p1csrg0_25" descr="" access="RO" offset="0x0.18" size="0x0.1" />
	<field name="p1csrg0_26" descr="" access="RO" offset="0x0.19" size="0x0.1" />
	<field name="p1csrg0_27" descr="" access="RO" offset="0x0.20" size="0x0.1" />
	<field name="p1csrg0_28" descr="" access="RO" offset="0x0.21" size="0x0.1" />
	<field name="p1csrg0_29" descr="" access="RO" offset="0x0.22" size="0x0.1" />
	<field name="p1csrg0_30" descr="" access="RO" offset="0x0.23" size="0x0.1" />
	<field name="p1csrg0_31" descr="" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="p1csrg1_0" descr="" access="RO" offset="0x0.25" size="0x0.1" />
	<field name="p1csrg1_1" descr="" access="RO" offset="0x0.26" size="0x0.1" />
	<field name="p1csrg1_2" descr="" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="lcsrg0_9" descr="" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="lcsrg1_5" descr="" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="lcsrg1_16" descr="" access="RO" offset="0x4.2" size="0x0.1" />
	<field name="lcsrg1_20" descr="" access="RO" offset="0x4.3" size="0x0.1" />
	<field name="lcsrg1_21" descr="" access="RO" offset="0x4.4" size="0x0.1" />
	<field name="lcsrg1_22" descr="" access="RO" offset="0x4.5" size="0x0.1" />
	<field name="lcsrg1_23" descr="" access="RO" offset="0x4.6" size="0x0.1" />
	<field name="lcsrg1_24" descr="" access="RO" offset="0x4.7" size="0x0.1" />
	<field name="lcsrg1_25" descr="" access="RO" offset="0x4.8" size="0x0.1" />
	<field name="lcsrg1_26" descr="" access="RO" offset="0x4.9" size="0x0.1" />
	<field name="lcsrg1_27" descr="" access="RO" offset="0x4.10" size="0x0.1" />
	<field name="lcsrg1_31" descr="" access="RO" offset="0x4.11" size="0x0.1" />
	<field name="lcsrg2_0" descr="" access="RO" offset="0x4.12" size="0x0.1" />
	<field name="lcsrg2_1" descr="" access="RO" offset="0x4.13" size="0x0.1" />
	<field name="lcsrg2_2" descr="" access="RO" offset="0x4.14" size="0x0.1" />
	<field name="lcsrg2_3" descr="" access="RO" offset="0x4.15" size="0x0.1" />
	<field name="lcsrg2_6" descr="" access="RO" offset="0x4.16" size="0x0.1" />
	<field name="lcsrg2_9" descr="" access="RO" offset="0x4.17" size="0x0.1" />
	<field name="lcsrg3_12" descr="" access="RO" offset="0x4.18" size="0x0.1" />
	<field name="lcsrg3_15" descr="" access="RO" offset="0x4.19" size="0x0.1" />
	<field name="lcsrg3_16" descr="" access="RO" offset="0x4.20" size="0x0.1" />
	<field name="lcsrg3_17" descr="" access="RO" offset="0x4.21" size="0x0.1" />
	<field name="lcsrg4_12" descr="" access="RO" offset="0x4.22" size="0x0.1" />
	<field name="lcsrg4_13" descr="" access="RO" offset="0x4.23" size="0x0.1" />
	<field name="lcsrg4_15" descr="" access="RO" offset="0x4.24" size="0x0.1" />
	<field name="lcsrg4_16" descr="" access="RO" offset="0x4.25" size="0x0.1" />
	<field name="lcsrg4_17" descr="" access="RO" offset="0x4.26" size="0x0.1" />
	<field name="lcsrg4_18" descr="" access="RO" offset="0x4.27" size="0x0.1" />
	<field name="lcsrg4_19" descr="" access="RO" offset="0x4.28" size="0x0.1" />
	<field name="lcsrg5_5" descr="" access="RO" offset="0x4.29" size="0x0.1" />
	<field name="lcsrg5_17" descr="" access="RO" offset="0x4.30" size="0x0.1" />
	<field name="lcsrg6_4" descr="" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="lcsrg6_10" descr="" access="RO" offset="0x8.0" size="0x0.1" />
	<field name="lcsrg6_11" descr="" access="RO" offset="0x8.1" size="0x0.1" />
	<field name="lcsrg6_12" descr="" access="RO" offset="0x8.2" size="0x0.1" />
	<field name="lcsrg6_13" descr="" access="RO" offset="0x8.3" size="0x0.1" />
	<field name="lcsrg6_14" descr="" access="RO" offset="0x8.4" size="0x0.1" />
	<field name="lcsrg6_15" descr="" access="RO" offset="0x8.5" size="0x0.1" />
	<field name="lcsrg6_16" descr="" access="RO" offset="0x8.6" size="0x0.1" />
	<field name="lcsrg6_17" descr="" access="RO" offset="0x8.7" size="0x0.1" />
	<field name="lcsrg6_18" descr="" access="RO" offset="0x8.8" size="0x0.1" />
	<field name="lcsrg6_24" descr="" access="RO" offset="0x8.9" size="0x0.1" />
	<field name="lcsrg6_27" descr="" access="RO" offset="0x8.10" size="0x0.1" />
	<field name="lcsrg6_28" descr="" access="RO" offset="0x8.11" size="0x0.1" />
	<field name="lcsrg6_29" descr="" access="RO" offset="0x8.12" size="0x0.1" />
	<field name="lcsrg6_30" descr="" access="RO" offset="0x8.13" size="0x0.1" />
	<field name="lcsrg6_31" descr="" access="RO" offset="0x8.14" size="0x0.1" />
	<field name="lcsrg7_0" descr="" access="RO" offset="0x8.15" size="0x0.1" />
	<field name="lcsrg7_1" descr="" access="RO" offset="0x8.16" size="0x0.1" />
	<field name="lcsrg7_2" descr="" access="RO" offset="0x8.17" size="0x0.1" />
	<field name="lcsrg7_3" descr="" access="RO" offset="0x8.18" size="0x0.1" />
	<field name="lcsrg7_4" descr="" access="RO" offset="0x8.19" size="0x0.1" />
	<field name="lcsrg7_5" descr="" access="RO" offset="0x8.20" size="0x0.1" />
	<field name="lcsrg7_6" descr="" access="RO" offset="0x8.21" size="0x0.1" />
	<field name="lcsrg7_7" descr="" access="RO" offset="0x8.22" size="0x0.1" />
	<field name="lcsrg7_8" descr="" access="RO" offset="0x8.23" size="0x0.1" />
	<field name="lcsrg7_9" descr="" access="RO" offset="0x8.24" size="0x0.1" />
	<field name="lcsrg7_12" descr="" access="RO" offset="0x8.25" size="0x0.1" />
	<field name="lcsrg7_15" descr="" access="RO" offset="0x8.26" size="0x0.1" />
	<field name="lcsrg7_18" descr="" access="RO" offset="0x8.27" size="0x0.1" />
	<field name="lcsrg7_19" descr="" access="RO" offset="0x8.28" size="0x0.1" />
	<field name="lcsrg10_4" descr="" access="RO" offset="0x8.29" size="0x0.1" />
	<field name="lcsrg10_7" descr="" access="RO" offset="0x8.30" size="0x0.1" />
	<field name="clear_on_read_executed" descr="" access="RO" offset="0xc.30" size="0x0.1" />
	<field name="status" descr="" access="RO" offset="0xc.31" size="0x0.1" />
	<field name="lcsrg2_12" descr="tx_sync_fifo_cause_sticky_dist_error" access="RO" offset="0x10.0" size="0x0.1" />
	<field name="lcsrg2_13" descr="tx_sync_fifo_cause_fsm_start" access="RO" offset="0x10.1" size="0x0.1" />
	<field name="lcsrg2_14" descr="tx_sync_fifo_cause_lock" access="RO" offset="0x10.2" size="0x0.1" />
	<field name="lcsrg2_15" descr="tx_sync_fifo_cause_lock_lost" access="RO" offset="0x10.3" size="0x0.1" />
	<field name="lcsrg2_16" descr="tx_sync_fifo_cause_bad_margin_op" access="RO" offset="0x10.4" size="0x0.1" />
	<field name="lcsrg2_17" descr="tx_sync_fifo_cause_bad_margin_antiphase" access="RO" offset="0x10.5" size="0x0.1" />
</node>

<node name="sltr_cause_list_uphy7_ext" descr="" size="0x10.0" >
	<field name="p0csrg0_21" descr="" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="p0csrg0_22" descr="" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="p0csrg0_23" descr="" access="RO" offset="0x0.2" size="0x0.1" />
	<field name="p0csrg0_24" descr="" access="RO" offset="0x0.3" size="0x0.1" />
	<field name="p0csrg0_25" descr="" access="RO" offset="0x0.4" size="0x0.1" />
	<field name="p0csrg0_26" descr="" access="RO" offset="0x0.5" size="0x0.1" />
	<field name="p0csrg0_27" descr="" access="RO" offset="0x0.6" size="0x0.1" />
	<field name="p0csrg0_28" descr="" access="RO" offset="0x0.7" size="0x0.1" />
	<field name="p1csrg0_21" descr="" access="RO" offset="0x0.8" size="0x0.1" />
	<field name="p1csrg0_22" descr="" access="RO" offset="0x0.9" size="0x0.1" />
	<field name="p1csrg0_23" descr="" access="RO" offset="0x0.10" size="0x0.1" />
	<field name="p1csrg0_24" descr="" access="RO" offset="0x0.11" size="0x0.1" />
	<field name="p1csrg0_25" descr="" access="RO" offset="0x0.12" size="0x0.1" />
	<field name="p1csrg0_26" descr="" access="RO" offset="0x0.13" size="0x0.1" />
	<field name="p1csrg0_27" descr="" access="RO" offset="0x0.14" size="0x0.1" />
	<field name="p1csrg0_28" descr="" access="RO" offset="0x0.15" size="0x0.1" />
	<field name="lcsrg0_4" descr="" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="lcsrg1_0" descr="" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="lcsrg1_1" descr="" access="RO" offset="0x4.2" size="0x0.1" />
	<field name="lcsrg1_2" descr="" access="RO" offset="0x4.3" size="0x0.1" />
	<field name="lcsrg1_4" descr="" access="RO" offset="0x4.4" size="0x0.1" />
	<field name="lcsrg1_14" descr="" access="RO" offset="0x4.5" size="0x0.1" />
	<field name="lcsrg1_17" descr="" access="RO" offset="0x4.6" size="0x0.1" />
	<field name="lcsrg1_18" descr="" access="RO" offset="0x4.7" size="0x0.1" />
	<field name="lcsrg1_19" descr="" access="RO" offset="0x4.8" size="0x0.1" />
	<field name="lcsrg1_20" descr="" access="RO" offset="0x4.9" size="0x0.1" />
	<field name="lcsrg1_21" descr="" access="RO" offset="0x4.10" size="0x0.1" />
	<field name="lcsrg1_22" descr="" access="RO" offset="0x4.11" size="0x0.1" />
	<field name="lcsrg1_23" descr="" access="RO" offset="0x4.12" size="0x0.1" />
	<field name="lcsrg1_24" descr="" access="RO" offset="0x4.13" size="0x0.1" />
	<field name="lcsrg1_25" descr="" access="RO" offset="0x4.14" size="0x0.1" />
	<field name="lcsrg2_22" descr="" access="RO" offset="0x4.15" size="0x0.1" />
	<field name="lcsrg2_23" descr="" access="RO" offset="0x4.16" size="0x0.1" />
	<field name="lcsrg2_24" descr="" access="RO" offset="0x4.17" size="0x0.1" />
	<field name="lcsrg2_25" descr="" access="RO" offset="0x4.18" size="0x0.1" />
	<field name="lcsrg2_26" descr="" access="RO" offset="0x4.19" size="0x0.1" />
	<field name="lcsrg2_27" descr="" access="RO" offset="0x4.20" size="0x0.1" />
	<field name="lcsrg2_28" descr="" access="RO" offset="0x4.21" size="0x0.1" />
	<field name="lcsrg2_29" descr="" access="RO" offset="0x4.22" size="0x0.1" />
	<field name="lcsrg2_30" descr="" access="RO" offset="0x4.23" size="0x0.1" />
	<field name="lcsrg3_1" descr="" access="RO" offset="0x4.24" size="0x0.1" />
	<field name="lcsrg3_20" descr="" access="RO" offset="0x4.25" size="0x0.1" />
	<field name="lcsrg3_23" descr="" access="RO" offset="0x4.26" size="0x0.1" />
	<field name="lcsrg3_24" descr="" access="RO" offset="0x4.27" size="0x0.1" />
	<field name="lcsrg3_25" descr="" access="RO" offset="0x4.28" size="0x0.1" />
	<field name="lcsrg3_26" descr="" access="RO" offset="0x4.29" size="0x0.1" />
	<field name="lcsrg3_27" descr="" access="RO" offset="0x4.30" size="0x0.1" />
	<field name="lcsrg3_28" descr="" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="lcsrg3_29" descr="" access="RO" offset="0x8.0" size="0x0.1" />
	<field name="lcsrg3_30" descr="" access="RO" offset="0x8.1" size="0x0.1" />
	<field name="lcsrg3_31" descr="" access="RO" offset="0x8.2" size="0x0.1" />
	<field name="l_lcsrg2_5" descr="" access="RO" offset="0x8.3" size="0x0.1" />
	<field name="l_lcsrg2_6" descr="" access="RO" offset="0x8.4" size="0x0.1" />
	<field name="l_lcsrg2_7" descr="" access="RO" offset="0x8.5" size="0x0.1" />
	<field name="l_lcsrg2_22" descr="" access="RO" offset="0x8.6" size="0x0.1" />
	<field name="l_lcsrg2_23" descr="" access="RO" offset="0x8.7" size="0x0.1" />
	<field name="lcsrg0_8" descr="tx_sync_fifo_cause_sticky_dist_error" access="RO" offset="0x8.8" size="0x0.1" />
	<field name="lcsrg0_9" descr="tx_sync_fifo_cause_fsm_start" access="RO" offset="0x8.9" size="0x0.1" />
	<field name="lcsrg0_10" descr="tx_sync_fifo_cause_lock" access="RO" offset="0x8.10" size="0x0.1" />
	<field name="lcsrg0_11" descr="tx_sync_fifo_cause_lock_lost" access="RO" offset="0x8.11" size="0x0.1" />
	<field name="lcsrg0_12" descr="tx_sync_fifo_cause_bad_margin_op" access="RO" offset="0x8.12" size="0x0.1" />
	<field name="lcsrg0_13" descr="tx_sync_fifo_cause_bad_margin_antiphase" access="RO" offset="0x8.13" size="0x0.1" />
	<field name="clear_on_read_executed" descr="" access="RO" offset="0xc.30" size="0x0.1" />
	<field name="status" descr="" access="RO" offset="0xc.31" size="0x0.1" />
</node>

<node name="sltr_cause_list_uphy8_ext" descr="" size="0x14.0" >
	<field name="p0csrg0_21" descr="" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="p0csrg0_22" descr="" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="p0csrg0_23" descr="" access="RO" offset="0x0.2" size="0x0.1" />
	<field name="p0csrg0_24" descr="" access="RO" offset="0x0.3" size="0x0.1" />
	<field name="p0csrg0_25" descr="" access="RO" offset="0x0.4" size="0x0.1" />
	<field name="p0csrg0_26" descr="" access="RO" offset="0x0.5" size="0x0.1" />
	<field name="p0csrg0_27" descr="" access="RO" offset="0x0.6" size="0x0.1" />
	<field name="p0csrg0_28" descr="" access="RO" offset="0x0.7" size="0x0.1" />
	<field name="p0csrg0_29" descr="" access="RO" offset="0x0.8" size="0x0.1" />
	<field name="p0csrg0_30" descr="" access="RO" offset="0x0.9" size="0x0.1" />
	<field name="p0csrg0_31" descr="" access="RO" offset="0x0.10" size="0x0.1" />
	<field name="p0csrg1_0" descr="" access="RO" offset="0x0.11" size="0x0.1" />
	<field name="p0csrg1_1" descr="" access="RO" offset="0x0.12" size="0x0.1" />
	<field name="p0csrg1_2" descr="" access="RO" offset="0x0.13" size="0x0.1" />
	<field name="p1csrg0_21" descr="" access="RO" offset="0x0.14" size="0x0.1" />
	<field name="p1csrg0_22" descr="" access="RO" offset="0x0.15" size="0x0.1" />
	<field name="p1csrg0_23" descr="" access="RO" offset="0x0.16" size="0x0.1" />
	<field name="p1csrg0_24" descr="" access="RO" offset="0x0.17" size="0x0.1" />
	<field name="p1csrg0_25" descr="" access="RO" offset="0x0.18" size="0x0.1" />
	<field name="p1csrg0_26" descr="" access="RO" offset="0x0.19" size="0x0.1" />
	<field name="p1csrg0_27" descr="" access="RO" offset="0x0.20" size="0x0.1" />
	<field name="p1csrg0_28" descr="" access="RO" offset="0x0.21" size="0x0.1" />
	<field name="p1csrg0_29" descr="" access="RO" offset="0x0.22" size="0x0.1" />
	<field name="p1csrg0_30" descr="" access="RO" offset="0x0.23" size="0x0.1" />
	<field name="p1csrg0_31" descr="" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="p1csrg1_0" descr="" access="RO" offset="0x0.25" size="0x0.1" />
	<field name="p1csrg1_1" descr="" access="RO" offset="0x0.26" size="0x0.1" />
	<field name="p1csrg1_2" descr="" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="lcsrg0_3" descr="" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="lcsrg0_22" descr="" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="lcsrg0_29" descr="" access="RO" offset="0x4.2" size="0x0.1" />
	<field name="lcsrg1_10" descr="" access="RO" offset="0x4.3" size="0x0.1" />
	<field name="lcsrg1_11" descr="" access="RO" offset="0x4.4" size="0x0.1" />
	<field name="lcsrg1_12" descr="" access="RO" offset="0x4.5" size="0x0.1" />
	<field name="lcsrg1_13" descr="" access="RO" offset="0x4.6" size="0x0.1" />
	<field name="lcsrg1_14" descr="" access="RO" offset="0x4.7" size="0x0.1" />
	<field name="lcsrg1_15" descr="" access="RO" offset="0x4.8" size="0x0.1" />
	<field name="lcsrg1_16" descr="" access="RO" offset="0x4.9" size="0x0.1" />
	<field name="lcsrg1_18" descr="" access="RO" offset="0x4.10" size="0x0.1" />
	<field name="lcsrg1_22" descr="" access="RO" offset="0x4.11" size="0x0.1" />
	<field name="lcsrg1_23" descr="" access="RO" offset="0x4.12" size="0x0.1" />
	<field name="lcsrg1_24" descr="" access="RO" offset="0x4.13" size="0x0.1" />
	<field name="lcsrg1_25" descr="" access="RO" offset="0x4.14" size="0x0.1" />
	<field name="lcsrg1_26" descr="" access="RO" offset="0x4.15" size="0x0.1" />
	<field name="lcsrg2_0" descr="" access="RO" offset="0x4.16" size="0x0.1" />
	<field name="lcsrg2_5" descr="" access="RO" offset="0x4.17" size="0x0.1" />
	<field name="lcsrg3_8" descr="" access="RO" offset="0x4.18" size="0x0.1" />
	<field name="lcsrg3_11" descr="" access="RO" offset="0x4.19" size="0x0.1" />
	<field name="lcsrg3_12" descr="" access="RO" offset="0x4.20" size="0x0.1" />
	<field name="lcsrg3_13" descr="" access="RO" offset="0x4.21" size="0x0.1" />
	<field name="lcsrg4_8" descr="" access="RO" offset="0x4.22" size="0x0.1" />
	<field name="lcsrg4_9" descr="" access="RO" offset="0x4.23" size="0x0.1" />
	<field name="lcsrg2_8" descr="tx_sync_fifo_cause_sticky_dist_error" access="RO" offset="0x4.24" size="0x0.1" />
	<field name="lcsrg2_9" descr="tx_sync_fifo_cause_fsm_start" access="RO" offset="0x4.25" size="0x0.1" />
	<field name="lcsrg2_10" descr="tx_sync_fifo_cause_lock" access="RO" offset="0x4.26" size="0x0.1" />
	<field name="lcsrg2_11" descr="tx_sync_fifo_cause_lock_lost" access="RO" offset="0x4.27" size="0x0.1" />
	<field name="lcsrg2_12" descr="tx_sync_fifo_cause_bad_margin_op" access="RO" offset="0x4.28" size="0x0.1" />
	<field name="lcsrg2_13" descr="tx_sync_fifo_cause_bad_margin_antiphase" access="RO" offset="0x4.29" size="0x0.1" />
	<field name="lcsrg4_11" descr="" access="RO" offset="0x8.0" size="0x0.1" />
	<field name="lcsrg4_12" descr="" access="RO" offset="0x8.1" size="0x0.1" />
	<field name="lcsrg4_13" descr="" access="RO" offset="0x8.2" size="0x0.1" />
	<field name="lcsrg4_14" descr="" access="RO" offset="0x8.3" size="0x0.1" />
	<field name="lcsrg4_15" descr="" access="RO" offset="0x8.4" size="0x0.1" />
	<field name="lcsrg5_1" descr="" access="RO" offset="0x8.5" size="0x0.1" />
	<field name="lcsrg5_13" descr="" access="RO" offset="0x8.6" size="0x0.1" />
	<field name="lcsrg5_29" descr="" access="RO" offset="0x8.7" size="0x0.1" />
	<field name="lcsrg6_4" descr="" access="RO" offset="0x8.8" size="0x0.1" />
	<field name="lcsrg6_5" descr="" access="RO" offset="0x8.9" size="0x0.1" />
	<field name="lcsrg6_6" descr="" access="RO" offset="0x8.10" size="0x0.1" />
	<field name="lcsrg6_7" descr="" access="RO" offset="0x8.11" size="0x0.1" />
	<field name="lcsrg6_18" descr="" access="RO" offset="0x8.12" size="0x0.1" />
	<field name="lcsrg6_19" descr="" access="RO" offset="0x8.13" size="0x0.1" />
	<field name="lcsrg6_20" descr="" access="RO" offset="0x8.14" size="0x0.1" />
	<field name="lcsrg6_21" descr="" access="RO" offset="0x8.15" size="0x0.1" />
	<field name="lcsrg6_22" descr="" access="RO" offset="0x8.16" size="0x0.1" />
	<field name="lcsrg6_23" descr="" access="RO" offset="0x8.17" size="0x0.1" />
	<field name="lcsrg6_24" descr="" access="RO" offset="0x8.18" size="0x0.1" />
	<field name="lcsrg6_25" descr="" access="RO" offset="0x8.19" size="0x0.1" />
	<field name="lcsrg6_26" descr="" access="RO" offset="0x8.20" size="0x0.1" />
	<field name="lcsrg6_27" descr="" access="RO" offset="0x8.21" size="0x0.1" />
	<field name="lcsrg7_14" descr="" access="RO" offset="0x8.22" size="0x0.1" />
	<field name="lcsrg7_15" descr="" access="RO" offset="0x8.23" size="0x0.1" />
	<field name="lcsrg7_16" descr="" access="RO" offset="0x8.24" size="0x0.1" />
	<field name="lcsrg7_17" descr="" access="RO" offset="0x8.25" size="0x0.1" />
	<field name="lcsrg7_18" descr="" access="RO" offset="0x8.26" size="0x0.1" />
	<field name="lcsrg7_19" descr="" access="RO" offset="0x8.27" size="0x0.1" />
	<field name="lcsrg7_20" descr="" access="RO" offset="0x8.28" size="0x0.1" />
	<field name="lcsrg7_21" descr="" access="RO" offset="0x8.29" size="0x0.1" />
	<field name="lcsrg7_26" descr="" access="RO" offset="0x8.30" size="0x0.1" />
	<field name="lcsrg7_27" descr="" access="RO" offset="0x8.31" size="0x0.1" />
	<field name="lcsrg7_28" descr="" access="RO" offset="0xc.0" size="0x0.1" />
	<field name="lcsrg7_29" descr="" access="RO" offset="0xc.1" size="0x0.1" />
	<field name="lcsrg7_30" descr="" access="RO" offset="0xc.2" size="0x0.1" />
	<field name="lcsrg7_31" descr="" access="RO" offset="0xc.3" size="0x0.1" />
	<field name="lcsrg8_0" descr="" access="RO" offset="0xc.4" size="0x0.1" />
	<field name="lcsrg8_1" descr="" access="RO" offset="0xc.5" size="0x0.1" />
	<field name="lcsrg8_2" descr="" access="RO" offset="0xc.6" size="0x0.1" />
	<field name="lcsrg8_3" descr="" access="RO" offset="0xc.7" size="0x0.1" />
	<field name="lcsrg8_4" descr="" access="RO" offset="0xc.8" size="0x0.1" />
	<field name="lcsrg8_5" descr="" access="RO" offset="0xc.9" size="0x0.1" />
	<field name="lcsrg8_6" descr="" access="RO" offset="0xc.10" size="0x0.1" />
	<field name="lcsrg8_7" descr="" access="RO" offset="0xc.11" size="0x0.1" />
	<field name="lcsrg8_8" descr="" access="RO" offset="0xc.12" size="0x0.1" />
	<field name="lcsrg10_30" descr="" access="RO" offset="0xc.13" size="0x0.1" />
	<field name="lcsrg11_1" descr="" access="RO" offset="0xc.14" size="0x0.1" />
	<field name="clear_on_read_executed" descr="" access="RO" offset="0x10.30" size="0x0.1" />
	<field name="status" descr="" access="RO" offset="0x10.31" size="0x0.1" />
</node>

<node name="sltr_non_periodic_non_destructive_7_5_ext" descr="" size="0x10.0" >
</node>

<node name="sltr_non_periodic_non_destructive_ext" descr="" size="0x18.0" >
	<field name="ag_group_exist" descr="" access="RO" offset="0x0.26" size="0x0.1" />
	<field name="ae_group_exist" descr="" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="y_group_exist" descr="" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="ab_group_exist" descr="" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="w_group_exist" descr="" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="e_group_exist" descr="" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="e_group6" descr="" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="e_group5" descr="" access="RO" offset="0x4.10" size="0x0.2" />
	<field name="e_group4" descr="" access="RO" offset="0x4.13" size="0x0.3" />
	<field name="e_group3" descr="" access="RO" offset="0x4.17" size="0x0.2" />
	<field name="e_group2" descr="" access="RO" offset="0x4.20" size="0x0.2" />
	<field name="e_group1" descr="" access="RO" offset="0x4.23" size="0x0.3" />
	<field name="e_group0" descr="" access="RO" offset="0x4.27" size="0x0.5" />
	<field name="w_group4" descr="" access="RO" offset="0x8.0" size="0x0.5" />
	<field name="w_group3" descr="" access="RO" offset="0x8.5" size="0x0.5" />
	<field name="w_group2" descr="" access="RO" offset="0x8.10" size="0x0.5" />
	<field name="w_group1" descr="" access="RO" offset="0x8.15" size="0x0.5" />
	<field name="w_group0" descr="" access="RO" offset="0x8.20" size="0x0.5" />
	<field name="e_group8" descr="" access="RO" offset="0x8.26" size="0x0.2" />
	<field name="e_group7" descr="" access="RO" offset="0x8.29" size="0x0.3" />
	<field name="w_group10" descr="" access="RO" offset="0xc.2" size="0x0.5" />
	<field name="w_group9" descr="" access="RO" offset="0xc.7" size="0x0.5" />
	<field name="w_group8" descr="" access="RO" offset="0xc.12" size="0x0.5" />
	<field name="w_group7" descr="" access="RO" offset="0xc.17" size="0x0.5" />
	<field name="w_group6" descr="" access="RO" offset="0xc.22" size="0x0.5" />
	<field name="w_group5" descr="" access="RO" offset="0xc.27" size="0x0.5" />
	<field name="ab_group0" descr="" access="RO" offset="0x10.3" size="0x0.3" />
	<field name="w_group15" descr="" access="RO" offset="0x10.7" size="0x0.5" />
	<field name="w_group14" descr="" access="RO" offset="0x10.12" size="0x0.5" />
	<field name="w_group13" descr="" access="RO" offset="0x10.17" size="0x0.5" />
	<field name="w_group12" descr="" access="RO" offset="0x10.22" size="0x0.5" />
	<field name="w_group11" descr="" access="RO" offset="0x10.27" size="0x0.5" />
	<field name="ag_group0" descr="" access="RO" offset="0x14.0" size="0x0.7" />
	<field name="ae_group1" descr="" access="RO" offset="0x14.12" size="0x0.4" />
	<field name="ae_group0" descr="" access="RO" offset="0x14.16" size="0x0.5" />
	<field name="y_group0" descr="" access="RO" offset="0x14.23" size="0x0.9" />
</node>

<node name="sltr_periodic_non_destructive_7_5_ext" descr="" size="0xd8.0" >
</node>

<node name="sltr_periodic_non_destructive_ext" descr="" size="0x124.0" >
	<field name="v_group_exist" descr="" access="RO" offset="0x0.11" size="0x0.1" />
	<field name="t_group_exist" descr="" access="RO" offset="0x0.12" size="0x0.1" />
	<field name="qb_group_exist" descr="" access="RO" offset="0x0.13" size="0x0.1" />
	<field name="q_group_exist" descr="" access="RO" offset="0x0.14" size="0x0.1" />
	<field name="qc_group_exist" descr="" access="RO" offset="0x0.15" size="0x0.1" />
	<field name="p_group_exist" descr="" access="RO" offset="0x0.16" size="0x0.1" />
	<field name="od_group_exist" descr="" access="RO" offset="0x0.17" size="0x0.1" />
	<field name="oc_group_exist" descr="" access="RO" offset="0x0.18" size="0x0.1" />
	<field name="ob_group_exist" descr="" access="RO" offset="0x0.19" size="0x0.1" />
	<field name="oa_group_exist" descr="" access="RO" offset="0x0.20" size="0x0.1" />
	<field name="qa_group_exist" descr="" access="RO" offset="0x0.21" size="0x0.1" />
	<field name="i_group_exist" descr="" access="RO" offset="0x0.22" size="0x0.1" />
	<field name="d_group_exist" descr="" access="RO" offset="0x0.23" size="0x0.1" />
	<field name="c_group_exist" descr="" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="bs_group_exist" descr="" access="RO" offset="0x0.25" size="0x0.1" />
	<field name="bc_group_exist" descr="" access="RO" offset="0x0.26" size="0x0.1" />
	<field name="af_group_exist" descr="" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="afm_group_exist" descr="" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="f_group_exist" descr="" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="m_group_exist" descr="" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="m_group5" descr="" access="RO" offset="0x4.0" size="0x0.10" />
	<field name="m_group3" descr="" access="RO" offset="0x4.10" size="0x0.10" />
	<field name="m_group4" descr="" access="RO" offset="0x4.20" size="0x0.10" />
	<field name="afm_group5" descr="" access="RO" offset="0xc.0" size="0x0.5" />
	<field name="afm_group4" descr="" access="RO" offset="0xc.7" size="0x0.6" />
	<field name="afm_group3" descr="" access="RO" offset="0xc.15" size="0x0.8" />
	<field name="f_group0" descr="" access="RO" offset="0xc.23" size="0x0.6" />
	<field name="afm_group2" descr="" access="RO" offset="0x10.0" size="0x0.8" />
	<field name="afm_group1" descr="" access="RO" offset="0x10.10" size="0x0.9" />
	<field name="af_group1" descr="" access="RO" offset="0x10.21" size="0x0.8" />
	<field name="af_group2" descr="" access="RO" offset="0x14.0" size="0x0.8" />
	<field name="af_group3" descr="" access="RO" offset="0x14.10" size="0x0.7" />
	<field name="af_group4" descr="" access="RO" offset="0x14.19" size="0x0.7" />
	<field name="m_group0" descr="" access="RO" offset="0x14.28" size="0x0.4" />
	<field name="af_group5" descr="" access="RO" offset="0x18.0" size="0x0.7" />
	<field name="af_group6" descr="" access="RO" offset="0x18.9" size="0x0.6" />
	<field name="af_group7" descr="" access="RO" offset="0x18.17" size="0x0.6" />
	<field name="af_group8" descr="" access="RO" offset="0x18.25" size="0x0.6" />
	<field name="af_group9" descr="" access="RO" offset="0x1c.0" size="0x0.6" />
	<field name="af_group10" descr="" access="RO" offset="0x1c.8" size="0x0.5" />
	<field name="af_group11" descr="" access="RO" offset="0x1c.15" size="0x0.5" />
	<field name="af_group12" descr="" access="RO" offset="0x1c.22" size="0x0.5" />
	<field name="bs_group0" descr="" access="RO" offset="0x20.0" size="0x0.6" />
	<field name="bc_group0" descr="" access="RO" offset="0x20.6" size="0x0.4" />
	<field name="bs_group1" descr="" access="RO" offset="0x20.11" size="0x0.6" />
	<field name="bc_group1" descr="" access="RO" offset="0x20.17" size="0x0.4" />
	<field name="bs_group2" descr="" access="RO" offset="0x20.22" size="0x0.6" />
	<field name="bc_group2" descr="" access="RO" offset="0x20.28" size="0x0.4" />
	<field name="bs_group3" descr="" access="RO" offset="0x24.0" size="0x0.6" />
	<field name="bc_group3" descr="" access="RO" offset="0x24.6" size="0x0.4" />
	<field name="bs_group4" descr="" access="RO" offset="0x24.11" size="0x0.6" />
	<field name="bc_group4" descr="" access="RO" offset="0x24.17" size="0x0.4" />
	<field name="bs_group5" descr="" access="RO" offset="0x24.22" size="0x0.6" />
	<field name="bc_group5" descr="" access="RO" offset="0x24.28" size="0x0.4" />
	<field name="bs_group6" descr="" access="RO" offset="0x28.0" size="0x0.6" />
	<field name="bc_group6" descr="" access="RO" offset="0x28.6" size="0x0.4" />
	<field name="bs_group7" descr="" access="RO" offset="0x28.11" size="0x0.6" />
	<field name="bc_group7" descr="" access="RO" offset="0x28.17" size="0x0.4" />
	<field name="bs_group8" descr="" access="RO" offset="0x28.22" size="0x0.6" />
	<field name="bc_group8" descr="" access="RO" offset="0x28.28" size="0x0.4" />
	<field name="bs_group9" descr="" access="RO" offset="0x2c.0" size="0x0.6" />
	<field name="bc_group9" descr="" access="RO" offset="0x2c.6" size="0x0.4" />
	<field name="bs_group10" descr="" access="RO" offset="0x2c.11" size="0x0.6" />
	<field name="bc_group10" descr="" access="RO" offset="0x2c.17" size="0x0.4" />
	<field name="bs_group11" descr="" access="RO" offset="0x2c.22" size="0x0.6" />
	<field name="bc_group11" descr="" access="RO" offset="0x2c.28" size="0x0.4" />
	<field name="bs_group12" descr="" access="RO" offset="0x30.0" size="0x0.6" />
	<field name="bc_group12" descr="" access="RO" offset="0x30.6" size="0x0.4" />
	<field name="bs_group13" descr="" access="RO" offset="0x30.11" size="0x0.6" />
	<field name="bc_group13" descr="" access="RO" offset="0x30.17" size="0x0.4" />
	<field name="bs_group14" descr="" access="RO" offset="0x30.22" size="0x0.6" />
	<field name="bc_group14" descr="" access="RO" offset="0x30.28" size="0x0.4" />
	<field name="bs_group15" descr="" access="RO" offset="0x34.0" size="0x0.6" />
	<field name="bc_group15" descr="" access="RO" offset="0x34.6" size="0x0.4" />
	<field name="c_group0" descr="" access="RO" offset="0x34.11" size="0x0.10" />
	<field name="c_group1" descr="" access="RO" offset="0x34.22" size="0x0.10" />
	<field name="c_group2" descr="" access="RO" offset="0x38.0" size="0x0.10" />
	<field name="c_group3" descr="" access="RO" offset="0x38.11" size="0x0.10" />
	<field name="c_group4" descr="" access="RO" offset="0x38.22" size="0x0.10" />
	<field name="c_group5" descr="" access="RO" offset="0x3c.0" size="0x0.10" />
	<field name="c_group6" descr="" access="RO" offset="0x3c.11" size="0x0.10" />
	<field name="c_group7" descr="" access="RO" offset="0x3c.22" size="0x0.10" />
	<field name="c_group8" descr="" access="RO" offset="0x40.0" size="0x0.10" />
	<field name="c_group9" descr="" access="RO" offset="0x40.11" size="0x0.10" />
	<field name="c_group10" descr="" access="RO" offset="0x40.22" size="0x0.10" />
	<field name="c_group11" descr="" access="RO" offset="0x44.0" size="0x0.10" />
	<field name="c_group12" descr="" access="RO" offset="0x44.11" size="0x0.10" />
	<field name="d_group0" descr="" access="RO" offset="0x44.22" size="0x0.10" />
	<field name="d_group1" descr="" access="RO" offset="0x48.0" size="0x0.10" />
	<field name="d_group2" descr="" access="RO" offset="0x48.11" size="0x0.10" />
	<field name="d_group3" descr="" access="RO" offset="0x48.22" size="0x0.10" />
	<field name="d_group4" descr="" access="RO" offset="0x4c.0" size="0x0.10" />
	<field name="d_group5" descr="" access="RO" offset="0x4c.11" size="0x0.10" />
	<field name="d_group6" descr="" access="RO" offset="0x4c.22" size="0x0.10" />
	<field name="d_group7" descr="" access="RO" offset="0x50.0" size="0x0.10" />
	<field name="d_group8" descr="" access="RO" offset="0x50.11" size="0x0.10" />
	<field name="d_group9" descr="" access="RO" offset="0x50.22" size="0x0.10" />
	<field name="d_group10" descr="" access="RO" offset="0x54.0" size="0x0.10" />
	<field name="d_group11" descr="" access="RO" offset="0x54.11" size="0x0.10" />
	<field name="d_group12" descr="" access="RO" offset="0x54.22" size="0x0.10" />
	<field name="i_group4" descr="" access="RO" offset="0x58.0" size="0x0.8" />
	<field name="i_group3" descr="" access="RO" offset="0x58.8" size="0x0.8" />
	<field name="i_group2" descr="" access="RO" offset="0x58.16" size="0x0.8" />
	<field name="i_group1" descr="" access="RO" offset="0x58.24" size="0x0.8" />
	<field name="i_group8" descr="" access="RO" offset="0x5c.0" size="0x0.8" />
	<field name="i_group7" descr="" access="RO" offset="0x5c.8" size="0x0.8" />
	<field name="i_group6" descr="" access="RO" offset="0x5c.16" size="0x0.8" />
	<field name="i_group5" descr="" access="RO" offset="0x5c.24" size="0x0.8" />
	<field name="qa_group1" descr="" access="RO" offset="0x60.0" size="0x0.11" />
	<field name="m_group6" descr="" access="RO" offset="0x60.11" size="0x0.10" />
	<field name="m_group2" descr="" access="RO" offset="0x60.22" size="0x0.10" />
	<field name="oa_group3" descr="" access="RO" offset="0x64.0" size="0x0.8" />
	<field name="oa_group2" descr="" access="RO" offset="0x64.8" size="0x0.8" />
	<field name="oa_group1" descr="" access="RO" offset="0x64.16" size="0x0.8" />
	<field name="oa_group0" descr="" access="RO" offset="0x64.24" size="0x0.8" />
	<field name="oa_group7" descr="" access="RO" offset="0x68.0" size="0x0.8" />
	<field name="oa_group6" descr="" access="RO" offset="0x68.8" size="0x0.8" />
	<field name="oa_group5" descr="" access="RO" offset="0x68.16" size="0x0.8" />
	<field name="oa_group4" descr="" access="RO" offset="0x68.24" size="0x0.8" />
	<field name="oa_group11" descr="" access="RO" offset="0x6c.0" size="0x0.8" />
	<field name="oa_group10" descr="" access="RO" offset="0x6c.8" size="0x0.8" />
	<field name="oa_group9" descr="" access="RO" offset="0x6c.16" size="0x0.8" />
	<field name="oa_group8" descr="" access="RO" offset="0x6c.24" size="0x0.8" />
	<field name="oa_group15" descr="" access="RO" offset="0x70.0" size="0x0.8" />
	<field name="oa_group14" descr="" access="RO" offset="0x70.8" size="0x0.8" />
	<field name="oa_group13" descr="" access="RO" offset="0x70.16" size="0x0.8" />
	<field name="oa_group12" descr="" access="RO" offset="0x70.24" size="0x0.8" />
	<field name="oa_group19" descr="" access="RO" offset="0x74.0" size="0x0.8" />
	<field name="oa_group18" descr="" access="RO" offset="0x74.8" size="0x0.8" />
	<field name="oa_group17" descr="" access="RO" offset="0x74.16" size="0x0.8" />
	<field name="oa_group16" descr="" access="RO" offset="0x74.24" size="0x0.8" />
	<field name="oa_group23" descr="" access="RO" offset="0x78.0" size="0x0.8" />
	<field name="oa_group22" descr="" access="RO" offset="0x78.8" size="0x0.8" />
	<field name="oa_group21" descr="" access="RO" offset="0x78.16" size="0x0.8" />
	<field name="oa_group20" descr="" access="RO" offset="0x78.24" size="0x0.8" />
	<field name="oa_group27" descr="" access="RO" offset="0x7c.0" size="0x0.8" />
	<field name="oa_group26" descr="" access="RO" offset="0x7c.8" size="0x0.8" />
	<field name="oa_group25" descr="" access="RO" offset="0x7c.16" size="0x0.8" />
	<field name="oa_group24" descr="" access="RO" offset="0x7c.24" size="0x0.8" />
	<field name="oa_group31" descr="" access="RO" offset="0x80.0" size="0x0.8" />
	<field name="oa_group30" descr="" access="RO" offset="0x80.8" size="0x0.8" />
	<field name="oa_group29" descr="" access="RO" offset="0x80.16" size="0x0.8" />
	<field name="oa_group28" descr="" access="RO" offset="0x80.24" size="0x0.8" />
	<field name="ob_group3" descr="" access="RO" offset="0x84.0" size="0x0.8" />
	<field name="ob_group2" descr="" access="RO" offset="0x84.8" size="0x0.8" />
	<field name="ob_group1" descr="" access="RO" offset="0x84.16" size="0x0.8" />
	<field name="ob_group0" descr="" access="RO" offset="0x84.24" size="0x0.8" />
	<field name="ob_group7" descr="" access="RO" offset="0x88.0" size="0x0.8" />
	<field name="ob_group6" descr="" access="RO" offset="0x88.8" size="0x0.8" />
	<field name="ob_group5" descr="" access="RO" offset="0x88.16" size="0x0.8" />
	<field name="ob_group4" descr="" access="RO" offset="0x88.24" size="0x0.8" />
	<field name="ob_group11" descr="" access="RO" offset="0x8c.0" size="0x0.8" />
	<field name="ob_group10" descr="" access="RO" offset="0x8c.8" size="0x0.8" />
	<field name="ob_group9" descr="" access="RO" offset="0x8c.16" size="0x0.8" />
	<field name="ob_group8" descr="" access="RO" offset="0x8c.24" size="0x0.8" />
	<field name="ob_group15" descr="" access="RO" offset="0x90.0" size="0x0.8" />
	<field name="ob_group14" descr="" access="RO" offset="0x90.8" size="0x0.8" />
	<field name="ob_group13" descr="" access="RO" offset="0x90.16" size="0x0.8" />
	<field name="ob_group12" descr="" access="RO" offset="0x90.24" size="0x0.8" />
	<field name="ob_group19" descr="" access="RO" offset="0x94.0" size="0x0.8" />
	<field name="ob_group18" descr="" access="RO" offset="0x94.8" size="0x0.8" />
	<field name="ob_group17" descr="" access="RO" offset="0x94.16" size="0x0.8" />
	<field name="ob_group16" descr="" access="RO" offset="0x94.24" size="0x0.8" />
	<field name="ob_group23" descr="" access="RO" offset="0x98.0" size="0x0.8" />
	<field name="ob_group22" descr="" access="RO" offset="0x98.8" size="0x0.8" />
	<field name="ob_group21" descr="" access="RO" offset="0x98.16" size="0x0.8" />
	<field name="ob_group20" descr="" access="RO" offset="0x98.24" size="0x0.8" />
	<field name="ob_group27" descr="" access="RO" offset="0x9c.0" size="0x0.8" />
	<field name="ob_group26" descr="" access="RO" offset="0x9c.8" size="0x0.8" />
	<field name="ob_group25" descr="" access="RO" offset="0x9c.16" size="0x0.8" />
	<field name="ob_group24" descr="" access="RO" offset="0x9c.24" size="0x0.8" />
	<field name="ob_group31" descr="" access="RO" offset="0xa0.0" size="0x0.8" />
	<field name="ob_group30" descr="" access="RO" offset="0xa0.8" size="0x0.8" />
	<field name="ob_group29" descr="" access="RO" offset="0xa0.16" size="0x0.8" />
	<field name="ob_group28" descr="" access="RO" offset="0xa0.24" size="0x0.8" />
	<field name="oc_group3" descr="" access="RO" offset="0xa4.0" size="0x0.8" />
	<field name="oc_group2" descr="" access="RO" offset="0xa4.8" size="0x0.8" />
	<field name="oc_group1" descr="" access="RO" offset="0xa4.16" size="0x0.8" />
	<field name="oc_group0" descr="" access="RO" offset="0xa4.24" size="0x0.8" />
	<field name="oc_group7" descr="" access="RO" offset="0xa8.0" size="0x0.8" />
	<field name="oc_group6" descr="" access="RO" offset="0xa8.8" size="0x0.8" />
	<field name="oc_group5" descr="" access="RO" offset="0xa8.16" size="0x0.8" />
	<field name="oc_group4" descr="" access="RO" offset="0xa8.24" size="0x0.8" />
	<field name="oc_group11" descr="" access="RO" offset="0xac.0" size="0x0.8" />
	<field name="oc_group10" descr="" access="RO" offset="0xac.8" size="0x0.8" />
	<field name="oc_group9" descr="" access="RO" offset="0xac.16" size="0x0.8" />
	<field name="oc_group8" descr="" access="RO" offset="0xac.24" size="0x0.8" />
	<field name="oc_group15" descr="" access="RO" offset="0xb0.0" size="0x0.8" />
	<field name="oc_group14" descr="" access="RO" offset="0xb0.8" size="0x0.8" />
	<field name="oc_group13" descr="" access="RO" offset="0xb0.16" size="0x0.8" />
	<field name="oc_group12" descr="" access="RO" offset="0xb0.24" size="0x0.8" />
	<field name="oc_group19" descr="" access="RO" offset="0xb4.0" size="0x0.8" />
	<field name="oc_group18" descr="" access="RO" offset="0xb4.8" size="0x0.8" />
	<field name="oc_group17" descr="" access="RO" offset="0xb4.16" size="0x0.8" />
	<field name="oc_group16" descr="" access="RO" offset="0xb4.24" size="0x0.8" />
	<field name="oc_group23" descr="" access="RO" offset="0xb8.0" size="0x0.8" />
	<field name="oc_group22" descr="" access="RO" offset="0xb8.8" size="0x0.8" />
	<field name="oc_group21" descr="" access="RO" offset="0xb8.16" size="0x0.8" />
	<field name="oc_group20" descr="" access="RO" offset="0xb8.24" size="0x0.8" />
	<field name="oc_group27" descr="" access="RO" offset="0xbc.0" size="0x0.8" />
	<field name="oc_group26" descr="" access="RO" offset="0xbc.8" size="0x0.8" />
	<field name="oc_group25" descr="" access="RO" offset="0xbc.16" size="0x0.8" />
	<field name="oc_group24" descr="" access="RO" offset="0xbc.24" size="0x0.8" />
	<field name="oc_group31" descr="" access="RO" offset="0xc0.0" size="0x0.8" />
	<field name="oc_group30" descr="" access="RO" offset="0xc0.8" size="0x0.8" />
	<field name="oc_group29" descr="" access="RO" offset="0xc0.16" size="0x0.8" />
	<field name="oc_group28" descr="" access="RO" offset="0xc0.24" size="0x0.8" />
	<field name="od_group3" descr="" access="RO" offset="0xc4.0" size="0x0.8" />
	<field name="od_group2" descr="" access="RO" offset="0xc4.8" size="0x0.8" />
	<field name="od_group1" descr="" access="RO" offset="0xc4.16" size="0x0.8" />
	<field name="od_group0" descr="" access="RO" offset="0xc4.24" size="0x0.8" />
	<field name="od_group7" descr="" access="RO" offset="0xc8.0" size="0x0.8" />
	<field name="od_group6" descr="" access="RO" offset="0xc8.8" size="0x0.8" />
	<field name="od_group5" descr="" access="RO" offset="0xc8.16" size="0x0.8" />
	<field name="od_group4" descr="" access="RO" offset="0xc8.24" size="0x0.8" />
	<field name="od_group11" descr="" access="RO" offset="0xcc.0" size="0x0.8" />
	<field name="od_group10" descr="" access="RO" offset="0xcc.8" size="0x0.8" />
	<field name="od_group9" descr="" access="RO" offset="0xcc.16" size="0x0.8" />
	<field name="od_group8" descr="" access="RO" offset="0xcc.24" size="0x0.8" />
	<field name="od_group15" descr="" access="RO" offset="0xd0.0" size="0x0.8" />
	<field name="od_group14" descr="" access="RO" offset="0xd0.8" size="0x0.8" />
	<field name="od_group13" descr="" access="RO" offset="0xd0.16" size="0x0.8" />
	<field name="od_group12" descr="" access="RO" offset="0xd0.24" size="0x0.8" />
	<field name="od_group19" descr="" access="RO" offset="0xd4.0" size="0x0.8" />
	<field name="od_group18" descr="" access="RO" offset="0xd4.8" size="0x0.8" />
	<field name="od_group17" descr="" access="RO" offset="0xd4.16" size="0x0.8" />
	<field name="od_group16" descr="" access="RO" offset="0xd4.24" size="0x0.8" />
	<field name="od_group23" descr="" access="RO" offset="0xd8.0" size="0x0.8" />
	<field name="od_group22" descr="" access="RO" offset="0xd8.8" size="0x0.8" />
	<field name="od_group21" descr="" access="RO" offset="0xd8.16" size="0x0.8" />
	<field name="od_group20" descr="" access="RO" offset="0xd8.24" size="0x0.8" />
	<field name="od_group27" descr="" access="RO" offset="0xdc.0" size="0x0.8" />
	<field name="od_group26" descr="" access="RO" offset="0xdc.8" size="0x0.8" />
	<field name="od_group25" descr="" access="RO" offset="0xdc.16" size="0x0.8" />
	<field name="od_group24" descr="" access="RO" offset="0xdc.24" size="0x0.8" />
	<field name="od_group31" descr="" access="RO" offset="0xe0.0" size="0x0.8" />
	<field name="od_group30" descr="" access="RO" offset="0xe0.8" size="0x0.8" />
	<field name="od_group29" descr="" access="RO" offset="0xe0.16" size="0x0.8" />
	<field name="od_group28" descr="" access="RO" offset="0xe0.24" size="0x0.8" />
	<field name="qa_group4" descr="" access="RO" offset="0xe4.0" size="0x0.11" />
	<field name="qa_group3" descr="" access="RO" offset="0xe4.11" size="0x0.11" />
	<field name="qa_group2" descr="" access="RO" offset="0xe4.22" size="0x0.10" />
	<field name="p_group3" descr="" access="RO" offset="0xe8.0" size="0x0.8" />
	<field name="p_group2" descr="" access="RO" offset="0xe8.8" size="0x0.8" />
	<field name="p_group1" descr="" access="RO" offset="0xe8.16" size="0x0.8" />
	<field name="p_group0" descr="" access="RO" offset="0xe8.24" size="0x0.8" />
	<field name="p_group7" descr="" access="RO" offset="0xec.0" size="0x0.8" />
	<field name="p_group6" descr="" access="RO" offset="0xec.8" size="0x0.8" />
	<field name="p_group5" descr="" access="RO" offset="0xec.16" size="0x0.8" />
	<field name="p_group4" descr="" access="RO" offset="0xec.24" size="0x0.8" />
	<field name="p_group11" descr="" access="RO" offset="0xf0.0" size="0x0.8" />
	<field name="p_group10" descr="" access="RO" offset="0xf0.8" size="0x0.8" />
	<field name="p_group9" descr="" access="RO" offset="0xf0.16" size="0x0.8" />
	<field name="p_group8" descr="" access="RO" offset="0xf0.24" size="0x0.8" />
	<field name="p_group15" descr="" access="RO" offset="0xf4.0" size="0x0.8" />
	<field name="p_group14" descr="" access="RO" offset="0xf4.8" size="0x0.8" />
	<field name="p_group13" descr="" access="RO" offset="0xf4.16" size="0x0.8" />
	<field name="p_group12" descr="" access="RO" offset="0xf4.24" size="0x0.8" />
	<field name="p_group19" descr="" access="RO" offset="0xf8.0" size="0x0.8" />
	<field name="p_group18" descr="" access="RO" offset="0xf8.8" size="0x0.8" />
	<field name="p_group17" descr="" access="RO" offset="0xf8.16" size="0x0.8" />
	<field name="p_group16" descr="" access="RO" offset="0xf8.24" size="0x0.8" />
	<field name="qc_group4" descr="" access="RO" offset="0xfc.0" size="0x0.6" />
	<field name="qc_group3" descr="" access="RO" offset="0xfc.6" size="0x0.6" />
	<field name="qc_group2" descr="" access="RO" offset="0xfc.12" size="0x0.6" />
	<field name="qc_group1" descr="" access="RO" offset="0xfc.18" size="0x0.6" />
	<field name="qc_group0" descr="" access="RO" offset="0xfc.24" size="0x0.6" />
	<field name="qc_group9" descr="" access="RO" offset="0x100.0" size="0x0.6" />
	<field name="qc_group8" descr="" access="RO" offset="0x100.6" size="0x0.6" />
	<field name="qc_group7" descr="" access="RO" offset="0x100.12" size="0x0.6" />
	<field name="qc_group6" descr="" access="RO" offset="0x100.18" size="0x0.6" />
	<field name="qc_group5" descr="" access="RO" offset="0x100.24" size="0x0.6" />
	<field name="qc_group14" descr="" access="RO" offset="0x104.0" size="0x0.6" />
	<field name="qc_group13" descr="" access="RO" offset="0x104.6" size="0x0.6" />
	<field name="qc_group12" descr="" access="RO" offset="0x104.12" size="0x0.6" />
	<field name="qc_group11" descr="" access="RO" offset="0x104.18" size="0x0.6" />
	<field name="qc_group10" descr="" access="RO" offset="0x104.24" size="0x0.6" />
	<field name="qc_group19" descr="" access="RO" offset="0x108.0" size="0x0.6" />
	<field name="qc_group18" descr="" access="RO" offset="0x108.6" size="0x0.6" />
	<field name="qc_group17" descr="" access="RO" offset="0x108.12" size="0x0.6" />
	<field name="qc_group16" descr="" access="RO" offset="0x108.18" size="0x0.6" />
	<field name="qc_group15" descr="" access="RO" offset="0x108.24" size="0x0.6" />
	<field name="qb_group2" descr="" access="RO" offset="0x10c.4" size="0x0.5" />
	<field name="qb_group1" descr="" access="RO" offset="0x10c.9" size="0x0.5" />
	<field name="qb_group0" descr="" access="RO" offset="0x10c.14" size="0x0.5" />
	<field name="q_group0" descr="" access="RO" offset="0x10c.21" size="0x0.11" />
	<field name="t_group1" descr="" access="RO" offset="0x110.0" size="0x0.16" />
	<field name="t_group0" descr="" access="RO" offset="0x110.16" size="0x0.16" />
	<field name="vgroup0" descr="" access="RO" offset="0x114.0" size="0x0.16" />
	<field name="t_group2" descr="" access="RO" offset="0x114.16" size="0x0.16" />
	<field name="vgroup2" descr="" access="RO" offset="0x118.5" size="0x0.16" />
	<field name="vgroup1" descr="" access="RO" offset="0x118.21" size="0x0.11" />
	<field name="i_group10" descr="" access="RO" offset="0x11c.0" size="0x0.8" />
	<field name="i_group9" descr="" access="RO" offset="0x11c.8" size="0x0.8" />
	<field name="m_group1" descr="" access="RO" offset="0x11c.22" size="0x0.10" />
	<field name="qa_group2_ext" descr="" access="RO" offset="0x120.0" size="0x0.11" />
</node>

<node name="sltr_periodic_non_destructive_part2_ext" descr="" size="0x130.0" >
	<field name="hb_group_exist" descr="" access="RO" offset="0x0.13" size="0x0.1" />
	<field name="ai_group_exist" descr="" access="RO" offset="0x0.14" size="0x0.1" />
	<field name="ah_group_exist" descr="" access="RO" offset="0x0.15" size="0x0.1" />
	<field name="ad_group_exist" descr="" access="RO" offset="0x0.16" size="0x0.1" />
	<field name="ac_group_exist" descr="" access="RO" offset="0x0.17" size="0x0.1" />
	<field name="aa_group_exist" descr="" access="RO" offset="0x0.18" size="0x0.1" />
	<field name="jc_group_exist" descr="" access="RO" offset="0x0.19" size="0x0.1" />
	<field name="jb_group_exist" descr="" access="RO" offset="0x0.20" size="0x0.1" />
	<field name="ja_group_exist" descr="" access="RO" offset="0x0.21" size="0x0.1" />
	<field name="g_group_exist" descr="" access="RO" offset="0x0.22" size="0x0.1" />
	<field name="s_group_exist" descr="" access="RO" offset="0x0.23" size="0x0.1" />
	<field name="ha_group_exist" descr="" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="u_group_exist" descr="" access="RO" offset="0x0.25" size="0x0.1" />
	<field name="x_group_exist" descr="" access="RO" offset="0x0.26" size="0x0.1" />
	<field name="ze_group_exist" descr="" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="zd_group_exist" descr="" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="zc_group_exist" descr="" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="zb_group_exist" descr="" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="za_group_exist" descr="" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="za_group4" descr="" access="RO" offset="0x4.2" size="0x0.6" />
	<field name="za_group3" descr="" access="RO" offset="0x4.8" size="0x0.6" />
	<field name="za_group2" descr="" access="RO" offset="0x4.14" size="0x0.6" />
	<field name="za_group1" descr="" access="RO" offset="0x4.20" size="0x0.6" />
	<field name="za_group0" descr="" access="RO" offset="0x4.26" size="0x0.6" />
	<field name="za_group6" descr="" access="RO" offset="0x8.10" size="0x0.16" />
	<field name="za_group5" descr="" access="RO" offset="0x8.26" size="0x0.6" />
	<field name="zb_group4" descr="" access="RO" offset="0xc.2" size="0x0.6" />
	<field name="zb_group3" descr="" access="RO" offset="0xc.8" size="0x0.6" />
	<field name="zb_group2" descr="" access="RO" offset="0xc.14" size="0x0.6" />
	<field name="zb_group1" descr="" access="RO" offset="0xc.20" size="0x0.6" />
	<field name="zb_group0" descr="" access="RO" offset="0xc.26" size="0x0.6" />
	<field name="zb_group6" descr="" access="RO" offset="0x10.10" size="0x0.16" />
	<field name="zb_group5" descr="" access="RO" offset="0x10.26" size="0x0.6" />
	<field name="zc_group4" descr="" access="RO" offset="0x14.2" size="0x0.6" />
	<field name="zc_group3" descr="" access="RO" offset="0x14.8" size="0x0.6" />
	<field name="zc_group2" descr="" access="RO" offset="0x14.14" size="0x0.6" />
	<field name="zc_group1" descr="" access="RO" offset="0x14.20" size="0x0.6" />
	<field name="zc_group0" descr="" access="RO" offset="0x14.26" size="0x0.6" />
	<field name="ze_group1" descr="" access="RO" offset="0x18.4" size="0x0.4" />
	<field name="ze_group0" descr="" access="RO" offset="0x18.8" size="0x0.6" />
	<field name="zd_group1" descr="" access="RO" offset="0x18.15" size="0x0.5" />
	<field name="zd_group0" descr="" access="RO" offset="0x18.20" size="0x0.5" />
	<field name="zc_group5" descr="" access="RO" offset="0x18.26" size="0x0.6" />
	<field name="x_group1" descr="" access="RO" offset="0x1c.0" size="0x0.16" />
	<field name="x_group0" descr="" access="RO" offset="0x1c.16" size="0x0.16" />
	<field name="x_group5" descr="" access="RO" offset="0x20.0" size="0x0.6" />
	<field name="x_group4" descr="" access="RO" offset="0x20.6" size="0x0.4" />
	<field name="x_group3" descr="" access="RO" offset="0x20.10" size="0x0.6" />
	<field name="x_group2" descr="" access="RO" offset="0x20.16" size="0x0.16" />
	<field name="x_group7" descr="" access="RO" offset="0x24.15" size="0x0.13" />
	<field name="x_group6" descr="" access="RO" offset="0x24.28" size="0x0.4" />
	<field name="u_group1" descr="" access="RO" offset="0x28.0" size="0x0.16" />
	<field name="u_group0" descr="" access="RO" offset="0x28.16" size="0x0.16" />
	<field name="u_group3" descr="" access="RO" offset="0x2c.0" size="0x0.16" />
	<field name="u_group2" descr="" access="RO" offset="0x2c.16" size="0x0.16" />
	<field name="u_group5" descr="" access="RO" offset="0x30.0" size="0x0.16" />
	<field name="u_group4" descr="" access="RO" offset="0x30.16" size="0x0.16" />
	<field name="u_group7" descr="" access="RO" offset="0x34.0" size="0x0.16" />
	<field name="u_group6" descr="" access="RO" offset="0x34.16" size="0x0.16" />
	<field name="u_group9" descr="" access="RO" offset="0x38.0" size="0x0.16" />
	<field name="u_group8" descr="" access="RO" offset="0x38.16" size="0x0.16" />
	<field name="u_group11" descr="" access="RO" offset="0x3c.0" size="0x0.16" />
	<field name="u_group10" descr="" access="RO" offset="0x3c.16" size="0x0.16" />
	<field name="u_group13" descr="" access="RO" offset="0x40.0" size="0x0.16" />
	<field name="u_group12" descr="" access="RO" offset="0x40.16" size="0x0.16" />
	<field name="u_group15" descr="" access="RO" offset="0x44.0" size="0x0.16" />
	<field name="u_group14" descr="" access="RO" offset="0x44.16" size="0x0.16" />
	<field name="ha_group" descr="" access="RO" high_bound="15" low_bound="0" offset="0x48.24" size="0x10.0" />
	<field name="hb_group" descr="" access="RO" high_bound="15" low_bound="0" offset="0x58.24" size="0x10.0" />
	<field name="s_group1" descr="" access="RO" offset="0x68.0" size="0x0.16" />
	<field name="s_group0" descr="" access="RO" offset="0x68.16" size="0x0.16" />
	<field name="s_group3" descr="" access="RO" offset="0x6c.0" size="0x0.16" />
	<field name="s_group2" descr="" access="RO" offset="0x6c.16" size="0x0.16" />
	<field name="s_group5" descr="" access="RO" offset="0x70.0" size="0x0.16" />
	<field name="s_group4" descr="" access="RO" offset="0x70.16" size="0x0.16" />
	<field name="s_group7" descr="" access="RO" offset="0x74.0" size="0x0.16" />
	<field name="s_group6" descr="" access="RO" offset="0x74.16" size="0x0.16" />
	<field name="s_group9" descr="" access="RO" offset="0x78.0" size="0x0.16" />
	<field name="s_group8" descr="" access="RO" offset="0x78.16" size="0x0.16" />
	<field name="s_group11" descr="" access="RO" offset="0x7c.0" size="0x0.16" />
	<field name="s_group10" descr="" access="RO" offset="0x7c.16" size="0x0.16" />
	<field name="s_group13" descr="" access="RO" offset="0x80.0" size="0x0.16" />
	<field name="s_group12" descr="" access="RO" offset="0x80.16" size="0x0.16" />
	<field name="s_group15" descr="" access="RO" offset="0x84.0" size="0x0.16" />
	<field name="s_group14" descr="" access="RO" offset="0x84.16" size="0x0.16" />
	<field name="g_group1" descr="" access="RO" offset="0x88.0" size="0x0.16" />
	<field name="g_group0" descr="" access="RO" offset="0x88.16" size="0x0.16" />
	<field name="g_group3" descr="" access="RO" offset="0x8c.0" size="0x0.16" />
	<field name="g_group2" descr="" access="RO" offset="0x8c.16" size="0x0.16" />
	<field name="g_group5" descr="" access="RO" offset="0x90.0" size="0x0.16" />
	<field name="g_group4" descr="" access="RO" offset="0x90.16" size="0x0.16" />
	<field name="g_group7" descr="" access="RO" offset="0x94.0" size="0x0.16" />
	<field name="g_group6" descr="" access="RO" offset="0x94.16" size="0x0.16" />
	<field name="g_group9" descr="" access="RO" offset="0x98.0" size="0x0.16" />
	<field name="g_group8" descr="" access="RO" offset="0x98.16" size="0x0.16" />
	<field name="ja_group" descr="" access="RO" high_bound="27" low_bound="0" offset="0x9c.24" size="0x1c.0" />
	<field name="jb_group2" descr="" access="RO" offset="0xb8.0" size="0x0.9" />
	<field name="jb_group1" descr="" access="RO" offset="0xb8.11" size="0x0.9" />
	<field name="jb_group0" descr="" access="RO" offset="0xb8.23" size="0x0.9" />
	<field name="jb_group5" descr="" access="RO" offset="0xbc.0" size="0x0.9" />
	<field name="jb_group4" descr="" access="RO" offset="0xbc.11" size="0x0.9" />
	<field name="jb_group3" descr="" access="RO" offset="0xbc.23" size="0x0.9" />
	<field name="jb_group8" descr="" access="RO" offset="0xc0.0" size="0x0.9" />
	<field name="jb_group7" descr="" access="RO" offset="0xc0.11" size="0x0.9" />
	<field name="jb_group6" descr="" access="RO" offset="0xc0.23" size="0x0.9" />
	<field name="jb_group11" descr="" access="RO" offset="0xc4.0" size="0x0.9" />
	<field name="jb_group10" descr="" access="RO" offset="0xc4.11" size="0x0.9" />
	<field name="jb_group9" descr="" access="RO" offset="0xc4.23" size="0x0.9" />
	<field name="jb_group14" descr="" access="RO" offset="0xc8.0" size="0x0.9" />
	<field name="jb_group13" descr="" access="RO" offset="0xc8.11" size="0x0.9" />
	<field name="jb_group12" descr="" access="RO" offset="0xc8.23" size="0x0.9" />
	<field name="jb_group17" descr="" access="RO" offset="0xcc.0" size="0x0.9" />
	<field name="jb_group16" descr="" access="RO" offset="0xcc.11" size="0x0.9" />
	<field name="jb_group15" descr="" access="RO" offset="0xcc.23" size="0x0.9" />
	<field name="jb_group20" descr="" access="RO" offset="0xd0.0" size="0x0.9" />
	<field name="jb_group19" descr="" access="RO" offset="0xd0.11" size="0x0.9" />
	<field name="jb_group18" descr="" access="RO" offset="0xd0.23" size="0x0.9" />
	<field name="jb_group23" descr="" access="RO" offset="0xd4.0" size="0x0.9" />
	<field name="jb_group22" descr="" access="RO" offset="0xd4.11" size="0x0.9" />
	<field name="jb_group21" descr="" access="RO" offset="0xd4.23" size="0x0.9" />
	<field name="jb_group26" descr="" access="RO" offset="0xd8.0" size="0x0.9" />
	<field name="jb_group25" descr="" access="RO" offset="0xd8.11" size="0x0.9" />
	<field name="jb_group24" descr="" access="RO" offset="0xd8.23" size="0x0.9" />
	<field name="jc_group0" descr="" access="RO" offset="0xdc.7" size="0x0.13" />
	<field name="jb_group27" descr="" access="RO" offset="0xdc.23" size="0x0.9" />
	<field name="jc_group2" descr="" access="RO" offset="0xe0.5" size="0x0.13" />
	<field name="jc_group1" descr="" access="RO" offset="0xe0.19" size="0x0.13" />
	<field name="aa_group1" descr="" access="RO" offset="0xe4.24" size="0x0.3" />
	<field name="aa_group0" descr="" access="RO" offset="0xe4.27" size="0x0.5" />
	<field name="ac_group1" descr="" access="RO" offset="0xe8.0" size="0x0.16" />
	<field name="ac_group0" descr="" access="RO" offset="0xe8.16" size="0x0.16" />
	<field name="ad_group8" descr="" access="RO" offset="0xec.3" size="0x0.4" />
	<field name="ad_group7" descr="" access="RO" offset="0xec.7" size="0x0.3" />
	<field name="ad_group6" descr="" access="RO" offset="0xec.10" size="0x0.1" />
	<field name="ad_group5" descr="" access="RO" offset="0xec.11" size="0x0.5" />
	<field name="ad_group4" descr="" access="RO" offset="0xec.16" size="0x0.5" />
	<field name="ad_group3" descr="" access="RO" offset="0xec.21" size="0x0.2" />
	<field name="ad_group2" descr="" access="RO" offset="0xec.23" size="0x0.2" />
	<field name="ad_group1" descr="" access="RO" offset="0xec.25" size="0x0.4" />
	<field name="ad_group0" descr="" access="RO" offset="0xec.29" size="0x0.3" />
	<field name="ah_group2" descr="" access="RO" offset="0xf0.0" size="0x0.5" />
	<field name="ah_group1" descr="" access="RO" offset="0xf0.5" size="0x0.5" />
	<field name="ah_group0" descr="" access="RO" offset="0xf0.10" size="0x0.16" />
	<field name="ad_group9" descr="" access="RO" offset="0xf0.27" size="0x0.5" />
	<field name="ai_group1" descr="" access="RO" offset="0xf4.0" size="0x0.6" />
	<field name="ai_group0" descr="" access="RO" offset="0xf4.6" size="0x0.6" />
	<field name="ah_group4" descr="" access="RO" offset="0xf4.19" size="0x0.6" />
	<field name="ah_group3" descr="" access="RO" offset="0xf4.25" size="0x0.7" />
	<field name="ai_group6" descr="" access="RO" offset="0xf8.2" size="0x0.6" />
	<field name="ai_group5" descr="" access="RO" offset="0xf8.8" size="0x0.6" />
	<field name="ai_group4" descr="" access="RO" offset="0xf8.14" size="0x0.6" />
	<field name="ai_group3" descr="" access="RO" offset="0xf8.20" size="0x0.6" />
	<field name="ai_group2" descr="" access="RO" offset="0xf8.26" size="0x0.6" />
	<field name="ai_group11" descr="" access="RO" offset="0xfc.2" size="0x0.6" />
	<field name="ai_group10" descr="" access="RO" offset="0xfc.8" size="0x0.6" />
	<field name="ai_group9" descr="" access="RO" offset="0xfc.14" size="0x0.6" />
	<field name="ai_group8" descr="" access="RO" offset="0xfc.20" size="0x0.6" />
	<field name="ai_group7" descr="" access="RO" offset="0xfc.26" size="0x0.6" />
	<field name="ai_group16" descr="" access="RO" offset="0x100.2" size="0x0.6" />
	<field name="ai_group15" descr="" access="RO" offset="0x100.8" size="0x0.6" />
	<field name="ai_group14" descr="" access="RO" offset="0x100.14" size="0x0.6" />
	<field name="ai_group13" descr="" access="RO" offset="0x100.20" size="0x0.6" />
	<field name="ai_group12" descr="" access="RO" offset="0x100.26" size="0x0.6" />
	<field name="ai_group21" descr="" access="RO" offset="0x104.2" size="0x0.6" />
	<field name="ai_group20" descr="" access="RO" offset="0x104.8" size="0x0.6" />
	<field name="ai_group19" descr="" access="RO" offset="0x104.14" size="0x0.6" />
	<field name="ai_group18" descr="" access="RO" offset="0x104.20" size="0x0.6" />
	<field name="ai_group17" descr="" access="RO" offset="0x104.26" size="0x0.6" />
	<field name="ai_group26" descr="" access="RO" offset="0x108.2" size="0x0.6" />
	<field name="ai_group25" descr="" access="RO" offset="0x108.8" size="0x0.6" />
	<field name="ai_group24" descr="" access="RO" offset="0x108.14" size="0x0.6" />
	<field name="ai_group23" descr="" access="RO" offset="0x108.20" size="0x0.6" />
	<field name="ai_group22" descr="" access="RO" offset="0x108.26" size="0x0.6" />
	<field name="ai_group31" descr="" access="RO" offset="0x10c.2" size="0x0.6" />
	<field name="ai_group30" descr="" access="RO" offset="0x10c.8" size="0x0.6" />
	<field name="ai_group29" descr="" access="RO" offset="0x10c.14" size="0x0.6" />
	<field name="ai_group28" descr="" access="RO" offset="0x10c.20" size="0x0.6" />
	<field name="ai_group27" descr="" access="RO" offset="0x10c.26" size="0x0.6" />
	<field name="ai_group36" descr="" access="RO" offset="0x110.2" size="0x0.6" />
	<field name="ai_group35" descr="" access="RO" offset="0x110.8" size="0x0.6" />
	<field name="ai_group34" descr="" access="RO" offset="0x110.14" size="0x0.6" />
	<field name="ai_group33" descr="" access="RO" offset="0x110.20" size="0x0.6" />
	<field name="ai_group32" descr="" access="RO" offset="0x110.26" size="0x0.6" />
	<field name="ai_group41" descr="" access="RO" offset="0x114.2" size="0x0.6" />
	<field name="ai_group40" descr="" access="RO" offset="0x114.8" size="0x0.6" />
	<field name="ai_group39" descr="" access="RO" offset="0x114.14" size="0x0.6" />
	<field name="ai_group38" descr="" access="RO" offset="0x114.20" size="0x0.6" />
	<field name="ai_group37" descr="" access="RO" offset="0x114.26" size="0x0.6" />
	<field name="ai_group46" descr="" access="RO" offset="0x118.2" size="0x0.6" />
	<field name="ai_group45" descr="" access="RO" offset="0x118.8" size="0x0.6" />
	<field name="ai_group44" descr="" access="RO" offset="0x118.14" size="0x0.6" />
	<field name="ai_group43" descr="" access="RO" offset="0x118.20" size="0x0.6" />
	<field name="ai_group42" descr="" access="RO" offset="0x118.26" size="0x0.6" />
	<field name="ai_group51" descr="" access="RO" offset="0x11c.2" size="0x0.6" />
	<field name="ai_group50" descr="" access="RO" offset="0x11c.8" size="0x0.6" />
	<field name="ai_group49" descr="" access="RO" offset="0x11c.14" size="0x0.6" />
	<field name="ai_group48" descr="" access="RO" offset="0x11c.20" size="0x0.6" />
	<field name="ai_group47" descr="" access="RO" offset="0x11c.26" size="0x0.6" />
	<field name="ai_group56" descr="" access="RO" offset="0x120.2" size="0x0.6" />
	<field name="ai_group55" descr="" access="RO" offset="0x120.8" size="0x0.6" />
	<field name="ai_group54" descr="" access="RO" offset="0x120.14" size="0x0.6" />
	<field name="ai_group53" descr="" access="RO" offset="0x120.20" size="0x0.6" />
	<field name="ai_group52" descr="" access="RO" offset="0x120.26" size="0x0.6" />
	<field name="ai_group61" descr="" access="RO" offset="0x124.2" size="0x0.6" />
	<field name="ai_group60" descr="" access="RO" offset="0x124.8" size="0x0.6" />
	<field name="ai_group59" descr="" access="RO" offset="0x124.14" size="0x0.6" />
	<field name="ai_group58" descr="" access="RO" offset="0x124.20" size="0x0.6" />
	<field name="ai_group57" descr="" access="RO" offset="0x124.26" size="0x0.6" />
	<field name="ai_group63" descr="" access="RO" offset="0x128.20" size="0x0.6" />
	<field name="ai_group62" descr="" access="RO" offset="0x128.26" size="0x0.6" />
</node>

<node name="sltr_periodic_non_destructive_part3_ext" descr="" size="0xc4.0" >
	<field name="n_group_exist" descr="" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="n_group1" descr="" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="n_group0" descr="" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="n_group3" descr="" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="n_group2" descr="" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="n_group5" descr="" access="RO" offset="0xc.0" size="0x0.16" />
	<field name="n_group4" descr="" access="RO" offset="0xc.16" size="0x0.16" />
	<field name="n_group7" descr="" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="n_group6" descr="" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="n_group9" descr="" access="RO" offset="0x14.0" size="0x0.16" />
	<field name="n_group8" descr="" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="n_group11" descr="" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="n_group10" descr="" access="RO" offset="0x18.16" size="0x0.16" />
	<field name="n_group13" descr="" access="RO" offset="0x1c.0" size="0x0.16" />
	<field name="n_group12" descr="" access="RO" offset="0x1c.16" size="0x0.16" />
	<field name="n_group15" descr="" access="RO" offset="0x20.0" size="0x0.16" />
	<field name="n_group14" descr="" access="RO" offset="0x20.16" size="0x0.16" />
	<field name="n_group17" descr="" access="RO" offset="0x24.0" size="0x0.16" />
	<field name="n_group16" descr="" access="RO" offset="0x24.16" size="0x0.16" />
	<field name="n_group19" descr="" access="RO" offset="0x28.0" size="0x0.16" />
	<field name="n_group18" descr="" access="RO" offset="0x28.16" size="0x0.16" />
	<field name="n_group21" descr="" access="RO" offset="0x2c.0" size="0x0.16" />
	<field name="n_group20" descr="" access="RO" offset="0x2c.16" size="0x0.16" />
	<field name="n_group23" descr="" access="RO" offset="0x30.0" size="0x0.16" />
	<field name="n_group22" descr="" access="RO" offset="0x30.16" size="0x0.16" />
	<field name="n_group25" descr="" access="RO" offset="0x34.0" size="0x0.16" />
	<field name="n_group24" descr="" access="RO" offset="0x34.16" size="0x0.16" />
	<field name="n_group27" descr="" access="RO" offset="0x38.0" size="0x0.16" />
	<field name="n_group26" descr="" access="RO" offset="0x38.16" size="0x0.16" />
	<field name="n_group29" descr="" access="RO" offset="0x3c.0" size="0x0.16" />
	<field name="n_group28" descr="" access="RO" offset="0x3c.16" size="0x0.16" />
	<field name="n_group31" descr="" access="RO" offset="0x40.0" size="0x0.16" />
	<field name="n_group30" descr="" access="RO" offset="0x40.16" size="0x0.16" />
	<field name="n_group33" descr="" access="RO" offset="0x44.0" size="0x0.16" />
	<field name="n_group32" descr="" access="RO" offset="0x44.16" size="0x0.16" />
	<field name="n_group35" descr="" access="RO" offset="0x48.0" size="0x0.16" />
	<field name="n_group34" descr="" access="RO" offset="0x48.16" size="0x0.16" />
	<field name="n_group37" descr="" access="RO" offset="0x4c.0" size="0x0.16" />
	<field name="n_group36" descr="" access="RO" offset="0x4c.16" size="0x0.16" />
	<field name="n_group39" descr="" access="RO" offset="0x50.0" size="0x0.16" />
	<field name="n_group38" descr="" access="RO" offset="0x50.16" size="0x0.16" />
	<field name="n_group41" descr="" access="RO" offset="0x54.0" size="0x0.16" />
	<field name="n_group40" descr="" access="RO" offset="0x54.16" size="0x0.16" />
	<field name="n_group43" descr="" access="RO" offset="0x58.0" size="0x0.16" />
	<field name="n_group42" descr="" access="RO" offset="0x58.16" size="0x0.16" />
	<field name="n_group45" descr="" access="RO" offset="0x5c.0" size="0x0.16" />
	<field name="n_group44" descr="" access="RO" offset="0x5c.16" size="0x0.16" />
	<field name="n_group47" descr="" access="RO" offset="0x60.0" size="0x0.16" />
	<field name="n_group46" descr="" access="RO" offset="0x60.16" size="0x0.16" />
	<field name="n_group49" descr="" access="RO" offset="0x64.0" size="0x0.16" />
	<field name="n_group48" descr="" access="RO" offset="0x64.16" size="0x0.16" />
	<field name="n_group51" descr="" access="RO" offset="0x68.0" size="0x0.16" />
	<field name="n_group50" descr="" access="RO" offset="0x68.16" size="0x0.16" />
	<field name="n_group53" descr="" access="RO" offset="0x6c.0" size="0x0.16" />
	<field name="n_group52" descr="" access="RO" offset="0x6c.16" size="0x0.16" />
	<field name="n_group55" descr="" access="RO" offset="0x70.0" size="0x0.16" />
	<field name="n_group54" descr="" access="RO" offset="0x70.16" size="0x0.16" />
	<field name="n_group57" descr="" access="RO" offset="0x74.0" size="0x0.16" />
	<field name="n_group56" descr="" access="RO" offset="0x74.16" size="0x0.16" />
	<field name="n_group59" descr="" access="RO" offset="0x78.0" size="0x0.16" />
	<field name="n_group58" descr="" access="RO" offset="0x78.16" size="0x0.16" />
	<field name="n_group61" descr="" access="RO" offset="0x7c.0" size="0x0.16" />
	<field name="n_group60" descr="" access="RO" offset="0x7c.16" size="0x0.16" />
	<field name="n_group63" descr="" access="RO" offset="0x80.0" size="0x0.16" />
	<field name="n_group62" descr="" access="RO" offset="0x80.16" size="0x0.16" />
	<field name="n_group65" descr="" access="RO" offset="0x84.0" size="0x0.16" />
	<field name="n_group64" descr="" access="RO" offset="0x84.16" size="0x0.16" />
	<field name="n_group67" descr="" access="RO" offset="0x88.0" size="0x0.16" />
	<field name="n_group66" descr="" access="RO" offset="0x88.16" size="0x0.16" />
	<field name="n_group69" descr="" access="RO" offset="0x8c.0" size="0x0.16" />
	<field name="n_group68" descr="" access="RO" offset="0x8c.16" size="0x0.16" />
	<field name="n_group71" descr="" access="RO" offset="0x90.0" size="0x0.16" />
	<field name="n_group70" descr="" access="RO" offset="0x90.16" size="0x0.16" />
	<field name="n_group73" descr="" access="RO" offset="0x94.0" size="0x0.16" />
	<field name="n_group72" descr="" access="RO" offset="0x94.16" size="0x0.16" />
	<field name="n_group75" descr="" access="RO" offset="0x98.0" size="0x0.16" />
	<field name="n_group74" descr="" access="RO" offset="0x98.16" size="0x0.16" />
	<field name="n_group77" descr="" access="RO" offset="0x9c.0" size="0x0.16" />
	<field name="n_group76" descr="" access="RO" offset="0x9c.16" size="0x0.16" />
	<field name="n_group79" descr="" access="RO" offset="0xa0.0" size="0x0.16" />
	<field name="n_group78" descr="" access="RO" offset="0xa0.16" size="0x0.16" />
	<field name="n_group81" descr="" access="RO" offset="0xa4.0" size="0x0.16" />
	<field name="n_group80" descr="" access="RO" offset="0xa4.16" size="0x0.16" />
	<field name="n_group83" descr="" access="RO" offset="0xa8.0" size="0x0.16" />
	<field name="n_group82" descr="" access="RO" offset="0xa8.16" size="0x0.16" />
	<field name="n_group85" descr="" access="RO" offset="0xac.0" size="0x0.16" />
	<field name="n_group84" descr="" access="RO" offset="0xac.16" size="0x0.16" />
	<field name="n_group87" descr="" access="RO" offset="0xb0.0" size="0x0.16" />
	<field name="n_group86" descr="" access="RO" offset="0xb0.16" size="0x0.16" />
	<field name="n_group89" descr="" access="RO" offset="0xb4.0" size="0x0.16" />
	<field name="n_group88" descr="" access="RO" offset="0xb4.16" size="0x0.16" />
	<field name="n_group91" descr="" access="RO" offset="0xb8.0" size="0x0.16" />
	<field name="n_group90" descr="" access="RO" offset="0xb8.16" size="0x0.16" />
	<field name="n_group93" descr="" access="RO" offset="0xbc.0" size="0x0.16" />
	<field name="n_group92" descr="" access="RO" offset="0xbc.16" size="0x0.16" />
	<field name="n_group95" descr="" access="RO" offset="0xc0.0" size="0x0.16" />
	<field name="n_group94" descr="" access="RO" offset="0xc0.16" size="0x0.16" />
</node>

<node name="stat_bufferx_reg_ext" descr="" size="0x8.0" >
	<field name="watermark" descr="Watermark in cells (max buffer usage since last clear)For stat_shared_headroom_pool, this field is reserved." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="used_buffer" descr="Number of used buffer cells.For stat_port_shared_headroom_pool this field is reserved." access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="string_db_parameters_ext" descr="" size="0x8.0" >
	<field name="string_db_base_address" descr="Offset of the first string of the section, relative to the entire string\;data base, given in bytes." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="string_db_size" descr="Size of string database section, given in bytes" access="RO" offset="0x4.0" size="0x0.24" />
</node>

<node name="uint64" descr="" size="0x8.0" >
	<field name="hi" descr="" access="RW" offset="0x0.0" size="0x4.0" />
	<field name="lo" descr="" access="RW" offset="0x4.0" size="0x4.0" />
</node>

<node name="ukdri_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clear" descr="Clear Indications" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="ktu_disccard_vec" descr="Per bit:Bit0: VersionFail - Version is not zeroBit1: ProtocolTypeFail - Protocol is not correctBit2: MsgVSActualSizeFail - Msg size does not match actual sizeBit3: SkMtdNotExist - No MTD in SK messageBit4: SkMtdAlignment - MTD in SK is not DW alignBit5: SkSecAlignment - SEC in SK in not DW alignBit6: MsgSizeVsDsHeaderFail - Msg size vs header mismatchBit7: MsgSizeTooSmall - Actual header size is smaller then minimum size." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="nvle_msg_disccard_vec" descr="Per bit:Bit0: MsgSizeNotMatchOpcode - MSG size does not match the opcodeBit1: VersionFail - NVLE wrong versionBit2: CmdOpcodeFail - Wrong NVLE cmd_opcodeBit3: PortNumFail - Wrong port number in NVLE headerBit4: PipeNumFail - Invalid pipe numberBit5: DataSizeFail - wrong data sizeBit6: SlotIndexFail - Invalid slot indexBit7: NVLEMsgSizeTooSmall - NVLE msg size is smaller then 3." access="RO" offset="0xc.0" size="0x4.0" />
</node>

<node name="undfd_ext" descr="" size="0x8.0" >
	<field name="pipe_index" descr="PipeFor GB100 can be either 0 or 1" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="local_port" descr="" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="dfd_en" descr="DFD en, when enabled the encryption will set an authentication error\;tag:0: DFD disabled (default)1: DFD enabled" access="RW" offset="0x4.0" size="0x0.1" />
</node>

<node name="undri_ext" descr="" size="0x10.0" >
	<field name="pipe_index" descr="PipeFor GB100 can be either 0 or 1" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="dir" descr="Direction:0: Decr1: Encr" access="INDEX" offset="0x0.12" size="0x0.1" />
	<field name="local_port" descr="Local port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clear" descr="Clear Indications" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="discard_vec" descr="Per bit:Bit0: BadPktTypeBit1: NoNVSecTagBit2: NvsetagBadVersionBit3: BadPktLenBit4: PktLenMinSizeBit5: AR_MissMatchBit6: FlowMapEntryNotValidBit7: StateEntryNotValidBit8: KeyEntryNotValidBit9: FeedbackOverrunBit10: NVSecTagErrorBit11: NVLECreditIssueDecryption only:Bit12: AuthenticationFailBit13: ReplayFail" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="unrc_ext" descr="" size="0x40.0" >
	<field name="pipe_index" descr="PipeFor GB100 can be either 0 or 1" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="local_port" descr="" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clear" descr="Clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="ing_error_packets" descr="count number of error packets ingressing to the NVLE.Note: this counter count all the error packet in NVLE - it includes the\;ing_auth_error counter.For counter layout see Counter Layout" subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
	<field name="ing_good_packets" descr="count number of good packets ingressing the NVLEFor counter layout see\;Counter Layout" subnode="uint64" access="RO" offset="0x18.0" size="0x8.0" />
	<field name="egr_good_packets" descr="count number of good packets egressing the NVLEFor counter layout see\;Counter Layout" subnode="uint64" access="RO" offset="0x20.0" size="0x8.0" />
	<field name="egr_error_packets" descr="count number of error packets egressing the NVLENote: egr_good_packets + egr_error_packets = sum of all packets\;egressing the NVLEFor counter layout see Counter Layout" subnode="uint64" access="RO" offset="0x28.0" size="0x8.0" />
	<field name="ktu_msg_cnt" descr="Number of messages that was sent from the KTU to the NVLEs.Note - this counter is not per pipe.For counter layout see Counter Layout" subnode="uint64" access="RO" offset="0x30.0" size="0x8.0" />
	<field name="ing_auth_error" descr="Number of authentication errors.For counter layout see Counter Layout" subnode="uint64" access="RO" offset="0x38.0" size="0x8.0" />
</node>

<node name="unrsa_ext" descr="" size="0x18.0" >
	<field name="pipe_index" descr="PipeFor GB100 can be either 0 or 1" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="dir" descr="Direction:0: Decr1: Encr" access="INDEX" offset="0x0.12" size="0x0.1" />
	<field name="local_port" descr="" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="entry_index" descr="Entry Index.Decr range 0..max_cap_sec_key_entry * 2 + 1Encr range 0..max_cap_sec_key_entry" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="ev" descr="Entry Valid:0: Entry is not valid1: Entry is validAll RO fields have no meaning when ev=0" access="RO" offset="0x8.24" size="0x0.1" />
	<field name="packet_number" descr="Packet numberNote: GB100 HW has only 56 bitsFW note: for Decr read from expected packet number, for Encr read from\;SADB" subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="unwkm_ext" descr="" size="0x8c.0" >
	<field name="status" descr="Return status:0: OKFW will parse these fields and set the relevant bit if the value is not\;valid (1-4 are only for SK):Bit1: ktu_msg.SK.common_header_version!=0Bit2: ktu_msg.SK.Protocol != NVLEBit3: ktu_msg.SK.nvle_version !=0Bit4: ktu_msg.SK.hw_port == not_validBit5: ktu_msg.op != 1, 2, 3Bit6: ktu_msg.size \&gt; 22Bit15: at least one of the bits in errors is set" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="local_port" descr="Local port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lpv" descr="Local port valid:0: local_port field is reserved. FW will look at ktu_msg1: local_port is valid. FW will ignore hw_port in ktu_msg if exist." access="OP" offset="0x0.31" size="0x0.1" />
	<field name="errors" descr="KTU error vector, each error set the corresponding bit in the error\;vector:Bit3: CMD_VER_ERR - the command is specified with unsupported\;KTU_CMD.VER.Bit4: CMD_OP_ERR - the command is specified with unsupported KTU_CMD.OP.Bit5: CMD_AA_ERR - The command is specified with unsupported KTU_CMD.AA\;for the givenKTU_CMD.OP.Bit6: CMD_ARG_ERR - The command is specified with unsupported\;KTU_CMD.ARGs for the givenKTU_CMD.OP.Bit8: INS_IWK_DIS_ERR - INS_IWK command is started but INS_IWK was\;disabled.Bit9: INS_WK_DIS_ERR - INS_WK command is started but INS_WK was\;disabled.Bit10: INS_SK_DIS_ERR - INS_SK command is startedbut INS_SK was disabled.Bit11: INS_WK_NWK_ERR - INS_WK command is started but no previous valid\;WK is available.Bit12: INS_SK_NWK_ERR - INS_SK command is started but no valid WK is\;available.Bit14: CMD_AUTH_ERR - The authentication check of the triggered command\;fails.Bit16: ANTI_REPLAY_CNT_CHK_ERR - Anti-replay Counter check fails.Bit17: OUTPUT_ERR - Output to the downstream unit is returned with error\;responses.Bit31: MAX_CMD_FAILURE_ERR - 10 commands failure. the count resets after\;IWK or WK succeeds." access="RW" offset="0x4.0" size="0x4.0" />
	<field name="ktu_msg" descr="KTU Message LayoutFW will extract these fields of the CM:protocol type - make sure KUW TBD ‘0’version - make sure FW can parse this version TBD 0hw_port - note: hw port = local_port-1Note: this is a WO field, cannot be read" access="WO" high_bound="31" low_bound="0" offset="0xc.0" size="0x80.0" />
</node>

<node name="root" size="0x410.0" descr="" >
	<field name="register_access_table_gpu_Nodes" offset="0x0.0" size="0x410.0" subnode="register_access_table_gpu_Nodes" descr="" />
</node>

<node name="register_access_table_gpu_Nodes" size="0x410.0" attr_is_union="1" descr="" >
	<field name="access_reg_summary_selector_ext" offset="0x0.0" size="0x410.0" subnode="access_reg_summary_selector_ext" descr="" />
</node>
</NodesDefinition>
