/*
 * Copyright(c) 2026 NVIDIA CORPORATION & AFFILIATES.All rights reserved.
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


/*
NVML API Reference

The NVIDIA Management Library (NVML) is a C-based programmatic interface for monitoring and
managing various states within NVIDIA Tesla &tm; GPUs. It is intended to be a platform for building
3rd party applications, and is also the underlying library for the NVIDIA-supported nvidia-smi
tool. NVML is thread-safe so it is safe to make simultaneous NVML calls from multiple threads.

API Documentation

Supported platforms:
- Windows:     Windows Server 2008 R2 64bit, Windows Server 2012 R2 64bit, Windows 7 64bit, Windows 8 64bit, Windows 10 64bit
- Linux:       32-bit and 64-bit
- Hypervisors: Windows Server 2008R2/2012 Hyper-V 64bit, Citrix XenServer 6.2 SP1+, VMware ESX 5.1/5.5

Supported products:
- Full Support
    - All Tesla products, starting with the Fermi architecture
    - All Quadro products, starting with the Fermi architecture
    - All vGPU Software products, starting with the Kepler architecture
    - Selected GeForce Titan products
- Limited Support
    - All Geforce products, starting with the Fermi architecture

The NVML library can be found at \%ProgramW6432\%\\"NVIDIA Corporation"\\NVSMI\\ on Windows. It is
not be added to the system path by default. To dynamically link to NVML, add this path to the PATH
environmental variable. To dynamically load NVML, call LoadLibrary with this path.

On Linux the NVML library will be found on the standard library path. For 64 bit Linux, both the 32 bit
and 64 bit NVML libraries will be installed.

Online documentation for this library is available at http://docs.nvidia.com/deploy/nvml-api/index.html
*/

#ifndef __nvml_nvml_h__
#define __nvml_nvml_h__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * On Windows, set up methods for DLL export
 * define NVML_STATIC_IMPORT when using nvml_loader library
 */
#if defined(_WINDOWS) || defined(_WIN32)
    #if !defined NVML_STATIC_IMPORT
        #if defined NVML_LIB_EXPORT
            #define DECLDIR __declspec(dllexport)
        #else
            #define DECLDIR __declspec(dllimport)
        #endif
    #else
        #define DECLDIR
    #endif
#else
    #define DECLDIR
#endif

/*
 * Deprecation definition.
 */
#if defined(_WINDOWS) || defined(_WIN32)
   #define DEPRECATED(ver) __declspec(deprecated)
#else
   #define DEPRECATED(ver) __attribute__((deprecated))
#endif

/**
 * NVML API versioning support
 */
#define NVML_API_VERSION            13      //!< NVML API version identifier.
#define NVML_API_VERSION_STR        "13"    //!< NVML API version identifier as a string.
/**
 * Defining NVML_NO_UNVERSIONED_FUNC_DEFS will disable "auto upgrading" of APIs.
 * e.g. the user will have to call nvmlInit_v2 instead of nvmlInit. Enable this
 * guard if you need to support older versions of the API
 */
#ifndef NVML_NO_UNVERSIONED_FUNC_DEFS
    #define nvmlInit                                    nvmlInit_v2
    #define nvmlDeviceGetPciInfo                        nvmlDeviceGetPciInfo_v3
    #define nvmlDeviceGetCount                          nvmlDeviceGetCount_v2
    #define nvmlDeviceGetHandleByIndex                  nvmlDeviceGetHandleByIndex_v2
#endif // #ifndef NVML_NO_UNVERSIONED_FUNC_DEFS

typedef struct nvmlDevice_st* nvmlDevice_t;

/**
 * Buffer size guaranteed to be large enough for pci bus id
 */
#define NVML_DEVICE_PCI_BUS_ID_BUFFER_SIZE      32 //!< Buffer size for PCI bus ID.

/**
 * Buffer size guaranteed to be large enough for pci bus id for \p busIdLegacy
 */
#define NVML_DEVICE_PCI_BUS_ID_BUFFER_V2_SIZE   16 //!< Buffer size for legacy PCI bus ID.

/**
 * PCI information about a GPU device.
 */
typedef struct nvmlPciInfo_st
{
    char busIdLegacy[NVML_DEVICE_PCI_BUS_ID_BUFFER_V2_SIZE]; //!< The legacy tuple domain:bus:device.function PCI identifier (&amp; NULL terminator)
    unsigned int domain;             //!< The PCI domain on which the device's bus resides, 0 to 0xffffffff
    unsigned int bus;                //!< The bus on which the device resides, 0 to 0xff
    unsigned int device;             //!< The device's id on the bus, 0 to 31
    unsigned int pciDeviceId;        //!< The combined 16-bit device id and 16-bit vendor id

    // Added in NVML 2.285 API
    unsigned int pciSubSystemId;     //!< The 32-bit Sub System Device ID

    char busId[NVML_DEVICE_PCI_BUS_ID_BUFFER_SIZE]; //!< The tuple domain:bus:device.function PCI identifier (&amp; NULL terminator)
} nvmlPciInfo_t;

