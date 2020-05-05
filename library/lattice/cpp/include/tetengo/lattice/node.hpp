/*! \file
    \brief A node.

    Copyright (C) 2019-2020 kaoru  https://www.tetengo.org/
*/

#if !defined(TETENGO_LATTICE_NODE_HPP)
#define TETENGO_LATTICE_NODE_HPP

#include <any>
#include <cstddef>
#include <limits>
#include <string_view>

#include <tetengo/lattice/entry.hpp>


namespace tetengo::lattice
{
    /*!
        \brief A node.
    */
    class node
    {
    public:
        // static functions

        /*!
            \brief Returns the BOS (Beginning of Sequence).

            \return The BOS.
        */
        static const node& bos();

        /*!
            \brief Returns an EOS (End of Sequence).

            \param preceding_step An index of a preceding step.
            \param path_cost      A path cost.

            \return An EOS.
        */
        static node eos(std::size_t preceding_step, int path_cost);


        // constructors and destructor

        /*!
            \brief Creates a node.

            \param key            A key.
            \param value          A value.
            \param preceding_step An index of a preceding step.
            \param node_cost      A node cost.
            \param path_cost      A path cost.
        */
        node(std::string_view key, std::any value, std::size_t preceding_step, int node_cost, int path_cost);

        /*!
            \brief Creates a node from a vocabulary entry.

            \param entry          An entry.
            \param preceding_step An index of a preceding step.
            \param path_cost      A path cost.
        */
        explicit node(
            const entry_view& entry,
            std::size_t       preceding_step = std::numeric_limits<std::size_t>::max(),
            int               path_cost = std::numeric_limits<int>::max());


        // functions

        /*!
            \brief Returns the key.

            \return The key.
        */
        const std::string_view& key() const;

        /*!
            \brief Returns the value.

            \return The value.
        */
        const std::any& value() const;

        /*!
            \brief Returns the index of the preceding step.

            \return The index of the preceding step.
        */
        std::size_t preceding_step() const;

        /*!
            \brief Returns the node cost.

            \return The node cost.
        */
        int node_cost() const;

        /*!
            \brief Returns the path cost.

            \return The path cost.
        */
        int path_cost() const;


    private:
        // variables

        std::string_view m_key;

        std::any m_value;

        std::size_t m_preceding_step;

        int m_node_cost;

        int m_path_cost;
    };


}


#endif
