#pragma once
#ifndef Fle_Input_h__
#define Fle_Input_h__

/*********************************************************************************
created:	2017/02/15   02:20AM
filename: 	Fle_Input.h
file base:	Fle_Input
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Modified class for an input widget that can support various 
			justifications, and copy/paste support.
/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>
#include <FLE/Fle_Box.h>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_InputWidget : public Fl_Input
{
public:
	// Description:
	// Default ctor to create an input widget with copy and paste support.
	Fle_InputWidget(int _x, int _y, int _w, int _h, const char* _lable = 0);

	// Description:
	// Function to set a color to the right click popup window.
	void setRightClickPopupColor(Fl_Color _color) { m_rclick_pop_clr = _color; }
	// Description:
	// Function to get a color of the right click popup window.
	Fl_Color getRightClickPopupColor(Fl_Color _color) const { return m_rclick_pop_clr; }
	// Description:
	// Function to set a color to the right click popup window.
	void setRightClickPopupTextColor(Fl_Color _color) { m_rclick_pop_tclr = _color; }
	// Description:
	// Function to get a color of the right click popup window.
	Fl_Color getRightClickPopupTextColor(Fl_Color _color) const { return m_rclick_pop_tclr; }

protected:
	int handle(int _event) override;

private:
	static void copy_cb(Fl_Widget*, void*);
	static void paste_cb(Fl_Widget*, void*);

	Fl_Color m_rclick_pop_clr;
	Fl_Color m_rclick_pop_tclr;
};

class FL_ESSENTIALS_EXPORT Fle_Input : public Fl_Group
{
public:
	// Description:
	// Default ctor to creare an input widget with various justification support, and copy and paste as well.
	Fle_Input(int _x, int _y, int _w, int _h, const char* _lable = 0, Fl_Align _label_align = FL_ALIGN_LEFT);
	// Description:
	// Function to set text justification. 
	// Expects one of: FL_ALIGN_LEFT, FL_ALIGN_CENTER, FL_ALIGN_RIGHT.
	void justify(Fl_Align _val);
	// Description:
	// Function to get text justification.
	Fl_Align justify() const;
	// Description:
	// Function to set the input text value.
	void value(const char* _val);
	// Description:
	// Function to get the text value.
	const char *value() const;
	// Description:
	// Function to set box type.
	void box(Fl_Boxtype _b);
	// Description:
	// Function to get box type.
	Fl_Boxtype box() const;
	// Description:
	// Function to set color.
	void color(Fl_Color _c);
	// Description:
	// Function to get color.
	Fl_Color color() const;
	// Description:
	// Function to set text color.
	void textcolor(Fl_Color _c);
	// Description:
	// Function to get text color.
	Fl_Color textcolor() const;
	// Description:
	// Function to set text size.
	void textsize(int _size);
	// Description:
	// Function to get text size.
	int textsize() const;
	// Description:
	// Function to set text font.
	void textfont(Fl_Font _size);
	// Description:
	// Function to get text font.
	Fl_Font textfont() const;

	// Description:
	// Function to get a pointer to label box.
	Fl_Box* getLabelBox() const { return p_label; }

	// Description:
	// Function to get a pointer to internal input widget.
	Fle_InputWidget* getInputWidget() const { return p_input; }

protected:
	int handle(int _event) override;

private:
	Fle_InputWidget* p_input;
	Fl_Box* p_label;
};

}

#endif // Fle_Input_h__