/**
 *  @file eagine/unit/poly/unit.inl
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>
#include <typeinfo>
#include <typeindex>

namespace eagine {
namespace unit {
namespace poly {
//------------------------------------------------------------------------------
// value_conv
//------------------------------------------------------------------------------
class value_conv
{
private:
	std::type_index _type;
	void (*_to_base_unit)(void);
	void (*_fm_base_unit)(void);
	const value_conv* _base_conv;

	friend class unit;
public:
	template <typename T>
	value_conv(
		T*,
		T (*to_base)(T),
		T (*fm_base)(T),
		const value_conv* conv
	): _type(std::type_index(typeid(T)))
	 , _to_base_unit((void(*)(void))to_base)
	 , _fm_base_unit((void(*)(void))fm_base)
	 , _base_conv(conv)
	{ }

	const value_conv* base_conv(void) const
	{
		return _base_conv?_base_conv:this;
	}

	template <typename T>
	T to_base_unit(T v) const
	{
		if(_to_base_unit)
		{
			return ((T(*)(T))_to_base_unit)(v);
		}
		else return v;
	}

	template <typename T>
	T from_base_unit(T v) const
	{
		if(_fm_base_unit)
		{
			return ((T(*)(T))_fm_base_unit)(v);
		}
		else return v;
	}
};
//------------------------------------------------------------------------------
// unit::_infos
//------------------------------------------------------------------------------
#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
std::map<std::pair<dimension, system>, unit::_unit_info>&
unit::_infos(void)
{
	static std::map<std::pair<dimension, system>, _unit_info> im;
	return im;
}
//------------------------------------------------------------------------------
// unit::_get_info
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
const unit::_unit_info*
unit::_get_info(const dimension& d, const system& s)
{
	auto p = _infos().find({d, s});

	if(p == _infos().end())
	{
		p = _infos().insert({
			{d, s}, {
				d, s,
				nullptr,
				nullptr,
				0,
				0,
				nullptr
			}
		}).first;
	}
	return &p->second;
}
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
// unit::_make_info
//------------------------------------------------------------------------------
template <typename U>
inline
unit::_unit_info
unit::_make_info(const unit::_unit_info* base_info)
{
	return {
		poly::dimension(typename U::dimension()),
		poly::system(typename U::system()),
		meta::c_str<typename eagine::unit::info<U>::name>(),
		meta::c_str<typename eagine::unit::info<U>::symbol>(),
		meta::size<typename eagine::unit::info<U>::name>(),
		meta::size<typename eagine::unit::info<U>::symbol>(),
		base_info
	};
}
//------------------------------------------------------------------------------
// unit::_get_info
//------------------------------------------------------------------------------
template <typename D, typename S>
inline
const unit::_unit_info*
unit::_get_info(eagine::unit::unit<D,S> u)
{
	typedef eagine::unit::unit<D,S> U;

	auto p = _infos().find({dimension((D())), system((S()))});

	if((p == _infos().end()) || (p->second.name == nullptr))
	{
		p = _infos().insert({
			{dimension((D())), system((S()))},
			_make_info<U>(nullptr)
		}).first;
	}

	return &p->second;
}
//------------------------------------------------------------------------------
// unit::_get_info
//------------------------------------------------------------------------------
template <typename D, typename S, typename Sys>
inline
const unit::_unit_info*
unit::_get_info(eagine::unit::scaled_unit<D,S,Sys>)
{
	typedef eagine::unit::scaled_unit<D,S,Sys> SU;
	typedef eagine::unit::unit<D,Sys> U;
	static _unit_info su = _make_info<SU>(_get_info(U()));

	return &su;
}
//------------------------------------------------------------------------------
// unit::_get_conv
//------------------------------------------------------------------------------
template <typename T, typename D, typename S>
inline
const value_conv*
unit::_get_conv(eagine::unit::unit<D,S>)
{
	static value_conv conv(
		(T*)nullptr,
		(T(*)(T))nullptr,
		(T(*)(T))nullptr,
		(value_conv*)nullptr
	);
	return &conv;
}
//------------------------------------------------------------------------------
// unit::_get_conv
//------------------------------------------------------------------------------
template <typename T, typename D, typename S, typename Sys>
inline
const value_conv*
unit::_get_conv(eagine::unit::scaled_unit<D,S,Sys>)
{
	static value_conv conv(
		(T*)nullptr,
		(T(*)(T))([](T v) -> T
		{
			return eagine::unit::value_conv<
				eagine::unit::scaled_unit<D,S,Sys>,
				eagine::unit::unit<D,Sys>
			>::type::template apply<T>(v);
		}),
		(T(*)(T))([](T v) -> T
		{
			return eagine::unit::value_conv<
				eagine::unit::unit<D,Sys>,
				eagine::unit::scaled_unit<D,S,Sys>
			>::type::template apply<T>(v);
		}),
		_get_conv<T>(eagine::unit::unit<D,Sys>())
	);
	return &conv;
}
//------------------------------------------------------------------------------
#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
//------------------------------------------------------------------------------
// unit + unit
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
unit
operator + (const unit& a, const unit& b)
{
	if((a.dim() != b.dim()) || (a.sys() != b.sys()))
	{
		assert(!"Adding incompatible units"); // TODO exception
	}

	return a.base_unit();
}
//------------------------------------------------------------------------------
// unit - unit
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
unit
operator - (const unit& a, const unit& b)
{
	if((a.dim() != b.dim()) || (a.sys() != b.sys()))
	{
		assert(!"Subtracting incompatible units"); // TODO exception
	}

	return a.base_unit();
}
//------------------------------------------------------------------------------
// unit * unit
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
unit
operator * (const unit& a, const unit& b)
{
	if((a.sys() != b.sys()))
	{
		assert(!"Multiplying incompatible units"); // TODO exception
	}

	return unit(
		unit::_get_info(a.dim()*b.dim(), a.sys()),
		a._conv->base_conv()
	);
}
//------------------------------------------------------------------------------
// unit / unit
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
unit
operator / (const unit& a, const unit& b)
{
	if((a.sys() != b.sys()))
	{
		assert(!"Dividing incompatible units"); // TODO exception
	}

	return unit(
		unit::_get_info(a.dim()/b.dim(), a.sys()),
		a._conv->base_conv()
	);
}
//------------------------------------------------------------------------------
// unit::base_unit
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
unit
unit::base_unit(void) const
{
	assert(_info);
	assert(_conv);

	return unit(
		_info->_base_info?_info->_base_info:_info,
		_conv->base_conv()
	);
}
#endif
//------------------------------------------------------------------------------
// unit::_to_base
//------------------------------------------------------------------------------
template <typename T>
inline
T unit::_to_base(T v) const
{
	assert(_conv);
	return _conv->template to_base_unit<T>(v);
}
//------------------------------------------------------------------------------
// unit::_from_base
//------------------------------------------------------------------------------
template <typename T>
inline
T unit::_from_base(T v) const
{
	assert(_conv);
	return _conv->template from_base_unit<T>(v);
}
//------------------------------------------------------------------------------
} // namespace poly
} // namespace unit
} // namespace eagine


