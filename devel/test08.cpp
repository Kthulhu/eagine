/**
 *  .file devel/test08.cpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
//------------------
#include <eagine/base/dl_export.hpp>
#include <eagine/dyli/loader.hpp>
#include <eagine/dyli/content.hpp>
#include <eagine/dyli/product.hpp>
//------------------

struct data
{
	int i;
	double d;
	bool b;
} const g_data { 123, 456.789, false };

EAGINE_DL_PUBLIC(const data*) get_data(void)
{
	return &g_data;
}

EAGINE_DL_PUBLIC(eagine::base::shared_ptr<data>) make_data(void)
{
	data d = {23, 45.67, true};
	return eagine::base::make_shared<data>(d);
}


int main(void)
{
	using namespace eagine;

	try
	{
		using namespace eagine::dyli;

		dyli::loader ldr;
		dyli::library lib = ldr.load("libm.so");

		dyli::weak_lib wlib = lib;
		dyli::function<double(double)> sin;

		if(dyli::library lib2 = wlib)
		{
			sin = lib2.function<double(double)>("sin");

			dyli::weak_func<double(double)> wsin = sin;

			std::cout << wsin.require()(1) << std::endl;
			std::cout << wsin(2) << std::endl;
		}

		lib.release();

		std::cout << sin(3) << std::endl;

		dyli::weak_func<double(double)> wsin = sin;
		
		std::cout << wsin(4) << std::endl;

		sin.release();

		dyli::library exe = ldr.main_exe();

		dyli::function<dyli::content<data>(void)> gd =
			exe.function<dyli::content<data>(void)>("get_data");
		dyli::content<data> cd = gd();
		dyli::weak_cont<data> wcd = cd;
		dyli::content<data> cd2 = wcd;
		std::cout << cd2->i << std::endl;

		dyli::function<dyli::product<data>(void)> md =
			exe.function<dyli::product<data>(void)>("make_data");
		dyli::product<data> pd = md();
		dyli::weak_prod<data> wpd = pd;
		dyli::product<data> pd2 = wpd;
		std::cout << pd2->i << std::endl;

		std::cout << wsin(5) << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
