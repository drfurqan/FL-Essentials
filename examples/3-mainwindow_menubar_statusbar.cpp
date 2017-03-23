/*********************************************************************************
created:	2017/03/05   02:57AM
filename: 	mainwindow_menubar_statusbar.cpp
file base:	mainwindow_menubar_statusbar
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	MainWindow (with a menu and a statusbar) application written in FLE.

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
#include "Fle_Widgets.h"

using namespace R3D;

void menu_cb(Fl_Widget* _w, void* _p)
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

int main(int argc, char* argv[])
{
	// library initialization with default modes.
	Fle_Core::init();

	// create a main window.
	Fle_MainWindow* w = new Fle_MainWindow(1024, 500, "Hello World");
	w->setMinimumSize(Fle_Size(300, 300));
	w->setMaximumSize(Fle_Size(10000, 10000));

	// load image from disk and display in the central widget.
	w->getCentralWidget()->getBox()->loadImage("D:\\aw.jpg");
	w->getCentralWidget()->getBox()->setImageDrawType(Fle_ImageDrawType::Fit);

	// show the menubar and set it's fixed height.
	w->getMenuBar()->show();
	w->setMenuBarFixedHeight(25);
	{
		// add items to menubar.
		Fle_MenuBar* menu = w->getMenuBar();
		menu->add(" FILE /          New             ",		FL_CTRL + 'n', menu_cb);
		menu->add(" FILE /          Open             ",		FL_CTRL + 'o', menu_cb, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /          Save             ",		FL_CTRL + 's', menu_cb);
		menu->add(" FILE /          Save As...             ",			0, menu_cb, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /          Print...             ", FL_CTRL + 'p', menu_cb, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /          Exit             ",		FL_ALT + FL_F + 4, menu_cb);;
		menu->add(" EDIT /          Copy             ",		FL_CTRL + 'c', menu_cb);
		menu->add(" EDIT /          Paste            ",		FL_CTRL + 'v', menu_cb);
		menu->add(" EDIT /          Delete            ",	FL_CTRL + 'd', menu_cb);
	}

	// set fixed width and margins to statusbar.
	w->getStatusBar()->show();
	w->getStatusBar()->setMargins(5, 15, 0, 0);
	w->setStatusBarFixedHeight(25);
	{
		// add a Left-Right horizontal layout in the statusbar.
		Fle_HLayoutLR* layout = w->getStatusBar()->addLayoutLR(21);
		layout->setMargins(0, 0, 2, 0);
		layout->setBackgroundColor(0, 122, 204);

		// begin to add/pack widgets at the most left side of the statusbar.
		layout->beginLeft();

		Fle_Box* p_textbox = new Fle_Box(0, 0, 300, 21);		// a text box at the most left corner.
		p_textbox->box(FL_FLAT_BOX);
		p_textbox->color(Fle_Widgets::fromRGB(0, 122, 204));
		p_textbox->getFont()->setSize(12);
		p_textbox->getFont()->setColor(Fle_Widgets::fromRGB(255, 255, 255));
		p_textbox->getFont()->setAlignment(FL_ALIGN_LEFT);
		p_textbox->setText("Ready");

		w->getStatusBar()->setTextBox(p_textbox);		// set the text box to show messages with time interval.

		Fle_Box* label = Fle_Widgets::createLabel(21, "Slider ");
		label->color(Fle_Widgets::fromRGB(0, 122, 204));
		label->getFont()->setColor(Fle_Widgets::fromRGB(255, 255, 255));

		Fle_InputSlider* b1 = Fle_Widgets::createIntInputSlider(200, 21);
		b1->labelcolor(Fle_Widgets::fromRGB(255, 255, 255));

		Fle_Button* b2 = Fle_Widgets::createButton(21, "D:\\play.png", "D:\\stop.png");
		Fle_Button* b3 = Fle_Widgets::createButton(100, 21, "Button 3", 1, Fle_Widgets::ButtonType::NORMAL);

		// stop adding/packing widgets at the most left side of the statusbar.
		layout->endLeft();

		// begin to add/pack widgets at the most right side of the statusbar.
		layout->beginRight();

		Fle_Box* box = Fle_Widgets::createBox(100, 21, "a box is here");
		box->color(Fle_Widgets::fromRGB(0, 122, 204));
		box->getFont()->setColor(Fle_Widgets::fromRGB(255, 255, 255));

		Fle_Box* b = Fle_Widgets::createImageBox(35, 21, "D:\\people.jpg");

		Fle_Widgets::createClock(22, 22);

		// stop adding/packing widgets at the most right side of the statusbar.
		layout->endRight();
	}

	// show the main window.
	w->show(argc, argv);
	w->updateGeometry();

	// execute the main loop.
	return Fle_Core::exec();
}