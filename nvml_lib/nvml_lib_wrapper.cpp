#include <dlfcn.h>
#include <nvml.h>

#include "nvml_exception.h"
#include "nvml_lib_wrapper.h"


NvmlLibWrapper::NvmlLibWrapper(const string libPath) : _libPath(libPath)
{
    _libraryHandle = dlopen(_libPath.c_str(), RTLD_LAZY);
    if (!_libraryHandle) {
        throw NvmlException("Failed to load libnvidia-ml.so, %s\n", dlerror());
    }

    LoadDynamicFuncs();
    InitNvmlSDK();
}

NvmlLibWrapper::~NvmlLibWrapper()
{
    nvmlShutdown();

    if (_libraryHandle) {
        dlclose(_libraryHandle);
        _libraryHandle = nullptr;
    }
}


void NvmlLibWrapper::InitNvmlSDK()
{
    nvmlReturn_t error = nvmlInit_v2();

    if (error) {
        throw NvmlException("Error initializing NVML SDK: %s\n", nvmlErrorString(error));
    }
}

void* NvmlLibWrapper::LoadDynamicFunc(const std::string& functionName)
{
    const char* error;
    void      * funcPointer = nullptr;

    funcPointer = dlsym(_libraryHandle, functionName.c_str());

    if ((error = dlerror()) != nullptr) {
        throw NvmlException("Failed to load dynamic function: %s. error: %s\n", functionName, error);
    }

    return funcPointer;
}

void NvmlLibWrapper::LoadDynamicFuncs()
{
    nvmlInit_v2 = (f_nvmlInit_v2)LoadDynamicFunc("nvmlInit_v2");
    nvmlShutdown = (f_nvmlShutdown)LoadDynamicFunc("nvmlShutdown");
    nvmlDeviceGetHandleByIndex_v2 = (f_nvmlDeviceGetHandleByIndex_v2)LoadDynamicFunc("nvmlDeviceGetHandleByIndex_v2");
    nvmlDeviceGetPciInfo_v3 = (f_nvmlDeviceGetPciInfo_v3)LoadDynamicFunc("nvmlDeviceGetPciInfo_v3");
    nvmlErrorString = (f_nvmlErrorString)LoadDynamicFunc("nvmlErrorString");
    nvmlDeviceReadWritePRM = (f_nvmlDeviceReadWritePRM)LoadDynamicFunc("nvmlDeviceReadWritePRM");
}
