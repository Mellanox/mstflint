/*
 * Copyright(c) 2025 NVIDIA CORPORATION & AFFILIATES.All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.You may choose to be licensed under the terms of the GNU
 * General Public License(GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 * Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 * -Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 * -Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and / or other materials
 * provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <stdio.h>
#include <elf.h>

#define DPA_OBJ_SECTION_NAME          ".dpa_obj"
#define DPA_BIN_SECTION_PREFIX        ".dpa_bin_"
#define DPA_SIG_SECTION_PREFIX        ".dpa_sig_"


#define DPA_SIG_SECTION_DEFAULT_LEN 65536

typedef Elf64_Ehdr     ELFHeader;
typedef Elf64_Shdr     SectionHeader;
typedef Elf64_Off      ELFOffset;

#ifndef CPU_ENUM
#define CPU_ENUM
enum DPA_ID {
  NV_DPA_GENERIC = 0,
  NV_DPA_CX7 = 1,
  NV_DPA_BF3 = 2,
  NV_DPA_CX8 = 3,
  NV_DPA_CX9 = 4,
  NV_DPA_UNKNOWN = 0xFFFF,
  NV_DPA_LAST = NV_DPA_UNKNOWN
};
#endif

typedef struct {
  enum DPA_ID ID;
  Elf64_Off    offset;
  uint64_t     size;
} DevObjHandle;

typedef struct {
  char*         name;
  uint64_t      arch_count;
  DevObjHandle* ObjTable;
} AppHandle;

typedef struct {
  AppHandle* table;
  uint64_t   count;
} AppTable;

#ifdef __cplusplus
extern "C" {
#endif
/// \brief Returns an AppTable object containing a 
/// list of AppHandle objects which for each app contains its contain the name,
/// how many architecture variants are available and a list of device objects
/// for each architecture. The list contains the device id, offset and size.
///
/// \param[in] file File handle of an executable containing DPA apps
/// \return AppTable object
AppTable getAppList(FILE* file);

void freeAppList(AppTable appTable);

enum UPDATE_SIGN_RESULT {
  UPDATE_SIGN_OK  = 0,
  UPDATE_SIGN_SIGSIZE,
  UPDATE_SIGN_NULLARG,
  UPDATE_SIGN_FILEERR,
  UPDATE_SIGN_NOSEC,
  UPDATE_SIGN_FATERR
};

/// \brief Writes sigSection to given DPA app's reserved signature section
/// for a given device.
///
/// \param[in] fHandle File handle of the executable with read and write
/// permission.
/// \param[in] appName Name of the app.
/// \param[in] ID device id
/// \param[in] sigSection signature section blob.
/// \param[in] size size of the sigSection buffer.
/// \retval 0 successfully updated signature blob.
/// \retval 1 sigSEction size larger than reserved signature section in file.
/// \retval 2 NULL pointer passed as argument.
/// \retval 3 fHandle not available for read and write.
/// \retval 4 signature section not found in file.
/// \retval 5 invalid multi arch signature section
int updateSignatureData(FILE *fHandle, char *appName, enum DPA_ID ID,
                        uint8_t *sigSection, size_t sigSectionSize);

#ifdef __cplusplus
}
#endif
