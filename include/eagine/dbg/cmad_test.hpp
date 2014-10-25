/**
 *  @file eagine/dbg/cmad_test.hpp
 *  @brief Utility class logging copy-move-assignment-destroy operations
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_DBG_CMAD_TEST_1308281038_HPP
#define EAGINE_DBG_CMAD_TEST_1308281038_HPP

#include <iosfwd>

namespace EAGine {
namespace dbg {

// copy-move-assign-destroy test
struct cmad_tester
{
	std::ostream* _pout;

	std::ostream& _out(void) const;

	cmad_tester(std::ostream& out)
	noexcept;

	cmad_tester(void)
	noexcept
	 : cmad_tester(std::cout)
	{ }

	cmad_tester(cmad_tester&& tmp)
	noexcept;

	cmad_tester(const cmad_tester& that)
	noexcept;

	~cmad_tester(void)
	noexcept
	{
		_out()	<< "cmad|"
			<< (void*)this
			<< "|destroy|"
			<< std::endl;
	}

	cmad_tester& operator = (cmad_tester&& tmp)
	noexcept
	{
		_pout = tmp._pout;
		_out()	<< "cmad|"
			<< (void*)this
			<< "|move assign from|"
			<< &tmp
			<< std::endl;
		return *this;
	}

	cmad_tester& operator = (const cmad_tester& that)
	noexcept
	{
		_pout = that._pout;
		_out()	<< "cmad|"
			<< (void*)this
			<< "|copy assign from|"
			<< &that
			<< std::endl;
		return *this;
	}
};

} // namespace dbg
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/dbg/cmad_tester.inl>
#endif

#endif //include guard

