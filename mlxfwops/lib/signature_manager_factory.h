#pragma once

#include "signature_manager.h"
#include "dev_mgt/tools_dev_types.h"

class SignatureManagerFactory
{
public:
    static SignatureManagerFactory* GetInstance() {
        static SignatureManagerFactory obj;
        return &obj;
    }

    ISignatureManager* CreateSignatureManager(u_int32_t hwDevId, u_int32_t hwRevId) {
        dm_dev_id_t deviceId = DeviceUnknown;
        if (dm_get_device_id_offline(hwDevId, hwRevId, &deviceId)) {
            printf("Failed to identify the device - Can not create SignatureManager!\n");
            return (ISignatureManager*)NULL;
        }

        if (deviceId == DeviceBlueField) {
            return new BluefieldFwOperationsSignatureManager();
        }
        else if (deviceId == DeviceConnectX6) {
            return new ConnectX6FwOperationsSignatureManager();
        }
        else if (deviceId == DeviceConnectX6DX) {
            return new ConnectX6DXFwOperationsSignatureManager();
        }
        else {
            return new FwOperationsSignatureManager();
        }

    }
};
