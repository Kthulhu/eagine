/**
 *  @file eagine/base/bits/path.hpp
 *  @brief Implementation of helpers for the path utility class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_BITS_PATH_1308191259_HPP
#define EAGINE_BASE_BITS_PATH_1308191259_HPP

#include <eagine/base/vector.hpp>
#include <eagine/base/string.hpp>
#include <cstring>
#include <cstddef>
#include <cassert>

namespace eagine {
namespace base {

enum class pa;
enum class par;
class path;

namespace bits {

bool is_valid_path_entry(const char*, std::size_t = 0);
void validate_path_entry(const char*, std::size_t = 0);

struct path_entry
{
	static const unsigned _par_ent = 0x1;

	unsigned _flags;
	std::size_t _pos;
	std::size_t _len;

	bool _is_par_ent(void) const
	{
		return (_flags & _par_ent) == _par_ent;
	}

	path_entry(par, std::size_t pos)
	 : _flags(_par_ent)
	 , _pos(pos)
	 , _len(0)
	{ }

	path_entry(std::size_t pos, std::size_t len)
	 : _flags(0x0)
	 , _pos(pos)
	 , _len(len)
	{ }

	path_entry(std::size_t len)
	 : _flags(0x0)
	 , _pos(0)
	 , _len(len)
	{ }
};

template <typename Parent>
class path_cat;

class path_cat_base
{
protected:
	std::size_t _hlen;
	std::size_t _elen;

	static std::size_t _size(pa) { return 0; }

	template <typename Parent_>
	static std::size_t _size(const path_cat<Parent_>& pc)
	{
		return pc._size();
	}

	static std::size_t _ents(pa)
	{
		return 0;
	}

	template <typename Parent_>
	static std::size_t _ents(const path_cat<Parent_>& pc)
	{
		return pc._entries();
	}

	static void _fill(const vector<char>&, pa) { }

	template <typename Parent_>
	static void _fill(
		vector<char>& v,
		const path_cat<Parent_>& pc
	)
	{
		pc._fill(v);
	}

	static void _fill(const vector<path_entry>&, pa) { }

	template <typename Parent_>
	static void _fill(
		vector<path_entry>& v,
		const path_cat<Parent_>& pc
	)
	{
		pc._fill(v);
	}

	void _fill(vector<char>& v, const char* elem) const;
	void _fill(vector<path_entry>& v, const char*) const;

	template <typename Parent_>
	path_cat_base(const Parent_& parent, const char* elem)
	 : _hlen(_size(parent))
	 , _elen(elem?std::strlen(elem):0)
	{ }

	template <typename Parent_>
	path_cat_base(const Parent_& parent, par /*ent*/)
	 : _hlen(_size(parent))
	 , _elen(0)
	{ }
public:
	std::size_t _size(void) const
	{
		return _hlen + _elen;
	}
};

template <typename Parent>
class path_cat
 : public path_cat_base
{
private:
	friend class path_cat_base;

	Parent _parent;
	const char* _elem;
public:
	path_cat(const Parent& parent, const char* elem)
	 : path_cat_base(parent, elem)
	 , _parent(parent)
	 , _elem(elem)
	{ }

	path_cat(const Parent& parent, par ent)
	 : path_cat_base(parent, ent)
	 , _parent(parent)
	 , _elem(nullptr)
	{ }

	std::size_t _entries(void) const
	{
		return path_cat_base::_ents(_parent)+1;
	}

	void _fill(vector<char>& v) const
	{
		path_cat_base::_fill(v, _parent);
		path_cat_base::_fill(v, _elem);
	}

	void _fill(vector<path_entry>& v) const
	{
		path_cat_base::_fill(v, _parent);
		path_cat_base::_fill(v, _elem);
	}
};

} // namespace bits

inline bits::path_cat<pa> operator / (pa th, const char* a)
{
	return bits::path_cat<pa>(th, a);
}

inline bits::path_cat<pa> operator / (pa th, par ent)
{
	return bits::path_cat<pa>(th, ent);
}

