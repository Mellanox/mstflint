/*
 * Copyright (c) 2020-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "mft_sdk/mft_sdk.h"
#include "mlxlink/modules/mlxlink_fields.h"
#include "mlxreg/mlxreg_fields.h"

#include <stddef.h>
#include <stdint.h>

// FEC Histogram field names (test-only, not part of mlxlink production headers)
static const char* const FIELD_HISTOGRAM_OF_FEC_ERRORS = "Histogram of FEC Errors";

#ifdef __cplusplus
extern "C"
{
#endif

    /* Field descriptor for table-driven printing.
     * fieldType — how to read/format the value at `offset`:
     *   0 = operational-info enum (capabilityBit selects the display-name table
     *       in test_utils.cpp — deliberately not MlxlinkMaps, see the comment there)
     *   1 = uint16_t              2 = double "%.01f"      3 = uint32_t
     *   4 = ScientificNotation    5 = per-lane errors     6 = temperature "%dC"
     *   7 = voltage "%.4fV"       9 = uint8_t             10 = per-lane ScientificNotation
     */
    typedef struct
    {
        uint32_t capabilityBit;
        const char* displayName;
        size_t offset;
        int fieldType;
    } FieldDescriptor;

#define NUM_OP_INFO_FIELDS 7
#define NUM_COUNTER_FIELDS 10
#define NUM_DDM_FIELDS 2

    const FieldDescriptor* getOpInfoFields(void);
    const FieldDescriptor* getCounterFields(void);
    const FieldDescriptor* getDDMFields(void);

    /**
     * Convert a struct field to its display string (mlxlink-compatible).
     * Handles operational info enums, counter numerics, etc.
     * based on the FieldDescriptor's structType and capabilityBit.
     */
    const char* fieldValueToString(const void* structPtr, const FieldDescriptor* field);

    /**
     * Format a histogram bin range string in mlxlink-compatible format.
     * Returns "[X]" when minRange == maxRange, or "[X:Y]" otherwise.
     * The returned pointer is valid until the next call (thread-local buffer).
     */
    const char* histogramBinRangeToString(uint32_t minRange, uint32_t maxRange);

#define FIELD_TYPE_HEX_U32 8

    /**
     * Convert a uint32_t register field value to a hex display string ("0x%x").
     * Wraps fieldValueToString with FIELD_TYPE_HEX_U32.
     * The returned pointer is valid until the next call (thread-local buffer).
     */
    const char* fieldValueToHexString(uint32_t value);

    /**
     * Convert a MstPrmAccessType enum to its display string (RO/WO/RW/INDEX/OP).
     */
    const char* accessTypeToString(MstPrmAccessType accessType);

#ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus
#include <cstdio>
#include <cstdlib>
#include <string>

/*
 * Class: EnvVarGuard
 * ------------------------------
 * RAII guard for environment variables: sets `name` to `value` and restores
 * the previous value (or unsets) on destruction. Shared by every test TU
 * linked into the unified/so binaries. (sdk_test.cpp keeps a local copy on
 * purpose: the standalone sdk-test binary has no test-utils dependency.)
 */
class EnvVarGuard
{
public:
    EnvVarGuard(const std::string& name, const std::string& value) : name_(name)
    {
        const char* old = std::getenv(name.c_str());
        if (old)
        {
            oldValue_ = old;
            hadOld_ = true;
        }
        setenv(name.c_str(), value.c_str(), 1);
    }

    ~EnvVarGuard()
    {
        if (hadOld_)
        {
            setenv(name_.c_str(), oldValue_.c_str(), 1);
        }
        else
        {
            unsetenv(name_.c_str());
        }
    }

private:
    std::string name_;
    std::string oldValue_;
    bool hadOld_ = false;
};

extern std::string g_devicePci;
extern std::string g_port; // empty => device default port

/**
 * Parse "-d DEVICE" and optional "-p PORT" from argv into g_devicePci / g_port.
 * Prepends "0000:" to the device when it contains ':' but lacks the domain prefix.
 */
void parseDevicePciArg(int argc, char** argv);

// Build a telemetry context targeting g_port (empty g_port => device default port).
inline MstTelemetryContext makeTelemetryContext()
{
    MstTelemetryContext context;
    MST_TELEMETRY_CONTEXT_INIT(&context);
    if (!g_port.empty())
    {
        snprintf(context.label_port, sizeof(context.label_port), "%s", g_port.c_str());
    }
    return context;
}
#endif

#endif /* TEST_UTILS_H */
