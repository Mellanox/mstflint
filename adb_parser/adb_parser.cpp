/*
 * Copyright (c) 2012-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 *  Version: $Id$
 */

/*************************** _Adb_impl ***************************/
/**
 * Function: _Adb_impl::_Adb_impl
 **/

#include "adb_parser.h"
#include "adb_xml_parser.h"

#include "adb_instance.h"
#include "adb_condition.h"
#include "adb_condVar.h"
#include "buf_ops.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "common/tools_algorithm.h"
#include "common/tools_regex.h"

namespace Algorithm = mstflint::common::algorithm;
namespace Regex = mstflint::common::regex;
using namespace std;
using namespace xmlCreator;

#if 0

int main()
{
#define ADB_FILE "path_to.adb"
    _Adb_impl adb;
    if (!adb.load(ADB_FILE, true)) {
        printf("Failed : %s\n", adb.getLastError().c_str());
        return 1;
    }

    try
    {
        //adb.printx(0);
        cout << "Root node: " << adb.rootNode << endl;
        _AdbInstance_impl<> *root = adb.createLayout(adb.rootNode, false, NULL);
        _AdbInstance_impl<> *child = root->getChildByPath("packetA.x");
        if (!child) {
            printf("can't find packetA.x\n");
            return 1;
        }

        printf("Child name: %s, addr: %s\n", child->name.c_str(), formatAddr(child->offset, child->size).c_str());

        string n1, n2;
        u_int64_t v1, v2;
        child->intToEnum(0, n1);
        child->intToEnum(1, n2);
        child->enumToInt("SET", v1);
        child->enumToInt("GET", v2);

        printf("enumName(0) = %s, enumName(1) = %s, value(SET) = %d, value(GET) = %d", n1.c_str(), n2.c_str(), v1, v2);
        //root->print();
    }
    catch (AdbException &exp)
    {
        printf("-E- %s\n", exp.what());
        return 1;
    }

    cout << endl;
    //adb.print(0);
    return 0;
}
#endif

template<bool e, typename O>
_Adb_impl<e, O>::_Adb_impl() :
    bigEndianArr(false), singleEntryArrSupp(false), _checkDsAlign(false), _enforceGuiChecks(false)
{
    _logFile = new LogFile;
}

/**
 * Function: _Adb_impl::~_Adb_impl
 **/
template<bool e, typename O>
_Adb_impl<e, O>::~_Adb_impl()
{
    // Free configs
    for (size_t i = 0; i < configs.size(); i++)
        delete configs[i];

    // Free nodes
    typename NodesMap::iterator iter;
    for (iter = nodesMap.begin(); iter != nodesMap.end(); iter++)
        delete iter->second;

    delete _logFile;
}

/**
 * Function: _Adb_impl::raiseException
 **/
template<bool e, typename O>
void _Adb_impl<e, O>::raiseException(bool allowMultipleExceptions,
                                     string exceptionTxt,
                                     const string expType,
                                     bool raise_warnings)
{
    if (allowMultipleExceptions)
    {
        ExceptionHolder::insertNewException(expType, exceptionTxt);
    }
    else
    {
        if (!raise_warnings && expType == ExceptionHolder::WARN_EXCEPTION)
        {
            cerr << "-WARNING-: " << exceptionTxt << endl;
    	}
    	else
    	{
            throw AdbException(exceptionTxt);
    	}
    }
}

/**
 * Function: _Adb_impl::printAdbExceptionMap
 * This function will print the content of the _Adb_impl Exception Map
 **/
template<bool e, typename O>
string _Adb_impl<e, O>::printAdbExceptionMap()
{
    return ExceptionHolder::printAdbExceptionMap();
}

/**
 * Function: _Adb_impl::clearAdbExceptionMap
 * This function will clear the content of the _Adb_impl Exception Map
 **/
template<bool e, typename O>
void _Adb_impl<e, O>::clearAdbExceptionMap()
{
    ExceptionHolder::clearAdbExceptionMap();
}

/**
 * Function: _Adb_impl::load
 **/
