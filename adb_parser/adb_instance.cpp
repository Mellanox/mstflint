/*
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
/*************************** AdbInstance ***************************/
/**
 * Function: AdbInstance::AdbInstance
 **/

#include "adb_instance.h"
#include "adb_node.h"
#include "adb_field.h"
#include "adb_expr.h"
#include "adb_exceptionHolder.h"
#include "buf_ops.h"
#include <string>
#include <boost/algorithm/string.hpp>

#include <list>

#if __cplusplus >= 201402L
#include <regex>
#else
#include <boost/regex.hpp>
using namespace boost;
#endif

// Constants
const char AdbInstance::path_seperator{'.'};
const string AdbInstance::EXP_PATTERN{"\\s*([a-zA-Z0-9_]+)=((\\$\\(.*?\\)|\\S+|$)*)\\s*"};

string addPathSuffixForArraySupport(string path)
{
    if (path[path.length() - 1] == ']')
    { // Won't add suffix if leaf is in Array
        return "";
    }
    size_t pos = 0;
    string suffix = "";
    while ((pos = path.find("[")) != std::string::npos)
    { // Add array index number in path to suffix.
        size_t end_pos = path.find("]");
        size_t len = end_pos - pos - 1;
        suffix = suffix + "_" + path.substr(pos + 1, len);
        path.erase(0, end_pos + 1);
    }
    return suffix;
}

AdbInstance::AdbInstance(AdbField* i_fieldDesc,
                         AdbNode* i_nodeDesc,
                         u_int32_t i_arrIdx,
                         AdbInstance* i_parent,
                         map<string, string> vars,
                         bool bigEndianArr,
                         bool isExprEval,
                         unsigned char adabe_version) :
    fieldDesc(i_fieldDesc),
    nodeDesc(i_nodeDesc),
    parent(i_parent),
    arrIdx(i_arrIdx),
    offset(calcArrOffset(bigEndianArr)),
    size(i_fieldDesc->eSize())
{
    // Re-initializations due to packing efficiency
    string array_name_suffix{fieldDesc->isArray() ? "[" + to_string(arrIdx + fieldDesc->lowBound) + "]" : ""};
    layout_item_name = i_fieldDesc->name + array_name_suffix;

    // TODO: the whole block below looks unnecesarry
    if (fieldDesc->offset == 0xffffffff)
    {
        if (parent->subItems.size() > 0)
        {
            fieldDesc->offset = parent->subItems.back()->offset;
        }
        else
        {
            fieldDesc->offset = parent->offset;
        }
    }

    init_props(adabe_version);

    if (isExprEval)
    {
        initInstOps(false);
        eval_expressions(vars);
    }
}

void AdbInstance::initInstOps(bool is_root)
{
    AttrsMap& attrs_map = is_root ? nodeDesc->attrs : fieldDesc->attrs;
    inst_ops_props = new InstOpsProperties(attrs_map);

    auto found_it = getInstanceAttrIterator("condition");
    if (found_it != inst_ops_props->instAttrsMap.end() && parent->getInstanceAttr("is_conditional") == "1")
    {
        inst_ops_props->condition.setCondition(found_it->second);
    }

    found_it = getInstanceAttrIterator("size_condition");
    if (found_it != inst_ops_props->instAttrsMap.end())
    {
        string cond_size = found_it->second;
        if (cond_size.substr(0, 10) == "$(parent).")
        {
            cond_size.erase(0, 10);
        }
        inst_ops_props->conditionalSize.setCondition(cond_size);
    }
}

/**
 * Function: Adb::calcArrOffset
 **/
u_int32_t AdbInstance::calcArrOffset(bool bigEndianArr)
{
    u_int32_t o_offset;
    if (fieldDesc->eSize() >= 32)
    {
        // Make sure this is dword aligned
        if (fieldDesc->eSize() % 32 || parent->offset % 32 || fieldDesc->offset % 32)
        {
            throw AdbException("Field " + fieldDesc->name + " isn't dword aligned");
        }
        o_offset = parent->offset + fieldDesc->offset + fieldDesc->eSize() * arrIdx;
    }
    else
    {
        if (bigEndianArr)
        {
            o_offset = (int)parent->offset + (int)fieldDesc->offset - (int)fieldDesc->eSize() * arrIdx;

            int dwordDelta = abs((dword(parent->offset + fieldDesc->offset) - dword(o_offset))) / 4;

            if (dwordDelta)
            {
                o_offset += 32 * 2 * dwordDelta;
            }
        }
        else
        {
            o_offset = parent->offset + fieldDesc->offset + fieldDesc->eSize() * arrIdx;
        }
    }
    return o_offset;
}

