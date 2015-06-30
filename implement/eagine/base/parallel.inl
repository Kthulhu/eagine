/**
 *  @file eagine/base/parallel.inl
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>

namespace eagine {
namespace base {
//------------------------------------------------------------------------------
// base_parallel_execution::wait
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void
base_parallel_execution::
wait(void)
{
	if(!_evts.empty())
	{
		for(future<void>& finished : _evts)
		{
			finished.wait();
		}
		_evts.clear();
	}
}
//------------------------------------------------------------------------------
// parallel_execution::parallel_execution
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
parallel_execution::
parallel_execution(
	const callable_ref<bool(std::size_t)>& kern,
	execution_params& params,
	const allocator<void>& alloc
): base_parallel_execution(alloc)
 , _kern(kern)
{
	auto kern_wrap =
		[this](void)
		{
			while(true)
			{
				std::size_t id = _id++;
				if(!_kern(id)) break;
			}
		};

	_evts.reserve(params._thread_count);

	for(unsigned i=0; i<params._thread_count; ++i)
	{
		_evts.push_back(async(launch::async, kern_wrap));
	}
}
//------------------------------------------------------------------------------
// stateful_parallel_execution::stateful_parallel_execution
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
stateful_parallel_execution::
stateful_parallel_execution(
	vector<callable<bool(std::size_t)>>&& knls,
	execution_params&,
	const allocator<void>& alloc
): base_parallel_execution(alloc)
 , _knls(knls)
{
	_evts.reserve(_knls.size());

	for(auto& kern : _knls)
	{
		auto kern_wrap =
			[this,&kern](void)
			{
				while(true)
				{
					std::size_t id = _id++;
					if(!kern(id)) break;
				}
			};
		_evts.push_back(async(launch::async, kern_wrap));
	}
}
//------------------------------------------------------------------------------
} // namespace base
} // namespace eagine

