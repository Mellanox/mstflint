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

#include <iostream>
#include <stdarg.h>
#include <sys/stat.h>
#include "mlxdpa.h"
#include "mft_utils.h"
#include "mlxdpa_utils.h"
#include "certcontainerimp.h"
#include "tools_version.h"

#define INDENT  "    "
#define INDENT2 INDENT INDENT
#define INDENT3 "\t\t"

static void printFlagLine(string flag_l, char flag_s, string param, string desc)
{
    string shortFlag(1, flag_s);
    string flags = (flag_s != ' ' ? "-" + shortFlag + "|" : "   ");

    flags += "--" + flag_l + (param.length() ? " <" + param + ">" : "");
    printf(INDENT2 "%-40s", flags.c_str());
    printf(INDENT3 ": %s\n", desc.c_str());
}

const string MlxDpa::HOST_ELF_FLAG = "host_elf";
const char   MlxDpa::HOST_ELF_FLAG_SHORT = 'e';
const string MlxDpa::CERTIFICATE_FLAG = "certificate";
const char   MlxDpa::CERTIFICATE_FLAG_SHORT = 'c';
const string MlxDpa::PRIVATE_KEY_FLAG = "private_key";
const char   MlxDpa::PRIVATE_KEY_FLAG_SHORT = 'p';
const string MlxDpa::OUTPUT_FILE_FLAG = "output_file";
const char   MlxDpa::OUTPUT_FILE_FLAG_SHORT = 'o';
const string MlxDpa::HELP_FLAG = "help";
const char   MlxDpa::HELP_FLAG_SHORT = 'h';
const string MlxDpa::VERSION_FLAG = "version";
const char   MlxDpa::VERSION_FLAG_SHORT = 'v';
const string MlxDpa::CERT_CHAIN_COUNT_FLAG = "cert_chain_count";
const string MlxDpa::LIFE_CYCLE_PRIORITY_FLAG = "life_cycle_priority";
const string MlxDpa::KEYPAIR_UUID_FLAG = "keypair_uuid";
const string MlxDpa::CERT_UUID_FLAG = "cert_uuid";
const string MlxDpa::REMOVE_ALL_CERTS_FLAG = "remove_all_certs";
const string MlxDpa::CERT_CONTAINER_FLAG = "cert_container";
const string MlxDpa::CERT_CONTAINER_TYPE_FLAG = "cert_container_type";
const string MlxDpa::SIGN_DPA_APPS = "sign_dpa_apps";
const string MlxDpa::CERT_CONTAINER_FINGERPRINT = "CERTIFICATE.BIN!";

const map < string, MlxDpa::MlxDpaCmd > MlxDpa::_cmdStringToEnum = {
    {"sign_dpa_apps", SignDPAApps},
    {"create_cert_container", CreateDPACertContainer},
    {"sign_cert_container", SignDPACertContainer}
};

MlxDpa::MlxDpa() :
    CommandLineRequester("mstdpa OPTIONS"),
    _cmdParser("mstdpa"),
    _hostELFPath(""),
    _certificatePath(""),
    _privateKeyPem(""),
    _outputPath(""),
    _certChainCount(3),
    _priority(CertStructHeader::StructPriority::Unknown),
    _keypairUUIDSpecified(false),
    _certUUIDSpecified(false),
    _keypairUUID{0, 0, 0, 0},
    _certUUID{0, 0, 0, 0},
    _removeAllCertsSpecified(false),
    _removeAllCerts(false),
    _certContainerPath(""),
    _certContainerType(CertContainerType::UnknownType),
    _command(Unknown)
{
    InitCmdParser();
}

MlxDpa::~MlxDpa()
{
}

