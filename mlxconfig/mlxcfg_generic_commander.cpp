/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 * mlxcfg_generic_commander.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: ahmads
 */


#include <set>
#include <mtcr.h>
#include <mft_sig_handler.h>
#include <tools_dev_types.h>
#include <algorithm>
#include "mlxcfg_generic_commander.h"
#include "mlxcfg_utils.h"
#include "mlxcfg_tlv.h"
#include "mlxcfg_status.h"


#if ! defined(DISABLE_XML2)
    #include <libxml/parser.h>
    #include <libxml/tree.h>
#endif

using namespace std;

#define TLVCLASS_OFFSET 24
#define TLVCLASS_SIZE 8
#define BIN_FILE_FINGERPRINT "MLNX.CONFIG.BIN!"
#define BIN_FILE_FINGERPRINT_SIZE 16 //bytes
#define RAW_FILE_FINGERPRINT "MLNX_RAW_TLV_FILE"
#define XMLNS "http://www.mellanox.com/config"
#define XML_ROOT "config"

#define XML_DOCUMENT_START  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"\
        "<" XML_ROOT " xmlns=\"" XMLNS "\">"
#define XML_DOCUMENT_END "</" XML_ROOT ">"
#define XML_COMMENT_NODE "comment"

#define IGNORE_IF_EMPTY_NODE(n) \
    if (!n->name) {\
        continue;\
    }
#define IGNORE_IF_TEXT_NODE(n) \
    if(xmlNodeIsText(n)) {\
        n = n->next;\
        continue;\
    }
#define IGNORE_IF_COMMENT_NODE(n) \
    if (xmlStrcasecmp(n->name,\
            (const xmlChar*)XML_COMMENT_NODE) == 0) {\
        n = n->next;\
        continue;\
    }
#define IGNORE_UNUSEFUL_NODE(n) \
        IGNORE_IF_EMPTY_NODE(n)\
        IGNORE_IF_TEXT_NODE(n)\
        IGNORE_IF_COMMENT_NODE(n)
#define XMLFREE_AND_SET_NULL(p) \
        if (p) {\
            xmlFree(p);\
            p = NULL;\
        }
#define GET_AND_SET_ATTR(attrVal, currTlv, attr) \
        attrVal = xmlGetProp(currTlv, (const xmlChar*)attr);\
        if (attrVal) {\
            tlvConf->setAttr(attr, (const char*)attrVal);\
            XMLFREE_AND_SET_NULL(attrVal);\
        }

#define EQ_STR "=="
#define NOT_EQ_STR "!="

enum OP {EQUAL, NOT_EQUAL};

#define PCI_ACCESS_ONLY "Access to device should be through PCI interface only"

void GenericCommander::supportsNVData()
{
    struct tools_open_nvqc nvqcTlv;
    memset(&nvqcTlv, 0, sizeof(struct tools_open_nvqc));
    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    rc = reg_access_nvqc(_mf, REG_ACCESS_METHOD_GET, &nvqcTlv);
    dealWithSignal();
    if (rc == ME_REG_ACCESS_BAD_PARAM || rc == ME_REG_ACCESS_INTERNAL_ERROR) {
        throw MlxcfgException("FW does not support NV access registers");
    }
    if (rc) {
        throw MlxcfgException(
            "Error when trying to check if NV access registers are supported");
    }
    return;
}

GenericCommander::GenericCommander(mfile* mf, string dbName)
                                 : Commander(mf), _dbManager(NULL) {
    int rc;
    u_int32_t type = 0;

    if (_mf != NULL) {
        rc = mget_mdevs_type(mf, &type);
        if (rc) {
            throw MlxcfgException("Failed to get device type");
        }
    #ifndef MST_UL
        if (type != MST_PCICONF && type != MST_PCI) {
            throw MlxcfgException(PCI_ACCESS_ONLY);
        }
    #else
        if (type != MTCR_ACCESS_CONFIG && type != MTCR_ACCESS_MEMORY) {
            throw MlxcfgException(PCI_ACCESS_ONLY);
        }
    #endif

        supportsNVData();
    }

    if(dbName.empty()) {//take internal db file
#ifdef __WIN__
        char execFilePathCStr[1024] = {0x0};
        GetModuleFileName(GetModuleHandle("libmtcr-1.dll"), execFilePathCStr, 1024);
        dbName = execFilePathCStr;
        dbName = dbName.substr(0, dbName.rfind("\\") + 1);
        dbName += "mlxconfig_dbs\\mlxconfig.db";
#elif defined MST_UL
        dbName = DATA_PATH "/mlxconfig_dbs/mlxconfig.db";
#else
        char line[1024] = {0};
        string confFile = string(ROOT_PATH) + string("etc/mft/mft.conf");
        FILE* fd = fopen(confFile.c_str(), "r");
        if (!fd) {
            throw MlxcfgException("Failed to open conf file : %s\n", confFile.c_str());
        }
        string prefix = "", dataPath = "";
        while ((fgets(line, 1024, fd))) {
            string l = line;
            if (l.find("mlxconfig_dbs") != string::npos) {
               size_t eqPos = l.find("=");
               if (eqPos != string::npos) {
                   dataPath = l.substr(eqPos + 1);
                   dataPath = mlxcfg_trim(dataPath);
               }
            } else if(l.find("mft_prefix_location") != string::npos) {
                size_t eqPos = l.find("=");
                if (eqPos != string::npos) {
                    prefix = l.substr(eqPos + 1);
                    prefix = mlxcfg_trim(prefix);
                }
            }
         }
         if (!prefix.empty() && !dataPath.empty()) {
             dbName = prefix + dataPath + "/mlxconfig.db";
         }
         fclose(fd);
#endif
    }

    _dbManager = new MlxcfgDBManager(dbName);
}

