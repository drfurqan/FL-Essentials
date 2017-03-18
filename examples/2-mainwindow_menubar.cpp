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

#include "Fle_Core.h"
#include "Fle_MainWindow.h"
#include "Fle_Dialog.h"

using namespace R3D;

void menu_callback(Fl_Widget* _w, void* _p)
{
	std::ostringstream sstream;
	sstream <<
		"<br><center><h3>FLE v1.1.0</h3></center>"
		"<center><h6>(March 06 2017)</h6></center>"
		"<br><center><h4><a href=\"http://real3d.pk/\">http://real3d.pk/</a></h4></center>"
		"</p><br><center><a href=\"mailto:info@real3d.pk\">info@real3d.pk</a></center></p>";
	Fle_Dialog::openHelpDialog
	(
		400, 300,
		"About",
		sstream.str(),
		Fle_Font(13, FL_WHITE),
		"",
		Fle_Font(13, FL_WHITE)
	);
}

int main(int argc, char *argv[])
{
	// library initialization with default modes.
	Fle_Core::init();

	// create a main window.
	Fle_MainWindow* w = new Fle_MainWindow(1024, 500, "Hello World");
	w->setMinimumSize(cv::Size(300, 300));
	w->setMaximumSize(cv::Size(10000, 10000));

	// load image from disk and display in the central widget.
	w->getCentralWidget()->getBox()->loadImage("D:\\aw.jpg");
	w->getCentralWidget()->getBox()->setImageDrawType(Fle_ImageDrawType::Fit);

	// show the menubar and set it's fixed height.
	w->getMenuBar()->show();
	w->setMenuBarFixedHeight(25);
	{
		// add items to menubar.
		Fle_MenuBar* menu = w->getMenuBar();
		menu->add(" FILE /          New             ",		FL_CTRL + 'n', menu_callback);
		menu->add(" FILE /          Open             ",		FL_CTRL + 'o', menu_callback, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /          Save             ",		FL_CTRL + 's', menu_callback);
		menu->add(" FILE /          Save As...             ",			0, menu_callback, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /          Print...             ", FL_CTRL + 'p', menu_callback, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /          Exit             ",		FL_ALT + FL_F + 4, menu_callback);;
		menu->add(" EDIT /          Copy             ",		FL_CTRL + 'c', menu_callback);
		menu->add(" EDIT /          Paste            ",		FL_CTRL + 'v', menu_callback);
		menu->add(" EDIT /          Delete            ",	FL_CTRL + 'd', menu_callback);
	}

	// show the main window.
	w->show(argc, argv);

	// execute the main loop.
	return Fle_Core::exec();
}