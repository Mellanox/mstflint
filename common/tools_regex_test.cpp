/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "tools_regex.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace Regex = mstflint::common::regex;

TEST(regex, PatternError) {
  EXPECT_THROW(Regex::regex("(missing closing bracket"), Regex::regex_error);
  EXPECT_THROW(Regex::regex("[missing closing bracket"), Regex::regex_error);
  // something that boost detects, while stdlib regex not
#if defined USE_BOOST_REGEX
  EXPECT_THROW(Regex::regex("|) messed alternation"), Regex::regex_error);
  EXPECT_THROW(Regex::regex("(| messed alternation"), Regex::regex_error);
#elif defined USE_STDLIB_REGEX
#else
#endif
  EXPECT_THROW(Regex::regex("(| messed alternation"), Regex::regex_error);
  EXPECT_THROW(Regex::regex("a{2,1} invalid quantifier range"),
               Regex::regex_error);
  EXPECT_THROW(Regex::regex("?+* invalid quantifier order"),
               Regex::regex_error);
}

#define PATTERN_XENOPHILE "^([^\\$]*)(\\$\\(([^)]+)\\))(.*)$"

TEST(match_result, PatternXenophile1) {
  Regex::regex pattern(PATTERN_XENOPHILE);
  Regex::match_results<std::string::const_iterator> match;
  std::string input = "Hello $(123) World";
  EXPECT_TRUE(Regex::regex_match(input, match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(match.str(), "Hello $(123) World");
  EXPECT_EQ(match.suffix().first, input.end());
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 5);

  // operator==(const std::string&, sub_match)
  EXPECT_TRUE("Hello $(123) World" == match[0]);
  // operator sub_match::std::string()
  EXPECT_EQ(static_cast<std::string>(match[0]), "Hello $(123) World");
  EXPECT_EQ(match[0].str(), "Hello $(123) World");

  EXPECT_TRUE("Hello " == match[1]);
  EXPECT_EQ(match[1].str(), "Hello ");
  EXPECT_EQ(static_cast<std::string>(match[1]), "Hello ");

  EXPECT_TRUE("$(123)" == match[2]);
  EXPECT_EQ(match[2].str(), "$(123)");
  EXPECT_EQ(static_cast<std::string>(match[2]), "$(123)");

  EXPECT_TRUE("123" == match[3]);
  EXPECT_EQ(match[3].str(), "123");
  EXPECT_EQ(static_cast<std::string>(match[3]), "123");

  EXPECT_TRUE(" World" == match[4]);
  EXPECT_EQ(match[4].str(), " World");
  EXPECT_EQ(static_cast<std::string>(match[4]), " World");
}

TEST(match_result, PatternXenophile2) {
  Regex::regex pattern(PATTERN_XENOPHILE);
  Regex::match_results<std::string::const_iterator> match;
  std::string input = "Start$(123)Middle$(456)End";
  EXPECT_TRUE(Regex::regex_match(input, match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(match.str(), "Start$(123)Middle$(456)End");
  EXPECT_EQ(match.suffix().first, input.end());
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 5);
  EXPECT_TRUE("Start$(123)Middle$(456)End" == match[0]);
  EXPECT_EQ(match[0].str(), "Start$(123)Middle$(456)End");
  EXPECT_EQ(static_cast<std::string>(match[0]), "Start$(123)Middle$(456)End");
  EXPECT_TRUE("Start" == match[1]);
  EXPECT_EQ(match[1].str(), "Start");
  EXPECT_EQ(static_cast<std::string>(match[1]), "Start");
  EXPECT_TRUE("$(123)" == match[2]);
  EXPECT_EQ(match[2].str(), "$(123)");
  EXPECT_EQ(static_cast<std::string>(match[2]), "$(123)");
  EXPECT_TRUE("123" == match[3]);
  EXPECT_EQ(match[3].str(), "123");
  EXPECT_EQ(static_cast<std::string>(match[3]), "123");
  EXPECT_TRUE("Middle$(456)End" == match[4]);
  EXPECT_EQ(match[4].str(), "Middle$(456)End");
  EXPECT_EQ(static_cast<std::string>(match[4]), "Middle$(456)End");
}

TEST(match_result, PatternXenophile3) {
  Regex::regex pattern(PATTERN_XENOPHILE);
  Regex::match_results<std::string::const_iterator> match;
  std::string input = "$(1)$(2)$(3)";
  EXPECT_TRUE(Regex::regex_match(input, match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(match.str(), "$(1)$(2)$(3)");
  EXPECT_EQ(match.suffix().first, input.end());
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 5);
  EXPECT_TRUE("$(1)$(2)$(3)" == match[0]);
  EXPECT_EQ(match[0].str(), "$(1)$(2)$(3)");
  EXPECT_EQ(static_cast<std::string>(match[0]), "$(1)$(2)$(3)");
  EXPECT_TRUE("" == match[1]);
  EXPECT_EQ(match[1].str(), "");
  EXPECT_EQ(static_cast<std::string>(match[1]), "");
  EXPECT_TRUE("$(1)" == match[2]);
  EXPECT_EQ(match[2].str(), "$(1)");
  EXPECT_EQ(static_cast<std::string>(match[2]), "$(1)");
  EXPECT_TRUE("1" == match[3]);
  EXPECT_EQ(match[3].str(), "1");
  EXPECT_EQ(static_cast<std::string>(match[3]), "1");
  EXPECT_TRUE("$(2)$(3)" == match[4]);
  EXPECT_EQ(match[4].str(), "$(2)$(3)");
  EXPECT_EQ(static_cast<std::string>(match[4]), "$(2)$(3)");
}

TEST(match_result, PatternXenophile4) {
  Regex::regex pattern(PATTERN_XENOPHILE);
  Regex::match_results<std::string::const_iterator> match;
  std::string input = "This should not match.";
  EXPECT_FALSE(Regex::regex_match(input, match, pattern));
}
#undef PATTERN_XENOPHILE

TEST(match_result, RangeLoop) {
  Regex::regex pattern("(A)(B)(C)(D)(E)(F)(G)(H)(I)(J)(K)(L)(M)(N)(O)");
  Regex::match_results<std::string::const_iterator> match;
  std::string input = "ABCDEFGHIJKLMNO";
  EXPECT_TRUE(Regex::regex_match(input, match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(match.str(), "ABCDEFGHIJKLMNO");
  EXPECT_EQ(match.suffix().first, input.end());
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 16);
  std::string actual;
  for (auto e : match) {
    actual.append(e);
  }
  EXPECT_EQ(actual, "ABCDEFGHIJKLMNOABCDEFGHIJKLMNO");
}

TEST(regex_match, NegativePartialMatch) {
  Regex::regex pattern("partial");
  std::string input = "String with partial match";
  EXPECT_FALSE(Regex::regex_match(input, pattern));
}

TEST(regex_match, NegativePartialMatchWithResult) {
  Regex::regex pattern("partial");
  Regex::match_results<std::string::const_iterator> match;
  std::string input = "String with partial match";
  EXPECT_FALSE(Regex::regex_match(input, match, pattern));
}

TEST(regex_match, TagAttrDefinePattern) {
  Regex::regex pattern("([A-Za-z_]\\w*)=(\\w+)");
  EXPECT_TRUE(Regex::regex_match("NaMe1235=VaLuE456", pattern));
  EXPECT_TRUE(Regex::regex_match("my_var=42", pattern));
  EXPECT_TRUE(Regex::regex_match("_variable_name=hello", pattern));
  EXPECT_TRUE(Regex::regex_match("someValue=9876", pattern));
  EXPECT_TRUE(Regex::regex_match("camelCaseVar=abcdef", pattern));
  EXPECT_TRUE(Regex::regex_match("another_variable=xyz123", pattern));
  EXPECT_TRUE(Regex::regex_match("Name=Value", pattern));
  EXPECT_TRUE(Regex::regex_match("_underscore_name=12345", pattern));
  EXPECT_TRUE(Regex::regex_match("someWord=hello_world", pattern));
  EXPECT_TRUE(Regex::regex_match("Var_123=abc_def", pattern));
  EXPECT_FALSE(Regex::regex_match("=value", pattern));
  EXPECT_FALSE(Regex::regex_match("variable_name=", pattern));
  EXPECT_FALSE(Regex::regex_match("@=123", pattern));
  EXPECT_FALSE(Regex::regex_match("=Value", pattern));
  EXPECT_FALSE(Regex::regex_match("Var_123 =", pattern));
}

TEST(regex_match, EnumPattern) {
  Regex::regex pattern("(\\s*\\w+\\s*=\\s*(0x)?[0-9a-fA-F]+\\s*(,)?)+");
  EXPECT_TRUE(Regex::regex_match("name=0x1A,age=0x10", pattern));
  EXPECT_TRUE(
      Regex::regex_match("color=0xFF,quantity=0x2,price=0x7A", pattern));
  EXPECT_TRUE(Regex::regex_match("ID = 0xA5, Score = 0x7D", pattern));
  EXPECT_TRUE(Regex::regex_match("key1=0x1,key2=0x2,key3=0x3", pattern));
  EXPECT_TRUE(Regex::regex_match("item=0x4,item2=0x5", pattern));
  EXPECT_TRUE(Regex::regex_match("name=0xA5,age=7D", pattern));
  EXPECT_TRUE(Regex::regex_match("color=0xFF,quantity=2,price=0x7A", pattern));
  EXPECT_TRUE(Regex::regex_match("name=0x1A,age=0x10,", pattern));
  EXPECT_TRUE(Regex::regex_match("name=0x1A,age=0x10,color=FF", pattern));
  EXPECT_TRUE(Regex::regex_match("123=0x1A,age=0x10", pattern));
  EXPECT_FALSE(Regex::regex_match("=0xA5, =0x7D", pattern));
  EXPECT_FALSE(Regex::regex_match("name==0x1A,age=0x10", pattern));
  EXPECT_FALSE(Regex::regex_match("name=0x1A;age=0x10", pattern));
  EXPECT_FALSE(Regex::regex_match("=0x1A,age=0x10", pattern));
  EXPECT_FALSE(Regex::regex_match("name=,age=0x10", pattern));
  EXPECT_FALSE(Regex::regex_match("name=0x1A,=0x10", pattern));
  EXPECT_FALSE(Regex::regex_match("name 0x1A,age=0x10", pattern));
  EXPECT_FALSE(Regex::regex_match("name=0x1A,age=0x1.0", pattern));
}

TEST(regex_match, VersionPattern) {
  Regex::regex pattern("^[0-9].[0-9].[0-9]$");
  EXPECT_TRUE(Regex::regex_match("1.2.3", pattern));
  EXPECT_TRUE(Regex::regex_match("9.0.5", pattern));
  EXPECT_TRUE(Regex::regex_match("0.0.0", pattern));
  EXPECT_TRUE(Regex::regex_match("7.8.9", pattern));
  EXPECT_FALSE(Regex::regex_match(" 1.2.3", pattern));
  EXPECT_FALSE(Regex::regex_match("12.34.56", pattern));
  EXPECT_FALSE(Regex::regex_match("1.2.3.", pattern));
  EXPECT_FALSE(Regex::regex_match("1.a.3", pattern));
  EXPECT_FALSE(Regex::regex_match("1..3", pattern));
  EXPECT_FALSE(Regex::regex_match("1.2", pattern));
}

TEST(regex_match, SubExpressions) {
  Regex::regex pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)");
  Regex::smatch match;
  std::string input = "abcdefghijklmno";
  EXPECT_TRUE(Regex::regex_match(input, match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(match.str(), "abcdefghijklmno");
  EXPECT_EQ(match.suffix().first, input.end());
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 16);
  EXPECT_EQ(static_cast<std::string>(match[0]), "abcdefghijklmno");
  EXPECT_EQ(static_cast<std::string>(match[1]), "a");
  EXPECT_EQ(static_cast<std::string>(match[2]), "b");
  EXPECT_EQ(static_cast<std::string>(match[3]), "c");
  EXPECT_EQ(static_cast<std::string>(match[4]), "d");
  EXPECT_EQ(static_cast<std::string>(match[5]), "e");
  EXPECT_EQ(static_cast<std::string>(match[6]), "f");
  EXPECT_EQ(static_cast<std::string>(match[7]), "g");
  EXPECT_EQ(static_cast<std::string>(match[8]), "h");
  EXPECT_EQ(static_cast<std::string>(match[9]), "i");
  EXPECT_EQ(static_cast<std::string>(match[10]), "j");
  EXPECT_EQ(static_cast<std::string>(match[11]), "k");
  EXPECT_EQ(static_cast<std::string>(match[12]), "l");
  EXPECT_EQ(static_cast<std::string>(match[13]), "m");
  EXPECT_EQ(static_cast<std::string>(match[14]), "n");
  EXPECT_EQ(static_cast<std::string>(match[15]), "o");
}

#if defined USE_STDLIB_REGEX
// stdlib based implementation constrains max number of subexpressions
TEST(regex_match, MaxSubExpressions) {
  Regex::regex pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)(p)");
  Regex::smatch match;
  std::string input = "abcdefghijklmnop";
  EXPECT_THROW(Regex::regex_match(input, match, pattern), Regex::regex_error);
}
#endif

TEST(regex_search, SubExpressionsStringNoPrefixSuffix) {
  Regex::regex pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)");
  Regex::smatch match;
  std::string input = "abcdefghijklmno";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(match.str(), "abcdefghijklmno");
  EXPECT_EQ(match.suffix().first, input.end());
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 16);
  EXPECT_EQ(static_cast<std::string>(match[0]), "abcdefghijklmno");
  EXPECT_EQ(static_cast<std::string>(match[1]), "a");
  EXPECT_EQ(static_cast<std::string>(match[2]), "b");
  EXPECT_EQ(static_cast<std::string>(match[3]), "c");
  EXPECT_EQ(static_cast<std::string>(match[4]), "d");
  EXPECT_EQ(static_cast<std::string>(match[5]), "e");
  EXPECT_EQ(static_cast<std::string>(match[6]), "f");
  EXPECT_EQ(static_cast<std::string>(match[7]), "g");
  EXPECT_EQ(static_cast<std::string>(match[8]), "h");
  EXPECT_EQ(static_cast<std::string>(match[9]), "i");
  EXPECT_EQ(static_cast<std::string>(match[10]), "j");
  EXPECT_EQ(static_cast<std::string>(match[11]), "k");
  EXPECT_EQ(static_cast<std::string>(match[12]), "l");
  EXPECT_EQ(static_cast<std::string>(match[13]), "m");
  EXPECT_EQ(static_cast<std::string>(match[14]), "n");
  EXPECT_EQ(static_cast<std::string>(match[15]), "o");
}

TEST(regex_search, SubExpressionsStringNoSuffix) {
  Regex::regex pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)");
  Regex::smatch match;
  std::string input = "PREFIXabcdefghijklmno";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(static_cast<std::string>(match.prefix()), "PREFIX");
  EXPECT_EQ(match.str(), "abcdefghijklmno");
  EXPECT_EQ(match.suffix().first, input.end());
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 16);
  EXPECT_EQ(static_cast<std::string>(match[0]), "abcdefghijklmno");
  EXPECT_EQ(static_cast<std::string>(match[1]), "a");
  EXPECT_EQ(static_cast<std::string>(match[2]), "b");
  EXPECT_EQ(static_cast<std::string>(match[3]), "c");
  EXPECT_EQ(static_cast<std::string>(match[4]), "d");
  EXPECT_EQ(static_cast<std::string>(match[5]), "e");
  EXPECT_EQ(static_cast<std::string>(match[6]), "f");
  EXPECT_EQ(static_cast<std::string>(match[7]), "g");
  EXPECT_EQ(static_cast<std::string>(match[8]), "h");
  EXPECT_EQ(static_cast<std::string>(match[9]), "i");
  EXPECT_EQ(static_cast<std::string>(match[10]), "j");
  EXPECT_EQ(static_cast<std::string>(match[11]), "k");
  EXPECT_EQ(static_cast<std::string>(match[12]), "l");
  EXPECT_EQ(static_cast<std::string>(match[13]), "m");
  EXPECT_EQ(static_cast<std::string>(match[14]), "n");
  EXPECT_EQ(static_cast<std::string>(match[15]), "o");
}

