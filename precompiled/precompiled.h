/*! \file
    \brief The precompiled header.

    This file is generated by kogyan/tool/make_precompiled_h.py.

    Copyright (C) 2019-2021 kaoru  https://www.tetengo.org/
*/

#if !defined(PRECOMPILED_H)
#define PRECOMPILED_H


/* C Standard Library */
#include <assert.h>
#include <locale.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#if defined(__cplusplus)

// C++ Standard Library
#include <algorithm>
#include <any>
#include <cassert>
#include <cctype>
#include <clocale>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <optional>
#include <ostream>
#include <queue>
#include <regex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/container_hash/hash.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/core/pointer_traits.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/scope_exit.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/stl_interfaces/iterator_interface.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#endif


// Platform Dependent
#if defined(_MSC_VER)
#if defined(__cplusplus)
#define NOMINMAX
#include <Windows.h>
#endif
#else
#include <errno.h>
#include <iconv.h>
#endif


#endif
