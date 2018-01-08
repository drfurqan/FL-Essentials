#pragma once
#ifndef Fle_StringUtil_h__
#define Fle_StringUtil_h__

/*********************************************************************************
created:	2017/01/30   09:42AM
filename: 	Fle_StringUtil.h
file base:	Fle_StringUtil
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Some general purpose methods to handle std::string

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>		// std::setprecision(6)

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_StringUtil
{

public:
	// Description:
	// It returns true if a give char is white space.
	static bool isWhiteSpace(const char _c);
	// Description:
	// Trim heading and trailing white spaces of a string.
	static std::string trimHeadAndTailWhiteSpaces(const std::string& _str);
	// Description:
	// Convert a string to upper case.
	static std::string convertToUpper(const std::string& _str);
	// Description:
	// Convert a string to lower case.
	static std::string convertToLower(const std::string& _str);
	// Description:
	// Extract file name with extension from a given file path.
	static std::string extractFileNameWithExt(const std::string& _path);
	// Description:
	// Extract file name without extension from a given file path.
	static std::string extractFileNameWithoutExt(const std::string& _path);
	// Description:
	// Extract file path from a given file path (excluding the file name).
	static std::string extractFilePath(const std::string& _path);
	// Description:
	// Extract file extension with dot from a given file path.
	static std::string extractFileExtWithDot(const std::string& _path);
	// Description:
	// Extract file extension from a given file path.
	static std::string extractFileExt(const std::string& _path);
	// Description:
	// Extract directory path from a given file path.
	static std::string extractDirectory(const std::string& _path);
	// Description:
	// Change file extension of a give file path.
	static std::string changeExt(const std::string& _path, const std::string& _ext);
	// Description:
	// Change file name of given file path.
	static std::string changeFileName(const std::string& _path, const std::string& _new_file_name);
	// Description:
	// It returns true if a given file has a given extension.
	static bool checkFileExt(std::string _filename, std::string _extension);

	// Description:
	// Function that returns true if the given file exists.
	static bool isFileExist(const std::string& _path);

	// Description:
	// Function to convert any number to string.
	template <typename _T>
	static std::string convertToString(_T _val, std::ios_base& (*_f)(std::ios_base&))
	{
		std::stringstream stream;
		stream << _f << _val;
		return stream.str();
	}
	// Description:
	// Function to convert any number to string.
	template <typename _T>
	static std::string convertToString(_T _val, int _precision = 3)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(_precision) << _val;
		return stream.str();
		// OR
		//return  std::to_string(_val);  // C++ 11
	}

	// Description:
	// Function to find all lexicographic permutations of given string where 
	// repetition of characters is allowed.
	// Example:
	// auto p = Fle_StringUtil::getLexicographicPermutations("ABC");
	// for (const auto& i : p)
	//	 std::cout << i << " ";
	static std::vector<std::string> getLexicographicPermutations(const std::string& _input);

	// Description:
	// Function to check if the input string '_str' ends with given string '_to_match_str'.
	// It returns true on success.
	static bool endsWith(const std::string& _str, const std::string& _to_match_str);

	// Description:
	// Case sensitive function to check if the input string '_str' ends with given string '_to_match_str'.
	// It returns true on success.
	static bool endsWith_caseInsensitive(std::string _str, std::string _to_match_str);

	// Description:
	// Function that counts decimals of the given number and returns it.
	// It only counts up to 5 decimals. More than five decimals will give you zero.
	// Example: getDecimalCount(0.001) will return 3.
	static std::size_t getDecimalCount(double _num);
};

template std::string Fle_StringUtil::convertToString(int _val, int _precision);
template std::string Fle_StringUtil::convertToString(unsigned int _val, int _precision);
template std::string Fle_StringUtil::convertToString(float _val, int _precision);
template std::string Fle_StringUtil::convertToString(double _val, int _precision);
template std::string Fle_StringUtil::convertToString(long _val, int _precision);
template std::string Fle_StringUtil::convertToString(long long _val, int _precision);

}

#endif // Fle_StringUtil_h__