/*********************************************************************************
created:	2017/01/30   09:42AM
filename: 	Fle_StatusBar.h
file base:	Fle_StatusBar
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	StatusBar class to create a horizontal kind of bar which contains various
widgets to be added in the status bar. Widgets will be added from the most
left side by default.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_StatusBar.h"
#include "Fle_Timer.h"

using namespace R3D;

Fle_StatusBar::Fle_StatusBar(int _x, int _y, int _w, int _h, const char* _label) :
Fle_VHLayout(_x, _y, _w, _h, _label),
p_textbox(nullptr)
{
	setBackgroundColor(0, 122, 204);
	getLayout()->setBackgroundColor(0, 122, 204);
	Fle_VHLayout::end();
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

	std::function<void()> f = [&]()
	{
		p_textbox->setText("Ready");
		p_textbox->redraw();
		Fle_VHLayout::redraw();
	};
	Fle_Timer::singleShot(_time_in_sec, f);
}