void AdbInstance::eval_expressions(AttrsMap& parent_vars)
{
    static regex EXP_REGEX(EXP_PATTERN);
    try
    {
        // First add the special variables
        parent_vars["NAME"] = layout_item_name;
        parent_vars["ARR_IDX"] = to_string(arrIdx);
        parent_vars["BN"] = "[" + to_string(offset % 32 + size - 1) + ":" + to_string(offset % 32) + "]";
        parent_vars["parent"] = "#(parent)"; // special internal name

        // Get variables attribute value
        AttrsMap::iterator it = fieldDesc->attrs.find("variables");

        // build var_name->value map from varAttrStr
        if (it != fieldDesc->attrs.end())
        {
            string& varStr = it->second;
            boost::algorithm::trim(varStr);
            match_results<string::const_iterator> what;
            string::const_iterator start = varStr.begin();
            string::const_iterator end = varStr.end();

            string var;
            string exp;

            while (regex_search(start, end, what, EXP_REGEX))
            {
                var = string(what[1].first, what[1].second);
                exp = string(what[2].first, what[2].second);

                parent_vars[var] = evalExpr(exp, &parent_vars);
                start = what[0].second;
            }
        }

        // evaluate other attrs
        for (auto attr : fieldDesc->attrs)
        {
            if (attr.first == "variables")
            {
                continue;
            }
            inst_ops_props->instAttrsMap[attr.first] = evalExpr(attr.second, &parent_vars);
        }
        inst_ops_props->varsMap = parent_vars;
    }
    catch (AdbException& exp)
    {
        string exceptionTxt = "Failed to evaluate expression for field (" + fullName() + "): " + exp.what_s();
        throw AdbException(exceptionTxt);
    }
}

/**
 * Function: Adb::evalExpr
 **/
string AdbInstance::evalExpr(string expr, AttrsMap* vars)
{
    if (expr.find('$') == string::npos)
    {
        return expr;
    }

    smatch what, what2;
    regex singleExpr("^([^\\$]*)(\\$\\(([^)]+)\\))(.*)$");
    while (regex_search(expr, what, singleExpr))
    {
        string vname = what[3].str();
        string vvalue;
        regex singleVar("^[a-zA-Z_][a-zA-Z0-9_]*$");

        // Need to change to array-like initialization when we'll move to c++11
        vector<string> specialVars;
        specialVars.push_back("NAME");
        specialVars.push_back("ARR_IDX");
        specialVars.push_back("BN");
        specialVars.push_back("parent");

        if (regex_search(vname, what2, singleVar))
        {
            if (find(specialVars.begin(), specialVars.end(), vname) == specialVars.end())
            {
                return expr;
            }
            else
            {
                AttrsMap::iterator it = vars->find(vname);
                if (it == vars->end())
                {
                    throw AdbException("Can't find the variable: " + vname);
                }
                vvalue = it->second;
            }
        }
        else
        {
            string vnameCopy = vname;
            regex singleVarInExpr("[a-zA-Z_][a-zA-Z0-9_]*");
            smatch matches;
            while (regex_search(vnameCopy, matches, singleVarInExpr))
            {
                if (find(specialVars.begin(), specialVars.end(), matches[0]) == specialVars.end())
                {
                    return expr;
                }
                vnameCopy = matches.suffix();
            }

            char exp[vname.size() + 1];
            char* expPtr = exp;
            strcpy(exp, vname.c_str());
            u_int64_t res;
            AdbExpr adbExpr;
            adbExpr.setVars(vars);
            int status = adbExpr.expr(&expPtr, &res);
            string statusStr;

            if (status < 0)
            {
                switch (status)
                {
                    case Expr::ERR_RPAR_EXP:
                        statusStr = "Right parentheses expected";
                        break;

                    case Expr::ERR_VALUE_EXP:
                        statusStr = "Value expected";
                        break;

                    case Expr::ERR_BIN_EXP:
                        statusStr = "Binary operation expected ";
                        break;

                    case Expr::ERR_DIV_ZERO:
                        statusStr = "Divide zero attempt";
                        break;

                    case Expr::ERR_BAD_NUMBER:
                        statusStr = "Bad constant syntax";
                        break;

                    case Expr::ERR_BAD_NAME:
                        statusStr = "Variable Name not resolved";
                        break;

                    default:
                        statusStr = "Unknown error";
                }

                throw AdbException("Error evaluating expression " + expr + " : " + statusStr);
            }

            vvalue = to_string(res);
        }

        expr = what[1].str() + vvalue + what[4].str();
    }

    return expr;
}

