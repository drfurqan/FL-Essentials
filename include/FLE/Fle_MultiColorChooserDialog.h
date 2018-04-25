#pragma once
#ifndef Fle_MultiColorChooserDialog_h__
#define Fle_MultiColorChooserDialog_h__

/*********************************************************************************
created:	2017/11/22   04:02AM
filename: 	Fle_MultiColorChooserDialog.h
file base:	Fle_MultiColorChooserDialog
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized multi color dialog that creates two color choosers
inside of a dialog box with OK, Cancel, and Default buttons.

usage example:

// save the current color in case of user presses the cancel button.
double b1[3];
double b2[3];
window->GetBackground(b1);
window->GetBackground2(b2);

Fle_ColorChooser* c = new Fle_ColorChooser(600, 240, "Select background color");
c->getChooser1()->callback(bg_color1_cb, mw);
c->getChooser2()->callback(bg_color2_cb, mw);
if (c->exec() == 0) // 0 for canceled
{
	window->SetBackground(b1[0], b1[1], b1[2]);
	window->SetBackground2(b2[0], b2[1], b2[2]);
	MainWindow->Redraw();
}

// callback for the color chooser.
void MainWindow::bg_color1_cb(Fl_Widget* _w, void* _p)
{
	auto mw = static_cast<MainWindow*>(_p);
	if (!mw) return;

	auto c = static_cast<Fl_Color_Chooser*>(_w);
	if (!c) return;

	mw->window->SetBackground(c->r(), c->g(), c->b());
	mw->window->Redraw();
}

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>
#include <FLE/Fle_Dialog.h>
#include <FLE/Fle_Layout.h>
#include <FLE/Fle_ColorChooser.h>

#include <string>
#include <vector>

namespace R3D
{

// Description:
// Class that creates two color choosers inside of a dialog box
// with OK, Cancel, and Default buttons.

class FL_ESSENTIALS_EXPORT Fle_MultiColorChooserDialog
{
public:
	// Description:
	// Constructor to create a color choose widget.
	Fle_MultiColorChooserDialog(int _w = 600, int _h = 240, 
		double _r1 = 0.0, double _g1 = 0.0, double _b1 = 0.0, 
		double _r2 = 0.29, double _g2 = 0.33, double _b2 = 0.35, 
		const char* _title = "Choose Colors");
	// Description:
	// Destructor to release data.
	virtual ~Fle_MultiColorChooserDialog();

	// Description:
	// Function to set the default color of the color chooser.
	void setDefaultColors(double _r1, double _g1, double _b1, double _r2, double _g2, double _b2);
	
	// Description:
	// Function to execute the color chooser.
	// It returns 0 on Cancel button press and 1 on Ok button.
	// Note: exec will delete the widget so always create 
	// a new object in order to use it many times.
	int exec();

	// Description:
	// Function to return a pointer to first chooser.
	Fle_ColorChooser* getChooser1() const { return p_cc1; }
	// Description:
	// Function to return a pointer to second chooser.
	Fle_ColorChooser* getChooser2() const { return p_cc2; }
	// Description:
	// Function to return a dialog.
	Fle_Dialog* getDialog() const { return p_dialog; }

protected:
	Fle_HLayout* p_layout;
	Fle_Button* p_ok;
	Fle_Button* p_reset;
	Fle_Button* p_cancel;
	double m_default_color1[3];
	double m_default_color2[3];

private:
	Fle_ColorChooser* p_cc1;
	Fle_ColorChooser* p_cc2;
	Fle_Dialog* p_dialog;
	static void close_cb(Fl_Widget* _w, void* _p);
	static void default_colors_cb(Fl_Widget* _w, void* _p);
};

}

#endif // Fle_MultiColorChooserDialog_h__