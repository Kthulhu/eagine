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
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace EAGine {
namespace base {
//------------------------------------------------------------------------------
// guid::guid
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
guid::guid(const ::boost::uuids::uuid& that)
 : ::boost::uuids::uuid(that)
{ }
//------------------------------------------------------------------------------
// guid::guid
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
guid::guid(void)
 : ::boost::uuids::uuid( ::boost::uuids::random_generator()())
{ }
//------------------------------------------------------------------------------
// guid::guid
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
guid::guid(const cstrref& str)
 : ::boost::uuids::uuid( ::boost::uuids::string_generator()(
	str.null_terminated()?
	str.data():
	str.str().c_str()
))
{ }
//------------------------------------------------------------------------------
// guid::guid
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
guid::guid(std::nullptr_t)
 : ::boost::uuids::uuid( ::boost::uuids::nil_generator()())
{ }
//------------------------------------------------------------------------------
// guid::nil
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
guid guid::nil(void)
{
	return guid( ::boost::uuids::nil_generator()());
}
//------------------------------------------------------------------------------
// guid operator <<
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
std::ostream& operator << (std::ostream& out, const guid& id)
{
	out << static_cast< const ::boost::uuids::uuid& >(id);
	return out;
}
//------------------------------------------------------------------------------
} // namespace base
} // namespace EAGine

