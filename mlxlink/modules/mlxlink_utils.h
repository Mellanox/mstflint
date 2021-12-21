/*
 * Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef MLXLINK_UTILS_H
#define MLXLINK_UTILS_H

#include "mlxlink_logger.h"
#include "mlxlink_maps.h"
#include <math.h>
#include <signal.h>

using namespace std;

enum CABLE_MULTIPLIER {
    CABLE_0_0_MUL,
    CABLE_0_1_MUL,
    CABLE_1_0_MUL,
    CABLE_1_1_MUL
};

#if __cplusplus <= 199711L
template<typename T>
std::string to_string(T toConvert)
{
    std::stringstream out;
    out << toConvert;
    return out.str();
}
#endif

template<typename T>
bool isIn(const T &val, std::vector<T> &vect)
{
    auto it = find(vect.begin(), vect.end(), val);
    return (it != vect.end());
}

u_int32_t findMaxKey(std::vector<std::string> keys);
string getCompliance(u_int32_t compliance, std::map<u_int32_t,
        std::string> complianceMap, bool bitMasked = false);
string getComplianceIb(u_int32_t compliance, std::map<u_int32_t,
        std::string> complianceMap, bool bitMasked = false);
void termHandler(int sig);
string deleteLastChar(const string &s, u_int32_t numOfCharsToRemove = 1);
string getStringFromVector(std::vector<std::string> values);
string getStringFromVector(std::vector<float> values);
u_int64_t add32BitTo64(u_int32_t value1, u_int32_t value2);
string getFullString(u_int64_t intVal);
string status2Color(u_int32_t status);
string getLoopbackColor(u_int32_t loopbackMode);
string getAnDisableColor(u_int32_t anDisable);
string IBSupportedSpeeds2Str(u_int32_t mask);
string EthSupportedSpeeds2Str(u_int32_t int_mask);
string EthExtSupportedSpeeds2Str(u_int32_t int_mask);
string SupportedSpeeds2Str(u_int32_t proto_active, u_int32_t mask,
        bool extended=false);
string getOui(u_int32_t oui);
int getBitvalue(u_int32_t mask, int idx);
string getPowerClass(MlxlinkMaps *mlxlinkMaps, u_int32_t cableIdentifier, u_int32_t powerClass, u_int32_t maxPower);
int ptysSpeedToExtMaskETH(const string & speed);
int ptysSpeedToMaskETH(const string &speed);
int ptysSpeedToMaskIB(const string &speed);
bool isPAM4Speed(u_int32_t speedMask, u_int32_t protoActive, bool extended=false);
bool checkPaosCmd(const string &paosCmd);
bool checkPepcForceMode(const string &forceMode);
bool checkPepcANMode(const string &anMode);
bool checkPplmCmd(const string &pplmCmd);
bool checkPplrCmd(const string &pplrCmd);
string prbsMaskToLaneRate(u_int32_t mask);
u_int32_t prbsMaskToRateNum(u_int32_t mask);
bool prbsLaneRateCheck(const string &rate);
string prbsMaskToTuningStatus(u_int32_t mask);
string prbsMaskToLockStatus(u_int32_t mask, u_int32_t numOfLanesToUse);
bool checkPrbsCmd(const string &prbsCmd);
bool checkTestMode(const string &testMode);
string FEC2Str(const string &fecShort, const string &speedStrG);
string speedToFecSpeedStr(const string &speed, u_int32_t numOfLanes);
PAOS_CMD paos_to_int(const string &cmd);
int pepc_force_mode_to_int(const string &forceMode);
int pepc_an_mode_to_int(const string &anMode);
bool endsWith(const std::string &value, const std::string &ending);
void findAndReplace(string& source, const string &find, const string &replace);
string getCableIdentifier(u_int32_t identifier);
bool isCMISCable(u_int32_t identifier);
bool isQsfpCable(u_int32_t identifier);
string getCmisCableType(u_int32_t cableType, u_int32_t cableLength);
string getCableType(u_int32_t cableType);
string getTemp(u_int32_t temp, int celsParam = 256);
float getPower(u_int16_t power);
int getHeight(u_int16_t height);
int getPhase(u_int8_t phase);
int getVersion(u_int8_t version);
string getGroupStr(u_int32_t advancedOpcode);
string toUpperCase(string &str);
string toLowerCase(string &str);
string getCableMedia(u_int32_t cableType);
string pcieSpeedStr(u_int32_t linkSpeedActive);
string pcieDeviceStatusStr(u_int32_t deviceStatus);
double mw_to_dbm(double x);
int readSigned(u_int32_t value, u_int32_t fieldSize);
int readSignedByte(u_int32_t value);
void setPrintTitle(MlxlinkCmdPrint &mlxlinkCmdPrint, string title,
        u_int32_t size, bool print = true);
void setPrintVal(MlxlinkCmdPrint &mlxlinkCmdPrint, string key,
        string value, string color = ANSI_COLOR_RESET, bool print = true,
        bool valid = true, bool arrayValue = false, bool colorKey = false);
bool isSpeed25GPerLane(u_int32_t speed, u_int32_t protocol);
string linkWidthMaskToStr(u_int32_t width);
bool isSpeed50GPerLane(u_int32_t speed, u_int32_t protocol);
bool isSpeed100GPerLane(u_int32_t speed, u_int32_t protocol);
bool askUser(const char *question, bool force = false);
string getCableLengthStr(u_int32_t cableLength, bool cmisCable);
string getRxTxCDRState(u_int32_t state, u_int32_t numOfLanes);
string getFwVersion(bool passive, u_int32_t moduleFWVer);
string getVendorRev(u_int32_t rev);
string getStrByValue(u_int32_t flags, map<u_int32_t, string> map);
string getStrByMask(u_int32_t bitmask, map<u_int32_t, string> maskMap, const string &fieldSeparator = ",");
string getStrByMaskFromPair(u_int32_t bitmask, map<u_int32_t, pair<string, string>> maskMap,
                            const string &fieldSeparator = ",", u_int32_t pairIndex = 0);
#endif
