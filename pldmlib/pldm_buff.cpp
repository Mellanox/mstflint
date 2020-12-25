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
 *
 * pldm_buff.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: Samer Deeb
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include <compatibility.h>

#include "pldm_buff.h"


PldmBuffer::PldmBuffer(): m_buff(NULL), m_pos(0), m_size(0) {
}

PldmBuffer::~PldmBuffer() {
    if (m_buff) {
        delete [] m_buff;
        m_buff = NULL;
    }
}

bool PldmBuffer::loadFile(const std::string& fname)
{
    // open the file:
    FILE * fp;

    fp = fopen(fname.c_str(), "rb");
    if (!fp) {
        return false;
    }

    //Get file length
    fseek(fp, 0, SEEK_END);
    m_size=ftell(fp);
    fseek(fp, 0, SEEK_SET);

    //Allocate memory
    if (m_buff) {
        delete [] m_buff;
        m_buff = NULL;
    }

    m_buff= new u_int8_t[m_size+1];
    if (!m_buff)
    {
        return false;
    }

    //Read file contents into buffer
    size_t read_size = fread(m_buff, m_size, 1, fp);
    fclose(fp);

    return (read_size == (size_t)m_size);
}


void PldmBuffer::read(u_int8_t & val) {
    val = *(m_buff + m_pos);
    m_pos += sizeof(u_int8_t);
}

void PldmBuffer::read(u_int16_t & val) {
    val = *(u_int16_t *)(m_buff + m_pos);
    m_pos += sizeof(u_int16_t);
    val = __le16_to_cpu(val);
}

void PldmBuffer::read(u_int32_t & val) {
    val = *(u_int32_t *)(m_buff + m_pos);
    m_pos += sizeof(u_int32_t);
    val = __le32_to_cpu(val);
}

void PldmBuffer::read(std::string& str, size_t str_size) {
    u_int8_t *arr = new u_int8_t[str_size];
    read(arr, str_size);
    str = std::string(reinterpret_cast<char const *>(arr), str_size);
    delete [] arr;
}

void PldmBuffer::read(u_int8_t *arr, size_t arr_size) {
    memcpy(arr, m_buff + m_pos, arr_size);
    m_pos += arr_size;
}

int PldmBuffer::seek(long offset, int whence) {
    long new_pos = -1;

    switch(whence) {
    case SEEK_SET:
        new_pos = offset;
        break;
    case SEEK_CUR:
        new_pos = m_pos + offset;
        break;
    case SEEK_END:
        new_pos = m_size + offset;
        break;
    }

    if(new_pos < 0 || new_pos > m_size) {
        return -1;
    }
    m_pos = new_pos;
    return 0;
}

long PldmBuffer::tell() {
    return m_pos;
}

