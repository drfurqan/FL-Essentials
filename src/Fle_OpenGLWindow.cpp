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
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_OpenGLWindow.h"
#include "Fle_WindowsUtil.h"	// needed for maximized

#include <FL/Fl.H>
#include <FL/gl.H>
//#include <FL/glu.H>
//#include <FL/glut.H>
#include <FL/x.H>               // needed for fl_display

using namespace R3D;

Fle_OpenGLWindow::Fle_OpenGLWindow(int _x, int _y, int _w, int _h, const char* _title, int _icon_index) :
Fl_Gl_Window(_x, _y, _w, _h, _title),
m_first_time_init(true),
m_minsize(cv::Size(10, 10)),
m_maxsize(cv::Size(Fl::w() + 1000, Fl::h() + 1000))
{
	mode(FL_DOUBLE | FL_RGB8 | FL_DEPTH | FL_ACCUM | FL_ALPHA | FL_STENCIL | FL_MULTISAMPLE);
#ifdef WIN32
	icon(LoadIcon(fl_display, MAKEINTRESOURCE(_icon_index)));
#endif // WIN32
	color(fl_rgb_color(214, 219, 233));
	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	resizable(this);
	size_range(10, 10);
	callback(closeCallback, (void*)this);
	end();

	// setting up timer event.
	std::function<void()> tf = [&]()
	{
		this->timerEvent();
	};
	m_timer.setFunction(tf);
	m_timer.setTime(1.0 / 70.0);	// (1.0 / 70.0) gives us 60 ~ 63 FPS.
	// setting up idle event that is basically an infinite loop
	// that should update/redraw the window for real-time rendering.
	std::function<void()> f = [&]()
	{
		this->idleEvent();
	};
	m_idle.setFunction(f);
}

Fle_OpenGLWindow::Fle_OpenGLWindow(int _w, int _h, const char* _title, int _icon_index) :
Fl_Gl_Window(0, 0, _w, _h, _title),
m_first_time_init(true),
m_minsize(cv::Size(10, 10)),
m_maxsize(cv::Size(Fl::w() + 1000, Fl::h() + 1000))
{
	mode(FL_DOUBLE | FL_RGB8 | FL_DEPTH | FL_ACCUM | FL_ALPHA | FL_STENCIL | FL_MULTISAMPLE);
#ifdef WIN32
	icon(LoadIcon(fl_display, MAKEINTRESOURCE(_icon_index)));
#endif // WIN32
	color(fl_rgb_color(214, 219, 233));
	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	resizable(this);
	size_range(10, 10);
	callback((Fl_Callback*)closeCallback, (void*)this);
	
	// positioned at center of the screen.
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);
	end(); // this call is necessary to prevent any additional UI widgets from becoming subcomponents of this window.
	
		   // setting up timer event.
	std::function<void()> tf = [&]()
	{
		this->timerEvent();
	};
	m_timer.setFunction(tf);
	m_timer.setTime(1.0 / 70.0);	// (1.0 / 70.0) gives us 60 ~ 63 FPS.
	// setting up idle event that is basically an infinite loop
	// that should update/redraw the window for real-time rendering.
	std::function<void()> f = [&]()
	{
		this->idleEvent();
	};
	m_idle.setFunction(f);
}

Fle_OpenGLWindow::~Fle_OpenGLWindow()
{
	closeEvent();
}

