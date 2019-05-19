#ifdef _MSC_VER
// disable warnings:
// C4244: conversion from 'double' to 'float'
// C4267: conversion from 'size_t' to 'int'
// C4305: truncation from 'double' to 'float'
#pragma warning ( disable : 4244 4267 4305 )
#endif

/*********************************************************************************
created:	2018/08/05   02:02AM
filename: 	main.cpp
file base:	main
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	example that creates a basic GUI based application for
viewing and editing images.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>
#include "Fle_ImageViewer.h"

using namespace R3D;

int main(int argc, char* argv[])
{
	// library initialization with default modes.
	Fle_Core::init(Fle_Core::DARK_COLOR_THEME);

	// get the screen size.
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);

	// create and show the window.
	Fle_ImageViewer win(X + W / 2 - 640 / 2, Y + H / 2 - 480 / 2, W / 2, H / 2, "FL-Essentials Image Viewer");
	win.show();

	// execute the main loop.
	return Fle_Core::exec();
}
