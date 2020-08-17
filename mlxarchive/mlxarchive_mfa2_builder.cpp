
/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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

/*
 *  mlxarchive_mfa2_builder.cpp
 *
 *  Created on: March 26, 2017
 *      Author: Ahmad Soboh
 */

#include <json/writer.h>
#include <json/reader.h>

#include "mlxfwops/lib/mlxfwops_com.h"
#include "mlxfwops/lib/fw_ops.h"
#include "mlxarchive_mfa2_builder.h"

using namespace mfa2;

#define VERSION_STR             "Version"
#define CREATION_TIME_STR       "Creation Time"
#define COMMENT_STR             "Comment"
#define DEVICEDESCRIPTORS_STR   "Device Descriptors"
#define COMPONENTS_STR          "Components"
#define PSID_STR                "PSID"
#define SOURCE_STR              "Source"

/* MFA2JSONBuilder Class */
MFA2JSONBuilder::MFA2JSONBuilder(const string& jsonString)
{

    Json::Reader reader;

    if (!reader.parse(jsonString, _root)) {
        printf("jsonFile=%s %s\n", jsonString.c_str(), reader.getFormatedErrorMessages().c_str());
        /*throw MFA2Exception("Error parsing the JSON file: %s\n",
                reader.getFormatedErrorMessages().c_str());*/
        printf("Error parsing the JSON file\n");
        return;
    }
    if (!_root.isMember(COMPONENTS_STR)) {
        //TODO throw exception
        printf("no components\n");
    }
    _componentsJSON = _root[COMPONENTS_STR];

    if (!_root.isMember(DEVICEDESCRIPTORS_STR)) {
        //TODO throw exception
        printf("no device descriptors\n");
    }
    _deviceDescriptorsJSON = _root[DEVICEDESCRIPTORS_STR];
}

PackageDescriptor MFA2JSONBuilder::getPackageDescriptor() const
{
    printf("xxxxxxxxxxxxx\n");
    //Version Extension is mandatory
    if (!_root.isMember(VERSION_STR)) {
        //TODO throw exception
    }
    if (!_root.isMember(CREATION_TIME_STR)) {
        //TODO throw exception
    }
    VersionExtension versionExtension(_root[VERSION_STR].asString());

    printf("_deviceDescriptorsJSON.size()=%d\n", _deviceDescriptorsJSON.size());
    PackageDescriptor packageDescriptor(_deviceDescriptorsJSON.size(),
            _componentsJSON.size(), versionExtension);
    //Check if there are any extension that apply to PackageDescriptor
    if (_root.isMember(COMMENT_STR)) {
        CommentExtension* commentExtension =
                new CommentExtension(_root[COMMENT_STR].asString());
        packageDescriptor.addExtension(commentExtension);
    }
    return packageDescriptor;
}

vector<DeviceDescriptor> MFA2JSONBuilder::getDeviceDescriptors() const
{
    vector<DeviceDescriptor> deviceDescriptors;

    for (unsigned int i = 0; i < _deviceDescriptorsJSON.size(); i++) {
        vector<ComponentPointerExtension> componentPointers;

        if (!_deviceDescriptorsJSON[i].isMember(COMPONENTS_STR)) {
            //TODO throw exception: no components
            printf("Components are missing\n");
            exit(1);
        }
        for (unsigned int k = 0; k < _deviceDescriptorsJSON[i][COMPONENTS_STR].size(); k++) {
            bool componentFound = false;
            string name = _deviceDescriptorsJSON[i][COMPONENTS_STR][k].asString();
            int j = 0;
            for (Json::ValueIterator itr = _componentsJSON.begin();
                            itr != _componentsJSON.end(); itr++, j++) {
                Json::Value componentJSON = _componentsJSON[name];
                if (itr.key().asString() == name) {
                    ComponentPointerExtension componentPointer(j);
                    componentPointers.push_back(componentPointer);
                    componentFound = true;
                    break;
                }
            }
            if (!componentFound) {
                //throw excpetion
                printf("Component %s was not found", name.c_str());
                exit(1);
            }
        }

        if (!_deviceDescriptorsJSON[i].isMember(PSID_STR)) {
            //TODO throw exception: no PSID
            printf("PSID is missing\n");
            exit(1);
        }
        PSIDExtension PSID(_deviceDescriptorsJSON[i][PSID_STR].asString());

        DeviceDescriptor deviceDescriptor(componentPointers, PSID);
        deviceDescriptors.push_back(deviceDescriptor);
    }

    return deviceDescriptors;
}

vector<Component> MFA2JSONBuilder::getComponents() const
{
    vector<Component> components;

    for (Json::ValueIterator itr = _componentsJSON.begin();
                itr != _componentsJSON.end(); itr++) {
        string name = itr.key().asString();
        Json::Value componentJSON = _componentsJSON[name];
        //Version Extension is mandatory
        if (!componentJSON.isMember(VERSION_STR)) {
            //TODO throw exception
            printf("version is missing\n");
            exit(1);
        }
        if (!componentJSON.isMember(CREATION_TIME_STR)) {
            //TODO throw exception
            printf("creation time is missing\n");
            exit(1);
        }

        VersionExtension version(componentJSON[VERSION_STR].asString());

        if (!componentJSON.isMember(SOURCE_STR)) {
            //TODO throw exception
            printf("creation time is missing\n");
            exit(1);
        }
        ComponentDescriptor componentDescriptor(version,
                componentJSON[SOURCE_STR].asString());

        //Check optional extensions:
        if (componentJSON.isMember(COMMENT_STR)) {
            CommentExtension* commentExtension =
                    new CommentExtension(componentJSON[COMMENT_STR].asString());
            componentDescriptor.addExtension(commentExtension);
        }

        Component component(componentDescriptor);
        components.push_back(component);
    }

    return components;
}


