#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>
#include "include/mtcr_ul/mtcr.h"
#include "mtcr_ul/mtcr_cables.h"
#include "dev_mgt/tools_dev_types.h"
#include "reg_access/reg_access.h"
#include "tools_layouts/reg_access_hca_layouts.h"
#include "tools_layouts/reg_access_switch_layouts.h"
#include "mft_utils/mft_sig_handler.h"
#include "tools_layouts/reg_access_switch_layouts.h"

#ifdef ENABLE_MST_DEV_I2C
#define VMDL_PORT_OFFSET 0xb4
#define VMDL_PORT_TENS_MASK 0x0000000F
#define VMDL_PORT_ONES_MASK 0x00000F00
#define VMDL_PORT_ONES_SHIFT 8
#endif
#define VMDL_DEV_ID 0x80


const std::string TOOL_NAME = "mstcable_discovery";
const std::string MSTFLINT_DEV_DIR = "/dev/mstflint/";

/* mft_signal_set_msg() takes a non-const pointer. */
static char INTERRUPT_MSG[] = "\nInterrupted, Exiting...\n";

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

int isModuleSecondary(mfile* mf, u_int32_t module, bool* isSecondary)
{
    if (!mf || !isSecondary) {
        return -1;
    }

    struct reg_access_switch_pmaos_reg_ext pmaos;
    memset(&pmaos, 0, sizeof(pmaos));
    pmaos.module = module;

    reg_access_status_t rc = reg_access_pmaos(mf, REG_ACCESS_METHOD_GET, &pmaos);
    if (rc) {
        return -1;
    }

    *isSecondary = (pmaos.secondary != 0);
    return 0;
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

void ClearCableDeviceFiles()
{
    DIR* dir = opendir(MSTFLINT_DEV_DIR.c_str());
    if (!dir) {
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, "cable_") == NULL) {
            continue;
        }
        std::string path = MSTFLINT_DEV_DIR + entry->d_name;
        unlink(path.c_str());
    }
    closedir(dir);
}

void CreateCableDeviceFile(const std::string& cable_name)
{
    CreateDirectoryIfNotExist(MSTFLINT_DEV_DIR);
    std::ofstream mstDeviceFile(MSTFLINT_DEV_DIR + cable_name, std::ios::out | std::ios::trunc);
    mstDeviceFile.close();
}

#ifdef ENABLE_MST_DEV_I2C
int discoverVmdlOnI2c(unsigned int& cable_count) {
    dev_info   * devs = NULL;
    int          device_count = 0;
    int          port = 0;
    u_int32_t    port_dword = 0;
    mfile      * cable_mf = NULL;

    // Read directory directly since raw i2c devices are not shown in m_devices_ul
    DIR        * d = opendir("/dev");
    struct dirent* dir;
    while ((dir = readdir(d)) != NULL)
    {
        if (dir->d_name[0] == '.')
        {
            continue;
        }
        if (!strstr(dir->d_name, "i2c-"))
        {
            continue;
        }
    
        port = 0;
        port_dword = 0;
        std::string base_cable_name = std::string(dir->d_name) + "_" + VMDL_DEVICE_STR + std::to_string(port);
        cable_mf = mopen_adv(base_cable_name.c_str(), (MType)(MST_DEFAULT | MST_CABLE));
        if (!cable_mf)
        {
            continue;
        }
        u_int32_t hw_dev_id = 0;
        dm_dev_id_t dm_dev_id = DeviceUnknown;
        get_cable_id(cable_mf, &hw_dev_id, &dm_dev_id);
        if (hw_dev_id != VMDL_DEV_ID)
        {
            mclose(cable_mf);
            continue;
        }
        if (mcables_read4(cable_mf, VMDL_PORT_OFFSET, &port_dword) != 4)
        {
            mclose(cable_mf);
            continue;
        }
        port = ((port_dword & VMDL_PORT_TENS_MASK) * 10) + ((port_dword & VMDL_PORT_ONES_MASK) >> VMDL_PORT_ONES_SHIFT);
        mclose(cable_mf);
        std::string cable_name = std::string(dir->d_name) + "_" + VMDL_DEVICE_STR + std::to_string(port);
        CreateCableDeviceFile(cable_name);
        cable_count++;
    }
    return 0;
}
#endif