/**
 * Function: AdbInstance::AdbInstance
 **/
AdbInstance::~AdbInstance()
{
    for (size_t i = 0; i < subItems.size(); i++)
    {
        delete subItems[i];
    }

    if (inst_ops_props)
    {
        delete inst_ops_props;
    }
}

/**
 * Function: AdbInstance::get_field_name
 **/
const string& AdbInstance::get_field_name()
{
    return layout_item_name;
}

/**
 * Function: AdbInstance::isLeaf
 **/
bool AdbInstance::isLeaf()
{
    return nodeDesc == NULL;
}

/**
 * Function: isUnionisUnion
 **/
bool AdbInstance::isUnion()
{
    return isNode() && nodeDesc->isUnion;
}

/**
 * Function: AdbInstance::isStruct
 **/
bool AdbInstance::isStruct()
{
    return isNode() && !isUnion();
}

/**
 * Function: AdbInstance::isNode
 **/
bool AdbInstance::isNode()
{
    return !isLeaf();
}

/**
 * Function: AdbInstance::isNode
 **/
bool AdbInstance::isPartOfArray()
{
    return fieldDesc->isArray();
}

/**
 * Function: AdbInstance::fullName
 **/
string AdbInstance::fullName(size_t skipLevel)
{
    list<string> fnList;
    AdbInstance* p = parent;

    fnList.push_front(layout_item_name);
    while (p != NULL)
    {
        fnList.push_front(p->layout_item_name);
        p = p->parent;
    }

    if (fnList.size() > skipLevel)
    {
        while (skipLevel--)
        {
            fnList.pop_front();
        }

        return boost::algorithm::join(fnList, ".");
    }
    else
    {
        return fnList.back();
    }
}

void AdbInstance::init_props(unsigned char adabe_version) // logic of this function is copied from devmon and it's
                                                          // bugous
{
    if (!fieldDesc)
    {
        return;
    }
    if (isPartOfArray())
    {
        string fiVal = getInstanceAttr("valid_first_index");
        string strideVal = getInstanceAttr("valid_stride");

        if (!fiVal.empty() && !strideVal.empty())
        {
            u_int32_t fi = stoul(fiVal);
            int stride = stoi(strideVal);
            if (arrIdx < fi || (arrIdx - fi) % stride != 0)
            {
                inst_props.valid_array_index = 0;
            }
        }
    }

    string access_type;
    string sem;
    if (adabe_version == 2)
    {
        access_type = getInstanceAttr("access_type");
        if (access_type == "ReadSet")
        {
            inst_props.is_semaphore = 1;
        }
        else if (access_type == "WO")
        {
            inst_props.access_r = 0;
        }
        else if (access_type == "RO")
        {
            inst_props.access_w = 0;
        }
    }
    else
    {
        sem = getInstanceAttr("sem");
        access_type = getInstanceAttr("rw");
        if (!sem.empty())
        {
            inst_props.is_semaphore = stoi(sem) > 0;
        }
        if (access_type == "WO")
        {
            inst_props.access_r = 0;
        }
        else if (access_type == "RO")
        {
            inst_props.access_w = 0;
        }
    }

    sem = getInstanceAttr("gw");
    if (!sem.empty())
    {
        inst_props.is_semaphore = stoi(sem) > 0;
    }

    if (parent)
    {
        if (!parent->inst_props.valid_array_index)
        {
            inst_props.valid_array_index = 0;
        }

        if (!inst_props.valid_array_index)
        {
            inst_props.access_r = 1;
            inst_props.access_w = 1;
            inst_props.is_semaphore = 0;
        }
        else
        {
            // if (parent->inst_ops.access_r && !parent->inst_ops.access_w)
            // {
            //     inst_ops.access_w = 0;
            // }
            // if (!parent->inst_ops.access_r && parent->inst_ops.access_w)
            // {
            //     inst_ops.access_r = 0;
            // }
            if (parent->inst_props.is_semaphore)
            {
                inst_props.is_semaphore = 1;
            }
        }
    }
}

