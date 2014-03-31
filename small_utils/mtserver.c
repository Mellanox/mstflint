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
 *  mtserver.c - Mellanox Software tools (mst) server (remote mtcr calls)
 *
 *  The buffers foramt:
 *
 *  Send buff: The buffer which send by the client side.
 *  Rcv  buff: The buffer which send by the server side.
 *  Mopen:
 *       Send buff:  O   Dtype       DevName
 *                   O   0x00000001  O  0x00000001  /dev/mst/mt25418_pci_cr0
 *       Rcv buff:   O
 *
 *  Mclose:
 *       Send buff:  C
 *       Rcv  buff:  O
 *
 *  Mdevices:
 *       Send buff:  L
 *       Rcv  buff:  O   DevsNum
 *                   [List of devices]
 *                   O   4
 *                  /dev/mst/mtusb-1
 *                  /dev/mst/mt25418_pciconf0
 *                  /dev/mst/mt25418_pci_uar0
 *                  /dev/mst/mt25418_pci_cr0
 *
 *  Mread4:
 *       Send buff:  R   Offset
 *                   R   0x000f0014
 *       Rcv  buff:  O   Value
 *                   O   0x00a00190
 *
 *  Mwrite4:
 *       Send buff:  W   Offset      Value
 *                   W   0x000f0018  0x12345678
 *       Rcv  buff:  O
 *
 *
 *  Mread64:
 *       Send buff:  r   AddrWidth   SlaveAddr  Size  Offeset
 *                   r   0           0x77       0x1   0x0
 *       Rcv  buff:  O   Size        data
 *                   O   0x1         00
 *
 *  Mwrite64:
 *       Send buff:  r   AddrWidth   SlaveAddr  Size  Offeset  data
 *                   r   0           0x77       0x1   0x0      00
 *       Rcv  buff:  O
 *
 *  Version:
 *       Send buff:  V
 *       Rcv  buff:  O   Version
 *                   O   1.1
 *
 *  Mi2c_detect:
 *       Send buff:  S
 *       Rcv  buff:  S   [SlaveAdrr]  ...  [SlaveAdrr]
 *                   O   0x70 0x48
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include "mtcr.h"
#include "tcp.h"

/*
 * Constants
 */
#define DEF_PORT 23108
#define BUF_LEN  256
#define DEV_LEN  2048

int sdebug = 0;
int port = DEF_PORT;    /* Default port */

#ifndef __WIN__
    #define PREP_SIGNAL(signal_handler) signal(SIGPIPE, signal_handler);
    #define WIN_INIT()
    #define WIN_CLOSE(mf, cmd)
    #define WIN_WHILE()
#else
    #include <Winsock2.h>
    #define PREP_SIGNAL(signal_handler)
    #define WIN_INIT() {                          \
        int rc;                                   \
        WSADATA wsaData;                          \
        rc = WSAStartup(MAKEWORD(2, 2), &wsaData);\
        if (rc != 0) {                            \
            printf("-E- Winsock initialization failed (WSAStartup returned %d\n", rc);\
            exit(1);                            \
        }                                         \
    }
    #define WIN_CLOSE(mf, cmd) {\
         if (!mf && cmd != 'V') {\
             break;\
         }\
    }

    #define WIN_WHILE() while (1)
#endif

#ifdef SIMULATOR

    #include <sys/mman.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>

    #define FILE_PATH "/tmp/mmap.log"
    #define NUM_INTS  (0x40000)
    #define FILE_SIZE (NUM_INTS * sizeof(int))

u_int32_t* cr_space;
char sim_str[100] = "\t-i[d]  <id>   - set the device id.\n";
int id;
int fd;
mfile *mopen(const char *name)
{
    name = NULL;
    return(mfile*)0;

}


mfile *mopend(const char *name, DType dtype)
{
    name  = NULL;
    dtype = 0;
    return(mfile*)1;
}

int mclose(mfile *mf)
{
    mf = NULL;
    return 0;
}

int mdevices(char *buf, int len, int mask)
{
    len  = 0;
    mask = 0;
    strcpy(buf, "Simulator");
    return 1;
}

int mread4(mfile *mf, unsigned int offset, u_int32_t *value)
{
    mf     = NULL;
    *value = cr_space[offset/4];
    return 4;
}

int mwrite4(mfile *mf, unsigned int offset, u_int32_t value)
{
    mf = NULL;
    cr_space[offset/4] = value;
    return 4;
}
int mi2c_detect (mfile *mf, u_int8_t slv_arr[SLV_ADDRS_NUM])
{
    mf      = NULL;
    slv_arr = NULL;
    return 1;
}
int mread_i2cblock(mfile *mf, unsigned char i2c_slave, u_int8_t addr_width,
                            unsigned int offset, void *data, int length)
{
    mf         = NULL;
    i2c_slave  = 1;
    addr_width = 1;
    offset     = 1;
    data       = NULL;
    length     = 1;
    return 0;
}