template <typename Parent>
inline bits::path_cat<bits::path_cat<Parent> >
operator / (const bits::path_cat<Parent>& parent, const char* a)
{
	return bits::path_cat<bits::path_cat<Parent> >(parent, a);
}

template <typename Parent>
inline bits::path_cat<bits::path_cat<Parent> >
operator / (const bits::path_cat<Parent>& parent, par ent)
{
	return bits::path_cat<bits::path_cat<Parent> >(parent, ent);
}

namespace bits {

class path_entry_ref_base
{
protected:
	static string _get_str(
		const vector<char>& storage,
		const bits::path_entry& entry,
		const string& par
	);

	static void _set_str(
		vector<char>& storage,
		vector<bits::path_entry>& entries,
		std::size_t entry,
		const char* entry_name,
		std::size_t name_len = 0
	);

	static void _set_par(
		vector<char>& storage,
		vector<bits::path_entry>& entries,
		std::size_t entry
	);

	static void _swap(
		vector<char>& storage,
		vector<bits::path_entry>& entries,
		std::size_t lo,
		std::size_t hi
	);
};

template <typename Storage, typename Entries>
class path_entry_iterator_tpl;

template <typename Storage, typename Entries>
class path_entry_ref_tpl
 : public path_entry_ref_base
{
public:
	Storage* _storage;
	Entries* _entries;
	std::size_t _index;

	Storage& _store(void) const
	{
		assert(_storage);
		return *_storage;
	}

	typename Entries::reference _entry(void) const
	{
		assert(_entries);
		return (*_entries)[_index];
	}

	path_entry_ref_tpl(
		Storage& storage,
		Entries& entries,
		std::size_t entry
	): _storage(&storage)
	 , _entries(&entries)
	 , _index(entry)
	{ }

	friend bool operator == (
		const path_entry_ref_tpl& a,
		const path_entry_ref_tpl& b
	)
	{
		std::size_t a_len = a._entry()._len;
		std::size_t b_len = b._entry()._len;

		if(a_len != b_len) return false;
		if(a_len == 0) return true;

		return std::strncmp(
			a._store().data()+
			a._entry()._pos,
			b._store().data()+
			b._entry()._pos,
			a_len
		) == 0;
	}

	friend bool operator == (
		const path_entry_ref_tpl& p,
		const char* c_str
	)
	{
		if(p._entry()._is_par_ent())
			return false;

		std::size_t p_len = p._entry()._len;

		return std::strncmp(
			p._store().data()+
			p._entry()._pos,
			c_str,
			p_len
		) == 0;
	}

	friend bool operator == (
		const char* c_str,
		const path_entry_ref_tpl& p
	)
	{
		if(p._entry()._is_par_ent())
			return false;

		std::size_t p_len = p._entry()._len;

		return std::strncmp(
			p._store().data()+
			p._entry()._pos,
			c_str,
			p_len
		) == 0;
	}

	friend bool operator == (
		const path_entry_ref_tpl& p,
		par ent
	)
	{
		(void)ent;
		return p._entry()._is_par_ent();
	}

	friend bool operator == (
		par ent,
		const path_entry_ref_tpl& p
	)
	{
		(void)ent;
		return p._entry()._is_par_ent();
	}

	friend bool operator != (
		const path_entry_ref_tpl& a,
		const path_entry_ref_tpl& b
	)
	{
		std::size_t a_len = a._entry()._len;
		std::size_t b_len = b._entry()._len;

		if(a_len != b_len) return true;
		if(a_len == 0) return false;

		return std::strncmp(
			a._store().data()+
			a._entry()._pos,
			b._store().data()+
			b._entry()._pos,
			a._entry()._len
		) != 0;
	}

	friend bool operator != (
		const path_entry_ref_tpl& p,
		const char* c_str
	)
	{
		if(p._entry()._is_par_ent())
			return true;

		std::size_t p_len = p._entry()._len;

		return std::strncmp(
			p._store().data()+
			p._entry()._pos,
			c_str,
			p_len
		) != 0;
	}

	friend bool operator != (
		const char* c_str,
		const path_entry_ref_tpl& p
	)
	{
		if(p._entry()._is_par_ent())
			return true;

		std::size_t p_len = p._entry()._len;

		return std::strncmp(
			p._store().data()+
			p._entry()._pos,
			c_str,
			p_len
		) != 0;
	}

	friend bool operator != (
		const path_entry_ref_tpl& p,
		par ent
	)
	{
		(void)ent;
		return !p._entry()._is_par_ent();
	}

	friend bool operator != (
		par ent,
		const path_entry_ref_tpl& p
	)
	{
		(void)ent;
		return !p._entry()._is_par_ent();
	}

	friend bool operator <  (
		const path_entry_ref_tpl& a,
		const path_entry_ref_tpl& b
	)
	{
		std::size_t a_len = a._entry()._len;
		std::size_t b_len = b._entry()._len;

		if((a_len == 0) && (b_len != 0))
			return true;

		int cmp = std::strncmp(
			a._store().data()+
			a._entry()._pos,
			b._store().data()+
			b._entry()._pos,
			a_len<b_len?a_len:b_len
		);
		if(cmp == 0)
		{
			return a_len <  b_len;
		}
		if(cmp < 0)
		{
			return a_len == b_len;
		}
		return false;
	}

	string str(const string& par = "..") const
	{
		return path_entry_ref_base::_get_str(
			_store(),
			_entry(),
			par
		);
	}

	operator string (void) const
	{
		return str();
	}

	const char* data(void) const
	{
		if(_entry()._is_par_ent())
		{
			return "";
		}
		else
		{
			return _store().data()+_entry()._pos;
		}
	}

	std::size_t size(void) const
	{
		return _entry()._len;
	}

	bool is_parent_entry(void) const
	{
		return _entry()._is_par_ent();
	}

	path_entry_ref_tpl& set(const char* entry_name)
	{
		path_entry_ref_base::_set_str(
			*_storage,
			*_entries,
			_index,
			entry_name
		);
		return *this;
	}

	path_entry_ref_tpl& set(const string& entry_name)
	{
		path_entry_ref_base::_set_str(
			*_storage,
			*_entries,
			_index,
			entry_name.c_str(),
			entry_name.size()
		);
		return *this;
	}

	path_entry_ref_tpl& set(par /*ent*/)
	{
		path_entry_ref_base::_set_par(
			*_storage,
			*_entries,
			_index
		);
		return *this;
	}

	path_entry_ref_tpl& set(const path_entry_ref_tpl& that)
	{
		if(that._entry()._is_par_ent())
		{
			path_entry_ref_base::_set_par(
				*_storage,
				*_entries,
				_index
			);
		}
		else
		{
			path_entry_ref_base::_set_str(
				*_storage,
				*_entries,
				_index,
				that._store().data()+
				that._entry()._pos,
				that._entry()._len
			);
		}
		return *this;
	}

	template <typename T>
	path_entry_ref_tpl& operator = (T&& value)
	{
		return set(std::forward<T>(value));
	}

	path_entry_ref_tpl& operator = (const path_entry_ref_tpl& that)
	{
		return set(that);
	}

	void swap(path_entry_ref_tpl& that)
	{
		if(_index != that._index)
		{
			bool same_path =
				(_storage == that._storage) &&
				(_entries == that._entries);

			if(same_path)
			{
				bool b = _index < that._index;

				path_entry_ref_base::_swap(
					*_storage,
					*_entries,
					b?_index:that._index,
					b?that._index:_index
				);
			}
			else
			{
				assert(!"Not implemented!");
			}
		}
	}
};

template <typename Storage, typename Entries>
inline void swap(
	path_entry_ref_tpl<Storage, Entries> a,
	path_entry_ref_tpl<Storage, Entries> b
)
{
	return a.swap(b);
}

template <typename Storage, typename Entries>
class path_entry_ptr_tpl
{
public:
	Storage* _storage;
	Entries* _entries;
	std::size_t _index;

