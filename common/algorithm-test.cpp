#include <deque>
#include <list>

#include "algorithm.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(is_any_of, Trivia) {
  EXPECT_TRUE(mstflint::common::algorithm::is_any_of("BC")('B'));
  EXPECT_FALSE(mstflint::common::algorithm::is_any_of("BC")('A'));
  EXPECT_FALSE(mstflint::common::algorithm::is_any_of("")('A'));
  EXPECT_FALSE(mstflint::common::algorithm::is_any_of("BC")('\0'));
  EXPECT_TRUE(mstflint::common::algorithm::is_any_of("BC")('B'));
  EXPECT_TRUE(mstflint::common::algorithm::is_any_of("~!@#$%^&*()_+")('^'));
  EXPECT_FALSE(mstflint::common::algorithm::is_any_of("~!@#$%^&*()_+")('<'));
}

TEST(is_any_of, Ascii) {
  std::string set =
      "\0\1\2\3\4\5\6\7\n\v\f\r\16\17\18\19\20\21\22\23\24\25\26\27\28\29\30\31"
      " !\"#$%&'()*+,-./"
      "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
      "abcdefghijklmnopqrstuvwxyz{|}~\127";
  for (auto c : set) {
    EXPECT_TRUE(mstflint::common::algorithm::is_any_of(set)(c));
  }
}

TEST(is_any_of, Empty) {
  std::string set =
      "\0\1\2\3\4\5\6\7\n\v\f\r\16\17\18\19\20\21\22\23\24\25\26\27\28\29\30\31"
      " !\"#$%&'()*+,-./"
      "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
      "abcdefghijklmnopqrstuvwxyz{|}~\127";
  for (auto c : set) {
    EXPECT_FALSE(mstflint::common::algorithm::is_any_of("")(c));
  }
}

