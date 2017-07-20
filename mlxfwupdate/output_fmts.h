
/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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

#ifndef __OUTPUT_FMTS__
#define __OUTPUT_FMTS__

#include <vector>
#include <string>
#include "mlnx_dev.h"
#include "psid_query_item.h"
#include "psid_lookup_db.h"
#include <map>

using namespace std;

class OutputFmts
{
public:
    int createInventoryXML(vector<MlnxDev*> &devs, PsidLookupDB &psidLookupDB, int result, string msg, string &buffer, int buf_is_file);
    int createBurnXML(vector<MlnxDev*> &devs, map<string, PsidQueryItem> &psidUpdateInfo, PsidLookupDB &psidLookupDB, string &buffer, int buf_is_file, int CompareFFV);
    int createFailXML(int result, int update_query_, string &buffer, int buf_is_file);
    void setForceModeParam(bool force_mode);

private:
    bool _force_mode;
};


#endif
