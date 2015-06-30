/**
 *  @file eagine/base/deferred.hpp
 *  @brief Deferred function call
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_DEFERRED_1308281038_HPP
#define EAGINE_BASE_DEFERRED_1308281038_HPP

#include <eagine/base/callable.hpp>
#include <exception>

namespace eagine {
namespace base {

class deferred
{
private:
	callable<void(void)> _func;
public:
	deferred(void)
	noexcept
	{ }

	deferred(callable<void(void)>&& func)
	 : _func(std::move(func))
	{ }

	~deferred(void)
	{
		if(is_callable())
		{
			if(!std::uncaught_exception())
			{
				_func();
			}
		}
	}

	bool is_callable(void) const
	{
		return bool(_func);
	}

	void trigger(void)
	{
		if(is_callable())
		{
			callable<void(void)> func = std::move(_func);
			func();
		}
	}

	bool cancel(void)
	{
		if(is_callable())
		{
			_func = callable<void(void)>();
			return true;
		}
		return false;
	}

	explicit
	operator bool (void) const
	noexcept
	{
		return is_callable();
	}

	bool operator!(void) const
	noexcept
	{
		return !is_callable();
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

