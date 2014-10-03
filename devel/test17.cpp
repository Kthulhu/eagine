/**
 *  .file devel/test17.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
//--
#include <eagine/unit/poly/quantity.hpp>
//--
#include <eagine/unit/quantity.hpp>
#include <eagine/unit/info.hpp>
#include <eagine/unit/dimensionless.hpp>
#include <eagine/unit/si.hpp>
#include <eagine/unit/si/force.hpp>
#include <eagine/unit/si/energy.hpp>
#include <eagine/unit/si/power.hpp>
#include <eagine/unit/si/electric_tension.hpp>
#include <eagine/unit/derived.hpp>

namespace EAGine {
namespace unit {
namespace poly {


} // namespace poly
} // namespace unit
} // namespace EAGine

int main(void)
{
	using namespace EAGine::unit;
	using EAGine::unit::time;

	poly::dimension m((mass()));
	poly::dimension L((length()));
	poly::dimension t((time()));
	poly::dimension I((electric_current()));
	poly::dimension C((electric_charge()));
	poly::dimension V((electric_tension()));
	poly::dimension R((electrical_resistance()));
	poly::dimension S((electrical_conductance()));
	poly::dimension A((area()));
	poly::dimension v((velocity()));
	poly::dimension a((acceleration()));
	poly::dimension F((force()));
	poly::dimension E((energy()));
	poly::dimension P((power()));

	auto x = (m*L*L/(t*t*t));

	auto f = [](const poly::combined_dimension& cd) -> bool
	{
		bool first = true;
		int pc = 0;
		int ic = 0;
		for(auto& p : cd)
		{
			if(p.second > 0)
			{
				if(first) first = false;
				else std::cout << "*";
				std::cout << p.first.name();
				if(p.second != 1)
				{
					std::cout << "^";
					std::cout << p.second;
				}
				++pc;
			}
			else if(p.second < 0)
			{
				++ic;
			}
		}
		if(ic)
		{
			first = true;

			if(pc == 0) std::cout << "1/";
			else std::cout << "/";

			if(ic > 1) std::cout << "(";

			for(auto& p : cd)
			{
				if(p.second < 0)
				{
					if(first) first = false;
					else std::cout << "*";
					
					std::cout << p.first.name();
					if(p.second != -1)
					{
						std::cout << "^";
						std::cout << -p.second;
					}
				}
			}

			if(ic > 1) std::cout << ")";
		}
		
		std::cout << std::endl;
		return true;
	};

	x.enumerate_combinations(f, 3);

	poly::quantity<double> q1(1, !meter()/!minute());

	poly::quantity<double> ql(7.2, kilometer());
	poly::quantity<double> qt(1, hour());

	//poly::quantity<double> q(ql/qt);
	poly::quantity<double> q(ql/qt, q1.value_unit());


	std::cout << q.dim().name() << ": ";
	std::cout << q.value();
	std::cout << q.value_unit().symbol() << std::endl;

	return 0;
}
