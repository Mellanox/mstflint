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

import os
import sys

script_dir = os.path.dirname(os.path.realpath(__file__))
for logger_dir in (os.path.join(script_dir, os.pardir),
                   os.path.join(script_dir, os.pardir, os.pardir, "mft_core", "mft_core_utils", "nvtoolslogger")):
    if os.path.isfile(os.path.join(logger_dir, "nvtoolslogger_api.py")):
        if logger_dir not in sys.path:
            sys.path.append(logger_dir)
        break

try:
    import platform
    import shlex
    import subprocess
    import tools_version
    import argparse
    import traceback
    from nvtoolslogger_api import Layer, Logger
except Exception as e:
    print("-E- could not import : %s" % str(e))
    sys.exit(1)


# Constants ###########################
PROG = "mstregdump"
DUMP_EXEC = "mstregdump-bin"

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
    class CauseAction(argparse.Action):
        def __call__(self, parser, namespace, values, option_string=None):
            cause_addr, cause_offset = values
            setattr(namespace, self.dest, values)
            setattr(namespace, "cause_addr", cause_addr)
            setattr(namespace, "cause_offset", cause_offset)

        def check_format(value):
            error_msg = ""
            try:
                cause_addr, cause_offset = value.split(".")
                if not cause_addr or not cause_offset:
                    raise ValueError
            except ValueError:
                error_msg = 'cause format "address.offset", both address and offset must be provided'
            else:
                try:
                    if int(cause_addr, 0) < 0 or int(cause_offset, 0) < 0:
                        raise ValueError
                except ValueError:
                    error_msg = 'cause_address and cause_offset must be non-negative numerical values'
            if error_msg:
                raise ValueError(error_msg)

            return (cause_addr, cause_offset)

    arg_parser = argparse.ArgumentParser(prog=PROG)
    arg_parser.add_argument("device")
    arg_parser.add_argument("i2c_secondary_after_device", nargs="?", metavar="i2c_secondary", type=lambda s: int(s, 0), help=argparse.SUPPRESS)
    arg_parser.add_argument("-v", "-version", "--version", action="version", version=tools_version.GetVersionString(PROG))
    arg_parser.add_argument("-full", "--full", action="store_true", help="Dump more expanded list of addresses")
    arg_parser.add_argument("--cause", type=CauseAction.check_format, action=CauseAction, metavar="address.offset", help=argparse.SUPPRESS)
    arg_parser.add_argument("--i2c_secondary", type=lambda s: int(s, 0), help="I2C secondary [0-127]")
    # --legacy takes the dump through mstregdump-bin without trying the resource dump memory path on a device
    arg_parser.add_argument("-legacy", "--legacy", action="store_true", help=argparse.SUPPRESS)
    arg_parser.add_argument("-output_file", "--output_file", metavar="FILENAME", help="Write the dump to a file instead of the screen")

    mstdump_args = arg_parser.parse_args(argv)
    if mstdump_args.i2c_secondary_after_device is not None:
        if mstdump_args.i2c_secondary is not None:
            arg_parser.error("the I2C secondary is given both after the device and with --i2c_secondary")
        mstdump_args.i2c_secondary = mstdump_args.i2c_secondary_after_device
    return mstdump_args


######################################################################
# Description:  Build and run the mstregdump-bin command
######################################################################


def run_mstregdump(mstdump_args, write_line):
    # the device is positional and the i2c secondary follows it, so the flag has
    # to be placed before them rather than appended
    full_str = "-full" if mstdump_args.full else ""
    cause_str = "--cause=%s.%s" % (mstdump_args.cause_addr, mstdump_args.cause_offset) if mstdump_args.cause else ""
    i2c_secondary_str = str(mstdump_args.i2c_secondary) if mstdump_args.i2c_secondary else ""

    mstregdump_cmd = "%s %s %s %s %s" % (shlex.quote(os.path.join(script_dir, DUMP_EXEC)), full_str, mstdump_args.device, cause_str, i2c_secondary_str)
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


def get_fast_dump_fallback_reason(device):
    # the menu query is taken over memory mode, which makes it a probe of the whole
    # fast path: a machine without memory mode, and a firmware with no resource dump
    # at all, both fail it and are left the mstregdump-bin path
    try:
        add_resourcetools_to_path()

        from resourcedump_lib.commands.QueryCommand import QueryCommand
        from resourcedump_lib.utils import constants as cs

        menu_command = QueryCommand(device=device, mem=cs.DEVICE_RDMA)
        menu_command.execute()
        menu = menu_command.get_segments()[0]
        if any(record.segment_name == CRSPACE_RESOURCE for record in menu.get_records()):
            return None
        return "the resource dump menu lists no {0} resource".format(CRSPACE_RESOURCE)
    except Exception as error:
        return "the resource dump menu query over memory mode failed: {0}".format(error)

######################################################################
# Description:  Dump the CRSPACE resource through resource dump
######################################################################


def run_resourcedump(device, write_line):
    try:
        add_resourcetools_to_path()

        from resourcedump_lib.commands.DumpCommand import DumpCommand
        from resourcedump_lib.utils import constants as cs
        from resourceparse_lib.formatters.AdbBasicFormatter import AdbBasicFormatter
        from resourceparse_lib.parsers.AddressValueParser import AddressValueParser

        dump_command = DumpCommand(device=device, segment=CRSPACE_RESOURCE, depth=CRSPACE_DUMP_DEPTH, mem=cs.DEVICE_RDMA)
        dump_command.execute()

        # the address-value parse method emits the "0xADDR 0xVAL" lines itself, so the
        # formatter it is built with takes no part in the output
        parser = AddressValueParser(None, AdbBasicFormatter(AdbBasicFormatter.get_arg_parser().parse_args([])))
        segments = dump_command.get_segments(True)
        for segment in segments:
            parser.parse_segment(segment)
    except Exception as error:
        Logger.error(Layer.MSTDUMP, "Failed to dump {0} through resource dump: {1}".format(device, error))
        print("-E- Failed to dump {0} through resource dump: {1}. Try running mstregdump with --legacy".format(device, error), file=sys.stderr)
        return 1

    for segment in segments:
        for line in segment.get_parsed_data():
            write_line(line)

    return 0

######################################################################
# Description:  Modify the output of mstregdump-bin and get the needed part
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
        if mstdump_args.legacy:
            Logger.info(Layer.MSTDUMP, "Dumping {0} through {1}: --legacy was given".format(mstdump_args.device, DUMP_EXEC))
            return run_mstregdump(mstdump_args, writer.write)
        fallback_reason = get_fast_dump_fallback_reason(mstdump_args.device)
        if fallback_reason is None:
            Logger.info(Layer.MSTDUMP, "Dumping {0} through the {1} resource over resource dump memory mode".format(mstdump_args.device, CRSPACE_RESOURCE))
            return run_resourcedump(mstdump_args.device, writer.write)
        Logger.warning(Layer.MSTDUMP, "Dumping {0} through {1}: {2}".format(mstdump_args.device, DUMP_EXEC, fallback_reason))
        return run_mstregdump(mstdump_args, writer.write)
    finally:
        writer.close()


def dump_device(device, output_file=None, legacy=False):
    # the arguments are built by the command line parser, so a caller in process
    # gets the defaults the user gets
    argv = [device]
    if legacy:
        argv.append("--legacy")
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
    except Exception as error:
        Logger.error(Layer.MSTDUMP, "Unexpected failure: {0}".format(" | ".join(line.strip() for line in traceback.format_exc().splitlines() if line.strip())))
        print("-E- {0}".format(error), file=sys.stderr)
        sys.exit(1)
