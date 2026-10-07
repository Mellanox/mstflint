/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#ifndef __CABLE_FW_MANAGER_H__
#define __CABLE_FW_MANAGER_H__

#include <map>
#include <string>
#include <vector>

#include "common/compatibility.h"
#include "cmd_line_params.h"

using namespace std;

/* Seconds to let the cables finish switching image before they are verified. A cable slower
 * than this fails verification even though its burn succeeded, so --cable_activation_wait
 * raises it.
 */
#define CABLE_ACTIVATION_WAIT_DEFAULT 60

/* A switch ASIC reachable from this host. */
struct AsicInfo
{
    string devName; // MST device name or PCI address, in the form mopen() accepts
};

/* The switch ASICs of the system, keyed by the Geographical Address each reports in MGIR.
 *
 * The GA is the value MMAM answers with when asked which ASIC owns a given cable, and it is the
 * only way to tell two ASICs of a multi-ASIC system apart, because a module index alone is
 * ambiguous. Keying by it is what makes that lookup a lookup; it also means a system cannot be
 * built with two ASICs at one address, which would otherwise make every cable ambiguous, and it
 * puts the ASICs in address order so that GA 0 - the one the system-wide registers are read from -
 * is simply the first. The count is the map's own size and is not tracked beside it.
 */
typedef map<u_int8_t, AsicInfo> AsicsByGa;

/* Which of the cable's two firmware slots is meant. A cable runs from one slot and an update
 * is written into the other, so a target slot always names where the image is going, never where
 * the cable is running - and phase 5 passes a cable only once that target has become the
 * running slot.
 */
enum CableImageSlot
{
    CABLE_IMAGE_SLOT_A,
    CABLE_IMAGE_SLOT_B
};

/* What phase 3 decided to do with a cable. Every discovered cable gets one of these,
 * including the ones left alone, because the report has to account for every port.
 */
enum CableUpdateAction
{
    // Zero on purpose: an entry nobody has ruled on reads as undecided rather than as an
    // instruction to burn, which is what the first enumerator would otherwise mean.
    CABLE_ACTION_UNDECIDED,
    CABLE_ACTION_UPDATE,
    CABLE_ACTION_SKIP_NOT_PRESENT,
    CABLE_ACTION_SKIP_3RD_PARTY,    // not an NVIDIA cable, or detected as fake
    CABLE_ACTION_SKIP_NOT_BURNABLE, // MCQI reports neither firmware-update procedure
    CABLE_ACTION_SKIP_NO_FW_FILE,   // nothing in the package matched it
    CABLE_ACTION_SKIP_CURRENT       // already running the version the package offers
};

/* A firmware version as the cable reports it. */
struct CableFwVersion
{
    u_int8_t major = 0;
    u_int8_t minor = 0;
    u_int16_t subminor = 0;
};

/* The faceplate number for a cable: what `mlxlink --port` and `flint --downstream_device_ids`
 * take, and the only cable number a report prints. Measured one above the local module index.
 *
 * A function rather than a stored field, because no register this tool reads supplies a label
 * port - MMAM has no label field and PLLP.label_port is indexed by local_port on a single ASIC -
 * so it can only ever be arithmetic, and a stored copy is a second place that can disagree. If a
 * multi-ASIC system turns out to number faceplate labels across the system rather than per ASIC,
 * the offset is added here and nowhere else.
 */
inline u_int32_t cableLabelPort(u_int32_t localIndex)
{
    return localIndex + 1;
}