TEST(is_any_of, StlCompatibility) {
  std::string s = "abcdefghijklmnopqrstuvwxyz";
  EXPECT_TRUE(std::all_of(
      s.begin(), s.end(),
      mstflint::common::algorithm::is_any_of("abcdefghijklmnopqrstuvwxyz")));
  EXPECT_FALSE(std::all_of(
      s.begin(), s.end(),
      mstflint::common::algorithm::is_any_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ")));
  EXPECT_TRUE(std::none_of(
      s.begin(), s.end(),
      mstflint::common::algorithm::is_any_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ")));
  EXPECT_FALSE(std::none_of(
      s.begin(), s.end(),
      mstflint::common::algorithm::is_any_of("abcdefghijklmnopqrstuvwxyz")));
  EXPECT_FALSE(std::any_of(
      s.begin(), s.end(),
      mstflint::common::algorithm::is_any_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ")));
  EXPECT_TRUE(std::any_of(
      s.begin(), s.end(),
      mstflint::common::algorithm::is_any_of("abcdefghijklmnOPQRSTUVWXYZ")));
}

TEST(to_lower, Trivia) {
  std::string actual = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string expected = "abcdefghijklmnopqrstuvwxyz";
  mstflint::common::algorithm::to_lower(actual);
  EXPECT_EQ(expected, actual);
  EXPECT_EQ(expected, mstflint::common::algorithm::to_lower_copy(
                          std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ")));
}

TEST(to_upper, Trivia) {
  std::string actual = "abcdefghijklmnopqrstuvwxyz";
  std::string expected = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  mstflint::common::algorithm::to_upper(actual);
  EXPECT_EQ(expected, actual);
  EXPECT_EQ(expected, mstflint::common::algorithm::to_upper_copy(
                          std::string("abcdefghijklmnopqrstuvwxyz")));
}

TEST(trim, Trivia) {
  std::string actual = "   coupe-moi   ";
  mstflint::common::algorithm::trim(actual);
  EXPECT_EQ(actual, "coupe-moi");
}

TEST(trim, NothingToDo) {
  std::string actual = "rien a faire";
  mstflint::common::algorithm::trim(actual);
  EXPECT_EQ(actual, "rien a faire");
}

TEST(trim, LeftOnly) {
  std::string actual = "rien a faire depuis le debut   ";
  mstflint::common::algorithm::trim(actual);
  EXPECT_EQ(actual, "rien a faire depuis le debut");
}

TEST(trim, RightOnly) {
  std::string actual = "   rien a faire depuis la fin";
  mstflint::common::algorithm::trim(actual);
  EXPECT_EQ(actual, "rien a faire depuis la fin");
}

TEST(trim, AllSpaces) {
  std::string actual = "             ";
  mstflint::common::algorithm::trim(actual);
  EXPECT_TRUE(actual.empty());
}

TEST(trim, Empty) {
  std::string actual = "";
  mstflint::common::algorithm::trim(actual);
  EXPECT_TRUE(actual.empty());
}

TEST(join, Trivia) {
  std::vector<std::string> v = {"The",  "quick", "brown", "fox", "jumps",
                                "over", "the",   "lazy",  "dog"};
  EXPECT_EQ(mstflint::common::algorithm::join(v, " "),
            "The quick brown fox jumps over the lazy dog");
  std::list<std::string> l = {"Why", "did",   "the",     "computer", "catch",
                              "a",   "cold?", "Because", "it",       "had",
                              "too", "many",  "windows", "open!"};
  EXPECT_EQ(mstflint::common::algorithm::join(l, " "),
            "Why did the computer catch a cold? Because it had too many "
            "windows open!");
  std::deque<std::string> d = {"What", "do",   "you", "call",  "a",
                               "fish", "with", "no",  "eyes?", "Fsh!"};
  EXPECT_EQ(mstflint::common::algorithm::join(d, " "),
            "What do you call a fish with no eyes? Fsh!");
}

TEST(join, EmptySeparator) {
  std::vector<std::string> v = {"The",     "Five", "Boxing",
                                "Wizards", "Jump", "Quickly"};
  EXPECT_EQ(mstflint::common::algorithm::join(v, ""),
            "TheFiveBoxingWizardsJumpQuickly");
}

TEST(join, EmptyContainer) {
  std::vector<std::string> v;
  EXPECT_TRUE(mstflint::common::algorithm::join(v, ",").empty());
}

TEST(join, SingleElement) {
  std::vector<std::string> v = {"Single"};
  EXPECT_EQ(mstflint::common::algorithm::join(v, ", "), "Single");
}

TEST(join, LongSeparator) {
  std::vector<std::string> v = {"Pack", "my",    "box",    "with",
                                "five", "dozen", "liquor", "jugs."};
  EXPECT_EQ(mstflint::common::algorithm::join(v, "!@#$%^&*()_+"),
            "Pack!@#$%^&*()_+my!@#$%^&*()_+box!@#$%^&*()_+with!@#$%^&*()_+five!"
            "@#$%^&*()_+dozen!@#$%^&*()_+liquor!@#$%^&*()_+jugs.");
}

TEST(split, SingleCharDelimiterInputStlVector) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "one,two,three,four",
      mstflint::common::algorithm::is_any_of(","));
  EXPECT_THAT(actual,
              ::testing::ElementsAreArray({"one", "two", "three", "four"}));
}

TEST(split, SingleCharDelimiterInputStlList) {
  std::list<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "one,two,three,four",
      mstflint::common::algorithm::is_any_of(","));
  EXPECT_THAT(actual,
              ::testing::ElementsAreArray({"one", "two", "three", "four"}));
}

TEST(split, SingleCharDelimiterInputStlDeque) {
  std::deque<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "one,two,three,four",
      mstflint::common::algorithm::is_any_of(","));
  EXPECT_THAT(actual,
              ::testing::ElementsAreArray({"one", "two", "three", "four"}));
}

TEST(split, SingleCharDelimiterExtraCall) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "one,two,three,four",
      mstflint::common::algorithm::is_any_of(","));
  EXPECT_THAT(actual,
              ::testing::ElementsAreArray({"one", "two", "three", "four"}));
  mstflint::common::algorithm::split(
      actual, "five.six.eight.nine",
      mstflint::common::algorithm::is_any_of("."));
  EXPECT_THAT(actual,
              ::testing::ElementsAreArray({"five", "six", "eight", "nine"}));
}

TEST(split, EmptyDelimiter) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "one,two,three,four", mstflint::common::algorithm::is_any_of(""));
  EXPECT_THAT(actual, ::testing::ElementsAreArray({"one,two,three,four"}));
}

