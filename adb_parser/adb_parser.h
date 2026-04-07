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
#ifndef ADB_ADB_H
#define ADB_ADB_H

class LogFile;

#include <type_traits>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <exception>
#include <list>
#include <common/compatibility.h>
#include "adb_expr.h"
#include "adb_node.h"
#include "adb_field.h"
#include "adb_exceptionHolder.h"
#include "adb_logfile.h"
#include "adb_config.h"
#include "adb_instance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdexcept>
#include "adb_xmlCreator.h"
#include "adb_condition.h"

#ifdef __WIN__
#include <process.h>
#define OS_PATH_SEP "\\"
#else
#define OS_PATH_SEP "/"
#endif

using namespace std;

#if defined(__MINGW32__) || defined(__MINGW64__)
#define PRINTF_FORMAT __MINGW_PRINTF_FORMAT
#else
#define PRINTF_FORMAT printf
#endif

template<typename T_OFFSET>
class AdbField_impl;

template<typename T_OFFSET>
class AdbNode_impl;

using namespace xmlCreator;
using namespace std;

struct IncludeFileInfo;
typedef map<string, IncludeFileInfo> IncludeFileMap;
typedef map<string, string> AttrsMap;
typedef vector<AdbConfig*> ConfigList;
typedef map<string, AttrsMap> InstanceAttrs;
typedef map<string, AttrsMap> NodeAttrs;
typedef map<string, vector<string>> ExceptionsMap;

struct IncludeFileInfo
{
    string fullPath;
    string includedFromFile;
    int includedFromLine;
};

struct PartitionTree
{
    string name;
    bool stop;
    PartitionTree* parent;
    vector<PartitionTree*> sub_items;
};

template<bool eval_expr = false, typename T_OFFSET = uint32_t>
class _Adb_impl
{
public:
    using AdbField = AdbField_impl<T_OFFSET>;
    using AdbNode = AdbNode_impl<T_OFFSET>;
    using AdbInstance = _AdbInstance_impl<eval_expr, T_OFFSET>;

    using AdbFieldLarge = AdbFieldLarge_impl<T_OFFSET>;
    using AdbNodeLarge = AdbNodeLarge_impl<T_OFFSET>;

    using AdbCondition = _AdbCondition_impl<T_OFFSET>;
    using AdbCondVar = _AdbCondVar_impl<T_OFFSET>;
    using NodesMap = map<string, AdbNode*>;
    using PathPart = pair<string, vector<uint32_t>>;
    using SplittedPath = vector<PathPart>;

    // Methods
    _Adb_impl();
    ~_Adb_impl();
    void raiseException(bool allowMultipleExceptions,
                        string exceptionTxt,
                        const string expType,
                        bool raise_warnings = true);
    // strict union means:
    //   1- dwrod aligned unions
    //   2- contains nodes only
    //   3- check node size vs instance size
    bool loadFromString(const char* adbContents,
                        bool addReserved = false,
                        bool strict = true,
                        bool enforceExtraChecks = false,
                        string root_node_name = "root");
    bool load(string fname,
              bool addReserved = false,
              bool strict = true,
              string includePath = "",
              string includeDir = "",
              bool enforceExtraChecks = false,
              bool getAllExceptions = false,
              string logFile = "",
              bool checkDsAlign = false,
              bool enforceGuiChecks = false,
              bool force_dword_align = false,
              bool cd_mode = false,
              bool variable_alignment = false,
              string root_node_name = "root");
    string toXml(vector<string> nodeNames = vector<string>(),
                 bool addRootNode = false,
                 string rootName = "MainNode",
                 string addPrefix = "",
                 bool bigEndian = false);

    void addMissingNodes(int depth, bool allowMultipleExceptions);
    AdbInstance* createLayout(string rootNodeName,
                              int depth = -1, /* -1 means instantiate full tree */
                              bool ignoreMissingNodes = false,
                              bool getAllExceptions = false,
                              bool optimize_time = false,
                              T_OFFSET root_offset = 0,
                              string root_display_name = "",
                              PartitionTree* partition_tree = nullptr,
                              AdbField* rootField = nullptr,
                              string ancestor_path = "",
                              bool array_path_wildcards = false,
                              bool strict_instance_ops = true,
                              bool enable_parse_missing_sons = false);
    vector<string> getNodeDeps(string nodeName);
    void add_include(string fileName, string filePath, string included_from, int lineNumber);
    string getLastError();

    // Layout traversal function
    void traverse_layout(AdbInstance* instance,
                         const string& path,
                         T_OFFSET offset_shift,
                         const uint8_t* buffer,
                         uint32_t buffer_size,
                         bool (*func)(const string&, uint64_t, uint64_t, AdbInstance*, void*),
                         void* context,
                         bool evaluate_conditions = true,
                         bool handle_enums = false,
                         bool full_path = true,
                         bool allow_multiple_exceptions = false); // internal argument passed inside recursion, by
                                                                  // return value of "func"

