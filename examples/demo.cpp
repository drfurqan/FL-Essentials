/*********************************************************************************
created:	2017/03/01   12:06AM
filename: 	demo.cpp
file base:	demo
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	a demo application written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Core.h"
#include "Fle_MainWindow.h"
#include "Fle_OpenGLWindow.h"
#include "Fle_MenuBar.h"
#include "Fle_Widgets.h"
#include "Fle_Layout.h"
#include "Fle_Dialog.h"
#include "Fle_Spinner.h"
#include "Fle_ProgressBar.h"
#include "Fle_MessageBox.h"

#include <FL/Fl_Output.H>

#include <iostream>

using namespace R3D;

// a callback that will open a dialog which contains 5 inputs.
// By pressing OK button, all input can be used in calculations.
void new_callback(Fl_Widget* _w, void* _p)
{
	std::vector<const char*> _labels = { "Frame: ", "Fps: ", "Cam: ", "XYZ: ", "ABC: " };
	std::vector<double> _values = { 0, 1, 2.5, 3, 4.1 };
	std::vector<double> _minimums = { 0, 0, 2, 3, 4 };
	std::vector<double> _maximums = { 99, 100, 200, 300, 400 };
	std::vector<double> _steps = { 0.1, 1, 0.2, 3, 0.4 };
	if (Fle_Dialog::getNumbers(300, 300, "Dialog with Five Double/Integer Inputs", _labels, _values, _minimums, _maximums, _steps))
	{
		for (std::size_t i = 0; i < _labels.size(); i++)
			std::cout << _values[i] << std::endl;
	}
}

// close (top right) button callback for the main window.
void main_callback_close(Fl_Widget* _w, void* _p)
{
	switch (Fle_Dialog::ask(400, 150, "Warning", "Are you sure you want to close?"))
	{
	case 0: 
		std::cout << "No is pressed." << std::endl; 
		break;
	case 1: 
		std::cout << "Yes is pressed." << std::endl; 
		static_cast<Fl_Double_Window*>(_p)->hide();
		break;
	case 2: 
		std::cout << "Cancel is pressed." << std::endl; 
		break;
	}
}

// callback for menus.
void menu_cb(Fl_Widget* _w, void*)
{
	Fl_Menu_* mw = static_cast<Fl_Menu_*>(_w);
	const Fl_Menu_Item* m = mw->mvalue();
	if (!m) return;

	if (m->shortcut())
		std::cout << fl_shortcut_label(m->shortcut()) << std::endl;
	else
		std::cout << m->label() << std::endl;
}

int main()
{
	// library initialization with default modes.
	Fle_Core::init();

	// create a main window.
	Fle_MainWindow* w = new Fle_MainWindow(1400, 800, "Hello World");
	w->setMinimumSize(cv::Size(300, 300));
	w->setMaximumSize(cv::Size(10000, 10000));
	w->setMargins(2, 2, 2, 2);
	w->callback(main_callback_close, w);

	// show all toolbars.
	w->getMenuBar()->show();
	w->getTopToolBar()->show();
	w->getLeftToolBar()->show();
	w->getRightToolBar()->show();
	w->getStatusBar()->show();

	// load image from disk and display in the central widget.
	w->getCentralWidget()->getBox()->loadImage("D:\\aw.jpg");
	w->getCentralWidget()->getBox()->setImageDrawType(Fle_ImageDrawType::Fit);

	// add OpenGL window in the central widget.
	//w->begin();
	//Fle_OpenGLWindow* opengl = new Fle_OpenGLWindow(0, 0, w->getCentralWidget()->w(), w->getCentralWidget()->h(), "OpenGL Window");
	//w->end();

	// set the menubar fixed height.
	w->setMenuBarFixedHeight(25);
	{
		// add items to menubar.
		Fle_MenuBar* menu = w->getMenuBar();
		menu->add(" FILE /          New             ", "^n", new_callback);
		menu->add(" FILE /          Open             ", "^o", new_callback, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /          Save             ", "^s", new_callback);
		menu->add(" FILE /          Save As...             ", 0, new_callback, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /          Print...             ", "^p", new_callback, 0, FL_MENU_DIVIDER);
		menu->add(" FILE /          Exit             ", "^q", new_callback);;
		menu->add(" EDIT /          Copy             ", "^c", new_callback);
		menu->add(" EDIT /          Paste            ", "^v", new_callback);
		menu->add(" EDIT /          Delete            ", "^d", new_callback);
	}

	// set top toolbar margins and fixed height.
	w->getTopToolBar()->setMargins(5, 6, 0, 0);
	w->setTopToolBarFixedHeight(25);
	{
		// add a Left-Right horizontal layout in the top tool bar.
		Fle_HLayoutLR* tblayout = w->getTopToolBar()->addLayoutLR(23);
		tblayout->setMargins(0, 0, 2, 0);
		tblayout->setBackgroundColor(214, 219, 233);

		// begin to add/pack widgets at the most left side of the toolbar.
		tblayout->beginLeft();
		Fle_Widgets::createSpinner(80, 21, 80);
		Fle_Widgets::createValueOutput(80, 21, 80, 0.1);
		tblayout->endLeft();		// stop adding/packing widgets at the most left side of the toolbar.

		// begin to add/pack widgets at the most right side of the toolbar.
		tblayout->beginRight();
		Fl_Menu_Button* mb = Fle_Widgets::createDropDownMenu(100, 21, "Hello", 0, menu_cb, w);
		mb->add("  1", FL_ALT + 'r', 0, 0, FL_MENU_DIVIDER);
		mb->add("  2");
		mb->add("  3");
		mb->value(0);	// set as current item.

		Fl_Choice* cm = Fle_Widgets::createChoiceMenu(100, 21, 1, menu_cb, w);
		cm->add("  1231", FL_ALT + 'r', 0, 0, FL_MENU_DIVIDER);
		cm->add("  2");
		cm->add("  3");
		cm->value(0);	// set as current item.

		Fl_Input_Choice* inm = Fle_Widgets::createInputChoiceMenu(100, 21);
		inm->menubutton()->add("  1231", FL_ALT + 'r', 0, 0, FL_MENU_DIVIDER);
		inm->menubutton()->add("  2");
		inm->menubutton()->add("  3");
		inm->value(0);	// set as current item.
		tblayout->endRight();		// stop adding/packing widgets at the most right side of the toolbar.
	}

	// set fixed width and margins to left toolbar.
	w->getLeftToolBar()->setMargins(2, 2, 4, 4);
	w->setLeftToolBarFixedWidth(100);
	{
		// begin to add/pack widgets at top.
		w->getLeftToolBar()->beginTop();

		Fle_Group* gr = Fle_Widgets::createGroup(100, 121, "group: ");
		gr->color(fl_rgb_color(214, 219, 233));
		Fle_CheckGroup* cg = Fle_Widgets::createCheckGroup(100, 121, "Check: ");
		cg->color(fl_rgb_color(214, 219, 233));

		Fle_Button* b2 = new Fle_Button(0, 0, 100, 20, "1");
		Fle_Button* b3 = new Fle_Button(0, 0, 100, 20, "2");
		Fl_Choice* cm = Fle_Widgets::createChoiceMenu(100, 21);
		cm->add("  1", FL_ALT + 'r', 0, 0, FL_MENU_DIVIDER);
		cm->add("  2");
		cm->add("  3");
		cm->value(0);	// set as current item.

		w->getLeftToolBar()->endTop();		// stop adding/packing widgets at top.

		// begin to add/pack widgets at bottom.
		w->getLeftToolBar()->beginBottom();
		{Fle_Button* b2 = new Fle_Button(0, 0, 100, 20, "1");
		Fle_Button* b3 = new Fle_Button(0, 0, 100, 20, "2"); }
		w->getLeftToolBar()->endBottom();	// stop adding/packing widgets at bottom.
	}

	// set fixed width and margins to right toolbar.
	w->getRightToolBar()->setMargins(2, 2, 4, 4);
	w->setRightToolBarFixedWidth(100);
	{
		// begin to add/pack widgets at top.
		w->getRightToolBar()->beginTop();

		Fle_Button *btn = new Fle_Button(0, 0, 96, 30, "FLE Button");
		btn->color(Fle_Widgets::fromRGB(124, 124, 0));
		btn->selection_color(Fle_Widgets::fromRGB(124, 0, 124));
		btn->setResizeable(false);
		btn->callback((Fl_Callback*)new_callback);

		// stop adding/packing widgets at top.
		w->getRightToolBar()->endTop();

		// begin to add/pack widgets at bottom.
		w->getRightToolBar()->beginBottom();

		Fle_Button* icon_btn = new Fle_Button(0, 0, 100, 96, "");
		icon_btn->box(FL_BORDER_FRAME);
		icon_btn->labelcolor(fl_rgb_color(255, 0, 0));
		icon_btn->setResizeable(false);
		icon_btn->setOn(true);
		// icon_btn->loadIcons("D:\\play.png", "D:\\stop.png", cv::Size(64, 64));
		icon_btn->callback((Fl_Callback*)new_callback);

		// stop adding/packing widgets at bottom.
		w->getRightToolBar()->endBottom();
	}

	// set fixed width and margins to statusbar.
	w->getStatusBar()->setMargins(5, 15, 0, 0);
	w->setStatusBarFixedHeight(40);
	{
		// add a Left-Right horizontal layout in the statusbar.
		Fle_HLayoutLR* layout = w->getStatusBar()->addLayoutLR(35);
		layout->setMargins(0, 0, 2, 0);
		layout->setBackgroundColor(0, 122, 204);

		// begin to add/pack widgets at the most left side of the statusbar.
		layout->beginLeft();

		Fle_Box* p_textbox = new Fle_Box(0, 0, 300, 35);		// a text box at the most left corner.
		p_textbox->box(FL_FLAT_BOX);
		p_textbox->color(Fle_Widgets::fromRGB(0, 122, 204));
		p_textbox->getFont()->setSize(12);
		p_textbox->getFont()->setColor(Fle_Widgets::fromRGB(255, 255, 255));
		p_textbox->getFont()->setAlignment(FL_ALIGN_LEFT);
		p_textbox->setText("Ready");

		w->getStatusBar()->setTextBox(p_textbox);		// set the text box to show messages with time interval.

		Fle_InputSlider* b1 = new Fle_InputSlider(0, 0, 300, 35, "1");
		// Fle_Button* b2 = new Fle_Button(0, 0, 35, 35, "D:\\play.png", "D:\\stop.png", cv::Size(35, 35));
		Fle_Button* b3 = new Fle_Button(0, 0, 100, 20, "1");

		Fle_ProgressBar* prog = new Fle_ProgressBar(0, 0, 200, 35);
		prog->value(.45);

		// stop adding/packing widgets at the most left side of the statusbar.
		layout->endLeft();

		// begin to add/pack widgets at the most right side of the statusbar.
		layout->beginRight();

		Fle_Box* b = new Fle_Box(0, 0, 150, 35);
		b->loadImage("D:\\people.jpg");

		Fl_Output*p_box_fps = new Fl_Output(0, 0, 30, 35);
		p_box_fps->box(FL_FLAT_BOX);
		p_box_fps->color(fl_rgb_color(0, 122, 204));
		p_box_fps->textcolor(fl_rgb_color(255, 255, 255));
		p_box_fps->textsize(12);
		p_box_fps->value("24");
		Fl_Output*	p_box_nframes = new Fl_Output(0, 0, 30, 35);
		p_box_nframes->box(FL_FLAT_BOX);
		p_box_nframes->color(fl_rgb_color(0, 122, 204));
		p_box_nframes->textcolor(fl_rgb_color(255, 255, 255));
		p_box_nframes->textsize(12);
		p_box_nframes->value("138");

		Fle_Widgets::createClock(35, 35);

		// stop adding/packing widgets at the most right side of the statusbar.
		layout->endRight();
	}

	w->showMaximized();				// show the main window.
	w->updateGeometry();	// update geometry.
	w->getStatusBar()->showMessage("Initialized...", 5);	// show message at the statusbar for 5 seconds.

	return Fle_Core::exec();		// execute the main loop.
}