/**
 *  @file eagine/base/locale.inl
 *  @brief Implementation of basic localization/translation support.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>
#include <iostream>

namespace EAGine {
namespace base {

#if EAGINE_USE_BOOST_LOCALE

#else // EAGINE_USE_BOOST_LOCALE

//------------------------------------------------------------------------------
// text_message operator <<
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
std::ostream& operator << (std::ostream& out, const text_message& message)
{
	out << message._msg;
	return out;
}
//------------------------------------------------------------------------------
// translate
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
text_message translate(const char* str)
{
	return text_message(str);
}
//------------------------------------------------------------------------------
// translate
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
text_message translate(const char* /*context*/, const char* str)
{
	return text_message(str);
}
//------------------------------------------------------------------------------
// translate
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
text_message translate(const char* single, const char* plural, int n)
{
	return text_message(n==1?single:plural);
}
//------------------------------------------------------------------------------
// translate
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
text_message translate(
	const char* /*context*/,
	const char* single,
	const char* plural,
	int n
)
{
	return text_message(n==1?single:plural);
}
//------------------------------------------------------------------------------

#endif // !EAGINE_USE_BOOST_LOCALE

} // namespace base
} // namespace EAGine


