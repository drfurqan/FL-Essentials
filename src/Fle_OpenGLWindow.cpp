/*********************************************************************************
created:	2017/02/27   06:14PM
filename: 	Fle_OpenGLWindow.h
file base:	Fle_OpenGLWindow
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A generalized OpenGL window with basic necessary functions.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_OpenGLWindow.h>
#include <FLE/Fle_WindowsUtil.h>	// needed for maximized

#include <FL/Fl.H>
#include <FL/gl.h>
#include <FL/x.H>               // needed for fl_display

using namespace R3D;

Fle_OpenGLWindow::Fle_OpenGLWindow(int _x, int _y, int _w, int _h, const char* _title, int _icon_index) :
	Fl_Gl_Window(_x, _y, _w, _h, _title),
	m_minsize(Fle_Size(10, 10)),
	m_maxsize(Fle_Size(Fl::w() + 1000, Fl::h() + 1000)),
	m_dnd(false)
{
	Fl_Gl_Window::mode(FL_RGB8 | FL_DOUBLE | FL_ALPHA | FL_DEPTH | FL_ACCUM | FL_STENCIL | FL_MULTISAMPLE);
#ifdef WIN32
	icon(LoadIcon(fl_display, MAKEINTRESOURCE(_icon_index)));
#endif // WIN32

	Fl_Gl_Window::end();

	color(fl_rgb_color(214, 219, 233));
	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	resizable(this);
	size_range(10, 10);
	callback(closeCallback, static_cast<void*>(this));

	// setting up timer event.
	std::function<void()> tf = [this]() { timerEvent(); };
	m_timer.setFunction(tf);
	m_timer.setTime(1.0 / 70.0);	// (1.0 / 70.0) gives us 60 ~ 63 FPS.

	// setting up idle event that is basically an infinite loop
	// that should update/redraw the window for real-time rendering.
	std::function<void()> f = [this]() { idleEvent(); };
	m_idle.setFunction(f);
}

Fle_OpenGLWindow::Fle_OpenGLWindow(int _w, int _h, const char* _title, int _icon_index) :
	Fl_Gl_Window(0, 0, _w, _h, _title),
	m_minsize(Fle_Size(10, 10)),
	m_maxsize(Fle_Size(Fl::w() + 1000, Fl::h() + 1000)),
	m_dnd(false)
{
	Fl_Gl_Window::mode(FL_RGB8 | FL_DOUBLE | FL_ALPHA | FL_DEPTH | FL_ACCUM | FL_STENCIL | FL_MULTISAMPLE);
#ifdef WIN32
	icon(LoadIcon(fl_display, MAKEINTRESOURCE(_icon_index)));
#endif // WIN32

	Fl_Gl_Window::end();

	color(fl_rgb_color(214, 219, 233));
	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	resizable(this);
	size_range(10, 10);
	callback(closeCallback, static_cast<void*>(this));

	// setting up timer event.
	std::function<void()> tf = [this]() { timerEvent(); };
	m_timer.setFunction(tf);
	m_timer.setTime(1.0 / 70.0);	// (1.0 / 70.0) gives us 60 ~ 63 FPS.

	// setting up idle event that is basically an infinite loop
	// that should update/redraw the window for real-time rendering.
	std::function<void()> f = [this]() { idleEvent(); };
	m_idle.setFunction(f);

	// positioned at center of the screen.
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);
}

Fle_OpenGLWindow::~Fle_OpenGLWindow()
{
	Fle_OpenGLWindow::closeEvent();
}

void Fle_OpenGLWindow::initializeGL()
{
}

void Fle_OpenGLWindow::makeCurrent()
{
	Fl_Gl_Window::make_current();
}

void Fle_OpenGLWindow::paintGL()
{
}

void Fle_OpenGLWindow::draw()
{
	if (!visible()) 
		return;

	// it will be called only one time. 
	// but it will also be called whenever we resize the window.
	if (!valid())
	{
		// we need OpenGL initialization only first time.
		static bool first_time_init = true;
		if (first_time_init)
		{
			first_time_init = false;
			makeCurrent();
			initializeGL();
		}
	}

	makeCurrent();
	paintGL();
}

void Fle_OpenGLWindow::timerEvent()
{
}
void Fle_OpenGLWindow::idleEvent()
{
}

void Fle_OpenGLWindow::redraw()
{
	Fl_Gl_Window::redraw();
}
void Fle_OpenGLWindow::update()
{ 
	redraw();
}
void Fle_OpenGLWindow::resize(int _x, int _y, int _w, int _h)
{
	Fl_Gl_Window::resize(_x, _y, _w, _h);
	resizeGL(_w, _h);
	redraw();
}
void Fle_OpenGLWindow::size(int _w, int _h)
{
	resize(x(), y(), _w, _h);
}
void Fle_OpenGLWindow::resizeGL(int _w, int _h)
{
}

void Fle_OpenGLWindow::showMinimized()
{
	show();
	Fle_WindowsUtil::setWindowOption(label(), Fle_WindowsUtil::Options::ShowMinimized);
	size(w(), h());
}
void Fle_OpenGLWindow::showMaximized()
{
	showMinimized();		// this does the trick for a little animation started from bottom.
	Fle_WindowsUtil::setWindowOption(label(), Fle_WindowsUtil::Options::ShowMaximized);
	size(w(), h());
}
void Fle_OpenGLWindow::showFullScreen()
{
	show();
	fullscreen();
	size(w(), h());
}
void Fle_OpenGLWindow::showNormal()
{
	show();
	fullscreen_off();
	size(w(), h());
}
void Fle_OpenGLWindow::setMinimumSize(const Fle_Size& _size)
{
	m_minsize = _size;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}
void Fle_OpenGLWindow::setMaximumSize(const Fle_Size& _size)
{
	m_maxsize = _size;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}
void Fle_OpenGLWindow::setResizeable(bool _b)
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
void Fle_OpenGLWindow::setFixedWidth(int _w)
{
	m_minsize.width = _w;
	m_maxsize.width = _w;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}
void Fle_OpenGLWindow::setFixedHeight(int _h)
{
	m_minsize.height = _h;
	m_maxsize.height = _h;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}

/************************************************************************/
/* Mouse interaction with Window                                        */
/************************************************************************/
int Fle_OpenGLWindow::mouseLeftButtonPressEvent(int _x, int _y)
{
	return 0;
}
int Fle_OpenGLWindow::mouseRightButtonPressEvent(int _x, int _y)
{
	return 0;
}
int Fle_OpenGLWindow::mouseMiddleButtonPressEvent(int _x, int _y)
{
	return 0;
}
int Fle_OpenGLWindow::mouseLeftButtonReleaseEvent()
{
	return 0;
}
int Fle_OpenGLWindow::mouseRightButtonReleaseEvent()
{
	return 0;
}
int Fle_OpenGLWindow::mouseMiddleButtonReleaseEvent()
{
	return 0;
}
int Fle_OpenGLWindow::mouseWheelForwardEvent()
{
	return 0;
}
int Fle_OpenGLWindow::mouseWheelBackwardEvent()
{
	return 0;
}

