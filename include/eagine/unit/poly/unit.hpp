/**
 *  @file eagine/unit/poly/unit.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_POLY_UNIT_1308281038_HPP
#define EAGINE_UNIT_POLY_UNIT_1308281038_HPP

#include <eagine/unit/poly/dimension.hpp>
#include <eagine/unit/poly/system.hpp>

namespace eagine {
namespace unit {
namespace poly {

class value_conv;

class unit
{
private:
	struct _unit_info
	{
		dimension dim;
		system sys;
		const char* name;
		const char* sym;
		std::size_t name_len;
		std::size_t sym_len;
		const _unit_info* _base_info;
	};

	const _unit_info* _info;

	static std::map<std::pair<dimension, system>, _unit_info>&
	_infos(void);

	template <typename U>
	static _unit_info _make_info(const _unit_info*);

	static const _unit_info*
	_get_info(const dimension&, const system&);

	template <typename D, typename S>
	static const _unit_info*
	_get_info(eagine::unit::unit<D,S>);

	template <typename D, typename S, typename Sys>
	static const _unit_info*
	_get_info(eagine::unit::scaled_unit<D,S,Sys>);

	const value_conv* _conv;

	template <typename T, typename D, typename S>
	static const value_conv*
	_get_conv(eagine::unit::unit<D,S>);

	template <typename T, typename D, typename S, typename Sys>
	static const value_conv*
	_get_conv(eagine::unit::scaled_unit<D,S,Sys>);

	unit(const _unit_info* info, const value_conv* conv)
	 : _info(info)
	 , _conv(conv)
	{
		assert(_info);
		assert(_conv);
	}
public:
	template <typename T, typename Unit>
	unit(T*, Unit u)
	 : _info(_get_info(u))
	 , _conv(_get_conv<T>(u))
	{ }

	friend bool operator == (const unit& a, const unit& b)
	{
		return	(a._info == b._info) &&
			(a._conv == b._conv);
	}

	friend bool operator != (const unit& a, const unit& b)
	{
		return	(a._info != b._info) ||
			(a._conv != b._conv);
	}

	friend unit operator + (const unit& a, const unit& b);
	friend unit operator - (const unit& a, const unit& b);
	friend unit operator * (const unit& a, const unit& b);
	friend unit operator / (const unit& a, const unit& b);

	const poly::dimension& dim(void) const
	{
		assert(_info);
		return _info->dim;
	}

	const poly::system& sys(void) const
	{
		assert(_info);
		return _info->sys;
	}

	eagine::base::cstrref name(void) const
	{
		assert(_info);
		return eagine::base::cstrref(
			_info->name,
			_info->name_len
		);
	}

	eagine::base::cstrref symbol(void) const
	{
		assert(_info);
		return eagine::base::cstrref(
			_info->sym,
			_info->sym_len
		);
	}

	unit base_unit(void) const;

	template <typename T>
	T _to_base(T v) const;

	template <typename T>
	T _from_base(T v) const;
};

} // namespace poly
} // namespace unit
} // namespace eagine

#include <eagine/unit/poly/unit.inl>

#endif //include guard

