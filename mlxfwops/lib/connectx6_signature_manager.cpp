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
 

#include <map>

#include "signature_manager.h"
#include "tools_utils.h"
#include "fs4_ops.h"
#include "fs3_ops.h"
using namespace std;


bool ConnectX6FwOperationsSignatureManager::AddSignature(mfile* mf, Fs3Operations* imageOps, Flash *f, u_int32_t imageOffset)
{
(void)mf;
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    int signature_size = 3 * HMAC_SIGNATURE_LENGTH;
    uint8_t signature_data[3 * HMAC_SIGNATURE_LENGTH] = { 0 };
    //FOR BOOT, CRITICAL, NON-CRITICAL
    imageOps->GetImageCache().get(signature_data, imageOffset, signature_size);
    if (!f->write(imageOffset, signature_data, signature_size)) {
        return errmsg(MLXFW_FLASH_WRITE_ERR, "Failed to burn HMAC digest: %s", f->err());
    }
#else  
    (void)imageOps;
    (void)f;
    (void)imageOffset;
#endif
    return true;
};
