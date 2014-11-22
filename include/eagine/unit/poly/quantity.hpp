/**
 *  @file eagine/unit/poly/quantity.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_POLY_QUANTITY_1308281038_HPP
#define EAGINE_UNIT_POLY_QUANTITY_1308281038_HPP

#include <eagine/unit/poly/unit.hpp>

namespace eagine {
namespace unit {
namespace poly {

class quantity_base
{
protected:
	static void _assert_compatible(const unit& a, const unit& b);
};

template <typename T>
class quantity
 : public quantity_base
{
private:
	T _v;
	unit _u;

	static T _to_base(const quantity& a)
	{
		return a._u._to_base(a._v);
	}
public:
	quantity(const quantity& q, unit u)
	 : _v(u.template _from_base<T>(q._u.template _to_base<T>(q._v)))
	 , _u(u)
	{ }

	quantity(T v, unit u)
	 : _v(v)
	 , _u(u)
	{ }

	template <typename Unit>
	quantity(T v, Unit u)
	 : _v(v)
	 , _u(&_v, u)
	{ }

	friend bool operator == (const quantity& a, const quantity& b)
	{
		_assert_compatible(a._u, b._u);
		return	_to_base(a) == _to_base(b);
	}

	friend bool operator != (const quantity& a, const quantity& b)
	{
		_assert_compatible(a._u, b._u);
		return	_to_base(a) != _to_base(b);
	}

	friend bool operator <  (const quantity& a, const quantity& b)
	{
		_assert_compatible(a._u, b._u);
		return	_to_base(a) <  _to_base(b);
	}

	friend bool operator <= (const quantity& a, const quantity& b)
	{
		_assert_compatible(a._u, b._u);
		return	_to_base(a) <= _to_base(b);
	}

	friend bool operator >  (const quantity& a, const quantity& b)
	{
		_assert_compatible(a._u, b._u);
		return	_to_base(a) >  _to_base(b);
	}

	friend bool operator >= (const quantity& a, const quantity& b)
	{
		_assert_compatible(a._u, b._u);
		return	_to_base(a) >= _to_base(b);
	}

	friend quantity operator + (const quantity& a, const quantity& b)
	{
		_assert_compatible(a._u, b._u);
		return quantity(
			_to_base(a)+
			_to_base(b),
			a._u+b._u
		);
	}

	friend quantity operator - (const quantity& a, const quantity& b)
	{
		_assert_compatible(a._u, b._u);
		return quantity(
			_to_base(a)-
			_to_base(b),
			a._u-b._u
		);
	}

	friend quantity operator * (const quantity& a, const quantity& b)
	{
		return quantity(
			_to_base(a)*
			_to_base(b),
			a._u*b._u
		);
	}

	friend quantity operator / (const quantity& a, const quantity& b)
	{
		return quantity(
			_to_base(a)/
			_to_base(b),
			a._u/b._u
		);
	}

	const poly::dimension& dim(void) const
	{
		return _u.dim();
	}

	const poly::unit& value_unit(void) const
	{
		return _u;
	}

	const T& value(void) const
	{
		return _v;
	}
};

} // namespace poly
} // namespace unit
} // namespace eagine

#include <eagine/unit/poly/quantity.inl>

#endif //include guard

