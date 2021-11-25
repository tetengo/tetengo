/*! \file
    \brief An input.

    Copyright (C) 2019-2021 kaoru  https://www.tetengo.org/
*/

#include <cstddef>

#include <tetengo/lattice/input.hpp>


namespace tetengo::lattice
{
    input::~input() = default;

    std::size_t input::length() const
    {
        return length_impl();
    }


}
