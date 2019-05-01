#pragma once
#ifndef Fle_Slider_h__
#define Fle_Slider_h__

/*********************************************************************************
created:	2017/02/15   02:20AM
filename: 	Fle_Slider.h
file base:	Fle_Slider
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized FL_Slider.
/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <FL/Fl_Slider.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_Slider : public Fl_Slider
{
public:
	// Description:
	// Creates a new Fl_Slider widget using the given position, size, and label string.
	Fle_Slider(int _x, int _y, int _w, int _h, const char* _lable = 0);

protected:
	void draw_bg(int X, int Y, int W, int H);
	void draw(int X, int Y, int W, int H);
	void draw() override;
};

}

#endif // Fle_Slider_h__