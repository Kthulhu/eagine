/**
 *  @file eagine/dbg/hexdump.inl
 *  @brief Implementation component-related functions
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>
#include <iostream>
#include <cctype>

namespace EAGine {
namespace dbg {
//------------------------------------------------------------------------------
// hexdump::_to_hex_b
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void
hexdump::_to_hex_b(std::ostream& out, byte b)
{
	static const char hd[16] = {
		'0','1','2','3',
		'4','5','6','7',
		'8','9','a','b',
		'c','d','e','f'
	};
	out << hd[(b>>4)&0x0F] << hd[b&0x0F];
}
//------------------------------------------------------------------------------
// ostream << hexdump
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
std::ostream&
operator << (std::ostream& out, const hexdump& hd)
{
	typedef unsigned char byte;

	out << std::endl;

	const byte* row = hd._bgn - std::size_t(hd._bgn) % 16;

	while(row < hd._end)
	{
		out << ((const void*)row);
		out << "|";

		const byte* pos = row;
		for(unsigned b=0; b<16; ++b)
		{
			if(b == 8)
			{
				out << " ";
			}

			if(pos < hd._bgn || pos >= hd._end)
			{
				out << " ..";
			}
			else
			{
				out << " ";
				hexdump::_to_hex_b(out, *pos);
			}
			++pos;
		}

		out << " |";

		pos = row;
		for(unsigned b=0; b<16; ++b)
		{
			if(b == 8)
			{
				out << " ";
			}

			if(pos < hd._bgn || pos >= hd._end || !std::isprint(*pos))
			{
				out << ".";
			}
			else
			{
				out << char(*pos);
			}
			++pos;
		}

		row += 16;

		out << "|" << std::endl;
	}

	return out;
}
//------------------------------------------------------------------------------
} // namespace dbg
} // namespace EAGine