TEST(split, EmptyString) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "", mstflint::common::algorithm::is_any_of(","));
  EXPECT_THAT(actual, ::testing::ElementsAreArray({""}));
}

TEST(split, EmptyDelimiterEmptyString) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "", mstflint::common::algorithm::is_any_of(""));
  EXPECT_THAT(actual, ::testing::ElementsAreArray({""}));
}

TEST(split, SingleCharConsecutiveDelimiters) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "one,,two,three,,,four",
      mstflint::common::algorithm::is_any_of(","));
  EXPECT_THAT(actual, ::testing::ElementsAreArray(
                          {"one", "", "two", "three", "", "", "four"}));
}

TEST(split, SingleCharDelimiterAtTheEdges) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, ",one,two,three,four,",
      mstflint::common::algorithm::is_any_of(","));
  EXPECT_THAT(actual, ::testing::ElementsAreArray(
                          {"", "one", "two", "three", "four", ""}));
}

TEST(split, SingleCharConsecutiveDelimitersAtTheEdges) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, ",,,one,two,three,four,,,,",
      mstflint::common::algorithm::is_any_of(","));
  EXPECT_THAT(actual,
              ::testing::ElementsAreArray(
                  {"", "", "", "one", "two", "three", "four", "", "", "", ""}));
}

TEST(split, MultiCharDelimiter) {
  std::vector<std::string> actual;

  mstflint::common::algorithm::split(
      actual, "one!two@three#four",
      mstflint::common::algorithm::is_any_of("!@#"));
  EXPECT_THAT(actual,
              ::testing::ElementsAreArray({"one", "two", "three", "four"}));

  mstflint::common::algorithm::split(
      actual, "one!two@three#four",
      mstflint::common::algorithm::is_any_of("!@#$%^"));
  EXPECT_THAT(actual,
              ::testing::ElementsAreArray({"one", "two", "three", "four"}));
}

TEST(split, MultiCharDelimiterExtraCall) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "one,two.three/four",
      mstflint::common::algorithm::is_any_of(",./"));
  EXPECT_THAT(actual,
              ::testing::ElementsAreArray({"one", "two", "three", "four"}));
  mstflint::common::algorithm::split(
      actual, "five<six?eight>nine",
      mstflint::common::algorithm::is_any_of("<>?"));
  EXPECT_THAT(actual,
              ::testing::ElementsAreArray({"five", "six", "eight", "nine"}));
}

TEST(split, MultiDelimiterEmptyString) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "", mstflint::common::algorithm::is_any_of(",./"));
  EXPECT_THAT(actual, ::testing::ElementsAreArray({""}));
}

TEST(split, MultiCharConsecutiveDelimiters) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "one*two(*three*(&four",
      mstflint::common::algorithm::is_any_of("&*("));
  EXPECT_THAT(actual, ::testing::ElementsAreArray(
                          {"one", "two", "", "three", "", "", "four"}));
}

TEST(split, MultiCharDelimiterAtTheEdges) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "*one&two)three+four(",
      mstflint::common::algorithm::is_any_of("&*()+"));
  EXPECT_THAT(actual, ::testing::ElementsAreArray(
                          {"", "one", "two", "three", "four", ""}));
}

TEST(split, MultiCharConsecutiveDelimitersAtTheEdges) {
  std::vector<std::string> actual;
  mstflint::common::algorithm::split(
      actual, "%^#*one&two)three+four(%#^+",
      mstflint::common::algorithm::is_any_of("&*()+#%^"));
  EXPECT_THAT(actual, ::testing::ElementsAreArray({"", "", "", "", "one", "two",
                                                   "three", "four", "", "", "",
                                                   "", ""}));
}

