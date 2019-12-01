/*!
    \brief A storage.

    Copyright (C) 2019 kaoru
 */

#include <cstdint>
#include <memory>
#include <optional>
#include <sstream>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo/trie/storage.hpp>


namespace
{
    class concrete_storage : public tetengo::trie::storage
    {
    private:
        // virtual functions

        virtual std::int32_t base_at_impl(std::size_t /*base_check_index*/) const override
        {
            return 42;
        }

        virtual void set_base_at_impl(std::size_t /*base_check_index*/, std::int32_t /*value*/) override {}

        virtual std::uint8_t check_at_impl(std::size_t /*base_check_index*/) const override
        {
            return 24;
        }

        virtual void set_check_at_impl(std::size_t /*base_check_index*/, std::uint8_t /*value*/) override {}

        virtual double filling_rate_impl() const override
        {
            return 0.9;
        }

        virtual const std::vector<std::uint32_t>& base_check_array_impl() const override
        {
            static const std::vector<std::uint32_t> singleton(3, 4242);
            return singleton;
        }

        virtual std::optional<std::size_t> mapped_storage_index_impl(std::size_t /*mapped_index*/) const override
        {
            return std::nullopt;
        }

        virtual void add_mapped_storage_index_impl(std::size_t /*mapped_index*/) override {}

        virtual void serialize_impl(std::ostream& /*output_stream*/) const override {}

        std::unique_ptr<storage> clone_impl() const override
        {
            return std::make_unique<concrete_storage>();
        }
    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo)
BOOST_AUTO_TEST_SUITE(trie)
BOOST_AUTO_TEST_SUITE(storage)


BOOST_AUTO_TEST_CASE(construction)
{
    BOOST_TEST_PASSPOINT();

    const concrete_storage storage_{};
}

BOOST_AUTO_TEST_CASE(base_at)
{
    BOOST_TEST_PASSPOINT();

    const concrete_storage storage_{};

    BOOST_TEST(storage_.base_at(24) == 42);
}

BOOST_AUTO_TEST_CASE(set_base_at)
{
    BOOST_TEST_PASSPOINT();

    concrete_storage storage_{};

    storage_.set_base_at(42, 4242);
}

BOOST_AUTO_TEST_CASE(check_at)
{
    BOOST_TEST_PASSPOINT();

    const concrete_storage storage_{};

    BOOST_TEST(storage_.check_at(42) == 24);
}

BOOST_AUTO_TEST_CASE(set_check_at)
{
    BOOST_TEST_PASSPOINT();

    concrete_storage storage_{};

    storage_.set_check_at(24, 124);
}

BOOST_AUTO_TEST_CASE(filling_rate)
{
    BOOST_TEST_PASSPOINT();

    concrete_storage storage_{};

    BOOST_CHECK_CLOSE(storage_.filling_rate(), 0.9, 0.01);
}

BOOST_AUTO_TEST_CASE(base_check_array)
{
    BOOST_TEST_PASSPOINT();

    const concrete_storage storage_{};

    const auto base_check_array = storage_.base_check_array();

    static const std::vector<std::uint32_t> expected(3, 4242);
    BOOST_TEST(base_check_array == expected);
}

BOOST_AUTO_TEST_CASE(mapped_storage_index)
{
    BOOST_TEST_PASSPOINT();

    const concrete_storage storage_{};

    BOOST_TEST(!storage_.mapped_storage_index(42));
}

BOOST_AUTO_TEST_CASE(add_mapped_storage_index)
{
    BOOST_TEST_PASSPOINT();

    concrete_storage storage_{};

    storage_.add_mapped_storage_index(42);
}

BOOST_AUTO_TEST_CASE(serialize)
{
    BOOST_TEST_PASSPOINT();

    const concrete_storage storage_{};

    std::ostringstream output_stream{};
    storage_.serialize(output_stream);
}

BOOST_AUTO_TEST_CASE(clone)
{
    BOOST_TEST_PASSPOINT();

    const concrete_storage storage_{};

    const auto p_clone = storage_.clone();
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
