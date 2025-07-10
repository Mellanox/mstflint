#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include "include/mtcr_ul/mtcr.h"
#include "mtcr_ul/mtcr_cables.h"
#include "dev_mgt/tools_dev_types.h"
#include "reg_access/reg_access.h"
#include "tools_layouts/reg_access_hca_layouts.h"


int checkModule(mfile* mf, u_int32_t localPort)
{
    int ret = -1;
    if (localPort < 1 || !mf)
    {
        //std::cout << "Invalid local port" << std::endl;
        return ret;
    }

    struct reg_access_hca_pmlp_reg_ext pmlp;
    memset(&pmlp, 0, sizeof(pmlp));
    pmlp.local_port = localPort;
    if (reg_access_pmlp(mf, REG_ACCESS_METHOD_GET, &pmlp))
    {
       // std::cout << "Failed to get module" << std::endl;
    }
    else
    {
        if (pmlp.width)
        {
            ret = pmlp.lane_module_mapping[0].module;
        }
    }

    return ret;
}

int main(int argc, char* argv[])
{
    dev_info* devs = NULL;
    int device_count = 0;
    int num_ports = 0;
    int verbose = 0;
    int domain_needed = 0;
    int ul_mode = 0;

    devs = mdevices_info_v(0xffffffff, &device_count, 0);

    if (!device_count || !devs) {
        printf("\nNo supported PCIe devices were found.\n");
        goto cleanup;
    }

    for (int i = 0; i < device_count; i++) {
        mfile* mf = mopen_adv(devs[i].dev_name, (MType)(MST_DEFAULT | MST_CABLE));
        if (!mf) {
            continue;
        }

        u_int32_t hw_id = 0;
        u_int32_t hw_rev = 0;
        dm_dev_id_t devid_t = DeviceUnknown;
        if (dm_get_device_id(mf, &devid_t, &hw_id, &hw_rev) != GET_DEV_ID_SUCCESS) {
            mclose(mf);
            continue;
        }

        
        if (dm_is_5th_gen_hca(devid_t)) {
            num_ports = 1;
            if (checkModule(mf, num_ports) == -1) {
                mclose(mf);
                continue;
            }
        }

        else {
            num_ports = dm_get_hw_ports_num(devid_t);
        }

        if (num_ports == -1) {
            mclose(mf);
            continue;
        }

        mclose(mf);

        for (int port = 0; port < num_ports; port++) {
            std::string cable_name = std::string(devs[i].dev_name) + "_" + CABLE_DEVICE_STR + std::to_string(port);
            mfile* cable_mf = mopen_adv(cable_name.c_str(), (MType)(MST_DEFAULT | MST_CABLE));
            if (!cable_mf) {
                continue;
            }

            else {
                printf("Cable %s found\n", cable_name.c_str());
            }

            mclose(mf);
        }        
    }

cleanup:
    if (devs) {
        free(devs);
    }

    return 0;
}