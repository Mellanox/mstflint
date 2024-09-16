<NodesDefinition version="2">
    <config  big_endian_arr="1" />

    <node name="unlimited_array_example" size="0x80.0" segment_id="0x1329">
        <field name="regular_field1" offset="0x0" size="0x4" />
        <field name="short_aligned_array" offset="0x4.16" size="0x8" low_bound="0" high_bound="3" />
        <field name="regular_field2" offset="0xC.16" size="0x2" />
        <field name="short_sk_start_array" offset="0xC.0" size="0x6" low_bound="0" high_bound="2" />
        <field name="regular_field3" offset="0x14" size="0x4" />
        <field name="short_sk_end_array" offset="0x18.16" size="0x6" low_bound="0" high_bound="2" />
        <field name="regular_field4" offset="0x1C.0" size="0x2" />
        <field name="regular_field5" offset="0x20.16" size="0x2" />
        <field name="short_sk_array" offset="0x20.0" size="0x8" low_bound="0" high_bound="3" />
        <field name="regular_field6" offset="0x28.0" size="0x2" />
        <field name="regular_field7" offset="0x2C.24" size="0x1" />
        <field name="sk_byte_array" offset="0x2C.16" size="0x9" low_bound="0" high_bound="8" />
        <field name="regular_field8" offset="0x34.0" size="0x2" />
        <field name="full_byte_array" offset="0x38.24" size="0xC" low_bound="0" high_bound="11" />
        <field name="regular_field9" offset="0x44.0" size="0x4" />
        <field name="dword_array" offset="0x48.0" size="0x10" low_bound="0" high_bound="3" />
        <field name="regular_field10" offset="0x58.0" size="0x4" />
        <field name="multi_dword_array" offset="0x5c.0" size="0x20" low_bound="0" high_bound="3" />
        <field name="regular_field11" offset="0x7C.0" size="0x4" />
    </node>
</NodesDefinition>
