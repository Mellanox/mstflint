/*
 *
 * Copyright (c) 2011 Mellanox Technologies Ltd.  All rights reserved.
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
//
// Generic version for all tools
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gitversion.h"

#ifndef TOOLS_SVN_VER
    #define TOOLS_SVN_VER "N/A"
#endif

#ifndef MFT_VERSION_STR
    #define MFT_VERSION_STR "mft 3.0.0"
#endif

static inline
int get_version_string(char* buf, int buf_size, const char* exe_name, const char* tool_version) {
    int len = 0;
    // "svn ci" updates the below line

    (void)buf_size; /* TODO: Not checked for now */


    if (tool_version == NULL || !strcmp(tool_version, "")) {
        len = sprintf(buf, "%s, ", exe_name);
    } else {
        len = sprintf(buf, "%s %s, ", exe_name, tool_version);
    }
    // cut out first and last "$" from the SVN version string:
    len += sprintf(buf + len, "%s, built on %s, %s. GIT Version: %s",
                  MFT_VERSION_STR,
                  __DATE__,
                  __TIME__,
                  TOOLS_SVN_VER);
    return len;
}

static inline
void print_version_string(const char* exe_name, const char* tool_version) {
    char buf[1024];
    get_version_string(buf, sizeof(buf), exe_name, tool_version);
    printf("%s\n", buf);
}
