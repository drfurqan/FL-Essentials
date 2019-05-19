#pragma once
#ifndef Fle_Window_h__
#define Fle_Window_h__

/*********************************************************************************
created:	2017/01/27   02:05AM
filename: 	Fle_Window.h
file base:	Fle_Window
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A generalized window class with thread-safe image handling, and with 
basic necessary functions.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FL/Fl_Window.h>
#include <FLE/Fle_Box.h>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_Window : public Fl_Window
{
public:
	// Description:
	// Constructor to create a window by specifying it's position, size, and title.
	// _icon_index is the id of the icon that you want to display on the title bar.
	Fle_Window(int _x, int _y, int _w, int _h, const char* _title, int _icon_index = 101);
	// Description:
	// Destructor that destroys timers (if any) and other data.
	virtual ~Fle_Window();

	// Description:
	// Function to resize the window by specifying the width and height.
	// This function will not be called while resizing, only above function resize() does call.
	virtual void size(int _w, int _h);

	// Description:
	// Function to set the background color of the widget.
	void setBackgroundColor(uchar _red, uchar _green, uchar _blue);
	// Description:
	// Function to set the background color of the widget.
	void setBackgroundColor(Fl_Color _color);
	// Description:
	// Function to get the background color of the widget.
	Fl_Color getBackgroundColor() const;
	// Description:
	// Function to set the background color of the widget.
	void color(uchar _red, uchar _green, uchar _blue);
	// Description:
	// Function to set the background color of the widget.
	void color(Fl_Color _color);
	// Description:
	// Function to get the background color of the widget.
	Fl_Color color() const;

	// Description:
	// Function to make this window transparent by specifying the alpha value.
	void setTransparency(float _alpha) const;
};

}

#endif // Fle_Window_h__