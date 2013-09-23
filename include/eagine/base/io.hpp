/**
 *  @file eagine/base/io.hpp
 *  @brief Basic input/output.
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_IO_1308281038_HPP
#define EAGINE_BASE_IO_1308281038_HPP

#include <eagine/base/type.hpp>
#include <eagine/base/vector.hpp>

#include <iostream>
#include <fstream>

namespace EAGine {
namespace base {

using ::std::istream;
using ::std::ostream;
using ::std::ifstream;
using ::std::ofstream;

using ::std::streampos;
using ::std::ios;

vector<byte> load_stream_data(istream& input);
vector<byte> load_file_data(const char* fs_path);

} // namespace base
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/io.inl>
#endif

#endif //include guard

