/*********************************************************************************
created:	2017/03/14   02:11AM
filename: 	OGLWindow_main.cpp
file base:	OGLWindow_main
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	OpenGL program to animate the scene, written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>
#include <FLE/Fle_MainWindow.h>
#include "OGLWindow.h"

int main(int argc, char* argv[])
{
	// library initialization with default modes.
	Fle_Core::init();
	// to make widgets flat.
	Fl::set_boxtype(Fl_Boxtype::FL_UP_BOX, Fl_Boxtype::FL_BORDER_BOX);			// change box type to flat only.
	Fl::set_boxtype(Fl_Boxtype::FL_DOWN_BOX, Fl_Boxtype::FL_BORDER_BOX);		// change menu check box type to flat only.
	Fl::set_boxtype(Fl_Boxtype::_FL_ROUND_DOWN_BOX, Fl_Boxtype::FL_BORDER_BOX);	// change menu radio box type to flat only.
	Fl::set_boxtype(Fl_Boxtype::_FL_ROUND_UP_BOX, Fl_Boxtype::FL_BORDER_BOX);	// change box type to flat only.

	// create main window that can have menubar, toolbars, statusbar etc.
	Fle_MainWindow win(1024, 500, "OpenGL Program with Animation, Events, Lights, and Material");
	win.begin();

	// add OpenGL window to the main window by specifying it's width and height.
	GLWindow* glwin = new GLWindow(0, 0, 1024, 500);

	win.end();
	win.show(argc, argv);
	win.updateGeometry();

	// execute the main loop.
	return Fle_Core::exec();
}

