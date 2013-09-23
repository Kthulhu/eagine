/**
 *  @file eagine/base/io.inl
 *  @brief Implementation of input/output operations.
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eagine/eagine_config.hpp>
#include <eagine/base/locale.hpp>
#include <eagine/base/format.hpp>
#include <eagine/base/string.hpp>
#include <eagine/base/error.hpp>

namespace EAGine {
namespace base {

EAGINE_LIB_FUNC
vector<byte> load_stream_data(istream& input)
{
	if(!input.good())
	{
		throw runtime_error(string(
			translate("Input stream is not open for reading")
		));
	}

	streampos begin = input.tellg();
	input.seekg(0, ios::end);
	streampos end = input.tellg();
	input.seekg(0, ios::beg);

	vector<byte> buffer(end - begin, 0x00);
	if(!input.read((char*)buffer.data(), buffer.size()).good())
	{
		throw runtime_error(string(
			translate("Failed to read data from input stream")
		));
	}

	return std::move(buffer);
}

EAGINE_LIB_FUNC
vector<byte> load_file_data(const char* fs_path)
{
	ifstream input(fs_path);
	try { return load_stream_data(input); }
	catch(...)
	{
		throw_with_nested(runtime_error((
			format(translate("Failed to load data from file '{1}'"))
			% fs_path
		).str()));
	}
}

} // namespace base
} // namespace EAGine

