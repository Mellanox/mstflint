/*
 *
 *  mtcr.h - Mellanox Software tools (mst) driver definitions
 *
 * Copyright (c) 2005 Mellanox Technologies Ltd.  All rights reserved.
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

#ifndef _MST_H
#define _MST_H

//use memory mapped /dev/mem for access
#define CONFIG_ENABLE_MMAP 1
//mmap /dev/mem for memory access (does not work on sparc)
#define CONFIG_USE_DEV_MEM 1

//use pci configuration cycles for access
#define CONFIG_ENABLE_PCICONF 1

//#define CONFIG_HAVE_LONG_ADDRESS 1
#define CONFIG_HAVE_LONG_LONG_ADDRESS 1


#if CONFIG_ENABLE_PCICONF
#define _XOPEN_SOURCE 500
#endif

#if CONFIG_ENABLE_MMAP
#define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>

#include <unistd.h>

#include <netinet/in.h>
#include <endian.h>
#include <byteswap.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


#if CONFIG_ENABLE_MMAP
#include <sys/mman.h>
#if !CONFIG_USE_DEV_MEM
#include <sys/pci.h>
#include <sys/ioctl.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#endif


#ifndef __be32_to_cpu
#define __be32_to_cpu(x) ntohl(x)
#endif
#ifndef __cpu_to_be32
#define __cpu_to_be32(x) htonl(x)
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN
#ifndef __cpu_to_le32
#define  __cpu_to_le32(x) (x)
#endif
#ifndef __le32_to_cpu
#define  __le32_to_cpu(x) (x)
#endif
#elif __BYTE_ORDER == __BIG_ENDIAN
#ifndef __cpu_to_le32
#define  __cpu_to_le32(x) bswap_32(x)
#endif
#ifndef __le32_to_cpu
#define  __le32_to_cpu(x) bswap_32(x)
#endif
#else
#ifndef __cpu_to_le32
#define  __cpu_to_le32(x) bswap_32(__cpu_to_be32(x))
#endif
#ifndef __le32_to_cpu
#define  __le32_to_cpu(x) __be32_to_cpu(bswap_32(x))
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*  All fields in the following structure are not supposed to be used */
/*  or modified by user programs. */
typedef struct mfile_t {
    int           fd;
    void          *ptr;
} mfile;


#if CONFIG_ENABLE_MMAP
/*
 * The PCI interface treats multi-function devices as independent
 * devices.  The slot/function address of each device is encoded
 * in a single byte as follows:
 *
 *	7:3 = slot
 *	2:0 = function
 */
#define PCI_DEVFN(slot,func)	((((slot) & 0x1f) << 3) | ((func) & 0x07))
#define PCI_SLOT(devfn)		(((devfn) >> 3) & 0x1f)
#define PCI_FUNC(devfn)		((devfn) & 0x07)

