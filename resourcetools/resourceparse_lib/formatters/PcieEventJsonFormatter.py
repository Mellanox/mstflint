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

import json

from resourceparse_lib.formatters.SegmentFormatter import FORMATTER_CLASSES
from resourceparse_lib.formatters.PcieEventFormatter import PcieEventFormatter


class PcieEventJsonFormatter(PcieEventFormatter):
    """This class serialize the PCIe event log as a JSON document.

    It collects what the event report collects - the same header, the same events
    and the same issues, through the same segment hooks - and only presents them
    differently, so the two formats of the tool cannot disagree about what the
    device reported.

    Where the report has to pick one location line per event, the document states
    every identifier the event carries: a consumer has no reason to lose the DPN of
    an event that also has a BDF. It states only those, though - an identifier the
    event layout does not describe at all is absent from the object rather than null.
    """

    FORMATTER_TYPE = "pcie-events-json"

    HEADER_KEY = "header"
    MESSAGES_KEY = "collecting_issues"
    EVENTS_KEY = "events"
    LOST_EVENTS_KEY = "lost_events"
    DETAILS_KEY = "details"

    # The parts of an event stated under a key of their own, the two location
    # identifiers among them. The details follow under DETAILS_KEY, and the format
    # they are rendered with is a presentation matter the document has no key for.
    EVENT_KEYS = ("time", "event_class", "bdf", "dpn", "event")

    # The payload fields each location identifier is composed of, for the keys of
    # EVENT_KEYS that name one. An event layout describes either identifier, both or
    # neither, and a key is stated only by the events whose layout describes it.
    LOCATION_IDENTIFIER_FIELDS = {
        "bdf": PcieEventFormatter.EventFields.BDF_FIELDS,
        "dpn": PcieEventFormatter.EventFields.DPN_FIELDS,
    }

    INDENT = 4

    @staticmethod
    def get_description():
        return \
            """        This formatter serializes the PCIe event log as a JSON document: the report
        header, an object per event with its location and details, and the issues
        raised while collecting them.
        Use the common -o/--out option to write it to a file.
"""

    def get_output(self, parsed_segment_db):
        """This method return the whole event log as the lines of a JSON document.

        The header is keyed by the slots of EventReportHeader, as the report labels
        it, so the two presentations cannot drift apart. It is nested rather than
        flattened because the count it holds is named after the events themselves.
        """
        self._report_header.events = len(self._event_fields)

        document = {self.HEADER_KEY: {slot: getattr(self._report_header, slot)
                                      for slot in self.EventReportHeader.__slots__},
                    self.MESSAGES_KEY: self._segment_messages,
                    self.EVENTS_KEY: [self._build_event_object(event_fields) for event_fields in self._event_fields],
                    self.LOST_EVENTS_KEY: self._lost_events_count}

        return json.dumps(document, indent=self.INDENT).split("\n")

    @classmethod
    def _build_event_object(cls, event_fields):
        """This method present one event as an object, holding under its details the
        fields that have no key of their own.

        A location identifier is keyed only when the payload describes the fields it
        is composed of, since a null under a key the layout has no fields for would
        claim an identifier the event could never have stated. Where the layout does
        describe them and the event still left one out, the key stays with a null
        value: that is an identifier missing, not an identifier that does not apply.
        """
        event = {key: getattr(event_fields, key) for key in cls.EVENT_KEYS
                 if cls._describes_identifier(event_fields.details, key)}
        event[cls.DETAILS_KEY] = dict(cls._detail_field_items(event_fields.details))
        return event

    @classmethod
    def _describes_identifier(cls, details, key):
        """This method tell whether the payload describes the location identifier a
        key names. A key naming no identifier is stated by every event.
        """
        fields = cls.LOCATION_IDENTIFIER_FIELDS.get(key)
        return fields is None or any(field in details for field in fields)


FORMATTER_CLASSES[PcieEventJsonFormatter.FORMATTER_TYPE] = PcieEventJsonFormatter
