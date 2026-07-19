/*
 * packaging_smoke.c — minimal C client for the mstflint SDK packaging tests.
 *
 * Compiled BY THE TEST (test_build_flags.py) against the headers and library
 * of the package variant under test, then run against a live device. Proves,
 * for a relocated/renamed install, that:
 *   - the public headers compile from the variant includedir,
 *   - the client links and the loader resolves the .so from the variant libdir,
 *   - the compiled-in PRM database path (DATA_PATH, derived from the variant
 *     datadir) resolves at runtime — mstInitRegisterMap parses the .adb.
 *
 * Build (done by the test):
 *   gcc -O2 -o packaging_smoke packaging_smoke.c \
 *       -I<includedir>/mstflint/sdk \
 *       -L<libdir>/mstflint/sdk -lmstflint_sdk \
 *       -Wl,-rpath,<libdir>/mstflint/sdk -Wl,--allow-shlib-undefined
 *
 * Run:  sudo ./packaging_smoke <bdf>     exit 0 = MGIR read with >= 50 fields
 */
#include <stdio.h>
#include <mft_sdk/mft_sdk.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "usage: packaging_smoke <device-bdf>\n");
        return 2;
    }
    const char* deviceId = argv[1];

    MstDevice dev = NULL;
    MstStatus rc = mstGetDeviceHandle(&dev, deviceId);
    if (rc != MST_SUCCESS)
    {
        fprintf(stderr, "mstGetDeviceHandle(%s) failed, status=%d\n", deviceId, rc);
        return 1;
    }

    MstPrmRegisterMap regMap;
    rc = mstInitRegisterMap(dev, "MGIR", &regMap);
    if (rc != MST_SUCCESS)
    {
        /* Most likely failure for a relocated package: DATA_PATH does not
         * resolve, i.e. the PRM .adb is not where the .so expects it. */
        fprintf(stderr, "mstInitRegisterMap(MGIR) failed, status=%d "
                        "(PRM db not found at the compiled-in DATA_PATH?)\n", rc);
        mstReleaseDeviceHandle(dev);
        return 1;
    }

    rc = mstSendPRMRegister(dev, &regMap, MST_PRM_GET);
    if (rc != MST_SUCCESS)
    {
        fprintf(stderr, "mstSendPRMRegister(MGIR, GET) failed, status=%d\n", rc);
        mstFreePrmRegisterMap(&regMap);
        mstReleaseDeviceHandle(dev);
        return 1;
    }

    printf("MGIR @ %s: %u fields\n", deviceId, regMap.number_of_fields);
    int ok = regMap.number_of_fields >= 50;

    mstFreePrmRegisterMap(&regMap);
    mstReleaseDeviceHandle(dev);
    return ok ? 0 : 1;
}
