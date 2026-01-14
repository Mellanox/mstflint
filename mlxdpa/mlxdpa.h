/*
 * Copyright (c) 2013-2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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

 #ifndef MLXDPA_H_
 #define MLXDPA_H_
 
 #include <map>
 #include <string>
 
 #include <elfio/elfio.hpp>
 
 #include "baseHeader.h"
 #include "certcontainerbase.h"
 #include "cmdparser/cmdparser.h"
 #include "cryptodata.h"
 #include "dpaAppStructHeader.h"
 
 class MlxDpa : public CommandLineRequester
 {
 public:
     MlxDpa();
     ~MlxDpa();
 
     void Run(int argc, char** argv);
     void SignHostElf();
     void SignSingleElf();
     void SignCertContainer();
     void CreateSingleElf();
     void CreateCertContainer();
     void CreateAppRemovalContainer();
     void SignAppRemovalContainer();
     void QueryManifestBlobSingleElf();
 
 private:
     enum MlxDpaCmd
     {
         SignDPAApps,
         CreateSingleDpaApp,
         SignSingleDpaApp,
         SignDPACertContainer,
         CreateDPACertContainer,
         CreateDPAAppRemovalContainer,
         SignDpaAppRemovalContainer,
         QueryManifestSingleElf,
         Unknown
     };
 
     enum CertContainerType
     {
         AddCert,
         RemoveCert,
         UnknownType
     };
 
     vector<u_int8_t> CreateCryptoDataStream(const vector<u_int8_t>& dpaAppElf,
                                             unique_ptr<MlxSign::Signer>& signer,
                                             CryptoDataSection& cryptoDataSection);
     unique_ptr<MlxSign::Signer> CreateSigner(string privateKeyPem, string keyLabel);
     vector<u_int8_t> CreateHeaderDataStream(DpaAppStructHeader headerData);
     vector<CertContainerItem> GetCertContainer(CertContainerType type);
     CertContainerType ToContainerType(string type);
     void AddPadding(vector<u_int8_t>& bufStream);
 
     void InitCmdParser();
     void PrintHelp();
     ParseStatus ParseCommandLine(int argc, char** argv);
     bool ParseAndFindCommand(int argc, char** argv);
     ParseStatus HandleOption(string name, string value);
     void ParamValidate();
 
     static const map<string, MlxDpaCmd> _cmdStringToEnum;
     static const string HOST_ELF_FLAG;
     static const char HOST_ELF_FLAG_SHORT;
     static const string SINGLE_APP_FLAG;
     static const char SINGLE_APP_FLAG_SHORT;
     static const string CERTIFICATE_FLAG;
     static const char CERTIFICATE_FLAG_SHORT;

     static const string PRIVATE_KEY_FLAG;
     static const char PRIVATE_KEY_FLAG_SHORT;
     static const string OUTPUT_FILE_FLAG;
     static const char OUTPUT_FILE_FLAG_SHORT;
     static const string HELP_FLAG;
     static const char HELP_FLAG_SHORT;
     static const string VERSION_FLAG;
     static const char VERSION_FLAG_SHORT;
     static const string CERT_CHAIN_COUNT_FLAG;
     static const string LIFE_CYCLE_PRIORITY_FLAG;
     static const string NVIDIA_SIGNED_OEM_FLAG;
     static const string KEEP_SIG_FLAG;
     static const char KEEP_SIG_FLAG_SHORT;
     static const string KEYPAIR_UUID_FLAG;
     static const string CERT_UUID_FLAG;
     static const string DPA_APP_UUID_FLAG;
     static const string REMOVE_ALL_CERTS_FLAG;
     static const string CERT_CONTAINER_FLAG;
     static const string CERT_CONTAINER_TYPE_FLAG;
     static const string DPA_APP_REMOVAL_CONTAINER_FLAG;
     static const string SIGN_DPA_APPS;
     static const string SIGN_SINGLE_DPA_APP;
     static const string QUERY_MANIFEST_SINGLE_ELF;
     static const string CREATE_DPA_APP_REMOVAL;
     static const string CERT_CONTAINER_FINGERPRINT;
     static const string SINGLE_APP_DPA_FINGERPRINT;
     static const string APP_METADATA_FLAG;
     static const char APP_METADATA_FLAG_SHORT;
     static const string MANIFEST_FLAG;
 
     const u_int32_t ALIGNMENT = 4;
 
     CommandLineParser _cmdParser;
     string _hostELFPath;
     string _singleAppPath;
     string _certificatePath;
     string _appMetadataPath;
     string _manifestPath;
     bool _appMetadataPresent;
     bool _manifestPresent;
     vector<u_int8_t> _appMetadata;
     vector<u_int8_t> _manifest;
     bool _isAwsHsm;
     bool _isKeepSig;
     string _keyLabel;
     string _privateKeyPem;
     string _outputPath;
     u_int32_t _certChainCount;
     bool _nvidiaSignedOem;
     BaseHeader::StructPriority _priority;
     bool _keypairUUIDSpecified;
     bool _certUUIDSpecified;
     bool _dpaAppUUIDSpecified;
     u_int32_t _keypairUUID[4];
     u_int32_t _certUUID[4];
     u_int32_t _dpaAppUUID[4];
     bool _removeAllCertsSpecified;
     bool _removeAllCerts;
     string _certContainerPath;
     string _dpaAppRemovalContainerPath;
     CertContainerType _certContainerType;
     MlxDpaCmd _command;
 };
 
 #endif /* MLXDPA_H_ */