int mwrite_i2cblock(mfile *mf, unsigned char i2c_slave, u_int8_t addr_width,
                    unsigned int offset, void *data, int length)
{
    mf         = NULL;
    i2c_slave  = 1;
    addr_width = 1;
    offset     = 1;
    data       = NULL;
    length     = 1;
    return 0;
}

int mwrite4_block(mfile *mf, unsigned int offset, u_int32_t* data, int byte_len);


int check_id_arg(char* av[], int ac, int *i)
{
    char *end;
    if (++(*i) >= ac) {
        printf("After switch \"%s\" device id is expected.\n", av[--(*i)]);
        printf("Type \"%s -h\" for help.\n", av[0]);
        exit(1);
    }
    id = (int)strtol(av[*i], &end, 0);
    if (*end) {
        printf("Invalid id: \"%s\" -- ?\n", end);
        printf("Type \"%s -h\" for help.\n", av[0]);
        exit(1);
    }
    return 0;

}

int prepare_the_map_file(void)
{
    int i;
    int result;
    fd = open(FILE_PATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);

    if (fd == -1) {
        printf("-E- Error opening file for writing");
        exit(1);
    }

    result = lseek(fd, FILE_SIZE-1, SEEK_SET);
    if (result == -1) {
        close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(1);
    }

    result = write(fd, "", 1);
    if (result != 1) {
        close(fd);
        perror("Error writing last byte of the file");
        exit(1);
    }

    cr_space = mmap(0, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (cr_space == MAP_FAILED) {
        close(fd);
        perror("Error mmapping the file");
        exit(1);
    }
    for (i = 0; i < NUM_INTS; ++i) {
        cr_space[i] = 0;
    }

    // write id
    if (id != 0) {
        cr_space[0xf0014/4] = id;
    }
    return 0;
}

int unmap_and_close_file(void)
{
    if (munmap(cr_space, FILE_SIZE) == -1) {
        perror("Error un-mmapping the file");
    }
    close(fd);
    return 0;
}
#else

char sim_str[100] = "";
int check_id_arg(char* av[], int ac, int *i)
{
    ac = 0;
    printf("Invalid switch \"%s\".\n", av[*i]);
    printf("Type \"%s -h\" for help.\n", av[0]);
    exit(1);

}

int prepare_the_map_file(void)
{
    return 0;
}

int unmap_and_close_file(void)
{
    return 0;

}
#endif
/* ////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////// */
void usage(const char *s)
{
    printf("Usage:\n\t%s [switches]\n\n", s);
    printf("Switches may be:\n");
    printf("\t-p[ort] <port> - Listen to specify port (default is %d).\n", port);
    printf("\t-d[ebug]       - Print all socket traffic (for debuging only).\n");
    printf("%s", sim_str);
    printf("\t-h[elp]        - Print help message.\n");
    exit (1);
}

/* ////////////////////////////////////////////////////////////////////// */
static void writes_deb(int con, char *s)
{
    writes(con, s);
    if (sdebug)
        printf("-> %s\n", s);
}

/* ////////////////////////////////////////////////////////////////////// */
void write_err(int con)
{
    writen(con, "E ", 2);
    writes(con, strerror(errno));
    if (sdebug)
        printf("-> E %s\n", strerror(errno));
}

/* ////////////////////////////////////////////////////////////////////// */
void write_ok(int con)
{
    writes_deb(con, "O");
}

/* ////////////////////////////////////////////////////////////////////// */
void mySignal()
{
    exit(0);
}

#define GET_PARAM(param, str, type, param_name, err_msg) {\
    char* end;\
    param = (type)strtoul(str, &end, 0);\
    if (*end) {\
        sprintf(err_msg, "E Invalid %s", param_name);\
        return 1;\
    }\
}




