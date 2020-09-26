/*! \file
    \brief An east Asian character width.

    Copyright (C) 2019-2020 kaoru  https://www.tetengo.org/
*/

#include <cstddef>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo/cli/east_asian_character_width.hpp>


namespace tetengo::cli
{
    class east_asian_character_width::impl : private boost::noncopyable
    {
    public:
        // static functions

        static const east_asian_character_width& instance()
        {
            static const east_asian_character_width singleton{};
            return singleton;
        }


        // functions

        std::size_t width_of_impl(const char32_t previous_code_point, const char32_t code_point) const
        {
            const auto class_ = class_of(code_point);
            if (previous_code_point != 0 && is_combining(class_))
            {
                return 0;
            }
            const auto absolute_class = class_ < 0 ? -class_ : class_;
            switch (absolute_class)
            {
            case 1: // A
            case 2: // F
            case 6: // W
                return 2;
            default:
                return 1;
            }
        }
    };


    const east_asian_character_width& east_asian_character_width::instance()
    {
        return impl::instance();
    }

    east_asian_character_width::~east_asian_character_width() = default;

    east_asian_character_width::east_asian_character_width() : m_p_impl{ std::make_unique<impl>() } {}

    std::size_t
    east_asian_character_width::width_of_impl(const char32_t previous_code_point, const char32_t code_point) const
    {
        return m_p_impl->width_of_impl(previous_code_point, code_point);
    }


}
