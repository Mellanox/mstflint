# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

import sys

if sys.version_info[0] < 3:
    print("Error: This tool supports python 3.x only. Exiting...")
    exit(1)

import argparse  # noqa: E402
import os  # noqa: E402

import tools_version  # noqa: E402
from nvltssm_lib.LtssmTraceException import LtssmTraceException  # noqa: E402
from nvltssm_lib.LtssmTraceManager import LtssmTraceManager  # noqa: E402
from nvltssm_lib.formatters.LtssmFormatter import FORMATTER_CLASSES, formatter_type  # noqa: E402


class LtssmTrace:
    """This class is responsible for the LTSSM trace UI by handling the user inputs
       and running the requested trace.
    """

    DESCRIPTION = \
        """Description:
    This tool decodes the PCIe LTSSM history logged by the device out of an
    "mstdump" output, and prints the state transitions oldest first.
"""

    DEFAULT_FORMATTER = "report"

    _arg_parser = None

    @classmethod
    def _init_arg_parser(cls):
        tool_name = os.path.basename(__file__).split('.')[0]

        cls._arg_parser = argparse.ArgumentParser(prog=tool_name, description=cls.DESCRIPTION, add_help=False,
                                                  formatter_class=argparse.RawDescriptionHelpFormatter)

        required_args = cls._arg_parser.add_argument_group('required arguments')
        link_args = cls._arg_parser.add_argument_group('link selection arguments')
        optional_args = cls._arg_parser.add_argument_group('optional arguments')

        required_args.add_argument("--dump", dest="dump_file", type=cls._valid_path_arg_type, required=True,
                                   help='Location of the "mstdump" output to decode')

        link_args.add_argument("--pcore", type=int, default=0, help='Index of the pcore holding the link. Default: 0')
        link_args.add_argument("--link", type=int, default=0, help='Index of the link within the pcore. Default: 0')
        link_args.add_argument("--port", type=int,
                               help='Port number of the link, taken instead of --pcore and --link')
        link_args.add_argument("--lport", type=int,
                               help='Local port number of the link, taken instead of --pcore and --link')

        optional_args.add_argument("--device-type", dest="device_name", metavar="NAME",
                                   help='Device the dump was taken from, e.g. "ConnectX8", taken instead of reading '
                                        'the device id out of the dump. Needed for a device whose dump carries '
                                        'no device id')
        optional_args.add_argument("-f", "--formatter", dest="formatter", type=formatter_type,
                                   default=FORMATTER_CLASSES[cls.DEFAULT_FORMATTER],
                                   help="Available options: {}. Default: '{}'".format(list(FORMATTER_CLASSES.keys()),
                                                                                      cls.DEFAULT_FORMATTER))
        optional_args.add_argument("-o", "--out", help='Location of the output file')
        optional_args.add_argument('--version', action='version', help="Shows the tool's version and exit",
                                   version=tools_version.GetVersionString(tool_name, None))
        optional_args.add_argument("-h", "--help", action="help", help="show this help message and exit")

    @staticmethod
    def _valid_path_arg_type(path):
        if not os.path.exists(path):
            raise argparse.ArgumentTypeError("no such file: '{}'".format(path))

        return path

    @classmethod
    def run(cls):
        cls._init_arg_parser()
        args = cls._arg_parser.parse_args()

        manager = LtssmTraceManager(args.dump_file, args.formatter(),
                                    args.pcore, args.link, args.port, args.lport, args.device_name)
        output = "\n".join(manager.get_output()) + "\n"

        if args.out:
            with open(args.out, "w") as out_file:
                out_file.write(output)
        else:
            sys.stdout.write(output)


def main():
    try:
        LtssmTrace.run()
    except LtssmTraceException as exp:
        print("-E- {}".format(exp))
        return 1
    except KeyboardInterrupt:
        print("\n-E- Interrupted")
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
