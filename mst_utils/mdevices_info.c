/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
 *  Version: $Id$
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include "mtcr.h"
#include "dev_mgt/tools_dev_types.h"
#ifdef __linux__
#include <linux/limits.h>
#include <dirent.h>
#include <libgen.h>
#ifdef ENABLE_VFIO
#include "vfio_driver_access/VFIODriverAccessWrapperC.h"
#endif
#endif
#ifndef __FreeBSD__
#include "mtcr_ul/mtcr_ul_com.h"
#endif
#define MAX_DEVFN 256
#define BUF_MAX 4096

#ifdef __FreeBSD__
mfile* mopen_ul(const char* name)
{
    (void)name;
    return 0;
}

#ifdef ENABLE_VFIO
static inline bool CheckifVfioPciDriverIsLoaded(void)
{
    return false;
}
#endif
#endif

int is_type_exist(dev_info* devs, int len, Mdevs type)
{
    int i;

    for (i = 0; i < len; i++)
    {
        if (devs[i].type & type)
        {
            return 1;
        }
    }

    return 0;
}

int is_pci_domain_needed(dev_info* devs, int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        if (devs[i].type == MDEVS_TAVOR_CR)
        {
            if (devs[i].pci.domain)
            {
                return 1;
            }
        }
    }

    return 0;
}
/* */
/* given the path to the bond primary, extract the secondary eth devices */
/* */
int get_secondarys(char* path, char* buf, ssize_t bufsize)
{
    int count = 0;
    FILE* fp = fopen(path, "r");

    if (fp == NULL)
    {
        /* no secondary defined the device */
        return 0;
    }
    char* s = fgets(buf, bufsize, fp);

    fclose(fp);
    if (s == NULL)
    {
        /* no data to read for secondary devices */
        return 0;
    }
    /* strip trailing newlines/etc */
    buf[strcspn(buf, "\r\n")] = 0; /* works for LF, CR, CRLF, LFCR, ... */
    /* walk the secondary list, turning into zero terminated strings */
    char* tok = strtok(buf, (char*)" ");

    while (tok != NULL)
    {
        count++;
        tok = strtok(NULL, (char*)" ");
    }
    return count;
}