TEST(regex_search, SubExpressionsStringNoPrefix) {
  Regex::regex pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)");
  Regex::smatch match;
  std::string input = "abcdefghijklmnoSUFFIX";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(match.str(), "abcdefghijklmno");
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_EQ(static_cast<std::string>(match.suffix()), "SUFFIX");
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 16);
  EXPECT_EQ(static_cast<std::string>(match[0]), "abcdefghijklmno");
  EXPECT_EQ(static_cast<std::string>(match[1]), "a");
  EXPECT_EQ(static_cast<std::string>(match[2]), "b");
  EXPECT_EQ(static_cast<std::string>(match[3]), "c");
  EXPECT_EQ(static_cast<std::string>(match[4]), "d");
  EXPECT_EQ(static_cast<std::string>(match[5]), "e");
  EXPECT_EQ(static_cast<std::string>(match[6]), "f");
  EXPECT_EQ(static_cast<std::string>(match[7]), "g");
  EXPECT_EQ(static_cast<std::string>(match[8]), "h");
  EXPECT_EQ(static_cast<std::string>(match[9]), "i");
  EXPECT_EQ(static_cast<std::string>(match[10]), "j");
  EXPECT_EQ(static_cast<std::string>(match[11]), "k");
  EXPECT_EQ(static_cast<std::string>(match[12]), "l");
  EXPECT_EQ(static_cast<std::string>(match[13]), "m");
  EXPECT_EQ(static_cast<std::string>(match[14]), "n");
  EXPECT_EQ(static_cast<std::string>(match[15]), "o");
}

