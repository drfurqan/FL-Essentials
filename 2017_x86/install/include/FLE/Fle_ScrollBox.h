#pragma once
#ifndef Fle_ScrollBox_h__
#define Fle_ScrollBox_h__

/*********************************************************************************
created:	2017/01/27   04:02AM
filename: 	Fle_ScrollBox.h
file base:	Fle_ScrollBox
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized scroll box widget with image zoom/pan support.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Box.h>

#include <FL/Fl_Scroll.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_ScrollBox : public Fl_Scroll
{
public:
	// Description:
	// Constructor to create a box widget inside the parent window.
	// Default box style/type is Fl_Boxtype::FL_NO_BOX.
	// By default, image draw type is ImageDrawType::Fit.
	// Note: zooming only wors with ImageDrawType::Center.
	Fle_ScrollBox(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor to release data.
	virtual ~Fle_ScrollBox();

	// Description:
	// Function to resize the window.
	// Overridden function that will be called while resizing the window.
	virtual void resize(int _x, int _y, int _w, int _h) override;
	// Description:
	// Function to resize the window.
	// Overridden function that will be called while resizing the window.
	virtual void size(int _w, int _h);

	// Description:
	// Function to make zoom in with a scale of 1.2.
	void zoomIn();
	// Description:
	// Function to make zoom out with a scale of 0.8.
	void zoomOut();

	// Description:
	// Function to set a pointer to embedded box.
	// Better to first delete the previous one and then assign a pointer to new one.
	void setBox(Fle_Box* _b);
	// Description:
	// Function to get a pointer to embedded box.
	Fle_Box* getBox() const { return p_box; }

protected:
	// Description:
	// Function to handle events.
	virtual int handle(int _event) override;
	// Description:
	// Embedded box inside the Double_Window.
	Fle_Box* p_box;
};

}

#endif // Fle_ScrollBox_h__