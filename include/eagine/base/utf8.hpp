/**
 *  @file eagine/base/utf8.hpp
 *  @brief Helper utf8-related tools
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2011-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_UTF8_1102101236_HPP
#define EAGINE_BASE_UTF8_1102101236_HPP

#include <eagine/eagine_config.hpp>
#include <eagine/base/vector.hpp>
#include <eagine/base/type.hpp>
#include <cstddef>

namespace eagine {
namespace base {

typedef char32_t unicode_cp;

std::size_t utf8_bytes_required(
	const unicode_cp* cp_str,
	std::size_t len
) noexcept;

void convert_code_point_to_utf8(
	unicode_cp cp,
	char* str,
	std::size_t& len
) noexcept;

void convert_code_points_to_utf8(
	const unicode_cp* cps,
	std::size_t len,
	vector<char>& result
);

std::size_t code_points_required(
	const char* str,
	std::size_t len
) noexcept;

unicode_cp convert_utf8_to_code_point(
	const char* str,
	std::size_t len,
	std::size_t& cp_len
) noexcept;

void convert_utf8_to_code_points(
	const char* str,
	std::size_t len,
	vector<unicode_cp>& result
);

// utf8_validator
class utf8_validator
{
private:
	static
	byte to_byte(const char*)
	noexcept;
public:
	// Validates the utf8 string, returns _end or nullptr
	static
	const char* validate(const char* begin, const char* end)
	noexcept;

	bool operator()(const char* begin, const char* end) const
	noexcept
	{
		return validate(begin, end) == end;
	}
};

// valid_utf8
inline
bool valid_utf8(const char* begin, const char* end)
noexcept
{
#if !defined(EAGINE_NO_UTF8_CHECKS) || !EAGINE_NO_UTF8_CHECKS
	return utf8_validator::validate(begin, end) == end;
#else
	(void)begin;
	(void)end;
	return true;
#endif
}

} // namespace base
} // namespace eagine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/utf8.inl>
#endif

#endif