/* One pluggable cable, addressed by three different index spaces.
 *
 * For a cable sitting in cage L of the ASIC that owns it:
 *
 *   value    what it is           who takes it
 *   -------  -------------------  ---------------------------------------------------
 *   g        global cable index   MMAM only, which answers with the owning ga and L
 *   L        local module index   MCIA, PMAOS, and MMAM.local_module, which supplies it
 *   L + 1    label port           mlxlink -p, flint --downstream_device_ids, the report
 *   L + 2    MCC/MCQI wire index  MCC and MCQI; 0 there is the host device
 *
 * flint is where the two conversions are visible: it subtracts one from its
 * --downstream_device_ids value for the PMAOS read and adds one to it for MCC and MCQI
 * (user/flint/subcommands_linkx.cpp, BurnLinkX and QueryLinkX), so the local module and
 * the MCC index are two apart, not one.
 *
 * That gap is measured, not documented. MCC's own PRM text says device_index is the local
 * module plus one (tools_layouts/adb/prm/switch/ext/register_access_table.adb,
 * MCC.device_index), and it is the more plausible-sounding of the two - which is the danger:
 * addressing a cable one off reads or burns the neighbouring cage and reports no error at
 * all. Do not close that gap to match the PRM without re-measuring on hardware first, which
 * takes one command: FW_COMPS_DEBUG=1 makes FwCompsMgr print the index it sends, so
 *
 *     FW_COMPS_DEBUG=1 flint -d <dev> --linkx --downstream_device_ids <L+1> q full
 *
 * shows the LINKX_PROPERTIES read (infoType 6) going out at L+2. The other MCQI lines it
 * prints are component discovery against the host at index 0, not the cable.
 *
 * `localIndex` comes from MMAM.local_module rather than being computed, and each value is
 * stored as discovered rather than recomputed at the point of use.
 */
struct CableInfo
{
    u_int32_t globalIndex = 0;
    // globalIndex + 1. The global index is zero-based on the wire and no number this tool shows a
    // user is, so this is what every message naming a port prints. Stored rather than derived at
    // each use because every caller wants the same conversion.
    u_int32_t globalPort = 0;
    u_int32_t localIndex = 0;
    u_int8_t asicGa = 0; // owning ASIC, from MMAM.ga
    string asicDevName;  // the AsicInfo::devName that asicGa resolves to
    // MMAM.module_type, kept for one question: whether MMAM.ga names this entry's owning ASIC.
    // The PRM documents ga as Reserved for the backplane and chip2chip types and for no others,
    // so asicGa is trustworthy for every other type and worthless for those.
    u_int8_t moduleType = 0;
    bool isPlugged = false;  // a cable is plugged into the cage
    bool isBurnable = false; // the cable speaks a firmware-update protocol this tool can drive
    bool isNvidia = false;   // false for a third party or fake cable, which is reported and never updated
    string state;            // cable state; reported, but no state disqualifies a cable from an update

    // EEPROM identity, the key phase 3 matches package metadata against.
    string partNumber;
    string vendorName;
    string serialNumber;
    u_int32_t vendorOui = 0;
    string vendorRev; // two ASCII characters, for example "B1"
    u_int8_t hwRevMajor = 0;

    // Running firmware, from the MCQI LinkX properties.
    CableFwVersion fwImageA;
    CableFwVersion fwImageB;
    CableImageSlot runningSlot = CABLE_IMAGE_SLOT_A;
    // MCQI LinkX properties, 6 bits. 0 means the cable implements neither firmware-update
    // procedure; 1 is SFF-8636 with pseudo-CMIS, 2-7 are CMIS 4.0 through 5.5. isBurnable folds
    // several conditions into one bool, so this is the only one of them the report can still
    // name when a cable is skipped.
    u_int8_t managementInterfaceProtocol = 0;
    // MCQI LinkX properties, 4 bits. 0 means the cable needs a host power cycle after Run FW
    // Image, 1 and 2 mean it activates itself. A cable that needs the power cycle is still
    // running its old image when phase 5 re-queries it, so the report has to say that rather
    // than blame the burn.
    u_int8_t activationType = 0;

    // Filled by phase 3. targetSlot is always the slot that is not running.
    CableUpdateAction action = CABLE_ACTION_UNDECIDED;
    CableImageSlot targetSlot = CABLE_IMAGE_SLOT_A;
    CableFwVersion targetVersion;
    // The file inside the user's package this cable matched. The report names this and only
    // this: a path the tool invented is not an answer to which image went onto the cable.
    string packageImagePath;
    bool isDowngrade = false; // the target version is older than the running one
};

