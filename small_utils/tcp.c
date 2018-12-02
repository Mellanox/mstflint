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
 *  tcp.c - simple socket library routines
 *
 */

#ifndef INSIDE_MTCR
#define INSIDE_MTCR
#include "tcp.h"
#else
// HACK: We redefine it here also because when including from mtcr.c tcp.h is not included
typedef enum proto_type {
    PT_TCP = 0,
    PT_UDP,
} proto_type_t;
#endif


#include <errno.h>
#include <fcntl.h>
#include <memory.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UDP_RECV_FLAGS 0

#ifndef __WIN__
    #include <unistd.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/un.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/ioctl.h>
    #include <arpa/inet.h>

    #define SOCKET_BACKLOG           1
    #undef COMP_CLOSE
    #define COMP_CLOSE               close
    #define TCP_COMP_READ(s, b, l)         read(s, b, l)
    #define TCP_COMP_WRITE(s, b, l)        write(s, b, l)

    #define UDP_COMP_READ(s, b, l)         recv(s, b, l, UDP_RECV_FLAGS)
    #define UDP_COMP_WRITE(s, b, l)        send(s, b, l, UDP_RECV_FLAGS)

    #define GET_CHILD_PID(child_pid) child_pid = fork()
    #define EXEC_SIGNAL() if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {return -1;}
    #define EXEC_FOR() for (;;)
    #define RET_ZERO_IN_WIN()
    #define WIN_INIT()
#else
    #include <winsock2.h>
    #include <io.h>

    #define socklen_t int

    #define SOCKET_BACKLOG           5

#ifdef   COMP_CLOSE
    #undef  COMP_CLOSE
    #undef  COMP_READ
    #undef  COMP_WRITE
#endif
    #define COMP_CLOSE               closesocket

    #define TCP_COMP_READ(s, b, l)         recv(s, b, l, 0)
    #define TCP_COMP_WRITE(s, b, l)        send(s, b, l, 0)

    #define UDP_COMP_READ(s, b, l)         recv(s, b, l, UDP_RECV_FLAGS)
    #define UDP_COMP_WRITE(s, b, l)        send(s, b, l, UDP_RECV_FLAGS)


    #define GET_CHILD_PID(child_pid) child_pid = 0
    #define EXEC_SIGNAL()
    #define EXEC_FOR()
    #define RET_ZERO_IN_WIN()         return 0

    #define WIN_INIT() {                          \
        int rc;                                   \
        WSADATA wsaData;                          \
        rc = WSAStartup(MAKEWORD(2, 2), &wsaData); \
        if (rc != 0) {                            \
            return -1;                            \
        }                                         \
}
#endif

#undef  COMP_READ

#define COMP_ACCESS(s, b, l, p, f1, f2) (p == PT_UDP) ? f1(s, b, l) : f2(s, b, l);

#define COMP_READ(s, b, l, p) COMP_ACCESS(s, b, l, p, UDP_COMP_READ, TCP_COMP_READ)

#define COMP_WRITE(s, b, l, p) COMP_ACCESS(s, b, l, p, UDP_COMP_WRITE, TCP_COMP_WRITE)


#define EXEC_PROTO_FUNC(proto, tcp_func, udp_func, args) { \
        if (proto == PT_UDP) { \
            return udp_func args; \
        } \
        return tcp_func args; \
}


/* ----------------------------------------------------- */
/* ------------------------------ Log all socket traffic */
/* ----------------------------------------------------- */
/* ////////////////////////////////////////////////////////////////////// */
static int log_ena = 0;
INSIDE_MTCR void logset(const int ena) { log_ena = ena;}
INSIDE_MTCR int  plog(const char *fmt, ...)
{
    va_list ap;
    int rc = 0;

    if (log_ena) {
        va_start(ap, fmt);
        rc = vprintf(fmt, ap);
        va_end(ap);
    }
    return rc;
}

/* --------------------------------------------------- */
/* ------------------------------ Base socket routines */
/* --------------------------------------------------- */

