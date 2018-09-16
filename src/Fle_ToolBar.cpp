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
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ToolBar.h>

using namespace R3D;

Fle_ToolBar::Fle_ToolBar(int _x, int _y, int _w, int _h, const char* _label) :
Fle_VHLayout(_x, _y, _w, _h, _label)
{
	Fle_VHLayout::end();
	Fle_VHLayout::setBackgroundColor(214, 219, 233);
	getCentralLayout()->setBackgroundColor(214, 219, 233);
}