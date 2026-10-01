# Copyright (c) 2013 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

try:
    import sys
    import os
    import platform
    import subprocess
    import tools_version
    import argparse
except Exception as e:
    print("-E- could not import : %s" % str(e))
    sys.exit(1)


# Constants ###########################
PROG = "mstdump"
DUMP_EXEC = "mstregdump"

# the firmware resource holding the dump, and the flat walk it is taken with
CRSPACE_RESOURCE = "CRSPACE"
CRSPACE_DUMP_DEPTH = 0

# reminder of the old help message, maybe return this format in the future
HELP_MESSAGE = '''   Mellanox %s utility, dumps device internal configuration data\n\
   Usage: %s [-full] <device> [i2c-secondary] [-v[ersion] [-h[elp]]]\n\n\
   -full                        :  Dump more expanded list of addresses\n\
        Note: be careful when using this flag, None safe addresses might be read.\n\
   -v | --version               :  Display version info\n\
   -h | --help                  :  Print this help message\n\
   Example :\n\
            %s %s\n
'''

######################################################################
# Description:  Execute command and get (rc, stdout-output, stderr-output)
######################################################################


def cmd_exec(cmd, device, write_line):
    # print("Executing: %s" % cmd)
    p = subprocess.Popen(cmd,
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         universal_newlines=True,
                         shell=True)
    for line in p.stdout:
        # Skip section prints
        if "=====" in line or "section=mstdump" in line:
            continue
        write_line(modify_output(line, device))
    return p.wait()


######################################################################
# Description:  Parse arguments
######################################################################


def parse_args(argv=None):
    arg_parser = argparse.ArgumentParser(prog=PROG)
    arg_parser.add_argument("device")
    arg_parser.add_argument("-v", "-version", "--version", action="version", version=tools_version.GetVersionString(PROG))
    arg_parser.add_argument("-full", "--full", action="store_true", help="Dump more expanded list of addresses")
    arg_parser.add_argument("--i2c_secondary", type=lambda s: int(s, 0), help="I2C secondary [0-127]")
    arg_parser.add_argument("-fast", "--fast", action="store_true",
                            help="Take the dump through the resource dump memory path on a device supporting it, "
                                 "which is faster than reading the addresses one by one")
    arg_parser.add_argument("-output_file", "--output_file", metavar="FILENAME",
                            help="Write the dump to FILENAME instead of the screen")

    return arg_parser.parse_args(argv)


######################################################################
# Description:  Build and run the mstregdump command
######################################################################


def run_mstregdump(mstdump_args, write_line):
    # the device is positional and the i2c secondary follows it, so the flag has
    # to be placed before them rather than appended
    full_str = "-full" if mstdump_args.full else ""
    i2c_secondary_str = str(mstdump_args.i2c_secondary) if mstdump_args.i2c_secondary else ""

    mstregdump_cmd = "%s %s %s %s" % (DUMP_EXEC, full_str, mstdump_args.device, i2c_secondary_str)
    return cmd_exec(mstregdump_cmd, mstdump_args.device, write_line)

######################################################################
# Description:  Check whether the fast dump is available on this machine
######################################################################


def add_resourcetools_to_path():
    # resource dump is driven at the python level out of its own directory, which
    # is a sibling of this one and is not on the path of this tool
    mft_py_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    resourcetools_dir = os.path.join(mft_py_dir, "resourcetools")
    if resourcetools_dir not in sys.path:
        sys.path.append(resourcetools_dir)


def is_fast_dump_available(device):
    # the menu query is taken over memory mode, which makes it a probe of the whole
    # fast path: a machine without memory mode, and a firmware with no resource dump
    # at all, both fail it and are left the mstregdump path
    try:
        add_resourcetools_to_path()

        from resourcedump_lib.commands.QueryCommand import QueryCommand
        from resourcedump_lib.utils import constants as cs

        menu_command = QueryCommand(device=device, mem=cs.DEVICE_RDMA)
        menu_command.execute()
        menu = menu_command.get_segments()[0]
        return any(record.segment_name == CRSPACE_RESOURCE for record in menu.get_records())
    except Exception:
        return False

######################################################################
# Description:  Dump the CRSPACE resource through resource dump
######################################################################


def run_resourcedump(device, write_line):
    add_resourcetools_to_path()

    from resourcedump_lib.commands.DumpCommand import DumpCommand
    from resourcedump_lib.utils import constants as cs
    from resourceparse_lib.formatters.AdbBasicFormatter import AdbBasicFormatter
    from resourceparse_lib.parsers.AddressValueParser import AddressValueParser

    # nothing is caught here: the probe already had this device answer over this
    # path, so a failure now is a failure worth reporting
    dump_command = DumpCommand(device=device, segment=CRSPACE_RESOURCE, depth=CRSPACE_DUMP_DEPTH, mem=cs.DEVICE_RDMA)
    dump_command.execute()

    # the address-value parse method emits the "0xADDR 0xVAL" lines itself, so the
    # formatter it is built with takes no part in the output
    parser = AddressValueParser(None, AdbBasicFormatter(AdbBasicFormatter.get_arg_parser().parse_args([])))
    for segment in dump_command.get_segments(True):
        parser.parse_segment(segment)
        for line in segment.get_parsed_data():
            write_line(line)

    return 0

######################################################################
# Description:  Modify the output of mstregdump and get the needed part
######################################################################


def modify_output(dump_output, device):
    if "Failed to open device:" in dump_output:
        return "Unable to open device %s. Exiting." % device
    else:
        return dump_output.strip()

######################################################################
# Description:  Write the dump lines where they were asked for
######################################################################


class LineWriter:
    # both dump sources write their lines here, so they cannot disagree about
    # the destination
    def __init__(self, output_file):
        self._out_file = open(output_file, "w") if output_file else None

    def write(self, line):
        if self._out_file:
            self._out_file.write(line + "\n")
        else:
            print(line)

    def close(self):
        if self._out_file:
            self._out_file.close()

######################################################################
# Description:  Dump a device, the entry point of both UIs
######################################################################


def dump(mstdump_args):
    # the root check sits here rather than at the command line, so that a tool
    # calling this in process is refused the same way the user is
    if platform.system() != "Windows" and os.geteuid() != 0:
        print("-E- Permission denied: User is not root")
        return 1

    writer = LineWriter(mstdump_args.output_file)
    try:
        if mstdump_args.fast and is_fast_dump_available(mstdump_args.device):
            return run_resourcedump(mstdump_args.device, writer.write)
        return run_mstregdump(mstdump_args, writer.write)
    finally:
        writer.close()


def dump_device(device, output_file=None, fast=False):
    # the arguments are built by the command line parser, so a caller in process
    # gets the defaults the user gets
    argv = [device]
    if fast:
        argv.append("--fast")
    if output_file:
        argv += ["--output_file", output_file]

    return dump(parse_args(argv))

######################################################################
# Description:  Main
######################################################################


if __name__ == "__main__":
    try:
        if dump(parse_args()):
            sys.exit(1)
    except KeyboardInterrupt:
        print("Interrupted, exiting ...")
        sys.exit(1)