/* Class FWDirectoryBuilder */

FWDirectoryBuilder::FWDirectoryBuilder(const string& version, string directory) :
                _version(VersionExtension(version)), _directory(directory)
{
    string fileExtension = ".bin";
    vector<string> files;
    int index = 0;
    try
    {
        listDir(directory.c_str(), files);
    }
    catch(std::exception& e)
    {
        std::string err_str = "locale::facet::_S_create_c_locale name not valid";
        if(!err_str.compare(e.what()))
        {
            fprintf(stderr, "Exception: '%s' was catched.\nPlease try to add the following line into your /etc/profile file and retry:\nexport LC_ALL=C; unset LANGUAGE\n"
            "Please note, you need to reload the .profile file, after editing. \nsource /etc/profile might help.\n", e.what());
            exit(1);
        }
        throw e;
    }
    VECTOR_ITERATOR(string, files, file) {
      if ((*file).rfind(fileExtension) == ((*file).size() - fileExtension.size())) {
        string fullPath = directory + "/" + (*file);
        //_files.push_back(fullPath);

        //Query FW Image retrieve version, date, psid info
        char errBuff[1024];
        FwOperations* ops = FwOperations::FwOperationsCreate(
                (void*)fullPath.c_str(), NULL, NULL, FHT_FW_FILE, errBuff,
                1024);
        if (!ops) {
            printf("Can't handle the FW image file %s\n", fullPath.c_str());
            exit(1);
        }
        fw_info_t fwQueryResult;
        if (!ops->FwQuery(&fwQueryResult, true, false)) {
            //throw exception
            printf("Can't query FW image file %s:%s\n", fullPath.c_str(), ops->err());
            exit(1);
        }
        /*FWInfo fwInfo;
        memcpy(fwInfo.version, fwQueryResult.fw_info.fw_ver, sizeof(fwInfo.version));
        memcpy(fwInfo.date, fwQueryResult.fw_info.fw_rel_date, sizeof(fwInfo.date));
        fwInfo.psid = fwQueryResult.fw_info.psid;
        _fwInfo[fullPath] = fwInfo;*/
        //_imgsFwOps[fullPath] = ops;
        vector<ComponentPointerExtension> componentPointers;
        PSIDExtension PSID(fwQueryResult.fw_info.psid);
        ComponentPointerExtension componentPointer(index++);
        componentPointers.push_back(componentPointer);
        DeviceDescriptor deviceDescriptor(componentPointers, PSID);
        _deviceDescriptors.push_back(deviceDescriptor);
        VersionExtension version(fwQueryResult.fw_info.fw_ver, fwQueryResult.fw_info.fw_rel_date);
        vector<u_int8_t> data;
        if (!ops->FwExtract4MBImage(data, true)) {
            printf("Can't Extract FW data from the image file %s:%s\n",
                   fullPath.c_str(), ops->err());
            exit(1);
        }
        ComponentDescriptor componentDescriptor(version, data);
        Component component(componentDescriptor);
        _components.push_back(component);
      }
    }
};

PackageDescriptor FWDirectoryBuilder::getPackageDescriptor() const
{
    PackageDescriptor packageDescriptor(_deviceDescriptors.size(), _components.size(), _version);
    return packageDescriptor;
}

vector<DeviceDescriptor> FWDirectoryBuilder::getDeviceDescriptors() const
{
    return _deviceDescriptors;
    /*vector<DeviceDescriptor> deviceDescriptors;

    CONST_VECTOR_ITERATOR(string, _files, file) {
        PSIDExtension PSID("MT_0000000");
        vector<ComponentPointerExtension> componentPointers;

        ComponentPointerExtension componentPointer(
                distance(_files.begin(), file));
        componentPointers.push_back(componentPointer);
        DeviceDescriptor deviceDescriptor(componentPointers, PSID);
        deviceDescriptors.push_back(deviceDescriptor);
    }

    return deviceDescriptors;*/
}

vector<Component> FWDirectoryBuilder::getComponents() const
{
    return _components;
    /*vector<Component> components;

    CONST_VECTOR_ITERATOR(string, _files, file) {
        VersionExtension version("4.5.666", "20.9.1992");
        vector<u_int8_t> data;
        _imgsFwOps[(*file)]->FwExtract4MBImage(data, false);
        ComponentDescriptor componentDescriptor(version, data);

        Component component(componentDescriptor);
        components.push_back(component);
    }

    return components;*/
}

/*FWDirectoryBuilder::~FWDirectoryBuilder()
{
    VECTOR_ITERATOR(FwOperations*, _imgsFwOps, imgFwOps) {
        if ((*imgFwOps)) {
            (*imgFwOps)->FwCleanUp();
            delete (*imgFwOps);
        }
    }
}*/
