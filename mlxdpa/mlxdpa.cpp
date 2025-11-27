/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 #include "mlxdpa.h"
 #include <tuple>
 #include <sys/stat.h>
 
 #include <iostream>
 
 #include "baseHeader.h"
 #include "certcontainerimp.h"
#include "tools_version.h"
 #include "dpaAppRemoval.h"
 #include "dpaAppStructHeader.h"
 #include "hostless.h"
 #include "hostelf.h"
#include "mft_utils.h"
 #include "mlxdpa_utils.h"
 
 // using namespace ELFIO;
 
 #define INDENT "    "
 #define INDENT2 INDENT INDENT
 #define INDENT3 "\t\t"
 
 using appArchDataHandle = DevObjHandle*;
 using appArchManifestHandle = DevObjHandle*;
 
 static void printFlagLine(string flag_l, char flag_s, string param, string desc)
 {
     string shortFlag(1, flag_s);
     string flags = (flag_s != ' ' ? "-" + shortFlag + "|" : "   ");
     flags += "--" + flag_l + (param.length() ? " <" + param + ">" : "");
     printf(INDENT2 "%-40s", flags.c_str());
     printf(INDENT3 ": %s\n", desc.c_str());
 }
 
 const string MlxDpa::HOST_ELF_FLAG = "host_elf";
 const char MlxDpa::HOST_ELF_FLAG_SHORT = 'e';
 const string MlxDpa::SINGLE_APP_FLAG = "single_app";
 const char MlxDpa::SINGLE_APP_FLAG_SHORT = 's';
 const string MlxDpa::CERTIFICATE_FLAG = "certificate";
 const char MlxDpa::CERTIFICATE_FLAG_SHORT = 'c';
 const string MlxDpa::PRIVATE_KEY_FLAG = "private_key";
 const char MlxDpa::PRIVATE_KEY_FLAG_SHORT = 'p';
 const string MlxDpa::OUTPUT_FILE_FLAG = "output_file";
 const char MlxDpa::OUTPUT_FILE_FLAG_SHORT = 'o';
 const string MlxDpa::HELP_FLAG = "help";
 const char MlxDpa::HELP_FLAG_SHORT = 'h';
 const string MlxDpa::VERSION_FLAG = "version";
 const char MlxDpa::VERSION_FLAG_SHORT = 'v';
 const string MlxDpa::CERT_CHAIN_COUNT_FLAG = "cert_chain_count";
 const string MlxDpa::LIFE_CYCLE_PRIORITY_FLAG = "life_cycle_priority";
 const string MlxDpa::NVIDIA_SIGNED_OEM_FLAG = "nvidia_signed_oem";
 const string MlxDpa::KEEP_SIG_FLAG = "keep_sig";
 const char MlxDpa::KEEP_SIG_FLAG_SHORT = 'k';
 const string MlxDpa::KEYPAIR_UUID_FLAG = "keypair_uuid";
 const string MlxDpa::CERT_UUID_FLAG = "cert_uuid";
 const string MlxDpa::DPA_APP_UUID_FLAG = "dpa_app_uuid";
 const string MlxDpa::REMOVE_ALL_CERTS_FLAG = "remove_all_certs";
 const string MlxDpa::CERT_CONTAINER_FLAG = "cert_container";
 const string MlxDpa::DPA_APP_REMOVAL_CONTAINER_FLAG = "dpa_app_removal_container";
 const string MlxDpa::CERT_CONTAINER_TYPE_FLAG = "cert_container_type";
 const string MlxDpa::SIGN_DPA_APPS = "sign_dpa_apps";
 const string MlxDpa::SIGN_SINGLE_DPA_APP = "sign_single_dpa_app";
 const string MlxDpa::QUERY_MANIFEST_SINGLE_ELF = "query_manifest_single_elf";
 const string MlxDpa::CREATE_DPA_APP_REMOVAL = "create_dpa_app_removal";
 const string MlxDpa::CERT_CONTAINER_FINGERPRINT = "CERTIFICATE.BIN!";
 const string MlxDpa::SINGLE_APP_DPA_FINGERPRINT = "NV_DPA_APP.BIN!!";
 const string MlxDpa::APP_METADATA_FLAG = "app_metadata";
 const char MlxDpa::APP_METADATA_FLAG_SHORT = 'm';
 const string MlxDpa::MANIFEST_FLAG = "manifest";
 
 const map<string, MlxDpa::MlxDpaCmd> MlxDpa::_cmdStringToEnum = {
   {"sign_dpa_apps", SignDPAApps},
   {"create_single_dpa_app", CreateSingleDpaApp},
   {"sign_single_dpa_app", SignSingleDpaApp},
   {"query_manifest", QueryManifestSingleElf},
   {"create_cert_container", CreateDPACertContainer},
   {"sign_cert_container", SignDPACertContainer},
   {"create_dpa_app_removal", CreateDPAAppRemovalContainer},
   {"sign_dpa_app_removal", SignDpaAppRemovalContainer}};
 
 MlxDpa::MlxDpa() :
     CommandLineRequester("mstdpa OPTIONS"),
     _cmdParser("mstdpa"),
     _hostELFPath(""),
     _singleAppPath(""),
     _certificatePath(""),
     _appMetadataPath(""),
     _manifestPath(""),
     _appMetadataPresent(false),
     _manifestPresent(false),
     _appMetadata(),
     _manifest(),
     _isKeepSig(false),
     _privateKeyPem(""),
     _outputPath(""),
     _certChainCount(3),
     _nvidiaSignedOem(false),
     _priority(BaseHeader::StructPriority::Unknown),
     _keypairUUIDSpecified(false),
     _certUUIDSpecified(false),
     _dpaAppUUIDSpecified(false),
     _keypairUUID{0, 0, 0, 0},
     _certUUID{0, 0, 0, 0},
     _dpaAppUUID{0, 0, 0, 0},
     _removeAllCertsSpecified(false),
     _removeAllCerts(false),
     _certContainerPath(""),
     _dpaAppRemovalContainerPath(""),
     _certContainerType(CertContainerType::UnknownType),
     _command(Unknown)
 {
     InitCmdParser();
 }
 
 MlxDpa::~MlxDpa() {}
 
 void MlxDpa::PrintHelp()
 {
     printf(INDENT "NAME:\n" INDENT2 "mstdpa"
                   "\n" INDENT "SYNOPSIS:\n" INDENT2 "mlxdpa"
                   " [Options] <Command>\n");
 
     printf(INDENT "DESCRIPTION:\n" INDENT2
                   "Signs DPA Host ELF files, using private key pem file.\n" INDENT2
                   "Crypto data section is created for each DPA app in the Host ELF file.");
 
     printf("\n");
     printf(INDENT "OPTIONS:\n");
     printFlagLine(HOST_ELF_FLAG, HOST_ELF_FLAG_SHORT, "Host ELF", "Path to the Host ELF file containing DPA apps");
     printFlagLine(SINGLE_APP_FLAG, SINGLE_APP_FLAG_SHORT, "Single App", "Path to the single app file");
     printFlagLine(APP_METADATA_FLAG, APP_METADATA_FLAG_SHORT, "App Metadata", "Path to the app metadata yaml file");
     printFlagLine(MANIFEST_FLAG, ' ', "Manifest", "Path to the manifest file");
     printFlagLine(CERT_CHAIN_COUNT_FLAG, ' ', "Hex number", "Number of certificates in the provided certificate chain");
     printFlagLine(CERTIFICATE_FLAG,
                   CERTIFICATE_FLAG_SHORT,
                   "Certificate",
                   "Path to a certificate or certificate chain file to embed in the crypto data sections");
     printFlagLine(PRIVATE_KEY_FLAG,
                   PRIVATE_KEY_FLAG_SHORT,
                   "Private key PEM",
                   "Path to private key PEM file for signature generation");
     printFlagLine(OUTPUT_FILE_FLAG, OUTPUT_FILE_FLAG_SHORT, "Path", "Path to output signed Host ELF");
     printFlagLine(KEEP_SIG_FLAG, KEEP_SIG_FLAG_SHORT, "", "The whole certificate container will be kept");
     printFlagLine(LIFE_CYCLE_PRIORITY_FLAG, ' ', "Nvidia, OEM, User",
                   "Life-cycle priority of requested certificate container");
     printFlagLine(NVIDIA_SIGNED_OEM_FLAG, ' ', "", "NVIDIA signed OEM certificate");
     printFlagLine(KEYPAIR_UUID_FLAG, ' ', "UUID", "Key-pair UUID of the private key used for sign");
     printFlagLine(CERT_UUID_FLAG, ' ', "UUID", "Time base UUID generated right before signing");
     printFlagLine(DPA_APP_UUID_FLAG, ' ', "UUID", "Time base UUID generated right before signing");
     printFlagLine(REMOVE_ALL_CERTS_FLAG, ' ', "",
                   "Remove all CA Certificates, provide with the sign_cert_remove command");
     printFlagLine(DPA_APP_REMOVAL_CONTAINER_FLAG, ' ', "Path", "Path to a dpa app removal container to sign");
     printFlagLine(CERT_CONTAINER_FLAG, ' ', "Path", "Path to a certificate container to sign");
     printFlagLine(CERT_CONTAINER_TYPE_FLAG, ' ', "Add/Remove", "Type of certificate container to create");
     printFlagLine(HELP_FLAG, HELP_FLAG_SHORT, "", "Show help message and exit");
     printFlagLine(VERSION_FLAG, VERSION_FLAG_SHORT, "", "Show version and exit");
 
     printf(INDENT "\n");
     printf(INDENT "COMMANDS SUMMARY - Certificate Container:\n");
     printf(INDENT2 "%-24s: %s\n",
            "create_cert_container",
            "generate a certificate container, used for adding or removing certificates from a DPA device.");
     printf(INDENT2 "%-24s: %s\n", "sign_cert_container", "sign a previously generated certificate container.");
 
     printf(INDENT "\n");
     printf(INDENT "COMMANDS SUMMARY - Host ELF and Single ELF:\n");
     printf(INDENT2 "%-24s: %s\n",
            "sign_dpa_apps",
            "signs all dpa apps in the provided host elf, creating crypto data section for each app.");
     printf(INDENT2 "%-24s: %s\n", "create_single_dpa_app",
            "create single dpa app container, creating container for the dpa app.");
     printf(INDENT2 "%-24s: %s\n", "sign_single_dpa_app",
            "sign single dpa app, creating crypto data section for the app.");
     printf(INDENT2 "%-24s: %s\n", "query_manifest", "query manifest from single elf.");
     printf(INDENT2 "%-24s: %s\n", "create_dpa_app_removal",
            "create a dpa app removal container, used for removing a dpa app from a DPA device.");
     printf(INDENT2 "%-24s: %s\n", "sign_dpa_app_removal", "sign a previously generated dpa app removal container.");
     printf(INDENT "\n");
     printf(INDENT "Examples - Certificate Container:\n");
     printf(
       INDENT2 "%-63s: %s\n",
       "Create certificate upload container with keep_sig flag",
       "mstdpa --cert_container_type add -c /tmp/cert.der -o /tmp/cert_container.bin --life_cycle_priority OEM --keep_sig create_cert_container");
     printf(
       INDENT2 "%-63s: %s\n",
       "Create certificate upload container without keep_sig flag",
       "mstdpa --cert_container_type add -c /tmp/cert.der -o /tmp/cert_container.bin --life_cycle_priority OEM create_cert_container");
     printf(
       INDENT2 "%-63s: %s\n",
       "Create certificate upload container with nvidia_signed_oem flag",
       "mstdpa --cert_container_type add -c /tmp/cert.der -o /tmp/cert_container.bin --nvidia_signed_oem create_cert_container");
     printf(
       INDENT2 "%-63s: %s\n",
       "Create certificate remove all container",
       "mstdpa --cert_container_type remove --remove_all_certs -o /tmp/cert_container.bin --life_cycle_priority OEM create_cert_container");
 
     printf(
       INDENT2 "%-63s: %s\n", "Create certificate remove container",
       "mstdpa --cert_container_type remove --cert_uuid 7c0ab0fc-082e-11ee-bd9d-e43d1a1f06ae -o /tmp/cert_container.bin --life_cycle_priority OEM create_cert_container");
     printf(
       INDENT2 "%-63s: %s\n",
       "Sign certificate container",
       "mstdpa --cert_container /tmp/cert_container.bin -p /tmp/p_key.pem --keypair_uuid 3c8f46b2-159f-11ee-9ac4-e43d1a1f06ae "
       "--cert_uuid 7c0ab0fc-082e-11ee-bd9d-e43d1a1f06ae --life_cycle_priority OEM -o /tmp/signed_cert_container.bin sign_cert_container");
     printf(
       INDENT2 "%-63s: %s\n",
       "Sign certificate container with nvidia_signed_oem flag",
       "mstdpa --cert_container /tmp/cert_container.bin -p /tmp/p_key.pem --keypair_uuid 3c8f46b2-159f-11ee-9ac4-e43d1a1f06ae "
       "--cert_uuid 7c0ab0fc-082e-11ee-bd9d-e43d1a1f06ae --nvidia_signed_oem -o /tmp/signed_cert_container.bin sign_cert_container");
     printf(INDENT "\n");
     printf(INDENT "Examples - Host ELF and Single ELF:\n");
     printf(
       INDENT2 "%-52s: %s\n",
       "Sign Host ELF using PEM file",
       "mstdpa -e /tmp/host.elf -c /tmp/chain.cert -p /tmp/p_key.pem [--cert_chain_count 5] -o /tmp/signed_host.bin sign_dpa_apps");
     printf(
       INDENT2 "%-52s: %s\n",
       "Create upload container for single app",
       "mstdpa -s /tmp/singleApp.elf --life_cycle_priority OEM  -m /tmp/appmetadata.yaml --manifest /tmp/manifest.bin -o /tmp/single_app.bin create_single_dpa_app");
     printf(
       INDENT2 "%-52s: %s\n",
       "Sign upload container for single app using PEM file",
       "mstdpa -s /tmp/single_app.bin -c /tmp/chain.cert -p /tmp/p_key.pem [--cert_chain_count 5] --life_cycle_priority OEM -o /tmp/signed_single_app.bin sign_single_dpa_app");
     printf(INDENT2 "%-52s: %s\n",
            "Query manifest from single elf",
            "mstdpa -s /tmp/singleApp.elf -o /tmp/manifest.bin query_manifest");
     printf(
       INDENT2 "%-52s: %s\n",
       "Create Dpa app removal container",
       "mstdpa --dpa_app_uuid 7c0ab0fc-082e-11ee-bd9d-e43d1a1f06ae -o /tmp/dpa_app_removal_container.bin --life_cycle_priority OEM create_dpa_app_removal");
     printf(
       INDENT2 "%-52s: %s\n",
       "Sign Dpa app removal container",
       "mstdpa --dpa_app_removal_container /tmp/dpa_app_removal_container.bin --keypair_uuid 3c8f46b2-159f-11ee-9ac4-e43d1a1f06ae -p /tmp/p_key.pem"
       "-o /tmp/signed_dpa_app_removal_container.bin --life_cycle_priority OEM sign_dpa_app_removal");
     printf("\n");
 }
 
 void MlxDpa::InitCmdParser()
 {
     AddOptions(HOST_ELF_FLAG, HOST_ELF_FLAG_SHORT, "<path>", "Path to host ELF file");
     AddOptions(SINGLE_APP_FLAG, SINGLE_APP_FLAG_SHORT, "<path>", "Path to single app file");
     AddOptions(CERTIFICATE_FLAG, CERTIFICATE_FLAG_SHORT, "<path>", "Path to a certificate or certificate chain");
     AddOptions(APP_METADATA_FLAG, APP_METADATA_FLAG_SHORT, "<path>", "Path to the app metadata yaml file");
     AddOptions(MANIFEST_FLAG, ' ', "<path>", "Path to the manifest file");
     AddOptions(CERT_CHAIN_COUNT_FLAG, ' ', "<hex number>", "Number of certificates in the certificate chain");
     AddOptions(PRIVATE_KEY_FLAG, PRIVATE_KEY_FLAG_SHORT, "<string>", "Private key for DPA App signature");
     AddOptions(HELP_FLAG, HELP_FLAG_SHORT, "", "Show help message and exit");
     AddOptions(VERSION_FLAG, VERSION_FLAG_SHORT, "", "Show version and exit");
     AddOptions(OUTPUT_FILE_FLAG, OUTPUT_FILE_FLAG_SHORT, "<path>", "Path to output file");
     AddOptions(LIFE_CYCLE_PRIORITY_FLAG, ' ', "<enum>",
                "Life-cycle priority of certificate addition/removal container");
     AddOptions(NVIDIA_SIGNED_OEM_FLAG, ' ', "", "NVIDIA signed OEM certificate");
     AddOptions(KEYPAIR_UUID_FLAG, ' ', "<uuid>", "Key-pair UUID of signing key.");
     AddOptions(CERT_UUID_FLAG, ' ', "<uuid>", "RFC-4122 compliant time-based UUID.");
     AddOptions(DPA_APP_UUID_FLAG, ' ', "<uuid>", "RFC-4122 compliant time-based UUID.");
     AddOptions(REMOVE_ALL_CERTS_FLAG, ' ', "", "Remove all CA Certificates.");
     AddOptions(DPA_APP_REMOVAL_CONTAINER_FLAG, ' ', "<path>", "dpa app removal container to sign.");
     AddOptions(CERT_CONTAINER_FLAG, ' ', "<path>", "Certificate container to sign.");
     AddOptions(CERT_CONTAINER_TYPE_FLAG, ' ', "<Add/Remove>", "Type of certificate container to create.");
     AddOptions(KEEP_SIG_FLAG, KEEP_SIG_FLAG_SHORT, "", "flag for set keep_sig as 1");

     _cmdParser.AddRequester(this);
 }
 
 ParseStatus MlxDpa::HandleOption(string name, string value)
 {
     if (name == HELP_FLAG)
     {
         PrintHelp();
         return PARSE_OK_WITH_EXIT;
     }
     else if (name == VERSION_FLAG)
     {
         print_version_string("mstdpa", NULL);
         return PARSE_OK_WITH_EXIT;
     }
     else if (name == HOST_ELF_FLAG)
     {
         _hostELFPath = value;
         return PARSE_OK;
     }
     else if (name == SINGLE_APP_FLAG)
     {
         _singleAppPath = value;
         return PARSE_OK;
     }
     else if (name == CERTIFICATE_FLAG)
     {
         _certificatePath = value;
         return PARSE_OK;
     }
     else if (name == APP_METADATA_FLAG)
     {
         _appMetadataPath = value;
         return PARSE_OK;
     }
     else if (name == MANIFEST_FLAG)
     {
         _manifestPath = value;
         return PARSE_OK;
     }
     else if (name == PRIVATE_KEY_FLAG)
     {
         _privateKeyPem = value;
         return PARSE_OK;
     }
     else if (name == KEEP_SIG_FLAG)
     {
         _isKeepSig = true;
         return PARSE_OK;
     }
     else if (name == OUTPUT_FILE_FLAG)
     {
         _outputPath = value;
         return PARSE_OK;
     }
     else if (name == CERT_CHAIN_COUNT_FLAG)
     {
         u_int32_t count = 0;
         if (!strToNum(value, count, 16))
         {
             throw MlxDpaException("value given to cert_chain_count is not a hex number.");
         }
         _certChainCount = count;
         return PARSE_OK;
     }
     else if (name == LIFE_CYCLE_PRIORITY_FLAG)
     {
         _priority = BaseHeader::ToStructPriority(value);
         if (_priority == BaseHeader::StructPriority::Unknown)
         {
             throw MlxDpaException("Unknown life-cycle priority given.");
         }
         return PARSE_OK;
     }
     else if (name == NVIDIA_SIGNED_OEM_FLAG)
     {
         _nvidiaSignedOem = true;
         return PARSE_OK;
     }
     else if (name == KEYPAIR_UUID_FLAG)
     {
         _keypairUUIDSpecified = true;
         if (!ParseUUID(value, _keypairUUID))
         {
             throw MlxDpaException("Unknown key-pair uuid format given.");
         }
         return PARSE_OK;
     }
     else if (name == DPA_APP_UUID_FLAG)
     {
         _dpaAppUUIDSpecified = true;
         if (!ParseUUID(value, _dpaAppUUID))
         {
             throw MlxDpaException("Unknown dpa app uuid format given.");
         }
         return PARSE_OK;
     }
     else if (name == CERT_UUID_FLAG)
     {
         _certUUIDSpecified = true;
         if (!ParseUUID(value, _certUUID))
         {
             throw MlxDpaException("Unknown cert uuid format given.");
         }
         return PARSE_OK;
     }
     else if (name == DPA_APP_REMOVAL_CONTAINER_FLAG)
     {
         _dpaAppRemovalContainerPath = value;
         return PARSE_OK;
     }
     else if (name == CERT_CONTAINER_FLAG)
     {
         _certContainerPath = value;
         return PARSE_OK;
     }
     else if (name == CERT_CONTAINER_TYPE_FLAG)
     {
         _certContainerType = ToContainerType(value);
         if (_certContainerType == UnknownType)
         {
             throw MlxDpaException("Unknown certificate container type provided.");
         }
         return PARSE_OK;
     }
     else if (name == REMOVE_ALL_CERTS_FLAG)
     {
         _removeAllCertsSpecified = true;
         _removeAllCerts = true;
         if (_certContainerType != RemoveCert)
         {
             throw MlxDpaException("remove_all_certs can be provided only with containter type \"remove\".");
         }
         return PARSE_OK;
     }
 
     return PARSE_ERROR;
 }
 
 bool MlxDpa::ParseAndFindCommand(int argc, char** argv)
 {
     // first argument is tool name
     if (argc == 1)
     {
         throw MlxDpaException("No commands or flags have been specified.");
     }
 
     // a command must be specified as the last argument
     for (int i = 1; i < argc - 1; ++i)
     {
         if (_cmdStringToEnum.find(argv[i]) != _cmdStringToEnum.end())
         {
             throw MlxDpaException("Commands must be specified at the end of the CLI.");
         }
     }
 
     auto lastArg = _cmdStringToEnum.find(argv[argc - 1]);
     if (lastArg != _cmdStringToEnum.end())
     {
         _command = lastArg->second;
         return true;
     }
 
     return false;
 }
 
 void MlxDpa::ParamValidate()
 {
     if (_command == CreateSingleDpaApp)
     {
         if (_singleAppPath.empty())
         {
             throw MlxDpaException("path to single app must be specified to create DPA app.");
         }
         if (mft_utils::IsFileEmpty(_singleAppPath, true))
         {
             throw MlxDpaException("Single app file is empty or does not exist.");
         }
         if (_priority == BaseHeader::StructPriority::Unknown)
         {
             throw MlxDpaException("Valid priority must be specified to sign DPA app.");
         }
         if (_appMetadataPath.empty())
         {
             throw MlxDpaException("path to app metadata must be specified to create DPA app.");
         }
         if (_outputPath.empty())
         {
             throw MlxDpaException("Output file path must be specified to create DPA app.");
         }
     }
     else if (_command == QueryManifestSingleElf)
     {
         if (_singleAppPath.empty())
         {
             throw MlxDpaException("path to single app must be specified to query manifest.");
         }
         if (mft_utils::IsFileEmpty(_singleAppPath, true))
         {
             throw MlxDpaException("The dpa app file is empty or does not exist.");
         }
         if (_outputPath.empty())
         {
             throw MlxDpaException("Output file path must be specified to query manifest.");
         }
     }
     if (_command == SignDPAApps || _command == SignSingleDpaApp)
     {
         if (_command == SignDPAApps)
         {
             if (_hostELFPath.empty())
             {
                 throw MlxDpaException("path to Host ELF must be specified to sign DPA apps.");
             }
             if (mft_utils::IsFileEmpty(_hostELFPath, true))
             {
                 throw MlxDpaException("Host ELF file is empty or does not exist.");
             }
             if (!_manifestPath.empty())
             {
                 throw MlxDpaException("manifest flag is not supported with sign_dpa_apps command.");
             }
             if (!_appMetadataPath.empty())
             {
                 throw MlxDpaException("app_metadata flag is not supported with sign_dpa_apps command.");
             }
         }
         if (_command == SignSingleDpaApp)
         {
             if (_singleAppPath.empty())
             {
                 throw MlxDpaException("path to single app must be specified to sign DPA app.");
             }
             if (mft_utils::IsFileEmpty(_singleAppPath, true))
             {
                 throw MlxDpaException("Single app file is empty or does not exist.");
             }
             if (_priority == BaseHeader::StructPriority::Unknown)
             {
                 throw MlxDpaException("Valid priority must be specified to sign single DPA app.");
             }
             if (_nvidiaSignedOem)
             {
                 throw MlxDpaException("nvidia_signed_oem flag is not supported with sign_dpa_app command.");
             }
         }
         if (_certificatePath.empty())
         {
             throw MlxDpaException("path to OEM certificate chain must be specified to sign DPA app.");
         }
         if (mft_utils::IsFileEmpty(_certificatePath, true))
         {
             throw MlxDpaException("Certificate file is empty or does not exist.");
         }
         if (_privateKeyPem.empty() && !_isAwsHsm)
         {
             throw MlxDpaException("Must provide private key or use AWS HSM flag.");
         }
         if (!_privateKeyPem.empty() && _isAwsHsm)
         {
             throw MlxDpaException("Can't use AWS HSM flag and provide private key pem, chose one of them.");
         }
         if (!_privateKeyPem.empty() && mft_utils::IsFileEmpty(_privateKeyPem, true))
         {
             throw MlxDpaException("Private key file is empty or does not exist.");
         }
         if (_isAwsHsm && _keyLabel.empty())
         {
             throw MlxDpaException("Must provide private key label for AWS HSM sign flow.");
         }
         if (_outputPath.empty())
         {
             throw MlxDpaException("Output file path must be specified to sign DPA app.");
         }
     }
     else if (_command == CreateDPAAppRemovalContainer)
     {
         if (_nvidiaSignedOem)
         {
             throw MlxDpaException("Cannot use --nvidia_signed_oem flag with create_dpa_app_removal command.");
         }
         if (_priority == BaseHeader::StructPriority::Unknown)
         {
             throw MlxDpaException("Valid priority must be specified to create dpa app removal container.");
         }
         if (_outputPath.empty())
         {
             throw MlxDpaException("Output file path must be specified to create dpa app removal container.");
         }
         if (!_dpaAppUUIDSpecified)
         {
             throw MlxDpaException("dpa app uuid must be specified to create dpa app removal container.");
         }
     }
     else if (_command == CreateDPACertContainer)
     {
         if (_outputPath.empty())
         {
             throw MlxDpaException("Output file path must be specified to create certificte container.");
         }
         if (_certContainerType == AddCert)
         {
             if (!_nvidiaSignedOem && _priority == BaseHeader::StructPriority::Unknown)
             {
                 throw MlxDpaException(
                   "Valid priority must be specified to create certificte container or used with --nvidia_signed_oem flag.");
             }
             if (_nvidiaSignedOem && _priority != BaseHeader::StructPriority::Unknown)
             {
                 throw MlxDpaException("Cannot use priority flag with --nvidia_signed_oem flag.");
             }
             if (_certificatePath.empty())
             {
                 throw MlxDpaException("Path to a certificate must be specified to create certificte container.");
             }
             struct stat stat_buf;
             int rc = stat(_certificatePath.c_str(), &stat_buf);
             if (rc)
             {
                 throw MlxDpaException("Couldn't open %s, %s.", _certificatePath.c_str(), strerror(errno));
             }
             if (stat_buf.st_size >= 1792) // FW limitation of certs is less than 1792
             {
                 throw MlxDpaException("Certificate size limited to less than 1792 bytes.");
             }
         }
         if (_certContainerType == RemoveCert)
         {
             if (_nvidiaSignedOem)
             {
                 throw MlxDpaException(
                   "nvidia_signed_oem flag is not supported with create remove certificate container command.");
             }
             if (_priority == CertStructHeader::StructPriority::Unknown)
             {
                 throw MlxDpaException("Valid priority must be specified to create certificte container.");
             }
             if (!_removeAllCertsSpecified && !_certUUIDSpecified)
             {
                 throw MlxDpaException(
                   "must provide cert_uuid or remove_all_certs to create remove certificate cotainer.");
             }
         }
     }
     else if (_command == SignDPACertContainer || _command == SignDpaAppRemovalContainer)
     {
         if (_command == SignDPACertContainer)
         {
             if (_nvidiaSignedOem && _priority != CertStructHeader::StructPriority::Unknown)
             {
                 throw MlxDpaException("Cannot use priority flag with --nvidia_signed_oem flag. please use one of them.");
             }
             if (!_nvidiaSignedOem && _priority == CertStructHeader::StructPriority::Unknown)
             {
                 throw MlxDpaException("Valid priority must be specified to sign a certificte container.");
             }
             if (_certContainerPath.empty())
             {
                 throw MlxDpaException("Must provide path to the certificate container to sign.");
             }
             if (mft_utils::IsFileEmpty(_certContainerPath, true))
             {
                 throw MlxDpaException("Certificate container file is empty or does not exist.");
             }
         }
         else if (_command == SignDpaAppRemovalContainer)
         {
             if (_dpaAppRemovalContainerPath.empty())
             {
                 throw MlxDpaException("Must provide path to the dpa app removal container to sign.");
             }
             if (mft_utils::IsFileEmpty(_dpaAppRemovalContainerPath, true))
             {
                 throw MlxDpaException("DPA app removal container file is empty or does not exist.");
             }
             if (_nvidiaSignedOem)
             {
                 throw MlxDpaException("Cannot use --nvidia_signed_oem flag with sign_dpa_app_removal command.");
             }
         }
         if (!_keypairUUIDSpecified)
         {
             throw MlxDpaException("Keypair UUID must be specified to create certificte container.");
         }
         if (_privateKeyPem.empty() && !_isAwsHsm)
         {
             throw MlxDpaException("Must provide private key or use AWS HSM flag.");
         }
         if (!_privateKeyPem.empty() && _isAwsHsm)
         {
             throw MlxDpaException("Can't use AWS HSM flag and provide private key pem, chose one of them.");
         }
         if (!_privateKeyPem.empty() && mft_utils::IsFileEmpty(_privateKeyPem, true))
         {
             throw MlxDpaException("Private key file is empty or does not exist.");
         }
         if (_isAwsHsm && _keyLabel.empty())
         {
             throw MlxDpaException("Must provide private key label for AWS HSM sign flow.");
         }
         if (_outputPath.empty())
         {
             throw MlxDpaException("Output file path must be specified to create certificte container.");
         }
     }
     else if (_command == Unknown)
     {
         throw MlxDpaException("Please specify a command.");
     }
 }
 
 ParseStatus MlxDpa::ParseCommandLine(int argc, char** argv)
 {
     ParseStatus rc = PARSE_OK;
 
     if (ParseAndFindCommand(argc, argv))
     {
         argc--;
     }
 
     rc = _cmdParser.ParseOptions(argc, argv);
     if (rc == PARSE_OK_WITH_EXIT)
     {
         return rc;
     }
     else if (rc == PARSE_ERROR)
     {
         PrintHelp();
         throw MlxDpaException("Failed to parse arguments. %s", _cmdParser.GetErrDesc());
     }
 
     ParamValidate();
 
     return rc;
 }
 
 /********************************************************************************************************************/
 /*                                                                                                                  */
 /*                                          tool logic                                                              */
 /*                                                                                                                  */
 /********************************************************************************************************************/
 
 MlxDpa::CertContainerType MlxDpa::ToContainerType(string type)
 {
     mft_utils::to_lowercase(type);
     if (type == "add")
     {
         return CertContainerType::AddCert;
     }
     else if (type == "remove")
     {
         return CertContainerType::RemoveCert;
     }
     else
     {
         return CertContainerType::UnknownType;
     }
 }

