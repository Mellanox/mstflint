/*
 * Copyright (c) 2020-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
 */

#include "OperatingSystemAPI.h"

#include <fstream>
#include <stdio.h>
#include <unistd.h>

bool OperatingSystemAPI::FileExists(const std::string& sFilePath)
{
    std::ifstream f(sFilePath.c_str());
    bool bReturn = f.good();
    f.close();
    return bReturn;
}

int OperatingSystemAPI::SuppressStderr()
{
    fflush(stderr);
    int fd = dup(STDERR_FILENO);
    FILE* file = freopen("/dev/null", "w", stderr);
    if (file == NULL) {
        return -1;
    }
    return fd;
}

void OperatingSystemAPI::RestoreStderr(const int fd)
{
    fflush(stderr);
    dup2(fd, fileno(stderr));
    close(fd);
}
