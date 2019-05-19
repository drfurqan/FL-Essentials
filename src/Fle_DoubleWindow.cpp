/*********************************************************************************
created:	2017/01/27   02:05AM
filename: 	Fle_DoubleWindow.h
file base:	Fle_DoubleWindow
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

#include <FLE/Fle_DoubleWindow.h>
#include <FLE/Fle_WindowsUtil.h>	// needed for maximized

#include <FL/Fl.H>
#include <FL/x.H>					// needed for fl_display

using namespace R3D;

Fle_DoubleWindow::Fle_DoubleWindow(int _x, int _y, int _w, int _h, const char* _title, int _icon_index) :
	Fl_Double_Window(_x, _y, _w, _h, _title),
	m_minsize(Fle_Size(10, 10)),
	m_maxsize(Fle_Size(Fl::w() + 100000, Fl::h() + 100000)),
	m_dnd(false)
{
	//Fl_Pixmap ico(img);
	//Fl_RGB_Image app(&ico);
	//icon(&app);
	//default_icon(&app);

#ifdef WIN32
	icon(LoadIcon(fl_display, MAKEINTRESOURCE(_icon_index)));
#endif // WIN32

	Fl_Double_Window::end(); // This call is necessary to prevent any additional UI widgets from becoming subcomponents of this window.

	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	color(fl_rgb_color(238, 243, 250));
	box(FL_FLAT_BOX);
	resizable(this);
	size_range(10, 10);		// it will enable minimize, maximize, close button in the title bar.
	user_data(static_cast<void*>(this));
	callback(closeCallback, static_cast<void*>(this));

	m_timer.setFunction([this]() { timerEvent(); });	// setting up timer event.
	m_idle.setFunction([this]() { idleEvent(); });		// setting up idle event.
}
Fle_DoubleWindow::Fle_DoubleWindow(int _w, int _h, const char* _title, int _icon_index) :
	Fl_Double_Window(0, 0, _w, _h, _title),
	m_minsize(Fle_Size(10, 10)),
	m_maxsize(Fle_Size(Fl::w() + 100000, Fl::h() + 100000)),
	m_dnd(false)
{
	//Fl_Pixmap ico(img);
	//Fl_RGB_Image app(&ico);
	//icon(&app);
	//default_icon(&app);

#ifdef WIN32
	icon(LoadIcon(fl_display, MAKEINTRESOURCE(_icon_index)));
#endif // WIN32

	Fl_Double_Window::end(); // This call is necessary to prevent any additional UI widgets from becoming subcomponents of this window.

	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	color(fl_rgb_color(238, 243, 250));
	box(FL_FLAT_BOX);
	resizable(this);
	size_range(10, 10);		// it will enable minimize, maximize, close button in the title bar.
	user_data(static_cast<void*>(this));
	callback(closeCallback, static_cast<void*>(this));

	m_timer.setFunction([this]() { timerEvent(); });	// setting up timer event.
	m_idle.setFunction([this]() { idleEvent(); });		// setting up idle event.

	// positioned at center of the screen.
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);
}
Fle_DoubleWindow::~Fle_DoubleWindow()
{
}

void Fle_DoubleWindow::timerEvent()
{
}
void Fle_DoubleWindow::idleEvent()
{
}

void Fle_DoubleWindow::redraw()
{
	Fl_Double_Window::redraw();
}
void Fle_DoubleWindow::update()
{
	redraw();
}

void Fle_DoubleWindow::paintEvent()
{
}
void Fle_DoubleWindow::draw()
{
	if (!visible()) return;

	Fl_Double_Window::draw();
	paintEvent();
}

void Fle_DoubleWindow::showMinimized()
{
	show();
	Fle_WindowsUtil::setWindowOption(label(), Fle_WindowsUtil::Options::ShowMinimized);
	size(w(), h());
}
void Fle_DoubleWindow::showMaximized()
{
	showMinimized();		// this does the trick for a little animation started from bottom.
	Fle_WindowsUtil::setWindowOption(label(), Fle_WindowsUtil::Options::ShowMaximized);
	size(w(), h());
}
void Fle_DoubleWindow::showFullScreen()
{
	show();
	fullscreen();
	size(w(), h());
}
void Fle_DoubleWindow::showNormal()
{
	show();
	fullscreen_off();
	size(w(), h());
}
void Fle_DoubleWindow::show(bool _at_screen_center)
{
	if (_at_screen_center)
	{
		// positioned at center of the screen.
		int X, Y, W, H;
		Fl::screen_work_area(X, Y, W, H);
		position(X + W / 2 - w() / 2, Y + H / 2 - h() / 2);
	}

	Fl_Double_Window::show();
}

void Fle_DoubleWindow::resize(int _x, int _y, int _w, int _h)
{
	Fl_Double_Window::resize(_x, _y, _w, _h);
}
void Fle_DoubleWindow::size(int _w, int _h)
{
	resize(x(), y(), _w, _h);
}
void Fle_DoubleWindow::setMinimumSize(const Fle_Size& _size)
{
	m_minsize = _size;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}
void Fle_DoubleWindow::setMaximumSize(const Fle_Size& _size)
{
	m_maxsize = _size;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}
void Fle_DoubleWindow::setResizeable(bool _b)
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
void Fle_DoubleWindow::setFixedWidth(int _w)
{
	m_minsize.width = _w;
	m_maxsize.width = _w;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}
void Fle_DoubleWindow::setFixedHeight(int _h)
{
	m_minsize.height = _h;
	m_maxsize.height = _h;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}

/************************************************************************/
/* Mouse interaction with Window                                        */
/************************************************************************/
int Fle_DoubleWindow::mouseLeftButtonPressEvent(int _x, int _y)
{
	//std::cout << "Abstract_Window: left mouse button is pressed, and the coordinates are (" << _x << ", " << _y << ").\n";
	return 0;
}
int Fle_DoubleWindow::mouseRightButtonPressEvent(int _x, int _y)
{
	//std::cout << "right mouse button is pressed, and the coordinates are (" << _x << ", " << _y << ").\n";
	return 0;
}
int Fle_DoubleWindow::mouseMiddleButtonPressEvent(int _x, int _y)
{
	//std::cout << "middle mouse button is pressed, and the coordinates are (" << _x << ", " << _y << ").\n";
	return 0;
}
int Fle_DoubleWindow::mouseLeftButtonReleaseEvent()
{
	//std::cout << "left mouse button is released.\n";
	return 0;
}
int Fle_DoubleWindow::mouseRightButtonReleaseEvent()
{
	//std::cout << "right mouse button is released.\n";
	return 0;
}
int Fle_DoubleWindow::mouseMiddleButtonReleaseEvent()
{
	//std::cout << "middle mouse button is released.\n";
	return 0;
}
int Fle_DoubleWindow::mouseWheelForwardEvent()
{
	//std::cout << "mouse wheel is moving forward.\n";
	return 0;
}
int Fle_DoubleWindow::mouseWheelBackwardEvent()
{
	//std::cout << "mouse wheel is moving backward.\n";
	return 0;
}

