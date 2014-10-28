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
#include <cstring>

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
// guid::to_string
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
string
guid::to_string(void) const
{
	return ::boost::uuids::to_string(*this);
}
//------------------------------------------------------------------------------
// guid::to_lim_string
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
lim_string<36>
guid::to_lim_string(void) const
{
	static const char hd[16] = {
		'0','1','2','3','4','5','6','7',
		'8','9','a','b','c','d','e','f'
	};
	return {
		hd[(data[ 0] >> 4) & 0x0F],
		hd[(data[ 0] >> 0) & 0x0F],
		hd[(data[ 1] >> 4) & 0x0F],
		hd[(data[ 1] >> 0) & 0x0F],
		hd[(data[ 2] >> 4) & 0x0F],
		hd[(data[ 2] >> 0) & 0x0F],
		hd[(data[ 3] >> 4) & 0x0F],
		hd[(data[ 3] >> 0) & 0x0F],
		'-',
		hd[(data[ 4] >> 4) & 0x0F],
		hd[(data[ 4] >> 0) & 0x0F],
		hd[(data[ 5] >> 4) & 0x0F],
		hd[(data[ 5] >> 0) & 0x0F],
		'-',
		hd[(data[ 6] >> 4) & 0x0F],
		hd[(data[ 6] >> 0) & 0x0F],
		hd[(data[ 7] >> 4) & 0x0F],
		hd[(data[ 7] >> 0) & 0x0F],
		'-',
		hd[(data[ 8] >> 4) & 0x0F],
		hd[(data[ 8] >> 0) & 0x0F],
		hd[(data[ 9] >> 4) & 0x0F],
		hd[(data[ 9] >> 0) & 0x0F],
		'-',
		hd[(data[10] >> 4) & 0x0F],
		hd[(data[10] >> 0) & 0x0F],
		hd[(data[11] >> 4) & 0x0F],
		hd[(data[11] >> 0) & 0x0F],
		hd[(data[12] >> 4) & 0x0F],
		hd[(data[12] >> 0) & 0x0F],
		hd[(data[13] >> 4) & 0x0F],
		hd[(data[13] >> 0) & 0x0F],
		hd[(data[14] >> 4) & 0x0F],
		hd[(data[14] >> 0) & 0x0F],
		hd[(data[15] >> 4) & 0x0F],
		hd[(data[15] >> 0) & 0x0F]
	};
}
//------------------------------------------------------------------------------
// guid::is_valid_string
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
bool guid::is_valid_string(const cstrref& str)
{
	if(str.size() != 36) return false;

	static const char* h = "0123456789abcdefABCDEF";
	static const char* c = "-";
	static const char* m = "000000001000010000100001000000000000";
	static const char* x[2] = {h, c};

	for(unsigned i=0; i<36; ++i)
	{
		if(!std::strchr(x[int(m[i]-'0')], str[i]))
			return false;
	}
	return true;
}
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