TEST(regex_search, SubExpressionsString) {
  Regex::regex pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)");
  Regex::smatch match;
  std::string input = "PREFIXabcdefghijklmnoSUFFIX";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(static_cast<std::string>(match.prefix()), "PREFIX");
  EXPECT_EQ(match.str(), "abcdefghijklmno");
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_EQ(static_cast<std::string>(match.suffix()), "SUFFIX");
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 16);
  EXPECT_EQ(static_cast<std::string>(match[0]), "abcdefghijklmno");
  EXPECT_EQ(static_cast<std::string>(match[1]), "a");
  EXPECT_EQ(static_cast<std::string>(match[2]), "b");
  EXPECT_EQ(static_cast<std::string>(match[3]), "c");
  EXPECT_EQ(static_cast<std::string>(match[4]), "d");
  EXPECT_EQ(static_cast<std::string>(match[5]), "e");
  EXPECT_EQ(static_cast<std::string>(match[6]), "f");
  EXPECT_EQ(static_cast<std::string>(match[7]), "g");
  EXPECT_EQ(static_cast<std::string>(match[8]), "h");
  EXPECT_EQ(static_cast<std::string>(match[9]), "i");
  EXPECT_EQ(static_cast<std::string>(match[10]), "j");
  EXPECT_EQ(static_cast<std::string>(match[11]), "k");
  EXPECT_EQ(static_cast<std::string>(match[12]), "l");
  EXPECT_EQ(static_cast<std::string>(match[13]), "m");
  EXPECT_EQ(static_cast<std::string>(match[14]), "n");
  EXPECT_EQ(static_cast<std::string>(match[15]), "o");
}