/**
 * Return values for NVML API calls.
 */
typedef enum nvmlReturn_enum
{
    // cppcheck-suppress *
    NVML_SUCCESS = 0,                          //!< The operation was successful
    NVML_ERROR_UNINITIALIZED = 1,              //!< NVML was not first initialized with nvmlInit()
    NVML_ERROR_INVALID_ARGUMENT = 2,           //!< A supplied argument is invalid
    NVML_ERROR_NOT_SUPPORTED = 3,              //!< The requested operation is not available on target device
    NVML_ERROR_NO_PERMISSION = 4,              //!< The current user does not have permission for operation
    NVML_ERROR_ALREADY_INITIALIZED = 5,        //!< Deprecated: Multiple initializations are now allowed through ref counting
    NVML_ERROR_NOT_FOUND = 6,                  //!< A query to find an object was unsuccessful
    NVML_ERROR_INSUFFICIENT_SIZE = 7,          //!< An input argument is not large enough
    NVML_ERROR_INSUFFICIENT_POWER = 8,         //!< A device's external power cables are not properly attached
    NVML_ERROR_DRIVER_NOT_LOADED = 9,          //!< NVIDIA driver is not loaded
    NVML_ERROR_TIMEOUT = 10,                   //!< User provided timeout passed
    NVML_ERROR_IRQ_ISSUE = 11,                 //!< NVIDIA Kernel detected an interrupt issue with a GPU
    NVML_ERROR_LIBRARY_NOT_FOUND = 12,         //!< NVML Shared Library couldn't be found or loaded
    NVML_ERROR_FUNCTION_NOT_FOUND = 13,        //!< Local version of NVML doesn't implement this function
    NVML_ERROR_CORRUPTED_INFOROM = 14,         //!< infoROM is corrupted
    NVML_ERROR_GPU_IS_LOST = 15,               //!< The GPU has fallen off the bus or has otherwise become inaccessible
    NVML_ERROR_RESET_REQUIRED = 16,            //!< The GPU requires a reset before it can be used again
    NVML_ERROR_OPERATING_SYSTEM = 17,          //!< The GPU control device has been blocked by the operating system/cgroups
    NVML_ERROR_LIB_RM_VERSION_MISMATCH = 18,   //!< RM detects a driver/library version mismatch
    NVML_ERROR_IN_USE = 19,                    //!< An operation cannot be performed because the GPU is currently in use
    NVML_ERROR_MEMORY = 20,                    //!< Insufficient memory
    NVML_ERROR_NO_DATA = 21,                   //!< No data
    NVML_ERROR_VGPU_ECC_NOT_SUPPORTED = 22,    //!< The requested vgpu operation is not available on target device, becasue ECC is enabled
    NVML_ERROR_INSUFFICIENT_RESOURCES = 23,    //!< Ran out of critical resources, other than memory
    NVML_ERROR_FREQ_NOT_SUPPORTED = 24,        //!< Ran out of critical resources, other than memory
    NVML_ERROR_ARGUMENT_VERSION_MISMATCH = 25, //!< The provided version is invalid/unsupported
    NVML_ERROR_DEPRECATED  = 26,               //!< The requested functionality has been deprecated
    NVML_ERROR_NOT_READY = 27,                 //!< The system is not ready for the request
    NVML_ERROR_GPU_NOT_FOUND = 28,             //!< No GPUs were found
    NVML_ERROR_INVALID_STATE = 29,             //!< Resource not in correct state to perform requested operation
    NVML_ERROR_RESET_TYPE_NOT_SUPPORTED = 30,  //!< Reset not supported for given device/parameters
    NVML_ERROR_UNKNOWN = 999                   //!< An internal driver error occurred
} nvmlReturn_t;

