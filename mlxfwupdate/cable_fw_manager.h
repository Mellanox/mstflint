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
#include <sstream>
#include <string>
#include <vector>

#include "common/compatibility.h"
#include <mtcr.h>
#include "cmd_line_params.h"

using namespace std;

/* Seconds to pause between the download and the activation. Activation reports its own
 * completion, so nothing has to be waited out after it; the pause exists only for cables that
 * want settling time between the two, and no cable in the supported set asks for it.
 */
#define CABLE_ACTIVATION_WAIT_DEFAULT 0

/* Seconds phase 5 lets a burned cable re-train before it is verified. A self-activating cable
 * resets, so its link drops and comes back; measured link-up times are around three seconds.
 */
#define CABLE_VERIFY_WAIT_DEFAULT 5

/* A switch ASIC reachable from this host. */
struct AsicInfo
{
    string devName;     // MST device name or PCI address, in the form mopen() accepts
    string description; // model description, truncated at the first ';' the way flint prints it
    string fwVersion;   // running firmware, from MGIR
    // Local module index -> local port, swept out of PLLP once. PDDR is addressed by local port
    // and nothing maps a cage to one, so the mapping has to be inverted from the register that
    // carries both.
    map<u_int32_t, u_int32_t> localPortByCage;
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

/* What was decided for a cable. Phase 3 rules on every entry it can reach, and phase 1 rules on
 * the ones it already knows it will never be able to address. Every discovered cable gets one of
 * these, including the ones left alone, because the report has to account for every port.
 */
enum CableUpdateAction
{
    // Zero on purpose: an entry nobody has ruled on reads as undecided rather than as an
    // instruction to burn, which is what the first enumerator would otherwise mean.
    CABLE_ACTION_UNDECIDED,
    CABLE_ACTION_UPDATE,
    // Decided in phase 1 rather than phase 3: MMAM.ga is Reserved for some module types, and for
    // those the entry names no owner ASIC and nothing downstream can address it.
    CABLE_ACTION_SKIP_ASIC_DETECTION_NOT_SUPPORTED,
    CABLE_ACTION_SKIP_NOT_PLUGGED,
    CABLE_ACTION_SKIP_UNREADABLE, // the cage is populated but the cable did not answer
                                  // Not an NVIDIA cable. A counterfeit is reported as one of these too;
                                  // which of the two the firmware said is in the debug trace.
    CABLE_ACTION_SKIP_3RD_PARTY,
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
 * take, and the number MCC and MCCE answer in. Measured one above the local module index. The
 * report keys cables on the chassis-wide port instead, and carries this one only where a device
 * error has to be matched back to a cable.
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

/* The index MCC, MCQI and MCQS take on the wire, one above the label port. Kept here beside
 * cableLabelPort() for the same reason: the two conversions are the whole of the arithmetic, and a
 * second copy of either is a second place that can disagree.
 */
inline u_int32_t cableMccIndex(u_int32_t localIndex)
{
    return cableLabelPort(localIndex) + 1;
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
    bool isPlugged = false;     // a cable is plugged into the cage
    bool isReadable = false;    // its identity was read; nothing below means anything without it
    string linkState;           // PHY manager state, what mlxlink shows as "State"
    u_int8_t operStatus = 0xff; // raw PMAOS.oper_status; 0xff means it was never read
    bool isBurnable = false;    // the cable speaks a firmware-update protocol this tool can drive
    bool isNvidia = false;      // false for a third party or fake cable, which is reported and never updated
    // The raw MFCDR verdict, kept rather than folded into isNvidia alone. The report calls a
    // counterfeit and a third party cable the same thing, so this is the only place the
    // difference survives to reach the trace. It is also a statement about the cage that does not
    // depend on the EEPROM having read, which is why it outranks an unreadable identity.
    u_int8_t vendorStatus = 0; // CABLE_VENDOR_STATUS_UNKNOWN; 0xff when MFCDR could have answered and did not
    string state;              // cable state; reported, but no state disqualifies a cable from an update

    // EEPROM identity, the key phase 3 matches package metadata against.
    string partNumber;
    string vendorName;
    string serialNumber;
    u_int32_t vendorOui = 0;
    string vendorRev; // two ASCII characters, for example "B1"
    // Cage form factor. PDDR names it with a firmware enum; the EEPROM fallback names it from the
    // SFF-8024 identifier byte, which is a different number space carrying the same meaning.
    string identifier;
    string manufacturingDate;
    u_int8_t hwRevMajor = 0;
    u_int8_t hwRevMinor = 0;

    // Running firmware, from the MCQI LinkX properties.
    CableFwVersion fwImageA;
    CableFwVersion fwImageB;
    CableImageSlot runningSlot = CABLE_IMAGE_SLOT_A;
    bool isRunningImage = false; // an image is actually running; runningSlot is meaningless without it
    bool fwRead = false;         // MCQI answered; without it every version here is a default, not a reading
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
    int packageEntryIndex = -1; // the metadata entry it matched, which the extended header is built from
    bool isDowngrade = false;   // the target version is older than the running one
};

/* One metadata entry from the update package and the binary it names.
 *
 * Which keys an entry carries is itself information: the match narrows to exactly the keys
 * present.
 */
struct FwPackageEntry
{
    string metadataPath; // location inside the package, for the report and for error messages
    string imagePath;    // the binary the metadata names, resolved relative to the metadata file
    // The match keys, as the metadata wrote them; all but the vendor name may hold ? and *
    // wildcards. The part number is the package folder's when the entry states none.
    string vendorName;
    string vendorPartNumber;
    string vendorOui;
    string vendorRev;
    string vendorSn;
    string hwRevMajor;
    string hwRevMinor;
    string activeFwVersion;
    CableFwVersion fwVersion; // the load's version, which the cable is updated to
    // Which of the optional keys the entry carried. A key the metadata omits is not compared at
    // all, which is how the package decides how narrowly each binary matches; without these an
    // omitted vendor revision would be indistinguishable from one that is genuinely empty.
    bool hasVendorOui = false;
    bool hasVendorRev = false;
    bool hasVendorSn = false;
    bool hasHwRevMajor = false;
    bool hasHwRevMinor = false;
    bool hasActiveFwVersion = false;
    bool hasExtendedHeader = false;      // the binary carries the 48-byte header already
    bool hasLinkXExtendedHeader = false; // and it is the LinkX wrap, which no cable can be matched against
    bool isValid = false;
    string parseError; // why isValid is false; reported rather than fatal
};

/* The fields the device matches an image against before it will write it to a cable, all taken
 * from the metadata entry. A zero field is a wildcard, so a CM/JDM (contract or joint-design
 * manufacturer) entry yields a header that names only the part number and the product id; an ODM
 * (original design manufacturer) entry adds its vendor revision and hardware major. The key
 * doubles as the grouping key, since cables matched by different entries need different headers.
 */
struct CableExtHeaderKey
{
    string partNumber;       // VendorPN, as the metadata spells it
    string vendorRev;        // VendorRev when the metadata states it, empty (zero bytes) otherwise
    u_int8_t hwRevMajor = 0; // the hardware major when the metadata states it, zero otherwise
    u_int8_t productId = 0;  // the LinkX product id, which is the metadata firmware major

