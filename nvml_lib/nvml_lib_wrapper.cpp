#include <dlfcn.h>
#include <nvml.h>

#include "nvml_exception.h"
#include "nvml_lib_wrapper.h"


NvmlLibWrapper::NvmlLibWrapper(const string libPath) : _libPath(libPath)
{
    LoadDynamicLib();
    LoadDynamicFuncs();
    InitNvmlSDK();
}

NvmlLibWrapper::~NvmlLibWrapper()
{
    nvmlShutdown();
    FreeDynamicLib();
}


void NvmlLibWrapper::InitNvmlSDK()
{
    nvmlReturn_t error = nvmlInit_v2();

    if (error)
    {
        throw NvmlException("Error initializing NVML SDK: %s\n", nvmlErrorString(error));
    }
}

void NvmlLibWrapper::LoadDynamicLib()
{
    _libraryHandle = dlopen(_libPath.c_str(), RTLD_LAZY);
    if (!_libraryHandle) {
        throw NvmlException("Failed to load libnvidia-ml.so, %s\n", dlerror());
    }
}

void NvmlLibWrapper::FreeDynamicLib()
{
    if (_libraryHandle) {
        dlclose(_libraryHandle);
        _libraryHandle = nullptr;
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
    try
    {
        nvmlInit = (f_nvmlInit_v2)LoadDynamicFunc("nvmlInit_v2");
        nvmlShutdown = (f_nvmlShutdown)LoadDynamicFunc("nvmlShutdown");
        nvmlDeviceGetCount = (f_nvmlDeviceGetCount_v2)LoadDynamicFunc("nvmlDeviceGetCount_v2");
        nvmlDeviceGetHandleByIndex =
          (f_nvmlDeviceGetHandleByIndex_v2)LoadDynamicFunc("nvmlDeviceGetHandleByIndex_v2");
        nvmlDeviceGetPciInfo =
          (f_nvmlDeviceGetPciInfo_v3)LoadDynamicFunc("nvmlDeviceGetPciInfo_v3");
        nvmlErrorString = (f_nvmlErrorString)LoadDynamicFunc("nvmlErrorString");
        nvmlDeviceReadWritePRM =
          (f_nvmlDeviceReadWritePRM)LoadDynamicFunc("nvmlDeviceReadWritePRM_v1");
    }
    catch (const std::exception& e)
    {
         throw NvmlException(e.what() + string("\nPlease make sure you are using an up to date version of NVML lib."));
    }
}
