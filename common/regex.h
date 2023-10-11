#ifndef MSTFLINT_REGEX_H
#define MSTFLINT_REGEX_H

#include <boost/regex.hpp>

namespace mstflint
{
namespace common
{
namespace regex
{
using boost::regex;
using boost::match_results;
using boost::regex_search;
using boost::smatch;
using boost::regex_replace;
using boost::regex_match;

} // namespace regex
} // namespace common
} // namespace mstflint
#endif // MSTFLINT_REGEX_H
