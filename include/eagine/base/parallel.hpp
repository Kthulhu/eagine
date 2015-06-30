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

#include <eagine/base/callable.hpp>
#include <eagine/base/future.hpp>
#include <eagine/base/atomic.hpp>
#include <eagine/base/vector.hpp>
#include <eagine/base/alloc.hpp>

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

	base_parallel_execution(const allocator<void>& alloc)
	noexcept
	 : _id(0u)
	 , _evts(allocator<future<void>>(alloc))
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
	callable_ref<bool(std::size_t)> _kern;

	parallel_execution(
		const callable_ref<bool(std::size_t)>&,
		execution_params&,
		const allocator<void>&
	);

	friend class parallelizer;
public:
	parallel_execution(parallel_execution&&) = default;
};

class stateful_parallel_execution
 : public base_parallel_execution
{
private:
	vector<callable<bool(std::size_t)>> _knls;

	stateful_parallel_execution(
		vector<callable<bool(std::size_t)>>&&,
		execution_params&,
		const allocator<void>&
	);

	friend class parallelizer;
public:
	stateful_parallel_execution(stateful_parallel_execution&&) = default;

};

class parallelizer
{
private:
	allocator<void> _alloc;

	static
	execution_params& _prepare_params(execution_params& param)
	{
		// TODO
		return param;
	}
public:
	parallelizer(void) = default;

	parallelizer(const allocator<void>& alloc)
	 : _alloc(alloc)
	{ }

	parallel_execution
	execute(
		const callable_ref<bool(std::size_t)>& kernel,
		execution_params& params
	) const
	{
		return parallel_execution(
			kernel,
			_prepare_params(params),
			_alloc
		);
	}

	template <typename Kernel>
	parallel_execution
	execute(
		const Kernel& kernel,
		execution_params& params
	) const
	{
		return parallel_execution(
			callable_ref<bool(std::size_t)>(kernel),
			_prepare_params(params),
			_alloc
		);
	}

	template <typename Kernel>
	parallel_execution
	execute(const callable_ref<bool(std::size_t)>& kernel) const
	{
		execution_params params;
		return execute(kernel, params);
	}

	template <typename Kernel>
	stateful_parallel_execution
	execute_stateful(
		const Kernel& kernel,
		execution_params& params
	) const
	{
		_prepare_params(params);

		vector<callable<bool(std::size_t)>> kernels((
			allocator<callable<bool(std::size_t)>>(_alloc)
		));
		kernels.reserve(params._thread_count);

		for(unsigned i=0; i<params._thread_count; ++i)
		{
			kernels.emplace_back(
				std::allocator_arg,
				_alloc,
				Kernel(kernel)
			);
		}

		return stateful_parallel_execution(
			std::move(kernels),
			params,
			_alloc
		);
	}

	template <typename Kernel>
	stateful_parallel_execution
	execute_stateful(const Kernel& kernel) const
	{
		execution_params params;
		return execute_stateful(kernel, params);
	}
};

} // namespace base
} // namespace eagine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/parallel.inl>
#endif

#endif //include guard

