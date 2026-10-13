/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

 #include "pldm.h"

 #include <algorithm>
 #include <cstdio>
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
 #include "common/tools_endianness.h"
 
 #define PACKAGE_VERSION_STR "Package Version"
 #define PACKAGE_HEADER_FORMAT_REVISION_STR "Package Header Format Revision"
 #define RELEASE_DATE_TIME "Release Date Time"
 #define COMPONENT_STR "Component"
 #define COMPONENTS_STR "Components"
 #define COMPONENT_VERSION_STR "Version Str"
 #define DESCRIPTORS_STR "Descriptors"
 #define SET_VERSION_STR "Set Version"
 #define DEVICERECORDS_STR "Device Records"
 #define DOWNSTREAM_DEVICES_STR "Downstream Device Records"
 #define DEVICERECORD_STR "Device Record"
 #define DEVICERECORD_OPTION_STR "Options"
 #define MIN_VERSION_COMPARISON_STAMP_STR "Min Version Comparison Stamp"
 
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
 
 static u_int32_t
   parseHexStamp(const Json::Value& json, const string& contextName, const char* keyName, u_int32_t defaultVal)
 {
     const u_int8_t STAMP_BYTES_LEN = 4;
     string stampStr = GetStringFromJson(json, keyName, "");
     if (stampStr.empty())
     {
         return defaultVal;
     }
     if (!ValidSizeAndFormat(stampStr, STAMP_BYTES_LEN))
     {
         throw PLDMException(
           "Invalid value for %s in %s. It must be in hexadecimal format and no more than %d bytes in length.\n",
           keyName, contextName.c_str(), STAMP_BYTES_LEN);
     }
     // Normalize bare "0x"/"0X" (empty hex after stripping prefix) to "0x0" so strToNum succeeds.
     string normalizedStamp = stampStr;
     if (normalizedStamp.size() == 2 && normalizedStamp[0] == '0' && tolower(normalizedStamp[1]) == 'x')
     {
         normalizedStamp += "0";
     }
     u_int32_t stamp;
     if (!mft_utils::strToNum(normalizedStamp, stamp))
     {
         throw PLDMException("%s string %s is not valid\n", keyName, stampStr.c_str());
     }
     return stamp;
 }

 static u_int32_t parseComparisonStamp(const Json::Value& componentJSON, const string& name)
 {
     // Empty or absent comparison stamp defaults to 0xffffffff ("always update" sentinel).
     return parseHexStamp(componentJSON, name, COMPONENT_COMPARISON_STAMP_STR, 0xffffffff);
 }
 
 void PLDM::ParseCommonRecordFields(const Json::Value& deviceRecord,
                                    vector<u_int8_t>& appliedComponents,
                                    vector<PLDMDescriptor>& descriptors)
 {
     for (unsigned int j = 0; j < deviceRecord[COMPONENTS_STR].size(); j++)
     {
         bool componentFound = false;
         string componentName = deviceRecord[COMPONENTS_STR][j].asString();
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

     for (unsigned int j = 0; j < deviceRecord[DESCRIPTORS_STR].size(); j++)
     {
         for (Json::ValueConstIterator itr = deviceRecord[DESCRIPTORS_STR][j].begin();
              itr != deviceRecord[DESCRIPTORS_STR][j].end();
              itr++)
         {
             string type = itr.key().asString();
             string val = deviceRecord[DESCRIPTORS_STR][j][type].asString();

             if (val == "DEFAULT_VALUE")
             {
                 if (!PLDMDescriptor::IsDefaultValue(type))
                 {
                     throw PLDMException("The descriptor type '%s' cannot have 'DEFAULT_VALUE' as its value.",
                                         type.c_str());
                 }
                 val = PLDMDescriptor::GetDefaultValue(type);
             }

             descriptors.push_back(PLDMDescriptor(type, val));
         }
     }
 }

 PLDMDeviceRecord PLDM::ParseDeviceRecord(const Json::Value& deviceRecord)
 {
     vector<u_int8_t> appliedComponents(_componentBitmapLength / 8);
     vector<PLDMDescriptor> descriptors;
     ParseCommonRecordFields(deviceRecord, appliedComponents, descriptors);

     return PLDMDeviceRecord(GetStringFromJson(deviceRecord, SET_VERSION_STR),
                             GetStringFromJson(deviceRecord, DEVICERECORD_OPTION_STR),
                             appliedComponents,
                             descriptors);
 }

 static void validateDownstreamStampConsistency(const Json::Value& deviceRecord)
 {
     const string optionsStr = GetStringFromJson(deviceRecord, DEVICERECORD_OPTION_STR, "");
     u_int32_t updateOptionFlags = 0x0;
     if (!optionsStr.empty() && !mft_utils::strToNum(optionsStr, updateOptionFlags))
     {
         throw PLDMException("Invalid downstream record Options value: %s", optionsStr.c_str());
     }
     // Stamp is only serialized when the downstream device supports self-contained activation (bit0 set in option).
     const bool selfContainedActivation = (updateOptionFlags & DOWNSTREAM_SELF_CONTAINED_ACTIVATION_BIT) != 0;
     const bool stampPresent = !GetStringFromJson(deviceRecord, MIN_VERSION_COMPARISON_STAMP_STR, "").empty();
     if (stampPresent && !selfContainedActivation)
     {
         throw PLDMException("Downstream record has '%s' but DOWNSTREAM_SELF_CONTAINED_ACTIVATION_BIT (bit0) "
                             "is not set in Options - stamp would be silently dropped.",
                             MIN_VERSION_COMPARISON_STAMP_STR);
     }
 }

 PLDMDownstreamDeviceRecord PLDM::ParseDownstreamDeviceRecord(const Json::Value& deviceRecord)
 {
     vector<u_int8_t> appliedComponents(_componentBitmapLength / 8);
     vector<PLDMDescriptor> descriptors;
     ParseCommonRecordFields(deviceRecord, appliedComponents, descriptors);

     validateDownstreamStampConsistency(deviceRecord);

     const u_int32_t minVersionComparisonStamp =
       parseHexStamp(deviceRecord, "downstream device record", MIN_VERSION_COMPARISON_STAMP_STR, 0);

     return PLDMDownstreamDeviceRecord(GetStringFromJson(deviceRecord, SET_VERSION_STR),
                                       GetStringFromJson(deviceRecord, DEVICERECORD_OPTION_STR),
                                       appliedComponents,
                                       descriptors,
                                       minVersionComparisonStamp);
 }

 bool PLDM::IsDownstreamComponent(const std::string& componentName, const Json::Value& root) const
 {
     Json::Value downstreamDevices = root[DOWNSTREAM_DEVICES_STR];
     if (downstreamDevices.empty())
     {
         return false;
     }
     for (unsigned int i = 0; i < downstreamDevices.size(); i++)
     {
         const Json::Value& components = downstreamDevices[i][COMPONENTS_STR];
         for (unsigned int j = 0; j < components.size(); j++)
         {
             if (components[j].asString() == componentName)
             {
                 return true;
             }
         }
     }
     return false;
 }

 PLDM::PLDM(const string& cookBook, bool recovery)
 {
     Json::Value root, componentsJSON, deviceRecordsJSON, downstreamDevicesJSON;
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
                                             comparisonStamp,
                                             // For Downstream Components, the classification is 0xFFFF
                                             IsDownstreamComponent(name, root) ? "0xFFFF" : ""));
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
         _deviceRecords.push_back(ParseDeviceRecord(deviceRecordsJSON[i]));
     }

     // parse the downstream devices
     downstreamDevicesJSON = root[DOWNSTREAM_DEVICES_STR];
     if (!downstreamDevicesJSON.empty() && _packageHeaderFormatRevision < FIRST_REVISION_SUPPORTED_DOWNSTREAM_DEVICES)
     {
         throw PLDMException("Cookbook contains downstream device records but Package Header Format Revision "
                             "is 0x%x; downstream records require revision >= 0x%x.",
                             _packageHeaderFormatRevision, FIRST_REVISION_SUPPORTED_DOWNSTREAM_DEVICES);
     }
     for (unsigned int i = 0; i < downstreamDevicesJSON.size(); i++)
     {
         _downstreamDevices.push_back(ParseDownstreamDeviceRecord(downstreamDevicesJSON[i]));
     }

     if (!_deviceRecords.size() && !_downstreamDevices.size())
     {
         throw PLDMException("The cookbook must include at least one device record or downstream device.");
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
         dumpUInt8(buff, static_cast<u_int8_t>(_downstreamDevices.size()));
         // dump DownStream Device Records
         for (unsigned int i = 0; i < _downstreamDevices.size(); i++)
         {
             _downstreamDevices[i].Pack(buff);
         }
     }
 
     // ComponentImageCount
     dumpUInt16(buff, _components.size());
 
     // dump ComponentImageInformation
     for (unsigned int i = 0; i < _components.size(); i++)
     {
         _components[i].ComponentInfoPack(buff, _packageHeaderFormatRevision);
     }
 
     // save the checksum offset
     checksumFieldOffset = buff.size();
     dumpUInt32(buff, 0x0); // will be back-patched later
 
     // set the header size before dumping the components data
     ((u_int16_t*)(buff.data() + headerSizeFieldOffset))[0] = mft_cpu_to_le16(buff.size());
 
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
       mft_cpu_to_le32(crc32((unsigned char*)buff.data(), checksumFieldOffset));
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
 
 Json::Value PLDM::BuildDeviceRecordFromJson(const Json::Value& deviceRecord,
                                             int& componentCounter,
                                             Json::Value& components,
                                             bool reuseComponents,
                                             bool keepDescriptorsOrder,
                                             bool isDownstream)
 {
     Json::Value deviceRecordAttr;
     deviceRecordAttr[SET_VERSION_STR] = "";
     deviceRecordAttr[DEVICERECORD_OPTION_STR] = "";
     if (isDownstream)
     {
         deviceRecordAttr[MIN_VERSION_COMPARISON_STAMP_STR] = "";
     }
     deviceRecordAttr[DESCRIPTORS_STR] = Json::Value(Json::arrayValue);
     deviceRecordAttr[COMPONENTS_STR] = Json::Value(Json::arrayValue);

     Json::Value componentsNames = deviceRecord[COMPONENTS_STR];
     for (unsigned int i = 0; i < componentsNames.size(); i++)
     {
         string identifier = componentsNames[i].asString();
         identifier = ValidAndNormalizeComponentIdentifier(identifier);
         const string compName = AddComponent(identifier, componentCounter, components, reuseComponents);
         deviceRecordAttr[COMPONENTS_STR].append(compName);
     }

     Json::Value descriptors = deviceRecord[DESCRIPTORS_STR];

     // Append descriptors to device record
     for (const auto& name : GetOrderedDescriptorNames(descriptors, keepDescriptorsOrder))
     {
         Json::Value descriptor;
         descriptor[name] = PLDMDescriptor::IsDefaultValue(name) ? "DEFAULT_VALUE" : "";
         deviceRecordAttr[DESCRIPTORS_STR].append(descriptor);
     }

     return deviceRecordAttr;
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
         pldmJSON[DEVICERECORDS_STR].append(BuildDeviceRecordFromJson(deviceRecords[i],
                                                                      componentCounter,
                                                                      pldmJSON[COMPONENTS_STR],
                                                                      reuseComponents,
                                                                      keepDescriptorsOrder,
                                                                      /*isDownstream=*/false));
     }

     Json::Value downstreamDevices = root[DOWNSTREAM_DEVICES_STR];
     if (!downstreamDevices.empty())
     {
         pldmJSON[DOWNSTREAM_DEVICES_STR] = Json::Value(Json::arrayValue);
         for (unsigned int i = 0; i < downstreamDevices.size(); i++)
         {
             pldmJSON[DOWNSTREAM_DEVICES_STR].append(BuildDeviceRecordFromJson(downstreamDevices[i],
                                                                               componentCounter,
                                                                               pldmJSON[COMPONENTS_STR],
                                                                               reuseComponents,
                                                                               keepDescriptorsOrder,
                                                                               /*isDownstream=*/true));
         }
     }
     // pldmJSON[COMPONENTS_STR] =  components;
     Json::StyledWriter writer;
     string doc = writer.write(pldmJSON);
     if (!WriteToFile(fname, doc))
     {
         throw PLDMException("Cannot write to file %s", fname.c_str());
     }
 }