TEST(replace_all, SingleOccurrence) {
  std::string actual = "This is a sample text.";
  mstflint::common::algorithm::replace_all(actual, "sample", "replacement");
  EXPECT_EQ(actual, "This is a replacement text.");
  EXPECT_EQ(mstflint::common::algorithm::replace_all_copy(
                std::string("This is a sample text."), "sample", "replacement"),
            "This is a replacement text.");
}

TEST(replace_all, MultipleOccurrences) {
  std::string actual = "The quick brown quick fox jumps over the quick dog.";
  mstflint::common::algorithm::replace_all(actual, "quick", "lazy");
  EXPECT_EQ(actual, "The lazy brown lazy fox jumps over the lazy dog.");
  EXPECT_EQ(
      mstflint::common::algorithm::replace_all_copy(
          std::string("The quick brown quick fox jumps over the quick dog."),
          "quick", "lazy"),
      "The lazy brown lazy fox jumps over the lazy dog.");
}

TEST(replace_all, NoMatch) {
  std::string actual = "This is a sample text.";
  mstflint::common::algorithm::replace_all(actual, "missing", "replacement");
  EXPECT_EQ(actual, "This is a sample text.");
  EXPECT_EQ(
      mstflint::common::algorithm::replace_all_copy(
          std::string("This is a sample text."), "missing", "replacement"),
      "This is a sample text.");
}

TEST(replace_all, EmptyInput) {
  std::string actual = "";
  mstflint::common::algorithm::replace_all(actual, "missing", "replacement");
  EXPECT_EQ(actual, "");
  EXPECT_EQ(mstflint::common::algorithm::replace_all_copy(
                std::string(""), "missing", "replacement"),
            "");
}

TEST(replace_all, EmptySearch) {
  std::string actual = "";
  mstflint::common::algorithm::replace_all(actual, "", "replacement");
  EXPECT_EQ(actual, "");
  EXPECT_EQ(mstflint::common::algorithm::replace_all_copy(std::string(""), "",
                                                          "replacement"),
            "");
}

TEST(replace_all, EmptyFormat) {
  std::string actual = "This is a sample text.";
  mstflint::common::algorithm::replace_all(actual, "sample", "");
  EXPECT_EQ(actual, "This is a  text.");
  EXPECT_EQ(mstflint::common::algorithm::replace_all_copy(
                std::string("This is a sample text."), "sample", ""),
            "This is a  text.");
}

TEST(replace_all, EmptySearchEmptyFormat) {
  std::string actual = "This is a sample text.";
  mstflint::common::algorithm::replace_all(actual, "", "");
  EXPECT_EQ(actual, "This is a sample text.");
  EXPECT_EQ(mstflint::common::algorithm::replace_all_copy(
                std::string("This is a sample text."), "", ""),
            "This is a sample text.");
}

TEST(replace_all, SearchLargerThanInput) {
  std::string actual = "This is a sample text.";
  mstflint::common::algorithm::replace_all(
      actual, "This is a much longer search string than the input.",
      "replacement");
  EXPECT_EQ(actual, "This is a sample text.");
  EXPECT_EQ(mstflint::common::algorithm::replace_all_copy(
                std::string("This is a sample text."),
                "This is a much longer search string than the input.",
                "replacement"),
            "This is a sample text.");
}

