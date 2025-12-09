/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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
 * End of legal section ......................................................
*/


#ifndef TIME_COMPAT_H
#define TIME_COMPAT_H

#include <time.h>

#if defined(__WIN__)

    #include <windows.h>

#if !defined(__MINGW32__) && !defined(__MINGW64__)
    #include <winsock2.h>    // for struct timeval
    #define inline _inline
    //typedef struct timeval {
    //    long tv_sec;
    //    long tv_usec;
    //} timeval;
#endif
    
    static inline int gettimeofday(struct timeval *tp, void *tzp) {
        FILETIME ft;
        long long *time64 = (long long *) &ft;
    
        GetSystemTimeAsFileTime (&ft);
    
        /* Convert from 100s of nanoseconds since 1601-01-01
         * to Unix epoch. */
        *time64 -= 116444736000000000LL;
        *time64 /= 10;
    
        tp->tv_sec = (long)(*time64 / 1000000);
        tp->tv_usec = *time64 % 1000000;
        return 0;
    }

#else

    #include <sys/time.h>

#endif

#endif  // TIME_COMPAT_H
