/**
 *  @file eagine/base/application.inl
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eagine/eagine_config.hpp>
#include <eagine/base/string_algo.hpp>
#include <eagine/base/error.hpp>
#include <eagine/base/locale.hpp>
#include <eagine/fisy/path.hpp>

// TODO other platforms
#if defined(__unix__)
#include <cerrno>
#include <unistd.h>

#if defined(__linux__)
#include <linux/limits.h>
#endif

#endif

namespace eagine {
namespace base {
//------------------------------------------------------------------------------
// application::_prog_args
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
program_args&
application::_prog_args(void)
noexcept
{
	static program_args pa;
	return pa;
}
//------------------------------------------------------------------------------
// application::_exe_dir_str
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
std::string&
application::_exe_dir_str(void)
noexcept
{
	static std::string s;
	return s;
}
//------------------------------------------------------------------------------
// application::_exe_name_str
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
std::string&
application::_exe_name_str(void)
noexcept
{
	static std::string s;
	return s;
}
//------------------------------------------------------------------------------
// application::parse_command_line
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
application&
application::parse_command_line(const program_args& prog_args)
{
	_prog_args() = prog_args;

	vector<cstrref> exe_path;
	split_into(exe_path, args().command(), fisy::path::separator());

	_exe_name_str() = exe_path.back().std_str();
	exe_path.pop_back();

	_exe_dir_str() = join<std::string>(exe_path, fisy::path::separator());

	return *this;
}
//------------------------------------------------------------------------------
#ifdef __unix__
#ifdef __linux__
static const std::size_t _application_path_size = PATH_MAX;
#else
static const std::size_t _application_path_size = 4096;
#endif
//------------------------------------------------------------------------------
static inline
const char*
_application_get_cwd(char* b, std::size_t n)
{
	if(::getcwd(b, n-1) == nullptr)
	{
		throw system_error(
			errno,
			std::system_category(),
			translate("Error getting current working directory")
		);
	}
	return b;
}
//------------------------------------------------------------------------------
static inline
const char*
_application_get_exepath(char* b, std::size_t n)
{
	if(::readlink("/proc/self/exe", b, n) < 0)
	{
		throw system_error(
			errno,
			std::system_category(),
			translate("Error getting application executable path")
		);
	}
	return b;
}
//------------------------------------------------------------------------------
#else
#error application::cwd not supported on this platform
#endif
//------------------------------------------------------------------------------
// application::exepath
//------------------------------------------------------------------------------
std::string
application::exepath(void)
{
	char buffer[_application_path_size];
	return std::string(_application_get_exepath(
		buffer,
		_application_path_size
	));
}
//------------------------------------------------------------------------------
// application::exepath
//------------------------------------------------------------------------------
string
application::exepath(const allocator<char>& alloc)
{
	char buffer[_application_path_size];
	return string(_application_get_exepath(
		buffer,
		_application_path_size
	), alloc);
}
//------------------------------------------------------------------------------
// application::cwd
//------------------------------------------------------------------------------
std::string
application::cwd(void)
{
	char buffer[_application_path_size];
	return std::string(_application_get_cwd(
		buffer,
		_application_path_size
	));
}
//------------------------------------------------------------------------------
// application::cwd
//------------------------------------------------------------------------------
string
application::cwd(const allocator<char>& alloc)
{
	char buffer[_application_path_size];
	return string(_application_get_cwd(
		buffer,
		_application_path_size
	), alloc);
}
//------------------------------------------------------------------------------
} // namespace base
} // namespace eagine


