/*
 * Copyright (c) 2020 Mellanox Technologies Ltd.  All rights reserved.
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

#ifndef HEX_64
#define HEX_64


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>
#define PEM_1_PREFIX "-----BEGIN RSA PRIVATE KEY-----"
#define PEM_1_PREFIX_LENGTH strlen(PEM_1_PREFIX)
#define PEM_8_PREFIX "-----BEGIN PRIVATE KEY-----"
#define PEM_8_PREFIX_LENGTH strlen(PEM_8_PREFIX)
class Hex64Manipulations
{
private:
    std::string base64_decode(std::string encoded_string);
    bool PrintHexData(const std::string& data);
    std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
    std::size_t pos_of_char(const unsigned char chr);
    bool ReadInputPemFile(const char* fileName, std::vector<unsigned char> &outputBuffer, unsigned int& inputSize, bool& IsPem8Format);
public:
    Hex64Manipulations() {}
    virtual ~Hex64Manipulations() {}
    bool ParsePemFile(std::string inputFile, std::vector<unsigned char>& outputBuffer, bool& IsPemFile8Format);
};
#endif
