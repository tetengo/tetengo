/*! \file
    \brief A line counting reader.

    Copyright (C) 2019-2020 kaoru  https://www.tetengo.org/
*/

#if !defined(TETENGO_JSON_LINECOUNTINGREADER_HPP)
#define TETENGO_JSON_LINECOUNTINGREADER_HPP

#include <cstddef>
#include <memory>
#include <string_view>
#include <utility>

#include <boost/operators.hpp>

#include <tetengo/json/reader.hpp>


namespace tetengo::json
{
    /*!
        \brief A location.
    */
    class location : public boost::equality_comparable<location>
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a location.

            \param line         A line.
            \param line_index   A line index. 1-origin.
            \param column_index A column index. 1-origin.
        */
        constexpr location(std::string_view line, std::size_t line_index, std::size_t column_index) :
        m_line{ std::move(line) }, m_line_index{ line_index }, m_column_index{ column_index }
        {}


        // functions

        /*!
            \brief Returns true when one location is equal to another.

            \param one   One location.
            \param another Another location.

            \retval true  When one is equal to another.
            \retval false Otherwise.
        */
        friend constexpr bool operator==(const location& one, const location& another)
        {
            return one.m_line == another.m_line && one.m_line_index == another.m_line_index &&
                   one.m_column_index == another.m_column_index;
        }

        /*!
            \brief Returns the line.

            \return The line.
        */
        [[nodiscard]] constexpr const std::string_view& line() const
        {
            return m_line;
        }

        /*!
            \brief Returns the line index.

            \return The line index.
        */
        [[nodiscard]] constexpr std::size_t line_index() const
        {
            return m_line_index;
        }

        /*!
            \brief Returns the column index.

            \return The column index.
        */
        [[nodiscard]] constexpr std::size_t column_index() const
        {
            return m_column_index;
        }


    private:
        // variables

        std::string_view m_line;

        std::size_t m_line_index;

        std::size_t m_column_index;
    };


    /*!
        \brief A line counting reader.
    */
    class line_counting_reader : public reader
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a line counting reader.

            \param p_base_reader A unique pointer to a base reader.

            \throw std::invalid_argument When p_base_reader is nullptr.
        */
        explicit line_counting_reader(std::unique_ptr<reader>&& p_base_reader);

        /*!
            \brief Destroys the line counting reader.
        */
        virtual ~line_counting_reader();


        // functions

        /*!
            Returns the location.

            \return The location.

            \throw std::logic_error When current position is beyond the termination point.
        */
        [[nodiscard]] location get_location() const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool has_next_impl() const override;

        virtual char peek_impl() const override;

        virtual void next_impl() override;
    };


}


#endif
