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

#ifndef ADB_INSTANCE_H
#define ADB_INSTANCE_H

#include "adb_xmlCreator.h"
#include "adb_condition.h"

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iterator>

using namespace std;
using namespace xmlCreator;

typedef map<string, string> AttrsMap;
class AdbField;
class AdbNode;
struct PartitionTree;
class LayoutItemAttrsMap
{
public:
    class iterator
    {
    public:
        using value_type = pair<string, string>;
        using difference_type = std::ptrdiff_t;
        using pointer = pair<string, string>*;
        using reference = pair<string, string>&;
        using iterator_category = bidirectional_iterator_tag;

        explicit iterator(LayoutItemAttrsMap& container, AttrsMap::iterator current, bool past_layout_specific = false);

        iterator(const iterator& other) = default;

        iterator() = default;
        iterator& operator=(const iterator& other) = default;

        reference operator*() const;
        pointer operator->();

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

    private:
        void advance_internal();
        void regress_internal();

        LayoutItemAttrsMap* _container;
        AttrsMap::iterator _current;
        bool _layout_specific_end;
    };

    using value_type = AttrsMap::value_type;

    LayoutItemAttrsMap(AttrsMap& field_desc_attrs);
    LayoutItemAttrsMap(LayoutItemAttrsMap& field_desc_attrs) = default;
    LayoutItemAttrsMap& operator=(const LayoutItemAttrsMap& other);

    iterator begin();
    iterator& end();

    // string at(const string& key);
    // const string& at(const string& key ) const;

    iterator find(const string& key);
    bool contains(const string& key);

    // pair<iterator, bool> insert(const value_type& value);

    string& operator[](const string& key);

private:
    AttrsMap _layout_specific_attrs{};
    AttrsMap& _field_desc_attrs;
    set<string> _overriden{};
    iterator _end{*this, _field_desc_attrs.end(), true};
};

class AdbInstance
{
    struct InstOpsProperties
    {
        LayoutItemAttrsMap instAttrsMap; // Attributes after evaluations and array expanding
        AttrsMap varsMap{};              // all variables relevant to this item after evaluation
        AdbCondition condition{};
        AdbCondition conditionalSize{}; // for dynamic arrays

        InstOpsProperties(AttrsMap& field_attrs);
    };

    struct InstancePropertiesMask
    {
        unsigned char is_semaphore : 1, access_r : 1, access_w : 1, valid_array_index : 1, is_diff : 1,
          is_name_extended : 1;

        InstancePropertiesMask()
        {
            is_semaphore = 0;
            access_r = 1;
            access_w = 1;
            valid_array_index = 1;
            is_diff = 0;
            is_name_extended = 0;
        }
    };

    struct LayoutPartitionProps
    {
        PartitionTree* partition_tree;

        LayoutPartitionProps(PartitionTree* tree);
    };

public:
    // Methods
    AdbInstance() = default;
    AdbInstance(AdbField* i_fieldDesc,
                AdbNode* i_nodeDesc,
                u_int32_t i_arrIdx,
                AdbInstance* i_parent,
                map<string, string> vars,
                bool bigEndianArr,
                bool isExprEval,
                unsigned char adabe_version = 1,
                bool optimize_time = false,
                bool stop_on_partition = false,
                PartitionTree* next_partition_tree = nullptr);

    ~AdbInstance();
    void init_props(unsigned char adabe_version);
    u_int32_t calcArrOffset(bool bigEndianArr);
    bool stop_on_partition() const;
    void eval_expressions(AttrsMap& i_vars);
    static string evalExpr(string expr, AttrsMap* vars);
    const string& get_field_name();
    bool isLeaf();
    bool isUnion();
    bool isStruct();
    bool isNode();
    bool isPartOfArray();
    string fullName(size_t skipLevel = 0);
    bool isReserved();
    bool is_valid_array_index() const;
    bool is_semaphore() const;
    bool is_ro() const;
    bool is_wo() const;
    bool is_diff() const;
    void set_is_diff(bool val);
    bool isEnumExists();
    u_int32_t dwordAddr(uint8_t alignment = 32);
    u_int32_t startBit(uint8_t alignment = 32);
    bool enumToInt(const string& name, u_int64_t& val); // false means no enum value found
    bool intToEnum(u_int64_t val, string& valName);     // false means no enum name found
    map<string, u_int64_t> getEnumMap();
    vector<u_int64_t> getEnumValues();
    AdbInstance* getUnionSelectedNodeName(const u_int64_t& selectorVal);
    AdbInstance* getUnionSelectedNodeName(const string& selectorEnum);
    bool operator<(const AdbInstance& other);
    bool isConditionalNode();
    bool isConditionValid(map<string, string>* valuesMap);
    // DB like access methods
    AdbInstance* getChildByPath(const string& path, bool isCaseSensitive = true);
    vector<AdbInstance*> findChild(const string& name, bool isCaseSensitive = true, bool by_inst_name = false);
    AdbInstance* get_root();
    string getInstanceAttr(const string& attrName) const;
    bool getInstanceAttr(const string& attrName, string& value);
    LayoutItemAttrsMap::iterator getInstanceAttrIterator(const string& attrName);
    void setInstanceAttr(const string& attrName, const string& attrValue);
    void setVarsMap(const string& attrName, const string& attrValue);
    void setVarsMap(const AttrsMap& AttrsMap);
    AttrsMap getVarsMap();
    vector<AdbInstance*> getLeafFields(bool extendedName); // Get all leaf fields
    void pushBuf(u_int8_t* buf, u_int64_t value);
    u_int64_t popBuf(u_int8_t* buf);
    void initInstOps(bool is_root = false);
    // FOR DEBUG
    void print(int indent = 0);

public:
    // Constants
    static const char path_seperator;
    static const string EXP_PATTERN;

    // Members
    string layout_item_name{}; // instance name
    string full_path{};
    vector<AdbInstance*> subItems{};
    AdbField* fieldDesc{nullptr};
    AdbNode* nodeDesc{nullptr};
    AdbInstance* parent{nullptr};
    AdbInstance* unionSelector{nullptr}; // For union instances only
    InstOpsProperties* inst_ops_props{nullptr};
    u_int32_t arrIdx{0};
    u_int32_t offset{0xffffffff}; // Global offset in bits (Relative to 0)
    u_int32_t size{0};            // in bits
    u_int32_t maxLeafSize{0};     // in bits for DS alignment check
    InstancePropertiesMask inst_props{};
    PartitionTree* partition_tree{nullptr};
};

#endif
