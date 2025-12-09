/*
 * Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef IBD_DEVICE
#define IBD_DEVICE

enum devid {
    DI_CX =     0xa00190,
    DI_CX2 =    0xb00190,
    DI_CX3 =    0x0001f5,
    DI_CX3A1 =  0x0101f5,
    DI_CX3Pro = 0x0001f7,
    DI_CIB =    0x0001ff,
    DI_CX4 =    0x000209,
    DI_CX4LX =  0x00020b,
    DI_CX5 =    0x00020d,
    DI_CX6 =    0x00020f,
    DI_CX6DX =  0x000212,
    DI_BF2 =    0x000214,
    DI_BF2A1 =  0x010214,
    DI_BF3 =    0x00021c,
    DI_BF4 =    0x000220,
    DI_CX7 =    0x000218,
    DI_CX8 =    0x00021e,
    DI_CX9 =    0x000224,
};

#endif
