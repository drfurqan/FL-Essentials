#pragma once
#ifndef Fle_StatusBar_h__
#define Fle_StatusBar_h__

/*********************************************************************************
created:	2017/01/30   09:42AM
filename: 	Fle_StatusBar.h
file base:	Fle_StatusBar
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	StatusBar class to create a horizontal kind of bar which contains a
layout to add various kind of layout and widgets.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Layout.h>
#include <FLE/Fle_Timer.h>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_StatusBar : public Fle_VHLayout
{
public:
	// Description:
	// Constructor to create a status bar with position, size, and title.
	// Default values:
	// Qt colors
	// RGB(240, 240, 240);
	// MS VS2013 colors
	// RGB(0, 122, 204);
	Fle_StatusBar(int _x, int _y, int _w, int _h, const char* _label = 0);
	// Description:
	// Destructor that destroys the data.
	virtual ~Fle_StatusBar();

	// Description:
	// Function to show the specified text in the TextBox (specified by setTextBox()).
	// _time_in_sec is the time in seconds, that means, how long the text should be displayed,
	// after the time is over, default text given in setDefaultText("Ready") will be displayed.
	// This does the same work as setText(), it just provides you to specify the time in seconds. 
	void showMessage(const std::string& _text, int _time_in_sec);

	// Description:
	// Function to set a pointer to text box (for message display) in the statusbar.
	// TextBox can be added to statusbar like this:

	//Fle_HLayoutLR* layout = w->getStatusBar()->addLayoutLR(21, Fle_VHLayout::Position::AT_TOP);
	//{
	//	layout->beginLeft();
	//	Fle_Box* p_textbox = new Fle_Box(0, 0, 300, 25);		// a text box at the most left corner.
	//	p_textbox->box(FL_FLAT_BOX);
	//	p_textbox->color(Fle_Core::fromRGB(0, 122, 204));
	//	p_textbox->getFont()->setSize(12);
	//	p_textbox->getFont()->setColor(Fle_Core::fromRGB(255, 255, 255));
	//	p_textbox->getFont()->setAlignment(FL_ALIGN_LEFT);
	//	p_textbox->setText("Ready");
	//	layout->endLeft();
	//	w->getStatusBar()->setTextBox(p_textbox);
	//}
	//w->getStatusBar()->setMargins(2, 2, 2, 2);
	//w->setStatusBarFixedHeight(25);

	// Very important note: always use FL_FLAT_BOX and set background color as required. 
	// Never use FL_NO_BOX, it creates issues while updating the widget.
	void setTextBox(Fle_Box* _p) { p_textbox = _p; }
	// Description:
	// Function to get a pointer to text box.
	Fle_Box* getTextBox() const { return p_textbox; }

	// Description:
	// Function to set the default text that should be displayed after the time is over.
	// Default value is "Ready".
	void setDefaultText(const std::string& _text) { m_default_text = _text; }
	// Description:
	// Function to get the default text.
	// Default value is "Ready".
	std::string getDefaultText() const { return m_default_text; }

protected:
	Fle_Box* p_textbox;
	std::string m_default_text;
	Fle_Timer m_timer;
};

}

#endif // Fle_StatusBar_h__