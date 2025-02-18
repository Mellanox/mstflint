#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <nvml.h>
#include "mtcr_nvml.h"
#include "mtcr_gpu.h"
#include "mtcr_common.h"

#define MY_DLSYM(dl_ctx, func_name)                               \
    do                                                            \
    {                                                             \
        const char* dl_error;                                     \
        dl_ctx->func_name = dlsym(dl_ctx->dl_handle, #func_name); \
        if ((dl_error = dlerror()) != NULL)                       \
        {                                                         \
            DBG_PRINTF(dl_error);                                 \
            return -1;                                            \
        }                                                         \
    } while (0)

typedef void* (*f_nvmlDeviceGetHandleByIndex_v2)(int, nvmlDevice_t*);
typedef nvmlReturn_t (*f_nvmlDeviceGetPciInfo_v3)(nvmlDevice_t, nvmlPciInfo_t*);
typedef const char* (*f_nvmlErrorString)(nvmlReturn_t);
typedef nvmlReturn_t (*f_nvmlInit_v2)(void);
typedef nvmlReturn_t (*f_nvmlShutdown)(void);

typedef struct nvml_dll_ctx_t {
    void                          * dl_handle;
    f_nvmlShutdown                  nvmlShutdown;
    f_nvmlInit_v2                   nvmlInit_v2;
    f_nvmlDeviceGetHandleByIndex_v2 nvmlDeviceGetHandleByIndex_v2;
    f_nvmlDeviceGetPciInfo_v3       nvmlDeviceGetPciInfo_v3;
    f_nvmlErrorString               nvmlErrorString;
} nvml_dll_ctx;

int init_nvml_lib_handle(mfile* mf)
{
    nvml_dll_ctx* nvml_ctx = NULL;

    if (!(nvml_ctx = (nvml_dll_ctx*)malloc(sizeof(nvml_dll_ctx)))) {
        DBG_PRINTF("Failed to allocate nvml_ctx");
        return -1;
    }
    memset(nvml_ctx, 0, sizeof(nvml_ctx));

    nvml_ctx->dl_handle = dlopen("libnvidia-ml.so", RTLD_LAZY);

    if (!nvml_ctx->dl_handle) {
        printf("Failed to load libnvidia-ml.so, %s\n", dlerror());
        return -1;
    }

    dlerror();

    MY_DLSYM(nvml_ctx, nvmlInit_v2);
    MY_DLSYM(nvml_ctx, nvmlShutdown);
    MY_DLSYM(nvml_ctx, nvmlDeviceGetHandleByIndex_v2);
    MY_DLSYM(nvml_ctx, nvmlDeviceGetPciInfo_v3);
    MY_DLSYM(nvml_ctx, nvmlErrorString);

    mf->ctx = nvml_ctx;
    return 0;
}

u_int16_t nvml_get_pci_id(mfile* mf)
{
    nvmlPciInfo_t pci;

    memset(&pci, 0, sizeof(pci));

    nvml_dll_ctx* nvml_dll_handle = (nvml_dll_ctx*)mf->ctx;
    nvmlReturn_t  ret = nvml_dll_handle->nvmlDeviceGetPciInfo_v3(*(nvmlDevice_t*)mf->nvml_device, &pci);

    if (ret) {
        return -1;
    }
    /* Mask out vendor ID on the lower 16  bits. */
    return ((pci.pciDeviceId & 0xffff0000) >> 16);
}

void free_nvml_lib_handle(mfile* mf)
{
    if (mf && mf->ctx) {
        dlclose(((nvml_dll_ctx*)(mf->ctx))->dl_handle);
        free((nvml_dll_ctx*)mf->ctx);
        mf->ctx = NULL;
    }
}

int nvml_mclose(mfile* mf)
{
    if (mf) {
        close_nvml_ifc(mf);
    }
    return 0;
}


void close_nvml_ifc(mfile* mf)
{
    if (mf) {
        nvml_dll_ctx* nvml_dll_handle = (nvml_dll_ctx*)mf->ctx;
        if (nvml_dll_handle) {
            /* Sutdown NVML SDK. */
            nvml_dll_handle->nvmlShutdown();
        }

        /* Free NVML device handle. */
        free(mf->nvml_device);
        mf->nvml_device = NULL;

        /* Free NVML lib handle. */
        free_nvml_lib_handle(mf);
    }
}

int init_nvml_ifc(mfile* mf, const char* dev_name)
{
    char        *endptr;
    unsigned int device_index;
    char       * device_index_location = strstr(dev_name, "nvidia") + 6;

    device_index = strtoul(device_index_location, &endptr, 10);

    init_nvml_lib_handle(mf);

    mf->nvml_device = malloc(sizeof(nvmlDevice_t));

    if (!mf->nvml_device) {
        DBG_PRINTF("Failed to allocate memory for NVML GPU device");
        return -1;
    }

    nvml_dll_ctx* nvml_dll_handle = (nvml_dll_ctx*)mf->ctx;

    /* Init NVML SDK. */
    nvml_dll_handle->nvmlInit_v2();

    /* Init device handle by index (e.g. /dev/nvidiaX) */
    nvml_dll_handle->nvmlDeviceGetHandleByIndex_v2(device_index, mf->nvml_device);

    if (mf->nvml_device == NULL) {
        printf("Failed to open MVNL GPU device by index: %d\n", device_index);
        return -1;
    }

    return 0;
}

u_int16_t nvml_get_device_id(mfile* mf)
{
    return get_hw_dev_id_by_pci_id(nvml_get_pci_id(mf));
}
