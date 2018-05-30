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
#include <vector>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_WindowsUtil
{
public:

	// Description:
	// Function to create a stdout/stderr console at runtime for subsystem:windows or release mode.
	// It will enable the dos style console in Release version that you see in Debug version.
	// It only work on Windows (WIN32) environment.
	static void enableDosConsoleInReleaseMode();

	// Description:
	// Options for window.
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

	// Description:
	// Options for getting system folders paths.
	enum class SystemFolder
	{
		Documents = 0,
		Pictures,
		Videos,
		Music,
		Desktop,
		Windows,
		ProgramFiles,
		CommonAppData,
		StartMenu
	};

	// Description:
	// Function to get the system folder path such as Documents, Pictures, Videos, Music, etc.
	static std::string getSystemFolderPath(Fle_WindowsUtil::SystemFolder _folder);

	// Description:
	// Function that returns the directory path with no end backslash.
	static std::string getCurrentDirectory();

	// Description:
	// Function that returns a list of all folders in the given folder.
	// Example:
	// auto folders = Fle_WindowsUtil::getAllFolders("D:\\images\\*.*");
	// for (auto f : folders)
	//	 std::cout << f << std::endl;
	static std::vector<std::string> getAllFolders(const std::string& _folder_path);
	// Description:
	// Function that returns a list of all files in the given folder.
	// Example:
	// auto files = Fle_WindowsUtil::getAllFiles("D:\\images\\*.*");
	// for (auto f : files)
	//	 std::cout << f << std::endl;
	static std::vector<std::string> getAllFiles(const std::string& _folder_path);

	// Description:
	// Function that returns MSVC version string.
	// Pass _MSC_VER as argument.
	static std::string getMsvcVersionString(int _msc_ver);

	// Description:
	// Function make the given process id window always on top.
	static void makeWindowAlwaysOnTop(unsigned long _process_id, bool _isontop);

	// Description:
	// Function make this window always on top.
	static void makeWindowAlwaysOnTop(bool _isontop);

	// Description:
	// Function that create a mutex and returns it's handle.
	static void* createMutex(const char* _name);

	// Description:
	// Function that returns true if the given mutex name already exists.
	static bool mutexAlreadyExists(const char* _name);
};

}

#endif // Fle_WindowsUtil_h__