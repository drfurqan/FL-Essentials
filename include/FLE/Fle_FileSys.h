#pragma once
#ifndef Fle_FileSys_h__
#define Fle_FileSys_h__

/*********************************************************************************
created:	2018/03/22   01:58AM
filename: 	Fle_FileSys.h
file base:	Fle_FileSys
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	This class contains some important file system utility functions.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <string>  
#include <experimental/filesystem>  

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_FileSys
{
public:
	// Description:
	// Function that returns the file size of the given file path.
	static auto changeDirectoryName(const std::string& _directory_path, const std::string& _str) -> std::string;

	// Description:
	// Function that returns the file size of the given file path.
	static auto getFileSize(const std::experimental::filesystem::path& _filepath) -> std::uintmax_t;

	// Description:
	// Function that returns the last modified time of the given file path.
	static auto getLastModifiedTime(const std::experimental::filesystem::v1::directory_entry& _filepath) -> std::string;

	// Description:
	// Function that extracts the file name of the given file path.
	// _with_extension = true => file name with extension.
	// _with_extension = false => file name without extension.
	static auto getFileName(std::string _filepath, bool _with_extension) -> std::string;

	// Description:
	// Function to check if given path object is of a File.
	static auto filePathExist(std::experimental::filesystem::path _pathobject) -> bool;
	// Description:
	// Function to check if given string path is of a Directory.
	static auto directoryPathExist(std::experimental::filesystem::path _pathobject) -> bool;
	// Description:
	// Function to check if given string path is of a File.
	static auto fileExist(std::string _filepath) -> bool;
	// Description:
	// Function to check if given string path is of a Directory.
	static auto directoryExist(std::string _directory_path) -> bool;

	// Description:
	// Function that returns a list of all files of the given directory plus all files of the sub-directories.
	// Example:
	// auto fl = Fle_FileSys::getAllDirectories("D:\\images", { "logs" });
	// for (auto f : fl)
	//	 std::cout << f << std::endl;
	static auto getAllFilesInDirectory(const std::string& _directory_path, const std::vector<std::string> _directory_skiplist = {}) -> std::vector<std::string>;
	// Description:
	// Function that returns a list of all sub-directories (including the given directory path) of the given directory path.
	// This function will ignores the empty directories and does not add to the list.
	// Example:
	// auto dir = Fle_FileSys::getAllDirectories("D:\\images");
	// for (auto f : dir)
	//	 std::cout << f << std::endl;
	static auto getAllDirectories(const std::string& _directory_path, const std::vector<std::string> _directory_skiplist = {}, const std::string& _end_slash = "") -> std::vector<std::string>;
};

}

#endif // Fle_FileSys_h__