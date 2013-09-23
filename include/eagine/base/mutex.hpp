/**
 *  @file eagine/base/mutex.hpp
 *  @brief Mutex synchronization.
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_MUTEX_1308281038_HPP
#define EAGINE_BASE_MUTEX_1308281038_HPP

#include <mutex>

namespace EAGine {
namespace base {

using ::std::mutex;
using ::std::lock_guard;
using ::std::unique_lock;

using ::std::defer_lock;
using ::std::try_to_lock;
using ::std::adopt_lock;

using ::std::try_lock;
using ::std::lock;

} // namespace base
} // namespace EAGine

#endif //include guard

