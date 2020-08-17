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
 */

#ifndef MLXFWOPS_LIB_FW_VERSION_H_
#define MLXFWOPS_LIB_FW_VERSION_H_
#include <iostream>
#include <string>
#include <stdexcept>

#ifdef __WIN__

#ifdef MLXFWOP_EXPORTS
#define MLXFWOP_API __declspec(dllexport)
#else
#define MLXFWOP_API __declspec(dllimport)
#endif

#else
#define MLXFWOP_API
#endif

const std::string DIFFERENT_BRANCHES_EXCEPTION =
        "Trying to compare different branches is invalid";
const std::string NOT_SET_VERSION = "";
const unsigned short MAX_VERSION_LENGTH = 28;

class FwVersionException: public std::runtime_error {
public:
    FwVersionException() :
            std::runtime_error(DIFFERENT_BRANCHES_EXCEPTION) {
    }
};


class MLXFWOP_API FwVersion {
    /*
     * Using MGIR command, when a given FW binary has non-zero value in
     * DEVELOPMENT_INFO, it shall be treated as a development branch file.
     * When the FW binary has empty (filled by 0x0) DEVELOPMENT_INFO field,
     * the FW file is a regular FW release file.
     * (From Development FW Versions for switches)
     */
public:
    FwVersion();
    FwVersion(unsigned short int, unsigned short int, unsigned short int,
            const std::string& = "");
    virtual ~FwVersion();
    FwVersion(const FwVersion&);
    FwVersion& operator=(const FwVersion&);
    bool operator==(const FwVersion&) const;
    bool operator!=(const FwVersion&) const;
    bool operator>(const FwVersion &) const;
    bool operator<(const FwVersion &) const;
    bool operator>=(const FwVersion &) const;
    bool operator<=(const FwVersion &) const;
    std::string get() const;
    friend std::ostream& operator<<(std::ostream&, const FwVersion&);
    std::string get_fw_version(const std::string& master_format = "%d.%d.%d",
            bool even_subminor = false,
            const std::string& not_set = NOT_SET_VERSION) const;
    bool is_set() const;
    bool are_same_branch(const FwVersion&) const;
    int compare_master_version(const FwVersion&) const;
    int compare(const FwVersion&) const;
    virtual FwVersion* clone() const;
protected:
    unsigned short int _major;
    unsigned short int _minor;
    unsigned short int _subminor;
    std::string _devBranchTag;
    virtual std::string get_master_version(const std::string& format,
            bool even_subminor = false) const;
private:
    bool is_master_branch() const;
    /*
     * currently we have 3 FW version format
     * 0: MM.mm.ssss
     * 1: MM.mmbb.ssss
     * 2: MM.mm.bsss / MM.mm.bbss for branch !=0
     * 3: string
     * Where:
     * M: major digit
     * m: minor digit
     * b: branch digit
     * s: subminor digit
     */
    int get_master_format() const;
};

#endif /* MLXFWOPS_LIB_FW_VERSION_H_ */