/* ////////////////////////////////////////////////////////////////////// */
/*
** readn - read n bytes from the socket "fd"
**
** Attempt to read "nbytes" bytes from socket "fd" into "ptr".
** Returns number of bytes read, or -1 if an error occurs.
** Will read less than the specified count *only* if the peer sends
** EOF
*/
/*
   INSIDE_MTCR int readn(int fd, void *vptr, int nbytes, proto_type_t proto)
   {
    int     nleft, nread;
    char    *ptr = (char *)vptr;
    nleft = nbytes;
    while (nleft > 0) {
        do {
            nread = COMP_READ(fd, ptr, nleft, proto);
        }
        while (nread < 0 && errno == EINTR);

        if (nread < 0)
            return -1;              // error, return -1
        else if (nread == 0)
            break;                  //  EOF

        nleft -= nread;
        ptr   += nread;
    }
    return(nbytes - nleft);         //  return >= 0
   }
 */

INSIDE_MTCR int tcp_reads(int fd, char *ptr, int maxlen)
{
    int n, done = 0, rc;
    char c;
    for (n = 0; (n < maxlen - 1) && !done; n++) {
        do {
            rc = COMP_READ(fd, &c, 1, PT_TCP);
        }
        while (rc < 0 && errno == EINTR);

        switch (rc) {
        case 1:
            *ptr++ = c;
            if (c == '\0') {
                done = 1;
            }
            break;

        case 0:
            done = 1;
            break;

        default:
            return -1;     /*  error */
        }
    }
    *ptr = '\0';
    return n - 1;
}

