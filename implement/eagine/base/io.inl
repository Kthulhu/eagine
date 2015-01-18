/**
 *  @file eagine/base/io.inl
 *  @brief Implementation of input/output operations.
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eagine/eagine_config.hpp>
#include <eagine/base/locale.hpp>
#include <eagine/base/format.hpp>
#include <eagine/base/string.hpp>
#include <eagine/base/error.hpp>

namespace eagine {
namespace base {
//------------------------------------------------------------------------------
// _fetch_stream_data
//------------------------------------------------------------------------------
template <typename T>
static inline
void _fetch_stream_data(istream& input, vector<T>& buffer)
{
	if(!input.good())
	{
		throw runtime_error(translate(
			"Input stream is not open for reading"
		).str());
	}

	streampos begin = input.tellg();
	input.seekg(0, ios::end);
	streampos end = input.tellg();
	input.seekg(0, ios::beg);

	buffer.resize(end - begin, 0x00);
	if(!input.read((char*)buffer.data(), buffer.size()).good())
	{
		throw runtime_error(translate(
			"Failed to read data from input stream"
		).str());
	}
}
//------------------------------------------------------------------------------
// load_stream_data
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
vector<byte> load_stream_data(istream& input)
{
	vector<byte> buffer;
	_fetch_stream_data(input, buffer);
	return std::move(buffer);
}
//------------------------------------------------------------------------------
// load_file_data
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
vector<byte> load_file_data(const cstrref& fs_path)
{
	ifstream input(c_str(fs_path).get());
	try { return load_stream_data(input); }
	catch(...)
	{
		throw_with_nested(runtime_error((
			format(translate("Failed to load data from file '{1}'"))
			% fs_path.str()
		).str()));
	}
}
//------------------------------------------------------------------------------
// load_stream_text
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
vector<char> load_stream_text(istream& input)
{
	vector<char> buffer;
	_fetch_stream_data(input, buffer);
	return std::move(buffer);
}
//------------------------------------------------------------------------------
// load_file_text
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
vector<char> load_file_text(const cstrref& fs_path)
{
	ifstream input(c_str(fs_path).get());
	try { return load_stream_text(input); }
	catch(...)
	{
		throw_with_nested(runtime_error((
			format(translate("Failed to load text from file '{1}'"))
			% fs_path.str()
		).str()));
	}
}
//------------------------------------------------------------------------------
} // namespace base
} // namespace eagine

