/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 * mlxarchive_mfa2_package_gen.h
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#ifndef MLXARCHIVE_MFA2_PACKAGE_GEN_H_
#define MLXARCHIVE_MFA2_PACKAGE_GEN_H_

#include <string>
#include <vector>

#include <compatibility.h>

#include "mlxarchive_mfa2.h"

using namespace std;
using namespace mfa2;

class MFA2PackageGen {

private:

public:
    MFA2PackageGen() {};

    void generateBinFromJSON(const string& jsonFile, vector<u_int8_t>& buff) const;
    void generateBinFromFWDirectory(const string& directory, const string& version, vector<u_int8_t>& buff) const;
    //void generateBinFromDir     (vector<u_int8_t>& buff);
    //void generateJSONFromDir    (const string& output);
    //void generateJSONFromBin    (const string& output);

    //static void generateEmptyJSON(const string& output);

};

#endif
