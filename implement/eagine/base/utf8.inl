/**
 *  .file oglplus/string/utf8.ipp
 *  .brief Helper utf8-related tools
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2011-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>
#include <eagine/base/assert.hpp>

namespace eagine {
namespace base {
//------------------------------------------------------------------------------
// utf8_bytes_required
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
std::size_t
utf8_bytes_required(
	const unicode_cp* cp_str,
	std::size_t len
) noexcept
{
	std::size_t result = 0;
	for(std::size_t i=0; i!=len; ++i)
	{
		unicode_cp cp = *cp_str++;

		if((cp & ~0x0000007Fu) == 0)
		{
			result += 1;
		}
		else if((cp & ~0x000007FFu) == 0)
		{
			result += 2;
		}
		else if((cp & ~0x0000FFFFu) == 0)
		{
			result += 3;
		}
		else if((cp & ~0x001FFFFFu) == 0)
		{
			result += 4;
		}
		else if((cp & ~0x03FFFFFFu) == 0)
		{
			result += 5;
		}
		else if((cp & ~0x7FFFFFFFu) == 0)
		{
			result += 6;
		}
		else EAGINE_ABORT("Invalid code point");
	}
	return result;
}
//------------------------------------------------------------------------------
// convert_code_point_to_utf8
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void
convert_code_point_to_utf8(
	unicode_cp cp,
	char* str,
	std::size_t& len
) noexcept
{
	// 7-bits -> one byte
	if((cp & ~0x0000007Fu) == 0)
	{
		str[0] = char(cp);
		len = 1;
	}
	// 11-bits -> two bytes
	else if((cp & ~0x000007FFu) == 0)
	{
		str[0] = char(((cp & 0x000007C0u) >>  6) | 0xC0);
		str[1] = char(((cp & 0x0000003Fu) >>  0) | 0x80);
		len = 2;
	}
	// 16-bits -> three bytes
	else if((cp & ~0x0000FFFFu) == 0)
	{
		str[0] = char(((cp & 0x0000F000u) >> 12) | 0xE0);
		str[1] = char(((cp & 0x00000FC0u) >>  6) | 0x80);
		str[2] = char(((cp & 0x0000003Fu) >>  0) | 0x80);
		len = 3;
	}
	// 21-bits -> four bytes
	else if((cp & ~0x001FFFFFu) == 0)
	{
		str[0] = char(((cp & 0x001C0000u) >> 18) | 0xF0);
		str[1] = char(((cp & 0x0003F000u) >> 12) | 0x80);
		str[2] = char(((cp & 0x00000FC0u) >>  6) | 0x80);
		str[3] = char(((cp & 0x0000003Fu) >>  0) | 0x80);
		len = 4;
	}
	// 26-bits -> five bytes
	else if((cp & ~0x03FFFFFFu) == 0)
	{
		str[0] = char(((cp & 0x03000000u) >> 24) | 0xF8);
		str[1] = char(((cp & 0x00FC0000u) >> 18) | 0x80);
		str[2] = char(((cp & 0x0003F000u) >> 12) | 0x80);
		str[3] = char(((cp & 0x00000FC0u) >>  6) | 0x80);
		str[4] = char(((cp & 0x0000003Fu) >>  0) | 0x80);
		len = 5;
	}
	// 31-bits -> six bytes
	else if((cp & ~0x7FFFFFFFu) == 0)
	{
		str[0] = char(((cp & 0x40000000u) >> 30) | 0xFC);
		str[1] = char(((cp & 0x3F000000u) >> 24) | 0x80);
		str[2] = char(((cp & 0x00FC0000u) >> 18) | 0x80);
		str[3] = char(((cp & 0x0003F000u) >> 12) | 0x80);
		str[4] = char(((cp & 0x00000FC0u) >>  6) | 0x80);
		str[5] = char(((cp & 0x0000003Fu) >>  0) | 0x80);
		len = 6;
	}
	else EAGINE_ABORT("Invalid code point");
}
//------------------------------------------------------------------------------
// convert_code_points_to_utf8
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void
convert_code_points_to_utf8(
	const unicode_cp* cps,
	std::size_t len,
	vector<char>& result
)
{
	std::size_t u8len = utf8_bytes_required(cps, len);

	result.resize(u8len);

	char* cptr = result.data();
	std::size_t clen = 0;
	while(len)
	{
		convert_code_point_to_utf8(*cps, cptr, clen);

		assert(u8len >= clen);
		assert(clen > 0);

		u8len -= clen;
		cptr += clen;

		len -= 1;
		cps += 1;
	}
	assert(u8len == 0);
}
//------------------------------------------------------------------------------
// code_points_required
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
std::size_t
code_points_required(
	const char* str,
	std::size_t len
) noexcept
{
	static_assert(sizeof(char) == sizeof(unsigned char), "");
	const unsigned char* pb = reinterpret_cast<const unsigned char*>(str);

	std::size_t result = 0;

	while(len != 0)
	{
		std::size_t skip = 0;
		if(((*pb) & 0x80u) == 0x00u)
		{
			skip = 1;
		}
		else if(((*pb) & 0xE0u) == 0xC0u)
		{
			skip = 2;
		}
		else if(((*pb) & 0xF0u) == 0xE0u)
		{
			skip = 3;
		}
		else if(((*pb) & 0xF8u) == 0xF0u)
		{
			skip = 4;
		}
		else if(((*pb) & 0xFCu) == 0xF8u)
		{
			skip = 5;
		}
		else if(((*pb) & 0xFEu) == 0xFCu)
		{
			skip = 6;
		}
		else EAGINE_ABORT("Invalid UTF8 sequence");

		assert(len >= skip);
		len -= skip;
		pb += skip;

		++result;
	}
	return result;
}
//------------------------------------------------------------------------------
// convert_utf8_to_code_point
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
unicode_cp
convert_utf8_to_code_point(
	const char* str,
	std::size_t len,
	std::size_t& cp_len
) noexcept
{
	static_assert(sizeof(char) == sizeof(unsigned char), "");
	const unsigned char*bytes = reinterpret_cast<const unsigned char*>(str);

	// 0xxxxxxx
	if((bytes[0] & 0x80u) == 0x00u)
	{
		assert(len >= 1);
		cp_len = 1;
		return unicode_cp(bytes[0]);
	}
	// 110xxxxx
	else if((bytes[0] & 0xE0u) == 0xC0u)
	{
		// but not 11000000
		assert(len >= 2);
		cp_len = 2;
		return unicode_cp(
			(((bytes[0] & ~0xE0u) <<  6) & 0x00000FC0u)|
			(((bytes[1] & ~0xC0u) <<  0) & 0x0000003Fu)
		);
	}
	// 1110xxxx
	else if((bytes[0] & 0xF0u) == 0xE0u)
	{
		// but not 11100000
		assert(len >= 3);
		cp_len = 3;
		return unicode_cp(
			(((bytes[0] & ~0xF0u) << 12) & 0x0003F000u)|
			(((bytes[1] & ~0xC0u) <<  6) & 0x00000FC0u)|
			(((bytes[2] & ~0xC0u) <<  0) & 0x0000003Fu)
		);
	}
	// 11110xxx
	else if((bytes[0] & 0xF8u) == 0xF0u)
	{
		// but not 11110000
		assert(len >= 4);
		cp_len = 4;
		return unicode_cp(
			(((bytes[0] & ~0xF8u) << 18) & 0x00FC0000u)|
			(((bytes[1] & ~0xC0u) << 12) & 0x0003F000u)|
			(((bytes[2] & ~0xC0u) <<  6) & 0x00000FC0u)|
			(((bytes[3] & ~0xC0u) <<  0) & 0x0000003Fu)
		);
	}
	// 111110xx
	else if((bytes[0] & 0xFCu) == 0xF8u)
	{
		// but not 11111000
		assert(len >= 5);
		cp_len = 5;
		return unicode_cp(
			(((bytes[0] & ~0xFCu) << 24) & 0x3F000000u)|
			(((bytes[1] & ~0xC0u) << 18) & 0x00FC0000u)|
			(((bytes[2] & ~0xC0u) << 12) & 0x0003F000u)|
			(((bytes[3] & ~0xC0u) <<  6) & 0x00000FC0u)|
			(((bytes[4] & ~0xC0u) <<  0) & 0x0000003Fu)
		);
	}
	// 1111110x
	else if((bytes[0] & 0xFEu) == 0xFCu)
	{
		// but not 11111100
		assert(len >= 6);
		cp_len = 6;
		return unicode_cp(
			(((bytes[0] & ~0xFEu) << 30) & 0xC0000000u)|
			(((bytes[1] & ~0xC0u) << 24) & 0x3F000000u)|
			(((bytes[2] & ~0xC0u) << 18) & 0x00FC0000u)|
			(((bytes[3] & ~0xC0u) << 12) & 0x0003F000u)|
			(((bytes[4] & ~0xC0u) <<  6) & 0x00000FC0u)|
			(((bytes[5] & ~0xC0u) <<  0) & 0x0000003Fu)
		);
	}
	EAGINE_ABORT("Invalid UTF8 sequence");
	return unicode_cp();
}
//------------------------------------------------------------------------------
// convert_utf8_to_code_points
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void
convert_utf8_to_code_points(
	const char* str,
	std::size_t len,
	vector<unicode_cp>& result
)
{
	std::size_t ulen = code_points_required(str, len);
	result.resize(ulen);

	unicode_cp* cpptr = result.data();
	std::size_t cplen = 0;
	while(len)
	{
		*cpptr = convert_utf8_to_code_point(str, len, cplen);
		++cpptr;

		assert(cplen > 0);
		assert(len >= cplen);
		len -= cplen;
		str += cplen;

		ulen -= 1;
	}
	assert(ulen == 0);
}
//------------------------------------------------------------------------------
// utf8_validator_to_byte
//------------------------------------------------------------------------------
inline
byte utf8_validator::to_byte(const char* s)
noexcept
{
	assert(s != nullptr);
	return *reinterpret_cast<const byte*>(s);
}
//------------------------------------------------------------------------------
// utf8_validator::validate
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
const char*
utf8_validator::validate(const char* pos, const char* end)
noexcept
{
	unsigned bytes = 0;
	assert(pos != nullptr);
	assert(end != nullptr);

	byte b = 0x00u;

	while((pos != end) && ((b = to_byte(pos)) != 0x00u))
	{
		// there are remaining bytes in the sequence
		if(bytes)
		{
			// the byte must be 10xxxxxx
			if((b & 0xC0u) != 0x80u)
			{
				return nullptr;
			}
			--bytes;
		}
		// this is _a beginning of a new sequence
		else if(b & 0x80u)
		{
			// 110xxxxx
			if((b & 0xE0u) == 0xC0u)
			{
				bytes = 1;
			}
			// 1110xxxx
			else if((b & 0xF0u) == 0xE0u)
			{
				bytes = 2;
			}
			// 11110xxx
			else if((b & 0xF8u) == 0xF0u)
			{
				bytes = 3;
			}
			// 111110xx
			else if((b & 0xFCu) == 0xF8u)
			{
				bytes = 4;
			}
			// 1111110x
			else if((b & 0xFEu) == 0xFCu)
			{
				bytes = 5;
			}
		}
		++pos;
	}
	return pos;
}
//------------------------------------------------------------------------------
} // namespace base
} // namespace eagine