/* Find the specific device by scanning /proc/bus/pci/devices */
int mfind(const char* name, off_t* offset_p,
		unsigned *bus_p, unsigned *dev_p, unsigned *func_p)
{
  FILE* f;
	unsigned     irq;
#if CONFIG_HAVE_LONG_LONG_ADDRESS
	unsigned long long 
#elif CONFIG_HAVE_LONG_ADDRESS
	unsigned long
#else
	unsigned
#endif
	base_addr[6], rom_base_addr, size[6], rom_size;

  unsigned    bus ;
  unsigned   dev ;
  unsigned   func ;
  unsigned   vendor_id ;
  unsigned   device_id ;
  unsigned int cnt;

  unsigned long long offset;

  unsigned my_domain = 0;
  unsigned my_bus;
  unsigned my_dev;
  unsigned my_func;
  char buf[4048];

  int scnt;

  scnt=sscanf(name,"%x:%x.%x", & my_bus, & my_dev, & my_func);

  if (scnt == 3) goto name_parsed;

  scnt=sscanf(name,"%x:%x:%x.%x", & my_domain, & my_bus, & my_dev, & my_func);

  if (scnt == 4) goto name_parsed;

  fprintf(stderr,"Unable to parse device %s\n", name);
  errno=EINVAL;
  return 1;

name_parsed:

  if (my_domain) {
    fprintf(stderr,"Device %s: domain number %#x detected.\n"
		   "Only domain 0x0 supported for now, sorry.\n",
		   name, my_domain);
    errno=EINVAL;
    return 1;
  }
  
  f = fopen("/proc/bus/pci/devices", "r");
  if (!f) return 1;

  for(;;)
  if (fgets(buf, sizeof(buf)-1, f))
    {
      unsigned dfn, vend;

      cnt = sscanf(buf,
#if CONFIG_HAVE_LONG_LONG_ADDRESS
	     "%x %x %x %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx",
#elif CONFIG_HAVE_LONG_ADDRESS
	     "%x %x %x %lx %lx %lx %lx %lx %lx %lx %lx %lx %lx %lx %lx %lx %lx",
#else
	     "%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x",
#endif
	     &dfn,
	     &vend,
	     &irq,
	     &base_addr[0],
	     &base_addr[1],
	     &base_addr[2],
	     &base_addr[3],
	     &base_addr[4],
	     &base_addr[5],
	     &rom_base_addr,
	     &size[0],
	     &size[1],
	     &size[2],
	     &size[3],
	     &size[4],
	     &size[5],
	     &rom_size);
      if (cnt != 9 && cnt != 10 && cnt != 17)
      {
        fprintf(stderr,"proc: parse error (read only %d items)\n", cnt);
        fprintf(stderr,"the offending line in " "/proc/bus/pci/devices" " is "
			"\"%.*s\"\n", (int)sizeof(buf), buf);
        goto error;
      }
      bus = dfn >> 8U;
      dev = PCI_SLOT(dfn & 0xff);
      func = PCI_FUNC(dfn & 0xff);
      vendor_id = vend >> 16U;
      device_id = vend & 0xffff;

      if (bus == my_bus && dev == my_dev && func == my_func)
      {
        break;
      }
    }
  else
    goto error;

  if (cnt != 17 || size[1] != 0 || size[0] != 0x100000)
  {
        fprintf(stderr,"proc: unexpected region size values: "
#if CONFIG_HAVE_LONG_LONG_ADDRESS
			"cnt=%d, size[0]=%#llx, size[1]=%#llx\n",
#elif CONFIG_HAVE_LONG_ADDRESS
			"cnt=%d, size[0]=%#lx, size[1]=%#lx\n",
#else
			"cnt=%d, size[0]=%#x, size[1]=%#x\n",
#endif
			cnt,size[0],size[1]);
        fprintf(stderr,"the offending line in " "/proc/bus/pci/devices" " is "
			"\"%.*s\"\n", (int)sizeof(buf), buf);
        goto error;
  }


  offset=((unsigned long long)(base_addr[1])<<32)+
    ((unsigned long long)(base_addr[0])&~(unsigned long long)(0xfffff));

  *offset_p=offset;
  *bus_p=bus;
  *dev_p=dev;
  *func_p=func;

  fclose(f);
  return 0;

error:
  errno=ENOENT;
  fclose(f);
  return 1;
}

#endif

/*
 * Open Mellanox Software tools (mst) driver. Device type==TAVOR
 * Return valid mfile ptr or 0 on failure
 */