/**
 * Function: AdbInstance::fullName
 **/
bool AdbInstance::isReserved()
{
    return fieldDesc->isReserved;
}

bool AdbInstance::is_valid_array_index() const
{
    return inst_props.valid_array_index;
}

bool AdbInstance::is_semaphore() const
{
    return inst_props.is_semaphore;
}

bool AdbInstance::is_ro() const
{
    return inst_props.access_r && !inst_props.access_w;
}

bool AdbInstance::is_wo() const
{
    return !inst_props.access_r && inst_props.access_w;
}

bool AdbInstance::is_diff() const
{
    return inst_props.is_diff;
}

void AdbInstance::set_is_diff(bool val)
{
    inst_props.is_diff = val;
}

/**
 * Function: AdbInstance::fullName
 **/
u_int32_t AdbInstance::dwordAddr()
{
    return (offset >> 5) << 2;
}

/**
 * Function: AdbInstance::fullName
 **/
u_int32_t AdbInstance::startBit()
{
    return offset % 32;
}

/**
 * Function: AdbInstance::operator<
 **/
bool AdbInstance::operator<(const AdbInstance& other)
{
    return offset < other.offset;
}

/**
 * Function: AdbInstance::getChildByPath
 **/
AdbInstance* AdbInstance::getChildByPath(const string& path, bool isCaseSensitive)
{
    string effPath = isCaseSensitive ? path : boost::algorithm::to_lower_copy(path);
    if (effPath[0] == '.')
    {
        effPath.erase(0, 1);
    }

    size_t idx = effPath.find(".");
    string childName = idx == string::npos ? effPath : effPath.substr(0, idx);
    string grandChildPath = idx == string::npos ? string() : effPath.substr(idx + 1);

    if (path.empty())
    {
        return this;
    }

    // Search for childName
    AdbInstance* child = NULL;
    for (size_t i = 0; i < subItems.size(); i++)
    {
        string subName = isCaseSensitive ? subItems[i]->layout_item_name :
                                           boost::algorithm::to_lower_copy(subItems[i]->layout_item_name);
        if (subName == childName)
        {
            child = subItems[i];
            break;
        }
    }

    if (!child)
    {
        return NULL;
    }

    // if grandChildPath isn't empty this means we need to continue and find the desired field in grand child node
    return grandChildPath.empty() ? child : child->getChildByPath(grandChildPath, isCaseSensitive);
}

/**
 * Function: AdbInstance::findChild
 **/
vector<AdbInstance*> AdbInstance::findChild(const string& childName, bool isCaseSensitive, bool by_inst_name)
{
    string effName = isCaseSensitive ? childName : boost::algorithm::to_lower_copy(childName);
    vector<AdbInstance*> childList;

    if (by_inst_name || isLeaf())
    {
        if (layout_item_name == childName)
        {
            childList.push_back(this);
        }
    }
    else
    {
        if (isNode() && nodeDesc->name == childName)
        {
            childList.push_back(this);
        }
    }

    // do that recursively for all child items
    for (size_t i = 0; i < subItems.size(); i++)
    {
        vector<AdbInstance*> l = subItems[i]->findChild(effName, true);
        childList.insert(childList.end(), l.begin(), l.end());
    }

    return childList;
}

/**
 * Function: AdbInstance::getAttr
 **/
string AdbInstance::getInstanceAttr(const string& attrName) const
{
    if (inst_ops_props)
    {
        LayoutItemAttrsMap::iterator it = inst_ops_props->instAttrsMap.find(attrName);
        return it == inst_ops_props->instAttrsMap.end() ? string() : it->second;
    }
    else if (fieldDesc)
    {
        AttrsMap::iterator it = fieldDesc->attrs.find(attrName);
        return it == fieldDesc->attrs.end() ? string() : it->second;
    }
    else if (nodeDesc)
    {
        AttrsMap::iterator it = nodeDesc->attrs.find(attrName);
        return it == nodeDesc->attrs.end() ? string() : it->second;
    }
    return string();
}

/**
 * Function: AdbInstance::getAttr
 **/
