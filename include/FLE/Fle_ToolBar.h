#pragma once
#ifndef Fle_ToolBar_h__
#define Fle_ToolBar_h__

/*********************************************************************************
created:	2017/01/28   06:54AM
filename: 	Fle_ToolBar.h
file base:	Fle_ToolBar
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A class to create toolbars in horizontal and vertical directions.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Layout.h>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_ToolBar : public Fle_VHLayout
{
public:
	// Description:
	// Constructor to create a status bar with position, size, and title.
	Fle_ToolBar(int _x, int _y, int _w, int _h, const char* _label = 0);
};

}

#endif // Fle_ToolBar_h__