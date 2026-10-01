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

import datetime
import re
from enum import IntEnum, auto

from resourceparse_lib.formatters.SegmentFormatter import SegmentFormatter, FORMATTER_CLASSES
from resourceparse_lib.utils import constants as cs
from resourceparse_lib.utils.common_functions import is_resource_segment


class PcieEventFormatter(SegmentFormatter):
    """This class present NVLOG event segments as a PCIe event log.

    One block per event segment, under a header naming the device, the event view
    that was requested and the number of events the report holds. A block opens
    with a line carrying the time of the event, the class it belongs to and its
    name, and continues with where it happened and the detail lines of the
    selected payload.

    The layout of those detail lines is not written here: the selected union arm
    declares it as a format attribute in the ADABE, so an arm that grows a field
    presents it with no change to this class.

    The formatter accumulates the whole report and returns it from get_output(),
    rather than writing into the segments, since the header states a count that is
    only known once the last event was seen.

    A resource-dump request is answered with several response segments, of which
    every resource segment carries an event record and the control segments carry
    none, so the control segments contribute no block. Two of them still have
    something to say, and say it in the header rather than in a block: the info
    segment states the firmware version of the device, and an error or notice
    segment states why the events it was asked for are not there.
    """

    class EventSection(IntEnum):
        """The parts an event TLV is built of, in parse order: the NVLOG header,
        the event, the payload union, and under it the arm the event_id selected.

        Member names are the ADABE node names uppercased. PAYLOAD_ARM is entered
        under the union at the call site, not by name lookup.
        """

        EVENT_HEADER = auto()
        PCIE_EVENT = auto()
        PAYLOAD = auto()
        PAYLOAD_ARM = auto()

    class EventFields:
        """The fields of one event, composed from the field maps of its segment.

        It states what the event carries rather than how a report presents it: an
        event holding both a BDF and a DPN keeps both, and the details are the
        fields of the selected arm next to the format it declares for them, so the
        lines they compose are rendered by the formatter that needs them.
        """

        __slots__ = ("time", "event_class", "bdf", "dpn", "event", "details", "details_format")

        EVENT_HEADER_SEPARATOR = "  "
        TIME_BRACKET_FORMAT = "[{0}]"
        EVENT_CLASS_BRACKET_FORMAT = "[{0}]"
        EVENT_NAME_FORMAT = "**{0}**"

        TIME_LOW_FIELD = "time_lo"
        TIME_HIGH_FIELD = "time_hi"
        TIME_SYNCED_FIELD = "time_synced"
        LOST_EVENT_FIELD = "lost_event"
        EVENT_ID_FIELD = "event_id"

        BDF_LABEL = "BDF"
        DPN_LABEL = "DPN"
        BDF_FIELDS = ("bus", "device", "function")
        DPN_FIELDS = ("depth", "pcie_index", "node")
        # bus is 8 bits, device 5 and function 3, so the BDF value is the lspci notation
        BDF_FORMAT = "{0:02x}:{1:02x}.{2:x}"
        DPN_FORMAT = "{0}/{1}/{2}"
        LOCATION_FIELDS = BDF_FIELDS + DPN_FIELDS
        # The report states one location, the most specific identifier the event has
        LOCATION_LINE_FORMAT = "{0}  {1}"
        LOCATION_LINES = ((BDF_LABEL, "bdf"), (DPN_LABEL, "dpn"))

        TIME_HIGH_SHIFT = 32
        SYNCED_TIME_FORMAT = "%Y-%m-%d %H:%M:%S.%f"
        # The seconds are right aligned on a field wide enough for a multi-year uptime, so
        # that uptimes of a different magnitude line up on their decimal point. A narrower
        # field is only a minimum width, and the point walks right once it overflows
        UPTIME_FORMAT = "{0:>8}.{1:06d}s"

        ENUM_VALUE_PATTERN = re.compile(r"^\((?P<symbol>\S+) = \S+\)$")

        def __init__(self, header_fields, details, event_id, event_class, details_format):
            self.time = self._format_time(header_fields)
            self.event_class = event_class if event_class else cs.LABEL_NOT_AVAILABLE
            self.bdf = self._format_identifier(details, self.BDF_FORMAT, self.BDF_FIELDS)
            self.dpn = self._format_identifier(details, self.DPN_FORMAT, self.DPN_FIELDS)
            self.event = self._format_event(event_id)
            self.details = details
            self.details_format = details_format

        @classmethod
        def _format_time(cls, header_fields):
            time_low = cls._to_int(header_fields.get(cls.TIME_LOW_FIELD))
            time_high = cls._to_int(header_fields.get(cls.TIME_HIGH_FIELD))
            if time_low is None or time_high is None:
                return cs.LABEL_NOT_AVAILABLE

            # the seconds and the microseconds are kept apart in both forms, a float
            # loses microseconds at the magnitude of an epoch time
            microseconds = (time_high << cls.TIME_HIGH_SHIFT) | time_low
            seconds, remainder = divmod(microseconds, int(1e6))

            if not cls._to_int(header_fields.get(cls.TIME_SYNCED_FIELD)):
                return cls._format_uptime(seconds, remainder)

            try:
                event_time = datetime.datetime.fromtimestamp(seconds, datetime.timezone.utc) \
                    + datetime.timedelta(microseconds=remainder)
                return event_time.strftime(cls.SYNCED_TIME_FORMAT)
            except (OverflowError, OSError, ValueError):
                return cls._format_uptime(seconds, remainder)

        @classmethod
        def _format_uptime(cls, seconds, remainder):
            return cls.UPTIME_FORMAT.format(seconds, remainder)

        @classmethod
        def _format_identifier(cls, details, value_format, fields):
            """This method compose one identifier of where the event happened, or None
            when the payload does not state it in full.

            An identifier missing any one of its parts is passed over rather than
            half-composed, since a partial one identifies nothing - 00:??.0 names no
            device.
            """
            parts = [cls._to_int(details.get(field)) for field in fields]
            if all(part is not None for part in parts):
                return value_format.format(*parts)

            return None

        @classmethod
        def _format_event(cls, event_id):
            if event_id is None:
                return cs.LABEL_NOT_AVAILABLE

            symbol = cls._enum_symbol(event_id)
            if symbol is None:
                return event_id
            return symbol.replace("_", " ").capitalize()

        @classmethod
        def _enum_symbol(cls, value):
            enum_value = cls.ENUM_VALUE_PATTERN.match(value)
            return enum_value.group("symbol") if enum_value else None

        @staticmethod
        def _to_int(value):
            try:
                return int(value, 0)
            except (TypeError, ValueError):
                return None

    class EventReportHeader:
        __slots__ = ("device", "view", "fw_version", "events")
        HEADER_LABELS = ("Device", "Event view", "FW version", "Events")
        HEADER_LABEL_WIDTH = 14
        HEADER_VALUE_SEPARATOR = ": "
        HEADER_LINE_FORMAT = "{0:<{1}}{2}{3}"

        def __init__(self, device, view, fw_version=None):
            self.device = device
            self.view = view
            self.fw_version = cs.LABEL_NOT_AVAILABLE if fw_version is None else fw_version
            self.events = 0

        def format_header(self):
            """This method present the header as one labelled line per field, in the
            order the fields are declared.
            """
            return [self.HEADER_LINE_FORMAT.format(label, self.HEADER_LABEL_WIDTH,
                                                   self.HEADER_VALUE_SEPARATOR, getattr(self, slot))
                    for label, slot in zip(self.HEADER_LABELS, self.__slots__)]

    FORMATTER_TYPE = "pcie-events"

    TITLE = "PCIe Event Log"

    DEFAULT_INDENT = "  "

    EVENT_CLASS_ATTR = "event_class"
    DETAILS_FORMAT_ATTR = "format"
    DETAILS_ITEM_FORMAT = "{0} {1}"
    DETAILS_SEPARATOR = " | "

    # An xml attribute value cannot hold a real newline - the parser normalises it
    # to a space - so a details format spells a line break as these two characters
    DETAILS_LINE_BREAK_ESCAPE = "\\n"

    # The enum label of a value the event does not carry. It is dropped from the
    # line it was rendered into, which is how an arm presents a field only when it
    # means something, with no conditional in the format string.
    OMITTED_VALUE_SYMBOL = "_N/A_"
    OMITTED_VALUE_PATTERN = re.compile(r"\s*" + re.escape(OMITTED_VALUE_SYMBOL))

    LOST_EVENTS_NOTICE = "Lost events were reported before {0} records."

    # The response segments that carry a message instead of an event: firmware
    # answers a request it will not serve with an error segment, and qualifies an
    # answer it does serve with a notice segment
    MESSAGE_SEGMENT_TYPES = (cs.RESOURCE_DUMP_SEGMENT_TYPE_ERROR,
                             cs.RESOURCE_DUMP_SEGMENT_TYPE_NOTICE)
    MESSAGES_TITLE = "Events Collecting Issues"

    # A segment message quotes a fixed width string field, so it trails the NUL
    # padding of that field - which a terminal renders as a run of blanks
    SEGMENT_MESSAGE_PADDING = "\x00 \t\r\n"

    ARRAY_ELEMENT_PATTERN = re.compile(r"^(?P<name>.+)\[(?P<index>\d+)\]$")

    @classmethod
    def get_arg_parser(cls, prog=None):
        arg_parser = super().get_arg_parser(prog)

        optional_named = arg_parser.add_argument_group('optional arguments')
        optional_named.add_argument("--device", default=cs.LABEL_NOT_AVAILABLE, help='The device the events were read from, for the log header')
        optional_named.add_argument("--view", default=cs.LABEL_NOT_AVAILABLE, help='The event view that was requested, for the log header')

        return arg_parser

    @staticmethod
    def get_description():
        return \
            """        This formatter presents the segments as a PCIe event log: a block per
        event, with its time, class and name, followed by its location and details.
"""

    def __init__(self, formatter_args):
        super().__init__(formatter_args)
        self._report_header = self.EventReportHeader(formatter_args.device, formatter_args.view)
        self._event_fields = []
        self._segment_messages = []
        self._lost_events_count = 0
        self._segment_type = None
        self._event_header_fields = {}
        self._event_details_fields = {}
        self._event_id = None
        self._event_class = None
        self._details_format = None
        self._current_section = None

    def format_segment_header(self, seg_type, seg_name, additional_info, seg):
        self._start_record(seg_type)
        if seg_type == cs.RESOURCE_DUMP_SEGMENT_TYPE_INFO:
            self._report_header.fw_version = seg.get_display_fw_version() or cs.LABEL_NOT_AVAILABLE
        elif seg_type in self.MESSAGE_SEGMENT_TYPES:
            self._collect_segment_message(seg)

    def _collect_segment_message(self, seg):
        """This method take the message of a segment that carries one instead of an
        event, so that a firmware refusal is not presented as an event log that is
        simply empty.

        Only the last entry is taken: get_messages() formats the message and appends
        it before returning the whole list, so the entry this call produced is the
        one at the end - the parser calls it once more of its own. A segment holding
        no more than its header produces no message at all.
        """
        messages = seg.get_messages()
        if messages:
            # [-1] only because ErrorSegment.get_messages() appends on every call and
            # AdbResourceParser calls it again after us — an unrelated bug; fix the
            # messages mechanism instead of copying the whole list here.
            self._segment_messages.append(messages[-1].rstrip(self.SEGMENT_MESSAGE_PADDING))

    def format_inner_field(self, field_name, seg, layout_item=None):
        """This method follow the parse through the parts of the event TLV, so that
        a field is presented as what its part of the layout makes it.

        A node of a part the layout has a section for opens that section, and the
        node under the payload union is the arm the event_id selected. A node the
        layout has no section for - the segment itself, or one nested inside an arm
        - leaves the section it is parsed under.
        """
        if not is_resource_segment(self._segment_type) or layout_item is None:
            return

        section = getattr(self.EventSection, layout_item.name.upper(), None)
        if section is not None:
            self._current_section = section
        elif self._current_section is self.EventSection.PAYLOAD:
            self._current_section = self.EventSection.PAYLOAD_ARM
            self._event_class = layout_item.attrs.get(self.EVENT_CLASS_ATTR)
            self._details_format = layout_item.attrs.get(self.DETAILS_FORMAT_ATTR)

    def format_terminal_field(self, field_name, field_value, seg, layout_item=None):
        if not is_resource_segment(self._segment_type):
            return

        name = field_name.rsplit(".", 1)[-1]

        if self._current_section is self.EventSection.PAYLOAD_ARM:
            self._event_details_fields[name] = field_value
        elif self._current_section is self.EventSection.EVENT_HEADER:
            self._event_header_fields[name] = field_value
        elif name == self.EventFields.EVENT_ID_FIELD:
            self._event_id = field_value

    def end_segment(self, seg):
        if not is_resource_segment(self._segment_type):
            return

        self._event_fields.append(self.EventFields(self._event_header_fields, self._event_details_fields,
                                                   self._event_id, self._event_class, self._details_format))
        lost_events = self._event_header_fields.get(self.EventFields.LOST_EVENT_FIELD)
        self._lost_events_count += self.EventFields._to_int(lost_events) or 0

    def get_output(self, parsed_segment_db):
        self._report_header.events = len(self._event_fields)

        lines = [self.TITLE]
        lines.extend(self._report_header.format_header())

        if self._segment_messages:
            lines.append("")
            lines.append(self.MESSAGES_TITLE)
            lines.extend(self.DEFAULT_INDENT + message for message in self._segment_messages)

        for event_fields in self._event_fields:
            lines.append("")
            lines.extend(self._build_event_block(event_fields))

        if self._lost_events_count > 0:
            lines.append("")
            lines.append(self.LOST_EVENTS_NOTICE.format(self._lost_events_count))

        return lines

    def _start_record(self, segment_type):
        """This method start the accumulation of a single event, since a record is
        built from the fields of one segment.
        """
        self._segment_type = segment_type
        self._event_header_fields = {}
        self._event_details_fields = {}
        self._event_id = None
        self._event_class = None
        self._details_format = None
        self._current_section = None

    @classmethod
    def _format_details(cls, event_fields):
        """This method present the fields of the event that have no line of their
        own as the lines the selected arm asked for, or as a plain listing when the
        arm declares no format at all.

        An arm declaring an empty format states that it has no details to present,
        which is not the same as declaring none: the listing is the fallback of an
        arm the layout has no format for.
        """
        rendered = None
        if event_fields.details_format is not None:
            rendered = cls._render_details(event_fields.details_format, event_fields.details)
        if rendered is None:
            rendered = cls._list_details(event_fields.details)

        lines = (cls.OMITTED_VALUE_PATTERN.sub("", line).strip() for line in rendered.split("\n"))
        return [line for line in lines if line]

    @classmethod
    def _render_details(cls, details_format, details):
        """This method render a details format string, or return None when it and
        the layout disagree, so that the plain listing takes over.

        The line break escape is resolved before the values are placed, so that a
        value holding those two characters cannot open a line of its own.
        """
        try:
            return details_format.replace(cls.DETAILS_LINE_BREAK_ESCAPE, "\n").format(**cls._build_details_values(details))
        except (KeyError, IndexError, AttributeError):
            return None

    @classmethod
    def _list_details(cls, details):
        """This method present the details of an arm that declares no format, as a
        plain listing of the fields that have no line of their own.
        """
        return cls.DETAILS_SEPARATOR.join(
            cls.DETAILS_ITEM_FORMAT.format(name, display_value)
            for name, display_value in cls._detail_field_items(details))

    @classmethod
    def _detail_field_items(cls, details):
        """This method yield the fields of the event that have no line of their own,
        each by its display value, in the order the layout declares them.

        A field the event does not carry is dropped rather than yielded, which is
        how an arm presents a field only when it means something.
        """
        for name, value in details.items():
            if not cls._is_detail_field(name):
                continue
            display_value = cls._field_display_value(value)
            if display_value != cls.OMITTED_VALUE_SYMBOL:
                yield name, display_value

    @classmethod
    def _build_details_values(cls, details):
        """This method collect the values a details format string is rendered with,
        an array as a list, so that an element is reachable as {name[index]}.
        """
        values = {}
        for name, value in details.items():
            array_element = cls.ARRAY_ELEMENT_PATTERN.match(name)
            if array_element:
                values.setdefault(array_element.group("name"), []).append(cls._field_display_value(value))
            else:
                values[name] = cls._field_display_value(value)
        return values

    @classmethod
    def _is_detail_field(cls, field_name):
        array_element = cls.ARRAY_ELEMENT_PATTERN.match(field_name)
        name = array_element.group("name") if array_element else field_name
        return name not in cls.EventFields.LOCATION_FIELDS

    @classmethod
    def _build_event_block(cls, event_fields):
        """This method present one event as the line that identifies it and the
        detail lines indented under it.

        A part the event has nothing to state contributes nothing: an arm that
        declares no class opens the block with the time alone, and an arm with
        neither BDF nor DPN fields has no location line.
        """
        header_parts = [cls.EventFields.TIME_BRACKET_FORMAT.format(event_fields.time)]
        if event_fields.event_class != cs.LABEL_NOT_AVAILABLE:
            header_parts.append(cls.EventFields.EVENT_CLASS_BRACKET_FORMAT.format(event_fields.event_class.upper()))
        header_parts.append(cls.EventFields.EVENT_NAME_FORMAT.format(event_fields.event))

        lines = [cls.EventFields.EVENT_HEADER_SEPARATOR.join(header_parts)]
        location = cls._format_location(event_fields)
        if location:
            lines.append(cls.DEFAULT_INDENT + location)
        lines.extend(cls.DEFAULT_INDENT + detail for detail in cls._format_details(event_fields))
        return lines

    @classmethod
    def _format_location(cls, event_fields):
        """This method present the one location line of the report, stating the most
        specific identifier the event carries - its BDF when it has one, and its DPN
        otherwise.

        The choice is the report's, not the event's: the fields state every
        identifier the event gave, and an event carrying both is presented by its
        BDF alone. An event carrying neither has no location line at all, rather
        than one reading N/A.
        """
        for label, identifier in cls.EventFields.LOCATION_LINES:
            value = getattr(event_fields, identifier)
            if value:
                return cls.EventFields.LOCATION_LINE_FORMAT.format(label, value)

        return None

    @classmethod
    def _field_display_value(cls, value):
        """This method present a decoded value, an enum by its symbol alone, since
        the numeric value of an enum carries nothing for the reader.
        """
        symbol = cls.EventFields._enum_symbol(value)
        return symbol if symbol is not None else value


FORMATTER_CLASSES[PcieEventFormatter.FORMATTER_TYPE] = PcieEventFormatter
