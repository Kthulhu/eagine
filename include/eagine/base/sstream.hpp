/**
 *  @file eagine/base/sstream.hpp
 *  @brief String stream
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_SSTREAM_1412032016_HPP
#define EAGINE_BASE_SSTREAM_1412032016_HPP

#include <eagine/base/string.hpp>
#include <sstream>

namespace eagine {
namespace base {

typedef ::std::basic_stringstream<
	string::value_type,
	string::traits_type,
	string::allocator_type
> stringstream;

} // namespace base
} // namespace eagine

#endif //include guard

