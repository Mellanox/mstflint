
#include "tools_json.h"

namespace mstflint
{
namespace common
{
// Implementation of class ReaderWrapper
// ////////////////////////////////
ReaderWrapper::ReaderWrapper()
{
    reader = new Json::Reader{};
}
ReaderWrapper::~ReaderWrapper()
{
    delete reader;
}
Json::Reader* ReaderWrapper::getReader()
{
    return reader;
}
// Implementation of class ReaderWrapper
// ////////////////////////////////
} // namespace common
} // namespace mstflint
