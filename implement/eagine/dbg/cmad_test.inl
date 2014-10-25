/**
 *  @file eagine/dbg/cmad_test.inl
 *  @brief Implementation of cmad_tester
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>
#include <iostream>
#include <utility>
#include <cassert>

namespace EAGine {
namespace dbg {
//------------------------------------------------------------------------------
// cmad_tester::_out
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
std::ostream&
cmad_tester::_out(void) const
{
	assert(_pout != nullptr);
	return *_pout;
}
//------------------------------------------------------------------------------
// cmad_tester - init
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
cmad_tester::cmad_tester(std::ostream& out)
noexcept
 : _pout(&out)
{
	_out()	<< "cmad|"
		<< (void*)this
		<< "|construction"
		<< std::endl;
}
//------------------------------------------------------------------------------
// cmad_tester - move
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
cmad_tester::cmad_tester(cmad_tester&& tmp)
noexcept
 : _pout(tmp._pout)
{
	_out()	<< "cmad|"
		<< (void*)this
		<< "|move from|"
		<< &tmp
		<< std::endl;
}
//------------------------------------------------------------------------------
// cmad_tester - copy
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
cmad_tester::cmad_tester(const cmad_tester& that)
noexcept
 : _pout(that._pout)
{
	_out()	<< "cmad|"
		<< (void*)this
		<< "|copy from|"
		<< &that
		<< std::endl;
}
//------------------------------------------------------------------------------
// cmad_tester - destroy
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
cmad_tester::~cmad_tester(void)
noexcept
{
	_out()	<< "cmad|"
		<< (void*)this
		<< "|destroy|"
		<< std::endl;
}
//------------------------------------------------------------------------------
// cmad_tester - move assign
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
cmad_tester&
cmad_tester::operator = (cmad_tester&& tmp)
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
//------------------------------------------------------------------------------
// cmad_tester - copy assign
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
cmad_tester&
cmad_tester::operator = (const cmad_tester& that)
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
//------------------------------------------------------------------------------
} // namespace dbg
} // namespace EAGine