bool AdbInstance::getInstanceAttr(const string& attrName,
                                  string& value) // TODO: solve this with templates or more general impl of iterator
{
    bool ret{false};
    if (inst_ops_props)
    {
        LayoutItemAttrsMap::iterator it = inst_ops_props->instAttrsMap.find(attrName);
        if (it != inst_ops_props->instAttrsMap.end())
        {
            value = it->second;
            ret = true;
        }
    }
    else if (fieldDesc)
    {
        AttrsMap::iterator it = fieldDesc->attrs.find(attrName);
        if (it != fieldDesc->attrs.end())
        {
            value = it->second;
            ret = true;
        }
    }
    else if (nodeDesc)
    {
        AttrsMap::iterator it = nodeDesc->attrs.find(attrName);
        if (it != nodeDesc->attrs.end())
        {
            value = it->second;
            ret = true;
        }
    }
    return ret;
}

/**
 * Function: AdbInstance::getInstanceAttrIterator
 **/
LayoutItemAttrsMap::iterator AdbInstance::getInstanceAttrIterator(const string& attrName)
{
    if (inst_ops_props)
    {
        return inst_ops_props->instAttrsMap.find(attrName);
    }
    else
    {
        throw AdbException("Getting Layout-Item attributes is illegal, when eval_expr is disabled");
    }
}

/**
 * Function: AdbInstance::setInstanceAttr
 **/
void AdbInstance::setInstanceAttr(const string& attrName, const string& attrValue)
{
    if (inst_ops_props)
    {
        inst_ops_props->instAttrsMap[attrName] = attrValue;
    }
    else
    {
        throw AdbException("Setting Layout-Item attributes is illegal, when eval_expr is disabled");
    }
}

/**
 * Function: AdbInstance::setVarsMap - set an item in vars map
 **/
void AdbInstance::setVarsMap(const string& attrName, const string& attrValue)
{
    if (inst_ops_props)
    {
        inst_ops_props->varsMap[attrName] = attrValue;
    }
    else
    {
        throw AdbException("Setting Layout-Item vars is illegal, when eval_expr is disabled");
    }
}

/**
 * Function: AdbInstance::setVarsMap - set an item in vars map
 **/
void AdbInstance::setVarsMap(const AttrsMap& AttrsMap)
{
    if (inst_ops_props)
    {
        inst_ops_props->varsMap = AttrsMap;
    }
    else
    {
        throw AdbException("Setting Layout-Item vars is illegal, when eval_expr is disabled");
    }
}

/**
 * Function: AdbInstance::setVarsMap - returns a copy of vars map
 **/
AttrsMap AdbInstance::getVarsMap()
{
    if (inst_ops_props)
    {
        return inst_ops_props->varsMap;
    }
    else
    {
        throw AdbException("Layout-Item vars are illegal, when eval_expr is disabled");
    }
}

/**
 * Function: AdbInstance::isEnumExists
 **/
bool AdbInstance::isEnumExists()
{
    return inst_ops_props ? inst_ops_props->instAttrsMap.contains("enum") : fieldDesc->attrs.count("enum");
}

/**
 * Function: AdbInstance::enumToInt
 **/
bool AdbInstance::enumToInt(const string& name, u_int64_t& val)
{
    string enums;
    bool enum_found = getInstanceAttr("enum", enums);

    if (!enum_found)
    {
        return false;
    }

    vector<string> enumValues;
    boost::algorithm::split(enumValues, enums, boost::is_any_of(string(",")));

    for (size_t i = 0; i < enumValues.size(); i++)
    {
        vector<string> pair;
        string trimedEnumValues = enumValues[i];
        boost::algorithm::trim(trimedEnumValues);
        boost::algorithm::split(pair, trimedEnumValues, boost::is_any_of(string("=")));

        if (pair.size() != 2)
        {
            continue;
        }

        char* end;
        if (pair[0] == name)
        {
            val = strtoul(pair[1].c_str(), &end, 0);
            if (*end != '\0')
            {
                return false;
            }
            return true;
        }
    }

    return false;
}

/**
 * Function: AdbInstance::intToEnum
 **/
