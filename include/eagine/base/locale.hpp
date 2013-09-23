/**
 *  @file eagine/base/locale.hpp
 *  @brief Basic localization/translation support.
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_LOCALE_1308281038_HPP
#define EAGINE_BASE_LOCALE_1308281038_HPP

#include <eagine/eagine_config.hpp>
#include <eagine/base/string.hpp>

#if EAGINE_USE_BOOST_LOCALE
#include <boost/locale.hpp>
#else
#include <iosfwd>
#endif

namespace EAGine {
namespace base {

#if EAGINE_USE_BOOST_LOCALE

typedef ::boost::locale::basic_message<char> text_message;
using ::boost::locale::translate;

#else // EAGINE_USE_BOOST_LOCALE
class text_message;

text_message translate(const char* str);
text_message translate(const char* context, const char* str);
text_message translate(const char* single, const char* plural, int n);
text_message translate(
	const char* context,
	const char* single,
	const char* plural,
	int n
);

std::ostream& operator << (std::ostream&, const text_message&);

class text_message
{
private:
	const char* _msg;
public:
	text_message(void)
	 : _msg("")
	{ }

	text_message(const char* msg)
	 : _msg(msg)
	{ }

	friend std::ostream& operator << (std::ostream&, const text_message&);

	explicit operator string (void) const
	{
		return string(_msg);
	}
};
#endif // !EAGINE_USE_BOOST_LOCALE

} // namespace base
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/locale.inl>
#endif

#endif //include guard

