/*********************************************************************************
created:	2018/03/22   01:58AM
filename: 	Fle_FileSys.cpp
file base:	Fle_FileSys
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	This class contains some important file system utility functions.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_FileSys.h>

#include <iostream>  
#include <chrono>
#include <algorithm>

using namespace R3D;
namespace fs = std::experimental::filesystem;

auto Fle_FileSys::changeDirectoryName(const std::string& _directory_path, const std::string& _str) -> std::string
{
	fs::path po(_directory_path);
	auto fn = po.filename().string();
	auto s = po.parent_path().string();
	return (s + "\\" + _str + fn);
}

auto Fle_FileSys::getFileSize(const fs::path& _filepath) -> std::uintmax_t
{
	if (fs::exists(_filepath) && fs::is_regular_file(_filepath))
	{
		auto err = std::error_code{};
		auto filesize = fs::file_size(_filepath, err);
		if (filesize != static_cast<uintmax_t>(-1))
			return filesize;
	}

	return static_cast<uintmax_t>(-1);
}

auto Fle_FileSys::getLastModifiedTime(const fs::v1::directory_entry& _filepath) -> std::string
{
	auto cftime = std::chrono::system_clock::to_time_t(fs::last_write_time(_filepath));
	return std::asctime(std::localtime(&cftime));
}

auto Fle_FileSys::getFileName(std::string _filepath, bool _with_extension) -> std::string
{
	fs::path po(_filepath);

	if (_with_extension)
		return po.filename().string();
	else
	{
		if (po.has_stem())
			return po.stem().string();
	}

	return "";
}

auto Fle_FileSys::filePathExist(fs::path _pathobject) -> bool
{
	try
	{
		if (fs::exists(_pathobject) && fs::is_regular_file(_pathobject))
			return true;
	}
	catch (fs::filesystem_error& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return false;
}
auto Fle_FileSys::directoryPathExist(fs::path _pathobject) -> bool
{
	try 
	{
		if (fs::exists(_pathobject) && fs::is_directory(_pathobject))
			return true;
	}
	catch (fs::filesystem_error& _e)
	{
		std::cerr << _e.what() << std::endl;
	}
	return false;
}
auto Fle_FileSys::fileExist(std::string _filepath) -> bool
{
	try
	{
		fs::path po(_filepath);
		if (fs::exists(po) && fs::is_regular_file(po))
			return true;
	}
	catch (fs::filesystem_error& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return false;
}
auto Fle_FileSys::directoryExist(std::string _directory_path) -> bool
{
	try
	{
		fs::path po(_directory_path);
		if (fs::exists(po) && fs::is_directory(po))
			return true;
	}
	catch (fs::filesystem_error& _e)
	{
		std::cerr << _e.what() << std::endl;
	}
	return false;
}

auto Fle_FileSys::getAllFilesInDirectory(const std::string& _directory_path, const std::vector<std::string> _directory_skiplist) -> std::vector<std::string>
{
	std::vector<std::string> files;
	try
	{
		if (fs::exists(_directory_path) && fs::is_directory(_directory_path))
		{
			fs::recursive_directory_iterator iter(_directory_path);
			fs::recursive_directory_iterator end;

			while (iter != end)
			{
				if (fs::is_directory(iter->path()) && (std::find(_directory_skiplist.begin(), _directory_skiplist.end(), iter->path().filename()) != _directory_skiplist.end()))
					iter.disable_recursion_pending();
				else
				{
					if (filePathExist(iter->path()))
						files.push_back(iter->path().string());
				}

				std::error_code ec;
				iter.increment(ec);
				if (ec) std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
			}
		}
	}
	catch (std::system_error& _e)
	{
		std::cerr << "Exception occurs: " << _e.what();
	}

	return files;
}

auto getAllSubDirectories2(const std::string& _directory_path, const std::vector<std::string> _directory_skiplist, const std::string& _end_slash) -> std::vector<std::string>
{
	std::vector<std::string> files;
	try 
	{
		if (fs::exists(_directory_path) && fs::is_directory(_directory_path))
		{
			fs::recursive_directory_iterator iter(_directory_path);
			fs::recursive_directory_iterator end;

			while (iter != end)
			{
				if (fs::is_directory(iter->path()) && (std::find(_directory_skiplist.begin(), _directory_skiplist.end(), iter->path().filename()) != _directory_skiplist.end()))
					iter.disable_recursion_pending();
				else
					if (Fle_FileSys::filePathExist(iter->path()))
						files.push_back(iter->path().parent_path().string() + _end_slash);

				std::error_code ec;
				iter.increment(ec);
				if (ec) std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
			}
		}
	}
	catch (std::system_error& _e)
	{
		std::cerr << "Exception occurs: " << _e.what();
	}

	return files;
}

auto Fle_FileSys::getAllDirectories(const std::string& _directory_path, const std::vector<std::string> _directory_skiplist, const std::string& _end_slash) -> std::vector<std::string>
{
	auto files = getAllSubDirectories2(_directory_path, _directory_skiplist, _end_slash);
	if (files.size() > 1) // remove duplicates
	{
		std::sort(files.begin(), files.end());
		files.erase(std::unique(files.begin(), files.end()), files.end());
	}
	return files;
}