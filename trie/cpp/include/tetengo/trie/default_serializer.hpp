/*! \file
    \brief A default serializer.

    Copyright (C) 2019 kaoru
*/

#if !defined(TETENGO_TRIE_DEFAULTSERIALIZER_HPP)
#define TETENGO_TRIE_DEFAULTSERIALIZER_HPP

#include <string>
#include <type_traits>


namespace tetengo::trie
{
    /*!
        \brief A default serializer.

        \tparam Object An object type.
    */
    template <typename Object, typename = void>
    class default_serializer;


#if !defined(DOCUMENTATION)
    template <>
    class default_serializer<std::string>
    {
    public:
        // functions

        const std::string& operator()(const std::string& object) const;
    };

    template <typename Char>
    class default_serializer<std::basic_string<Char>>
    {
    public:
        // functions

        std::string operator()(const std::basic_string<Char>& object) const;
    };

    template <typename Integer>
    class default_serializer<Integer, std::enable_if_t<std::is_integral<Integer>::value>>
    {
    public:
        // functions

        std::string operator()(Integer object) const;
    };

#endif
}


#endif
