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

#if !defined(NO_OPEN_SSL)
#include <mlxsign_lib/mlxsign_lib.h>
#endif
#include "mlxcfg_generic_commander.h"
#include "mlxcfg_utils.h"
#include "mlxcfg_tlv.h"
#include "mlxcfg_status.h"
#include "mlxcfg_expression.h"

#if !defined(DISABLE_XML2)
    #include <libxml/parser.h>
    #include <libxml/tree.h>
#endif

using namespace std;
using namespace mlxcfg;

#define TLVCLASS_OFFSET 24
#define TLVCLASS_SIZE 8
#define BIN_FILE_FINGERPRINT "MLNX.CONFIG.BIN!"
#define BIN_FILE_FINGERPRINT_SIZE 16 //bytes
#define RAW_FILE_FINGERPRINT "MLNX_RAW_TLV_FILE"
#define XMLNS "http://www.mellanox.com/config"
#define XML_ROOT "config"

#define XML_DOCUMENT_START  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" \
    "<" XML_ROOT " xmlns=\"" XMLNS "\">"
#define XML_DOCUMENT_END "</" XML_ROOT ">"
#define XML_COMMENT_NODE "comment"

#define IGNORE_IF_EMPTY_NODE(n) \
    if (!n->name) { \
        continue; \
    }
#define IGNORE_IF_TEXT_NODE(n) \
    if (xmlNodeIsText(n)) { \
        n = n->next; \
        continue; \
    }
#define IGNORE_IF_COMMENT_NODE(n) \
    if (xmlStrcasecmp(n->name, \
                      (const xmlChar*)XML_COMMENT_NODE) == 0) { \
        n = n->next; \
        continue; \
    }
#define IGNORE_UNUSEFUL_NODE(n) \
    IGNORE_IF_EMPTY_NODE(n) \
    IGNORE_IF_TEXT_NODE(n) \
    IGNORE_IF_COMMENT_NODE(n)
#define XMLFREE_AND_SET_NULL(p) \
    if (p) { \
        xmlFree(p); \
        p = NULL; \
    }
#define GET_AND_SET_ATTR(attrVal, currTlv, attr) \
    attrVal = xmlGetProp(currTlv, (const xmlChar*)attr); \
    if (attrVal) { \
        tlvConf->setAttr(attr, (const char*)attrVal); \
        XMLFREE_AND_SET_NULL(attrVal); \
    }

#define EQ_STR "=="
#define NOT_EQ_STR "!="

enum OP {EQUAL, NOT_EQUAL};

#define PCI_ACCESS_ONLY "Access to device should be through PCI interface only"

const u_int8_t debugTokenId = 0x5;
const u_int8_t csTokenId = 0x7;
const u_int32_t idMlnxId = 0x10e;

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
    if (rc == ME_REG_ACCESS_REG_NOT_SUPP) {
        throw MlxcfgException("NVQC access register is not supported."
                " Try a different type of access to the device.");
    }
    if (rc) {
        throw MlxcfgException("Error when trying to check if NV access registers are supported");
    }
    return;
}

GenericCommander::GenericCommander(mfile *mf, string dbName)
    : Commander(mf), _dbManager(NULL)
{
    if (_mf != NULL) {
        supportsNVData();
    }

    if (dbName.empty()) {
        dbName = Commander::getDefaultDBName(false);
    }

    _dbManager = new MlxcfgDBManager(dbName);
}

GenericCommander::~GenericCommander()
{
    delete _dbManager;
}

bool sortParamView(const ParamView& a, const ParamView& b)
{
    return a.mlxconfigName < b.mlxconfigName;
}

void GenericCommander::excludeDuplicatedTLVs(vector<TLVConfView>& s,
                                             vector<TLVConfView>& d)
{
    VECTOR_ITERATOR(TLVConfView, s, it) {
        bool found = false;
        for (vector<TLVConfView>::reverse_iterator rIt = d.rbegin();
             rIt != d.rend();
             rIt++) {
            if ((*it).name == (*rIt).name) {
                VECTOR_ITERATOR(ParamView, (*it).params, p) {
                    (*rIt).params.push_back(*p);
                }
                found = true;
                break;
            }
        }
        if (!found) {
            d.push_back(*it);
        }
    }
}

void GenericCommander::getAllConfigurations(vector<TLVConfView>& confs)
{

    _dbManager->getAllTLVs();

    VECTOR_ITERATOR(TLVConf*, _dbManager->fetchedTLVs, it) {
        TLVConf *tlv = *it;
        TLVConfView tlvConfView;
        if (tlv->_cap == 0 &&
            tlv->isMlxconfigSupported() == true) {
            tlv->getView(tlvConfView);
            confs.push_back(tlvConfView);
        }
    }

    return;
}

void GenericCommander::queryConfigViews(std::vector<TLVConfView> & confs, const std::string & configName, QueryType qt)
{
    bool added = false;
    bool config_found = false;
    std::map<std::string, size_t> tlvViewMap;

    _dbManager->getAllTLVs();
    VECTOR_ITERATOR(TLVConf*, _dbManager->fetchedTLVs, it) {
        TLVConf *tlv = *it;
        if (tlv->_cap != 0 || tlv->isMlxconfigSupported() == false) {
            continue;
        }
        if (!configName.empty()) {
            if (configName != tlv->_mlxconfigName) {
                continue;
            }
        }
        vector<ParamView> result;
        queryTLV(tlv, result, qt);
        std::map<std::string, size_t>::iterator map_it = \
            tlvViewMap.find(tlv->_mlxconfigName);
        if (map_it != tlvViewMap.end()) {
            size_t index = (*map_it).second;
            VECTOR_ITERATOR(ParamView, result, p) {
                confs[index].params.push_back(*p);
            }
        } else {
            config_found = true;
            TLVConfView tlvConfView;
            tlv->getView(tlvConfView);
            tlvConfView.params.clear();
            VECTOR_ITERATOR(ParamView, result, p) {
                tlvConfView.params.push_back(*p);
            }
            if (tlvConfView.params.size() > 0) {
                confs.push_back(tlvConfView);
                tlvViewMap[tlv->_mlxconfigName] = confs.size() - 1;
                added = true;
            }
        }
    }
    if (!configName.empty()) {
        const char *msg = NULL;
        if (!config_found) {
            msg = "The configuration %s was not found";
        } else if (!added) {
            msg = "The configuration %s is empty";
        }
        if (msg != NULL) {
            throw MlxcfgException(msg, configName.c_str());
        }
    }

}

