/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) June 2011, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
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
