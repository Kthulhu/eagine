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
	unsigned _thread_count = 2;
	std::size_t invocations = 0;
};

class parallelizer;

class base_parallel_execution
{
protected:
	atomic<std::size_t> _id;
	vector<future<void>> _evts;

	base_parallel_execution(void)
	noexcept
	 : _id(0u)
	{ }

	base_parallel_execution(base_parallel_execution&& tmp)
	noexcept
	 : _id(tmp._id.load())
	 , _evts(std::move(tmp._evts))
	{ }
public:
	~base_parallel_execution(void)
	noexcept
	{
		wait();
	}

	void wait(void);
};

class parallel_execution
 : public base_parallel_execution
{
private:
	functor_ref<bool(std::size_t)> _kern;

	parallel_execution(
		const functor_ref<bool(std::size_t)>&,
		execution_params&
	);

	friend class parallelizer;
public:
	parallel_execution(parallel_execution&&) = default;
};

class stateful_parallel_execution
 : public base_parallel_execution
{
private:
	vector<functor<bool(std::size_t)>> _knls;

	stateful_parallel_execution(
		vector<functor<bool(std::size_t)>>&&,
		execution_params&
	);

	friend class parallelizer;
public:
	stateful_parallel_execution(stateful_parallel_execution&&) = default;

};

class parallelizer
{
private:
	//TODO allocator

	static
	execution_params& _prepare_params(execution_params& param)
	{
		// TODO
		return param;
	}
public:
	parallel_execution
	execute(
		const functor_ref<bool(std::size_t)>& kernel,
		execution_params& params
	) const
	{
		return parallel_execution(
			kernel,
			_prepare_params(params)
		);
	}

	parallel_execution
	execute(const functor_ref<bool(std::size_t)>& kernel) const
	{
		execution_params params;
		return parallel_execution(
			kernel,
			_prepare_params(params)
		);
	}
};

} // namespace base
} // namespace eagine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/parallel.inl>
#endif

#endif //include guard

