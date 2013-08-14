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

/*
 *
 *  tcp.h - simple socket library definitions
 *
 */

#ifndef _MST_SOCKETS_H
#define _MST_SOCKETS_H

#ifndef __WIN__
    #define ATTRIBUTE  __attribute__ ((format (printf, 1, 2)))
#else
    #define ATTRIBUTE
#endif


/*
** logset - call it w/ non-zero to see output via log.
**          Otherwise all log calls will be ignored
*/
void logset(const int ena);

/*
** plog - debug printouts (like printf). Set 1 via logset to see output
*/
int plog(const char *fmt, ...) ATTRIBUTE;

/*
** open_cli_connection - open client TCP connection and return socket fd
*/
int open_cli_connection(const char *host, const int port);

/*
** open_serv_connection - open server TCP connection and return socket fd
*/
int open_serv_connection(const int port);

/*
** readn - read n bytes from the socket "fd"
**
** Attempt to read "nbytes" bytes from socket "fd" into "ptr".
** Returns number of bytes read, or -1 if an error occurs.
** Will read less than the specified count *only* if the peer sends
** EOF
*/
int readn(int fd, void *vptr, int nbytes);

/*
** reads - reads string (till \0)  from the socket "fd"
*/
int reads(int fd, char *ptr, int maxlen);

/*
** readnl - reads till till newline  from the socket "fd"
*/
int readnl(int fd, char *ptr, int maxlen);

/*
** writen - write n bytes to the socket "fd"
**
** Attempt to write "nbytes" bytes to socket "fd" from "ptr".
** Returns number of bytes written, or -1 if an error occurs.
** Return value will always be either -1 or "nbytes"
*/
int writen(int fd, void *vptr, int nbytes);

/*
** writes - write string (null ternminated buffer) to the socket "fd"
*/
int writes(int fd, char *ptr);

/*
** writenl - write newline ternminated buffer to the socket "fd"
*/
int writenl(int fd, char *ptr);

#endif
