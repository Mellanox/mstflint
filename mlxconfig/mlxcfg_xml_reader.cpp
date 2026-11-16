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

#include "mlxcfg_xml_reader.h"
#include "mlxcfg_utils.h"

#include <climits>
#include <cstring>
#include <exception>
#include <memory>
#include <expat.h>

namespace
{
using mlxcfg::XML_READER_MAX_DEPTH;
using mlxcfg::XML_READER_PARSE_ERROR;
using mlxcfg::XmlAttrs;
using mlxcfg::XmlStreamHandler;

const XML_Char NS_SEPARATOR = '\x01';
// The declared encoding is ignored: input is read as UTF-8 (ASCII is a subset), or as UTF-16 when the first bytes
// show it (with or without a byte order mark).
const XML_Char INPUT_ENCODING[] = "UTF-8";

struct ParserDeleter
{
    void operator()(XML_Parser parser) const { XML_ParserFree(parser); }
};

enum class FailureReason
{
    ExpatError,
    TooDeep,
    Doctype,
    HandlerError
};

struct ReaderContext
{
    ReaderContext(XML_Parser parser, XmlStreamHandler& handler) :
        parser(parser),
        handler(handler),
        depth(0),
        failed(false),
        reason(FailureReason::ExpatError),
        failedLine(0),
        failedColumn(0)
    {
    }
    XML_Parser parser;
    XmlStreamHandler& handler;
    size_t depth; // number of open elements
    bool failed;
    FailureReason reason;
    XML_Size failedLine;
    XML_Size failedColumn;
    // Set by a callback when the handler throws; parseXmlStream rethrows it after XML_Parse returns.
    std::exception_ptr handlerError;
};

// Exceptions must not cross expat's C frames: handlers record the failure and stop the parser instead.
// The position is taken here because once the parser stops, it points past the failing token.
void fail(ReaderContext& ctx, FailureReason reason)
{
    if (!ctx.failed)
    {
        ctx.reason = reason;
        ctx.failedLine = XML_GetCurrentLineNumber(ctx.parser);
        ctx.failedColumn = XML_GetCurrentColumnNumber(ctx.parser);
    }
    ctx.failed = true;
    XML_StopParser(ctx.parser, XML_FALSE);
}

// Called only from inside a catch block: current_exception() needs an active exception.
void recordHandlerError(ReaderContext& ctx)
{
    ctx.handlerError = std::current_exception();
    fail(ctx, FailureReason::HandlerError);
}

std::string failureText(const ReaderContext& ctx, XML_Parser parser)
{
    switch (ctx.reason)
    {
        case FailureReason::TooDeep:
            return "elements are nested deeper than " + std::to_string(XML_READER_MAX_DEPTH) + " levels";
        case FailureReason::Doctype:
            return "DOCTYPE declarations are not supported";
        default:
        {
            const XML_LChar* text = XML_ErrorString(XML_GetErrorCode(parser));
            return text ? text : "unknown error";
        }
    }
}

void throwParseError(XML_Size line, XML_Size column, const std::string& reason)
{
    throw MlxcfgException("%s: line %lu, column %lu: %s\n",
                          XML_READER_PARSE_ERROR,
                          static_cast<unsigned long>(line),
                          static_cast<unsigned long>(column) + 1,
                          reason.c_str());
}

void splitName(const XML_Char* fullName, std::string& nsUri, std::string& localName)
{
    const XML_Char* separator = strchr(fullName, NS_SEPARATOR);
    if (separator)
    {
        nsUri.assign(fullName, separator - fullName);
        localName = separator + 1;
    }
    else
    {
        nsUri.clear();
        localName = fullName;
    }
}

void XMLCALL OnStartElement(void* userData, const XML_Char* name, const XML_Char** atts)
{
    ReaderContext& ctx = *static_cast<ReaderContext*>(userData);
    if (ctx.failed)
    {
        return;
    }
    if (ctx.depth >= XML_READER_MAX_DEPTH)
    {
        fail(ctx, FailureReason::TooDeep);
        return;
    }
    ctx.depth++;
    try
    {
        std::string nsUri;
        std::string localName;
        splitName(name, nsUri, localName);
        XmlAttrs attrs;
        std::string attrNsUri;
        std::string attrName;
        for (size_t i = 0; atts[i]; i += 2)
        {
            splitName(atts[i], attrNsUri, attrName);
            attrs.insert(std::make_pair(attrName, std::string(atts[i + 1])));
        }
        ctx.handler.OnStartElement(nsUri, localName, attrs);
    }
    catch (...)
    {
        recordHandlerError(ctx);
    }
}

void XMLCALL OnEndElement(void* userData, const XML_Char*)
{
    ReaderContext& ctx = *static_cast<ReaderContext*>(userData);
    if (ctx.failed)
    {
        return;
    }
    ctx.depth--;
    try
    {
        ctx.handler.OnEndElement();
    }
    catch (...)
    {
        recordHandlerError(ctx);
    }
}

void XMLCALL OnCharacterData(void* userData, const XML_Char* text, int len)
{
    ReaderContext& ctx = *static_cast<ReaderContext*>(userData);
    if (ctx.failed || ctx.depth == 0)
    {
        return;
    }
    try
    {
        ctx.handler.OnText(text, static_cast<size_t>(len));
    }
    catch (...)
    {
        recordHandlerError(ctx);
    }
}

// Security: DOCTYPE is rejected to block entity-expansion and external-entity attacks.
// Do not remove this check.
void XMLCALL OnStartDoctype(void* userData, const XML_Char*, const XML_Char*, const XML_Char*, int)
{
    fail(*static_cast<ReaderContext*>(userData), FailureReason::Doctype);
}
} // namespace

