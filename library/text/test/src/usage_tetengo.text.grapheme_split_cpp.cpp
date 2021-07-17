/*! \file
    \brief The usage of grapheme splitting.

    Copyright (C) 2019-2021 kaoru  https://www.tetengo.org/
*/

#include "usage_tetengo.text.grapheme_split_cpp.hpp"

// [grapheme_split]
#include <cassert>
#include <locale>
#include <memory>
#include <string>
#include <vector>

#include <tetengo/text/grapheme_splitter.hpp>


namespace usage_tetengo::text
{
    constexpr char operator"" _c(unsigned long long value)
    {
        return static_cast<char>(value);
    }

    const std::locale& japanese_locale();

    const std::locale& english_locale();

    void grapheme_split()
    {
        static const std::string string_{
            // clang-format off
            // HIGH-SPEED TRAIN WITH BULLET NOSE (width: 2)
            0xF0_c, 0x9F_c, 0x9A_c, 0x85_c, // U+1F685
            // POLAR BEAR (width: 2)
            0xF0_c, 0x9F_c, 0x90_c, 0xBB_c, // U+1F43B
            0xE2_c, 0x80_c, 0x8D_c, // U+200D
            0xE2_c, 0x9D_c, 0x84_c, // U+2744
            0xEF_c, 0xB8_c, 0x8F_c, // U+FE0F
            // SNOWFLAKE (width: neutral  2 in the East Asian locale and 1 in the other locale)
            0xE2_c, 0x9D_c, 0x84_c, // U+2744
            // clang-format on
        };

        {
            // Creates a grapheme splitter for the Japanese locale.
            const tetengo::text::grapheme_splitter gs{ std::locale{ japanese_locale() } };

            // Splits the string into graphemes.
            // The splitter will return three graphemes.
            // The width of the grapheme of SNOWFLAKE will be 2.
            const auto graphemes = gs.split(string_);
            assert(graphemes.size() == 3U);
            assert(graphemes[0].offset() == 0U && graphemes[0].width() == 2U);
            assert(graphemes[1].offset() == 4U && graphemes[1].width() == 2U);
            assert(graphemes[2].offset() == 17U && graphemes[2].width() == 2U);
        }
        {
            // Creates a grapheme splitter for the English locale.
            const tetengo::text::grapheme_splitter gs{ std::locale{ english_locale() } };

            // Splits the string into graphemes.
            // The splitter will return three graphemes.
            // The width of the grapheme of SNOWFLAKE will be 1.
            const auto graphemes = gs.split(string_);
            assert(graphemes.size() == 3U);
            assert(graphemes[0].offset() == 0U && graphemes[0].width() == 2U);
            assert(graphemes[1].offset() == 4U && graphemes[1].width() == 2U);
            assert(graphemes[2].offset() == 17U && graphemes[2].width() == 1U);
        }
    }

    const std::locale& japanese_locale()
    {
#if defined(_WIN32)
        static const std::locale singleton{ "Japanese_Japan.932" };
#else
        static const std::locale singleton{ "ja_JP.UTF-8" };
#endif
        return singleton;
    }

    const std::locale& english_locale()
    {
#if defined(_WIN32)
        static const std::locale singleton{ "English_United States.1252" };
#else
        static const std::locale singleton{ "en_US.UTF-8" };
#endif
        return singleton;
    }
}
// [grapheme_split]