GenericCommander::~GenericCommander()
{
    delete _dbManager;
}

bool sortParamView(ParamView a, ParamView b) {
    return a.mlxconfigName < b.mlxconfigName;
}

void GenericCommander::excludeDuplicatedTLVs(vector<TLVConfView>& s,
        vector<TLVConfView>& d) {
    VECTOR_ITERATOR(TLVConfView, s, it) {
        bool found = false;
        for(vector<TLVConfView>::reverse_iterator rIt = d.rbegin();
                rIt != d.rend();
                rIt++) {
            if((*it).name == (*rIt).name) {
                VECTOR_ITERATOR(ParamView, (*it).params, p) {
                    (*rIt).params.push_back(*p);
                }
                found = true;
                break;
            }
        }
        if(!found) {
            d.push_back(*it);
        }
    }
}

void GenericCommander::getAllConfigurations(vector<TLVConfView>& confs) {

    _dbManager->getAllTLVs();

    VECTOR_ITERATOR(TLVConf*, _dbManager->fetchedTLVs, it) {
        TLVConf* tlv = *it;
        TLVConfView tlvConfView;
        if(tlv->_cap == 0 &&
             tlv->isMlxconfigSupported() == true) {
            tlv->getView(tlvConfView);
            confs.push_back(tlvConfView);
        }
    }

    return;
}

void GenericCommander::printParamViews(FILE* f, vector<ParamView>& v) {
    VECTOR_ITERATOR(ParamView, v, pIt) {
        string s = (*pIt).mlxconfigName + "=<";
        switch((*pIt).type) {
            case BOOLEAN_TYPE:
                s += "False|True>";
                break;
            case UNSIGNED:
                s += "NUM>";
                break;
            case INTEGER:
                s += "NUM>";//todo talk with Dan regarding this???
                break;
            case ENUM:
                printEnums(*pIt, s);
                break;
            case STRING:
                s += "STRING>";
                break;
        }
        size_t len = (*pIt).mlxconfigName.length();
        if ((*pIt).mlxconfigName.rfind("_P2") == len - 3) {
            fprintf(f, "%20s%-40s\n\n", " ", s.c_str());
            continue;
        }
        size_t prevPos = 0;
        size_t pos = (*pIt).description.find("\\;", 0);
        fprintf(f, "%20s%-40s", " ", s.c_str());
        fprintf(f, "%s\n", (*pIt).description.substr(0, pos).c_str());
        while(pos != std::string::npos) {
            prevPos = pos + 2;
            pos = (*pIt).description.find("\\;", prevPos);
            fprintf(f, "%60s%s\n", " ",  (*pIt).description.substr(prevPos, pos - prevPos).c_str());
        }
    }
}

void GenericCommander::printTLVConfViews(FILE* f, vector<TLVConfView>& v) {
    VECTOR_ITERATOR(TLVConfView, v, it) {
        TLVConfView tv = (*it);
        fprintf(f, "\t\t%s:%s\n", tv.name.c_str(), tv.description.c_str());
        //sort the params
        std::sort(tv.params.begin(), tv.params.end(), sortParamView);
        printParamViews(f, tv.params);
    }
}
void GenericCommander::printLongDesc(FILE* f) {
    vector<TLVConfView> allConfs, confsForPrint;

    getAllConfigurations(allConfs);

    excludeDuplicatedTLVs(allConfs, confsForPrint);

    printTLVConfViews(f, confsForPrint);

}