int Fle_OpenGLWindow::mouseLeftButtonDragEvent(int _x, int _y)
{
	return 0;
}
int Fle_OpenGLWindow::mouseRightButtonDragEvent(int _x, int _y)
{
	return 0;
}
int Fle_OpenGLWindow::mouseMiddleButtonDragEvent(int _x, int _y)
{
	return 0;
}

int Fle_OpenGLWindow::mouseMoveEvent(int _x, int _y)
{
	return 0;
}

/************************************************************************/
/* Keyboard interaction with Window                                     */
/************************************************************************/
int Fle_OpenGLWindow::keyPressEvent(int _key)
{
	return 0;
}
int Fle_OpenGLWindow::processEvents(int _event)
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
		makeCurrent();
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
		else if (keyPressEvent(Fl::event_key()))
			return 1;

		break;

	default:
		break;
	}

	return Fl_Gl_Window::handle(_event);	// we handled the event if we didn't return earlier
}
int Fle_OpenGLWindow::handle(int _event)
{
	return processEvents(_event);
}

int Fle_OpenGLWindow::dragDropEvent(const std::string& _text)
{
	return 0;
}

void Fle_OpenGLWindow::closeEvent()
{
	m_timer.stop();
	m_idle.stop();
	hide();
}

void Fle_OpenGLWindow::closeCallback(Fl_Widget* _w, void* _p)
{
	Fle_OpenGLWindow* w = static_cast<Fle_OpenGLWindow*>(_p);
	if (w) w->closeEvent();
}

void Fle_OpenGLWindow::drawImage(int _x, int _y, int _w, int _h, unsigned char* _data, int _channels, float _z_depth)
{
	if (!visible()) 
		return;

	makeCurrent();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glRasterPos3f(
		-1.f + 2.f*static_cast<GLfloat>(_x - Fl_Gl_Window::x()) / static_cast<GLfloat>(Fl_Gl_Window::w()),
		-1.f + 2.f*static_cast<GLfloat>(_y - Fl_Gl_Window::y()) / static_cast<GLfloat>(Fl_Gl_Window::h()),
		_z_depth); // front or back

	if (_channels == 3)
		glDrawPixels(_w, _h, GL_RGB, GL_UNSIGNED_BYTE, _data);
	else if (_channels == 4)
		glDrawPixels(_w, _h, GL_RGBA, GL_UNSIGNED_BYTE, _data);
	else if (_channels == 1)
		glDrawPixels(_w, _h, GL_LUMINANCE, GL_UNSIGNED_BYTE, _data);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
