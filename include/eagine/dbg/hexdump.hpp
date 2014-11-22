/**
 *  @file eagine/dbg/hexdump.hpp
 *  @brief Utility for printing blocks of memory in hexadecimal format.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_DBG_HEXDUMP_1308281038_HPP
#define EAGINE_DBG_HEXDUMP_1308281038_HPP

#include <eagine/base/memory_block.hpp>
#include <iosfwd>
#include <memory>

namespace eagine {
namespace dbg {

using base::byte;

class hexdump
{
private:
	const byte* _bgn;
	const byte* _end;

	static void _to_hex_b(std::ostream& out, byte b);
public:
	hexdump(const void* p, std::size_t s)
	 : _bgn((const byte*)p)
	 , _end(_bgn+s)
	{ }

	template <bool Const>
	hexdump(const base::basic_memory_block<Const>& mb)
	 : _bgn((const byte*)mb.addr())
	 , _end(_bgn+mb.size())
	{ }

	template <typename T>
	hexdump(const T& v)
	 : _bgn((const byte*)(const void*)std::addressof(v))
	 , _end(_bgn+sizeof(v))
	{ }

	friend std::ostream& operator << (std::ostream&, const hexdump&);
};

} // namespace dbg
} // namespace eagine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/dbg/hexdump.inl>
#endif

#endif //include guard

