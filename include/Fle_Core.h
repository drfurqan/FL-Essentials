#pragma once
#ifndef Fle_Core_h__
#define Fle_Core_h__

/*********************************************************************************
created:	2017/01/28   03:26AM
filename: 	Fle_Core.h
file base:	Fle_Core
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Core functionalities of Fle lib.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Export.h"

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_Core
{
public:
	// Description:
	// Function to initialize the FLE and FLTK libraries.
	static void init();
	// Description:
	// Function to event loop for the library.
	static int exec();
};

}

#endif // Fle_Core_h__