void Fle_OpenGLWindow::begin()
{
	Fl_Gl_Window::begin();
}
void Fle_OpenGLWindow::end()
{
	Fl_Gl_Window::end();
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
	if (!visible()) return;

	Fl_Gl_Window::draw();

	// it will be called only one time. 
	// but it will also be called whenever we resize the window.
	if (!valid())
	{
		// we need OpenGL initialization only first time.
		if (m_first_time_init)
		{
			initializeGL();
			m_first_time_init = false;
			valid(1);
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
	reshape(_w, _h);
}
void Fle_OpenGLWindow::size(int _w, int _h)
{
	resize(x(), y(), _w, _h);
}
void Fle_OpenGLWindow::reshape(int _w, int _h)
{
}

void Fle_OpenGLWindow::showMinimized()
{
	show();
	Fle_WindowsUtil::setWindowOption(label(), Fle_WindowsUtil::Options::ShowMinimized);
}
void Fle_OpenGLWindow::showMaximized()
{
	showMinimized();		// this does the trick for a little animation started from bottom.
	Fle_WindowsUtil::setWindowOption(label(), Fle_WindowsUtil::Options::ShowMaximized);
}
void Fle_OpenGLWindow::showFullScreen()
{
	show();
	fullscreen();
}
void Fle_OpenGLWindow::showNormal()
{
	show();
	fullscreen_off();
}
void Fle_OpenGLWindow::setMinimumSize(const cv::Size& _size)
{
	m_minsize = _size;
	size_range(m_minsize.width, m_minsize.height, m_maxsize.width, m_maxsize.height);
}
void Fle_OpenGLWindow::setMaximumSize(const cv::Size& _size)
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
void Fle_OpenGLWindow::mouseLeftButtonPressEvent(int _x, int _y)
{
	//std::cout << "left mouse button is pressed, and the coordinates are (" << _x << ", " << _y << ").\n";
}
void Fle_OpenGLWindow::mouseRightButtonPressEvent(int _x, int _y)
{
	//std::cout << "right mouse button is pressed, and the coordinates are (" << _x << ", " << _y << ").\n";
}
void Fle_OpenGLWindow::mouseMiddleButtonPressEvent(int _x, int _y)
{
	//std::cout << "middle mouse button is pressed, and the coordinates are (" << _x << ", " << _y << ").\n";
}
void Fle_OpenGLWindow::mouseLeftButtonReleaseEvent()
{
	//std::cout << "left mouse button is released.\n";
}
void Fle_OpenGLWindow::mouseRightButtonReleaseEvent()
{
	//std::cout << "right mouse button is released.\n";
}
void Fle_OpenGLWindow::mouseMiddleButtonReleaseEvent()
{
	//std::cout << "middle mouse button is released.\n";
}
void Fle_OpenGLWindow::mouseWheelForwardEvent()
{
	//std::cout << "mouse wheel is moving forward.\n";
}
void Fle_OpenGLWindow::mouseWheelBackwardEvent()
{
	//std::cout << "mouse wheel is moving backward.\n";
}

void Fle_OpenGLWindow::mouseLeftButtonDragEvent(int _x, int _y)
{
}
void Fle_OpenGLWindow::mouseRightButtonDragEvent(int _x, int _y)
{
}
void Fle_OpenGLWindow::mouseMiddleButtonDragEvent(int _x, int _y)
{
}

void Fle_OpenGLWindow::mouseMoveEvent(int _x, int _y)
{
	//std::cout << _x << "\t" << _y << "\n";
}
int Fle_OpenGLWindow::keyPressEvent(int _key)
{
	return 0;
}

int Fle_OpenGLWindow::processEvents(int _event)
{
	static int x, y;

	switch (_event)
	{
	case FL_FOCUS:
	case FL_UNFOCUS:
		return 1;
		break;								// enables receiving keyboard events

	case FL_PUSH:
		x = Fl::event_x();
		y = Fl::event_y();
		makeCurrent();
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
		}
		break;

	case FL_MOUSEWHEEL:
		switch (Fl::event_dy())
		{
		case 1:
			mouseWheelBackwardEvent();
			return 1;

		case -1:
			mouseWheelForwardEvent();
			return 1;
		}
		return 1;

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
		}
		break;

	case FL_MOVE:
		x = Fl::event_x();
		y = Fl::event_y();
		mouseMoveEvent(x, y);
		break;

	case FL_KEYBOARD:
		switch (Fl::event_key())
		{
			// disabling the Escape key. (by default, Escape key closes the window.)
		case FL_Escape:
			return 1;
		}
		if (keyPressEvent(Fl::event_key()))
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

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glRasterPos3f(-1.f + 2.f*static_cast<GLfloat>(_x - x()) / static_cast<GLfloat>(w()),
		-1.f + 2.f*static_cast<GLfloat>(_y - y()) / static_cast<GLfloat>(h()),
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

	glPopAttrib();
}
