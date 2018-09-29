/*********************************************************************************
created:	2017/02/15   02:20AM
filename: 	Fle_Slider.cpp
file base:	Fle_Slider
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized FL_Slider.
/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Slider.h>

#include <FL/Fl_Menu_Button.H>

using namespace R3D;

Fle_Slider::Fle_Slider(int _x, int _y, int _w, int _h, const char* _lable) :
	Fl_Slider(_x, _y, _w, _h, _lable)
{
}

void Fle_Slider::draw()
{
	Fl_Slider::draw();
}