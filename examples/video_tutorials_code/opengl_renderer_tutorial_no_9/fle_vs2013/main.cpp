/*********************************************************************************
created:	2017/07/01   03:11AM
filename: 	main.cpp
file base:	main
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	a simple 3D mesh renderer that supports PLY file format with texture.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
	// library initialization with default modes.
	Fle_Core::init();

	// create main window that can have menubar, toolbars, statusbar etc.
	MainWindow win(1024, 500, "3D Mesh Renderer (written in FLE)");
	win.show(argc, argv);
	win.showMaximized();
	win.updateGeometry();

	// execute the main loop.
	return Fle_Core::exec();
}