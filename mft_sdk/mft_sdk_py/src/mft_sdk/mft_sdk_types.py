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

"""
Python ctypes bindings for the NVIDIA MFT SDK
This file provides Python ctypes bindings for the MFT SDK types.
"""

from collections import OrderedDict
from ctypes import Structure, c_uint32, c_char, c_void_p, sizeof, POINTER
from enum import IntEnum
from typing import Any


# Constants
MAX_DEVICE_IDENTIFIER_LENGTH = 256

MstDevice = c_void_p


def _build_context(context_type, port: str = "", **fields):
    """Build the C struct for an SDK context type, with its common fields filled in.

    Shared by every SDK context: size lets the SDK detect the ABI version the binding was built
    against, and an empty port => device default port. A context declaring fields beyond those
    two passes them as keyword arguments, which its type requires like any other field.
    """
    return context_type(size=sizeof(context_type.c_type), label_port=port, **fields).to_c()


# Every MstStruct subclass, in declaration order. The test suite iterates it, so a
# type cannot be added without being covered.
MST_STRUCT_TYPES = []


def _identity(value):
    return value


def _decode_utf8(value: bytes) -> str:
    return value.decode('utf-8')


def _encode_utf8(value: str) -> bytes:
    return value.encode('utf-8')


def _struct_to_c(value):
    return value.to_c()


def _converters(py_type) -> tuple:
    """The (decode, encode) pair a field converts through, from its Python type.

    An IntEnum converts through the enum class itself, so a value the enum does not
    define raises ValueError rather than reaching the caller as a bare int; a str
    converts through UTF-8, and a nested MstStruct through its own from_c/to_c.
    Anything else is already the Python value ctypes hands back.
    """
    if isinstance(py_type, type):
        if issubclass(py_type, IntEnum):
            return py_type, int
        if issubclass(py_type, MftSdkStruct):
            return py_type.from_c, _struct_to_c
        if py_type is str:
            return _decode_utf8, _encode_utf8
    return _identity, _identity


class _ScalarField():
    """One C field holding one value, converted by its _converters pair.

    Shares the field interface CountedArray implements: c_fields(), from_c(), to_c().
    """

    has_default = False

    def __init__(self, name: str, py_type, c_type):
        self.name = name
        self.py_type = py_type
        self.c_type = c_type
        self.decode, self.encode = _converters(py_type)

    def c_fields(self) -> list:
        return [(self.name, self.c_type)]

    def from_c(self, c_struct):
        return self.decode(getattr(c_struct, self.name))

    def to_c(self, c_struct, value):
        setattr(c_struct, self.name, self.encode(value))


class CountedArray():
    """A C pointer to an array, counted by the C field named by count, exposed as a
    list of the element type the field is annotated with.

    The only field kind that needs more than its ctypes type, because it spans two C
    fields. MstStruct publishes count as a read-only property over the list, so the
    count is never a second thing to keep in step.

    Elements are nested MftSdkStructs by default, converted through their own
    from_c()/to_c(). Pass element_c_type for a plain scalar array (e.g. List[int]),
    where there is no nested struct and the ctypes type itself is the conversion.
    """

    has_default = True

    def __init__(self, count: str, count_c_type=c_uint32, element_c_type=None):
        self.count = count
        self.count_c_type = count_c_type
        self.element_c_type = element_c_type

    def bind(self, name: str, py_type):
        self.name = name
        self.py_type = py_type
        self.element_type = py_type.__args__[0]

    def _element_c_type(self):
        return self.element_c_type if self.element_c_type is not None else self.element_type.c_type

    def c_fields(self) -> list:
        return [(self.count, self.count_c_type),
                (self.name, POINTER(self._element_c_type()))]

    def default(self) -> list:
        return []

    def from_c(self, c_struct) -> list:
        pointer = getattr(c_struct, self.name)
        if not pointer:
            return []
        indices = range(getattr(c_struct, self.count))
        if self.element_c_type is not None:
            return [pointer[index] for index in indices]
        return [self.element_type.from_c(pointer[index]) for index in indices]

    def to_c(self, c_struct, value):
        # Assigning the array to a pointer field records it in the structure's ctypes
        # _objects, so it stays alive as long as the structure C is reading does.
        # An empty list maps to a NULL pointer, matching the C convention that NULL
        # means "absent/default" rather than pointing to an empty array.
        setattr(c_struct, self.count, len(value))
        if not value:
            setattr(c_struct, self.name, None)
            return
        elements = value if self.element_c_type is not None else (element.to_c() for element in value)
        setattr(c_struct, self.name, (self._element_c_type() * len(value))(*elements))