int Fle_DoubleWindow::mouseLeftButtonDragEvent(int _x, int _y)
{
	return 0;
}
int Fle_DoubleWindow::mouseRightButtonDragEvent(int _x, int _y)
{
	return 0;
}
int Fle_DoubleWindow::mouseMiddleButtonDragEvent(int _x, int _y)
{
	return 0;
}

int Fle_DoubleWindow::mouseMoveEvent(int _x, int _y)
{
	return 0;
}

/************************************************************************/
/* Keyboard interaction with Window                                     */
/************************************************************************/
int Fle_DoubleWindow::keyPressEvent(int _key)
{
	return 0;
}
int Fle_DoubleWindow::processEvents(int _event)
{
	static int x, y;

	switch (_event)
	{
	case FL_UNFOCUS:
	case FL_FOCUS:
		return 1;

	case FL_DND_LEAVE:
	case FL_DND_DRAG:
	case FL_DND_RELEASE:
		return m_dnd ? 1 : 0;

		// event when a user releases a file on this widget.
	case FL_PASTE:
		if (dragDropEvent(Fl::event_text()))
			return 1;
		break;

	case FL_PUSH:
		x = Fl::event_x();
		y = Fl::event_y();
		take_focus();						// this allows key events to work.
		if (Fl::event_button() == FL_LEFT_MOUSE)
		{
			if (mouseLeftButtonPressEvent(x, y))
				return 1;
		}
		else if (Fl::event_button() == FL_MIDDLE_MOUSE)
		{
			if (mouseMiddleButtonPressEvent(x, y))
				return 1;
		}
		else if (Fl::event_button() == FL_RIGHT_MOUSE)
		{
			if (mouseRightButtonPressEvent(x, y))
				return 1;
		}
		break;

	case FL_RELEASE:
		if (Fl::event_button() == FL_LEFT_MOUSE)
		{
			if (mouseLeftButtonReleaseEvent())
				return 1;
		}
		else if (Fl::event_button() == FL_MIDDLE_MOUSE)
		{
			if (mouseMiddleButtonReleaseEvent())
				return 1;
		}
		else if (Fl::event_button() == FL_RIGHT_MOUSE)
		{
			if (mouseRightButtonReleaseEvent())
				return 1;
		}
		break;

	case FL_DRAG:									// mouse moved while down event.
		x = Fl::event_x();
		y = Fl::event_y();

		if (Fl::event_button1())					// with FL_DRAG event "Fl::event_button() == FL_LEFT_MOUSE" doesn't work.
		{
			if (mouseLeftButtonDragEvent(x, y))
				return 1;
		}
		else if (Fl::event_button2())
		{
			if (mouseMiddleButtonDragEvent(x, y))
				return 1;
		}
		else if (Fl::event_button3())
		{
			if (mouseRightButtonDragEvent(x, y))
				return 1;
		}
		break;

	case FL_MOVE:
		x = Fl::event_x();
		y = Fl::event_y();
		if (mouseMoveEvent(x, y))
			return 1;
		break;

	case FL_MOUSEWHEEL:
		if (Fl::event_dy() == 1)
		{
			if (mouseWheelBackwardEvent())
				return 1;
		}
		else if (Fl::event_dy() == -1)
		{
			if (mouseWheelForwardEvent())
				return 1;
		}
		break;

	case FL_KEYBOARD:
		if (Fl::event_key() == FL_Escape)	// disabling the Escape key. (by default, Escape key closes the window.)
			return 1;
		else if(keyPressEvent(Fl::event_key()))
			return 1;

		break;

	default:
		break;
	}

	return Fl_Double_Window::handle(_event);	// we handled the event if we didn't return earlier
}
int Fle_DoubleWindow::handle(int _event)
{
	return processEvents(_event);
}

