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
Copyright (C) 2017 REAL3D

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
Fl_Double_Window(_x, _y, _w, _h, _title),
m_minsize(Fle_Size(10, 10)),
m_maxsize(Fle_Size(Fl::w() + 100000, Fl::h() + 100000))
{
	//Fl_Pixmap ico(flviewer);
	//Fl_RGB_Image app(&ico);
	//icon(&app);
	//default_icon(&app);

#ifdef WIN32
	icon(LoadIcon(fl_display, MAKEINTRESOURCE(_icon_index)));
#endif // WIN32

	p_box = new Fle_Box(0, 0, _w, _h, _title);
	p_box->box(FL_FLAT_BOX);
	p_box->color(fl_rgb_color(238, 243, 250));

	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	color(fl_rgb_color(238, 243, 250));
	box(FL_FLAT_BOX);
	resizable(this);
	size_range(10, 10);
	user_data(static_cast<void*>(this));
	callback(closeCallback, static_cast<void*>(this));
	Fl_Double_Window::end(); // This call is necessary to prevent any additional UI widgets from becoming subcomponents of this window.

	// setting up timer event.
	std::function<void()> tf = [&]()
	{
		timerEvent();
	};
	m_timer.setFunction(tf);

	// setting up idle event.
	std::function<void()> idf = [&]()
	{
		idleEvent();
	};
	m_idle.setFunction(idf);
}

Fle_Window::Fle_Window(int _w, int _h, const char* _title, int _icon_index) :
Fl_Double_Window(0, 0, _w, _h, _title),
m_minsize(Fle_Size(10, 10)),
m_maxsize(Fle_Size(Fl::w() + 100000, Fl::h() + 100000))
{
#ifdef WIN32
	icon(LoadIcon(fl_display, MAKEINTRESOURCE(_icon_index)));
#endif // WIN32

	p_box = new Fle_Box(0, 0, _w, _h, _title);
	p_box->box(FL_FLAT_BOX);
	p_box->color(fl_rgb_color(238, 243, 250));

	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	color(fl_rgb_color(238, 243, 250));
	box(FL_FLAT_BOX);
	resizable(this);
	size_range(10, 10);
	user_data(static_cast<void*>(this));
	callback(closeCallback, static_cast<void*>(this));

	// positioned at center of the screen.
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);

	Fl_Double_Window::end(); // this call is necessary to prevent any additional UI widgets from becoming subcomponents of this window.

	// setting up timer event.
	std::function<void()> tf = [&]()
	{
		timerEvent();
	};
	m_timer.setFunction(tf);

	// setting up idle event.
	std::function<void()> idf = [&]()
	{
		idleEvent();
	};
	m_idle.setFunction(idf);
}

Fle_Window::~Fle_Window()
{
}

void Fle_Window::begin()
{
	Fl_Double_Window::begin();
}
void Fle_Window::end()
{
	Fl_Double_Window::end();
}

void Fle_Window::timerEvent()
{
}
void Fle_Window::idleEvent()
{
}

void Fle_Window::redraw()
{
	if(p_box) p_box->redraw();
	Fl_Double_Window::redraw();
}
void Fle_Window::update()
{
	redraw();
}

void Fle_Window::paintEvent()
{
}
void Fle_Window::draw()
{
	if (!visible()) return;

	Fl_Double_Window::draw();
	paintEvent();
}

void Fle_Window::showMinimized()
{
	show();
	Fle_WindowsUtil::setWindowOption(label(), Fle_WindowsUtil::Options::ShowMinimized);
	size(w(), h());
}
void Fle_Window::showMaximized()
{
	showMinimized();		// this does the trick for a little animation started from bottom.
	Fle_WindowsUtil::setWindowOption(label(), Fle_WindowsUtil::Options::ShowMaximized);
	size(w(), h());
}
void Fle_Window::showFullScreen()
{
	show();
	fullscreen();
	size(w(), h());
}
void Fle_Window::showNormal()
{
	show();
	fullscreen_off();
	size(w(), h());
}

void Fle_Window::resize(int _x, int _y, int _w, int _h)
{
	Fl_Double_Window::resize(_x, _y, _w, _h);
	if(p_box) p_box->position((_w - p_box->w()) / 2, (_h - p_box->h()) / 2);	// position the image box at center.
}
void Fle_Window::size(int _w, int _h)
{
	resize(Fl_Double_Window::x(), Fl_Double_Window::y(), _w, _h);
}
void Fle_Window::setMinimumSize(const Fle_Size& _size)
{
	m_minsize = _size;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}
void Fle_Window::setMaximumSize(const Fle_Size& _size)
{
	m_maxsize = _size;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}
void Fle_Window::setResizeable(bool _b)
{
	if (_b)
	{
		resizable(this);
		size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
	}
	else
	{
		resizable(nullptr);
		size_range(w(), h(), w(), h());
	}
}
void Fle_Window::setFixedWidth(int _w)
{
	m_minsize.width = _w;
	m_maxsize.width = _w;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}
void Fle_Window::setFixedHeight(int _h)
{
	m_minsize.height = _h;
	m_maxsize.height = _h;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}
