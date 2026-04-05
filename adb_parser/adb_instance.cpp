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

/*************************** _AdbInstance_impl ***************************/
/**
 * Function: _AdbInstance_impl::_AdbInstance_impl
 **/

#include "adb_instance.h"
#include "adb_node.h"
#include "adb_field.h"
#include "adb_expr.h"
#include "adb_exceptionHolder.h"
#include "buf_ops.h"
#include <string>
#include <list>
#include <algorithm>
#include <iostream>
#include "common/tools_regex.h"
#include "common/tools_algorithm.h"

namespace Regex = mstflint::common::regex;
namespace Algorithm = mstflint::common::algorithm;

template<bool e, typename T_OFFSET>
_AdbInstance_impl<e, T_OFFSET>::_AdbInstance_impl(AdbField* i_fieldDesc,
                                                  AdbNode* i_nodeDesc,
                                                  uint32_t i_arrIdx,
                                                  _AdbInstance_impl<e, T_OFFSET>* i_parent,
                                                  map<string, string> vars,
                                                  bool bigEndianArr,
                                                  unsigned char adabe_version,
                                                  bool optimize_time,
                                                  bool stop_on_partition,
                                                  PartitionTree* next_partition_tree,
                                                  bool path_array_wildcards) :
    fieldDesc(i_fieldDesc), nodeDesc(i_nodeDesc), parent(i_parent), arrIdx(i_arrIdx), offset(calcArrOffset(bigEndianArr))
{
    // Re-initializations due to packing efficiency
    string array_name_suffix{fieldDesc->isArray() ? "[" + to_string(arrIdx + fieldDesc->lowBound) + "]" : ""};
    layout_item_name = i_fieldDesc->name + array_name_suffix;
    if (optimize_time)
    {
        if (fieldDesc->isArray() && path_array_wildcards)
        {
            array_name_suffix = "[*]";
        }
        full_path = parent ? parent->full_path + "." + i_fieldDesc->name + array_name_suffix :
                             i_fieldDesc->name + array_name_suffix;
    }

    // TODO: the whole block below looks unnecesarry
    if (fieldDesc->offset == static_cast<T_OFFSET>(-1))
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

    if (stop_on_partition)
    {
        partition_props = new LayoutPartitionProps(next_partition_tree);
    }

    if (!stop_on_partition)
    {
        init_props(adabe_version);

        initInstOps();
        eval_expressions(vars);
    }
}

// template<bool eval_expr, typename O>
// template<bool U>
// typename enable_if<U>::type
// _AdbInstance_impl<eval_expr, O>::initInstOps()
// {
//     string value;
//     auto found = getInstanceAttr("condition", value);
//     if (found && parent->getInstanceAttr("is_conditional") == "1")
//     {
//         inst_ops_props.condition.setCondition(value);
//     }

//     found = getInstanceAttr("size_condition", value);
//     if (found)
//     {
//         string cond_size = value;
//         if (cond_size.substr(0, 10) == "$(parent).")
//         {
//             cond_size.erase(0, 10);
//         }
//         inst_ops_props.conditionalSize.setCondition(cond_size);
//     }
// }

// template<bool eval_expr, typename O>
// template<bool U>
// typename enable_if<!U>::type
// _AdbInstance_impl<eval_expr, O>::initInstOps()
// {
//     return;
// }

template<bool e, typename T_OFFSET>
T_OFFSET _AdbInstance_impl<e, T_OFFSET>::calcArrOffset(bool bigEndianArr, uint8_t align)
{
    T_OFFSET element_offset;
    T_OFFSET parent_offset = parent ? parent->offset : 0;
    if (fieldDesc->eSize() >= 32)
    {
        // Make sure this is dword aligned
        if (fieldDesc->eSize() % 32 || parent_offset % 32 || fieldDesc->offset % 32)
        {
            throw AdbException("Field " + fieldDesc->name + " isn't dword aligned");
        }
    }

    if (fieldDesc->eSize() >= 32 || !bigEndianArr || fieldDesc->array_type == AdbField::ArrayType::none ||
        fieldDesc->array_type == AdbField::ArrayType::single_entry)
    {
        element_offset = parent_offset + fieldDesc->offset + fieldDesc->eSize() * arrIdx;
    }
    else // be arrays, small elements
    {
        T_OFFSET array_offset = parent_offset + fieldDesc->offset;
        T_OFFSET element_size = fieldDesc->eSize();
        T_OFFSET array_dword_offset = array_offset / align * align;
        T_OFFSET element_dword_offset =
          (align - array_offset % align + ((T_OFFSET)arrIdx - 1) * element_size) / align * align;
        T_OFFSET element_bit_offset = (array_offset + (align - (T_OFFSET)arrIdx * element_size) % align) % align;

        element_offset = array_dword_offset + element_dword_offset + element_bit_offset;
    }
    return element_offset;
}

