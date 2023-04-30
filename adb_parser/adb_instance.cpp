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
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

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

AdbInstance::AdbInstance() :
    fieldDesc(NULL),
    nodeDesc(NULL),
    parent(NULL),
    condition(AdbCondition()),
    conditionalSize(AdbCondition()),
    offset(0xffffffff),
    size(0),
    maxLeafSize(0),
    arrIdx(0),
    isNameBeenExtended(false),
    unionSelector(NULL),
    isDiff(false),
    userData(NULL)

{
}

/**
 * Function: AdbInstance::AdbInstance
 **/
AdbInstance::~AdbInstance()
{
    for (size_t i = 0; i < subItems.size(); i++)
        delete subItems[i];
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
string AdbInstance::fullName(int skipLevel)
{
    list<string> fnList;
    AdbInstance* p = parent;

    fnList.push_front(name);
    while (p != NULL)
    {
        fnList.push_front(p->name);
        p = p->parent;
    }

    if ((int)fnList.size() > skipLevel)
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

/**
 * Function: AdbInstance::fullName
 **/
bool AdbInstance::isReserved()
{
    return fieldDesc->isReserved;
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
        string subName = isCaseSensitive ? subItems[i]->name : boost::algorithm::to_lower_copy(subItems[i]->name);
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
        if (name == childName)
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
    AttrsMap::const_iterator it = instAttrsMap.find(attrName);
    if (it == instAttrsMap.end())
    {
        if (fieldDesc)
        {
            it = fieldDesc->attrs.find(attrName);
            if (it == fieldDesc->attrs.end())
            {
                return string();
            }
        }
        else
        {
            return string();
        }
    }
    return it->second;
}

/**
 * Function: AdbInstance::getInstanceAttrIterator
 **/
AttrsMap::iterator AdbInstance::getInstanceAttrIterator(const string& attrName, bool& found)
{
    AttrsMap::iterator it = instAttrsMap.find(attrName);
    found = false;
    if (it != instAttrsMap.end())
    {
        found = true;
    }
    else if (fieldDesc)
    {
        it = fieldDesc->attrs.find(attrName);
        if (it != fieldDesc->attrs.end())
        {
            found = true;
        }
    }
    return it;
}

/**
 * Function: AdbInstance::setInstanceAttr
 **/
void AdbInstance::setInstanceAttr(const string& attrName, const string& attrValue)
{
    instAttrsMap[attrName] = attrValue;
}

/*
 * Function: AdbInstance::copyAllInstanceAttr - copies all attrs from attributes structure
 **/
void AdbInstance::copyAllInstanceAttr(AttrsMap& attsToCopy)
{
    instAttrsMap = attsToCopy;
}

/**
 * Function: AdbInstance::getFullInstanceAttrsMapCopy - returns the instance attr map by val
 **/
AttrsMap AdbInstance::getFullInstanceAttrsMapCopy()
{
    AttrsMap tmpCopy;
    // copy first the fields attr map
    for (AttrsMap::iterator it = fieldDesc->attrs.begin(); it != fieldDesc->attrs.end(); it++)
    {
        tmpCopy[it->first] = it->second;
    }
    // copy the overriden variables - in instAttrsMap
    for (AttrsMap::iterator it = instAttrsMap.begin(); it != instAttrsMap.end(); it++)
    {
        tmpCopy[it->first] = it->second;
    }
    return tmpCopy;
}

/**
 * Function: AdbInstance::setVarsMap - set an item in vars map
 **/
void AdbInstance::setVarsMap(const string& attrName, const string& attrValue)
{
    varsMap[attrName] = attrValue;
}

/**
 * Function: AdbInstance::setVarsMap - set an item in vars map
 **/
void AdbInstance::setVarsMap(const AttrsMap& AttrsMap)
{
    varsMap = AttrsMap;
}

/**
 * Function: AdbInstance::setVarsMap - returns a copy of vars map
 **/
AttrsMap AdbInstance::getVarsMap()
{
    return varsMap;
}

/**
 * Function: AdbInstance::isEnumExists
 **/
bool AdbInstance::isEnumExists()
{
    return !getInstanceAttr("enum").empty();
}

/**
 * Function: AdbInstance::enumToInt
 **/
bool AdbInstance::enumToInt(const string& name, u_int64_t& val)
{
    vector<string> enumValues;
    string enums = getInstanceAttr("enum");
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
    vector<string> enumValues;
    string enums = getInstanceAttr("enum");
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
    vector<string> enumValues;
    string enums = getInstanceAttr("enum");
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
            // continue;
        }

        char* end;
        u_int64_t intVal = strtoul(pair[1].c_str(), &end, 0);
        if (*end != '\0')
        {
            throw AdbException(string("Can't evaluate enum (") + pair[0].c_str() + "): " + pair[1].c_str());
            // continue;
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
    vector<string> enumValues;
    string enums = getInstanceAttr("enum");
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
        throw AdbException("Can't find selector for union: " + name);
    }

    map<string, u_int64_t> selectorValMap = unionSelector->getEnumMap();
    for (map<string, u_int64_t>::iterator it = selectorValMap.begin(); it != selectorValMap.end(); it++)
    {
        if (it->second == selectorVal)
        {
            const string& selectorEnum = it->first;
            // search for the sub instance with the "selected_by" attribute == selectorEnum
            for (size_t i = 0; i < subItems.size(); i++)
            {
                if (subItems[i]->getInstanceAttr("selected_by") == selectorEnum)
                {
                    return subItems[i];
                }
            }
            throw AdbException("Found selector value (" + selectorEnum + ") is defined for selector field (" +
                               unionSelector->name + ") but no appropriate subfield of this union was found");
        }
    }

    throw AdbException("Union selector field (" + unionSelector->name + ") doesn't define selector value (" +
                       boost::lexical_cast<string>(selectorVal));
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
        throw AdbException("Can't find selector for union: " + name);
    }

    for (size_t i = 0; i < subItems.size(); i++)
    {
        if (subItems[i]->getInstanceAttr("selected_by") == selectorEnum)
        {
            return subItems[i];
        }
    }

    throw AdbException("Union selector field (" + unionSelector->name + ") doesn't define a selector value (" +
                       selectorEnum + ")");
}

/**
 * Function: AdbInstance::isConditionalNode
 * Throws exception: AdbException
 **/
bool AdbInstance::isConditionalNode()
{
    if (isNode())
    {
        return (getInstanceAttr("is_conditional") == "1");
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
            if (extendenName && !subItems[i]->isNameBeenExtended)
            {
                if (subItems[i]->parent->fieldDesc->subNode == "uint64")
                {
                    subItems[i]->name = subItems[i]->parent->name + "_" + subItems[i]->name;
                }
                else
                {
                    subItems[i]->name = subItems[i]->name + addPathSuffixForArraySupport(subItems[i]->fullName());
                }
                subItems[i]->isNameBeenExtended = true;
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