unique_ptr<MlxSign::Signer> MlxDpa::CreateSigner(string privateKeyPem, string keyLabel)
{
    unique_ptr<MlxSign::Signer> signer = nullptr;

#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    signer = unique_ptr<MlxSign::Signer>(new MlxSign::MlxSignRSAViaOpenssl(privateKeyPem));

    if (signer != nullptr && signer->Init() != MlxSign::MLX_SIGN_SUCCESS)
    {
        throw MlxDpaException("failed to create signer.");
    }
#else
    throw MlxDpaException("mstdpa sign is not supported.");
#endif

    return signer;
}

vector<CertContainerItem> MlxDpa::GetCertContainer(CertContainerType type)
{
    vector<CertContainerItem> container;

    if (type == AddCert)
    {
         BaseHeader::StructPriority priorityCACert = _priority;
         BaseHeader::StructPriority priorityCaCertMetadata = _priority;
         if (_nvidiaSignedOem)
         {
             priorityCaCertMetadata =
               CertStructHeader::GetPriorityNvidiaSignedOem(CertStructHeader::StructType::CacertMetadata);
             priorityCACert =
               CertStructHeader::GetPriorityNvidiaSignedOem(CertStructHeader::StructType::CertificateX509);
         }
         container.push_back(
           CertContainerItem(priorityCaCertMetadata,
                             make_shared<CACertMetaData>(_certUUID, _keypairUUID, static_cast<u_int8_t>(_isKeepSig))));
         container.push_back(CertContainerItem(priorityCACert, make_shared<CACert>(_certificatePath)));
     }
     else if (type == RemoveCert)
     {
         container.push_back(
           CertContainerItem(_priority, make_shared<CACertRemove>(_certUUID, _keypairUUID, _removeAllCerts)));
     }
     else
     {
         throw MlxDpaException("Unsupported command for container creation.");
     }
     return container;
 }
 
 void MlxDpa::CreateAppRemovalContainer()
 {
     vector<u_int8_t> serializedContainer;
 
     const string X = SINGLE_APP_DPA_FINGERPRINT;
 
     DpaAppRemoveMetadata dpaAppRemovalMetadata(_dpaAppUUID, _keypairUUID);
     vector<u_int8_t> serializedMetadata = dpaAppRemovalMetadata.Serialize();
     DpaAppStructHeader headerDpaAppRemovalMetadata(_priority, DpaAppStructHeader::StructType::DPA_APP_REMOVE_METADATA,
                                                    serializedMetadata.size());
     vector<u_int8_t> headerDpaAppRemovalMetadataByteStream = CreateHeaderDataStream(headerDpaAppRemovalMetadata);
 
     serializedContainer.insert(end(serializedContainer), begin(X), end(X));
 
     serializedContainer.insert(end(serializedContainer), begin(headerDpaAppRemovalMetadataByteStream),
                                end(headerDpaAppRemovalMetadataByteStream));
     serializedContainer.insert(end(serializedContainer), begin(serializedMetadata), end(serializedMetadata));
 
     ofstream removalContainer(_outputPath, std::ios::binary);
     removalContainer.write((char*)serializedContainer.data(), serializedContainer.size());
     removalContainer.close();
     cout << "DpaRemoval container created successfully!" << endl;
 }
 
