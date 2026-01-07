#ifndef DEVICE_TYPE_DETECTOR_H
#define DEVICE_TYPE_DETECTOR_H

#include <string>
#include <vector>
#include "mtcr.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"

class DeviceTypeDetector
{
public:
    static bool IsPCIESwitchDevice(const mfile* mf);
    static void AddSocketDirectDevices(const mfile* mf, std::vector<std::string>& asicDBDFTargets);
    static bool IsInInternalHost();

private:
    static bool IsUpstreamPortType(const mfile* mf, int pcieIndex);
    static std::string GetMacAddress(const mfile* mf);
};

#endif // DEVICE_TYPE_DETECTOR_H