void GenericCommander::printEnums(ParamView p, string& s) {
    std::map<string,u_int32_t>::iterator it;

    it = p.textualVals.begin();
    if(it == p.textualVals.end()) {
        throw MlxcfgException("The type of the parameter %s is ENUM, but enums were not found", p.mlxconfigName.c_str());
    }
    s += it->first;
    it++;
    for(; it != p.textualVals.end(); ++it) {
        s += "|" + it->first;
    }
    s += ">";
}

void parseDependency(string d, string& t, string& p,
        u_int32_t& v, OP& op) {
    //we assume there is only one tlv
    size_t opPos, dotPos, opStrLen;

    opPos = d.find(EQ_STR);
    opStrLen = strlen(EQ_STR);
    op = EQUAL;
    if (opPos == string::npos) {
        opPos = d.find(NOT_EQ_STR);
        opStrLen = strlen(NOT_EQ_STR);
        op = NOT_EQUAL;
        if (opPos == string::npos) {
            throw MlxcfgException(
                    "There is no '" EQ_STR "' nor '" NOT_EQ_STR
                    "' in the dependency %s", d.c_str());
        }
    }
    dotPos = d.find('.');
    if (dotPos == string::npos) {
        //dependency is in the same tlv
        t = "";
        p = d.substr(0, opPos);
    } else {
        t = d.substr(0, dotPos);
        p = d.substr(dotPos + 1, opPos - dotPos - 1);
    }
    v = atoi(d.substr(opPos + opStrLen, d.length() - opPos - opStrLen).c_str());
}

bool GenericCommander::checkDependency(TLVConf* cTLV, string dStr) {
    OP op;
    TLVConf* dTLV;
    u_int32_t l,r;
    string dTLVName, dParamName;

    if(dStr.empty()) {
        return true;
    }

    parseDependency(dStr, dTLVName, dParamName, r, op);

    if (dTLVName.empty()) {
        //the param belongs to current tlv
        l = cTLV->getParamValueByName(dParamName);
    } else {
        dTLV = _dbManager->getTLVByName(dTLVName, cTLV->_port);
        if (dTLV == NULL) {
            throw MlxcfgException("The TLV configuration %s was not found",
                    dTLVName.c_str());
        }
        if (!dTLV->isFWSupported(_mf, false)) {
            return false;
        }
        dTLV->query(_mf, QueryNext);
        l = dTLV->getParamValueByName(dParamName);
    }
    //printf("-D- l=%d r=%d op=%d\n", l, r, (u_int32_t)op);
    return (op == EQUAL) ? (l == r) : (l != r);
}

void GenericCommander::filterByDependency(TLVConf* cTLV,
        const vector<pair<ParamView, string> >& dependencyTable,
        vector<ParamView>& result) {
    for(size_t i = 0; i < dependencyTable.size(); i++) {
        if (checkDependency(cTLV, dependencyTable[i].second)) {
            //printf("-D- n= %s d=%s\n", dependencyTable[i].first.mlxconfigName.c_str(), dependencyTable[i].second.c_str());
            result.push_back(dependencyTable[i].first);
        }
    }
}

void GenericCommander::queryTLV(TLVConf* tlv,
        vector<ParamView>& paramsConf, QueryType qt) {
    if (!tlv->_cap &&
            tlv->isMlxconfigSupported() &&
            tlv->isFWSupported(_mf, true)) {
        vector<pair<ParamView, string> > dependencyTable =
                tlv->query(_mf, qt);
        filterByDependency(tlv, dependencyTable, paramsConf);
    }
    return;
}

void GenericCommander::queryParamViews(vector<ParamView>& params, QueryType qt) {
    vector<ParamView> pc;
    std::set<TLVConf*> uniqueTLVs;

    VECTOR_ITERATOR(ParamView, params, p){
        TLVConf* tlv = _dbManager->getTLVByParamMlxconfigName((*p).mlxconfigName);
        uniqueTLVs.insert(tlv);
    }

    SET_ITERATOR(TLVConf*, uniqueTLVs, it) {
        queryTLV(*it, pc, qt);
    }

    VECTOR_ITERATOR(ParamView, params, i){
        bool found = false;
        VECTOR_ITERATOR(ParamView, pc, j){
            //printf("-D- pc[j]=%s\n", j->mlxconfigName.c_str());
            if(i->mlxconfigName == j->mlxconfigName) {
                i->val = j->val;
                i->strVal = j->strVal;
                found = true;
                break;
            }
        }
        if (!found) {
            throw MlxcfgException("The Device doesn't support %s parameter",
                    i->mlxconfigName.c_str());
        }
    }
}

void GenericCommander::queryAll(vector<ParamView>& params, QueryType qt) {
    _dbManager->getAllTLVs();
    VECTOR_ITERATOR(TLVConf*, _dbManager->fetchedTLVs, it) {
        vector<ParamView> result;
        queryTLV((*it), result, qt);
        params.insert(params.end(), result.begin(), result.end());
    }
}