    string printAdbExceptionMap();
    void clearAdbExceptionMap();

    // FOR DEBUG
    void print(int indent = 0);

private:
    template<bool U = eval_expr>
    typename enable_if<!U>::type updateLayoutConditions(bool useConditionalArrays);

    template<bool U = eval_expr>
    typename enable_if<U>::type updateLayoutConditions(bool useConditionalArrays);

    template<bool U = eval_expr>
    typename enable_if<!U>::type updateConditionsLists(AdbInstance* inst);

    template<bool U = eval_expr>
    typename enable_if<U>::type updateConditionsLists(AdbInstance* inst);

public:
    // Members
    string version;
    NodesMap nodesMap;
    ConfigList configs;
    string rootNode;
    bool bigEndianArr;
    bool singleEntryArrSupp;
    InstanceAttrs instAttrs; // Key is instance's Adabe full path, value is attribute map
    NodeAttrs nodeAttrs{};   // Key is node[.field], value is attribute map
    string srcDocName;
    string srcDocVer;
    LogFile* _logFile;

    /* For internal use */
public:
    vector<string> includePaths;
    std::map<string, string> defines_map;
    string mainFileName;
    IncludeFileMap includedFiles;
    vector<string> warnings;

private:
    bool createInstance(AdbField* fieldDesc,
                        AdbInstance* parent,
                        map<string, string> vars,
                        int depth,
                        bool ignoreMissingNodes = false,
                        bool enable_parse_missing_sons = false,
                        vector<SplittedPath> missing_sons = vector<SplittedPath>(),
                        bool getAllExceptions = false,
                        bool optimize_time = false,
                        PartitionTree* partition_tree = nullptr,
                        bool array_path_wildcards = false);
    bool checkInstSizeConsistency(bool getAllExceptions = false);
    static PartitionTree* prune_up(PartitionTree* partition_tree);
    static bool
      skip_or_get_child_missing_sons(vector<SplittedPath>& missing_sons, AdbField& child_field, uint32_t array_idx);
    vector<SplittedPath> parse_missing_sons(AdbNode& node, bool allowMultipleExceptions);
    PathPart parse_missing_son_part(const string& part, const string& ranges, bool allowMultipleExceptions);

private:
    string _lastError;
    bool _checkDsAlign;
    bool _enforceGuiChecks;
    bool _force_dword_align;
    bool _cd_mode;
    list<AdbInstance*> _unionSelectorEvalDeffered;
    list<AdbInstance*> _conditionInstances;
    list<AdbInstance*> _conditionalArrays;
    void checkInstanceOffsetValidity(AdbInstance* inst, AdbInstance* parent, bool allowMultipleExceptions);
    void throwExeption(bool allowMultipleExceptions, string exceptionTxt, string addedMsgMultiExp);

    void traverse_layout(AdbInstance* instance,
                         const string& path,
                         T_OFFSET offset_shift,
                         const uint8_t* buffer,
                         uint32_t buffer_size,
                         bool (*func)(const string&, uint64_t, uint64_t, AdbInstance*, void*),
                         void* context,
                         string suffix, // internal argument for legacy array support
                         bool& stop,    // internal argument passed inside recursion, by return value of "func"
                         bool evaluate_conditions = true,
                         bool handle_enums = false,
                         bool full_path = true,
                         bool allow_multiple_exceptions = false);

    // Helper functions for traverse_layout
    uint64_t _trvrs_calc_cond_num_elements(AdbInstance* instance,
                                           T_OFFSET offset_shift,
                                           const uint8_t* buffer,
                                           uint32_t buffer_size,
                                           bool evaluate_conditions,
                                           bool allow_multiple_exceptions);
    string _trvrs_get_element_array_suffix(uint64_t i, AdbInstance* instance, bool full_path);
    void _trvrs_handle_enums(AdbInstance* instance,
                             const string& element_path,
                             T_OFFSET element_offset_shift,
                             const uint8_t* buffer,
                             bool (*func)(const string&, uint64_t, uint64_t, AdbInstance*, void*),
                             void* context);
    AdbInstance* _trvrs_get_selected_node(AdbInstance* instance, T_OFFSET element_offset_shift, const uint8_t* buffer);
};

using AdbLegacy = _Adb_impl<false, uint32_t>;
using AdbAdvLegacy = _Adb_impl<true, uint32_t>;

using Adb = _Adb_impl<false, uint64_t>;
using AdbAdv = _Adb_impl<true, uint64_t>;

#endif
