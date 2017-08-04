/*********************************************************************************
created:	2017/02/25   01:58AM
filename: 	Fle_WindowsUtil.h
file base:	Fle_WindowsUtil
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	This class contains some important Windows utility functions.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_WindowsUtil.h>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#include <shlobj.h>
#endif // _WIN32
#include <sys/types.h> // required for stat.h
#include <sys/stat.h> // no clue why required -- man pages say so

using namespace R3D;

bool Fle_WindowsUtil::setWindowOption(const char* _window_title, Options _option)
{
#ifdef _WIN32
	HWND hWnd = FindWindowA(NULL, _window_title);
	if (hWnd)
	{
		ShowWindow(hWnd, static_cast<int>(_option));
		ShowWindow(hWnd, static_cast<int>(_option));
		// for multi-threaded applications
		//ShowWindowAsync(hWnd, static_cast<int>(_option));
		//ShowWindowAsync(hWnd, static_cast<int>(_option));
		return true;
	}
#endif // _WIN32
	return false;
}

std::wstring Fle_WindowsUtil::string_to_wstring(const std::string& _str)
{
	std::wstring temp;
#ifdef _WIN32
	int len;
	int slength = static_cast<int>(_str.length() + 1);
	len = MultiByteToWideChar(CP_ACP, 0, _str.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, _str.c_str(), slength, buf, len);
	temp = buf;
	delete[] buf;
#endif // _WIN32
	return temp;
}

std::string Fle_WindowsUtil::wstring_to_string(const std::wstring& _wstr)
{
	std::string temp;
#ifdef _WIN32
	int slength = static_cast<int>(_wstr.length() + 1);
	int len = WideCharToMultiByte(CP_ACP, 0, _wstr.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, _wstr.c_str(), slength, buf, len, 0, 0);
	temp = buf;
	delete[] buf;
#endif // _WIN32
	return temp;
}

#ifdef _UNICODE
static std::wstring m_wstring_file;
static std::wstring m_wstring_verb;
#else
static std::string m_wstring_file;
static std::string m_wstring_verb;
#endif // _UNICODE

void Fle_WindowsUtil::shellExecute(const std::string& _filename, const std::string& _command)
{
#ifdef _WIN32
#ifdef _UNICODE
	m_wstring_file = string_to_wstring(_filename).c_str();
	m_wstring_verb = string_to_wstring(_command).c_str();
#else
	m_wstring_file = _filename;
	m_wstring_verb = _command;
#endif // _UNICODE

	SHELLEXECUTEINFO info = { 0 };
	info.cbSize = sizeof info;
	info.lpFile = m_wstring_file.c_str();
	info.nShow = SW_SHOW;
	info.fMask = SEE_MASK_INVOKEIDLIST;
	info.lpVerb = m_wstring_verb.c_str();
	ShellExecuteEx(&info);
#endif // _WIN32
}

bool Fle_WindowsUtil::create_directory(const std::string& _dir_name)
{
#if defined(_WIN32)
	if (_mkdir(_dir_name.c_str()) == 0)
		return true;
#else 
	mode_t nMode = 0733; // UNIX style permissions
	if(mkdir(_dir_name.c_str(), nMode) == 0) // can be used on non-Windows
		return true;
#endif
	return false;
}

std::string Fle_WindowsUtil::getSystemFolderPath(int _csidl)
{
#if defined(_WIN32)
	wchar_t folder[1024];
	HRESULT hr = SHGetFolderPathW(0, _csidl, 0, 0, folder);
	if (SUCCEEDED(hr))
	{
		char str[1024];
		wcstombs(str, folder, 1023);
		return str;
	}
#endif

	return "";
}
std::string Fle_WindowsUtil::getSystemFolderPath(Fle_WindowsUtil::SystemFolder _folder)
{
#if defined(_WIN32)
	if (_folder == Fle_WindowsUtil::SystemFolder::Documents)
		return getSystemFolderPath(CSIDL_MYDOCUMENTS);
	else if (_folder == Fle_WindowsUtil::SystemFolder::Pictures)
		return getSystemFolderPath(CSIDL_MYPICTURES);
	else if (_folder == Fle_WindowsUtil::SystemFolder::Videos)
		return getSystemFolderPath(CSIDL_MYVIDEO);
	else if (_folder == Fle_WindowsUtil::SystemFolder::Music)
		return getSystemFolderPath(CSIDL_MYMUSIC);
	else if (_folder == Fle_WindowsUtil::SystemFolder::Desktop)
		return getSystemFolderPath(CSIDL_DESKTOP);
#endif

	return "";
}