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

#ifndef ADB_INSTANCE_H
#define ADB_INSTANCE_H

#include "adb_xmlCreator.h"
#include "adb_condition.h"

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iterator>

#include <type_traits>

using namespace std;
using namespace xmlCreator;

typedef map<string, string> AttrsMap;

template<typename T_OFFSET>
class AdbField_impl;

template<typename T_OFFSET>
class AdbFieldLarge_impl;

template<typename T_OFFSET>
class AdbNode_impl;

template<typename T_OFFSET>
class AdbNodeLarge_impl;

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

template<bool eval_expr = false, typename T_OFFSET = uint32_t>
class _AdbInstance_impl
{
    using AdbNode = AdbNode_impl<T_OFFSET>;
    using AdbField = AdbField_impl<T_OFFSET>;
    using AdbNodeLarge = AdbNodeLarge_impl<T_OFFSET>;
    using AdbFieldLarge = AdbFieldLarge_impl<T_OFFSET>;
    using AdbCondition = _AdbCondition_impl<T_OFFSET>;
struct InstOpsPropertiesBasic
{
    LayoutItemAttrsMap* instAttrsMap{nullptr}; // Attributes after evaluations and array expanding
};

struct InstOpsPropertiesExtended
{
        LayoutItemAttrsMap* instAttrsMap{nullptr}; // Attributes after evaluations and array expanding
    AttrsMap varsMap{};               // all variables relevant to this item after evaluation
    AdbCondition condition{};
    AdbCondition conditionalSize{}; // for dynamic arrays
};



    using InstOpsProperties = typename conditional<eval_expr, InstOpsPropertiesExtended, InstOpsPropertiesBasic>::type;

    struct InstancePropertiesMask
    {
        unsigned char is_semaphore : 1, access_r : 1, access_w : 1, valid_array_index : 1, is_diff : 1,
          is_name_extended : 1, is_index : 1, is_op : 1;

        InstancePropertiesMask()
        {
            is_semaphore = 0;
            access_r = 1;
            access_w = 1;
            valid_array_index = 1;
            is_diff = 0;
            is_name_extended = 0;
            is_index = 0;
            is_op = 0;
        }
    };

    struct LayoutPartitionProps
    {
        PartitionTree* partition_tree;

        LayoutPartitionProps(PartitionTree* tree);
    };

public:
    // Methods
    _AdbInstance_impl() = default;
    _AdbInstance_impl(AdbField* i_fieldDesc,
                      AdbNode* i_nodeDesc,
                      u_int32_t i_arrIdx,
                      _AdbInstance_impl<eval_expr, T_OFFSET>* i_parent,
                      map<string, string> vars,
                      bool bigEndianArr,
                      unsigned char adabe_version = 1,
                      bool optimize_time = false,
                      bool stop_on_partition = false,
                      PartitionTree* next_partition_tree = nullptr,
                      bool path_array_wildcards = false);
    ~_AdbInstance_impl();
    void init_props(unsigned char adabe_version);

    T_OFFSET get_size() const;
    T_OFFSET get_max_leaf_size() const;
    void update_max_leaf();

    T_OFFSET calcArrOffset(bool bigEndianArr, uint8_t align = 32);
    bool stop_on_partition() const;

    template<bool U = eval_expr>
    typename enable_if<U>::type eval_expressions(AttrsMap& i_vars);

    template<bool U = eval_expr>
    typename enable_if<!U>::type eval_expressions(AttrsMap& i_vars);

    static string evalExpr(string expr, AttrsMap* vars);
    static string addPathSuffixForArraySupport(string path);
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
    bool is_index() const;
    bool is_op() const;
    bool is_diff() const;
    void set_is_diff(bool val);
    bool isEnumExists();
    T_OFFSET dwordAddr(uint8_t alignment = 32);
    uint32_t startBit(uint8_t alignment = 32);
    bool enumToInt(const string& name, uint64_t& val); // false means no enum value found
    bool intToEnum(uint64_t val, string& valName);     // false means no enum name found
    map<string, uint64_t> getEnumMap();
    vector<uint64_t> getEnumValues();
    _AdbInstance_impl<eval_expr, T_OFFSET>* getUnionSelectedNodeName(const uint64_t& selectorVal);
    _AdbInstance_impl<eval_expr, T_OFFSET>* getUnionSelectedNodeName(const string& selectorEnum);
    bool operator<(const _AdbInstance_impl<eval_expr, T_OFFSET>& other);
    bool isConditionalNode();
    bool containsDynamicArray();
    bool isConditionValid(map<string, string>* valuesMap);
    // DB like access methods
    _AdbInstance_impl<eval_expr, T_OFFSET>* getChildByPath(const string& path, bool isCaseSensitive = true);
    _AdbInstance_impl<eval_expr, T_OFFSET>* get_layout_item_by_path(const std::string& path);
    vector<_AdbInstance_impl<eval_expr, T_OFFSET>*>
      findChild(const string& name, bool isCaseSensitive = true, bool by_inst_name = false);
    _AdbInstance_impl<eval_expr, T_OFFSET>* get_root();
    string getInstanceAttr(const string& attrName) const;
    bool getInstanceAttr(const string& attrName, string& value);
    LayoutItemAttrsMap::iterator getInstanceAttrIterator(const string& attrName);
    void setInstanceAttr(const string& attrName, const string& attrValue);

