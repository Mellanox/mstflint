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

#pragma once

#include <string>
#include <utility>
#include <vector>

namespace nbu
{
namespace mft
{
namespace common
{
/**
 * @brief Escape text so it can be written inside an XML element or attribute value.
 * @param text The text to escape.
 * @param is_attribute True when the text goes into an attribute value, false for element text.
 * @return The escaped text.
 *
 * Always escapes & < > and carriage return. For attribute values it also escapes " and the
 * newline and tab characters. Other bytes, including control characters and invalid UTF-8,
 * are copied unchanged.
 */
::std::string escape_xml(const ::std::string& text, bool is_attribute);

/// Ordered attribute name/value pairs, so the attribute order in the output is kept.
typedef ::std::vector<::std::pair<::std::string, ::std::string>> xml_attrs;

/**
 * @brief Build one attribute, as ` name="value"` (with a leading space), the value escaped for an attribute.
 */
::std::string xml_attr(const ::std::string& name, const ::std::string& value);

/**
 * @brief Build an opening tag: `<tag a="v" b="w">`, or `<tag a="v" b="w"/>` when self_close is true.
 */
::std::string xml_open_tag(const ::std::string& tag, const xml_attrs& attrs = xml_attrs(), bool self_close = false);

/**
 * @brief Build a closing tag: `</tag>`.
 */
::std::string xml_close_tag(const ::std::string& tag);

/**
 * @brief Build a whole element: `<tag attrs>escaped text</tag>`, or `<tag attrs/>` when text is empty.
 */
::std::string xml_element(const ::std::string& tag, const xml_attrs& attrs, const ::std::string& text);

} // namespace common
} // namespace mft
} // namespace nbu
