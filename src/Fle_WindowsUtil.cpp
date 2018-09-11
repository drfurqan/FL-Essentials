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
#define _WIN32_WINNT 0x0501 // needed for AttachConsole
#include <windows.h>
#include <wincon.h> 	// AttachConsole()
#include <direct.h>
#include <shlobj.h>
#include <Shellapi.h>	// SHELLEXECUTEINFO
#include <process.h>	// _getpid()
#include <stdio.h>
#include <lmcons.h>
#endif // _WIN32
#include <sys/types.h> 	// required for stat.h
#include <sys/stat.h> 	// no clue why required -- man pages say so

using namespace R3D;

void Fle_WindowsUtil::enableDosConsoleInReleaseMode()
{
#ifdef _WIN32
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);
#endif // _WIN32
}

bool Fle_WindowsUtil::setWindowOption(const char* _window_title, Options _option)
{
#ifdef _WIN32
	HWND hWnd = FindWindowA(nullptr, _window_title);
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
	int slength = static_cast<int>(_str.length() + 1);
	int len = MultiByteToWideChar(CP_ACP, 0, _str.c_str(), slength, 0, 0);
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
	if (_filename.empty()) return;
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
	else if (_folder == Fle_WindowsUtil::SystemFolder::Windows)
		return getSystemFolderPath(CSIDL_WINDOWS);
	else if (_folder == Fle_WindowsUtil::SystemFolder::ProgramFiles)
		return getSystemFolderPath(CSIDL_PROGRAM_FILES);
	else if (_folder == Fle_WindowsUtil::SystemFolder::CommonAppData)
		return getSystemFolderPath(CSIDL_COMMON_APPDATA);
	else if (_folder == Fle_WindowsUtil::SystemFolder::StartMenu)
		return getSystemFolderPath(CSIDL_STARTMENU);
#endif

	return "";
}

std::string Fle_WindowsUtil::getCurrentDirectory()
{
	const unsigned long n = 1024;
#if defined(_WIN32)
		char cd[n];
#ifdef _UNICODE
			GetCurrentDirectoryA(n, cd);
#else
			GetCurrentDirectory(n, cd);
#endif
			return std::string(cd);
#else
return "";
	//char result[n];
	//ssize_t count = readlink("/proc/self/exe", result, n);
	//return std::string(result, (count > 0) ? count : 0);
#endif
}

std::string Fle_WindowsUtil::getMsvcVersionString(int _msc_ver)
{
	std::string version;
	switch (_msc_ver)
	{
	case 1310:
		version = "MSVC++ 7.1 (Visual Studio 2003)";
		break;
	case 1400:
		version = "MSVC++ 8.0 (Visual Studio 2005)";
		break;
	case 1500:
		version = "MSVC++ 9.0 (Visual Studio 2008)";
		break;
	case 1600:
		version = "MSVC++ 10.0 (Visual Studio 2010)";
		break;
	case 1700:
		version = "MSVC++ 11.0 (Visual Studio 2012)";
		break;
	case 1800:
		version = "MSVC++ 12.0 (Visual Studio 2013)";
		break;
	case 1900:
		version = "MSVC++ 14.0 (Visual Studio 2015)";
		break;
	case 1910:
		version = "MSVC++ 14.1 (Visual Studio 2017)";
		break;
	case 1912:
		version = "MSVC++ 14.1 (Visual Studio 2017)";
		break;
	default:
		version = "unknown MSVC++ version";
	}
	return version;
}

