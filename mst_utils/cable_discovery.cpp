#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <iostream>
#include <stdexcept>
#include "include/mtcr_ul/mtcr.h"
#include "mtcr_ul/mtcr_cables.h"
#include "dev_mgt/tools_dev_types.h"
#include "reg_access/reg_access.h"
#include "tools_layouts/reg_access_hca_layouts.h"


const std::string TOOL_NAME = "mstcable_discovery";
const std::string MSTFLINT_DEV_DIR = "/dev/mstflint/";

int checkModule(mfile* mf, u_int32_t localPort)
{
    int ret = -1;

    if ((localPort < 1) || !mf) {
        /*std::cout << "Invalid local port" << std::endl; */
        return ret;
    }

    struct reg_access_hca_pmlp_reg_ext pmlp;

    memset(&pmlp, 0, sizeof(pmlp));
    pmlp.local_port = localPort;
    if (reg_access_pmlp(mf, REG_ACCESS_METHOD_GET, &pmlp)) {
        /* std::cout << "Failed to get module" << std::endl; */
    } else {
        if (pmlp.width) {
            ret = pmlp.lane_module_mapping[0].module;
        }
    }

    return ret;
}

void CreateDirectoryIfNotExist(const std::string& poNewDirectory)
{
    if (mkdir(poNewDirectory.c_str(),
              0777)) {
        switch (errno) {
        case EEXIST:
        case 0:
            return;

        default:
            throw std::runtime_error("Unable to create the directory: " + poNewDirectory + " " + strerror(errno));
            return;
        }
    }
}

int main(int argc, char* argv[])
{
    dev_info   * devs = NULL;
    int          device_count = 0;
    int          num_ports = -1;
    int          verbose = 0;
    int          domain_needed = 0;
    int          ul_mode = 0;
    unsigned int cable_count = 0;

    if (argc > 1)
    {
        std::cout << "Invalid argument: " << argv[1] << std::endl;
        std::cout << "Usage: " << TOOL_NAME << std::endl;
        return 1;
    }

    devs = mdevices_info_v(MDEVS_TAVOR, &device_count, 1);

    if (!device_count || !devs) {
        std::cout << "No supported PCIe devices were found." << std::endl;
        if (devs) {
            free(devs);
        }
    }

    for (int i = 0; i < device_count; i++) {
        mfile* mf = mopen_adv(devs[i].dev_name, (MType)(MST_DEFAULT | MST_CABLE));
        if (!mf) {
            continue;
        }

        u_int32_t   hw_id = 0;
        u_int32_t   hw_rev = 0;
        dm_dev_id_t devid_type = DeviceUnknown;
        if (dm_get_device_id(mf, &devid_type, &hw_id, &hw_rev) != GET_DEV_ID_SUCCESS) {
            mclose(mf);
            continue;
        }


        if (dm_is_5th_gen_hca(devid_type) && !dm_is_bluefield(devid_type)) {
            num_ports = 1;
            if (checkModule(mf, num_ports) == -1) {
                mclose(mf);
                continue;
            }
        } else if (dm_dev_is_switch(devid_type) && !dm_is_gpu(devid_type)) {
            num_ports = dm_get_hw_ports_num(devid_type);
        } else {
            mclose(mf);
            continue;
        }

        mclose(mf);

        for (int port = 0; port < num_ports; port++) {
            std::string cable_name = std::string(devs[i].dev_name) + "_" + CABLE_DEVICE_STR + std::to_string(port);
            mfile     * cable_mf = mopen_adv(cable_name.c_str(), (MType)(MST_DEFAULT | MST_CABLE));
            if (!cable_mf) {
                continue;
            } else {
                CreateDirectoryIfNotExist(MSTFLINT_DEV_DIR);
                std::ofstream mstDeviceFile(MSTFLINT_DEV_DIR + cable_name, std::ios::out | std::ios::trunc);
                mstDeviceFile.close();
                cable_count++;
            }

            mclose(cable_mf);
        }
    }

    if (cable_count == 0) {
        std::cout << "No supported NVIDIA cables were found." << std::endl;
    } else {
        std::cout << "Added " << cable_count << " NVIDIA cable devices." << std::endl;
    }

    return 0;
}
