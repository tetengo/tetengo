/*! \file
    \brief A constraint.

    Copyright (C) 2019-2020 kaoru  https://www.tetengo.org/
 */

#include <any>
#include <memory>
#include <string_view>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo/lattice/constraint.hpp>
#include <tetengo/lattice/constraint_element.hpp>
#include <tetengo/lattice/node.hpp>
#include <tetengo/lattice/node_constraint_element.hpp>
#include <tetengo/lattice/wildcard_constraint_element.hpp>


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

    const std::vector<tetengo::lattice::node>& path_b_e()
    {
        static const std::vector<tetengo::lattice::node> singleton{
            tetengo::lattice::node::bos(&bos_preceding_edge_costs()),
            tetengo::lattice::node::eos(0, &preceding_edge_costs(), 0, 0)
        };
        return singleton;
    }

    const std::vector<tetengo::lattice::node>& path_b_m_s_t_e()
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

    const std::vector<tetengo::lattice::node>& path_b_m_a_t_e()
    {
        static const std::vector<tetengo::lattice::node> singleton{
            tetengo::lattice::node::bos(&bos_preceding_edge_costs()),
            tetengo::lattice::node{ "mizuho", &node_value(), 0, &preceding_edge_costs(), 0, 0, 0 },
            tetengo::lattice::node{ "ariake", &node_value(), 1, &preceding_edge_costs(), 0, 0, 0 },
            tetengo::lattice::node{ "tsubame", &node_value(), 2, &preceding_edge_costs(), 0, 0, 0 },
            tetengo::lattice::node::eos(3, &preceding_edge_costs(), 0, 0)
        };
        return singleton;
    }

    const std::vector<tetengo::lattice::node>& path_b_h_t_e()
    {
        static const std::vector<tetengo::lattice::node> singleton{
            tetengo::lattice::node::bos(&bos_preceding_edge_costs()),
            tetengo::lattice::node{ "hinokuni", &node_value(), 0, &preceding_edge_costs(), 0, 0, 0 },
            tetengo::lattice::node{ "tsubame", &node_value(), 2, &preceding_edge_costs(), 0, 0, 0 },
            tetengo::lattice::node::eos(3, &preceding_edge_costs(), 0, 0)
        };
        return singleton;
    }

    const std::vector<tetengo::lattice::node>& path_b_k_s_k_e()
    {
        static const std::vector<tetengo::lattice::node> singleton{
            tetengo::lattice::node::bos(&bos_preceding_edge_costs()),
            tetengo::lattice::node{ "kamome", &node_value(), 0, &preceding_edge_costs(), 0, 0, 0 },
            tetengo::lattice::node{ "sakura", &node_value(), 1, &preceding_edge_costs(), 0, 0, 0 },
            tetengo::lattice::node{ "kumagawa", &node_value(), 2, &preceding_edge_costs(), 0, 0, 0 },
            tetengo::lattice::node::eos(3, &preceding_edge_costs(), 0, 0)
        };
        return singleton;
    }

    std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> make_pattern_b_e()
    {
        std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> pattern{};
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_e()[0]));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_e()[1]));
        return pattern;
    }

    std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> make_pattern_b_m_s_t_e()
    {
        std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> pattern{};
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[0]));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[1]));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[2]));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[3]));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[4]));
        return pattern;
    }

    std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> make_pattern_b_m_w_t_e()
    {
        std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> pattern{};
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[0]));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[1]));
        pattern.push_back(std::make_unique<tetengo::lattice::wildcard_constraint_element>(1));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[3]));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[4]));
        return pattern;
    }

    std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> make_pattern_b_w_t_e()
    {
        std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> pattern{};
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[0]));
        pattern.push_back(std::make_unique<tetengo::lattice::wildcard_constraint_element>(0));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[3]));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[4]));
        return pattern;
    }

    std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> make_pattern_b_w_s_w_e()
    {
        std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> pattern{};
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[0]));
        pattern.push_back(std::make_unique<tetengo::lattice::wildcard_constraint_element>(0));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[2]));
        pattern.push_back(std::make_unique<tetengo::lattice::wildcard_constraint_element>(2));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[4]));
        return pattern;
    }

    std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> make_pattern_b_w_e()
    {
        std::vector<std::unique_ptr<tetengo::lattice::constraint_element>> pattern{};
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[0]));
        pattern.push_back(std::make_unique<tetengo::lattice::wildcard_constraint_element>(0));
        pattern.push_back(std::make_unique<tetengo::lattice::node_constraint_element>(path_b_m_s_t_e()[4]));
        return pattern;
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo)
BOOST_AUTO_TEST_SUITE(lattice)
BOOST_AUTO_TEST_SUITE(constraint)


