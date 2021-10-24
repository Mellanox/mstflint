/*                  - Mellanox Confidential and Proprietary -
 *
 * Copyright (C) February 2010, Mellanox Technologies Ltd. ALL RIGHTS RESERVED.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * Except as specifically permitted herein, no portion of the information,
 * including but not limited to object code and source code, may be reproduced,
 * modified, distributed, republished or otherwise exploited in any form or by
 * any means for any purpose without the prior written permission of Mellanox
 * Technologies Ltd. Use of software subject to the terms and conditions
 * detailed in the file "LICENSE.txt".
 *
 * End of legal section ......................................................
 *
 *  adb_db.c - "C" wrapper module for adb_parser classes.
 *              This module provides an alternative "C" way to work with AdbInstance objects.
 *
 *  Version: $Id$
 *
 *  Author: Wasim Abu Moch (wasim@mellanox.co.il)
 */

#include <vector>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "adb_db.h"

#define CHECK_FIELD(field, node_w) \
    if (((AdbInstance*)field)->isReserved()) { \
        continue; \
    } \
    offset = db_field_offset(field); \
    if (offset - node_w->node->offset < from || \
        offset - node_w->node->offset > to) { \
        continue; \
    }

struct node_wrapper
{
    AdbInstance *node;
    vector<AdbInstance*> *fields;
};

static char err[1024] = {0};

/**
 * db_create
 */
adb_db_t* db_create()
{
    return new Adb();

}

/**
 * db_load
 */
int db_load(adb_db_t *db, const char *adb_file_path, int add_reserved)
{
    if (!((Adb*)db)->load(adb_file_path, add_reserved, NULL, false)) {
        sprintf(err, "Failed to load adabe project: %s", ((Adb*)db)->getLastError().c_str());
        return 1;
    }

    return 0;
}

/**
 * db_load_from_str
 */
int db_load_from_str(adb_db_t *db, const char *adb_data, int add_reserved)
{
    if (!((Adb*)db)->loadFromString(adb_data, add_reserved, NULL, false)) {
        sprintf(err, "Failed to load adabe project: %s", ((Adb*)db)->getLastError().c_str());
        return 1;
    }

    return 0;
}

/**
 * db_destroy
 */
void db_destroy(adb_db_t *db)
{
    if (db) {
        delete (Adb*)db;
    }
}

/**
 * db_destroy
 */
const char* db_get_last_err()
{
    return err;
}


adb_limits_map_t* db_create_limits_map(adb_db_t *db)
{
    map<string, string> *limits = new map<string, string>();

    // Load defines
    if (db) {
        for (size_t i = 0; i < ((Adb*)db)->configs.size(); i++) {
            AttrsMap::iterator attrs_map = ((Adb*)db)->configs[i]->attrs.find("define");
            if (attrs_map != ((Adb*)db)->configs[i]->attrs.end()) {
                vector<string> defVal;
                boost::algorithm::split(defVal, attrs_map->second, boost::is_any_of(string("=")));

                if (defVal.size() == 1) {
                    ((map<string, string>*)limits)->insert(pair<string, string>(defVal[0], "0"));
                } else {
                    ((map<string, string>*)limits)->insert(pair<string, string>(defVal[0], defVal[1]));
                }
            }
        }
    }
    return (adb_limits_map_t*)limits;

}

void db_destroy_limits_map(adb_limits_map_t *limits)
{
    if (limits) {
        ((map<string, string>*)limits)->clear();
        delete (map<string, string>*)limits;
    }
}

/**
 * db_get_node
 */
adb_node_t* db_get_node(adb_db_t *db, const char *node_name)
{
    Adb *adb = (Adb*)db;
    AdbInstance *node = adb->createLayout(node_name, false, NULL);
    if (!node) {
        sprintf(err, "Failed to create node %s: %s", node_name, adb->getLastError().c_str());
        return NULL;
    }
    struct node_wrapper *node_w = (struct node_wrapper*)malloc(sizeof(struct node_wrapper));
    if (!node_w) {
        delete node;
        sprintf(err, "Failed to allocate memory for node");
        return NULL;
    }
    memset(node_w, 0, sizeof(*node_w));
    node_w->node = node;
    node_w->fields = new vector<AdbInstance*>;
    *node_w->fields = node->getLeafFields(false);
    return node_w;
}

