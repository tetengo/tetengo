/*! \file
    \brief An east Asian width list.

    This file is generated by tool/make_east_asian_width_cpp.py.

    Copyright (C) 2019-2021 kaoru  https://www.tetengo.org/
*/

#if !defined(TETENGO_TEXT_GRAPHEMESPLITTING_EASTASIANWIDTH_HPP_)
#define TETENGO_TEXT_GRAPHEMESPLITTING_EASTASIANWIDTH_HPP_

#include <cstddef>


namespace tetengo::text::grapheme_splitting
{
    enum class east_asian_width_class_type
    {
        ambiguous,
        fullwidth,
        halfwidth,
        narrow,
        wide,
        neutral,
    };

    enum class emoji_type
    {
        emoji,
        normal,
    };

    enum class grapheme_break_property_type
    {
        cr,
        lf,
        control,
        extend,
        zwj,
        regional,
        prepend,
        spacing_mark,
        l,
        v,
        t,
        lv,
        lvt,
        other,
    };


    struct character_property_map_element_type
    {
        char32_t code_point;

        east_asian_width_class_type class_;

        emoji_type emoji;

        grapheme_break_property_type grapheme;
    };


    extern const std::size_t character_property_map_size;

    extern const character_property_map_element_type character_property_map[];


}


#endif
