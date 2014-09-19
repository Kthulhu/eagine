/**
 *  @file eagine/base/flat_bag.hpp
 *  @brief Flat bag.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_FLAT_BAG_1308281038_HPP
#define EAGINE_BASE_FLAT_BAG_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <eagine/base/vector.hpp>

#include <cassert>
#include <algorithm>

namespace EAGine {
namespace base {

template <
	typename Item,
	typename Alloc = base::allocator<Item>
>
class flat_bag
{
private:
	base::vector<Item, Alloc> _items;

	typename base::vector<Item, Alloc>::iterator
	_ilb(const Item& item)
	{
		return std::lower_bound(_items.begin(), _items.end(), item);
	}

	typename base::vector<Item, Alloc>::const_iterator
	_ilb(const Item& item) const
	{
		return std::lower_bound(_items.begin(), _items.end(), item);
	}
public:
	flat_bag(void) = default;

	flat_bag(const Alloc& alloc)
	 : _items(alloc)
	{ }

	bool empty(void) const
	{
		return _items.empty();
	}

	std::size_t size(void) const
	{
		return _items.size();
	}

	void reserve(std::size_t sz)
	{
		_items.reserve(sz);
	}

	template <typename Item_>
	void push_back(Item_&& item)
	{
		assert(_items.empty() || (_items.back() < item));

		_items.push_back(std::forward<Item>(item));
	}

	template <typename Func>
	void for_each(Func func) const
	{
		for(std::size_t i = 0, n = size(); i!=n; ++i)
		{
			func(_items[i]);
		}
	}

	bool insert(const Item& item)
	{
		auto pos = _ilb(item);

		if((pos == _items.end()) || (item < *pos))
		{
			_items.insert(pos, item);
			return true;
		}
		else
		{
			assert(*pos == item);
			return false;
		}
	}

	bool remove(const Item& item)
	{
		auto pos = _ilb(item);

		if(!(pos == _items.end()) && !(item < *pos))
		{
			_items.erase(pos);
			return true;
		}
		else return false;
	}

	bool contains(const Item& item) const
	{
		auto pos = _ilb(item);

		return ((pos != _items.end()) && (*pos == item));
	}

	const Item& item_at(std::size_t pos) const
	{
		assert(pos < _items.size());
		return _items.at(pos);
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