int parse_i2c_cmd(char* buf, u_int8_t* addr_width, u_int8_t* slave_addr, int* size,
                  unsigned int* offset, u_int8_t* data, char* err_msg)
{
    char* p_arr[5];
    u_int8_t args_num;
    int i;

    if (*buf == 'r') {
        args_num = 4;
    } else {
        args_num = 5;
    }

    p_arr[0]  = buf + 2;
    for (i = 1; i <= args_num; i++) {
        p_arr[i] = strchr(p_arr[i - 1], ' ');
        if (p_arr[i] == NULL) {
            break;
        }
        *(p_arr[i]) = '\0';
        p_arr[i]++;
    }

    if (i < args_num) {
        sprintf(err_msg, "E Bad msg internal error");
        return 1;
    }
    GET_PARAM(*addr_width, p_arr[0], u_int8_t, "address width", err_msg);
    GET_PARAM(*slave_addr, p_arr[1], u_int8_t, "slave address", err_msg);
    GET_PARAM(*size,       p_arr[2], u_int8_t, "length", err_msg);
    GET_PARAM(*offset,     p_arr[3], u_int8_t, "offset", err_msg);

    if (args_num == 5) {
        char* p = p_arr[4];

        if (*size > 64) {
            sprintf(err_msg, "E Bad size which should be less than 64");
            return 1;
        }
        if ((*size * 2) != (int)strlen(p)) {
            sprintf(err_msg, "E Bad data section");
            return 1;
        }
        for (i = 0; i < *size; i++) {
            char tmp_num[10];
            // TODO: use 16 on the  strtoul
            strncpy(tmp_num, "0x", 2);
            strncpy(tmp_num + 2, p, 2);
            tmp_num[4] = '\0';
            ((u_int8_t*)data)[i] = (u_int8_t)strtoul(tmp_num, 0 , 0);
            p += 2;
        }
    }

    return 0;
}

int copy_buff_to_str(char* str, u_int8_t* data, int size)
{
    char* p = str;
    int i;
    for (i = 0; i < size; i++) {
        sprintf(p, "%02x", data[i]);
        p += 2;
    }
    return 0;
}

