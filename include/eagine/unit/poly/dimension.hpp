/**
 *  @file eagine/unit/poly/dimension.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_POLY_DIMENSION_1308281038_HPP
#define EAGINE_UNIT_POLY_DIMENSION_1308281038_HPP

#include <eagine/unit/dimensionless.hpp>
#include <eagine/base/function.hpp>
#include <eagine/base/array.hpp>
#include <eagine/base/vector.hpp>
#include <eagine/base/string.hpp>
#include <eagine/meta/string.hpp>
#include <map>

namespace eagine {
namespace unit {
namespace poly {

class dimension;

typedef eagine::base::vector<std::pair<dimension, int>> combined_dimension;

class dimension
{
public:
	static constexpr unsigned max_dims = 12;
private:
	typedef eagine::base::array<signed char, max_dims> _dims_t;
	_dims_t _dims;

	static void _add(_dims_t& c, const _dims_t& a, const _dims_t& b);
	static void _sub(_dims_t& c, const _dims_t& a, const _dims_t& b);
	static bool _negeq(const _dims_t& a, const _dims_t& b);
	static bool _dimls(const _dims_t& a);

	template <typename Dim>
	static _dims_t _make_dims(Dim);

	struct _info_t
	{
		const char* name;
		std::size_t name_len;
	};
	const _info_t* _info;

	static std::map<_dims_t, _info_t>& _infos(void);

	template <typename Dim>
	static _info_t _make_info(void);

	static const _info_t*
	_ins_and_get_info(_info_t(*)(void), const _dims_t&);

	template <typename Dim>
	static const _info_t* _get_info(Dim, const _dims_t& dims);

	static const _info_t* _get_info(const _dims_t& dims);

	bool _enum_hlp(
		const eagine::base::function<bool(const combined_dimension&)>&,
		combined_dimension&,
		std::map<_dims_t, _info_t>::const_iterator,
		unsigned depth
	) const;

	dimension(const _dims_t& dims)
	 : _dims(dims)
	 , _info(_get_info(_dims))
	{ }
public:
	template <typename H, typename T>
	dimension(bits::dims<H, T> d)
	 : _dims(_make_dims(d))
	 , _info(_get_info(d, _dims))
	{ }

	dimension(void)
	 : dimension(eagine::unit::dimensionless())
	{ }

	friend bool operator == (const dimension& a, const dimension& b)
	{
		return a._dims == b._dims;
	}

	friend bool operator != (const dimension& a, const dimension& b)
	{
		return a._dims != b._dims;
	}

	friend bool operator <  (const dimension& a, const dimension& b)
	{
		return a._dims < b._dims;
	}

	friend dimension operator * (const dimension& a, const dimension& b)
	{
		_dims_t dims;
		_add(dims, a._dims, b._dims);
		return dimension(dims);
	}

	friend dimension operator / (const dimension& a, const dimension& b)
	{
		_dims_t dims;
		_sub(dims, a._dims, b._dims);
		return dimension(dims);
	}

	void enumerate_combinations(
		const eagine::base::function<
			bool(const combined_dimension&)
		>&,
		unsigned depth
	) const;

	eagine::base::cstrref name(void) const;

	template <typename BaseDim>
	int power(base::dimension<BaseDim> = BaseDim())
	{
		return int(_dims[base::dim_num<BaseDim>()]);
	}
};

} // namespace poly
} // namespace unit
} // namespace eagine

#include <eagine/unit/poly/dimension.inl>

#endif //include guard

