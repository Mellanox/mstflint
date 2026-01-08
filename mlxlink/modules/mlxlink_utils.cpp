/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "mlxlink_utils.h"

void termHandler(int sig)
{
    printf("Interrupted, Exiting...\n");
    exit(sig);
}

u_int32_t findMaxKey(vector<string> keys)
{
    u_int32_t maxKeySize = 0;
    for (vector<string>::iterator it = keys.begin(); it != keys.end(); ++it)
    {
        if ((*it).length() > maxKeySize)
        {
            maxKeySize = (*it).length();
        }
    }
    return maxKeySize;
}

string convertIntToHexString(int toConvert)
{
    stringstream hexStr;
    hexStr << hex << toConvert;
    return hexStr.str();
}

string deleteLastChar(const string& s, u_int32_t numOfCharsToRemove)
{
    string newStr = s;
    if (newStr.size() && newStr.size() > numOfCharsToRemove)
    {
        newStr.erase(newStr.size() - numOfCharsToRemove);
    }
    return newStr;
}

float convertFloatPrec(float value)
{
    string s;
    char strVal[32];
    float res;
    u_int32_t prec = 3;

    snprintf(strVal, sizeof(strVal), "%.*f", prec, value);
    res = stof(string(strVal));

    return res;
}

string getStringFromVector(vector<string> values)
{
    string s;
    for (vector<string>::const_iterator i = values.begin(); i != values.end(); ++i)
    {
        s += *i + ',';
    }
    return deleteLastChar(s);
}

string getStringFromVector(vector<float> values)
{
    string s;
    char strVal[32];
    u_int32_t prec = 0;
    for (vector<float>::const_iterator i = values.begin(); i != values.end(); ++i)
    {
        if (abs((*i - ((int)*i))) > 0)
        {
            prec = 3;
        }
        else
        {
            prec = 0;
        }
        snprintf(strVal, sizeof(strVal), "%.*f", prec, *i);
        s += string(strVal) + ',';
    }
    return deleteLastChar(s);
}

u_int64_t add32BitTo64(u_int32_t value1, u_int32_t value2)
{
    return (((u_int64_t)value1) << 32 | value2);
}

string getFullString(u_int64_t intVal)
{
    string strVal = "";

    if (intVal)
    {
        for (int i = 56; i > -1; i -= 8)
        {
            strVal.push_back((char)(intVal >> i));
        }
    }
    else
    {
        strVal = "N/A";
    }

    return strVal;
}

string status2Color(u_int32_t status)
{
    return (status == 0 || status == 1023) ? ANSI_COLOR_GREEN : ANSI_COLOR_RED;
}

string getLoopbackColor(u_int32_t loopbackMode)
{
    switch (loopbackMode)
    {
        case LOOPBACK_MODE_NO:
            return ANSI_COLOR_GREEN;
            break;

        case LOOPBACK_MODE_REMOTE:
            return ANSI_COLOR_CYAN;
            break;

        case LOOPBACK_MODE_LOCAL:
            return ANSI_COLOR_BLUE;
            break;

        case LOOPBACK_MODE_EXTERNAL:
            return ANSI_COLOR_MAGENTA;

        case LOOPBACK_MODE_LL:
            return ANSI_COLOR_YELLOW;
        default:
            return ANSI_COLOR_RED;
    }
    return ANSI_COLOR_RED;
}

string getAnDisableColor(u_int32_t anDisable)
{
    switch (anDisable)
    {
        case AN_DISABLE_NORMAL:
            return ANSI_COLOR_GREEN;

        case AN_DISABLE_FORCE:
            return ANSI_COLOR_BLUE;

        default:
            return ANSI_COLOR_RED;
    }
}

string IBSupportedSpeeds2Str(u_int32_t mask)
{
    string maskStr = "";

    if (mask & IB_LINK_SPEED_XDR)
    {
        maskStr += "XDR,";
    }
    if (mask & IB_LINK_SPEED_NDR)
    {
        maskStr += "NDR,";
    }
    if (mask & IB_LINK_SPEED_HDR)
    {
        maskStr += "HDR,";
    }
    if (mask & IB_LINK_SPEED_EDR)
    {
        maskStr += "EDR,";
    }
    if (mask & IB_LINK_SPEED_FDR)
    {
        maskStr += "FDR,";
    }
    if (mask & IB_LINK_SPEED_FDR10)
    {
        maskStr += "FDR10,";
    }
    if (mask & IB_LINK_SPEED_QDR)
    {
        maskStr += "QDR,";
    }
    if (mask & IB_LINK_SPEED_DDR)
    {
        maskStr += "DDR,";
    }
    if (mask & IB_LINK_SPEED_SDR)
    {
        maskStr += "SDR,";
    }

    return deleteLastChar(maskStr);
}

string EthSupportedSpeeds2Str(u_int32_t int_mask)
{
    string maskStr = "";

    if ((int_mask & ETH_LINK_SPEED_100G_CR4) || (int_mask & ETH_LINK_SPEED_100G_KR4) ||
        (int_mask & ETH_LINK_SPEED_100G_SR4) || (int_mask & ETH_LINK_SPEED_100G_LR4))
    {
        maskStr += "100G,";
    }
    if ((int_mask & ETH_LINK_SPEED_56G_R4) || (int_mask & ETH_LINK_SPEED_56G_CR4) ||
        (int_mask & ETH_LINK_SPEED_56G_KR4))
    {
        maskStr += "56G,";
    }
    if ((int_mask & ETH_LINK_SPEED_50G_CR2) || (int_mask & ETH_LINK_SPEED_50G_KR2) ||
        (int_mask & ETH_LINK_SPEED_50G_SR2) || (int_mask & ETH_LINK_SPEED_50G_KR4))
    {
        maskStr += "50G,";
    }
    if ((int_mask & ETH_LINK_SPEED_40G_CR4) || (int_mask & ETH_LINK_SPEED_40G_KR4) ||
        (int_mask & ETH_LINK_SPEED_40G_SR4) || (int_mask & ETH_LINK_SPEED_40G_LR4))
    {
        maskStr += "40G,";
    }
    if ((int_mask & ETH_LINK_SPEED_25G_CR) || (int_mask & ETH_LINK_SPEED_25G_KR) || (int_mask & ETH_LINK_SPEED_25G_SR))
    {
        maskStr += "25G,";
    }
    if (int_mask & ETH_LINK_SPEED_20G_KR2)
    {
        maskStr += "20G,";
    }
    if ((int_mask & ETH_LINK_SPEED_10G_CR) || (int_mask & ETH_LINK_SPEED_10G_KR) ||
        (int_mask & ETH_LINK_SPEED_10G_SR) || (int_mask & ETH_LINK_SPEED_10G_LR) ||
        (int_mask & ETH_LINK_SPEED_10G_CX4) || (int_mask & ETH_LINK_SPEED_10G_KX4) ||
        (int_mask & ETH_LINK_SPEED_10G_BaseT))
    {
        maskStr += "10G,";
    }
    if ((int_mask & ETH_LINK_SPEED_1000_SGMII) || (int_mask & ETH_LINK_SPEED_1000_KX) ||
        (int_mask & ETH_LINK_SPEED_1000_BaseT))
    {
        maskStr += "1G,";
    }
    if (int_mask & ETH_LINK_SPEED_100_BaseTx)
    {
        maskStr += "100M,";
    }
    if (int_mask & ETH_LINK_SPEED_10M)
    {
        maskStr += "10M,";
    }

    return deleteLastChar(maskStr);
}