    template<bool U = eval_expr>
    typename enable_if<U>::type setVarsMap(const string& attrName, const string& attrValue);

    template<bool U = eval_expr>
    typename enable_if<!U>::type setVarsMap(const string& attrName, const string& attrValue);

    template<bool U = eval_expr>
    typename enable_if<U>::type setVarsMap(const AttrsMap& AttrsMap);

    template<bool U = eval_expr>
    typename enable_if<!U>::type setVarsMap(const AttrsMap& AttrsMap);

    template<bool U = eval_expr>
    typename enable_if<U, AttrsMap>::type getVarsMap();

    template<bool U = eval_expr>
    typename enable_if<!U, AttrsMap>::type getVarsMap();
    template<bool U = eval_expr>
    typename enable_if<U, AdbCondition*>::type getCondition();
    template<bool U = eval_expr>
    typename enable_if<!U, AdbCondition*>::type getCondition();

    template<bool U = eval_expr>
    typename enable_if<U, AdbCondition*>::type getArraySizeCondition();

    template<bool U = eval_expr>
    typename enable_if<!U, AdbCondition*>::type getArraySizeCondition();

    vector<_AdbInstance_impl<eval_expr, T_OFFSET>*> getLeafFields(bool extendedName); // Get all leaf fields
    void pushBuf(uint8_t* buf, uint64_t value);
    void pushBufLE(uint8_t* buf, uint64_t value);
    uint64_t popBuf(uint8_t* buf);
    uint64_t popBufLE(uint8_t* buf);

    template<bool U = eval_expr>
    typename enable_if<U>::type initInstOps();

    template<bool U = eval_expr>
    typename enable_if<!U>::type initInstOps();

    // FOR DEBUG
    void print(int indent = 0);

public:
    // Constants
    static const char path_seperator;
    static const string EXP_PATTERN;

    // Members
    string layout_item_name{}; // instance name
    string full_path{};
    vector<_AdbInstance_impl<eval_expr, T_OFFSET>*> subItems{};
    AdbField* fieldDesc{nullptr};
    AdbNode* nodeDesc{nullptr};
    _AdbInstance_impl<eval_expr, T_OFFSET>* parent{nullptr};
    _AdbInstance_impl<eval_expr, T_OFFSET>* unionSelector{nullptr}; // For union instances only
    InstOpsProperties inst_ops_props{};
    uint32_t arrIdx{0};
    T_OFFSET offset{0xffffffff};  // Global offset in bits (Relative to 0) todo: put static cast
    AdbField* _max_leaf{nullptr}; // for DS alignment check
    InstancePropertiesMask inst_props{};
    LayoutPartitionProps* partition_props{nullptr};
private:
    _AdbInstance_impl<eval_expr, T_OFFSET>* find_layout_item_dfs(const std::string& path);
};

// TODO: try to move the function definition below to the cpp file, currently fails linkage
template<bool eval_expr, typename O>
template<bool U>
typename enable_if<U>::type _AdbInstance_impl<eval_expr, O>::initInstOps()
{
    string value;
    auto found_inst_condition = getInstanceAttr("condition", value);
    if (found_inst_condition && parent && parent->nodeDesc)
    {
        auto is_conditional = parent->nodeDesc->attrs.find("is_conditional");
        if (is_conditional != parent->nodeDesc->attrs.end() && is_conditional->second == "1")
    {
            inst_ops_props.condition.init(value);
        }
    }
    auto found_size_condition = getInstanceAttr("size_condition", value);
    if (found_size_condition)
    {
        inst_ops_props.conditionalSize.init(value);
    }
}

template<bool eval_expr, typename O>
template<bool U>
typename enable_if<!U>::type _AdbInstance_impl<eval_expr, O>::initInstOps()
{
    return;
}

using AdbInstanceLegacy = _AdbInstance_impl<false, uint32_t>;
using AdbInstanceAdvLegacy = _AdbInstance_impl<true, uint32_t>;
// using AdbInstance = _AdbInstance_impl<false, uint32_t>;
// using AdbInstanceAdv = _AdbInstance_impl<true, uint32_t>;

using AdbInstance = _AdbInstance_impl<false, uint64_t>;
using AdbInstanceAdv = _AdbInstance_impl<true, uint64_t>;
// using AdbInstanceNew = _AdbInstance_impl<false, uint64_t>;
// using AdbInstanceAdvNew = _AdbInstance_impl<true, uint64_t>;

// Constants Definitions
template<bool e, typename O>
const char _AdbInstance_impl<e, O>::path_seperator{'.'};
template<bool e, typename O>
const string _AdbInstance_impl<e, O>::EXP_PATTERN{"\\s*([a-zA-Z0-9_]+)=((\\$\\(.*?\\)|\\S+|$)*)\\s*"};

#endif
