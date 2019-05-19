#pragma once
#ifndef Fle_ImageViewer_h__
#define Fle_ImageViewer_h__

/*********************************************************************************
created:	2018/08/05   02:02AM
filename: 	Fle_ImageViewer.h
file base:	Fle_ImageViewer
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	class that creates a basic GUI based application for
viewing and editing images.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_MainWindow.h>
#include <FLE/Fle_ImageScrollBox.h>

namespace R3D
{

class Fle_ImageViewer : public Fle_MainWindow
{
public:
	// Description:
	// Constructor to create a window by specifying it's position, size, title.
	// _icon_index is the id of the icon that you want to display on the title bar.
	Fle_ImageViewer(int _x, int _y, int _w, int _h, const char* _title = 0, int _icon_index = 101);

	// Description:
	// Function that returns a pointer to an image box.
	Fle_ImageScrollBox* getImageBox() const { return p_imgBox; }

private:
	// Description:
	// Function to add menu bar in the main window.
	void addMenuBar();
	// Description:
	// Function to add status bar in the main window.
	void addStatusBar();
	// Description:
	// Function to add top bar in the main window.
	void addTopBar();
	// Description:
	// Function to add left side bar in the main window.
	void addLeftBar();
	// Description:
	// Function to add right side bar in the main window.
	void addRightBar();

	// Description:
	// Overridden functions for handling the mouse events.
	int mouseRightButtonPressEvent(int _x, int _y) override;	// when right mouse button is pressed.

	// callbacks
	static void open_image(Fl_Widget* _w, void* _p);
	static void save_as_image_cb(Fl_Widget* _w, void* _p);
	static void exit_cb(Fl_Widget* _w, void* _p);
	static void about_cb(Fl_Widget* _w, void* _p);

protected:
	Fle_ImageScrollBox* p_imgBox;
};

}

#endif // Fle_ImageViewer_h__