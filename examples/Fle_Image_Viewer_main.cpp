/*********************************************************************************
created:	2017/03/05   11:36PM
filename: 	Fle_Image_Viewer_main.cpp
file base:	Fle_Image_Viewer_main
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	a demo application (Real3D Photo Viewer) written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>
#include "Fle_Image_Viewer.h"

using namespace R3D;

int main(int argc, char* argv[])
{
	// library initialization with default modes.
	uchar r = 220, g = 220, b = 220;
	Fle_Core::init();
	Fl::set_color(FL_BACKGROUND_COLOR, r, g, b);			// it will change the radio button's background color.
	Fl::set_color(FL_DARK3, r, g, b);						// change the FL_MENU_DIVIDER line color
	Fl::set_color(FL_LIGHT3, r - 10, g - 10, b - 10);		// change the FL_MENU_DIVIDER line color
	Fl::set_color(FL_BACKGROUND2_COLOR, 255, 255, 255);		// it will change the radio button's background color.
	Fl::set_color(FL_FOREGROUND_COLOR, 0, 0, 0);			// it will change the menu's text color.
	Fl::set_color(FL_BLACK, 0, 0, 0);						// change the black color of FLTK widgets to dark gray.
	// to make widgets flat.
	Fl::set_boxtype(Fl_Boxtype::FL_UP_BOX, Fl_Boxtype::FL_FLAT_BOX);			// change box type to flat only.
	Fl::set_boxtype(Fl_Boxtype::FL_DOWN_BOX, Fl_Boxtype::FL_BORDER_BOX);		// change menu check box type to flat only.
	Fl::set_boxtype(Fl_Boxtype::_FL_ROUND_DOWN_BOX, Fl_Boxtype::FL_BORDER_BOX);	// change menu radio box type to flat only.
	Fl::set_boxtype(Fl_Boxtype::_FL_ROUND_UP_BOX, Fl_Boxtype::FL_BORDER_BOX);	// change box type to flat only.
	Fl::box_color(FL_GRAY);
	Fl::set_box_color(FL_GRAY);

	// parsing arguments, argv[1] will be the file name when we 
	// open any image using the executable of this application.
	std::string file;
	if (argc == 2) 
		file = argv[1];

	// create and initialize an image viewer.
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	Fle_Image_Viewer win(W, H - 24, "Real3d Photo Viewer");
	win.show();
	win.updateGeometry();
	win.loadImage(file);	// load the image from command line.

	return Fle_Core::exec();		// execute the main loop.
}