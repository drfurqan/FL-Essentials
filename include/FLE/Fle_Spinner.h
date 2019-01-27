#pragma once
#ifndef Fle_Spinner_h__
#define Fle_Spinner_h__

/*********************************************************************************
created:	2017/03/14   07:20PM
filename: 	Fle_Spinner.h
file base:	Fle_Spinner
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Spinner class that allows to change the settings of Up and Down buttons.
/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <FL/Fl_Spinner.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_Spinner : public Fl_Spinner
{
public:
	// Description:
	// Default ctor to create a spinner widget.
	Fle_Spinner(int _x, int _y, int _w, int _h, const char* _lable = 0);

	// Description:
	// Function that sets the flags used to decide when a callback is called.
	void when(uchar i);

	// Description:
	// Function to get a reference to up button.
	Fl_Repeat_Button& getUpButton() { return up_button_; }
	// Description:
	// Function to get a reference to down button.
	Fl_Repeat_Button& getDownButton() { return down_button_; }
};

}

#endif // Fle_Spinner_h__