void GenericCommander::getCfg(ParamView& pv, QueryType qt)
{
    vector<ParamView> pc;

    TLVConf* tlv = _dbManager->getTLVByParamMlxconfigName(pv.mlxconfigName);
    queryTLV(tlv, pc, qt);

    VECTOR_ITERATOR(ParamView, pc, j){
        //printf("-D- pc[j]=%s\n", j->mlxconfigName.c_str());
        if(pv.mlxconfigName == j->mlxconfigName) {
            pv.val = j->val;
            pv.strVal = j->strVal;
            break;
        }
    }
}

void GenericCommander::setCfg(vector<ParamView>& params, bool force) {
    std::set<TLVConf*> uniqueTLVs;
    map<string, TLVConf*> tlvMap;

    VECTOR_ITERATOR(ParamView, params, p){
        TLVConf* tlv = _dbManager->getTLVByParamMlxconfigName((*p).mlxconfigName);
        tlvMap[(*p).mlxconfigName] = tlv;
        uniqueTLVs.insert(tlv);
    }

    //set user values
    VECTOR_ITERATOR(ParamView, params, p){
        //printf("-D- p=%s v=%s\n", (*p).mlxconfigName.c_str(), (*p).strVal.c_str());
        tlvMap[(*p).mlxconfigName]->updateParamByMlxconfigName((*p).mlxconfigName, (*p).strVal);
    }

    //prepare ruleTLVs,and check rules
    if(!force) {
        //printf("-D- do not force!\n");
        SET_ITERATOR(TLVConf*, uniqueTLVs, it) {
            TLVConf* tlv = *it;
            std::set<string> strRuleTLVs;
            tlv->getRuleTLVs(strRuleTLVs);
            vector<TLVConf*> ruleTLVs;
            SET_ITERATOR(string, strRuleTLVs, j){
                string strRuleTLV = *j;
                TLVConf* ruleTLV =
                        _dbManager->getTLVByName(strRuleTLV, tlv->_port);
                if (!ruleTLV->isFWSupported(_mf, false)) {
                    throw MlxcfgException("The Rule TLV configuration %s is not supported by FW",
                            strRuleTLV.c_str());
                    break;
                }
                ruleTLV->query(_mf, QueryNext);
                ruleTLVs.push_back(ruleTLV);
            }
            tlv->checkRules(ruleTLVs);
        }
    }

    //set the tlv on the device
    SET_ITERATOR(TLVConf*, uniqueTLVs, it) {
        //printf("-D- t=%s\n", (*it)->_name.c_str());
        (*it)->setOnDevice(_mf);
    }

    return;
}

bool GenericCommander::isDefaultSupported() {
    struct tools_open_nvqgc nvqgcTlv;

    memset(&nvqgcTlv, 0, sizeof(struct tools_open_nvqgc));
    MError rc;

    mft_signal_set_handling(1);
    rc = reg_access_nvqgc(_mf, REG_ACCESS_METHOD_GET, &nvqgcTlv);
    dealWithSignal();
    if (rc == ME_REG_ACCESS_BAD_PARAM || rc == ME_REG_ACCESS_INTERNAL_ERROR) {
        return false;
    } else if(rc == ME_OK){
        return nvqgcTlv.read_factory_settings_support;
    }
    throw MlxcfgException("Error when checked if Firmware supports querying default configurations or not: %s.", m_err2str((MError)rc));
}

bool GenericCommander::isCurrentSupported() {
    struct tools_open_nvqgc nvqgcTlv;

    memset(&nvqgcTlv, 0, sizeof(struct tools_open_nvqgc));
    MError rc;

    mft_signal_set_handling(1);
    rc = reg_access_nvqgc(_mf, REG_ACCESS_METHOD_GET, &nvqgcTlv);
    dealWithSignal();
    if (rc == ME_REG_ACCESS_BAD_PARAM || rc == ME_REG_ACCESS_INTERNAL_ERROR) {
        return false;
    } else if(rc == ME_OK){
        return nvqgcTlv.nvda_read_current_settings;
    }
    throw MlxcfgException(
            "Error when checked if Firmware supports "
            "querying current configurations or not: %s.",
            m_err2str((MError)rc));
}

void GenericCommander::clearSemaphore() {
    int rc = icmd_clear_semaphore(_mf);
    if(rc) {
        throw MlxcfgException("Failed to unlock semaphore: %s.", m_err2str((MError)rc));
    }
}