bool AdbInstance::intToEnum(u_int64_t val, string& valName)
{
    string enums;
    bool enum_found = getInstanceAttr("enum", enums);

    if (!enum_found)
    {
        return false;
    }

    vector<string> enumValues;
    boost::algorithm::split(enumValues, enums, boost::is_any_of(string(",")));

    for (size_t i = 0; i < enumValues.size(); i++)
    {
        vector<string> pair;
        string trimedEnumValues = enumValues[i];
        boost::algorithm::trim(trimedEnumValues);
        boost::algorithm::split(pair, trimedEnumValues, boost::is_any_of(string("=")));

        if (pair.size() != 2)
        {
            continue;
        }

        char* end;
        u_int64_t tmp = strtoul(pair[1].c_str(), &end, 0);
        if (*end != '\0')
        {
            continue;
        }

        if (tmp == val)
        {
            valName = pair[0];
            return true;
        }
    }

    return false;
}

/**
 * Function: AdbInstance::getEnumMap
 **/
map<string, u_int64_t> AdbInstance::getEnumMap()
{
    map<string, u_int64_t> enumMap;
    string enums;

    bool enum_found = getInstanceAttr("enum", enums);

    if (!enum_found)
    {
        return enumMap;
    }

    vector<string> enumValues;
    boost::algorithm::split(enumValues, enums, boost::is_any_of(string(",")));

    for (size_t i = 0; i < enumValues.size(); i++)
    {
        vector<string> pair;
        string trimedEnumValues = enumValues[i];
        boost::algorithm::trim(trimedEnumValues);
        boost::algorithm::split(pair, trimedEnumValues, boost::is_any_of(string("=")));
        if (pair.size() != 2)
        {
            throw AdbException("Can't parse enum: " + enumValues[i]);
        }

        char* end;
        u_int64_t intVal = strtoul(pair[1].c_str(), &end, 0);
        if (*end != '\0')
        {
            throw AdbException(string("Can't evaluate enum (") + pair[0].c_str() + "): " + pair[1].c_str());
        }

        enumMap[pair[0]] = intVal;
    }

    return enumMap;
}

/**
 * Function: AdbInstance::getEnumValues
 **/
vector<u_int64_t> AdbInstance::getEnumValues()
{
    vector<u_int64_t> values;
    string enums;

    bool enum_found = getInstanceAttr("enum", enums);
    if (!enum_found)
    {
        return values;
    }

    vector<string> enumValues;
    boost::algorithm::split(enumValues, enums, boost::is_any_of(string(",")));

    for (size_t i = 0; i < enumValues.size(); i++)
    {
        vector<string> pair;
        string trimedEnumValues = enumValues[i];
        boost::algorithm::trim(trimedEnumValues);
        boost::algorithm::split(pair, trimedEnumValues, boost::is_any_of(string("=")));
        if (pair.size() != 2)
        {
            continue;
        }

        char* end;
        u_int64_t intVal = strtoul(pair[1].c_str(), &end, 0);
        if (*end != '\0')
        {
            continue;
        }

        values.push_back(intVal);
    }

    return values;
}

/**
 * Function: AdbInstance::getUnionSelectedNodeName
 **/
AdbInstance* AdbInstance::getUnionSelectedNodeName(const u_int64_t& selectorVal)
{
    if (!isUnion())
    {
        throw AdbException("This is not union node (%s), can't get selected node name", fullName().c_str());
    }

    if (!unionSelector)
    {
        throw AdbException("Can't find selector for union: " + layout_item_name);
    }

    map<string, u_int64_t> selectorValMap = unionSelector->getEnumMap();
    string sel_by;
    for (map<string, u_int64_t>::iterator it = selectorValMap.begin(); it != selectorValMap.end(); it++)
    {
        if (it->second == selectorVal)
        {
            const string& selectorEnum = it->first;
            // search for the sub instance with the "selected_by" attribute == selectorEnum
            for (size_t i = 0; i < subItems.size(); i++)
            {
                if (getInstanceAttr("selected_by", sel_by) && sel_by == selectorEnum)
                {
                    return subItems[i];
                }
            }
            throw AdbException("Found selector value (" + selectorEnum + ") is defined for selector field (" +
                               unionSelector->layout_item_name +
                               ") but no appropriate subfield of this union was found");
        }
    }

    throw AdbException("Union selector field (" + unionSelector->layout_item_name +
                       ") doesn't define selector value (" + to_string(selectorVal));
}

/**
 * Function: AdbInstance::getUnionSelectedNodeName
 **/
