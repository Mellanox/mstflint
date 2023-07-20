/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#ifndef MLXDPA_H_
#define MLXDPA_H_

#include <string>
#include <cmdparser/cmdparser.h>
#include <map>
#include <elfio/elfio.hpp>
#include "cryptodata.h"
#include "hostelf.h"
#include "certcontainerbase.h"

class MlxDpa : public CommandLineRequester
{
public:
    MlxDpa();
    ~MlxDpa();

    void Run(int argc, char** argv);
    void SignHostElf();
    void SignCertContainer();
    void CreateCertContainer();

private:
    enum MlxDpaCmd
    {
        SignDPAApps,
        SignDPACertContainer,
        CreateDPACertContainer,
        Unknown
    };

    enum CertContainerType
    {
        AddCert,
        RemoveCert,
        UnknownType
    };

    unique_ptr<MlxSign::Signer> CreateSigner(string privateKeyPem, string keyLabel);
    vector<CertContainerItem> GetCertContainer(CertContainerType type);
    CertContainerType ToContainerType(string type);

    void InitCmdParser();
    void PrintHelp();
    ParseStatus ParseCommandLine(int argc, char** argv);
    bool ParseAndFindCommand(int argc, char** argv);
    ParseStatus HandleOption(string name, string value);
    void ParamValidate();

    static const map<string, MlxDpaCmd> _cmdStringToEnum;
    static const string HOST_ELF_FLAG;
    static const char HOST_ELF_FLAG_SHORT;
    static const string CERTIFICATE_FLAG;
    static const char CERTIFICATE_FLAG_SHORT;
    static const string AWS_HSM_FLAG;
    static const char AWS_HSM_FLAG_SHORT;
    static const string KEY_LABEL_FLAG;
    static const char KEY_LABEL_FLAG_SHORT;
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
    static const string KEYPAIR_UUID_FLAG;
    static const string CERT_UUID_FLAG;
    static const string REMOVE_ALL_CERTS_FLAG;
    static const string CERT_CONTAINER_FLAG;
    static const string CERT_CONTAINER_TYPE_FLAG;
    static const string SIGN_DPA_APPS;
    static const string CERT_CONTAINER_FINGERPRINT;

    CommandLineParser _cmdParser;
    string _hostELFPath;
    string _certificatePath;
    bool _isAwsHsm;
    string _keyLabel;
    string _privateKeyPem;
    string _outputPath;
    u_int32_t _certChainCount;
    CertStructHeader::StructPriority _priority;
    bool _keypairUUIDSpecified;
    bool _certUUIDSpecified;
    u_int32_t _keypairUUID[4];
    u_int32_t _certUUID[4];
    bool _removeAllCertsSpecified;
    bool _removeAllCerts;
    string _certContainerPath;
    CertContainerType _certContainerType;
    MlxDpaCmd _command;
};

#endif /* MLXDPA_H_ */