char* map_eth_bond_name(char* net_dev, char* buf, ssize_t bufsize)
{
    int link_size = 0;
    char path[PATH_MAX] = {0};
    char secondary_buf[BUF_MAX] = {0};

    /* see if we have a bond primary for the device */
    /* and if the bond primary has secondarys */
    snprintf(path, PATH_MAX, "/sys/class/net/%s/master/bonding/slaves", net_dev);
    int i;
    int count = get_secondarys(path, secondary_buf, sizeof(secondary_buf));
    char* tok = secondary_buf;
    int found = 0;

    for (i = 0; i < count; i++)
    {
        /* see if the net_dev is a secondary */
        /* its possible to have a primary, but not be a secondary device (ovs) */
        if (strcmp(net_dev, tok) == 0)
        {
            found = 1;
            break;
        }
        tok = tok + strlen(tok) + 1;
    }
    if (found == 0)
    {
        return NULL;
    }
    /* extract the name of the bond primary from the link */
    snprintf(path, PATH_MAX, "/sys/class/net/%s/master", net_dev);
    link_size = readlink(path, buf, bufsize - 1);
    if (link_size > 0)
    {
        /* printf("BOND_LINK:%d:%s\n", link_size, buf); */
        /* parse the bond primary ETH link name */
        buf[link_size] = 0;
        char* name = strrchr(buf, '/');
        name++;
        return name;
    }
    /* printf("NO BOND_LINK:%d:%s\n", link_size, path); */
    return NULL;
}
/*  set in main, used by find_rdma_bond_dev */
static dev_info* devs = 0;
static int len = 0;
dev_info* find_rdma_bond_dev(char* net_dev)
{
    int i;
    int j;

    for (i = 0; i < len; i++)
    {
        dev_info* dev = &devs[i];
        if (dev->pci.net_devs != NULL)
        {
            for (j = 0; dev->pci.net_devs[j]; j++)
            {
                if (strcmp(net_dev, dev->pci.net_devs[j]) == 0)
                {
                    return dev;
                }
            }
        }
    }
    return NULL;
}
int fmt_ib_dev(dev_info* dev, char* fmt)
{
    /* Add IB devices info */
    if (dev->pci.ib_devs)
    {
        int j;
        int last = 0;
        for (j = 0; dev->pci.ib_devs[j]; j++)
        {
            last += snprintf(fmt + last, BUF_MAX, "%s", dev->pci.ib_devs[j]);
            if (dev->pci.ib_devs[j + 1])
            {
                last += sprintf(fmt + last, ",");
            }
        }
        return 1;
    }
    else
    {
        sprintf(fmt, " ");
        return 0;
    }
}
int get_rdma_bond_dev(char* map_rdma, int map_rdma_size, char* net_dev_secondary, char* net_dev_primary)
{
    (void)map_rdma_size;
    char path[PATH_MAX];
    char secondary_buf[BUF_MAX];
    dev_info* rdma_bond_dev;

    /* getthe list of secondarys for the primary device */
    snprintf(path, PATH_MAX, "/sys/devices/virtual/net/%s/bonding/slaves", net_dev_primary);
    int i;
    int count = get_secondarys(path, secondary_buf, sizeof(secondary_buf));
    char* tok = secondary_buf;

    for (i = 0; i < count; i++)
    {
        /* if this a different secondary than the net_dev_secondary, */
        if (strcmp(net_dev_secondary, tok) != 0)
        {
            /* see if the different secondary has a rdma_bond_dev */
            rdma_bond_dev = find_rdma_bond_dev(tok);
            if (rdma_bond_dev != NULL)
            {
                if (fmt_ib_dev(rdma_bond_dev, map_rdma) == 1)
                {
                    /* output the missing ibdev rdma_bond_device */
                    return 1;
                }
                break;
            }
        }
        tok = tok + strlen(tok) + 1;
    }
    return 0;
}
int print_rdma_bond_dev(char* net_dev_secondary, char* net_dev_primary)
{
    char map_rdma[BUF_MAX];

    if (get_rdma_bond_dev(map_rdma, sizeof(map_rdma), net_dev_secondary, net_dev_primary))
    {
        /* output the missing rdma_bond_device */
        printf("%-16s", map_rdma);
        return 1;
    }
    printf("%-16s", " ");
    /* no secondary dev found */
    return 0;
}

// Calculate the NET string length for a single device
int calculate_net_string_length(dev_info* dev)
{
    int length = 1;

    if (dev->pci.net_devs)
    {
        char map_eth[BUF_MAX];
        for (int i = 0; dev->pci.net_devs[i]; i++)
        {
            char* net_dev = map_eth_bond_name(dev->pci.net_devs[i], map_eth, sizeof(map_eth));
            if (net_dev == NULL)
            {
                net_dev = dev->pci.net_devs[i];
            }
            length += strlen("net-") + strlen(net_dev);
            if (dev->pci.net_devs[i + 1])
            {
                length += 1; // for comma
            }
        }
    }

    return length;
}

// Calculate max NET column width
int get_max_net_column_width(dev_info* devs, int len)
{
    int max_width = 0;
    for (int i = 0; i < len; i++)
    {
        if (devs[i].type == MDEVS_TAVOR_CR)
        {
            int width = calculate_net_string_length(&devs[i]);
            if (width > max_width)
            {
                max_width = width;
            }
        }
    }

    return max_width + 1; // +1 for space
}