AdbInstance* AdbInstance::getUnionSelectedNodeName(const string& selectorEnum)
{
    if (!isUnion())
    {
        throw AdbException("This is not union node (%s), can't get selected node name", fullName().c_str());
    }

    if (!unionSelector)
    {
        throw AdbException("Can't find selector for union: " + fullName());
    }

    string sel_by;
    for (auto subItem : subItems)
    {
        if (subItem->getInstanceAttr("selected_by", sel_by) && sel_by == selectorEnum)
        {
            return subItem;
        }
    }

    throw AdbException("Union selector field (" + unionSelector->layout_item_name +
                       ") doesn't define a selector value (" + selectorEnum + ")");
}

/**
 * Function: AdbInstance::isConditionalNode
 * Throws exception: AdbException
 **/
bool AdbInstance::isConditionalNode()
{
    if (isNode())
    {
        string is_conditional;
        bool found = getInstanceAttr("is_conditional", is_conditional);
        return (found && is_conditional == "1");
    }
    return false;
}

/**
 * Function: AdbInstance::isConditionValid
 * Throws exception: AdbException
 **/
bool AdbInstance::isConditionValid(map<string, string>* valuesMap)
{
    u_int64_t res;
    AdbExpr expressionChecker;
    int status = -1;
    char* condExp;
    char* exp;

    if (fieldDesc->condition.empty())
    {
        return true;
    }

    condExp = new char[fieldDesc->condition.size() + 1];
    exp = condExp;
    if (!exp)
    {
        throw AdbException("Memory allocation error");
    }
    strcpy(exp, fieldDesc->condition.c_str());

    expressionChecker.setVars(valuesMap);
    try
    {
        status = expressionChecker.expr(&exp, &res);
    }
    catch (AdbException& e)
    {
        delete[] condExp;
        throw AdbException(string("AdbException: ") + e.what_s());
    }
    delete[] condExp;

    if (status < 0)
    {
        throw AdbException(string("Error evaluating expression \"") + fieldDesc->condition.c_str() +
                           "\" : " + AdbExpr::statusStr(status));
    }

    return (status >= 0 && res != 0);
}

/**
 * Function: AdbInstance::getLeafFields
 **/
vector<AdbInstance*> AdbInstance::getLeafFields(bool extendenName)
{
    vector<AdbInstance*> fields;

    for (size_t i = 0; i < subItems.size(); i++)
    {
        if (subItems[i]->isNode())
        {
            vector<AdbInstance*> subFields = subItems[i]->getLeafFields(extendenName);
            fields.insert(fields.end(), subFields.begin(), subFields.end());
        }
        else
        {
            if (extendenName && !subItems[i]->inst_props.is_name_extended)
            {
                if (subItems[i]->parent->fieldDesc->subNode == "uint64")
                {
                    subItems[i]->layout_item_name =
                      subItems[i]->parent->layout_item_name + "_" + subItems[i]->layout_item_name;
                }
                else
                {
                    subItems[i]->layout_item_name += addPathSuffixForArraySupport(subItems[i]->fullName());
                }
                subItems[i]->inst_props.is_name_extended = true;
            }
            fields.push_back(subItems[i]);
        }
    }

    return fields;
}

/**
 * Function: AdbInstance::pushBuf
 **/
void AdbInstance::pushBuf(u_int8_t* buf, u_int64_t value)
{
    push_to_buf(buf, offset, size, value);
}

/**
 * Function: AdbInstance::popBuf
 **/
u_int64_t AdbInstance::popBuf(u_int8_t* buf)
{
    return pop_from_buf(buf, offset, size);
}

/**
 * Function: AdbInstance::print
 **/
void AdbInstance::print(int indent)
{
    string indentStr = indentString(indent);
    printf("%sfullName: %s, offset: 0x%x.%d, size: 0x%x.%d, isNode:%d, isUnion:%d\n", indentStr.c_str(),
           fullName().c_str(), (offset >> 5) << 2, offset % 32, (size >> 5) << 2, size % 32, isNode(), isUnion());

    if (isNode())
    {
        for (size_t i = 0; i < subItems.size(); i++)
            subItems[i]->print(indent + 1);
    }
}

AdbInstance::InstOpsProperties::InstOpsProperties(AttrsMap& field_attrs) : instAttrsMap(field_attrs) {}

LayoutItemAttrsMap::LayoutItemAttrsMap(AttrsMap& field_desc_attrs) : _field_desc_attrs(field_desc_attrs) {}