void GenericCommander::invalidateCfgs() {
    int rc;
    struct tools_open_nvia nviaTlv;
    u_int8_t buffer[TOOLS_OPEN_NVIA_SIZE] = {0};
    memset(&nviaTlv, 0, sizeof(struct tools_open_nvia));
    tools_open_nvia_pack(&nviaTlv, buffer);
    mft_signal_set_handling(1);
    rc = reg_access_nvia(_mf, REG_ACCESS_METHOD_SET, &nviaTlv);
    dealWithSignal();

    if(rc) {
        throw MlxcfgException("Failed to invalidate configurations: %s.", m_err2str((MError)rc));
    }
}

const char* GenericCommander::loadConfigurationGetStr() {
    int rc;
    dm_dev_id_t deviceId;
    u_int32_t hwDevId, hwRevId;
    struct cibfw_register_mfrl mfrl;

    if( dm_get_device_id(_mf, &deviceId, &hwDevId, &hwRevId) ) {
        throw MlxcfgException("Failed to identify the device");
    }

    memset(&mfrl, 0, sizeof(mfrl));

    if (deviceId == DeviceConnectX4 || deviceId == DeviceConnectX4LX || deviceId == DeviceConnectX5) {
        // send warm boot (bit 6)
        mfrl.reset_level = 1 << 6;
        mft_signal_set_handling(1);
        rc = reg_access_mfrl(_mf,REG_ACCESS_METHOD_SET, &mfrl);
        dealWithSignal();
        if (rc) {
            return "Please power cycle machine to load new configurations.";
        }
    }

    return "Please reboot machine to load new configurations.";
}

void GenericCommander::setRawCfg(std::vector<u_int32_t> rawTlvVec)
{
    RawCfgParams5thGen rawTlv;
    if (rawTlv.setRawData(rawTlvVec)) {
        throw MlxcfgException(rawTlv.err());
    }

    if (rawTlv.setOnDev(_mf)) {
        throw MlxcfgException(rawTlv.err());
    }
}

void GenericCommander::dumpRawCfg(std::vector<u_int32_t> rawTlvVec, std::string& tlvDump)
{
    RawCfgParams5thGen rawTlv;
    if (rawTlv.setRawData(rawTlvVec)) {
        throw MlxcfgException(rawTlv.err());
    }
    tlvDump = rawTlv.dumpTlv();
}

void GenericCommander::backupCfgs(vector<BackupView>& views)
{
    int rc;
    int status = 0;
    u_int32_t ptr = 0;
    struct tools_open_mnvgn mnvgnTlv;
    do {
        memset(&mnvgnTlv, 0, sizeof(struct tools_open_mnvgn));
        mnvgnTlv.nv_pointer = ptr;
        mft_signal_set_handling(1);
        rc = reg_access_mnvgn(_mf, REG_ACCESS_METHOD_GET, &mnvgnTlv, &status);
        dealWithSignal();
        if (rc) {
            if(status == ME_NOT_IMPLEMENTED) {
                throw MlxcfgException("Firmware does not support backup command");
            }
            throw MlxcfgException("Failed to backup configurations: %s.", m_err2str((MError)rc));
        }
        ptr = mnvgnTlv.nv_pointer;
        if (ptr != 0) {
            BackupView view;
            view.type = mnvgnTlv.nv_hdr.type.tlv_type_dw.tlv_type_dw;
            view.writerId = mnvgnTlv.nv_hdr.writer_id;
            view.writerHostId = mnvgnTlv.nv_hdr.writer_host_id;
            vector<u_int8_t> v;
            v.resize(TOOLS_OPEN_NV_HDR_FIFTH_GEN_SIZE + mnvgnTlv.nv_hdr.length);
            //Copy header:
            tools_open_nv_hdr_fifth_gen_pack(&mnvgnTlv.nv_hdr, v.data());
            //Copy data:
            memcpy(v.data() + TOOLS_OPEN_NV_HDR_FIFTH_GEN_SIZE,
                    &mnvgnTlv.nv_data,
                    mnvgnTlv.nv_hdr.length);
            view.tlvBin = v;
            views.push_back(view);
        }
    } while (ptr != 0);

}

void GenericCommander::updateParamViewValue(ParamView& p, string v)
{
    TLVConf* tlv = _dbManager->getTLVByParamMlxconfigName(p.mlxconfigName);
    tlv->parseParamValue(p.mlxconfigName, v, p.val, p.strVal);
    //printf("-D- %d %s", p.val, p.strVal.c_str());
}

void GenericCommander::genTLVsList(vector<string>& tlvs)
{
    _dbManager->getAllTLVs();
    VECTOR_ITERATOR(TLVConf*, _dbManager->fetchedTLVs, it) {
        if (find(tlvs.begin(), tlvs.end(), (*it)->_name) == tlvs.end()) {
            tlvs.push_back((*it)->_name);
        }
    }
}