void MlxDpa::PrintHelp()
{
    printf(INDENT "NAME:\n" INDENT2 "mlxdpa"
           "\n" INDENT "SYNOPSIS:\n" INDENT2 "mlxdpa"
           " [Options] <Command>\n");

    printf(INDENT "DESCRIPTION:\n" INDENT2
           "Signs DPA Host ELF files, using AWS sign server or private key pem file.\n" INDENT2
           "Crypto data section is created for each DPA app in the Host ELF file.");

    printf("\n");
    printf(INDENT "OPTIONS:\n");
    printFlagLine(HOST_ELF_FLAG, HOST_ELF_FLAG_SHORT, "Host ELF", "Path to the Host ELF file containing DPA apps");
    printFlagLine(CERTIFICATE_FLAG,
                  CERTIFICATE_FLAG_SHORT,
                  "Certificate",
                  "Path to a certificate or certificate chain file to embed in the crypto data sections");
    printFlagLine(PRIVATE_KEY_FLAG,
                  PRIVATE_KEY_FLAG_SHORT,
                  "Private key PEM",
                  "Path to private key PEM file for signature generation");
    printFlagLine(OUTPUT_FILE_FLAG, OUTPUT_FILE_FLAG_SHORT, "Path", "Path to output signed Host ELF");
    printFlagLine(
        LIFE_CYCLE_PRIORITY_FLAG, ' ', "Nvidia, OEM, User", "Life-cycle priority of requested certificate container");
    printFlagLine(KEYPAIR_UUID_FLAG, ' ', "UUID", "Key-pair UUID of the private key used for sign");
    printFlagLine(CERT_UUID_FLAG, ' ', "UUID", "Time base UUID generated right before signing");
    printFlagLine(
        REMOVE_ALL_CERTS_FLAG, ' ', "", "Remove all CA Certificates, provide with the sign_cert_remove command");
    printFlagLine(CERT_CONTAINER_FLAG, ' ', "Path", "Path to a certificate container to sign");
    printFlagLine(CERT_CONTAINER_TYPE_FLAG, ' ', "Add/Remove", "Type of certificate container to create");
    printFlagLine(HELP_FLAG, HELP_FLAG_SHORT, "", "Show help message and exit");
    printFlagLine(VERSION_FLAG, VERSION_FLAG_SHORT, "", "Show version and exit");

    printf(INDENT "COMMANDS SUMMARY:\n");
    printf(INDENT2 "%-24s: %s\n",
           "sign_dpa_apps",
           "signs all dpa apps in the provided host elf, creating crypto data section for each app.");
    printf(INDENT2 "%-24s: %s\n",
           "create_cert_container",
           "generate a certificate container, used for adding or removing certificates from a DPA device.");
    printf(INDENT2 "%-24s: %s\n", "sign_cert_container", "sign a previously generated certificate container.");

    printf(INDENT "Examples:\n");
    printf(INDENT2 "%-24s: %s\n",
           "Sign Host ELF using PEM file",
           "mstdpa -e /tmp/host.elf -c /tmp/chain.cert -p /tmp/p_key.pem -o /tmp/signed_host.elf sign_dpa_apps");
    printf(
        INDENT2 "%-24s: %s\n",
        "Create certificate upload container",
        "mstdpa --cert_container_type add -c /tmp/cert.der -o /tmp/cert_container.bin --life_cycle_priority OEM create_cert_container");
    printf(
        INDENT2 "%-24s: %s\n",
        "Create certificate remove all container",
        "mstdpa --cert_container_type remove --remove_all_certs -o /tmp/cert_container.bin --life_cycle_priority OEM create_cert_container");
    printf(
        INDENT2 "%-24s: %s\n",
        "Create certificate remove container",
        "mstdpa --cert_container_type remove --cert_uuid 7c0ab0fc-082e-11ee-bd9d-e43d1a1f06ae -o /tmp/cert_container.bin --life_cycle_priority OEM create_cert_container");
    printf(
        INDENT2 "%-24s: %s\n",
        "Sign certificate container",
        "mstdpa --cert_container /tmp/cert_container.bin -p /tmp/p_key.pem --keypair_uuid 3c8f46b2-159f-11ee-9ac4-e43d1a1f06ae "
        "--cert_uuid 7c0ab0fc-082e-11ee-bd9d-e43d1a1f06ae --life_cycle_priority OEM -o /tmp/signed_cert_container.bin sign_cert_container");

    printf("\n");
}

