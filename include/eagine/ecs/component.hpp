/**
 *  @file eagine/ecs/component.hpp
 *  @brief E/CS component-related types and constants.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_ECS_COMPONENT_1408161720_HPP
#define EAGINE_ECS_COMPONENT_1408161720_HPP

#include <eagine/meta/type_traits.hpp>
#include <cstddef>
#include <map>

namespace EAGine {
namespace ecs {

// Component access key type
typedef std::size_t component_key_t;

// nil component key value
constexpr component_key_t nil_component_key = ~(component_key_t(0));

// component unique identifier
typedef std::size_t component_uid;

class component_uid_getter
{
private:static component_uid& _curr_uid(void);
public: static component_uid new_uid(void);
};

template <typename Derived>
class component
{
public:
	static component_uid uid(void)
	{
		static component_uid cid = component_uid_getter::new_uid();
		return cid;
	}
};

template <typename X>
inline component_uid get_component_uid(void)
{
	typedef typename meta::remove_const<
		typename meta::remove_reference<X>::type
	>::type Component;
	return Component::uid();
}

template <typename T>
class component_uid_map
 : public base::vector<T>
{
public:
	component_uid_map(void) = default;

	typename base::vector<T>::const_iterator
	find(component_uid cid) const
	{
		if(cid < this->size())
		{
			return this->begin()+cid;
		}
		else return this->end();
	}

	typename base::vector<T>::iterator
	find(component_uid cid)
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

	T& operator [] (component_uid cid)
	{
		if(cid >= this->size())
		{
			this->resize(cid+1);
		}
		return this->at(cid);
	}
};

// interface for maps of entities to component access keys
template <typename Entity>
struct entity_component_map
{
	typedef component_key_t key_t;

	virtual ~entity_component_map(void) noexcept { }

	virtual bool read_only(void) const = 0;

	virtual std::size_t size(void) = 0;

	virtual const Entity& entity(std::size_t pos) = 0;

	virtual key_t key(std::size_t pos) = 0;

	virtual key_t find(const Entity& ent) = 0;

	virtual void reserve(std::size_t count) = 0;

	virtual key_t store(const Entity& ent, key_t key) = 0;

	virtual key_t remove(const Entity& ent) = 0;

	virtual void swap(const Entity& e1, const Entity& e2) = 0;
};

} // namespace ecs
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/ecs/component.inl>
#endif

#endif //include guard