void find_all_fwctl_devices(dev_info* devs, int dev_count)
{
#ifdef __linux__
    DIR* dir;
    struct dirent* ent;
    char device_path[PATH_MAX];
    char absolute_device_path[PATH_MAX];
    char pci_addr[32];
    int i;
    int idx;

    // printf("find_all_fwctl_devices: find_all_fwctl_devices() called with %d devices\n", dev_count);

    for (i = 0; i < dev_count; i++)
    {
        if (devs[i].type == MDEVS_TAVOR_CR)
        {
            devs[i].pci.fwctl_dev[0] = '\0';
        }
    }

    dir = opendir("/sys/class/fwctl");
    if (dir == NULL)
    {
        // printf("find_all_fwctl_devices: Failed to open /sys/class/fwctl directory\n");
        return;
    }
    // printf("find_all_fwctl_devices: Successfully opened /sys/class/fwctl directory\n");

    // Iterate through fwctl devices
    while ((ent = readdir(dir)) != NULL)
    {
        if (ent->d_name[0] == '.')
            continue;

        // printf("find_all_fwctl_devices: Found directory entry: %s\n", ent->d_name);

        // Check if this is a fwctl device (pattern: fwctl[0-9]+)
        if (sscanf(ent->d_name, "fwctl%d", &idx) != 1)
        {
            // printf("find_all_fwctl_devices: Skipping %s - not a fwctl device\n", ent->d_name);
            continue;
        }

        // Get the device symlink
        snprintf(device_path, sizeof(device_path), "/sys/class/fwctl/%s/device", ent->d_name);

        // Resolve the symlink
        // realpath returns an absolute path like: /sys/devices/pci0000:00/0000:00:02.0/0000:04:00.0
        if (realpath(device_path, absolute_device_path) == NULL)
        {
            // printf("find_all_fwctl_devices: Failed to resolve fwctl device symlink for %s\n", ent->d_name);
            continue;
        }
        // printf("find_all_fwctl_devices: Symlink %s resolves to %s\n", device_path, absolute_device_path);

        // Extract PCI address
        char* pci_name = basename(absolute_device_path);
        if (pci_name != NULL)
        {
            unsigned int domain, bus, dev, func;
            // Parse PCI address (format: DDDD:BB:DD.F)
            if (sscanf(pci_name, "%x:%x:%x.%x", &domain, &bus, &dev, &func) == 4)
            {
                snprintf(pci_addr, sizeof(pci_addr), "%04x:%02x:%02x.%x", domain, bus, dev, func);
                // printf("find_all_fwctl_devices: Extracted PCI address: %s\n", pci_addr);

                for (i = 0; i < dev_count; i++)
                {
                    if (devs[i].type == MDEVS_TAVOR_CR)
                    {
                        char dev_pci_addr[32];
                        snprintf(dev_pci_addr, sizeof(dev_pci_addr), "%04x:%02x:%02x.%x", devs[i].pci.domain, devs[i].pci.bus, devs[i].pci.dev, devs[i].pci.func);

                        if (strcmp(dev_pci_addr, pci_addr) == 0)
                        {
                            snprintf(devs[i].pci.fwctl_dev, DEV_NAME_SZ, "/dev/fwctl/%s", ent->d_name);
                            // printf("find_all_fwctl_devices: Matched device %s with fwctl device /dev/fwctl/%s\n",
                            //        dev_pci_addr, ent->d_name);
                            break;
                        }
                    }
                }
            }
        }
    }

    closedir(dir);

    // Print summary of assignments
    // printf("find_all_fwctl_devices: fwctl device assignments:\n");
    for (i = 0; i < dev_count; i++)
    {
        if (devs[i].type == MDEVS_TAVOR_CR && devs[i].pci.fwctl_dev[0] != '\0')
        {
            // printf("find_all_fwctl_devices:   %04x:%02x:%02x.%x -> %s\n", devs[i].pci.domain, devs[i].pci.bus,
            //        devs[i].pci.dev, devs[i].pci.func, devs[i].pci.fwctl_dev);
        }
    }
#else
    // Not supported on other platforms - clear all fwctl_dev fields
    int i;
    for (i = 0; i < dev_count; i++)
    {
        if (devs[i].type == MDEVS_TAVOR_CR)
        {
            devs[i].pci.fwctl_dev[0] = '\0';
        }
    }
#endif
}