def _bind_own_fields(cls) -> OrderedDict:
    """Bind the fields declared in cls's own body, in declaration order.

    Each is annotated with its Python type and assigned either the ctypes type
    holding it or a CountedArray.
    """
    annotations = getattr(cls, "__annotations__", None)
    if not isinstance(annotations, dict):
        annotations = {}
    fields = OrderedDict()
    for name, py_type in annotations.items():
        declared = cls.__dict__.get(name)
        if isinstance(declared, CountedArray):
            declared.bind(name, py_type)
            fields[name] = declared
        else:
            try:
                sizeof(declared)
            except TypeError:
                raise TypeError("{}.{} must be assigned its ctypes type or a CountedArray".format(
                    cls.__name__, name))
            fields[name] = _ScalarField(name, py_type, declared)
        delattr(cls, name)  # a declaration is layout metadata; callers must see values here
    return fields


def _generate_c_type(cls):
    """Build the ctypes structure mirroring cls's declaration.

    Fields inherited from a base class are laid out inline. Where the C header nests
    them in a struct member instead, the two layouts are equivalent as long as that
    member sits at offset 0 and its alignment does not exceed the outer structure's;
    the tests pin that equivalence.
    """
    c_fields = []
    for field in cls._fields.values():
        c_fields.extend(field.c_fields())
    return type("_" + cls.__name__, (Structure,), {"_fields_": c_fields})


def _count_property(list_field_name: str) -> property:
    return property(lambda self: len(getattr(self, list_field_name)))


class MftSdkStruct():
    """Base for the SDK's data types, declared once for both Python and C.

    A subclass annotates every field with its Python type and assigns the ctypes
    type holding it, or a CountedArray; the matching ctypes structure is generated
    as c_type, and __init__, __eq__ and __repr__ follow the same declaration. A
    subclass inherits its base's fields, ahead of its own.
    """

    def __init_subclass__(cls, **kwargs):
        super().__init_subclass__(**kwargs)
        cls._fields = OrderedDict()
        for base in cls.__bases__:
            cls._fields.update(getattr(base, "_fields", {}))
        own_fields = _bind_own_fields(cls)
        cls._fields.update(own_fields)
        cls.c_type = _generate_c_type(cls)
        for field in own_fields.values():
            if isinstance(field, CountedArray):
                setattr(cls, field.count, _count_property(field.name))
        MST_STRUCT_TYPES.append(cls)

    def __init__(self, *args, **kwargs):
        values = dict(zip(self._fields, args))
        values.update(kwargs)
        for name, field in self._fields.items():
            if name in values:
                setattr(self, name, values.pop(name))
            elif field.has_default:
                setattr(self, name, field.default())
            else:
                raise TypeError("{}() is missing argument {!r}".format(type(self).__name__, name))
        if values:
            raise TypeError("{}() got unexpected arguments: {}".format(
                type(self).__name__, ", ".join(sorted(values))))

    __hash__ = None  # mutable, like the C structures these mirror

    def __eq__(self, other):
        if type(other) is not type(self):
            return NotImplemented
        return all(getattr(self, name) == getattr(other, name) for name in self._fields)

    def __repr__(self):
        return "{}({})".format(type(self).__name__, ", ".join(
            "{}={!r}".format(name, getattr(self, name)) for name in self._fields))

    def as_dict(self) -> dict:
        """This object's fields as a dict, nested MstStructs included."""
        values = {}
        for name in self._fields:
            value = getattr(self, name)
            if isinstance(value, MftSdkStruct):
                value = value.as_dict()
            elif isinstance(value, list):
                value = [element.as_dict() if isinstance(element, MftSdkStruct) else element
                         for element in value]
            values[name] = value
        return values

    @classmethod
    def from_c(cls, c_struct) -> Any:
        """Build an instance from a filled ctypes structure of type c_type."""
        return cls(**{field.name: field.from_c(c_struct) for field in cls._fields.values()})

    def to_c(self):
        """Fill and return a new ctypes structure of type c_type."""
        c_struct = self.c_type()
        for field in self._fields.values():
            field.to_c(c_struct, getattr(self, field.name))
        return c_struct