mfile *mopen(const char *name)
{
  mfile *mf;
  off_t offset;
  int err;

  mf=(mfile*)malloc(sizeof(mfile));
  if (!mf) return 0;

  //If device name starts with /proc/bus/pci we'll use configuration cycles
  if (!strncmp(name,"/proc/bus/pci/",strlen("/proc/bus/pci/")))
  {
#if (CONFIG_ENABLE_PCICONF)
    mf->fd = open(name,O_RDWR | O_SYNC);
    if (mf->fd<0) goto open_failed;

    mf->ptr=NULL;
#else
    goto open_failed;
#endif
  }
  else
  {
#if CONFIG_ENABLE_MMAP
    unsigned bus, dev, func;
    if (mfind(name,&offset,&bus,&dev,&func)) goto find_failed;

#if CONFIG_USE_DEV_MEM
    mf->fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mf->fd<0) goto open_failed;
#else
    {
	    struct stat dummybuf;
	    char file_name[]="/proc/bus/pci/0000:00/00.0";
	    sprintf(file_name,"/proc/bus/pci/%2.2x/%2.2x.%1.1x",
			    bus,dev,func);
	    if (stat(file_name,&dummybuf))
		    sprintf(file_name,"/proc/bus/pci/0000:%2.2x/%2.2x.%1.1x",
			    bus,dev,func);
	    mf->fd = open(file_name, O_RDWR | O_SYNC);
	    if (mf->fd<0) goto open_failed;

	    if (ioctl(mf->fd, PCIIOC_MMAP_IS_MEM) < 0) goto ioctl_failed;
    }
#endif

    mf->ptr = mmap(NULL, 0x100000, PROT_READ | PROT_WRITE,
        MAP_SHARED, mf->fd, offset);

    if ( (! mf->ptr) || (mf->ptr == MAP_FAILED) ) goto map_failed;

#else
    goto open_failed;
#endif
  }
  return mf;


#if CONFIG_ENABLE_MMAP
map_failed:
        err = errno;
        close(mf->fd);
        errno = err;
#if !CONFIG_USE_DEV_MEM
ioctl_failed:
#endif
#endif
open_failed:
        err = errno;
        free(mf);
        errno = err;

#if CONFIG_ENABLE_MMAP
find_failed:
#endif
        return 0;
}

/*
 * Close Mellanox driver
 * req. descriptor
 */
int mclose(mfile *mf)
{
#if CONFIG_ENABLE_MMAP
  if (mf->ptr)
    munmap(mf->ptr,0x10000);
#endif
  close(mf->fd);
  free(mf);
  return 0;
}

/*
 * Read 4 bytes, return number of succ. read bytes or -1 on failure
 */
int mread4(mfile *mf, unsigned int offset, u_int32_t *value)
{
#if CONFIG_ENABLE_MMAP
  if (mf->ptr)
  {
            *value = __be32_to_cpu(*((u_int32_t *)((char *)mf->ptr + offset)));
            return 4;
  }
#endif
#if CONFIG_ENABLE_PCICONF
  {
    int rc;
    offset=__cpu_to_le32(offset);
    rc=pwrite(mf->fd, &offset, 4, 22*4);
    if (rc < 0)
    {
      perror("write offset");
      return rc;
    }
    if (rc!=4) return 0;
    rc=pread(mf->fd, value, 4, 23*4);
    if (rc < 0)
    {
      perror("read value");
      return rc;
    }
    *value=__le32_to_cpu(*value);
    return rc;
  }
#else
  return 0;
#endif
}

/*
 * Write 4 bytes, return number of succ. written bytes or -1 on failure
 */
int mwrite4(mfile *mf, unsigned int offset, u_int32_t value)
{
#if CONFIG_ENABLE_MMAP
  if (mf->ptr)
  {
            *((u_int32_t *)((char *)mf->ptr + offset)) = __cpu_to_be32(value);
            return 4;
  }
#endif
#if CONFIG_ENABLE_PCICONF
  {
    int rc;
    offset=__cpu_to_le32(offset);
    rc=pwrite(mf->fd, &offset, 4, 22*4);
    if (rc < 0)
    {
      perror("write offset");
      return rc;
    }
    if (rc!=4) return 0;
    value=__cpu_to_le32(value);
    rc=pwrite(mf->fd, &value, 4, 23*4);
    if (rc < 0)
    {
      perror("write value");
      return rc;
    }
    return rc;
  }
#else
  return 0;
#endif
}

#ifdef __cplusplus
}
#endif

#define DEV_MST_EXAMPLE1 "03:00.0"
#define DEV_MST_EXAMPLE2 "/proc/bus/pci/03/00.0"


#endif