/* One metadata file from the update package and the binary it names.
 *
 * Which fields a file carries is itself information: a file giving only a part number
 * and a firmware major describes a LinkX image with no extended header, and the match
 * narrows to exactly the fields present.
 */
struct FwPackageEntry
{
    string metadataPath;     // location inside the package, for the report and for error messages
    string imagePath;        // the binary the metadata names, resolved relative to the metadata file
    string vendorPartNumber; // the package folder this entry came from
    string vendorName;
    u_int32_t vendorOui = 0;
    string vendorRev;
    u_int8_t hwRevMajor = 0;
    CableFwVersion fwVersion;
    bool hasExtendedHeader = false; // the binary already carries the 48-byte header, so no copy is needed
    bool isValid = false;
    string parseError; // why isValid is false; reported rather than fatal
};

/* Cables that share an owning ASIC and a binary, burned in one transaction.
 *
 * Grouping is forced by the transport, not chosen for speed: one burn carries one image
 * through one ASIC, and an ASIC cannot address another ASIC's cables.
 */
struct CablePlanEntry
{
    string asicDevName;
    u_int8_t asicGa = 0;
    // Two paths, because the file the user is told about and the file the burn opens are not
    // always the same one. packageImagePath is the entry in the user's package and is the only
    // one that reaches the report; burnImagePath is what phase 4 hands to the device, which for
    // an image that needed the extended header synthesized is the copy phase 3 wrote. Phase 3
    // sets them equal whenever the package binary already carried the header, so phase 4 opens
    // burnImagePath unconditionally.
    string packageImagePath;
    string burnImagePath;
    CableFwVersion fwVersion; // the version this binary installs
    // Indices into the cable list. The device selects the cables itself, so this is
    // what the group is expected to cover, and it is what phase 5 checks it against.
    vector<u_int32_t> cableIndices;
};

/* What became of one cable after an update attempt. */
struct CableUpdateResult
{
    u_int32_t globalIndex = 0;
    u_int32_t localIndex = 0;
    string asicDevName;
    bool succeeded = false;
    u_int8_t mccErrorCode = 0;  // failures only, from MCCE
    u_int16_t cdbErrorCode = 0; // failures only, from MCCE
    string status;              // human-readable outcome, shown in the report
};

/* Drives a fleet-wide cable firmware update for mlxfwmanager.
 *
 * The tool's ordinary path keys every device on a PSID and matches it against an MFA.
 * Cables have no PSID and are reached through their owning ASIC rather than through a
 * device node of their own, so this class runs its own discovery, matching and burn
 * instead of joining the MlnxDev list.
 *
 * The flow is five phases, described one by one on the private methods below.
 * `--cable_query` runs phases 1, 2 and 5; `--cable_dry_run` adds phase 3 and stops
 * before anything is written to a cable; `--cable_update` runs all five.
 *
 * Scope, which is narrower than the general cable-update problem:
 *  - only NVIDIA LinkX images and images carrying the 48-byte extended header are
 *    updated; third-party and fake cables are reported and skipped, never burned;
 *  - the whole system is scanned and every cable with a matching binary is updated.
 *    There is no single-ASIC and no port-range selection - the device picks the
 *    cables, in auto-update mode;
 *  - the device firmware has to support no_stop_on_error, since a fleet burn that
 *    stops at the first bad cable defeats the purpose.
 *
 * Errors are reported as err_msgs.h codes. Progress text accumulates in `_log` and is
 * printed by the caller: the print_out/print_err macros live in mlxfwmanager.h, but that
 * header also defines FOut, FErr, FLog and formatted_output at file scope, so only one
 * translation unit can include it.
 */
class CableFwManager
{
public:
    explicit CableFwManager(const CmdLineParams& cmdParams);
    ~CableFwManager();

    /* Run the phases the requested mode needs and return an err_msgs.h code.
     *
     * A single cable or a single ASIC group failing does not end the run: phase 4
     * keeps going so that one bad cable cannot strand the rest of the chassis, and the
     * failures surface in the phase 5 report.
     */
    int run();