void MlxDpa::InitCmdParser()
{
    AddOptions(HOST_ELF_FLAG, HOST_ELF_FLAG_SHORT, "<path>", "Path to host ELF file");
    AddOptions(CERTIFICATE_FLAG, CERTIFICATE_FLAG_SHORT, "<path>", "Path to a certificate or certificate chain");
    AddOptions(CERT_CHAIN_COUNT_FLAG, ' ', "<hex number>", "Number of certificates in the certificate chain");
    AddOptions(PRIVATE_KEY_FLAG, PRIVATE_KEY_FLAG_SHORT, "<string>", "Private key for DPA App signature");
    AddOptions(HELP_FLAG, HELP_FLAG_SHORT, "", "Show help message and exit");
    AddOptions(VERSION_FLAG, VERSION_FLAG_SHORT, "", "Show version and exit");
    AddOptions(OUTPUT_FILE_FLAG, OUTPUT_FILE_FLAG_SHORT, "<path>", "Path to output file");
    AddOptions(
        LIFE_CYCLE_PRIORITY_FLAG, ' ', "<enum>", "Life-cycle priority of certificate addition/removal container");
    AddOptions(KEYPAIR_UUID_FLAG, ' ', "<uuid>", "Key-pair UUID of signing key.");
    AddOptions(CERT_UUID_FLAG, ' ', "<uuid>", "RFC-4122 compliant time-based UUID.");
    AddOptions(REMOVE_ALL_CERTS_FLAG, ' ', "", "Remove all CA Certificates.");
    AddOptions(CERT_CONTAINER_FLAG, ' ', "<path>", "Certificate container to sign.");
    AddOptions(CERT_CONTAINER_TYPE_FLAG, ' ', "<Add/Remove>", "Type of certificate container to create.");
    _cmdParser.AddRequester(this);
}

ParseStatus MlxDpa::HandleOption(string name, string value)
{
    if (name == HELP_FLAG) {
        PrintHelp();
        return PARSE_OK_WITH_EXIT;
    } else if (name == VERSION_FLAG) {
        print_version_string("mlxdpa", NULL);
        return PARSE_OK_WITH_EXIT;
    } else if (name == HOST_ELF_FLAG) {
        _hostELFPath = value;
        return PARSE_OK;
    } else if (name == CERTIFICATE_FLAG) {
        _certificatePath = value;
        return PARSE_OK;
    } else if (name == PRIVATE_KEY_FLAG) {
        _privateKeyPem = value;
        return PARSE_OK;
    } else if (name == OUTPUT_FILE_FLAG) {
        _outputPath = value;
        return PARSE_OK;
    } else if (name == CERT_CHAIN_COUNT_FLAG) {
        u_int32_t count = 0;
        if (!strToNum(value, count, 16)) {
            throw MlxDpaException("value given to cert_chain_count is not a hex number.");
        }
        _certChainCount = count;
        return PARSE_OK;
    } else if (name == LIFE_CYCLE_PRIORITY_FLAG) {
        _priority = CertStructHeader::ToStructPriority(value);
        if (_priority == CertStructHeader::StructPriority::Unknown) {
            throw MlxDpaException("Unknown life-cycle priority given.");
        }
        return PARSE_OK;
    } else if (name == KEYPAIR_UUID_FLAG) {
        _keypairUUIDSpecified = true;
        if (!ParseUUID(value, _keypairUUID)) {
            throw MlxDpaException("Unknown key-pair uuid format given.");
        }
        return PARSE_OK;
    } else if (name == CERT_UUID_FLAG) {
        _certUUIDSpecified = true;
        if (!ParseUUID(value, _certUUID)) {
            throw MlxDpaException("Unknown cert uuid format given.");
        }
        return PARSE_OK;
    } else if (name == CERT_CONTAINER_FLAG) {
        _certContainerPath = value;
        return PARSE_OK;
    } else if (name == CERT_CONTAINER_TYPE_FLAG) {
        _certContainerType = ToContainerType(value);
        if (_certContainerType == UnknownType) {
            throw MlxDpaException("Unknown certificate container type provided.");
        }
        return PARSE_OK;
    } else if (name == REMOVE_ALL_CERTS_FLAG) {
        _removeAllCertsSpecified = true;
        _removeAllCerts = true;
        if (_certContainerType != RemoveCert) {
            throw MlxDpaException("remove_all_certs can be provided only with the sign_cert_remove command.");
        }
        return PARSE_OK;
    }

    return PARSE_ERROR;
}

