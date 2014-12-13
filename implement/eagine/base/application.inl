/**
 *  @file eagine/base/application.inl
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eagine/eagine_config.hpp>
#include <eagine/base/string_algo.hpp>
#include <eagine/fisy/path.hpp>

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
} // namespace base
} // namespace eagine


