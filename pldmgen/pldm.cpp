/*
 * SPDX-FileCopyrightText: Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: LicenseRef-NvidiaProprietary
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
 */

 #include "pldm.h"

 #include <algorithm>
 #include <fstream>
 
 #include <json/reader.h>
 #include <json/writer.h>
 #include <sys/time.h>
 
 #include "pldm_utils/pldm_utils.h"
 #include "pldm_time.h"
 #include "pldm_descriptor.h"
 #include "pldmlib/pldm_buff.h"
 #include "pldmlib/pldm_pkg.h"
 #include "pldmlib/pldm_dev_id_record.h"
 #include "pldmlib/pldm_record_descriptor.h"
 
 #define PACKAGE_VERSION_STR "Package Version"
 #define PACKAGE_HEADER_FORMAT_REVISION_STR "Package Header Format Revision"
 #define RELEASE_DATE_TIME "Release Date Time"
 #define COMPONENT_STR "Component"
 #define COMPONENTS_STR "Components"
 #define COMPONENT_VERSION_STR "Version Str"
 #define DESCRIPTORS_STR "Descriptors"
 #define SET_VERSION_STR "Set Version"
 #define DEVICERECORDS_STR "Device Records"
 #define DEVICERECORD_OPTION_STR "Options"
 
 #define PACKAGE_VERSION_STR_MAX_SIZE 255
 
 using namespace std;
 
 unsigned int crc32(unsigned char* message, unsigned int size)
 {
     unsigned int i, j;
     unsigned int byte, crc, mask;
 
     i = 0;
     crc = 0xFFFFFFFF;
     while (i < size)
     {
         byte = message[i]; // Get next byte.
         crc = crc ^ byte;
         for (j = 8; j > 0; j--)
         { // Do eight times.
             mask = -(crc & 1);
             crc = (crc >> 1) ^ (0xEDB88320 & mask);
         }
         i = i + 1;
     }
     return ~crc;
 }
 
 static u_int32_t parseComparisonStamp(const Json::Value& componentJSON, const string& name)
 {
     const u_int8_t COMPARISON_STAMP_BYTES_LEN = 4;
     string stampStr = GetStringFromJson(componentJSON, COMPONENT_COMPARISON_STAMP_STR, "");
     // Empty or absent comparison stamp defaults to 0xffffffff ("always update" sentinel).
     if (stampStr.empty())
     {
         return 0xffffffff;
     }
     if (!ValidSizeAndFormat(stampStr, COMPARISON_STAMP_BYTES_LEN))
     {
         throw PLDMException(
           "Invalid value for comparison stamp in %s component. It must be in hexadecimal format and no more than %d bytes in length.\n",
           name.c_str(), COMPARISON_STAMP_BYTES_LEN);
     }
     u_int32_t comparisonStamp;
     if (!mft_utils::strToNum(stampStr, comparisonStamp))
     {
         throw PLDMException("Comparison stamp string %s is not valid\n", stampStr.c_str());
     }
 
     return comparisonStamp;
 }
 
 PLDM::PLDM(const string& cookBook, bool recovery)
 {
     Json::Value root, componentsJSON, deviceRecordsJSON;
     nbu::mft::common::ReaderWrapper readerwrapper;
     Json::Reader* reader = readerwrapper.getReader();
     bool parsingSuccessful = reader->parse(cookBook, root);
     if (!parsingSuccessful)
     {
         throw PLDMException("Error parsing the cookbook file: %s\n", reader->getFormattedErrorMessages().c_str());
         return;
     }
 
     // parse the package version
     _packageVersion = GetStringFromJson(root, PACKAGE_VERSION_STR);
     if (_packageVersion.length() > PACKAGE_VERSION_STR_MAX_SIZE)
     {
         throw PLDMException("Package version string %s is not valid, "
                             "Max length is 255 chars",
                             _packageVersion.c_str());
     }
 
    u_int32_t packageHeaderFormatRevision = 0x0;
    const string packageHeaderFormatRevisionStr = GetStringFromJson(root, PACKAGE_HEADER_FORMAT_REVISION_STR, "0x1");
    if (!mft_utils::strToNum(packageHeaderFormatRevisionStr, packageHeaderFormatRevision))
     {
        throw PLDMException("Package header format revision string %s is not valid\n",
                            packageHeaderFormatRevisionStr.c_str());
     }
     packageHeaderFormatRevision = packageHeaderFormatRevision == 0x0 ? 0x1 : packageHeaderFormatRevision;
     // check if the package header format revision is supported
     if (PACKAGE_HEADER_FORMAT_REVISION_MAP.find(packageHeaderFormatRevision) == PACKAGE_HEADER_FORMAT_REVISION_MAP.end())
     {
         throw PLDMException("Package header format revision %d is not supported\n", packageHeaderFormatRevision);
     }
     _packageHeaderFormatRevision = packageHeaderFormatRevision;
 
     // parse the release date time
     _releaseDateTime = GetStringFromJson(root, RELEASE_DATE_TIME);
 
     // parse the components
     componentsJSON = root[COMPONENTS_STR];
     for (Json::ValueIterator itr = componentsJSON.begin(); itr != componentsJSON.end(); itr++)
     {
         string name = itr.key().asString();
         Json::Value componentJSON = componentsJSON[name];
 
         string strComponentIdentifier = GetStringFromJson(componentJSON, IDENTIFIER_STR);
         strComponentIdentifier = (strComponentIdentifier.empty()) ? "FW" : strComponentIdentifier;
         ComponentIdentifier componentIdentifier = ComponentIdentifier::Identifier_Not_Valid;
         StringToComponentIdentifier(strComponentIdentifier, componentIdentifier);
 
         string fwSource = GetStringFromJson(componentJSON, SOURCE_STR);
         if (fwSource.empty())
         {
             throw PLDMException("The cookbook must include source for all components.");
         }
 
         if ((componentIdentifier == ComponentIdentifier::Identifier_FW_Comp ||
              componentIdentifier == ComponentIdentifier::Identifier_NIC_FW_Comp ||
              componentIdentifier == ComponentIdentifier::Identifier_FW_SPC6_Comp) &&
             !recovery)
         {
             fwSource = PLDMComponent::extractFwData(fwSource);
         }
 
         u_int32_t comparisonStamp = parseComparisonStamp(componentJSON, name);
 
         _components.push_back(PLDMComponent(name,
                                             fwSource,
                                             GetStringFromJson(componentJSON, VERSION_STR),
                                             componentIdentifier,
                                             GetStringFromJson(componentJSON, COMPONENT_OPTIONS_STR),
                                             GetStringFromJson(componentJSON, COMPONENT_ACTIVATION_METHOD_STR),
                                             comparisonStamp));
     }
     if (!_components.size())
     {
         throw PLDMException("The cookbook must include at least one component.");
     }
 
     // component Bitmap Length must be byte aligned (multiple of 8)
     _componentBitmapLength = 8 * ((_components.size() + 7) / 8);
 
     // parse the device records
     deviceRecordsJSON = root[DEVICERECORDS_STR];
     for (unsigned int i = 0; i < deviceRecordsJSON.size(); i++)
     {
         vector<u_int8_t> appliedComponents(_componentBitmapLength / 8);
         vector<PLDMDescriptor> descriptors;
 
         // parse applied components
         for (unsigned int j = 0; j < deviceRecordsJSON[i][COMPONENTS_STR].size(); j++)
         {
             bool componentFound = false;
             string componentName = deviceRecordsJSON[i][COMPONENTS_STR][j].asString();
             for (unsigned int k = 0; k < _components.size(); k++)
             {
                 if (_components[k]._name == componentName)
                 {
                     appliedComponents[k / 8] |= (1 << (k % 8));
                     componentFound = true;
                 }
             }
             if (!componentFound)
             {
                 throw PLDMException("Component %s was not found in the defined "
                                     "components list",
                                     componentName.c_str());
             }
         }
 
         // parse descriptors
         for (unsigned int j = 0; j < deviceRecordsJSON[i][DESCRIPTORS_STR].size(); j++)
         {
             for (Json::ValueIterator itr = deviceRecordsJSON[i][DESCRIPTORS_STR][j].begin();
                  itr != deviceRecordsJSON[i][DESCRIPTORS_STR][j].end();
                  itr++)
             {
                 string type = itr.key().asString();
                 string val = deviceRecordsJSON[i][DESCRIPTORS_STR][j][type].asString();
 
                 // if default value is set, use the default value
                 if (val == "DEFAULT_VALUE")
                 {
                     if (!PLDMDescriptor::IsDefaultValue(type))
                     {
                         throw PLDMException("The descriptor type '%s' cannot have 'DEFAULT_VALUE' as its value.",
                                             type.c_str());
                     }
                     string default_value = PLDMDescriptor::GetDefaultValue(type);
                     val = default_value;
                 }
 
                 descriptors.push_back(PLDMDescriptor(type, val));
             }
         }
 
         PLDMDeviceRecord deviceRecord(GetStringFromJson(deviceRecordsJSON[i], SET_VERSION_STR),
                                       GetStringFromJson(deviceRecordsJSON[i], DEVICERECORD_OPTION_STR),
                                       appliedComponents,
                                       descriptors);
         _deviceRecords.push_back(deviceRecord);
     }
     if (!_deviceRecords.size())
     {
         throw PLDMException("The cookbook must include at least one device record.");
     }
 }
 
 void PLDM::Pack(vector<u_int8_t>& buff)
 {
     u_int32_t headerSizeFieldOffset, checksumFieldOffset;
 
     // PackageHeaderIdentifier
     for (auto& identifier : PACKAGE_HEADER_FORMAT_REVISION_MAP.at(_packageHeaderFormatRevision))
     {
         dumpUInt8(buff, identifier);
     }
 
     // PackageHeaderFormatRevision
     dumpUInt8(buff, (u_int8_t)_packageHeaderFormatRevision);
 
     // PackageHeaderSize: save the current offset
     headerSizeFieldOffset = buff.size();
     dumpUInt16(buff, 0x0);
 
     // TODO: timestamp104 (13 bytes)
     dumpTimeStamp104(buff, _releaseDateTime);
 
     // ComponentBitmapBitLength
     dumpUInt16(buff, _componentBitmapLength);
 
     // PackageVersionStringType
     dumpUInt8(buff, VERSION_STRING_TYPE_ASCII);
 
     // PackageVersionStringLength
     dumpUInt8(buff, _packageVersion.length());
 
     // PackageVersionString
     dumpString(buff, _packageVersion);
 
     // DeviceIDRecordCount
     dumpUInt8(buff, _deviceRecords.size());
 
     // dump FirmwareDeviceIDRecords
     for (unsigned int i = 0; i < _deviceRecords.size(); i++)
     {
         _deviceRecords[i].Pack(buff);
     }
     // if package header format revision is greater than 0x1, the package support downstream device record
     if (_packageHeaderFormatRevision >= FIRST_REVISION_SUPPORTED_DOWNSTREAM_DEVICES)
     {
         // DownStream Device Record Count
         dumpUInt8(buff, 0x0);
     }
 
     // ComponentImageCount
     dumpUInt16(buff, _components.size());
 
     // dump ComponentImageInformation
     for (unsigned int i = 0; i < _components.size(); i++)
     {
         _components[i].ComponentInfoPack(buff);
     }
 
     // save the checksum offset
     checksumFieldOffset = buff.size();
     dumpUInt32(buff, 0x0); // will be back-patched later
 
     // set the header size before dumping the components data
     ((u_int16_t*)(buff.data() + headerSizeFieldOffset))[0] = __cpu_to_le16(buff.size());
 
     // dump the components data
     for (unsigned int i = 0; i < _components.size(); i++)
     {
         // BackPatch the component's offset in the ComponentInforamtion
         _components[i].SetComponentLocationOffset(buff, buff.size());
         // Pack the data of the component
         _components[i].ComponentDataPack(buff);
     }
 
     // calculate the checksum
     ((u_int32_t*)(buff.data() + checksumFieldOffset))[0] =
       __cpu_to_le32(crc32((unsigned char*)buff.data(), checksumFieldOffset));
 }
 
 void PLDM::AddComponentsValues(Json::Value& componentAttr)
 {
     componentAttr[SOURCE_STR] = "";
     componentAttr[VERSION_STR] = "";
     componentAttr[COMPONENT_COMPARISON_STAMP_STR] = "";
     componentAttr[COMPONENT_OPTIONS_STR] = "";
     componentAttr[COMPONENT_ACTIVATION_METHOD_STR] = "";
 }
 
 string PLDM::FindComponentNameByIdentifier(const string& identifier, const Json::Value& components)
 {
     if (!components.isObject())
     {
         return "";
     }
 
     const std::vector<std::string> memberNames = components.getMemberNames();
     for (const std::string& name : memberNames)
     {
         const Json::Value& idValue = components[name][IDENTIFIER_STR];
         if (idValue.isString() && idValue.asString() == identifier)
         {
             return name;
         }
     }
     return "";
 }
 
 // Adds a new component to the components JSON object.
 // - If reuseComponents is true and a component with the given identifier already exists,
 //   returns its existing name instead of creating a new entry.
 // - Otherwise, increments the component counter, generates a new component name
 //   adds a new entry to components with default attributes, and returns the new name.
 // The returned component name can later be used to associate the component in device records.
 string PLDM::AddComponent(const std::string& identifier,
                           int& componentCounter,
                           Json::Value& components,
                           bool reuseComponents)
 {
     if (reuseComponents)
     {
         string existingName = FindComponentNameByIdentifier(identifier, components);
         if (!existingName.empty())
         {
             return existingName;
         }
     }
 
     Json::Value componentAttr;
     AddComponentsValues(componentAttr);
     componentAttr[IDENTIFIER_STR] = identifier;
 
     const string newName = COMPONENT_STR " " + NumToStr(componentCounter);
     components[newName] = componentAttr;
     componentCounter++;
     return newName;
 }
 
 static vector<string> GetOrderedDescriptorNames(const Json::Value& descriptors, bool keepDescriptorsOrder)
 {
     vector<string> givenNames;
     if (descriptors.isArray() && !descriptors.empty())
     {
         for (unsigned int j = 0; j < descriptors.size(); j++)
         {
             givenNames.push_back(PLDMDescriptor::ValidAndNormalizeValue(descriptors[j].asString()));
         }
     }
     vector<string> orderedNames;
     if (keepDescriptorsOrder)
     {
         orderedNames = givenNames;
     }
     else
     {
         for (const auto& entry : DESCRIPTOR_TYPE_LIST)
         {
             if (std::find(givenNames.begin(), givenNames.end(), entry.first) != givenNames.end())
             {
                 orderedNames.push_back(entry.first);
             }
         }
     }
 
     return orderedNames;
 }
 
 void PLDM::GenerateEmptyCookBookFromJson(const string& json, bool reuseComponents, const string& fname, bool keepDescriptorsOrder)
 {
     Json::Value root;
     std::ifstream jsonStream(json);
     if (!jsonStream)
     {
         throw PLDMException("Error opening the cookbook file: %s\n", json.c_str());
         return;
     }
 
     nbu::mft::common::ReaderWrapper readerwrapper;
     Json::Reader* reader = readerwrapper.getReader();
     reader->parse(jsonStream, root);
 
     // init the structure of the empty cookbook
     Json::Value pldmJSON;
     pldmJSON[DEVICERECORDS_STR] = Json::Value(Json::arrayValue);
     pldmJSON[COMPONENTS_STR] = Json::Value(Json::objectValue);
     pldmJSON[PACKAGE_VERSION_STR] = "";
     pldmJSON[RELEASE_DATE_TIME] = "";
 
     Json::Value deviceRecords = root[DEVICERECORDS_STR];
     int componentCounter = 0;
     for (unsigned int i = 0; i < deviceRecords.size(); i++)
     {
         Json::Value deviceRecordAttr;
         deviceRecordAttr[SET_VERSION_STR] = "";
         deviceRecordAttr[DEVICERECORD_OPTION_STR] = "";
         deviceRecordAttr[DESCRIPTORS_STR] = Json::Value(Json::arrayValue);
         deviceRecordAttr[COMPONENTS_STR] = Json::Value(Json::arrayValue);
 
         Json::Value componentsNames = deviceRecords[i]["Components"];
         for (unsigned int j = 0; j < componentsNames.size(); j++)
         {
             string identifier = componentsNames[j].asString();
             identifier = ValidAndNormalizeComponentIdentifier(identifier);
             const string compName =
               AddComponent(identifier, componentCounter, pldmJSON[COMPONENTS_STR], reuseComponents);
             deviceRecordAttr[COMPONENTS_STR].append(compName);
         }
 
         Json::Value descriptors = deviceRecords[i]["Descriptors"];
 
         // Append descriptors to device record
         for (const auto& name : GetOrderedDescriptorNames(descriptors, keepDescriptorsOrder))
         {
             Json::Value descriptor;
             descriptor[name] = PLDMDescriptor::IsDefaultValue(name) ? "DEFAULT_VALUE" : "";
             deviceRecordAttr[DESCRIPTORS_STR].append(descriptor);
         }
         pldmJSON[DEVICERECORDS_STR].append(deviceRecordAttr);
     }
     // pldmJSON[COMPONENTS_STR] =  components;
     Json::StyledWriter writer;
     string doc = writer.write(pldmJSON);
     if (!WriteToFile(fname, doc))
     {
         throw PLDMException("Cannot write to file %s", fname.c_str());
     }
 }

