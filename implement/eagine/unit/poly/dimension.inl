/**
 *  @file eagine/unit/poly/dimension.inl
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>

namespace EAGine {
namespace unit {
namespace poly {
//------------------------------------------------------------------------------
// dimension::_add
//------------------------------------------------------------------------------
inline
void
dimension::_add(_dims_t& c, const _dims_t& a, const _dims_t& b)
{
	for(unsigned i=0; i<max_dims; ++i)
	{
		c[i] = a[i] + b[i];
	}
}
//------------------------------------------------------------------------------
// dimension::_sub
//------------------------------------------------------------------------------
inline
void
dimension::_sub(_dims_t& c, const _dims_t& a, const _dims_t& b)
{
	for(unsigned i=0; i<max_dims; ++i)
	{
		c[i] = a[i] - b[i];
	}
}
//------------------------------------------------------------------------------
// dimension::_negeq
//------------------------------------------------------------------------------
inline
bool 
dimension::_negeq(const _dims_t& a, const _dims_t& b)
{
	for(unsigned i=0; i<max_dims; ++i)
	{
		if(a[i] != -b[i]) return false;
	}
	return true;
}
//------------------------------------------------------------------------------
inline
bool
dimension::_dimls(const _dims_t& a)
{
	for(unsigned i=0; i<max_dims; ++i)
	{
		if(a[i] != 0) return false;
	}
	return true;
}
//------------------------------------------------------------------------------
// dimension::_init_hlp
//------------------------------------------------------------------------------
template <typename ... DimPow>
struct _dim_init_hlp
{
	typedef EAGine::base::array<signed char, dimension::max_dims> _dims_t;

	typedef _dim_init_hlp type;

	template <typename ... T>
	static inline void _eat(T...){ }

	template <typename DP>
	static int _set_dim(_dims_t& dims, DP)
	{
		dims[base::dim_num<typename DP::dim>()] = DP::pow::value;
		return 0;
	}

	static void apply(_dims_t& dims)
	{
		_eat(_set_dim(dims, DimPow())...);
	}
};
//------------------------------------------------------------------------------
// dimension::_make_dims
//------------------------------------------------------------------------------
template <typename Dim>
inline
dimension::_dims_t
dimension::_make_dims(Dim)
{
	_dims_t result = {{0,0,0,0,0,0,0,0,0,0,0,0}};

	typedef typename bits::apply<_dim_init_hlp, Dim>::type hlpr;

	hlpr::apply(result);

	return result;
}
//------------------------------------------------------------------------------
// dimension::_infos
//------------------------------------------------------------------------------
#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
EAGINE_LIB_FUNC
std::map<dimension::_dims_t, dimension::_info_t>&
dimension::_infos(void)
{
	static std::map<_dims_t, _info_t> im;
	return im;
}
#endif
//------------------------------------------------------------------------------
// dimension::_make_info
//------------------------------------------------------------------------------
template <typename Dim>
inline
dimension::_info_t
dimension::_make_info(void)
{
	return {
		meta::c_str<
			typename EAGine::unit::info<Dim>::name
		>::value,
		meta::size<
			typename EAGine::unit::info<Dim>::name
		>::value
	};
}
//------------------------------------------------------------------------------
// dimension::_ins_and_get_info
//------------------------------------------------------------------------------
#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
EAGINE_LIB_FUNC
const dimension::_info_t*
dimension::_ins_and_get_info(_info_t(*make_info)(void), const _dims_t& dims)
{
	auto p = _infos().find(dims);

	if(p == _infos().end())
	{
		p = _infos().insert({dims, make_info()}).first;
	}
	assert(p != _infos().end());

	return &p->second;
}
#endif
//------------------------------------------------------------------------------
// dimension::_get_info
//------------------------------------------------------------------------------
template <typename Dim>
inline
const dimension::_info_t*
dimension::_get_info(Dim, const _dims_t& dims)
{
	return _ins_and_get_info(&_make_info<Dim>, dims);
}
//------------------------------------------------------------------------------
#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
//------------------------------------------------------------------------------
// dimension::_get_info
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
const dimension::_info_t*
dimension::_get_info(const _dims_t& dims)
{
	auto p = _infos().find(dims);

	if(p == _infos().end())
	{
		return nullptr;
	}
	
	return &p->second;
}
//------------------------------------------------------------------------------
// dimension::_enum_hlp
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
bool
dimension::_enum_hlp(
	const EAGine::base::function<bool(const combined_dimension&)>& func,
	combined_dimension& cdims,
	std::map<_dims_t, _info_t>::const_iterator pos,
	unsigned depth
) const
{
	std::map<_dims_t, _info_t>::const_iterator i = pos, e = _infos().end();

	bool done = false;

	while((i != e) && (!done))
	{
		bool used = false;
		for(auto& p : cdims)
		{
			if(p.first._dims == i->first)
			{
				used = true;
				break;
			}
			else if(_negeq(p.first._dims, i->first))
			{
				used = true;
				break;
			}
		}
		if(used || _dimls(i->first))
		{
			++i;
			continue;
		}
		else if(depth == 0)
		{
			if(_dims == i->first)
			{
				cdims.push_back({*this, 1});
				done |= !func(cdims);
				cdims.pop_back();
			}
			else if(_negeq(_dims, i->first))
			{
				cdims.push_back({dimension(i->first),-1});
				done |= !func(cdims);
				cdims.pop_back();
			}
		}
		else if(_dims != i->first)
		{
			dimension c(i->first), tmp;

			if(!done)
			{
				tmp = *this / c;

				cdims.push_back({c, 1});
				tmp._enum_hlp(func, cdims, i, depth-1);
				cdims.pop_back();
			}

			if(!done)
			{
				tmp = *this * c;

				cdims.push_back({c,-1});
				tmp._enum_hlp(func, cdims, i, depth-1);
				cdims.pop_back();
			}
		}
		++i;
	}

	return !done;
}
//------------------------------------------------------------------------------
// dimension::enumerate_combinations
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void
dimension::enumerate_combinations(
	const EAGine::base::function<
		bool(const combined_dimension&)
	>& func,
	unsigned depth
) const
{
	combined_dimension cdims;
	for(unsigned d=0; d<=depth; ++d)
	{
		if(!_enum_hlp(func, cdims, _infos().begin(), d))
			break;
	}
}
//------------------------------------------------------------------------------
// dimension::name
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
EAGine::base::cstrref
dimension::name(void) const
{
	if(_info)
	{
		return EAGine::base::cstrref(
			_info->name,
			_info->name_len
		);
	}
	return EAGine::base::cstrref();
}
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
} // namespace poly
} // namespace unit
} // namespace EAGine


