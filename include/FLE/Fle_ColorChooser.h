#pragma once
#ifndef Fle_ColorChooser_h__
#define Fle_ColorChooser_h__

/*********************************************************************************
created:	2017/11/10   04:02AM
filename: 	Fle_ColorChooser.h
file base:	Fle_ColorChooser
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized color chooser widget.

usage example:
			// save the current color in case of user press the cancel button.
			double b1[3];
			double b2[3];
			window->GetBackground(b1);
			window->GetBackground2(b2);

			Fle_ColorChooser* c = new Fle_ColorChooser(600, 240, "Select background color");
			c->setDefaultColors(0.809 * 255, 0.762 * 255, 0.856 * 255, 0.66 * 255, 0.689 * 255, 0.851 * 255);
			c->getChooser1()->callback(bg_color1_cb, mw);
			c->getChooser2()->callback(bg_color2_cb, mw);
			if (c->exec() == 0)
			{
				window->SetBackground(b1[0], b1[1], b1[2]);
				window->SetBackground2(b2[0], b2[1], b2[2]);
				MainWindow->Redraw();
			}

			// callback for the color chooser.
			void MainWindow::bg_color1_cb(Fl_Widget* _w, void* _p)
			{
				MainWindow* mw = static_cast<MainWindow*>(_p);
				if (!mw) return;

				Fl_Color_Chooser* c = static_cast<Fl_Color_Chooser*>(_w);
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

#include <FL/Fl_Color_Chooser.H>

#include <string>
#include <vector>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_ColorChooser
{
public:
	// Description:
	// Constructor to create a color choose widget.
	Fle_ColorChooser(int _w, int _h, const char* _title = "Color Chooser");
	// Description:
	// Destructor to release data.
	virtual ~Fle_ColorChooser();

	// Description:
	// Function to set the default color of the color chooser.
	void setDefaultColors(unsigned char _r1, unsigned char _g1, unsigned char _b1,
		unsigned char _r2, unsigned char _g2, unsigned char _b2);
	
	// Description:
	// Function to execute the color chooser.
	// It returns 0 on Cancel button press and 1 on Ok button.
	// Note: exec will delete the widget so always create 
	// a new object in order to use it many times.
	int exec();

	// Description:
	// Function to return a pointer to first chooser.
	Fl_Color_Chooser* getChooser1() const { return p_cc1; }
	// Description:
	// Function to return a pointer to second chooser.
	Fl_Color_Chooser* getChooser2() const { return p_cc2; }
	// Description:
	// Function to return a dialog.
	Fle_Dialog* getDialog() const { return p_dialog; }

protected:
	Fle_HLayout* p_layout;
	Fle_Button* p_ok;
	Fle_Button* p_reset;
	Fle_Button* p_cancel;
	unsigned char m_default_color1[3];
	unsigned char m_default_color2[3];

private:
	Fl_Color_Chooser* p_cc1;
	Fl_Color_Chooser* p_cc2;
	Fle_Dialog* p_dialog;
	static void close_cb(Fl_Widget* _w, void* _p);
	static void default_colors_cb(Fl_Widget* _w, void* _p);
};

}

#endif // Fle_ColorChooser_h__