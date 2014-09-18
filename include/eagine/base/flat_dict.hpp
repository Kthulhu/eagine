/**
 *  @file eagine/base/flat_dict.hpp
 *  @brief Flat dict.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_FLAT_DICT_1308281038_HPP
#define EAGINE_BASE_FLAT_DICT_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <eagine/base/vector.hpp>
#include <eagine/base/optional.hpp>

#include <cassert>
#include <algorithm>

namespace EAGine {
namespace base {

template <typename Key, typename Val, typename KeyIter, typename ValIter>
class const_flat_range_dict
{
private:
	KeyIter _bkeys, _ekeys;
	ValIter _bvals, _evals;

	KeyIter _klb(const Key& key) const
	{
		using ::std::lower_bound;
		return lower_bound(_bkeys, _ekeys, key);
	}

	std::size_t _koffs(KeyIter pos) const
	{
		using ::std::distance;
		return distance(_bkeys, pos);
	}
public:
	const_flat_range_dict(
		KeyIter bkeys, KeyIter ekeys,
		ValIter bvals, ValIter evals
	): _bkeys(bkeys)
	 , _ekeys(ekeys)
	 , _bvals(bvals)
	 , _evals(evals)
	{ }

	std::size_t size(void) const
	{
		using ::std::distance;
		assert(distance(_bkeys, _ekeys) == distance(_bvals, _evals));
		return distance(_bkeys, _ekeys);
	}

	bool empty(void) const
	{
		return size() == 0;
	}

	template <typename Func>
	void for_each(Func func) const
	{
		KeyIter ikeys = _bkeys;
		ValIter ivals = _bvals;

		while(ikeys != _ekeys)
		{
			assert(ivals != _evals);
			func(*ikeys, *ivals);
			++ikeys;
			++ivals;
		}
	}

	const Key& key_at(std::size_t pos) const
	{
		assert(pos < size());
		return *(_bkeys+pos);
	}

	const Val& val_at(std::size_t pos) const
	{
		assert(pos < size());
		return *(_bvals+pos);
	}

	bool contains(const Key& key) const
	{
		auto pos = _klb(key);
		return ((pos != _ekeys) && (*pos == key));
	}

	Val get(const Key& key, Val not_found) const
	{
		auto pos = _klb(key);

		if((pos != _ekeys) && (*pos == key))
		{
			return *(_bvals+_koffs(pos));
		}
		else return not_found;
	}

	optional<Val> get(const Key& key) const
	{
		auto pos = _klb(key);

		if((pos != _ekeys) && (*pos == key))
		{
			return optional<Val>(*(_bvals+_koffs(pos)));
		}
		else return optional<Val>();
	}
};

template <
	typename Key,
	typename Val,
	typename KAlloc = base::allocator<Key>,
	typename VAlloc = base::allocator<Val>
>
class flat_dict
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
	flat_dict(void) = default;

	flat_dict(const KAlloc& k_alloc, const VAlloc& v_alloc)
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

	void reserve(std::size_t sz)
	{
		_keys.reserve(sz);
		_vals.reserve(sz);
	}

	template <typename Key_, typename Val_>
	void push_back(Key_&& key, Val_&& val)
	{
		assert(_keys.size() == _vals.size());
		assert(_keys.empty() || (_keys.back() < key));

		_keys.push_back(std::forward<Key>(key));
		_keys.push_back(std::forward<Val>(val));
	}

	template <typename Func>
	void for_each(Func func) const
	{
		for(std::size_t i = 0, n = size(); i!=n; ++i)
		{
			func(_keys[i], _vals[i]);
		}
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

	Val store(const Key& key, Val val, Val old)
	{
		auto pos = _klb(key);

		if((pos == _keys.end()) || (key < *pos))
		{
			_vals.insert(_vit(pos), val);
			_keys.insert(pos, key);
		}
		else
		{
			assert(*pos == key);
			auto o = _koffs(pos);
			old = _vals[o];
			_vals[o] = val;
		}
		return old;
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

	Val remove(const Key& key, Val old)
	{
		auto pos = _klb(key);

		if(!(pos == _keys.end()) && !(key < *pos))
		{
			auto vp = _vit(pos);
			old = *vp;
			_vals.erase(vp);
			_keys.erase(pos);
		}
		return old;
	}

	void swap(const Key& k1, const Key& k2)
	{
		auto p1 = _klb(k1);
		auto p2 = _klb(k2);

		bool f1 = (!(p1 == _keys.end()) && !(k1 < *p1));
		bool f2 = (!(p2 == _keys.end()) && !(k2 < *p2));

		if(f1 && f2)
		{
			auto vp1 = _vit(p1);
			auto vp2 = _vit(p2);

			using std::swap;
			swap(*vp1, *vp2);
		}
		else if(f1)
		{
			auto vp1 = _vit(p1);
			Val val = std::move(*vp1);

			_vals.erase(vp1);
			_keys.erase(p1);

			p2 = _klb(k2);

			_vals.insert(_vit(p2), std::move(val));
			_keys.insert(p2, k2);
		}
		else if(f2)
		{
			auto vp2 = _vit(p2);
			Val val = std::move(*vp2);

			_vals.erase(vp2);
			_keys.erase(p2);

			p1 = _klb(k1);

			_vals.insert(_vit(p1), std::move(val));
			_keys.insert(p1, k1);
		}
	}

	bool contains(const Key& key) const
	{
		auto pos = _klb(key);

		return ((pos != _keys.end()) && (*pos == key));
	}

	const Key& key_at(std::size_t pos) const
	{
		assert(pos < _keys.size());
		return _keys.at(pos);
	}

	const Val& val_at(std::size_t pos) const
	{
		assert(pos < _vals.size());
		return _vals.at(pos);
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

	optional<Val> get(const Key& key) const
	{
		auto pos = _klb(key);

		if((pos != _keys.end()) && (*pos == key))
		{
			return optional<Val>(_vals.at(_koffs(pos)));
		}
		else return optional<Val>();
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

