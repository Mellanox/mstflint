#ifndef PCI_LIBRARY_H
#define PCI_LIBRARY_H

#include <cstdint>
#include <mtcr.h>
#include "reg_access/reg_access_common.h"
#include "tools_layouts/reg_access_hca_layouts.h"
#include <vector>
#include <string>
#include <utility>
#include <map>

class PCILibrary
{
public:
    static void SetPCIDomain(int& failedToSetSegmentBase);

private:
    static void CheckPCIRegistersSupported(mfile* mf);
    static std::string GetV3FieldFromVPD(const std::string& dbdf);
    static void FindDirectNicDevice(std::map<std::string, std::uint32_t>& directNicDevice);
};

#endif