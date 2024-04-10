/*
 * NVIDIA_COPYRIGHT_BEGIN
 *
 * Copyright (c) 2022-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
 *
 * NVIDIA_COPYRIGHT_END
 */

#include <stdio.h>
#include <elf.h>

#define DPA_OBJ_SECTION_NAME          ".dpa_obj"
#define DPA_BIN_SECTION_PREFIX        ".dpa_bin_"
#define DPA_SIG_SECTION_PREFIX        ".dpa_sig_"

#define DPA_SIG_SECTION_DEFAULT_LEN 4096

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

/// \brief Writes sigSection to given DPA app's reserved signature section.
///
/// \param[in] fHandle File handle of the executable with read and write
/// permission.
/// \param[in] appName Name of the app.
/// \param[in] sigSection signature section blob.
/// \param[in] size size of the sigSection buffer.
/// \retval 0 successfully updated signature blob.
/// \retval 1 sigSEction size larger than reserved signature section in file.
/// \retval 2 NULL pointer passed as argument.
/// \retval 3 fHandle not available for read and write.
/// \retval 4 signature section not found in file.
int updateSignatureData(FILE *fHandle, char *appName, uint8_t *sigSection,
                        size_t sigSectionSize);

#ifdef __cplusplus
}
#endif
