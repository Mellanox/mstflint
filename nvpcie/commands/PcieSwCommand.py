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

from abc import ABC, abstractmethod


class PcieSwCommand(ABC):
    """This class is the base of every nvpcie sub-command.

    Each sub-command is a thin wrapper over an existing MFT tool and declares
    its own arguments next to the code that consumes them, so adding a
    sub-command does not touch the tool entry point.

    Sub-classes take plain keyword arguments (not an argparse namespace) so that
    they stay usable from python - the snapshot command builds its sub-commands
    programmatically rather than through argparse.
    """

    DESCRIPTION = ""

    # the CLI word the command is reached under, for a command spelled
    # "<group> <command>" rather than as a word of its own
    COMMAND_GROUP = None

    # the sub-parser the command declared its arguments on, so that a rejected
    # combination is reported as a usage error of that command
    _arg_parser = None

    @classmethod
    def set_argument_parser(cls, parser):
        """This method add the command arguments to its sub-parser.

        Sub-classes call super() first, so inherited arguments are presented
        before the command specific ones.
        """
        cls._arg_parser = parser

    @classmethod
    def validate_arguments(cls, arguments):
        """This method reject an argument combination argparse cannot express, by
        calling cls._arg_parser.error() so that it is reported as a usage error.

        The common arguments and the command ones are declared on two different
        parsers, so a rule spanning both - a command needing either the common
        device or an argument of its own - has no argparse construct to state it.
        """
        pass

    @abstractmethod
    def run(self):
        """This method execute the command and return a process exit code."""
        pass
