/**
 *  @file eagine/base/format.inl
 *  @brief Implementation of basic text formatting
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>
#include <iostream>

namespace EAGine {
namespace base {

#if EAGINE_USE_BOOST_LOCALE

#else // EAGINE_USE_BOOST_LOCALE

EAGINE_LIB_FUNC
std::ostream& operator << (std::ostream& out, const format& fmt)
{
	out << fmt._message;
	return out;
}

#endif // !EAGINE_USE_BOOST_LOCALE

} // namespace base
} // namespace EAGine