// Write `count` bytes into the selected record's vendor-defined descriptor of `type` at `offset`,
// then repack it into the buffer.
static bool setVendorDescriptorBytes(PldmDevIdRecord* rec,
                                     PldmRecordDescriptor::VendorDefinedType type,
                                     size_t offset,
                                     const u_int8_t* bytes,
                                     size_t count,
                                     PldmBuffer& buff)
{
    PldmRecordDescriptor* desc = rec->findVendorDefinedDescriptor(type);
    if (desc == NULL)
    {
        return false;
    }
    u_int8_t* value = desc->getMutableValue();
    if (value == NULL || desc->getValueLength() < offset + count)
    {
        return false;
    }
    for (size_t i = 0; i < count; i++)
    {
        value[offset + i] = bytes[i];
    }
    if (!desc->pack(buff))
    {
        throw PLDMException("Failed to pack modified descriptor back into buffer.");
    }
    return true;
}

void PLDM::DisableCustomPsid(const string& inputFile,
                             const string& outputFile,
                             const string& psid,
                             const string& minorVersion)
{
    // Convert the validated minor value to a single byte; both the PSID (ASCII) and the
    // APSKU (numeric) edits use this one byte.
    u_int32_t minorNum = 0;
    if (!mft_utils::strToNum(minorVersion, minorNum, 16) || minorNum > 0xFF)
    {
        throw PLDMException("Invalid minor version '%s'; expected a hex byte (00-FF).", minorVersion.c_str());
    }
    u_int8_t minorByte = (u_int8_t)minorNum;
    char minorHex[3];
    snprintf(minorHex, sizeof(minorHex), "%02X", minorByte);

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

    // Set the PSID minor digits (uppercase ASCII hex of the chosen byte).
    // Per PSID-format spec from architecture: bytes [5] and [6] are the minor digits.
    const size_t PSID_MINOR_OFFSET = 5;
    // Convert the minor version to two bytes (ASCII hex of the chosen byte)
    u_int8_t psidMinor[2] = {(u_int8_t)minorHex[0], (u_int8_t)minorHex[1]};
    if (!setVendorDescriptorBytes(rec, PldmRecordDescriptor::VendorDefinedType::PSID, PSID_MINOR_OFFSET, psidMinor, 2,
                                  buff))
    {
        throw PLDMException("No PSID descriptor in selected record, or PSID value too short for minor edit.");
    }

    // Keep the APSKU descriptor's minor byte consistent. APSKU is stored little-endian, so its
    // most-significant byte (offset 3) tracks the PSID minor. An absent/short APSKU is skipped.
    const size_t APSKU_MINOR_BYTE_OFFSET = 3;
    if (!setVendorDescriptorBytes(rec, PldmRecordDescriptor::VendorDefinedType::APSKU, APSKU_MINOR_BYTE_OFFSET,
                                  &minorByte, 1, buff))
    {
        printf("-I- APSKU descriptor absent or too short in selected record; APSKU byte not updated.\n");
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
