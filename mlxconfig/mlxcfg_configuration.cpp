/*
 * Copyright (c) 2021-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "mlxcfg_configuration.h"
#include <string>

using namespace std;

SystemConfiguration::SystemConfiguration() : name(""), relevantDevices(""), asicNumber(-1), parametersString("") {}

SystemConfiguration::SystemConfiguration(int argc, char** argv, char** colNames) :
    name(""), relevantDevices(""), asicNumber(-1), parametersString("")
{
    for (int i = 0; i < argc; i++)
    {
        if (argv[i] == NULL)
        {
            continue;
        }
        string colName = colNames[i];
        string val = argv[i];

        if (colName == "configuration_name")
        {
            name = val;
        }
        else if (colName == "relevant_devices")
        {
            relevantDevices = val;
        }
        else if (colName == "asic_number")
        {
            asicNumber = std::stoi(val);
        }
        else if (colName == "parameters_string")
        {
            parametersString = val;
        }
    }
}
