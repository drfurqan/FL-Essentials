#pragma once
#ifndef Fle_Export_h__
#define Fle_Export_h__

/********************************************************************
created:	2013/12/22
created:	22:12:2013   4:32
filename: 	Fle_Export.h
file base:	Fle_Export
file ext:	h
author:		Furqan Ullah (Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved
	
purpose:	DLL and Lib support

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#  if defined(FL_ESSENTIALS_DLL)
#    ifdef FL_ESSENTIALS_LIBRARY
#      define FL_ESSENTIALS_EXPORT	__declspec(dllexport)
#    else
#      define FL_ESSENTIALS_EXPORT	__declspec(dllimport)
#    endif /* FL_ESSENTIALS_LIBRARY */
#  else
#    define FL_ESSENTIALS_EXPORT
#  endif /* FL_ESSENTIALS_DLL */


#endif // Fle_Export_h__