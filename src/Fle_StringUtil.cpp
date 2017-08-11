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

#include <FLE/Fle_StringUtil.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace R3D;

// Check if a character is a white space or not
bool Fle_StringUtil::isWhiteSpace(const char c)
{
	return (c == ' ') || (c == '\t') || (c == '\n') || (c == '\r');
}
std::string Fle_StringUtil::trimHeadAndTailWhiteSpaces(const std::string& _str)
{
	size_t l = _str.size();
	size_t p1 = 0, p2 = l - 1;
	while ((p1 < p2) && isWhiteSpace(_str[p1]))
		++p1;
	while ((p2 > p1) && isWhiteSpace(_str[p2]))
		--p2;
	return _str.substr(p1, p2 - p1 + 1);
}
std::string Fle_StringUtil::convertToUpper(const std::string& _str)
{
	//std::string result(aString);
	//for(unsigned int i = 0; i < result.size(); ++ i)
	//	result[i] = ::toupper(result[i]);
	//return result;

	std::string s;
	s.resize(_str.size());
	std::transform(_str.begin(), _str.end(), s.begin(), ::toupper);
	return s;
}
std::string Fle_StringUtil::convertToLower(const std::string& str)
{
	std::string s;
	s.resize(str.size());
	std::transform(str.begin(), str.end(), s.begin(), ::tolower);
	return s;
}
std::string Fle_StringUtil::extractFileNameWithExt(const std::string &aString)
{
	std::string result = "";
	size_t pathPos = aString.rfind("/");
	if (pathPos == std::string::npos)
		pathPos = aString.rfind("\\");
	if (pathPos != std::string::npos)
		result = aString.substr(pathPos + 1);
	return result;
}
std::string Fle_StringUtil::extractFileNameWithoutExt(const std::string &filepath)
{
	std::string aString = extractFileNameWithExt(filepath);
	size_t position = aString.find(".");
	std::string result = (std::string::npos == position) ? aString : aString.substr(0, position);
	return result;
}
std::string Fle_StringUtil::extractFilePath(const std::string &aString)
{
	std::string result = "";
	size_t pathPos = aString.rfind("/");
	if (pathPos == std::string::npos)
		pathPos = aString.rfind("\\");
	if (pathPos != std::string::npos)
		result = aString.substr(0, pathPos);
	return result;
}
std::string Fle_StringUtil::extractFileExtWithDot(const std::string &aString)
{
	std::string result = "";
	size_t extPos = aString.rfind(".");
	if (extPos != std::string::npos)
		result = aString.substr(extPos);
	return result;
}
std::string Fle_StringUtil::extractFileExt(const std::string &aString)
{
	std::string result = "";
	size_t extPos = aString.rfind(".");
	if (extPos != std::string::npos)
		result = aString.substr(extPos);
	result.erase(0, 1);	// remove the first dot.
	return result;
}
std::string Fle_StringUtil::extractDirectory(const std::string& path)
{
	return extractFilePath(path);
}
std::string Fle_StringUtil::changeExt(const std::string& path, const std::string& ext)
{
	std::string filename = extractFileNameWithExt(path);
#if defined(_WIN32)
	return extractDirectory(path) + "\\" + filename.substr(0, filename.find_last_of('.')) + ext;
#else 
	return extractDirectory(path) + "/" + filename.substr(0, filename.find_last_of('.')) + ext;
#endif
}
std::string Fle_StringUtil::changeFileName(const std::string& path, const std::string& newFileName)
{
#if defined(_WIN32)
	return extractDirectory(path) + "\\" + newFileName;
#else 
	return extractDirectory(path) + "/" + newFileName;
#endif
}
bool Fle_StringUtil::checkFileExt(std::string filename, std::string extension)
{
	std::locale loc1;
	std::use_facet<std::ctype<char> >(loc1).tolower(&*filename.begin(), &*filename.rbegin());
	std::use_facet<std::ctype<char> >(loc1).tolower(&*extension.begin(), &*extension.rbegin());
	std::string end = filename.substr(filename.length() - extension.length(), extension.length());
	return end == extension;
}
bool Fle_StringUtil::isFileExist(const std::string& _path)
{
	std::ifstream f(_path);
	return f.good();
}
