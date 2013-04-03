/*
 *
 * flint.cpp - FLash INTerface
 *
 * Copyright (c) 2011 Mellanox Technologies Ltd.  All rights reserved.
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
 *  Version: $Id: flint.cpp 10696 2013-04-03 08:25:51Z mohammad $
 *
 */


#include "flint_ops.h"
#ifndef DEV_MST_EXAMPLE1
    #define DEV_MST_EXAMPLE1 "/dev/mst/mt25418_pci_cr0"
#endif

#ifndef DEV_MST_EXAMPLE2
    #define DEV_MST_EXAMPLE2 "/dev/mst/mt25418_pciconf0"
#endif

#ifndef FLINT_NAME
    #ifdef __GNUC__
        #define FLINT_NAME "flint"
    #else
        #define FLINT_NAME "flint"
    #endif
#endif

extern bool _silent;
extern bool _assume_yes;
extern bool _assume_no;
extern bool _no_erase;
extern bool _no_burn;
extern bool _unlock_bypass;
extern bool _byte_write;
extern bool _print_crc;

extern const char* g_sectNames[];

#define GETGUID(s, g) do { if (!ops.getGUID(s,g)) return 1; } while (0)
#define GETKEY(s, g) do { if (!ops.getGUID(s,g, "Invalid Key syntax, it should contain only hexa numbers.")) return 1; } while (0)
#define GET_FLASH_PARAMS(a, fp) do { if (!ops.getFlashParams(a, fp)) return 1; } while (0)

#define HW_SET_CMD "set"
#define HW_GET_CMD "query"

CommandType ParseCommand(const char* cmd) {
    u_int32_t cmdLenGiven = strlen(cmd);

    for (u_int32_t i = 0 ; i < numbel(g_commands); i++ ) {
        if (g_commands[i].requireExactMatch ) {
            if (!strcmp(cmd, g_commands[i].cmdName)) {
                return g_commands[i].cmd;
            }
        } else {
            // Match if given cmd maches the beginning of the checked cmd
            if (!strncmp(cmd, g_commands[i].cmdName, cmdLenGiven )) {
                return g_commands[i].cmd;
            }
        }
    }
    return CMD_UNKNOWN;
}

