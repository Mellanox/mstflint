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
 * mlxarchive_mfa2_package_gen.cpp
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */


#include "mlxarchive_mfa2_package_gen.h"
#include "mlxarchive_mfa2_builder.h"


void MFA2PackageGen::generateBinFromJSON(const string& jsonFile,
        vector<u_int8_t>& buff) const
{
    /*Director director;
    MFA2Builder JSONBuilder(jsonFile);
    director.setBuilder(JSONBuilder);
    MFA2 mfa2 = director.getMFA2();
    mfa2.pack(buff);*/

    MFA2JSONBuilder builder(jsonFile);
    MFA2 mfa2(builder.getPackageDescriptor(),
            builder.getDeviceDescriptors(),
            builder.getComponents());
    mfa2.generateBinary(buff);

    //mfa2.patch(buff);
}

void MFA2PackageGen::generateBinFromFWDirectory(const string& directory, const string& version,
        vector<u_int8_t>& buff) const
{
    FWDirectoryBuilder builder(version, directory);
    MFA2 mfa2(builder.getPackageDescriptor(),
            builder.getDeviceDescriptors(),
            builder.getComponents());
    mfa2.generateBinary(buff);
}
