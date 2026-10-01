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

from nvltssm_lib.LtssmRing import LtssmAnnotation, LtssmTables
from nvltssm_lib.formatters.LtssmFormatter import FORMATTER_CLASSES, LtssmFormatter


class LtssmLegacyFormatter(LtssmFormatter):
    """Presents the ring exactly as the reference ltssm_tracer.py does.

    Every line is reproduced as that tool emits it, quirks included: a blank
    reason name for reason 0, the "Redo Equalizaion" spelling, a current width
    that is a lane count rather than an encoding, a current time without a unit
    and the leading space its logger format prepends.
    """

    FORMATTER_TYPE = "legacy"

    LINE = " {}"
    BANNER_WIDTH = 100
    BANNER_DEVICE = "pcie_mst_device: {}, pcore: {}, link: {}"
    ENTRY = "%-3d | [G%d / X%-2d] | [0x%02x]- %-35s | Reason %d - %-20s | %s"
    EVENT = "%-3d | [FW_EVENT] | [0x%02x]- %-35s | %s  %-28s | %s"
    CURRENT = "CUR | [G%d / X%-2d] | [0x%02x]- %-35s | Reason %d - %-20s | %-5.1f"
    SPEED_CHANGE = "< -- Speed change: ({} -> {}) -- >"
    WIDTH_CHANGE = "< -- width change: (x{} -> x{}) -- >"
    NOTABLE_STATE = "< -- {} -- >"
    TIME = "{:.2f}ms"
    TIME_SATURATED = "{:.2f}ms (MAX)"
    # The reference prints no reason name for reason 0, so Framing Error never shows.
    BLANK_REASON = 0

    @staticmethod
    def get_description():
        return \
            """Presents the LTSSM history in the text of the reference ltssm_tracer.py, for consumers that parse it."""

    def format_header(self, dump_file, device_name, pcore, link, ring):
        banner = "=" * self.BANNER_WIDTH

        return [
            self.LINE.format(banner),
            self.LINE.format(self.BANNER_DEVICE.format(dump_file, pcore, link)),
            self.LINE.format(banner),
        ]

    def format_entry(self, entry):
        reason_name = "" if entry.reason == self.BLANK_REASON else LtssmTables.REASONS.get(entry.reason, "")
        row = self.ENTRY % (entry.slot, entry.speed, entry.link_width, entry.state, entry.state_name, entry.reason,
                            reason_name, self._time(entry.timing))

        return [self.LINE.format(row)]

    def format_event(self, event):
        row = self.EVENT % (event.slot, event.event_num, event.event_name, " ", " ", self._time(event.timing))

        return [self.LINE.format(row)]

    def format_annotation(self, annotation):
        if annotation.kind == LtssmAnnotation.SPEED_CHANGE:
            note = self.SPEED_CHANGE.format(annotation.old, annotation.new)
        elif annotation.kind == LtssmAnnotation.WIDTH_CHANGE:
            note = self.WIDTH_CHANGE.format(annotation.old, annotation.new)
        else:
            note = self.NOTABLE_STATE.format(annotation.name)

        return [self.LINE.format(note)]

    def format_current_state(self, current_state):
        row = self.CURRENT % (current_state.speed, current_state.link_width, current_state.state,
                              current_state.state_name, 0, "", 0)

        return [self.LINE.format(row)]

    def _time(self, timing):
        template = self.TIME_SATURATED if timing.is_saturated else self.TIME

        return template.format(timing.milliseconds)


FORMATTER_CLASSES[LtssmLegacyFormatter.FORMATTER_TYPE] = LtssmLegacyFormatter
