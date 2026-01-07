#ifndef RESET_PARAMETER_DEFS_H
#define RESET_PARAMETER_DEFS_H

#include <set>
#include <tuple>
#include <string>

#define PCI_INDEX_0 0
#define PCI_INDEX_1 1

enum class ResetLevel
{
    LIVE_PATCH = 0x0,
    IMMEDIATE_RESET = 0x1,
    PCI_RESET = 0x3,
    WARM_REBOOT = 0x4,
    UNKNOWN = 0x5
};
enum class ResetType
{
    FULL_CHIP = 0,
    PHY_LESS = 1,
    NIC_ONLY = 2,
    ARM_ONLY = 3,
    ARM_OS_SHUTDOWN = 4,
    NETWORK_RESET = 5,
    UNKNOWN
};
enum class ResetSync
{
    TOOL_FLOW = 0x0,
    DRIVER_FLOW = 0x1,
    FW_FLOW = 0x2,
    UNKNOWN = 0x3
};
enum class ResetMethod
{
    LINK_DISABLE = 0x0,
    HOT_RESET = 0x1,
    UNKNOWN = 0x2
};
enum class ResetLevelBitmask
{
    UNKNOWN = 0x0,
    LIVE_PATCH = 0x1,
    IMMEDIATE_RESET = 0x2,
    PCI_RESET = 0x8,
    WARM_REBOOT = 0x40
};
enum class ResetSyncBitmask
{
    UNKNOWN = 0x0,
    TOOL_FLOW = 0x1,
    DRIVER_FLOW = 0x2,
    FW_FLOW = 0x4
};
enum class ResetMethodBitmask
{
    UNKNOWN = 0x0,
    LINK_DISABLE = 0x1,
    HOT_RESET = 0x2
};
enum class ResetCommandType
{
    UNKNOWN = 0x0,
    QUERY,
    RESET
};
enum class ResetFlowStep
{
    StopNicDriver,
    DisableLinks,
    SendMFRL,
    PreConditionForHotReset,
    HotReset,
    LinkDisableReset,
    PciReset,
    StartNicDriver,
    WaitForReady,
    MSTRestart,
    SaveUptimeBeforeReset,
    CheckUptimeAfterReset
};

struct ResetKey
{
    ResetLevel level;
    ResetType type;
    ResetSync sync;
    ResetMethod method;

    bool operator<(const ResetKey& other) const
    {
        return std::tie(level, type, sync, method) < std::tie(other.level, other.type, other.sync, other.method);
    }
};

struct ResetDeviceParam
{
    std::set<ResetLevel> levelSupported;
    std::set<ResetSync> syncSupported;
    std::set<ResetType> typeSupported;
    std::set<ResetMethod> methodSupported;
};

struct FullResetDeviceParam
{
    struct ResetDeviceParam resetParam;

    ResetLevel defaultLevel;
    ResetType defaultType;
    ResetSync defaultSync;
    ResetMethod defaultMethod;
};

// Returned parameters by the chooser
struct ResetFlowParameters
{
    ResetLevel level;
    ResetType type;
    ResetSync sync;
    ResetMethod method;
};

enum class NicDriverState
{
    WAS_BOUND = 0,
    WAS_UNBOUND
};
enum class HotResetFlow
{
    SINGLE_DEVICE = 0,
    SOCKET_DIRECT = 1,
    DIRECT_NIC = 2,
    UNKNOWN = 3
};
#endif // RESET_PARAMETER_DEFS_H