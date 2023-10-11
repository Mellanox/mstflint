#ifndef MSTFLINT_STRING_H
#define MSTFLINT_STRING_H

#include <boost/algorithm/string.hpp>

namespace mstflint
{
namespace common
{
namespace algorithm
{

using boost::algorithm::join;
using boost::algorithm::replace_all_copy;
using boost::algorithm::split;
using boost::algorithm::to_lower;
using boost::algorithm::to_lower_copy;
using boost::algorithm::trim;
using boost::is_any_of;

}
} // namespace common
} // namespace mstflint

#endif // MSTFLINT_STRING_H