TEST(regex_search, SubExpressionsRangeNoPrefixSuffix) {
  Regex::regex pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)");
  Regex::smatch match;
  std::string input = "abcdefghijklmno";
  EXPECT_TRUE(
      Regex::regex_search(input.cbegin(), input.cend(), match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(match.str(), "abcdefghijklmno");
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().first, input.end());
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 16);
  EXPECT_EQ(static_cast<std::string>(match[0]), "abcdefghijklmno");
  EXPECT_EQ(static_cast<std::string>(match[1]), "a");
  EXPECT_EQ(static_cast<std::string>(match[2]), "b");
  EXPECT_EQ(static_cast<std::string>(match[3]), "c");
  EXPECT_EQ(static_cast<std::string>(match[4]), "d");
  EXPECT_EQ(static_cast<std::string>(match[5]), "e");
  EXPECT_EQ(static_cast<std::string>(match[6]), "f");
  EXPECT_EQ(static_cast<std::string>(match[7]), "g");
  EXPECT_EQ(static_cast<std::string>(match[8]), "h");
  EXPECT_EQ(static_cast<std::string>(match[9]), "i");
  EXPECT_EQ(static_cast<std::string>(match[10]), "j");
  EXPECT_EQ(static_cast<std::string>(match[11]), "k");
  EXPECT_EQ(static_cast<std::string>(match[12]), "l");
  EXPECT_EQ(static_cast<std::string>(match[13]), "m");
  EXPECT_EQ(static_cast<std::string>(match[14]), "n");
  EXPECT_EQ(static_cast<std::string>(match[15]), "o");
}

