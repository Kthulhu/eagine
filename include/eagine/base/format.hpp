/**
 *  @file eagine/base/format.hpp
 *  @brief Basic string formatting
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_FORMAT_1308281038_HPP
#define EAGINE_BASE_FORMAT_1308281038_HPP

#include <eagine/base/locale.hpp>
#include <iosfwd>

namespace EAGine {
namespace base {

#if EAGINE_USE_BOOST_LOCALE

using ::boost::locale::format;

#else // EAGINE_USE_BOOST_LOCALE
class format;

std::ostream& operator << (std::ostream&, const format&);

// No-op implementation of format
class format
{
private:
	text_message _message;
public:
	format(const text_message& message)
	 : _message(message)
	{ }

	template <typename T>
	friend const format& operator % (const format& that, T&&)
	{
		return that;
	}

	template <typename T>
	friend format& operator % (format& that, T&&)
	{
		return that;
	}

	string str(void) const
	{
		return string(_message);
	}

	friend std::ostream& operator << (std::ostream&, const format&);
};
#endif // !EAGINE_USE_BOOST_LOCALE

} // namespace base
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/format.inl>
#endif

#endif //include guard

