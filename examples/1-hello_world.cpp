/*********************************************************************************
created:	2017/03/05   02:57AM
filename: 	hello_world.cpp
file base:	hello_world
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Hello world example application written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>
#include <FLE/Fle_MainWindow.h>
#include <FLE/Fle_ImageBox.h>

using namespace R3D;

int main()
{
	// library initialization with default modes.
	Fle_Core::init(Fle_Core::DARK_COLOR_THEME);

	// get the screen size.
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);

	// create and show the window.
	Fle_MainWindow win(X + W / 2 - 640 / 2, Y + H / 2 - 480 / 2, W / 2, H / 2, "Hello World");

	//Fle_ImageScrollBox* imgBox = new Fle_ImageScrollBox(0, 0, win.w(), win.h());			// no zooming using mouse wheel, mouse wheel will be used for vertical and horizontal scrolling.
	Fle_ImageBox* imgBox = new Fle_ImageBox(0, 0, win.w(), win.h());	// zooming using mouse wheel, vertical and horizontal scrolling is disabled.
	imgBox->color(win.color());
	imgBox->setImageDrawType(Fle_ImageDrawType::Fit);
	imgBox->loadImage("C:\\image.png", true); // load image from the disk and reset the ROI.

	// set as a central widget.
	win.setCentralWidget(imgBox);

	// show the main window.
	win.show();

	// execute the main loop.
	return Fle_Core::exec();
}