	path_entry_ptr_tpl(
		Storage& storage,
		Entries& entries,
		std::size_t entry
	): _storage(&storage)
	 , _entries(&entries)
	 , _index(entry)
	{ }

	path_entry_ref_tpl<Storage, Entries> operator * (void)
	{
		assert(_storage != nullptr);
		assert(_entries != nullptr);
		return path_entry_ref_tpl<Storage, Entries>(
			*_storage,
			*_entries,
			_index
		);
	}
};

template <typename Storage, typename Entries>
class path_entry_iterator_tpl
{
public:
	//typedef None value_type;
	typedef path_entry_ref_tpl<Storage, Entries> reference;
	typedef path_entry_ptr_tpl<Storage, Entries> pointer;
private:
	friend class eagine::base::path;

	reference _ref;

	path_entry_iterator_tpl(
		Storage& storage,
		Entries& entries,
		std::size_t iter
	): _ref(storage, entries, iter)
	{ }

public:
	typedef std::ptrdiff_t distance;
	typedef std::ptrdiff_t difference_type;
	typedef std::random_access_iterator_tag iterator_category;

	friend bool operator == (
		const path_entry_iterator_tpl& a,
		const path_entry_iterator_tpl& b
	)
	{
		return a._ref._index == b._ref._index;
	}