/**
 * @brief Initialize the NVML Library lazily, without allocating any device state.
 *
 * This will initialize the NVML Library state without enumerating any discovered
 * devices. This will allow NVML to communicate with a device, even if other devices
 * are in an unstable or bad state. Enumeration of a device can be done by obtaining
 * the device handle via the nvmlDeviceGetHandleBy* class of APIs.
 *
 * This method needs to be called once before any usage of NVML Library APIs.
 *
 * %ALL_PRODUCTS%
 *
 * @return
 * - \ref NVML_SUCCESS                   if the NVML Library was properly initialized.
 * - \ref NVML_ERROR_DRIVER_NOT_LOADED   if the NVIDIA driver is not running.
 * - \ref NVML_ERROR_NO_PERMISSION       if the NVML Library does not have permission to talk to the driver.
 * - \ref NVML_ERROR_UNKNOWN             if there is an unexpected error.
 *
 * @note  A reference count of the number of initializations is maintained, and
 *        a corresponding call to \ref nvmlShutdown() needs to be issued once usage
 *        of the NVML Library is complete. Shutdown will only occur after the
 *        reference count reaches zero.
 *
 * @see nvmlShutdown()
 */
nvmlReturn_t DECLDIR nvmlInit_v2(void);

/**
 * @brief Shut down and cleanup NVML Library state.
 *
 * This will shut down and cleanup NVML Library state by releasing all device and
 * library resources previously allocated with \ref nvmlInit_v2() or \ref nvmlInitWithFlags().
 * This should be called after all NVML work is done, and once for each call to
 * \ref nvmlInit_v2() or \ref nvmlInitWithFlags().
 *
 * Complete shutdown will only occur when the reference count of all prior NVML
 * initializations reaches zero. No error will be reported if this is called
 * more times than \ref nvmlInit_v2() or \ref nvmlInitWithFlags().
 *
 * %ALL_PRODUCTS%
 *
 * @return
 * - \ref NVML_SUCCESS                 if the NVML Library was properly shut down.
 * - \ref NVML_ERROR_UNINITIALIZED     if the NVML Library was not previously initialized.
 * - \ref NVML_ERROR_UNKNOWN           if there is an unexpected error.
 */
nvmlReturn_t DECLDIR nvmlShutdown(void);

/**
 * Helper method for converting NVML error codes into readable strings.
 *
 * %ALL_PRODUCTS%
 *
 * @param result                               NVML error code to convert
 *
 * @return String representation of the error.
 *
 */
const DECLDIR char* nvmlErrorString(nvmlReturn_t result);

/**
 * Retrieves the number of compute devices in the system. A compute device is a single GPU.
 *
 * %ALL_PRODUCTS%
 *
 * Note: New nvmlDeviceGetCount_v2 (default in NVML 5.319) returns count of all devices in the system
 *       even if nvmlDeviceGetHandleByIndex_v2 returns NVML_ERROR_NO_PERMISSION for such device.
 *       Update your code to handle this error, or use NVML 4.304 or older nvml header file.
 *       For backward binary compatibility reasons _v1 version of the API is still present in the shared
 *       library.
 *       Old _v1 version of nvmlDeviceGetCount doesn't count devices that NVML has no permission to talk to.
 *
 * @param deviceCount                          Reference in which to return the number of accessible devices
 *
 * @return
 *         - \ref NVML_SUCCESS                 if \a deviceCount has been set
 *         - \ref NVML_ERROR_UNINITIALIZED     if the library has not been successfully initialized
 *         - \ref NVML_ERROR_INVALID_ARGUMENT  if \a deviceCount is NULL
 *         - \ref NVML_ERROR_UNKNOWN           on any unexpected error
 */
nvmlReturn_t DECLDIR nvmlDeviceGetCount_v2(unsigned int *deviceCount);

/**
 * Acquire the handle for a particular device, based on its index.
 *
 * %ALL_PRODUCTS%
 *
 * Valid indices are derived from the \a accessibleDevices count returned by
 *   \ref nvmlDeviceGetCount_v2(). For example, if \a accessibleDevices is 2 the valid indices
 *   are 0 and 1, corresponding to GPU 0 and GPU 1.
 *
 * The order in which NVML enumerates devices has no guarantees of consistency between reboots. For that reason it
 *   is recommended that devices be looked up by their PCI ids or UUID. See
 *   \ref nvmlDeviceGetHandleByUUID() and \ref nvmlDeviceGetHandleByPciBusId_v2().
 *
 * Note: The NVML index may not correlate with other APIs, such as the CUDA device index.
 *
 * Starting from NVML 5, this API causes NVML to initialize the target GPU
 * NVML may initialize additional GPUs if:
 *  - The target GPU is an SLI slave
 *
 * Note: New nvmlDeviceGetCount_v2 (default in NVML 5.319) returns count of all devices in the system
 *       even if nvmlDeviceGetHandleByIndex_v2 returns NVML_ERROR_NO_PERMISSION for such device.
 *       Update your code to handle this error, or use NVML 4.304 or older nvml header file.
 *       For backward binary compatibility reasons _v1 version of the API is still present in the shared
 *       library.
 *       Old _v1 version of nvmlDeviceGetCount doesn't count devices that NVML has no permission to talk to.
 *
 *       This means that nvmlDeviceGetHandleByIndex_v2 and _v1 can return different devices for the same index.
 *       If you don't touch macros that map old (_v1) versions to _v2 versions at the top of the file you don't
 *       need to worry about that.
 *
 * @param index                                The index of the target GPU, >= 0 and < \a accessibleDevices
 * @param device                               Reference in which to return the device handle
 *
 * @return
 *         - \ref NVML_SUCCESS                  if \a device has been set
 *         - \ref NVML_ERROR_UNINITIALIZED      if the library has not been successfully initialized
 *         - \ref NVML_ERROR_INVALID_ARGUMENT   if \a index is invalid or \a device is NULL
 *         - \ref NVML_ERROR_INSUFFICIENT_POWER if any attached devices have improperly attached external power cables
 *         - \ref NVML_ERROR_NO_PERMISSION      if the user doesn't have permission to talk to this device
 *         - \ref NVML_ERROR_IRQ_ISSUE          if NVIDIA kernel detected an interrupt issue with the attached GPUs
 *         - \ref NVML_ERROR_GPU_IS_LOST        if the target GPU has fallen off the bus or is otherwise inaccessible
 *         - \ref NVML_ERROR_UNKNOWN            on any unexpected error
 *
 * @see nvmlDeviceGetIndex
 * @see nvmlDeviceGetCount
 */