/**
 * db_node_destroy
 */
void db_node_destroy(adb_node_t *node)
{
    struct node_wrapper *node_w = (struct node_wrapper*)node;
    if (node_w) {
        if (node_w->node) {
            delete node_w->node;
        }
        if (node_w->fields) {
            delete node_w->fields;
        }
        free(node_w);
    }
}

/**
 * db_node_name
 */
void db_node_name(adb_node_t *node, char name[])
{
    struct node_wrapper *node_w = (struct node_wrapper*)node;
    strcpy(name, node_w->node->name.c_str());
}

/**
 * db_node_size
 */
int db_node_size(adb_node_t *node)
{
    struct node_wrapper *node_w = (struct node_wrapper*)node;
    return node_w->node->size;
}

/**
 * db_node_num_of_fields
 */
int db_node_num_of_fields(adb_node_t *node)
{
    struct node_wrapper *node_w = (struct node_wrapper*)node;
    return (int)node_w->fields->size();
}

/**
 * db_node_get_field
 */
adb_field_t* db_node_get_field(adb_node_t *node, int field_idx)
{
    if (field_idx >= db_node_num_of_fields(node)) {
        sprintf(err, "index out of range");
        return NULL;
    }

    struct node_wrapper *node_w = (struct node_wrapper*)node;
    return node_w->fields->at(field_idx);
}

/**
 * db_node_get_field_by_path
 */
adb_field_t* db_node_get_field_by_path(adb_node_t *node, const char *path, int is_case_sensitive)
{
    struct node_wrapper *node_w = (struct node_wrapper*)node;
    string fullPath(path);

    if (node_w->node->isConditionalNode()) {
        fullPath += ".val";
    }
    for (size_t i = 0; i < node_w->fields->size(); i++) {
        if (is_case_sensitive) {
            if (node_w->fields->at(i)->fullName(1) == fullPath) {
                return node_w->fields->at(i);
            }
        } else {
            string field_name_lower = boost::algorithm::to_lower_copy(node_w->fields->at(i)->fullName(1));
            string path_lower = boost::algorithm::to_lower_copy(fullPath);

            if (path_lower == field_name_lower) {
                return node_w->fields->at(i);
            }
        }
    }

    sprintf(err, "Can't find field (%s)", path);
    return NULL;
}

/**
 * db_node_dump
 * Returns: false on error
 */
bool db_node_dump(adb_node_t *node, u_int8_t buf[], dump_format_t format, FILE *stream)
{
    struct node_wrapper *node_w = (struct node_wrapper*)node;
    return db_node_range_dump(node, 0, node_w->node->size - 1, buf, format, stream);
}

/**
 * db_node_dump_with_limits
 * Returns: false on error
 */
bool db_node_conditional_dump(adb_node_t *node,
                              u_int8_t buf[],
                              dump_format_t format,
                              FILE *stream,
                              adb_limits_map_t *values_map)
{
    struct node_wrapper *node_w = (struct node_wrapper*)node;
    return db_node_conditional_range_dump(node, 0, node_w->node->size - 1, buf, format, stream, values_map);
}

/*
 * db_node_range_dump
 * Returns: false on error
 */
bool db_node_range_dump(adb_node_t *node, u_int32_t from, u_int32_t to,
                        u_int8_t buf[], dump_format_t format, FILE *stream)
{
    return db_node_conditional_range_dump(node, from, to, buf, format, stream, NULL);
}

/*
 * db_node_range_dump_with_limits
 * Returns: false on error
 */