void GenericCommander::genXMLTemplateAux(vector<string> tlvs,
        string& xmlTemplate, bool allAttrs, bool withVal, bool defaultAttrVal)
{
    xmlTemplate = XML_DOCUMENT_START;

    VECTOR_ITERATOR(string, tlvs, it) {
        string tlvTemplate;
        TLVConf* tlv = NULL;
        try {//user didn't tell us if it is a per port tlv
            //so try port==0
            tlv = _dbManager->getTLVByName(*it, 0);
        } catch (MlxcfgException&){
            //or port==1
            tlv = _dbManager->getTLVByName(*it, 1);
        }
        tlv->genXMLTemplate(tlvTemplate, allAttrs, withVal, defaultAttrVal);
        xmlTemplate += "\n" + tlvTemplate + "\n";
    }

    xmlTemplate += XML_DOCUMENT_END;
}

void GenericCommander::genXMLTemplate(vector<string> tlvs,
        string& xmlTemplate, bool allAttrs)
{
    genXMLTemplateAux(tlvs, xmlTemplate, allAttrs, false, true);
}

void GenericCommander::binTLV2XML(vector<u_int32_t> binTLV, string& xmlTemplate)
{
    u_int32_t id;
    tools_open_nv_hdr_fifth_gen hdr;
    tools_open_nv_hdr_fifth_gen_unpack(&hdr, (u_int8_t*)binTLV.data());

    //verify TLV length
    if (hdr.length != (binTLV.size() - 3) * 4) {
        throw MlxcfgException(
            "TLV size mismatch. reported length in TLV header: "
            "0x%x. actual length: 0x%x",
            hdr.length, (binTLV.size() - 3) * 4);
    }


    TLVClass tlvClass = (TLVClass)EXTRACT(hdr.type.tlv_type_dw.tlv_type_dw,
            TLVCLASS_OFFSET, TLVCLASS_SIZE);
    TLVClass tlvClassTemp;
    tools_open_tlv_type type;
    type.tlv_type_dw.tlv_type_dw = binTLV[1];

    //printf("-D- type dw=%d\n", type.tlv_type_dw.tlv_type_dw);
    TLVConf::unpackTLVType(tlvClass, type, id);
    if (tlvClass == Physical_Port_Common) {
        tlvClassTemp = Physical_Port;
    } else if (tlvClass == Per_Host_All_Functions ||
               tlvClass == All_Hosts_Per_Function ||
               tlvClass == All_Hosts_All_Functions) {
        tlvClassTemp = Per_Host_Per_Function;
    } else {
        tlvClassTemp = tlvClass;
    }
    TLVConf* tlv = _dbManager->getTLVByIndexAndClass(id, tlvClassTemp);
    //set attrs
    tlv->_attrs[RD_EN_ATTR] = numToStr(hdr.rd_en);
    tlv->_attrs[OVR_EN_ATTR] = numToStr(hdr.over_en);
    if (tlvClass == Physical_Port) {
        tlv->_attrs[PORT_ATTR] = numToStr(type.per_port.port);
    } else if (tlvClass == Physical_Port_Common) {
        tlv->_attrs[PORT_ATTR] = ALL_ATTR_VAL;
    } else if (tlvClass == Per_Host_All_Functions) {
        tlv->_attrs[HOST_ATTR] = numToStr(type.per_host.host);
        tlv->_attrs[FUNC_ATTR] = ALL_ATTR_VAL;
    } else if (tlvClass == Per_Host_Per_Function) {
        tlv->_attrs[HOST_ATTR] = numToStr(type.per_host.host);
        tlv->_attrs[FUNC_ATTR] = numToStr(type.per_host.function);
    } else if (tlvClass == All_Hosts_All_Functions) {
        tlv->_attrs[HOST_ATTR] = ALL_ATTR_VAL;
        tlv->_attrs[FUNC_ATTR] = ALL_ATTR_VAL;
    } else if (tlvClass == All_Hosts_Per_Function) {
        tlv->_attrs[HOST_ATTR] = ALL_ATTR_VAL;
        tlv->_attrs[FUNC_ATTR] = numToStr(type.per_host.function);
    }
    tlv->unpack((u_int8_t*)(binTLV.data() + 3));//the header size is 3dws
    tlv->genXMLTemplate(xmlTemplate, true, true, false);
}

