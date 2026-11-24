<NodesDefinition version="2">
    <node name="short_segment" size="0x10.0" segment_id="0x1329" is_conditional="1">
        <field name="plain_field" offset="0x0" size="0x4" />
        <field name="opt_field" offset="0x4" size="0x4" condition="$(parent).kind == 1" />
        <field name="payload" offset="0x8" size="0x4" union_selector="$(parent).kind" subnode="payload_union" />
        <field name="kind" offset="0xC" size="0x4" enum="IDLE=0x0,BUSY=0x1" />
    </node>

    <node name="payload_union" size="0x4.0" attr_is_union="1">
        <field name="idle" offset="0x0" size="0x4" selected_by="IDLE" />
        <field name="busy" offset="0x0" size="0x4" selected_by="BUSY" />
    </node>
</NodesDefinition>
