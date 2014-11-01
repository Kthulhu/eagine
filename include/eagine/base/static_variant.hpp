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

template <std::size_t Offset, typename ... T>
struct static_variant
{
private:
	static_assert(
		sizeof...(T) > 0,
		"No types in static_variant!"
	);

	const unsigned var_id;

	template <typename V, unsigned I>
	void _do_accept(
		V& v,
		meta::integral_constant<unsigned, I>,
		meta::integral_constant<unsigned, I>
	)
	{
		typedef typename tuple_element<
			I, tuple<T...>
		>::type _e_t;

		v(*(const _e_t*)((const byte*)(const void*)(&var_id)+Offset));
	}

	template <typename V, unsigned L, unsigned H>
	void _do_accept(
		V& v,
		meta::integral_constant<unsigned, L>,
		meta::integral_constant<unsigned, H>
	)
	{
		if(var_id <= (L+H)/2)
		{
			_do_accept(v,
				meta::integral_constant<unsigned, L>(),
				meta::integral_constant<unsigned, (L+H)/2>()
			);
		}
		else
		{
			_do_accept(v,
				meta::integral_constant<unsigned, (L+H)/2+1>(),
				meta::integral_constant<unsigned, H>()
			);
		}
	}

	template <typename Visitor>
	void _do_accept_ref(Visitor& v)
	{
		_do_accept(v,
			meta::integral_constant<unsigned, 0>(),
			meta::integral_constant<unsigned, sizeof...(T)-1>()
		);
	}

	static_variant(void)
	 : var_id(0)
	{ }
public:
	template <typename Visitor>
	void accept(Visitor visit)
	{
		_do_accept_ref(visit);
	}

	template <typename Visitor>
	void accept(reference_wrapper<Visitor> visit)
	{
		_do_accept_ref(visit.get());
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

