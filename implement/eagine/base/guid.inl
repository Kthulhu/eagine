/**
 *  @file eagine/base/guid.inl
 *  @brief Implementation of globaly unique identifier
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eagine/eagine_config.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace EAGine {
namespace base {

EAGINE_LIB_FUNC
guid::guid(const ::boost::uuids::uuid& that)
 : ::boost::uuids::uuid(that)
{ }

EAGINE_LIB_FUNC
guid::guid(void)
 : ::boost::uuids::uuid( ::boost::uuids::random_generator()())
{ }

EAGINE_LIB_FUNC
guid guid::nil(void)
{
	return guid( ::boost::uuids::nil_generator()());
}

EAGINE_LIB_FUNC
std::ostream& operator << (std::ostream& out, const guid& id)
{
	out << static_cast< const ::boost::uuids::uuid& >(id);
	return out;
}

} // namespace base
} // namespace EAGine

