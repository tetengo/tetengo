/*! \file
    \brief A wildcard constraint element.

    Copyright (C) 2019-2025 kaoru  https://www.tetengo.org/
*/

#include <any>
#include <cstddef>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/scope_exit.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo/lattice/constraintElement.h>
#include <tetengo/lattice/entry.h>
#include <tetengo/lattice/input.h>
#include <tetengo/lattice/node.h>
#include <tetengo/lattice/node.hpp>
#include <tetengo/lattice/string_input.hpp>
#include <tetengo/lattice/wildcard_constraint_element.hpp>


BOOST_AUTO_TEST_SUITE(test_tetengo)
BOOST_AUTO_TEST_SUITE(lattice)
BOOST_AUTO_TEST_SUITE(wildcard_constraint_element)


BOOST_AUTO_TEST_CASE(construction)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::wildcard_constraint_element element{ 3 };
    }

    {
        const auto* const p_constraint_element = tetengo_lattice_constraintElement_createWildcardConstraintElement(3);
        BOOST_SCOPE_EXIT(p_constraint_element)
        {
            tetengo_lattice_constraintElement_destroy(p_constraint_element);
        }
        BOOST_SCOPE_EXIT_END;
        BOOST_TEST(p_constraint_element);
    }
}

BOOST_AUTO_TEST_CASE(matches)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::wildcard_constraint_element element{ 3 };

        {
            const tetengo::lattice::string_input key{ "mizuho" };
            const std::any                       value{ 42 };
            const std::vector<int>               preceding_edge_costs{ 3, 1, 4, 1, 5, 9, 2, 6 };
            const tetengo::lattice::node         node_{ &key, &value, 0, 1, &preceding_edge_costs, 5, 24, 2424 };

            BOOST_TEST(element.matches(node_) < 0);
        }
        {
            const tetengo::lattice::string_input key{ "sakura" };
            const std::any                       value{ 42 };
            const std::vector<int>               preceding_edge_costs{ 3, 1, 4, 1, 5, 9, 2, 6 };
            const tetengo::lattice::node         node_{ &key, &value, 0, 3, &preceding_edge_costs, 5, 24, 2424 };

            BOOST_TEST(element.matches(node_) == 0);
        }
        {
            const tetengo::lattice::string_input key{ "tsubame" };
            const std::any                       value{ 42 };
            const std::vector<int>               preceding_edge_costs{ 3, 1, 4, 1, 5, 9, 2, 6 };
            const tetengo::lattice::node         node_{ &key, &value, 0, 5, &preceding_edge_costs, 5, 24, 2424 };

            BOOST_TEST(element.matches(node_) > 0);
        }
    }
    {
        const tetengo::lattice::wildcard_constraint_element element{ std::numeric_limits<std::size_t>::max() };

        {
            const std::vector<int>       preceding_edge_costs{};
            const tetengo::lattice::node node_ = tetengo::lattice::node::bos(&preceding_edge_costs);

            BOOST_TEST(element.matches(node_) == 0);
        }
        {
            const tetengo::lattice::string_input key{ "mizuho" };
            const std::any                       value{ 42 };
            const std::vector<int>               preceding_edge_costs{ 3, 1, 4, 1, 5, 9, 2, 6 };
            const tetengo::lattice::node         node_{ &key, &value, 0, 1, &preceding_edge_costs, 5, 24, 2424 };

            BOOST_TEST(element.matches(node_) > 0);
        }
    }

    {
        const auto* const p_constraint_element = tetengo_lattice_constraintElement_createWildcardConstraintElement(3);
        BOOST_SCOPE_EXIT(p_constraint_element)
        {
            tetengo_lattice_constraintElement_destroy(p_constraint_element);
        }
        BOOST_SCOPE_EXIT_END;
        BOOST_TEST_REQUIRE(p_constraint_element);

        {
            const auto* const p_key = tetengo_lattice_input_createStringInput("mizuho");
            BOOST_SCOPE_EXIT(p_key)
            {
                tetengo_lattice_input_destroy(p_key);
            }
            BOOST_SCOPE_EXIT_END;
            const std::any               value{ reinterpret_cast<const void*>("MIZUHO") };
            const std::vector<int>       preceding_edge_costs{ 3, 1, 4, 1, 5, 9, 2, 6 };
            const tetengo_lattice_node_t node{ tetengo_lattice_entryView_toKeyHandle(p_key),
                                               reinterpret_cast<tetengo_lattice_entryView_valueHandle_t>(&value),
                                               0,
                                               1,
                                               std::data(preceding_edge_costs),
                                               std::size(preceding_edge_costs),
                                               5,
                                               24,
                                               2424 };

            BOOST_TEST(tetengo_lattice_constraintElement_matches(p_constraint_element, &node) < 0);
        }
        {
            const auto* const p_key = tetengo_lattice_input_createStringInput("sakura");
            BOOST_SCOPE_EXIT(p_key)
            {
                tetengo_lattice_input_destroy(p_key);
            }
            BOOST_SCOPE_EXIT_END;
            const std::any               value{ reinterpret_cast<const void*>("SAKURA") };
            const std::vector<int>       preceding_edge_costs{ 3, 1, 4, 1, 5, 9, 2, 6 };
            const tetengo_lattice_node_t node{ tetengo_lattice_entryView_toKeyHandle(p_key),
                                               reinterpret_cast<tetengo_lattice_entryView_valueHandle_t>(&value),
                                               0,
                                               3,
                                               std::data(preceding_edge_costs),
                                               std::size(preceding_edge_costs),
                                               5,
                                               24,
                                               2424 };

            BOOST_TEST(tetengo_lattice_constraintElement_matches(p_constraint_element, &node) == 0);
        }
        {
            const auto* const p_key = tetengo_lattice_input_createStringInput("tsubame");
            BOOST_SCOPE_EXIT(p_key)
            {
                tetengo_lattice_input_destroy(p_key);
            }
            BOOST_SCOPE_EXIT_END;
            const std::any               value{ reinterpret_cast<const void*>("TSUBAME") };
            const std::vector<int>       preceding_edge_costs{ 3, 1, 4, 1, 5, 9, 2, 6 };
            const tetengo_lattice_node_t node{ tetengo_lattice_entryView_toKeyHandle(p_key),
                                               reinterpret_cast<tetengo_lattice_entryView_valueHandle_t>(&value),
                                               0,
                                               5,
                                               std::data(preceding_edge_costs),
                                               std::size(preceding_edge_costs),
                                               5,
                                               24,
                                               2424 };

            BOOST_TEST(tetengo_lattice_constraintElement_matches(p_constraint_element, &node) > 0);
        }
    }
    {
        const auto* const p_constraint_element =
            tetengo_lattice_constraintElement_createWildcardConstraintElement(std::numeric_limits<size_t>::max());
        BOOST_SCOPE_EXIT(p_constraint_element)
        {
            tetengo_lattice_constraintElement_destroy(p_constraint_element);
        }
        BOOST_SCOPE_EXIT_END;
        BOOST_TEST_REQUIRE(p_constraint_element);

        {
            const std::vector<int> preceding_edge_costs{};
            tetengo_lattice_node_t node{};
            tetengo_lattice_node_bos(std::data(preceding_edge_costs), std::size(preceding_edge_costs), &node);

            BOOST_TEST(tetengo_lattice_constraintElement_matches(p_constraint_element, &node) == 0);
        }
        {
            const auto* const p_key = tetengo_lattice_input_createStringInput("mizuho");
            BOOST_SCOPE_EXIT(p_key)
            {
                tetengo_lattice_input_destroy(p_key);
            }
            BOOST_SCOPE_EXIT_END;
            const std::any               value{ reinterpret_cast<const void*>("MIZUHO") };
            const std::vector<int>       preceding_edge_costs{ 3, 1, 4, 1, 5, 9, 2, 6 };
            const tetengo_lattice_node_t node{ tetengo_lattice_entryView_toKeyHandle(p_key),
                                               reinterpret_cast<tetengo_lattice_entryView_valueHandle_t>(&value),
                                               0,
                                               1,
                                               std::data(preceding_edge_costs),
                                               std::size(preceding_edge_costs),
                                               5,
                                               24,
                                               2424 };

            BOOST_TEST(tetengo_lattice_constraintElement_matches(p_constraint_element, &node) > 0);
        }
    }
    {
        const auto* const p_key = tetengo_lattice_input_createStringInput("mizuho");
        BOOST_SCOPE_EXIT(p_key)
        {
            tetengo_lattice_input_destroy(p_key);
        }
        BOOST_SCOPE_EXIT_END;
        const std::any               value{ reinterpret_cast<const void*>("MIZUHO") };
        const std::vector<int>       preceding_edge_costs{ 3, 1, 4, 1, 5, 9, 2, 6 };
        const tetengo_lattice_node_t node{ tetengo_lattice_entryView_toKeyHandle(p_key),
                                           reinterpret_cast<tetengo_lattice_entryView_valueHandle_t>(&value),
                                           0,
                                           1,
                                           std::data(preceding_edge_costs),
                                           std::size(preceding_edge_costs),
                                           5,
                                           24,
                                           2424 };

        BOOST_TEST(tetengo_lattice_constraintElement_matches(nullptr, &node) < 0);
    }
    {
        const auto* const p_constraint_element = tetengo_lattice_constraintElement_createWildcardConstraintElement(3);
        BOOST_SCOPE_EXIT(p_constraint_element)
        {
            tetengo_lattice_constraintElement_destroy(p_constraint_element);
        }
        BOOST_SCOPE_EXIT_END;
        BOOST_TEST_REQUIRE(p_constraint_element);

        BOOST_TEST(tetengo_lattice_constraintElement_matches(p_constraint_element, nullptr) < 0);
    }
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
