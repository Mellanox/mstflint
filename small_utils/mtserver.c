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
 *                   O   0x00000001 /dev/mst/mt25418_pci_cr0
 *       Send buff(W/O Dtype, deprecated):  O   DevName
 *                                          O   /dev/mst/mt25418_pci_cr0
 *       Rcv buff:   O   VSEC_SUPP
 *                   O   1
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
 *       Send buff:  r   AddrWidth   SlaveAddr  Size  Offset
 *                   r   0           0x77       0x1   0x0
 *       Rcv  buff:  O   Size        data
 *                   O   0x1         00
 *
 *  Mwrite64:
 *       Send buff:  r   AddrWidth   SlaveAddr  Size  Offset  data
 *                   r   0           0x77       0x1   0x0      00
 *       Rcv  buff:  O
 *
 *  Mread4Block:
 *       Send buff:  B  Offset size[bytes]
 *                   B  0      0x100 (maximum size is 512 bytes)
 *       Rcv buff:   O   dword1 dword2 ... dwordN
 *
 * Mwrite4Block:
 *       Send buff:  U  Offset size[bytes] dowrd1 dword2 ... dwordN
 *                   U  0 0x100 (maximum size is 512 bytes)
 *       Rcv buff:   O
 *
 *  Version:
 *       Send buff:  V
 *       Rcv  buff:  O   Version
 *                   O   1.4
 *
 *  Mi2c_detect:
 *       Send buff:  S
 *       Rcv  buff:  S   [SlaveAdrr]  ...  [SlaveAdrr]
 *                   O   0x70 0x48
 *
 *  Mpci_change:
 *       Send buff:  P
 *       Rcv  buff:  O
 *
 *  Mset_addr_space:
 *       Send buff:  A   <AddressSpace>
 *       Rcv  buff:  O
 */

#ifndef __WIN__
    #define PREP_SIGNAL(signal_handler) signal(SIGPIPE, signal_handler);
    #define WIN_INIT()
    #define WIN_CLOSE(mf, cmd)
    #define WIN_WHILE()
#else
    #include <winsock2.h>
    #define PREP_SIGNAL(signal_handler)
    #define WIN_INIT() {                          \
        int rc;                                   \
        WSADATA wsaData;                          \
        rc = WSAStartup(MAKEWORD(2, 2), &wsaData); \
        if (rc != 0) {                            \
            printf("-E- Winsock initialization failed (WSAStartup returned %d\n", rc); \
            exit(1);                            \
        }                                         \
}
    #define WIN_CLOSE(mf, cmd) { \
        if (!mf && cmd != 'V') { \
            break; \
        } \
}

    #define WIN_WHILE() while (1)
#endif

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <compatibility.h>

#include "mtcr.h"
#include "tcp.h"
#include "tools_version.h"
#include "common/tools_utils.h"

/*
 * Constants
 */
#define DEF_PORT    23108
#define MAX_DWORDS  128
#define BUF_LEN  (MAX_DWORDS * 4 * 3)
#define DEV_LEN  2048


int sdebug = 0;
int port = DEF_PORT;    /* Default port */


/* ////////////////////////////////////////////////////////////////////// */
static void writes_deb(int con, char *s)
{
    writes(con, s, PT_TCP);
    if (sdebug) {
        printf("-> %s\n", s);
    }
}

/* ////////////////////////////////////////////////////////////////////// */
void write_err(int con)
{
    writen(con, "E ", 2, PT_TCP);
    writes(con, strerror(errno), PT_TCP);
    if (sdebug) {
        printf("-> E %s\n", strerror(errno));
    }
}

/* ////////////////////////////////////////////////////////////////////// */
void write_ok(int con)
{
    writes_deb(con, "O");
}


// On windows we don't have simulator in the meantime!
#if defined(SIMULATOR) && !defined(__WIN__)

    #include <sys/mman.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>

    #define FILE_PATH "/tmp/mmap.log"
    #define NUM_INTS  (0x200000)
    #define FILE_SIZE (NUM_INTS * sizeof(int))