LayoutItemAttrsMap& LayoutItemAttrsMap::operator=(const LayoutItemAttrsMap& other)
{
    _layout_specific_attrs = other._layout_specific_attrs;
    _field_desc_attrs = other._layout_specific_attrs;

    return *this;
}

LayoutItemAttrsMap::iterator LayoutItemAttrsMap::find(const string& key)
{
    auto attr_it = _layout_specific_attrs.find(key);
    bool past_layout_specific = attr_it == _layout_specific_attrs.end();
    if (past_layout_specific)
    {
        attr_it = _field_desc_attrs.find(key);
    }
    return iterator(*this, attr_it, past_layout_specific);
}

bool LayoutItemAttrsMap::contains(const string& key)
{
    return find(key) != end();
}

string& LayoutItemAttrsMap::operator[](const string& key)
{
    auto attr_value_it = _layout_specific_attrs.find(key);
    if (attr_value_it == _layout_specific_attrs.end())
    {
        attr_value_it = _field_desc_attrs.find(key);
        if (attr_value_it != _field_desc_attrs.end())
        {
            _overriden.insert(key);
            return _layout_specific_attrs[key] = attr_value_it->second;
        }
    }
    return _layout_specific_attrs[key];
}

LayoutItemAttrsMap::iterator LayoutItemAttrsMap::begin()
{
    return iterator(*this, _layout_specific_attrs.begin(),
                    _layout_specific_attrs.begin() == _layout_specific_attrs.end());
}

LayoutItemAttrsMap::iterator& LayoutItemAttrsMap::end() // TODO: implement static end
{
    return _end;
}

LayoutItemAttrsMap::iterator::iterator(LayoutItemAttrsMap& container,
                                       AttrsMap::iterator current,
                                       bool past_layout_specific) :
    _container(&container),
    _current{current != container._layout_specific_attrs.end() ? current : container._field_desc_attrs.begin()},
    _layout_specific_end{past_layout_specific}
{
}

LayoutItemAttrsMap::iterator::reference LayoutItemAttrsMap::iterator::operator*() const
{
    return (reference)(*_current);
}

LayoutItemAttrsMap::iterator::pointer LayoutItemAttrsMap::iterator::operator->()
{
    return (pointer)(&(*_current));
}

void LayoutItemAttrsMap::iterator::advance_internal()
{
    ++_current;
    if (!_layout_specific_end && _current == _container->_layout_specific_attrs.end())
    {
        _layout_specific_end = true;
        _current = _container->_field_desc_attrs.begin();
    }
    if (_layout_specific_end)
    {
        while (_current != _container->_field_desc_attrs.end() && _container->_overriden.count(_current->first))
        {
            ++_current;
        }
    }
}

void LayoutItemAttrsMap::iterator::regress_internal()
{
    if (_layout_specific_end && _current == _container->_field_desc_attrs.begin())
    {
        _layout_specific_end = false;
        _current = _container->_layout_specific_attrs.end();
    }
    --_current;

    if (_layout_specific_end)
    {
        while (_container->_overriden.count(_current->first))
        {
            if (_current != _container->_field_desc_attrs.begin())
            {
                --_current;
            }
            else
            {
                _layout_specific_end = false;
                _current = _container->_layout_specific_attrs.end();
                --_current;
                break;
            }
        }
    }
}

LayoutItemAttrsMap::iterator& LayoutItemAttrsMap::iterator::operator++()
{
    advance_internal();
    return *this;
}

LayoutItemAttrsMap::iterator LayoutItemAttrsMap::iterator::operator++(int)
{
    iterator tmp = *this; // TODO: make sure that the copy ctor is sufficient for this
    advance_internal();
    return tmp;
}

LayoutItemAttrsMap::iterator& LayoutItemAttrsMap::iterator::operator--()
{
    regress_internal();
    return *this;
}

LayoutItemAttrsMap::iterator LayoutItemAttrsMap::iterator::operator--(int)
{
    iterator tmp = *this; // TODO: make sure that the copy ctor is sufficient for this
    regress_internal();
    return tmp;
}

bool LayoutItemAttrsMap::iterator::operator==(const iterator& rhs) const
{
    return _current == rhs._current;
}

bool LayoutItemAttrsMap::iterator::operator!=(const iterator& rhs) const
{
    return _current != rhs._current;
}
