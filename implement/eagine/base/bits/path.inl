/**
 *  @file eagine/base/bits/path.inl
 *  @brief Implementation path utility helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <string>
#include <stdexcept>

namespace EAGine {
namespace base {
namespace bits {

EAGINE_LIB_FUNC
bool is_valid_path_entry(const char* entry, std::size_t len)
{
	if(!entry) return false;
	if((!len) && (std::strlen(entry) == 0)) return false;
	if(std::strchr(entry,  '/')) return false;
	if(std::strchr(entry,  ':')) return false;
	if(std::strchr(entry, '\\')) return false;
	if(std::strstr(entry, "..")) return false;
	return true;
}

EAGINE_LIB_FUNC
void validate_path_entry(const char* entry, std::size_t len)
{
	if(!is_valid_path_entry(entry, len))
	{
		std::runtime_error(
			string("Invalid path entry '")+
			(entry?entry:"<null>")+
			"'"
		);
	}
}

EAGINE_LIB_FUNC
string path_entry_ref_base::_get_str(
	const vector<char>& storage,
	const bits::path_entry& entry,
	const string& par
)
{
	if(entry._is_par_ent())
	{
		return par;
	}
	else
	{
		return string(
			storage.data()+entry._pos,
			storage.data()+entry._pos+entry._len
		);
	}
}

EAGINE_LIB_FUNC
void path_entry_ref_base::_set_str(
	vector<char>& storage,
	vector<bits::path_entry>& entries,
	std::size_t entry_index,
	const char* entry_name,
	std::size_t name_len
)
{
	assert(entry_name);
	bits::path_entry& entry = entries[entry_index];

	if(!name_len) name_len = std::strlen(entry_name);
	validate_path_entry(entry_name, name_len);

	if(name_len > entry._len)
	{
		std::strncpy(
			storage.data()+entry._pos,
			entry_name,
			entry._len
		);
		storage.insert(
			storage.begin()+entry._pos+entry._len,
			entry_name+entry._len,
			entry_name+name_len
		);
		for(std::size_t e=entry_index+1;e<entries.size();++e)
		{
			entries[e]._pos += name_len - entry._len;
		}
	}
	else if(name_len < entry._len)
	{
		std::strncpy(
			storage.data()+entry._pos,
			entry_name,
			name_len
		);
		storage.erase(
			storage.begin()+entry._pos+name_len,
			storage.begin()+entry._pos+entry._len
		);
		for(std::size_t e=entry_index+1;e<entries.size();++e)
		{
			entries[e]._pos -= entry._len - name_len;
		}
	}
	else
	{
		std::strncpy(
			storage.data()+entry._pos,
			entry_name,
			name_len
		);
	}

	entry._len = name_len;
	entry._flags &= ~path_entry::_par_ent;
}

EAGINE_LIB_FUNC
void path_entry_ref_base::_set_par(
	vector<char>& storage,
	vector<bits::path_entry>& entries,
	std::size_t entry_index
)
{
	bits::path_entry& entry = entries[entry_index];
	if(!entry._is_par_ent())
	{
		storage.erase(
			storage.begin()+entry._pos,
			storage.begin()+entry._pos+entry._len
		);
		entry._len = 0;
		entry._flags |= path_entry::_par_ent;
	}
}

EAGINE_LIB_FUNC
void path_entry_ref_base::_swap(
	vector<char>& storage,
	vector<bits::path_entry>& entries,
	std::size_t lo,
	std::size_t hi
)
{
	assert(lo <= hi);

	const string tmp_lo(
		storage.data()+
		entries[lo]._pos,
		entries[lo]._len
	);
	const string tmp_hi(
		storage.data()+
		entries[hi]._pos,
		entries[hi]._len
	);

	std::memmove(
		storage.data()+
		entries[lo]._pos+
		entries[hi]._len,
		storage.data()+
		entries[lo]._pos+
		entries[lo]._len,
		entries[hi]._pos-
		entries[lo]._pos
	);

	std::ptrdiff_t diff = entries[hi]._len - entries[lo]._len;

	entries[lo]._len = entries[hi]._len;
	for(std::size_t i=lo+1; i!=hi; ++i)
	{
		entries[i]._pos += diff;
	}
	entries[hi]._pos += diff;
	entries[hi]._len -= diff;

	using std::swap;
	swap(entries[hi]._flags, entries[lo]._flags);

	std::memcpy(
		storage.data()+
		entries[lo]._pos,
		tmp_hi.data(),
		tmp_hi.size()
	);

	std::memcpy(
		storage.data()+
		entries[hi]._pos,
		tmp_lo.data(),
		tmp_lo.size()
	);
}

EAGINE_LIB_FUNC
void path_cat_base::_fill(vector<char>& v, const char* elem) const
 {
	validate_path_entry(elem);
	if(elem) v.insert(v.end(), elem, elem+_elen);
}

EAGINE_LIB_FUNC
void path_cat_base::_fill(vector<path_entry>& v, const char* elem) const
{
	if(elem)
	{
		validate_path_entry(elem);
		v.push_back(path_entry(_hlen, _elen));
	}
	else v.push_back(path_entry(par::ent, _hlen));
}

} // namespace bits
} // namespace base
} // namespace EAGine
