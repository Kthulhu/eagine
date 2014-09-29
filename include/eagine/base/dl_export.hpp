/**
 *  @file eagine/base/dl_export.hpp
 *  @brief Helpers for declaring exported library functions
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_DL_EXPORT_1308281038_HPP
#define EAGINE_BASE_DL_EXPORT_1308281038_HPP

#define EAGINE_DL_PUBLIC(...) \
extern "C" __attribute__((visibility("default"))) __VA_ARGS__

#define EAGINE_DL_PRIVATE(...) \
__attribute__((visibility("hidden"))) __VA_ARGS__

#endif //include guard