////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                           MAIN                                     //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
// sed -e 's/"/\\"/g' < flint.txt | perl -pe 's/^(.*)$/"$1\\n"/'
void usage(bool full = false)
{

#ifdef FOR_MAN
    #define MAN_BR ".br\n"

    #define QUOTE(s)      #s
    #define MAN_SH(name)  ".SH " #name "\n"
    #define MAN_SS(name)  ".SS " #name "\n"
    #define MAN_FS
#else
    #define MAN_BR
    #define MAN_SH(name)  name "\n"
    #define MAN_SS(name)  name "\n"
    #define MAN_FS(name)  "   " name "\n"
#endif



    const char *descr =
#ifdef FOR_MAN
    ".TH \"flint\" \"\" \"Mar 2013\" \"MFT 3.0.0\" \"Administration\"\n"
    MAN_SH("NAME")
#endif
    "\n"
    "               FLINT - FLash INTerface\n"

    "\n"
    MAN_SH("SYNOPSIS")
    "    " FLINT_NAME " [switches...] <command> [parameters...]\n"
//    "Switches summary:\n"
//    "-----------------\n"
    "\n"
    MAN_SH("DESCRIPTION")
    "    "FLINT_NAME " is a FW (firmware) burning and flash memory operations tool for\n"
    "    Mellanox Infiniband HCAs, Ethernet NIC cards, and switch devices.\n"
    "\n"
    MAN_SS("OPTIONS")
    "\n"
    "    -d[evice] <device> - Device flash is connected to.\n"
    "                         Commands affected: all\n"
    "\n"
    "    -guid <GUID>       - GUID base value. 4 GUIDs\n"
    "                         are automatically assigned to the\n"
    "                         following values:\n"
    "\n"
    "                         guid   -> node GUID\n"
    "                         guid+1 -> port1\n"
    "                         guid+2 -> port2\n"
    "                         guid+3 -> system image GUID.\n"
    "\n"
    "                         Note: port2 guid will be assigned even for a\n"
    "                         single port HCA - The HCA ignores this value.\n"
    "\n"
    "                         Commands affected: burn, sg\n"
    "\n"
    "    -guids <GUIDs...>  - 4 GUIDs must be specified here.\n"
    "                         The specified GUIDs are assigned\n"
    "                         to the following fields, repectively:\n"
    "                         node, port1, port2 and system image GUID.\n"
    "\n"
    "                         Note: port2 guid must be specified even for a\n"
    "                         single port HCA - The HCA ignores this value.\n"
    "                         It can be set to 0x0.\n"
    "\n"
    "                         Commands affected: burn, sg\n"
    "\n"

    "    -mac <MAC>         - MAC address base value. 2 MACs\n"
    "                         are automatically assigned to the\n"
    "                         following values:\n"
    "\n"
    "                         mac    -> port1\n"
    "                         mac+1  -> port2\n"
    "\n"
    "                         Commands affected: burn, sg\n"
    "\n"
    "    -macs <MACs...>    - 2 MACs must be specified here.\n"
    "                         The specified MACs are assigned\n"
    "                         to port1, port2, repectively.\n"
    "                         Commands affected: burn, sg\n"
    "                         Note: -mac/-macs flags are applicable only for Mellanox\n"
    "                               Technologies ethernet products.\n"
    "\n"
    "    -uid <UID>         - BridgeX only. Derive and set the device UIDs (GUIDs, MACs, WWNs).\n"
    "                         UIDs are derived from the given base UID according to Mellanox Methodology\n"
    "                         Commands affected: burn, sg\n"
    "\n"
    "    -uids <UIDs...>    - BridgeX only. 29 space separated UIDs must be specified here.\n"
    "                         The specified UIDs are assigned to the following fields, repectively:\n"
    "                         G0-MAC-PI0      G0-MAC-PI1      G0-MAC-PI2\n"
    "                         G0-MAC-PE0      G0-MAC-PE1      G0-MAC-PE2    G0-MAC-PE3\n"
    "                         G0-FC-WWPN-P0   G0-FC-WWPN-P1   G0-FC-WWPN-P2 G0-FC-WWPN-P3\n"
    "                         G0-IB-NODE-GUID G0-IB-PORT-GUID G0-FC-WWNN\n"
    "                         G1-MAC-PI0      G1-MAC-PI1      G1-MAC-PI2\n"
    "                         G1-MAC-PE0      G1-MAC-PE1      G1-MAC-PE2    G1-MAC-PE3\n"
    "                         G1-FC-WWPN-P0   G1-FC-WWPN-P1   G1-FC-WWPN-P2 G1-FC-WWPN-P3\n"
    "                         G1-IB-NODE-GUID G1-IB-PORT-GUID G1-FC-WWNN\n"
    "                         IB-SYSTEM-GUID\n"
    "                         Commands affected: burn, sg\n"
    "\n"
    "    -blank_guids       - Burn the image with blank GUIDs and MACs (where\n"
    "                         applicable). These values can be set later using\n"
    "                         the \"sg\" command (see details below).\n"
    "\n"
    "                         Commands affected: burn\n"
    "\n"
    "    -clear_semaphore   - Force clear the flash semaphore on the device.\n"
    "                         No command is allowed when this flag is used.\n"
    "                         NOTE: May result in system instability or flash\n"
    "                               corruption if the device or another\n"
    "                               application is currently using the flash.\n"
    "                               Exercise caution.\n"
    "\n"
    "    -h[elp]            - Prints this message and exits\n"
    "    -hh                - Prints extended command help\n"
    "\n"
    "    -i[mage] <image>   - Binary image file.\n"
    "                         Commands affected: burn, verify\n"
    "\n"
    "    -qq                - Run a quick query. When specified, flint will not perform full\n"
    "                         image integrity checks during the query operation. This may shorten\n"
    "                         execution time when running over slow interfaces (e.g., I2C, MTUSB-1).\n"
    "                         Commands affected: burn, query\n"
    "\n"
    "    -nofs              - Burn image in a non failsafe manner.\n"
    "\n"
    "    -allow_psid_change - Allow burning a FW image with a different PSID (Parameter Set ID)than the\n"
    "                         one currently on flash. Note that changing a PSID may cause the device to\n"
    "                         malfunction. Use only if you know what you are doing\n"
    "\n"
    "    -allow_rom_change\n"
    "                       - Allow burning/removing a ROM to/from FW image when product version is present.\n"
    "                         Use only if you know what you are doing\n"
    "\n"
    "    -override_cache_replacement\n"
    "                       - On SwitchX/ConnectIB devices:\n"
MAN_BR
    "                         Allow accessing the flash even if the cache replacement mode is enabled.\n"
    "                         NOTE: This flag is intended for advanced users only.\n"
    "                               Running in this mode may cause the firmware to hang.\n"
    "\n"
    "    -no_flash_verify   - Do not verify each write on the flash.\n"
    "\n"
#if 0
    "    -unlock            - Use unlock bypass feature of the flash for quicker burn.\n"
    "                         Commands affected: burn\n"
    "\n"
#endif
    "    -s[ilent]          - Do not print burn progress flyer.\n"
    "                         Commands affected: burn\n"
    "\n"
    "    -y[es]             - Non interactive mode - assume answer\n"
    "                         \"yes\" to all questions.\n"
    "                         Commands affected: all\n"
    "\n"
    "    -no                - Non interactive mode - assume answer\n"
    "                         \"no\" to all questions.\n"
    "                         Commands affected: all\n"
    "\n"
    "    -vsd  <string>     - Write this string, of up to 208 characters, to VSD when burn.\n"
    "\n"
    "    -use_image_ps      - Burn vsd as appears in the given image - do not keep existing VSD on flash.\n"
    "                         Commands affected: burn\n"
    "\n"
    "    -use_image_guids   - Burn (guids/uids/macs) as appears in the given image.\n"
    "                         Commands affected: burn\n"
    "\n"
    "    -use_image_rom     - Do not save the ROM which exists in the device.\n"
    "                         Commands affected: burn\n"
    "\n"
    "    -dual_image        - Make the burn process burn two images on flash (previously default algorithm). Current\n"
    "                         default failsafe burn process burns a single image (in alternating locations).\n"
    "                         Commands affected: burn\n"
    "\n"
    "    -striped_image     - Use this flag to indicate that the given image file is in a \"striped image\" format.\n"
    "                         Commands affected: query verify\n"
    "\n"
    "    -banks <banks>\n"
    "                       - Set the number of attached flash devices (banks)\n"
    "\n"
    "    -log <log_file>\n"
    "                       - Print the burning status to the specified log file\n"
    "\n"
    "    -flash_params "FLASH_PARAMS_OPTS"\n"
    "                       - Use the given parameters to access the flash instead of reading them from the flash.\n"
    "                         Supported parameters:\n"
    // TODO: Get the supported type list from the mflash library.
    "                           Type: The type of the flash, such as: M25PXxx, M25Pxx, SST25VFxx, W25QxxBV.\n"
    "                           log2size: The log2 of the flash size.\n"
    "                           num_of_flashes: the number of the flashes connected to the device.\n"
    "\n"
    "    -v                 - Version info.\n"
    "\n"
    MAN_SS("COMMANDS SUMMARY")
#ifndef FOR_MAN
    "\n(use -hh flag for full commands description):\n"
#else
    "\n"
#endif
    "\n"
    "Common FW Update and Query:\n"
    "  b[urn]              - Burn flash\n"
    "  q[uery]  [full]     - Query misc. flash/firmware characteristics, use \"full\" to get more information.\n"
    "  v[erify] [showitoc] - Verify entire flash, use \"showitoc\" to see ITOC headers in FS3 image only.\n"
    "  swreset             - SW reset the target un-managed switch device. This command\n"
    "                        is supported only in the In-Band access method.\n"
    "\n"
    "Expansion ROM Update:\n"
    "  brom     <ROM-file> - Burn the specified ROM file on the flash.\n"
    "  drom                - Remove the ROM section from the flash.\n"
    "  rrom     <out-file> - Read the ROM section from the flash.\n"
    "\n"
    "Initial Burn, Production:\n"
    "  bb                  - Burn Block - Burns the given image as is. \n"
    "                        No checks are done.\n"
    "  sg       [nocrc]    - Set GUIDs.\n"
    "  smg                 - Set manufacture GUIDs (For FS3 image only).\n"
    "  set_vpd  [vpd file] - Set read-only VPD (For FS3 image only).\n"
    "  sv                  - Set the VSD.\n"
    "\n"
    "Misc FW Image operations:\n"
    "  ri       <out-file> - Read the fw image on the flash.\n"
    "  dc       [out-file] - Dump Configuration: print fw configuration file\n"
    "                        for the given image.\n"
    "  dth      [out-file] - Dump Tracer Hash: dump the tracer hash if it is integrated in the FW image\n"
    "\n"

    "HW Access Key:\n"
    "  set_key  [key]      - Set/Update the HW access key which is used to enable/disable access to HW.\n"
    "                        The key can be provided in the command line or interactively typed after\n"
    "                        the command is given\n"
    "                        NOTE: The new key is activated only after the device is reset.\n"
    "  hw_access <enable|disable> [key]\n"
    "                      - Enable/disable the access to the HW.\n"
    "                        The key can be provided in the command line or interactively typed after\n"
    "                        the command is given\n"
    "\n"

    "Low Level Flash Operations:\n"
    "  cfi                 - Query flash device parameters.\n"
    "                      - THE 'cfi' COMMAND IS DEPRECATED AND WILL BE REMOVED IN FUTURE RELEASES, PLEASE USE 'hw query' INSTEAD.\n"

#ifdef EXTERNAL
    "  hw query            - Query HW info and flash attributes.\n"
#else
    "  hw <query|set> [ATTR=VAL]\n"
    "                      - Set/query HW info and flash attributes.\n"
    "                        Supported attributes:\n"
    "                          QuadEn can be 0 or 1\n"
    "                            Example: QuadEn=1\n"
    "                          Flash[0|1|2|3].WriteProtected can be <Top|Bottom>,<1|2|4|8|16|32|64>-<Sectors|SubSectors>\n"
    "                            Example: Flash1.WriteProtected=Top,1-SubSectors\n"
#endif
    "  e[rase]  <addr>     - Erase sector\n"
    "  rw       <addr>     - Read one dword from flash\n"
    "  ww       <addr> < data> \n"
    "                      - Write one dword to flash\n"
    "  wwne     <addr>     - Write one dword to flash without sector erase\n"
    "  wbne     <addr> <size> <data ...> \n"
    "                      - Write a data block to flash without sector erase\n"
    "  rb       <addr> <size> [out-file]\n"
    "                      - Read  a data block from flash\n"
    "\n"
    "  Return values:\n"
    "  0 - Successful completion\n"
    "  1 - An error has occurred\n"
    "  7 - For burn command - FW already updated - burn was aborted.\n"
    "\n";




    const char* full_descr =
    "\n"
    MAN_SS("COMMAND DESCRIPTION")
    "\n"
    "* Burn flash\n"
    "  Performs failsafe FW update from a raw binary image.\n"
    "\n"
    "    Command:\n"
    "        b[urn]\n"
    "    Parameters:\n"
    "        None\n"
    "    Examples:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " -i image1.bin burn\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE2 " -guid 0x2c9000100d050 -i image1.bin b\n"
    "\n"
    "\n"
    "* Query miscellaneous FW and flash parameters\n"
    "  Display FW Version, GUIDs, PSID, and other info\n"
    "\n"
    "    Command:\n"
    "        q[uery]\n"
    "    Parameters:\n"
    "        None\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " query\n"
    "\n"
    "\n"
    "* Verify entire flash.\n"
    "\n"
    "    Command:\n"
    "        v[erify]\n"
    "    Parameters:\n"
    "        None\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " v\n"
    "\n"
    "\n"
    "* Burn the specified exp-ROM on the flash.\n"
    "\n"
    "    Command:\n"
    "        brom\n"
    "    Parameters:\n"
    "        file - The exp-ROM file.\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " brom exp-rom.rom\n"
    "\n"
    "* Remove the exp-ROM from the flash if it is existing.\n"
    "\n"
    "    Command:\n"
    "        drom\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " drom\n"
    "\n"
    "* Read the exp-ROM from the flash if it is existing.\n"
    "\n"
    "    Command:\n"
    "        rrom\n"
    "        file - filename to write the exp-ROM to.\n"

    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " rrom exp-rom.rom\n"
    "\n"
    "* Burn Block\n"
    "  Burns entire flash verbatim from raw binary image. No checks are done on the flash or\n"
    "  on the given image file. No fields (such as VSD or Guids) are read from flash. \n"
    "\n"
    "    Command:\n"
    "        bb\n"
    "    Parameters:\n"
    "        None\n"
    "    Examples:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " -i image1.bin bb\n"
    "\n"
    "\n"
    "* Set GUIDs\n"
    "  Set GUIDs/MACs/UIDs in the given device/image.\n"
    "  Use -guid(s), -mac(s) and -uid(s) flags to set the desired values.\n"
    "  - On pre-ConnectX devices, the sg command  is used in production to apply GUIDs/MACs values\n"
    "    to cards that were pre-burnt with blank GUIDs. It is not meant for\n"
    "    use in field\n"
    "  - On 4th generation devices, this command can operate on both image file and image on flash.\n"
    "    If the GUIDs/MACs/UIDs in the image on flash are non-blank,\n"
    "    flint will re-burn the current image using the given GUIDs/MACs/UIDs."
    "\n"
    "    Command:\n"
    "        sg\n"

    "    Parameters:\n"
    "        nocrc: (optional) When specified the flint would not update\n"
    "                the full image crc after changing the guids\n"
    "    Examples:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " -guid 0x0002c9000100d050 sg\n"
    "\n"
    "\n"
    "* Set VSD\n"
    "  Set VSD in the given device/image.\n"
    "  Use -vsd flag to set the desired VSD string.\n"
    "\n"
    "    Command:\n"
    "        sv\n"
    "    Parameters:\n"
    "       None.\n"
    "    Examples:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " -vsd VSD_STRING sv\n"
    "\n"
    "\n"

    "* Set manufacture GUID\n"
    "  Set manufacture GUIDs in the given FS3 image.\n"
    "  Use -uid flag to set the desired GUIDs.\n"
    "\n"
    "    Command:\n"
    "        smg\n"
    "    Parameters:\n"
    "       None.\n"
    "    Examples:\n"
    "        " FLINT_NAME " -i fw_image.bin -uid 0x0002c9000100d050 smg\n"
    "\n"
    "\n"


    "* Set Read-only VPD\n"
    "  Set VPD in the given FS3 image.\n"
    "\n"
    "    Command:\n"
    "        smg\n"
    "    Parameters:\n"
    "       None.\n"
    "    Examples:\n"
    "        " FLINT_NAME " -i fw_image.bin set_vpd vpd.bin\n"
    "\n"
    "\n"


    "* Print (to screen or to a file) the FW configuration text file used by the image generation process.\n"
    "  This command would fail if the image does not contain a FW configuration section. Existence of this\n"
    "  section depends on the version of the image generation tool.\n"
    "\n"
    "    Command:\n"
    "        dc\n"
    "    Parameters:\n"
    "        file - (optional) filename to write the dumped configuration to. If not given, the data\n"
    "               is printed to screen\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " dc\n"
    "\n"

    "* Print (to screen or to a file) the tracer HASH text file used by the FW.\n"
    "  This command would fail if the image does not contain a Hash file.\n"
    "\n"
    "    Command:\n"
    "        dth\n"
    "    Parameters:\n"
    "        file - (optional) filename to write the dumped tracer hash file to. If not given, the data\n"
    "               is printed to screen\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " dth hash.csv\n"
    "\n"

    "\n"
    "* Set/Update the HW access key which is used to enable/disable access to HW.\n"
    "\n"
    "    Command:\n"
    "        set_key\n"
    "    Parameters:\n"
    "        key - (optional) The new key you intend to set (in hex).\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " set_key 1234deaf5678\n"
    "\n"

    "* Enable/disable the access to the HW.\n"
    "\n"
    "    Command:\n"
    "        hw_access\n"
    "    Parameters:\n"
    "        <enable/disable> - Specify if you intend to disable or enable the HW access.\n"
    "                           You will be asked to type a key when you try to enable HW access.\n"
    "        key              - (optional) The key you intend to use for enabling the HW access.\n"

    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " hw_access enable\n"
    "\n"


#ifdef EXTERNAL
    "* Query HW info and flash attributes.\n"
    "    \nCommand:\n"
    "        hw\n"
    "    Parameters:\n"
    "        query\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " hw query\n"
#else
    "* Access HW info and flash attributes.\n"
    "    \nCommand:\n"
    "        hw\n"
    "    Parameters:\n"
    "        query                 - query HW info\n"
    "        set ATTR=VAL          - set flash attribure\n"
    "                                Supported attributes:\n"
    "                                  QuadEn can be 0 or 1\n"
    "                                  Flash[0|1|2|3].WriteProtected can be:\n"
    "                                  <Top|Bottom>,<1|2|4|8|16|32|64>-<Sectors|SubSectors>\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " hw query\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " hw set QuadEn=1\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " hw set Flash1.WriteProtected=Top,1-SubSectors\n"
#endif
    "\n"

    "* Erase sector.\n"
    "  Erases a sector that contains specified address.\n"
    "\n"
    "    Command:\n"
    "        e[rase]\n"
    "    Parameters:\n"
    "        addr - address of word in sector that you want\n"
    "                   to erase.\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " erase 0x10000\n"
    "\n"
    "\n"

    "* Read one dword from flash.\n"
    "\n"
    "    Command:\n"
    "        rw\n"
    "    Parameters:\n"
    "        addr - address of word to read\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " rw 0x20\n"
    "\n"
    "\n"
    "* Write one dword to flash.\n"
    "  Note that the utility will read an entire flash sector,\n"
    "  modify one word and write the sector back. This may take\n"
    "  a few seconds.\n"
    "\n"
    "    Command:\n"
    "        ww\n"
    "    Parameters:\n"
    "        addr - address of word\n"
    "        data - value of word\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " ww 0x10008 0x5a445a44\n"
    "\n"
    "\n"
    "* Write one dword to flash without sector erase.\n"
    "  Note that the result of operation is undefined and depends\n"
    "  on flash type. Usually \"bitwise AND\" (&) between specified\n"
    "  word and previous flash contents will be written to\n"
    "  specified address.\n"
    "\n"
    "    Command:\n"
    "        wwne\n"
    "    Parameters:\n"
    "        addr - address of word\n"
    "        data - value of word\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " wwne 0x10008 0x5a445a44\n"
    "\n"
    "* Read a data block from the flash and write it to a file or to screen.\n"
    "\n"
    "    Command:\n"
    "        rb\n"
    "    Parameters:\n"
    "        addr - address of block\n"
    "        size - size of data to read in bytes\n"
    "        file - filename to write the block (raw binary). If not given, the data\n"
    "               is printed to screen\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " rb 0x10000 100 file.bin\n"
    "\n"
    "* Read the FW image from flash and write it to a file.\n"
    "\n"
    "    Command:\n"
    "        ri\n"
    "    Parameters:\n"
    "        file - filename to write the image to (raw binary).\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " ri file.bin\n"
    "\n"
    "* Write a block of data to the flash without erasing.\n"
    "\n"
    "    Command:\n"
    "        wbne\n"
    "    Parameters:\n"
    "        addr - address of block\n"
    "        size - size of data to write in bytes\n"
    "        data - data to write - space seperated dwords\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " wbne 0x10000 12 0x30000 0x76800 0x5a445a44\n"
    "\n"
    MAN_SH("RETURN VALUES")
    "\n"
    "   0 - Successful completion\n"
    "   1 - An error has occurred\n"
    "   7 - For burn command - FW already updated - burn was aborted.\n"
#ifdef FOR_MAN
    MAN_SH("KNOWN ISSUES")
    "If flint is forcefully killed without giving it a chance to clean up,\n"
    "the HCA internal flash semaphore may not be released, and prevent further\n"
    "activation of flint. Use the -clear_semaphore flag to force clearing of\n"
    "this semaphore.\n"
#endif
;
    printf(descr);
    if (full) {
        printf(full_descr);
    }
}

// The Log file writing implementation

FILE* f_log_fh = NULL;
#define BURN_INTERRUPTED 0x1234


void close_log()
{
    if (f_log_fh != NULL) {
        fclose(f_log_fh);
    }
    return;
}

#define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])

const char*   month_2monstr (int month) {
    static const char* month_2monstr_arr[] = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec",
    };
    int arr_size = (int)ARR_SIZE(month_2monstr_arr);
    return month < arr_size ? month_2monstr_arr[month] : "???";
}


