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
from argparse import ArgumentTypeError

from nvltssm_lib.LtssmRing import LtssmAnnotation, LtssmCurrentState, LtssmEntry, LtssmEvent

FORMATTER_CLASSES = {}


def formatter_type(name):
    chosen_type = FORMATTER_CLASSES.get(name)
    if not chosen_type:
        raise ArgumentTypeError("invalid formatter type")

    return chosen_type


class LtssmFormatter(ABC):
    """This class defines how a decoded LTSSM ring is presented.

    The ring walk, the field decode and the name tables stay in LtssmRing; a
    formatter only decides the shape of the output, so the same decode can be
    rendered as a readable report or as the legacy tracer text.
    """

    def get_output(self, dump_file, device_name, pcore, link, ring):
        """This method returns the whole report as a list of lines."""
        lines = self.format_header(dump_file, device_name, pcore, link, ring)

        for record in ring.walk():
            lines.extend(self.format_record(record))

        return lines

    def format_record(self, record):
        if isinstance(record, LtssmEvent):
            return self.format_event(record)

        if isinstance(record, LtssmEntry):
            return self.format_entry(record)

        if isinstance(record, LtssmAnnotation):
            return self.format_annotation(record)

        if isinstance(record, LtssmCurrentState):
            return self.format_current_state(record)

        return []

    @staticmethod
    @abstractmethod
    def get_description():
        return \
            """"""

    @abstractmethod
    def format_header(self, dump_file, device_name, pcore, link, ring):
        """This method presents what the report is of, before the first record."""
        pass

    @abstractmethod
    def format_entry(self, entry):
        """This method presents one logged LTSSM state transition."""
        pass

    @abstractmethod
    def format_event(self, event):
        """This method presents one logged firmware event."""
        pass

    @abstractmethod
    def format_annotation(self, annotation):
        """This method presents a note about the entry that follows it."""
        pass

    @abstractmethod
    def format_current_state(self, current_state):
        """This method presents the link state as it is now, closing the report."""
        pass
