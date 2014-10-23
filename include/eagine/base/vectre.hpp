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
			if(_chunks.empty())
			{
				_chunks.emplace_back(_alloc);
				_chunks.back().reserve(_unit);

				if(n > _unit)
				{
					n -= _unit;
				}
				else break;
			}
			else
			{
				std::size_t m = _unit - (l?_chunks[l-1].size():0);

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
	}
public:
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

	T& front(void)
	{
		assert(!_chunks.empty());
		return _chunks.front().front();
	}

	const T& front(void) const
	{
		assert(!_chunks.empty());
		return _chunks.front().front();
	}

	T& back(void)
	{
		assert(!_chunks.empty());
		return _chunks._lc().back();
	}

	const T& back(void) const
	{
		assert(!_chunks.empty());
		return _chunks._lc().back();
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