void print_time_to_log()
{
    time_t rawtime;
    struct tm * timeinfo;

    if (f_log_fh == NULL) {
        return;
    }

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    fprintf(f_log_fh, "%-3s %2d %02d:%02d:%02d ", month_2monstr(timeinfo->tm_mon), timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return;
}

int print_line_to_log(const char* format, ...)
{
    va_list  args;

    if (f_log_fh == NULL) {
        return 0;
    }
    print_time_to_log();
    va_start(args, format);
    vfprintf(f_log_fh, format, args);
    va_end(args);

    return 0;
}

int write_cmd_to_log(char* av[], int ac, CommandType cmd)
{
    int i;
    char pre_str[50];
    if (f_log_fh == NULL) {
        return 0;
    }
    if (cmd == CMD_BURN_ROM) {
        sprintf(pre_str, "ROM");
    } else {
        sprintf(pre_str, "FW");
    }
    print_time_to_log();
    fprintf(f_log_fh, "Start %s burning: ", pre_str);
    for (i = 0; i < ac; i++) {
        fprintf(f_log_fh, "%s ", av[i]);
    }
    fprintf(f_log_fh, "\n");

    return 0;
}

int write_result_to_log(int is_failed, const char* err_msg)
{
    char msg[MAX_ERR_STR_LEN];

    strcpy(msg, err_msg);
    if (is_failed == 0) {
        print_line_to_log("Burn completed successfully\n");
    } else if (is_failed == BURN_INTERRUPTED) {
        print_line_to_log("Burn interrupted by user\n");
    } else {
        int msg_len = strlen(msg);
        // cleanup the msg
        for (int i = 0; i < msg_len; i++) {
            if (msg[i] == '\n') {
                if (i == msg_len - 1) {
                    msg[i] = '\0';
                } else {
                    msg[i] = ' ';
                }
            }
        }
        print_line_to_log("Burn failed: %s\n", msg);
    }
    return 0;
}



//
// Signal handlers
//

Flash* g_flash = NULL;

#ifdef _WIN32

HANDLE main_thread;

#define GET_MAIN_THREAD() {\
     int rc = DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(),\
                              &main_thread, 0, FALSE, DUPLICATE_SAME_ACCESS);\
     if (rc == 0) {\
         main_thread = NULL;\
     }\
}

#define CHECK_WIN_SIGNAL() {\
     if (main_thread == NULL) {\
         report_warn("An internal error occurred. This program can not be interrupted.\n");\
         signal(signum, TerminationHandler);\
         return;\
     }\
}

#define SUSPEND_MAIN_THREAD() {\
     SuspendThread(main_thread);\
}

#else

#define GET_MAIN_THREAD()
#define WIN_TERM_THREAD()
#define CHECK_WIN_SIGNAL()
#define SUSPEND_MAIN_THREAD()
#endif




int g_signals_for_termination[] = {
    SIGINT,
#ifndef _WIN32
    SIGHUP,
    SIGPIPE,
#endif
    SIGTERM
};



void TerminationHandler (int signum)
{
    static volatile sig_atomic_t fatal_error_in_progress = 0;

    CHECK_WIN_SIGNAL();
    if (fatal_error_in_progress)
        raise (signum);
    fatal_error_in_progress = 1;

    signal (signum, SIG_DFL);

    write_result_to_log(BURN_INTERRUPTED, "");
    close_log();
    if (g_flash != NULL) {
        report("\n Received signal %d. Cleaning up ...", signum);
        fflush(stdout);
        SUSPEND_MAIN_THREAD();
        sleep(1); // let erase sector end
        //g_flash->wait_ready("Process termination");

        g_flash->close();
        report(" Done.\n");
    }
    raise(signum);
}

int get_num_of_banks(char* env, int* num_of_banks)
{
    char* endp;

    *num_of_banks = strtoul(env, &endp, 0);
    if (*endp != '\0' || (*num_of_banks < 1 || *num_of_banks > 4)) {
        return 1;
    }
    return 0;
}



#define INCR_GUID(base_guid, user_guid, incr_val) { \
            u_int64_t g = base_guid.h;              \
            g = (g << 32) | base_guid.l;            \
            g += incr_val;                          \
            user_guid.h = (u_int32_t)(g >> 32);     \
            user_guid.l = (u_int32_t)g;             \
}

guid_t GetBaseMac(guid_t base_guid)
{
    guid_t base_mac;
    base_mac.l = (base_guid.l & 0x00ffffff) | ((base_guid.h & 0xff00) << 16);
    base_mac.h = base_guid.h >> 16;
    return base_mac;
}

bool InitBxGuids(guid_t* user_guids, guid_t base_guid1) {

    int base_index = 0;
    guid_t base_mac, base_guid;

    for (int i = 0; i < Operations::BX_SLICES_NUM; i++) {
        base_index = i * Operations::BX_SLICE_GUIDS;
        INCR_GUID(base_guid1, base_guid, i * 8);
        // Init Guids
        int base_guids_index = base_index + Operations::BI_GUIDS;

        for (int j = 0; j < Operations::BX_NP_GUIDS; j++) {
            if (j == 0) {
                // The node guid should be the same one on the two slices.
                INCR_GUID(base_guid1, user_guids[base_guids_index + j], j);
            } else {
                INCR_GUID(base_guid, user_guids[base_guids_index + j], j);
            }

        }
        // Init Macs
        base_mac = GetBaseMac(base_guid);
        int base_macs_index = base_index + Operations::BI_IMACS;
        for (int j = 0; j < Operations::BX_MACS; j++) {
            INCR_GUID(base_mac, user_guids[base_macs_index + j], j);
        }
        // Init WWPNSs
        int base_wwpn_index = base_index + Operations::BI_WWPNS;
        int base_emac_index = base_index + Operations::BI_EMACS;

        for (int j = 0; j < Operations::BX_WWPNS; j++) {
            user_guids[base_wwpn_index + j].l =  user_guids[base_emac_index + j].l;
            user_guids[base_wwpn_index + j].h = (user_guids[base_emac_index + j].h | (0x2000 << 16));
        }

        // Init WWNNS
        int base_wwnn_index = base_index + Operations::BI_WWNNS;
        base_emac_index = base_index + Operations::BI_EMACS;

        user_guids[base_wwnn_index].l =  user_guids[base_emac_index].l;
        user_guids[base_wwnn_index].h = (user_guids[base_emac_index].h | (0x2001 << 16));
    }

    // Init SysGuid
    INCR_GUID(base_guid1, user_guids[Operations::BI_SYS_GUID], 7);
    return true;
}

bool IsCmdSupportLog(CommandType cmd) {

    switch (cmd) {
        case CMD_BURN:
        case CMD_BURN_BLOCK:
        case CMD_BURN_ROM:
            return true;
        default:
            return false;
    }
    return false;
}

void PrintFSBurnErr(Flash& f, Operations& ops, const char* operation)
{
    ops.PrepareBurnErr(f);
    report_err(ops._err_msg, "%s Failed: %s\n", operation, ops.err());
    return;
}


#ifdef __WIN__
    #define WIN_NOT_SUPPORTED_GOTO(cmd, rc, label) do { \
		report_err(ops._err_msg,"%s command is not supported in windows.\n", cmd); rc = 1; goto label;\
    } while(0);
#else
    #define WIN_NOT_SUPPORTED_GOTO(cmd, rc, label)
#endif






////////////////////////////////////////////////////////////////////////
//

// Return values:
#define RC_FW_ALREADY_UPDATED 7

#define NEXTS(s) do {                                        \
    if (++i >= ac)                                           \
    {                                                        \
        report_err(ops._err_msg, "Missed parameter after \"%s\" switch\n", s); \
        return 1;                                            \
    }} while(0)
#define NEXTC(p, s) do {                                           \
    if (++i >= ac)                                                 \
    {                                                              \
        report_err(ops._err_msg, "Missed %s parameter after \"%s\" command\n", p,s); \
        return 1;                                                  \
    }} while(0)

#define SETERR(args) do { printf("*** ERROR *** "); printf args; printf("\n"); return 1; } while(0)

#define GET_PASSWORD_FROM_USER(pre_str, key_struct_p) {\
	    char key_arr[MAX_PASSWORD_LEN];\
	    GetPasswordFromUser(pre_str, key_arr);\
	    GETKEY(key_arr, key_struct_p);\
}

#define GET_KEY_FROM_USER(command, key_struct_p, from_password_p) {\
        if (i + 2 == ac) {\
            NEXTC("<HW_ACCESS_KEY>", command);\
            GETKEY(av[i], key_struct_p);\
            *from_password_p = 0;\
        } else {\
        	GET_PASSWORD_FROM_USER("Enter key ", key_struct_p);\
        	*from_password_p = 1;\
        }\
}

