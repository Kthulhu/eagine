/**
 *  .file devel/test16.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
//--
#include <eagine/unit/quantity.hpp>
#include <eagine/unit/info.hpp>
#include <eagine/unit/si.hpp>
#include <eagine/unit/si/force.hpp>
#include <eagine/unit/si/energy.hpp>
#include <eagine/unit/si/power.hpp>
#include <eagine/unit/si/electric_tension.hpp>
#include <eagine/unit/derived.hpp>

namespace EAGine {
namespace unit {

} // namespace unit
} // namespace EAGine

#define EAGine_PRINT(EXPR) \
	std::cout << "|" << quantity_name(EXPR) << "|" << #EXPR << "| "<< value(EXPR) << unit_symbol(EXPR) << std::endl

int main(void)
{
	using namespace EAGine::unit;
	using EAGine::unit::time;

	std::cout << EAGine::meta::c_str<info<area>::name>::value << std::endl;

	quantity<turn> at = {1};
	quantity<radian> ar = at;
	quantity<degree> ad = at;
	quantity<gradian> ag = ad;
	quantity<pi_rad> ap = ag;
	quantity<quarter> aq = ar;

	EAGine_PRINT(at);
	EAGine_PRINT(ar);
	EAGine_PRINT(ad);
	EAGine_PRINT(ag);
	EAGine_PRINT(ap);

	quantity<minute> tm = {2};
	quantity<second> ts = tm;
	quantity<hour> th = tm;

	EAGine_PRINT(tm);
	EAGine_PRINT(ts);
	EAGine_PRINT(th);

	EAGine_PRINT(aq/th);
	EAGine_PRINT(at/tm);

	quantity<millimeter> lmm = {1000};
	quantity<unit<length>> lm = {1};
	quantity<kilometer> lkm = lm;
	quantity<unit<mass>> mkg = {1};

	quantity<ampere> eca = {1};

	EAGine_PRINT(eca);
	EAGine_PRINT(lm);
	EAGine_PRINT(lkm);
	EAGine_PRINT(lkm*lm);
	EAGine_PRINT(lkm/lm);
	EAGine_PRINT(lkm*lkm);
	EAGine_PRINT(lkm/lkm);
	EAGine_PRINT(lkm/tm);

	EAGine_PRINT(lmm*lmm);
	EAGine_PRINT(lmm*lmm*lmm);
	EAGine_PRINT(lm*lmm);
	EAGine_PRINT(lmm*lm);

	EAGine_PRINT(mkg*lm/(ts*ts));
	EAGine_PRINT(mkg*lm*lm/(ts*ts));
	EAGine_PRINT(mkg*lm*lm/(ts*ts*ts));
	EAGine_PRINT(mkg*lm*lm/(ts*ts*ts*eca));


	auto x = (mkg*mkg)/lm;
	auto y = mkg*(mkg/lm);
	auto z = x+y;
	auto w = x-y;

	EAGine_PRINT(z);
	EAGine_PRINT(w);

	return 0;
}
