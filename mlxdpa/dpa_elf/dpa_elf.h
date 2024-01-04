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

#include <stdio.h>
#include <elf.h>

#define DPA_OBJ_SECTION_NAME          ".dpa_obj"
#define DPA_BIN_SECTION_PREFIX        ".dpa_bin_"
#define DPA_SIG_NAME_SECTION_PREFIX   ".dpa_sig_name_"

#define SIG_SECTION_NAME_MAX_LEN    256

typedef Elf64_Ehdr     ELFHeader;
typedef Elf64_Shdr     SectionHeader;
typedef Elf64_Off      ELFOffset;

typedef struct {
  char*        name;
  Elf64_Off    offset;
  uint64_t     size;
} AppHandle;

typedef struct {
  AppHandle* table;
  uint64_t   count;
} AppTable;


#ifdef __cplusplus
extern "C" {
#endif
/// \brief Returns an AppTable object containing a 
/// list of AppHandle objects which contain the name,
/// offset, size and signature section name for all apps
///
/// \param[in] file File handle of an executable containing DPA apps
/// \return AppTable object
AppTable getAppList(FILE* file);

/// \brief Updates the signature blob section name in the section which
/// is reserved to contain the signature section name. This function
/// asserts if the sigSectionName string length is greater than 255 bytes or
/// if the file handle is not open for both reading and writing
///
/// \param[in] fHandle File handle of the executable with read and write permission
/// \param[in] appName Name of the app
/// \param[in] sigSectionName Name of the signature blob section
/// \return Returns 0 on success or non-zero value otherwise
int updateSigSectionName(FILE* fHandle, char* appName, char* sigSectionName);
#ifdef __cplusplus
}
#endif
