/*! \file
    \brief An N-best lattice path iterator.

    Copyright (C) 2019-2024 kaoru  https://www.tetengo.org/
*/

#include <algorithm>
#include <any>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/scope_exit.hpp>
#include <boost/stl_interfaces/iterator_interface.hpp> // IWYU pragma: keep

#include <tetengo/lattice/constraint.h>
#include <tetengo/lattice/entry.h>
#include <tetengo/lattice/input.h>
#include <tetengo/lattice/lattice.h>
#include <tetengo/lattice/nBestIterator.h>
#include <tetengo/lattice/n_best_iterator.hpp>
#include <tetengo/lattice/node.h>
#include <tetengo/lattice/node.hpp>
#include <tetengo/lattice/path.h>
#include <tetengo/lattice/path.hpp>

#include "tetengo_lattice_constraint.hpp"
#include "tetengo_lattice_input.hpp"
#include "tetengo_lattice_lattice.hpp"


struct tetengo_lattice_nBestIterator_tag
{
    std::unique_ptr<std::pair<tetengo::lattice::n_best_iterator, tetengo::lattice::n_best_iterator>>
        p_cpp_iterator_pair;

    std::unique_ptr<std::vector<int>> p_cpp_eos_preceding_edge_costs;

    tetengo_lattice_nBestIterator_tag(
        std::unique_ptr<std::pair<tetengo::lattice::n_best_iterator, tetengo::lattice::n_best_iterator>>&&
                                            p_cpp_iterator_pair,
        std::unique_ptr<std::vector<int>>&& p_cpp_eos_preceding_edge_costs) :
    p_cpp_iterator_pair{ std::move(p_cpp_iterator_pair) },
    p_cpp_eos_preceding_edge_costs{ std::move(p_cpp_eos_preceding_edge_costs) }
    {}
};

tetengo_lattice_nBestIterator_t* tetengo_lattice_nBestIterator_create(
    const tetengo_lattice_lattice_t* const p_lattice,
    const tetengo_lattice_node_t* const    p_eos_node,
    tetengo_lattice_constraint_t* const    p_constraint)
{
    try
    {
        BOOST_SCOPE_EXIT(p_constraint)
        {
            tetengo_lattice_constraint_destroy(p_constraint);
        }
        BOOST_SCOPE_EXIT_END;

        if (!p_lattice)
        {
            throw std::invalid_argument{ "p_lattice is NULL." };
        }
        if (!p_eos_node)
        {
            throw std::invalid_argument{ "p_eos_node is NULL." };
        }
        if (!p_constraint)
        {
            throw std::invalid_argument{ "p_constraint is NULL." };
        }

        const auto* const p_cpp_node_key = tetengo_lattice_entryView_createKeyOf(p_eos_node->key_handle);
        BOOST_SCOPE_EXIT(p_cpp_node_key)
        {
            tetengo_lattice_input_destroy(p_cpp_node_key);
        }
        BOOST_SCOPE_EXIT_END;
        auto p_cpp_preceding_edge_costs = std::make_unique<std::vector<int>>(
            p_eos_node->p_preceding_edge_costs,
            p_eos_node->p_preceding_edge_costs + p_eos_node->preceding_edge_cost_count);
        tetengo::lattice::node cpp_eos_node{ p_cpp_node_key ? &p_cpp_node_key->cpp_input() : nullptr,
                                             reinterpret_cast<const std::any*>(p_eos_node->value_handle),
                                             p_eos_node->index_in_step,
                                             p_eos_node->preceding_step,
                                             std::to_address(p_cpp_preceding_edge_costs),
                                             p_eos_node->best_preceding_node,
                                             p_eos_node->node_cost,
                                             p_eos_node->path_cost };

        auto p_instance = std::make_unique<tetengo_lattice_nBestIterator_t>(
            std::make_unique<std::pair<tetengo::lattice::n_best_iterator, tetengo::lattice::n_best_iterator>>(
                tetengo::lattice::n_best_iterator{
                    *p_lattice->p_cpp_lattice, std::move(cpp_eos_node), std::move(p_constraint->p_cpp_constraint) },
                tetengo::lattice::n_best_iterator{}),
            std::move(p_cpp_preceding_edge_costs));
        return p_instance.release();
    }
    catch (...)
    {
        return nullptr;
    }
}

void tetengo_lattice_nBestIterator_destroy(const tetengo_lattice_nBestIterator_t* const p_iterator)
{
    try
    {
        const std::unique_ptr<const tetengo_lattice_nBestIterator_t> p_instance{ p_iterator };
    }
    catch (...)
    {}
}

tetengo_lattice_path_t*
tetengo_lattice_nBestIterator_createPath(const tetengo_lattice_nBestIterator_t* const p_iterator)
{
    try
    {
        if (!p_iterator)
        {
            throw std::invalid_argument{ "p_iterator is NULL." };
        }

        const auto& cpp_path = *p_iterator->p_cpp_iterator_pair->first;

        std::vector<tetengo_lattice_node_t> nodes{};
        nodes.reserve(std::size(cpp_path.nodes()));
        for (const auto& cpp_node: cpp_path.nodes())
        {
            nodes.push_back({ reinterpret_cast<tetengo_lattice_entryView_keyHandle_t>(cpp_node.p_key()),
                              reinterpret_cast<tetengo_lattice_entryView_valueHandle_t>(&cpp_node.value()),
                              cpp_node.index_in_step(),
                              cpp_node.preceding_step(),
                              std::data(cpp_node.preceding_edge_costs()),
                              std::size(cpp_node.preceding_edge_costs()),
                              cpp_node.best_preceding_node(),
                              cpp_node.node_cost(),
                              cpp_node.path_cost() });
        }

        return tetengo_lattice_path_create(std::data(nodes), std::size(nodes), cpp_path.cost());
    }
    catch (...)
    {
        return nullptr;
    }
}

bool tetengo_lattice_nBestIterator_hasNext(const tetengo_lattice_nBestIterator_t* p_iterator)
{
    try
    {
        if (!p_iterator)
        {
            throw std::invalid_argument{ "p_iterator is NULL." };
        }

        return p_iterator->p_cpp_iterator_pair->first != p_iterator->p_cpp_iterator_pair->second;
    }
    catch (...)
    {
        return false;
    }
}

void tetengo_lattice_nBestIterator_next(tetengo_lattice_nBestIterator_t* p_iterator)
{
    try
    {
        if (!p_iterator)
        {
            throw std::invalid_argument{ "p_iterator is NULL." };
        }

        ++p_iterator->p_cpp_iterator_pair->first;
    }
    catch (...)
    {}
}