bool MlxDpa::ParseAndFindCommand(int argc, char** argv)
{
    /* first argument is tool name */
    if (argc == 1) {
        throw MlxDpaException("No commands or flags have been specified.");
    }

    /* a command must be specified as the last argument */
    for (int i = 1; i < argc - 1; ++i) {
        if (_cmdStringToEnum.find(argv[i]) != _cmdStringToEnum.end()) {
            throw MlxDpaException("Commands must be specified at the end of the CLI.");
        }
    }

    auto lastArg = _cmdStringToEnum.find(argv[argc - 1]);

    if (lastArg != _cmdStringToEnum.end()) {
        _command = lastArg->second;
        return true;
    }

    return false;
}

void MlxDpa::ParamValidate()
{
    if (_command == SignDPAApps) {
        if (_hostELFPath.empty()) {
            throw MlxDpaException("path to Host ELF must be specified to sign DPA apps.");
        }
        if (_certificatePath.empty()) {
            throw MlxDpaException("path to OEM certificate chain must be specified to sign DPA apps.");
        }
        if (_privateKeyPem.empty()) {
            throw MlxDpaException("Must provide private key.");
        }
    } else if (_command == CreateDPACertContainer) {
        if (_priority == CertStructHeader::StructPriority::Unknown) {
            throw MlxDpaException("Valid priority must be specified to create certificte container.");
        }
        if (_outputPath.empty()) {
            throw MlxDpaException("Output file path must be specified to create certificte container.");
        }
        if (_certContainerType == AddCert) {
            if (_certificatePath.empty()) {
                throw MlxDpaException("Path to a certificate must be specified to create certificte container.");
            }
            struct stat stat_buf;
            int         rc = stat(_certificatePath.c_str(), &stat_buf);
            if (rc) {
                throw MlxDpaException("Couldn't open %s, %s.", _certificatePath.c_str(), strerror(errno));
            }
            if (stat_buf.st_size >= 1792) { /* FW limitation of certs is less than 1792 */
                throw MlxDpaException("Certificate size limited to less than 1792 bytes.");
            }
        }
        if (_certContainerType == RemoveCert) {
            if (!_removeAllCertsSpecified && !_certUUIDSpecified) {
                throw MlxDpaException(
                    "must provide cert_uuid or remove_all_certs to create remove certificate cotainer.");
            }
        }
    } else if (_command == SignDPACertContainer) {
        if (_priority == CertStructHeader::StructPriority::Unknown) {
            throw MlxDpaException("Valid priority must be specified to sign a certificte container.");
        }
        if (!_keypairUUIDSpecified) {
            throw MlxDpaException("Keypair UUID must be specified to create certificte container.");
        }
        if (_privateKeyPem.empty()) {
            throw MlxDpaException("Must provide private key.");
        }
        if (_certContainerPath.empty()) {
            throw MlxDpaException("Must provide path to the certificate container to sign.");
        }
        if (_outputPath.empty()) {
            throw MlxDpaException("Output file path must be specified to create certificte container.");
        }
    } else if (_command == Unknown) {
        throw MlxDpaException("Please specify a command.");
    }
}