void mlxcfg::parseXmlStream(const std::string& xml, XmlStreamHandler& handler)
{
    if (xml.size() > INT_MAX)
    {
        throw MlxcfgException("%s: the document is larger than %d bytes\n", XML_READER_PARSE_ERROR, INT_MAX);
    }
    std::unique_ptr<XML_ParserStruct, ParserDeleter> parser(XML_ParserCreateNS(INPUT_ENCODING, NS_SEPARATOR));
    if (!parser)
    {
        throw MlxcfgException("%s: out of memory\n", XML_READER_PARSE_ERROR);
    }
    ReaderContext ctx(parser.get(), handler);
    XML_SetUserData(parser.get(), &ctx);
    XML_SetElementHandler(parser.get(), OnStartElement, OnEndElement);
    XML_SetCharacterDataHandler(parser.get(), OnCharacterData);
    XML_SetStartDoctypeDeclHandler(parser.get(), OnStartDoctype);
    XML_SetParamEntityParsing(parser.get(), XML_PARAM_ENTITY_PARSING_NEVER);

    enum XML_Status status = XML_Parse(parser.get(), xml.data(), static_cast<int>(xml.size()), XML_TRUE);
    // The callbacks can't throw through expat's C code, so they store the exception and stop the parser.
    // Rethrow it here, after expat has returned.
    if (ctx.handlerError)
    {
        std::rethrow_exception(ctx.handlerError);
    }
    if (status != XML_STATUS_OK || ctx.failed)
    {
        const XML_Size line = ctx.failed ? ctx.failedLine : XML_GetCurrentLineNumber(parser.get());
        const XML_Size column = ctx.failed ? ctx.failedColumn : XML_GetCurrentColumnNumber(parser.get());
        throwParseError(line, column, failureText(ctx, parser.get()));
    }
}

void mlxcfg::checkXmlRoot(const std::string& nsUri,
                          const std::string& name,
                          const std::string& expectedRoot,
                          const std::string& expectedNs)
{
    if (name != expectedRoot)
    {
        throw MlxcfgException("The XML root node must be %s", expectedRoot.c_str());
    }
    // check fingerprint
    if (nsUri != expectedNs)
    {
        throw MlxcfgException("The XML Fingerprint %s is missing or incorrect", expectedNs.c_str());
    }
}