#define MAX_PASSWORD_LEN 256
#if !defined(__WIN__) && !defined(__DJGPP__)
int mygetch(void)
{
    struct termios oldt,
    newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
// TODO: Move this function to the tools common file.
int GetPasswordFromUser(char *pre_str, char buffer[MAX_PASSWORD_LEN])
{
    char c;
    int pos = 0;

    printf("%s: ", pre_str);
    do {
        c = mygetch();

        if( ((pos < MAX_PASSWORD_LEN - 1)) && isprint(c) ) {
            buffer[ pos++ ] = c;
            printf("%c", '*');
        } else if( (c == 8 || c == 127) && pos ) {
            buffer[ pos-- ] = '\0';
            printf("%s", "\b \b");
        }

    } while( c != '\n' );
    printf("\n");
    buffer[pos] = '\0';
    return true;
}

#else
int GetPasswordFromUser(char *pre_str, char buffer[MAX_PASSWORD_LEN])
{
    printf("%s: ", pre_str);
    scanf("%s", buffer);
    return true;
}

#endif

int main(int ac, char *av[])
{
    char         *image_fname=0, *device=0, *log_file=0;
    bool         clear_semaphore    = false;
    bool         silent             = false;
    bool         guids_specified    = false;
    bool         macs_specified     = false;
    bool         uids_specified     = false;
    bool         burn_failsafe      = true;
    bool         use_image_ps       = false;
    bool         use_image_guids    = false;
    bool         use_image_rom      = false;
    bool         single_image_burn  = true;
    bool         checkMatchingDevId = true;
    bool         allowPsidChange    = false;
    bool         allowdRomChange    = false;
    bool         writeToLog         = false;
    bool         ignoreCompatCheck  = false;
    bool         is_hw_cmd_set      = false; // The default of the hw command is query in order to run query when we have CFI (backward compatible)
    bool         img_type_given     = false;
    const char*  cmdStr             = NULL;
    char         *param_to_set = NULL;
    char         *user_vsd=0;
    char         *user_psid=0;
    guid_t       user_guids[Operations::MAX_GUIDS];
    guid_t       base_guid;
    int          rc = 0;
    int          num_of_banks = 0;
    int          ignoreCasheRepGuard = 0;
    u_int8_t     img_type = Operations::FS_FS2_GEN;
    flash_params_t flash_params;
    flash_params_t *flash_params_p = NULL;


    CommandType cmd = CMD_UNKNOWN;
    u_int32_t     dump_sect_type = H_FW_CONF;
    auto_ptr<Flash>       f;
    auto_ptr<Flash>       tmp_flash(new Flash);

    FImage                fim;

    Operations            ops;

    FBase*      fbase     = NULL;
    const char* cmdTarget = NULL;
    const char* cmdAccess = NULL;

    u_int32_t        fs2_image  = 0;
    u_int32_t        fs2_device = 0;
    u_int8_t    is_cr_space_locked = 0;
    u_int8_t fs_gen = 0;

    Operations::ImageInfo binImageInfo, flashImageInfo, mainImageInfo;
    bool fwFlashInfoOK = false, fwImageInfoOK = false, mainImageInfoOK = false;
    //
    // Map termination signal handlers
    //
    int i;
    for (i = 0 ; i < (int)(sizeof(g_signals_for_termination)/sizeof(g_signals_for_termination[0])) ; i++ ) {
        signal (g_signals_for_termination[i], TerminationHandler);
    }
    GET_MAIN_THREAD();

    if (ac < 2) {
        usage();
        rc =  1; goto done;
    }

    // Init with FFs - for ConnectX if only MAC or GUID is specified
    memset(user_guids, 0xff, sizeof(user_guids));

    // Go thru command line options
    for (i=1; i < ac; i++) {
        //
        // Switches
        // --------
        //
        if (*av[i] == '-') {
            int switchLen = strlen(av[i]);

            if (!strcmp(av[i], "-dual_image"))
                single_image_burn = false;

            else if (!strcmp(av[i], "-clear_semaphore")) {
                clear_semaphore = true;
            }

            else if (!strncmp(av[i], "-device", switchLen)) {
                NEXTS("-device");
                device = av[i];

            } else if (!strcmp(av[i], "-v") || !strcmp(av[i], "-vv")) {
            #ifdef EXTERNAL
                print_version_string("flint", "");
            #else
                print_version_string("flint(internal)", "");
            #endif
                rc =  0; goto done;
            } else if (!strcmp(av[i], "-unlock")) {
                _unlock_bypass = true;
            } else if (!strcmp(av[i], "-noerase")) {
                _no_erase = true;
            } else if (!strcmp(av[i], "-noburn")) {
                 _no_burn = true;
            } else if (!strcmp(av[i], "-crc")) {
                 _print_crc = true;
            } else if (!strcmp(av[i], "-bytewrite")) {
                if (device) {
                    report_err(ops._err_msg, "\"-bytewrite\" should be specified before \"-device\" switch in the command line.\n");
                    rc =  1; goto done;
                }
                _byte_write = true;
            } else if (!strcmp(av[i], "-vsd")) {
                NEXTS("-vsd");
                user_vsd = av[i];
            } else if (!strncmp(av[i], "-image", switchLen)) {
                NEXTS("-image");
                image_fname = av[i];
            } else if (!strcmp(av[i], "-guid")) {
                NEXTS("-guid");
                GETGUID(av[i], &user_guids[0]);
                for (int i=1; i<Operations::GUIDS; i++) {
                    INCR_GUID(user_guids[0], user_guids[i], i);
                }
                guids_specified = true;
            } else if (!strcmp(av[i], "-guids")) {
                if (i + 4 >= ac) {
                    report_err(ops._err_msg, "Exactly four GUIDs must be specified.\n");
                    rc =  1; goto done;
                }
                i++;
                for (int j=0; j<Operations::GUIDS; j++) {
                    GETGUID(av[i+j], &user_guids[j]);
                }
                i += 3;
                guids_specified = true;

            } else if (!strcmp(av[i], "-mac")) {
                NEXTS("-mac");
                GETGUID(av[i], &user_guids[Operations::GUIDS]);
                for (int i=1; i < Operations::MACS ; i++) {
                    INCR_GUID(user_guids[Operations::GUIDS], user_guids[Operations::GUIDS + i], i);
                }
                macs_specified = true;
            } else if (!strcmp(av[i], "-macs")) {
                if (i + 2 >= ac) {
                    report_err(ops._err_msg, "Exactly two MACs must be specified.\n");
                    rc =  1; goto done;
                }
                i++;
                for (int j=0; j<Operations::MACS; j++) {
                    GETGUID(av[i+j], &user_guids[Operations::GUIDS+j]);
                }
                i += 1;
                macs_specified = true;
            } else if (!strcmp(av[i], "-uid")) {
                NEXTS("-uid");
                GETGUID(av[i], &base_guid);
                InitBxGuids(user_guids, base_guid);
                uids_specified = true;
            } else if (!strcmp(av[i], "-uids")) {
                if (i + Operations::BX_ALL_GUIDS >= ac) {
                    report_err(ops._err_msg, "Exactly %d UIDs must be specified.\n", Operations::BX_ALL_GUIDS);
                    rc =  1; goto done;
                }
                i++;
                for (int j = 0; j < Operations::BX_ALL_GUIDS; j++) {
                    GETGUID(av[i+j], &user_guids[j]);
                }
                i += (Operations::BX_ALL_GUIDS - 1);
                uids_specified = true;
            } else if (!strcmp(av[i], "-banks")) {
                NEXTS("-banks");
                rc = get_num_of_banks(av[i], &num_of_banks);
                if (rc) {
                    report_err(ops._err_msg, "Bad number of banks(%s), it should be between 1 and 4\n", av[i]);
                    rc = 1; goto done;
                }
            } else if (!strcmp(av[i], "-log")) {
                NEXTS("-log");
                log_file   = av[i];
                writeToLog = true;
            } else if (!strcmp(av[i], "-flash_params")) {
                NEXTS("-flash_params");
                GET_FLASH_PARAMS(av[i], &flash_params);
                flash_params_p = &flash_params;
            } else if (!strcmp(av[i], "-img_type")) {
                NEXTS("-img_type");
                char *img_type_str = av[i];
                //GET_FLASH_PARAMS(av[i], &flash_params);
                img_type_given = true;
                if (!strcmp(img_type_str, "FS2")) {
                    img_type = Operations::FS_FS2_GEN;
                } else if (!strcmp(img_type_str, "FS3")) {
                    img_type = Operations::FS_FS3_GEN;
                } else {
                    report_warn("Unknown image type: %s, supported types: FS2, FS3\n", img_type_str);
                    img_type_given = false;
                }
            } else if (!strncmp(av[i], "-silent", switchLen))
                silent = true;
            else if (!strcmp(av[i], "-use_image_ps"))
                use_image_ps = true;
            else if (!strcmp(av[i], "-use_image_guids"))
                use_image_guids = true;
            else if (!strcmp(av[i], "-use_image_rom"))
                use_image_rom = true;
            else if (!strcmp(av[i], "-no_devid_check"))
                checkMatchingDevId = false;
            else if (!strncmp(av[i], "-nofs", 5))
                burn_failsafe = false;
            else if (!strcmp(av[i], "-striped_image"))
                ops.SetFs2StripedImage(true);
            else if (!strcmp(av[i], "-blank_guids"))
                ops.SetBurnBlankGuids(true);
            else if (!strcmp(av[i], "-qq"))
                ops.SetQuickQuery(true);
            else if (!strncmp(av[i], "-yes", switchLen))
                _assume_yes = true;
            else if (!strcmp(av[i], "-no"))
                _assume_no = true;
            else if (!strcmp(av[i], "-byte_mode"))
                Flash::_byte_mode = true;
            else if (!strcmp(av[i], "-no_flash_verify"))
                Flash::_no_flash_verify = true;
            else if (!strcmp(av[i], "-allow_psid_change"))
                 allowPsidChange = true;
            else if (!strcmp(av[i], "-allow_rom_change"))
                allowdRomChange = true;
            else if (!strcmp(av[i], "-override_cache_replacement") || !strcmp(av[i], "-ocr")) {
                ignoreCasheRepGuard = 1;
            } else if (!strcmp(av[i], "-no_compat_check")) {
                ignoreCompatCheck = true;
            } else if (!strncmp(av[i], "-hh", 3) ||  !strncmp(av[i], "--hh", 4)) {
                usage(true);
                rc =  0; goto done;
            } else if (!strncmp(av[i], "-help", switchLen) ||  !strncmp(av[i], "--h", 3)) {
                usage();
                rc =  0; goto done;
            } else {
                report_err(ops._err_msg, "Invalid switch \"%s\" is specified.\n", av[i]);
                rc =  1; goto done;
            }
        } else {
            // Command
            cmdStr = av[i];
            break;
        }
    }
    if (_assume_yes && _assume_no) {
        report_err(ops._err_msg, "-yes and -no options can not be specified together.\n");
        rc =  1; goto done;
    }

    if (ops.GetBurnBlankGuids() && (guids_specified || macs_specified || uids_specified)) {
        report_err(ops._err_msg, "-blank_guids and (-uid(s) -guid(s) -mac(s)) options can not be specified together.\n");
        rc =  1; goto done;
    }


    //
    // Commands
    // --------
    //

    if (clear_semaphore) {
        if (cmdStr) {
            report_err(ops._err_msg, "No command is allowed when -clear_semaphore flag is given.\n");
            rc =  1; goto done;
        } else {
            cmdStr = "clear_semaphore";
        }
    }

    if (!cmdStr) {
        report_err(ops._err_msg, "No command given. See help for details.\n");
        rc =  1; goto done;
    }

    //
    // Check and parse command
    //
    cmd = ParseCommand(cmdStr);

    if (cmd == CMD_UNKNOWN) {
        report_err(ops._err_msg, "Invalid command \"%s\".\n", av[i]);
        rc =  1; goto done;
    }

    if (cmd == CMD_CLEAR_SEM) {
        clear_semaphore = true;
    }

    if (!ops.CheckCommandInputs(device, image_fname, cmd)) {
        rc = 1; goto done;
    }

    if (!ops.CheckMaxCmdArguments(cmd, ac - i - 1)) {
        rc = 1; goto done;
    }

    if (device) {
        // Open the device
        f = tmp_flash;

        if (f.get() == NULL) {
            report_err(ops._err_msg, "Memory allocation failed\n");
            rc =  1; goto done;
        }
        if (ignoreCasheRepGuard) {
            report_warn("Firmware flash cache access is enabled. Running in this mode may cause the firmware to hang.");
        }

        g_flash = f.get();
        if (!f->open(device, clear_semaphore, false, num_of_banks, flash_params_p, ignoreCasheRepGuard)) {
            is_cr_space_locked = f->get_cr_space_locked();

            // We will ignore this failure when we want to disable/enable the HW access
            if (!(is_cr_space_locked && cmd == CMD_HW_ACCESS)) {
                report_err(ops._err_msg, "Can not open %s: %s\n", device, f->err());
                rc =  1; goto done;
            }

        }

        ops.SetNumPorts(f->get_port_num());

        cmdTarget = "Flash";
        cmdAccess = device;
        fbase     = f.get();

        // Connectx Mode:
        fs2_device = ops.CheckIsFs2(*fbase);
    }

    if (image_fname) {
        if (!fim.open(image_fname)) {
            report_err(ops._err_msg, "Image file open failed: %s\n", fim.err());
            rc =  1; goto done;
        }

        cmdTarget = "Image file";
        cmdAccess = image_fname;
        fbase     = &fim;

        // Connectx mode:
        fs2_image = ops.CheckIsFs2(fim);
    }
    /*
    if (fs2_image && fs2_device && (fs2_image != fs2_device)) {
        report_err(ops._err_msg, "Image file and image burnt into device are not from the same type\n", fim.err());
        rc =  1; goto done;
    }
    */

    if (img_type_given) {
        fs_gen = img_type;
    } else {
        if (fs2_image || fs2_device) {
            fs_gen = (fs2_device == 0) ? fs2_image : fs2_device;
        }
    }
    if (!is_cr_space_locked && cmd != CMD_QUERY_ROM && fs_gen == Operations::FS_OLD_GEN) {
        report_err(ops._err_msg, "Image/Device type is not supported: old or unknown type.\n");
        rc =  1; goto done;
    }
    ops.SetFsGen(fs_gen);

    if (device) {
        // Get the info of the FW burnt in the flash and Check compatibilty with FW
        if (!ops.GetInfoAndCheckCompt(*f, flashImageInfo, fwFlashInfoOK, ignoreCompatCheck)) {
            report_err(ops._err_msg, "%s", ops.err());
            rc = 1; goto done;
        }
        mainImageInfo = flashImageInfo;
        mainImageInfoOK = fwFlashInfoOK;

        // Disable the address convertor to not disturb the other functions
        f->set_address_convertor(0,0);
    }

    if (image_fname) {
        // Get the info of the FW burnt in the flash and Check compatibilty with FW
        if (!ops.GetInfoAndCheckCompt(fim, binImageInfo, fwImageInfoOK, ignoreCompatCheck)) {
            report_err(ops._err_msg, "%s", ops.err());
            rc = 1; goto done;
        }
        if (!device) {
            mainImageInfo = binImageInfo;
            mainImageInfoOK = fwImageInfoOK;
        }

    }


    // Get environment variables
    if (!writeToLog) {
        log_file = getenv(FLINT_LOG_ENV);
        if (log_file) {
            writeToLog = true;
        }
    }
    if (getenv(FLINT_IGNORE_TTY)) {
        ops.SetIgnoreTty(true);
    }


    // Open Log file if it was asked to.
    if (writeToLog == true) {
        if (IsCmdSupportLog(cmd)) {
            f_log_fh = fopen(log_file, "a+");
            if (f_log_fh == NULL) {
                report_warn("Failed to open log file \"%s\": %s. No logs will be saved\n", log_file,
                            strerror(errno));
            }
            write_cmd_to_log(av, ac, cmd);
        }
    }

    switch (cmd) {
    case CMD_BURN:
    case CMD_BURN_BLOCK:
        {
            //
            // BURN
            //
            Operations::ImageInfo fileInfo, tmpFileInfo;
            Operations::ImageInfo flashInfo;
            bool burn_block = (cmd == CMD_BURN_BLOCK);


            if (!burn_block) {
                if (ops.IsFs3()) {
                    if (!ops.BurnFs3Image(*f, fim, !silent)) {
                        report_err(ops._err_msg, "Burning FS3 image failed: %s\n", ops.err());
                        rc = 1; goto done;
                    }
                    return 0;
                }

                if (ops.GetFs2StripedImage()) {
                    report_err(ops._err_msg, "The -striped_image cannot be used with the burn command\n");
                    rc = 1; goto done;
                }

                if (fs2_image != fs2_device) {
                    report_err(ops._err_msg, "The given device %s a FS2 image type, but the given image file %s a FS2 FW image\n",
                           fs2_device ? "requires" : "does not require",
                           fs2_image  ? "contains" : "does not contain");
                    rc =  1; goto done;
                }

                // Make checks and replace vsd/guids.
                bool old_silent = _silent;
                _silent = true;
                if (!ops.Verify(fim, &tmpFileInfo) || !ops.QueryAll(fim, &tmpFileInfo)) {
                    report_err(ops._err_msg, "%s: Not a valid image file (%s)\n", image_fname, ops.err());
                    rc =  1; goto done;
                }

                if (checkMatchingDevId) {
                    if (tmpFileInfo.infoOffs[Operations::II_HwDevsId]) {
                        if (!ops.CheckMatchingHwDevId(f->get_dev_id(),
                                                    f->get_rev_id(),
                                                    tmpFileInfo)) {
                            report_err(ops._err_msg, "Device/Image mismatch: %s\n",
                                   ops.err());
                            rc =  1; goto done;
                        }
                    } else if (tmpFileInfo.infoOffs[Operations::II_DeviceType]) {

                        if (!ops.CheckMatchingDevId(f->get_dev_id(), tmpFileInfo.devType)) {
                            report_err(ops._err_msg, "Device/Image mismatch: %s\n",
                                   ops.err());
                            rc =  1; goto done;
                        }
                    }
                }


                // Get GUID and VSD info from flash

                bool read_guids = true;

                // Flash query (unlike image file query) does not have to
                // pass. E.G. blank flash and the user supplies the needed data (guids, vsd).

                bool flash_query_res= true;
                if (ops.GetQuickQuery()) {
                    report_warn("Running quick query - Skipping full image integrity checks.\n");
                    ops.initSectToRead(H_ROM);
                    if (ops.IsFs2()) {
                        flash_query_res = ops.VerifyFs2(*f, &flashInfo, false);
                    }

                    if (flash_query_res) {
                        flash_query_res = ops.QueryAll(*f, &flashInfo);
                    }
                } else {
                    flash_query_res = ops.Verify(*f, &flashInfo) && ops.QueryAll(*f, &flashInfo);
                }

                // Check exp rom:
                if (flash_query_res && (ops.CntxIsEth(flashInfo.devType) || ops.CntxIsIb(flashInfo.devType)) &&
                    (ops.IsFwSupportingRomModify(tmpFileInfo.fwVer) || tmpFileInfo.expRomFound) && !use_image_rom &&
                    !flashInfo.infoOffs[Operations::II_ProductVer]) {
                    // Enter here when:
                    //                  The fw on the flash is ok &&
                    //                  The device is hermon      &&
                    //                  The image fw supports modifying ROM OR it contains ROM &&.
                    //                  The user didn't ask to burn the image rom.
                    //                  The  fw on the flash doesn't contain product version

                    bool getRomFromDev = false;

                    if (tmpFileInfo.expRomFound && flashInfo.expRomFound) {
                        printf("\n    Note: Both the image file and the flash contain a ROM image.\n"
                               "          Select \"yes\" to use the ROM from the given image file.\n"
                               "          Select \"no\" to keep the existing ROM in the flash\n");
                        _silent = false;
                        ops.DisplayExpRomInfo(&flashInfo, "    Current ROM info on flash: ");
                        ops.DisplayExpRomInfo(&tmpFileInfo, "    ROM info from image file : ");
                        _silent = true;

                        if (!ops.ask_user("Use the ROM from the image file")) {
                            getRomFromDev = true;
                        } else {
                            getRomFromDev = false;
                        }
                    } else if (!tmpFileInfo.expRomFound && flashInfo.expRomFound) {
                        getRomFromDev = true;
                    }

                    if (getRomFromDev == true) {
                        if (!ops.IntegrateDevRomInImage(fim, flashInfo, fileInfo)) {
                            report_err(ops._err_msg, "Failed to integrate the device rom into the Image: %s\n",
                                       ops.err());
                            rc = 1; goto done;
                        }
                    } else {
                        fileInfo = tmpFileInfo;
                    }
                } else {
                    fileInfo = tmpFileInfo;
                }

                if (!ops.CheckMatchingExpRomDevId(&fileInfo)) {
                    report_warn("Image file ROM: %s\n", ops.err());
                    if (!ops.ask_user()) {
                        rc =  1; goto done;
                    }
                }

                bool ib_dev;
                bool eth_dev;
                bool bx_dev;
                // Get the FW types
                bx_dev = ops.IsBridgeX(fileInfo.devType);
                ops.SetDevFlags(fileInfo.devType, ib_dev, eth_dev);

                // Check if there is a need to read guids
                if (use_image_guids || ops.GetBurnBlankGuids() || (guids_specified && ib_dev) ||
                    (macs_specified && eth_dev) || (uids_specified && bx_dev)) {
                    read_guids = false;
                }
                // Check if the burnt FW is ok and readable in order to get the GUIDs later
                if (read_guids && !flash_query_res) {
                    ops.PrintMissGuidErr(ib_dev, eth_dev, bx_dev);
                    if (burn_failsafe) {
                        report_err(ops._err_msg,
                        "Can not extract GUIDs info from flash, %s\n"
                        "    Can not burn in a failsafe mode.\n"
                        "    If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n", ops.err());
                    } else {
                        report_err(ops._err_msg, "Can not extract GUIDs info from flash, %s\n", ops.err());
                    }
                    rc =  1; goto done;
                }
                bool  is_guids_specified  =  guids_specified || macs_specified || uids_specified;
                // Patch GUIDS
                if (is_guids_specified) {
                    if (!ops.CheckGuidsFlags(fileInfo.devType, guids_specified, macs_specified, uids_specified)) {
                        report_err(ops._err_msg, "%s\n", ops.err());
                        rc =  1; goto done;
                    }
                    if (!ops.patchGUIDs(fim,
                                        &fileInfo,
                                        eth_dev,
                                        bx_dev,
                                        guids_specified,
                                        macs_specified,
                                        uids_specified,
                                        user_guids,
                                        flashInfo.imageOk ? flashInfo.guids : NULL,
                                        flashInfo.guidNum)) {
                        rc =  1; goto done;
                    }
                } else if (!use_image_guids) {
                    if (!ops.patchGUIDs(fim,
                                        &fileInfo,
                                        eth_dev,
                                        bx_dev,
                                        false,
                                        false,
                                        false,
                                        NULL,
                                        flashInfo.guids,
                                        flashInfo.guidNum)) {
                        rc =  1; goto done;
                    }
                }

                if (is_guids_specified || use_image_guids) {
                    guid_t* new_guids = user_guids;
                    guid_t* old_guids = flashInfo.imageOk ? flashInfo.guids : NULL;
                    if (!is_guids_specified && use_image_guids) {
                        new_guids = fileInfo.guids;
                    }
                    if (!ops.reportGuidChaneges(&fileInfo, new_guids, old_guids, ib_dev, eth_dev, bx_dev)) {
                        rc =  1; goto done;
                    }

                }


                if (burn_failsafe & (!fileInfo.isFailsafe || !flashInfo.isFailsafe)) {

                    if ((!fileInfo.isFailsafe && !flashInfo.isFailsafe)) {
                        // When both image and flash are non-failsafe, flint will burn in a non-failsafe mode
                        burn_failsafe = false;
                    } else {
                        // when only one of image and flash is non-failsafe, flint will fail with appropriate message
                        report_err(ops._err_msg, "Failsafe burn failed: FW image in the %s is non failsafe.\n"
                        "    you cannot burn a%s failsafe image over a%s failsafe image in a failsafe mode.\n"
                        "    If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n",
                        fileInfo.isFailsafe ? "flash" : "given file", fileInfo.isFailsafe ? "" : " non",  flashInfo.isFailsafe ? "" : " non");

                        rc =  1; goto done;
                    }
                }

                if (!user_vsd && !(flashInfo.psOk || (flashInfo.infoOffs[Operations::II_PSID] &&
                                                      flashInfo.infoOffs[Operations::II_VSD]  ))) {
                    printf("\n");
                    if (burn_failsafe) {

                        report_err(ops._err_msg, "Can not extract VSD/PSID info from flash.\n"
                                  "    Can not burn in a failsafe mode. Please use \"-nofs\" flag to burn in a non failsafe mode.\n");
                        rc =  1; goto done;
                    } else {
                        report_warn("Can not extract VSD/PSID info from flash.\n\n"
                               "    To use a specific VSD, abort and re-burn specifying the\n"
                               "    needed info (using command line flags -vsd / -use_image_ps).\n"
                               "    You can also continue burn using blank VSD.\n");

                        if (!ops.ask_user()) {
                            rc =  1; goto done;
                        }
                    }
                }

                // Print FW versions:
                printf("\n");
                char curr_ver[124], new_ver[124];
                printf("    Current FW version on flash:  ");
                if (flashInfo.infoOffs[Operations::II_FwVersion]) {
                    sprintf(curr_ver, "%d.%d.%d", flashInfo.fwVer[0], flashInfo.fwVer[1], flashInfo.fwVer[2]);
                } else {
                    sprintf(curr_ver, "N/A");
                }
                printf(curr_ver); printf("\n");

                printf("    New FW version:               ");
                if (fileInfo.infoOffs[Operations::II_FwVersion]) {
                    sprintf(new_ver, "%d.%d.%d", fileInfo.fwVer[0], fileInfo.fwVer[1], fileInfo.fwVer[2]);
                } else {
                    sprintf(new_ver, "N/A");
                }
                printf(new_ver); printf("\n");

                print_line_to_log("Current FW version on flash: %s,  New FW version: %s\n", curr_ver, new_ver);

                bool updateRequired = true;

                if (fileInfo.infoOffs[Operations::II_FwVersion]  &&
                    flashInfo.infoOffs[Operations::II_FwVersion]) {

                    updateRequired = ops.FwVerLessThan(flashInfo.fwVer, fileInfo.fwVer);
                }

                if (!updateRequired) {
                    printf("\n    Note: The new FW version is not newer than the current FW version on flash.\n");
                    if (! ops.ask_user()) {
                        rc =  RC_FW_ALREADY_UPDATED; goto done;
                    }
                }

                if (fileInfo.infoOffs[Operations::II_IsGa] && !fileInfo.isGa) {
                    printf("\n    Note: You are attempting to burn a pre-production FW image.\n");
                    if (! ops.ask_user()) {
                        rc =  1; goto done;
                    }
                }

                if (!use_image_ps) {
                    if (fileInfo.psOk || (ops.IsFs2() && fileInfo.infoOffs[Operations::II_VSD])) {
                        if (!ops.patchVSD(fim,
                                          &fileInfo,
                                          user_vsd,
                                          user_psid,
                                          flashInfo.vsd,
                                          NULL,
                                          fileInfo.psid )) {
                            rc =  1; goto done;
                        }
                    }
                }
                if (!ops.patchHwAccessKey(fim, flashInfo, fileInfo)) {
                    rc =  1; goto done;
                }

                // Check PSID and ib -> eth change.
                if (fileInfo.infoOffs[Operations::II_PSID]  &&
                    flashInfo.infoOffs[Operations::II_PSID] &&
                    strncmp( fileInfo.psid, flashInfo.psid, PSID_LEN)) {
                    if (ops.IsFs2() &&
                        (!ib_dev && eth_dev) &&
                        flashInfo.infoOffs[Operations::II_DeviceType] &&
                        ops.CntxIsIb(flashInfo.devType) &&
                        !ops.CntxIsEth(flashInfo.devType)) {

                        printf("\n    You are about to replace FW image type from IB to ETH image.\n");
                        if (! ops.ask_user()) {
                            rc =  1; goto done;
                        }
                    } else {
                        if (allowPsidChange) {
                            printf("\n    You are about to replace current PSID on flash - \"%s\" with a different PSID - \"%s\".\n"
                                   "    Note: It is highly recommended not to change the PSID.\n",
                                   flashInfo.psid,
                                   fileInfo.psid);
                            if (! ops.ask_user()) {
                                rc =  1; goto done;
                            }

                        } else {
                            printf("\n");
                            report_err(ops._err_msg, "PSID mismatch. The PSID on flash (%s) differs from the PSID in the given image (%s).\n",
                                   flashInfo.psid,
                                   fileInfo.psid);
                            //printf("    It is highly recommended not to change the PSID. To force a PSID change, use the -allow_psid_change flag\n");
                            rc =  1; goto done;
                        }
                    }

                }



                // Verify config offset. Should never be different between image and flash (unless changing PSID).
                if (fileInfo.configPad != flashInfo.configPad) {
                    printf("\n");
                    report_err(ops._err_msg, "Configuration section offset on flash (%d) differs from the Configuration section offset in the given image (%d).\n",
                                   flashInfo.psid,
                                   fileInfo.psid);
                    if (allowPsidChange) {
                        if (! ops.ask_user()) {
                            rc =  1; goto done;
                        }
                    } else {
                        rc =  1; goto done;
                    }
                }

                _silent = old_silent;

            } else {
                // BURN BLOCK:
                burn_failsafe = false;
                if (ops.IsFs3()) {
                    report_err(ops._err_msg , "bb command is not supported anymore in FS3 image, please use b for burning FS3 image.\n");
                    rc = 1; goto done;

                }
            }

            // Burn it
            if (burn_failsafe) {
                // FS burn
                bool ret;
                if (ops.IsFs2()) {
                    ret = ops.CntxFailSafeBurn(*f,
                                               fim,
                                               !silent,
                                               &flashInfo,
                                               &fileInfo,
                                               false,
                                               NULL); // Allow reconfigure

                } else {
                    report_err(ops._err_msg, "FW Burning failed: old FW image format.\n");
                    rc = 1; goto done;
                }
                if (!ret) {
                    PrintFSBurnErr(*f, ops, "Image burn");
                    rc = 1; goto done;
                }
            } else {
                //
                // Not failsafe (sequential) burn
                //

                // Ask is it OK
                printf("\n");
                if (burn_block) {
                    printf("Block burn: The given image will be burnt as is. No fields (such\n");
                    printf("as GUIDS,VSD) are taken from current image on flash.\n");
                }
                printf("Burn process will not be failsafe. No checks will be performed.\n");

                printf("ALL flash, including the Invariant Sector will be overwritten.\n");
                printf("If this process fails, computer may remain in an inoperable state.\n");

                if (!ops.ask_user()) {
                    rc =  1; goto done;
                }

                // Non FS burn
                bool ret;
                if (ops.IsFs2() && !burn_block) {
                    ret = ops.CntxFailSafeBurn(*f,
                                               fim,
                                               !silent,
                                               &flashInfo,
                                               &fileInfo,
                                               true, // Allow nofs
                                               NULL); // Allow reconfigure
                } else {
                    ret = ops.write_image(*f, 0, fim.getBuf(), fim.getBufLength(),!silent, "");
                }


                if (!ret) {
                    report("\n");
                    report_err(ops._err_msg, "Non failsafe burn failed: %s\n", ops.err());
                    rc =  1; goto done;
                }
                report("\n");
            }
        }
        break;

    case CMD_BURN_ROM:
        {
            char *rom_file = NULL;
            NEXTC("<ROM_FILE>", "brom");
            rom_file = av[i];
            _silent = true;

            // Open Rom file, get its size and read it
            FImage rom_image;
            if (!rom_image.open(rom_file, true)) {
                report_err(ops._err_msg, "ROM file open failed: %s\n", rom_image.err());
                rc =  1; goto done;
            }

            if (rom_image.getBufLength() == 0) {
                report_err(ops._err_msg, "Bad ROM file: Empty file.\n");
                rc = 1; goto done;
            }

            Operations::ImageInfo dummy_info;
            if (ops.VerifyFs2(rom_image, &dummy_info)) {
                // Note that if this check passes it means that a FW image was
                // erroneously provided as an expansion ROM
                report_err(ops._err_msg, "File \"%s\" is a Mellanox FW image. Expecting an expansion ROM image.\n", rom_file);
                rc = 1; goto done;
            }

            Operations::ImageInfo file_info;
            Operations::ImageInfo flash_info;

            if (!ops.CheckDevImage(*f, flash_info, 1)) {
                report_err(ops._err_msg, "Burn ROM failed: %s\n", ops.err());
                rc = 1; goto done;
            }
            if (ops.IsRomEmpty(&flash_info) && !ops.IsFwSupportingRomModify(flash_info.fwVer)) {
                report_err(ops._err_msg, "It is not allowed to burn ROM on device which has fw: %d.%d.%d that doesn't contain ROM.\n", flash_info.fwVer[0],
                           flash_info.fwVer[1], flash_info.fwVer[2]);
                rc = 1; goto done;
            }

            if (!allowdRomChange && flash_info.infoOffs[Operations::II_ProductVer]) {
                report_err(ops._err_msg, "Burn ROM failed: The device FW contains common FW/ROM Product Version - The ROM cannot be updated separately.\n");
                rc =  1; goto done;
            }
            u_int32_t length        = ops._last_image_addr;
            u_int32_t new_data_size = length + TOTAL_SEC_SIZE(rom_image.getBufLength());
            vector<u_int8_t> data(length);
            vector<u_int8_t> new_data(new_data_size);

            // Read the image.
            if (!f->read(0, (u_int8_t*)(&data[0]), length)) {
                report_err(ops._err_msg, "Flash read failed: %s\n", f->err());
                rc =  1; goto done;
            }

            int new_image_size;

            // Insert the rom to the image.
            if(!ops.UpdateRomInImage((u_int8_t*)(&new_data[0]), (u_int8_t*)(&data[0]),
                                     (u_int8_t*)rom_image.getBuf(), rom_image.getBufLength(),
                                     &new_image_size)) {
                report_err(ops._err_msg, "Burning ROM Failed: %s\n", f->err());
                rc = 1; goto done;
            }

            // open the image
            fim.open((u_int32_t*)(&new_data[0]), new_image_size);

            if (!ops.VerifyFs2(fim, &file_info, false, false, true) || !ops.QueryAll(fim, &file_info)) {
                report_err(ops._err_msg, "Internal error: The prepared image is corrupted: %s\n", ops.err());
                rc = 1; goto done;
            }
            if (!ops.CheckMatchingExpRomDevId(&file_info)) {
                report_warn("Image file ROM: %s\n", ops.err());
                if (!ops.ask_user()) {
                    rc =  1; goto done;
                }
            }
            _silent = false;
            char rom_ver1[50], rom_ver2[50];
            printf("\n");
            char *info_str = "    Current ROM info on flash: ";
            char *info_str2 = "    New ROM info:              ";
            if (!ops.IsRomEmpty(&flash_info)) {
                ops.DisplayExpRomInfo(&flash_info, info_str);
                ops.GetExpRomStrVer(&flash_info, rom_ver1);
            } else {
                printf("%s", info_str);
                sprintf(rom_ver1, "N/A");
                printf("%s\n", rom_ver1);
            }
            ops.DisplayExpRomInfo(&file_info, info_str2);
            ops.GetExpRomStrVer(&file_info, rom_ver2);
            print_line_to_log(
                    "Current ROM version on flash (1st ROM of %d): %s, New ROM version (1st ROM of %d): %s\n",
                    flash_info.numOfExpRom, rom_ver1, file_info.numOfExpRom, rom_ver2);

            // Print the ROM versin of the curerrent and the new ROM.
            bool ret = ops.CntxFailSafeBurn(*f, fim, !silent, &flash_info, &flash_info, true, "Burning ROM image");
            if (!ret) {
                PrintFSBurnErr(*f, ops, "ROM burn");
                rc = 1; goto done;
            }

        }
        break;
    case CMD_REMOVE_ROM:
        {
            Operations::ImageInfo file_info;
            Operations::ImageInfo flash_info;

            // Verify to get some parameters
            _silent = true;
            if (!ops.CheckDevImageAndRom(*f, flash_info)) {
                report_err(ops._err_msg, "Remove ROM failed: %s\n", ops.err());
                rc = 1; goto done;
            }
            if (!ops.IsFwSupportingRomModify(flash_info.fwVer)) {
                report_err(ops._err_msg, "Remove ROM failed: Unsupported Fw version (%d.%d.%d)\n", flash_info.fwVer[0],
                           flash_info.fwVer[1], flash_info.fwVer[2]);
                rc = 1; goto done;
            }
            if (!allowdRomChange && flash_info.infoOffs[Operations::II_ProductVer]) {
                report_err(ops._err_msg, "Remove ROM failed: The device FW contains common FW/ROM Product Version - The ROM cannot be removed separately.\n");
                rc =  1; goto done;
            }


            u_int32_t length        = ops._last_image_addr;
            vector<u_int8_t> data(length);
            vector<u_int8_t> new_data(length);


            // Read the image.
            if (!f->read(0, (u_int8_t*)(&data[0]), length)) {
                report_err(ops._err_msg, "Flash read failed: %s\n", f->err());
                rc =  1; goto done;
            }
            int new_image_size;
            if(!ops.UpdateRomInImage((u_int8_t*)(&new_data[0]), (u_int8_t*)(&data[0]),
                                     NULL, 0, &new_image_size)) {
                report_err(ops._err_msg, "Removing ROM Failed: %s\n", f->err());
                rc = 1; goto done;
            }
            // Burn the Image after removing the ROM.
            fim.open((u_int32_t*)(&new_data[0]), new_image_size);

            // To verify the new image and exit if it's not VALID.
            if (!ops.VerifyFs2(fim, &file_info, false, false, true) || !ops.QueryAll(fim, &file_info)) {
                report_err(ops._err_msg, "Internal error: The prepared image after removing the ROM is corrupted: %s\n", ops.err());
                rc = 1; goto done;
            }

            _silent = false;
            bool ret = ops.CntxFailSafeBurn(*f, fim, !silent, &flash_info, &file_info, true,
                                            "Removing ROM image" );
            if (!ret) {
                PrintFSBurnErr(*f, ops, "ROM remove");
                rc = 1; goto done;
            }


        }
        break;
    case CMD_READ_ROM:
        {
            _silent = true;

            char* rom_file = NULL;
            NEXTC("<OUT_FILENAME>", "rrom");
            rom_file = av[i];

            FILE * file;
            if ((file = fopen(rom_file, "r")) != NULL) {
                fclose(file);
                printf("\n The given ROM file is existing, you are going to overwrite it.\n");
                if (!ops.ask_user()) {
                    rc =  1; goto done;
                }
            }

            Operations::ImageInfo flash_info;

            if (!ops.CheckDevImageAndRom(*fbase, flash_info)) {
                report_err(ops._err_msg, "Read ROM failed: %s\n", ops.err());
                rc = 1; goto done;
            }

            u_int32_t length = flash_info._rom_sect.size();
            FILE* fh;
            if ((fh = fopen(rom_file, "wb")) == NULL) {
                report_err(ops._err_msg, "Can not open %s: %s\n", av[i], strerror(errno));
                rc =  1; goto done;
            }

            // Write output
            if (fwrite((u_int8_t*)(&flash_info._rom_sect[0]),  1, length, fh) != length) {
                report_err(ops._err_msg, "File write error: %s\n", strerror(errno));
                fclose(fh);
                rc =  1; goto done;
            }
            fclose(fh);
        }
        break;
    case CMD_SET_VSD:
    {

        FImage                fim1;
        Operations::ImageInfo info;

        if (user_vsd == NULL) {
            report_err(ops._err_msg, "For set_vsd command, please specify the VSD (using command flag -vsd).\n");
            rc =  1; goto done;
        }
        _silent = true;

        if (!ops.CheckDevImage(*fbase, info)) {
            report_err(ops._err_msg, "Failed to set the VSD:: %s\n", ops.err());
            rc = 1; goto done;
        }
        _silent = false;

        // Check if we have info section in the image.
        if (!info.infoOffs[Operations::II_VSD]) {
            report_err(ops._err_msg, "Failed to set the VSD: No info section on the image.\n");
            rc = 1; goto done;
        }

        if (!ops.ModifyVSDSection(fbase, &info, user_vsd, image_fname, silent)) {
            report_err(ops._err_msg, "Failed to set the VSD: %s.\n", ops.err());
            rc = 1; goto done;
        }
    }
    break;

    case CMD_SET_KEY:
    {

        FImage                fim1;
        Operations::ImageInfo info;
        hw_key_t              key;
        u_int8_t got_pass;
        WIN_NOT_SUPPORTED_GOTO("set_key", rc, done);

        GET_KEY_FROM_USER("set_key", &key, &got_pass);

        // As the user to confirm the key
        if (got_pass) {
            hw_key_t second_key;
            GET_PASSWORD_FROM_USER("Verify key", &second_key);
            if (key.l != second_key.l || key.h != second_key.h) {
                report_err(ops._err_msg, "Failed to set the HW access key: The keys you entered did not match.\n");
                rc = 1; goto done;
            }
        }
        _silent = true;

        if (!ops.CheckDevImage(*fbase, info)) {
            report_err(ops._err_msg, "Failed to set the HW access key: %s\n", ops.err());
            rc = 1; goto done;
        }
        _silent = false;

        // Check if we have info section in the image.
        if (!info.infoOffs[Operations::II_HwAccessKey]) {
            report_err(ops._err_msg, "Failed to set the HW access key: The image does not support this operation.\n");
            rc = 1; goto done;
        }

        if (!ops.ModifyKeySection(fbase, &info, key, image_fname, silent)) {
            report_err(ops._err_msg, "Failed to set the HW access key: %s.\n", ops.err());
            rc = 1; goto done;
        }
    }
    break;


    case CMD_HW_ACCESS:
    {
        char *operation;
        WIN_NOT_SUPPORTED_GOTO("hw_access", rc, done);

        NEXTC("<disable/enable>", "hw_access");
        operation = av[i];

        if (!strcmp(operation, "disable")) {
            if (is_cr_space_locked) {
                printf("-I- HW access already disabled\n");
            } else {
                if (!f->disable_hw_access()) {
                    report_err(ops._err_msg, "%s\n", f->err());
                    rc =  1; goto done;
                }
            }
        } else if (!strcmp(operation, "enable")) {
            u_int64_t key;

            if (is_cr_space_locked == 0) {
                printf("-I- HW access already enabled\n");
            } else {
                hw_key_t key_struct;
                u_int8_t got_pass;
                GET_KEY_FROM_USER("hw_access", &key_struct, &got_pass);
                key = ((u_int64_t)key_struct.h << 32) | key_struct.l;
                if (!f->enable_hw_access(key)) {
                    report_err(ops._err_msg, "%s\n", f->err());
                    rc =  1; goto done;
                }
            }
        } else {
            report_err(ops._err_msg, "Bad option (%s). You can use enable or disable as options for hw_access.\n", operation);
            rc = 1; goto done;
        }


    }
    break;

    case CMD_SET_MFG_GUIDS:
    {
        if (ops.IsFs3()) {
            if (uids_specified == true) {
                if (!ops.Fs3UpdateSection(*fbase, &base_guid, FS3_MFG_INFO, false, image_fname)) {
                     report_err(ops._err_msg, "Failed to set manufacture guids: %s\n", ops.err());
                     rc =  1; goto done;
                }
            }
        } else {
            report_err(ops._err_msg, "Failed to set manufacture guids: This command works Only over FS3 FW image.\n");
            rc = 1; goto done;
        }
    }
    break;

    case CMD_BURN_VPD:
    {

        char* vpd_file = NULL;
        NEXTC("<VPD_FILENMAE>", "set_vpd");
        vpd_file = av[i];

        if (ops.IsFs3()) {
            if (!ops.Fs3UpdateSection(*fbase, vpd_file, FS3_VPD_R0, false, image_fname)) {
                 report_err(ops._err_msg, "Failed to set VPD: %s\n", ops.err());
                 rc =  1; goto done;
            }
        } else {
            report_err(ops._err_msg, "Failed to set VPD: This command works Only over FS3 FW image.\n");
            rc = 1; goto done;
        }
    }
    break;



    case CMD_SET_GUIDS:
        {
            Operations::ImageInfo info;
            u_int32_t guid_sect_addr[2] = {0};
            u_int32_t length;
            bool update_crc = true;

            // Get the arguments
            if (i + 2 <= ac) {
                NEXTC("<NOCRC>", "sg");
                char *nocrc = av[i];
                if (strcmp(nocrc, "nocrc")) {
                    report_err(ops._err_msg, "The sg parameter should be \"nocrc\" or nothing\n");
                    rc = 1; goto done;
                }
                update_crc = false;
            }
            // Get some info regarding the image.
            if (ops.IsFs2Only()) {
                _silent       = true;
                if (!ops.VerifyFs2(*fbase, &info, false, true)) {
                    report_err(ops._err_msg, "Can not set GUIDs: %s. \n", ops.err());
                    rc =  1; goto done;
                }
                _silent = false;
            }
            if (!ops.QueryAll(*fbase, &info)) {
                report_err(ops._err_msg, "Can not set GUIDs: %s query (%s) failed: %s\n", cmdTarget , cmdAccess, ops.err());
                rc =  1; goto done;
            }

            // Check if we have blank guids
            if (info.blankGuids && image_fname == NULL) {
                // There is blank GUIDs on the device (not image)
                length  = info.imageSize;

                if (!ops.CheckSetGuidsFlags(&info, macs_specified, guids_specified, uids_specified)) {
                    report_err(ops._err_msg, "%s\n", ops.err());
                    rc = 1; goto done;
                }

                if (ops.IsFs2() || !info.isFailsafe) {
                    guid_sect_addr[0] = info.guidPtr;
                } else {
                    int addr_idx = 0;
                    for (i = 0; i < 2; i++) {
                        if (info.allImgStart[i]) {
                            guid_sect_addr[addr_idx] = info.allImgStart[i] + info.guidPtr;
                            addr_idx++;
                        }
                    }
                }

                for (i = 0; i < 2 && guid_sect_addr[i]; i++ ) {
                    u_int32_t guid_sect[Operations::MAX_GUIDS*2 + 5]; // Save room for header + crc

                    if (!f->read(guid_sect_addr[i] - 16 , guid_sect, 16)) {
                        report_err(ops._err_msg, "Failed to read guids section - flash read error (%s)\n", fbase->err());
                    }

                    ops.patchGUIDsSection (guid_sect, 16, user_guids, info.guidNum);

                    if (!f->write(guid_sect_addr[i], guid_sect + 4 , info.guidNum * 8 + 4, true)) {
                        report_err(ops._err_msg, "Guids set failed - flash write error (%s)\n", fbase->err());
                    }
                }
                if (update_crc && ops.IsFs2()) {
                   // Read the image.
                    vector<u_int8_t> data(length);

                    if (!f->read(0, (u_int32_t*)(&data[0]), length)) {
                        report_err(ops._err_msg, "Flash read failed: %s\n", f->err());
                        rc =  1; goto done;
                    }
                    // TODO: Do we need to update the CRC existing ORENK
                    // Calc & Update CRC.
                    u_int32_t *new_data =  (u_int32_t*)(&data[0]);
                    u_int32_t crc = ops.CalcImageCRC(new_data, length / 4);
                    u_int32_ba old_dw = __be32_to_cpu(new_data[IMG_CRC_OFF / 4]);
                    old_dw.range(15, 0) =  crc;
                    u_int32_t new_crc_dw = CPUTO1(old_dw);

                    if (!f->write(IMG_CRC_OFF, &new_crc_dw, 4, true)) {
                        report_err(ops._err_msg, "Guids set failed - flash write error (%s)\n", fbase->err());
                    }
                }
            } else if (!ops.IsFs2()) {
                // 1- Old image
                // 2- Old device with no blank
                if (image_fname != NULL) {
                    report_err(ops._err_msg, "Can not set GUIDs for pre-ConnectX image.\n");
                } else {
                    report_err(ops._err_msg, "Can not set GUIDs: GUIDs are already set (Modifying GUIDs is not supported pre-ConnectX devices).\n");
                }
                rc =  1; goto done;
            } else if (ops.IsFs3()) {
                if (uids_specified == true) {
                    if (!ops.Fs3UpdateSection(*fbase, &base_guid, FS3_DEV_INFO, true, image_fname)) {
                        report_err(ops._err_msg, "Failed to set UID: %s\n", ops.err());
                        rc =  1; goto done;
                    }
               } else {
                    report_err(ops._err_msg, "Can not set Guids/Macs: uid is not specified, please run with -uid flag.\n");
                    rc =  1; goto done;
                }


            } else {
                // 1- FS2 image
                // 2- FS2 device with no blank guids
                guid_t *used_guids;

                // Check the guid given by the user
                if (!ops.CheckSetGuidsFlags(&info, macs_specified, guids_specified, uids_specified)) {
                    report_err(ops._err_msg, "%s\n", ops.err());
                    rc = 1; goto done;
                }
                if (image_fname == NULL) {
                    // 2- FS2 device with no blank Guids
                    report_warn("GUIDs are already set, re-burning image with the new GUIDs ...\n");
                }

                bool ib_dev, eth_dev, bx_dev;

                // Get the FW types
                bx_dev = ops.IsBridgeX(info.devType);
                ops.SetDevFlags(info.devType, ib_dev, eth_dev);
                guid_t* old_guids = info.imageOk ? info.guids : NULL;

                // Patch the GUIDs and prints any needed warnings
                if (!ops.preFS2PatchGUIDs(eth_dev, bx_dev, guids_specified, macs_specified, uids_specified, user_guids,
                        old_guids, &used_guids, info.guidNum)) {
                    rc = 1; goto done;
                }
                // Report the changes in the GUIDs
                if (!ops.reportGuidChaneges(&info, used_guids, old_guids, ib_dev, eth_dev, bx_dev)) {
                    rc =  1; goto done;
                }
                // Modify the guids in the burnt image and re-burn it
                if (!ops.ModifyGuidSection(fbase, &info, used_guids, image_fname, silent)) {
                    report_err(ops._err_msg, "GUIDs set failed: %s\n", ops.err());
                    rc = 1; goto done;
                }
            }
        }
        break;

    case CMD_ERASE_SECT:
        {
            //
            // ERASE SECTOR <ADDR>
            //     Parameters: <ADDR>
            //
            u_int32_t    addr;
            char         *endp;

            // Address of sector to erase
            NEXTC("<ADDR>", "erase");
            addr = strtoul(av[i], &endp, 0);
            if (*endp) {
                report_err(ops._err_msg, "Invalid address \"%s\"\n", av[i]);
                rc =  1; goto done;
            }

            // Erase
            if (!f->erase_sector(addr)) {
                report_err(ops._err_msg, "Erase sector failed: %s\n", f->err());
                rc =  1; goto done;
            }
        }
        break;

    case CMD_QUERY_FORCE:
    case CMD_QUERY:
        {
            // QUERY
            Operations::ImageInfo info;
            bool imageOk, full_query = false;

            // Check if we have full argument.
            if (ac > i + 1) {
                i++;
                if (!strcmp(av[i], "full")) {
                    full_query = true;
                } else {
                    report_err(ops._err_msg, "Unknown option \"%s\" for the query command.\n", av[i]); \
                    return 1;                                                  \
                }
            }

            _silent       = true;
            if (ops.GetQuickQuery()) {
                report_warn("Running quick query - Skipping full image integrity checks.\n");
                if (!ops.IsFs3()) {
                    ops.initSectToRead(H_ROM);
                }
            }

            imageOk = ops.Verify(*fbase, &info);

            _silent = false;

            if (!imageOk) {
                printf("\n");
                report_err(ops._err_msg, "%s query (%s) failed. Not a valid image.\n", cmdTarget , cmdAccess);
                rc =  1; goto done;
            }

            if (!ops.QueryAll(*fbase, &info)) {
                report_err(ops._err_msg, "%s query (%s) failed: %s\n", cmdTarget , cmdAccess, ops.err());
                rc =  1; goto done;
            }
            ops.DisplayImageInfo(&info, full_query);
        }
        break;

    case CMD_QUERY_ROM: {
        Operations::ImageInfo info;
        if (!ops.LoadAsExpRom(*fbase, &info) ||
            !ops.GetExpRomVersion(&info) ||
            !ops.DisplayExpRomInfo(&info, "Rom Info: ")) {

                report_err(ops._err_msg, "%s rom query (%s) failed: %s\n",
                    cmdTarget, cmdAccess, ops.err());
                rc = 1;
                goto done;
        }
    }
        break;
    case CMD_READ_BLOCK:
        {
            // READ BLOCK
            //     Parameters:  <ADDR> <LENGTH> [OUT_FILENAME]
            //     if OUT_FILENAME is given, binari read block is stored
            //     in the given file. Otherwise, data is printed to screen.
            u_int32_t    addr, length;
            u_int8_t     *data;
            char         *endp;

            bool         to_file = false;

            // Address and length
            NEXTC("<ADDR>", "rb");
            addr = strtoul(av[i], &endp, 0);
            if (*endp) {
                report_err(ops._err_msg, "Invalid address \"%s\"\n", av[i]);
                rc =  1; goto done;
            }
            NEXTC("<LENGTH>", "rb");
            length = strtoul(av[i], &endp, 0);
            if (*endp) {
                report_err(ops._err_msg, "Invalid length \"%s\"\n", av[i]);
                rc =  1; goto done;
            }
            data = new u_int8_t[length];

            // Output file
            FILE*  fh = NULL;

            if (i + 2 == ac)
                to_file = true;

            if (to_file) {
                NEXTC("<OUT_FILENAME>", "rb");
                if ((fh = fopen(av[i], "wb")) == NULL) {
                    report_err(ops._err_msg, "Can not open %s: %s\n", av[i], strerror(errno));
                    rc =  1; goto done;
                }
            }

            // Read flash
            if (!fbase->read(addr, data, length)) {
                report_err(ops._err_msg, "Flash read failed: %s\n", fbase->err());
                rc =  1; goto done;
            }

            if (to_file) {
                // Write output
                if (fwrite(data, 1, length, fh) != length) {
                    report_err(ops._err_msg, "File write error\n");
                    rc =  1; goto done;
                }
                fclose(fh);
            } else {
                for (u_int32_t i = 0; i < length ; i+=4) {
                    u_int32_t word = *((u_int32_t*)(data + i));

                    word  = __be32_to_cpu(word);
                    printf("0x%08x ", word);
                }
                printf("\n");
            }
            delete [] data;
        }
        break;

    case CMD_READ_WORD:
        {
            // READ DWORD <ADDR>
            //     Parameters: <ADDR>
            u_int32_t    data, addr;
            char         *endp;

            // Address
            NEXTC("<ADDR>", "rw");
            addr = strtoul(av[i], &endp, 0);
            if (*endp) {
                report_err(ops._err_msg, "Invalid address \"%s\"\n", av[i]);
                rc =  1; goto done;
            }

            // Read
            if (!f->read(addr, &data)) {
                report_err(ops._err_msg, "Flash read failed: %s\n", f->err());
                rc =  1; goto done;
            }
            printf("0x%08x\n", (unsigned int)__cpu_to_be32(data));

        }
        break;

    case CMD_VERIFY:
        {
            // VERIFY
            Operations::ImageInfo info;
            bool show_itoc = false;
            if (ac > i + 1) {
                i++;
                if (!strcmp(av[i], "showitoc")) {
                    show_itoc = true;
                } else {
                    report_err(ops._err_msg, "Unknown option \"%s\" for the verify command.\n", av[i]); \
                    return 1;                                                  \
                }
            }

            if (!ops.Verify(*fbase, &info, true, show_itoc)) {
                char err_tmp[MAX_ERR_STR_LEN];
                printf("\n");

                if (ops.err()) {
                    sprintf(err_tmp, ": %s", ops.err());
                } else {
                    sprintf(err_tmp, "%s", ". ");
                }
                report_err(ops._err_msg, "FW image verification failed%s AN HCA DEVICE CAN NOT BOOT FROM THIS IMAGE.\n",
                           err_tmp);
                rc =  1; goto done;
            } else {
                if (info.blankGuids) {
                    printf("\n");
                    report_err(ops._err_msg, "FW image verification failed: BLANK GUIDS. AN HCA DEVICE CAN NOT BOOT FROM THIS IMAGE.\n");
                    rc =  1; goto done;
                } else {
                    printf("\nFW image verification succeeded. Image is bootable.\n\n");
                }
            }
        }
        break;

    case CMD_DUMP_HASH:
        // The default dump_sect_type is  H_FW_CONF
        dump_sect_type = H_HASH_FILE;
    case CMD_DUMP_CONF:
        {
            // Dump conf
            Operations::ImageInfo info;
            _silent = true;
            if (ops.IsFs3()) {
                if (dump_sect_type == H_FW_CONF) {
                    dump_sect_type = FS3_DBG_LOG_MAP;
                }
            }
            ops.initSectToRead(dump_sect_type);
            char* dump_file = NULL;
            if (i + 2 <= ac) {
                NEXTC("<OUT_FILENAME>", "dh");
                dump_file = av[i];
            }

            ops.Verify(*fbase, &info);

            if (!ops.DumpFileSection(dump_file, dump_sect_type)) {
                report_err(ops._err_msg, "Failed dumping %s: %s\n", g_sectNames[dump_sect_type], ops.err());
                rc =  1; goto done;
            }
        }
        break;

    case CMD_DUMP_TRACER_HASH:
        {
            char* dump_file = NULL;
            Operations::ImageInfo info;
            std::vector<u_int8_t> data;
            if (i + 2 <= ac) {
                NEXTC("<OUT_FILENAME>", "dth");
                dump_file = av[i];
            }

            if (mainImageInfoOK) {
                if (!ops.DumpFile(dump_file, mainImageInfo.TracerHashSectZipped, "Tracer hash file")) {
                    report_err(ops._err_msg, "Failed to get tracer hash info: %s.\n", ops.err());
                    rc =  1; goto done;
                }
            } else {
                report_err(ops._err_msg, "No tracer hash file: Bad FW image.\n");
                rc =  1; goto done;
            }

        }
        break;
    case CMD_READ_IMAGE:
        {
            // Dump conf
            _silent = true;
            Operations::ImageInfo info;

            char* img_file = NULL;
            NEXTC("<OUT_FILENAME>", "ri");
            img_file = av[i];

            // For FS2 image, read only a single image. For other HCAs, try to read both images, since
            // the distributed image binary file also contains both images.
            ops.Verify(*f, &info, !ops.IsFs2());

            //printf("Last addr: 0x%08x\n", ops._last_image_addr);

            u_int32_t length = ops._last_image_addr;
            vector<u_int8_t> data(length);
            // Read flash
            if (ops.IsFs3()) {
                data = info._image_cache;
            } else {
                if (!f->read(0, (u_int32_t*)(&data[0]), length)) {
                    report_err(ops._err_msg, "Flash read failed: %s\n", f->err());
                    rc =  1; goto done;
                }
            }

            if (!ops.WriteImageToFile(img_file, (u_int8_t*)(&data[0]), length)) {
                report_err(ops._err_msg, "Read Image failed: %s.\n", ops.err());
                rc =  1; goto done;

            }
        }

        break;

    case CMD_WRITE_BLOCK:
        {
            // WRITE BLOCK
            //     Parameters:  <IN_FILENAME> <ADDR>
            u_int32_t    addr;
            char         *endp;

            // Input file
            FImage fim;

            NEXTC("<IN_FILENAME>", "wb");

            image_fname = av[i];

            // Address
            NEXTC("<ADDR>", "wb");
            addr = strtoul(av[i], &endp, 0);
            if (*endp) {
                report_err(ops._err_msg, "Invalid address \"%s\"\n", av[i]);
                rc =  1; goto done;
            }

            if (!fim.open(image_fname)) {
                report_err(ops._err_msg, "Image file open failed: %s\n", fim.err());
                rc =  1; goto done;
            }

            // Write flash
            if (!ops.write_image(*f, addr, fim.getBuf(), fim.getBufLength(), !silent, "")) {
                report_err(ops._err_msg, "Flash write failed: %s\n", ops.err());
                rc =  1; goto done;
            }
        }
        break;

    case CMD_WRITE_WORD:
        {
            // WRITE DWORD
            //     Parameters: <ADDR> <DATA>
            u_int32_t    data, addr;
            char         *endp;

            // Address and data
            NEXTC("<ADDR>", "ww");
            addr = strtoul(av[i], &endp, 0);
            if (*endp) {
                report_err(ops._err_msg, "Invalid address \"%s\"\n", av[i]);
                rc =  1; goto done;
            }
            NEXTC("<DATA>", "ww");
            data = __cpu_to_be32(strtoul(av[i], &endp, 0));
            if (*endp) {
                report_err(ops._err_msg, "Invalid data \"%s\"\n", av[i]);
                rc =  1; goto done;
            }

            //f->curr_sector = 0xffffffff;  // First time erase sector
            if (!f->write(addr, data)) {
                report_err(ops._err_msg, "Flash write failed: %s\n", f->err());
                rc =  1; goto done;
            }
        }
        break;

    case CMD_WRITE_BLOCK_NE:
        {
            // WRITE DWORD WITHOUT ERASE
            //     Parameters: <ADDR> <SIZE> <DATA>
            u_int32_t    size, addr;
            char         *endp;

            // Address and data
            NEXTC("<ADDR>", "wbne");
            addr = strtoul(av[i], &endp, 0);
            if (*endp) {
                report_err(ops._err_msg, "Invalid address \"%s\"\n", av[i]);
                rc =  1; goto done;
            }
            NEXTC("<SIZE>", "wbne");
            size = strtoul(av[i], &endp, 0);
            if (*endp || size % 4) {
                report_err(ops._err_msg, "Invalid size \"%s\"\n", av[i]);
                rc =  1; goto done;
            }
            vector<u_int32_t> data_vec(size/4);
            for (u_int32_t w = 0; w < size/4 ; w++) {
                NEXTC("<DATA>", "wbne");
                data_vec[w] = __cpu_to_be32(strtoul(av[i], &endp, 0));
                if (*endp) {
                    report_err(ops._err_msg, "Invalid data \"%s\"\n", av[i]);
                    rc =  1; goto done;
                }
            }

            if (!f->write(addr, &data_vec[0], size, true)) {
                report_err(ops._err_msg, "Flash write failed: %s\n", f->err());
                rc =  1; goto done;
            }
        }
        break;

    case CMD_WRITE_WORD_NE:
        {
            // WRITE DWORD WITHOUT ERASE
            //     Parameters: <ADDR> <DATA>
            u_int32_t    data, addr;
            char         *endp;

            // Address and data
            NEXTC("<ADDR>", "wwne");
            addr = strtoul(av[i], &endp, 0);
            if (*endp) {
                report_err(ops._err_msg, "Invalid address \"%s\"\n", av[i]);
                rc =  1; goto done;
            }
            NEXTC("<DATA>", "wwne");
            data = __cpu_to_be32(strtoul(av[i], &endp, 0));
            if (*endp) {
                report_err(ops._err_msg, "Invalid data \"%s\"\n", av[i]);
                rc =  1; goto done;
            }

            if (!f->write(addr, &data, 4, true)) {
                report_err(ops._err_msg, "Flash write failed: %s\n", f->err());
                rc =  1; goto done;
            }
        }
        break;

    case CMD_HW_INFO:
            char *hw_cmd;
            NEXTC("command", "hw");
            hw_cmd = av[i];
            if (!strcmp(hw_cmd, HW_GET_CMD)) {
               is_hw_cmd_set = false;
#ifndef EXTERNAL
            } else if (!strcmp(hw_cmd, HW_SET_CMD)) {
                is_hw_cmd_set = true;
                NEXTC("SET", "hw set");
                param_to_set = av[i];
#endif
            } else {
                report_err(ops._err_msg, "bad parameter of hw command: %s, see help for more info.\n", hw_cmd);
                rc =  1; goto done;
            }
    case CMD_CFI: // For backward compatibility
        {
            if (is_hw_cmd_set) {
                char *param_name, *param_val_str;
                param_name = strtok(param_to_set, "=");
                param_val_str = strtok(NULL, "=");
                // printf("-D- param_name = %s, param_val_str=%s\n", param_name, param_val_str);
                if (param_name == NULL || param_val_str == NULL) {
                    report_err(ops._err_msg, "bad argument of hw "HW_SET_CMD" command : %s, it should be in the format PARAM_NAME=VALUE\n", param_to_set);
                    rc =  1; goto done;
                }
                if (!f->set_attr(param_name, param_val_str)) {
                    report_err(ops._err_msg, "HW set failed: %s\n", f->err());
                    rc =  1; goto done;
                }
                printf("-I- %s parameter was set successfully\n", param_name);
            } else {
                if (!f->print_attr()) {
                    report_err(ops._err_msg, "HW query failed: %s\n", f->err());
                    rc =  1; goto done;
                }
            }
        }
        break;

    case CMD_CLEAR_SEM:
        // Do nothing - opening the device already cleared the semaphore.
        break;

    case CMD_SWRESET:
        printf("Resetting device %s ...\n", device);
        if (!f->sw_reset()) {
            report_err(ops._err_msg, "Software reset failed: %s\n", f->err());
            rc =  1; goto done;
        }

        break;

    default:
        report_err(ops._err_msg, "Internal error: Invalid command %d.\n", cmd);
        rc =  1; goto done;
    }

done:
    write_result_to_log(rc, ops._err_msg);

    close_log();

    // Mask signals
    for (i = 0 ; i < (int)(sizeof(g_signals_for_termination)/sizeof(g_signals_for_termination[0])) ; i++ ) {
        signal (g_signals_for_termination[i], SIG_IGN);
    }
    return rc;
}

