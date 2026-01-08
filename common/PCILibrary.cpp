/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

 #include "PCILibrary.h"
 #if defined(__WIN__) || defined(__FreeBSD__)
 void PCILibrary::SetPCIDomain(void)
 {
     return;
 }
 #else // not defined(__WIN__) || defined(__FreeBSD__)
 #include "reg_access/mcam_capabilities.h"
 #include "reg_access/reg_ids.h"
 #include "mft_core/mft_core_utils/logger/Logger.h"
 #include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
 
 using namespace mft_core;
 
 void PCILibrary::CheckPCIRegistersSupported(mfile* mf)
 {
     bool mpegc_supported = false;
     bool mpir_supported = false;
     reg_access_status_t rc = ME_OK;
     std::string dbdf = std::to_string(mf->dinfo->pci.domain) + ":" + std::to_string(mf->dinfo->pci.bus) + ":" +
                        std::to_string(mf->dinfo->pci.dev) + "." + std::to_string(mf->dinfo->pci.func);
     rc = isRegisterValidAccordingToMcamReg(mf, REG_ID_MPEGC, &mpegc_supported);
     if (rc != ME_OK)
     {
         LOG_AND_THROW_MFT_ERROR(std::string("Failed to check if MPEGC register is supported for dbdf: ") + dbdf);
     }
     if (!mpegc_supported)
     {
         LOG_AND_THROW_MFT_ERROR(std::string("MPEGC register is not supported for dbdf: ") + dbdf);
     }
     rc = isRegisterValidAccordingToMcamReg(mf, REG_ID_MPIR, &mpir_supported);
     if (rc != ME_OK)
     {
         LOG_AND_THROW_MFT_ERROR(std::string("Failed to check if MPIR register is supported for dbdf: ") + dbdf);
     }
     if (!mpir_supported)
     {
         LOG_AND_THROW_MFT_ERROR(std::string("MPIR register is not supported for dbdf: ") + dbdf);
     }
 }
 
 std::string PCILibrary::GetV3FieldFromVPD(const std::string& dbdf)
 {
     std::string v3 = "";
     std::string cmd = "lspci -s " + dbdf + " -vvv";
     FILE* pipe = popen(cmd.c_str(), "r");
     if (pipe)
     {
         char buffer[512];
         while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
         {
             std::string line(buffer);
             if (line.find("[V3]") != std::string::npos)
             {
                 if (!line.empty() && line.back() == '\n')
                 {
                     line.pop_back();
                 }
                 auto last_space = line.find_last_of(" ");
                 if (last_space != std::string::npos && last_space + 1 < line.size())
                 {
                     v3 = line.substr(last_space + 1);
                 }
                 break;
             }
         }
         pclose(pipe);
     }
     else
     {
         LOG_AND_THROW_MFT_ERROR(std::string("Failed to execute lspci command for device: ") + dbdf);
     }
     if (v3.empty())
     {
         LOG_AND_THROW_MFT_ERROR(std::string("No V3 field found in VPD for device: ") + dbdf);
     }
     return v3;
 }
 
 void PCILibrary::FindDirectNicDevice(std::map<std::string, std::uint32_t>& directNicDevice)
 {
     FILE* pipe = popen("lspci -D -d 15b3:2100", "r");
     if (pipe)
     {
         char buffer[256];
         while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
         {
             std::string line(buffer);
             LOG.Debug(line);
 
             // The DBDF is the first token before the space
             std::size_t first_space = line.find(' ');
             if (first_space != std::string::npos)
             {
                 std::string dbdf = line.substr(0, first_space);
                 std::string domain_str = dbdf.substr(0, dbdf.find(':'));
                 std::uint32_t domain = std::stoul(domain_str, nullptr, 16);
                 LOG.Debug(std::string("Found direct nic device: ") + dbdf + " with domain: " + std::to_string(domain));
                 std::string v3 = GetV3FieldFromVPD(dbdf);
                 directNicDevice[v3] = domain;
             }
         }
         pclose(pipe);
     }
     else
     {
         LOG_AND_THROW_MFT_ERROR(std::string("Failed to execute lspci command for direct nic devices"));
     }
 }
 
 void PCILibrary::SetPCIDomain(void)
 {
     int numDevices = 0;
     reg_access_status_t rc = ME_OK;
     int field_select = 0x80; // Set segment base and segment valid
     dev_info* pciDevices = mdevices_info(MDEVS_TAVOR_CR, &numDevices);
     if (!pciDevices)
     {
         LOG_AND_THROW_MFT_ERROR(std::string("Failed to get devices info. numDevices: ") + std::to_string(numDevices));
     }
 
     std::map<std::string, std::uint32_t> directNicDevice;
     PCILibrary::FindDirectNicDevice(directNicDevice);
     LOG.Debug("Number of found direct nic devices: " + std::to_string(directNicDevice.size()));
     for (int count = 0; count < numDevices; count++)
     {
         mfile* mf = mopen(pciDevices[count].dev_name);
         if (!mf)
         {
             LOG.Error(std::string("Failed to open device: ") + pciDevices[count].dev_name);
             continue;
         }
         try
         {
             CheckPCIRegistersSupported(mf);
         }
         catch (const MftGeneralException& e)
         {
             mclose(mf);
             continue;
         }
         struct reg_access_hca_mpqd_reg_ext mpqd;
         struct reg_access_hca_mpegc_reg_ext mpegc;
         memset(&mpqd, 0, sizeof(struct reg_access_hca_mpqd_reg_ext));
         memset(&mpegc, 0, sizeof(struct reg_access_hca_mpegc_reg_ext));
         char dbdf_buf[32];
         snprintf(dbdf_buf, sizeof(dbdf_buf), "%04x:%02x:%02x.%x", pciDevices[count].pci.domain,
                  pciDevices[count].pci.bus, pciDevices[count].pci.dev, pciDevices[count].pci.func);
         std::string dbdf(dbdf_buf);
         mpqd.DPNv = 1;
         rc = reg_access_mpqd(mf, REG_ACCESS_METHOD_GET, &mpqd);
         if (rc)
         {
             LOG.Error(std::string("Failed to get requester PCIe index for dbdf: ") + dbdf);
             mclose(mf);
             continue;
         }
         mpegc.segment_base = pciDevices[count].pci.domain;
         mpegc.seg_valid = 1;
         mpegc.pcie_index = mpqd.requester_pcie_index;
         mpegc.DPNv = 1;
         mpegc.field_select = field_select;
         LOG.Debug(std::string("Setting segment base for dbdf: ") + dbdf + " with segment base: " +
                   std::to_string(mpegc.segment_base) + " and pcie index: " + std::to_string(mpegc.pcie_index));
         rc = reg_access_mpegc(mf, REG_ACCESS_METHOD_SET, &mpegc);
         if (rc)
         {
             LOG.Error(std::string("Failed to set segment base for dbdf: ") + dbdf);
             mclose(mf);
             continue;
         }
 
         // According to arch (Oren S), mpir.sdm is not relevant for direct nic devices.
         if (!directNicDevice.empty())
         {
             std::string endPointV3 = GetV3FieldFromVPD(dbdf);
             if (directNicDevice.find(endPointV3) != directNicDevice.end())
             {
                 memset(&mpegc, 0, sizeof(struct reg_access_hca_mpegc_reg_ext));
                 mpegc.segment_base = directNicDevice[endPointV3];
                 mpegc.seg_valid = 1;
                 mpegc.field_select = field_select;
                 // According to arch (Oren S), when its direct nic, pci index < 1
                 if (mpqd.requester_pcie_index > 1)
                 {
                     LOG.Error(std::string("Direct nic device: ") + dbdf +
                               " has pci index > 1, but arch requires pci index < 1");
                     break;
                 }
                 else
                 {
                     mpegc.pcie_index = (mpqd.requester_pcie_index == 1) ? 0 : 1;
                 }
                 mpegc.DPNv = 1;
                 LOG.Debug(std::string("Setting segment base for direct nic device: ") +
                           std::to_string(directNicDevice[endPointV3]) + " with segment base: " +
                           std::to_string(mpegc.segment_base) + " and pcie index: " + std::to_string(mpegc.pcie_index));
                 rc = reg_access_mpegc(mf, REG_ACCESS_METHOD_SET, &mpegc);
                 if (rc)
                 {
                     LOG.Error(std::string("Failed to set segment base for direct nic device: ") +
                               std::to_string(directNicDevice[endPointV3]) +
                               " with segment base: " + std::to_string(mpegc.segment_base) +
                               " and pcie index: " + std::to_string(mpegc.pcie_index));
                     break;
                 }
                 LOG.Debug(std::string("Successfully set segment base for direct nic device: ") +
                           std::to_string(directNicDevice[endPointV3]) + " with segment base: " +
                           std::to_string(mpegc.segment_base) + " and pcie index: " + std::to_string(mpegc.pcie_index));
             }
         }
         mclose(mf);
     }
     free(pciDevices);
 }
 #endif