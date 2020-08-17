
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
 * mlxarchive_mfa2_extension.h
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#ifndef MLXARCHIVE_MFA2_EXTENSION_H_
#define MLXARCHIVE_MFA2_EXTENSION_H_

#include <string>
#include <vector>
#include <iostream>
#include <compatibility.h>
#include <tools_layouts/tools_open_layouts.h>

#include "mlxarchive_mfa2_element.h"
#include "mfa2_buff.h"

using namespace std;

namespace mfa2 {

class Version
{

public:
    Version() 
    {
        major = -1;
        minor = -1;
        subminor = -1;
    }


    Version(std::string version)
    {
        sscanf(version.c_str(), "%d.%d.%d", &major, &minor, &subminor);
    }

private:
    int major; 
    int minor;
    int subminor;

public:
    bool operator < (const Version& other)
    {
        if (major < other.major)
            return true;
        if (minor < other.minor)
            return true;
        if (subminor < other.subminor)
            return true;
        return false;
    }
    bool operator > (const Version& other)
    {
        if (major > other.major)
            return true;
        if (minor > other.minor)
            return true;
        if (subminor > other.subminor)
            return true;
        return false;
    }

    bool operator == (const Version& other)
    {
        return major == other.major
            && minor == other.minor
            && subminor == other.subminor;
    }

    friend std::ostream& operator << (std::ostream& stream, const Version& ver)
    {
        stream << ver.major;
        stream << '.';
        stream << ver.minor;
        stream << '.';
        stream << ver.subminor;
        return stream;
    }
};

class Extension : protected Element{
protected:
    enum ExtensionType {
        VersionExtensionType,
        SecurityInfoExtensionType,
        ComponentPointerExtensionType,
        SHA256ExtensionType,
        DescriptorsSHA256ExtensionType,
        CommentExtensionType,
        PSIDExtensionType,
        SourceFileNameExtensionType
    };

    MFA2Type extensionTypeToMFA2Type(ExtensionType type);

protected:
    /*class Digest {
    protected:
        vector<u_int8_t> _digest;
        const static u_int32_t _length = 0x20;
    public:
        void setDigest(vector<u_int8_t> digest);
    };*/

public:
    Extension(u_int8_t vesrion, ExtensionType type, u_int32_t length);

    virtual void pack(vector<u_int8_t>& buff) const = 0;
    virtual bool unpack(Mfa2Buffer & buff) = 0;

    virtual ~Extension  () {};
};

class VersionExtension : Extension {
private:
    u_int8_t _major;
    u_int16_t _subMinor;
    u_int8_t _minor;
    u_int8_t _seconds;
    u_int8_t _minutes;
    u_int8_t _hours;
    u_int8_t _day;
    u_int8_t _month;
    u_int16_t _year;
public:
    const static u_int8_t  ELEMENT_VERSION = 0x0;
    const static u_int32_t LENGTH  = TOOLS_OPEN_VERSION_SIZE;
    void fillTimeAndDate();

    VersionExtension(const string& version);
    VersionExtension(const u_int16_t* version);
    VersionExtension(const u_int16_t* version, const u_int16_t* fw_rel_date);
    void pack(vector<u_int8_t>& buff) const;
    bool unpack(Mfa2Buffer & buff);
    string getVersion(bool pad_sub_minor) const;
    string getDateAndTime() const;
    void   getDateAndTime(char* buffer) const;
    u_int8_t getMajor() const {
        return _major;
    }
    u_int8_t getMinor() const {
        return _minor;
    }
    u_int16_t getSubMinor() const {
        return _subMinor;
    }
};

/*class SecurityInfoExtension : Extension {

private:
    string _uuid;
    SecurityMode _securityMode;

public:
    SecurityInfoExtension(string uuid, SecurityMode mode);

};*/

class ComponentPointerExtension : Extension {
private:
    u_int16_t _componentIndex;
    u_int8_t  _storageId; //TODO: use enums
    u_int32_t _storageAddress;
public:
    const static u_int8_t  ELEMENT_VERSION = 0x0;
    const static u_int32_t LENGTH  = TOOLS_OPEN_COMPONENT_PTR_SIZE;

    explicit ComponentPointerExtension(u_int16_t componentIndex) :
                Extension(ELEMENT_VERSION, ComponentPointerExtensionType, LENGTH),
                _componentIndex(componentIndex),
                _storageId(0x1),
                _storageAddress(0x0){};

    void pack(vector<u_int8_t>& buff) const;
    bool unpack(Mfa2Buffer & buff);
    u_int16_t getComponentIndex() const { return _componentIndex;}
};

class SHA256Extension : Extension {
public:
    enum SHA256Scope {
        SHA256Scope_Descriptors,
        SHA256Scope_All
    };
    const static u_int8_t  ELEMENT_VERSION = 0x0;
    const static u_int32_t LENGTH  = 0x20;

    explicit SHA256Extension(enum SHA256Scope scope);
    void setDigest(vector<u_int8_t> digest);
    void pack(vector<u_int8_t>& buff) const;
    bool unpack(Mfa2Buffer & buff);
private:
    vector<u_int8_t> _digest;

    ExtensionType scopeToExtensionType(enum SHA256Scope);
};

/*class DescriptorsSHA256Extension : Extension, Extension::Digest {
private:
    const static u_int8_t  ELEMENT_VERSION = 0x0;
    const static u_int32_t LENGTH  = Extension::Digest::_length;
public:
    DescriptorsSHA256Extension() :
        Extension(ELEMENT_VERSION, DescriptorsSHA256ExtensionType, LENGTH) {};
    void pack(vector<u_int8_t>& buff) const;
};*/

class StringExtension : public Extension {
private:
    string _str;
public:
    StringExtension(u_int8_t vesrion, ExtensionType type, string str) :
        Extension(vesrion, type, str.length()),
        _str(str) {};
    u_int32_t length() const;
    void pack(vector<u_int8_t>& buff) const;
    bool unpack(Mfa2Buffer & buff);

    const string & getString() const { return _str;}
};

inline u_int32_t StringExtension::length() const
{
    return _str.length();
}

class CommentExtension : public StringExtension {
private:
    const static u_int8_t  ELEMENT_VERSION = 0x0;
public:
    explicit CommentExtension(string comment) :
        StringExtension(ELEMENT_VERSION, CommentExtensionType, comment) {};
};

class PSIDExtension : public StringExtension {
private:
    const static u_int8_t  ELEMENT_VERSION = 0x0;
public:
    explicit PSIDExtension(string psid) :
        StringExtension(ELEMENT_VERSION, PSIDExtensionType, psid) {};
};

class SourceFileNameExtension : public StringExtension {
private:
    const static u_int8_t  ELEMENT_VERSION = 0x0;
public:
    explicit SourceFileNameExtension(string src) :
        StringExtension(ELEMENT_VERSION, SourceFileNameExtensionType, src) {};
};
}
#endif
