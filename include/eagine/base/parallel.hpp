/**
 *  @file eagine/base/parallel.hpp
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_PARALLEL_1501121943_HPP
#define EAGINE_BASE_PARALLEL_1501121943_HPP

#include <eagine/base/functor.hpp>
#include <eagine/base/future.hpp>
#include <eagine/base/atomic.hpp>
#include <eagine/base/vector.hpp>

namespace eagine {
namespace base {

struct execution_params
{
	unsigned thread_count = 2;
	unsigned invocations = 0;
};

class parallelizer;

class parallel_execution
{
private:
	atomic<unsigned> _id;
	functor_ref<bool(unsigned)> _func;

	vector<future<void>> _evts;

	parallel_execution(
		const functor_ref<bool(unsigned)>&,
		execution_params&
	);

	friend class parallelizer;
public:
	parallel_execution(parallel_execution&& tmp)
	noexcept
	 : _id(unsigned(tmp._id))
	 , _func(std::move(tmp._func))
	 , _evts(std::move(tmp._evts))
	{ }

	~parallel_execution(void)
	noexcept
	{
		wait();
	}

	void wait(void);
};

class parallelizer
{
public:
	parallel_execution
	execute(
		const functor_ref<bool(unsigned)>& kernel,
		execution_params& params
	) const
	{
		return parallel_execution(kernel, params);
	}

	parallel_execution
	execute(const functor_ref<bool(unsigned)>& kernel) const
	{
		execution_params params;
		return parallel_execution(kernel, params);
	}
};

} // namespace base
} // namespace eagine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/parallel.inl>
#endif

#endif //include guard

