/**
 *  @file eagine/base/vectre.hpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_VECTRE_1308281038_HPP
#define EAGINE_BASE_VECTRE_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <eagine/base/vector.hpp>
#include <eagine/meta/type_traits.hpp>
#include <cassert>

namespace EAGine {
namespace base {

template <typename T, typename Alloc = allocator<T>>
class vectre
{
private:
	static constexpr std::size_t _default_unit = 4*1024;

	Alloc _alloc;
	std::size_t _unit;
	std::size_t _size;
	std::size_t _last;

	typedef vector<T, Alloc> _chunk_t;
	vector<_chunk_t> _chunks;

	bool _last_ok(void) const
	{
		if(_last > _chunks.size())
		{
			return false;
		}
		for(std::size_t i=1; i<_last; ++i)
		{
			if(_chunks[i-1].size() != _unit)
			{
				return false;
			}
		}
		for(std::size_t i=_last+1; i<=_chunks.size(); ++i)
		{
			if(_chunks[i-1].size() != 0)
			{
				return false;
			}
		}
		return true;
	}

	_chunk_t& _lc(void)
	{
		assert(_last_ok());
		return _chunks[_last-1];
	}

	const _chunk_t& _lc(void) const
	{
		assert(_last_ok());
		return _chunks[_last-1];
	}

	void _prepare_space(std::size_t n)
	{
		assert(_last_ok());
		std::size_t l = _last;

		while(true)
		{
			std::size_t m = (l?_unit - _chunks[l-1].size():0);

			if(n > m)
			{
				assert(l <= _chunks.size());
				if(l == _chunks.size())
				{
					_chunks.emplace_back(_alloc);
				}
				_chunks[l++].reserve(_unit);

				n -= m;
				if(n > _unit)
				{
					n -= _unit;
				}
				else break;
			}
			else break;
		}
	}

	template <typename V>
	struct _iterator
	{
		V* _v;
		std::size_t _i, _j;

		typedef typename meta::add_same_constness<V, T>::type
			value_type;
		typedef value_type& reference;
		typedef value_type* pointer;

		typedef std::ptrdiff_t difference_type;

		_iterator(void)
		noexcept
		 : _v(nullptr)
		 , _i(0)
		 , _j(0)
		{ }

		_iterator(V& vr)
		noexcept
		 : _v(&vr)
		 , _i(0)
		 , _j(0)
		{ }

		_iterator(V& vr, std::size_t p)
		noexcept
		 : _v(&vr)
		 , _i(p / vr._unit)
		 , _j(p % vr._unit)
		{ }

		_iterator(V& vr, std::size_t i, std::size_t j)
		noexcept
		 : _v(&vr)
		 , _i(i)
		 , _j(j)
		{ }

		friend bool operator == (
			const _iterator& a,
			const _iterator& b
		) noexcept
		{
			assert(a._v == b._v);
			return	(a._j == b._j) &&
				(a._i == b._i);
		}

		friend bool operator != (
			const _iterator& a,
			const _iterator& b
		) noexcept
		{
			assert(a._v == b._v);
			return	(a._j != b._j) ||
				(a._i != b._i);
		}

		friend bool operator <  (
			const _iterator& a,
			const _iterator& b
		) noexcept
		{
			assert(a._v == b._v);
			if(a._i <  b._i) return true;
			if(a._i == b._i) return (a._j < b._j);
			return false;
		}

		friend bool operator <= (
			const _iterator& a,
			const _iterator& b
		) noexcept
		{
			assert(a._v == b._v);
			if(a._i <  b._i) return true;
			if(a._i == b._i) return (a._j <= b._j);
			return false;
		}

		friend bool operator >  (
			const _iterator& a,
			const _iterator& b
		) noexcept
		{
			assert(a._v == b._v);
			if(a._i >  b._i) return true;
			if(a._i == b._i) return (a._j > b._j);
			return false;
		}

		friend bool operator >= (
			const _iterator& a,
			const _iterator& b
		) noexcept
		{
			assert(a._v == b._v);
			if(a._i >  b._i) return true;
			if(a._i == b._i) return (a._j >= b._j);
			return false;
		}

		friend difference_type operator - (
			const _iterator& a,
			const _iterator& b
		) noexcept
		{
			assert(a._v == b._v);
			assert(a._v != nullptr);
			return	(a._i - b._i)*a._v->_unit+
				(a._i - b._i);
		}

		friend _iterator operator + (
			const _iterator& a,
			difference_type d
		) noexcept
		{
			assert(a._v != nullptr);
			return _iterator(
				a._v,
				a._i+d/a._v->_unit,
				a._j+d%a._v->_unit
			);
		}

		_iterator& operator ++ (void)
		noexcept
		{
			assert(_v != nullptr);
			if(++_j == _v->_unit)
			{
				++_i;
				_j=0;
			}
			return *this;
		}

		reference operator * (void) const
		{
			assert(_v != nullptr);
			assert(_i < _v->_chunks.size());
			assert(_j < _v->_chunks[_i].size());
			return _v->_chunks[_i][_j];
		}
	};
	friend class _iterator<vectre>;
	friend class _iterator<const vectre>;
public:
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* pointer;
	typedef const T* const_pointer;

	typedef _iterator<vectre> iterator;
	typedef _iterator<const vectre> const_iterator;

	vectre(void)
	noexcept
	 : _unit(_default_unit)
	 , _size(0)
	 , _last(0)
	{ }

	vectre(const vectre&) = default;
	vectre(vectre&&) = default;

	vectre(std::size_t unit)
	noexcept
	 : _unit(unit)
	 , _size(0)
	 , _last(0)
	{ }

	vectre(const Alloc& alloc)
	noexcept
	 : _alloc(alloc)
	 , _unit(_default_unit)
	 , _size(0)
	 , _last(0)
	{ }

	vectre(std::size_t unit, const Alloc& alloc)
	noexcept
	 : _alloc(alloc)
	 , _unit(unit)
	 , _size(0)
	 , _last(0)
	{ }

	std::size_t unit_size(void) const
	noexcept
	{
		return _unit;
	}

	std::size_t capacity(void) const
	noexcept
	{
		std::size_t r = 0;
		for(const _chunk_t& c : _chunks)
		{
			r += c.capacity();
		}
		return r;
	}

	std::size_t count(void) const
	noexcept
	{
		std::size_t r = 0;
		for(const _chunk_t& c : _chunks)
		{
			r += c.size();
		}
		return r;
	}

	std::size_t size(void) const
	noexcept
	{
		assert(_size == count());
		return _size;
	}

	bool empty(void) const
	noexcept
	{
		return size() != 0;
	}

	void reserve(std::size_t n)
	{
		if(n > _size)
		{
			_prepare_space(n-_size);
		}
	}

	T& front(void)
	noexcept
	{
		assert(!_chunks.empty());
		return _chunks.front().front();
	}

	const T& front(void) const
	noexcept
	{
		assert(!_chunks.empty());
		return _chunks.front().front();
	}

	T& back(void)
	noexcept
	{
		assert(!_chunks.empty());
		return _chunks._lc().back();
	}

	const T& back(void) const
	noexcept
	{
		assert(!_chunks.empty());
		return _chunks._lc().back();
	}

	T& at(std::size_t pos)
	noexcept
	{
		assert(pos < size());
		std::size_t i = pos / _unit;
		std::size_t j = pos % _unit;

		return _chunks[i][j];
	}

	const T& at(std::size_t pos) const
	noexcept
	{
		assert(pos < size());
		std::size_t i = pos / _unit;
		std::size_t j = pos % _unit;

		return _chunks[i][j];
	}

	T& operator [](std::size_t pos)
	noexcept
	{
		return at(pos);
	}

	const T& operator [](std::size_t pos) const
	noexcept
	{
		return at(pos);
	}

	iterator begin(void)
	noexcept
	{
		return iterator(*this);
	}

	const_iterator begin(void) const
	noexcept
	{
		return const_iterator(*this);
	}

	iterator end(void)
	noexcept
	{
		return iterator(*this, _size);
	}

	const_iterator end(void) const
	noexcept
	{
		return const_iterator(*this, _size);
	}

	void push_back(const T& value)
	{
		_prepare_space(1);
		if((_last == 0) || (_lc().size() == _unit))
		{
			++_last;
		}
		_lc().push_back(value);
		++_size;
	}

	template <typename ... Arg>
	void emplace_back(Arg&& ... arg)
	{
		_prepare_space(1);
		if((_last == 0) || (_lc().size() == _unit))
		{
			++_last;
		}
		_lc().emplace_back(std::forward<Arg>(arg)...);
		++_size;
	}

	void pop_back(void)
	{
		_lc().pop_back();
		if(_lc().size() == 0)
		{
			--_last;
		}
		--_size;
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