    /* An image can only be wrapped when the part number and product id are known and fit. */
    bool isComplete() const;
    /* The fields as one string, so cables that can share a wrapped image group together. */
    string groupKey() const;
    /* The four fields as a sentence, for the debug trace that says how an image was wrapped. */
    string text() const;
};

/* Cables that share an owning ASIC and a binary, burned in one transaction.
 *
 * Grouping is forced by the transport, not chosen for speed: one burn carries one image
 * through one ASIC, and an ASIC cannot address another ASIC's cables. Cables that get a
 * synthesized extended header are grouped by its contents too, since cables matched by different
 * metadata entries get different headers.
 */
struct CablePlanEntry
{
    string asicDevName;
    u_int8_t asicGa = 0;
    // packageImagePath names the entry inside the user's package and is the only one the report
    // shows; burnImage is the byte sequence actually sent - the eight 0xFF bytes every LinkX burn
    // leads with, then the image, carrying the synthesized extended header when the package
    // binary had none.
    string packageImagePath;
    vector<u_int8_t> burnImage;
    CableFwVersion fwVersion; // the version this binary installs
    // Whether this group's burnImage carries a header this tool built, and the fields it was
    // built from. Kept rather than recomputed so the trace written before the burn can say what
    // the device is being asked to match.
    bool isWrapped = false;
    CableExtHeaderKey header;
    // The package shipped this image with a header of its own, which is sent as it stands. Kept
    // apart from isWrapped so the trace can tell it from an image that carries no header at all -
    // the one case where the device matches on the product id alone.
    bool imageHasOwnHeader = false;
    // Indices into the cable list. The device selects the cables itself, so this is
    // what the group is expected to cover, and it is what phase 5 checks it against.
    vector<u_int32_t> cableIndices;
};

/* What became of one cable after an update attempt. */
struct CableUpdateResult
{
    u_int32_t globalIndex = 0;
    u_int32_t globalPort = 0; // globalIndex + 1, the number the report keys every cable on
    u_int32_t localIndex = 0;
    u_int8_t asicGa = 0;
    string asicDevName;
    bool succeeded = false;
    bool burnAccepted = false;      // phase 4 sent the image and the device did not refuse this cable
    bool hasDeviceError = false;    // MCCE named this cable, so its error codes carry a reading
    bool readBack = false;          // phase 5 re-read this cable's firmware
    string phase;                   // the stage that decided the outcome, for the errors table
    u_int8_t mccErrorCode = 0;      // failures only, from MCCE
    u_int16_t cdbErrorCode = 0;     // failures only, from MCCE
    string mccErrorText;            // mccErrorCode named by the manager that returned it
    bool pendingPowerCycle = false; // burned, but the new image runs only after a host power cycle
    CableFwVersion pendingVersion;  // what it will run once power-cycled
    string stateBefore;             // link state read in phase 2, before the burn
    string stateAfter;              // link state re-read after the burn
    bool stateRegressed = false;    // it was Active before and is not after, which fails the group
    // What phase 5 read back, for the verification table.
    CableFwVersion fwImageA;
    CableFwVersion fwImageB;
    CableImageSlot runningSlot = CABLE_IMAGE_SLOT_A;
    bool isRunningImage = false;
    string status; // human-readable outcome, shown in the report
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
 * Errors are reported as err_msgs.h codes. Progress text is printed as it happens,
 * through a printer the caller supplies: a fleet update runs for minutes and the library
 * under it writes to stdout during a burn, so text held back to the end both arrives too
 * late to act on and interleaves wrongly with what the library already printed. The
 * printer has to come from the caller because the print_out/print_err macros live in
 * mlxfwmanager.h, which also defines FOut, FErr, FLog and formatted_output at file scope,
 * so only one translation unit can include it.
 *
 * What goes to the terminal is what an operator acts on. Per-port and per-file detail
 * goes to the nvtoolslogger trace instead, which the report tables account for in full:
 *   nvtoolslogger --set-module mlxfwmanager:debug
 */
class CableFwManager
{
public:
    /* Puts one piece of text in front of the user straight away. */
    typedef void (*ProgressPrinter)(const char* text);

