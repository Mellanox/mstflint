# Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "muparser-lib",
    srcs = [
        "muParser.cpp",
        "muParserBase.cpp",
        "muParserBytecode.cpp",
        "muParserCallback.cpp",
        "muParserError.cpp",
        "muParserInt.cpp",
        "muParserTokenReader.cpp",
    ],
    hdrs = [
        "muParser.h",
        "muParserBase.h",
        "muParserBytecode.h",
        "muParserCallback.h",
        "muParserDef.h",
        "muParserError.h",
        "muParserFixes.h",
        "muParserInt.h",
        "muParserTemplateMagic.h",
        "muParserToken.h",
        "muParserTokenReader.h",
    ],
    include_prefix = "muparser",
    linkopts = ["-lm"],
    visibility = [
        "//pkg:__pkg__",
        "//support/bazel/examples:__pkg__",
        "//user/mlxconfig:__pkg__",
    ],
)

cc_test(
    name = "muparser-lib-test",
    size = "small",
    srcs = [
        "muParserTest.cpp",
        "muParserTest.h",
        "t_ParserTest.cpp",
    ],
    deps = [
        ":muparser-lib",
    ],
)
