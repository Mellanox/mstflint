/*
 * Copyright(c) 2025 NVIDIA CORPORATION & AFFILIATES.All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.You may choose to be licensed under the terms of the GNU
 * General Public License(GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 * Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 * -Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 * -Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and / or other materials
 * provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ctype.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <glob.h>
#include "mlx5ctl.h"

int verbosity_level = 0;

/* find parent device under symlink: /sys/bus/auxiliary/devices/<device_name> */
static char *find_parent_device(char *device_name, char parent_dev[DEV_NAME_MAX])
{
	char resolved_path[PATH_MAX];
	char dev_path[PATH_MAX];
    char *parent, basename;

	snprintf(dev_path, sizeof(dev_path),
		 "/sys/bus/auxiliary/devices/%s", device_name);

        if (realpath(dev_path, resolved_path) == NULL)
                return NULL;

        parent = dirname(resolved_path);
        if (parent == NULL)
                return NULL;

	strncpy(parent_dev, strrchr(parent, '/') + 1, strlen(parent));
	return parent_dev;
}

int mlx5u_devinfo(struct mlx5u_dev *dev)
{
	struct mlx5ctl_info info = {};
	char parent_dev[DEV_PATH_MAX];
	int fd = dev->fd;
	int ret;

	ret = ioctl(fd, MLX5CTL_IOCTL_INFO, &info);
	if (ret) {
		printf("ioctl failed: %d errno(%d): %s\n", ret, errno, strerror(errno));
		return ret;
	}

	printf("ctldev: %s\n", dev->devname);
	printf("Parent dev: %s\n", find_parent_device(strrchr(dev->devname, '-') + 1, parent_dev));
	printf("UCTX UID: %d\n", info.uctx_uid);
	printf("UCTX CAP: 0x%x\n", info.uctx_cap);
	printf("DEV UCTX CAP: 0x%x\n", info.dev_uctx_cap);
	printf("USER CAP: 0x%x\n", info.ucap);

	printf("Current PID: %d FD %d\n", getpid(), fd);
	return 0;
}

static struct mlx5ctl_dev *_scan_ctl_devs(int *count) {
	glob_t glob_result;
	struct mlx5ctl_dev *devs;
	char* pattern = "/dev/mlx5ctl*";
	char parent_device_name[DEV_NAME_MAX];
	int ret = glob(pattern, GLOB_TILDE, NULL, &glob_result);

	if(ret != 0) {
		err_msg("Error while searching for files: %d\n", ret);
		return NULL;
	}

	if (glob_result.gl_pathc == 0)
		return NULL;

	devs = malloc(sizeof(struct mlx5ctl_dev) * glob_result.gl_pathc);
	memset(devs, 0, sizeof(struct mlx5ctl_dev) * glob_result.gl_pathc);
	if(devs == NULL) {
		err_msg("Error while allocating memory for devs: %d\n", ret);
		return NULL;

	}

	*count = glob_result.gl_pathc;

	for(unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
		char *pdev, *ctldev;

		/* /dev/mlx5ctl-mlx5_core.ctl.X */
		ctldev = strrchr(glob_result.gl_pathv[i], '-') + 1;
		/* mlx5_core.ctl.X */
		pdev = find_parent_device(ctldev, parent_device_name);

		devs[i].ctl_id = atoi(strrchr(ctldev, '.') + 1);
		strncpy(devs[i].ctldev, ctldev, DEV_NAME_MAX);
		if (pdev)
			strncpy(devs[i].mdev, pdev, DEV_NAME_MAX);
	}

	globfree(&glob_result);
	return devs;
}

static int is_a_number(const char *str)
{
	for (int i = 0; i < strlen(str); i++)
		if (!isdigit(str[i]))
			return 0;

	return 1;
}

static char *find_dev(const char *str, char dev_path[DEV_PATH_MAX])
{
	struct mlx5ctl_dev *devs;
	int count, i;

	snprintf(dev_path, DEV_PATH_MAX, "/dev/mlx5ctl-%s", str);
	if (access(dev_path, F_OK) == 0)
		return dev_path;

	if (is_a_number(str)) {
		int ctl_id = atoi(str);

		snprintf(dev_path, DEV_PATH_MAX, "/dev/mlx5ctl-mlx5_core.ctl.%d", ctl_id);
		if (access(dev_path, F_OK) == 0)
			return dev_path;
	}

	devs = _scan_ctl_devs(&count);
	if (devs == NULL)
		return NULL;

	for (i = 0; i < count; i++) {
		if (strcmp(devs[i].mdev, str))
			continue;

		snprintf(dev_path, DEV_PATH_MAX, "/dev/mlx5ctl-%s", devs[i].ctldev);
		free(devs);
		return dev_path;
	}

	free(devs);
	return NULL;
}

struct mlx5u_dev *mlx5u_open(const char *name)
{
	char dev_path[DEV_PATH_MAX];
        struct mlx5u_dev *dev;
        int fd;

	dev = malloc(sizeof(*dev));
	if (!dev)
		return NULL;

	dbg_msg(1, "looking for dev %s\n", name);
	if (find_dev(name, dev_path) == NULL) {
		err_msg("device %s not found\n", name);
		free(dev);
		return NULL;
	}

	strncpy(dev->devname, dev_path, sizeof(dev->devname));
	dbg_msg(1, "opening %s\n", dev->devname);



	fd = open(dev->devname, O_RDWR);
	if (fd < 0) {
		err_msg("open %s failed %d errno(%d): %s\n", dev->devname, fd, errno, strerror(errno));
		err_msg("please insmod mlx5ctl.ko and make sure the device file exists\n");
		free(dev);
		return NULL;
	}
	dev->fd = fd;
	dbg_msg(1, "opened %s descriptor fd(%d)\n", dev->devname, fd);
	return dev;
}


void mlx5u_close(struct mlx5u_dev *dev)
{
	close(dev->fd);
	free(dev);
}

int main(int argc, char *argv[])
{
	struct mlx5u_dev *dev;
	int ret;

	dev = mlx5u_open(argv[1]);
	if (!dev) {
		err_msg("Failed to open device %s\n", argv[1]);
		return 1;
	}
    ret = mlx5u_devinfo(dev);

	mlx5u_close(dev);

	return ret;
}