template<bool e, typename O>
bool _AdbInstance_impl<e, O>::stop_on_partition() const
{
    return partition_props != nullptr;
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<U>::type _AdbInstance_impl<eval_expr, O>::eval_expressions(AttrsMap& parent_vars)
{
    static Regex::regex EXP_REGEX(EXP_PATTERN);
    try
    {
        // First add the special variables
        parent_vars["NAME"] = layout_item_name;
        parent_vars["ARR_IDX"] = to_string(arrIdx);
        parent_vars["BN"] = "[" + to_string(offset % 32 + get_size() - 1) + ":" + to_string(offset % 32) + "]";
        parent_vars["parent"] = "#(parent)"; // special internal name

        // Get variables attribute value
        AttrsMap::iterator it = fieldDesc->attrs.find("variables");

        // build var_name->value map from varAttrStr
        if (it != fieldDesc->attrs.end())
        {
            string& varStr = it->second;
            Algorithm::trim(varStr);
            Regex::match_results<string::const_iterator> what;
            string::const_iterator start = varStr.begin();
            string::const_iterator end = varStr.end();

            string var;
            string exp;

            while (Regex::regex_search(start, end, what, EXP_REGEX))
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
            setInstanceAttr(attr.first, evalExpr(attr.second, &parent_vars));
        }
        inst_ops_props.varsMap = parent_vars;
    }
    catch (AdbException& exp)
    {
        string exceptionTxt = "Failed to evaluate expression for field (" + fullName() + "): " + exp.what_s();
        throw AdbException(exceptionTxt);
    }
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<!U>::type _AdbInstance_impl<eval_expr, O>::eval_expressions(AttrsMap& parent_vars)
{
    (void)parent_vars;
    return;
}

template<bool e, typename O>
string _AdbInstance_impl<e, O>::evalExpr(string expr, AttrsMap* vars)
{
    if (expr.find('$') == string::npos)
    {
        return expr;
    }

    Regex::smatch what, what2;
    static Regex::regex singleExpr("^([^\\$]*)(\\$\\(([^)]+)\\))(.*)$");
    while (Regex::regex_search(expr, what, singleExpr))
    {
        string vname = what[3].str();
        string vvalue;
        static Regex::regex singleVar("^[a-zA-Z_][a-zA-Z0-9_]*$");

        // Need to change to array-like initialization when we'll move to c++11
        vector<string> specialVars;
        specialVars.push_back("NAME");
        specialVars.push_back("ARR_IDX");
        specialVars.push_back("BN");
        specialVars.push_back("parent");

        if (Regex::regex_search(vname, what2, singleVar))
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
            static Regex::regex singleVarInExpr("[a-zA-Z_][a-zA-Z0-9_]*");
            Regex::smatch matches;
            while (Regex::regex_search(vnameCopy, matches, singleVarInExpr))
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
            uint64_t res;
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
 * Function: _AdbInstance_impl::addPathSuffixForArraySupport
 **/
template<bool e, typename O>
string _AdbInstance_impl<e, O>::addPathSuffixForArraySupport(string path)
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

/**
 * Function: _AdbInstance_impl::_AdbInstance_impl
 **/
template<bool e, typename O>
_AdbInstance_impl<e, O>::~_AdbInstance_impl()
{
    for (size_t i = 0; i < subItems.size(); i++)
    {
        delete subItems[i];
    }

    if (inst_ops_props.instAttrsMap)
    {
        delete inst_ops_props.instAttrsMap;
    }

    if (partition_props)
    {
        delete partition_props;
    }
}

/**
 * Function: _AdbInstance_impl::get_field_name
 **/
template<bool e, typename O>
const string& _AdbInstance_impl<e, O>::get_field_name()
{
    return layout_item_name;
}

/**
 * Function: _AdbInstance_impl::get_size
 **/
template<bool e, typename T_OFFSET>
T_OFFSET _AdbInstance_impl<e, T_OFFSET>::get_size() const
{
    return fieldDesc ? fieldDesc->eSize() : nodeDesc ? nodeDesc->get_size() : 0;
}

/**
 * Function: _AdbInstance_impl::get_max_leaf_size
 **/
template<bool e, typename T_OFFSET>
T_OFFSET _AdbInstance_impl<e, T_OFFSET>::get_max_leaf_size() const
{
    return _max_leaf ? _max_leaf->get_size() : 0;
}

/**
 * Function: _AdbInstance_impl::get_max_leaf_size
 **/
template<bool e, typename O>
void _AdbInstance_impl<e, O>::update_max_leaf()
{
    uint64_t esize = fieldDesc ? fieldDesc->get_size() : 0;
    if ((fieldDesc->isLeaf() || fieldDesc->subNode == "uint64") && (esize == 16 || esize == 32 || esize == 64)) // A
                                                                                                                // leaf
    {
        _max_leaf = fieldDesc;
    }
    if (parent)
    {
        if (_max_leaf && _max_leaf->get_size() > parent->get_max_leaf_size())
        {
            parent->_max_leaf = _max_leaf;
        }
    }
}

/**
 * Function: _AdbInstance_impl::isLeaf
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::isLeaf()
{
    return nodeDesc == NULL;
}

/**
 * Function: isUnionisUnion
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::isUnion()
{
    return isNode() && nodeDesc->isUnion;
}

/**
 * Function: _AdbInstance_impl::isStruct
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::isStruct()
{
    return isNode() && !isUnion();
}

/**
 * Function: _AdbInstance_impl::isNode
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::isNode()
{
    return !isLeaf();
}

/**
 * Function: _AdbInstance_impl::isNode
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::isPartOfArray()
{
    return fieldDesc->isArray();
}

/**
 * Function: _AdbInstance_impl::fullName
 **/
template<bool e, typename O>
string _AdbInstance_impl<e, O>::fullName(size_t skipLevel)
{
    if (!full_path.empty())
    {
        if (skipLevel == 0)
        {
            return full_path;
        }
        else
        {
            size_t pos = 0;
            for (size_t i = 0; i < skipLevel; ++i)
            {
                pos = full_path.find('.', pos);
                if (pos == std::string::npos)
                {
                    return "";
                }
                ++pos;
            }
            return full_path.substr(pos);
        }
    }
    list<string> fnList;
    _AdbInstance_impl<e, O>* p = parent;

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

        return Algorithm::join(fnList, ".");
    }
    else
    {
        return fnList.back();
    }
}

template<bool e, typename O>
void _AdbInstance_impl<e, O>::init_props(unsigned char adabe_version) // logic of this function is copied from devmon
                                                                      // and it's bugous
{
    if (!fieldDesc)
    {
        return;
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
            if (!parent->inst_props.access_w)
            {
                inst_props.access_w = 0;
            }
            if (!parent->inst_props.access_r)
            {
                inst_props.access_r = 0;
            }
            if (parent->inst_props.is_semaphore)
            {
                inst_props.is_semaphore = 1;
            }
            if (parent->inst_props.is_index)
            {
                inst_props.is_index = 1;
            }
            if (parent->inst_props.is_op)
            {
                inst_props.is_op = 1;
            }
        }
    }

    if (isPartOfArray())
    {
        string fiVal = getInstanceAttr("valid_first_index");
        string strideVal = getInstanceAttr("valid_stride");

        if (!fiVal.empty() && !strideVal.empty())
        {
            uint32_t fi = stoul(fiVal);
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
        if (access_type.empty())
        {
            access_type = getInstanceAttr("access");
        }
        if (!sem.empty())
        {
            inst_props.is_semaphore = stoi(sem) > 0;
        }
        if (access_type == "WO")
        {
            inst_props.is_index = 0;
            inst_props.is_op = 0;
            inst_props.access_r = 0;
            inst_props.access_w = 1;
        }
        else if (access_type == "RO")
        {
            inst_props.is_index = 0;
            inst_props.is_op = 0;
            inst_props.access_w = 0;
            inst_props.access_r = 1;
        }
        else if (access_type == "RW")
        {
            inst_props.is_index = 0;
            inst_props.is_op = 0;
            inst_props.access_r = 1;
            inst_props.access_w = 1;
        }
        else if (access_type == "INDEX")
        {
            inst_props.access_r = 1;
            inst_props.access_w = 1;
            inst_props.is_index = 1;
        }
        else if (access_type == "OP")
        {
            inst_props.access_r = 1;
            inst_props.access_w = 1;
            inst_props.is_op = 1;
        }
    }

    sem = getInstanceAttr("gw");
    if (!sem.empty())
    {
        inst_props.is_semaphore = stoi(sem) > 0;
    }
}

/**
 * Function: _AdbInstance_impl::fullName
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::isReserved()
{
    return fieldDesc->isReserved;
}

template<bool e, typename O>
bool _AdbInstance_impl<e, O>::is_valid_array_index() const
{
    return inst_props.valid_array_index;
}

template<bool e, typename O>
bool _AdbInstance_impl<e, O>::is_semaphore() const
{
    return inst_props.is_semaphore;
}

template<bool e, typename O>
bool _AdbInstance_impl<e, O>::is_ro() const
{
    return inst_props.access_r && !inst_props.access_w;
}

template<bool e, typename O>
bool _AdbInstance_impl<e, O>::is_wo() const
{
    return !inst_props.access_r && inst_props.access_w;
}

template<bool e, typename O>
bool _AdbInstance_impl<e, O>::is_index() const
{
    return inst_props.is_index;
}

template<bool e, typename O>
bool _AdbInstance_impl<e, O>::is_op() const
{
    return inst_props.is_op;
}

template<bool e, typename O>
bool _AdbInstance_impl<e, O>::is_diff() const
{
    return inst_props.is_diff;
}

template<bool e, typename O>
void _AdbInstance_impl<e, O>::set_is_diff(bool val)
{
    inst_props.is_diff = val;
}

/**
 * Function: _AdbInstance_impl::dwordAddr
 **/
template<bool e, typename T_OFFSET>
T_OFFSET _AdbInstance_impl<e, T_OFFSET>::dwordAddr(uint8_t alignment)
{
    return (offset / alignment) << 2;
}

/**
 * Function: _AdbInstance_impl::startBit
 **/
template<bool e, typename O>
uint32_t _AdbInstance_impl<e, O>::startBit(uint8_t alignment)
{
    return offset % alignment;
}

/**
 * Function: _AdbInstance_impl::operator<
 **/
template<bool e, typename T_OFFSET>
bool _AdbInstance_impl<e, T_OFFSET>::operator<(const _AdbInstance_impl<e, T_OFFSET>& other)
{
    return offset < other.offset;
}

/**
 * Function: _AdbInstance_impl::getChildByPath
 **/
template<bool e, typename O>
_AdbInstance_impl<e, O>* _AdbInstance_impl<e, O>::getChildByPath(const string& path, bool isCaseSensitive)
{
    string effPath = isCaseSensitive ? path : Algorithm::to_lower_copy(path);

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
    _AdbInstance_impl<e, O>* child = NULL;
    for (size_t i = 0; i < subItems.size(); i++)
    {
        string subName =
          isCaseSensitive ? subItems[i]->layout_item_name : Algorithm::to_lower_copy(subItems[i]->layout_item_name);
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
 * Function: _AdbInstance_impl::findChild
 **/
template<bool e, typename O>
vector<_AdbInstance_impl<e, O>*>
  _AdbInstance_impl<e, O>::findChild(const string& childName, bool isCaseSensitive, bool by_inst_name)
{
    string effName = isCaseSensitive ? childName : Algorithm::to_lower_copy(childName);
    vector<_AdbInstance_impl<e, O>*> childList;

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
        vector<_AdbInstance_impl<e, O>*> l = subItems[i]->findChild(effName, true);
        childList.insert(childList.end(), l.begin(), l.end());
    }

    return childList;
}

/**
 * Function: _AdbInstance_impl::get_root
 **/
template<bool e, typename O>
_AdbInstance_impl<e, O>* _AdbInstance_impl<e, O>::get_root()
{
    auto current_layout_item = this;
    while (current_layout_item->parent)
    {
        current_layout_item = current_layout_item->parent;
    }
    return current_layout_item;
}

/**
 * Function: _AdbInstance_impl::get_layout_item_by_path
 **/
template<bool e, typename T_OFFSET>
_AdbInstance_impl<e, T_OFFSET>* _AdbInstance_impl<e, T_OFFSET>::get_layout_item_by_path(const std::string& path)
{
    size_t separator_index = path.find(".");
    _AdbInstance_impl<e, T_OFFSET>* root_item = nullptr;

    // If There's a parent or segment prefix search path according to the prefix
    if (separator_index != std::string::npos)
    {
        std::string prefix = path.substr(0, separator_index);
        // Parent prefix list: "#(parent)", "$(parent)"
        if (prefix == "#(parent)" || prefix == "$(parent)")
        {
            root_item = this->parent;
            if (root_item && root_item->isUnion())
            {
                root_item = root_item->parent;
            }
            return root_item ? root_item->getChildByPath(path.substr(separator_index + 1)) : nullptr;
        }
        // Segment prefix: "$(segment)" todo: implement get_segment
        // else if (prefix == "$(segment)")
        // {
        //     root_item = this->get_segment();
        //     return root_item ? root_item->getChildByPath(path.substr(separator_index + 1)) : nullptr;
        // }
    }

    // If no relevant prefix
    else
    {
        root_item = this->parent;
        if (!root_item)
        {
            return nullptr;
        }

        // Try searching from parent
        _AdbInstance_impl<e, T_OFFSET>* found_item = root_item->getChildByPath(path);
        if (found_item)
        {
            return found_item;
        }

        // Try searching from segment root
        root_item = this->get_root();
        found_item = root_item->getChildByPath(path);
        if (found_item)
        {
            return found_item;
        }

        // Finally, try searching by DFS from segment root
        return root_item->find_layout_item_dfs(path);
    }

    return nullptr;
}

/**
 * Function: _AdbInstance_impl::_find_layout_item_dfs
 **/
template<bool e, typename T_OFFSET>
_AdbInstance_impl<e, T_OFFSET>* _AdbInstance_impl<e, T_OFFSET>::find_layout_item_dfs(const std::string& path)
{
    // Use a stack for DFS (equivalent to Python's deque)
    std::vector<_AdbInstance_impl<e, T_OFFSET>*> dfs_stack;

    // Add all subItems in reverse order to stack (equivalent to reversed(this->subItems))
    for (int i = this->subItems.size() - 1; i >= 0; --i)
    {
        dfs_stack.push_back(this->subItems[i]);
    }

    while (!dfs_stack.empty())
    {
        _AdbInstance_impl<e, T_OFFSET>* current_item = dfs_stack.back();
        dfs_stack.pop_back();

        _AdbInstance_impl<e, T_OFFSET>* found_item = current_item->getChildByPath(path);
        if (found_item)
        {
            return found_item;
        }

        // Add all subItems in reverse order to stack
        for (int i = current_item->subItems.size() - 1; i >= 0; --i)
        {
            dfs_stack.push_back(current_item->subItems[i]);
        }
    }

    return nullptr;
}

/**
 * Function: _AdbInstance_impl::getAttr
 **/
template<bool e, typename O>
string _AdbInstance_impl<e, O>::getInstanceAttr(const string& attrName) const
{
    if (inst_ops_props.instAttrsMap)
    {
        LayoutItemAttrsMap::iterator it = inst_ops_props.instAttrsMap->find(attrName);
        return it == inst_ops_props.instAttrsMap->end() ? string() : it->second;
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
 * Function: _AdbInstance_impl::getAttr
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::getInstanceAttr(const string& attrName,
                                              string& value) // TODO: solve this with templates or more general impl of
                                                             // iterator
{
    bool ret{false};
    if (inst_ops_props.instAttrsMap)
    {
        LayoutItemAttrsMap::iterator it = inst_ops_props.instAttrsMap->find(attrName);
        if (it != inst_ops_props.instAttrsMap->end())
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
 * Function: _AdbInstance_impl::getInstanceAttrIterator
 **/
template<bool e, typename O>
LayoutItemAttrsMap::iterator _AdbInstance_impl<e, O>::getInstanceAttrIterator(const string& attrName)
{
    if (inst_ops_props.instAttrsMap)
    {
        return inst_ops_props.instAttrsMap->find(attrName);
    }
    else
    {
        throw AdbException("Getting Layout-Item attributes is illegal, when eval_expr is disabled");
    }
}

/**
 * Function: _AdbInstance_impl::setInstanceAttr
 **/
template<bool e, typename O>
void _AdbInstance_impl<e, O>::setInstanceAttr(const string& attrName, const string& attrValue)
{
    if (!inst_ops_props.instAttrsMap)
    {
        AttrsMap& attrs_map = !parent ? nodeDesc->attrs : fieldDesc->attrs;
        inst_ops_props.instAttrsMap = new LayoutItemAttrsMap(attrs_map);
    }

    (*(inst_ops_props.instAttrsMap))[attrName] = attrValue;
}

/**
 * Function: _AdbInstance_impl::setVarsMap - set an item in vars map
 **/
template<bool eval_expr, typename O>
template<bool U>
typename enable_if<U>::type _AdbInstance_impl<eval_expr, O>::setVarsMap(const string& attrName, const string& attrValue)
{
    inst_ops_props.varsMap[attrName] = attrValue;
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<!U>::type _AdbInstance_impl<eval_expr, O>::setVarsMap(const string& attrName,
                                                                         const string& attrValue)
{
    (void)attrName;
    (void)attrValue;
    return;
}

/**
 * Function: _AdbInstance_impl::setVarsMap - set an item in vars map
 **/
template<bool eval_expr, typename O>
template<bool U>
typename enable_if<U>::type _AdbInstance_impl<eval_expr, O>::setVarsMap(const AttrsMap& AttrsMap)
{
    inst_ops_props.varsMap = AttrsMap;
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<!U>::type _AdbInstance_impl<eval_expr, O>::setVarsMap(const AttrsMap& AttrsMap)
{
    (void)AttrsMap;
    return;
}

// /**
//  * Function: _AdbInstance_impl::setVarsMap - returns a copy of vars map
//  **/
template<bool eval_expr, typename O>
template<bool U>
typename enable_if<U, AttrsMap>::type _AdbInstance_impl<eval_expr, O>::getVarsMap()
{
    return inst_ops_props.varsMap;
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<!U, AttrsMap>::type _AdbInstance_impl<eval_expr, O>::getVarsMap()
{
    return AttrsMap();
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<U, _AdbCondition_impl<O>*>::type _AdbInstance_impl<eval_expr, O>::getCondition()
{
    return inst_ops_props.condition.get_condition().empty() ? nullptr : &(inst_ops_props.condition);
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<!U, _AdbCondition_impl<O>*>::type _AdbInstance_impl<eval_expr, O>::getCondition()
{
    return nullptr;
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<U, _AdbCondition_impl<O>*>::type _AdbInstance_impl<eval_expr, O>::getArraySizeCondition()
{
    return inst_ops_props.conditionalSize.get_condition().empty() ? nullptr : &(inst_ops_props.conditionalSize);
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<!U, _AdbCondition_impl<O>*>::type _AdbInstance_impl<eval_expr, O>::getArraySizeCondition()
{
    return nullptr;
}

/**
 * Function: _AdbInstance_impl::isEnumExists
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::isEnumExists()
{
    return inst_ops_props.instAttrsMap ? inst_ops_props.instAttrsMap->contains("enum") :
           fieldDesc                   ? fieldDesc->attrs.count("enum") :
                                         false;
}

/**
 * Function: _AdbInstance_impl::enumToInt
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::enumToInt(const string& name, uint64_t& val)
{
    string enums;
    bool enum_found = getInstanceAttr("enum", enums);

    if (!enum_found)
    {
        return false;
    }

    vector<string> enumValues;
    Algorithm::split(enumValues, enums, Algorithm::is_any_of(","));

    for (size_t i = 0; i < enumValues.size(); i++)
    {
        vector<string> pair;
        string trimedEnumValues = enumValues[i];
        Algorithm::trim(trimedEnumValues);
        Algorithm::split(pair, trimedEnumValues, Algorithm::is_any_of("="));

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
 * Function: _AdbInstance_impl::intToEnum
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::intToEnum(uint64_t val, string& valName)
{
    string enums;
    bool enum_found = getInstanceAttr("enum", enums);

    if (!enum_found)
    {
        return false;
    }

    vector<string> enumValues;
    Algorithm::split(enumValues, enums, Algorithm::is_any_of(","));

    for (size_t i = 0; i < enumValues.size(); i++)
    {
        vector<string> pair;
        string trimedEnumValues = enumValues[i];
        Algorithm::trim(trimedEnumValues);
        Algorithm::split(pair, trimedEnumValues, Algorithm::is_any_of("="));

        if (pair.size() != 2)
        {
            continue;
        }

        char* end;
        uint64_t tmp = strtoul(pair[1].c_str(), &end, 0);
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
 * Function: _AdbInstance_impl::getEnumMap
 **/
template<bool e, typename O>
map<string, uint64_t> _AdbInstance_impl<e, O>::getEnumMap()
{
    map<string, uint64_t> enumMap;
    string enums;

    bool enum_found = getInstanceAttr("enum", enums);

    if (!enum_found)
    {
        return enumMap;
    }

    vector<string> enumValues;
    Algorithm::split(enumValues, enums, Algorithm::is_any_of(","));

    for (size_t i = 0; i < enumValues.size(); i++)
    {
        vector<string> pair;
        string trimedEnumValues = enumValues[i];
        Algorithm::trim(trimedEnumValues);
        Algorithm::split(pair, trimedEnumValues, Algorithm::is_any_of("="));
        if (pair.size() != 2)
        {
            continue;
            // (1)
            // throw AdbException("Can't parse enum: " + enums);
        }

        if (pair[0].empty())
        {
            continue;
            // (1)
            // throw AdbException("Can't parse enum: " + enums + ", " + enumValues[i] + ", empty key");
        }
        char* end;
        uint64_t intVal = strtoul(pair[1].c_str(), &end, 0);
        if (*end != '\0')
        {
            continue;
            // (1)
            // throw AdbException(string("Can't evaluate enum (") + pair[0].c_str() + "): " + pair[1].c_str());
        }

        enumMap[pair[0]] = intVal;
    }

    return enumMap;
}

/**
 * Function: _AdbInstance_impl::getEnumValues
 **/
template<bool e, typename O>
vector<uint64_t> _AdbInstance_impl<e, O>::getEnumValues()
{
    vector<uint64_t> values;
    string enums;

    bool enum_found = getInstanceAttr("enum", enums);
    if (!enum_found)
    {
        return values;
    }

    vector<string> enumValues;
    Algorithm::split(enumValues, enums, Algorithm::is_any_of(","));

    for (size_t i = 0; i < enumValues.size(); i++)
    {
        vector<string> pair;
        string trimedEnumValues = enumValues[i];
        Algorithm::trim(trimedEnumValues);
        Algorithm::split(pair, trimedEnumValues, Algorithm::is_any_of("="));
        if (pair.size() != 2)
        {
            continue;
        }

        char* end;
        uint64_t intVal = strtoul(pair[1].c_str(), &end, 0);
        if (*end != '\0')
        {
            continue;
        }

        values.push_back(intVal);
    }

    return values;
}

/**
 * Function: _AdbInstance_impl::getUnionSelectedNodeName
 **/
template<bool e, typename O>
_AdbInstance_impl<e, O>* _AdbInstance_impl<e, O>::getUnionSelectedNodeName(const uint64_t& selectorVal)
{
    if (!isUnion())
    {
        throw AdbException("This is not union node (%s), can't get selected node name", fullName().c_str());
    }

    if (!unionSelector)
    {
        throw AdbException("Can't find selector for union: " + layout_item_name);
    }

    map<string, uint64_t> selectorValMap = unionSelector->getEnumMap();
    for (map<string, uint64_t>::iterator it = selectorValMap.begin(); it != selectorValMap.end(); it++)
    {
        if (it->second == selectorVal)
        {
            const string& selectorEnum = it->first;
            // search for the sub instance with the "selected_by" attribute == selectorEnum
            string sel_by;
            for (auto subItem : subItems)
            {
                if (subItem->getInstanceAttr("selected_by", sel_by) && sel_by == selectorEnum)
                {
                    return subItem;
                }
            }
            throw AdbException("Found selector value (" + selectorEnum + ") is defined for selector field (" +
                               unionSelector->layout_item_name +
                               ") but no appropriate subfield of this union was found");
        }
    }

    throw AdbException("Union selector field (" + unionSelector->layout_item_name +
                       ") doesn't define selector value (" + to_string(selectorVal) + ")");
}

/**
 * Function: _AdbInstance_impl::getUnionSelectedNodeName
 **/
template<bool e, typename O>
_AdbInstance_impl<e, O>* _AdbInstance_impl<e, O>::getUnionSelectedNodeName(const string& selectorEnum)
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
 * Function: _AdbInstance_impl::isConditionalNode
 * Throws exception: AdbException
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::isConditionalNode()
{
    if (isNode())
    {
        string is_conditional;
        bool found = getInstanceAttr("is_conditional", is_conditional);
        if (!found)
        {
            const auto& it = nodeDesc->attrs.find("is_conditional");
            if (it != nodeDesc->attrs.end())
            {
                is_conditional = it->second;
                found = true;
            }
        }
        return (found && is_conditional == "1");
    }
    return false;
}

/**
 * Function: _AdbInstance_impl::containsDynamicArray
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::containsDynamicArray()
{
    if (!isNode())
    {
        return false;
    }

    _AdbInstance_impl<e, O>* last = nullptr;
    last = subItems.back();
    while (last)
    {
        if (last->fieldDesc->array_type >= AdbField_impl<O>::ArrayType::unlimited)
        {
            return true;
        }
        last = last->isNode() && last->subItems.size() > 0 ? last->subItems.back() : nullptr;
    }
    return false;
}

/**
 * Function: _AdbInstance_impl::isConditionValid
 * Throws exception: AdbException
 **/
template<bool e, typename O>
bool _AdbInstance_impl<e, O>::isConditionValid(map<string, string>* valuesMap)
{
    uint64_t res;
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
    catch (AdbException& er)
    {
        delete[] condExp;
        throw AdbException(string("AdbException: ") + er.what_s());
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
 * Function: _AdbInstance_impl::getLeafFields
 **/
template<bool e, typename O>
vector<_AdbInstance_impl<e, O>*> _AdbInstance_impl<e, O>::getLeafFields(bool extendenName)
{
    vector<_AdbInstance_impl<e, O>*> fields;

    for (size_t i = 0; i < subItems.size(); i++)
    {
        if (subItems[i]->isNode())
        {
            vector<_AdbInstance_impl<e, O>*> subFields = subItems[i]->getLeafFields(extendenName);
            fields.insert(fields.end(), subFields.begin(), subFields.end());
        }
        else
        {
            if (extendenName && !subItems[i]->inst_props.is_name_extended)
            {
                if (subItems[i]->parent->fieldDesc && subItems[i]->parent->fieldDesc->subNode == "uint64")
                {
                    subItems[i]->layout_item_name =
                      subItems[i]->parent->layout_item_name + "_" + subItems[i]->layout_item_name;
                }
                else
                {
                    subItems[i]->layout_item_name +=
                      _AdbInstance_impl<e, O>::addPathSuffixForArraySupport(subItems[i]->fullName());
                }
                subItems[i]->inst_props.is_name_extended = true;
            }
            fields.push_back(subItems[i]);
        }
    }

    return fields;
}

/**
 * Function: _AdbInstance_impl::pushBuf
 **/
template<bool e, typename O>
void _AdbInstance_impl<e, O>::pushBuf(uint8_t* buf, uint64_t value)
{
    push_to_buf(buf, offset, get_size(), value);
}

/**
 * Function: _AdbInstance_impl::pushBuf
 **/
template<bool e, typename O>
void _AdbInstance_impl<e, O>::pushBufLE(uint8_t* buf, uint64_t value)
{
    push_to_buf_le(buf, offset, get_size(), value);
}

/**
 * Function: _AdbInstance_impl::popBuf
 **/
template<bool e, typename O>
uint64_t _AdbInstance_impl<e, O>::popBuf(uint8_t* buf)
{
    return pop_from_buf(buf, offset, get_size());
}

/**
 * Function: _AdbInstance_impl::popBufLE
 **/
template<bool e, typename O>
uint64_t _AdbInstance_impl<e, O>::popBufLE(uint8_t* buf)
{
    bool wa = get_size() != 32 && isPartOfArray();
    return pop_from_buf_le(buf, offset, get_size(), wa);
}

/**
 * Function: _AdbInstance_impl::print
 **/
template<bool e, typename O>
void _AdbInstance_impl<e, O>::print(int indent)
{
    string indentStr = indentString(indent);
    auto offset_32 = static_cast<uint32_t>(offset);
    auto size_32 = static_cast<uint32_t>(get_size());

    printf("%sfullName: %s, offset: 0x%x.%d, size: 0x%x.%d, isNode:%d, isUnion:%d\n", indentStr.c_str(),
           fullName().c_str(), (offset_32 >> 5) << 2, offset_32 % 32, (size_32 >> 5) << 2, size_32 % 32, isNode(),
           isUnion());

    if (isNode())
    {
        for (size_t i = 0; i < subItems.size(); i++)
            subItems[i]->print(indent + 1);
    }
}

template<bool e, typename O>
_AdbInstance_impl<e, O>::LayoutPartitionProps::LayoutPartitionProps(PartitionTree* tree) : partition_tree(tree)
{
}

template class _AdbInstance_impl<false, uint32_t>;
template class _AdbInstance_impl<true, uint32_t>;

template class _AdbInstance_impl<false, uint64_t>;
template class _AdbInstance_impl<true, uint64_t>;

template typename enable_if<true, _AdbCondition_impl<uint32_t>*>::type
  _AdbInstance_impl<true, uint32_t>::getCondition<true>();
template typename enable_if<true, _AdbCondition_impl<uint64_t>*>::type
  _AdbInstance_impl<true, uint64_t>::getCondition<true>();

template typename enable_if<!false, _AdbCondition_impl<uint32_t>*>::type
  _AdbInstance_impl<false, uint32_t>::getCondition<false>();
template typename enable_if<!false, _AdbCondition_impl<uint64_t>*>::type
  _AdbInstance_impl<false, uint64_t>::getCondition<false>();

template typename enable_if<true, _AdbCondition_impl<uint32_t>*>::type
  _AdbInstance_impl<true, uint32_t>::getArraySizeCondition<true>();
template typename enable_if<true, _AdbCondition_impl<uint64_t>*>::type
  _AdbInstance_impl<true, uint64_t>::getArraySizeCondition<true>();

template typename enable_if<!false, _AdbCondition_impl<uint32_t>*>::type
  _AdbInstance_impl<false, uint32_t>::getArraySizeCondition<false>();
template typename enable_if<!false, _AdbCondition_impl<uint64_t>*>::type
  _AdbInstance_impl<false, uint64_t>::getArraySizeCondition<false>();

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