nvmlReturn_t DECLDIR nvmlDeviceGetHandleByIndex_v2(unsigned int index, nvmlDevice_t *device);

/**
 * Retrieves the PCI attributes of this device.
 *
 * %ALL_PRODUCTS%
 *
 * See \ref nvmlPciInfo_t for details on the available PCI info.
 *
 * @param device                               The identifier of the target device
 * @param pci                                  Reference in which to return the PCI info
 *
 * @return
 *         - \ref NVML_SUCCESS                 if \a pci has been populated
 *         - \ref NVML_ERROR_UNINITIALIZED     if the library has not been successfully initialized
 *         - \ref NVML_ERROR_INVALID_ARGUMENT  if \a device is invalid or \a pci is NULL
 *         - \ref NVML_ERROR_GPU_IS_LOST       if the target GPU has fallen off the bus or is otherwise inaccessible
 *         - \ref NVML_ERROR_UNKNOWN           on any unexpected error
 */
nvmlReturn_t DECLDIR nvmlDeviceGetPciInfo_v3(nvmlDevice_t device, nvmlPciInfo_t *pci);

#define NVML_PRM_DATA_MAX_SIZE 496 //!< Maximum size of the PRM data.
/**
 * Main PRM input structure
 */
typedef struct
{
    /* I/O parameters */
    unsigned dataSize;                                  //!< Size of the input TLV data.
    unsigned status;                                    //!< OUT: status of the PRM command
    union {
        /* Input data in TLV format */
        unsigned char inData[NVML_PRM_DATA_MAX_SIZE];   //!< IN: Input data in TLV format
        /* Output data in TLV format */
        unsigned char outData[NVML_PRM_DATA_MAX_SIZE];  //!< OUT: Output PRM data in TLV format
    };
} nvmlPRMTLV_v1_t;

/**
 * Read or write a GPU PRM register. The input is assumed to be in TLV format in
 * network byte order.
 *
 * %BLACKWELL_OR_NEWER%
 *
 * Supported on Linux only.
 *
 * @param device                                        Identifer of target GPU device
 * @param buffer                                        Structure holding the input data in TLV format as well as
 *                                                      the PRM register contents in TLV format (in the case of a successful
 *                                                      read operation).
 *                                                      Note: the input data and any returned data shall be in network byte order.
 *
 * @return
 *        - \ref NVML_SUCCESS                           on success
 *        - \ref NVML_ERROR_INVALID_ARGUMENT            if \p device or \p buffer are invalid
 *        - \ref NVML_ERROR_NO_PERMISSION               if user does not have permission to perform this operation
 *        - \ref NVML_ERROR_NOT_SUPPORTED               if this feature is not supported by the device
 */
nvmlReturn_t DECLDIR nvmlDeviceReadWritePRM_v1(nvmlDevice_t device, nvmlPRMTLV_v1_t *buffer);

#if defined(NVML_NO_UNVERSIONED_FUNC_DEFS)
// We don't define APIs to run new versions if this guard is present so there is
// no need to undef
#elif defined(__NVML_API_VERSION_INTERNAL)
#undef nvmlDeviceGetPciInfo
#undef nvmlDeviceGetCount
#undef nvmlDeviceGetHandleByIndex
#undef nvmlInit
#endif

#ifdef __cplusplus
}
#endif

#endif
