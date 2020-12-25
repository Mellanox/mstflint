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



#include "hex64.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

#ifndef UEFI_BUILD
#define DPRINTF(args)        do { char *reacDebug = getenv("HEX64_DEBUG"); \
                                  if (reacDebug != NULL) {  printf("\33[2K\r"); \
                                      printf("[HEX64_DEBUG]: -D- "); printf args; fflush(stdout);} } while (0)
#else
#define DPRINTF(...)
#endif



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
        DPRINTF(("0x%02x, ", scanResult));
        if ((j % 16) == 0) {
            DPRINTF(("\n"));
        }
        j++;
    }
    return true;
}

bool writeToFile(const std::vector<unsigned char>& buff, string filePath)
{
    FILE *fh = fopen(filePath.c_str(), "wb");
    if (fh == NULL) {
        return false;
    }
    // Write
    if (fwrite(&buff[0], 1, buff.size(), fh) != buff.size()) {
        fclose(fh);
        return false;
    }
    fclose(fh);
    return true;
}

bool Hex64Manipulations::ParsePemFile(string inputFile, vector<unsigned char>& outputBuffer, bool& IsPemFile8Format)
{
    vector<unsigned char> inputBuffer;
    unsigned int inputSize = 0;
    vector<unsigned char> finalBuffer;
    bool IsPem8Format = false;
    IsPemFile8Format = false;
    if (ReadInputPemFile(inputFile.c_str(), inputBuffer, inputSize, IsPem8Format) == false) {
        return false;
    }
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
    if (IsPem8Format) {
        IsPemFile8Format = true;
        if (finalBuffer.size() < 2376) {
            // details here  http://lapo.it/asn1js/
            unsigned int NumPlacesToFix = 2376 - finalBuffer.size();
            //actually the decoded file is absolutely legal from TLV point of view, but we must pad it to required size
            //important that we will not "fix" more then required!
            //it's actually zero's padding, but simple padding at the end of file doesn't work
            DPRINTF(("-D- PEM buffer size is %u places to fix %u\n", (unsigned int)finalBuffer.size(), NumPlacesToFix));
            vector<unsigned char> outputFixedBuffer(2376, 0);
            unsigned int corruptedIndex = 0;
            unsigned int fixedIndex = 0;
            while (fixedIndex != 2376) {
                outputFixedBuffer[fixedIndex] = finalBuffer[corruptedIndex];
                if (NumPlacesToFix > 0) {
                    if (corruptedIndex >= 3) {
                        if (finalBuffer[corruptedIndex - 3] == 0x02 && finalBuffer[corruptedIndex - 2] == 0x82 &&
                            (finalBuffer[corruptedIndex - 1] == 0x02 || finalBuffer[corruptedIndex - 1] == 0x01) &&
                            finalBuffer[corruptedIndex] == 0) {//"CORRUPTED" TLV
                            outputFixedBuffer[3] = outputFixedBuffer[3] + 1;//change the main TLV size
                            outputFixedBuffer[25] = outputFixedBuffer[25] + 1;//change the secondary TLV size
                            outputFixedBuffer[29] = outputFixedBuffer[29] + 1;//the same
                            outputFixedBuffer[fixedIndex] = 1;//increase current TLV by 1
                            fixedIndex++;//don't need to put 0, it's there already
                            DPRINTF(("-D- PEM buffer fixed at index %u to index %u\n", corruptedIndex, fixedIndex));
                            NumPlacesToFix--;
                        }
                    }
                }
                corruptedIndex++;
                fixedIndex++;
            }
            finalBuffer = outputFixedBuffer;
        }
        else {
            DPRINTF(("-D- size of decoded buffer is illegal %u\n", (unsigned int)finalBuffer.size()));
            return false;
        }
        outputBuffer.resize(finalBuffer.size());
        for (unsigned int i = 0; i < finalBuffer.size(); i++) {
            outputBuffer[i] = finalBuffer[i];
        }
        return true;
    }
    else {//NOT IsPem8Format, just copy the result to output buffer
        outputBuffer.resize(finalBuffer.size());
        for (unsigned int i = 0; i < finalBuffer.size(); i++) {
            outputBuffer[i] = finalBuffer[i];
        }
        DPRINTF(("-D- PEM outputBuffer buffer size is %u\n", (unsigned int)outputBuffer.size()));
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


bool Hex64Manipulations::ReadInputPemFile(const char* fileName, vector<unsigned char> &outputBuffer, unsigned int& inputSize, bool& IsPem8Format)
{
    bool IsPem1File = false;
    bool IsPem8File = false;
    IsPem8Format = false;
    vector<unsigned char> tempBuffer;
    FILE *fd = fopen(fileName, "rb");
    if (fd == NULL) {
        return false;
    }
    if (fseek(fd, 0, SEEK_END) < 0) {
        fclose(fd);
        return false;
    }
    size_t fileSize = ftell(fd);
    rewind(fd);
    tempBuffer.resize(fileSize);
    // Read
    if (fread(&tempBuffer[0], 1, fileSize, fd) != fileSize) {
        fclose(fd);
        return false;
    }
    if (memcmp(&tempBuffer[0], PEM_1_PREFIX, PEM_1_PREFIX_LENGTH) == 0) {
        IsPem1File = true;
    }
    else if (memcmp(&tempBuffer[0], PEM_8_PREFIX, PEM_8_PREFIX_LENGTH) == 0) {
        IsPem8File = true;
    }
    else {
        fclose(fd);
        return false;
    }

    /* If PEM8, Skip first 28 bytes */
    if (IsPem8File) {
        fseek(fd, PEM_8_PREFIX_LENGTH + 1, SEEK_SET);
        inputSize = fileSize - 55;//suffix is 27 bytes
        outputBuffer.resize(inputSize);
        // Read
        if (fread(&outputBuffer[0], 1, inputSize, fd) != inputSize) {
            fclose(fd);
            return false;
        }
        IsPem8Format = true;
    }
    else if (IsPem1File) {
        /* If PEM1, Skip first 32 bytes */
        fseek(fd, PEM_1_PREFIX_LENGTH + 1, SEEK_SET);
        inputSize = fileSize - 63;//suffix is 31 bytes
        outputBuffer.resize(inputSize);
        // Read
        if (fread(&outputBuffer[0], 1, inputSize, fd) != inputSize) {
            fclose(fd);
            return false;
        }

    }
    fclose(fd);
    return true;
}

