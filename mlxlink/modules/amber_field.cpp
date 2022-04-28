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

#include "amber_field.h"
#include "mlxlink_utils.h"
#include "mlxlink_reg_parser.h"

u_int32_t AmberField::_lastFieldIndex = 1;
bool AmberField::_dataValid = true;

AmberField::AmberField(const string &uiField, const string &uiValue,
                       bool visible) : _uiField(uiField), _visible(visible)
{
    _prmReg = "";
    _prmField = "";
    _prmValue = 0;
    _fieldGroup = "";
    _uiValue = AmberField::_dataValid? uiValue : "N/A";
    if (visible) {
        _fieldIndex = _lastFieldIndex;
        _lastFieldIndex++;
    } else {
        _fieldIndex = 0;
    }
    findAndReplace(_uiValue, ",", "_");
}

AmberField::AmberField(const string &uiField, const string &uiValue, u_int32_t fieldIndex,
                       bool visible) : _uiField(uiField), _visible(visible)
{
    _prmReg = "";
    _prmField = "";
    _fieldGroup = "";
    _prmValue = 0;
    _uiValue = AmberField::_dataValid? uiValue : "N/A";

    _fieldIndex = fieldIndex;
    _lastFieldIndex = _fieldIndex + 1;
    findAndReplace(_uiValue, ",", "_");
}

AmberField::~AmberField()
{
}

string AmberField::getValueFromFields(const vector<AmberField> &fields,
                                      const string &uiField, bool matchUiField)
{
    string value = "";
    bool found = false;
    for (auto it = fields.begin(); it != fields.end(); it++) {
        if (it->getUiField().find(uiField) != string::npos) {
            if (matchUiField && it->getUiField() != uiField) {
                continue;
            } else {
                value += it->getUiValue() + "_";
                found = true;
            }
        }
    }
    if (!found) {
        throw MlxRegException("Requested field does not exist: %s", uiField.c_str());
    }

    value = deleteLastChar(value);

    return value;
}

ostream& operator<<(ostream& os, const AmberField &amberField)
{
        if (amberField._visible) {
            char fieldName[128];
            sprintf(fieldName, "%-40s", amberField._uiField.c_str());
            os << amberField._fieldIndex << "\t"
               << fieldName << "\t\"" << amberField._uiValue << "\"";
        }
        return os;
}

bool operator<(const AmberField &first, const AmberField &second)
{
    return first._fieldIndex < second._fieldIndex;
}

string AmberField::getUiField() const
{
    return _uiField;
}

string AmberField::getUiValue() const
{
    return _uiValue;
}

u_int64_t AmberField::getPrmValue() const
{
    return _prmValue;
}


bool AmberField::isVisible()
{
    return _visible;
}

u_int32_t AmberField::getFieldIndex() const
{
    return _fieldIndex;
}

void AmberField::reset()
{
    AmberField::_lastFieldIndex = 1;
    AmberField::_dataValid = true;
}