u_int32_t *cr_space;
char sim_str[] = "\t-i[d]   <id>   - set the device id.\n"
                 "\t-f[ile] <file> - load cr-space snapshot from dump file.\n";
int id;
char *dump_file = NULL;
int fd;
mfile* mopen(const char *name)
{
    TOOLS_UNUSED(name);
    return (mfile*)0;

}


mfile* mopend(const char *name, DType dtype)
{
    TOOLS_UNUSED(name);
    TOOLS_UNUSED(dtype);
    return (mfile*)1;
}

int mclose(mfile *mf)
{
    TOOLS_UNUSED(mf);
    return 0;
}

int mdevices(char *buf, int len, int mask)
{
    TOOLS_UNUSED(len);
    TOOLS_UNUSED(mask);
    strcpy(buf, "Simulator");
    return 1;
}

int mread4(mfile *mf, unsigned int offset, u_int32_t *value)
{
    TOOLS_UNUSED(mf);
    *value = __be32_to_cpu(cr_space[offset / 4]);
    return 4;
}

int mwrite4(mfile *mf, unsigned int offset, u_int32_t value)
{
    TOOLS_UNUSED(mf);
    cr_space[offset / 4] = __cpu_to_be32(value);
    //cr_space[offset/4] = value;
    return 4;
}
int mi2c_detect(mfile *mf, u_int8_t slv_arr[SLV_ADDRS_NUM])
{
    TOOLS_UNUSED(mf);
    TOOLS_UNUSED(slv_arr);
    return -1;
}
int mread_i2cblock(mfile *mf, unsigned char i2c_slave, u_int8_t addr_width,
                   unsigned int offset, void *data, int length)
{
    TOOLS_UNUSED(mf);
    TOOLS_UNUSED(i2c_slave);
    TOOLS_UNUSED(addr_width);
    TOOLS_UNUSED(offset);
    TOOLS_UNUSED(data);
    TOOLS_UNUSED(length);
    return 0;
}

int mwrite_i2cblock(mfile *mf, unsigned char i2c_slave, u_int8_t addr_width,
                    unsigned int offset, void *data, int length)
{
    TOOLS_UNUSED(mf);
    TOOLS_UNUSED(i2c_slave);
    TOOLS_UNUSED(addr_width);
    TOOLS_UNUSED(offset);
    TOOLS_UNUSED(data);
    TOOLS_UNUSED(length);
    return 0;
}

int mwrite4_block(mfile *mf, unsigned int offset, u_int32_t *data, int byte_len)
{
    int i;
    //printf("-D- inside mtserver\n");
    if (byte_len % 4) {
        return EINVAL;               // verify byte_len is multiplation of dword size
    }
    mf = NULL;
    for (i = 0; i < byte_len; i += 4) {
        mwrite4(mf, offset + i, *(data++));
    }
    return byte_len;
}

static void fix_endianness(u_int32_t *buf, int len)
{
    int i;

    for (i = 0; i < (len / 4); ++i) {
        //printf("-D- before: buf[%d] = %#x\n", i, buf[i]);
        buf[i] = __be32_to_cpu(buf[i]);
        //printf("-D- before: buf[%d] = %#x\n", i, buf[i]);
    }
}

int mwrite_buffer(mfile *mf, unsigned int offset, u_int8_t *data, int byte_len)
{
    //printf("-D- inside: mstsim:mwrite_buffer\n");
    fix_endianness((u_int32_t*)data, byte_len);
    return mwrite4_block(mf, offset, (u_int32_t*)data, byte_len);
}


int mread4_block(mfile *mf, unsigned int offset, u_int32_t *data, int byte_len)
{
    int i;
    if (byte_len % 4) {
        return EINVAL;               // verify byte_len is multiplation of dword size
    }
    mf = NULL;
    for (i = 0; i < byte_len; i += 4) {
        mread4(mf, offset + i, data++);
    }
    return byte_len;
}

int check_id_arg(char *av[], int ac, int *i)
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

