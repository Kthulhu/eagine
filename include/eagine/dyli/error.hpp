/**
 *  @file eagine/dyli/error.hpp
 *  @brief Dynamically linked library errors
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_DYLI_ERROR_1408161720_HPP
#define EAGINE_DYLI_ERROR_1408161720_HPP

#include <eagine/base/string.hpp>
#include <eagine/base/error.hpp>

namespace eagine {
namespace dyli {

class not_loaded
 : public base::runtime_error
{
public:
	not_loaded(const base::string& msg)
	 : base::runtime_error(msg)
	{ }
};

} // namespace dyli
} // namespace eagine

#endif //include guard