/* ////////////////////////////////////////////////////////////////////// */
#define CHK(f)    do { if ((f) < 0) { perror(""); exit(1); } } while(0)
#define CHK2(f,m) do { if ((f) < 0) { perror(m); exit(1); } } while(0)
#define MSTSERVER_VERSION "1.1"
int main (int ac, char *av[])
{
    char *end;
    char* local_dev = NULL;
	char  buf[BUF_LEN], dev_buf[DEV_LEN];
    int   i, con, rc;
    mfile *mf = 0;

    /* Command line parsing. */
    for (i=1; i<ac; i++) {
        switch (*av[i]) {
        case '-':
            ++av[i];
            if (!strcmp(av[i], "p")  ||  !strcmp(av[i], "port")) {
                if (++i >= ac) {
                    printf("After switch \"%s\" port number is expected.\n",av[--i]);
                    printf("Type \"%s -h\" for help.\n", av[0]);
                    exit(1);
                }
                port = (int)strtol(av[i], &end, 0);
                if (*end) {
                    printf("Invalid port: \"%s\" -- ?\n", end);
                    printf("Type \"%s -h\" for help.\n", av[0]);
                    exit(1);
                }
            } else if (!strcmp(av[i], "dev")) {
                if (++i >= ac)
                {
                    printf("After switch \"%s\" a device is expected.\n",av[--i]);
                    printf("Type \"%s -h\" for help.\n", av[0]);
                    exit(1);
                }
                local_dev = av[i];

            } else if (!strcmp(av[i], "d")  ||  !strcmp(av[i], "debug")) {
                sdebug = 1;
            } else if (!strcmp(av[i], "h")  ||  !strcmp(av[i], "help")) {
                usage(av[0]);
            } else if (!strcmp(av[i], "i")  ||  !strcmp(av[i], "id")) {
                check_id_arg(av, ac, &i);
            } else {
                printf("Invalid switch \"%s\".\n", av[i]);
                printf("Type \"%s -h\" for help.\n", av[0]);
                exit(1);
            }
            break;
        case '?':
            usage(av[0]);
            break;
        default:
            printf("Invalid parameter \"%s\".\n", av[i]);
            printf("Type \"%s -h\" for help.\n", av[0]);
            exit(1);
        }
    }

    prepare_the_map_file();
    PREP_SIGNAL(mySignal);
    WIN_INIT();

    /* Now open and start work */
    logset(1);
    WIN_WHILE() {
        con = open_serv_connection(port);
        CHK2(con, "Open connection (server side)");

        for (;;) {

            memset(buf, 0, BUF_LEN);
            rc = reads(con, buf, BUF_LEN);
            CHK(rc);
            if (!rc) {
                break;    /*  EOF */
            }
            if (sdebug) {
                printf("<- %s\n", buf);
            }
            switch (*buf) {
            case 'O':   /*  Open mfile */

                if (mf)
                    writes_deb(con, "E Already opened");
                else {
                    int dtype = strtoul (buf+2, &end, 0);
                    if (*end != ' ')  {
                        /*  Old style (O DEV_NAME) */
                        mf = mopen(buf+2);
                    } else {
                        /*  New style (O FLAG DEV_NAME) */
                        mf = mopend (end+1, dtype);
                    }

                    if (mf) {
                        write_ok(con);
                    } else {
                        write_err(con);
                    }
                }
                break;
            case 'C':  /*  Close mfile */
                if (!mf)
                    writes_deb(con, "E Not opened");
                else {
                    if (mclose(mf) < 0) {
                        write_err(con);
                    } else {
                        write_ok(con);
                        mf = 0;
                    }
                }
                break;
            case 'V':  /*  Get version */
                writes_deb(con, "O "MSTSERVER_VERSION);
                break;
#ifndef MST_UL				
            case 'S':  /*  Scan I2C bus */
                if (!mf)
                    writes_deb(con, "E Not opened");
                else {
                    u_int8_t slv_arr[SLV_ADDRS_NUM];
                    if (mi2c_detect(mf, slv_arr) < 0) {
                        write_err(con);
                    } else {
                        int i;
                        char *p, buf[1024];
                        sprintf(buf, "O");
                        p =  buf + 1;
                        for (i = 0; i < SLV_ADDRS_NUM; i++) {
                            if (slv_arr[i]) {
                                sprintf(p, " 0x%02x", i);
                                p += strlen(p);
                            }
                        }
                        writes_deb(con, buf);
                    }
                }
                break;
#endif				
            case 'L':   /*  Get devices list */
                if (local_dev == NULL) {
                    rc = mdevices(dev_buf, DEV_LEN, MDEVS_ALL);
				} else {

                    strcpy(dev_buf, "/dev/mst/mtREMOTE_pci_cr0");
                    printf("-D- local_dev=%s dev_buf=%s\n", local_dev, dev_buf);
                    rc = 1;
                }

                if (rc < 0)
                    write_err(con);
                else {
                    char *p = &dev_buf[0], vbuf[16];
                    sprintf(vbuf, "O %d", rc);
                    writes_deb(con, vbuf);
                    for (i = 0; i < rc; i++, p += strlen(p)+1) {
                        writes_deb(con, p);
                    }
                }
                break;
            case 'R':   /*  Read word */
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    unsigned int offset;
                    u_int32_t    value;
                    offset = strtoul(buf+2, &end, 0);
                    if (*end) {
                        writes_deb(con, "E Invalid offset");
                    } else {
                        if (mread4(mf, offset, &value) < 4) {
                            write_err(con);
                        } else {
                            char vbuf[16];
                            sprintf(vbuf, "O 0x%08x", value);
                            writes_deb(con, vbuf);
                        }
                    }
                }
                break;
#ifndef MST_UL
            case 'r':   /*  Read I2C */
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    u_int8_t data[64];
                    char err_msg[256];
                    u_int8_t addr_width, slave_addr;
                    unsigned int offset;
                    int  size;

                    rc = parse_i2c_cmd(buf, &addr_width, &slave_addr, &size, &offset, data, err_msg);
                    if (rc) {
                        writes_deb(con, err_msg);
                    } else {
                        if (mread_i2cblock(mf, slave_addr, addr_width, offset, data, size) < size) {
                            write_err(con);
                        } else {
                            char vbuff[256];
                            sprintf(vbuff, "O 0x%x ", size);
                            copy_buff_to_str(&vbuff[strlen(vbuff)], data, size);
                            writes_deb(con, vbuff);
                        }
                    }
                }
                break;
            case 'w':   /*  Read I2C */
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    u_int8_t data[64];
                    char err_msg[256];
                    u_int8_t addr_width, slave_addr;
                    unsigned int offset;
                    int  size;

                    rc = parse_i2c_cmd(buf, &addr_width, &slave_addr, &size, &offset, data, err_msg);
                    if (rc) {
                        writes_deb(con, err_msg);
                    } else {
                        if (mwrite_i2cblock(mf, slave_addr, addr_width, offset, data, size) < size) {
                            write_err(con);
                        } else {
                            write_ok(con);
                        }
                    }
                }
                break;
#endif
            case 'W':   /*  Write word */
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    unsigned int offset;
                    u_int32_t    value;
                    char *p = strchr(buf+2, ' ');
                    if (!p) {
                        writes_deb(con, "E Invalid format (should be OFFS DATA)");
                    } else {
                        *p = '\0';
                        p++;
                        offset = strtoul(buf+2, &end, 0);
                        if (*end) {
                            writes_deb(con, "E Invalid offset");
                        } else {
                            value = strtoul(p, &end, 0);
                            if (*end) {
                                writes_deb(con, "E Invalid data");
                            } else {
                                if (mwrite4(mf, offset, value) < 4)  {
                                    write_err(con);
                                } else {
                                    write_ok(con);
                                }
                            }
                        }
                    }
                }
                break;
            default:
                writes(con, "E Invalid command");
                if (sdebug)
                    printf("-> E Invalid command (len:%d cmd:\"%s\")\n",
                           (int)strlen(buf), buf);
                break;
            }
            WIN_CLOSE(mf, *buf);
        }
    }

    unmap_and_close_file();
    return 0;
}
