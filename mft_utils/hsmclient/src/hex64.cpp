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

#ifndef __WIN__

#include "hex64.h"
#include <stdio.h>
using namespace std;
static const char* base64_chars[2] = {
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789"
             "+/",

             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789"
             "-_" };
size_t Hex64Manipulations::pos_of_char(const unsigned char chr) {
    //
    // Return the position of chr within base64_encode()
    //

    if (chr >= 'A' && chr <= 'Z') return chr - 'A';
    else if (chr >= 'a' && chr <= 'z') return chr - 'a' + ('Z' - 'A') + 1;
    else if (chr >= '0' && chr <= '9') return chr - '0' + ('Z' - 'A') + ('z' - 'a') + 2;
    else if (chr == '+' || chr == '-') return 62; // Be liberal with input and accept both url ('-') and non-url ('+') base 64 characters (
    else if (chr == '/' || chr == '_') return 63; // Ditto for '/' and '_'

    return 0xffff;
}

string Hex64Manipulations::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
    string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';

    }
    return ret;
}

bool Hex64Manipulations::PrintHexData(const string& data)
{
    unsigned int input_length = data.size();
    int j = 1;

    for (size_t i = 0; i < input_length; i++) {
        unsigned char scanResult = 0;
        scanResult = (unsigned char)data[i];
        printf("0x%02x, ", scanResult);
        if ((j % 16) == 0) {
            printf("\n");
        }
        j++;
    }
    return true;
}

bool Hex64Manipulations::ParsePemFile(string inputFile, vector<unsigned char>& outputBuffer)
{
    vector<unsigned char> inputBuffer;
    unsigned int inputSize = 0;
    vector<unsigned char> finalBuffer;
    ReadInputPemFile(inputFile.c_str(), inputBuffer, inputSize);
    string inputStr(inputBuffer.begin(), inputBuffer.end());
    string copy(inputStr);
    size_t pos = 0;
    while ((pos = copy.find("\n", pos)) != string::npos) {
        copy.erase(pos, 1);
    }
    string decoded_array = base64_decode(copy);
    if (decoded_array.empty()) {
        return false;
    }
    finalBuffer.resize(decoded_array.size());
    for (unsigned int i = 0; i < decoded_array.size(); i++) {
        finalBuffer[i] = decoded_array[i];
    }
    
    if (finalBuffer.size() != 2376) {
        if (finalBuffer.size() == 2375) {
            // sometimes hex64 format gives 1 byte less, as well as openssl tool, 
            // so add missing a zero byte at offset 558
            // details here  http://lapo.it/asn1js/
            if (finalBuffer[555] == 0x02 && finalBuffer[556] == 0x82 && finalBuffer[557] == 0x02 &&
                finalBuffer[558] == 0x00) {

                vector<unsigned char> outputFixedBuffer(2376, 0);
                for (unsigned int i = 0; i < 558; i++) {
                    outputFixedBuffer[i] = finalBuffer[i];
                }
                outputFixedBuffer[3] = outputFixedBuffer[3] + 1;//change the main TLV size
                outputFixedBuffer[25] = outputFixedBuffer[25] + 1;//change the secondary TLV size
                outputFixedBuffer[29] = outputFixedBuffer[29] + 1;//the same
                outputFixedBuffer[558] = 1;// this will construct TLV from 02 82 02 00 to 02 82 02 01
                outputFixedBuffer[559] = 0;// add zero before private exponent
                for (unsigned int i = 560; i < outputFixedBuffer.size(); i++) {
                    outputFixedBuffer[i] = finalBuffer[i - 1];
                }
                finalBuffer = outputFixedBuffer;
            }
            else {
                printf("Cannot parse the PEM file. The error is not private exponent.\n");
                return false;
            }
        }
        else {
            printf("Cannot parse the PEM file. The format must be PKCS8!\n");
            return false;
        }
    }
    outputBuffer.resize(finalBuffer.size());
    for (unsigned int i = 0; i < finalBuffer.size(); i++) {
        outputBuffer[i] = finalBuffer[i];
    }
    return true;
}

string Hex64Manipulations::base64_decode(string encoded_string)
{
    int length_of_string = encoded_string.length();
    if (!length_of_string) {
        return string("");
    }

    size_t in_len = length_of_string;
    size_t pos = 0;
    size_t approx_length_of_decoded_string = length_of_string / 4 * 3;
    string ret;
    ret.reserve(approx_length_of_decoded_string);

    while (pos < in_len) {
        unsigned int pos_of_char_1 = pos_of_char(encoded_string[pos + 1]);
        if (pos_of_char_1 == 0xffff) {
            return string();
        }
        ret.push_back(((pos_of_char(encoded_string[pos + 0])) << 2) + ((pos_of_char_1 & 0x30) >> 4));
        if (encoded_string[pos + 2] != '=' && encoded_string[pos + 2] != '.') { // accept URL-safe base 64 strings, too, so check for '.' also.
            unsigned int pos_of_char_2 = pos_of_char(encoded_string[pos + 2]);
            ret.push_back(((pos_of_char_1 & 0x0f) << 4) + ((pos_of_char_2 & 0x3c) >> 2));
            if (encoded_string[pos + 3] != '=' && encoded_string[pos + 3] != '.') {
                ret.push_back(((pos_of_char_2 & 0x03) << 6) + pos_of_char(encoded_string[pos + 3]));
            }
        }
        pos += 4;
    }
    return ret;
}

bool Hex64Manipulations::ReadInputPemFile(const char* fileName, vector<unsigned char> &outputBuffer, unsigned int& inputSize)
{
    FILE *fd = fopen(fileName, "rb");
    if (fd == NULL) {
        return false;
    }
    if (fseek(fd, 0, SEEK_END) < 0) {
        fclose(fd);
        return false;
    }
    long int fileSize = ftell(fd);
    if (fileSize < 0) {
        fclose(fd);
        return false;
    }
    rewind(fd);
    /* Skip first 28 bytes */
    fseek(fd, 28, SEEK_SET);
    inputSize = fileSize - 55;
    outputBuffer.resize(inputSize);
    // Read
    if (fread(&outputBuffer[0], 1, inputSize, fd) != inputSize) {
        fclose(fd);
        return false;
    }
    fclose(fd);
    return true;
}
#endif
