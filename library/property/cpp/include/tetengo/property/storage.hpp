/*! \file
    \brief A storage.

    Copyright (C) 2019-2024 kaoru  https://www.tetengo.org/
*/

#if !defined(TETENGO_PROPERTY_STORAGE_HPP)
#define TETENGO_PROPERTY_STORAGE_HPP

#include <cstdint>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>

#include <boost/core/noncopyable.hpp>


namespace tetengo::property
{
    /*!
        \brief A storage.
    */
    class storage : private boost::noncopyable
    {
    public:
        // types

        //! The value map type.
        using value_map_type = std::unordered_map<std::string, std::variant<bool, std::uint32_t, std::string>>;


        // constructors and destructor

        /*!
            \brief Destroys the storage.
        */
        virtual ~storage();


        // functions

        /*!
            \brief Returns the value in a boolean.

            \param key A key.

            \return The value. Or std::nullopt when no such key.
        */
        [[nodiscard]] std::optional<bool> get_bool(const std::filesystem::path& key) const;

        /*!
            \brief Sets a value in a boolean.

            \param key   A key.
            \param value A value.
        */
        void set_bool(const std::filesystem::path& key, bool value);

        /*!
            \brief Returns the value in an unsigned 32-bit integer.

            \param key A key.

            \return The value. Or std::nullopt when no such key.
        */
        [[nodiscard]] std::optional<std::uint32_t> get_uint32(const std::filesystem::path& key) const;

        /*!
            \brief Sets a value in an unsigned 32-bit integer.

            \param key   A key.
            \param value A value.
        */
        void set_uint32(const std::filesystem::path& key, std::uint32_t value);

        /*!
            \brief Returns the value in a string.

            \param key A key.

            \return The value. Or std::nullopt when no such key.
        */
        [[nodiscard]] std::optional<std::string> get_string(const std::filesystem::path& key) const;

        /*!
            \brief Sets a value in a string.

            \param key   A key.
            \param value A value.
        */
        void set_string(const std::filesystem::path& key, const std::string& value);

        /*!
            \brief Saves the values.
        */
        void save() const;


    protected:
        // constructors

        /*!
            \brief Creates a storage.

            \param value_map A value map.
        */
        explicit storage(value_map_type value_map);


        // functions

        /*!
            \brief Returns the value map.

            \return The value map.
        */
        [[nodiscard]] const value_map_type& value_map() const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual std::optional<bool> get_bool_impl(const std::filesystem::path& key) const;

        virtual void set_bool_impl(const std::filesystem::path& key, bool value);

        virtual std::optional<std::uint32_t> get_uint32_impl(const std::filesystem::path& key) const;

        virtual void set_uint32_impl(const std::filesystem::path& key, std::uint32_t value);

        virtual std::optional<std::string> get_string_impl(const std::filesystem::path& key) const;

        virtual void set_string_impl(const std::filesystem::path& key, const std::string& value);

        virtual void save_impl() const = 0;
    };


    /*!
        \brief A storage loader.
    */
    class storage_loader : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Destroys the storage loader.
        */
        virtual ~storage_loader();


        // functions

        /*!
            \brief Loads a storage.

            \param path A path.

            \return A unique pointer to a storage. Or nullptr on error.
        */
        [[nodiscard]] std::unique_ptr<storage> load(const std::filesystem::path& path) const;


    private:
        // virtual functions

        virtual std::unique_ptr<storage> load_impl(const std::filesystem::path& path) const = 0;
    };


}


#endif
