/**
 *  @file eagine/vect/shuffle.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_VECT_SHUFFLE_1308281038_HPP
#define EAGINE_VECT_SHUFFLE_1308281038_HPP

#include <eagine/vect/data.hpp>

namespace EAGine {
namespace vect {

template <typename T, unsigned N>
struct shuffle
{
	typedef typename data<T, N>::type _dT;

	template <unsigned ... I>
	static inline
	typename data<T,N>::type
	apply(const typename data<T,N>::type& v)
	{
#if defined(__clang__) && __SSE__
		return __builtin_shufflevector(v,v, I...);
#elif defined(__GNUC__) && __SSE__
		typedef typename data<unsigned,N>::type _mT;
		return __builtin_shuffle(v, _mT{I...});
#else
		return typename data<T, N>::type{v[I]...};
#endif
	}
};

} // namespace vect
} // namespace EAGine

#endif //include guard

