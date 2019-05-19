/*********************************************************************************
created:	2017/03/05   02:57AM
filename: 	mainwindow_menubar.cpp
file base:	mainwindow_menubar
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	MainWindow (with a menubar) application written in FLE.

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
#include <FLE/Fle_Dialog.h>

using namespace R3D;

void menu_callback(Fl_Widget* _w, void* _p)
{
	std::ostringstream sstream;
	sstream <<
		"<br><center><h3>FLE v1.3.1</h3></center>"
		"<center><h6>(March 27 2017)</h6></center>"
		"<br><center><h4><a href=\"http://real3d.pk/\">http://real3d.pk/</a></h4></center>"
		"</p><br><center><a href=\"mailto:info@real3d.pk\">info@real3d.pk</a></center></p>";
	Fle_Dialog::openHelpDialog
	(
		400, 300,
		"About",
		sstream.str(),
		Fle_Font(13, FL_WHITE),
		"FLE Title",
		Fle_Font(13, FL_WHITE)
	);
}

int main()
{
	// library initialization with default modes.
	Fle_Core::init();

	// get the screen size.
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);

	// create and show the window.
	Fle_MainWindow win(X + W / 2 - 640 / 2, Y + H / 2 - 480 / 2, W / 2, H / 2, "MainWindow with MenuBar");
	win.setMinimumSize(Fle_Size(300, 300));

	//Fle_ImageScrollBox* imgBox = new Fle_ImageScrollBox(0, 0, win.w(), win.h());			// no zooming using mouse wheel, mouse wheel will be used for vertical and horizontal scrolling.
	Fle_ImageBox* imgBox = new Fle_ImageBox(0, 0, win.w(), win.h());	// zooming using mouse wheel, vertical and horizontal scrolling is disabled.
	imgBox->color(win.color());
	imgBox->setImageDrawType(Fle_ImageDrawType::Fit);
	imgBox->loadImage("C:\\image.png", true); // load image from the disk and reset the ROI.

	// set as a central widget.
	win.setCentralWidget(imgBox);

	// add items to the menubar.
	{
		Fle_MenuBar* menu = win.getMenuBar();
		menu->add(" FILE /\t New \t\t\t", FL_CTRL + 'n', menu_callback);
		menu->add(" FILE /\t Open \t\t\t", FL_CTRL + 'o', menu_callback, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /\t Save \t\t\t", FL_CTRL + 's', menu_callback);
		menu->add(" FILE /\t Save As... \t\t\t", 0, menu_callback, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /\t Print... \t\t\t", FL_CTRL + 'p', menu_callback, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /\t Exit \t\t\t", FL_ALT + FL_F + 4, menu_callback);;
		menu->add(" EDIT /\t Copy \t\t\t", FL_CTRL + 'c', menu_callback);
		menu->add(" EDIT /\t Paste \t\t\t", FL_CTRL + 'v', menu_callback);
		menu->add(" EDIT /\t Delete \t\t\t", FL_CTRL + 'd', menu_callback);
	}
	// show the menubar.
	win.getMenuBar()->show();

	// show the main window at the center of the screen.
	win.show();

	// execute the main loop.
	return Fle_Core::exec();
}
