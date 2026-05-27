/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

 #include "pldm_component.h"
 #include "pldm_utils/pldm_utils.h"
 #include "pldm_descriptor.h"
 
 #include <sys/stat.h>
 
 #include <fstream>
 #include <sstream>
 #include "mlxfwops/lib/fw_ops.h"
 
 #define OPTIONS_BYTES_LEN 2
 #define ACTIVATION_METHOD_BYTES_LEN 2
 
 using namespace std;
 
 void PLDMComponent::ParseHexField(const string& value,
                                   ComponentField fieldId,
                                   u_int8_t maxBytes,
                                   const char* fieldName,
                                   u_int16_t& out) const
 {
     if (value.empty())
     {
         ComponentIdentifierToValue(_identifier, fieldId, out);
         return;
     }
     if (!ValidSizeAndFormat(value, maxBytes))
     {
         throw PLDMException(
           "Invalid value for %s in %s. It must be in hexadecimal format and no more than %d bytes in length.\n",
           fieldName,
           _name.c_str(),
           maxBytes);
     }
     std::istringstream(value) >> std::hex >> out;
 }
 
 PLDMComponent::PLDMComponent(const string& name,
                              const string& src,
                              const string& version,
                              ComponentIdentifier componentIdentifier,
                              const string& options,
                              const string& activationMethod,
                              u_int32_t comparisonStamp) :
     _name(name),
     _src(src),
     _version(version),
     _identifier(componentIdentifier),
     _offsetOfComponentDataOffset(0),
     _comparisonStamp(comparisonStamp)
 {
     ParseHexField(options, ComponentField::Options, OPTIONS_BYTES_LEN, "options", _options);
     ParseHexField(activationMethod,
                   ComponentField::ActivationMethod,
                   ACTIVATION_METHOD_BYTES_LEN,
                   "activation method",
                   _activationMethod);
 }
 
 void PLDMComponent::ComponentInfoPack(vector<u_int8_t>& buff)
 {
     // ComponentClassification
     u_int16_t classificationValue = 0x0;
     ComponentIdentifierToValue(_identifier, ComponentField::Classification, classificationValue);
     dumpUInt16(buff, classificationValue);
 
     // ComponentIdentifier
     u_int16_t identifierValue = 0x0;
     ComponentIdentifierToValue(_identifier, ComponentField::Identifier, identifierValue);
     dumpUInt16(buff, identifierValue);
 
     // ComponentComparisonStamp
     dumpUInt32(buff, _comparisonStamp);
 
     // ComponentOptions
     dumpUInt16(buff, _options);
 
     // RequestedComponentActivationMethod
     dumpUInt16(buff, _activationMethod);
 
     // ComponentLocationOffset
     _offsetOfComponentDataOffset = buff.size();
     dumpUInt32(buff, 0x0); // will be back-patched later
 
     // ComponentSize
     dumpUInt32(buff, ComponentDataSize());
 
     // ComponentVersionStringType
     dumpUInt8(buff, VERSION_STRING_TYPE_ASCII);
 
     // ComponentVersionStringLength
     dumpUInt8(buff, _version.length());
 
     // ComponentVersionString
     dumpString(buff, _version);
 }
 
 void PLDMComponent::ComponentDataPack(vector<u_int8_t>& buff)
 {
     vector<u_int8_t> fileBuff;
     streampos size;
 
     std::ifstream ifs(_src.c_str(), ios::in | ios::binary | ios::ate);
 
     if (ifs.fail())
     {
         throw PLDMException("Failed to open file: %s", _src.c_str());
     }
     size = ifs.tellg();
     fileBuff.resize((size_t)size);
     ifs.seekg(0, ios::beg);
     ifs.read((char*)fileBuff.data(), size);
     ifs.close();
 
     for (unsigned int i = 0; i < fileBuff.size(); i++)
     {
         buff.push_back(fileBuff[i]);
     }
 }
 
 u_int32_t PLDMComponent::ComponentDataSize()
 {
     int rc;
     struct stat stat_buf;
 
     rc = stat(_src.c_str(), &stat_buf);
 
     if (!rc)
     {
         // printf("stat_buf.st_size=%d\n", stat_buf.st_size);
         return stat_buf.st_size;
     }
 
     throw PLDMException("Cannot get the size of the file %s", _src.c_str());
 }
 
 void PLDMComponent::SetComponentLocationOffset(vector<u_int8_t>& buff, u_int32_t value)
 {
     ((u_int32_t*)(buff.data() + _offsetOfComponentDataOffset))[0] = __cpu_to_le32(value);
 }
 
 string PLDMComponent::extractFwData(string& imageSource)
 {
     const char* imgSource = imageSource.c_str();
     vector<u_int8_t> extractedImage;
     unique_ptr<FwOperations> _imgOps =
       unique_ptr<FwOperations>(FwOperations::FwOperationsCreate((void*)imgSource, NULL, NULL, FHT_FW_FILE));
     if (!_imgOps)
     {
         throw PLDMException("Failed to create FwOperations object.");
     }
     if (!_imgOps->FwExtract4MBImage(extractedImage, true))
     {
        throw PLDMException("Failed to extract fw data: %s", _imgOps->err());
     }
 
     string tmpFile = createTempFile();
     if (!WriteToFile(tmpFile, extractedImage))
     {
         throw PLDMException("Failed to write extracted fw data to a file.");
     }
     return tmpFile;
 }
 