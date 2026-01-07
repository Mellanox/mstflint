/*
 * Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "common/tools_string.h"

using std::string;

using nbu::mft::common::string_format;

TEST(string_format, Empty)
{
    std::string actual = string_format("");
    EXPECT_EQ(actual, "");
}

TEST(string_format, NoArguments)
{
    string actual = string_format("no arguments");
    ASSERT_EQ(actual, "no arguments");
}

TEST(string_format, MixedArguments)
{
    string actual = string_format("int8_t(dec): %d "
                                  "int8_t(hex): %02x "
                                  "int16_t(dec): %d "
                                  "int16_t(hex): %04x "
                                  "int32_t(dec): %d "
                                  "int32_t(hex): %08x "
                                  "int64_t(dec): %d "
                                  "int64_t(hex): %08x "
                                  "string: %s",
                                  -65,
                                  128,
                                  45861,
                                  -58621,
                                  -5694382568,
                                  9586526456,
                                  -36829764823,
                                  78901234567890,
                                  "Serendipity");

    ASSERT_EQ(actual,
              "int8_t(dec): -65 "
              "int8_t(hex): 80 "
              "int16_t(dec): 45861 "
              "int16_t(hex): ffff1b03 "
              "int32_t(dec): -1399415272 "
              "int32_t(hex): 3b66c8f8 "
              "int64_t(dec): 1824940841 "
              "int64_t(hex): a00f0ad2 "
              "string: Serendipity");
}

TEST(string_format, LongFormatString)
{
    string actual = string_format(
      "In the fantastical realm of %s, where luminous dragons soar through cotton candy skies and whisper"
      " secrets to %d ancient oak trees adorned with kaleidoscopic leaves that shimmer like iridescent "
      "fireflies on a midsummer night's dream. Beneath the twinkling canopy of stars, a whimsical parade "
      "of enchanted creatures twirls in harmonic syncopation to the celestial symphony conducted by the"
      " moon's radiant baton, weaving intricate tapestries of ethereal melodies that echo across the emerald "
      "valleys and mist-shrouded peaks. Enchanted waterfalls cascade in shimmering veils of liquid moonlight, "
      "casting spellbinding reflections upon the tranquil lakes where mermaids weave tales of forgotten realms "
      "and playful sprites perform acrobatic pirouettes amidst cascading blossoms of luminescent phosphorescence. "
      "Time dances in eternal reverie, painting the canvas of existence with strokes of serendipitous wonder and "
      "whimsical merriment, where each moment unfolds like a %05.15f mystical riddle waiting to be unraveled "
      "by the curious wanderer who dares to dream beyond the horizon of ordinary perception.",
      "Quixotica", -713549, 1.77245385091);

    ASSERT_EQ(
      actual,
      "In the fantastical realm of Quixotica, where luminous dragons soar through cotton candy skies and whisper"
      " secrets to -713549 ancient oak trees adorned with kaleidoscopic leaves that shimmer like iridescent "
      "fireflies on a midsummer night's dream. Beneath the twinkling canopy of stars, a whimsical parade "
      "of enchanted creatures twirls in harmonic syncopation to the celestial symphony conducted by the"
      " moon's radiant baton, weaving intricate tapestries of ethereal melodies that echo across the emerald "
      "valleys and mist-shrouded peaks. Enchanted waterfalls cascade in shimmering veils of liquid moonlight, "
      "casting spellbinding reflections upon the tranquil lakes where mermaids weave tales of forgotten realms "
      "and playful sprites perform acrobatic pirouettes amidst cascading blossoms of luminescent phosphorescence. "
      "Time dances in eternal reverie, painting the canvas of existence with strokes of serendipitous wonder and "
      "whimsical merriment, where each moment unfolds like a 1.772453850910000 mystical riddle waiting to be unraveled "
      "by the curious wanderer who dares to dream beyond the horizon of ordinary perception.");
}
