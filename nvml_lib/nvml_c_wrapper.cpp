#include <iostream>
#include <string.h>

#include "nvml_c_wrapper.h"
#include "nvml_device.h"
#include "nvml_exception.h"


unsigned int get_nvml_device_index(const char* device_name)
{
    char  *endptr;
    char   device_name_prefix[] = "/dev/nvidia";
    char * device_index_location = strstr((char*)device_name, device_name_prefix);

    if (device_index_location == nullptr) {
        throw NvmlException("Invalid device name: %s\n", device_name);
    }

    unsigned int device_index = strtoul(device_index_location + (sizeof(device_name_prefix) - 1), &endptr, 10);

    if ((device_index == 0) && (endptr == device_name)) {
        throw NvmlException("Invalid device name: %s\n", device_name);
    }
    return device_index;
}

int init_nvml_device(const char* device_name, void** device_pointer)
{
    try
    {
        unsigned int device_index = get_nvml_device_index(device_name);
        *device_pointer = (void*) new NvmlDevice(device_index);
        return 0;
    }
    catch(const NvmlException& exception)
    {
        std::cout << exception.what() << std::endl;
        return -1;
    }
}

int destroy_nvml_device(void* device_pointer)
{
    try
    {
        if (device_pointer) {
            delete static_cast < NvmlDevice* > (device_pointer);
            device_pointer = nullptr;
        }
    }
    catch(const NvmlException& exception)
    {
        std::cout << exception.what() << std::endl;
        return -1;
    }

    return 0;
}

int nvml_reg_access(unsigned char    * reg_data,
                    const unsigned int reg_size,
                    const unsigned int reg_id,
                    int              * reg_status,
                    bool               is_write,
                    void             * device_pointer)
{
    try
    {
        return static_cast < NvmlDevice * > (device_pointer)->SendPRMRegister(reg_data,
                                                                              reg_size,
                                                                              reg_id,
                                                                              *reg_status,
                                                                              is_write);
    }
    catch(const NvmlException& exception)
    {
        std::cout << exception.what() << std::endl;
        return -1;
    }
}

u_int16_t nvml_get_pci_id(void* device_pointer)
{
    try
    {
        return static_cast < NvmlDevice * > (device_pointer)->GetPciID();
    }
    catch(const NvmlException& exception)
    {
        std::cout << exception.what() << std::endl;
        return -1;
    }
}
