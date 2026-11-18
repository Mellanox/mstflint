/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MLXCFG_XML_READER_H_
#define MLXCFG_XML_READER_H_

#include <cstddef>
#include <map>
#include <string>

namespace mlxcfg
{
const size_t XML_READER_MAX_DEPTH = 256; // the root element counts as depth 1
const char* const XML_READER_PARSE_ERROR = "Failed to parse the XML document";

typedef std::map<std::string, std::string> XmlAttrs;

// After a handler throws, it receives no more events.
class XmlStreamHandler
{
public:
    virtual ~XmlStreamHandler() {}
    // attrs maps the local attribute names (namespace prefix stripped) to their values; when two attributes have
    // the same local name, the first one is kept.
    virtual void OnStartElement(const std::string& nsUri, const std::string& name, const XmlAttrs& attrs) = 0;
    virtual void OnEndElement() = 0;
    // Called for text inside an element; one text node can arrive in several calls.
    virtual void OnText(const char* text, size_t len) = 0;
};

void parseXmlStream(const std::string& xml, XmlStreamHandler& handler);

// Throws MlxcfgException unless the root element is named expectedRoot and is in the namespace expectedNs.
void checkXmlRoot(const std::string& nsUri,
                  const std::string& name,
                  const std::string& expectedRoot,
                  const std::string& expectedNs);
} // namespace mlxcfg

#endif /* MLXCFG_XML_READER_H_ */