    string getLastErrMsg() const { return _errMsg; }
    string getLog() const { return _log; }

private:
    /* Phase 1 - ASIC discovery.
     *
     * Enumerate every switch ASIC this host can reach - the programmatic equivalent of
     * `mst status`, via mdevices_info(MDEVS_TAVOR_CR) - and read MGIR on each to learn
     * its Geographical Address. There is no device selection: the map has to cover the
     * whole system.
     *
     * Then build the system-wide module map. The walk is bounded by MGPIR's
     * num_of_modules_per_system concatenated with its _msb half: the per-ASIC
     * num_of_modules is a different number, and the low byte on its own caps the walk
     * at 255 entries. MMAM, read by global module index, returns the owning ASIC's `ga`
     * along with the cable's local index on that ASIC.
     *
     * MMAM is the only register that spans ASICs, and its `ga` is the only ownership
     * test. Whether a register answers is not one: measured on two systems, a two-ASIC
     * chassis renumbers cages per ASIC and rejects MCIA and PMAOS for a cage it does not
     * own, while a four-ASIC chassis numbers cages system-wide and answers on every ASIC
     * for every cage - there, sweeping the ASICs finds each cable four times. So walk
     * MMAM once, key each cable by the `ga` it names, and de-duplicate; do not infer
     * ownership from a successful read, and do not assume cages are renumbered per ASIC.
     *
     * Read MGPIR through reg_access_mgpir_switch_ext(): the plain reg_access_mgpir()
     * helper binds a layout that carries gearbox counts and none of the module counts.
     *
     * Fills _asics, and the identity half of _cables.
     */
    int discoverSystem();

    /* Phase 2 - Cable discovery.
     *
     * For every cable found in phase 1, query its owning ASIC and decide whether it is
     * a candidate: a cage has to be populated, and the cable has to speak a
     * firmware-update protocol. MCQI's LinkX properties carry
     * management_interface_protocol, which is 0 for a cable that supports neither
     * update procedure - note this comes from MCQI, not MCIA, and MCQI is addressed by
     * the MCC device_index rather than by the local module index.
     *
     * Collect the identity phase 3 matches on - part number, vendor name and OUI,
     * vendor revision, hardware major revision - along with the serial number, the
     * cable state, and both firmware image versions with the slot that is running. Take
     * activation_type from the same MCQI read: it is what tells phase 5 whether a cable
     * activates itself or is waiting on a host power cycle.
     *
     * No cable state disqualifies a cable: a cable that is not Active or Ready is
     * still eligible, so state is recorded for the report and never used as a filter.
     *
     * Fills the remaining discovery fields of _cables.
     */
    int discoverCables();

    /* Phase 3 - Analysis and planning.
     *
     * Open the package named by `--cable_package`: one ZIP holding a folder per part
     * number, each folder holding metadata files and the binaries they describe, each
     * metadata file naming its binary by a path relative to itself.
     *
     * For each candidate cable, take the folder matching its part number and find the
     * one metadata file in it that matches. The metadata file is the authority: compare
     * exactly the fields it carries, so the package decides how narrowly each binary
     * matches. That gives the two shapes a file comes in - a CM or JDM entry carrying
     * vendor part number and firmware major, and an ODM entry additionally carrying
     * vendor revision, hardware major revision and vendor name/OUI. Vendor name/OUI
     * matters because two suppliers can ship the same part number, revision and
     * hardware major, and burning one vendor's image into the other's cable is the
     * failure this whole flow exists to avoid.
     *
     * Two cables of the same part number can legitimately need different binaries, so
     * a cable matching more than one metadata file is a packaging error rather than a
     * choice to make: fail the run and tell the user to fix the package.
     *
     * Give every cable an outcome, not only the ones to burn, and leave none UNDECIDED -
     * SKIP_NOT_PRESENT,
     * SKIP_3RD_PARTY, SKIP_NOT_BURNABLE, SKIP_NO_FW_FILE, SKIP_CURRENT or UPDATE - because the
     * report has to account for every port. An UPDATE whose target is older than the running
     * version still goes ahead but is flagged as a downgrade. The target slot is
     * whichever of A and B is not running; phase 5 checks that it became the running one.
     *
     * A metadata file carrying only part number and firmware major describes a LinkX
     * image with no extended header. Write a temporary copy with the 48-byte extended
     * header prepended and filled from the metadata, leaving vendor revision and
     * hardware revision zeroed: the device treats zeroed keys as wildcards, so it ends
     * up validating exactly the part number and firmware major the tool matched on.
     * That is a second, independent check on the same decision - worth the copy,
     * because a wrong image reaching a cable is unrecoverable in the field. The
     * package on disk is never modified, and the plan entry keeps the package path beside the
     * copy's, because the copy is an implementation detail of the burn and must never reach
     * the report.
     *
     * Finally group the chosen cables by owning ASIC and binary, since that is the
     * unit one burn transaction can carry.
     *
     * This is where `--cable_dry_run` stops. Everything up to here is read-only, so a
     * dry run is the way to check a package against a live chassis before committing to
     * a maintenance window.
     *
     * Fills _packages, the decision fields of _cables, and _plan.
     */
    int buildUpdatePlan();