class MstInterfaceType(IntEnum):
    """Interface types for MFT devices"""
    PCIe = 0
    Infiniband = 1
    MTUSB = 2
    NDC = 3
    I2C = 4
    Redfish = 5
    UnknownInterfaceType = 6


class MstPCIeSubInterfaceType(IntEnum):
    """PCIe sub-interface types"""
    FWCtl = 0
    VFIO = 1
    VsecMSTDriver = 2
    BAR0MSTDriver = 3
    VsecUserLevel = 4
    BAR0UserLevel = 5
    NvidiaDriver = 6
    UnknownPCIeSubInterfaceType = 7


class MstProductType(IntEnum):
    """Product types for MFT devices"""
    NIC = 0
    Switch = 1
    GPU = 2
    CPU = 3
    Retimer = 4
    UnknownProductType = 5


class MstDeviceType(IntEnum):
    """Device types for MFT devices"""
    ConnectX4 = 0
    ConnectX4LX = 1
    ConnectX5 = 2
    ConnectX6 = 3
    ConnectX6DX = 4
    ConnectX6LX = 5
    ConnectX7 = 6
    ConnectX8 = 7
    ConnectX8_Pure_PCIe_Switch = 8
    ConnectX9 = 9
    ConnectX9_Pure_PCIe_Switch = 10
    ConnectX10 = 11
    BlueField = 12
    BlueField2 = 13
    BlueField3 = 14
    BlueField4 = 15
    Spectrum = 16
    Spectrum2 = 17
    Spectrum3 = 18
    Spectrum4 = 19
    Spectrum5 = 20
    Spectrum6 = 21
    Spectrum7 = 22  # spc7_placeholder_need_to_verify - placeholder
    Quantum2 = 23
    Quantum3 = 24
    NVLink6_Switch = 25
    NVLink7_Switch = 26
    GB100 = 27
    GR100 = 28
    GR150 = 29
    GR150A01P = 30
    NR10 = 31
    FN100 = 32
    NVLink8_Switch = 33
    UnknownDeviceType = 34


class MstPcieSubInterfaceInfo(MftSdkStruct):
    """PCIe sub-interface information."""
    pcieSubInterfaceType: MstPCIeSubInterfaceType = c_uint32
    subInterfaceIdentifier: str = c_char * MAX_DEVICE_IDENTIFIER_LENGTH


class MstDeviceInfo(MftSdkStruct):
    """Device information."""
    productType: MstProductType = c_uint32
    deviceType: MstDeviceType = c_uint32
    interfaceType: MstInterfaceType = c_uint32
    deviceIdentifier: str = c_char * MAX_DEVICE_IDENTIFIER_LENGTH


class MstPciBDF(MftSdkStruct):
    """PCI bus-device-function address."""
    domain: int = c_uint32
    bus: int = c_uint32
    device: int = c_uint32
    function: int = c_uint32
