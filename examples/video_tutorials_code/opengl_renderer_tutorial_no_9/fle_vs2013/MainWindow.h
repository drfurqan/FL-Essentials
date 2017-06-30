#pragma once
#ifndef MainWindow_h__
#define MainWindow_h__

/*********************************************************************************
created:	2017/07/01   02:20AM
filename: 	MainWindow.h
file base:	MainWindow
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	class that creates a main windows with menu, statusbar, GL renderer, etc.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_MainWindow.h>
#include "GLRenderer.h"

using namespace R3D;

/************************************************************************/
/* class for Solar System                                               */
/************************************************************************/
class MainWindow : public Fle_MainWindow
{
public:
	// Description:
	// Constructor to create an OpenGL window by specifying it's size and title.
	// This constructor sets the position at the center of the screen/monitor.
	MainWindow(int _w, int _h, const char* _title);

protected:
	GLRenderer* p_renderer;	// pointer to GL renderer

private:
	void addMenuBar();		// function that adds menu and actions
	void addStatusBar();	// function that adds a statusbar

	static void new_cb(Fl_Widget* _w, void* _p);
	static void open_cb(Fl_Widget* _w, void* _p);
	static void texture_cb(Fl_Widget* _w, void* _p);
	static void exit_cb(Fl_Widget* _w, void* _p);

	static void animation_cb(Fl_Widget* _w, void* _p);

	static void website_cb(Fl_Widget* _w, void* _p);
	static void download_cb(Fl_Widget* _w, void* _p);
	static void about_cb(Fl_Widget* _w, void* _p);
};

#endif // MainWindow_h__