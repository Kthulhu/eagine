/**
 *  @file eagine/base/file_mapping.hpp
 *  @brief File memory mapping.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_FILE_MAPPING_1408161723_HPP
#define EAGINE_BASE_FILE_MAPPING_1408161723_HPP

#include <eagine/base/string.hpp>
#include <eagine/base/access_type.hpp>
#include <eagine/base/memory_block.hpp>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace eagine {
namespace base {

class mapped_file_region;

class file_mapping
{
private:
	friend class mapped_file_region;

	::boost::interprocess::mode_t _bmode;
	::boost::interprocess::file_mapping _bfile_map;

	static ::boost::interprocess::mode_t _get_mode(
		access_read_only_t
	)
	{
		return ::boost::interprocess::read_only;
	}

	static ::boost::interprocess::mode_t _get_mode(
		access_read_write_t
	)
	{
		return ::boost::interprocess::read_write;
	}
public:
	template <typename Access>
	file_mapping(cstrref path, Access access)
	 : _bmode(_get_mode(access))
	 , _bfile_map(
		path.null_terminated()?
		path.data():
		path.str().c_str(),
		 _bmode
	)
	{ }

	file_mapping(file_mapping&&) = default;
	file_mapping& operator = (file_mapping&&) = default;
};

class mapped_file_region
{
private:
	::boost::interprocess::mapped_region _bmap_reg;
public:
	mapped_file_region(file_mapping& fm)
	 : _bmap_reg(fm._bfile_map, fm._bmode)
	{ }

	mapped_file_region(
		file_mapping& fm,
		std::size_t offset,
		std::size_t size_
	): _bmap_reg(fm._bfile_map, fm._bmode, offset, size_)
	{ }

	mapped_file_region(mapped_file_region&&) = default;
	mapped_file_region& operator = (mapped_file_region&&) = default;

	void* address(void) const
	{
		return _bmap_reg.get_address();
	}

	std::size_t size(void) const
	{
		return _bmap_reg.get_size();
	}

	memory_block block(void) const
	{
		return memory_block(address(), size());
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

