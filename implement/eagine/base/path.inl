/**
 *  @file eagine/base/path.inl
 *  @brief Implementation of a general path utility class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eagine/base/bits/path.inl>

#include <iostream>

namespace EAGine {
namespace base {

EAGINE_LIB_FUNC
path::path(const char* init)
 : _storage(init, init+std::strlen(init))
 , _entries(1, _entry(_storage.size()))
{
}

EAGINE_LIB_FUNC
path::path(const path& p, const char* entry_name)
{
	_entry new_ent(_storage.size(), std::strlen(entry_name));

	_storage.reserve(p._storage.size()+new_ent._len);
	_storage.insert(
		_storage.begin(),
		p._storage.begin(),
		p._storage.end()
	);
	_storage.insert(
		_storage.end(),
		entry_name,
		entry_name+new_ent._len
	);

	_entries.reserve(p._entries.size()+1);
	_entries.insert(
		_entries.begin(),
		p._entries.begin(),
		p._entries.end()
	);
	_entries.push_back(new_ent);
}

EAGINE_LIB_FUNC
path& path::normalize(void)
{
	auto b = _entries.begin();
	auto e = _entries.end();
	auto i = b, j = b;

	while(i != e)
	{
		if((i != b) && (i->_is_par_ent()) && (!j->_is_par_ent()))
		{
			for(auto k=i+1; k!=e; ++k)
			{
				k->_pos -= j->_len;
			}
			_storage.erase(
				_storage.begin()+j->_pos,
				_storage.begin()+j->_pos+j->_len
			);
			std::size_t jo = j-b;
			_entries.erase(j, i+1);
			b = _entries.begin();
			e = _entries.end();
			j = b+jo;
			i = j;
		}
		else
		{
			j = i;
			++i;
		}
	}

	return *this;
}

EAGINE_LIB_FUNC
path& path::push_back(const char* entry_name)
{
	_entry new_ent(_storage.size(), std::strlen(entry_name));

	_storage.insert(
		_storage.end(),
		entry_name,
		entry_name+new_ent._len
	);

	_entries.push_back(new_ent);

	return *this;
}

EAGINE_LIB_FUNC
path& path::push_back(const string& entry_name)
{
	_entry new_ent(_storage.size(), entry_name.size());

	_storage.insert(
		_storage.end(),
		entry_name.begin(),
		entry_name.end()
	);

	_entries.push_back(new_ent);

	return *this;
}

EAGINE_LIB_FUNC
path& path::push_back(par ent)
{
	_entries.push_back(_entry(ent, _storage.size()));
	return *this;
}

EAGINE_LIB_FUNC
string path::str(const string& sep, const string& par) const
{
	string result;
	auto b = _entries.begin();
	auto e = _entries.end();

	if(b != e)
	{
		std::size_t npar = 0;
		for(auto i=b; i!=e; ++i)
		{
			if(i->_is_par_ent())
			{
				++npar;
			}
		}
		result.reserve(
			_storage.size()+
			sep.size()*(_entries.size()-1)+
			par.size()*npar
		);
		auto i = b;

		while(i != e)
		{
			if(i != b) result.append(sep);
			if(i->_is_par_ent())
			{
				result.append(par);
			}
			else
			{
				result.append(
					_storage.data()+i->_pos,
					_storage.data()+i->_pos+
					i->_len
				);
			}
			++i;
		}
	}
	return result;
}

EAGINE_LIB_FUNC
std::ostream& operator << (std::ostream& out, const path& p)
{
	// TODO
	return out << p.str() << " (" << p._str() << ")";
}

} // namespace base
} // namespace EAGine
