// Copyright 2007-2010 Baptiste Lepilleur
// Distributed under MIT license, or public domain if desired and
// recognized in your jurisdiction.
// See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#ifndef JSON_FORWARDS_H_INCLUDED
#define JSON_FORWARDS_H_INCLUDED

#include "config.h"

namespace Json
{
// writer.h
class FastWriter;
class StyledWriter;

// reader.h
class Reader;

// features.h
class Features;

// value.h
typedef int Int;
typedef unsigned int UInt;
class StaticString;
class Path;
class PathArgument;
class Value;
class ValueIteratorBase;
class ValueIterator;
class ValueConstIterator;
#ifdef JSON_VALUE_USE_INTERNAL_MAP
class ValueAllocator;
class ValueMapAllocator;
class ValueInternalLink;
class ValueInternalArray;
class ValueInternalMap;
#endif // #ifdef JSON_VALUE_USE_INTERNAL_MAP

} // namespace Json

#endif // JSON_FORWARDS_H_INCLUDED