TEST(regex_search, SubExpressionsRangeNoPrefix) {
  Regex::regex pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)");
  Regex::smatch match;
  std::string input = "abcdefghijklmnoSUFFIX";
  EXPECT_TRUE(
      Regex::regex_search(input.cbegin(), input.cend(), match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(match.str(), "abcdefghijklmno");
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_EQ(static_cast<std::string>(match.suffix()), "SUFFIX");
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 16);
  EXPECT_EQ(static_cast<std::string>(match[0]), "abcdefghijklmno");
  EXPECT_EQ(static_cast<std::string>(match[1]), "a");
  EXPECT_EQ(static_cast<std::string>(match[2]), "b");
  EXPECT_EQ(static_cast<std::string>(match[3]), "c");
  EXPECT_EQ(static_cast<std::string>(match[4]), "d");
  EXPECT_EQ(static_cast<std::string>(match[5]), "e");
  EXPECT_EQ(static_cast<std::string>(match[6]), "f");
  EXPECT_EQ(static_cast<std::string>(match[7]), "g");
  EXPECT_EQ(static_cast<std::string>(match[8]), "h");
  EXPECT_EQ(static_cast<std::string>(match[9]), "i");
  EXPECT_EQ(static_cast<std::string>(match[10]), "j");
  EXPECT_EQ(static_cast<std::string>(match[11]), "k");
  EXPECT_EQ(static_cast<std::string>(match[12]), "l");
  EXPECT_EQ(static_cast<std::string>(match[13]), "m");
  EXPECT_EQ(static_cast<std::string>(match[14]), "n");
  EXPECT_EQ(static_cast<std::string>(match[15]), "o");
}