	friend bool operator != (
		const path_entry_iterator_tpl& a,
		const path_entry_iterator_tpl& b
	)
	{
		return a._ref._index != b._ref._index;
	}

	friend bool operator <  (
		const path_entry_iterator_tpl& a,
		const path_entry_iterator_tpl& b
	)
	{
		return a._ref._index <  b._ref._index;
	}

	reference& operator * (void)
	{
		return _ref;
	}

	reference* operator -> (void)
	{
		return &_ref;
	}

	path_entry_iterator_tpl& operator ++ (void)
	{
		++_ref._index;
		return *this;
	}

	path_entry_iterator_tpl operator ++ (int)
	{
		std::size_t result = _ref._index;
		++_ref._index;
		return path_entry_iterator_tpl(
			_ref._storage,
			_ref._entries,
			result
		);
	}

	path_entry_iterator_tpl& operator -- (void)
	{
		assert(_ref._index != 0);
		--_ref._index;
		return *this;
	}

	path_entry_iterator_tpl operator -- (int)
	{
		assert(_ref._index != 0);
		std::size_t result = _ref._index;
		--_ref._index;
		return path_entry_iterator_tpl(
			_ref._storage,
			_ref._entries,
			result
		);
	}

	path_entry_iterator_tpl& operator += (distance n)
	{
		_ref._index += n;
		return *this;
	}

	friend path_entry_iterator_tpl operator + (
		const path_entry_iterator_tpl& x,
		distance n
	)
	{
		return path_entry_iterator_tpl(
			*x._ref._storage,
			*x._ref._entries,
			x._ref._index + n
		);
	}

	friend path_entry_iterator_tpl operator + (
		distance n,
		const path_entry_iterator_tpl& x
	)
	{
		return path_entry_iterator_tpl(
			*x._ref._storage,
			*x._ref._entries,
			x._ref._index + n
		);
	}

	friend path_entry_iterator_tpl operator - (
		const path_entry_iterator_tpl& x,
		distance n
	)
	{
		assert(x._ref._index >= n);
		return path_entry_iterator_tpl(
			*x._ref._storage,
			*x._ref._entries,
			x._ref._index - n
		);
	}

	friend typename path_entry_iterator_tpl::distance operator - (
		const path_entry_iterator_tpl& x,
		const path_entry_iterator_tpl& y
	)
	{
		return x._ref._index - y._ref._index;
	}

	reference operator [] (distance n)
	{
		reference result = _ref;
		result._index += n;
		return result;
	}
};

} // namespace bits
} // namespace base
} // namespace eagine

#endif // include guard
