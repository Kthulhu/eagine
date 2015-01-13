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
// parallel_execution::parallel_execution
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
parallel_execution::
parallel_execution(
	const functor_ref<bool(unsigned)>& func,
	execution_params& params
): _id(0)
 , _func(func)
{
	auto func_wrap =
		[=](void)
		{
			while(true)
			{
				unsigned id = _id++;
				if(!_func(id)) break;
			}
		};

	_evts.reserve(params.thread_count);

	for(unsigned i=0; i<params.thread_count; ++i)
	{
		_evts.push_back(async(launch::async, func_wrap));
	}
}
//------------------------------------------------------------------------------
// parallel_execution::wait
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void
parallel_execution::
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
} // namespace base
} // namespace eagine