void find_fwctl_device(dev_info* dev)
{
    // For single device, just call batch function with array of 1
    find_all_fwctl_devices(dev, 1);
}

void print_pci_info(dev_info* dev, int domain_needed, mfile* mf, int net_width)
{
    char dbdf[16384] = {0};
    char fmt[16384] = {0};

    /* Add PCI info */
    if (domain_needed)
    {
        sprintf(dbdf, "%04x:%02x:%02x.%x", dev->pci.domain, dev->pci.bus, dev->pci.dev, dev->pci.func);
        printf("%-16s", dbdf);
    }
    else
    {
        sprintf(dbdf, "%02x:%02x.%x", dev->pci.bus, dev->pci.dev, dev->pci.func);
        printf("%-10s", dbdf);
    }

    int hasIB = fmt_ib_dev(dev, fmt);

    if (hasIB)
    {
        printf("%-16s", fmt);
    }
    else
    {
        printf("%-16s", " ");
    }

    /* Add NET devices info */
    if (dev->pci.net_devs)
    {
        int j;
        int last = 0;
        char map_eth[BUF_MAX];
        int done = 0;
        for (j = 0; dev->pci.net_devs[j]; j++)
        {
            char* net_dev = map_eth_bond_name(dev->pci.net_devs[j], map_eth, sizeof(map_eth));
            if (net_dev == NULL)
            {
                net_dev = dev->pci.net_devs[j];
            }
            else if (hasIB == 0)
            {
                hasIB = print_rdma_bond_dev(dev->pci.net_devs[j], net_dev);
            }
            last += snprintf(fmt + last, BUF_MAX, "net-%s", net_dev);
            if (dev->pci.net_devs[j + 1])
            {
                last += sprintf(fmt + last, ",");
            }
        }
    }
    else
    {
        sprintf(fmt, " ");
    }
    printf("%-*s", net_width, fmt);

    /* Add NUMA node */
    printf("%-6s", dev->pci.numa_node);
#ifdef ENABLE_VFIO
    if (CheckifVfioPciDriverIsLoaded())
    {
        char vfio_dev[32];
        snprintf(vfio_dev, sizeof(vfio_dev), "vfio-%s", dbdf);
        printf("%-18s", vfio_dev);
    }
    else
    {
        printf("%-18s", " ");
    }
#else
    printf("%-18s", " ");
#endif

    // Add FWCTL
    if (dev->pci.fwctl_dev[0] != '\0')
    {
        printf("%-25s", dev->pci.fwctl_dev);
    }
    else
    {
        printf("%-25s", " ");
    }

    // Add STATE
    if (mf && (is_zombiefish_device(mf) || dm_is_livefish_mode(mf)))
    {
        printf("%-12s", "recovery");
    }
    else
    {
        printf("%-12s", " ");
    }

    printf("\n");
}

void printHelp()
{
    printf("NAME \n");
    printf("\tmdevices_info \n");
    printf("SYNOPSIS: \n");
    printf("\tmdevices_info [options]\n");
    printf("OPTIONS \n");
    printf("\t-h  | help \n");
    printf("\t-v  | Verbose \n");
    printf("\t-vv | Verbose \n");
}

int is_vsec_supported(char* device_name)
{
    int ret_value = 0;

    if (!device_name)
    {
        return ret_value;
    }

    mfile* mf = mopen_ul(device_name);

    if (mf)
    {
        ret_value = 1;
    }
    mclose(mf);
    return ret_value;
}

