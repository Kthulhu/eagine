/**
 *  @file eagine/base/static_variant.hpp
 *  @brief Static variant.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_STATIC_VARIANT_1408161728_HPP
#define EAGINE_BASE_STATIC_VARIANT_1408161728_HPP

#include <eagine/base/type.hpp>
#include <eagine/base/ref.hpp>
#include <eagine/base/tuple.hpp>
#include <eagine/meta/int_const.hpp>

namespace EAGine {
namespace base {

template <typename RV, std::size_t Offset, typename ... T>
struct static_variant
{
private:
	static_assert(
		sizeof...(T) > 0,
		"No types in static_variant!"
	);

	const unsigned _var_id;

	template <typename V, unsigned I>
	RV _do_accept(
		V& v,
		meta::integral_constant<unsigned, I>,
		meta::integral_constant<unsigned, I>
	)
	{
		typedef typename tuple_element<
			I, tuple<T...>
		>::type _e_t;

		return v(
			*(const _e_t*)
			((const byte*)(const void*)(&_var_id)+Offset)
		);
	}

	template <typename V, unsigned L, unsigned H>
	RV _do_accept(
		V& v,
		meta::integral_constant<unsigned, L>,
		meta::integral_constant<unsigned, H>
	)
	{
		constexpr unsigned M = (L+H)/2;
		if(_var_id <= M)
		{
			return _do_accept(v,
				meta::integral_constant<unsigned, L>(),
				meta::integral_constant<unsigned, M>()
			);
		}
		else
		{
			return _do_accept(v,
				meta::integral_constant<unsigned, M+1>(),
				meta::integral_constant<unsigned, H>()
			);
		}
	}

	template <typename Visitor>
	RV _do_accept_ref(Visitor& v)
	{
		return _do_accept(v,
			meta::integral_constant<unsigned, 0>(),
			meta::integral_constant<unsigned, sizeof...(T)-1>()
		);
	}

	static_variant(void)
	noexcept
	 : _var_id(0)
	{ }
public:
	unsigned var_id(void) const
	noexcept
	{
		return _var_id;
	}

	template <typename Visitor>
	RV accept(Visitor visit)
	{
		return _do_accept_ref(visit);
	}

	template <typename Visitor>
	RV accept(reference_wrapper<Visitor> visit)
	{
		return _do_accept_ref(visit.get());
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