void GenericCommander::getConfigViews(std::vector<TLVConfView> & confs, const std::string & configName)
{
    std::map<std::string, size_t> tlvViewMap;

    _dbManager->getAllTLVs();
    VECTOR_ITERATOR(TLVConf*, _dbManager->fetchedTLVs, it) {
        TLVConf *tlv = *it;
        if (tlv->_cap != 0 || tlv->isMlxconfigSupported() == false) {
            continue;
        }
        if (!configName.empty()) {
            if (configName != tlv->_mlxconfigName) {
                continue;
            }
        }
        std::map<std::string, size_t>::iterator map_it = \
            tlvViewMap.find(tlv->_mlxconfigName);
        if (map_it != tlvViewMap.end()) {
            size_t index = (*map_it).second;
            TLVConfView tlvConfView;
            tlv->getView(tlvConfView);

            VECTOR_ITERATOR(ParamView, tlvConfView.params, p) {
                confs[index].params.push_back(*p);
            }
        } else {
            TLVConfView tlvConfView;
            tlv->getView(tlvConfView);
            confs.push_back(tlvConfView);
            tlvViewMap[tlv->_mlxconfigName] = confs.size() - 1;
        }
    }
    if (tlvViewMap.empty() && !configName.empty()) {
        throw MlxcfgException(
                  "The configuration %s was not found",
                  configName.c_str());
    }
}

