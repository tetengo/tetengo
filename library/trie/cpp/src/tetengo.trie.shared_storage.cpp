/*! \file
    \brief A shared storage.

    Copyright (C) 2019-2022 kaoru  https://www.tetengo.org/
*/

#include <any>
#include <cstddef> // IWYU pragma: keep
#include <cstdint>
#include <istream>
#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo/trie/memory_storage.hpp>
#include <tetengo/trie/shared_storage.hpp>
#include <tetengo/trie/storage.hpp>
#include <tetengo/trie/value_serializer.hpp> // IWYU pragma: keep


namespace tetengo::trie
{
    class shared_storage::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        impl() : m_p_entity{ std::make_shared<memory_storage>() } {};

        impl(std::istream& input_stream, const value_deserializer& value_deserializer_) :
        m_p_entity{ std::make_shared<memory_storage>(input_stream, value_deserializer_) } {};


        // functions

        std::size_t base_check_size_impl() const
        {
            return m_p_entity->base_check_size();
        }

        std::int32_t base_at_impl(const std::size_t base_check_index) const
        {
            return m_p_entity->base_at(base_check_index);
        }

        void set_base_at_impl(const std::size_t base_check_index, const std::int32_t base)
        {
            m_p_entity->set_base_at(base_check_index, base);
        }

        std::uint8_t check_at_impl(const std::size_t base_check_index) const
        {
            return m_p_entity->check_at(base_check_index);
        }

        void set_check_at_impl(const std::size_t base_check_index, const std::uint8_t check)
        {
            m_p_entity->set_check_at(base_check_index, check);
        }

        std::size_t value_count_impl() const
        {
            return m_p_entity->value_count();
        }

        const std::any* value_at_impl(const std::size_t value_index) const
        {
            return m_p_entity->value_at(value_index);
        }

        void add_value_at_impl(const std::size_t value_index, std::any value)
        {
            m_p_entity->add_value_at(value_index, std::move(value));
        }

        double filling_rate_impl() const
        {
            return m_p_entity->filling_rate();
        }

        void serialize_impl(std::ostream& output_stream, const value_serializer& value_serializer_) const
        {
            m_p_entity->serialize(output_stream, value_serializer_);
        }

        std::unique_ptr<storage> clone_impl() const
        {
            auto p_clone = std::make_unique<shared_storage>();
            p_clone->m_p_impl->m_p_entity = m_p_entity;
            return p_clone;
        }


    private:
        // variables

        std::shared_ptr<storage> m_p_entity;
    };


    shared_storage::shared_storage() : m_p_impl{ std::make_unique<impl>() } {}

    shared_storage::shared_storage(std::istream& input_stream, const value_deserializer& value_deserializer_) :
    m_p_impl{ std::make_unique<impl>(input_stream, value_deserializer_) }
    {}

    shared_storage::~shared_storage() = default;

    std::size_t shared_storage::base_check_size_impl() const
    {
        return m_p_impl->base_check_size_impl();
    }

    std::int32_t shared_storage::base_at_impl(const std::size_t base_check_index) const
    {
        return m_p_impl->base_at_impl(base_check_index);
    }

    void shared_storage::set_base_at_impl(const std::size_t base_check_index, const std::int32_t base)
    {
        m_p_impl->set_base_at_impl(base_check_index, base);
    }

    std::uint8_t shared_storage::check_at_impl(const std::size_t base_check_index) const
    {
        return m_p_impl->check_at_impl(base_check_index);
    }

    void shared_storage::set_check_at_impl(const std::size_t base_check_index, const std::uint8_t check)
    {
        m_p_impl->set_check_at_impl(base_check_index, check);
    }

    std::size_t shared_storage::value_count_impl() const
    {
        return m_p_impl->value_count_impl();
    }

    const std::any* shared_storage::value_at_impl(const std::size_t value_index) const
    {
        return m_p_impl->value_at_impl(value_index);
    }

    void shared_storage::add_value_at_impl(const std::size_t value_index, std::any value)
    {
        return m_p_impl->add_value_at_impl(value_index, std::move(value));
    }

    double shared_storage::filling_rate_impl() const
    {
        return m_p_impl->filling_rate_impl();
    }

    void shared_storage::serialize_impl(std::ostream& output_stream, const value_serializer& value_serializer_) const
    {
        m_p_impl->serialize_impl(output_stream, value_serializer_);
    }

    std::unique_ptr<storage> shared_storage::clone_impl() const
    {
        return m_p_impl->clone_impl();
    }


}
