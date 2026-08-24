/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *  Version: $Id$
 *
 */

/*
 * HCA-capabilities probe: a thin C client over the INSTALLED mstflint SDK, so
 * test_hca_caps_validation.py can read SDK-side values (and provoke SDK-side
 * failures) without MFT's gtest harness -- which is rebuilt and reshipped on
 * MFT's schedule, not this repo's. Modelled on packaging/packaging_smoke.c.
 *
 * Every subcommand prints machine-parseable lines and nothing else:
 *   OK <...> | ERR <op> <status> <last-error-string> | VAL <field> <hex> <dec>
 * and exits 0 on "the SDK behaved", non-zero on "the SDK misbehaved" -- which
 * for the negative subcommands means the CALL SUCCEEDING is the failure.
 *
 * One subcommand per process on purpose: several of these are expected to take
 * the process down on a buggy SDK (null-instance dereference), and a crash must
 * be attributable to exactly one call rather than lose the whole run.
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mft_sdk/mft_sdk.h"
#include "mft_sdk/mft_sdk_types.h"
#include "mft_sdk/mft_sdk_errors.h"
#include "mft_sdk/mft_sdk_discovery.h"
#include "mft_sdk/mft_sdk_hca_caps.h"

#define MAX_FIELDS 32

static const char* errstr(MstDevice dev)
{
    const char* s = dev ? mstGetLastErrorString(dev) : NULL;
    return (s && *s) ? s : "(no error string)";
}

/* Open by fwctl name when the caller gave one ("fwctl0" / "/dev/fwctl/fwctl0"),
 * by BDF-through-fwctl when it looks like a BDF and fwctl was requested, else
 * the plain identifier path (an /dev/mst node, i.e. PCIconf). The three doors
 * behave differently and the gate checks need all three. */
static MstStatus open_dev(const char* ident, int want_fwctl, MstDevice* dev)
{
    unsigned dom = 0, bus = 0, devn = 0, fn = 0;

    if (strstr(ident, "fwctl"))
    {
        return mstGetDeviceHandleByFwctlDeviceName(dev, ident);
    }
    if (want_fwctl)
    {
        MstPciBDF bdf;
        if (sscanf(ident, "%x:%x:%x.%x", &dom, &bus, &devn, &fn) != 4 &&
            sscanf(ident, "%x:%x.%x", &bus, &devn, &fn) == 3)
        {
            dom = 0;
        }
        bdf.domain = dom;
        bdf.bus = bus;
        bdf.device = devn;
        bdf.function = fn;
        return mstGetDeviceHandleByBDF(dev, bdf, FWCtl);
    }
    return mstGetDeviceHandle(dev, ident);
}

/* ---- subcommands ------------------------------------------------------- */

static int cmd_types(MstDevice dev)
{
    char** types = NULL;
    unsigned int n = 0;
    MstStatus st = mstGetCapabilityTypesList(dev, &types, &n);
    unsigned int i;

    if (st != MST_SUCCESS)
    {
        printf("ERR types %d %s\n", (int)st, errstr(dev));
        return 2;
    }
    printf("OK types %u\n", n);
    for (i = 0; i < n; i++)
    {
        printf("TYPE %s\n", types[i]);
    }
    mstFreeHcaCapabilitiesArray(types, n);
    return 0;
}

static int cmd_meta(MstDevice dev, const char* type)
{
    MstHcaCapabilityMetadata meta;
    MstStatus st;
    unsigned int i;

    memset(&meta, 0, sizeof(meta));
    st = mstGetCapabilitiesByType(dev, type, &meta);
    if (st != MST_SUCCESS)
    {
        printf("ERR meta %d %s\n", (int)st, errstr(dev));
        return 2;
    }
    printf("OK meta %s %u\n", type, meta.numberOfFields);
    for (i = 0; i < meta.numberOfFields; i++)
    {
        printf("FIELD %s 0x%x %u %u %d\n", meta.fields[i].name, meta.fields[i].address, meta.fields[i].bitOffset,
               meta.fields[i].bitSize, (int)meta.fields[i].accessType);
    }
    mstFreeHcaCapabilitiesMetadata(&meta);
    return 0;
}

