/**
 *  @file eagine/dyli/detail.hpp
 *  @brief Dynamically linked library implementation details
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_DYLI_DETAIL_1408161720_HPP
#define EAGINE_DYLI_DETAIL_1408161720_HPP

#include <eagine/base/memory.hpp>
#include <eagine/base/utility.hpp>
#include <eagine/base/dyn_lib.hpp>
#include <eagine/base/error.hpp>

namespace EAGine {
namespace dyli {

template <typename T>
class content;
template <typename T>
class product;

namespace detail {

void required_lib_n_a(void);
void required_res_n_a(void);

inline
std::shared_ptr<base::dynamic_library>
require_lib(const std::weak_ptr<base::dynamic_library>& wlib)
{
	base::shared_ptr<base::dynamic_library> lib = wlib.lock();

	if(!bool(lib))
	{
		required_lib_n_a();
	}

	return base::move(lib);
}

template <typename T>
inline
std::shared_ptr<T>
require_ptr(const std::weak_ptr<T>& wptr)
{
	base::shared_ptr<T> ptr = wptr.lock();

	if(!bool(ptr))
	{
		required_res_n_a();
	}

	return base::move(ptr);
}

template <typename FuncType>
struct func_util;

template <typename RV, typename ... P>
struct func_util<RV(P...)>
{
	typedef RV(adjusted_t)(P...);

	static inline RV adapt_rv(
		const base::shared_ptr<base::dynamic_library>&,
		RV value
	)
	{
		return value;
	}
};

template <typename RV, typename ... P>
struct func_util<content<RV>(P...)>
{
	typedef RV*(adjusted_t)(P...);

	static content<RV> adapt_rv(
		const base::shared_ptr<base::dynamic_library>& lib,
		RV* ptr
	)
	{
		return content<RV>(lib, ptr);
	}
};

template <typename RV, typename ... P>
struct func_util<product<RV>(P...)>
{
	typedef base::shared_ptr<RV>(adjusted_t)(P...);

	static product<RV> adapt_rv(
		const base::shared_ptr<base::dynamic_library>& lib,
		base::shared_ptr<RV>&& ptr
	)
	{
		return product<RV>(lib, base::move(ptr));
	}
};

} // namespace detail
} // namespace dyli
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/dyli/detail.inl>
#endif

#endif //include guard

