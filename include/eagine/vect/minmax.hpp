/**
 *  @file eagine/vect/minmax.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_MINMAX_1308281038_HPP
#define EAGINE_VECT_MINMAX_1308281038_HPP

#include <eagine/vect/data.hpp>
#include <eagine/vect/shuffle.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N, bool V>
struct min
{
	typedef typename data<T, N, V>::type _dT;
	typedef typename data_param<T, N, V>::type _dpT;

	static inline
	_dT _hlp(_dpT a, _dpT b, meta::true_type)
	noexcept
	{
#if EAGINE_USE_SIMD && defined(__GNUC__) && !defined(__clang__)
		return (a<b)?a:b;
#else
		return _hlp(a, b, meta::false_type());
#endif
	}

	static inline
	_dT _hlp(_dpT a, _dpT b, meta::false_type)
	noexcept
	{
		_dT c = {};
		for(unsigned i=0; i<N; ++i)
		{
			c[i] = (a[i]<b[i])?a[i]:b[i];
		}
		return c;
	}


	static inline
	_dT apply(_dpT a, _dpT b)
	noexcept
	{
		return _hlp(a, b, has_vect_data<T, N, V>());
	}
};

template <typename T, unsigned N, bool V>
struct hmin
{
	typedef typename data<T, N, V>::type _dT;

	static
	_dT apply(_dT v)
	noexcept
	{
		T m = v[0];
		for(unsigned i=1; i<N; ++i)
		{
			if(m > v[i])
			{
				m = v[i];
			}
		}
		for(unsigned i=0; i<N; ++i)
		{
			v[i] = m;
		}
		return v;
	}
};

template <typename T, bool V>
struct hmin<T, 1, V>
{
	typedef typename data<T, 1, V>::type _dT;

	static inline
	_dT apply(_dT v)
	noexcept
	{
		return v;
	}
};

template <typename T, bool V>
struct hmin<T, 2, V>
{
	typedef typename data<T, 2, V>::type _dT;
	typedef typename data_param<T, 2, V>::type _dpT;
	typedef shuffle<T, 2, V> _sh;

	static
	_dT apply(_dpT v)
	noexcept
	{
		return min<T, 2, V>::apply(
			v,
			_sh::template apply<1,0>(v)
		);
	}
};

template <typename T, bool V>
struct hmin<T, 4, V>
{
	typedef typename data<T, 4, V>::type _dT;
	typedef typename data_param<T, 4, V>::type _dpT;
	typedef shuffle<T, 4, V> _sh;

	static constexpr inline
	_dT _hlp1(_dpT v)
	noexcept
	{
		return min<T, 4, V>::apply(
			v,
			_sh::template apply<1,0,3,2>(v)
		);
	}

	static constexpr inline
	_dT _hlp2(_dpT v)
	noexcept
	{
		return min<T, 4, V>::apply(
			v,
			_sh::template apply<2,3,0,1>(v)
		);
	}
	
	static constexpr inline
	_dT apply(_dpT v)
	noexcept
	{
		return _hlp2(_hlp1(v));
	}
};

template <typename T, unsigned N, bool V>
struct max
{
	typedef typename data<T, N, V>::type _dT;
	typedef typename data_param<T, N, V>::type _dpT;

	static inline
	_dT _hlp(_dpT a, _dpT b, meta::true_type)
	noexcept
	{
#if EAGINE_USE_SIMD && defined(__GNUC__) && !defined(__clang__)
		return (a>b)?a:b;
#else
		return _hlp(a, b, meta::false_type());
#endif
	}

	static inline
	_dT _hlp(_dpT a, _dpT b, meta::false_type)
	noexcept
	{
		_dT c = {};
		for(unsigned i=0; i<N; ++i)
		{
			c[i] = (a[i]>b[i])?a[i]:b[i];
		}
		return c;
	}


	static inline
	_dT apply(_dpT a, _dpT b)
	noexcept
	{
		return _hlp(a, b, has_vect_data<T, N, V>());
	}
};

template <typename T, unsigned N, bool V>
struct hmax
{
	typedef typename data<T, N, V>::type _dT;

	static
	_dT apply(_dT v)
	noexcept
	{
		T m = v[0];
		for(unsigned i=1; i<N; ++i)
		{
			if(m < v[i])
			{
				m = v[i];
			}
		}
		for(unsigned i=0; i<N; ++i)
		{
			v[i] = m;
		}
		return v;
	}
};

template <typename T, bool V>
struct hmax<T, 1, V>
{
	typedef typename data<T, 1, V>::type _dT;

	static inline
	_dT apply(_dT v)
	noexcept
	{
		return v;
	}
};

template <typename T, bool V>
struct hmax<T, 2, V>
{
	typedef typename data<T, 2, V>::type _dT;
	typedef typename data_param<T, 2, V>::type _dpT;
	typedef shuffle<T, 2, V> _sh;

	static
	_dT apply(_dT v)
	noexcept
	{
		return max<T, 2, V>::apply(
			v,
			_sh::template apply<1,0>(v)
		);
	}
};

template <typename T, bool V>
struct hmax<T, 4, V>
{
	typedef typename data<T, 4, V>::type _dT;
	typedef typename data_param<T, 4, V>::type _dpT;
	typedef shuffle<T, 4, V> _sh;

	static constexpr inline
	_dT _hlp1(_dpT v)
	noexcept
	{
		return max<T, 4, V>::apply(
			v,
			_sh::template apply<1,0,3,2>(v)
		);
	}

	static constexpr inline
	_dT _hlp2(_dpT v)
	noexcept
	{
		return max<T, 4, V>::apply(
			v,
			_sh::template apply<2,3,0,1>(v)
		);
	}
	
	static constexpr inline
	_dT apply(_dpT v)
	noexcept
	{
		return _hlp2(_hlp1(v));
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

