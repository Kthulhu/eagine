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

namespace eagine {
namespace unit {

} // namespace unit
} // namespace eagine

#define eagine_PRINT(EXPR) \
	std::cout << "|" << quantity_name(EXPR) << "|" << #EXPR << "| "<< value(EXPR) << unit_symbol(EXPR) << std::endl

int main(void)
{
	using namespace eagine::unit;
	using eagine::unit::time;

	std::cout << eagine::meta::c_str<info<area>::name>::value << std::endl;

	quantity<turn> at{1};
	quantity<radian> ar = at;
	quantity<degree> ad = at;
	quantity<gradian> ag = ad;
	quantity<pi_rad> ap = ag;
	quantity<quarter> aq = ar;

	eagine_PRINT(at);
	eagine_PRINT(ar);
	eagine_PRINT(ad);
	eagine_PRINT(ag);
	eagine_PRINT(ap);

	quantity<minute> tm{2};
	quantity<second> ts = tm;
	quantity<hour> th = tm;

	eagine_PRINT(tm);
	eagine_PRINT(ts);
	eagine_PRINT(th);

	eagine_PRINT(aq/th);
	eagine_PRINT(at/tm);

	quantity<millimeter> lmm{1000};
	quantity<unit<length>> lm{1};
	quantity<kilometer> lkm = lm;
	quantity<unit<mass>> mkg{1};

	quantity<ampere> eca{1};

	eagine_PRINT(eca);
	eagine_PRINT(lm);
	eagine_PRINT(lkm);
	eagine_PRINT(lkm*lm);
	eagine_PRINT(lkm/lm);
	eagine_PRINT(lkm*lkm);
	eagine_PRINT(lkm/lkm);
	eagine_PRINT(lkm/tm);

	eagine_PRINT(lmm*lmm);
	eagine_PRINT(lmm*lmm*lmm);
	eagine_PRINT(lm*lmm);
	eagine_PRINT(lmm*lm);

	eagine_PRINT(mkg*lm/(ts*ts));
	eagine_PRINT(mkg*lm*lm/(ts*ts));
	eagine_PRINT(mkg*lm*lm/(ts*ts*ts));
	eagine_PRINT(mkg*lm*lm/(ts*ts*ts*eca));

	quantity<unit<temperature>> tK{300};

	eagine_PRINT(mkg/(tK*tK));

	auto x = (mkg*mkg)/lm;
	auto y = mkg*(mkg/lm);
	auto z = x+y;
	auto w = x-y;

	eagine_PRINT(z);
	eagine_PRINT(w);

	double bla = (lmm/lkm);

	std::cout << double(lmm/lmm) << std::endl;

	return 0;
}