    /* Phase 4 - Download and activate.
     *
     * Burn each plan entry through its owning ASIC in auto-update mode, with
     * no_stop_on_error set so that a cable the device rejects does not abandon the rest
     * of the group. FwCompsMgr::SetIndexAndSize() takes both flags, and drives the
     * transfer into the non-running slot and then the activation.
     *
     * One burn per group, and no index range on the wire: with auto_update set,
     * FwCompsMgr clears device_index_size and never sends device_index, so the device
     * picks the cables by matching the image itself. The plan's cable list is what the
     * group is expected to cover, not an instruction to the device.
     *
     * A failed group is recorded and the run continues to the next one; never abandon
     * the remaining groups, since the whole point is that one bad cable cannot strand a
     * chassis. In auto-update mode the device chooses the cables, so there is no
     * per-cable progress here - the per-cable verdict comes from phase 5.
     *
     * After the last activation, give the cables time to finish switching image before
     * verifying - `--cable_activation_wait`, sixty seconds by default. A cable slower
     * than the wait fails verification even though its burn succeeded, which is why the
     * wait is the caller's to raise.
     *
     * Fills the outcome half of _results.
     */
    int downloadAndActivate();

    /* Phase 5 - Verification and report.
     *
     * In query mode this reports the inventory phase 2 built. After an update it
     * re-queries every cable that was burned and marks it succeeded only if the target
     * slot actually became the running one and the running version matches the target;
     * a cable that was active before the burn has to be active after it.
     *
     * A cable whose activationType is 0 is the exception: its firmware only takes effect
     * after the host power cycles it, so it still reports the old image here and the report
     * has to name the pending power cycle rather than record a failed burn.
     *
     * Failure detail comes from the device's error log rather than from the burn's
     * return code, which says nothing about which cable failed:
     * FwCompsMgr::GetBurnFailures() returns one entry per skipped cable with the
     * device and cable error codes. The cable ids in that log are already in the
     * number the user sees, so report them as they arrive.
     *
     * The report is plain text, self-contained, and named
     * cable_fw_update_report_<YYYYMMDD_HHMMSS>.txt in the current directory or in
     * `--cable_report_dir`: a summary count, the packages used, the pre-update
     * inventory, the plan, the post-update state, and an errors table of port, phase
     * and the two error codes. Every path the report prints is a package path; a copy the tool
     * wrote is never named, because the user has to be able to open, diff and re-ship the file
     * the report cites.
     *
     * Fills _results and emits the report.
     */
    int verifyAndReport();

    const CmdLineParams& _cmdParams;
    AsicsByGa _asics;
    vector<CableInfo> _cables;
    vector<FwPackageEntry> _packages;
    vector<CablePlanEntry> _plan;
    vector<CableUpdateResult> _results;
    string _errMsg;
    string _log;
};

#endif
