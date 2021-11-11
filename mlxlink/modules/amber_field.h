/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef AMBER_FIELD_H
#define AMBER_FIELD_H

#include <iostream>
#include <common/compatibility.h>
#include <vector>

using namespace std;

class AmberField {
public:
    AmberField (const string &uiField, const string &uiValue, bool visible = true);
    AmberField (const string &uiField, const string &uiValue, u_int64_t prmValue, bool visible = true);

    ~AmberField ();

    friend ostream& operator<<(ostream& os, const AmberField &amberField);

    string getUiField() const;
    string getUiValue() const;
    u_int64_t getPrmValue() const;
    bool isVisible();
    u_int32_t getFieldIndex();
    static void reset();
    static string getValueFromFields(const vector<AmberField> &fields, const string &uiField, bool getPrmValue = false);

    static u_int32_t _lastFieldIndex;
    static bool _dataValid;

private:
    u_int32_t _fieldIndex;
    string _prmReg;
    string _prmField;
    string _uiField;
    u_int64_t _prmValue;
    string _uiValue;
    string _fieldGroup;
    bool _visible;
};

#endif /* AMBER_FIELD_H */
