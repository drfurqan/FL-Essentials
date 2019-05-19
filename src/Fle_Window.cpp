/*********************************************************************************
created:	2017/01/27   02:05AM
filename: 	Fle_Window.h
file base:	Fle_Window
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A generalized window class with thread-safe image handling, and with
basic necessary functions.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Window.h>
#include <FLE/Fle_WindowsUtil.h>	// needed for maximized

#include <FL/Fl.H>
#include <FL/x.H>					// needed for fl_display

using namespace R3D;

Fle_Window::Fle_Window(int _x, int _y, int _w, int _h, const char* _title, int _icon_index) :
	Fl_Window(_x, _y, _w, _h, _title)
{
#ifdef WIN32
	icon(LoadIcon(fl_display, MAKEINTRESOURCE(_icon_index)));
#endif // WIN32

	Fl_Window::end(); // This call is necessary to prevent any additional UI widgets from becoming subcomponents of this window.
	
	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	color(fl_rgb_color(238, 243, 250));
	box(FL_FLAT_BOX);
	resizable(this);
	user_data(static_cast<void*>(this));
}
Fle_Window::~Fle_Window()
{
}

void Fle_Window::size(int _w, int _h)
{
	Fl_Window::resize(x(), y(), _w, _h);
}

void Fle_Window::setBackgroundColor(uchar _red, uchar _green, uchar _blue)
{
	Fl_Window::color(fl_rgb_color(_red, _green, _blue));
}
void Fle_Window::setBackgroundColor(Fl_Color _color)
{
	Fl_Window::color(_color);
}
Fl_Color Fle_Window::getBackgroundColor() const
{
	return Fl_Window::color();
}
void Fle_Window::color(uchar _red, uchar _green, uchar _blue)
{
	setBackgroundColor(_red, _green, _blue);
}
void Fle_Window::color(Fl_Color _color)
{
	setBackgroundColor(_color);
}
Fl_Color Fle_Window::color() const
{
	return getBackgroundColor();
}

void Fle_Window::setTransparency(float _alpha) const
{
#if defined(_WIN32)

	HWND hwnd = fl_xid(this);
	LONG_PTR exstyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
	if (!(exstyle & WS_EX_LAYERED))
		SetWindowLongPtr(hwnd, GWL_EXSTYLE, exstyle | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, 0, (BYTE)(0xFF * _alpha), LWA_ALPHA);

#elif defined(__linux__) || defined(__unix__)

	Atom atom = XInternAtom(fl_display, "_NET_WM_WINDOW_OPACITY", False);
	uint32_t opacity = (uint32_t)(UINT32_MAX * _alpha);
	XChangeProperty(fl_display, fl_xid(this), atom, XA_CARDINAL, 32, PropModeReplace, (unsigned char *)&opacity, 1);

#else
	// Transparency only supported on Microsoft Windows and Linux with X11.
#endif
}
