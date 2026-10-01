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

import argparse
import os
import sys
import tools_version

if sys.version_info[0] < 3:
    print("Error: This tool supports python 3.x only. Exiting...")
    exit(1)

# the commands drive resourcetools, nvltssm and mstdump at the python level,
# from their sibling directories
mft_py_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.append(os.path.join(mft_py_dir, "resourcetools"))
sys.path.append(os.path.join(mft_py_dir, "mstltssm"))
sys.path.append(os.path.join(mft_py_dir, "mstdump"))

from commands.CommandFactory import CommandFactory  # noqa
import commands  # noqa - registers the commands at the factory
from resourceparse_lib.utils.Exceptions import ResourceParseException  # noqa


class PcieSwDbg:
    """This class is responsible for the nvpcie UI by handling the user inputs
    and running the right command.
    """

    tool_name = os.path.basename(__file__).split('.')[0]

    DESCRIPTION = "NVIDIA PCIe Switch debug tool"

    # the CLI words that hold commands instead of running themselves, with what
    # they present in the help. A command names the one it belongs to
    _COMMAND_GROUPS = {
        "trace": "show a history the device logged",
    }

    @classmethod
    def get_arg_parser(cls):
        """This method build the tool parser from the registered commands, so
        adding a command does not require a change here.
        """
        arg_parser = argparse.ArgumentParser(prog=cls.tool_name, description=cls.DESCRIPTION)
        arg_parser.add_argument("-v", "--version", action="version", help="Shows tool version",
                                version=tools_version.GetVersionString(cls.tool_name, None))
        arg_parser.add_argument("-d", "--device", metavar="DEVICE",
                                help='The device to work on')

        command_parsers = arg_parser.add_subparsers(title='commands', dest="command")
        command_parsers.required = True
        group_parsers = {}
        for command_name, command_class in CommandFactory.commands.items():
            parsers = cls._get_parsers_of_group(command_parsers, group_parsers, command_class.COMMAND_GROUP)
            command_parser = parsers.add_parser(command_name, help=command_class.DESCRIPTION,
                                                description=command_class.DESCRIPTION)
            command_class.set_argument_parser(command_parser)

        return arg_parser

    @classmethod
    def _get_parsers_of_group(cls, command_parsers, group_parsers, group_name):
        """This method return the sub-parsers the commands of a group are declared on.

        A group holds commands rather than running itself, so its parser is built
        on the first command naming it and the ones after it are added to the same.
        """
        if not group_name:
            return command_parsers

        if group_name not in group_parsers:
            group_parser = command_parsers.add_parser(group_name, help=cls._COMMAND_GROUPS[group_name],
                                                      description=cls._COMMAND_GROUPS[group_name])
            group_parsers[group_name] = group_parser.add_subparsers(title='commands',
                                                                    dest=cls._group_argument(group_name))
            group_parsers[group_name].required = True

        return group_parsers[group_name]

    @classmethod
    def _group_argument(cls, group_name):
        """This method return the argument a group keeps the chosen command in."""
        return "{0}_command".format(group_name)

    @classmethod
    def create_command(cls, arguments):
        """This method create the requested command out of the parsed arguments.

        The command is given the chance to reject a combination argparse cannot
        express, since the common arguments and the command ones are declared on
        two different parsers. The command name is then removed - both words of
        it when the command is reached through a group - so what is left are
        exactly the command arguments and the common ones.
        """
        command_args = vars(arguments)
        command_name = command_args.pop("command")
        if command_name in cls._COMMAND_GROUPS:
            command_name = command_args.pop(cls._group_argument(command_name))
        CommandFactory.get(command_name).validate_arguments(arguments)
        return CommandFactory.create(command_name, **command_args)


if __name__ == '__main__':
    try:
        args = PcieSwDbg.get_arg_parser().parse_args()
        command = PcieSwDbg.create_command(args)
        sys.exit(command.run())
    except KeyboardInterrupt:
        print("Aborted by user.")
        sys.exit(1)
    except ResourceParseException as rpe:
        print("Error: {0}. Exiting...".format(rpe))
        sys.exit(1)
    except Exception as e:
        print("Error: {0}. Exiting...".format(e))
        sys.exit(1)
