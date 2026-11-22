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

#ifndef MLXCFG_XML_TLV_BUILDER_H_
#define MLXCFG_XML_TLV_BUILDER_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "mlxcfg_db_manager.h"
#include "mlxcfg_tlv.h"
#include "mlxcfg_xml_reader.h"

namespace mlxcfg
{
class XmlTlvBuilder : public XmlStreamHandler
{
public:
    // The root element must be named rootName and be in the namespace rootNs.
    XmlTlvBuilder(MlxcfgDBManager* dbManager,
                  int maxPort,
                  const std::string& rootName,
                  const std::string& rootNs,
                  std::vector<std::shared_ptr<TLVConf>>& tlvs);

    void OnStartElement(const std::string& nsUri, const std::string& name, const XmlAttrs& attrs) override;
    void OnText(const char* text, size_t len) override;
    void OnEndElement() override;

    void checkAnyTlvFound() const;

private:
    enum Level
    {
        ROOT_LEVEL = 1,
        TLV_LEVEL = 2,
        PARAM_LEVEL = 3,
        MAX_LEVEL = PARAM_LEVEL
    };

    void setAttrIfPresent(const XmlAttrs& attrs, const char* attr);
    void startTlv(const std::string& name, const XmlAttrs& attrs);
    void startParam(const std::string& name, const XmlAttrs& attrs);
    void endParam();
    void endTlv();

    MlxcfgDBManager* _dbManager;
    int _maxPort;
    std::string _rootName;
    std::string _rootNs;
    std::vector<std::shared_ptr<TLVConf>>& _tlvs;
    size_t _depth;
    std::shared_ptr<TLVConf> _tlvConf;
    std::string _paramName;
    std::string _paramIndex;
    bool _paramHasIndex;
    std::string _paramText;
    std::vector<std::string> _collectedParams;
    std::map<std::string, std::map<u_int32_t, std::string>> _arrayValues;
};
} // namespace mlxcfg

#endif /* MLXCFG_XML_TLV_BUILDER_H_ */
