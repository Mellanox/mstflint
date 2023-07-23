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
/*************************** Adb ***************************/
/**
 * Function: Adb::Adb
 **/

#include "adb_parser.h"
#include "adb_xml_parser.h"

#include "adb_instance.h"
#include "adb_condition.h"
#include "adb_condVar.h"
#include "buf_ops.h"

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace xmlCreator;

#if 0

int main()
{
#define ADB_FILE "path_to.adb"
    Adb adb;
    if (!adb.load(ADB_FILE, true)) {
        printf("Failed : %s\n", adb.getLastError().c_str());
        return 1;
    }

    try
    {
        //adb.print(0);
        cout << "Root node: " << adb.rootNode << endl;
        AdbInstance *root = adb.createLayout(adb.rootNode, false, NULL);
        AdbInstance *child = root->getChildByPath("packetA.x");
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

Adb::Adb() : bigEndianArr(false), singleEntryArrSupp(false), _checkDsAlign(false), _enforceGuiChecks(false)
{
    _logFile = new LogFile;
}

/**
 * Function: Adb::~Adb
 **/
Adb::~Adb()
{
    // Free configs
    for (size_t i = 0; i < configs.size(); i++)
        delete configs[i];

    // Free nodes
    NodesMap::iterator iter;
    for (iter = nodesMap.begin(); iter != nodesMap.end(); iter++)
        delete iter->second;

    delete _logFile;
}

/**
 * Function: Adb::raiseException
 **/
void Adb::raiseException(bool allowMultipleExceptions, string exceptionTxt, const string expType)
{
    if (allowMultipleExceptions)
    {
        ExceptionHolder::insertNewException(expType, exceptionTxt);
    }
    else
    {
        throw AdbException(exceptionTxt);
    }
    return;
}

/**
 * Function: Adb::getAdbExceptionsMap
 * This function return the adb exception map
 **/
void Adb::fetchAdbExceptionsMap(ExceptionsMap otherMap)
{
    vector<string> fatals = otherMap[ExceptionHolder::FATAL_EXCEPTION];
    for (vector<string>::iterator it = fatals.begin(); it != fatals.end(); ++it)
    {
        insertNewException(ExceptionHolder::FATAL_EXCEPTION, *it);
    }
    vector<string> errors = otherMap[ExceptionHolder::ERROR_EXCEPTION];
    for (vector<string>::iterator it = errors.begin(); it != errors.end(); ++it)
    {
        insertNewException(ExceptionHolder::ERROR_EXCEPTION, *it);
    }
    vector<string> warnings = otherMap[ExceptionHolder::WARN_EXCEPTION];
    for (vector<string>::iterator it = warnings.begin(); it != warnings.end(); ++it)
    {
        insertNewException(ExceptionHolder::WARN_EXCEPTION, *it);
    }
}

/**
 * Function: Adb::insertNewException
 * This function take the excpetion type [FATAL:0, ERROR:1, WARNING:2] and the exception string
 * Then it insert it to the adb exception map
 **/
void Adb::insertNewException(const string exceptionType, string exceptionTxt)
{
    adbExceptionMap[exceptionType].push_back(exceptionTxt);
}

/**
 * Function: Adb::printAdbExceptionMap
 * This function will pring the content of the Adb Exception Map
 **/
string Adb::printAdbExceptionMap()
{
    string errorStr = "";
    vector<string> fatals = adbExceptionMap[ExceptionHolder::FATAL_EXCEPTION];
    for (vector<string>::iterator it = fatals.begin(); it != fatals.end(); ++it)
    {
        errorStr += "-" + ExceptionHolder::FATAL_EXCEPTION + "- " + *it + ";";
    }
    vector<string> errors = adbExceptionMap[ExceptionHolder::ERROR_EXCEPTION];
    for (vector<string>::iterator it = errors.begin(); it != errors.end(); ++it)
    {
        errorStr += "-" + ExceptionHolder::ERROR_EXCEPTION + "- " + *it + ";";
    }
    vector<string> warnings = adbExceptionMap[ExceptionHolder::WARN_EXCEPTION];
    for (vector<string>::iterator it = warnings.begin(); it != warnings.end(); ++it)
    {
        errorStr += "-" + ExceptionHolder::WARN_EXCEPTION + "- " + "- " + *it + ";";
    }
    return errorStr;
}

/**
 * Function: Adb::load
 **/
bool Adb::load(string fname,
               bool addReserved,
               bool evalExpr,
               bool strict,
               string includePath,
               string includeDir,
               bool enforceExtraChecks,
               bool allowMultipleExceptions,
               string logFileStr,
               bool checkDsAlign,
               bool enforceGuiChecks,
               bool force_pad_32)
{
    try
    {
        bool status = true;
        mainFileName = fname;
        if (allowMultipleExceptions)
        {
            AdbParser::setAllowMultipleExceptionsTrue();
        }
        _logFile->init(logFileStr, allowMultipleExceptions);
        AdbParser p(fname, this, addReserved, evalExpr, strict, includePath, enforceExtraChecks, checkDsAlign,
                    enforceGuiChecks, force_pad_32);
        _checkDsAlign = checkDsAlign;
        _enforceGuiChecks = enforceGuiChecks;
        if (!p.load())
        {
            _lastError = p.getError();
            status = false;
        }
        if (status && includeDir != "")
        {
            AdbParser::includeAllFilesInDir(&p, includeDir);
        }
        if (status && !nodesMap.size())
        {
            _lastError = "Empty project, no nodes were found";
            if (allowMultipleExceptions)
            {
                insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
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
            fetchAdbExceptionsMap(ExceptionHolder::getAdbExceptionsMap());
            status = false;
        }
        return status;
    }
    catch (AdbException& e)
    {
        _lastError = e.what_s();
        if (allowMultipleExceptions)
        {
            insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }
}

/**
 * Function: Adb::loadFromString
 **/
bool Adb::loadFromString(const char* adbContents, bool addReserved, bool evalExpr, bool strict, bool enforceExtraChecks)
{
    try
    {
        AdbParser p(string(), this, addReserved, evalExpr, strict, "", enforceExtraChecks);
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
    catch (AdbException& e)
    {
        _lastError = e.what_s();
        return false;
    }
}

/**
 * Function: Adb::toXml
 **/
string Adb::toXml(vector<string> nodeNames, bool addRootNode, string rootName, string addPrefix)
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
            for (NodesMap::iterator it = nodesMap.begin(); it != nodesMap.end(); it++)
            {
                AdbNode* node = it->second;
                xml += node->toXml(addPrefix);
            }
        }
        else
        {
            u_int32_t maxSize = 0;
            for (size_t i = 0; i < nodeDeps.size(); i++)
            {
                NodesMap::iterator it = nodesMap.find(nodeDeps[i]);
                if (it == nodesMap.end())
                {
                    _lastError = "Can't find node definition for: " + nodeDeps[i];
                    return "";
                }

                AdbNode* node = it->second;
                xml += node->toXml(addPrefix) + "\n\n";

                maxSize = TOOLS_MAX(node->size, maxSize);
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
                        << ((node->size >> 5) << 2) << "." << dec << (node->size % 32)
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
 * Function: Adb::addMissingNodes
 **/

AdbInstance* Adb::addMissingNodes(int depth, bool allowMultipleExceptions)
{
    try
    {
        NodesMap::iterator it;
        for (it = nodesMap.begin(); it != nodesMap.end(); it++)
        {
            AdbNode* nodeDesc = it->second;
            for (size_t i = 0; (depth == -1 || depth > 0) && i < nodeDesc->fields.size(); i++)
            {
                AdbField* fieldDesc = nodeDesc->fields[i];
                for (u_int32_t i = 0; i < fieldDesc->arrayLen(); i++)
                {
                    if (fieldDesc->isStruct())
                    {
                        NodesMap::iterator it2 = nodesMap.find(fieldDesc->subNode);
                        if (it2 == nodesMap.end())
                        {
                            // If in ignore missing nodes mode, it should create temporary node with placeholder
                            AdbNode* tmpNode = new AdbNode;
                            tmpNode->name = fieldDesc->subNode;
                            tmpNode->size = fieldDesc->eSize();
                            tmpNode->desc = fieldDesc->desc + " ***MISSING NODE***";
                            tmpNode->isUnion = false;
                            tmpNode->fileName = "tempForMissingNodes.adb";
                            tmpNode->lineNumber = 0;
                            AdbField* tmpField = new AdbField;
                            tmpField->name = "placeholder";
                            tmpField->desc = "This field is part of auto generated node for missing node.";
                            tmpField->size = tmpNode->size;
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
            insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return NULL;
    }
    catch (...)
    {
        _lastError = "Unknown error occurred";
        return NULL;
    }
    return NULL;
}

/**
 * Function: Adb::createLayout
 **/
AdbInstance* Adb::createLayout(string rootNodeName,
                               bool isExprEval,
                               int depth,
                               bool ignoreMissingNodes,
                               bool allowMultipleExceptions)
{
    try
    {
        // find root in nodes map
        NodesMap::iterator it;
        it = nodesMap.find(rootNodeName);
        if (it == nodesMap.end())
        {
            raiseException(allowMultipleExceptions,
                           "Can't find definition for node \"" + rootNodeName + "\"",
                           ExceptionHolder::FATAL_EXCEPTION);
        }

        AdbNode* nodeDesc = it->second;
        nodeDesc->inLayout = true;
        AdbInstance* rootItem = new AdbInstance();
        rootItem->fieldDesc = NULL;
        rootItem->nodeDesc = nodeDesc;
        rootItem->parent = NULL;
        rootItem->layout_item_name = nodeDesc->name;
        rootItem->offset = 0;
        rootItem->size = nodeDesc->size;
        if (isExprEval)
        {
            rootItem->initInstOps(true);
        }

        map<string, string> emptyVars;
        _unionSelectorEvalDeffered.clear();
        _conditionInstances.clear();
        _conditionalArrays.clear();
        if (ignoreMissingNodes)
        {
            addMissingNodes(depth, allowMultipleExceptions);
        }

        for (size_t i = 0; (depth == -1 || depth > 0) && i < nodeDesc->fields.size(); i++)
        {
            createInstance(nodeDesc->fields[i], rootItem, emptyVars, isExprEval, depth == -1 ? -1 : depth - 1,
                           ignoreMissingNodes, allowMultipleExceptions);
        }

        // Now set the instance attributes (override field attrs), only if this is root node instantiation
        if (isExprEval && rootNodeName == rootNode && depth == -1)
        {
            for (InstanceAttrs::iterator it = instAttrs.begin(); it != instAttrs.end(); it++)
            {
                size_t idx = it->first.find(".");
                string path = idx == string::npos ? string() : it->first.substr(idx + 1);

                AdbInstance* inst = rootItem->getChildByPath(path);
                if (!inst)
                {
                    raiseException(allowMultipleExceptions,
                                   "Can't find instance path (" + it->first + ") defined in <instance_ops> section",
                                   ExceptionHolder::ERROR_EXCEPTION);
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
        for (list<AdbInstance*>::iterator it = _unionSelectorEvalDeffered.begin();
             it != _unionSelectorEvalDeffered.end();
             it++)
        {
            bool foundSelector = true;
            vector<string> path;
            AdbInstance* inst = *it;
            AdbInstance* curInst = inst;
            const string splitVal = inst->getInstanceAttr("union_selector");
            boost::algorithm::split(path, splitVal, boost::is_any_of(string(".")));
            for (size_t i = 0; i < path.size(); i++)
            {
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

                    map<string, u_int64_t>::iterator it;
                    map<string, u_int64_t> selectorValMap = inst->unionSelector->getEnumMap();
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

        // initialize condition variables objects
        if (isExprEval)
        {
            for (list<AdbInstance*>::iterator it = _conditionInstances.begin(); it != _conditionInstances.end(); it++)
            {
                map<string, CondVar> variables = (*it)->inst_ops_props->condition.getVarsMap();
                for (map<string, CondVar>::iterator it2 = variables.begin(); it2 != variables.end(); it2++)
                {
                    string currentName = it2->first;
                    CondVar* currentVar = &(it2->second);
                    map<string, string>::iterator currentDefine = defines_map.find(currentName);
                    if (currentDefine != defines_map.end())
                    {
                        currentVar->setScalar(std::stoi(currentDefine->second));
                    }
                    // else // if it's a conditional variable
                    // {
                    //     //TODO: to be evaluated later!
                    // }
                }
            }

            // validate size condition
            for (list<AdbInstance*>::iterator it = _conditionalArrays.begin(); it != _conditionalArrays.end(); it++)
            {
                string condSize = (*it)->inst_ops_props->conditionalSize.getCondition();

                if ((*it)->parent->getChildByPath(condSize) == nullptr)
                {
                    raiseException(allowMultipleExceptions,
                                   "The size_condition path doesn't exist. In instance: \"" + (*it)->fullName() + "\"" +
                                     "field name: \"" + (*it)->fieldDesc->name + "\"",
                                   ExceptionHolder::FATAL_EXCEPTION);
                }
            }
        }

        if (allowMultipleExceptions && ExceptionHolder::getNumberOfExceptions() > 0)
        {
            fetchAdbExceptionsMap(ExceptionHolder::getAdbExceptionsMap());
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
            insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return NULL;
    }
    catch (...)
    {
        _lastError = "Unknown error occurred";
        return NULL;
    }
}

/**
 * Function: Adb::getNodeDeps
 **/
vector<string> Adb::getNodeDeps(string nodeName)
{
    NodesMap::iterator it = nodesMap.find(nodeName);
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
 * Function: Adb::createInstance
 **/
bool Adb::createInstance(AdbField* field,
                         AdbInstance* parent,
                         map<string, string> vars,
                         bool isExprEval,
                         int depth,
                         bool ignoreMissingNodes,
                         bool allowMultipleExceptions)
{
    for (u_int32_t i = 0; i < field->arrayLen(); i++)
    {
        AdbInstance* inst{nullptr};
        AdbNode* node{nullptr};
        string attr_val;
        bool found_attr;
        LayoutItemAttrsMap::iterator found_it;
        try
        {
            if (field->isStruct())
            {
                auto nodes_it = nodesMap.find(field->subNode);
                if (nodes_it == nodesMap.end())
                {
                    throw AdbException("Can't find the definition for subnode: " + field->subNode +
                                       " of field: " + field->name);
                }
                node = nodes_it->second;
            }
            inst = new AdbInstance(field, node, i, parent, vars, bigEndianArr, isExprEval, stoi(version));
        }
        catch (AdbException& exp)
        {
            delete inst;
            if (allowMultipleExceptions)
            {
                insertNewException(ExceptionHolder::ERROR_EXCEPTION, exp.what());
            }
            else
            {
                throw exp;
            }
        }

        /* if union and uses selecotr field add it to _unionSelectorEvalDeffered in order to defferred evaluation */
        found_attr = inst->getInstanceAttr("union_selector", attr_val);
        if (inst->isUnion() && found_attr)
        {
            _unionSelectorEvalDeffered.push_back(inst);
        }

        if (isExprEval)
        {
            // if the field has a condition attribute
            if (!inst->inst_ops_props->condition.getCondition().empty())
            {
                _conditionInstances.push_back(inst);
            }

            // if the layout item has a conditional array
            if (!inst->inst_ops_props->conditionalSize.getCondition().empty())
            {
                _conditionalArrays.push_back(inst);
            }
        }

        checkInstanceOffsetValidity(inst, parent, allowMultipleExceptions);

        if (field->isStruct() && !inst->nodeDesc->fields.empty() && (depth == -1 || depth > 0))
        {
            if (inst->nodeDesc->inLayout)
            {
                delete inst;
                raiseException(false,
                               "Cyclic definition of nodes, node: " + field->name + " was already added to the layout",
                               ExceptionHolder::ERROR_EXCEPTION);
            }
            inst->nodeDesc->inLayout = true;

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
                createInstance(*it, inst, vars, isExprEval, depth == -1 ? -1 : depth - 1, ignoreMissingNodes,
                               allowMultipleExceptions);
            }
            inst->nodeDesc->inLayout = false;

            if (_checkDsAlign && inst->maxLeafSize != 0 && inst->size % inst->maxLeafSize != 0)
            {
                raiseException(allowMultipleExceptions,
                               "Node: " + inst->nodeDesc->name + " size(" + to_string(inst->size) +
                                 ") is not aligned with largest leaf(" + to_string(inst->maxLeafSize) + ")",
                               ExceptionHolder::ERROR_EXCEPTION);
            }

            if (!inst->isUnion() && inst->subItems.size() > 0)
            {
                stable_sort(inst->subItems.begin(), inst->subItems.end(),
                            compareFieldsPtr<AdbInstance>); // TODO: try to remove this shit

                for (size_t j = 0; j < inst->subItems.size() - 1; j++)
                {
                    if (inst->subItems[j + 1]->offset < inst->subItems[j]->offset + inst->subItems[j]->size)
                    {
                        string exceptionTxt =
                          "Field (" + inst->subItems[j + 1]->get_field_name() + ") (" +
                          formatAddr(inst->subItems[j + 1]->offset, inst->subItems[j + 1]->size).c_str() +
                          ") overlaps with (" + inst->subItems[j]->get_field_name() + ") (" +
                          formatAddr(inst->subItems[j]->offset, inst->subItems[j]->size).c_str() + ")";
                        raiseException(allowMultipleExceptions, exceptionTxt, ExceptionHolder::ERROR_EXCEPTION);
                    }
                }
            }
        }

        u_int32_t esize = inst->fieldDesc->size;
        if ((field->isLeaf() || field->subNode == "uint64") && (esize == 16 || esize == 32 || esize == 64)) // A leaf
        {
            inst->maxLeafSize = esize;
        }
        if (parent)
        {
            parent->subItems.push_back(inst);
            if (inst->maxLeafSize > parent->maxLeafSize)
            {
                parent->maxLeafSize = inst->maxLeafSize;
            }
        }
    }
    return true;
}

/**
 * Function: Adb::checkInstanceOffsetValidity
 **/
void Adb::checkInstanceOffsetValidity(AdbInstance* inst, AdbInstance* parent, bool allowMultipleExceptions)
{
    if (inst->offset + inst->size > parent->offset + parent->size)
    {
        string exceptionTxt = "Field (" + inst->get_field_name() + ") " + formatAddr(inst->offset, inst->size) +
                              " crosses its parent node (" + parent->get_field_name() + ") " +
                              formatAddr(parent->offset, parent->size) + " boundaries";
        if (allowMultipleExceptions)
        {
            insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
        }
        else
        {
            throw AdbException(exceptionTxt);
        }
    }
}

/**
 * Function: Adb::checkInstSizeConsistency
 **/
bool Adb::checkInstSizeConsistency(bool allowMultipleExceptions)
{
    bool status = true;
    for (NodesMap::iterator it = nodesMap.begin(); it != nodesMap.end(); it++)
    {
        for (size_t i = 0; i < it->second->fields.size(); i++)
        {
            if (it->second->fields[i]->isStruct())
            {
                NodesMap::iterator iter = nodesMap.find(it->second->fields[i]->subNode);
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
                if (node->size != it->second->fields[i]->size / it->second->fields[i]->arrayLen())
                {
                    char tmp[256];
                    sprintf(tmp, "Node (%s) size 0x%x.%d is not consistent with the instance (%s->%s) size 0x%x.%d",
                            node->name.c_str(), (node->size >> 5) << 2, node->size % 32, it->second->name.c_str(),
                            it->second->fields[i]->name.c_str(), (it->second->fields[i]->size >> 5) << 2,
                            it->second->fields[i]->size % 32);
                    _lastError = tmp;
                    if (allowMultipleExceptions)
                    {
                        status = false;
                        insertNewException(ExceptionHolder::ERROR_EXCEPTION, tmp);
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
 * Function: Adb::getLastError
 **/
string Adb::getLastError()
{
    return _lastError;
}

void Adb::add_include(string fileName, string filePath, string included_from, int lineNumber)
{
    includedFiles[fileName] = IncludeFileInfo{filePath, included_from, lineNumber};
}

/**
 * Function: Adb::print
 **/
void Adb::print(int indent)
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
    NodesMap::iterator iter;
    for (iter = nodesMap.begin(); iter != nodesMap.end(); iter++)
        iter->second->print(indent + 1);
}