template<bool e, typename O>
bool _Adb_impl<e, O>::load(string fname,
                           bool addReserved,
                           bool strict,
                           string includePath,
                           string includeDir,
                           bool enforceExtraChecks,
                           bool allowMultipleExceptions,
                           string logFileStr,
                           bool checkDsAlign,
                           bool enforceGuiChecks,
                           bool force_dword_align,
                           bool cd_mode,
                           bool variable_alignment,
                           string root_node_name)
{
    try
    {
        bool status = true;
        mainFileName = fname;
        if (allowMultipleExceptions)
        {
            AdbParser<e, O>::setAllowMultipleExceptionsTrue();
        }
        _logFile->init(logFileStr, allowMultipleExceptions);
        AdbParser<e, O> p(fname, this, root_node_name, addReserved, strict, includePath, enforceExtraChecks,
                          checkDsAlign, enforceGuiChecks, force_dword_align, cd_mode, variable_alignment);
        _checkDsAlign = checkDsAlign;
        _enforceGuiChecks = enforceGuiChecks;
        _force_dword_align = force_dword_align;
        _cd_mode = cd_mode;
        if (!p.load())
        {
            _lastError = p.getError();
            status = false;
        }
        if (status && includeDir != "")
        {
            AdbParser<e, O>::includeAllFilesInDir(&p, includeDir);
        }
        if (status && !nodesMap.size())
        {
            _lastError = "Empty project, no nodes were found";
            if (allowMultipleExceptions)
            {
                ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
            }
            status = false;
        }
        if (status)
        {
            bool checkSizeConsistency = strict ? checkInstSizeConsistency(allowMultipleExceptions) : true;
            status = status && checkSizeConsistency;
        }
        if (allowMultipleExceptions && ExceptionHolder::getNumberOfExceptions() > 0)
        {
            status = false;
        }
        return status;
    }
    catch (AdbException& er)
    {
        _lastError = er.what_s();
        if (allowMultipleExceptions)
        {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }
    catch (AdbStopException& er)
    {
        return false;
    }
    catch (...)
    {
        _lastError = "Unknown error occurred in loading ADB";
        ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        return false;
    }
}

/**
 * Function: _Adb_impl::loadFromString
 **/
template<bool e, typename O>
bool _Adb_impl<e, O>::loadFromString(const char* adbContents,
                                     bool addReserved,
                                     bool strict,
                                     bool enforceExtraChecks,
                                     string root_node_name)
{
    try
    {
        AdbParser<e, O> p(string(), this, root_node_name, addReserved, strict, "", enforceExtraChecks);
        mainFileName = OS_PATH_SEP;
        if (!p.loadFromString(adbContents))
        {
            _lastError = p.getError();
            return false;
        }

        if (!nodesMap.size())
        {
            _lastError = "Empty project, no nodes were found";
            return false;
        }

        return strict ? checkInstSizeConsistency() : true;
    }
    catch (AdbException& er)
    {
        _lastError = er.what_s();
        return false;
    }
    catch (AdbStopException& er)
    {
        return false;
    }
}

/**
 * Function: _Adb_impl::toXml
 **/
template<bool e, typename O>
string
  _Adb_impl<e, O>::toXml(vector<string> nodeNames, bool addRootNode, string rootName, string addPrefix, bool bigEndian)
{
    try
    {
        vector<string> nodeDeps;
        for (vector<string>::iterator it = nodeNames.begin(); it != nodeNames.end(); it++)
        {
            vector<string> tmp = getNodeDeps(*it);
            nodeDeps.insert(nodeDeps.end(), tmp.begin(), tmp.end());
        }
        stable_sort(nodeDeps.begin(), nodeDeps.end());
        nodeDeps.erase(unique(nodeDeps.begin(), nodeDeps.end()), nodeDeps.end());

        string xml;
        if (this->version == "2")
        {
            xml = "<NodesDefinition version=\"2\">\n";
        }
        else
        {
            xml = "<NodesDefinition>\n";
        }
        for (ConfigList::iterator it = configs.begin(); it != configs.end(); it++)
        {
            xml += (*it)->toXml() + "\n";
        }

        // Add source info
        xml += "<info source_doc_name=\"" + encodeXml(descNativeToXml(srcDocName)) + "\" source_doc_version=\"" +
               encodeXml(descNativeToXml(srcDocVer)) + "\" />\n";

        if (nodeNames.empty())
        {
            for (typename NodesMap::iterator it = nodesMap.begin(); it != nodesMap.end(); it++)
            {
                AdbNode* node = it->second;
                xml += node->toXml(addPrefix, bigEndian) + "\n";
            }
        }
        else
        {
            uint32_t maxSize = 0;
            for (size_t i = 0; i < nodeDeps.size(); i++)
            {
                typename NodesMap::iterator it = nodesMap.find(nodeDeps[i]);
                if (it == nodesMap.end())
                {
                    _lastError = "Can't find node definition for: " + nodeDeps[i];
                    return "";
                }

                AdbNode* node = it->second;
                xml += node->toXml(addPrefix, bigEndian) + "\n\n";

                maxSize = TOOLS_MAX(node->get_size(), maxSize);
            }

            if (addRootNode)
            {
                stringstream buf;
                buf << "<node name=\"root\" size=\"0x" << hex << ((maxSize >> 5) << 2) << "." << dec << (maxSize % 32)
                    << "\" descr=\"\" >\n";
                buf << "\t<field name=\"" << rootName << "\" offset=\"0x0.0\""
                    << " size=\"0x" << hex << ((maxSize >> 5) << 2) << "." << dec << (maxSize % 32) << "\" subnode=\""
                    << addPrefix + rootName << "\" descr=\"\" />\n";
                buf << "</node>\n\n";

                buf << "<node name=\"" + addPrefix + rootName + "\" size=\"0x" << hex << ((maxSize >> 5) << 2) << "."
                    << dec << (maxSize % 32) << "\" attr_is_union=\"1\" descr=\"\" >\n";
                for (size_t i = 0; i < nodeNames.size(); i++)
                {
                    AdbNode* node = nodesMap[nodeNames[i]];
                    buf << "\t<field name=\"" << node->name << "\" offset=\"0x0.0\" size=\"0x" << hex
                        << ((node->get_size() >> 5) << 2) << "." << dec << (node->get_size() % 32)
                        << "\" subnode=\"" + addPrefix + node->name + "\" descr=\"\" />\n";
                }
                buf << "</node>\n";
                xml += buf.str();
            }
        }

        xml += "</NodesDefinition>\n";
        return xml;
    }
    catch (AdbException& exp)
    {
        _lastError = exp.what_s();
        return "";
    }
}

/**
 * Function: _Adb_impl::addMissingNodes
 **/

template<bool e, typename O>
void _Adb_impl<e, O>::addMissingNodes(int depth, bool allowMultipleExceptions)
{
    try
    {
        typename NodesMap::iterator it;
        for (it = nodesMap.begin(); it != nodesMap.end(); it++)
        {
            AdbNode* nodeDesc = it->second;
            for (size_t i = 0; (depth == -1 || depth > 0) && i < nodeDesc->fields.size(); i++)
            {
                AdbField* fieldDesc = nodeDesc->fields[i];
                for (uint32_t i = 0; i < fieldDesc->arrayLen(); i++)
                {
                    if (fieldDesc->isStruct())
                    {
                        typename NodesMap::iterator it2 = nodesMap.find(fieldDesc->subNode);
                        if (it2 == nodesMap.end())
                        {
                            // If in ignore missing nodes mode, it should create temporary node with placeholder
                            AdbNode* tmpNode = new AdbNode;
                            tmpNode->name = fieldDesc->subNode;
                            tmpNode->set_size(fieldDesc->eSize());
                            tmpNode->desc = fieldDesc->desc + " ***MISSING NODE***";
                            tmpNode->isUnion = false;
                            tmpNode->fileName = "tempForMissingNodes.adb";
                            tmpNode->lineNumber = 0;
                            AdbField* tmpField = new AdbField;
                            tmpField->name = "placeholder";
                            tmpField->desc = "This field is part of auto generated node for missing node.";
                            tmpField->set_size(tmpNode->get_size());
                            tmpField->offset = 0;
                            tmpNode->fields.push_back(tmpField);
                            nodesMap.insert(pair<string, AdbNode*>(tmpNode->name, tmpNode));
                        }
                    }
                }
            }
        }
    }
    catch (AdbException& exp)
    {
        _lastError = exp.what_s();
        if (allowMultipleExceptions)
        {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
    }
    catch (...)
    {
        _lastError = "Unknown error occurred";
    }
}

template<bool e, typename O>
typename _Adb_impl<e, O>::PathPart
  _Adb_impl<e, O>::parse_missing_son_part(const string& part, const string& ranges_str, bool allowMultipleExceptions)
{
    PathPart result;
    result.first = part;

    if (!ranges_str.empty())
    {
        vector<string> ranges;
        Algorithm::split(ranges, ranges_str, Algorithm::is_any_of(","));
        for (auto& range : ranges)
        {
            Algorithm::trim(range);
            size_t colon_pos = range.find(':');
            try
            {
                if (colon_pos != string::npos)
                {
                    uint32_t start = stoul(range.substr(0, colon_pos));
                    uint32_t end = stoul(range.substr(colon_pos + 1));
                    for (uint32_t i = start; i <= end; ++i)
                    {
                        result.second.push_back(i);
                    }
                }
                else
                {
                    result.second.push_back(stoul(range));
                }
            }
            catch (const std::runtime_error&)
            {
                raiseException(allowMultipleExceptions, "Failed to parse missing_sons attribute",
                               ExceptionHolder::ERROR_EXCEPTION);
                break;
            }
            catch (const std::logic_error&)
            {
                raiseException(allowMultipleExceptions, "Failed to parse missing_sons attribute",
                               ExceptionHolder::ERROR_EXCEPTION);
                break;
            }
        }
    }
    return result;
}

template<bool e, typename O>
vector<typename _Adb_impl<e, O>::SplittedPath> _Adb_impl<e, O>::parse_missing_sons(AdbNode& node,
                                                                                   bool allowMultipleExceptions)
{
    static Regex::regex path_part_pattern("(\\.)?(\\w+)(\\[([^\\]]*)\\])?(@\\([^\\)]*\\))?");
    vector<SplittedPath> missing_sons;
    auto found_it = node.attrs.find("missing_sons");
    if (found_it != node.attrs.end() && !found_it->second.empty())
    {
        vector<string> missing_sons_paths;
        Algorithm::split(missing_sons_paths, found_it->second, Algorithm::is_any_of(" "));
        for (auto path : missing_sons_paths)
        {
            if (path.size() > 0)
            {
                SplittedPath splitted_missing_son;
                Regex::sregex_iterator it_end;
                Regex::smatch::difference_type prev_end(0);
                for (Regex::sregex_iterator it(path.begin(), path.end(), path_part_pattern); it != it_end; ++it)
                {
                    auto& match = *it;
                    if (match.position() != prev_end)
                    {
                        raiseException(allowMultipleExceptions,
                                       "Failed to parse missing_sons attribute",
                                       ExceptionHolder::ERROR_EXCEPTION);
                        return missing_sons;
                    }
                    prev_end = match.position() + match.length();

                    auto& part = match[2];
                    auto& ranges = match[4];

                    splitted_missing_son.push_back(
                      parse_missing_son_part(part.str(), ranges.str(), allowMultipleExceptions));
                }
                missing_sons.push_back(splitted_missing_son);
            }
        }
    }
    return missing_sons;
}

template<bool e, typename O>
bool _Adb_impl<e, O>::skip_or_get_child_missing_sons(vector<SplittedPath>& missing_sons,
                                                     AdbField& child_field,
                                                     uint32_t array_idx)
{
    vector<SplittedPath> child_missing_sons;
    for (auto missing_son_list : missing_sons)
    {
        size_t missing_son_list_depth = missing_son_list.size();
        if (missing_son_list_depth > 0)
        {
            if (child_field.name == missing_son_list[0].first)
            {
                if (missing_son_list_depth == 1)
                {
                    if (missing_son_list[0].second.size() == 0)
                    {
                        return true;
                    }
                    else
                    {
                        if (find(missing_son_list[0].second.begin(), missing_son_list[0].second.end(), array_idx) !=
                            missing_son_list[0].second.end())
                        {
                            return true;
                        }
                    }
                }
                else
                {
                    if (missing_son_list[0].second.empty() ||
                        find(missing_son_list[0].second.begin(), missing_son_list[0].second.end(), array_idx) !=
                          missing_son_list[0].second.end())
                    {
                        child_missing_sons.push_back(SplittedPath(missing_son_list.begin() + 1, missing_son_list.end()));
                    }
                }
            }
        }
    }
    missing_sons = child_missing_sons;
    return false;
}

/**
 * Function: _Adb_impl::createLayout
 **/
template<bool eval_expr, typename T_OFFSET>
typename _Adb_impl<eval_expr, T_OFFSET>::AdbInstance*
  _Adb_impl<eval_expr, T_OFFSET>::createLayout(string rootNodeName,
                                               int depth,
                                               bool ignoreMissingNodes,
                                               bool allowMultipleExceptions,
                                               bool optimize_time,
                                               T_OFFSET root_offset,
                                               string root_display_name,
                                               PartitionTree* partition_tree,
                                               AdbField* rootField,
                                               string ancestor_path,
                                               bool array_path_wildcards,
                                               bool strict_instance_ops,
                                               bool enable_parse_missing_sons)
{
    try
    {
        // find root in nodes map
        typename NodesMap::iterator it;
        it = nodesMap.find(rootNodeName);
        if (it == nodesMap.end())
        {
            throw AdbException("Can't find definition for node \"" + rootNodeName + "\"");
        }

        AdbNode* nodeDesc = it->second;
        nodeDesc->inLayout = true && depth == -1;
        AdbInstance* rootItem = new AdbInstance();
        rootItem->fieldDesc = rootField;
        rootItem->nodeDesc = nodeDesc;
        rootItem->parent = nullptr;
        rootItem->layout_item_name = root_display_name.size() > 0 ? root_display_name : nodeDesc->name;
        if (optimize_time)
        {
            rootItem->full_path = rootItem->layout_item_name;
        }
        rootItem->offset = root_offset;
        rootItem->initInstOps();

        map<string, string> emptyVars;
        _unionSelectorEvalDeffered.clear();
        _conditionInstances.clear();
        _conditionalArrays.clear();
        if (ignoreMissingNodes)
        {
            addMissingNodes(depth, allowMultipleExceptions);
        }

        vector<SplittedPath> missing_sons =
          enable_parse_missing_sons ? parse_missing_sons(*nodeDesc, allowMultipleExceptions) : vector<SplittedPath>();

        for (size_t i = 0; (depth == -1 || depth > 0) && i < nodeDesc->fields.size(); i++)
        {
            PartitionTree* next_partition_tree = nullptr;
            if (partition_tree)
            {
                auto found_partition_tree =
                  find_if(partition_tree->sub_items.begin(), partition_tree->sub_items.end(),
                          [&nodeDesc, i](PartitionTree* si) { return si->name == nodeDesc->fields[i]->name; });
                if (found_partition_tree != partition_tree->sub_items.end())
                {
                    next_partition_tree = *found_partition_tree;
                }
            }
            createInstance(nodeDesc->fields[i], rootItem, emptyVars, depth == -1 ? -1 : depth - 1, ignoreMissingNodes,
                           enable_parse_missing_sons, missing_sons, allowMultipleExceptions, optimize_time,
                           next_partition_tree, array_path_wildcards);
        }

        nodeDesc->inLayout = false;

        // Now set the instance attributes (override field attrs), only if this is root node instantiation
        if (depth == -1 && (rootNodeName == rootNode || !ancestor_path.empty()))
        {
            string path_prefix = string();
            if (!ancestor_path.empty())
            {
                size_t first_dot = ancestor_path.find('.');
                if (first_dot != string::npos)
                {
                    path_prefix = ancestor_path.substr(first_dot + 1);
                }
                path_prefix =
                  path_prefix.empty() ? rootItem->get_field_name() : path_prefix + "." + rootItem->get_field_name();
            }
            for (InstanceAttrs::iterator it = instAttrs.begin(); it != instAttrs.end(); it++)
            {
                string path = it->first;
                size_t idx = path.find(".");
                if (idx != string::npos)
                {
                    path = path.substr(idx + 1);
                }
                if (!path_prefix.empty() && path.compare(0, path_prefix.length(), path_prefix) == 0)
                {
                    path = path.substr(path_prefix.length());
                    if (!path.empty() && path[0] == '.')
                    {
                        path = path.substr(1);
                    }
                }

                AdbInstance* inst = rootItem->getChildByPath(path);
                if (!inst)
                {
                    if (strict_instance_ops)
                    {
                        raiseException(allowMultipleExceptions,
                                       "Can't find instance path (" + it->first + ") defined in <instance_ops> section",
                                       ExceptionHolder::ERROR_EXCEPTION);
                    }
                    else
                    {
                        continue;
                    }
                }

                for (AttrsMap::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
                {
                    if (allowMultipleExceptions && !inst)
                    {
                        break;
                    }
                    inst->setInstanceAttr(it2->first, it2->second);
                }
            }
        }

        /* Evaluate unions selector fields*/
        for (typename list<AdbInstance*>::iterator it = _unionSelectorEvalDeffered.begin();
             it != _unionSelectorEvalDeffered.end();
             it++)
        {
            bool foundSelector = true;
            vector<string> path;
            AdbInstance* inst = *it;
            AdbInstance* curInst = inst;
            const string splitVal = inst->getInstanceAttr("union_selector");
            Algorithm::split(path, splitVal, Algorithm::is_any_of("."));
            for (size_t i = 0; i < path.size(); i++)
            {
                // TODO: The code below is shady, looks buggy
                if (path[i] == "#(parent)" || path[i] == "$(parent)")
                {
                    curInst = curInst->parent;
                    if (curInst == NULL || i == path.size() - 1)
                    {
                        foundSelector = false;
                        if (rootNodeName == rootNode)
                        { // give this warning only if this root instantiation
                            if (allowMultipleExceptions)
                                cout << "allow multiple";
                            raiseException(allowMultipleExceptions,
                                           "Invalid union selector (" + inst->fullName() +
                                             "), must be a leaf field, cannot be a parent of root",
                                           ExceptionHolder::ERROR_EXCEPTION);
                        }
                        break;
                    }
                }
                else
                {
                    size_t j;
                    bool inPath = false;
                    for (j = 0; j < curInst->subItems.size(); j++)
                    {
                        if (curInst->subItems[j]->get_field_name() == path[i])
                        {
                            curInst = curInst->subItems[j];
                            inPath = true;
                            break;
                        }
                    }

                    if (j == curInst->subItems.size() && !inPath)
                    {
                        foundSelector = false;
                        if (rootNodeName == rootNode)
                        { // give this warning only if this root instantiation
                            raiseException(allowMultipleExceptions,
                                           "Failed to find union selector for union (" + inst->fullName() +
                                             ") Can't find field (" + path[i] + ") under (" + curInst->fullName() + ")",
                                           ExceptionHolder::ERROR_EXCEPTION);
                        }
                        break;
                    }
                }
            }

            if (foundSelector)
            {
                string selector_val;
                inst->unionSelector = curInst;
                for (size_t i = 0; i < inst->subItems.size(); i++)
                {
                    if (inst->subItems[i]->isReserved())
                    {
                        continue;
                    }

                    // make sure all union subnodes define "selected_by" attribute
                    bool found = inst->subItems[i]->getInstanceAttr("selected_by", selector_val);
                    if (!found)
                    {
                        raiseException(allowMultipleExceptions,
                                       "In union (" + inst->fullName() + ") the union subnode (" +
                                         inst->subItems[i]->get_field_name() + ") doesn't define selection value",
                                       ExceptionHolder::ERROR_EXCEPTION);
                    }

                    // make sure that all union subnodes selector values are defined in the selector field enum
                    if (selector_val == "")
                    {
                        continue;
                    }

                    if (!inst->unionSelector->isEnumExists())
                    {
                        string exceptionTxt = "In union (" + inst->fullName() + ") the union selector (" +
                                              inst->unionSelector->fullName() + ") is not an enum";
                        raiseException(allowMultipleExceptions, exceptionTxt, ExceptionHolder::ERROR_EXCEPTION);
                        break;
                    }

                    map<string, uint64_t>::iterator it;
                    map<string, uint64_t> selectorValMap = inst->unionSelector->getEnumMap();
                    for (it = selectorValMap.begin(); it != selectorValMap.end(); it++)
                    {
                        if (it->first == selector_val)
                        {
                            break;
                        }
                    }

                    // if not found in map throw exeption
                    if (it == selectorValMap.end())
                    {
                        string exceptionTxt = "In union (" + inst->fullName() + ") the union subnode (" +
                                              inst->subItems[i]->get_field_name() + ") uses a selector value (" +
                                              selector_val + ") which isn't defined in the selector field (" +
                                              inst->unionSelector->fullName() + ")";
                        raiseException(allowMultipleExceptions, exceptionTxt, ExceptionHolder::ERROR_EXCEPTION);
                    }
                }
            }
        }

        updateLayoutConditions(false); // Process condition instances
        updateLayoutConditions(true);  // Process conditional arrays

        if (allowMultipleExceptions && ExceptionHolder::getNumberOfExceptions() > 0)
        {
            delete rootItem;
            rootItem = NULL;
        }
        return rootItem;
    }
    catch (AdbException& exp)
    {
        _lastError = exp.what_s();
        if (allowMultipleExceptions)
        {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return nullptr;
    }
    catch (AdbStopException& er)
    {
        return nullptr;
    }
    catch (...)
    {
        _lastError = "Unknown error occurred in create layout";
        ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        return nullptr;
    }
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<U>::type _Adb_impl<eval_expr, O>::updateLayoutConditions(bool useConditionalArrays)
{
    // Choose which list to iterate based on the flag
    const list<AdbInstance*>& instances = useConditionalArrays ? _conditionalArrays : _conditionInstances;

    for (typename list<AdbInstance*>::const_iterator it = instances.begin(); it != instances.end(); it++)
    {
        // Choose which condition object to use based on the flag
        map<string, AdbCondVar>& variables = useConditionalArrays ?
                                               (*it)->inst_ops_props.conditionalSize.get_vars_map() :
                                               (*it)->inst_ops_props.condition.get_vars_map();

        AdbCondition& conditionObj =
          useConditionalArrays ? (*it)->inst_ops_props.conditionalSize : (*it)->inst_ops_props.condition;

        for (typename map<string, AdbCondVar>::iterator it2 = variables.begin(); it2 != variables.end(); it2++)
        {
            string currentName = it2->first;
            AdbCondVar* currentVar = &(it2->second);
            map<string, string>::iterator currentDefine = defines_map.find(currentName);
            if (currentDefine != defines_map.end())
            {
                currentVar->set_value(std::stoi(currentDefine->second));
            }
            else // if it's a conditional variable
            {
                auto& search_path = currentVar->is_name_modified() ? currentVar->get_original_name() : currentName;
            // }
                AdbInstance* reffered_layout_item = (*it)->get_layout_item_by_path(search_path);
                if (reffered_layout_item)
                {
                    currentVar->set_instance(reffered_layout_item);
                    if (reffered_layout_item->isEnumExists())
                    {
                        conditionObj.update_enum(currentName);
                    }
                }
            }
        }
    }
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<!U>::type _Adb_impl<eval_expr, O>::updateLayoutConditions(bool useConditionalArrays)
{
    (void)useConditionalArrays;
    return;
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<U>::type _Adb_impl<eval_expr, O>::updateConditionsLists(AdbInstance* inst)
{
    // if the field has a condition attribute
    if (!inst->inst_ops_props.condition.get_condition().empty())
    {
        _conditionInstances.push_back(inst);
    }

    // if the layout item has a conditional array
    if (!inst->inst_ops_props.conditionalSize.get_condition().empty())
    {
        _conditionalArrays.push_back(inst);
    }
    return;
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<!U>::type _Adb_impl<eval_expr, O>::updateConditionsLists(AdbInstance* inst)
{
    (void)inst;
    return;
}

/**
 * Function: _Adb_impl::getNodeDeps
 **/
template<bool e, typename O>
vector<string> _Adb_impl<e, O>::getNodeDeps(string nodeName)
{
    typename NodesMap::iterator it = nodesMap.find(nodeName);
    if (it == nodesMap.end())
    {
        throw AdbException("Can't find node definition for: " + nodeName);
    }

    AdbNode* node = it->second;
    vector<string> deps(1, node->name);

    for (size_t i = 0; i < node->fields.size(); i++)
    {
        if (node->fields[i]->isStruct())
        {
            deps.push_back(node->fields[i]->subNode);
            vector<string> subDeps = getNodeDeps(node->fields[i]->subNode);
            deps.insert(deps.end(), subDeps.begin(), subDeps.end());
        }
    }

    stable_sort(deps.begin(), deps.end());
    deps.erase(unique(deps.begin(), deps.end()), deps.end());
    return deps;
}

/**
 * Function: _Adb_impl::createInstance
 **/
template<bool eval_expr, typename O>
bool _Adb_impl<eval_expr, O>::createInstance(AdbField* field,
                                             AdbInstance* parent,
                                             map<string, string> vars,
                                             int depth,
                                             bool ignoreMissingNodes,
                                             bool enable_parse_missing_sons,
                                             vector<SplittedPath> parent_missing_sons,
                                             bool allowMultipleExceptions,
                                             bool optimize_time,
                                             PartitionTree* partition_tree,
                                             bool array_path_wildcards)
{
    // Stop on exclude tree leaf
    auto stop_on_partition_tree = partition_tree && partition_tree->stop;

    if (stop_on_partition_tree)
    {
        partition_tree = prune_up(partition_tree);
    }

    AdbNode* node{nullptr};
    if (field->isStruct())
    {
        auto nodes_it = nodesMap.find(field->subNode);
        if (nodes_it == nodesMap.end())
        {
            raiseException(allowMultipleExceptions,
                           "Can't find the definition for subnode: " + field->subNode + " of field: " + field->name,
                           ExceptionHolder::ERROR_EXCEPTION);
        }
        node = nodes_it->second;
    }

    auto missing_sons =
      enable_parse_missing_sons && node ? parse_missing_sons(*node, allowMultipleExceptions) : vector<SplittedPath>();

    for (uint32_t i = 0; i < field->arrayLen(); i++)
    {
        vector<SplittedPath> next_missing_sons = parent_missing_sons;
        if (enable_parse_missing_sons && skip_or_get_child_missing_sons(next_missing_sons, *field, i))
        {
            continue;
        }
        next_missing_sons.insert(next_missing_sons.end(), missing_sons.begin(), missing_sons.end());

        AdbInstance* inst{nullptr};
        string attr_val;
        bool found_attr;
        LayoutItemAttrsMap::iterator found_it;
        try
        {
            inst = new AdbInstance(field, node, i, parent, vars, bigEndianArr, stoi(version), optimize_time,
                                   stop_on_partition_tree, partition_tree, array_path_wildcards);
        }
        catch (AdbException& exp)
        {
            delete inst;
            if (allowMultipleExceptions)
            {
                ExceptionHolder::insertNewException(ExceptionHolder::ERROR_EXCEPTION, exp.what());
                return false;
            }
            else
            {
                throw exp;
            }
        }

        checkInstanceOffsetValidity(inst, parent, allowMultipleExceptions);

        if (!stop_on_partition_tree)
        {
            /* if union and uses selecotr field add it to _unionSelectorEvalDeffered in order to defferred evaluation */
            found_attr = inst->getInstanceAttr("union_selector", attr_val);
            if (inst->isUnion() && found_attr)
            {
                _unionSelectorEvalDeffered.push_back(inst);
            }

            updateConditionsLists(inst);

            if (field->isStruct() && inst->nodeDesc && !inst->nodeDesc->fields.empty() && (depth == -1 || depth > 0))
            {
                if (inst->nodeDesc->inLayout)
                {
                    delete inst;
                    inst = nullptr; // Set inst to nullptr to avoid dangling pointer
                    raiseException(
                      false,
                      "Cyclic definition of nodes, node: " + field->name + " was already added to the layout",
                      ExceptionHolder::ERROR_EXCEPTION);
                }
                else
                {
                    inst->nodeDesc->inLayout = true && depth == -1;
                }

                // // validation 2 TODO: move validation to adbXMLParser
                // if (inst->size != inst->nodeDesc->size)
                // {
                //     inst->nodeDesc->size = inst->size;
                //     /*throw AdbException("Node +(" + inst->name + ") size (" + to_string(inst->size)) +
                //      " isn't the same as its instance (" + inst->nodeDesc->name +
                //      ") (" +  to_string(inst->nodeDesc->size) + ")";*/
                // }

                for (auto it = inst->nodeDesc->fields.begin(); it != inst->nodeDesc->fields.end(); it++)
                {
                    PartitionTree* next_partition_tree = nullptr;
                    if (partition_tree)
                    {
                        auto found_partition_tree =
                          find_if(partition_tree->sub_items.begin(), partition_tree->sub_items.end(),
                                  [&it](PartitionTree* si) { return si->name == (*it)->name; });
                        if (found_partition_tree != partition_tree->sub_items.end())
                        {
                            next_partition_tree = *found_partition_tree;
                        }
                    }
                    createInstance(*it, inst, vars, depth == -1 ? -1 : depth - 1, ignoreMissingNodes,
                                   enable_parse_missing_sons, next_missing_sons, allowMultipleExceptions, optimize_time,
                                   next_partition_tree, array_path_wildcards);
                }
                inst->nodeDesc->inLayout = false;

                if (_checkDsAlign && inst->get_max_leaf_size() != 0 && inst->get_size() % inst->get_max_leaf_size() != 0)
                {
                    raiseException(allowMultipleExceptions,
                                   "Node: " + inst->nodeDesc->name + " size(" + to_string(inst->get_size()) +
                                     ") is not aligned with largest leaf(" + to_string(inst->get_max_leaf_size()) + ")",
                                   ExceptionHolder::ERROR_EXCEPTION);
                }

                if (!inst->isUnion() && inst->subItems.size() > 0)
                {
                    stable_sort(inst->subItems.begin(), inst->subItems.end(),
                                compareFieldsPtr<AdbInstance>); // TODO: try to remove this shit

                    for (size_t j = 0; j < inst->subItems.size() - 1; j++)
                    {
                        if (inst->subItems[j + 1]->offset < inst->subItems[j]->offset + inst->subItems[j]->get_size())
                        {
                            string exceptionTxt =
                              "Field (" + inst->subItems[j + 1]->get_field_name() + ") (" +
                              formatAddr(inst->subItems[j + 1]->offset, inst->subItems[j + 1]->get_size()).c_str() +
                              ") overlaps with (" + inst->subItems[j]->get_field_name() + ") (" +
                              formatAddr(inst->subItems[j]->offset, inst->subItems[j]->get_size()).c_str() + ")";
                            raiseException(allowMultipleExceptions, exceptionTxt, ExceptionHolder::ERROR_EXCEPTION);
                        }
                    }
                }
            }

            inst->update_max_leaf();
        }
        if (parent)
        {
            parent->subItems.push_back(inst);
        }
    }
    return true;
}

/**
 * Function: _Adb_impl::checkInstanceOffsetValidity
 **/
template<bool e, typename O>
void _Adb_impl<e, O>::checkInstanceOffsetValidity(AdbInstance* inst,
                                                  _Adb_impl<e, O>::AdbInstance* parent,
                                                  bool allowMultipleExceptions)
{
    if (inst->offset + inst->get_size() > parent->offset + parent->get_size())
    {
        string exceptionTxt = "Field (" + inst->get_field_name() + ") " + formatAddr(inst->offset, inst->get_size()) +
                              " crosses its parent node (" + parent->get_field_name() + ") " +
                              formatAddr(parent->offset, parent->get_size()) + " boundaries";
        if (allowMultipleExceptions)
        {
            ExceptionHolder::insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
        }
        else
        {
            throw AdbException(exceptionTxt);
        }
    }
}

/**
 * Function: _Adb_impl::checkInstSizeConsistency
 **/
template<bool e, typename O>
bool _Adb_impl<e, O>::checkInstSizeConsistency(bool allowMultipleExceptions)
{
    bool status = true;
    for (typename NodesMap::iterator it = nodesMap.begin(); it != nodesMap.end(); it++)
    {
        for (size_t i = 0; i < it->second->fields.size(); i++)
        {
            if (it->second->fields[i]->isStruct())
            {
                typename NodesMap::iterator iter = nodesMap.find(it->second->fields[i]->subNode);
                if (iter == nodesMap.end())
                {
                    continue;
                    /*
                     _lastError = "Can't find definition of subnode \"" + it->second->fields[i]->subNode +
                     "\" instantiated from node \"" + it->first + "\"";
                     return false;
                     */
                }
                AdbNode* node = nodesMap[it->second->fields[i]->subNode];
                if (node->get_size() != it->second->fields[i]->get_size() / it->second->fields[i]->arrayLen())
                {
                    stringstream err_stream;
                    err_stream << "Node (" << node->name << ") size 0x" << std::hex << ((node->get_size() >> 5) << 2)
                               << "." << node->get_size() % 32 << " is not consistent with the instance ("
                               << it->second->name << "->" << it->second->fields[i]->name << ") size 0x" << std::hex
                               << ((it->second->fields[i]->get_size() >> 5) << 2) << "."
                               << it->second->fields[i]->get_size() % 32;
                    _lastError = err_stream.str();
                    if (allowMultipleExceptions)
                    {
                        status = false;
                        ExceptionHolder::insertNewException(ExceptionHolder::ERROR_EXCEPTION, _lastError);
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }

    return status;
}

/**
 * Function: _Adb_impl::getLastError
 **/
template<bool e, typename O>
string _Adb_impl<e, O>::getLastError()
{
    return _lastError;
}

template<bool e, typename O>
void _Adb_impl<e, O>::add_include(string fileName, string filePath, string included_from, int lineNumber)
{
    includedFiles[fileName] = IncludeFileInfo{filePath, included_from, lineNumber};
}

/**
 * Function: _Adb_impl::print
 **/
template<bool e, typename O>
void _Adb_impl<e, O>::print(int indent)
{
    cout << indentString(indent) << "Include paths: " << endl;
    for (size_t i = 0; i < includePaths.size(); i++)
        cout << indentString(indent + 1) << includePaths[i] << endl;

    cout << indentString(indent) << "Is Big Endian Arrays: " << bigEndianArr << endl;
    cout << "-------------------------------------" << endl;
    cout << indentString(indent) << "Configs: " << endl;
    for (size_t i = 0; i < configs.size(); i++)
        configs[i]->print(indent + 1);

    cout << "-------------------------------------" << endl;
    cout << indentString(indent) << "Nodes" << endl;
    typename NodesMap::iterator iter;
    for (iter = nodesMap.begin(); iter != nodesMap.end(); iter++)
        iter->second->print(indent + 1);
}

template<bool e, typename O>
PartitionTree* _Adb_impl<e, O>::prune_up(PartitionTree* partition_tree)
{
    if (partition_tree->sub_items.size() > 0)
    {
        partition_tree->stop = false;
    }
    else
    {
        auto current_tree = partition_tree;
        PartitionTree* parent_tree = current_tree->parent;
        partition_tree = nullptr;

        do
        {
            auto found = find(parent_tree->sub_items.begin(), parent_tree->sub_items.end(), current_tree);
            parent_tree->sub_items.erase(found);

            auto temp = current_tree;
            current_tree = parent_tree;
            parent_tree = current_tree->parent;
            delete temp;
        } while (parent_tree && current_tree && current_tree->sub_items.size() == 0);
    }
    return partition_tree;
}

template<bool eval_expr, typename T_OFFSET>
uint64_t _Adb_impl<eval_expr, T_OFFSET>::_trvrs_calc_cond_num_elements(AdbInstance* instance,
                                                                       T_OFFSET offset_shift,
                                                                       const uint8_t* buffer,
                                                                       uint32_t buffer_size,
                                                                       bool evaluate_conditions,
                                                                       bool allow_multiple_exceptions)
{
    uint64_t num_elements = 1;
    auto* array_size_condition = instance->getArraySizeCondition();
    if (array_size_condition)
    {
        if (evaluate_conditions)
        {
            try
            {
                // Evaluate the conditional size to get the number of elements
                num_elements = array_size_condition->evaluate(const_cast<uint8_t*>(buffer), offset_shift);
            }
            catch (const AdbException& e)
            {
                // If conditional size evaluation fails, default to 1 element
                num_elements = 1;
                raiseException(
                  allow_multiple_exceptions,
                  "Field " + instance->get_field_name() +
                    " with array size condition, evaluation failed, treating as regular node and processing all children\n" +
                    e.what(),
                  ExceptionHolder::WARN_EXCEPTION, false);
            }
        }
        else if (buffer_size > 0)
        {
            // Calculate maximum number of elements that fit in the remaining buffer
            T_OFFSET current_bit_offset = instance->offset + offset_shift;
            T_OFFSET current_byte_offset = current_bit_offset / 8;
            T_OFFSET remaining_bytes = (buffer_size > current_byte_offset) ? (buffer_size - current_byte_offset) : 0;
            T_OFFSET remaining_bits = remaining_bytes * 8;
            T_OFFSET element_size_bits = instance->get_size();

            if (element_size_bits > 0 && remaining_bits >= element_size_bits)
            {
                num_elements = remaining_bits / element_size_bits;
            }
            else
            {
                num_elements = 0; // No space for even one element
            }
        }
    }
    return num_elements;
}

template<bool eval_expr, typename T_OFFSET>
string _Adb_impl<eval_expr, T_OFFSET>::_trvrs_get_element_array_suffix(uint64_t i, AdbInstance* instance, bool full_path)
{
    string array_index = "";
    string array_suffix = "";
    uint32_t low_bound = instance->fieldDesc ? instance->fieldDesc->lowBound : 0;

    if (instance->fieldDesc && instance->fieldDesc->array_type == AdbField::ArrayType::dynamic)
    {
        array_index = to_string(i + low_bound);
    }
    else if (instance->fieldDesc && instance->fieldDesc->array_type >= AdbField::ArrayType::definite &&
             instance->fieldDesc->array_type < AdbField::ArrayType::dynamic)
    {
        array_index = to_string(instance->arrIdx + low_bound);
    }
    if (!array_index.empty())
    {
        array_suffix =
          full_path || !instance->isNode() || (instance->fieldDesc && instance->fieldDesc->subNode == "uint64") ?
            "[" + array_index + "]" :
            "_" + array_index;
    }
    return array_suffix;
}

template<bool eval_expr, typename T_OFFSET>
void _Adb_impl<eval_expr, T_OFFSET>::_trvrs_handle_enums(
  AdbInstance* instance,
  const string& element_path,
  T_OFFSET element_offset_shift,
  const uint8_t* buffer,
  bool (*func)(const string&, uint64_t, uint64_t, AdbInstance*, void*),
  void* context)
{
    T_OFFSET field_offset = instance->offset + element_offset_shift;
    uint64_t enum_value =
      pop_from_buf(buffer, static_cast<uint32_t>(field_offset), static_cast<uint32_t>(instance->get_size()));

    string enum_string;
    if (instance->intToEnum(enum_value, enum_string))
    {
        // For enums, we could call func with enum string info, but for simplicity use numeric value
        func(element_path, field_offset, enum_value, instance, context);
    }
    else
    {
        func(element_path, field_offset, enum_value, instance, context);
    }
}

template<bool eval_expr, typename T_OFFSET>
typename _Adb_impl<eval_expr, T_OFFSET>::AdbInstance*
  _Adb_impl<eval_expr, T_OFFSET>::_trvrs_get_selected_node(AdbInstance* instance,
                                                           T_OFFSET element_offset_shift,
                                                           const uint8_t* buffer)
{
    u_int32_t selectorValue =
      pop_from_buf(buffer, static_cast<uint32_t>(instance->unionSelector->offset + element_offset_shift),
                   static_cast<uint32_t>(instance->unionSelector->get_size()));

    return instance->getUnionSelectedNodeName(selectorValue);
}

template<bool eval_expr, typename T_OFFSET>
void _Adb_impl<eval_expr, T_OFFSET>::traverse_layout(
  AdbInstance* instance,
  const string& path,
  T_OFFSET offset_shift,
  const uint8_t* buffer,
  uint32_t buffer_size, // TODO: validate correct type size
  bool (*func)(const string&, uint64_t, uint64_t, AdbInstance*, void*),
  void* context,
  bool evaluate_conditions,
  bool handle_enums,
  bool full_path,
  bool allow_multiple_exceptions)
{
    string suffix = "";
    bool stop = false;
    traverse_layout(instance, path, offset_shift, buffer, buffer_size, func, context, suffix, stop, evaluate_conditions,
                    handle_enums, full_path, allow_multiple_exceptions);
}

template<bool eval_expr, typename T_OFFSET>
void _Adb_impl<eval_expr, T_OFFSET>::traverse_layout(
  AdbInstance* instance,
  const string& path,
  T_OFFSET offset_shift,
  const uint8_t* buffer,
  uint32_t buffer_size, // TODO: validate correct type size
  bool (*func)(const string&, uint64_t, uint64_t, AdbInstance*, void*),
  void* context,
  string suffix,
  bool& stop,
  bool evaluate_conditions,
  bool handle_enums,
  bool full_path,
  bool allow_multiple_exceptions)
{
    if (stop || !instance || !func)
    {
        return;
    }

    evaluate_conditions = evaluate_conditions && buffer && buffer_size > 0;
    handle_enums = handle_enums && buffer && buffer_size > 0;

    auto* condition = instance->getCondition();
    if (evaluate_conditions && condition && !condition->get_condition().empty())
    {
        try
        {
            // Use the condition's evaluate method with the buffer
            uint64_t condition_result = condition->evaluate(const_cast<uint8_t*>(buffer), offset_shift);
            if (condition_result == 0)
            {
                return; // Skip this field if condition evaluates to false
            }
        }
        catch (const AdbException& e)
        {
            // failed to evaluate condition, continue with the layout traversal
            raiseException(
              allow_multiple_exceptions,
              "Field " + instance->get_field_name() +
                " with condition, evaluation failed, treating as regular node and processing all children\n" + e.what(),
              ExceptionHolder::WARN_EXCEPTION, false);
        }
    }

    // Handle conditional arrays - evaluate conditional size to get num_elements
    uint64_t num_elements = _trvrs_calc_cond_num_elements(instance, offset_shift, buffer, buffer_size,
                                                          evaluate_conditions, allow_multiple_exceptions);

    string previous_suffix = suffix;
    for (uint64_t i = 0; i < num_elements; i++)
    {
        if (stop)
        {
            return;
        }

        string path_suffix = _trvrs_get_element_array_suffix(i, instance, full_path);
        string element_path = full_path ? path + path_suffix : path;
        if (!full_path && !path_suffix.empty())
        {
            suffix = instance->isNode() ? previous_suffix + path_suffix : path_suffix;
        }

        string sep = element_path.empty() ? "" : ".";
        T_OFFSET element_offset_shift = offset_shift + (instance->get_size() * i);

        // Handle enum fields - similar to _parse_enum_field, but only if handle_enums is true
        if (handle_enums && instance->isEnumExists())
        {
            _trvrs_handle_enums(instance, element_path, element_offset_shift, buffer, func, context);
        }
        // Handle nodes with sub-items (structs/unions) - similar to field.subItems handling
        else if (instance->isNode() && !instance->subItems.empty())
        {
            // For unions, handle selected items (simplified version of _get_union_selected_items)
            if (evaluate_conditions && instance->isUnion() && instance->unionSelector)
            {
                AdbInstance* selectedNode = nullptr;
                try
                {
                    selectedNode = _trvrs_get_selected_node(instance, element_offset_shift, buffer);
                }
                catch (const AdbException& e)
                {
                    // If getUnionSelectedNodeName throws an exception, treat as a regular non-union node
                    // and process all children
                    raiseException(
                      allow_multiple_exceptions,
                      "Field " + instance->get_field_name() +
                        " with union selector failed treating as regular node and processing all children\n" + e.what(),
                      ExceptionHolder::WARN_EXCEPTION, false);
                    for (auto sub_item : instance->subItems)
                    {
                        if (stop)
                        {
                            return;
                        }
                        string sub_item_path =
                          full_path ? element_path + sep + sub_item->fieldDesc->name : sub_item->fieldDesc->name;
                        traverse_layout(sub_item, sub_item_path, element_offset_shift, buffer, buffer_size, func,
                                        context, suffix, stop, evaluate_conditions, handle_enums, full_path,
                                        allow_multiple_exceptions);
                    }
                    return;
                }
                string selected_node_path =
                  full_path ? element_path + sep + selectedNode->fieldDesc->name : selectedNode->fieldDesc->name;
                traverse_layout(selectedNode, selected_node_path, element_offset_shift, buffer, buffer_size, func,
                                context, suffix, stop, evaluate_conditions, handle_enums, full_path,
                                allow_multiple_exceptions);
            }
            else
            {
                for (auto sub_item : instance->subItems)
                {
                    if (stop)
                    {
                        return;
                    }
                    string sub_item_path =
                      full_path ? element_path + sep + sub_item->fieldDesc->name : sub_item->fieldDesc->name;
                    traverse_layout(sub_item, sub_item_path, element_offset_shift, buffer, buffer_size, func, context,
                                    suffix, stop, evaluate_conditions, handle_enums, full_path,
                                    allow_multiple_exceptions);
                }
            }
        }
        // Handle leaf fields - similar to the final else clause in _parse_seg_field
        else
        {
            T_OFFSET field_offset = instance->offset + element_offset_shift;
            uint64_t value = 0;
            if (buffer)
            {
                if (buffer_size >= (field_offset + instance->get_size()) / 8)
                {
                    value = pop_from_buf(buffer, static_cast<uint32_t>(field_offset),
                                         static_cast<uint32_t>(instance->get_size()));
                }
                else
                {
                    raiseException(allow_multiple_exceptions,
                                   "On layout traversal, trying to evaluate field, " + instance->get_field_name() +
                                     ", with offset, " + to_string(field_offset) + ",overflowing the buffer size, " +
                                     to_string(buffer_size) + "\n",
                                   ExceptionHolder::ERROR_EXCEPTION);
                }
            }
            if (!full_path)
            {
                bool is_uint64 =
                  instance->parent && instance->parent->fieldDesc && instance->parent->fieldDesc->subNode == "uint64";
                if (is_uint64)
                {
                    element_path = instance->parent->fieldDesc->name + suffix + "_" + element_path;
                }
                else if (!suffix.empty())
                {
                    element_path += suffix;
                }
            }
            stop = func(element_path, field_offset, value, instance, context);
        }
    }
}

template class _Adb_impl<false, uint32_t>;
template class _Adb_impl<false, uint64_t>;

template class _Adb_impl<true, uint32_t>;
template class _Adb_impl<true, uint64_t>;
