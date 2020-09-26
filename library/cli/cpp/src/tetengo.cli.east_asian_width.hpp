/*! \file
    \brief An east Asian width list.

    This file is generated by tools/make_east_asian_width_cpp.py.

    Copyright (C) 2019-2020 kaoru  https://www.tetengo.org/
*/

#if !defined(TETENGO_CLI_EASTASIANWIDTH_HPP_)
#define TETENGO_CLI_EASTASIANWIDTH_HPP_

#include <cstddef>


namespace tetengo::cli
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


    struct east_asian_width_type
    {
        char32_t code_point;

        east_asian_width_class_type class_;

        bool combining;
    };


    extern const std::size_t east_asian_width_list_size;

    extern const east_asian_width_type east_asian_width_list[];


}


#endif
