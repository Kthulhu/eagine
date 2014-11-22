/**
 *  @file eagine/path.hpp
 *  @brief Declaration of a general path utility class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_PATH_1308191259_HPP
#define EAGINE_PATH_1308191259_HPP

#include <eagine/eagine_config.hpp>
#include <eagine/base/bits/path.hpp>

#include <iosfwd>

namespace eagine {
namespace base {

/// Helper enumeration for starting path definitions
/**
 *  Example of usage
 *  @code
 *  path p = pa::th/"usr"/"local"/"bin";
 *  @endcode
 */
enum class pa { th };

/// Helper enumeration for adding parent path entries
/**
 *  Example of usage
 *  @code
 *  const char* username = ...
 *  path p = pa::th/"home"/user/par::ent/"common";
 *  @endcode
 */
enum class par { ent };

#if EAGINE_DOCUMENTATION_ONLY
/// const reference to a path entry
/**
 *  @note The lifetime of an path_entry ref is bound to the lifetime
 *   of the path from which it originates and modifications to that
 *   path (except for those made through path entry refs) invalidate
 *   existing path entry refs.
 *
 *  @see path
 *  @see path_entry_iterator
 *  @see path_entry_ref
 */
class const_path_entry_ref
{
public:
	/// Returns the path entry as a string
	string str(const string& par = "..") const;

	/// Returns true if the referenced entry is a parent entry
	bool is_parent_entry(void) const;
};
#else
typedef bits::path_entry_ref_tpl<
	const vector<char>,
	const vector<bits::path_entry>
> const_path_entry_ref;
#endif

#if EAGINE_DOCUMENTATION_ONLY
/// reference to a path entry
/**
 *  @see path
 *  @see path_entry_ref
 *  @see path_entry_iterator
 *  @see const_path_entry_iterator
 */
class path_entry_ref
{
public:
	/// Returns the path entry as a string
	string str(const string& par = "..") const;

	/// Returns true if the referenced entry is a parent entry
	bool is_parent_entry(void) const;
};
#else
typedef bits::path_entry_ref_tpl<
	vector<char>,
	vector<bits::path_entry>
> path_entry_ref;
#endif

#if EAGINE_DOCUMENTATION_ONLY
/// Path entry random access iterator
/**
 *  @note The lifetime of an path_entry iterator is bound to the lifetime
 *   of the path from which it originates and modifications to that
 *   path (except for those made through path entry refs) invalidate
 *   existing path entry iterators.
 *
 *  @see path
 */
struct path_entry_iterator;
#else
typedef bits::path_entry_iterator_tpl<
	vector<char>,
	vector<bits::path_entry>
> path_entry_iterator;

typedef bits::path_entry_iterator_tpl<
	const vector<char>,
	const vector<bits::path_entry>
> const_path_entry_iterator;
#endif

/// Class representing general paths in filesystems/configs/etc.
/**
 *  @see pa::th
 *  @see par::ent
 */
class path
{
private:
	vector<char> _storage;

	static const unsigned _par_ent = bits::path_entry::_par_ent;

	typedef bits::path_entry _entry;

	vector<_entry> _entries;
public:
	/// Default construction
	path(void) { }

	template <typename Parent>
	path(const bits::path_cat<Parent>& path_cat)
	{
		_storage.reserve(path_cat._size());
		path_cat._fill(_storage);

		_entries.reserve(path_cat._entries());
		path_cat._fill(_entries);
	}

	path(const char* init);

	path(const path& p, const char* entry_name);

	/// Returns true if the path is empty
	bool empty(void) const
	{
		return _entries.empty();
	}

	/// Returns the number of entries in the path
	std::size_t size(void) const
	{
		return _entries.size();
	}

	/// Clears the path
	/**
	 *  @post this->empty()
	 */
	void clear(void)
	{
		_storage.clear();
		_entries.clear();
	}

	/// Normalize this path
	path& normalize(void);

	/// Returns a const reference to the entry at the front of the path
	/**
	 *  @pre !this->empty()
	 */
	const_path_entry_ref front(void) const
	{
		assert(!_entries.empty());
		return const_path_entry_ref(
			_storage,
			_entries,
			0
		);
	}

	/// Returns a const reference to the entry at the back of the path
	/**
	 *  @pre !this->empty()
	 */
	const_path_entry_ref back(void) const
	{
		assert(!_entries.empty());
		return const_path_entry_ref(
			_storage,
			_entries,
			_entries.size()-1
		);
	}

	/// Returns a reference to the entry at the front of the path
	/**
	 *  @pre !this->empty()
	 */
	path_entry_ref front(void)
	{
		assert(!_entries.empty());
		return path_entry_ref(
			_storage,
			_entries,
			0
		);
	}

	/// Returns a reference to the entry at the back of the path
	/**
	 *  @pre !this->empty()
	 */
	path_entry_ref back(void)
	{
		assert(!_entries.empty());
		return path_entry_ref(
			_storage,
			_entries,
			_entries.size()-1
		);
	}

	/// const iterator type
	typedef const_path_entry_iterator const_iterator;

	/// Returns a const iterator pointing to the begin of the path
	const_iterator begin(void) const
	{
		return const_iterator(
			_storage,
			_entries,
			0
		);
	}

	/// Returns a const iterator pointing to the end of the path
	const_iterator end(void) const
	{
		return const_iterator(
			_storage,
			_entries,
			_entries.size()
		);
	}

	/// iterator type
	typedef path_entry_iterator iterator;

	/// Returns an iterator pointing to the begin of the path
	iterator begin(void)
	{
		return iterator(
			_storage,
			_entries,
			0
		);
	}

	/// Returns an iterator pointing to the end of the path
	iterator end(void)
	{
		return iterator(
			_storage,
			_entries,
			_entries.size()
		);
	}

	/// Push a new entry to the back of the path
	path& push_back(const char* entry_name);

	/// Push a new entry to the back of the path
	path& push_back(const string& entry_name);

	/// Push a parent entry to the back of the path
	path& push_back(par ent);

	/// Equivalent to push_back(entry_name)
	path& operator /= (const string& entry_name)
	{
		return push_back(entry_name);
	}

	/// Equivalent to push_back(ent)
	path& operator /= (par ent)
	{
		return push_back(ent);
	}

	/// Creates a new path with entry name appended
	friend path operator / (const path& p, const char* entry_name)
	{
		return path(p, entry_name);
	}

	/// Returns a string representation of this path
	/** In the returned string entries are separated by @p sep
	 *  and the parent entries are represented by @p par.
	 */
	string str(
		const string& sep = "/",
		const string& par = ".."
	) const;

	// TODO
	string _str(void) const
	{
		return string(_storage.data(), _storage.size());
	}
};

std::ostream& operator << (std::ostream& out, const path& p);

} // namespace base
} // namespace eagine

#if !EAGINE_LINK_LIBRARY || EAGINE_IMPLEMENTING_LIBRARY
#include <eagine/base/path.inl>
#endif

#endif // include guard
