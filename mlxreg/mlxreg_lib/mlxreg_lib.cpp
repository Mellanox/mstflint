/*
 * Copyright (c) 2019-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 */

#include <sstream>
#include "mlxreg_lib.h"
#include "cmdif/icmd_cif_open.h"
#ifndef MST_UL
#include <tools_layouts/adb_dbs.h>
#endif
#include <tools_layouts/prm_adb_db.h>
#include "common/tools_utils.h"
#include "common/tools_time.h"
#include <mlxreg_exception.h>

#define REG_ACCESS_UNION_NODE "access_reg_summary"

using namespace mlxreg;

template<bool dynamic>
const int _MlxRegLib_impl<dynamic>::RETRIES_COUNT = 3;
template<bool dynamic>
const int _MlxRegLib_impl<dynamic>::SLEEP_INTERVAL = 100;

template<bool dynamic>
_MlxRegLib_impl<dynamic>::_MlxRegLib_impl(mfile* mf, string extAdbFile, bool isExternal, bool batch_reg)
{
    _mf = mf;
    _isExternal = isExternal;
    _batch_reg = batch_reg;
    _currentNode = nullptr;
    try
    {
        if (_isExternal && extAdbFile == "")
        {
            dm_dev_id_t devID = getDevId();
            extAdbFile = PrmAdbDB::getDefaultDBName(devID);
        }
        initAdb(extAdbFile);
    }
    catch (MlxRegException& adbInitExp)
    {
        if (_adb)
        {
            delete _adb;
        }
        throw adbInitExp;
    }
    string unionNode = REG_ACCESS_UNION_NODE;
    string rootNode = unionNode + "_selector";
    if (_isExternal)
    {
        rootNode = rootNode + "_ext";
    }

    _regAccessRootNode = nullptr;
    if (!_batch_reg)
    {
        _regAccessRootNode = _adb->createLayout(rootNode, 2);
    }
    else
    {
        _regAccessRootNode = _adb->createLayout(rootNode);
    }
    if (!_regAccessRootNode)
    {
        throw MlxRegException("No supported access registers found");
    }
    _regAccessUnionNode = _regAccessRootNode->getChildByPath(unionNode);
    if (!_regAccessUnionNode)
    {
        throw MlxRegException("No supported access registers found");
    }
    if (!_regAccessUnionNode->isUnion())
    {
        throw MlxRegException("No supported access registers found");
    }
    try
    {
        _regAccessMap = _regAccessUnionNode->unionSelector->getEnumMap();
    }
    catch (AdbException& exp)
    {
        throw MlxRegException("Failed to extract registers info. %s", exp.what());
    }
    // Set error map
    std::map<int, std::string> errmap;
    errmap[MRLS_SUCCESS] = "Success";
    errmap[MRLS_GENERAL] = "General error";
    updateErrCodes(errmap);
}

/************************************
 * Function: ~_MlxRegLib_impl
 ************************************/
template<bool dynamic>
_MlxRegLib_impl<dynamic>::~_MlxRegLib_impl()
{
    if (!_batch_reg && _currentNode != nullptr)
    {
        delete _currentNode;
    }
    if (_regAccessRootNode)
    {
        delete _regAccessRootNode;
    }
    if (_adb)
    {
        delete _adb;
    }
}

template<bool dynamic>
dm_dev_id_t _MlxRegLib_impl<dynamic>::getDevId()
{
    return getDevId(_mf);
}

template<bool dynamic>
dm_dev_id_t _MlxRegLib_impl<dynamic>::getDevId(mfile* mf)
{
    dm_dev_id_t devID = DeviceUnknown;
    u_int32_t hwDevID = 0;
    u_int32_t hwChipRev = 0;

    if (dm_get_device_id(mf, &devID, &hwDevID, &hwChipRev))
    {
        throw MlxRegException("Failed to read device ID");
    }

    return devID;
}

template<bool dynamic>
bool _MlxRegLib_impl<dynamic>::isDeviceSupported(mfile* mf)
{
    dm_dev_id_t devID = getDevId(mf);
    return !dm_is_4th_gen(devID);
}

template<bool dynamic>
void _MlxRegLib_impl<dynamic>::initAdb(string extAdbFile)
{
    _adb = new Adb();
    if (extAdbFile != "")
    {
        if (!_adb->load(extAdbFile, false, false))
        {
            throw MlxRegException("Failure in loading Adabe file. %s", _adb->getLastError().c_str());
        }
    }
    else
    {
        throw MlxRegException("No Adabe was provided, please provide Adabe file to continue");
    }
}

/************************************
 * Function: findAdbNode
 ************************************/
