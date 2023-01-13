/*! \file
    \brief A connection.

    Copyright (C) 2019-2023 kaoru  https://www.tetengo.org/
*/

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo/lattice/connection.h>
#include <tetengo/lattice/connection.hpp>


BOOST_AUTO_TEST_SUITE(test_tetengo)
BOOST_AUTO_TEST_SUITE(lattice)
BOOST_AUTO_TEST_SUITE(connection)


BOOST_AUTO_TEST_CASE(construction)
{
    BOOST_TEST_PASSPOINT();

    {
        [[maybe_unused]] const tetengo::lattice::connection connection_{ 42 };
    }

    {
        [[maybe_unused]] const tetengo_lattice_connection_t connection_{ 42 };
    }
}

BOOST_AUTO_TEST_CASE(cost)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::connection connection_{ 42 };

        BOOST_TEST(connection_.cost() == 42);
    }

    {
        const tetengo_lattice_connection_t connection_{ 42 };

        BOOST_TEST(connection_.cost == 42);
    }
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