/* query <type> <max|current> [field ...] -- no fields = dump the whole map */
static int cmd_query(MstDevice dev, const char* type, const char* mode, char** fields, int nfields)
{
    MstHcaCapabilityMap map;
    MstCapabilityMode m = (strcmp(mode, "max") == 0) ? MST_CAPABILITY_MODE_MAX : MST_CAPABILITY_MODE_CURRENT;
    MstStatus st;
    int i;
    unsigned int u;

    memset(&map, 0, sizeof(map));
    st = mstInitHcaCapabilityMap(dev, type, &map);
    if (st != MST_SUCCESS)
    {
        printf("ERR init %d %s\n", (int)st, errstr(dev));
        return 2;
    }
    st = mstQueryHcaCapability(dev, type, &map, m, 0, MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    if (st != MST_SUCCESS)
    {
        printf("ERR query %d %s\n", (int)st, errstr(dev));
        mstFreeHcaCapabilityMap(&map);
        return 2;
    }
    printf("OK query %s %s %u\n", type, mode, map.numberOfCapabilities);

    if (nfields == 0)
    {
        for (u = 0; u < map.numberOfCapabilities; u++)
        {
            printf("VAL %s 0x%x %u\n", map.capabilities[u].capabilityName, map.capabilities[u].value,
                   map.capabilities[u].value);
        }
    }
    else
    {
        for (i = 0; i < nfields; i++)
        {
            uint32_t v = 0;
            st = mstGetCapabilityValue(dev, &map, fields[i], &v);
            if (st != MST_SUCCESS)
            {
                printf("MISS %s %d %s\n", fields[i], (int)st, errstr(dev));
                continue;
            }
            printf("VAL %s 0x%x %u\n", fields[i], v, v);
        }
    }
    mstFreeHcaCapabilityMap(&map);
    return 0;
}

/* Every HCA-caps entry point against one handle. Prints one GATE line each so
 * the caller can assert the status AND the message per entry point. */
static int cmd_gate(MstDevice dev)
{
    MstHcaCapabilityMap map;
    MstHcaCapabilityMetadata meta;
    char** types = NULL;
    unsigned int n = 0;
    uint32_t v = 0;
    MstStatus st;

    memset(&map, 0, sizeof(map));
    memset(&meta, 0, sizeof(meta));

    st = mstGetCapabilityTypesList(dev, &types, &n);
    printf("GATE mstGetCapabilityTypesList %d %s\n", (int)st, errstr(dev));
    if (st == MST_SUCCESS)
    {
        mstFreeHcaCapabilitiesArray(types, n);
    }

    st = mstGetCapabilitiesByType(dev, "qos_caps", &meta);
    printf("GATE mstGetCapabilitiesByType %d %s\n", (int)st, errstr(dev));
    if (st == MST_SUCCESS)
    {
        mstFreeHcaCapabilitiesMetadata(&meta);
    }

    st = mstInitHcaCapabilityMap(dev, "qos_caps", &map);
    printf("GATE mstInitHcaCapabilityMap %d %s\n", (int)st, errstr(dev));

    st = mstQueryHcaCapability(dev, "qos_caps", &map, MST_CAPABILITY_MODE_CURRENT, 0,
                               MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    printf("GATE mstQueryHcaCapability %d %s\n", (int)st, errstr(dev));

    st = mstSetHcaCapability(dev, "qos_caps", &map, MST_CAPABILITY_MODE_CURRENT, 0,
                             MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    printf("GATE mstSetHcaCapability %d %s\n", (int)st, errstr(dev));

    (void)v;
    mstFreeHcaCapabilityMap(&map);
    return 0;
}

/* The two entry points that never call initHcaCapabilities(): reached FIRST on
 * a fresh handle they have no HcaCapabilities object to work with. Isolated in
 * its own subcommand because a null-instance dereference takes the process
 * down, and the caller needs to see WHICH call did it. */
static int cmd_first_getvalue(MstDevice dev)
{
    MstHcaCapabilityMap map;
    uint32_t v = 0;
    MstStatus st;

    memset(&map, 0, sizeof(map));
    fflush(stdout);
    st = mstGetCapabilityValue(dev, &map, "packet_pacing_max_rate", &v);
    printf("FIRST mstGetCapabilityValue %d %s\n", (int)st, errstr(dev));
    return st == MST_SUCCESS ? 3 : 0;
}

static int cmd_first_setvalue(MstDevice dev)
{
    MstHcaCapabilityMap map;
    MstStatus st;

    memset(&map, 0, sizeof(map));
    fflush(stdout);
    st = mstSetCapabilityValue(dev, &map, "packet_pacing_max_rate", 0);
    printf("FIRST mstSetCapabilityValue %d %s\n", (int)st, errstr(dev));
    return st == MST_SUCCESS ? 3 : 0;
}

/* Every public entry point with NULL where a pointer is required. No device is
 * opened: MST_ERROR_INVALID_ARGUMENT must come out of the argument check, not
 * out of anything that touched hardware. */
static int cmd_nullargs(void)
{
    MstHcaCapabilityMap map;
    MstHcaCapabilityMetadata meta;
    char** types = NULL;
    unsigned int n = 0;
    uint32_t v = 0;
    int bad = 0;

    memset(&map, 0, sizeof(map));
    memset(&meta, 0, sizeof(meta));

#define WANT_INVALID(label, expr)                                       \
    do                                                                  \
    {                                                                   \
        MstStatus s_ = (expr);                                          \
        printf("NULLARG %s %d\n", label, (int)s_);                      \
        if (s_ != MST_ERROR_INVALID_ARGUMENT)                           \
        {                                                               \
            bad++;                                                      \
        }                                                               \
    } while (0)

    WANT_INVALID("typesList_nulldev", mstGetCapabilityTypesList(NULL, &types, &n));
    WANT_INVALID("typesList_nullarr", mstGetCapabilityTypesList((MstDevice)1, NULL, &n));
    WANT_INVALID("typesList_nullnum", mstGetCapabilityTypesList((MstDevice)1, &types, NULL));
    WANT_INVALID("byType_nulldev", mstGetCapabilitiesByType(NULL, "qos_caps", &meta));
    WANT_INVALID("byType_nullmeta", mstGetCapabilitiesByType((MstDevice)1, "qos_caps", NULL));
    WANT_INVALID("initMap_nulldev", mstInitHcaCapabilityMap(NULL, "qos_caps", &map));
    WANT_INVALID("initMap_nulltype", mstInitHcaCapabilityMap((MstDevice)1, NULL, &map));
    WANT_INVALID("initMap_nullmap", mstInitHcaCapabilityMap((MstDevice)1, "qos_caps", NULL));
    WANT_INVALID("query_nulldev", mstQueryHcaCapability(NULL, "qos_caps", &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                                        MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO));
    WANT_INVALID("set_nulldev", mstSetHcaCapability(NULL, "qos_caps", &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                                    MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO));
    WANT_INVALID("getValue_nulldev", mstGetCapabilityValue(NULL, &map, "x", &v));
    WANT_INVALID("getValue_nullmap", mstGetCapabilityValue((MstDevice)1, NULL, "x", &v));
    WANT_INVALID("getValue_nullname", mstGetCapabilityValue((MstDevice)1, &map, NULL, &v));
    WANT_INVALID("setValue_nulldev", mstSetCapabilityValue(NULL, &map, "x", 0));
    WANT_INVALID("setValue_nullmap", mstSetCapabilityValue((MstDevice)1, NULL, "x", 0));
    WANT_INVALID("setValue_nullname", mstSetCapabilityValue((MstDevice)1, &map, NULL, 0));
    WANT_INVALID("freeMap_null", mstFreeHcaCapabilityMap(NULL));
    WANT_INVALID("freeMeta_null", mstFreeHcaCapabilitiesMetadata(NULL));
    WANT_INVALID("freeArray_null", mstFreeHcaCapabilitiesArray(NULL, 0));
#undef WANT_INVALID

    printf("OK nullargs %d\n", bad);
    return bad ? 4 : 0;
}

/* The two error-string getters, on the paths DOCA actually takes.
 * doca_mgmt.c logs mstGetInitErrorString() with %%s when the handle could not be
 * created, and mstGetLastErrorString(ctx->mst_device) on the mstReleaseDeviceHandle
 * failure path -- neither is NULL-guarded, so a NULL return is a segfault INSIDE
 * DOCA's error handling, i.e. an SDK error becomes a DOCA crash. */
static int cmd_errstrings(void)
{
    const char* init_before = mstGetInitErrorString();
    const char* last_null = mstGetLastErrorString(NULL);
    MstDevice dev = NULL;
    const char* init_after;
    MstStatus st;

    printf("ERRSTR init_before %s\n", init_before ? "nonnull" : "NULL");
    printf("ERRSTR last_nulldev %s\n", last_null ? "nonnull" : "NULL");

    /* A name that cannot exist: the failing-open path DOCA hits on every host
     * without fwctl, and the one whose message DOCA prints. */
    st = mstGetDeviceHandleByFwctlDeviceName(&dev, "fwctl_no_such_device_zz");
    init_after = mstGetInitErrorString();
    printf("ERRSTR open_bad_status %d\n", (int)st);
    printf("ERRSTR init_after %s %s\n", init_after ? "nonnull" : "NULL",
           (init_after && *init_after) ? "nonempty" : "empty");
    if (st == MST_SUCCESS && dev)
    {
        mstReleaseDeviceHandle(dev);
    }
    return (init_before && last_null && init_after && *init_after) ? 0 : 7;
}

/* DOCA's free policy: it calls the free functions on error paths where the
 * structure may only be partially populated, and relies on the SDK NULLing the
 * pointer so its own free-once guard cannot double-free. Zeroed (not NULL)
 * structures must therefore free cleanly, and freeing twice must stay safe. */
static int cmd_freetolerance(void)
{
    MstHcaCapabilityMap map;
    MstHcaCapabilityMetadata meta;
    MstStatus a, b, c, d;

    memset(&map, 0, sizeof(map));
    memset(&meta, 0, sizeof(meta));

    a = mstFreeHcaCapabilityMap(&map);
    b = mstFreeHcaCapabilityMap(&map); /* twice: pointer must have been NULLed */
    c = mstFreeHcaCapabilitiesMetadata(&meta);
    d = mstFreeHcaCapabilitiesMetadata(&meta);
    printf("FREE zeroed_map %d %d meta %d %d map_ptr %s meta_ptr %s\n", (int)a, (int)b, (int)c, (int)d,
           map.capabilities ? "nonnull" : "null", meta.fields ? "nonnull" : "null");
    return (a == MST_SUCCESS && b == MST_SUCCESS && c == MST_SUCCESS && d == MST_SUCCESS && !map.capabilities &&
            !meta.fields)
             ? 0
             : 8;
}

/* DOCA never has the SDK to itself. mgmt_dev_ctx_create_from_devinfo opens its
 * OWN fd on /dev/fwctl/<name> (fwctl_dev_open) and only THEN calls
 * mstGetDeviceHandleByFwctlDeviceName on the same node; destroy releases the SDK
 * handle first and closes DOCA's fd second. So the SDK must tolerate a
 * pre-existing O_RDWR fd on the node, and releasing must leave that fd usable.
 * If the SDK ever took the device exclusively, every doca_mgmt_dev_ctx_create
 * would fail -- 100%, on every host. Takes the BARE node name, as DOCA passes it. */
static int cmd_doca_coexist(const char* fwctl_name)
{
    char path[256];
    int fd;
    MstDevice dev = NULL;
    MstStatus st;
    MstHcaCapabilityMap map;
    uint32_t v = 0;
    int rc = 0;

    if (strncmp(fwctl_name, "/dev/", 5) == 0)
    {
        snprintf(path, sizeof(path), "%s", fwctl_name);
    }
    else
    {
        snprintf(path, sizeof(path), "/dev/fwctl/%s", fwctl_name);
    }
    fd = open(path, O_RDWR);
    if (fd < 0)
    {
        printf("ERR coexist_open %s errno=%d\n", path, errno);
        return 2;
    }
    printf("COEXIST doca_fd_open %s\n", path);

    st = mstGetDeviceHandleByFwctlDeviceName(&dev, fwctl_name);
    printf("COEXIST sdk_open %d %s\n", (int)st, st == MST_SUCCESS ? "ok" : mstGetInitErrorString());
    if (st != MST_SUCCESS || !dev)
    {
        close(fd);
        return 9;
    }

    memset(&map, 0, sizeof(map));
    st = mstInitHcaCapabilityMap(dev, "cmd_hca_cap", &map);
    if (st == MST_SUCCESS)
    {
        st = mstQueryHcaCapability(dev, "cmd_hca_cap", &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                   MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    }
    if (st == MST_SUCCESS)
    {
        st = mstGetCapabilityValue(dev, &map, "vhca_id", &v);
    }
    printf("COEXIST query_while_fd_open %d %s\n", (int)st, st == MST_SUCCESS ? "ok" : errstr(dev));
    rc = (st == MST_SUCCESS) ? rc : 9;
    mstFreeHcaCapabilityMap(&map);

    /* Release order is DOCA's: SDK handle first, DOCA's own fd second. */
    st = mstReleaseDeviceHandle(dev);
    printf("COEXIST sdk_release %d\n", (int)st);

    /* DOCA's fd must still be alive and closable afterwards. */
    if (fcntl(fd, F_GETFD) == -1)
    {
        printf("COEXIST doca_fd_after_release dead errno=%d\n", errno);
        rc = 9;
    }
    else
    {
        printf("COEXIST doca_fd_after_release alive\n");
    }
    printf("COEXIST doca_fd_close %d\n", close(fd));
    return rc;
}

/* DOCA's write shape, replicated exactly: doca_mgmt_raw_hca_cap_modify is
 * mstInitHcaCapabilityMap -> mstSetCapabilityValue on ONLY the caller's fields
 * -> mstSetHcaCapability(MST_CAPABILITY_MODE_MAX, OTHER_FUNCTION_YES), with NO
 * query in between. mstSetHcaCapability pushes back every entry whose `set` flag
 * is true, so "exactly the fields DOCA asked for are flagged" is the property
 * that keeps a DOCA modify from writing capabilities nobody named.
 * The FW write itself is deliberately NOT issued here -- this reports the map
 * state DOCA would hand to it. */
static int cmd_doca_setshape(MstDevice dev, const char* type, const char* field, uint32_t value)
{
    MstHcaCapabilityMap map;
    MstStatus st;
    unsigned int u, flagged = 0, wrong = 0, init_count;

    memset(&map, 0, sizeof(map));
    st = mstInitHcaCapabilityMap(dev, type, &map);
    if (st != MST_SUCCESS)
    {
        printf("ERR init %d %s\n", (int)st, errstr(dev));
        return 2;
    }
    init_count = map.numberOfCapabilities;

    st = mstSetCapabilityValue(dev, &map, field, value);
    if (st != MST_SUCCESS)
    {
        printf("ERR setvalue %d %s\n", (int)st, errstr(dev));
        mstFreeHcaCapabilityMap(&map);
        return 2;
    }
    for (u = 0; u < map.numberOfCapabilities; u++)
    {
        if (!map.capabilities[u].set)
        {
            continue;
        }
        flagged++;
        if (strcmp(map.capabilities[u].capabilityName, field) != 0)
        {
            wrong++;
            if (wrong <= 8)
            {
                printf("STRAY %s 0x%x\n", map.capabilities[u].capabilityName, map.capabilities[u].value);
            }
        }
    }
    printf("OK docasetshape %s %s flagged=%u stray=%u init_count=%u count=%u\n", type, field, flagged, wrong,
           init_count, map.numberOfCapabilities);
    mstFreeHcaCapabilityMap(&map);
    return (flagged == 1 && wrong == 0) ? 0 : 6;
}

/* Contract for a freshly initialised (not yet queried) map: every entry must
 * read back as a DEFINED value, and no entry may already be flagged for
 * write-back -- mstSetHcaCapability writes exactly the flagged ones. */
static int cmd_initstate(MstDevice dev, const char* type)
{
    MstHcaCapabilityMap map;
    MstStatus st;
    unsigned int u, flagged = 0, nonzero = 0;

    memset(&map, 0, sizeof(map));
    st = mstInitHcaCapabilityMap(dev, type, &map);
    if (st != MST_SUCCESS)
    {
        printf("ERR init %d %s\n", (int)st, errstr(dev));
        return 2;
    }
    for (u = 0; u < map.numberOfCapabilities; u++)
    {
        if (map.capabilities[u].set)
        {
            if (flagged < 8)
            {
                printf("PRESET %s 0x%x\n", map.capabilities[u].capabilityName, map.capabilities[u].value);
            }
            flagged++;
        }
        if (map.capabilities[u].value != 0)
        {
            nonzero++;
        }
    }
    printf("OK initstate %s fields=%u preset=%u nonzero_value=%u\n", type, map.numberOfCapabilities, flagged, nonzero);
    mstFreeHcaCapabilityMap(&map);
    return flagged ? 5 : 0;
}

/* Re-query the SAME initialised map N times (trap T5): updateCapabilityMap
 * replaces map.capabilities without freeing the previous array. Reports the RSS
 * delta so the caller can size the leak against the map. */
static int cmd_requery(MstDevice dev, const char* type, int iterations)
{
    MstHcaCapabilityMap map;
    MstStatus st;
    long rss0 = 0, rss1 = 0;
    int i;
    FILE* f;

    memset(&map, 0, sizeof(map));
    st = mstInitHcaCapabilityMap(dev, type, &map);
    if (st != MST_SUCCESS)
    {
        printf("ERR init %d %s\n", (int)st, errstr(dev));
        return 2;
    }
    f = fopen("/proc/self/statm", "r");
    if (f)
    {
        if (fscanf(f, "%*s %ld", &rss0) != 1)
        {
            rss0 = 0;
        }
        fclose(f);
    }
    for (i = 0; i < iterations; i++)
    {
        st = mstQueryHcaCapability(dev, type, &map, MST_CAPABILITY_MODE_CURRENT, 0,
                                   MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
        if (st != MST_SUCCESS)
        {
            printf("ERR query %d %s\n", (int)st, errstr(dev));
            mstFreeHcaCapabilityMap(&map);
            return 2;
        }
    }
    f = fopen("/proc/self/statm", "r");
    if (f)
    {
        if (fscanf(f, "%*s %ld", &rss1) != 1)
        {
            rss1 = 0;
        }
        fclose(f);
    }
    printf("OK requery %s iterations=%d fields=%u rss_pages_delta=%ld entry_bytes=%u\n", type, iterations,
           map.numberOfCapabilities, rss1 - rss0, (unsigned)sizeof(MstHcaCapability));
    mstFreeHcaCapabilityMap(&map);
    return 0;
}

static void usage(void)
{
    fprintf(stderr,
            "usage: hca_caps_probe [--fwctl] <device> <subcommand> [args]\n"
            "  types                      list capability types\n"
            "  meta <type>                field metadata for one type\n"
            "  query <type> <max|current> [field ...]\n"
            "  gate                       every entry point once, status+message each\n"
            "  first-getvalue             mstGetCapabilityValue as the FIRST call\n"
            "  first-setvalue             mstSetCapabilityValue as the FIRST call\n"
            "  initstate <type>           post-init map contract (defined values, nothing flagged)\n"
            "  doca-setshape <type> <field> [value]\n"
            "                             DOCA's modify shape: init -> setValue on ONE field;\n"
            "                             reports how many entries ended up flagged for write-back\n"
            "  requery <type> <n>         re-query one initialised map n times\n"
            "  doca-coexist               open the fwctl node O_RDWR first, THEN the SDK handle\n"
            "                             (DOCA's order); query, release, check the fd survived\n"
            "  nullargs | errstrings | freetolerance   (no device needed)\n");
}

int main(int argc, char** argv)
{
    MstDevice dev = NULL;
    MstStatus st;
    int want_fwctl = 0;
    int a = 1;
    const char* ident;
    const char* cmd;
    int rc;

    if (a < argc && strcmp(argv[a], "--fwctl") == 0)
    {
        want_fwctl = 1;
        a++;
    }

    /* These three open nothing at all. */
    if (a < argc && strcmp(argv[a], "nullargs") == 0)
    {
        return cmd_nullargs();
    }
    if (a < argc && strcmp(argv[a], "errstrings") == 0)
    {
        return cmd_errstrings();
    }
    if (a < argc && strcmp(argv[a], "freetolerance") == 0)
    {
        return cmd_freetolerance();
    }
    /* Opens the fwctl node itself, before and independently of the SDK. */
    if (argc - a >= 2 && strcmp(argv[a + 1], "doca-coexist") == 0)
    {
        return cmd_doca_coexist(argv[a]);
    }
    if (argc - a < 2)
    {
        usage();
        return 1;
    }
    ident = argv[a++];
    cmd = argv[a++];

    st = open_dev(ident, want_fwctl, &dev);
    if (st != MST_SUCCESS || !dev)
    {
        /* The handle itself is the interesting result for the open-path checks. */
        printf("ERR open %d %s\n", (int)st, dev ? errstr(dev) : "(no handle)");
        return 2;
    }
    printf("OK open %s\n", ident);

    if (strcmp(cmd, "types") == 0)
    {
        rc = cmd_types(dev);
    }
    else if (strcmp(cmd, "meta") == 0 && argc - a >= 1)
    {
        rc = cmd_meta(dev, argv[a]);
    }
    else if (strcmp(cmd, "query") == 0 && argc - a >= 2)
    {
        int nf = argc - a - 2;
        rc = cmd_query(dev, argv[a], argv[a + 1], &argv[a + 2], nf > MAX_FIELDS ? MAX_FIELDS : nf);
    }
    else if (strcmp(cmd, "gate") == 0)
    {
        rc = cmd_gate(dev);
    }
    else if (strcmp(cmd, "first-getvalue") == 0)
    {
        rc = cmd_first_getvalue(dev);
    }
    else if (strcmp(cmd, "first-setvalue") == 0)
    {
        rc = cmd_first_setvalue(dev);
    }
    else if (strcmp(cmd, "initstate") == 0 && argc - a >= 1)
    {
        rc = cmd_initstate(dev, argv[a]);
    }
    else if (strcmp(cmd, "doca-setshape") == 0 && argc - a >= 2)
    {
        rc = cmd_doca_setshape(dev, argv[a], argv[a + 1], (uint32_t)strtoul(argc - a >= 3 ? argv[a + 2] : "0", NULL, 0));
    }
    else if (strcmp(cmd, "requery") == 0 && argc - a >= 2)
    {
        rc = cmd_requery(dev, argv[a], atoi(argv[a + 1]));
    }
    else
    {
        usage();
        rc = 1;
    }

    mstReleaseDeviceHandle(dev);
    return rc;
}