bool db_node_conditional_range_dump(adb_node_t *node,
                                    u_int32_t from,
                                    u_int32_t to,
                                    u_int8_t buf[],
                                    dump_format_t format,
                                    FILE *stream,
                                    adb_limits_map_t *values_map)
{
    int i;
    adb_field_t *field;
    char enum_str[256];
    char name[256];
    int is_enum;
    u_int32_t value;
    u_int32_t offset;
    u_int32_t size;
    struct node_wrapper *node_w = (struct node_wrapper*)node;
    if (values_map) {
        // Fill values map for conditions
        for (i = 0; i < db_node_num_of_fields(node); i++) {
            field = db_node_get_field(node, i);
            if (!field) {
                return false;
            }
            CHECK_FIELD(field, node_w);
            db_field_full_name(field, 0, name);
            value = db_field_value(field, (u_int8_t*)buf);
            if (node_w->node->isConditionalNode()) {
                char *p = strstr(name, ".val");
                if (p != NULL) {
                    *p = '\0';
                }
            }
            ((map<string, string>*)values_map)->insert(pair<string, string>(name, boost::lexical_cast<string>(value)));
        }
    }

    for (i = 0; i < db_node_num_of_fields(node); i++) {
        field = db_node_get_field(node, i);
        if (!field) {
            return false;
        }
        CHECK_FIELD(field, node_w);

        db_field_full_name(field, 0, name);
        value = db_field_value(field, (u_int8_t*)buf);
        if (node_w->node->isConditionalNode()) {
            char *p = strstr(name, ".val");
            if (p != NULL) {
                *p = '\0';
            }
        }
        /*
         * Just if the node is Conditional
         */
        if (node_w->node->isConditionalNode() && values_map != NULL) {
            try {
                AdbInstance *parentField = node_w->node->subItems[i];
                if (!parentField->isConditionValid(((map<string, string>*)values_map))) {
                    ((map<string, string>*)values_map)->erase(name);
                    continue;
                }
            } catch (...) {
                continue;
            }
        }

        is_enum = db_field_enum(field, value, enum_str);
        size = db_field_size(field);
        if (stream != NULL) {
            switch (format) {
            case DB_FORMAT_STANDARD:
                fprintf(stream, "%-40s : 0x%x %s\n", name, value, is_enum ? enum_str : "");
                break;

            case DB_FORMAT_STANDARD_NO_ENUM:
                fprintf(stream, "%-40s : 0x%x\n", name, value);
                break;

            case DB_FORMAT_FULL_DETAILS:
                fprintf(stream, "%-40s : 0x%x %s - address: 0x%x.%d:%d\n",
                        name, value, is_enum ? enum_str : "", offset / 32 * 4, offset % 32, size);
                break;
            }
        }
    }
    return true;
}

/**
 * db_field_name
 */
void db_field_name(adb_field_t *field, char name[])
{
    strcpy(name, ((AdbInstance*)field)->name.c_str());
}

/**
 * db_field_full_name
 */
void db_field_full_name(adb_field_t *field, int skip_level, char name[])
{
    strcpy(name, ((AdbInstance*)field)->fullName(skip_level + 1).c_str());
}

/**
 * db_field_offset
 */
int db_field_offset(adb_field_t *field)
{
    return ((AdbInstance*)field)->offset;
}

/**
 * db_field_size
 */
int db_field_size(adb_field_t *field)
{
    return ((AdbInstance*)field)->size;
}

/**
 * db_field_value
 */
u_int64_t db_field_value(adb_field_t *field, u_int8_t buf[])
{
//    cout << ((AdbInstance*)field)->offset / 8 << endl;
//    for (unsigned i = 0; i < ((AdbInstance*)field)->offset / 8; i++) {
//        printf ("%02x ", buf[i]);
//    }
    return ((AdbInstance*)field)->popBuf(buf);
}

/**
 * db_field_set_value
 */
void db_field_set_value(adb_field_t *field, u_int8_t buf[], u_int64_t value)
{
    ((AdbInstance*)field)->pushBuf(buf, value);
}

/**
 * db_field_enum
 */
int db_field_enum(adb_field_t *field, u_int64_t value, char enum_str[])
{
    string s;
    if (((AdbInstance*)field)->intToEnum(value, s)) {
        strcpy(enum_str, s.c_str());
        return 1;
    } else {
        strcpy(enum_str, "");
        return 0;
    }
}

/**
 * db_print_nodes
 */
void db_print_nodes(adb_db_t *db)
{
    int i = 0;

    printf("DB nodes list:\n");
    for (NodesMap::iterator iter = ((Adb*)db)->nodesMap.begin(); iter != ((Adb*)db)->nodesMap.end(); iter++) {
        i++;
        printf("%-5d) %s\n", i, iter->first.c_str());
    }
}
