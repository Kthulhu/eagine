/**
 *  @file eagine/base/file_content.hpp
 *  @brief File content.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_FILE_CONTENT_1408161723_HPP
#define EAGINE_BASE_FILE_CONTENT_1408161723_HPP

#include <eagine/base/file_mapping.hpp>

namespace EAGine {
namespace base {

class file_content
{
private:
	file_mapping _fm;
	mapped_file_region _mr;
public:
	file_content(cstrref path)
	 : _fm(path, access_read_only)
	 , _mr(_fm)
	{ }

	const void* data(void) const
	{
		return _mr.address();
	}

	std::size_t size(void) const
	{
		return _mr.size();
	}

	const_memory_block block(void) const
	{
		return const_memory_block(data(), size());
	}

	template <typename Ptr>
	operator basic_memory_block<Ptr> (void) const
	{
		return basic_memory_block<Ptr>(data(), size());
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