    CableFwManager(const CmdLineParams& cmdParams, ProgressPrinter printer);
    ~CableFwManager();

    /* Run the phases the requested mode needs and return an err_msgs.h code.
     *
     * A single cable or a single ASIC group failing does not end the run: phase 4
     * keeps going so that one bad cable cannot strand the rest of the chassis, and the
     * failures surface in the phase 5 report.
     */
    int run();

    string getLastErrMsg() const { return _errMsg; }

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

    /* Key every switch ASIC in `devs` into _asics by the Geographical Address it reports. */
    int collectSwitchAsics(dev_info* devs, int devsNum);

    /* Read the system-wide cable map into _cables, through the ASIC at Geographical Address 0. */
    int buildCableMap();

    /* Walk MMAM over `total` global indexes on `mf` and append every port to _cables. */
    int walkCableMap(mfile* mf, u_int32_t total);

    /* Phase 2 - Cable discovery.
     *
     * For every cable found in phase 1, query its owning ASIC and decide whether it is
     * a candidate: a cage has to be populated, and the cable has to speak a
     * firmware-update protocol. MCQI's LinkX properties carry
     * management_interface_protocol, which is 0 for a cable that supports neither
     * update procedure - note this comes from MCQI, not MCIA, and MCQI is addressed by
     * the MCC device_index rather than by the local module index.
     *
     * Whether a cage is populated comes from PDDR's cable type, the same source mlxlink -m uses;
     * PMAOS.oper_status decides only for a cage PDDR cannot answer for. Every read is attempted
     * whatever the others returned, so a cable shows all that could be read about it.
     *
     * Collect the identity phase 3 matches on - part number, vendor name and OUI,
     * vendor revision, hardware major revision - along with the serial number, the form
     * factor, the manufacturing date, the CMIS module state, and both firmware image versions
     * with the slot that is running. Take
     * activation_type from the same MCQI read: it is what tells phase 5 whether a cable
     * activates itself or is waiting on a host power cycle.
     *
     * No cable state disqualifies a cable: a cable that is not Active or Ready is
     * still eligible, so state is recorded for the report and never used as a filter.
     *
     * Fills the remaining discovery fields of _cables.
     */
    int discoverCables();

