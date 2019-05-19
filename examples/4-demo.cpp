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

#include <FLE/Fle_Core.h>
#include <FLE/Fle_MainWindow.h>
#include <FLE/Fle_OpenGLWindow.h>
#include <FLE/Fle_MenuBar.h>
#include <FLE/Fle_Widgets.h>
#include <FLE/Fle_Layout.h>
#include <FLE/Fle_Dialog.h>
#include <FLE/Fle_Spinner.h>
#include <FLE/Fle_ProgressBar.h>
#include <FLE/Fle_MessageBox.h>

#include <FL/Fl_Output.H>

#include <iostream>

using namespace R3D;

// a callback that will open a dialog which contains 5 inputs.
// By pressing OK button, all input can be used in calculations.
// a callback that will open a dialog which contains 5 inputs.
// By pressing OK button, all input can be used in calculations.
void menu_callback(Fl_Widget* _w, void* _p)
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

	std::cout << m->label() << std::endl;
}

int main()
{
	// library initialization with default modes.
	Fle_Core::init(Fle_Core::DARK_COLOR_THEME);

	// create a main window.
	Fle_MainWindow* w = new Fle_MainWindow(0, 0, 1400, 800, "Hello World");
	w->setMinimumSize(Fle_Size(300, 300));
	w->setMaximumSize(Fle_Size(10000, 10000));
	w->setMargins(2, 2, 2, 2);
	w->callback(main_callback_close, w);

	//Fle_ImageScrollBox* imgBox = new Fle_ImageScrollBox(0, 0, win.w(), win.h());			// no zooming using mouse wheel, mouse wheel will be used for vertical and horizontal scrolling.
	Fle_ImageBox* imgBox = new Fle_ImageBox(0, 0, w->w(), w->h());	// zooming using mouse wheel, vertical and horizontal scrolling is disabled.
	imgBox->color(w->color());
	imgBox->setImageDrawType(Fle_ImageDrawType::Fit);
	imgBox->loadImage("C:\\image.png", true); // load image from the disk and reset the ROI.

	// set as a central widget.
	w->setCentralWidget(imgBox);

	// add items to the menubar.
	{
		Fle_MenuBar* menu = w->getMenuBar();
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

	// show all toolbars.
	w->getMenuBar()->show();
	w->getTopBar()->show();
	w->getLeftBar()->show();
	w->getRightBar()->show();
	w->getStatusBar()->show();

	// set top toolbar margins and fixed height.
	w->getTopBar()->setMargins(5, 6, 0, 0);
	w->getTopBar()->setFixedHeight(25);
	{
		// add a Left-Right horizontal layout in the top tool bar.
		Fle_HLayoutLR* tblayout = w->getTopBar()->addLayoutLR(23);
		tblayout->box(FL_BORDER_BOX);
		tblayout->setMargins(0, 0, 2, 0);

		// begin to add/pack widgets at the most left side of the toolbar.
		tblayout->beginLeft();
		Fle_Spinner* spinner = Fle_Widgets::createSpinner(80, 21, 80);
		spinner->color(tblayout->color());
		Fl_Value_Output* vout = Fle_Widgets::createValueOutput(80, 21, 80, 0.1);
		vout->color(tblayout->color());
		tblayout->end();		// stop adding/packing widgets at the most left side of the toolbar.

		// begin to add/pack widgets at the most right side of the toolbar.
		tblayout->beginRight();
		Fl_Menu_Button* mb = Fle_Widgets::createDropDownMenu(100, 21, "Hello", 0, menu_cb, w);
		mb->color(Fl::get_color(FL_LIGHT1));
		mb->add("  1", FL_ALT + 'r', 0, 0, FL_MENU_DIVIDER);
		mb->add("  2");
		mb->add("  3");
		mb->value(0);	// set as current item.

		Fl_Choice* cm = Fle_Widgets::createChoiceMenu(100, 21, 1, menu_cb, w);
		cm->color(Fl::get_color(FL_LIGHT1));
		cm->textcolor(Fl::get_color(FL_FOREGROUND_COLOR));
		cm->add("  1231", FL_ALT + 'r', 0, 0, FL_MENU_DIVIDER);
		cm->add("  2");
		cm->add("  3");
		cm->value(0);	// set as current item.

		Fl_Input_Choice* inm = Fle_Widgets::createInputChoiceMenu(100, 21);
		inm->color(tblayout->color());
		inm->menubutton()->color(Fl::get_color(FL_LIGHT1));
		inm->menubutton()->textcolor(Fl::get_color(FL_FOREGROUND_COLOR));
		inm->selection_color(tblayout->color());
		inm->textcolor(FL_BLACK);
		inm->menubutton()->add("  1231", FL_ALT + 'r', 0, 0, FL_MENU_DIVIDER);
		inm->menubutton()->add("  2");
		inm->menubutton()->add("  3");
		inm->value(0);	// set as current item.
		tblayout->end();		// stop adding/packing widgets at the most right side of the toolbar.
	}

	// set fixed width and margins to left toolbar.
	w->getLeftBar()->setMargins(2, 2, 4, 4);
	w->getLeftBar()->setFixedWidth(100);
	{
		// begin to add/pack widgets at top.
		w->getLeftBar()->beginTop();

		Fle_Group* gr = Fle_Widgets::createGroup(100, 121, "group: ");
		gr->color(w->getLeftBar()->color());
		Fle_CheckGroup* cg = Fle_Widgets::createCheckGroup(100, 121, "Check: ");
		cg->color(w->getLeftBar()->color());
		cg->selection_color(Fl::get_color(FL_LIGHT1));

		Fle_Button* b2 = new Fle_Button(0, 0, 100, 20, "1");
		Fle_Button* b3 = new Fle_Button(0, 0, 100, 20, "2");
		Fl_Choice* cm = Fle_Widgets::createChoiceMenu(100, 21);
		cm->color(Fl::get_color(FL_LIGHT1));
		cm->textcolor(Fl::get_color(FL_FOREGROUND_COLOR));
		cm->add("  1", FL_ALT + 'r', 0, 0, FL_MENU_DIVIDER);
		cm->add("  2");
		cm->add("  3");
		cm->value(0);	// set as current item.

		w->getLeftBar()->end();		// stop adding/packing widgets at top.

		// begin to add/pack widgets at bottom.
		w->getLeftBar()->beginBottom();
		{Fle_Button* b2 = new Fle_Button(0, 0, 100, 20, "1");
		Fle_Button* b3 = new Fle_Button(0, 0, 100, 20, "2"); }
		w->getLeftBar()->end();	// stop adding/packing widgets at bottom.
	}

	// set fixed width and margins to right toolbar.
	w->getRightBar()->setMargins(2, 2, 4, 4);
	w->getRightBar()->setFixedWidth(100);
	{
		// begin to add/pack widgets at top.
		w->getRightBar()->beginTop();

		Fle_Button *btn = new Fle_Button(0, 0, 96, 30, "FLE Button");
		btn->color(w->getRightBar()->color());
		btn->selection_color(Fle_Widgets::fromRGB(240, 240, 240));
		btn->callback((Fl_Callback*)menu_callback);

		// stop adding/packing widgets at top.
		w->getRightBar()->end();
	}

	// set fixed width and margins to statusbar.
	w->getStatusBar()->setMargins(5, 15, 0, 0);
	w->getStatusBar()->setFixedHeight(40);
	{
		// add a Left-Right horizontal layout in the statusbar.
		Fle_HLayoutLR* layout = w->getStatusBar()->addLayoutLR(35);
		layout->setMargins(0, 0, 2, 0);

		// begin to add/pack widgets at the most left side of the statusbar.
		layout->beginLeft();

		Fle_Box* p_textbox = new Fle_Box(0, 0, 300, 35);		// a text box at the most left corner.
		p_textbox->box(FL_FLAT_BOX);
		p_textbox->color(layout->color());
		p_textbox->getFont()->setSize(12);
		p_textbox->getFont()->setColor(Fle_Widgets::fromRGB(255, 255, 255));
		p_textbox->getFont()->setAlignment(FL_ALIGN_LEFT);
		p_textbox->setText("Ready");
		w->getStatusBar()->setTextBox(p_textbox);		// set the text box to show messages with time interval.

		Fle_InputSlider* b1 = new Fle_InputSlider(0, 0, 300, 35, "1");
		b1->box(FL_GLEAM_UP_BOX);
		b1->color(layout->color());

		// Fle_Button* b2 = new Fle_Button(0, 0, 35, 35, "D:\\play.png", "D:\\stop.png", cv::Size(35, 35));
		Fle_Button* b3 = new Fle_Button(0, 0, 100, 20, "1");
		b3->color(layout->color());

		Fle_ProgressBar* prog = new Fle_ProgressBar(0, 0, 200, 35);
		prog->color(layout->color());
		prog->value(.45);

		// stop adding/packing widgets at the most left side of the statusbar.
		layout->end();

		// begin to add/pack widgets at the most right side of the statusbar.
		layout->beginRight();

		Fle_Box* b = new Fle_Box(0, 0, 150, 35);
		b->loadImage("D:\\people.jpg");

		Fl_Output* valueOut1 = new Fl_Output(0, 0, 30, 35);
		valueOut1->box(FL_FLAT_BOX);
		valueOut1->color(layout->color());
		valueOut1->textcolor(fl_rgb_color(255, 255, 255));
		valueOut1->textsize(12);
		valueOut1->value("24");

		Fl_Output*	valueOut2 = new Fl_Output(0, 0, 30, 35);
		valueOut2->box(FL_FLAT_BOX);
		valueOut2->color(layout->color());
		valueOut2->textcolor(fl_rgb_color(255, 255, 255));
		valueOut2->textsize(12);
		valueOut2->value("138");

		Fle_Widgets::createClock(35, 35);

		// stop adding/packing widgets at the most right side of the statusbar.
		layout->end();
	}

	w->showMaximized();				// show the main window.
	w->getStatusBar()->showMessage("Initialized...", 15);	// show message at the statusbar for 15 seconds.

	return Fle_Core::exec();		// execute the main loop.
}
