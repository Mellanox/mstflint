/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef PACKAGE_ERROR_CODES_H
#define PACKAGE_ERROR_CODES_H

#include <stddef.h>

/*
 * The package error codes from the LinkX Vendor Specific CDB spec. Several reports carry them and each lays them out
 * differently - the CDB FW-info reply pairs a 16-bit code with a 16-bit component index, MCCE reports a bare 16-bit
 * code and no index at all - so a caller splits its own field and asks here only about the code it extracted.
 *
 * The codes live in one table so the name and the has-component-index answer cannot drift apart from the code.
 */
struct PackageError
{
    unsigned int code;
    const char* name;
    bool hasComponentIndex;
};

/* The code the device reported, or NULL - the device supplies the value, so it can be anything. */
inline const PackageError* FindPackageError(unsigned int errorCode)
{
    // clang-format off
    /* code, name, carries a component index */
    static const PackageError packageErrors[] = {
        {0,  "PKG_OK",                             false},
        {1,  "PKG_FW_PRODUCT_ID_ERR",              false},
        {2,  "PKG_HASH_SIZE_ERR",                  false},
        {3,  "PKG_SIGNATURE_SIZE_ERR",             false},
        {4,  "PKG_TOC_SZ_ERR",                     true},
        {5,  "PKG_TOC_OFFSET_ERR",                 true},
        {6,  "PKG_BAD_LEN_ERR",                    true},
        {7,  "PKG_COMPONENT_OFFSET_ERR",           true},
        {8,  "PKG_COMPONENT_SIZE_ERR",             true},
        {9,  "PKG_MAGIC_NUM_ERR",                  false},
        {10, "PKG_HASH_ITEMS_ERR",                 false},
        {11, "PKG_SIGN_ITEMS_ERR",                 false},
        {12, "PKG_DESC_ERR",                       false},
        {13, "PKG_CERT_DESC_ERR",                  false},
        {14, "PKG_NO_HASH_SECTION_ERR",            false},
        {15, "PKG_NO_SIG_SECTION_ERR",             false},
        {16, "PKG_HASH_IDX_ERR",                   true},
        {17, "PKG_SIGN_IDX_ERR",                   true},
        {18, "PKG_HASH_NUM_IDX_ERR",               true},
        {19, "PKG_SIGN_NUM_IDX_ERR",               true},
        {20, "PKG_COMPONENTS_NO_OFFSET_ERR",       true},
        {21, "PKG_COMP_KIND_NOT_FOUND_ERR",        false},
        {22, "PKG_HASH_SECTION_LEN_ERR",           false},
        {23, "PKG_SIGNATURE_SECTION_LEN_ERR",      false},
        {24, "PKG_COMP_DESC_SECTION_LEN_ERR",      false},
        {25, "PKG_TOC_KIND_DUPLICATE_ERR",         false},
        {26, "PKG_COMPONENT_KIND_DUPLICATE_ERR",   true},
        {27, "PKG_TOC_KIND_INVALID_ERR",           true},
        {28, "PKG_IMG_LOAD_ADDR_ERR",              true},
        {29, "PKG_NO_TRAILER_ERR",                 false},
        {30, "PKG_NO_TRAILER_HASH_ERR",            false},
        {31, "PKG_NO_TRAILER_SIG_ERR",             false},
        {32, "PKG_TRAILER_HASH_ERR",               false},
        {33, "PKG_TRAILER_SECTION_LEN_ERR",        false},
        {34, "PKG_CERTIFICATE_ERR",                false},
        {35, "PKG_COMPONENT_KIND_INVALID_ERR",     false},
        {36, "PKG_FW_UPGRADE_VERSION_ERR",         false},
        {37, "PKG_NOT_FOUND_ERR",                  false},
        {38, "PKG_MAIN_FW_COMP_NOT_FOUND_ERR",     false},
        {39, "PKG_PACKAGE_SIGNATURE_ERR",          false},
        {40, "PKG_PACKAGE_SIZE_ERR",               false},
        {41, "PKG_NO_PERMISSIONS_ERR",             false},
        {42, "PKG_UNEXPECTED_VERSION_ERR",         false},
        {43, "PKG_UNEXPECTED_CID_ERR",             false},
        {44, "PKG_FORBIDDEN_DATE_ERR",             false},
        {45, "PKG_FORBIDDEN_VERSION_ERR",          false},
        {46, "PKG_FORBIDDEN_UNKNOWN_ERR",          false},
        {47, "PKG_HEADER_VERSION_ERR",             false},
        {48, "PKG_NO_AUTHENTICATOR_ERR",           false},
        {49, "PKG_AUTHENTICATOR_SECTION_HASH_ERR", false},
        {50, "PKG_AUTHENTICATOR_SECTION_SIG_ERR",  false},
        {51, "PKG_AUTHENTICATOR_SECTION_LEN_ERR",  false},
        {52, "PKG_AUTHENTICATOR_HASH_ERR",         false},
        {53, "PKG_NON_AUTH_COMP_HASH_ERR",         false},
        {54, "PKG_NON_AUTH_COMP_ERR",              false},
        {55, "RETIMER_BOOT_ERR",                   false},
        {56, "RETIMER_SIGNATURE_ERR",              false},
        {57, "RETIMER_FORBIDDEN_VERSION_ERR",      false},
        {58, "RETIMER_FW_UPDATE_ERR",              false},
        {59, "RETIMER_FUSE_BURN_ERR",              false}
    };
    // clang-format on

    for (size_t i = 0; i < sizeof(packageErrors) / sizeof(packageErrors[0]); i++)
    {
        if (packageErrors[i].code == errorCode)
        {
            return &packageErrors[i];
        }
    }
    return NULL;
}

/* Names a code. Out-of-range values - the device supplies them, so they can be anything - name as unknown. */
inline const char* PackageErrorCodeToString(unsigned int errorCode)
{
    const PackageError* packageError = FindPackageError(errorCode);
    return packageError ? packageError->name : "Unknown error code";
}

/* Whether the value is a code the spec defines, as opposed to something the device made up. */
inline bool PackageErrorCodeIsKnown(unsigned int errorCode)
{
    return FindPackageError(errorCode) != NULL;
}

/* Whether the code concerns a specific component, for reports that carry an index; the rest have none. */
inline bool PackageErrorCodeHasComponentIndex(unsigned int errorCode)
{
    const PackageError* packageError = FindPackageError(errorCode);
    return packageError && packageError->hasComponentIndex;
}

#endif // PACKAGE_ERROR_CODES_H