void GenericCommander::XML2TLVConf(const string xmlContent, vector<TLVConf*>& tlvs)
{
#if ! defined(DISABLE_XML2)
    xmlDocPtr doc;
    xmlNodePtr root, currTlv, currParam;
    xmlChar* portAttr = NULL, *hostAttr = NULL,
            *funcAttr = NULL, *rdEnAttr = NULL,
            *ovrEnAttr = NULL, *xmlVal = NULL;

    doc = xmlReadMemory(xmlContent.c_str(),
            xmlContent.size(), "noname.xml", NULL, 0);
    if (!doc) {
        throw MlxcfgException("Failed to parse the XML document\n");
    }

    try {
        root = xmlDocGetRootElement(doc);
        if(!root || xmlStrcmp(root->name, (const xmlChar *)XML_ROOT)) {
            throw MlxcfgException("The XML root node must be "XML_ROOT);
        }

        //check fingerprint
        if(!root->ns || xmlStrcmp(root->ns->href, (const xmlChar*)XMLNS)) {
            throw MlxcfgException("The XML Fingerprint " XMLNS  " is missing or incorrect");
        }

        currTlv = root->xmlChildrenNode;
        while (currTlv) {
            IGNORE_UNUSEFUL_NODE(currTlv)
            u_int32_t port;
            TLVConf* tlvConf;
            bool isAllPorts = false;

            //printf("-D- tlv name=%s\n", (char*)currTlv->name);
            portAttr =  xmlGetProp(currTlv, (const xmlChar*)PORT_ATTR);

            if (!portAttr) {
                port = 0;
            } else if (!xmlStrcasecmp(portAttr, (const xmlChar*)ALL_ATTR_VAL)) {
                isAllPorts = true;
                port = 1;
            } else if (!strToNum((const char*) portAttr, port) ||
                    (port != 1 && port != 2)) {
                throw MlxcfgException("Illegal value of port attribute %s",
                        (const char*) portAttr);
            }

            tlvConf = _dbManager->getTLVByName((char*)currTlv->name, port);

            if (isAllPorts) {
                tlvConf->setAttr(PORT_ATTR, ALL_ATTR_VAL);
            }
            GET_AND_SET_ATTR(ovrEnAttr, currTlv, OVR_EN_ATTR)
            GET_AND_SET_ATTR(rdEnAttr, currTlv, RD_EN_ATTR)
            GET_AND_SET_ATTR(hostAttr, currTlv, HOST_ATTR)
            GET_AND_SET_ATTR(funcAttr, currTlv, FUNC_ATTR)

            //loop over the parameters list
            currParam = currTlv->xmlChildrenNode;
            while (currParam) {
                IGNORE_UNUSEFUL_NODE(currParam)
                xmlVal = xmlNodeListGetString(doc, currParam->xmlChildrenNode, 1);
                if (!xmlVal) {
                    throw MlxcfgException("The Parameter %s does not have value",
                            (char*)currParam->name);
                }
                tlvConf->updateParamByName((char*)currParam->name, (char*)xmlVal);
                XMLFREE_AND_SET_NULL(xmlVal);
                currParam = currParam->next;
            }
            tlvs.push_back(tlvConf);
            currTlv = currTlv->next;
        }
        if (tlvs.size() == 0) {
            throw MlxcfgException("No TLV configurations were found in the XML");
        }
    } catch (MlxcfgException& e) {
        XMLFREE_AND_SET_NULL(portAttr)
        XMLFREE_AND_SET_NULL(portAttr)
        XMLFREE_AND_SET_NULL(ovrEnAttr)
        XMLFREE_AND_SET_NULL(rdEnAttr)
        XMLFREE_AND_SET_NULL(hostAttr)
        XMLFREE_AND_SET_NULL(funcAttr)
        XMLFREE_AND_SET_NULL(xmlVal)
        XMLFREE_AND_SET_NULL(doc)
        throw e;
    }
    xmlFreeDoc(doc);
#else
    (void) xmlContent;
    (void) tlvs;
    throw MlxcfgException("Can not run the command, the tool was not compiled against libxml2");
#endif
}

void GenericCommander::XML2Raw(const string xmlContent, string& raw)
{
    vector<TLVConf*> tlvs;

    XML2TLVConf(xmlContent, tlvs);

    raw = RAW_FILE_FINGERPRINT;

    VECTOR_ITERATOR(TLVConf*, tlvs, tlvConf) {
        string rawTLV;
        (*tlvConf)->genRaw(rawTLV);
        raw += '\n' + rawTLV + '\n';
    }
}

