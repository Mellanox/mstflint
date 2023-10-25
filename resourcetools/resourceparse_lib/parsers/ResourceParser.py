# Copyright (C) Jan 2020 Mellanox Technologies Ltd. All rights reserved.
# Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
# --


#######################################################
#
# ResourceParser.py
# Created on:      12-Jun-2023 11:13:33 AM
# Original author: astrutsovsky
#
#######################################################

from abc import ABC, abstractmethod
from argparse import ArgumentTypeError, ArgumentParser

PARSER_CLASSES = {}


def parser_type(name):
    chosen_type = PARSER_CLASSES.get(name)
    if not chosen_type:
        raise ArgumentTypeError("invalid parser type")
    return chosen_type


class ResourceParser(ABC):
    @abstractmethod
    def __init__(self, parser_args):
        pass

    @abstractmethod
    def parse_segment(self, segment):
        pass

    def get_title(self):
        return ""

    def get_segment_separator(self):
        return ""

    def validate(self):
        return True

    @classmethod
    def get_arg_parser(cls, prog=None):
        arg_parser = ArgumentParser(prog="{} ... --parser {}".format(prog, cls.PARSER_TYPE), description=cls.get_description(), add_help=False)
        return arg_parser

    @staticmethod
    @abstractmethod
    def get_description():
        return \
            """"""
