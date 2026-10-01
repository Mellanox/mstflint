# Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
from argparse import ArgumentTypeError, ArgumentParser

FORMATTER_CLASSES = {}


def formatter_type(name):
    chosen_type = FORMATTER_CLASSES.get(name)
    if not chosen_type:
        raise ArgumentTypeError("invalid formatter type")
    return chosen_type


class SegmentFormatter(ABC):
    """This class defines how a decoded segment is presented.

    The decode walk itself (offsets, conditions, unions, enums) stays in the
    parser; a formatter only decides the shape of the output. Parsers hold a
    formatter instance and route every decoded field through it, so a single
    decode implementation can render text, a customer-readable view or JSON.
    """

    def __init__(self, formatter_args):
        pass

    @classmethod
    def get_arg_parser(cls, prog=None):
        arg_parser = ArgumentParser(prog="{} ... --formatter {}".format(prog, cls.FORMATTER_TYPE), description=cls.get_description(), add_help=False)
        return arg_parser

    @staticmethod
    @abstractmethod
    def get_description():
        return \
            """"""

    def get_output(self, parsed_segment_db):
        """This method return the whole output as a list of lines, or None to let
        the printer build the output segment by segment.

        Formatters that write into the segments (the text ones) keep returning
        None; formatters that produce a single document (like JSON) return it
        here, so that the printer stays the only component that writes output.
        """
        return None

    def format_segment_header(self, seg_type, seg_name, additional_info, seg):
        """This method present the segment header. Formatters that emit no
        per-segment header (e.g. a flat table) may leave it as is.
        """
        pass

    @abstractmethod
    def format_terminal_field(self, field_name, field_value, seg, layout_item=None):
        """This method present a single decoded field that holds a value, where
        field_name is the full dotted path of the field and field_value its
        already-formatted value.

        layout_item is the adb layout item the value was decoded from, for the
        formatters that present a field according to its adb attributes. It is
        optional, so that a parser that decodes without an adb layout can format
        its fields as well.
        """
        pass

    def format_inner_field(self, field_name, seg, layout_item=None):
        """This method called for a field that holds other fields, before the
        parser descends into it, so that a formatter which presents a known layout
        can tell which part of it the fields that follow belong to.

        Formatters that present every field the same way may leave it as is.
        """
        pass

    def format_raw_data(self, seg, is_fallback):
        """This method present the raw bytes of a segment.

        is_fallback is True when the segment could not be decoded, so the raw data
        is the only content there is, and False when it is extra output requested
        on top of the decoded fields. Formatters that present no raw view may leave
        it as is.
        """
        pass

    def end_segment(self, seg):
        """This method called after the last field of a segment was formatted, to
        let formatters that accumulate a segment emit it as a whole.
        """
        pass
