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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/sysmacros.h>
#include <limits.h>
#include <stdint.h>
#include "mtcr.h"
#include "fwctrl_ioctl.h"
#include "dev_mgt/tools_dev_types.c"

#define DEV_NAME_MAX 64

struct fwctl_info_mlx5 {
	__u32 uid;
	__u32 uctx_caps;
};

struct mlx5ctl_dev {
	char ctldev[DEV_NAME_MAX];
	char mdev[DEV_NAME_MAX];
};

/*
 * This function is a wrapper of realpath, which resolves the real path of a given file.
 * It takes a directory file descriptor dirfd, a file path path and a buffer resolved_path to store the resolved path.
 * It temporarily changes the current directory using fchdir, calls realpath, and then restores the original directory.
*/
static char* realpathat(int dirfd, const char *path, char *resolved_path)
{
	int curfd;
	char *ret = NULL;

	curfd = open(".", O_DIRECTORY);
	if (curfd == -1)
    {
		return NULL;
    }

	if (fchdir(dirfd))
    {
		goto out;
    }

	ret = realpath(path, resolved_path);
out:
	fchdir(curfd);
	close(curfd);
	return ret;
}

/*
 * This function checks if a given path corresponds to an MLX5 device.
 * It opens the sysfs directory of the provided path and reads the symbolic link named "device/driver".
 * If the symbolic link does not contain "drivers/mlx5_core", it returns an error.
 * It then retrieves the real path of the device and verifies that it starts with "/sys/devices/".
 * If all checks pass, it constructs paths for control device and parent device.
 */
static int check_fwctl(const char *sysfs_path, struct mlx5ctl_dev *dev)
{
	char tmp[PATH_MAX];
	int sysfs_fd;
	ssize_t ret;

	sysfs_fd = open(sysfs_path, O_DIRECTORY);
	if (sysfs_fd == -1)
    {
		return -1;
    }

	ret = readlinkat(sysfs_fd, "device/driver", tmp, sizeof(tmp));
	if (ret == -1 || ret == sizeof(tmp))
    {
		ret = -1;
		goto out_close;
	}

	if (!strstr(tmp, "drivers/mlx5_core"))
    {
		ret = -1;
		goto out_close;
	}

	if (!realpathat(sysfs_fd, "device", tmp))
    {
		ret = -1;
		goto out_close;
	}

	if (strstr(tmp, "/sys/devices/") != tmp)
    {
		ret = -1;
		goto out_close;
	}

	snprintf(dev->ctldev, sizeof(dev->ctldev), "/dev/fwctl/%s",
		 sysfs_path + strlen("/sys/class/fwctl/"));
	snprintf(dev->mdev, sizeof(dev->mdev), "%s",
		 tmp + strlen("/sys/devices/"));

	ret = 0;

out_close:
	close(sysfs_fd);
	return ret;
}

int main(int argc, char* argv[])
{
	struct stat st;
	struct mlx5ctl_dev dev_desc = {};
	struct fwctl_info_mlx5 info_mlx5 = {};
	struct fwctl_info info = {
		.size = sizeof(info),
		.device_data_len = sizeof(info_mlx5),
		.out_device_data = (uintptr_t)&info_mlx5,
	};
	char sysfs_dev[PATH_MAX];
    char full_path_name[60];
    unsigned int device_id_offset = 0xf0014;
    unsigned int device_id;
	int ret;

    if (argc < 2)
    {
        printf("No device name provided. Exiting.\n");
        return 1;
    }

    char* device_name = argv[1];

    sprintf(full_path_name, "/dev/fwctl/%s", device_name);
    int fd = open(full_path_name, O_RDWR | O_SYNC);
    if (fd < 0)
    {
        printf("Failed to open the device: %s.\n", full_path_name);
        return fd;
    }

	ret = ioctl(fd, FWCTL_INFO, &info);
	if (ret)
    {
		printf("ioctl failed: %d errno(%d): %s\n", ret, errno, strerror(errno));
		return ret;
	}

	if (info.out_device_type != FWCTL_DEVICE_TYPE_MLX5)
    {
		printf("Not a MLX5 device");
		return -1;
	}

	if (fstat(fd, &st))
    {
		return -1;
	}

	snprintf(sysfs_dev, sizeof(sysfs_dev), "/sys/dev/char/%u:%u",
		 major(st.st_rdev), minor(st.st_rdev));
	if (check_fwctl(sysfs_dev, &dev_desc))
    {
		printf("Problem parsing sysfs");
		return -1;
	}

    mfile* mf = mopen(device_name);
    if (!mf)
    {
        printf("Failed to open the device: %s.\n", device_name);
    }

    mread4(mf, device_id_offset, &device_id);

    const char* device_type = dm_dev_hw_id2str(device_id);
    if (!device_type)
    {
        printf("Failed to get device type.\n");
    }

    mclose(mf);

	printf("ctldev: %s\n", full_path_name);
	printf("Parent dev: %s\n", dev_desc.mdev);
	printf("device ID: 0x%x\n", device_id);
	printf("device type: %s\n", device_type);
	printf("UCTX UID: %d\n", info_mlx5.uid);
	printf("UCTX CAP: 0x%x\n", info_mlx5.uctx_caps);
	printf("Current PID: %d FD %d\n", getpid(), fd);

	return 0;
}

