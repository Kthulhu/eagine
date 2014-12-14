/**
 *  @file eagine/base/applications.hpp
 *  @brief Monostate object providing info about the application
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_APPLICATION_1408161723_HPP
#define EAGINE_BASE_APPLICATION_1408161723_HPP

#include <eagine/base/string.hpp>
#include <eagine/base/vector.hpp>
#include <eagine/base/program_args.hpp>

namespace eagine {
namespace base {

class application
{
private:
	static
	program_args& _prog_args(void)
	noexcept;

	static
	std::string& _exe_dir_str(void)
	noexcept;

	static
	std::string& _exe_name_str(void)
	noexcept;
public:
	application&
	parse_command_line(const program_args& args);

	static
	const program_args& args(void)
	noexcept
	{
		return _prog_args();
	}

	static
	cstrref dirname(void)
	noexcept
	{
		return cstrref(_exe_dir_str());
	}

	static
	cstrref exename(void)
	noexcept
	{
		return cstrref(_exe_name_str());
	}

	static
	std::string exepath(void);

	static
	string exepath(const allocator<char>& alloc);

	static
	std::string cwd(void);

	static
	string cwd(const allocator<char>& alloc);
};

} // namespace base
} // namespace eagine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/application.inl>
#endif

#endif //include guard