TEST(regex_search, SubExpressionsRangeNoSuffix) {
  Regex::regex pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)");
  Regex::smatch match;
  std::string input = "PREFIXabcdefghijklmno";
  EXPECT_TRUE(
      Regex::regex_search(input.cbegin(), input.cend(), match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(static_cast<std::string>(match.prefix()), "PREFIX");
  EXPECT_EQ(match.str(), "abcdefghijklmno");
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().first, input.end());
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 16);
  EXPECT_EQ(static_cast<std::string>(match[0]), "abcdefghijklmno");
  EXPECT_EQ(static_cast<std::string>(match[1]), "a");
  EXPECT_EQ(static_cast<std::string>(match[2]), "b");
  EXPECT_EQ(static_cast<std::string>(match[3]), "c");
  EXPECT_EQ(static_cast<std::string>(match[4]), "d");
  EXPECT_EQ(static_cast<std::string>(match[5]), "e");
  EXPECT_EQ(static_cast<std::string>(match[6]), "f");
  EXPECT_EQ(static_cast<std::string>(match[7]), "g");
  EXPECT_EQ(static_cast<std::string>(match[8]), "h");
  EXPECT_EQ(static_cast<std::string>(match[9]), "i");
  EXPECT_EQ(static_cast<std::string>(match[10]), "j");
  EXPECT_EQ(static_cast<std::string>(match[11]), "k");
  EXPECT_EQ(static_cast<std::string>(match[12]), "l");
  EXPECT_EQ(static_cast<std::string>(match[13]), "m");
  EXPECT_EQ(static_cast<std::string>(match[14]), "n");
  EXPECT_EQ(static_cast<std::string>(match[15]), "o");
}

TEST(regex_search, SubExpressionsRange) {
  Regex::regex pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)");
  Regex::smatch match;
  std::string input = "PREFIXabcdefghijklmnoSUFFIX";
  EXPECT_TRUE(
      Regex::regex_search(input.cbegin(), input.cend(), match, pattern));
  EXPECT_EQ(match.prefix().first, input.begin());
  EXPECT_EQ(match.prefix().second, match[0].first);
  EXPECT_EQ(static_cast<std::string>(match.prefix()), "PREFIX");
  EXPECT_EQ(match.str(), "abcdefghijklmno");
  EXPECT_EQ(match.suffix().first, match[0].second);
  EXPECT_EQ(match.suffix().second, input.end());
  EXPECT_EQ(static_cast<std::string>(match.suffix()), "SUFFIX");
  EXPECT_FALSE(match.empty());
  EXPECT_EQ(match.size(), 16);
  EXPECT_EQ(static_cast<std::string>(match[0]), "abcdefghijklmno");
  EXPECT_EQ(static_cast<std::string>(match[1]), "a");
  EXPECT_EQ(static_cast<std::string>(match[2]), "b");
  EXPECT_EQ(static_cast<std::string>(match[3]), "c");
  EXPECT_EQ(static_cast<std::string>(match[4]), "d");
  EXPECT_EQ(static_cast<std::string>(match[5]), "e");
  EXPECT_EQ(static_cast<std::string>(match[6]), "f");
  EXPECT_EQ(static_cast<std::string>(match[7]), "g");
  EXPECT_EQ(static_cast<std::string>(match[8]), "h");
  EXPECT_EQ(static_cast<std::string>(match[9]), "i");
  EXPECT_EQ(static_cast<std::string>(match[10]), "j");
  EXPECT_EQ(static_cast<std::string>(match[11]), "k");
  EXPECT_EQ(static_cast<std::string>(match[12]), "l");
  EXPECT_EQ(static_cast<std::string>(match[13]), "m");
  EXPECT_EQ(static_cast<std::string>(match[14]), "n");
  EXPECT_EQ(static_cast<std::string>(match[15]), "o");
}

#define PATTERN_PEREGRINATE "(_[0-9]{2}_[0-9]+)"

TEST(regex_search, PatternPeregrinate1) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "Beginning_012_1234567890_End";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternPeregrinate2) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "x12_345";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternPeregrinate3) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "__23";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternPeregrinate4) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "_AB_CD";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternPeregrinate5) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "_AB_12";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternPeregrinate6) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "_1_23";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternPeregrinate7) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "_12_AB";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternPeregrinate8) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "_123_45";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternPeregrinate9) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "Start_x12_345_End";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternPeregrinate10) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "123_01_1234567890_456";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_01_1234567890");
}

TEST(regex_search, PatternPeregrinate11) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "_99_1";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_99_1");
}

TEST(regex_search, PatternPeregrinate12) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "_42_987";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_42_987");
}

TEST(regex_search, PatternPeregrinate13) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "_12_345";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_12_345");
}

TEST(regex_search, PatternPeregrinate14) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "_01_1234567890";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_01_1234567890");
}

