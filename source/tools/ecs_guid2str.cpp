/**
 *  .file tools/ecs_guid2str.cpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/base/program_args.hpp>
#include <eagine/base/memory.hpp>
#include <eagine/base/array.hpp>
#include <eagine/base/guid.hpp>
#include <eagine/base/io.hpp>

#include <eagine/ecs/component.hpp>

#include <iostream>
#include <cstdio>

std::ostream& print_usage(std::ostream& out)
{
	return out
		<< "Usage: ecs_guid2str [--help] | [GUID...]"
		<< std::endl
		<< std::endl
		<< "Options:"
		<< std::endl
		<< "--help | -h: Print this help screen and exit."
		<< std::endl
		<< "GUID : Name of a file containing a UTF-8 encoded text."
		<< std::endl;
}

int main(int argc, const char* argv[])
{
	using namespace EAGine;
	using namespace EAGine::base;

	const char dirsep = '/'; // TODO

	typedef unique_ptr<FILE, int(*)(FILE*)> raii_FILE;

	raii_FILE uids(std::tmpfile(), &std::fclose);
	raii_FILE keys(std::tmpfile(), &std::fclose);
	raii_FILE strs(std::tmpfile(), &std::fclose);

	std::size_t ofs = 0, len, nek = 0;
	std::ptrdiff_t ptr;

	const array<char, sizeof(ofs)> pad = {};
	const std::size_t ali = alignof(decltype(len));

	bool get_work_dir = false;
	bool get_out_path = false;
	string work_dir, out_path;

	for(auto arg : program_args(argc, argv))
	{
		if(get_work_dir)
		{
			work_dir = arg.str();
			if(!work_dir.empty())
			{
				if(work_dir.back() != dirsep)
				{
					const char tmp[2] = {dirsep, '\0'};
					work_dir.append(tmp);
				}
			}
			get_work_dir = false;
		}
		else if(get_out_path)
		{
			out_path = arg.str();
			get_out_path = false;
		}
		else if(arg.empty())
		{
			std::cerr
				<< "Invalid empty command line argument!"
				<< std::endl;
			print_usage(std::cerr);
			return 1;
		}
		else if(arg.front() != '-')
		{
			guid uid(arg);
			string path = work_dir + arg.str();
			vector<byte> str = load_file_data(path);

			len = ecs::component_key_t(str.size());
			std::size_t pdg = (len%ali)?ali-len%ali:0;

			assert(sizeof(uid) >= alignof(decltype(uid)));
			assert(sizeof(ofs) >= alignof(decltype(ofs)));
			assert(sizeof(len) >= alignof(decltype(len)));

			assert(ofs % alignof(decltype(len)) == 0);

			std::fwrite(&uid, sizeof(uid), 1, uids.get());
			std::fwrite(&ofs, sizeof(ofs), 1, keys.get());
			std::fwrite(&len, sizeof(len), 1, strs.get());

			std::fwrite(str.data(), sizeof(byte), str.size(), strs.get());
			std::fwrite(pad.data(), sizeof(byte), pdg, strs.get());

			ofs += sizeof(len)+len+pdg;
			nek += 1;
		}
		else if(arg.in("-d", "--work-dir"))
		{
			get_work_dir = true;
		}
		else if(arg.in("-o", "--output"))
		{
			get_out_path = true;
		}
		else
		{
			std::cerr
				<< "Invalid command line option '"
				<< arg
				<< "'!"
				<< std::endl;
			print_usage(std::cerr);
			return 1;
		}
	}

	raii_FILE output(
		out_path.empty()?
		stdout:
		std::fopen(out_path.c_str(), "w"),
		&std::fclose
	);

	// number of entities/keys
	std::fwrite(&nek, sizeof(nek), 1, output.get());
	std::fwrite(&nek, sizeof(nek), 1, output.get());
	// size of string block
	len = std::ftell(strs.get());
	std::fwrite(&len, sizeof(len), 1, output.get());

	// uids offsetptr
	ptr = 3*sizeof(ptr);
	std::fwrite(&ptr, sizeof(ptr), 1, output.get());

	// keys offsetptr
	len = std::ftell(uids.get());
	ptr = 2*sizeof(ptr)+len;
	std::fwrite(&ptr, sizeof(ptr), 1, output.get());

	// strings offsetptr
	len += std::ftell(keys.get());
	ptr = 1*sizeof(ptr)+len;
	std::fwrite(&ptr, sizeof(ptr), 1, output.get());

	FILE* files[3] = {uids.get(), keys.get(), strs.get()};

	for(unsigned f=0; f<3; ++f)
	{
		std::fseek(files[f], 0, SEEK_SET);

		byte buf[BUFSIZ];

		while((len = std::fread(buf, 1, BUFSIZ, files[f])) != 0)
		{
			std::fwrite(buf, 1, len, output.get());
		}
	}

	return 0;
}