    /* Fill one cable's plugged state, identity and firmware properties from its owning ASIC. A cable
     * that cannot be read is recorded and skipped rather than ending the sweep, so one bad cage
     * cannot hide the rest of the chassis.
     */
    /* Fill whatever PDDR left empty from the EEPROM, field by field. */
    void fillIdentityGapsFromEeprom(mfile* mf, CableInfo& cable);

    /* The local port serving a cage, from the swept map. PDDR is indexed by it. */
    bool cableLocalPort(const CableInfo& cable, u_int32_t& localPort);

    /* The link state for one cable, which PDDR indexes by local port rather than by cage. */
    string readCableLinkStateText(mfile* mf, const CableInfo& cable);

    void queryCable(mfile* mf, CableInfo& cable);

    /* Read the EEPROM identity - part number, vendor, revision, serial, form factor, module
     * state and manufacturing date. The field offsets differ between CMIS and SFF-8636, and the
     * identifier byte is what says which. The hardware revision lives on page 1, which a
     * flat-memory cable does not implement and MCIA does not refuse.
     */
    bool readCableIdentity(mfile* mf, CableInfo& cable);

    /* Read the MCQI LinkX properties: both image versions, which image is running if any, the
     * management interface protocol and the activation type.
     */
    bool readCableFwProperties(mfile* mf, CableInfo& cable);

    /* Phase 3 - Analysis and planning.
     *
     * Open the package named by `--cable_package`: a folder per part number, each folder
     * holding metadata files and the binaries they describe, each metadata entry naming its
     * binary by FwLoadName, relative to the file. It comes as one tgz (the IA's format), tar or
     * ZIP, or as a directory already holding that layout - the ZIP reader is not built on every
     * platform, so a tgz or an extracted directory is the way in where it is missing, and all of
     * them are read into the same shape so nothing downstream can tell them apart.
     *
     * Metadata follows the OIF CMIS Firmware Update Package IA: a file holds one entry or a list
     * of them, keyed by the CMIS field names. VendorName is matched exactly; every other key the
     * entry states is matched with ? and * wildcards, and a key it omits does not narrow the
     * match. A CM or JDM entry states no part number and takes its folder's. The load's FW major
     * must equal the cable's running one, since it is the product id the device checks.
     *
     * A cable that several entries match takes the one with the highest load version, the
     * first of them on a tie, and the trace names every candidate.
     *
     * Give every cable an outcome, not only the ones to burn, and leave none UNDECIDED -
     * SKIP_NOT_PLUGGED,
     * SKIP_3RD_PARTY, SKIP_NOT_BURNABLE, SKIP_NO_FW_FILE, SKIP_CURRENT or UPDATE - because the
     * report has to account for every port. An UPDATE whose target is older than the running
     * version still goes ahead but is flagged as a downgrade. The target slot is
     * whichever of A and B is not running; phase 5 checks that it became the running one.
     *
     * A raw LinkX image gets the 48-byte extended header synthesized in memory and prepended:
     * the part number and the load's FW major always, the vendor revision and hardware major only
     * when the entry states them without wildcards, zero otherwise, which the device treats as a
     * wildcard. The device then validates the same keys the tool matched on.
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

    /* Read every metadata file in the package into _packages, resolving each one's binary and
     * checking the digest it carries. A file that does not parse is recorded against itself and
     * the rest of the package is still used.
     */
    int loadPackage(map<string, vector<u_int8_t> >& contents);
    /* One metadata file, its entries each validated against the package files around it. */
    vector<FwPackageEntry> parseMetadataFile(const string& name,
                                             const vector<u_int8_t>& bytes,
                                             const map<string, vector<u_int8_t> >& contents) const;

    /* Give every cable an outcome. A cable that more than one metadata entry matches takes the
     * highest load version.
     */
    int decideCableActions();

