/**
 *  @file eagine/base/future.hpp
 *  @brief Futures and asynchronous execution.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_FUTURE_1308281038_HPP
#define EAGINE_BASE_FUTURE_1308281038_HPP

#include <future>

namespace EAGine {
namespace base {

using ::std::future;
using ::std::shared_future;
using ::std::promise;
using ::std::packaged_task;

using ::std::async;
using ::std::launch;
using ::std::future_status;

using ::std::future_error;
using ::std::future_errc;

} // namespace base
} // namespace EAGine

#endif //include guard