void GenericCommander::raw2XML(vector<string> lines, string& xmlTemplate)
{
    bool foundTlv = false;
    xmlTemplate = XML_DOCUMENT_START;

    //check fingerprint in first line
    vector<string>::iterator it = lines.begin();
    if (it == lines.end() || *it != RAW_FILE_FINGERPRINT) {
        throw MlxcfgException("Raw Content Fingerprint " RAW_FILE_FINGERPRINT " is missing or incorrect");
    }

    it++;

    for(; it != lines.end(); it++) {
        string tlvXMLTemplate;
        if ((*it)[0] == '%') { //a FILE_COMMENT tlv
            //TODO
        } else {
            //printf("-D- line=%s\n", it->c_str());
            char* p = NULL;
            vector<u_int32_t> binTLV;
            vector<string> dws = splitStr(*it, ' ');
            VECTOR_ITERATOR(string, dws, s) {
                //printf("s=%s\n", s->c_str());
                u_int32_t dw = __cpu_to_be32(strtoul((*s).c_str(), &p, 0));
                //printf("-D- s=%s dw=0x%x\n", s->c_str(), dw);
                if (!p) {
                    throw MlxcfgException("Input is not an unsigned number: %s",
                            (*s).c_str());
                }
                binTLV.push_back(dw);
            }
            if (!binTLV.empty()) {
                binTLV2XML(binTLV, tlvXMLTemplate);
                xmlTemplate += '\n' + tlvXMLTemplate + '\n';
                foundTlv = true;
            }
        }
    }

    if (!foundTlv) {
        throw MlxcfgException("No TLV configurations were found in the raw file");
    }

    xmlTemplate += "</" XML_ROOT ">";
    //printf("xmlTemplate=\n%s", xmlTemplate.c_str());
}

/*
 * RawCfgParams5thGen Class implementation
 */
RawCfgParams5thGen::RawCfgParams5thGen() {
    memset(&_nvdaTlv, 0, sizeof(struct tools_open_nvda));
}

int RawCfgParams5thGen::setRawData(const std::vector<u_int32_t>& tlvBuff) {
    if(tlvBuff.size() * 4 > TOOLS_OPEN_NVDA_SIZE){
        return errmsg(MCE_BAD_PARAM_VAL, "TLV size exceeds maximal limit. Maximum size is 0x%x bytes, actual length is 0x%x bytes", TOOLS_OPEN_NVDA_SIZE, (u_int32_t)(tlvBuff.size() * 4));
    }
    _tlvBuff = tlvBuff;
    memset(&_nvdaTlv, 0, sizeof(struct tools_open_nvda));
    std::vector<u_int32_t> tlvBuffBe = _tlvBuff;
    tlvBuffBe.resize(TOOLS_OPEN_NVDA_SIZE >> 2);
    memset(&tlvBuffBe[0], 0, TOOLS_OPEN_NVDA_SIZE);
    tlvBuffBe.insert(tlvBuffBe.begin(), _tlvBuff.begin(), _tlvBuff.end());
    for (std::vector<u_int32_t>::iterator it = tlvBuffBe.begin(); it != tlvBuffBe.end(); it++ ) {
        *it = __cpu_to_be32(*it);
    }
    tools_open_nvda_unpack(&_nvdaTlv, ((u_int8_t*)(&tlvBuffBe[0])));
    _nvdaTlv.nv_hdr.writer_id = WRITER_ID_ICMD_MLXCONFIG_SET_RAW;
    return verifyTlv();
}

int RawCfgParams5thGen::setOnDev(mfile* mf) {
    int rc;
    mft_signal_set_handling(1);
    DEBUG_PRINT_SEND(&_nvdaTlv, nvda);
    rc = reg_access_nvda(mf, REG_ACCESS_METHOD_SET, &_nvdaTlv);
    DEBUG_PRINT_RECEIVE(&_nvdaTlv, nvda);
    dealWithSignal();
    if (rc) {
        return errmsg("Failed to set raw TLV: %s", m_err2str((MError)rc));
    }
    return MCE_SUCCESS;
}

std::string RawCfgParams5thGen::dumpTlv() {
    char str[1024] = {0};
    snprintf(str, 1024, "Length: 0x%x\nVersion: %d\nOverrideEn: %d\nType: 0x%08x\nData: ", _nvdaTlv.nv_hdr.length,\
            _nvdaTlv.nv_hdr.version, _nvdaTlv.nv_hdr.over_en, _nvdaTlv.nv_hdr.type.tlv_type_dw.tlv_type_dw);
    for (size_t i=3; i < _tlvBuff.size(); i++) {
        char numStr[64] = {0};
        snprintf(numStr, 64, "0x%08x ", _tlvBuff[i]);
        strcat(str, numStr);
    }
    strcat(str, "\n");
    return str;
}

int RawCfgParams5thGen::verifyTlv() {
    // check TLV length
    int tlvLength = (_tlvBuff.size() - 3) << 2;
    if (tlvLength != _nvdaTlv.nv_hdr.length) {
        return errmsg(MCE_BAD_PARAM_VAL, "TLV size mismatch. reported length in TLV header: 0x%x. actual length: 0x%x", _nvdaTlv.nv_hdr.length, tlvLength);
    }
    return MCE_SUCCESS;
}
