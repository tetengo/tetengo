/*! \file
    \brief A dictionary building tool.

    Copyright (C) 2019-2020 kaoru
 */

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <exception>
#include <fstream> // IWYU pragma: keep
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/format.hpp>


namespace
{
    std::vector<std::string_view> split(const std::string_view& string, const char delimiter)
    {
        std::vector<std::string_view> elements{};

        auto first = static_cast<std::size_t>(0);
        for (;;)
        {
            if (first < string.length() && string[first] == '"')
            {
                const auto last = string.find_first_of('"', first + 1);
                if (last == std::string_view::npos)
                {
                    elements.push_back(string.substr(first + 1));
                    break;
                }
                elements.push_back(string.substr(first + 1, last - first - 1));
                assert(string[last + 1] == delimiter);
                first = last + 2;
            }
            else
            {
                const auto last = string.find_first_of(delimiter, first);
                if (last == std::string_view::npos)
                {
                    elements.push_back(string.substr(first));
                    break;
                }
                elements.push_back(string.substr(first, last - first));
                first = last + 1;
            }
        }

        return elements;
    }

    void insert_word_offset_to_map(
        const std::string_view&                                    key,
        const std::size_t                                          offset,
        std::unordered_map<std::string, std::vector<std::size_t>>& map)
    {
        auto i_value = map.find(std::string{ key });
        if (i_value == map.end())
        {
            i_value = map.insert(std::make_pair(key, std::vector<std::size_t>{})).first;
        }
        assert(i_value != map.end());

        if (std::find(i_value->second.begin(), i_value->second.end(), offset) != i_value->second.end())
        {
            return;
        }
        i_value->second.push_back(offset);
    }

    std::vector<std::pair<std::string_view, const std::vector<size_t>&>>
    map_to_vector(const std::unordered_map<std::string, std::vector<std::size_t>>& map)
    {
        std::vector<std::pair<std::string_view, const std::vector<size_t>&>> vector{};
        vector.reserve(map.size());

        for (const auto& value: map)
        {
            vector.emplace_back(value.first, value.second);
        }

        return vector;
    }


}


int main(const int argc, char** const argv)
{
    try
    {
        if (argc <= 1)
        {
            std::cout << "Usage: make_dict UniDic_lex.csv" << std::endl;
            return 0;
        }

        std::ifstream stream{ argv[1] };
        if (!stream)
        {
            throw std::ios_base::failure{ "Can't open the input file." };
        }

        std::unordered_map<std::string, std::vector<std::size_t>> word_offset_map{};

        auto line_head = static_cast<std::size_t>(0);
        for (auto i = static_cast<std::size_t>(0); stream; ++i)
        {
            std::string line{};
            std::getline(stream, line);
            const auto line_tail = line_head + line.length() + 1;
            if (line.empty())
            {
                line_head = line_tail;
                continue;
            }
            const auto elements = split(line, ',');
            if (elements.size() != 33)
            {
                std::cerr << boost::format{ "%8d: %s" } % i % elements[0] << "    \n" << std::flush;
                throw std::runtime_error{ "Invalid UniDic lex.csv format." };
            }

            insert_word_offset_to_map(elements[12], line_tail, word_offset_map);
            insert_word_offset_to_map(elements[24], line_tail, word_offset_map);

            if (i % 10000 == 0)
            {
                std::cerr << boost::format{ "%8d: %s" } % i % elements[0] << "    \r" << std::flush;
            }

            line_head = line_tail;
        }
        std::cerr << "Done.        " << std::endl;

        const auto word_offset_vector = map_to_vector(word_offset_map);

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Error: unknown error." << std::endl;
        return 1;
    }
}
