/**
 *  @file eagine/base/guid.hpp
 *  @brief Declaration of a globaly unique identifier
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_GUID_1308281038_HPP
#define EAGINE_BASE_GUID_1308281038_HPP

#include <eagine/base/string.hpp>
#include <boost/uuid/uuid.hpp>
#include <cstddef>
#include <iosfwd>

namespace EAGine {
namespace base {

/// Universaly/globally-unique identifier
struct guid
 : ::boost::uuids::uuid
{
	guid(const ::boost::uuids::uuid&);

	/// guid is DefaultConstructible
	guid(void);

	/// Constructs a GUID from a string
	guid(const cstrref& str);

	/// Constructs a nil GUID value
	guid(std::nullptr_t);

	/// Returns a string representing the GUID
	string to_string(void) const;

	/// Returns a lim_string representing the GUID
	lim_string<36> to_lim_string(void) const;

	/// Returns true if str is a valid GUID string
	static bool is_valid_string(const cstrref& str);

	/// Constructs a nil GUID value
	static guid nil(void);
};

std::ostream& operator << (std::ostream& out, const guid&);

} // namespace base
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/guid.inl>
#endif

#endif //include guard

