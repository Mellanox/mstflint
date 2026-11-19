/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
 */

#include "tools_xml.h"

namespace nbu
{
namespace mft
{
namespace common
{
std::string escape_xml(const std::string& text, bool is_attribute)
{
    std::string out;
    out.reserve(text.size());
    for (char c : text)
    {
        switch (c)
        {
            case '&':
                out += "&amp;";
                break;
            case '<':
                out += "&lt;";
                break;
            case '>':
                out += "&gt;";
                break;
            case '\r':
                out += "&#13;";
                break;
            case '"':
                out += is_attribute ? "&quot;" : "\"";
                break;
            case '\n':
                out += is_attribute ? "&#10;" : "\n";
                break;
            case '\t':
                out += is_attribute ? "&#9;" : "\t";
                break;
            default:
                out += c;
        }
    }
    return out;
}

std::string xml_attr(const std::string& name, const std::string& value)
{
    return " " + name + "=\"" + escape_xml(value, true) + "\"";
}

std::string xml_open_tag(const std::string& tag, const xml_attrs& attrs, bool self_close)
{
    std::string res = "<" + tag;
    for (const auto& attr : attrs)
    {
        res += xml_attr(attr.first, attr.second);
    }
    return res + (self_close ? "/>" : ">");
}

std::string xml_close_tag(const std::string& tag)
{
    return "</" + tag + ">";
}

std::string xml_element(const std::string& tag, const xml_attrs& attrs, const std::string& text)
{
    if (text.empty())
    {
        return xml_open_tag(tag, attrs, true);
    }
    return xml_open_tag(tag, attrs) + escape_xml(text, false) + xml_close_tag(tag);
}

} // namespace common
} // namespace mft
} // namespace nbu