void check_file_arg(char *av[], int ac, int *i)
{
    if (++(*i) >= ac) {
        printf("After switch \"%s\" dump file is expected.\n", av[--(*i)]);
        printf("Type \"%s -h\" for help.\n", av[0]);
        exit(1);
    }
    dump_file = av[*i];
}

void load_dump_file()
{
    #define BUFSIZE 40
    char buf[BUFSIZE];
    int line;
    FILE *fh = fopen(dump_file, "r");

    if (!fh) {
        printf("-E- Error opening dump file for reading: %s\n", strerror(errno));
        exit(1);
    }

    for (line = 1;; ++line) {
        int address, value;

        if (!fgets(buf, BUFSIZE, fh)) {
            if (feof(fh)) {
                break;
            }
            fclose(fh);
            printf("-E- Error reading dump file: %s\n", strerror(errno));
            exit(1);
        }

        if (sscanf(buf, "%x %x", &address, &value) < 2) {
            fclose(fh);
            printf("-E- Error parsing dump file at line %d\n", line);
            exit(1);
        }

        mwrite4(NULL, address, value);
    }

    fclose(fh);
}

int prepare_the_map_file(void)
{
    int i;
    int result;
    fd = open(FILE_PATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);

    if (fd == -1) {
        printf("-E- Error opening file for writing\n");
        exit(1);
    }

    result = lseek(fd, FILE_SIZE - 1, SEEK_SET);
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

    // load cr-space snapshot
    if (dump_file) {
        load_dump_file();
    }

    // write id
    if (id != 0) {
        mwrite4(NULL, 0xf0014, id);
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
void mpci_change(mfile *mf)
{
    TOOLS_UNUSED(mf);
}

void get_devices_list(int con)
{
    char dev_buf[DEV_LEN];
    int i, rc;
    rc = mdevices(dev_buf, DEV_LEN, MDEVS_ALL);
    if (rc < 0) {
        write_err(con);
    } else {
        char *p = &dev_buf[0], vbuf[16];
        sprintf(vbuf, "O %d", rc);
        writes_deb(con, vbuf);
        for (i = 0; i < rc; i++, p += strlen(p) + 1) {
            writes_deb(con, p);
        }
    }

}
int mget_vsec_supp(mfile *mf)
{
    TOOLS_UNUSED(mf);
    return 0;
}
int mset_addr_space(mfile *mf, int space)
{
    TOOLS_UNUSED(mf);
    TOOLS_UNUSED(space);
    return 0;
}
#else
extern void mpci_change(mfile *mf);

#if defined(__linux__) && !defined(__VMKERNEL_UW_NATIVE__) && !defined(__VMKERNEL_UW_VMKLINUX__)
extern int check_ul_mode();
#endif

char sim_str[100] = "";
int check_id_arg(char *av[], int ac, int *i)
{
    (void)ac;
    printf("Invalid switch \"%s\".\n", av[*i]);
    printf("Type \"%s -h\" for help.\n", av[0]);
    exit(1);

}

void check_file_arg(char *av[], int ac, int *i)
{
    (void)ac;
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

void get_devices_list(int con)
{
#ifndef MST_UL
    dev_info *mdevs_inf = NULL;
    int devs_num = -1, i = 0;
    mdevs_inf = mdevices_info(MDEVS_ALL & ~MDEVS_CABLE, &devs_num);

    if (devs_num < 0 || !mdevs_inf) {
        write_err(con);
    } else {
        char vbuf[16];
        int n = devs_num;
        for (i = 0; i < devs_num; i++) {
            if (mdevs_inf[i].pci.cr_dev[0]) {
                n++;
            }
        }
        sprintf(vbuf, "O %d", n);
        writes_deb(con, vbuf);
        for (i = 0; i < devs_num; i++) {
            if (mdevs_inf[i].pci.conf_dev[0]) {
                writes_deb(con, mdevs_inf[i].pci.conf_dev);
            } else {
                writes_deb(con, mdevs_inf[i].dev_name);
            }
            if (mdevs_inf[i].pci.cr_dev[0]) {
                writes_deb(con, mdevs_inf[i].pci.cr_dev);
            }
        }
    }
    mdevices_info_destroy(mdevs_inf, devs_num);
#else
    (void)con;
#endif
}
#endif
/* ////////////////////////////////////////////////////////////////////// */



/* ////////////////////////////////////////////////////////////////////// */
void usage(const char *s)
{
    printf("Usage:\n\t%s [switches]\n\n", s);
    printf("Switches may be:\n");
    printf("\t-p[ort] <port> - Listen to specify port (default is %d).\n", port);
    printf("\t-d[ebug]       - Print all socket traffic (for debugging only).\n");
    printf("%s", sim_str);
    printf("\t-h[elp]        - Print help message.\n");
    printf("\t-v[ersion]     - Print version.\n");
    exit(1);
}

/* ////////////////////////////////////////////////////////////////////// */
void mySignal()
{
    exit(0);
}

#define GET_PARAM(param, str, type, param_name, err_msg) { \
        char *end; \
        param = (type)strtoul(str, &end, 0); \
        if (*end) { \
            sprintf(err_msg, "E Invalid %s", param_name); \
            return 1; \
        } \
}




int parse_i2c_cmd(char *buf, u_int8_t *addr_width, u_int8_t *slave_addr, int *size,
                  unsigned int *offset, u_int8_t *data, char *err_msg)
{
    char *p_arr[5];
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
    GET_PARAM(*offset,     p_arr[3], u_int32_t, "offset", err_msg);

    if (args_num == 5) {
        char *p = p_arr[4];

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
            strncpy(tmp_num, "0x", 3);
            strncpy(tmp_num + 2, p, 3);
            tmp_num[4] = '\0';
            ((u_int8_t*)data)[i] = (u_int8_t)strtoul(tmp_num, 0, 0);
            p += 2;
        }
    }

    return 0;
}

int copy_buff_to_str(char *str, u_int8_t *data, int size)
{
    char *p = str;
    int i;
    for (i = 0; i < size; i++) {
        sprintf(p, "%02x", data[i]);
        p += 2;
    }
    return 0;
}

/* ////////////////////////////////////////////////////////////////////// */
#define CHK2(f, m) do { if ((f) < 0) { perror(m); exit(1); } } while (0)
#define MSTSERVER_VERSION "1.4"
#define MSTSERVER_NAME    "mtserver"

int main(int ac, char *av[])
{
    char *end;
    char *local_dev = NULL;
    char buf[BUF_LEN], dev_buf[DEV_LEN];
    int i, con, rc;
    mfile *mf = 0;

    /* Command line parsing. */
    for (i = 1; i < ac; i++) {
        switch (*av[i]) {
        case '-':
            ++av[i];
            if (!strcmp(av[i], "p")  ||  !strcmp(av[i], "port")) {
                if (++i >= ac) {
                    printf("After switch \"%s\" port number is expected.\n", av[--i]);
                    printf("Type \"%s -h\" for help.\n", av[0]);
                    exit(1);
                }
                port = (int)strtol(av[i], &end, 0);
                if (*end) {
                    printf("Invalid port: \"%s\" -- ?\n", end);
                    printf("Type \"%s -h\" for help.\n", av[0]);
                    exit(1);
                }
                if (port < 1 || port > 65535) {
                    printf("-E- Invalid port value: %d, port should be 16-bit number (Range: 1-65535)\n", port);
                    exit(1);
                }
            } else if (!strcmp(av[i], "dev")) {
                if (++i >= ac) {
                    printf("After switch \"%s\" a device is expected.\n", av[--i]);
                    printf("Type \"%s -h\" for help.\n", av[0]);
                    exit(1);
                }
                local_dev = av[i];

            } else if (!strcmp(av[i], "d")  ||  !strcmp(av[i], "debug")) {
                sdebug = 1;
            } else if (!strcmp(av[i], "h")  ||  !strcmp(av[i], "help")) {
                usage(av[0]);
            } else if (!strcmp(av[i], "v")  ||  !strcmp(av[i], "version")) {
                print_version_string(MSTSERVER_NAME, MSTSERVER_VERSION);
                exit(0);
            } else if (!strcmp(av[i], "i")  ||  !strcmp(av[i], "id")) {
                check_id_arg(av, ac, &i);
            } else if (!strcmp(av[i], "f")  ||  !strcmp(av[i], "file")) {
                check_file_arg(av, ac, &i);
            } else {
                printf("Invalid switch \"%s\".\n", av[i]);
                usage(av[0]);
                exit(1);
            }
            break;

        case '?':
            usage(av[0]);
            break;

        default:
            printf("Invalid parameter \"%s\".\n", av[i]);
            usage(av[0]);
            exit(1);
        }
    }

#ifdef MST_UL
    if (local_dev == NULL) {
        printf("When accessing via user level mst, -dev <bus:dev.fun> flag must be provided\n");
        exit(1);
    }

#endif

    prepare_the_map_file();
    PREP_SIGNAL(mySignal);
    WIN_INIT();

    /* Now open and start work */
    logset(1);
    WIN_WHILE() {
        con = open_serv_connection(port);
        int addrInUseError = 0;
        if (con < 0) {
#ifdef __WIN__
            addrInUseError = WSAEADDRINUSE;
#else
            addrInUseError = EADDRINUSE;
#endif        
            if (errno == addrInUseError) {
                printf("Open connection (server side): Address already in use\n");
                exit(1);
            }
        }
        CHK2(con, "Open connection (server side)");

        for (;;) {

            memset(buf, 0, BUF_LEN);
            rc = reads(con, buf, BUF_LEN, PT_TCP);
            if (rc <= 0) {
                if (sdebug) {
                    printf("-D- read failed - closing connection. rc=%d, %s\n", rc, strerror(errno));
                }
                close(con);

                // In windows:
                // A client socket is handled in teh main thread (single connection at a time).
                // On a connection close the socket and mf are closed and a new listening socket is opened.
                // In Linux:
                // The client socket is handled in a child process - which exits when teh client connection closes.
                //
                // TODO: Move to thread handling and unify Win and Lin behavior.
                //

                #ifndef __WIN__
                if (rc < 0) {
                    perror("");
                    exit(1);
                }
                #endif
                break;    /*  EOF */
            }
            if (sdebug) {
                printf("<- %s\n", buf);
            }
            switch (*buf) {
            case 'O':   /*  Open mfile */

                if (mf) {
                    writes_deb(con, "E Already opened");
                } else {
#ifndef MST_UL
                    DType dtype = strtoul(buf + 2, &end, 0);
                    if (*end != ' ') {
                        /*  Old style (O DEV_NAME) */
                        mf = mopen(buf + 2);
                    } else {
                        /*  New style (O FLAG DEV_NAME) */
                        mf = mopend(end + 1, dtype);
                    }
#else
                    mf = mopen(local_dev);
#endif
                    if (mf) {
                        // write Recv buffer
                        char res_buf[16];
                        snprintf(res_buf, 16, "O %d", mget_vsec_supp(mf));
                        writes_deb(con, res_buf);
                    } else {
                        write_err(con);
                    }
                }
                break;

            case 'C':  /*  Close mfile */
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
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

            case 'L':   /*  Get devices list */
                if (local_dev == NULL) {
                    get_devices_list(con);
                } else {
                    strcpy(dev_buf, "/dev/mst/mt25204_pci_cr0");
                    printf("-D- local_dev=%s dev_buf=%s\n", local_dev, dev_buf);
                    writes_deb(con, "O 1");
                    writes_deb(con, dev_buf);
                }

                break;

            case 'R':   /*  Read word */
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    unsigned int offset;
                    u_int32_t value;
                    offset = strtoul(buf + 2, &end, 0);
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
            case 'S':  /*  Scan I2C bus */
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    u_int8_t slv_arr[SLV_ADDRS_NUM] = {0};
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

            case 'B':
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    unsigned int offset;
                    int size;
                    u_int32_t buf_data[MAX_DWORDS];

                    offset = strtoul(buf + 2, &end, 0);
                    if (*end != ' ') {
                        writes_deb(con, "E Invalid offset");
                    }

                    size = strtoul(end, &end, 0);
                    if (*end != '\0') {
                        writes_deb(con, "E Invalid size");
                    }

                    if (mread4_block(mf, offset, buf_data, size) != size) {
                        write_err(con);
                    } else   {
                        int i;
                        int div4 = size >> 2;
                        int mod4 = size % 4;
                        sprintf(buf, "O");
                        char *last = buf + 1;
                        for (i = 0; i < div4; i++) {
                            last += sprintf(last, " 0x%08x", buf_data[i]);
                        }
                        /* If the size is not divided by 4 need to read the remained bytes */
                        if (mod4) {
                            last += sprintf(last, " 0x");
                            for (i = mod4 - 1; i >= 0; i--) {
                                last += sprintf(last, "%02x", ((u_int8_t*)buf_data)[div4 * 4 + i]);
                            }
                        }
                        writes_deb(con, buf);
                    }
                }
                break;

            case 'U':
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    unsigned int offset;
                    int size;
                    u_int32_t buf_data[MAX_DWORDS];
                    int i;

                    offset = strtoul(buf + 2, &end, 0);
                    if (*end != ' ') {
                        writes_deb(con, "E Invalid offset");
                    }

                    size = strtoul(end, &end, 0);
                    if (*end != ' ' || size > (MAX_DWORDS << 2)) {
                        writes_deb(con, "E Invalid size");
                    }

                    for (i = 0; i < (size + 3) >> 2; i++) {
                        ((u_int32_t*)buf_data)[i] = strtoul(end, &end, 0);

                        if (*end != (i < ((size + 3) >> 2) - 1 ? ' ' : '\0')) {
                            writes_deb(con, "E Invalid data");
                        }
                    }

                    if (mwrite4_block(mf, offset, buf_data, size) != size) {
                        write_err(con);
                    } else   {
                        write_ok(con);
                    }
                }
                break;

            case 'r':   /*  Read I2C */
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    u_int8_t data[64];
                    char err_msg[256];
                    u_int8_t addr_width, slave_addr;
                    unsigned int offset;
                    int size;

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
                    int size;

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

            case 'P':
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    mpci_change(mf);
                    write_ok(con);
                }
                break;

            case 'W':   /*  Write word */
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    unsigned int offset;
                    u_int32_t value;
                    char *p = strchr(buf + 2, ' ');
                    if (!p) {
                        writes_deb(con, "E Invalid format (should be OFFS DATA)");
                    } else {
                        *p = '\0';
                        p++;
                        offset = strtoul(buf + 2, &end, 0);
                        if (*end) {
                            writes_deb(con, "E Invalid offset");
                        } else {
                            value = strtoul(p, &end, 0);
                            if (*end) {
                                writes_deb(con, "E Invalid data");
                            } else {
                                if (mwrite4(mf, offset, value) < 4) {
                                    write_err(con);
                                } else {
                                    write_ok(con);
                                }
                            }
                        }
                    }
                }
                break;

            case 'A':
                if (!mf) {
                    writes_deb(con, "E Not opened");
                } else {
                    char *p = buf + 2;
                    int space;
                    space = strtol(p, &end, 0);
                    if (*end) {
                        writes_deb(con, "E Invalid offset");
                    }
                    if (mset_addr_space(mf, space)) {
                        write_err(con);
                    } else {
                        write_ok(con);
                    }
                }
                break;

            default:
                writes(con, "E Invalid command", PT_TCP);
                if (sdebug) {
                    printf("-> E Invalid command (len:%d cmd:\"%s\")\n",
                           (int)strlen(buf), buf);
                }
                break;
            }
            WIN_CLOSE(mf, *buf);
        }

        if (mf) {
            if (sdebug) {
                printf("-D- mf opened from a prev connection - closing\n");
            }
            mclose(mf);
            mf = 0;
        }
    }

    unmap_and_close_file();
    return 0;
}
