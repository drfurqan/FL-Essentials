#pragma once
#ifndef Fle_BoxWindow_h__
#define Fle_BoxWindow_h__

/*********************************************************************************
created:	2017/08/28   11:41PM
filename: 	Fle_BoxWindow.h
file base:	Fle_BoxWindow
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized window with an image box that supports zooming/panning.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Window.h>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_BoxWindow : public Fle_Window
{
public:
	// Description:
	// Constructor to create a box widget inside the parent window.
	// Default box style/type is Fl_Boxtype::FL_NO_BOX.
	// By default, image draw type is ImageDrawType::Fit.
	// Note: zooming only wors with ImageDrawType::Center.
	Fle_BoxWindow(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Constructor to create a window by specifying it's size and title.
	// This constructor sets the position at the center of the screen/monitor.
	// _icon_index is the id of the icon that you want to display on the title bar.
	Fle_BoxWindow(int _w, int _h, const char* _title);
	// Description:
	// Destructor to release data.
	virtual ~Fle_BoxWindow();

	// Description:
	// Function to make zoom in with a scale of 1.2.
	void zoomIn();
	// Description:
	// Function to make zoom out with a scale of 0.8.
	void zoomOut();

protected:

	// Description:
	// Overridden function that handles all kind of events.
	// Event handler (for internal use).
	virtual int handle(int _event) override;
};

}

#endif // Fle_BoxWindow_h__