/*! \file
    \brief An entry.

    Copyright (C) 2019-2021 kaoru  https://www.tetengo.org/
*/

#include <any>
#include <climits>
#include <iterator>
#include <string>

#include <boost/preprocessor.hpp>
#include <boost/scope_exit.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo/lattice/entry.h>
#include <tetengo/lattice/entry.hpp>
#include <tetengo/lattice/stringView.h>


namespace
{
    constexpr char operator""_c(const unsigned long long int uc)
    {
        return static_cast<char>(uc);
    }

    const std::string key_mizuho{ 0xE3_c, 0x81_c, 0xBF_c, 0xE3_c, 0x81_c, 0x9A_c, 0xE3_c, 0x81_c, 0xBB_c };

    const std::string surface_mizuho{ 0xE7_c, 0x91_c, 0x9E_c, 0xE7_c, 0xA9_c, 0x82_c };


}


BOOST_AUTO_TEST_SUITE(test_tetengo)
BOOST_AUTO_TEST_SUITE(lattice)
BOOST_AUTO_TEST_SUITE(entry)


BOOST_AUTO_TEST_CASE(bos_eos)
{
    BOOST_TEST_PASSPOINT();

    {
        static auto& bos_eos_ = tetengo::lattice::entry::bos_eos();

        BOOST_TEST(std::empty(bos_eos_.key()));
        BOOST_TEST(!bos_eos_.value().has_value());
        BOOST_TEST(bos_eos_.cost() == 0);
    }

    {
        static auto* const p_bos_eos = tetengo_lattice_entry_bosEos();

        BOOST_TEST(!p_bos_eos->key.p_head);
        BOOST_TEST(p_bos_eos->key.length == 0U);
        BOOST_TEST(!tetengo_lattice_entry_valueOf(p_bos_eos->value_handle));
        BOOST_TEST(p_bos_eos->cost == 0);
    }
}

BOOST_AUTO_TEST_CASE(construction)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::entry      entry1{ key_mizuho, surface_mizuho, 42 };
        const tetengo::lattice::entry_view view{ entry1 };
        const tetengo::lattice::entry      entry2{ view };
    }

    {
        const tetengo_lattice_stringView_t key{ key_mizuho.c_str(), key_mizuho.length() };
        const auto* const                  p_entry = tetengo_lattice_entry_create(&key, &surface_mizuho, 42);
        BOOST_SCOPE_EXIT(p_entry)
        {
            tetengo_lattice_entry_destroy(p_entry);
        }
        BOOST_SCOPE_EXIT_END;
        BOOST_TEST(p_entry);
    }
    {
        const auto* const p_entry = tetengo_lattice_entry_create(nullptr, &surface_mizuho, 42);
        BOOST_TEST(!p_entry);
    }
    {
        const std::any                    value{ reinterpret_cast<const void*>(&surface_mizuho) };
        const tetengo_lattice_entryView_t view{ { key_mizuho.c_str(), key_mizuho.length() },
                                                reinterpret_cast<tetengo_lattice_entry_valueHandle_t>(&value),
                                                42 };
        const auto* const                 p_entry = tetengo_lattice_entry_createWithView(&view);
        BOOST_SCOPE_EXIT(p_entry)
        {
            tetengo_lattice_entry_destroy(p_entry);
        }
        BOOST_SCOPE_EXIT_END;
        BOOST_TEST(p_entry);
    }
    {
        const auto* const p_entry = tetengo_lattice_entry_createWithView(nullptr);
        BOOST_TEST(!p_entry);
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
        const tetengo_lattice_stringView_t key{ key_mizuho.c_str(), key_mizuho.length() };
        const auto* const                  p_entry = tetengo_lattice_entry_create(&key, &surface_mizuho, 42);
        BOOST_SCOPE_EXIT(p_entry)
        {
            tetengo_lattice_entry_destroy(p_entry);
        }
        BOOST_SCOPE_EXIT_END;

        const auto* const p_key = tetengo_lattice_entry_key(p_entry);
        BOOST_TEST_REQUIRE(p_key);
        BOOST_TEST(p_key->p_head == key_mizuho.c_str());
        BOOST_TEST(p_key->length == key_mizuho.length());
    }
    {
        const auto* const p_key = tetengo_lattice_entry_key(nullptr);
        BOOST_TEST(!p_key);
    }
    {
        const std::any                    value{ reinterpret_cast<const void*>(&surface_mizuho) };
        const tetengo_lattice_entryView_t entry{ { key_mizuho.c_str(), key_mizuho.length() },
                                                 reinterpret_cast<tetengo_lattice_entry_valueHandle_t>(&value),
                                                 42 };

        BOOST_TEST(entry.key.p_head == key_mizuho.c_str());
        BOOST_TEST(entry.key.length == key_mizuho.length());
    }
}

BOOST_AUTO_TEST_CASE(value)
{
    BOOST_TEST_PASSPOINT();

    {
        const tetengo::lattice::entry entry_{ key_mizuho, surface_mizuho, 42 };

        BOOST_TEST(std::any_cast<std::string>(entry_.value()) == surface_mizuho);
    }

    {
        const tetengo_lattice_stringView_t key{ key_mizuho.c_str(), key_mizuho.length() };
        const auto* const                  p_entry = tetengo_lattice_entry_create(&key, &surface_mizuho, 42);
        BOOST_SCOPE_EXIT(p_entry)
        {
            tetengo_lattice_entry_destroy(p_entry);
        }
        BOOST_SCOPE_EXIT_END;

        const auto* const p_value = tetengo_lattice_entry_value(p_entry);
        BOOST_TEST_REQUIRE(p_value);
        BOOST_TEST(reinterpret_cast<const std::string*>(p_value) == &surface_mizuho);
    }
    {
        const auto* const p_value = tetengo_lattice_entry_value(nullptr);
        BOOST_TEST(!p_value);
    }
    {
        const std::any                    value{ reinterpret_cast<const void*>(&surface_mizuho) };
        const tetengo_lattice_entryView_t entry{ { key_mizuho.c_str(), key_mizuho.length() },
                                                 reinterpret_cast<tetengo_lattice_entry_valueHandle_t>(&value),
                                                 42 };

        BOOST_TEST(
            reinterpret_cast<const std::string*>(tetengo_lattice_entry_valueOf(entry.value_handle)) == &surface_mizuho);
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
        const tetengo_lattice_stringView_t key{ key_mizuho.c_str(), key_mizuho.length() };
        const auto* const                  p_entry = tetengo_lattice_entry_create(&key, &surface_mizuho, 42);
        BOOST_SCOPE_EXIT(p_entry)
        {
            tetengo_lattice_entry_destroy(p_entry);
        }
        BOOST_SCOPE_EXIT_END;

        const auto cost = tetengo_lattice_entry_cost(p_entry);
        BOOST_TEST(cost == 42);
    }
    {
        const auto cost = tetengo_lattice_entry_cost(nullptr);
        BOOST_TEST(cost == INT_MAX);
    }
    {
        const std::any                    value{ reinterpret_cast<const void*>(&surface_mizuho) };
        const tetengo_lattice_entryView_t entry{ { key_mizuho.c_str(), key_mizuho.length() },
                                                 reinterpret_cast<tetengo_lattice_entry_valueHandle_t>(&value),
                                                 42 };

        BOOST_TEST(entry.cost == 42);
    }
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
