/**
 *  @file eagine/eagine_config.hpp
 *  @brief Compile-time configuration options
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_CONFIG_1308191258_HPP
#define EAGINE_CONFIG_1308191258_HPP

#ifndef EAGINE_NO_SITE_CONFIG
# include <eagine/site_config.hpp>
#endif

#ifdef EAGINE_IMPLEMENTING_LIBRARY
# if EAGINE_IMPLEMENTING_LIBRARY
#  define EAGINE_LINK_LIBRARY 1
# endif
#endif

#ifndef EAGINE_LINK_LIBRARY
#define EAGINE_LINK_LIBRARY 0
#endif

#if EAGINE_LINK_LIBRARY
# define EAGINE_LIB_FUNC extern
#else
# define EAGINE_LIB_FUNC inline
#endif

#ifndef EAGINE_DOCUMENTATION_ONLY
#define EAGINE_DOCUMENTATION_ONLY 0
#endif

#ifndef EAGINE_USE_BOOST_LOCALE
#define EAGINE_USE_BOOST_LOCALE EAGINE_BOOST_LOCALE_FOUND
#endif

namespace EAGine {

} // namespace EAGine

#endif // include guard
