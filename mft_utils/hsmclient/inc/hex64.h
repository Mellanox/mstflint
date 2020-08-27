/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2020, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */

#ifndef HEX_64
#define HEX_64


#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Hex64Manipulations
{
private:
    std::string base64_decode(std::string encoded_string);
    bool PrintHexData(const std::string& data);
    std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
    std::size_t pos_of_char(const unsigned char chr);
    bool ReadInputPemFile(const char* fileName, std::vector<unsigned char> &outputBuffer, unsigned int& inputSize);
public:
    Hex64Manipulations() {}
    virtual ~Hex64Manipulations() {}
    bool ParsePemFile(std::string inputFile, std::vector<unsigned char>& outputBuffer);
};
#endif
