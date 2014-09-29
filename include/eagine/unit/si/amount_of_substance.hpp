/**
 *  @file eagine/unit/si/amount_of_substance.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_AMOUND_OF_SUBSTANCE_1308281038_HPP
#define EAGINE_UNIT_SI_AMOUND_OF_SUBSTANCE_1308281038_HPP

#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {
namespace base {

// mole
struct mole : unit<amount_of_substance, mole> { };

template <>
struct unit_info<mole>
{
	typedef meta::string<'m','o','l','e'> name;
	typedef meta::string<'m','o','l'> symbol;
};

} // namespace base

// si::base_unit<amount_of_substance>
template <>
struct si::base_unit<base::amount_of_substance> : base::mole { };

typedef unit<amount_of_substance, si> mole;

} // namespace unit
} // namespace EAGine

#endif //include guard

