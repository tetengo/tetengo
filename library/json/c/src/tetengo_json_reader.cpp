/*! \file
    \brief A reader.

    Copyright (C) 2019-2025 kaoru  https://www.tetengo.org/
*/

#include <fstream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include <stddef.h>

#include <boost/preprocessor.hpp>
#include <boost/scope_exit.hpp>

#include <tetengo/json/comment_removing_reader.hpp>
#include <tetengo/json/file_location.hpp>
#include <tetengo/json/line_counting_reader.hpp>
#include <tetengo/json/reader.h>
#include <tetengo/json/reader.hpp>
#include <tetengo/json/stream_reader.hpp>

#include "tetengo_json_reader.hpp"


size_t tetengo_json_reader_streamReaderDefaultBufferCapacity()
{
    return tetengo::json::stream_reader::default_buffer_capacity();
}

tetengo_json_reader_t* tetengo_json_reader_createStreamReader(const char* const file_path, const size_t buffer_capacity)
{
    try
    {
        if (!file_path)
        {
            throw std::invalid_argument{ "file_path is NULL." };
        }
        auto p_stream = std::make_unique<std::ifstream>(file_path);
        if (!*p_stream)
        {
            throw std::runtime_error{ "Can't open the file." };
        }

        auto p_cpp_reader = std::make_unique<tetengo::json::stream_reader>(std::move(p_stream), buffer_capacity);

        auto p_instance = std::make_unique<tetengo_json_reader_t>(std::move(p_cpp_reader));
        return p_instance.release();
    }
    catch (...)
    {
        return nullptr;
    }
}

tetengo_json_reader_t* tetengo_json_reader_createCommentRemovingReader(
    tetengo_json_reader_t* const p_base_reader,
    const char* const            single_line_begin)
{
    try
    {
        BOOST_SCOPE_EXIT(p_base_reader)
        {
            tetengo_json_reader_destroy(p_base_reader);
        }
        BOOST_SCOPE_EXIT_END;

        if (!p_base_reader)
        {
            throw std::invalid_argument{ "p_base_reader is NULL." };
        }
        if (!single_line_begin)
        {
            throw std::invalid_argument{ "single_line_begin is NULL." };
        }
        if (std::empty(std::string_view{ single_line_begin }))
        {
            throw std::invalid_argument{ "single_line_begin is empty." };
        }

        auto p_cpp_reader = std::make_unique<tetengo::json::comment_removing_reader>(
            std::move(p_base_reader->move_cpp_reader()), single_line_begin);

        auto p_instance = std::make_unique<tetengo_json_reader_t>(std::move(p_cpp_reader));
        return p_instance.release();
    }
    catch (...)
    {
        return nullptr;
    }
}

tetengo_json_reader_t* tetengo_json_reader_createLineCountingReader(tetengo_json_reader_t* const p_base_reader)
{
    try
    {
        BOOST_SCOPE_EXIT(p_base_reader)
        {
            tetengo_json_reader_destroy(p_base_reader);
        }
        BOOST_SCOPE_EXIT_END;

        if (!p_base_reader)
        {
            throw std::invalid_argument{ "p_base_reader is NULL." };
        }

        auto p_cpp_reader =
            std::make_unique<tetengo::json::line_counting_reader>(std::move(p_base_reader->move_cpp_reader()));

        auto p_instance = std::make_unique<tetengo_json_reader_t>(std::move(p_cpp_reader));
        return p_instance.release();
    }
    catch (...)
    {
        return nullptr;
    }
}

void tetengo_json_reader_destroy(const tetengo_json_reader_t* const p_reader)
{
    try
    {
        const std::unique_ptr<const tetengo_json_reader_t> p_instance{ p_reader };
    }
    catch (...)
    {}
}

bool tetengo_json_reader_getLocation(
    const tetengo_json_reader_t* const p_line_counting_reader,
    tetengo_json_location_t* const     p_location)
{
    try
    {
        if (!p_line_counting_reader)
        {
            throw std::invalid_argument{ "p_line_counting_reader is NULL." };
        }
        if (!p_location)
        {
            throw std::invalid_argument{ "p_location is NULL." };
        }

        const auto* const p_cpp_line_counting_reader =
            dynamic_cast<const tetengo::json::line_counting_reader*>(&p_line_counting_reader->cpp_reader());
        if (!p_cpp_line_counting_reader)
        {
            throw std::invalid_argument{ "p_line_counting_reader is not a line counting reader." };
        }

        const auto& cpp_location = p_cpp_line_counting_reader->get_location();
        p_location->line = cpp_location.line().c_str();
        p_location->line_length = cpp_location.line().length();
        p_location->line_index = cpp_location.line_index();
        p_location->column_index = cpp_location.column_index();

        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool tetengo_json_reader_hasNext(const tetengo_json_reader_t* const p_reader)
{
    try
    {
        if (!p_reader)
        {
            throw std::invalid_argument{ "p_reader is NULL." };
        }

        return p_reader->cpp_reader().has_next();
    }
    catch (...)
    {
        return false;
    }
}

char tetengo_json_reader_peek(const tetengo_json_reader_t* const p_reader)
{
    try
    {
        if (!p_reader)
        {
            throw std::invalid_argument{ "p_reader is NULL." };
        }

        return p_reader->cpp_reader().peek();
    }
    catch (...)
    {
        return 0;
    }
}

void tetengo_json_reader_next(tetengo_json_reader_t* const p_reader)
{
    try
    {
        if (!p_reader)
        {
            throw std::invalid_argument{ "p_reader is NULL." };
        }

        p_reader->cpp_reader().next();
    }
    catch (...)
    {}
}

const tetengo_json_reader_t* tetengo_json_reader_baseReader(const tetengo_json_reader_t* const p_reader)
{
    try
    {
        if (!p_reader)
        {
            throw std::invalid_argument{ "p_reader is NULL." };
        }

        p_reader->p_base_reader_placeholder =
            std::make_unique<tetengo_json_reader_t>(&p_reader->cpp_reader().base_reader());
        return std::to_address(p_reader->p_base_reader_placeholder);
    }
    catch (...)
    {
        return NULL;
    }
}