INSIDE_MTCR int udp_reads(int fd, char *ptr, int maxlen)
{
    int rc = 0;
    char *tmp_ptr = ptr;
    do {
        rc = COMP_READ(fd, tmp_ptr, maxlen - 1, PT_UDP);
    } while (rc < 0 && errno == EINTR);
    if (rc > 0) {
        tmp_ptr[rc] = '\0';
    } else {
        *tmp_ptr = '\0';
    }
    return rc - 1;
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** reads - reads string (till \0)  from the socket "fd"
*/
INSIDE_MTCR int reads(int fd, char *ptr, int maxlen, proto_type_t proto)
{
    if (proto == PT_UDP) {
        return udp_reads(fd, ptr, maxlen);
    }
    return tcp_reads(fd, ptr, maxlen);
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** readnl - reads till till newline  from the socket "fd"
*/
/*
   INSIDE_MTCR int readnl(int fd, char *ptr, int maxlen, proto_type_t proto)
   {
    int     n, done=0, rc;
    char    c;
    for (n = 0; n <= maxlen-1 && !done; n++) {
        do {
            rc = COMP_READ(fd, &c, 1, proto);
        }
        while (rc < 0 && errno == EINTR);

        switch (rc) {
        case 1:
 * ptr++ = c;
            if (c == '\n') {
 * ptr = '\0';
                done=1;
            }
            break;
        case 0:
            done=1;
            break;
        default:
            return -1;     //  error
        }
    }
    return n-1;
   }
 */

/* ////////////////////////////////////////////////////////////////////// */
/*
** writen - write n bytes to the socket "fd"
**
** Attempt to write "nbytes" bytes to socket "fd" from "ptr".
** Returns number of bytes written, or -1 if an error occurs.
** Return value will always be either -1 or "nbytes"
*/
INSIDE_MTCR int writen(int fd, void *vptr, int nbytes, proto_type_t proto)
{
    int nleft, nwritten;
    char    *ptr = (char*)vptr;

    nleft = nbytes;
    while (nleft > 0) {
        do {
            nwritten = COMP_WRITE(fd, ptr, nleft, proto);
        } while (nwritten < 0 && errno == EINTR);

        if (nwritten < 0) {
            return -1;
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }
    return(nbytes - nleft);
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** writes - write string (null ternminated buffer) to the socket "fd"
*/
INSIDE_MTCR int writes(int fd, char *ptr, proto_type_t proto)
{
    return writen(fd, ptr, strlen(ptr) + 1, proto);
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** writenl - write newline ternminated buffer to the socket "fd"
*/
/*
   INSIDE_MTCR int writenl(int fd, char *ptr, proto_type_t proto)
   {
    char *last = strchr(ptr, '\n');
    if (last)
        return writen(fd, ptr, last - ptr + 1, proto);
    return 0;
   }
 */

/* ////////////////////////////////////////////////////////////////////// */
/*
** open_cli_connection - open client TCP connection and return socket fd
*/
INSIDE_MTCR int open_cli_connection(const char *host, const int port, proto_type_t proto)
{
    int SockFD;
    struct sockaddr_in serv_addr;
    struct hostent      *hent;
    int needs_bind = 0;
    int type = SOCK_STREAM, domain = AF_INET;

    if (proto == PT_UDP) {
        needs_bind = 1;
        type = SOCK_DGRAM;
        domain = PF_INET;
    }

    plog("open_connection(%s, %d)\n", host, port);

    //Initialize Winsock
    WIN_INIT();

    /*  Try to determinate server IP address */
    if ((hent = gethostbyname(host)) == NULL) {
        errno = EINVAL;
        return -1;
    }

    /*
     * Fill in the structure "serv_addr" with the address of the
     * server that we want to connect with.
     */
    memset((char*) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    memcpy(&serv_addr.sin_addr, (*(hent->h_addr_list)), sizeof(struct in_addr));
    serv_addr.sin_port        = (short)htons((short)port);

    /*  Open a TCP socket (an Internet stream socket). */
    if ( (SockFD = socket(domain, type, 0)) < 0) {
        return -1;
    }


    if (needs_bind) {
        struct sockaddr_in my_addr;
        /*  Bind our local address so that the client can send to us. */
        memset((char*) &my_addr, 0, sizeof(my_addr));
        my_addr.sin_family      = AF_INET;
        my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        my_addr.sin_port        = (short)(htons((short)port));

        /*  Bind our local address so that the client can send to us. */
        if (bind(SockFD, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
            COMP_CLOSE(SockFD);
            perror("bind failed\n");
            return -1;
        }
    }

    /*
     * Connect to the server.
     */
    if (connect(SockFD, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        COMP_CLOSE(SockFD);
        return -1;
    }

    /*  All OK */
    return SockFD;
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** open_serv_connection - open server TCP connection and return socket fd
*/
INSIDE_MTCR int open_serv_connection(const int port)
{
    struct hostent     *hent;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_inet_addr;
    int SockFD, newsockfd;
    int clilen = sizeof(cli_inet_addr);
    int childpid;

    EXEC_SIGNAL()

    if ((SockFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    /*  Bind our local address so that the client can send to us. */
    memset((char*) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = (short)(htons((short)port));
    if (bind(SockFD, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        #ifdef __WIN__
        errno = WSAGetLastError();
        #endif
        COMP_CLOSE(SockFD);
        return -1;
    }

    /*  Get ready to accept connection */
    if (listen(SockFD, SOCKET_BACKLOG) < 0) {
        COMP_CLOSE(SockFD);
        return -1;
    }

    /*  Accept connection */
    EXEC_FOR()
    {
        plog("Waiting for connection on port %d\n", port);

        while ((newsockfd = accept(SockFD, (struct sockaddr*)&cli_inet_addr,
                                   (socklen_t*)&clilen)) < 0) {
            if (errno != EINTR) {
                COMP_CLOSE(SockFD);
                return -1;
            }
        }

        GET_CHILD_PID(childpid);

        if (childpid < 0) {
            COMP_CLOSE(newsockfd);
            COMP_CLOSE(SockFD);
            return -1;
        }
        if (childpid) {
            /*  We are parent */
            COMP_CLOSE(newsockfd);
            RET_ZERO_IN_WIN();
            /*   ... and try accept next connection */
        } else {
            /*  We are child */
            COMP_CLOSE(SockFD);

            /*  Determine the client host name */
            hent = gethostbyaddr((char*)&cli_inet_addr.sin_addr,
                                 sizeof(cli_inet_addr.sin_addr), AF_INET);
            plog("Accepted connection from host \"%s\" ",
                 hent ? hent->h_name : "????");

            /*  Determine the client host address */
            plog(" (%s)", inet_ntoa(cli_inet_addr.sin_addr));

            plog(", port %d\n", port);
            return newsockfd;
        }
    }

}