template<bool dynamic>
typename _MlxRegLib_impl<dynamic>::AdbInstance* _MlxRegLib_impl<dynamic>::findAdbNode(string name)
{
    if (_regAccessMap.find(name) == _regAccessMap.end())
    {
        throw MlxRegException("Can't find access register name: %s", name.c_str());
    }
    auto found_node = _regAccessUnionNode->getUnionSelectedNodeName(name);

    if (!_batch_reg)
    {
        found_node = _adb->createLayout(found_node->nodeDesc->name);
    }

    return found_node;
}

/************************************
 * Function: findAdbNode
 ************************************/
template<bool dynamic>
typename _MlxRegLib_impl<dynamic>::AdbInstance* _MlxRegLib_impl<dynamic>::findAdbNode(uint64_t id)
{
    try
    {
        auto found_node = _regAccessUnionNode->getUnionSelectedNodeName(id);
        if (!_batch_reg)
        {
            found_node = _adb->createLayout(found_node->nodeDesc->name);
        }

        return found_node;
    }
    catch (AdbException& er)
    {
        throw MlxRegException("Can't find access register with id: %d", id);
    }
}

/************************************
 * Function: showRegister
 ************************************/
template<bool dynamic>
MlxRegLibStatus _MlxRegLib_impl<dynamic>::showRegister(string regName, std::vector<AdbInstance*>& fields)
{
    AdbInstance* adbNode = findAdbNode(regName);
    fields = adbNode->getLeafFields(true);
    return MRLS_SUCCESS;
}

/************************************
 * Function: showRegisters
 ************************************/
template<bool dynamic>
MlxRegLibStatus _MlxRegLib_impl<dynamic>::showRegisters(std::vector<string>& regs)
{
    for (typename std::map<string, u_int64_t>::iterator it = _regAccessMap.begin(); it != _regAccessMap.end(); ++it)
    {
        regs.push_back(it->first);
    }
    return MRLS_SUCCESS;
}

/************************************
 * Function: sendMaccessReg
 ************************************/
template<bool dynamic>
int _MlxRegLib_impl<dynamic>::sendMaccessReg(u_int16_t regId, int method, std::vector<u_int32_t>& data)
{
    int status = 0;
    int rc = -1;
    std::vector<u_int32_t> temp_data;
    copy(data.begin(), data.end(), back_inserter(temp_data));
    int i = RETRIES_COUNT;
    do
    {
        rc = maccess_reg(_mf,
                         regId,
                         (maccess_reg_method_t)method,
                         (u_int32_t*)&data[0],
                         (sizeof(u_int32_t) * data.size()),
                         (sizeof(u_int32_t) * data.size()),
                         (sizeof(u_int32_t) * data.size()),
                         &status);
        if ((rc != ME_ICMD_STATUS_IFC_BUSY && status != ME_REG_ACCESS_BAD_PARAM) || !(_mf->flags & MDEVS_REM))
        {
            break;
        }
        data.clear();
        copy(temp_data.begin(), temp_data.end(), back_inserter(data));
        msleep(SLEEP_INTERVAL);
    } while (i-- > 0);
    temp_data.clear();
    return rc;
}

/************************************
 * Function: sendMaccessReg
 ************************************/
template<bool dynamic>
int _MlxRegLib_impl<dynamic>::sendMaccessReg(u_int16_t regId, int method, void* data, uint32_t size)
{
    int status = 0;
    int rc = -1;
    int i = RETRIES_COUNT;
    do
    {
        rc = maccess_reg(_mf, regId, (maccess_reg_method_t)method, (u_int32_t*)data, size, size, size, &status);
        if ((rc != ME_ICMD_STATUS_IFC_BUSY && status != ME_REG_ACCESS_BAD_PARAM) || !(_mf->flags & MDEVS_REM))
        {
            break;
        }
        msleep(SLEEP_INTERVAL);
    } while (i-- > 0);
    return rc;
}

/************************************
 * Function: sendRegister
 ************************************/
template<bool dynamic>
MlxRegLibStatus _MlxRegLib_impl<dynamic>::sendRegister(string regName, int method, std::vector<u_int32_t>& data)
{
    u_int16_t regId = (u_int16_t)_regAccessMap.find(regName)->second;
    int rc;
    rc = sendMaccessReg(regId, method, data);
    if (rc)
    {
        char error_msg[200];
        snprintf(error_msg, sizeof(error_msg), "Failed to send access register: %s", m_err2str((MError)rc));
        if (_mf->icmd.syndrome)
        {
            snprintf(error_msg + strlen(error_msg),
                     sizeof(error_msg) - strlen(error_msg),
                     " and the syndrome number is: 0x%X",
                     (_mf->icmd.syndrome));
        }
        throw MlxRegException(error_msg);
    }
    return MRLS_SUCCESS;
}

/************************************
 * Function: sendRegister
 ************************************/
template<bool dynamic>
MlxRegLibStatus _MlxRegLib_impl<dynamic>::sendRegister(u_int16_t regId, int method, std::vector<u_int32_t>& data)
{
    int rc;
    rc = sendMaccessReg(regId, method, data);
    if (rc)
    {
        throw MlxRegException("Failed send access register: %s", m_err2str((MError)rc));
    }
    return MRLS_SUCCESS;
}

