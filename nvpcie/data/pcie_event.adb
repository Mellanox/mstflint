<NodesDefinition version="2">
    <node name="pcie_event_tlv" size="0x40.0" segment_id="0x107c" descr="NVLOG TLV carrying a PCIe Events Log entry">
        <field name="event_header" subnode="nvlog_tlv_extra_data" offset="0x0.0" size="0x10.0" />
        <field name="pcie_event" subnode="pcie_event" offset="0x10.0" size="0x30.0" />
    </node>

    <node name="pcie_event" size="0x30.0" attr_is_union="1" descr="PCIe Events Log entry">
        <field name="event_id" offset="0x0.0" size="0x0.8" enum="FW_INFORMATION=0x1,LINK_STATUS_CHANGE=0x2,HOT_PLUG=0x3,AER_UNCORRECTABLE=0x4,AER_CORRECTABLE=0x5,PCIE_CONFIGURATION=0x6,DPC=0x7,L23=0x8" />
        <field name="length" descr="Payload length in DWs, not including the first DW" offset="0x0.8" size="0x0.4" />
        <field name="payload" offset="0x0.0" size="0x30.0" union_selector="$(parent).event_id" subnode="pcie_event_payload_union" />
    </node>

    <node name="pcie_event_payload_union" size="0x30.0" attr_is_union="1">
        <field name="fw_information" offset="0x0.0" size="0xc.0" selected_by="FW_INFORMATION" subnode="fw_information_payload" event_class="non-critical" format="fw major {fw_major} | minor {fw_minor} | sub minor {fw_sub_minor} | hash {fw_hash_1}" />
        <field name="link_status_change" offset="0x0.0" size="0x8.0" selected_by="LINK_STATUS_CHANGE" subnode="link_status_change_payload" event_class="critical" format="link {link_status} {link_width} {link_speed} | dl {dlactive} | flit {flit_status}\nperst {is_perst} | directed {is_directed}" />
        <field name="hot_plug" offset="0x0.0" size="0x8.0" selected_by="HOT_PLUG" subnode="hot_plug_payload" event_class="non-critical" format="slot {physical_slot_number} | event {slot_events} | value {event_value}" />
        <field name="aer_uncorrectable" offset="0x0.0" size="0x30.0" selected_by="AER_UNCORRECTABLE" subnode="aer_uncorrectable_payload" event_class="critical" format="status {error_status} | mask {mask} | severity {severity} | first error pointer {first_error_pointer}\nheader log {header_log[0]} {header_log[1]} {header_log[2]} {header_log[3]}\nprefix {prefix[0]} {prefix[1]} {prefix[2]} {prefix[3]}" />
        <field name="aer_correctable" offset="0x0.0" size="0xc.0" selected_by="AER_CORRECTABLE" subnode="aer_correctable_payload" event_class="non-critical" format="status {error_status} | mask {mask}" />
        <field name="pcie_configuration" offset="0x0.0" size="0x8.0" selected_by="PCIE_CONFIGURATION" subnode="pcie_configuration_payload" event_class="non-critical" format="mse {mse} | bme {bme} | tag {tag_type}\nmax payload tx {max_tx_payload_size} rx {max_rx_payload_size} | max read request {max_read_request}" />
        <field name="dpc" offset="0x0.0" size="0x4.0" selected_by="DPC" subnode="dpc_payload" event_class="critical" format="dpc {dpc_triggered} | trigger {trigger_reason} | extended {extended_reason}\ninterrupt {interrupt_triggered} | err_cor {error_correctable_triggered}" />
        <field name="l23" offset="0x0.0" size="0x4.0" selected_by="L23" subnode="l23_payload" format="" />
    </node>

    <node name="fw_information_payload" size="0xc.0" descr="Event ID 0x1, Length = 2DW">
        <field name="fw_major" offset="0x0.16" size="0x0.16" />
        <field name="fw_sub_minor" offset="0x4.16" size="0x0.16" />
        <field name="fw_minor" offset="0x4.0" size="0x0.16" />
        <field name="fw_hash_1" offset="0x8.0" size="0x4.0" />
    </node>

    <node name="link_status_change_payload" size="0x8.0" descr="Event ID 0x2, Length = 1DW">
        <field name="bus" offset="0x0.24" size="0x0.8" />
        <field name="node" offset="0x0.20" size="0x0.4" />
        <field name="pcie_index" offset="0x0.16" size="0x0.4" />
        <field name="depth" offset="0x0.12" size="0x0.4" />
        <field name="is_perst" offset="0x4.20" size="0x0.1" enum="none=0x0,asserted=0x1" />
        <field name="dlactive" offset="0x4.19" size="0x0.1" enum="inactive=0x0,active=0x1" />
        <field name="is_directed" offset="0x4.18" size="0x0.1" enum="no=0x0,yes=0x1" />
        <field name="flit_status" offset="0x4.17" size="0x0.1" enum="disabled=0x0,enabled=0x1" />
        <field name="link_status" offset="0x4.16" size="0x0.1" enum="DOWN=0x0,UP=0x1" />
        <field name="link_width" offset="0x4.12" size="0x0.4" enum="_N/A_=0x0,x1=0x1,x2=0x2,x4=0x3,x8=0x4,x16=0x5,x32=0x6" />
        <field name="link_speed" offset="0x4.8" size="0x0.4" enum="_N/A_=0x0,Gen1=0x1,Gen2=0x2,Gen3=0x3,Gen4=0x4,Gen5=0x5,Gen6=0x6" />
        <field name="function" offset="0x4.5" size="0x0.3" />
        <field name="device" offset="0x4.0" size="0x0.5" />
    </node>

    <node name="hot_plug_payload" size="0x8.0" descr="Event ID 0x3, Length = 1DW">
        <field name="bus" offset="0x0.24" size="0x0.8" />
        <field name="node" offset="0x0.20" size="0x0.4" />
        <field name="pcie_index" offset="0x0.16" size="0x0.4" />
        <field name="depth" offset="0x0.12" size="0x0.4" />
        <field name="event_value" offset="0x4.16" size="0x0.2" />
        <field name="slot_events" offset="0x4.13" size="0x0.3" enum="ATTENTION_BUTTON_PRESS=0x0,POWER_FAULT_DETECTED=0x1,MRL_SENSOR_CHANGE=0x2,PRESENCE_DATA_CHANGED=0x3,POWER_CONTROLLER_CONTROL_CHANGED=0x4,POWER_INDICATOR_CONTROL_CHANGED=0x5,ATTENTION_INDICATOR_CONTROL_CHANGED=0x6,INVALID=0x7" />
        <field name="physical_slot_number" offset="0x4.8" size="0x0.5" />
        <field name="function" offset="0x4.5" size="0x0.3" />
        <field name="device" offset="0x4.0" size="0x0.5" />
    </node>

    <node name="aer_uncorrectable_payload" size="0x30.0" descr="Event ID 0x4, Length = 11DW">
        <field name="first_error_pointer" offset="0x0.24" size="0x0.5" />
        <field name="node" offset="0x0.20" size="0x0.4" />
        <field name="pcie_index" offset="0x0.16" size="0x0.4" />
        <field name="depth" offset="0x0.12" size="0x0.4" />
        <field name="error_status" offset="0x4.0" size="0x4.0" />
        <field name="mask" offset="0x8.0" size="0x4.0" />
        <field name="severity" offset="0xc.0" size="0x4.0" />
        <field name="header_log" offset="0x10.0" size="0x10.0" low_bound="0" high_bound="3" />
        <field name="prefix" offset="0x20.0" size="0x10.0" low_bound="0" high_bound="3" />
    </node>

    <node name="aer_correctable_payload" size="0xc.0" descr="Event ID 0x5, Length = 2DW">
        <field name="node" offset="0x0.20" size="0x0.4" />
        <field name="pcie_index" offset="0x0.16" size="0x0.4" />
        <field name="depth" offset="0x0.12" size="0x0.4" />
        <field name="error_status" offset="0x4.0" size="0x4.0" />
        <field name="mask" offset="0x8.0" size="0x4.0" />
    </node>

    <node name="pcie_configuration_payload" size="0x8.0" descr="Event ID 0x6, Length = 1DW">
        <field name="mse" descr="Memory Space Enable" offset="0x0.25" size="0x0.1" enum="DISABLE=0x0,ENABLE=0x1" />
        <field name="bme" descr="Bus Master Enable" offset="0x0.24" size="0x0.1" enum="DISABLE=0x0,ENABLE=0x1" />
        <field name="node" offset="0x0.20" size="0x0.4" />
        <field name="pcie_index" offset="0x0.16" size="0x0.4" />
        <field name="depth" offset="0x0.12" size="0x0.4" />
        <field name="tag_type" descr="Widest tag the requester is enabled for" offset="0x4.12" size="0x0.3" enum="TAG_5BIT=0x0,TAG_8BIT=0x1,TAG_10BIT=0x2,TAG_14BIT=0x3" />
        <field name="max_tx_payload_size" offset="0x4.8" size="0x0.4" enum="NONE=0x0,B128=0x1,B256=0x2,B512=0x3,B1024=0x4,B2048=0x5,B4096=0x6" />
        <field name="max_rx_payload_size" offset="0x4.4" size="0x0.4" enum="NONE=0x0,B128=0x1,B256=0x2,B512=0x3,B1024=0x4,B2048=0x5,B4096=0x6" />
        <field name="max_read_request" offset="0x4.0" size="0x0.4" enum="NONE=0x0,B128=0x1,B256=0x2,B512=0x3,B1024=0x4,B2048=0x5,B4096=0x6" />
    </node>

    <node name="dpc_payload" size="0x4.0" descr="Event ID 0x7, Length = 0DW">
        <field name="error_correctable_triggered" descr="Set when an ERR_COR was sent as part of the DPC trigger flow" offset="0x0.30" size="0x0.1" enum="NOT_SENT=0x0,SENT=0x1" />
        <field name="interrupt_triggered" descr="DPC interrupt status" offset="0x0.29" size="0x0.1" enum="NOT_TRIGGERED=0x0,TRIGGERED=0x1" />
        <field name="extended_reason" offset="0x0.27" size="0x0.2" enum="RP_PIO_ERROR=0x0,DPC_SOFTWARE_TRIGGER=0x1" />
        <field name="trigger_reason" offset="0x0.25" size="0x0.2" enum="UNMASKED_UNCORRECTABLE_ERROR=0x0,ERR_NONFATAL_RECEIVED=0x1,ERR_FATAL_RECEIVED=0x2,SEE_EXTENDED_REASON=0x3" />
        <field name="dpc_triggered" offset="0x0.24" size="0x0.1" enum="DPC_RECOVER=0x0,DPC_TRIGGERED=0x1" />
        <field name="node" offset="0x0.20" size="0x0.4" />
        <field name="pcie_index" offset="0x0.16" size="0x0.4" />
        <field name="depth" offset="0x0.12" size="0x0.4" />
    </node>

    <node name="l23_payload" size="0x4.0" descr="Event ID 0x8, Length = 0DW, entry to link power state L2/L3">
        <field name="node" offset="0x0.20" size="0x0.4" />
        <field name="pcie_index" offset="0x0.16" size="0x0.4" />
        <field name="depth" offset="0x0.12" size="0x0.4" />
    </node>

    <node name="nvlog_tlv_extra_data" descr="" segment_id="0x107b" size="0x10.0" >
        <field name="time_lo" descr="The 32 LSB of the 64bit timestamp in microseconds. When time_synced=1 this is the time passed since the 1/1/1970 epoch. When time_synced=0 this is the NIC uptime." offset=".0" size="0x4.0" />
        <field name="time_hi" descr="The 32 MSB of the 64bit timestamp in microseconds. When time_synced=1 this is the time passed since the 1/1/1970 epoch. When time_synced=0 this is the NIC uptime." offset="0x4.0" size="0x4.0" />
        <field name="time_synced" descr="0x0: Boot - time is measured since NIC bootup; 0x1: Synced - time was synced by the host." offset="0xc.30" size=".1" />
        <field name="lost_event" descr="indicate that last operation was not written to flash(can be more than one event)" offset="0xc.31" size=".1" />
    </node>

    <node name="segment_command" descr="" segment_id="0xfffa" size="0x14.0" >
        <field name="segment_header" descr="The segment header. The segment type is 0xfffa" subnode="segment_header" offset="0x0.0" size="0x4.0" />
        <field name="vhca_id" descr="The vhca_id required by the resource_dump command" offset="0x4.0" size="0x0.16" />
        <field name="segment_called" descr="The segment required by the resource_dump command" offset="0x4.16" size="0x0.16" />
        <field name="index1" descr="1st index of required by the resource_dump command" offset="0x8.0" size="0x4.0" />
        <field name="index2" descr="2nd index of required by the resource_dump command" offset="0xc.0" size="0x4.0" />
        <field name="num_of_obj2" descr="2nd num_of_obj required by the resource_dump command" offset="0x10.0" size="0x0.16" />
        <field name="num_of_obj1" descr="1st num_of_obj required by the resource_dump command" offset="0x10.16" size="0x0.16" />
    </node>

    <node name="segment_error" descr="" segment_id="0xfffc" size="0x30.0" >
        <field name="segment_header" descr="The segment header. The segment type is 0xfffc" subnode="segment_header" offset="0x0.0" size="0x4.0" />
        <field name="syndrome_id" descr="Device syndrome for the error (optional, 0 if not used)" offset="0x4.0" size="0x0.16" />
        <field name="error" descr="A string containing the error" high_bound="7" low_bound="0" offset="0x10.0" size="0x20.0" />
    </node>

    <node name="segment_header" descr="" size="0x4.0" >
        <field name="segment_type" descr="The type of the segment" offset="0x0.0" size="0x0.16" />
        <field name="length_dw" descr="The total general segment length in DWORDs units." offset="0x0.16" size="0x0.16" />
    </node>

    <node name="segment_info" descr="" segment_id="0xfffe" size="0x10.0" >
        <field name="segment_header" descr="The segment header. The segment type is 0xfffe" subnode="segment_header" offset="0x0.0" size="0x4.0" />
        <field name="dump_version" descr="Dump format version" offset="0x4.0" size="0x0.8" />
        <field name="hw_version" descr="HW version, for parsing" offset="0x8.0" size="0x4.0" />
        <field name="fw_version" descr="FW version, for parsing" offset="0xc.0" size="0x4.0" />
    </node>

    <node name="segment_menu_header" descr="" segment_id="0xffff" size="0x8.0" >
        <field name="segment_header" descr="The segment header. The segment type is 0xffff" subnode="segment_header" offset="0x0.0" size="0x4.0" />
        <field name="num_of_records" descr="The number of general segments records in the list" offset="0x4.0" size="0x0.16" />
    </node>

    <node name="segment_notice" descr="" segment_id="0xfff9" size="0x30.0" >
        <field name="segment_header" descr="The segment header. The segment type is 0xfff9" subnode="segment_header" offset="0x0.0" size="0x4.0" />
        <field name="syndrome_id" descr="Device syndrome for the notice (optional, 0 if not used)" offset="0x4.0" size="0x0.16" />
        <field name="notice" descr="A string containing the notice" high_bound="7" low_bound="0" offset="0x10.0" size="0x20.0" />
    </node>

    <node name="segment_terminate" descr="" segment_id="0xfffb" size="0x4.0" >
        <field name="segment_header" descr="The segment header. The segment type is 0xfffb" subnode="segment_header" offset="0x0.0" size="0x4.0" />
    </node>
</NodesDefinition>