string EthExtSupportedSpeeds2Str(u_int32_t int_mask)
{
    string maskStr = "";
    if (int_mask & ETH_LINK_SPEED_EXT_200GAUI_1)
    {
        maskStr += "200G_1X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_400GAUI_2)
    {
        maskStr += "400G_2X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_800GAUI_4)
    {
        maskStr += "800G_4X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_1_6TAUI_8)
    {
        maskStr += "1600G_8X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_800GAUI_8)
    {
        maskStr += "800G_8X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_400GAUI_4)
    {
        maskStr += "400G_4X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_400GAUI_8)
    {
        maskStr += "400G_8X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_200GAUI_2)
    {
        maskStr += "200G_2X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_200GAUI_4)
    {
        maskStr += "200G_4X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_100GAUI_1)
    {
        maskStr += "100G_1X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_100GAUI_2)
    {
        maskStr += "100G_2X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_CAUI_4)
    {
        maskStr += "100G_4X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_50GAUI_1)
    {
        maskStr += "50G_1X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_50GAUI_2)
    {
        maskStr += "50G_2X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_XLAUI_4)
    {
        maskStr += "40G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_25GAUI_1)
    {
        maskStr += "25G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_XFI)
    {
        maskStr += "10G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_5GBASE_R)
    {
        maskStr += "5G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_2_5GBASE_X)
    {
        maskStr += "2.5G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_1000BASE_X)
    {
        maskStr += "1G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_SGMII_100M)
    {
        maskStr += "100M,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_SGMII_10M)
    {
        maskStr += "10M,";
    }

    return deleteLastChar(maskStr);
}

string SupportedSpeeds2Str(u_int32_t proto_active, u_int32_t mask, bool extended, bool isXdrSlowActive)
{
    if (isXdrSlowActive)
    {
        return "NDR";
    }
    switch (proto_active)
    {
        case IB:
            return IBSupportedSpeeds2Str(mask);
        case ETH:
            if (extended)
            {
                return EthExtSupportedSpeeds2Str(mask);
            }
    }

    return EthSupportedSpeeds2Str(mask);
}

string getOui(u_int32_t oui)
{
    string ouiStr;
    switch (oui)
    {
        case OTHER:
            ouiStr = "Other";
            break;

        case MELLANOX:
            ouiStr = "Mellanox";
            break;

        case KNOWN_OUI:
            ouiStr = "Known OUI";
            break;

        case NVIDIA:
            ouiStr = "Nvidia";
            break;

        default:
            ouiStr = "Other";
    }
    return ouiStr;
}

int getBitvalue(u_int32_t mask, int idx)
{
    return (1 & (mask >> (idx - 1)));
}

string getMaxPowerStr(u_int32_t maxPower)
{
    float maxPowerValue = maxPower * 0.25;

    char frmtValue[64];
    sprintf(frmtValue, "%.1f W max", maxPowerValue);
    return string(frmtValue);
}

string getPowerClassStringValue(u_int32_t cableIdentifier, u_int32_t powerClass, MlxlinkMaps* mlxlinkMaps)
{
    switch (cableIdentifier)
    {
        case IDENTIFIER_SFP_DD:
            return mlxlinkMaps->_sfpddPowerClass[powerClass];
        case IDENTIFIER_QSFP_DD:
        case IDENTIFIER_OSFP:
            return mlxlinkMaps->_qsfpddOsfpPowerClass[powerClass];
        default:
            try
            {
                return mlxlinkMaps->_sfpQsfpPowerClass[powerClass];
            }
            catch (const std::exception& e)
            {
                return "N/A";
            }
    }
}

float getPowerClassValue(u_int32_t cableIdentifier, u_int32_t powerClass, MlxlinkMaps* mlxlinkMaps)
{
    switch (cableIdentifier)
    {
        case IDENTIFIER_SFP_DD:
            return mlxlinkMaps->_sfpddPowerClassToValue[powerClass];
        case IDENTIFIER_QSFP_DD:
        case IDENTIFIER_OSFP:
            return mlxlinkMaps->_qsfpddPowerClassToValue[powerClass];
        default:
            return 0;
    }
}

string getPowerClassStr(MlxlinkMaps* mlxlinkMaps, u_int32_t cableIdentifier, u_int32_t powerClass)
{
    string powerClassStr = "N/A";
    string val = getPowerClassStringValue(cableIdentifier, powerClass, mlxlinkMaps);

    if (!val.empty())
    {
        powerClassStr = std::to_string(powerClass) + " (" + val + ")";
    }

    return powerClassStr;
}

string getPowerClass(MlxlinkMaps* mlxlinkMaps, u_int32_t cableIdentifier, u_int32_t powerClass, u_int32_t maxPower)
{
    string powerClassStr = "N/A";
    float maxPowerValue = maxPower * 0.25;
    string val = getPowerClassStringValue(cableIdentifier, powerClass, mlxlinkMaps);
    float powerClassVal = getPowerClassValue(cableIdentifier, powerClass, mlxlinkMaps);

    if ((maxPowerValue > powerClassVal) || (powerClass == POWER_CLASS8))
    {
        powerClassStr = getMaxPowerStr(maxPower);
    }
    else if (!val.empty())
    {
        powerClassStr = val;
    }

    return powerClassStr;
}

int ptysSpeedToExtMaskETH(const string& speed)
{
    if (speed == "10M")
    {
        return (ETH_LINK_SPEED_EXT_SGMII_10M);
    }
    if (speed == "100M")
    {
        return (ETH_LINK_SPEED_EXT_SGMII_100M);
    }
    if (speed == "1G")
    {
        return (ETH_LINK_SPEED_EXT_1000BASE_X);
    }
    if (speed == "2.5G")
    {
        return (ETH_LINK_SPEED_EXT_2_5GBASE_X);
    }
    if (speed == "5G")
    {
        return (ETH_LINK_SPEED_EXT_5GBASE_R);
    }
    if (speed == "10G")
    {
        return (ETH_LINK_SPEED_EXT_XFI);
    }
    if (speed == "25G")
    {
        return (ETH_LINK_SPEED_EXT_25GAUI_1);
    }
    if (speed == "40G")
    {
        return (ETH_LINK_SPEED_EXT_XLAUI_4);
    }
    if (speed == "50G_2X")
    {
        return (ETH_LINK_SPEED_EXT_50GAUI_2);
    }
    if (speed == "50G_1X")
    {
        return (ETH_LINK_SPEED_EXT_50GAUI_1);
    }
    if (speed == "100G_4X")
    {
        return (ETH_LINK_SPEED_EXT_CAUI_4);
    }
    if (speed == "100G_1X")
    {
        return (ETH_LINK_SPEED_EXT_100GAUI_1);
    }
    if (speed == "100G_2X")
    {
        return (ETH_LINK_SPEED_EXT_100GAUI_2);
    }
    if (speed == "200G_2X")
    {
        return ETH_LINK_SPEED_EXT_200GAUI_2;
    }
    if (speed == "200G_4X")
    {
        return ETH_LINK_SPEED_EXT_200GAUI_4;
    }
    if (speed == "400G_4X")
    {
        return ETH_LINK_SPEED_EXT_400GAUI_4;
    }
    if (speed == "400G_8X")
    {
        return ETH_LINK_SPEED_EXT_400GAUI_8;
    }
    if (speed == "800G_8X")
    {
        return ETH_LINK_SPEED_EXT_800GAUI_8;
    }
    if (speed == "200G_1X")
    {
        return ETH_LINK_SPEED_EXT_200GAUI_1;
    }
    if (speed == "400G_2X")
    {
        return ETH_LINK_SPEED_EXT_400GAUI_2;
    }
    if (speed == "800G_4X")
    {
        return ETH_LINK_SPEED_EXT_800GAUI_4;
    }
    if (speed == "1600G_8X")
    {
        return ETH_LINK_SPEED_EXT_1_6TAUI_8;
    }
    return 0x0;
}

int ptysSpeedToMaskETH(const string& speed)
{
    if (speed == "1G")
    {
        return (ETH_LINK_SPEED_1000_SGMII | ETH_LINK_SPEED_1000_KX | ETH_LINK_SPEED_1000_BaseT);
    }
    if (speed == "10G")
    {
        return (ETH_LINK_SPEED_10G_CX4 | ETH_LINK_SPEED_10G_KX4 | ETH_LINK_SPEED_10G_CR | ETH_LINK_SPEED_10G_KR |
                ETH_LINK_SPEED_10G_LR | ETH_LINK_SPEED_10G_SR | ETH_LINK_SPEED_10G_BaseT);
    }
    if (speed == "20G")
    {
        return ETH_LINK_SPEED_20G_KR2;
    }
    if (speed == "40G")
    {
        return (ETH_LINK_SPEED_40G_CR4 | ETH_LINK_SPEED_40G_KR4 | ETH_LINK_SPEED_40G_LR4 | ETH_LINK_SPEED_40G_SR4);
    }
    if (speed == "56G")
    {
        return (ETH_LINK_SPEED_56G_CR4 | ETH_LINK_SPEED_56G_KR4 | ETH_LINK_SPEED_56G_R4);
    }
    if (speed == "50G")
    {
        return (ETH_LINK_SPEED_50G_CR2 | ETH_LINK_SPEED_50G_KR2 | ETH_LINK_SPEED_50G_SR2 | ETH_LINK_SPEED_50G_KR4);
    }
    if (speed == "100G")
    {
        return (ETH_LINK_SPEED_100G_CR4 | ETH_LINK_SPEED_100G_KR4 | ETH_LINK_SPEED_100G_LR4 | ETH_LINK_SPEED_100G_SR4);
    }
    if (speed == "100M")
    {
        return ETH_LINK_SPEED_100_BaseTx;
    }
    if (speed == "10M")
    {
        return ETH_LINK_SPEED_10M;
    }
    if (speed == "25G")
    {
        return (ETH_LINK_SPEED_25G_CR | ETH_LINK_SPEED_25G_KR | ETH_LINK_SPEED_25G_SR);
    }
    return 0x0;
}

int ptysSpeedToMaskIB(const string& speed)
{
    if (speed == "SDR")
    {
        return IB_LINK_SPEED_SDR;
    }
    if (speed == "DDR")
    {
        return IB_LINK_SPEED_DDR;
    }
    if (speed == "QDR")
    {
        return IB_LINK_SPEED_QDR;
    }
    if (speed == "FDR10")
    {
        return IB_LINK_SPEED_FDR10;
    }
    if (speed == "FDR")
    {
        return IB_LINK_SPEED_FDR;
    }
    if (speed == "EDR")
    {
        return IB_LINK_SPEED_EDR;
    }
    if (speed == "HDR")
    {
        return IB_LINK_SPEED_HDR;
    }
    if (speed == "NDR")
    {
        return IB_LINK_SPEED_NDR;
    }
    if (speed == "XDR")
    {
        return IB_LINK_SPEED_XDR;
    }
    return 0x0;
}

bool isPAM4Speed(u_int32_t activeSpeed, u_int32_t protoActive, bool extended)
{
    bool pam4Signal = false;
    if (protoActive == ETH && extended)
    {
        if (activeSpeed == ETH_LINK_SPEED_EXT_50GAUI_1 || activeSpeed == ETH_LINK_SPEED_EXT_100GAUI_2 ||
            activeSpeed == ETH_LINK_SPEED_EXT_200GAUI_4 || activeSpeed == ETH_LINK_SPEED_EXT_400GAUI_8)
        {
            pam4Signal = true;
        }
    }
    else if (protoActive == IB)
    {
        if (activeSpeed == IB_LINK_SPEED_HDR || activeSpeed == IB_LINK_SPEED_NDR || activeSpeed == IB_LINK_SPEED_XDR)
        {
            pam4Signal = true;
        }
    }
    return pam4Signal;
}

string getStrByValue(u_int32_t flags, std::map<u_int32_t, std::string> map)
{
    string flagsStr = map[flags];

    if (flagsStr.empty())
    {
        flagsStr = "N/A";
    }

    return flagsStr;
}

string getStrByMaskFromPair(u_int32_t bitmask,
                            map<u_int32_t, pair<string, string>> maskMap,
                            const string& fieldSeparator,
                            u_int32_t pairIndex)
{
    map<u_int32_t, string> strMap;
    for (auto it = maskMap.begin(); it != maskMap.end(); it++)
    {
        strMap.insert(pair<u_int32_t, string>(it->first, pairIndex == 0 ? it->second.first : it->second.second));
    }
    return getStrByMask(bitmask, strMap, fieldSeparator);
}

string getStrByMask(u_int32_t bitmask, std::map<u_int32_t, std::string> maskMap, const string& fieldSeparator)
{
    string bitMaskStr = "";
    string tmpMaskStr = "";
    u_int32_t i = 1;
    u_int32_t bitmask_tmp = bitmask;
    if (bitmask)
    {
        while (bitmask_tmp != 0)
        {
            if (getBitvalue(bitmask, i))
            {
                tmpMaskStr = maskMap[pow(2.0, i - 1)];
                if (!tmpMaskStr.empty())
                {
                    bitMaskStr += tmpMaskStr + fieldSeparator;
                }
            }
            i++;
            bitmask_tmp >>= 1;
        }
        bitMaskStr = deleteLastChar(bitMaskStr, fieldSeparator.size());
    }
    else
    {
        bitMaskStr = "N/A";
    }

    return bitMaskStr;
}

bool checkPaosCmd(const string& paosCmd)
{
    if (paosCmd != "UP" && paosCmd != "DN" && paosCmd != "TG")
    {
        return false;
    }
    return true;
}

bool checkPmaosCmd(const string& pmaosCmd)
{
    if (pmaosCmd != "UP" && pmaosCmd != "DN" && pmaosCmd != "TG")
    {
        return false;
    }
    return true;
}

bool checkPepcForceMode(const string& forceMode)
{
    if (forceMode != "MA" && forceMode != "SL")
    {
        return false;
    }
    return true;
}

bool checkPepcANMode(const string& anMode)
{
    if (anMode != "AU" && anMode != "MA" && anMode != "SL")
    {
        return false;
    }
    return true;
}

bool checkPplrCmd(const string& pplrCmd)
{
    if (pplrCmd != "NO" && pplrCmd != "PH" && pplrCmd != "EX")
    {
        return false;
    }
    return true;
}

u_int32_t prbsMaskToRateNum(u_int32_t mask)
{
    if (mask == PRBS_SDR)
    {
        return 1;
    }
    if (mask == PRBS_DDR)
    {
        return 5;
    }
    if (mask == PRBS_QDR)
    {
        return 10;
    }
    if (mask == PRBS_FDR10)
    {
        return 40;
    }
    if (mask == PRBS_FDR)
    {
        return 56;
    }
    if (mask == PRBS_EDR)
    {
        return 100;
    }
    if (mask == PRBS_HDR)
    {
        return 200;
    }
    if (mask == PRBS_NDR)
    {
        return 400;
    }
    if (mask == PRBS_XDR)
    {
        return 800;
    }
    if (mask == PRBS_1G)
    {
        return 1;
    }
    if (mask == PRBS_XAUI)
    {
        return 2;
    }
    if (mask == PRBS_50G)
    {
        return 12;
    }
    return 0;
}

string prbsMaskToLockStatus(u_int32_t mask, u_int32_t numOfLanesToUse)
{
    string res = "";
    for (u_int32_t i = 0; i < numOfLanesToUse; i++)
    {
        if (mask & 1 << i)
        {
            res += "Locked";
        }
        else
        {
            res += "Not Locked";
        }
        if (i < numOfLanesToUse - 1)
        {
            res += MlxlinkRecord::jsonFormat ? "," : ",    ";
        }
    }
    return res;
}

bool checkPrbsCmd(const string& prbsCmd)
{
    if (prbsCmd != "DS" && prbsCmd != "EN" && prbsCmd != "TU")
    {
        return false;
    }
    return true;
}

bool checkPhyRecoveryCmd(const string& phyRecoveryCmd)
{
    if (phyRecoveryCmd != "EN" && phyRecoveryCmd != "DS")
    {
        return false;
    }
    return true;
}

bool checkLinkTrainingCmd(const string& linkTrainingCmd)
{
    if (linkTrainingCmd != "EN" && linkTrainingCmd != "DS" && linkTrainingCmd != "EN_EXT")
    {
        return false;
    }
    return true;
}

bool checkTestMode(const string& testMode)
{
    if (testMode != "Nominal" && testMode != "NOMINAL" && testMode != "CORNER" && testMode != "DRIFT" && testMode != "")
    {
        return false;
    }
    return true;
}

PMAOS_CMD pmaos_to_int(const string& cmd)
{
    if (cmd == "UP")
    {
        return PMAOS_UP;
    }
    if (cmd == "DN")
    {
        return PMAOS_DN;
    }
    if (cmd == "TG")
    {
        return PMAOS_TG;
    }
    return PMAOS_NO;
}

PAOS_CMD paos_to_int(const string& cmd)
{
    if (cmd == "UP")
    {
        return UP;
    }
    if (cmd == "DN")
    {
        return DN;
    }
    if (cmd == "TG")
    {
        return TG;
    }
    return NO;
}

int pepc_force_mode_to_int(const string& forceMode)
{
    if (forceMode == "MA")
    {
        return 0;
    }
    if (forceMode == "SL")
    {
        return 1;
    }
    return 0;
}

int pepc_an_mode_to_int(const string& anMode)
{
    if (anMode == "AU")
    {
        return 0;
    }
    if (anMode == "MA")
    {
        return 1;
    }
    if (anMode == "SL")
    {
        return 2;
    }
    return 0;
}

bool endsWith(string const& value, string const& ending)
{
    if (ending.size() >= value.size())
    {
        return false;
    }
    return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void findAndReplace(string& source, string const& find, string const& replace)
{
    for (string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
    {
        source.replace(i, find.length(), replace);
        i += replace.length();
    }
}

string getCableIdentifier(u_int32_t identifier)
{
    string identifierStr;
    switch (identifier)
    {
        case IDENTIFIER_QSFP28:
            identifierStr = "QSFP28";
            break;

        case IDENTIFIER_QSFP_PLUS:
            identifierStr = "QSFP+";
            break;

        case IDENTIFIER_SFP:
            identifierStr = "SFP28/SFP+";
            break;

        case IDENTIFIER_QSA:
            identifierStr = "QSA (QSFP->SFP)";
            break;

        case IDENTIFIER_BACKPLANE:
            identifierStr = "Backplane";
            break;

        case IDENTIFIER_SFP_DD:
            identifierStr = "SFP-DD";
            break;

        case IDENTIFIER_QSFP_DD:
            identifierStr = "QSFP-DD";
            break;

        case IDENTIFIER_QSFP_CMIS:
            identifierStr = "QSFP_CMIS";
            break;
        case IDENTIFIER_OSFP:
            identifierStr = "OSFP";
            break;
        case IDENTIFIER_DSFP:
            identifierStr = "DSFP";
            break;
        default:
            identifierStr = "N/A";
    }
    return identifierStr;
}

bool isCMISCable(u_int32_t identifier)
{
    bool cmisCable = (identifier == IDENTIFIER_SFP_DD) || (identifier == IDENTIFIER_QSFP_DD) ||
                     (identifier == IDENTIFIER_QSFP_CMIS) || (identifier == IDENTIFIER_OSFP) ||
                     (identifier == IDENTIFIER_DSFP);
    return cmisCable;
}

bool isQsfpCable(u_int32_t identifier)
{
    bool qsfpCable = (identifier == IDENTIFIER_QSFP28) || (identifier == IDENTIFIER_QSFP_PLUS) ||
                     (identifier == IDENTIFIER_QSFP_DD) || (identifier == IDENTIFIER_DSFP);
    return qsfpCable;
}

string getCableType(u_int32_t cableType)
{
    string cableTypeStr;
    switch (cableType)
    {
        case UNIDENTIFIED:
            cableTypeStr = "Unidentified";
            break;

        case ACTIVE:
            cableTypeStr = "Active cable (active copper / optics)";
            break;

        case OPTICAL_MODULE:
            cableTypeStr = "Optical Module (separated)";
            break;

        case PASSIVE:
            cableTypeStr = "Passive copper cable";
            break;

        case UNPLUGGED:
            cableTypeStr = "Cable unplugged";
            break;

        case TWISTED_PAIR:
            cableTypeStr = "Twisted Pair";
            break;

        case CPO:
            cableTypeStr = "CPO";
            break;

        case OE:
            cableTypeStr = "OE";
            break;

        case ELS:
            cableTypeStr = "ELS";
            break;

        default:
            cableTypeStr = "Unidentified";
            break;
    }
    return cableTypeStr;
}

string getTemp(u_int32_t temp, int celsParam)
{
    if (temp & 0x8000)
    {
        return "-" + to_string(((~temp & 0xFFFF) + 1) / celsParam);
    }

    return to_string(temp / celsParam);
}

float getPower(u_int16_t power, bool isModuleExtSupported)
{
    // FW reports dbm values as integers, we read values in uw and convert manually to dbm to have more accuracy
    // this function is used to convert the power values from UW to dBm
    double result = -40;

    if (isModuleExtSupported)
    {
        if (power != 0)
        {
            result = 10 * log10(float(power) / 1000.0);
        }

        return result;
    }
    else
    {
        if (power & 0x8000)
        {
            return -((~power & 0xFFFF) + 1);
        }
        return power;
    }
}

int getHeight(u_int16_t height)
{
    if (height & 0x8000)
    {
        return -((~height & 0xFFFF) + 1);
    }
    return height;
}

int getPhase(u_int8_t phase)
{
    if (phase & 0x80)
    {
        return -((~phase & 0xFF) + 1);
    }
    return phase;
}

int getVersion(u_int8_t version)
{
    if (version & 0x8)
    {
        return -((~version & 0xF) + 1);
    }
    return version;
}

string getGroupStr(u_int32_t advancedOpcode)
{
    if (advancedOpcode == 0 || advancedOpcode == 1023)
    {
        return "N/A";
    }
    else if (advancedOpcode < 1023)
    {
        return "PHY FW";
    }
    else if (advancedOpcode < 2048)
    {
        return "MNG FW";
    }
    return "CORE/DRIVER";
}

string toUpperCase(string& str)
{
    for (u_int32_t i = 0; i < str.length(); i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}

string toLowerCase(string& str)
{
    for (u_int32_t i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

string getCableMedia(u_int32_t cableType)
{
    string cableTypeStr;
    switch (cableType)
    {
        case UNIDENTIFIED:
            cableTypeStr = "Unidentified";
            break;

        case ACTIVE:
            cableTypeStr = "Active";
            break;

        case OPTICAL_MODULE:
            cableTypeStr = "Optical Module";
            break;

        case PASSIVE:
            cableTypeStr = "Passive";
            break;

        case UNPLUGGED:
            cableTypeStr = "Unplugged";
            break;

        default:
            cableTypeStr = "Unidentified";
    }
    return cableTypeStr;
}

string pcieSpeedStr(u_int32_t linkSpeedActive)
{
    string linkSpeedActiveStr;
    if (linkSpeedActive & GEN6)
    {
        linkSpeedActiveStr = "32G PAM-4 Gen6";
    }
    else if (linkSpeedActive & GEN5)
    {
        linkSpeedActiveStr = "32G-Gen 5";
    }
    else if (linkSpeedActive & GEN4)
    {
        linkSpeedActiveStr = "16G-Gen 4";
    }
    else if (linkSpeedActive & GEN3)
    {
        linkSpeedActiveStr = "8G-Gen 3";
    }
    else if (linkSpeedActive & GEN2)
    {
        linkSpeedActiveStr = "5G-Gen 2";
    }
    else if (linkSpeedActive & GEN1)
    {
        linkSpeedActiveStr = "2.5G-Gen 1";
    }
    else
    {
        linkSpeedActiveStr = "N/A";
    }
    return linkSpeedActiveStr;
}

string getCompliance(u_int32_t compliance, std::map<u_int32_t, std::string> complianceMap, bool bitMasked)
{
    string compliance_str = "";
    static const string separator = ",";
    static const size_t separator_size = separator.size();
    std::map<u_int32_t, std::string>::iterator it;
    if (!compliance)
    {
        return complianceMap.begin()->second;
    }
    if (bitMasked)
    {
        for (it = complianceMap.begin(); it != complianceMap.end(); ++it)
        {
            u_int32_t comp_bit = it->first;
            string curr_compliance = it->second;
            if (compliance & comp_bit)
            {
                if (curr_compliance != "" && (comp_bit != QSFP_ETHERNET_COMPLIANCE_CODE_EXT))
                {
                    compliance_str += (curr_compliance + separator);
                }
            }
        }
        size_t str_size = compliance_str.size();
        if (!compliance_str.empty() && compliance_str.rfind(separator) == str_size - separator_size)
        {
            compliance_str.erase(str_size - separator_size, separator_size);
        }
    }
    else
    {
        it = complianceMap.find(compliance);
        if (it == complianceMap.end())
        {
            compliance_str = "Unknown compliance " + to_string(compliance);
        }
        else
        {
            compliance_str = it->second;
        }
    }
    return compliance_str;
}

string getModuleFwVersion(bool passive, u_int32_t moduleFWVer)
{
    string moduleFWVersion = "N/A";
    if (!passive)
    {
        u_int32_t moduleFWVerChip = (moduleFWVer & 0xFF000000) >> 24;
        u_int32_t moduleFWVerQtr = (moduleFWVer & 0x00FF0000) >> 16;
        u_int32_t moduleFWVerFree = (moduleFWVer & 0x0000FFFF);
        if (moduleFWVer)
        {
            moduleFWVersion =
              to_string(moduleFWVerChip) + "." + to_string(moduleFWVerQtr) + "." + to_string(moduleFWVerFree);
        }
    }

    return moduleFWVersion;
}

string getVendorRev(u_int32_t rev)
{
    string value = "";
    u_int32_t shift = 0xFF000000;
    for (u_int32_t i = 0; i < 4; i++)
    {
        char c = (char)((rev & shift) >> (3 - i) * 8);
        if (c != 0 && c != 32)
        {
            value.push_back(c);
        }
        shift = shift >> 8;
    }
    return (value != "") ? value : "N/A";
}

string getCableLengthStr(u_int32_t cableLength, bool cmisCable)
{
    char cableLengthStr[32];
    u_int32_t prec = 0;
    if (cmisCable)
    {
        u_int32_t lengthValue = (cableLength & 0x3f);
        float multiplier = 0;
        u_int32_t multiplierMask = (cableLength >> 6) & 0x7;
        switch (multiplierMask)
        {
            case CABLE_0_0_MUL:
                multiplier = 0.1;
                prec = 1;
                break;
            case CABLE_0_1_MUL:
                multiplier = 1;
                break;
            case CABLE_1_0_MUL:
                multiplier = 10;
                break;
            case CABLE_1_1_MUL:
                multiplier = 100;
                break;
        }
        snprintf(cableLengthStr, sizeof(cableLengthStr), "%.*f", prec, ((float)lengthValue * multiplier));
    }
    else
    {
        snprintf(cableLengthStr, sizeof(cableLengthStr), "%d", cableLength);
    }
    return string(cableLengthStr);
}

string getRxTxCDRState(u_int32_t state, u_int32_t numOfLanes)
{
    string stateMask = "";
    u_int32_t mask = 1;
    for (u_int32_t i = 0; i < numOfLanes; i++)
    {
        if (state & mask)
        {
            stateMask += "ON,";
        }
        else
        {
            stateMask += "OFF,";
        }
        mask = mask << 1;
    }
    return deleteLastChar(stateMask);
}

double mw_to_dbm(double x)
{
    return 10 * log10(x);
}

string floatToStr(float num, int resolution)
{
    char fmt[32];

    if (!(num - static_cast<int>(num)))
    {
        snprintf(fmt, sizeof(fmt), "%.0f", num);
    }
    else if (resolution < 0)
    {
        snprintf(fmt, sizeof(fmt), "%f", num);
    }
    else
    {
        snprintf(fmt, sizeof(fmt), "%.*f", resolution, num);
    }

    return string(fmt);
}

int readSigned(u_int32_t value, u_int32_t fieldSize)
{
    u_int32_t signMask = (u_int32_t)pow(2.0, (1.0 * fieldSize) - 1);
    u_int32_t valueMask = (u_int32_t)pow(2.0, 1.0 * fieldSize) - 1;
    if (value & signMask)
    {
        return -((~value & valueMask) + 1);
    }
    return value;
}

int readSignedByte(u_int32_t value)
{
    return readSigned(value, 8);
}

void setPrintVal(MlxlinkCmdPrint& mlxlinkCmdPrint,
                 string key,
                 string value,
                 string color,
                 bool print,
                 bool valid,
                 bool arrayValue,
                 bool colorKey)
{
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].key = key;
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].val = valid ? value : "N/A";
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].color = color;
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].visible = print;
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].arrayValue = arrayValue;
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].colorKey = colorKey;
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].lineLen = mlxlinkCmdPrint.lineLen;
    mlxlinkCmdPrint.lastInsertedRow++;
}

int getPrintRowIndex(MlxlinkCmdPrint& mlxlinkCmdPrint, const string& key)
{
    int recordIndex = 0;

    for (const auto& record : mlxlinkCmdPrint.mlxlinkRecords)
    {
        if (record.key == key)
        {
            break;
        }
        recordIndex++;
    }

    return recordIndex;
}

void setPrintTitle(MlxlinkCmdPrint& mlxlinkCmdPrint, string title, u_int32_t size, bool print)
{
    mlxlinkCmdPrint.title = title;
    mlxlinkCmdPrint.visible = print;
    mlxlinkCmdPrint.initRecords(size);
    mlxlinkCmdPrint.lastInsertedRow = 0;
}

bool isSpeed25GPerLane(u_int32_t speed, u_int32_t protocol)
{
    if (protocol == IB)
    {
        return speed & IB_LINK_SPEED_EDR;
    }
    return (speed & ETH_LINK_SPEED_25G_LANE);
}

bool isSpeed50GPerLane(u_int32_t speed, u_int32_t protocol)
{
    if (protocol == IB)
    {
        return speed & IB_LINK_SPEED_HDR;
    }
    return (speed & ETH_LINK_SPEED_50G_LANE);
}

bool isSpeed100GPerLane(u_int32_t speed, u_int32_t protocol)
{
    if (protocol == IB)
    {
        return speed & IB_LINK_SPEED_NDR;
    }
    return (speed & ETH_LINK_SPEED_100G_LANE);
}

bool isSpeed200GPerLane(u_int32_t speed, u_int32_t protocol)
{
    (void)protocol;
    return (speed & LINK_SPEED_200G_LANE);
}

bool isNRZSpeed(u_int32_t speed, u_int32_t protocol)
{
    // this twisted condition was made due to 100G per lane and 25G per lane share a mutual bit (19) and causes the 100G
    // per lane to be recognized as 25G per lane.
    return !isSpeed100GPerLane(speed, protocol) &&
           (isSpeed25GPerLane(speed, protocol) ||
            !(isSpeed50GPerLane(speed, protocol) || isSpeed100GPerLane(speed, protocol) ||
              isSpeed200GPerLane(speed, protocol) || isSpeed25GPerLane(speed, protocol)));
}

string linkWidthMaskToStr(u_int32_t width)
{
    string widthStr = "";
    if (width)
    {
        if (width & 1)
        {
            widthStr += "1x_";
        }
        if (width & 2)
        {
            widthStr += "2x_";
        }
        if (width & 4)
        {
            widthStr += "4x_";
        }
        if (width & 8)
        {
            widthStr += "8x_";
        }
        widthStr = deleteLastChar(widthStr);
    }
    else
    {
        widthStr = "N/A";
    }
    return widthStr;
}

string getBDFStr(u_int32_t bdf)
{
    char bdfBuff[128];

    snprintf(bdfBuff, sizeof(bdfBuff), "%02x:%02x.%x", (u_int8_t)(bdf >> 8), (u_int8_t)(bdf >> 3) & 0x1f,
             (u_int8_t)(bdf)&7);

    return string(bdfBuff);
}

int getBDFInt(const string& bdfStr)
{
    u_int32_t bdf = 0;
    try
    {
        auto pfStr = MlxlinkRecord::split(bdfStr, ":");
        size_t sz;

        // make sure that there is one ":" symbol
        if (pfStr.size() != 2)
        {
            return -1;
        }

        // parse the port function par xx:00.0, split the sec
        auto funcStr = MlxlinkRecord::split(pfStr[1], ".");

        // make sure that there it's matching this format xx:xx.x
        if (pfStr[0].size() > 2 || pfStr[1].size() > 4 || funcStr.size() != 2)
        {
            return -1;
        }

        // append 0x to work with hex format only
        pfStr[0] = "0x" + pfStr[0];
        pfStr[1] = "0x" + pfStr[1];

        // parse the main pcie function 00:xx.x
        bdf = stoi(pfStr[0], &sz, 16);
        bdf <<= 8;
        if (sz != pfStr[0].size())
        {
            return -1;
        }

        u_int32_t tmp = stoi(funcStr[0], &sz, 16);
        tmp <<= 3;
        bdf |= tmp;
        if (sz != funcStr[0].size())
        {
            return -1;
        }

        // get the function number
        bdf |= stoi(funcStr[1], &sz, 0);
        if (sz != funcStr[1].size())
        {
            return -1;
        }
    }
    catch (const exception& exp)
    {
        return -1;
    }

    return bdf;
}

size_t LevStrMatch(const string& source, const string& target)
{
    const size_t srcLen = source.size();
    const size_t trgLen = target.size();
    size_t idx = 0;

    if (srcLen == 0)
        return trgLen;
    if (trgLen == 0)
        return srcLen;

    vector<size_t> costs(trgLen + 1);

    for (idx = 0; idx < costs.size(); idx++)
    {
        costs[idx] = idx;
    }

    idx = 0;
    for (auto srcChar : source)
    {
        costs[0] = idx + 1;
        size_t corner = idx;
        size_t jdx = 0;
        for (auto trgChar : target)
        {
            size_t upper = costs[jdx + 1];
            costs[jdx + 1] = (srcChar == trgChar) ? corner : 1 + min(min(upper, corner), costs[jdx]);
            corner = upper;
            ++jdx;
        }
        ++idx;
    }
    return costs[trgLen];
}

bool askUser(const char* question, bool force)
{
    if (MlxlinkRecord::jsonFormat && force)
    {
        return true;
    }

    bool ret = true;
    void (*old)(int);
    old = signal(SIGINT, termHandler);

    printf("\n %s ? (y/n) [n] : ", question);
    if (force)
    {
        printf("y\n");
    }
    else
    {
        fflush(stdout);
        string answer;
        getline(cin, answer);
        if (strcasecmp(answer.c_str(), "y") && strcasecmp(answer.c_str(), "yes"))
        {
            return false;
        }
    }

    signal(SIGINT, old);

    return ret;
}

std::string centerString(const std::string& str, int width, char fillChar)
{
    int strLen = getStringLengthWOColorCodes(str);
    if (width <= strLen)
    {
        return str;
    }

    int padding = (width - strLen) / 2;
    int remainingPadding = width - strLen - padding;

    std::string leftPadding(padding, fillChar);
    std::string rightPadding(remainingPadding, fillChar);

    return leftPadding + str + rightPadding;
}

std::string generateTableRow(const std::vector<std::pair<std::string, u_int32_t>>& columns,
                             const std::string& delimiter)
{
    std::stringstream tableRow("");
    if (columns.empty())
    {
        return "";
    }
    for (const auto& column : columns)
    {
        tableRow << delimiter << centerString(column.first, column.second);
    }
    tableRow << delimiter;
    return tableRow.str();
}

int getStringLengthWOColorCodes(const std::string& s)
{
    int length = 0;
    size_t i = 0;
    while (i < s.size())
    {
        if (s[i] == '\033' && i + 1 < s.size() && s[i + 1] == '[')
        {
            // Skip the escape sequence until 'm' is found
            size_t j = i + 2;
            while (j < s.size() && s[j] != 'm')
            {
                j++;
            }
            if (j < s.size())
            {
                i = j + 1; // Skip the entire escape sequence including 'm'
            }
            else
            {
                // If 'm' is not found, length is the rest of the string.
                length += (s.size() - i);
                break;
            }
        }
        else
        {
            length++;
            i++;
        }
    }
    return length;
}

void printMlxlinkTable(const std::vector<std::string>& tableData,
                       const std::vector<std::pair<std::string, u_int32_t>>& tableHeader)
{
    u_int32_t numCols = tableHeader.size();
    std::string tableHeaderRow = generateTableRow(tableHeader, "|");
    std::string underscoreRow(tableHeaderRow.length() - 2, '-');
    std::cout << "|" << underscoreRow << "|" << std::endl;
    std::cout << tableHeaderRow << std::endl;
    std::cout << "|" << underscoreRow << "|" << std::endl;
    for (u_int32_t i = 0; i < tableData.size() / numCols; i++)
    {
        std::vector<std::pair<std::string, u_int32_t>> rowData = {};
        for (u_int32_t j = 0; j < numCols; j++)
        {
            rowData.push_back(std::make_pair(tableData[i * numCols + j], tableHeader[j].second));
        }
        std::cout << generateTableRow(rowData, "|") << std::endl;
    }
}

void updateColumnWidthPopulateTable(std::vector<std::pair<std::string, u_int32_t>>& vectorToAmend,
                                    const u_int32_t locationInVector,
                                    std::vector<std::string>& tableData,
                                    const std::string& valToAdd,
                                    u_int32_t unformattedStrLen,
                                    bool isActive)
{
    if (locationInVector < vectorToAmend.size())
    {
        if (unformattedStrLen > vectorToAmend[locationInVector].second)
        {
            vectorToAmend[locationInVector].second = unformattedStrLen;
        }
    }
    else
    {
        throw std::out_of_range(
          string("Showing Multi Port Info Table raised the following exception: Location in vector is out of bounds"));
    }
    if (isActive && valToAdd != "N/A")
    {
        tableData.push_back(valToAdd);
    }
    else
    {
        tableData.push_back("");
    }
}

void printProgressBar(int completion, const std::string& preStr, const std::string& endStr)
{
    if (completion < 100)
    {
        std::cout << "\r" << preStr << std::setw(3) << completion << "%" << std::flush;
    }
    else if (completion == 100)
    {
        std::cout << "\r" << preStr << " DONE\n" << std::flush;
    }
    else
    { // printing endStr
        if (!endStr.empty())
        {
            std::cout << "\r" << endStr << std::endl;
        }
    }
    std::cout << std::flush;
}

static void string_appendv(std::string& out, const char* format, va_list args)
{
    static const int FIT_MOST_OF_THE_CASES = 1024;
    char buffer[FIT_MOST_OF_THE_CASES];
    size_t length = sizeof(buffer);

    va_list tmp_args;
    va_copy(tmp_args, args);
    int bytes_written = ::std::vsnprintf(buffer, length, format, tmp_args);
    va_end(tmp_args);

    if (bytes_written >= 0 && static_cast<size_t>(bytes_written) < length)
    {
        out.append(buffer, bytes_written);
        return;
    }

    if (bytes_written < 0)
    {
        out.append("encoding error formatting string :");
        out.append(format);
        return;
    }

    // if we reached this point than "bytes_written" represents the number of characters
    // that would have been written if buffer had been sufficiently large, not counting
    // the terminating null character

    length = bytes_written + 1;

    char* rubber_buffer(new char[length]);
    va_copy(tmp_args, args);
    bytes_written = ::std::vsnprintf(rubber_buffer, length, format, tmp_args);
    va_end(tmp_args);

    if (bytes_written >= 0 && static_cast<size_t>(bytes_written) < length)
    {
        out.append(rubber_buffer, bytes_written);
        delete[] rubber_buffer;
        return;
    }

    if (bytes_written < 0)
    {
        out.append("encoding error formatting string");
        out.append(format);
        delete[] rubber_buffer;
        return;
    }

    delete[] rubber_buffer;
    return;
}

std::string string_format(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    std::string out;
    string_appendv(out, format, args);
    va_end(args);
    return out;
}
/* SW controlled module utilities */
bool readBoolFromSysFs(const string& sysfsPath)
{
    std::ifstream f(sysfsPath);
    char ch;
    if (f.is_open() && f.get(ch) && ch == '1')
    {
        return true;
    }
    return false;
}

bool isModulePresent(const string& modulePath)
{
    string sysfsHwPresent = modulePath + "/" + HW_PRESENT;
    return readBoolFromSysFs(sysfsHwPresent);
}

bool isModulePoweredOn(const string& modulePath)
{
    string sysfsPowerOn = modulePath + "/" + POWER_ON;
    return readBoolFromSysFs(sysfsPowerOn);
}

/*end*/