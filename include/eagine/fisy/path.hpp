/**
 *  @file eagine/fisy/path.hpp
 *  @brief Filesystem path utilities
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_FISY_PATH_1408161723_HPP
#define EAGINE_FISY_PATH_1408161723_HPP

#include <eagine/base/string.hpp>
#include <eagine/base/string_algo.hpp>

namespace eagine {
namespace fisy {

class path
{
public:
	static inline
	base::cstrref separator(void)
	noexcept
	{
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
		return base::cstrref("\\");
#else
		return base::cstrref("/");
#endif
	}

	static inline
	base::cstrref ext_separator(void)
	noexcept
	{
		return base::cstrref(".");
	}

	static inline
	base::cstrref parent(void)
	noexcept
	{
		return base::cstrref("..");
	}

	static inline
	base::cstrref current(void)
	noexcept
	{
		return base::cstrref(".");
	}

	static inline
	base::cstrref dirname(const base::cstrref& p)
	noexcept
	{
		return slice_before_last(p, separator());
	}

	static inline
	base::cstrref basename(const base::cstrref& p)
	noexcept
	{
		return slice_after_last(p, separator());
	}
};

} // namespace fisy
} // namespace eagine

#endif //include guard