void MlxDpa::CreateCertContainer()
{
    vector<u_int8_t> serializedContainer;
    vector<CertContainerItem> container = GetCertContainer(_certContainerType);
    const string X = "CERTIFICATE.BIN!";

    serializedContainer.insert(end(serializedContainer), begin(X), end(X));
    for (auto item : container)
    {
        vector<u_int8_t> serializedItem = item.Serialize(true);
        serializedContainer.insert(end(serializedContainer), begin(serializedItem), end(serializedItem));
    }

    ofstream certContainer(_outputPath, std::ios::binary);
    certContainer.write((char*)serializedContainer.data(), serializedContainer.size());

    cout << "Certificate container created successfully!" << endl;
}

 void MlxDpa::SignAppRemovalContainer()
 {
     unique_ptr<MlxSign::Signer> signer = CreateSigner(_privateKeyPem, _keyLabel);
     std::fstream dpaRemoveContainerFile(_dpaAppRemovalContainerPath, ios::in | ios::out | std::ios::binary);
     if ((dpaRemoveContainerFile.rdstate() & std::ifstream::failbit) != 0)
     {
         throw MlxDpaException("Error opening '%s'", _dpaAppRemovalContainerPath.c_str());
     }
     vector<u_int8_t> dpaRemoveContainer((std::istreambuf_iterator<char>(dpaRemoveContainerFile)),
                                         std::istreambuf_iterator<char>());
 
     if (dpaRemoveContainer.size() < SINGLE_APP_DPA_FINGERPRINT.size() + DpaAppStructHeader::HEADER_SIZE_NO_AUTH +
                                       DpaAppRemoveMetadata::KEY_PAIR_UUID_SIZE +
                                       DpaAppRemoveMetadata::DPA_APP_UUID_SIZE + DpaAppRemoveMetadata::RESERVED_SIZE)
     {
         throw MlxDpaException("Invalid dpa app removal container.");
     }
 
     if (strncmp((const char*)dpaRemoveContainer.data(), SINGLE_APP_DPA_FINGERPRINT.c_str(),
                 SINGLE_APP_DPA_FINGERPRINT.size()) != 0)
     {
         throw MlxDpaException("Invalid dpa app removal container.");
     }
 
     vector<u_int8_t>::iterator containerIter = dpaRemoveContainer.begin() + SINGLE_APP_DPA_FINGERPRINT.size();
     DpaAppStructHeader metadataHeader;
     if (!metadataHeader.Deserialize(containerIter, containerIter + DpaAppStructHeader::HEADER_SIZE_NO_AUTH))
     {
         throw MlxDpaException("Invalid header size in given container.");
     }
     containerIter += DpaAppStructHeader::HEADER_SIZE_NO_AUTH;
 
     if (metadataHeader.GetType() == DpaAppStructHeader::StructType::DPA_APP_REMOVE_METADATA)
     {
         containerIter += sizeof(_dpaAppUUID);
         CPUTOn(_keypairUUID, sizeof(_keypairUUID) / 4);
         memcpy(&(*containerIter), _keypairUUID, sizeof(_keypairUUID));
         containerIter += sizeof(_keypairUUID);
     }
     else
     {
         throw MlxDpaException("Invalid dpa removal container, unknown header type.");
     }
 
     vector<u_int8_t> signature;
     MlxSign::ErrorCode rc = signer->Sign(dpaRemoveContainer, signature);
     if (rc != MlxSign::MLX_SIGN_SUCCESS)
     {
         throw MlxDpaException("Signing dpa removal container failed with error %#x.", rc);
     }
     DpaAppRemoveSignature dpaAppRemoveSignature(signature);
     vector<u_int8_t> serializedSignature = dpaAppRemoveSignature.Serialize();
     DpaAppStructHeader headerDpaAppRemovalSignature(_priority, DpaAppStructHeader::StructType::SIGNATURE,
                                                     serializedSignature.size());
     vector<u_int8_t> headerDpaAppRemovalSignatureByteStream = CreateHeaderDataStream(headerDpaAppRemovalSignature);
 
     dpaRemoveContainer.insert(end(dpaRemoveContainer), begin(headerDpaAppRemovalSignatureByteStream),
                               end(headerDpaAppRemovalSignatureByteStream));
     dpaRemoveContainer.insert(end(dpaRemoveContainer), begin(serializedSignature), end(serializedSignature));
 
     ofstream signedDpaRemoveContainer(_outputPath, std::ios::binary);
     signedDpaRemoveContainer.write((char*)dpaRemoveContainer.data(), dpaRemoveContainer.size());
 
     cout << "DPA removal container signed successfully!" << endl;
 }
 