BOOST_AUTO_TEST_CASE(construction)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::constraint constraint_{ make_pattern_b_e() };
    }
}

BOOST_AUTO_TEST_CASE(matches)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::constraint constraint_{ make_pattern_b_e() };

        BOOST_TEST(constraint_.matches(path_b_e()));
        BOOST_TEST(!constraint_.matches(path_b_m_s_t_e()));
        BOOST_TEST(!constraint_.matches(path_b_m_a_t_e()));
        BOOST_TEST(!constraint_.matches(path_b_h_t_e()));
        BOOST_TEST(!constraint_.matches(path_b_k_s_k_e()));
    }
    {
        const tetengo::lattice::constraint constraint_{ make_pattern_b_m_s_t_e() };

        BOOST_TEST(!constraint_.matches(path_b_e()));
        BOOST_TEST(constraint_.matches(path_b_m_s_t_e()));
        BOOST_TEST(!constraint_.matches(path_b_m_a_t_e()));
        BOOST_TEST(!constraint_.matches(path_b_h_t_e()));
        BOOST_TEST(!constraint_.matches(path_b_k_s_k_e()));
    }
    {
        const tetengo::lattice::constraint constraint_{ make_pattern_b_m_w_t_e() };

        BOOST_TEST(!constraint_.matches(path_b_e()));
        BOOST_TEST(constraint_.matches(path_b_m_s_t_e()));
        BOOST_TEST(constraint_.matches(path_b_m_a_t_e()));
        BOOST_TEST(!constraint_.matches(path_b_h_t_e()));
        BOOST_TEST(!constraint_.matches(path_b_k_s_k_e()));
    }
    {
        const tetengo::lattice::constraint constraint_{ make_pattern_b_w_t_e() };

        BOOST_TEST(!constraint_.matches(path_b_e()));
        BOOST_TEST(constraint_.matches(path_b_m_s_t_e()));
        BOOST_TEST(constraint_.matches(path_b_m_a_t_e()));
        BOOST_TEST(constraint_.matches(path_b_h_t_e()));
        BOOST_TEST(!constraint_.matches(path_b_k_s_k_e()));
    }
    {
        const tetengo::lattice::constraint constraint_{ make_pattern_b_w_s_w_e() };

        BOOST_TEST(!constraint_.matches(path_b_e()));
        BOOST_TEST(constraint_.matches(path_b_m_s_t_e()));
        BOOST_TEST(!constraint_.matches(path_b_m_a_t_e()));
        BOOST_TEST(!constraint_.matches(path_b_h_t_e()));
        BOOST_TEST(constraint_.matches(path_b_k_s_k_e()));
    }
    {
        const tetengo::lattice::constraint constraint_{ make_pattern_b_w_e() };

        BOOST_TEST(!constraint_.matches(path_b_e()));
        BOOST_TEST(constraint_.matches(path_b_m_s_t_e()));
        BOOST_TEST(constraint_.matches(path_b_m_a_t_e()));
        BOOST_TEST(constraint_.matches(path_b_h_t_e()));
        BOOST_TEST(constraint_.matches(path_b_k_s_k_e()));
    }
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