int Fle_DoubleWindow::dragDropEvent(const std::string& _text)
{
	return 0;
}

void Fle_DoubleWindow::closeEvent()
{
	m_timer.stop();
	m_idle.stop();
	hide();
}

void Fle_DoubleWindow::closeCallback(Fl_Widget* _w, void* _p)
{
	Fle_DoubleWindow* w = static_cast<Fle_DoubleWindow*>(_p);
	if (w) w->closeEvent();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void Fle_DoubleWindow::setBackgroundColor(uchar _red, uchar _green, uchar _blue) 
{ 
	Fl_Double_Window::color(fl_rgb_color(_red, _green, _blue));
}
void Fle_DoubleWindow::setBackgroundColor(Fl_Color _color)
{
	Fl_Double_Window::color(_color);
}
Fl_Color Fle_DoubleWindow::getBackgroundColor() const 
{ 
	return Fl_Double_Window::color(); 
}
void Fle_DoubleWindow::color(uchar _red, uchar _green, uchar _blue)
{
	setBackgroundColor(_red, _green, _blue);
}
void Fle_DoubleWindow::color(Fl_Color _color)
{
	setBackgroundColor(_color);
}
Fl_Color Fle_DoubleWindow::color() const
{
	return getBackgroundColor();
}

void Fle_DoubleWindow::setTransparency(float _alpha) const
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