void PLDM::DisableCustomPsid(const string& inputFile, const string& outputFile, const string& psid)
{
    PldmBuffer buff;
    if (!buff.loadFile(inputFile))
    {
        throw PLDMException("Failed to load input file: %s", inputFile.c_str());
    }
    PldmPkg pkg;
    if (!pkg.unpack(buff))
    {
        throw PLDMException("Failed to parse PLDM package from: %s", inputFile.c_str());
    }

    // if psid emty the first FD will be taken
    PldmDevIdRecord* rec = pkg.findRecordByPsid(psid);
    if (rec == NULL)
    {
        throw PLDMException("PSID '%s' not found in package.", psid.c_str());
    }
    PldmRecordDescriptor* psidDesc = rec->findVendorDefinedDescriptor(PldmRecordDescriptor::VendorDefinedType::PSID);
    if (psidDesc == NULL)
    {
        throw PLDMException("No PSID descriptor in selected device record.");
    }

    // Position of the "minor" digit within the PSID value buffer (from start of value).
    // Per PSID-format spec from architecture: bytes [5] and [6] are the minor digits.
    const size_t PSID_MINOR_OFFSET = 5;

    u_int16_t valueLen = psidDesc->getValueLength();
    u_int8_t* value = psidDesc->getMutableValue();
    if (value == NULL || valueLen == 0 || PSID_MINOR_OFFSET + 1 >= valueLen)
    {
        throw PLDMException("PSID value too short (length=%u) for minor edit at offset %zu.", (unsigned)valueLen,
                            PSID_MINOR_OFFSET);
    }
    // Zero the two minor digits.
    value[PSID_MINOR_OFFSET] = '0';
    value[PSID_MINOR_OFFSET + 1] = '0';

    if (!psidDesc->pack(buff))
    {
        throw PLDMException("Failed to pack modified PSID descriptor back into buffer.");
    }
    if (!pkg.recomputeHeaderChecksum(buff))
    {
        throw PLDMException("Failed to recompute package header checksum.");
    }
    if (!buff.saveFile(outputFile))
    {
        throw PLDMException("Failed to write output file: %s", outputFile.c_str());
    }
}
