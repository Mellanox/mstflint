/*
 * Copyright (c) 2021-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef CDB_CABLE_COMMANDER_H
#define CDB_CABLE_COMMANDER_H

#include "cdb_cable_access.h"

typedef int (*f_prog_func)(int completion);

struct MCUChallengeReply
{
    u_int8_t reserved[2];
    u_int8_t rreserved : 7;
    u_int8_t includeArcuse : 1;
    u_int8_t tokenOpcode;
    u_int32_t keypairUUID[4];
    u_int32_t linkxUID[2];
    u_int32_t psid[4];
    u_int32_t reserved2;
    u_int32_t fwVersion;
    u_int32_t reserved3[5];
    u_int32_t nonce[8];
    u_int32_t reserved4[2];
};

struct TokenStatusReply
{
    u_int8_t typeOfToken;
    u_int8_t statusOfToken;
    u_int16_t reserved;
    u_int32_t timeLeft;
};

struct ReadPublicKeyReply
{
    u_int8_t secureProvisioningVer;
    u_int8_t eplLength;
    u_int8_t lplLength;
    u_int8_t publicKeySize;
    u_int8_t* publicKeyBytes;
};

enum class EDPop : u_int8_t
{
    WRITE = 0,
    READ = 1
};

struct EDPPayloadHeader
{
    EDPop op;
    u_int16_t startPage;
    u_int8_t startAddress;
    u_int16_t dataLength;
};

enum BootStatusBits
{
    APP_REQ_BANK1 = (1 << 0),
    APP_REQ_BANK2 = (1 << 1),
    FOUND_COMMITTED_BANK = (1 << 2),
    IMG1_SHA256_SUCCESS = (1 << 3),
    IMG2_SHA256_SUCCESS = (1 << 4),
    IMG1_SIGNATURE_SUCCESS = (1 << 5),
    IMG2_SIGNATURE_SUCCESS = (1 << 6),
    IMG1_CHECKED = (1 << 7),
    IMG2_CHECKED = (1 << 8),
    IMG_SIGNATURE_SKIP = (1 << 9),
    ROOT_KEY_NONE = (1 << 10),
    ROOT_KEY_READ_FAIL = (1 << 11),
    MCU_FW_NOT_FOUND = (1 << 12),
    IMG1_HASH_ERR = (1 << 13),
    IMG2_HASH_ERR = (1 << 14),
    IMG1_CERT_CHAIN_ERR = (1 << 15),
    IMG2_CERT_CHAIN_ERR = (1 << 16),
    BOOT_STATUS_IMG1_VALID_FW_GLB_TBL = (1 << 17),
    BOOT_STATUS_IMG2_VALID_FW_GLB_TBL = (1 << 18),
    BOOT_STATUS_IMG1_ERR = (1 << 19),
    BOOT_STATUS_IMG2_ERR = (1 << 20),
    BOOT_STATUS_NO_KEY_SAFE_FOUND = (1 << 21),
    BOOT_STATUS_BOOT_INTERRUPTED = (1 << 22),
    BOOT_STATUS_APP_REQ_ABORT_BOOT = (1 << 23)
};

enum PackageErrorCode : u_int16_t
{
    PKG_OK = 0,
    PKG_FW_PRODUCT_ID_ERR = 1,
    PKG_HASH_SIZE_ERR = 2,
    PKG_SIGNATURE_SIZE_ERR = 3,
    PKG_TOC_SZ_ERR = 4,
    PKG_TOC_OFFSET_ERR = 5,
    PKG_BAD_LEN_ERR = 6,
    PKG_COMPONENT_OFFSET_ERR = 7,
    PKG_COMPONENT_SIZE_ERR = 8,
    PKG_MAGIC_NUM_ERR = 9,
    PKG_HASH_ITEMS_ERR = 10,
    PKG_SIGN_ITEMS_ERR = 11,
    PKG_DESC_ERR = 12,
    PKG_CERT_DESC_ERR = 13,
    PKG_NO_HASH_SECTION_ERR = 14,
    PKG_NO_SIG_SECTION_ERR = 15,
    PKG_HASH_IDX_ERR = 16,
    PKG_SIGN_IDX_ERR = 17,
    PKG_HASH_NUM_IDX_ERR = 18,
    PKG_SIGN_NUM_IDX_ERR = 19,
    PKG_COMPONENTS_NO_OFFSET_ERR = 20,
    PKG_COMP_KIND_NOT_FOUND_ERR = 21,
    PKG_HASH_SECTION_LEN_ERR = 22,
    PKG_SIGNATURE_SECTION_LEN_ERR = 23,
    PKG_COMP_DESC_SECTION_LEN_ERR = 24,
    PKG_TOC_KIND_DUPLICATE_ERR = 25,
    PKG_COMPONENT_KIND_DUPLICATE_ERR = 26,
    PKG_TOC_KIND_INVALID_ERR = 27,
    PKG_IMG_LOAD_ADDR_ERR = 28,
    PKG_NO_TRAILER_ERR = 29,
    PKG_NO_TRAILER_HASH_ERR = 30,
    PKG_NO_TRAILER_SIG_ERR = 31,
    PKG_TRAILER_HASH_ERR = 32,
    PKG_TRAILER_SECTION_LEN_ERR = 33,
    PKG_CERTIFICATE_ERR = 34,
    PKG_COMPONENT_KIND_INVALID_ERR = 35,
    PKG_FW_UPGRADE_VERSION_ERR = 36,
    PKG_NOT_FOUND_ERR = 37,
    PKG_MAIN_FW_COMP_NOT_FOUND_ERR = 38,
    PKG_PACKAGE_SIGNATURE_ERR = 39,
    PKG_PACKAGE_SIZE_ERR = 40,
    PKG_NO_PERMISSIONS_ERR = 41,
    PKG_UNEXPECTED_VERSION_ERR = 42,
    PKG_UNEXPECTED_CID_ERR = 43,
    PKG_FORBIDDEN_DATE_ERR = 44,
    PKG_FORBIDDEN_VERSION_ERR = 45,
    PKG_FORBIDDEN_UNKNOWN_ERR = 46,
    PKG_HEADER_VERSION_ERR = 47,
    PKG_NO_AUTHENTICATOR_ERR = 48,
    PKG_AUTHENTICATOR_SECTION_HASH_ERR = 49,
    PKG_AUTHENTICATOR_SECTION_SIG_ERR = 50,
    PKG_AUTHENTICATOR_SECTION_LEN_ERR = 51,
    PKG_AUTHENTICATOR_HASH_ERR = 52,
    PKG_NON_AUTH_COMP_HASH_ERR = 53,
    PKG_NON_AUTH_COMP_ERR = 54,
    RETIMER_BOOT_ERR = 55,
    RETIMER_SIGNATURE_ERR = 56,
    RETIMER_FORBIDDEN_VERSION_ERR = 57,
    RETIMER_FW_UPDATE_ERR = 58,
    PKG_UNKNOWN_ERR
};

static pair<BootStatusBits, string> _bootStatusToString[17];
static vector<pair<PackageErrorCode, string>> _packageErrorToString;
static vector<PackageErrorCode> _packageErrorsWithComponentIndex;
static vector<string> _validFWStates;

class FwManagementCdbCommander
{
public:
    explicit FwManagementCdbCommander(string mstDevName, bool clearCompletionFlag = false);

    void DownloadFWImage(const vector<u_int8_t>& image, const vector<u_int8_t>& vendorData, f_prog_func progressFunc);
    void SetPassword(string password);
    void SetCommandWaitingTime(string waitTime);
    void SetFWMngFeatures(FWManagementCdbAccess::FWMngFeatures fwMngFeatures);
    void ActivateImage();
    void RunImage(bool performInit = true);
    void CommitImage();

private:
    struct StartFWDownloadPayload
    {
        u_int32_t imageSize;
        u_int32_t reserved;
    };

    struct WriteFWBlockLPLPayload
    {
        u_int32_t blockAddress;
        u_int8_t firmwareBlock[116];
    };

    struct QueryStatusResponse
    {
        u_int8_t lengthOfStatus;
        u_int8_t unlockLevelAndPrivileges;
        u_int8_t firmwareDownloadAllowed;
    };

    void QueryStatus();
    void EnterPassword();
    bool IsActivationNeeded();
    void SendFwChunk(CmisCdbAccess::PayloadMethod payloadMethod,
                     vector<u_int8_t>::const_iterator fwChunk,
                     u_int32_t chunkSize,
                     u_int32_t blockAddress);
    void DownloadFWImageData(CmisCdbAccess::PayloadMethod payloadMethod,
                             u_int32_t vendorDataSize,
                             const vector<u_int8_t>& image,
                             f_prog_func progressFunc);
    void StartFWDownload(const vector<u_int8_t>& image, const vector<u_int8_t>& vendorData);
    void DealWithSignalDuringBurn();

    bool _modulePasswordSet;
    vector<u_int8_t> _modulePassword;
    FWManagementCdbAccess _fwMngCableAccess;
    u_int8_t _timeOutCounter;
};

#endif // CDB_CABLE_COMMANDER_H