/************************************************************************/
/* Make Window Always on Top                                            */
/************************************************************************/
#if defined(_WIN32)
BOOL CALLBACK EnumWindowsAlwaysOnTop(HWND _window_handle, LPARAM _l_param)
{
	DWORD searchedProcessId = static_cast<DWORD>(_l_param);  // This is the process ID we search for (passed from BringToForeground as lParam)
	DWORD windowProcessId = 0;
	GetWindowThreadProcessId(_window_handle, &windowProcessId); // Get process ID of the window we just found
	if (searchedProcessId == windowProcessId)
	{
		SetWindowPos(_window_handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
		return 0;	// Stop enumerating windows
	}
	return 1;		// Continue enumerating
}
BOOL CALLBACK EnumWindowsNotAlwaysOnTop(HWND _window_handle, LPARAM _l_param)
{
	unsigned long searchedProcessId = static_cast<unsigned long>(_l_param);  // This is the process ID we search for (passed from BringToForeground as lParam)
	unsigned long windowProcessId = 0;
	GetWindowThreadProcessId(_window_handle, &windowProcessId); // Get process ID of the window we just found
	if (searchedProcessId == windowProcessId)
	{
		SetWindowPos(_window_handle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
		return 0;	// Stop enumerating windows
	}
	return 1;		// Continue enumerating
}
#endif // _WIN32

void Fle_WindowsUtil::makeWindowAlwaysOnTop(unsigned long _process_id, bool _isontop)
{
#if defined(_WIN32)
	if (_isontop)
		EnumWindows(&EnumWindowsAlwaysOnTop, (LPARAM)_process_id);
	else
		EnumWindows(&EnumWindowsNotAlwaysOnTop, (LPARAM)_process_id);
#endif // _WIN32
}

void Fle_WindowsUtil::makeWindowAlwaysOnTop(bool _isontop)
{
#if defined(_WIN32)
	makeWindowAlwaysOnTop(_getpid(), _isontop);
#endif // _WIN32
}

void* Fle_WindowsUtil::createMutex(const char* _name)
{
	void* h = nullptr;
#if defined(_WIN32)
#ifdef _UNICODE
	h = CreateMutex(nullptr, TRUE, string_to_wstring(_name).c_str());
#else
	h = CreateMutex(nullptr, TRUE, _name);
#endif // _UNICODE
	const unsigned long e = GetLastError();
	if (e == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(h);
		return nullptr;
	}
	else if (e == ERROR_ACCESS_DENIED)
	{
		CloseHandle(h);
		return nullptr;
	}
#endif // _WIN32
	return h;
}

bool Fle_WindowsUtil::mutexAlreadyExists(const char* _name)
{
	void* h = nullptr;
#if defined(_WIN32)
#ifdef _UNICODE
	h = CreateMutex(nullptr, TRUE, string_to_wstring(_name).c_str());
#else
	h = CreateMutex(nullptr, TRUE, _name);
#endif // _UNICODE
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(h);
		return true;
	}
	CloseHandle(h);
	return false;
#endif // _WIN32
	return false;
}

/*-------------------------------------------------------------------------
https://support.microsoft.com/en-us/help/118626/how-to-determine-whether-a-thread-is-running-in-user-context-of-local
This function checks the token of the calling thread to see if the caller
belongs to the Administrators group.

Return Value:
TRUE if the caller is an administrator on the local machine.
Otherwise, FALSE.
--------------------------------------------------------------------------*/
int Fle_WindowsUtil::isCurrentUserLocalAdministrator()
{
#if defined(_WIN32)

	BOOL   fReturn = FALSE;
	DWORD  dwStatus;
	DWORD  dwAccessMask;
	DWORD  dwAccessDesired;
	DWORD  dwACLSize;
	DWORD  dwStructureSize = sizeof(PRIVILEGE_SET);
	PACL   pACL = NULL;
	PSID   psidAdmin = NULL;

	HANDLE hToken = NULL;
	HANDLE hImpersonationToken = NULL;

	PRIVILEGE_SET   ps;
	GENERIC_MAPPING GenericMapping;

	PSECURITY_DESCRIPTOR     psdAdmin = NULL;
	SID_IDENTIFIER_AUTHORITY SystemSidAuthority = SECURITY_NT_AUTHORITY;

	const DWORD ACCESS_READ = 1;
	const DWORD ACCESS_WRITE = 2;

	__try
	{

		if (!OpenThreadToken(GetCurrentThread(), TOKEN_DUPLICATE | TOKEN_QUERY, TRUE, &hToken))
		{
			if (GetLastError() != ERROR_NO_TOKEN)
				__leave;

			if (!OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE | TOKEN_QUERY, &hToken))
				__leave;
		}

		if (!DuplicateToken(hToken, SecurityImpersonation, &hImpersonationToken))
			__leave;

		if (!AllocateAndInitializeSid(&SystemSidAuthority, 2,
			SECURITY_BUILTIN_DOMAIN_RID,
			DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0, &psidAdmin))
			__leave;

		psdAdmin = LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
		if (psdAdmin == NULL)
			__leave;

		if (!InitializeSecurityDescriptor(psdAdmin, SECURITY_DESCRIPTOR_REVISION))
			__leave;

		// Compute size needed for the ACL.
		dwACLSize = sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) + GetLengthSid(psidAdmin) - sizeof(DWORD);

		pACL = (PACL)LocalAlloc(LPTR, dwACLSize);
		if (pACL == NULL)
			__leave;

		if (!InitializeAcl(pACL, dwACLSize, ACL_REVISION2))
			__leave;

		dwAccessMask = ACCESS_READ | ACCESS_WRITE;

		if (!AddAccessAllowedAce(pACL, ACL_REVISION2, dwAccessMask, psidAdmin))
			__leave;

		if (!SetSecurityDescriptorDacl(psdAdmin, TRUE, pACL, FALSE))
			__leave;

		/*
		   AccessCheck validates a security descriptor somewhat; set the group
			 and owner so that enough of the security descriptor is filled out to
			 make AccessCheck happy.
		 */
		SetSecurityDescriptorGroup(psdAdmin, psidAdmin, FALSE);
		SetSecurityDescriptorOwner(psdAdmin, psidAdmin, FALSE);

		if (!IsValidSecurityDescriptor(psdAdmin))
			__leave;

		dwAccessDesired = ACCESS_READ;

		/*
		   Initialize GenericMapping structure even though you
		   do not use generic rights.
		*/
		GenericMapping.GenericRead = ACCESS_READ;
		GenericMapping.GenericWrite = ACCESS_WRITE;
		GenericMapping.GenericExecute = 0;
		GenericMapping.GenericAll = ACCESS_READ | ACCESS_WRITE;

		if (!AccessCheck(psdAdmin, hImpersonationToken, dwAccessDesired,
			&GenericMapping, &ps, &dwStructureSize, &dwStatus,
			&fReturn))
		{
			fReturn = FALSE;
			__leave;
		}
	}
	__finally
	{
		// Clean up.
		if (pACL) LocalFree(pACL);
		if (psdAdmin) LocalFree(psdAdmin);
		if (psidAdmin) FreeSid(psidAdmin);
		if (hImpersonationToken) CloseHandle(hImpersonationToken);
		if (hToken) CloseHandle(hToken);
	}

	return int(fReturn);
#endif // _WIN32

	return 0;
}