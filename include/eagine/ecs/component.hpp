/**
 *  @file eagine/ecs/component.hpp
 *  @brief E/CS component-related types and constants.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_COMPONENT_1408161720_HPP
#define EAGINE_ECS_COMPONENT_1408161720_HPP

#include <eagine/base/vector.hpp>
#include <eagine/meta/type_traits.hpp>
#include <cstddef>

namespace EAGine {
namespace ecs {

// component unique identifier
typedef std::size_t component_uid_t;

// component_uid_getter
class component_uid_getter
{
private:
	static component_uid_t& _curr_uid(void);
public:
	static component_uid_t new_uid(void);
};

// component_uid
template <typename Derived>
struct component_uid
{
	static component_uid_t value(void)
	{
		static component_uid_t cid = component_uid_getter::new_uid();
		return cid;
	}

	component_uid_t operator()(void) const
	{
		return value();
	}
};

// component - base class
template <typename Derived>
struct component
{
	static component_uid<Derived> uid;
};

template <typename Derived>
component_uid<Derived> component<Derived>::uid = {};

// get_component_uid
template <typename X>
inline component_uid_t get_component_uid(void)
{
	typedef typename meta::remove_const<
		typename meta::remove_reference<X>::type
	>::type Component;
	return Component::uid();
}

// component_uid_map
template <typename T>
class component_uid_map
 : public base::vector<T>
{
public:
	component_uid_map(void) = default;

	typename base::vector<T>::const_iterator
	find(component_uid_t cid) const
	{
		if(cid < this->size())
		{
			return this->begin()+cid;
		}
		else return this->end();
	}

	typename base::vector<T>::iterator
	find(component_uid_t cid)
	{
		if(cid < this->size())
		{
			return this->begin()+cid;
		}
		else return this->end();
	}

	void erase(typename base::vector<T>::iterator pos)
	{
		*pos = T();
	}

	T& operator [] (component_uid_t cid)
	{
		if(cid >= this->size())
		{
			this->resize(cid+1);
		}
		return this->at(cid);
	}
};

} // namespace ecs
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/ecs/component.inl>
#endif

#endif //include guard

