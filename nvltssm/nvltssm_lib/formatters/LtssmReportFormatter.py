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

from nvltssm_lib.LtssmRing import LtssmAnnotation, LtssmTiming
from nvltssm_lib.formatters.LtssmFormatter import FORMATTER_CLASSES, LtssmFormatter


class LtssmReportFormatter(LtssmFormatter):
    """Presents the ring as a column-aligned history table."""

    FORMATTER_TYPE = "report"

    ROW = "{:>4}  {:<5} {:<5} {:<38} {:<21} {}"
    ANNOTATION = "{:>4}  -- {} --"
    COLUMNS = ("Slot", "Speed", "Width", "State", "Exit reason", "Dwell")
    SEPARATOR = ("----", "-----", "-----", "--------------------------------------",
                 "---------------------", "------------")
    CURRENT_SLOT = "CUR"
    FW_EVENT_SPEED = "FW"
    ABSENT = "-"

    @staticmethod
    def get_description():
        return \
            """Presents the LTSSM history as a column-aligned table, oldest transition first."""

    def format_header(self, dump_file, device_name, pcore, link, ring):
        return [
            "LTSSM history of pcore {}, link {}".format(pcore, link),
            "Dump: {}{}".format(dump_file, " ({})".format(device_name) if device_name else ""),
            "Ring: {} slots, oldest first, next write slot {}, tick {} ns".format(
                ring.SIZE, ring.current_index, LtssmTiming.TICK_NS),
            "",
            self.ROW.format(*self.COLUMNS),
            self.ROW.format(*self.SEPARATOR),
        ]

    def format_entry(self, entry):
        return [self.ROW.format(entry.slot,
                                self._speed(entry.speed),
                                "x{}".format(entry.link_width),
                                self._state(entry.state, entry.state_name),
                                entry.reason_name or self.ABSENT,
                                self._dwell(entry.timing))]

    def format_event(self, event):
        return [self.ROW.format(event.slot,
                                self.FW_EVENT_SPEED,
                                self.ABSENT,
                                self._state(event.event_num, event.event_name),
                                self.ABSENT,
                                self._dwell(event.timing))]

    def format_annotation(self, annotation):
        if annotation.kind == LtssmAnnotation.SPEED_CHANGE:
            note = "Speed change: {} -> {}".format(self._speed(annotation.old), self._speed(annotation.new))
        elif annotation.kind == LtssmAnnotation.WIDTH_CHANGE:
            note = "Width change: x{} -> x{}".format(annotation.old, annotation.new)
        else:
            note = annotation.name

        return [self.ANNOTATION.format("", note)]

    def format_current_state(self, current_state):
        return [self.ROW.format(self.CURRENT_SLOT,
                                self._speed(current_state.speed),
                                "x{}".format(current_state.link_width),
                                self._state(current_state.state, current_state.state_name),
                                self.ABSENT,
                                self.ABSENT)]

    def _speed(self, speed):
        return "Gen{}".format(speed)

    def _state(self, code, name):
        return "0x{:02x} {}".format(code, name or "unknown")

    def _dwell(self, timing):
        if timing.is_saturated:
            return "{:.2f} ms or more".format(timing.milliseconds)

        return "{:.2f} ms".format(timing.milliseconds)


FORMATTER_CLASSES[LtssmReportFormatter.FORMATTER_TYPE] = LtssmReportFormatter