int main(int argc, char* argv[])
{
    dev_info   * devs = NULL;
    int          device_count = 0;
    int          num_ports = -1;
    int          verbose = 0;
    int          domain_needed = 0;
    int          ul_mode = 0;
    unsigned int cable_count = 0;

    bool filterSecondary = false;
#ifdef ENABLE_MST_DEV_I2C
    bool discoverVmdlOverI2c = false;
#endif

    for (int argIdx = 1; argIdx < argc; argIdx++)
    {
        std::string arg = argv[argIdx];
        if (arg == "--filter_secondary")
        {
            filterSecondary = true;
        }
#ifdef ENABLE_MST_DEV_I2C
        else if (arg == "--discover_vmdl_on_i2c")
        {
            discoverVmdlOverI2c = 1;
        }
#endif
        else
        {
            std::cout << "Invalid argument: " << arg << std::endl;
            std::cout << "Usage: " << TOOL_NAME << " [--filter_secondary]";
#ifdef ENABLE_MST_DEV_I2C
            std::cout << " [--discover_vmdl_on_i2c]";
#endif
            std::cout << std::endl;
            return 1;
        }
    }

    /* The handler only raises a flag, which lets the in-flight access run to
     * its cleanup and drop the semaphore; we then stop at the next loop boundary,
     * where no semaphore is held. */
    mft_signal_set_msg(INTERRUPT_MSG);
    mft_signal_set_handling(1);

    /* Refresh inventory: drop prior stubs before recreating the current set. */
    ClearCableDeviceFiles();

    devs = mdevices_info_v(MDEVS_TAVOR, &device_count, 1);

    if (!device_count || !devs)
    {
        std::cout << "No supported PCIe devices were found." << std::endl;
        if (devs)
        {
            free(devs);
        }
        mft_restore_and_raise();
        return 0;
    }

    for (int i = 0; i < device_count && !mft_signal_is_fired(); i++)
    {
        mfile* mf = mopen_adv(devs[i].dev_name, (MType)(MST_DEFAULT | MST_CABLE));
        if (!mf)
        {
            continue;
        }

        u_int32_t   hw_id = 0;
        u_int32_t   hw_rev = 0;
        dm_dev_id_t devid_type = DeviceUnknown;
        if (dm_get_device_id(mf, &devid_type, &hw_id, &hw_rev) != GET_DEV_ID_SUCCESS)
        {
            mclose(mf);
            continue;
        }

        if (dm_is_5th_gen_hca(devid_type))
        {
            const int fixed_num_ports = 1;
            num_ports = checkModule(mf, fixed_num_ports);
            if (num_ports == -1)
            {
                mclose(mf);
                continue;
            }
            else
            {
                if (filterSecondary)
                {
                    bool isSecondary = false;
                    if (isModuleSecondary(mf, (u_int32_t)num_ports, &isSecondary) == 0 && isSecondary)
                    {
                        mclose(mf);
                        continue;
                    }
                }
                std::string cable_name = std::string(devs[i].dev_name) + "_" + CABLE_DEVICE_STR + std::to_string(num_ports);
                mfile* cable_mf = mopen_adv(cable_name.c_str(), (MType)(MST_DEFAULT | MST_CABLE));
                if (cable_mf)
                {
                    u_int32_t dev_type = 0;
                    mget_mdevs_type(cable_mf, &dev_type);
                    if (dev_type == MST_CABLE)
                    {
                        CreateCableDeviceFile(cable_name);
                        cable_count++;    
                    }
                    mclose(cable_mf);
                }
            }
        } 
        else if (dm_dev_is_switch(devid_type) && !dm_is_gpu(devid_type))
        {
            num_ports = dm_get_hw_ports_num(devid_type);

            u_int8_t is_vmdl_device = 0;
            const char *device_str = CABLE_DEVICE_STR;
            dm_dev_is_vmdl(mf, devid_type, &is_vmdl_device);  // On failure assume not vmdl device
            if (is_vmdl_device)
            {
                device_str = VMDL_DEVICE_STR;

                struct reg_access_switch_mgpir_ext mgpir;
                memset(&mgpir, 0, sizeof(mgpir));
                reg_access_status_t mgpir_rc = reg_access_mgpir_switch_ext(mf, REG_ACCESS_METHOD_GET, &mgpir);
                if (!mgpir_rc)
                {
                    num_ports = mgpir.hw_info.num_of_modules;
                }
            }
            for (int port = 0; port < num_ports && !mft_signal_is_fired(); port++)
            {
                if (filterSecondary)
                {
                    bool isSecondary = false;
                    if (isModuleSecondary(mf, (u_int32_t)port, &isSecondary) == 0 && isSecondary)
                    {
                        continue;
                    }
                }
                std::string cable_name = std::string(devs[i].dev_name) + "_" + device_str + std::to_string(port);
                mfile     * cable_mf = mopen_adv(cable_name.c_str(), (MType)(MST_DEFAULT | MST_CABLE));
                if (!cable_mf)
                {
                    continue;
                }
                if (is_vmdl_device)
                {
                    u_int32_t hw_dev_id = 0;
                    dm_dev_id_t dm_dev_id = DeviceUnknown;
                    get_cable_id(cable_mf, &hw_dev_id, &dm_dev_id);
                    if (hw_dev_id != VMDL_DEV_ID)
                    {
                        cable_name = std::string(devs[i].dev_name) + "_" + CABLE_DEVICE_STR + std::to_string(port);
                    }
                }

                CreateCableDeviceFile(cable_name);
                cable_count++;
    
                mclose(cable_mf);
            }
        }
        mclose(mf);
    }

    free(devs);
#ifdef ENABLE_MST_DEV_I2C
    if (discoverVmdlOverI2c)
    {
        discoverVmdlOnI2c(cable_count);
    }
#endif

    if (mft_signal_is_fired())
    {
        std::cout << "Interrupted after adding " << cable_count << " NVIDIA cable devices." << std::endl;
    }
    else if (cable_count == 0)
    {
        std::cout << "No supported NVIDIA cables were found." << std::endl;
    }
    else
    {
        std::cout << "Added " << cable_count << " NVIDIA cable devices." << std::endl;
    }

    /* Restores the previous handlers, and - if a signal did fire - re-raises it so
     * the shell sees the tool as interrupted rather than as a clean exit. */
    mft_restore_and_raise();

    return 0;
}
