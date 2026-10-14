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
# --

import argparse
import errno
import os

from pathlib import Path


def nearest_existing(path):
    """The closest component of "path" that is there, so a name not created yet
    is answered for by whatever it would be created under.

    Each component is read through "os.path", which answers "no" for one behind
    a directory that cannot be searched rather than raising on it.
    """
    nearest = Path(path)
    while not os.path.lexists(nearest) and nearest != nearest.parent:
        nearest = nearest.parent

    return nearest


def is_link_loop(path):
    """Whether "path" is a cycle of symlinks, which resolves to a link again.
    A dangling one resolves to the missing target it names, so it answers no.
    """
    return os.path.lexists(path) and os.path.islink(os.path.realpath(path))


def unreachable_reason(directory):
    """Why "directory" did not answer: a cycle of symlinks, something that is
    not a directory, one that cannot be searched, or simply not there.

    Reading the failed stat as "missing" would name the wrong mistake whenever
    the caller only lacks search permission somewhere above it, named a loop, or
    named something below a file. A dangling symlink is the one component that
    does read as missing, which is what walking through it answers.
    """
    nearest = nearest_existing(directory)
    if is_link_loop(nearest):
        return errno.ELOOP

    if not os.path.exists(nearest):
        return errno.ENOENT

    if not nearest.is_dir():
        return errno.ENOTDIR

    if not os.access(nearest, os.X_OK):
        return errno.EACCES

    return errno.ENOENT


def verify_input_file(path):
    """An "argparse" type for an argument naming a file the tool reads.

    The parent is answered for before the file is stat'ed, since a name behind a
    directory that cannot be searched fails its stat rather than reporting what
    is there, and pathlib passes that failure on instead of reading it as "no".

    A cycle of symlinks is refused as the loop it is, since it does not exist as
    far as a stat is concerned while the open answers something else entirely.

    An empty argument is refused rather than read as the current directory, for
    the reason verify_output_file refuses one.

    A trailing separator on something that is not a directory is refused as what
    the open answers, since Path drops the separator and would otherwise read
    the name as the file it names.
    """
    in_file = Path(path)
    parent = in_file.parent
    if not path:
        reason = errno.ENOENT
    elif not os.path.exists(parent):
        reason = unreachable_reason(parent)
    elif not parent.is_dir():
        reason = errno.ENOTDIR
    elif not os.access(parent, os.X_OK):
        reason = errno.EACCES
    elif is_link_loop(path):
        reason = errno.ELOOP
    elif not in_file.exists():
        reason = errno.ENOENT
    elif in_file.is_dir():
        reason = errno.EISDIR
    elif path[-1] in (os.sep, os.altsep):
        reason = errno.ENOTDIR
    elif not in_file.is_file():
        reason = errno.EINVAL
    elif not os.access(in_file, os.R_OK):
        reason = errno.EACCES
    else:
        return path

    raise argparse.ArgumentTypeError("Failed to read '{}': {}".format(path, os.strerror(reason)))


def verify_output_file(path):
    """An "argparse" type for an argument naming a file the tool writes.

    An empty argument is refused rather than read as a request to print, since
    the realistic way to arrive at one is a script naming a variable it never
    set, and silently printing hides that.

    A trailing separator is refused, since it names a directory while Path drops
    it, which would otherwise pass the checks and fail the open.

    A dangling symlink is answered for by what it points at rather than refused,
    since writing it creates that target where the target's parent exists. One
    that points at itself resolves to a link again, and is refused as the loop
    it is.

    What cannot be searched is answered for before the destination is stat'ed,
    since a name behind such a directory fails its stat rather than reporting
    what is there, and pathlib passes that failure on instead of reading it as
    "no". Those reads go through "os.path", which does not raise.

    An existing destination has to be a regular file: a tool opening a FIFO to
    write it waits for a reader that may never come, and a device node takes the
    output in place of a file.
    """
    out_file = Path(path)
    if not os.path.exists(path) and os.path.lexists(path):
        out_file = Path(os.path.realpath(path))

    parent = out_file.parent
    if not path:
        reason = errno.ENOENT
    elif path[-1] in (os.sep, os.altsep):
        reason = errno.EISDIR
    elif is_link_loop(path):
        reason = errno.ELOOP
    elif not os.path.exists(parent):
        reason = unreachable_reason(parent)
    elif not parent.is_dir():
        reason = errno.ENOTDIR
    elif not os.access(parent, os.X_OK):
        reason = errno.EACCES
    elif out_file.is_dir():
        reason = errno.EISDIR
    elif out_file.exists() and not out_file.is_file():
        reason = errno.EINVAL
    elif not (os.access(out_file, os.W_OK) if out_file.exists()
              else os.access(parent, os.W_OK)):
        reason = errno.EACCES
    else:
        return path

    raise argparse.ArgumentTypeError("Failed to write '{}': {}".format(path, os.strerror(reason)))


def verify_output_dir(path):
    """An "argparse" type for an argument naming a directory the tool writes into.

    An empty argument is refused rather than read as the current directory, for
    the reason verify_output_file refuses one.

    A chain of components that do not exist yet is accepted, since the tool
    creates the directory it was given - so it is the nearest component that
    does exist which says whether it can be created. A symlink is answered for
    by what it points at, and a dangling one is refused rather than passed over:
    creating the directory it names fails on the link already being there. A
    cycle of them is named as the loop it is, which is what the create answers.
    """
    nearest = nearest_existing(path)
    if not path:
        reason = errno.ENOENT
    elif is_link_loop(nearest):
        reason = errno.ELOOP
    elif not nearest.is_dir():
        reason = errno.ENOTDIR
    elif not os.access(nearest, os.W_OK | os.X_OK):
        reason = errno.EACCES
    else:
        return path

    raise argparse.ArgumentTypeError("Failed to write '{}': {}".format(path, os.strerror(reason)))