/************************************************************************/
/* Mouse interaction with Window                                        */
/************************************************************************/
void Fle_Window::mouseLeftButtonPressEvent(int _x, int _y)
{
	//std::cout << "Abstract_Window: left mouse button is pressed, and the coordinates are (" << _x << ", " << _y << ").\n";
}
void Fle_Window::mouseRightButtonPressEvent(int _x, int _y)
{
	//std::cout << "right mouse button is pressed, and the coordinates are (" << _x << ", " << _y << ").\n";
}
void Fle_Window::mouseMiddleButtonPressEvent(int _x, int _y)
{
	//std::cout << "middle mouse button is pressed, and the coordinates are (" << _x << ", " << _y << ").\n";
}
void Fle_Window::mouseLeftButtonReleaseEvent()
{
	//std::cout << "left mouse button is released.\n";
}
void Fle_Window::mouseRightButtonReleaseEvent()
{
	//std::cout << "right mouse button is released.\n";
}
void Fle_Window::mouseMiddleButtonReleaseEvent()
{
	//std::cout << "middle mouse button is released.\n";
}
void Fle_Window::mouseWheelForwardEvent()
{
	//std::cout << "mouse wheel is moving forward.\n";
}
void Fle_Window::mouseWheelBackwardEvent()
{
	//std::cout << "mouse wheel is moving backward.\n";
}

void Fle_Window::mouseLeftButtonDragEvent(int _x, int _y)
{
}
void Fle_Window::mouseRightButtonDragEvent(int _x, int _y)
{
}
void Fle_Window::mouseMiddleButtonDragEvent(int _x, int _y)
{
}

void Fle_Window::mouseMoveEvent(int _x, int _y)
{
}
int Fle_Window::keyPressEvent(int _key)
{
	return 0;
}

int Fle_Window::processEvents(int _event)
{
	static int x, y;

	switch (_event)
	{
	case FL_PUSH:
		x = Fl::event_x();
		y = Fl::event_y();
		take_focus();						// this allows key events to work.

		switch (Fl::event_button())
		{
		case FL_LEFT_MOUSE:
			mouseLeftButtonPressEvent(x, y);
			break;

		case FL_RIGHT_MOUSE:
			mouseRightButtonPressEvent(x, y);
			break;

		case FL_MIDDLE_MOUSE:
			mouseMiddleButtonPressEvent(x, y);
			break;

		default:
			break;
		}
		break;

	case FL_RELEASE:
		switch (Fl::event_button())
		{
		case FL_LEFT_MOUSE:
			mouseLeftButtonReleaseEvent();
			break;

		case FL_RIGHT_MOUSE:
			mouseRightButtonReleaseEvent();
			break;

		case FL_MIDDLE_MOUSE:
			mouseMiddleButtonReleaseEvent();
			break;

		default:
			break;
		}
		break;

	case FL_MOUSEWHEEL:
		switch (Fl::event_dy())
		{
		case 1:
			mouseWheelBackwardEvent();
			break;

		case -1:
			mouseWheelForwardEvent();
			break;

		default:
			break;
		}
		break;

	case FL_DRAG:									// mouse moved while down event.
		x = Fl::event_x();
		y = Fl::event_y();

		switch (Fl::event_button())
		{
		case FL_LEFT_MOUSE:
			mouseLeftButtonDragEvent(x, y);
			break;

		case FL_RIGHT_MOUSE:
			mouseRightButtonDragEvent(x, y);
			break;

		case FL_MIDDLE_MOUSE:
			mouseMiddleButtonDragEvent(x, y);
			break;

		default:
			break;
		}
		break;

	case FL_MOVE:
		x = Fl::event_x();
		y = Fl::event_y();
		mouseMoveEvent(x, y);
		break;

	case FL_KEYBOARD:
		if (Fl::event_key() == FL_Escape)	// disabling the Escape key. (by default, Escape key closes the window.)
			return 1;
		if(keyPressEvent(Fl::event_key()))
			return 1;
		break;

	default:
		break;
	}

	return Fl_Double_Window::handle(_event);	// we handled the event if we didn't return earlier
}

int Fle_Window::handle(int _event)
{
	return processEvents(_event);
}

void Fle_Window::closeEvent()
{
	m_timer.stop();
	m_idle.stop();
	hide();
}

void Fle_Window::closeCallback(Fl_Widget* _w, void* _p)
{
	Fle_Window* w = static_cast<Fle_Window*>(_p);
	if (w) w->closeEvent();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void Fle_Window::setBackgroundColor(uchar _red, uchar _green, uchar _blue) 
{ 
	if(p_box) p_box->color(fl_rgb_color(_red, _green, _blue));
	Fl_Double_Window::color(fl_rgb_color(_red, _green, _blue));
}
void Fle_Window::setBackgroundColor(Fl_Color _color)
{
	if (p_box) p_box->color(_color);
	Fl_Double_Window::color(_color);
}
Fl_Color Fle_Window::getBackgroundColor() const 
{ 
	return Fl_Double_Window::color(); 
}
void Fle_Window::setBox(Fle_Box* _b) 
{
	if (_b == nullptr) 
		return;

	if (p_box)
	{
		remove(p_box);
		delete p_box;
	}
	p_box = _b;
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