TEST(regex_search, PatternPeregrinate15) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "_00_98765";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_00_98765");
}

TEST(regex_search, PatternPeregrinate16) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "Text_ABC_12_345_SomeText";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_12_345");
}

TEST(regex_search, PatternPeregrinate17) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "Start_00_98765_End";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_00_98765");
}

TEST(regex_search, PatternPeregrinate18) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "Prefix_12_345_Suffix";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_12_345");
}

TEST(regex_search, PatternPeregrinate19) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "Pre_99_1_Post";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_99_1");
}

TEST(regex_search, PatternPeregrinate20) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "Beginning_01_1234567890_End";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_01_1234567890");
}

TEST(regex_search, PatternPeregrinate21) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "Before_42_987_After";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_42_987");
}

TEST(regex_search, PatternPeregrinate22) {
  Regex::regex pattern(PATTERN_PEREGRINATE);
  Regex::smatch match;
  std::string input = "_01_1234567890";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "_01_1234567890");
}

#undef PATTERN_PEREGRINATE

#define PATTERN_SELENOPHILE "\\s*([a-zA-Z0-9_]+)=((\\$\\(.*?\\)|\\S+|$)*)\\s*"

TEST(regex_search, PatternSelenophile1) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "name=John";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "name=John");
  EXPECT_EQ(std::string(match[1]), "name");
  EXPECT_EQ(std::string(match[2]), "John");
}

TEST(regex_search, PatternSelenophile2) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "age=25";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "age=25");
  EXPECT_EQ(std::string(match[1]), "age");
  EXPECT_EQ(std::string(match[2]), "25");
}

TEST(regex_search, PatternSelenophile3) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "city=$(New York)";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "city=$(New York)");
  EXPECT_EQ(std::string(match[1]), "city");
  EXPECT_EQ(std::string(match[2]), "$(New York)");
}

TEST(regex_search, PatternSelenophile4) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "gender=Male";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "gender=Male");
  EXPECT_EQ(std::string(match[1]), "gender");
  EXPECT_EQ(std::string(match[2]), "Male");
}

TEST(regex_search, PatternSelenophile5) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "employee=$(John Doe, Engineer)";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "employee=$(John Doe, Engineer)");
  EXPECT_EQ(std::string(match[1]), "employee");
  EXPECT_EQ(std::string(match[2]), "$(John Doe, Engineer)");
}

TEST(regex_search, PatternSelenophile6) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "state=CA";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "state=CA");
  EXPECT_EQ(std::string(match[1]), "state");
  EXPECT_EQ(std::string(match[2]), "CA");
}

TEST(regex_search, PatternSelenophile7) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "key1 = value1";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternSelenophile8) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "code=$(12345,ABC)";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "code=$(12345,ABC)");
  EXPECT_EQ(std::string(match[1]), "code");
  EXPECT_EQ(std::string(match[2]), "$(12345,ABC)");
}

TEST(regex_search, PatternSelenophile9) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "=John";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternSelenophile10) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "=25";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternSelenophile11) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "$(New York";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternSelenophile12) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "city=";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
  EXPECT_EQ(match.str(), "city=");
  EXPECT_EQ(std::string(match[1]), "city");
  EXPECT_EQ(std::string(match[2]), "");
}

TEST(regex_search, PatternSelenophile13) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "=";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternSelenophile14) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "=()";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternSelenophile15) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = "= =";
  EXPECT_FALSE(Regex::regex_search(input, match, pattern));
}

TEST(regex_search, PatternSelenophile16) {
  Regex::regex pattern(PATTERN_SELENOPHILE);
  Regex::smatch match;
  std::string input = R"(
<field name="access_reg_summary_selector_ext" offset="0x0.0" size="0x26e0.0" subnode="access_reg_summary_selector_ext" descr="" />
)";

  auto start = input.cbegin();
  auto end = input.cend();

  EXPECT_TRUE(Regex::regex_search(start, end, match, pattern));
  EXPECT_EQ(std::string(match[1].first, match[1].second), "name");
  EXPECT_EQ(std::string(match[2].first, match[2].second),
            R"("access_reg_summary_selector_ext")");
  start = match[0].second;

  EXPECT_TRUE(Regex::regex_search(start, end, match, pattern));
  EXPECT_EQ(std::string(match[1].first, match[1].second), "offset");
  EXPECT_EQ(std::string(match[2].first, match[2].second), R"("0x0.0")");
  start = match[0].second;

  EXPECT_TRUE(Regex::regex_search(start, end, match, pattern));
  EXPECT_EQ(std::string(match[1].first, match[1].second), "size");
  EXPECT_EQ(std::string(match[2].first, match[2].second), R"("0x26e0.0")");
  start = match[0].second;

  EXPECT_TRUE(Regex::regex_search(start, end, match, pattern));
  EXPECT_EQ(std::string(match[1].first, match[1].second), "subnode");
  EXPECT_EQ(std::string(match[2].first, match[2].second),
            R"("access_reg_summary_selector_ext")");
  start = match[0].second;

  EXPECT_TRUE(Regex::regex_search(start, end, match, pattern));
  EXPECT_EQ(std::string(match[1].first, match[1].second), "descr");
  EXPECT_EQ(std::string(match[2].first, match[2].second), R"("")");
  start = match[0].second;

  EXPECT_FALSE(Regex::regex_search(start, end, match, pattern));
}

