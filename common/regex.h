#ifndef MSTFLINT_REGEX_H
#define MSTFLINT_REGEX_H

#include "config.h"

#ifdef USE_BOOST_REGEX
#include <boost/regex.hpp>
#else
#include <regex>
#endif

namespace mstflint
{
namespace common
{
namespace regex
{
#ifdef USE_BOOST_REGEX
using boost::regex;
using boost::match_results;
using boost::regex_search;
using boost::smatch;
using boost::regex_replace;
using boost::regex_match;
#else
using std::regex;
using std::match_results;
using std::regex_search;
using std::smatch;
using std::regex_replace;
using std::regex_match;
#endif

} // namespace regex
} // namespace common
} // namespace mstflint
#endif // MSTFLINT_REGEX_H