    /* Group the chosen cables by owning ASIC and binary - the unit one burn transaction carries -
     * and write the temporary header-prefixed copy for any image that needs one.
     */
    int groupUpdatePlan(const map<string, vector<u_int8_t> >& contents);

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
     * The download and the activation are separable, and `--cable_activation_wait` puts a pause
     * between them. Waiting after the activation would buy nothing: the activation reports its
     * own completion, so a cable is either running the new image by then or is one of the cables
     * that needs a host power cycle, which no wait can shorten. With no wait asked for, the two
     * run as a single transaction.
     *
     * Fills the outcome half of _results.
     */
    int downloadAndActivate();

    /* Refuse the run unless every ASIC can report per-cable burn errors. A device that cannot
     * stops at the first bad cable, which turns a fleet update into a partial one nobody asked
     * for, so a mixed system has to be aligned before it is burned rather than during.
     */
    int checkNoStopOnErrorSupport();

    /* Burn one group and record what became of each of its cables. A group that fails is recorded
     * and the run moves to the next one, since the whole point is that one bad cable cannot
     * strand a chassis.
     */
    void burnPlanEntry(const CablePlanEntry& group, size_t firstResult);

    /* One pass of the burn state machine. The download and the activation are separable, which is
     * what lets a wait sit between them.
     */
    /* The cached handle for a switch, opened on first use. NULL if it cannot be opened, and a
     * failure is not cached.
     */
    mfile* deviceHandle(const string& devName);

    bool runBurnStage(mfile* mf,
                      const vector<u_int8_t>& image,
                      bool download,
                      bool activate,
                      size_t firstResult,
                      size_t lastResult,
                      string& errMsg,
                      string& stageName);

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
     * the report cites. It is printed to the screen first unless `--cable_report_file_only`.
     *
     * Fills _results and emits the report.
     */
    int verifyAndReport();

    /* Re-read every cable that was burned and decide whether it took the image. A cable whose
     * firmware only takes effect after the host power cycles it still reports the old version
     * here, which is a pending power cycle rather than a failed burn.
     */
    void verifyBurnedCables();

    /* Collect the per-device detail the report prints but the phases never needed: the device
     * description, and the text for the error codes the device returned.
     */
    void collectReportDetails();

    /* Render the whole report. The template is fixed, so a field that does not apply to the flow
     * that ran prints N/A rather than being left out.
     */
    string buildReport();

    /* The report's sections. Each prints N/A rather than nothing when the run did not reach the
     * phase that fills it, so the shape of the report does not depend on the mode.
     */
    void appendPackagesTable(std::ostringstream& report);
    /* withAsic adds the owning ASIC and its label port. Only DISCOVERY offers them, and only
     * under --verbose: the plan and the verification tables already carry columns of their own.
     * ERRORS builds its own header and carries both unconditionally.
     */
    void appendCableColumns(std::ostringstream& report, bool withAsic);
    void appendCableRow(std::ostringstream& report, const CableInfo& cable, bool withAsic);
    void appendDiscoveryTable(std::ostringstream& report);
    void appendPlanTable(std::ostringstream& report);
    void appendVerificationTable(std::ostringstream& report);
    void appendErrorsTable(std::ostringstream& report);

    /* Write the report beside the others, named for the moment it was produced. */
    int writeReport(const string& text);

    /* The metadata entry a planned image came from, or NULL when the package no longer holds it. */
    const FwPackageEntry* packageEntryFor(const string& imagePath) const;
    const FwPackageEntry* matchedEntryFor(const CableInfo& cable) const;

    /* Say which cables are about to change and to what, before the first byte reaches one. */
    void announceUpdatePlan();

    /* Put text in front of the user now. Every progress line in this class goes through here. */
    void emitProgress(const string& text);

    const CmdLineParams& _cmdParams;
    AsicsByGa _asics;
    // One open handle per switch, so a run that touches an ASIC once per cable, once per burn
    // group and again per result does not reopen it each time. FwCompsMgr does not take
    // ownership of a handle it is constructed with, so sharing one is safe.
    map<string, mfile*> _openDevices;
    vector<CableInfo> _cables;
    vector<FwPackageEntry> _packages;
    vector<CablePlanEntry> _plan;
    vector<CableUpdateResult> _results;
    string _errMsg;
    ProgressPrinter _printer;
    // Phase 3 ruled on every cable. Until it has, every action is the default, and neither the plan
    // table nor the skipped count can say anything true about them.
    bool _planned;
    // Why an update ended before its first burn, for the report: without it the ERRORS section of
    // an update that never started reads the same as one that burned cleanly.
    string _notStartedReason;
};

#endif
