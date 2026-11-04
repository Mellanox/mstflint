/*
 *
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *  mtcr_ul_deprecation.c - the link-time deprecation notice of libmtcr_ul.a
 *
 */

/*
 * GNU ld prints the contents of a .gnu.warning section as a warning whenever an
 * object that contains one is linked in. This object is not part of
 * libmtcr_ul.a: it is the only member of libmtcr_ul_deprecation.a, installed
 * next to it and named only in the installed $(libdir)/libmtcr_ul.a linker
 * script (see install-exec-hook in Makefile.am). That script also declares
 * EXTERN(mtcr_ul_deprecation_notice), so every program linked with -lmtcr_ul
 * pulls this object in, and prints the notice, once, however often -lmtcr_ul
 * appears on its command line. mstflint's own tools, the Python bindings and the
 * SDK link libmtcr_ul.a in the build tree and do not print it.
 * The notice is GNU/Linux only, as in MFT. The symbol is hidden, so programs and
 * libraries that link it never export it.
 */
#ifdef __gnu_linux__
__asm__(".section .gnu.warning,\"\",%progbits\n\t"
        ".string \"The deprecation of libmtcr_ul.a will be announced after mstflint 4.39.0. "
        "Users are encouraged to migrate to the mstflint SDK, libmstflint_sdk.so (pkg-config: mstflint_sdk). "
        "Upcoming mstflint release notes will document the SDK APIs that replace those provided by "
        "libmtcr_ul.a.\"\n\t"
        ".previous");
#endif
__asm__(".globl mtcr_ul_deprecation_notice\n\t"
        ".hidden mtcr_ul_deprecation_notice\n\t"
        ".set mtcr_ul_deprecation_notice, 0");
