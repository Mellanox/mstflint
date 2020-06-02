/*                                                                         
 * Copyright (C) Jan 2020 Mellanox Technologies Ltd. All rights reserved.   
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
        else if (deviceId == DeviceBlueField2) {
            return new Bluefield2FwOperationsSignatureManager();
        }
        else if (deviceId == DeviceConnectX6LX) {
            return new ConnectX6LXFwOperationsSignatureManager();
        }
        else {
            return new FwOperationsSignatureManager();
        }

    }

    ISignatureManager* CreateSignatureManager(chip_type_t chip) {
        if (chip == CT_BLUEFIELD) {
            return new BluefieldFwOperationsSignatureManager();
        }
        else if (chip == CT_CONNECTX6) {
            return new ConnectX6FwOperationsSignatureManager();
        }
        else if (chip == CT_CONNECTX6DX) {
            return new ConnectX6DXFwOperationsSignatureManager();
        }
        else if (chip == CT_BLUEFIELD2) {
            return new Bluefield2FwOperationsSignatureManager();
        }
        else if (chip == CT_CONNECTX6LX) {
            return new ConnectX6LXFwOperationsSignatureManager();
        }
        else {
            return new FwOperationsSignatureManager();
        }
    }
};