ParseStatus MlxDpa::ParseCommandLine(int argc, char** argv)
{
    ParseStatus rc = PARSE_OK;

    if (ParseAndFindCommand(argc, argv)) {
        argc--;
    }

    rc = _cmdParser.ParseOptions(argc, argv);
    if (rc == PARSE_OK_WITH_EXIT) {
        return rc;
    } else if (rc == PARSE_ERROR) {
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
    if (type == "add") {
        return CertContainerType::AddCert;
    } else if (type == "remove") {
        return CertContainerType::RemoveCert;
    } else {
        return CertContainerType::UnknownType;
    }
}

unique_ptr < MlxSign::Signer > MlxDpa::CreateSigner(string privateKeyPem, string keyLabel)
{
    unique_ptr < MlxSign::Signer > signer = nullptr;

#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    signer = unique_ptr < MlxSign::Signer > (new MlxSign::MlxSignRSAViaOpenssl(privateKeyPem));

    if ((signer != nullptr) && (signer->Init() != MlxSign::MLX_SIGN_SUCCESS)) {
        throw MlxDpaException("failed to create signer.");
    }
#else
    throw MlxDpaException("mstdpa sign is not supported.");
#endif

    return signer;
}

vector < CertContainerItem > MlxDpa::GetCertContainer(CertContainerType type)
{
    vector < CertContainerItem > container;

    if (type == AddCert) {
        container.push_back(CertContainerItem(_priority, new CACertMetaData(_certUUID, _keypairUUID)));
        container.push_back(CertContainerItem(_priority, new CACert(_certificatePath)));
    } else if (type == RemoveCert) {
        container.push_back(CertContainerItem(_priority, new CACertRemove(_certUUID, _keypairUUID, _removeAllCerts)));
    } else {
        throw MlxDpaException("Unsupported command for container creation.");
    }
    return container;
}

void MlxDpa::CreateCertContainer()
{
    vector < u_int8_t > serializedContainer;
    vector < CertContainerItem > container = GetCertContainer(_certContainerType);
    const string X = "CERTIFICATE.BIN!";

    serializedContainer.insert(end(serializedContainer), begin(X), end(X));
    for (auto item : container) {
        vector < u_int8_t > serializedItem = item.Serialize(true);
        serializedContainer.insert(end(serializedContainer), begin(serializedItem), end(serializedItem));
    }

    ofstream certContainer(_outputPath, std::ios::binary);
    certContainer.write((char*)serializedContainer.data(), serializedContainer.size());

    cout << "Certificate container created successfully!" << endl;
}

void MlxDpa::SignCertContainer()
{
    unique_ptr < MlxSign::Signer > signer = CreateSigner(_privateKeyPem, _keyLabel);
    std::fstream certContainerFile(_certContainerPath, ios::in | ios::out | std::ios::binary);
    if ((certContainerFile.rdstate() & std::ifstream::failbit) != 0) {
        throw MlxDpaException("Error opening '%s'", _certContainerPath.c_str());
    }
    vector < u_int8_t > certContainer((std::istreambuf_iterator < char > (certContainerFile)),
                                      std::istreambuf_iterator < char > ());

    if (certContainer.size() <
        CERT_CONTAINER_FINGERPRINT.size() + CertStructHeader::HEADER_SIZE + CertStructBase::METADATA_SIZE) {
        throw MlxDpaException("Invalid certificate container.");
    }

    if (strncmp(
            (const char*)certContainer.data(), CERT_CONTAINER_FINGERPRINT.c_str(),
            CERT_CONTAINER_FINGERPRINT.size()) != 0) {
        throw MlxDpaException("Invalid certificate container.");
    }

    vector < u_int8_t > ::iterator containerIter = certContainer.begin() + CERT_CONTAINER_FINGERPRINT.size();
    CertStructHeader metadataHeader;

    if (!metadataHeader.Deserialize(containerIter, containerIter + CertStructHeader::HEADER_SIZE)) {
        throw MlxDpaException("Invalid header size in given container.");
    }
    containerIter += CertStructHeader::HEADER_SIZE;

    CPUTOn(_keypairUUID, sizeof(_keypairUUID) / 4);

    if (metadataHeader.GetType() == CertStructHeader::StructType::CacertMetadata) {
        if (!_certUUIDSpecified) {
            throw MlxDpaException("Cert UUID must be specified to create certificte container.");
        }
        CPUTOn(_certUUID, sizeof(_certUUID) / 4);
        memcpy(&(*containerIter), _certUUID, sizeof(_certUUID));
        containerIter += sizeof(_certUUID);
        containerIter += 4;
        memcpy(&(*containerIter), _keypairUUID, sizeof(_keypairUUID));
    } else if (metadataHeader.GetType() == CertStructHeader::StructType::CacertRemove) {
        containerIter += sizeof(_certUUID);
        memcpy(&(*containerIter), _keypairUUID, sizeof(_keypairUUID));
    } else {
        throw MlxDpaException("Invalid certificate container, unknown header type.");
    }

    vector < u_int8_t > signature;
    MlxSign::ErrorCode rc = signer->Sign(certContainer, signature);

    if (rc != MlxSign::MLX_SIGN_SUCCESS) {
        throw MlxDpaException("Signing certificate container failed with error %#x.", rc);
    }

    CertContainerItem signatureItem(_priority, new CertStructSignature(signature));
    vector < u_int8_t > serializedItem = signatureItem.Serialize(true);
    certContainer.insert(end(certContainer), begin(serializedItem), end(serializedItem));

    ofstream signedCertContainer(_outputPath, std::ios::binary);
    signedCertContainer.write((char*)certContainer.data(), certContainer.size());

    cout << "Certificate container signed successfully!" << endl;
}

void MlxDpa::SignHostElf()
{
    const u_int32_t ALIGNMENT = 4;

    HostElf hostElf(_hostELFPath, _outputPath);
    CryptoDataSection::CertChain certChain;

    unique_ptr < MlxSign::Signer > signer = CreateSigner(_privateKeyPem, _keyLabel);
    vector < AppHandle * > dpaAppsList = hostElf.GetListOfDpaApps();

    certChain.AddCertificates(_certificatePath);
    certChain.SetCount(_certChainCount);

    for (auto app : dpaAppsList) {
        CryptoDataSection cryptoDataSection(certChain);

        vector < u_int8_t > dpaAppElf = hostElf.GetDpaApp(*app);

        MLX_DPA_DPRINTF(("Generating Hash List for %s.\n", app->name));
        cryptoDataSection.GenerateHashListFromELF(dpaAppElf);

        cryptoDataSection.Sign(*signer);

        vector < u_int8_t > cryptoDataSectionByteStream = cryptoDataSection.Serialize();
        CPUTOn(cryptoDataSectionByteStream.data(),
               cryptoDataSectionByteStream.size() / 4); /* Converting crypto data blob to bin-endian */

        /* Add padding if required, after crypto data blob is converted to big-endian */
        if (cryptoDataSectionByteStream.size() % ALIGNMENT) {
            u_int32_t paddingSize = ALIGNMENT - (cryptoDataSectionByteStream.size() % ALIGNMENT);
            cryptoDataSectionByteStream.resize(cryptoDataSectionByteStream.size() + paddingSize, 0xff);
        }

        /* remove preexisting section to avoid collision */
        string sigSectionName = "sig_" + string(app->name);
        hostElf.RemoveSection(sigSectionName);

        hostElf.AddSection(sigSectionName, cryptoDataSectionByteStream);

        /* invoke 3rd party function to update metadata in host elf output file */
        FILE* outHostELF = fopen(_outputPath.c_str(), "r+");
        if (outHostELF == NULL) {
            throw MlxDpaException("Failed to open Host ELF file with error: %s", strerror(errno));
        }
        if (updateSigSectionName(outHostELF, app->name, (char*)sigSectionName.c_str())) {
            throw MlxDpaException("Failed to update signature section name in metadata for %s.\n", app->name);
        }
    }

    cout << _outputPath << " was signed successfully." << endl;
}

void MlxDpa::Run(int argc, char** argv)
{
    if (ParseCommandLine(argc, argv) != PARSE_OK) {
        return;
    }

    switch (_command) {
    case SignDPAApps:
        SignHostElf();
        break;

    case CreateDPACertContainer:
        CreateCertContainer();
        break;

    case SignDPACertContainer:
        SignCertContainer();
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
    catch(const MlxDpaException& ex)
    {
        cerr << "-E- " << ex.what() << endl;
        return 1;
    }
    catch(const std::exception& ex)
    {
        cerr << "-E- General Exception: " << ex.what() << endl;
        return 1;
    }
    return 0;
}
