/*! \file
    \brief A path.

    Copyright (C) 2019-2020 kaoru  https://www.tetengo.org/
 */

#include <algorithm>
#include <any>
#include <cstddef>
#include <iterator>
#include <string_view>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/scope_exit.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo/lattice/node.h>
#include <tetengo/lattice/node.hpp>
#include <tetengo/lattice/path.h>
#include <tetengo/lattice/path.hpp>
#include <tetengo/lattice/stringView.h>


namespace
{
    const std::any& node_value()
    {
        static const std::any singleton{ 42 };
        return singleton;
    }

    const std::vector<int>& bos_preceding_edge_costs()
    {
        static const std::vector<int> singleton{};
        return singleton;
    }

    const std::vector<int>& preceding_edge_costs()
    {
        static const std::vector<int> singleton{ 1 };
        return singleton;
    }

    const std::vector<tetengo::lattice::node>& cpp_nodes()
    {
        static const std::vector<tetengo::lattice::node> singleton{
            tetengo::lattice::node::bos(&bos_preceding_edge_costs()),
            tetengo::lattice::node{ "mizuho", &node_value(), 0, &preceding_edge_costs(), 0, 0, 0 },
            tetengo::lattice::node{ "sakura", &node_value(), 1, &preceding_edge_costs(), 0, 0, 0 },
            tetengo::lattice::node{ "tsubame", &node_value(), 2, &preceding_edge_costs(), 0, 0, 0 },
            tetengo::lattice::node::eos(3, &preceding_edge_costs(), 0, 0)
        };
        return singleton;
    }

    tetengo_lattice_node_t to_c_node(const tetengo::lattice::node& cpp_node)
    {
        tetengo_lattice_node_t c_node{};

        c_node.key.p_head = cpp_node.key().data();
        c_node.key.length = cpp_node.key().length();
        c_node.value_handle = reinterpret_cast<tetengo_lattice_entry_valueHandle_t>(&cpp_node.value());
        c_node.preceding_step = cpp_node.preceding_step();
        c_node.p_preceding_edge_costs = cpp_node.preceding_edge_costs().data();
        c_node.preceding_edge_cost_count = cpp_node.preceding_edge_costs().size();
        c_node.best_preceding_node = cpp_node.best_preceding_node();
        c_node.node_cost = cpp_node.node_cost();
        c_node.path_cost = cpp_node.path_cost();

        return c_node;
    }

    const std::vector<tetengo_lattice_node_t>& c_nodes()
    {
        static const std::vector<tetengo_lattice_node_t> singleton{ []() {
            std::vector<tetengo_lattice_node_t>          nodes{};
            nodes.reserve(cpp_nodes().size());
            std::transform(std::begin(cpp_nodes()), std::end(cpp_nodes()), std::back_inserter(nodes), to_c_node);
            return nodes;
        }() };
        return singleton;
    }

    bool equal_nodes(const std::vector<tetengo_lattice_node_t>& one, const std::vector<tetengo_lattice_node_t>& another)
    {
        if (one.size() != another.size())
        {
            return false;
        }

        for (auto i = static_cast<std::size_t>(0); i < one.size(); ++i)
        {
            if (!tetengo_lattice_node_equal(&one[i], &another[i]))
            {
                return false;
            }
        }

        return true;
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo)
BOOST_AUTO_TEST_SUITE(lattice)
BOOST_AUTO_TEST_SUITE(path)


BOOST_AUTO_TEST_CASE(construction)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::path path_{};
    }
    {
        const tetengo::lattice::path path_{ cpp_nodes(), 42 };
    }

    {
        const auto* const p_path = tetengo_lattice_path_create(c_nodes().data(), c_nodes().size(), 42);
        BOOST_SCOPE_EXIT(p_path)
        {
            tetengo_lattice_path_destroy(p_path);
        }
        BOOST_SCOPE_EXIT_END;

        BOOST_TEST(p_path);
    }
    {
        const auto* const p_path = tetengo_lattice_path_create(nullptr, 0, 42);

        BOOST_TEST(!p_path);
    }
}

BOOST_AUTO_TEST_CASE(nodes)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::path path_{};

        BOOST_CHECK(path_.nodes().empty());
    }
    {
        const tetengo::lattice::path path_{ cpp_nodes(), 42 };

        BOOST_CHECK(path_.nodes() == cpp_nodes());
    }

    {
        const auto* const p_path = tetengo_lattice_path_createEmpty();
        BOOST_SCOPE_EXIT(p_path)
        {
            tetengo_lattice_path_destroy(p_path);
        }
        BOOST_SCOPE_EXIT_END;

        const auto node_count = tetengo_lattice_path_pNodes(p_path, nullptr);
        BOOST_TEST(node_count == 0);
    }
    {
        const auto* const p_path = tetengo_lattice_path_create(c_nodes().data(), c_nodes().size(), 42);
        BOOST_SCOPE_EXIT(p_path)
        {
            tetengo_lattice_path_destroy(p_path);
        }
        BOOST_SCOPE_EXIT_END;

        const auto node_count = tetengo_lattice_path_pNodes(p_path, nullptr);
        BOOST_TEST_REQUIRE(node_count == c_nodes().size());
        std::vector<tetengo_lattice_node_t> nodes{ node_count };
        const auto                          node_count_again = tetengo_lattice_path_pNodes(p_path, nodes.data());
        BOOST_TEST(node_count_again == c_nodes().size());
        BOOST_TEST(equal_nodes(nodes, c_nodes()));
    }
    {
        const auto node_count = tetengo_lattice_path_pNodes(nullptr, nullptr);
        BOOST_TEST(node_count == 0U);
    }
}

BOOST_AUTO_TEST_CASE(cost)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::path path_{};

        BOOST_CHECK(path_.cost() == 0U);
    }
    {
        const tetengo::lattice::path path_{ cpp_nodes(), 42 };

        BOOST_TEST(path_.cost() == 42U);
    }

    {
        const auto* const p_path = tetengo_lattice_path_createEmpty();
        BOOST_SCOPE_EXIT(p_path)
        {
            tetengo_lattice_path_destroy(p_path);
        }
        BOOST_SCOPE_EXIT_END;

        BOOST_TEST(tetengo_lattice_path_cost(p_path) == 0U);
    }
    {
        const auto* const p_path = tetengo_lattice_path_create(c_nodes().data(), c_nodes().size(), 42);
        BOOST_SCOPE_EXIT(p_path)
        {
            tetengo_lattice_path_destroy(p_path);
        }
        BOOST_SCOPE_EXIT_END;

        BOOST_TEST(tetengo_lattice_path_cost(p_path) == 42U);
    }
    {
        BOOST_TEST(tetengo_lattice_path_cost(nullptr) == 0U);
    }
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