void MlxDpa::SignCertContainer()
{
    unique_ptr<MlxSign::Signer> signer = CreateSigner(_privateKeyPem, _keyLabel);
    std::fstream certContainerFile(_certContainerPath, ios::in | ios::out | std::ios::binary);
    if ((certContainerFile.rdstate() & std::ifstream::failbit) != 0)
    {
        throw MlxDpaException("Error opening '%s'", _certContainerPath.c_str());
    }
    vector<u_int8_t> certContainer((std::istreambuf_iterator<char>(certContainerFile)),
                                   std::istreambuf_iterator<char>());

    if (certContainer.size() <
        CERT_CONTAINER_FINGERPRINT.size() + CertStructHeader::HEADER_SIZE + CertStructBase::METADATA_SIZE)
    {
        throw MlxDpaException("Invalid certificate container.");
    }

    if (strncmp(
          (const char*)certContainer.data(), CERT_CONTAINER_FINGERPRINT.c_str(), CERT_CONTAINER_FINGERPRINT.size()) != 0)
    {
        throw MlxDpaException("Invalid certificate container.");
    }

    vector<u_int8_t>::iterator containerIter = certContainer.begin() + CERT_CONTAINER_FINGERPRINT.size();
    CertStructHeader metadataHeader;
    if (!metadataHeader.Deserialize(containerIter, containerIter + CertStructHeader::HEADER_SIZE))
    {
        throw MlxDpaException("Invalid header size in given container.");
    }
    containerIter += CertStructHeader::HEADER_SIZE;

    CPUTOn(_keypairUUID, sizeof(_keypairUUID) / 4);

    if (metadataHeader.GetType() == CertStructHeader::StructType::CacertMetadata)
    {
         if (_nvidiaSignedOem)
         {
             CertStructHeader cacertHeader;
             u_int16_t caCertMetadataDataSize = metadataHeader.GetLength() - CertStructHeader::HEADER_SIZE;
             if (!cacertHeader.Deserialize(containerIter + caCertMetadataDataSize,
                                           containerIter + caCertMetadataDataSize + CertStructHeader::HEADER_SIZE))
             {
                 throw MlxDpaException("Invalid header size in given container.");
             }
             if (cacertHeader.GetType() != CertStructHeader::StructType::CertificateX509)
             {
                 throw MlxDpaException("Not found certificatex509 in given container.");
             }
             if (!(metadataHeader.ValidateNvidiaSignedOemPriority()) ||
                 !(cacertHeader.ValidateNvidiaSignedOemPriority()))
             {
                 throw MlxDpaException("Invalid priority in given container.");
             }
         }
 
        if (!_certUUIDSpecified)
        {
            throw MlxDpaException("Cert UUID must be specified to create certificte container.");
        }
        CPUTOn(_certUUID, sizeof(_certUUID) / 4);
        memcpy(&(*containerIter), _certUUID, sizeof(_certUUID));
        containerIter += sizeof(_certUUID);
        containerIter += 4;
        memcpy(&(*containerIter), _keypairUUID, sizeof(_keypairUUID));
    }
    else if (metadataHeader.GetType() == CertStructHeader::StructType::CacertRemove)
    {
        containerIter += sizeof(_certUUID);
        memcpy(&(*containerIter), _keypairUUID, sizeof(_keypairUUID));
    }
    else
    {
       throw MlxDpaException("Invalid certificate container, unknown header type.");
    }

    vector<u_int8_t> signature;
    MlxSign::ErrorCode rc = signer->Sign(certContainer, signature);
    if (rc != MlxSign::MLX_SIGN_SUCCESS)
    {
        throw MlxDpaException("Signing certificate container failed with error %#x.", rc);
    }
     if (_nvidiaSignedOem)
     {
         _priority = CertStructHeader::GetPriorityNvidiaSignedOem(CertStructHeader::StructType::Signature);
     }
    CertContainerItem signatureItem(_priority, make_shared<CertStructSignature>(signature));
    vector<u_int8_t> serializedItem = signatureItem.Serialize(true);
    certContainer.insert(end(certContainer), begin(serializedItem), end(serializedItem));

    ofstream signedCertContainer(_outputPath, std::ios::binary);
    signedCertContainer.write((char*)certContainer.data(), certContainer.size());

    cout << "Certificate container signed successfully!" << endl;
}

 vector<u_int8_t> MlxDpa::CreateHeaderDataStream(DpaAppStructHeader headerData)
 {
     vector<u_int8_t> haederDataSectionByteStream = headerData.Serialize();
 
     return haederDataSectionByteStream;
 }
 
 void MlxDpa::AddPadding(vector<u_int8_t>& bufStream)
 {
     if (bufStream.size() % ALIGNMENT)
     {
         u_int32_t paddingSize = ALIGNMENT - (bufStream.size() % ALIGNMENT);
         bufStream.resize(bufStream.size() + paddingSize, 0xff);
     }
 }
 
 vector<u_int8_t> MlxDpa::CreateCryptoDataStream(const vector<u_int8_t>& dpaAppElf,
                                                 unique_ptr<MlxSign::Signer>& signer,
                                                 CryptoDataSection& cryptoDataSection)
 {
     if (_appMetadataPresent)
     {
         cryptoDataSection.SetAppMetadata(_appMetadata);
     }
     if (_manifestPresent)
     {
         cryptoDataSection.SetManifest(_manifest);
     }
     cryptoDataSection.SetAppMetadataPresent(_appMetadataPresent);
     cryptoDataSection.SetManifestPresent(_manifestPresent);
     cryptoDataSection.GenerateHashListFromELF(dpaAppElf);
     cryptoDataSection.Sign(*signer);
     vector<u_int8_t> cryptoDataSectionByteStream = cryptoDataSection.Serialize();
     CPUTOn(cryptoDataSectionByteStream.data(),
            cryptoDataSectionByteStream.size() / 4); // Converting crypto data blob to bin-endian
 
     // Add padding if required, after crypto data blob is converted to big-endian
     AddPadding(cryptoDataSectionByteStream);
     return cryptoDataSectionByteStream;
 }
 void MlxDpa::CreateSingleElf()
 {
     HostLess hostLess(_singleAppPath, _appMetadataPath, _manifestPath);
     vector<u_int8_t> dpaAppElf = hostLess.GetElfData();
     DpaAppStructHeader headerDpaApp(_priority, DpaAppStructHeader::StructType::DPA_ELF, hostLess.GetElfSize());
     vector<u_int8_t> headerDataSectionByteStream = CreateHeaderDataStream(headerDpaApp);
 
     vector<u_int8_t> appMetadata = hostLess.GetAppMetadata();
     DpaAppStructHeader headerAppMetadata(_priority, DpaAppStructHeader::StructType::DPA_APP_METADATA,
                                          hostLess.GetAppMetadataSize());
     vector<u_int8_t> headerAppMetadataByteStream = CreateHeaderDataStream(headerAppMetadata);
 
     vector<u_int8_t> manifest = hostLess.GetManifest();
     DpaAppStructHeader headerManifest(_priority, DpaAppStructHeader::StructType::DPA_APP_MANIFEST,
                                       hostLess.GetManifestSize());
     vector<u_int8_t> headerManifestByteStream = CreateHeaderDataStream(headerManifest);
 
     std::ofstream outputElfFile(_outputPath);
     if (!outputElfFile)
     {
         throw MlxDpaException("Failed to open file '%s'", _outputPath.c_str());
     }
     outputElfFile.write(reinterpret_cast<const char*>(SINGLE_APP_DPA_FINGERPRINT.data()),
                         SINGLE_APP_DPA_FINGERPRINT.size());
     outputElfFile.write(reinterpret_cast<const char*>(headerDataSectionByteStream.data()),
                         (headerDataSectionByteStream.size()));
     outputElfFile.write(reinterpret_cast<const char*>(dpaAppElf.data()), dpaAppElf.size());
     outputElfFile.write(reinterpret_cast<const char*>(headerAppMetadataByteStream.data()),
                         headerAppMetadataByteStream.size());
     outputElfFile.write(reinterpret_cast<const char*>(appMetadata.data()), appMetadata.size());
     outputElfFile.write(reinterpret_cast<const char*>(headerManifestByteStream.data()),
                         headerManifestByteStream.size());
     if (hostLess.IsManifestPresent())
     {
         outputElfFile.write(reinterpret_cast<const char*>(manifest.data()), manifest.size());
     }
     outputElfFile.close();
     std::cout << _outputPath << " was created successfully with UUID: " << hostLess.GetAppMetadataUUID() << std::endl;
 }
 
 void MlxDpa::SignSingleElf()
 {
     HostLess hostLess(_singleAppPath, _priority);
 
     CryptoDataSection::CertChain certChain;
     unique_ptr<MlxSign::Signer> signer = CreateSigner(_privateKeyPem, _keyLabel);
     certChain.AddCertificates(_certificatePath);
     certChain.SetCount(_certChainCount);
 
     CryptoDataSection cryptoDataSection(certChain);
     cryptoDataSection.SetSingleElfState();
 
     vector<u_int8_t> elfData = hostLess.GetElfData();
     _appMetadata = hostLess.GetAppMetadata();
     _appMetadataPresent = hostLess.IsAppMetadataPresent();
     _manifestPresent = hostLess.IsManifestPresent();
     if (_manifestPresent)
     {
         _manifest = hostLess.GetManifest();
     }
 
     vector<u_int8_t> cryptoDataSectionByteStream = CreateCryptoDataStream(elfData, signer, cryptoDataSection);
 
     vector<u_int8_t> headerElfByteStream = CreateHeaderDataStream(hostLess.GetElfHeader());
 
     DpaAppStructHeader headerDataCryptoBlob(_priority, DpaAppStructHeader::StructType::DPA_CRYPTO_BLOB,
                                             cryptoDataSectionByteStream.size());
     vector<u_int8_t> headerDataCryptoBlobByteStream = CreateHeaderDataStream(headerDataCryptoBlob);
 
     DpaAppStructHeader headerAppMetadata = hostLess.GetAppMetadataHeader();
     vector<u_int8_t> headerAppMetadataByteStream = CreateHeaderDataStream(headerAppMetadata);
 
     DpaAppStructHeader headerManifest = hostLess.GetManifestHeader();
     vector<u_int8_t> headerManifestByteStream = CreateHeaderDataStream(headerManifest);
 
     std::ofstream outputElfFile(_outputPath);
     if (!outputElfFile)
     {
         throw MlxDpaException("Failed to open file '%s'", _outputPath.c_str());
     }
     outputElfFile.write(reinterpret_cast<const char*>(SINGLE_APP_DPA_FINGERPRINT.data()),
                         SINGLE_APP_DPA_FINGERPRINT.size());
     outputElfFile.write(reinterpret_cast<const char*>(headerElfByteStream.data()), (headerElfByteStream.size()));
     outputElfFile.write(reinterpret_cast<const char*>(elfData.data()), elfData.size());
     outputElfFile.write(reinterpret_cast<const char*>(headerDataCryptoBlobByteStream.data()),
                         headerDataCryptoBlobByteStream.size());
     outputElfFile.write(reinterpret_cast<const char*>(cryptoDataSectionByteStream.data()),
                         cryptoDataSectionByteStream.size());
     outputElfFile.write(reinterpret_cast<const char*>(headerAppMetadataByteStream.data()),
                         headerAppMetadataByteStream.size());
     outputElfFile.write(reinterpret_cast<const char*>(_appMetadata.data()), _appMetadata.size());
     outputElfFile.write(reinterpret_cast<const char*>(headerManifestByteStream.data()),
                         headerManifestByteStream.size());
     if (_manifestPresent)
     {
         outputElfFile.write(reinterpret_cast<const char*>(_manifest.data()), _manifest.size());
     }
     outputElfFile.close();
     std::cout << _outputPath << " was signed successfully." << std::endl;
 }
 
 void MlxDpa::QueryManifestBlobSingleElf()
 {
     HostLess hostLess(_singleAppPath, _priority, false);
     vector<u_int8_t> manifest = hostLess.GetManifest();
     std::ofstream outputManifestFile(_outputPath, std::ios::binary);
     outputManifestFile.write(reinterpret_cast<const char*>(manifest.data()), manifest.size());
     outputManifestFile.close();
     std::cout << _outputPath << " was created successfully." << std::endl;
 }
 
 void MlxDpa::SignHostElf()
 {
     if (_outputPath.empty())
     {
         _outputPath = _hostELFPath;
     }
     else
     {
         string cmd("cp " + _hostELFPath + " " + _outputPath);
         RunCommand(cmd, "Failed to create output file");
     }
 
     HostElf hostElf(_hostELFPath, _outputPath);
     CryptoDataSection::CertChain certChain;
     unique_ptr<MlxSign::Signer> signer = CreateSigner(_privateKeyPem, _keyLabel);
     vector<AppHandle*> dpaAppsList = hostElf.GetListOfDpaApps();
 
     certChain.AddCertificates(_certificatePath);
     certChain.SetCount(_certChainCount);
 
     for (auto app : dpaAppsList)
     {
         vector<std::tuple<appArchDataHandle, appArchManifestHandle>> dpaArchAppsList =
           hostElf.GetListOfDpaArchApps(app->ObjTable, app->arch_count, app->ProcAttrsTable);
         for (auto archApp : dpaArchAppsList)
         {
             CryptoDataSection cryptoDataSection(certChain);
 
             appArchDataHandle archAppElf = std::get<0>(archApp);
             appArchManifestHandle archAppManifest = std::get<1>(archApp);
 
             vector<u_int8_t> dpaAppElf = hostElf.GetDpaApp(*archAppElf);
             if (archAppManifest != NULL)
             {
                 _manifest = hostElf.GetManifestDpaApp(*archAppManifest);
                 _manifestPresent = !_manifest.empty();
             }
             MLX_DPA_DPRINTF(("Generating Hash List for %s, HW version %d\n", app->name,
                              archAppElf->ID)); // TODO: Maybe need a function to print as string the enum archApp->ID
 
             vector<u_int8_t> cryptoDataSectionByteStream = CreateCryptoDataStream(dpaAppElf, signer, cryptoDataSection);
 
             // invoke 3rd party function to update metadata in host elf output file
             FILE* outHostELF = fopen(_outputPath.c_str(), "r+");
             if (outHostELF == NULL)
             {
                 throw MlxDpaException("Failed to open Host ELF file with error: %s", strerror(errno));
             }
             MLX_DPA_DPRINTF(("Calling updateSignatureData: appName %s, HW version %d, cryptoData size %lu.\n",
                              app->name, archAppElf->ID, (long)cryptoDataSectionByteStream.size()));
             int rc = updateSignatureData(outHostELF, app->name, archAppElf->ID, cryptoDataSectionByteStream.data(),
                                          cryptoDataSectionByteStream.size());
             if (rc != 0)
             {
                 string err("Failed to add crypto data for app" + string(app->name) + "with HW version" +
                            std::to_string(archAppElf->ID) + ".");
                 if (rc > 0 && rc < NUM_OF_RET_VALS)
                 {
                     err += " " + updateSigErrors[rc];
                 }
                 throw MlxDpaException(err.c_str());
             }
 
             if (fclose(outHostELF) != 0)
             {
                 throw MlxDpaException("Failed to close Host ELF file with error: %s", strerror(errno));
             }
         }
     }
 
     cout << _outputPath << " was signed successfully." << endl;
 }
 
 void MlxDpa::Run(int argc, char** argv)
 {
     if (ParseCommandLine(argc, argv) != PARSE_OK)
     {
         return;
     }
 
     switch (_command)
     {
         case SignDPAApps:
             SignHostElf();
             break;
         case CreateSingleDpaApp:
             CreateSingleElf();
             break;
         case SignSingleDpaApp:
             SignSingleElf();
             break;
         case CreateDPAAppRemovalContainer:
             CreateAppRemovalContainer();
             break;
         case CreateDPACertContainer:
             CreateCertContainer();
             break;
         case SignDPACertContainer:
             SignCertContainer();
             break;
         case SignDpaAppRemovalContainer:
             SignAppRemovalContainer();
             break;
         case QueryManifestSingleElf:
             QueryManifestBlobSingleElf();
             break;
         default:
             throw MlxDpaException("Unknown command code %d", _command);
     }
 }
 
 int main(int argc, char** argv)
 {
     try
     {
         MlxDpa mlxDpa;
         mlxDpa.Run(argc, argv);
     }
     catch (const MlxDpaException& ex)
     {
         cerr << "-E- " << ex.what() << endl;
         return 1;
     }
     catch (const std::exception& ex)
     {
         cerr << "-E- General Exception: " << ex.what() << endl;
         return 1;
     }
     return 0;
 }