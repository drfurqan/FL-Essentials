#pragma once
#ifndef Fle_WindowsUtil_h__
#define Fle_WindowsUtil_h__

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

#include <FLE/Fle_Export.h>

#include <string>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_WindowsUtil
{
public:

	enum class Options
	{
		Hide = 0,
		ShowNormal,
		ShowMinimized,
		ShowMaximized,
		ShowNoActivate,
		Show,
		MinimumSize,
		ShowMinNoActivate,
		ShowNA,
		Restore,
		ShowDefault,
		ForceMinimize,
	};

	// Description:
	// Function to perform certain operations specified by Options on a window.
	// It only work on Windows (WIN32) environment.
	static bool setWindowOption(const char* _window_title, Options _option);

	// Description:
	// Function to convert wstring (wchar_t) to string.
	static std::wstring string_to_wstring(const std::string& _str);
	// Description:
	// Function to convert string to wstring (wchar_t).
	static std::string wstring_to_string(const std::wstring& _wstr);

	// Description:
	// Function to execute windows shell commands.
	// _command could be "open", "properties", etc. etc.
	static void shellExecute(const std::string& _filename, const std::string& _command = "properties");

	// Description:
	// Function to create a directory at the specified name.
	static bool create_directory(const std::string& _dir_name);

	// Description:
	// Function to get the system folder path such as Documents, Pictures, Videos, Music, etc.
	// Example:
	// std::string video = getSystemFolderPath(CSIDL_MYVIDEO);
	static std::string getSystemFolderPath(int _csidl);

	enum class SystemFolder
	{
		Documents = 0,
		Pictures,
		Videos,
		Music,
		Desktop
	};

	// Description:
	// Function to get the system folder path such as Documents, Pictures, Videos, Music, etc.
	static std::string getSystemFolderPath(Fle_WindowsUtil::SystemFolder _folder);
};

}

#endif // Fle_WindowsUtil_h__