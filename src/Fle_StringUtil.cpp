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
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_StringUtil.h>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace R3D;

char Fle_StringUtil::separator()
{
	#if defined(WIN32) || defined(_WIN32) 
	return '\\';
	#else
	return '/';
	#endif
}

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
	std::size_t pathPos = aString.rfind("/");
	if (pathPos == std::string::npos)
		pathPos = aString.rfind("\\");
	if (pathPos != std::string::npos)
		result = aString.substr(pathPos + 1);
	return result;
}
std::string Fle_StringUtil::extractFileNameWithoutExt(const std::string &filepath)
{
	std::string aString = extractFileNameWithExt(filepath);
	std::size_t position = aString.find(".");
	std::string result = (std::string::npos == position) ? aString : aString.substr(0, position);
	return result;
}
std::string Fle_StringUtil::extractFilePath(const std::string &aString)
{
	std::string result = "";
	std::size_t pathPos = aString.rfind("/");
	if (pathPos == std::string::npos)
		pathPos = aString.rfind("\\");
	if (pathPos != std::string::npos)
		result = aString.substr(0, pathPos);
	return result;
}
std::string Fle_StringUtil::extractFileExtWithDot(const std::string &aString)
{
	std::string result = "";
	std::size_t extPos = aString.rfind(".");
	if (extPos != std::string::npos)
		result = aString.substr(extPos);
	return result;
}
std::string Fle_StringUtil::extractFileExt(const std::string &aString)
{
	std::string result = "";
	std::size_t extPos = aString.rfind(".");
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
	return extractDirectory(path) + separator() + filename.substr(0, filename.find_last_of('.')) + ext;
}
std::string Fle_StringUtil::changeFileName(const std::string& path, const std::string& newFileName)
{
	return extractDirectory(path) + separator() + newFileName;
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

std::string Fle_StringUtil::replace(const std::string& _str, const std::string& _tofind, const std::string& _toreplace)
{
	std::string s(_str);
	std::size_t position = 0;
	for (position = s.find(_tofind); position != std::string::npos; position = s.find(_tofind, position))
		s.replace(position, 1, _toreplace);
	return s;
}
void Fle_StringUtil::replaceWithDoubleBackslash(std::string& _path)
{
	for (std::size_t i = 0; i < _path.size(); i++)
	{
		if (_path[i] == '\\')
		{
			_path.insert(i, "\\");
			i++;
		}
	}
}

static void LexicographicPermutations(const std::string& _input, const std::string& _output, std::vector<std::string>& _permutations)
{
	// base condition (permutation found)
	if (_output.length() == _input.length())
	{
		_permutations.push_back(_output);
		return;
	}

	// consider all characters of the string one by one
	for (std::size_t i = 0; i < _input.length(); i++)
	{
		// skip adjacent duplicates
		while (i + 1 < _input.length() && _input[i] == _input[i + 1])
			i++;

		LexicographicPermutations(_input, _output + _input[i], _permutations);
	}

	// OR

	// consider all characters of the string one by one
	//for (std::size_t i = 0; i < _input.length(); i++)
	//{
	//	while (i + 1 < _input.length() && _input[i] == _input[i + 1])
	//		i++;

	//	_output.push_back(_input[i]);
	//	getLexicographicPermutations(_input, _output);
	//	_output.pop_back();		// backtrack
	//}
}

std::vector<std::string> Fle_StringUtil::getLexicographicPermutations(const std::string& _input)
{
	std::vector<std::string> p;
	p.reserve(_input.length() * _input.length());
	std::string s(_input);
	std::sort(s.begin(), s.end());	// sort the string to print in lexicographical order
	LexicographicPermutations(s, "", p);
	return p;
}

bool Fle_StringUtil::endsWith(const std::string& _str, const std::string& _to_match_str)
{
	if (_str.size() >= _to_match_str.size() && _str.compare(_str.size() - _to_match_str.size(), _to_match_str.size(), _to_match_str) == 0)
		return true;
	else
		return false;
}

bool Fle_StringUtil::endsWith_caseInsensitive(std::string _str, std::string _to_match_str)
{
	std::transform(_str.begin(), _str.end(), _str.begin(), ::tolower);
	std::transform(_to_match_str.begin(), _to_match_str.end(), _to_match_str.begin(), ::tolower);
	return endsWith(_str, _to_match_str);

}

std::size_t Fle_StringUtil::getDecimalCount(double _num)
{
	std::stringstream stream;
	stream << _num;
	std::string s(stream.str());
	if (std::stod(s) == std::stoi(s))
		return 0;
	size_t found;
	std::stoi(s, &found);	// look for "."
	std::size_t n = std::string(s).substr(found).size() - 1;
	return n < 0 ? 0 : n;
}

std::vector<std::string> Fle_StringUtil::splitByWhiteSpaces(const std::string& _str)
{
	std::string buf;
	std::stringstream ss(_str);
	std::vector<std::string> tokens;
	while (ss >> buf)
		tokens.push_back(buf);
	return tokens;
}