/************************************
 * Function: sendRegister
 ************************************/
template<bool dynamic>
MlxRegLibStatus _MlxRegLib_impl<dynamic>::sendRegister(u_int16_t regId, int method, void* data, uint32_t size)
{
    int rc;
    rc = sendMaccessReg(regId, method, data, size);
    if (rc)
    {
        throw MlxRegException("Failed send access register: %s", m_err2str((MError)rc));
    }
    return MRLS_SUCCESS;
}

/************************************
 * Function: getLastErrMsg
 ************************************/
template<bool dynamic>
string _MlxRegLib_impl<dynamic>::getLastErrMsg()
{
    std::stringstream sstm;
    int lastErrCode = getLastErrCode();
    string errCodeStr = err2Str(lastErrCode);
    string errStr = err();
    sstm << errCodeStr;
    if (errStr != errCodeStr)
    {
        sstm << ": " << errStr;
    }
    return sstm.str();
}

/************************************
 * Function: isRegSizeSupported
 ************************************/
template<bool dynamic>
bool _MlxRegLib_impl<dynamic>::isRegSizeSupported(string regName)
{
    AdbInstance* adbNode = _regAccessUnionNode->getUnionSelectedNodeName(regName);
    return (((adbNode->get_size() >> 3) <= (u_int32_t)mget_max_reg_size(_mf, MACCESS_REG_METHOD_SET)) ||
            ((adbNode->get_size() >> 3) <= (u_int32_t)mget_max_reg_size(_mf, MACCESS_REG_METHOD_GET)));
}

/************************************
 * Function: isAccessRegisterSupported
 ************************************/
 template<bool dynamic>
 void _MlxRegLib_impl<dynamic>::isAccessRegisterSupported(mfile* mf)
 {
     int                                    status;
     struct icmd_hca_icmd_query_cap_general icmd_cap;
     int                                    i = RETRIES_COUNT;
 
     if ((mf->tp == MST_FWCTL_CONTROL_DRIVER) || (mf->tp == MST_NVML)) {
         return;
     }
 
     do{
         memset(&icmd_cap, 0, sizeof(icmd_cap));
         status = get_icmd_query_cap(mf, &icmd_cap);
         if (!(status || (icmd_cap.allow_icmd_access_reg_on_all_registers == 0))) {
             break;
         }
         msleep(SLEEP_INTERVAL);
     } while (i-- > 0);
 
     if (status || (icmd_cap.allow_icmd_access_reg_on_all_registers == 0)) {
         throw MlxRegException("FW burnt on device does not support generic access register");
     }
 }

/************************************
 * Function: handle_buffer_endianness
 ************************************/
template<bool dynamic>
void _MlxRegLib_impl<dynamic>::handle_buffer_endianness(void* buffer, uint32_t size)
{
    for (uint32_t* addr = (uint32_t*)buffer; addr < (uint32_t*)buffer + size / sizeof(uint32_t); ++addr)
    {
        *addr = __cpu_to_be32(*addr);
    }
}
/************************************
 * Function: isAccessRegisterGMPSupported
 ************************************/
template<bool dynamic>
bool _MlxRegLib_impl<dynamic>::isAccessRegisterGMPSupported(maccess_reg_method_t reg_method)
{
    return (bool)(supports_reg_access_gmp(_mf, reg_method));
}

/************************************
 * Function: isIBDevice
 ************************************/
template<bool dynamic>
bool _MlxRegLib_impl<dynamic>::isIBDevice()
{
    return (bool)(_mf->flags & MDEVS_IB);
}

/************************************
 * Function: dumpRegisterData
 ************************************/
template<bool dynamic>
MlxRegLibStatus _MlxRegLib_impl<dynamic>::dumpRegisterData(string output_file_name, std::vector<u_int32_t>& data)
{
    FILE* outputFile = fopen(output_file_name.c_str(), "w");
    if (outputFile)
    {
        for (typename std::vector<u_int32_t>::size_type i = 0; i != data.size(); i++)
        {
            fprintf(outputFile, "%08x\n", CPU_TO_BE32(data[i]));
        }
    }
    else
    {
        throw MlxRegException("Failed to open file");
    }
    fclose(outputFile);
    return MRLS_SUCCESS;
}

// Static member template instantiations
template<>
map<dm_dev_id_t, _Adb_impl<false, uint32_t>*> _MlxRegLib_impl<false>::_adbDBs;
template<>
map<dm_dev_id_t, _Adb_impl<true, uint32_t>*> _MlxRegLib_impl<true>::_adbDBs;

// Explicit template instantiations
namespace mlxreg
{
template class _MlxRegLib_impl<false>;
template class _MlxRegLib_impl<true>;
} // namespace mlxreg