TEST(replace_all, IntputWithSpecialCharacters) {
  std::string actual =
      "This ! is # a $ sample % text ^ with & special * symbols.";
  mstflint::common::algorithm::replace_all(actual, "!", "EXCLAMATION MARK");
  EXPECT_EQ(actual, "This EXCLAMATION MARK is # a $ sample % text ^ with & "
                    "special * symbols.");
  EXPECT_EQ(
      mstflint::common::algorithm::replace_all_copy(
          std::string(
              "This ! is # a $ sample % text ^ with & special * symbols."),
          "!", "EXCLAMATION MARK"),
      "This EXCLAMATION MARK is # a $ sample % text ^ with & special * "
      "symbols.");
  mstflint::common::algorithm::replace_all(actual, "#", "HASH");
  EXPECT_EQ(actual, "This EXCLAMATION MARK is HASH a $ sample % text ^ with & "
                    "special * symbols.");
  EXPECT_EQ(
      mstflint::common::algorithm::replace_all_copy(
          std::string(
              "This EXCLAMATION MARK is # a $ sample % text ^ with & special "
              "* symbols."),
          "#", "HASH"),
      "This EXCLAMATION MARK is HASH a $ sample % text ^ with & special "
      "* symbols.");
  mstflint::common::algorithm::replace_all(actual, "$", "DOLLAR");
  EXPECT_EQ(actual, "This EXCLAMATION MARK is HASH a DOLLAR sample % text ^ "
                    "with & special * symbols.");
  EXPECT_EQ(
      mstflint::common::algorithm::replace_all_copy(
          std::string(
              "This EXCLAMATION MARK is HASH a DOLLAR sample % text ^ with & "
              "special * symbols."),
          "$", "DOLLAR"),
      "This EXCLAMATION MARK is HASH a DOLLAR sample % text ^ with & "
      "special * symbols.");
  mstflint::common::algorithm::replace_all(actual, "%", "PERCENT");
  EXPECT_EQ(actual, "This EXCLAMATION MARK is HASH a DOLLAR sample PERCENT "
                    "text ^ with & special * symbols.");
  EXPECT_EQ(
      mstflint::common::algorithm::replace_all_copy(
          std::string(
              "This EXCLAMATION MARK is HASH a DOLLAR sample % text ^ with & "
              "special * symbols."),
          "%", "PERCENT"),
      "This EXCLAMATION MARK is HASH a DOLLAR sample PERCENT text ^ with "
      "& special * symbols.");
  mstflint::common::algorithm::replace_all(actual, "^", "CARET");
  EXPECT_EQ(actual, "This EXCLAMATION MARK is HASH a DOLLAR sample PERCENT "
                    "text CARET with & special * symbols.");
  EXPECT_EQ(
      mstflint::common::algorithm::replace_all_copy(
          std::string(
              "This EXCLAMATION MARK is HASH a DOLLAR sample PERCENT text ^ "
              "with & special * symbols."),
          "^", "CARET"),
      "This EXCLAMATION MARK is HASH a DOLLAR sample PERCENT text CARET "
      "with & special * symbols.");
  mstflint::common::algorithm::replace_all(actual, "&", "AMPERSAND");
  EXPECT_EQ(actual, "This EXCLAMATION MARK is HASH a DOLLAR sample PERCENT "
                    "text CARET with AMPERSAND special * symbols.");
  EXPECT_EQ(
      mstflint::common::algorithm::replace_all_copy(
          std::string(
              "This EXCLAMATION MARK is HASH a DOLLAR sample PERCENT text "
              "CARET with & special * symbols."),
          "&", "AMPERSAND"),
      "This EXCLAMATION MARK is HASH a DOLLAR sample PERCENT text CARET "
      "with AMPERSAND special * symbols.");
  mstflint::common::algorithm::replace_all(actual, "*", "ASTERISK");
  EXPECT_EQ(actual, "This EXCLAMATION MARK is HASH a DOLLAR sample PERCENT "
                    "text CARET with AMPERSAND special ASTERISK symbols.");
  EXPECT_EQ(
      mstflint::common::algorithm::replace_all_copy(
          std::string(
              "This EXCLAMATION MARK is HASH a DOLLAR sample PERCENT text "
              "CARET with AMPERSAND special * symbols."),
          "*", "ASTERISK"),
      "This EXCLAMATION MARK is HASH a DOLLAR sample PERCENT text CARET "
      "with AMPERSAND special ASTERISK symbols.");
}

TEST(replace_all, ReplaceWithBackslashes) {
  std::string actual = "This is a sample text with \\n newlines.";
  mstflint::common::algorithm::replace_all(actual, "\\n", "NEWLINE");
  EXPECT_EQ(actual, "This is a sample text with NEWLINE newlines.");
  EXPECT_EQ(mstflint::common::algorithm::replace_all_copy(
                std::string("This is a sample text with \\n newlines."), "\\n",
                "NEWLINE"),
            "This is a sample text with NEWLINE newlines.");
}
