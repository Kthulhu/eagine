/**
 *  @file eagine/base/scope_exit.hpp
 *  @brief On scope exit
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_SCOPE_EXIT_1308281038_HPP
#define EAGINE_BASE_SCOPE_EXIT_1308281038_HPP

#include <eagine/base/functor.hpp>
#include <exception>
#include <cstddef>

namespace eagine {
namespace base {

class on_scope_exit
{
public:
	typedef functor_ref<void(void)> action_type;
private:
	action_type _on_success;
	action_type _on_failure;
public:
	on_scope_exit(
		const action_type& on_success,
		const action_type& on_failure
	) noexcept
	 : _on_success(on_success)
	 , _on_failure(on_failure)
	{ }

	on_scope_exit(
		std::nullptr_t,
		const action_type& on_failure
	) noexcept
	 : _on_failure(on_failure)
	{ }

	on_scope_exit(
		const action_type& on_success,
		std::nullptr_t
	) noexcept
	 : _on_success(on_success)
	{ }

	on_scope_exit(const action_type& action)
	noexcept
	 : on_scope_exit(action, action)
	{ }

	on_scope_exit(const on_scope_exit&) = delete;

	~on_scope_exit(void) noexcept(false)
	{
		if(std::uncaught_exception())
		{
			if(_on_failure) try
			{
				_on_failure();
			}
			catch(...) { }
		}
		else
		{
			if(_on_success)
			{
				_on_success();
			}
		}
	}

	void dismiss_on_success(void)
	{
		_on_success = action_type();
	}

	void dismiss_on_failure(void)
	{
		_on_failure = action_type();
	}

	void dismiss(void)
	{
		dismiss_on_success();
		dismiss_on_failure();
	}

};

} // namespace base
} // namespace eagine

#endif //include guard

