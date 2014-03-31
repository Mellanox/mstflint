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

#ifndef BIT_SLICE_H
#define BIT_SLICE_H

// BIT Slicing macros
#define ONES32(size)                    ((size)?(0xffffffff>>(32-(size))):0)
#define MASK32(offset,size)             (ONES32(size)<<(offset))

#define EXTRACT_C(source,offset,size)   ((((unsigned)(source))>>(offset)) & ONES32(size))
#define EXTRACT(src,start,len)          (((len)==32)?(src):EXTRACT_C(src,start,len))
#define EXT(src,end,start)              EXTRACT(src,start,end-start+1)

#define MERGE_C(rsrc1,rsrc2,start,len)  ((((rsrc2)<<(start)) & (MASK32((start),(len)))) | ((rsrc1) & (~MASK32((start),(len)))))
#define MERGE(rsrc1,rsrc2,start,len)    (((len)==32)?(rsrc2):MERGE_C(rsrc1,rsrc2,start,len))
#define INSERTF(src1, start1, src2, start2, len) MERGE((src1), EXTRACT((src2), (start2), (len)), (start1), (len))

#define ONES64(size)                    ((size)?(0xffffffffffffffffULL>>(64-(size))):0)
#define MASK64(offset,size)             (ONES64(size)<<(offset))

#define EXTRACT_C64(source,offset,size)   ((((unsigned long long)(source))>>(offset)) & ONES64(size))
#define EXTRACT64(src,start,len)          (((len)==64)?(src):EXTRACT_C64(src,start,len))

#define MERGE_C64(rsrc1,rsrc2,start,len)  ((((u_int64_t)(rsrc2)<<(start)) & (MASK64((start),(len)))) | ((rsrc1) & (~MASK64((start),(len)))))
#define MERGE64(rsrc1,rsrc2,start,len)    (((len)==64)?(rsrc2):MERGE_C64(rsrc1,rsrc2,start,len))
#define INSERTF64(src1, start1, src2, start2, len) MERGE64((src1), EXTRACT64((src2), (start2), (len)), (start1), (len))
#define EXT64(src,end,start)              EXTRACT64(src,start,end-start+1)

#ifndef __cplusplus
enum cpp_bool {false=0,true};
typedef unsigned char bool;
#endif

#endif