int main(int argc, char** argv)
{
    int rc = 1;
    int i;
    int verbose = 0;
    int vverbose = 0;
    int domain_needed = 0;
    int validFlag = 0;

    for (i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-v"))
        {
            verbose = 1;
            validFlag = 1;
        }

        if (!strcmp(argv[i], "-vv"))
        {
            verbose = 1;
            vverbose = 1;
            validFlag = 1;
        }

        if (!strcmp(argv[i], "-s"))
        {
#ifdef __FreeBSD__
            printf("-E- Unsupported option '-s' for FreeBSD \n");
            goto cleanup;
#endif

            return is_vsec_supported(argv[i + 1]);
        }

        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            printHelp();
            return 1;
        }
    }

    if ((argc > 1) && (validFlag != 1))
    {
        printf("-E- Unrecognized option\n");
        printHelp();
        return 1;
    }

    devs = mdevices_info_v(0xffffffff, &len, 1);

    if (!len)
    {
        printf("\n    No MST devices were found or MST modules are not loaded.\n"
               "    You may need to run 'mst start' to load MST modules.\n");
        goto cleanup;
    }

    if (!devs)
    {
        printf("-E- Failed to get available devices list\n");
        goto cleanup;
    }

    /* printf("-D- %d devices were found\n", len); */
    /* print pci devices */
    if (is_type_exist(devs, len, MDEVS_TAVOR_CR))
    {
        find_all_fwctl_devices(devs, len);
        printf("PCI devices:\n");
        printf("------------\n");

        domain_needed = is_pci_domain_needed(devs, len);
        int ul_mode = 0;
#ifndef __FreeBSD__
        ul_mode = devs[0].ul_mode;
#endif
        int net_width = 0;
        if (verbose)
        {
            // Calculate dynamic NET column width
            net_width = get_max_net_column_width(devs, len);
            if (domain_needed)
            {
                if (ul_mode)
                {
                    printf("%-24s%-9s%-16s%-16s%-*s%-6s%-18s%-25s%-12s\n",
                           "DEVICE_TYPE",
                           "MST",
                           "PCI",
                           "RDMA",
                           net_width,
                           "NET",
                           "NUMA",
#ifdef ENABLE_VFIO
                           "VFIO",
#else
                           "",
#endif
                           "FWCTL",
                           "STATE");
                }
                else
                {
                    printf("%-24s%-30s%-16s%-16s%-*s%-6s%-18s%-25s%-12s\n",
                           "DEVICE_TYPE",
                           "MST",
                           "PCI",
                           "RDMA",
                           net_width,
                           "NET",
                           "NUMA",
#ifdef ENABLE_VFIO
                           "VFIO",
#else
                           "",
#endif
                           "FWCTL",
                           "STATE");
                }
                /* printf("%-30s%-16s%-16s%-8s%-20s\n", "---", "-----------", "---", "----", "---"); */
            }
            else
            {
                if (ul_mode)
                {
                    printf("%-24s%-9s%-10s%-16s%-*s%-6s%-18s%-25s%-12s\n",
                           "DEVICE_TYPE",
                           "MST",
                           "PCI",
                           "RDMA",
                           net_width,
                           "NET",
                           "NUMA",
#ifdef ENABLE_VFIO
                           "VFIO",
#else
                           "",
#endif
                           "FWCTL",
                           "STATE");
                }
                else
                {
                    printf("%-24s%-30s%-10s%-16s%-*s%-6s%-18s%-25s%-12s\n",
                           "DEVICE_TYPE",
                           "MST",
                           "PCI",
                           "RDMA",
                           net_width,
                           "NET",
                           "NUMA",
#ifdef ENABLE_VFIO
                           "VFIO",
#else
                           "",
#endif
                           "FWCTL",
                           "STATE");
                }
                /* printf("%-30s%-16s%-10s%-8s%-20s\n", "---", "-----------", "---", "----", "---"); */
            }
        }

        /* dev_lst = devs; */
        /* dev_lst_len = len; */
        for (i = 0; i < len; i++)
        {
            if ((devs[i].type == MDEVS_TAVOR_CR) && (strstr(devs[i].dev_name, "cable_") == NULL))
            {
                mfile* mf = mopen(devs[i].dev_name);

                if (is_pcie_switch_device(mf) && !mf->functional_vsec_supp)
                {
                    mclose(mf);
                    continue;
                }

                dm_dev_id_t dev_id = 0;
                u_int32_t hw_id = 0;
                u_int32_t hw_rev = 0;
                char dev_type[128] = {0};
                if (!mf || dm_get_device_id_without_prints(mf, &dev_id, &hw_id, &hw_rev))
                {
/* Due to issue 2719128, we prefer to skip this device */
/*   and not filter using the 'pciconf' FreeBSD tool. */
#ifdef __FreeBSD__
                    continue;
#endif
                    snprintf(dev_type, 128, "NA");
                } else {
                    snprintf(dev_type, 128, "%s(rev:%x)", dm_dev_type2str(dev_id), hw_rev);
                }
                /* printf("-D- CF: %s, CR: %s\n", devs[i].pci.conf_dev, devs[i].pci.cr_dev); */
                int conf_exist = devs[i].pci.conf_dev[0];
                int cr_exist = devs[i].pci.cr_dev[0];
                if (ul_mode)
                {
                    cr_exist = 0;
                }
                if (vverbose)
                {
                    /* printf("-D- VVERBOS\n"); */
                    if (conf_exist)
                    {
                        printf("%-24s", dev_type);
                        if (ul_mode)
                        {
                            printf("%-9s", "NA");
                        }
                        else
                        {
                            printf("%-30s", devs[i].pci.conf_dev);
                        }
                        print_pci_info(&devs[i], domain_needed, mf, net_width);
                    }
                    if (cr_exist)
                    {
                        printf("%-24s", dev_type);
                        printf("%-30s", devs[i].pci.cr_dev);
                        print_pci_info(&devs[i], domain_needed, mf, net_width);
                    }
                }
                else
                {
                    /* printf("-D- NOT VERBOS\n"); */
                    if (conf_exist)
                    {
                        printf("%-24s", dev_type);
                        if (ul_mode)
                        {
                            if (verbose)
                            {
                                printf("%-9s", "NA");
                            }
                            else
                            {
                                printf("%-9s", devs[i].pci.cr_dev);
                            }
                        }
                        else
                        {
                            printf("%-30s", devs[i].pci.conf_dev);
                        }
                    }
                    if (cr_exist)
                    {
                        if (conf_exist)
                        {
                            print_pci_info(&devs[i], domain_needed, mf, net_width);
                            printf("\n");
                        }
                        printf("%-24s", dev_type);
                        printf("%-30s", devs[i].pci.cr_dev);
                    }

                    if (verbose)
                    {
                        print_pci_info(&devs[i], domain_needed, mf, net_width);
                    }
                }
                printf("\n");
                if (mf)
                {
                    mclose(mf);
                }
            }
        }
    }

    /* print infiniband devices */
    if (is_type_exist(devs, len, MDEVS_IB))
    {
        printf("Inband devices:\n");
        printf("---------------\n");

        for (i = 0; i < len; i++)
        {
            if (devs[i].type == MDEVS_IB)
            {
                printf("%s\n", devs[i].dev_name);
            }
        }
        printf("\n");
    }

    int cable_found = 0;
    for (i = 0; i < len; i++)
    {
        if (devs[i].dev_name && (strstr(devs[i].dev_name, "cable_") != NULL))
        {
            if (cable_found == 0)
            {
                printf("\nCable devices:\n");
                printf("---------------\n");
                cable_found = 1;
            }
            printf("%s\n", devs[i].dev_name);
        }
    }
    if (cable_found)
    {
        printf("\n");
    }

    rc = 0;
cleanup:
    if (devs)
    {
        mdevices_info_destroy(devs, len);
    }

    return rc;
}
