/**
 *  @file eagine/unit/poly/quantity.inl
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>
#include <eagine/base/assert.hpp>

namespace eagine {
namespace unit {
namespace poly {
//------------------------------------------------------------------------------
#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void
quantity_base::_assert_compatible(const unit& a, const unit& b)
{
	if((a.dim() != b.dim()) || (a.sys() != b.sys()))
	{
		EAGINE_ABORT("Incompatible units"); // TODO throw error
	}
}
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
} // namespace poly
} // namespace unit
} // namespace eagine


