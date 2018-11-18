
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
 */

/*
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