TEST(regex_search, EmptyInput) {
  Regex::regex pattern(".*");
  Regex::smatch match;
  std::string input = "";
  EXPECT_TRUE(Regex::regex_search(input, match, pattern));
}

TEST(regex_replace, Trivia) {
  Regex::regex pattern("\\s+");
  std::string input = " \ttext \t with\t white  spaces\t \t ";
  std::string format = "__WHITESPACE__";
  std::string output = Regex::regex_replace(input, pattern, format);
  EXPECT_EQ(output, "__WHITESPACE__text__WHITESPACE__with__WHITESPACE__white__"
                    "WHITESPACE__spaces__WHITESPACE__");
}

TEST(regex_replace, EmptyFormat) {
  Regex::regex pattern("\\s+");
  std::string input = " \t \tsecaps  etihw \thtiw \t txet\t ";
  std::string format = "";
  std::string output = Regex::regex_replace(input, pattern, format);
  EXPECT_EQ(output, "secapsetihwhtiwtxet");
}

TEST(regex_replace, EmptyInput) {
  Regex::regex pattern("\\s+");
  std::string input = "";
  std::string format = "replace string";
  std::string output = Regex::regex_replace(input, pattern, format);
  EXPECT_TRUE(output.empty());
}

TEST(regex_replace, EraseSentence) {
  Regex::regex pattern("[ a-zA-Z,.]");
  std::string input =
      R"(As the sun set behind the mountains, a gentle breeze rustled the leaves of the ancient oak tree, creating a peaceful atmosphere in the quiet village.)";
  std::string format = "";
  std::string output = Regex::regex_replace(input, pattern, format);
  EXPECT_TRUE(output.empty());
}

TEST(regex_replace, EraseSentenceAtOnce) {
  Regex::regex pattern(".*");
  std::string input =
      R"(The curious cat chased a fluttering butterfly through the lush green garden.)";
  std::string format = "";
  std::string output = Regex::regex_replace(input, pattern, format);
  EXPECT_TRUE(output.empty());
}

TEST(sregex_iterator, Increment)
{
    Regex::regex pattern("Do[a-zA-Z]*");
    std::string input = "Do you have a Dog named Donnie?";

    Regex::sregex_iterator it_end;
    Regex::sregex_iterator it(input.begin(), input.end(), pattern);
    EXPECT_EQ(it->str(), "Do");
    EXPECT_EQ((++it)->str(), "Dog");
    EXPECT_EQ((++it)->str(), "Donnie");
    EXPECT_TRUE(++it == it_end);
}

TEST(sregex_iterator, matchOne)
{
    Regex::regex pattern("Do[a-zA-Z]*");
    std::string input = "Who has a Dog named Ronnie?";

    Regex::sregex_iterator it_end;
    Regex::sregex_iterator it(input.begin(), input.end(), pattern);
    EXPECT_EQ(it->str(), "Dog");
    EXPECT_TRUE((++it) == it_end);
}

TEST(sregex_iterator, fullMatch)
{
    Regex::regex pattern("Do[a-zA-Z]*");
    std::string input = "Doberman";

    Regex::sregex_iterator it_end;
    Regex::sregex_iterator it(input.begin(), input.end(), pattern);
    EXPECT_EQ(it->str(), "Doberman");
    EXPECT_TRUE((++it) == it_end);
}

TEST(sregex_iterator, noMatch)
{
    Regex::regex pattern("Do[a-zA-Z]*");
    std::string input = "Hoberman";

    Regex::sregex_iterator it_end;
    Regex::sregex_iterator it(input.begin(), input.end(), pattern);
    EXPECT_TRUE(it == it_end);
}

TEST(sregex_iterator, emptyString)
{
    Regex::regex pattern("Do[a-zA-Z]*");
    std::string input = "";

    Regex::sregex_iterator it_end;
    Regex::sregex_iterator it(input.begin(), input.end(), pattern);
    EXPECT_TRUE(it == it_end);
}
