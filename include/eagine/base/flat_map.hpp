/**
 *  @file eagine/base/flat_map.hpp
 *  @brief Flat map.
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_FLAT_MAP_1308281038_HPP
#define EAGINE_BASE_FLAT_MAP_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <eagine/base/vector.hpp>

#include <cassert>
#include <algorithm>

namespace EAGine {
namespace base {

template <
	typename Key,
	typename Val,
	typename KAlloc = base::allocator<Key>,
	typename VAlloc = base::allocator<Val>
>
class flat_map
{
private:
	base::vector<Key, KAlloc> _keys;
	base::vector<Val, VAlloc> _vals;

	typename base::vector<Key, KAlloc>::iterator
	_klb(const Key& key)
	{
		return std::lower_bound(_keys.begin(), _keys.end(), key);
	}

	typename base::vector<Key, KAlloc>::const_iterator
	_klb(const Key& key) const
	{
		return std::lower_bound(_keys.begin(), _keys.end(), key);
	}

	std::size_t _koffs(
		const typename base::vector<Key, KAlloc>::const_iterator& pos
	) const
	{
		return std::distance(_keys.begin(), pos);
	}

	typename base::vector<Val, VAlloc>::iterator _vit(
		const typename base::vector<Key, KAlloc>::const_iterator& pos
	)
	{
		if(_vals.empty())
		{
			return _vals.end();
		}
		else
		{
			assert(_koffs(pos) <= _vals.size());
			return _vals.begin()+_koffs(pos);
		}
	}
public:
	flat_map(void) = default;

	flat_map(const KAlloc& k_alloc, const VAlloc& v_alloc)
	 : _keys(k_alloc)
	 , _vals(v_alloc)
	{ }

	bool empty(void) const
	{
		assert(_keys.empty() == _vals.empty());
		return _keys.empty();
	}

	std::size_t size(void) const
	{
		assert(_keys.size() == _vals.size());
		return _keys.size();
	}

	void reserve(std::size_t size)
	{
		_keys.reserve(size);
		_vals.reserve(size);
	}

	template <typename Key_, typename Val_>
	void push_back(Key_&& key, Val_&& val)
	{
		assert(_keys.size() == _vals.size());
		assert(_keys.empty() || (_keys.back() < key));

		_keys.push_back(std::forward<Key>(key));
		_keys.push_back(std::forward<Val>(val));
	}

	bool insert(const Key& key, Val val)
	{
		auto pos = _klb(key);

		if((pos == _keys.end()) || (key < *pos))
		{
			_vals.insert(_vit(pos), val);
			_keys.insert(pos, key);
			return true;
		}
		else
		{
			assert(*pos == key);
			_vals[_koffs(pos)] = val;
			return false;
		}
	}

	bool erase(const Key& key)
	{
		auto pos = _klb(key);

		if(!(pos == _keys.end()) && !(key < *pos))
		{
			_vals.erase(_vit(pos));
			_keys.erase(pos);
			return true;
		}
		else return false;
	}

	Val get(const Key& key, Val not_found) const
	{
		auto pos = _klb(key);

		if((pos != _keys.end()) && (*pos == key))
		{
			return _vals.at(_koffs(pos));
		}
		else return not_found;
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