void GenericCommander::printParamViews(FILE *f, vector<ParamView>& v)
{
    VECTOR_ITERATOR(ParamView, v, pIt) {
        string s = (*pIt).mlxconfigName + "=<";
        switch ((*pIt).type) {
        case BOOLEAN_TYPE:
            s += "False|True>";
            break;

        case UNSIGNED:
            s += "NUM>";
            break;

        case INTEGER:
            s += "NUM>";    //todo talk with Dan regarding this???
            break;

        case ENUM:
            printEnums(*pIt, s);
            break;

        case STRING:
            s += "STRING>";
            break;

        case BINARY:
            s += "BINARY>";
            break;

        case BYTES:
            s += "BYTES>";
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
        while (pos != std::string::npos) {
            prevPos = pos + 2;
            pos = (*pIt).description.find("\\;", prevPos);
            if (pos == std::string::npos) {
                fprintf(f, "%60s%s\n", " ",  (*pIt).description.substr(prevPos, ((*pIt).description.length() + 1) - prevPos).c_str());
            } else {
                fprintf(f, "%60s%s\n", " ",  (*pIt).description.substr(prevPos, pos - prevPos).c_str());
            }
        }
    }
}

void GenericCommander::printTLVConfViews(FILE *f, vector<TLVConfView>& v)
{
    VECTOR_ITERATOR(TLVConfView, v, it) {
        TLVConfView tv = (*it);
        fprintf(f, "\t\t%s:%s\n", tv.name.c_str(), tv.description.c_str());
        //sort the params
        std::sort(tv.params.begin(), tv.params.end(), sortParamView);
        printParamViews(f, tv.params);
    }
}
void GenericCommander::printLongDesc(FILE *f)
{
    vector<TLVConfView> allConfs, confsForPrint;

    getAllConfigurations(allConfs);

    excludeDuplicatedTLVs(allConfs, confsForPrint);

    printTLVConfViews(f, confsForPrint);

}

void GenericCommander::printEnums(const ParamView& p, string& s)
{
    std::map<string, u_int32_t>::const_iterator it;

    it = p.textualVals.begin();
    if (it == p.textualVals.end()) {
        throw MlxcfgException("The type of the parameter %s is ENUM, but enums were not found",
                              p.mlxconfigName.c_str());
    }
    s += it->first;
    it++;
    for (; it != p.textualVals.end(); ++it) {
        s += "|" + it->first;
    }
    s += ">";
}

void parseDependency(string d, string& t, string& p,
                     u_int32_t& v, OP& op)
{
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

bool GenericCommander::checkDependency(TLVConf *cTLV, string dStr)
{

    if (dStr.empty()) {
        return true;
    }

    Expression expression(dStr);
    vector<string> vars;
    expression.getVars(vars);
    VECTOR_ITERATOR(string, vars, it) {
        const size_t dotPos = (*it).find('.');
        if (dotPos == string::npos) { //parameter of current tlv
            expression.setVarVal((*it), cTLV->getParamValueByName((*it).replace(0, 1, "")));
        } else {
            string dTLVName = (*it).substr(0, dotPos).replace(0, 1, "");
            string dParamName = (*it).substr(dotPos + 1);
            TLVConf *dTLV = _dbManager->getTLVByName(dTLVName, cTLV->_port);
            if (dTLV == NULL) {
                throw MlxcfgException("The TLV configuration %s was not found",
                                      dTLVName.c_str());
            }
            if (!dTLV->isFWSupported(_mf, false)) {
                return false;
            }
            dTLV->query(_mf, QueryNext);
            expression.setVarVal((*it), dTLV->getParamValueByName(dParamName));
        }
    }

    return (expression.evaluate() != 0);
}

void GenericCommander::filterByDependency(TLVConf *cTLV,
                                          const vector<pair<ParamView, string> >& dependencyTable,
                                          vector<ParamView>& result)
{
    for (size_t i = 0; i < dependencyTable.size(); i++) {
        if (checkDependency(cTLV, dependencyTable[i].second)) {
            result.push_back(dependencyTable[i].first);
        }
    }
}

void GenericCommander::queryTLV(TLVConf *tlv,
                                vector<ParamView>& paramsConf, QueryType qt)
{
    if (!tlv->_cap &&
        tlv->isMlxconfigSupported() &&
        tlv->isFWSupported(_mf, true)) {
        vector<pair<ParamView, string> > dependencyTable =
            tlv->query(_mf, qt);
        filterByDependency(tlv, dependencyTable, paramsConf);
    }
    return;
}

void GenericCommander::queryParamViews(vector<ParamView>& params, QueryType qt)
{
    vector<ParamView> pc;
    std::set<TLVConf*> uniqueTLVs;
    map<string, string>  arrayStrs;

    VECTOR_ITERATOR(ParamView, params, p){
        unsigned int index = 0;
        bool isIndexed = false;
        bool isStartFromOneSupported = false;
        string mlxconfigName = (*p).mlxconfigName;
        if (isIndexedMlxconfigName(mlxconfigName)) {
            parseIndexedMlxconfigName(mlxconfigName, mlxconfigName, index);
            isIndexed = true;
        }
        isStartFromOneSupported = isIndexedStartFromOneSupported(mlxconfigName);
        TLVConf *tlv = _dbManager->getTLVByParamMlxconfigName(mlxconfigName, index);    
        uniqueTLVs.insert(tlv);
        // if not indexed and has suffix (its continuance array) need to get next tlv and change the array length (for query)
        if (!isIndexed && getArraySuffix(tlv->_name).size() > 0 && getArraySuffix(mlxconfigName).size() == 0 ) {
            while ( _dbManager->isParamMlxconfigNameExist( mlxconfigName + getArraySuffixByInterval( ((++index) * MAX_ARRAY_SIZE)) ) ) {
            } 
            if (isStartFromOneSupported) {
                arrayStrs[mlxconfigName] = "Array[1.." + numToStr((index * MAX_ARRAY_SIZE)) + "]";
            }
            else {
                arrayStrs[mlxconfigName] = "Array[0.." + numToStr((index * MAX_ARRAY_SIZE) - 1) + "]";
            }
            index = 0;
        }
    }

    SET_ITERATOR(TLVConf*, uniqueTLVs, it) {
        queryTLV(*it, pc, qt);
    }

    VECTOR_ITERATOR(ParamView, params, i){
        bool found = false;
        VECTOR_ITERATOR(ParamView, pc, j){
            bool isIIndexed = false;
            unsigned int iIndex = 0;
            string mlxconfigNameI = (*i).mlxconfigName;
            if (isIndexedMlxconfigName(mlxconfigNameI)) {
                parseIndexedMlxconfigName(mlxconfigNameI, mlxconfigNameI, iIndex);
                isIIndexed = true;
            }

            string mlxconfigNameJ = (*j).mlxconfigName;
            if (mlxconfigNameI == mlxconfigNameJ || (mlxconfigNameI + getArraySuffixByInterval(iIndex)) == mlxconfigNameJ) {
                if (isIIndexed) {
                    if (iIndex >= j->arrayVal.size() && (mlxconfigNameI + getArraySuffixByInterval(iIndex)) != mlxconfigNameJ) {
                        throw MlxcfgException("Index %d of the parameter %s is out of range. Maximal index is %zu",
                                              iIndex, mlxconfigNameI.c_str(), j->arrayVal.size() - 1);
                    }
                    i->val = j->arrayVal[iIndex % MAX_ARRAY_SIZE];
                    i->strVal = j->strArrayVal[iIndex % MAX_ARRAY_SIZE];
                } else {
                    i->val = j->val;
                    i->strVal = j->strVal;
                    if (!arrayStrs[mlxconfigNameI].empty()) {
                        i->strVal = arrayStrs[mlxconfigNameI];
                    }
                }
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

void GenericCommander::queryAll(vector<ParamView>& params, vector<string>& failedTLVs, QueryType qt)
{
    _dbManager->getAllTLVs();
    VECTOR_ITERATOR(TLVConf*, _dbManager->fetchedTLVs, it) {
        try {
            vector<ParamView> result;
            queryTLV((*it), result, qt);
            params.insert(params.end(), result.begin(), result.end());
        } catch (MlxcfgException& e) {
            failedTLVs.push_back((*it)->_name);
        }
    }
}

void GenericCommander::getCfg(ParamView& pv, QueryType qt)
{
    vector<ParamView> pc;

    TLVConf *tlv = _dbManager->getTLVByParamMlxconfigName(pv.mlxconfigName, 0);
    queryTLV(tlv, pc, qt);

    VECTOR_ITERATOR(ParamView, pc, j){
        //printf("-D- pc[j]=%s\n", j->mlxconfigName.c_str());
        if (pv.mlxconfigName == j->mlxconfigName) {
            pv.val = j->val;
            pv.strVal = j->strVal;
            break;
        }
    }
}

void GenericCommander::setCfg(vector<ParamView>& params, bool force)
{
    std::set<TLVConf*> uniqueTLVs;
    map<string, TLVConf*> tlvMap;

    VECTOR_ITERATOR(ParamView, params, p) {
        unsigned int index = 0;
        string mlxconfigName = (*p).mlxconfigName;
        bool isIndexed = false;
        if (isIndexedMlxconfigName(mlxconfigName)) {
            parseIndexedMlxconfigName(mlxconfigName, mlxconfigName, index);
            isIndexed = true;
        }
        TLVConf *tlv = _dbManager->getTLVByParamMlxconfigName(mlxconfigName, index);
        tlvMap[mlxconfigName] = tlv;
        uniqueTLVs.insert(tlv);

        if (isIndexed) {
            tlvMap[mlxconfigName]->updateParamByMlxconfigName(mlxconfigName, (*p).strVal, index);
        }
        else {
            tlvMap[(*p).mlxconfigName]->updateParamByMlxconfigName(mlxconfigName, (*p).strVal);
        }

    }

    //prepare ruleTLVs,and check rules
    if (!force) {
        //printf("-D- do not force!\n");
        SET_ITERATOR(TLVConf*, uniqueTLVs, it) {
            TLVConf *tlv = *it;
            std::set<string> strRuleTLVs;
            tlv->getRuleTLVs(strRuleTLVs);
            vector<TLVConf*> ruleTLVs;
            SET_ITERATOR(string, strRuleTLVs, j){
                string strRuleTLV = *j;
                TLVConf *ruleTLV =
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

bool GenericCommander::isDefaultSupported()
{
    struct tools_open_nvqgc nvqgcTlv;

    memset(&nvqgcTlv, 0, sizeof(struct tools_open_nvqgc));
    MError rc;

    mft_signal_set_handling(1);
    rc = reg_access_nvqgc(_mf, REG_ACCESS_METHOD_GET, &nvqgcTlv);
    dealWithSignal();
    if (rc == ME_REG_ACCESS_BAD_PARAM || rc == ME_REG_ACCESS_INTERNAL_ERROR) {
        return false;
    } else if (rc == ME_OK) {
        return nvqgcTlv.read_factory_settings_support;
    }
    throw MlxcfgException("Error when checked if Firmware supports querying default configurations or not: %s.", m_err2str((MError)rc));
}

bool GenericCommander::isCurrentSupported()
{
    struct tools_open_nvqgc nvqgcTlv;

    memset(&nvqgcTlv, 0, sizeof(struct tools_open_nvqgc));
    MError rc;

    mft_signal_set_handling(1);
    rc = reg_access_nvqgc(_mf, REG_ACCESS_METHOD_GET, &nvqgcTlv);
    dealWithSignal();
    if (rc == ME_REG_ACCESS_BAD_PARAM || rc == ME_REG_ACCESS_INTERNAL_ERROR) {
        return false;
    } else if (rc == ME_OK) {
        return nvqgcTlv.nvda_read_current_settings;
    }
    throw MlxcfgException(
              "Error when checked if Firmware supports "
              "querying current configurations or not: %s.",
              m_err2str((MError)rc));
}

void GenericCommander::clearSemaphore()
{
    int rc = icmd_clear_semaphore(_mf);
    if (rc) {
        throw MlxcfgException("Failed to unlock semaphore: %s.", m_err2str((MError)rc));
    }
}

void GenericCommander::invalidateCfgs()
{
    int rc;
    struct tools_open_nvia nviaTlv;
    u_int8_t buffer[TOOLS_OPEN_NVIA_SIZE] = {0};
    memset(&nviaTlv, 0, sizeof(struct tools_open_nvia));
    tools_open_nvia_pack(&nviaTlv, buffer);
    mft_signal_set_handling(1);
    rc = reg_access_nvia(_mf, REG_ACCESS_METHOD_SET, &nviaTlv);
    dealWithSignal();

    if (rc) {
        throw MlxcfgException("Failed to invalidate configurations: %s.", m_err2str((MError)rc));
    }
}


void GenericCommander::invalidateCfg(const std::string & configName)
{

    std::vector<TLVConf*> tlvArr;
    _dbManager->getAllTLVs();
    VECTOR_ITERATOR(TLVConf*, _dbManager->fetchedTLVs, it) {
        if ((*it)->_mlxconfigName == configName) {
            tlvArr.push_back(*it);
        }
    }
    if (tlvArr.empty()) {
        throw MlxcfgException("The configuration %s was not found",
                              configName.c_str());
    }

    VECTOR_ITERATOR(TLVConf*, tlvArr, it) {
        (*it)->invalidate(_mf);
    }
}

const char* GenericCommander::loadConfigurationGetStr()
{
    int rc;
    dm_dev_id_t deviceId = DeviceUnknown;
    u_int32_t hwDevId, hwRevId;
    struct reg_access_hca_mfrl_reg_ext mfrl;

    if (dm_get_device_id(_mf, &deviceId, &hwDevId, &hwRevId) ) {
        throw MlxcfgException("Failed to identify the device");
    }

    memset(&mfrl, 0, sizeof(mfrl));

    if (deviceId == DeviceConnectX4   ||
        deviceId == DeviceConnectX4LX ||
        deviceId == DeviceConnectX5   ||
        deviceId == DeviceBlueField ||
        deviceId == DeviceBlueField2 ||
        deviceId == DeviceConnectX6 ||
        deviceId == DeviceConnectX6DX ||
        deviceId == DeviceConnectX6LX) {
        // send warm boot (bit 6)
        mfrl.reset_level = 1 << 6;
        mft_signal_set_handling(1);
        rc = reg_access_mfrl(_mf, REG_ACCESS_METHOD_SET, &mfrl);
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
            if (status == ME_NOT_IMPLEMENTED) {
                throw MlxcfgException("Firmware does not support backup command");
            } else if (rc == ME_REG_ACCESS_RES_NOT_AVLBL) {
                throw MlxcfgException("NV data area may be empty, nothing to backup.");
            } else {
                throw MlxcfgException("Failed to backup configurations: %s.", m_err2str((MError)rc));
            }
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
    string mlxconfigName = p.mlxconfigName;
    unsigned int index = 0;
    if (isIndexedMlxconfigName(mlxconfigName)) {
        
        parseIndexedMlxconfigName(mlxconfigName, mlxconfigName, index);
    }
    TLVConf *tlv = _dbManager->getTLVByParamMlxconfigName(mlxconfigName, index);
    tlv->parseParamValue(mlxconfigName, v, p.val, p.strVal, index);
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
        TLVConf *tlv = NULL;
        try {//user didn't tell us if it is a per port tlv
            //so try port==0
            tlv = _dbManager->getTLVByName(*it, 0);
        } catch (MlxcfgException&) {
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

void GenericCommander::binTLV2TLVConf(const vector<u_int32_t>& binTLV, TLVConf*& tlv)
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
    tlv = _dbManager->getTLVByIndexAndClass(id, tlvClassTemp);
    //set attrs
    tlv->_attrs[WRITER_ID_ATTR] = numToStr(hdr.writer_id);
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
}

void GenericCommander::binTLV2XML(const vector<u_int32_t>& binTLV, string& xmlTemplate)
{
    TLVConf *tlv = NULL;
    binTLV2TLVConf(binTLV, tlv);
    tlv->genXMLTemplate(xmlTemplate, true, true, false);
}

void GenericCommander::bin2TLVConfs(const vector<u_int32_t>& tlvsBin, vector<TLVConf*>& tlvs)
{
    size_t size = 0;
    size_t hdrSize = (tools_open_nv_hdr_fifth_gen_size() >> 2);

    while (hdrSize + size < tlvsBin.size()) {
        TLVConf *tlv = NULL;
        vector<u_int32_t> tmpBuff;
        tools_open_nv_hdr_fifth_gen hdr;
        tools_open_nv_hdr_fifth_gen_unpack(&hdr, (u_int8_t*)(tlvsBin.data() + size));

        size_t tlvSize = hdrSize + (hdr.length >> 2);
        if (tlvSize > (tlvsBin.size() - size)) {
            throw MlxcfgException("Invalid Configuration buffer");
        }
        tmpBuff.insert(tmpBuff.begin(),
                       tlvsBin.begin() + size,
                       tlvsBin.begin() +  +size + tlvSize);
        binTLV2TLVConf(tmpBuff, tlv);
        tlvs.push_back(tlv);
        size += tlvSize;
    }

    if (size != tlvsBin.size()) {
        throw MlxcfgException("Invalid Configuration buffer");
    }
}

void GenericCommander::XML2TLVConf(const string& xmlContent, vector<TLVConf*>& tlvs)
{
#if !defined(DISABLE_XML2)
    xmlDocPtr doc;
    xmlNodePtr root, currTlv, currParam;
    xmlChar *portAttr = NULL, *hostAttr = NULL,
            *funcAttr = NULL, *rdEnAttr = NULL,
            *ovrEnAttr = NULL, *xmlVal = NULL,
            *indexAttr = NULL, *writerIdAttr = NULL;

    doc = xmlReadMemory(xmlContent.c_str(),
                        xmlContent.size(), "noname.xml", NULL, 0);
    if (!doc) {
        throw MlxcfgException("Failed to parse the XML document\n");
    }

    try {
        root = xmlDocGetRootElement(doc);
        if (!root || xmlStrcmp(root->name, (const xmlChar*)XML_ROOT)) {
            throw MlxcfgException("The XML root node must be " XML_ROOT);
        }

        //check fingerprint
        if (!root->ns || xmlStrcmp(root->ns->href, (const xmlChar*)XMLNS)) {
            throw MlxcfgException("The XML Fingerprint " XMLNS  " is missing or incorrect");
        }

        currTlv = root->xmlChildrenNode;
        while (currTlv) {
            IGNORE_UNUSEFUL_NODE(currTlv)
            u_int32_t port;
            TLVConf *tlvConf;
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

            tlvConf = _dbManager->getAndCreateTLVByName((char*)currTlv->name, port);

            if (isAllPorts) {
                tlvConf->setAttr(PORT_ATTR, ALL_ATTR_VAL);
            }
            GET_AND_SET_ATTR(writerIdAttr, currTlv, WRITER_ID_ATTR)
            GET_AND_SET_ATTR(ovrEnAttr, currTlv, OVR_EN_ATTR)
            GET_AND_SET_ATTR(rdEnAttr, currTlv, RD_EN_ATTR)
            GET_AND_SET_ATTR(hostAttr, currTlv, HOST_ATTR)
            GET_AND_SET_ATTR(funcAttr, currTlv, FUNC_ATTR)

            //loop over the parameters list
            vector<string> collectedParams;
            currParam = currTlv->xmlChildrenNode;
            map<string, map<u_int32_t, string> > arrayValues;
            while (currParam) {
                IGNORE_UNUSEFUL_NODE(currParam)
                xmlVal = xmlNodeListGetString(doc, currParam->xmlChildrenNode, 1);
                indexAttr = xmlGetProp(currParam, (const xmlChar*)INDEX_ATTR);
                if (xmlVal) {
                    if (indexAttr) {
                        string indexAttrStr = (const char*)indexAttr;
                        vector<u_int32_t> indexes;
                        extractIndexes(indexAttrStr, indexes);
                        VECTOR_ITERATOR(u_int32_t, indexes, it) {
                            arrayValues[(char*)currParam->name][*it] = (char*)xmlVal;
                        }
                    } else {
                        if (find(collectedParams.begin(), collectedParams.end(), (char*)currParam->name)
                            != collectedParams.end()) {
                            throw MlxcfgException("Duplicate use of same parameter: %s\n",
                                                  (char*)currParam->name);
                        }
                        collectedParams.push_back((char*)currParam->name);
                        tlvConf->updateParamByName((char*)currParam->name, (char*)xmlVal);
                    }
                } else {
                    if (tlvConf->isAStringParam((char*)currParam->name)) {
                        tlvConf->updateParamByName((char*)currParam->name, "");
                    } else {
                        throw MlxcfgException(
                                  "The Parameter %s of the configuration %s does not have value",
                                  (char*)currParam->name,
                                  tlvConf->_name.c_str());
                    }
                }
                XMLFREE_AND_SET_NULL(xmlVal);
                currParam = currParam->next;
            }
            //process arrayValues
            for (map<string, map<u_int32_t, string> >::iterator p = arrayValues.begin();
                 p != arrayValues.end(); ++p) {
                //TODO check validity of indices
                string paramName = p->first;
                vector<string> vals(p->second.size());
                for (map<u_int32_t, string>::iterator v = p->second.begin();
                     v != p->second.end(); ++v) {
                    vals[v->first] = v->second;
                }
                tlvConf->updateParamByName(paramName, vals);
            }
            tlvs.push_back(tlvConf);
            currTlv = currTlv->next;
        }
        if (tlvs.size() == 0) {
            throw MlxcfgException("No TLV configurations were found in the XML");
        }
    } catch (MlxcfgException& e) {
        XMLFREE_AND_SET_NULL(writerIdAttr)
        XMLFREE_AND_SET_NULL(portAttr)
        XMLFREE_AND_SET_NULL(ovrEnAttr)
        XMLFREE_AND_SET_NULL(rdEnAttr)
        XMLFREE_AND_SET_NULL(hostAttr)
        XMLFREE_AND_SET_NULL(funcAttr)
        XMLFREE_AND_SET_NULL(xmlVal)
        xmlFreeDoc(doc);
        doc = NULL;
        throw e;
    }
    xmlFreeDoc(doc);
#else
    (void) xmlContent;
    (void) tlvs;
    throw MlxcfgException("Can not run the command, the tool was not compiled against libxml2");
#endif
}

void GenericCommander::XML2Raw(const string& xmlContent, string& raw)
{
    vector<TLVConf*> tlvs;

    XML2TLVConf(xmlContent, tlvs);

    raw = RAW_FILE_FINGERPRINT;

    VECTOR_ITERATOR(TLVConf*, tlvs, tlvConf) {
        string rawTLV;
        (*tlvConf)->genRaw(rawTLV);
        raw += '\n' + rawTLV + '\n';
    }

    VECTOR_ITERATOR(TLVConf*, tlvs, tlvConf) {
        VECTOR_ITERATOR(Param*, (*tlvConf)->_params, param) {
            delete *param;
        }
        delete *tlvConf;
    }
}

void GenericCommander::TLVConf2Bin(const vector<TLVConf*>& tlvs, vector<u_int32_t>& buff, bool withHeader)
{
    CONST_VECTOR_ITERATOR(TLVConf*, tlvs, tlvConf) {
        vector<u_int32_t> tmpBuff;
        (*tlvConf)->genBin(tmpBuff, withHeader);
        buff.insert(buff.end(), tmpBuff.begin(), tmpBuff.end());
    }
}

void GenericCommander::XML2Bin(const string& xml, vector<u_int32_t>& buff, bool withHeader)
{
    vector<TLVConf*> tlvs;

    XML2TLVConf(xml, tlvs);

    TLVConf2Bin(tlvs, buff, withHeader);

    VECTOR_ITERATOR(TLVConf*, tlvs, tlvConf) {
        VECTOR_ITERATOR(Param*, (*tlvConf)->_params, param) {
            delete *param;
        }
        delete *tlvConf;
    }
}

void GenericCommander::sign(vector<u_int32_t>& buff, const string& privateKeyFile, const string& keyPairUUid)
{
    (void)keyPairUUid;
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    MlxSignRSA rsa;
    MlxSignSHA *mlxSignSHA = NULL;
    vector<u_int32_t> encDigestDW;
    vector<u_int8_t> digest, encDigest, bytesBuff;
    MlxSign::SHAType shaType;

    copyDwVectorToBytesVector(buff, bytesBuff);

    if (privateKeyFile.empty()) {
        shaType = MlxSign::SHA256;
        mlxSignSHA = new MlxSignSHA256();
    } else {
        int rc = rsa.setPrivKeyFromFile(privateKeyFile);
        if (rc) {
            throw MlxcfgException("Failed to set private key (rc = 0x%x)\n", rc);
        }
        int privKeyLength = rsa.getPrivKeyLength();
        if (privKeyLength == 0x100) {
            shaType = MlxSign::SHA256;
            mlxSignSHA = new MlxSignSHA256();
        } else if (privKeyLength == 0x200) {
            shaType = MlxSign::SHA512;
            mlxSignSHA = new MlxSignSHA512();
        } else {
            throw MlxcfgException("Invalid length of private key(%d bytes)",
                                  privKeyLength);
        }
    }

    (*mlxSignSHA) << bytesBuff;
    mlxSignSHA->getDigest(digest);
    delete mlxSignSHA;

    if (privateKeyFile.empty()) {
        encDigest.insert(encDigest.begin(), digest.begin(), digest.end());
    } else {
        int rc = rsa.sign(shaType, digest, encDigest);
        if (rc) {
            throw MlxcfgException("Failed to encrypt the digest (rc = 0x%x)\n", rc);
        }
    }
    //fetch the signature tlv from the database and fill in the data
    if (shaType == MlxSign::SHA256) {
        vector<u_int32_t> signTlvBin;
        TLVConf *signTLV = _dbManager->getTLVByName("file_signature", 0);

        Param *keyPairUUidParam = signTLV->findParamByName("keypair_uuid");
        ((BytesParamValue*) keyPairUUidParam->_value)->setVal(keyPairUUid);

        Param *signatureParam = signTLV->findParamByName("signature");
        if (NULL == signatureParam) {
            throw MlxcfgException("The signature parameter was not found\n");
        }
        copyBytesVectorToDwVector(encDigest, encDigestDW);
        VECTOR_BE32_TO_CPU(encDigestDW)
            ((BytesParamValue*) signatureParam->_value)->setVal(encDigestDW);

        signTLV->genBin(signTlvBin);

        buff.insert(buff.end(), signTlvBin.begin(), signTlvBin.end());
    } else {
        TLVConf *signTLV1 = _dbManager->getTLVByName("file_signature_512_a", 0);
        TLVConf *signTLV2 = _dbManager->getTLVByName("file_signature_512_b", 0);

        Param *keyPairUUidParam1 = signTLV1->findParamByName("keypair_uuid");
        ((BytesParamValue*) keyPairUUidParam1->_value)->setVal(keyPairUUid);
        Param *keyPairUUidParam2 = signTLV2->findParamByName("keypair_uuid");
        ((BytesParamValue*) keyPairUUidParam2->_value)->setVal(keyPairUUid);

        copyBytesVectorToDwVector(encDigest, encDigestDW);
        VECTOR_BE32_TO_CPU(encDigestDW)

        Param *signatureParam1 = signTLV1->findParamByName("signature");
        Param *signatureParam2 = signTLV2->findParamByName("signature");

        //For Debug:
        /*for(unsigned int i = 0; i < encDigestDW.size(); i++) {
            printf("0x%x ", encDigestDW[i]);
           }
           printf("\n");*/

        //split encDigestDW
        unsigned int middleOfEncDigestDW = encDigestDW.size() / 2;
        vector<u_int32_t> encDigestDW1(middleOfEncDigestDW), encDigestDW2(middleOfEncDigestDW);
        for (unsigned int i = 0; i < middleOfEncDigestDW; i++) {
            encDigestDW1[i] = encDigestDW[i];
            encDigestDW2[i] = encDigestDW[encDigestDW.size() / 2 + i];
        }
        ((BytesParamValue*) signatureParam1->_value)->setVal(encDigestDW1);
        ((BytesParamValue*) signatureParam2->_value)->setVal(encDigestDW2);

        //For Debug:
        /*for(unsigned int i = 0; i < encDigestDW1.size(); i++) {
            printf("0x%x ", encDigestDW1[i]);
           }
           printf("\n");
           for(unsigned int i = 0; i < encDigestDW2.size(); i++) {
            printf("0x%x ", encDigestDW2[i]);
           }
           printf("\n");*/

        vector<u_int32_t> signTlvBin1;
        signTLV1->genBin(signTlvBin1);
        buff.insert(buff.end(), signTlvBin1.begin(), signTlvBin1.end());

        vector<u_int32_t> signTlvBin2;
        signTLV2->genBin(signTlvBin2);
        buff.insert(buff.end(), signTlvBin2.begin(), signTlvBin2.end());
    }
#else
    (void)buff;
    (void)privateKeyFile;
    throw MlxcfgException("Sign command is not implemented\n");
#endif
}

void GenericCommander::sign(vector<u_int32_t>& buff)
{
    string keyPairUUid;
    sign(buff, "", keyPairUUid);
}

void GenericCommander::checkConfTlvs(const vector<TLVConf*>& tlvs, FwComponent::comps_ids_t& compsId)
{
    bool dbgCompFound = false;
    bool csCompFound = false;
    bool foundApplicableTLV = false;
    bool idMlnxCompFound = false;
    CONST_VECTOR_ITERATOR(TLVConf*, tlvs, it) {
        const TLVConf *tlv = *it;
        if (tlv->_tlvClass == NVFile &&
            tlv->_id == debugTokenId) {
            dbgCompFound = true;
            compsId = FwComponent::COMPID_DBG_TOKEN;
        } else if (tlv->_tlvClass == NVFile &&
                   tlv->_id == csTokenId) {
            csCompFound = true;
            compsId = FwComponent::COMPID_CS_TOKEN;
        } else if (tlv->_tlvClass == 0x0 &&
                   tlv->_id == idMlnxId) {
            idMlnxCompFound = true;
            compsId = FwComponent::COMPID_MLNX_NVCONFIG;
        } else if (tlv->_name == "file_applicable_to") {
            foundApplicableTLV = true;
        }
    }

    if (!dbgCompFound && !csCompFound && !idMlnxCompFound) {
        throw MlxcfgException("Unsupported device: No debug tokens or CS tokens or MLNX ID Components were found for this device");
    }

    if ((dbgCompFound && csCompFound) ||
        (dbgCompFound && idMlnxCompFound) ||
        (csCompFound && idMlnxCompFound)) {
        throw MlxcfgException("Only one component is allowed");
    }

    //At least one TLV must be file_applicable_to
    if (!foundApplicableTLV) {
        throw MlxcfgException("At least one file_applicable_to tlv must be in the configuration file");
    }

}

void GenericCommander::orderConfTlvs(vector<TLVConf*>& tlvs)
{
    VECTOR_ITERATOR(TLVConf*, tlvs, it) {
        TLVConf *tlv = *it;
        if (((tlv->_tlvClass == NVFile) &&
             (tlv->_id == debugTokenId || tlv->_id == csTokenId)) ||
            (tlv->_tlvClass == Global && tlv->_id == idMlnxId)) {
            *it = tlvs.front();
            tlvs.front() = tlv;
            break;
        }
    }

    //file_applicable_to must be after the component
    VECTOR_ITERATOR(TLVConf*, tlvs, it) {
        TLVConf *tlv = *it;
        if (tlv->_name == "file_applicable_to") {
            *it = *(tlvs.begin() + 1);
            *(tlvs.begin() + 1) = tlv;
            break;
        }
    }

}

void GenericCommander::createConf(const string& xml, vector<u_int32_t>& buff)
{
    vector<TLVConf*> tlvs;
    vector<u_int32_t> tlvsBuff;
    FwComponent::comps_ids_t compsId;

    //Add the fingerprint
    string fingerPrint(BIN_FILE_FINGERPRINT);
    for (unsigned int i = 0; i < fingerPrint.length(); i += 4) {
        buff.push_back(*(u_int32_t*)(fingerPrint.c_str() + i));
    }

    XML2TLVConf(xml, tlvs);

    checkConfTlvs(tlvs, compsId);

    orderConfTlvs(tlvs);

    TLVConf2Bin(tlvs, tlvsBuff, true);

    buff.insert(buff.end(), tlvsBuff.begin(), tlvsBuff.end());
}

void GenericCommander::apply(const vector<u_int8_t>& buff)
{
    FwComponent comp;
    vector<TLVConf*> tlvs;
    vector<u_int32_t> dwBuff;
    FwCompsMgr fwCompsAccess(_mf);
    vector<FwComponent> compsToBurn;
    FwComponent::comps_ids_t compsId;

    size_t fingerPrintLength = strlen(BIN_FILE_FINGERPRINT);

    //Check if there is a fingerprint:
    if (buff.size() < fingerPrintLength) {
        throw MlxcfgException("Invalid Configuration file");
    }
    for (unsigned int i = 0; i < fingerPrintLength; i += 4) {
        if (buff[i] != BIN_FILE_FINGERPRINT[i]) {
            throw MlxcfgException("Fingerprint is missing in the Configuration file");
        }
    }

    dwBuff.resize((buff.size() - fingerPrintLength) >> 2);
    memcpy(dwBuff.data(),
           buff.data() + fingerPrintLength,
           buff.size() - fingerPrintLength);
    bin2TLVConfs(dwBuff, tlvs);

    checkConfTlvs(tlvs, compsId);

    if (!fwCompsAccess.getFwSupport()) {
        throw MlxcfgException("Firmware does not support applying configurations files");
    }

    comp.init(buff, buff.size(), compsId);
    compsToBurn.push_back(comp);
    if (!fwCompsAccess.burnComponents(compsToBurn)) {
        throw MlxcfgException("Error applying the component: %s",
                              fwCompsAccess.getLastErrMsg());
    }

}

void GenericCommander::raw2XML(const vector<string>& lines, string& xmlTemplate)
{
    bool foundTlv = false;
    xmlTemplate = XML_DOCUMENT_START;

    //check fingerprint in first line
    vector<string>::const_iterator it = lines.begin();
    if (it == lines.end() || *it != RAW_FILE_FINGERPRINT) {
        throw MlxcfgException("Raw Content Fingerprint " RAW_FILE_FINGERPRINT " is missing or incorrect");
    }

    it++;

    for (; it != lines.end(); it++) {
        string tlvXMLTemplate;
        if ((*it)[0] == '%') { //a FILE_COMMENT tlv
            //TODO
        } else {
            //printf("-D- line=%s\n", it->c_str());
            char *p = NULL;
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
RawCfgParams5thGen::RawCfgParams5thGen()
{
    memset(&_nvdaTlv, 0, sizeof(struct tools_open_nvda));
}

int RawCfgParams5thGen::setRawData(const std::vector<u_int32_t>& tlvBuff)
{
    if (tlvBuff.size() * 4 > TOOLS_OPEN_NVDA_SIZE) {
        return errmsg(MCE_BAD_PARAM_VAL, "TLV size exceeds maximal limit. Maximum size is 0x%x bytes, actual length is 0x%x bytes", TOOLS_OPEN_NVDA_SIZE, (u_int32_t)(tlvBuff.size() * 4));
    }
    _tlvBuff = tlvBuff;
    memset(&_nvdaTlv, 0, sizeof(struct tools_open_nvda));
    std::vector<u_int32_t> tlvBuffBe = _tlvBuff;
    tlvBuffBe.resize(TOOLS_OPEN_NVDA_SIZE >> 2);
    memset(&tlvBuffBe[0], 0, TOOLS_OPEN_NVDA_SIZE);
    tlvBuffBe.insert(tlvBuffBe.begin(), _tlvBuff.begin(), _tlvBuff.end());
    for (std::vector<u_int32_t>::iterator it = tlvBuffBe.begin(); it != tlvBuffBe.end(); it++) {
        *it = __cpu_to_be32(*it);
    }
    tools_open_nvda_unpack(&_nvdaTlv, ((u_int8_t*)(&tlvBuffBe[0])));
    _nvdaTlv.nv_hdr.writer_id = WRITER_ID_ICMD_MLXCONFIG_SET_RAW;
    return verifyTlv();
}

int RawCfgParams5thGen::setOnDev(mfile *mf)
{
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

std::string RawCfgParams5thGen::dumpTlv()
{
    char str[1024] = {0};
    snprintf(str, 1024, "Length: 0x%x\nVersion: %d\nOverrideEn: %d\nType: 0x%08x\nData: ", _nvdaTlv.nv_hdr.length, \
             _nvdaTlv.nv_hdr.version, _nvdaTlv.nv_hdr.over_en, _nvdaTlv.nv_hdr.type.tlv_type_dw.tlv_type_dw);
    for (size_t i = 3; i < _tlvBuff.size(); i++) {
        char numStr[64] = {0};
        snprintf(numStr, 64, "0x%08x ", _tlvBuff[i]);
        strcat(str, numStr);
    }
    strcat(str, "\n");
    return str;
}

int RawCfgParams5thGen::verifyTlv()
{
    // check TLV length
    int tlvLength = (_tlvBuff.size() - 3) << 2;
    if (tlvLength != _nvdaTlv.nv_hdr.length) {
        return errmsg(MCE_BAD_PARAM_VAL, "TLV size mismatch. reported length in TLV header: 0x%x. actual length: 0x%x", _nvdaTlv.nv_hdr.length, tlvLength);
    }
    return MCE_SUCCESS;
}
