/*
 * NVIDIA_COPYRIGHT_BEGIN
 * 
 * Copyright (c) 2022, NVIDIA CORPORATION.  All rights reserved.
 * 
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 * 
 * NVIDIA_COPYRIGHT_END
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
