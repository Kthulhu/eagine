/**
 *  .file devel/test26.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/base/static_variant.hpp>
//------------------
#include <iostream>
#include <exception>
#include <tuple>

namespace eagine {
namespace base {

struct point
{
	float x,y;

	void render(std::ostream& out) const
	{
		out << "{x: " << x << ", y: " << y << "}";
	}
};

struct line
{
	point a, b;

	void render(std::ostream& out) const
	{
		out << "{a: ";
		a.render(out);
		out << ", b: ";
		b.render(out);
		out << "}";
	}
};

struct circle
{
	point center;
	float radius;

	void render(std::ostream& out) const
	{
		out << "{center: ";
		center.render(out);
		out << ", radius: " << radius << "}";
	}
};

struct rectangle
{
	point left_bottom;
	point right_top;

	void render(std::ostream& out) const
	{
		out << "{left_bottom: ";
		left_bottom.render(out);
		out << ", right_top: ";
		right_top.render(out);
		out << "}";
	}
};

struct triangle
{
	point a, b, c;

	void render(std::ostream& out) const
	{
		out << "{a: ";
		a.render(out);
		out << ", b: ";
		b.render(out);
		out << ", c: ";
		c.render(out);
		out << "}";
	}
};


struct render_shape
{
private:
	std::ostream& _out;
public:
	constexpr
	render_shape(std::ostream& out)
	 : _out(out)
	{ }

	template <typename T>
	void operator()(const T& p) const
	{
		p.render(_out);
	}
};

struct shape
 : static_variant<void, 4, point, line, circle, rectangle, triangle>
{
public:
	std::ostream& render(std::ostream& out)
	{
		render_shape r = {out};
		this->accept(r);
		return out;
	}
};

struct test
{
	const unsigned v0;
	point s0;
	const unsigned v1;
	triangle s1;
	const unsigned v2;
	circle s2;
};

} // namespace base
} // namespace eagine

int main(int argc, const char**)
{
	using namespace eagine::base;

	static_variant_dispatcher<
		static_variant<void, 4, point, line, circle, rectangle, triangle>,
		render_shape
	> svd;

	render_shape rs = {std::cout};

	test t = {
		0, {1.f, 2.f},
		3, {{3.f, 4.f},{5.f, 6.f},{7.f, 8.f}},
		1, {{7.f, 8.f}, 9.f}
	};

	(*((shape*)(void*)&t.v0)).render(std::cout) << std::endl;
	(*((shape*)(void*)&t.v1)).render(std::cout) << std::endl;
	(*((shape*)(void*)&t.v2)).render(std::cout) << std::endl;

	std::cout << std::endl;
	svd(*((shape*)(void*)&t.v0), rs);
	std::cout << std::endl;
	svd(*((shape*)(void*)&t.v1), rs);
	std::cout << std::endl;
	svd(*((shape*)(void*)&t.v2), rs);
	std::cout << std::endl;

	return 0;
}
