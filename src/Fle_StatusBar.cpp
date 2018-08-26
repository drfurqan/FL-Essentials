/*********************************************************************************
created:	2017/01/30   09:42AM
filename: 	Fle_StatusBar.h
file base:	Fle_StatusBar
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	StatusBar class to create a horizontal kind of bar. 
By default, widgets will be inserted/added from the most left side of the bar.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_StatusBar.h>

using namespace R3D;

Fle_StatusBar::Fle_StatusBar(int _x, int _y, int _w, int _h, const char* _label) :
Fle_VHLayout(_x, _y, _w, _h, _label),
p_textbox(nullptr),
m_default_text("Ready")
{
	Fle_Window::setBackgroundColor(0, 122, 204);
	getCentralLayout()->setBackgroundColor(0, 122, 204);
	Fle_VHLayout::end();

	// function that will be called after the specified time interval is passed.
	std::function<void()> f = [&]()
	{
		if (p_textbox)
		{
			p_textbox->setText(m_default_text);
			p_textbox->redraw();
			redraw();
		}
	};
	m_timer.setFunction(f);
	m_timer.setSingleShot(true);
	m_timer.pause(false);
}

Fle_StatusBar::~Fle_StatusBar()
{
}

void Fle_StatusBar::showMessage(const std::string& _text, int _time_in_sec)
{
	if (p_textbox == nullptr) return;

	p_textbox->setText(_text);
	p_textbox->redraw();
	Fle_VHLayout::redraw();

	m_timer.setTime(_time_in_sec);
	m_timer.stop();
	m_timer.start();
	Fl::wait(0.001);		// just wait a little to show the statusbar message.
}