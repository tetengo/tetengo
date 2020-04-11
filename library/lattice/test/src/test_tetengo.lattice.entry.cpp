/*! \file
    \brief An entry.

    Copyright (C) 2019-2020 kaoru  https://www.tetengo.org/
 */

#include <string>

#include <boost/core/ignore_unused.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo/lattice/entry.h>
#include <tetengo/lattice/entry.hpp>
#include <tetengo/lattice/string_view.h>


namespace
{
    constexpr char to_c(unsigned char uc)
    {
        return uc;
    }

    const std::string key_mizuho{ to_c(0xE3), to_c(0x81), to_c(0xBF), to_c(0xE3), to_c(0x81),
                                  to_c(0x9A), to_c(0xE3), to_c(0x81), to_c(0xBB) };

    const std::string surface_mizuho{ to_c(0xE7), to_c(0x91), to_c(0x9E), to_c(0xE7), to_c(0xA9), to_c(0x82) };

}


BOOST_AUTO_TEST_SUITE(test_tetengo)
BOOST_AUTO_TEST_SUITE(lattice)
BOOST_AUTO_TEST_SUITE(entry)


BOOST_AUTO_TEST_CASE(construction)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::entry      entry_{ key_mizuho, surface_mizuho, 42 };
        const tetengo::lattice::entry_view view_{ entry_ };
    }
    {
        const tetengo_lattice_entry entry_{ { key_mizuho.c_str(), key_mizuho.length() },
                                            { surface_mizuho.c_str(), surface_mizuho.length() },
                                            42 };
        boost::ignore_unused(entry_);
    }
}

BOOST_AUTO_TEST_CASE(key)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::entry entry_{ key_mizuho, surface_mizuho, 42 };

        BOOST_TEST(entry_.key() == key_mizuho);
    }
    {
        const tetengo_lattice_entry entry_{ { key_mizuho.c_str(), key_mizuho.length() },
                                            { surface_mizuho.c_str(), surface_mizuho.length() },
                                            42 };

        BOOST_TEST(entry_.key.p_head == key_mizuho.c_str());
        BOOST_TEST(entry_.key.length == key_mizuho.length());
    }
}

BOOST_AUTO_TEST_CASE(surface)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::entry entry_{ key_mizuho, surface_mizuho, 42 };

        BOOST_TEST(entry_.surface() == surface_mizuho);
    }
    {
        const tetengo_lattice_entry entry_{ { key_mizuho.c_str(), key_mizuho.length() },
                                            { surface_mizuho.c_str(), surface_mizuho.length() },
                                            42 };

        BOOST_TEST(entry_.surface.p_head == surface_mizuho.c_str());
        BOOST_TEST(entry_.surface.length == surface_mizuho.length());
    }
}

BOOST_AUTO_TEST_CASE(cost)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::entry entry_{ key_mizuho, surface_mizuho, 42 };

        BOOST_TEST(entry_.cost() == 42);
    }
    {
        const tetengo_lattice_entry entry_{ { key_mizuho.c_str(), key_mizuho.length() },
                                            { surface_mizuho.c_str(), surface_mizuho.length() },
                                            42 };

        BOOST_TEST(entry_.cost == 42);
    }
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
