#pragma once
#ifndef Fle_OpenGLWindow_h__
#define Fle_OpenGLWindow_h__

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

#include <FLE/Fle_Export.h>
#include <FLE/Fle_Timer.h>
#include <FLE/Fle_Size.h>

#include <FL/Fl_Gl_Window.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_OpenGLWindow : public Fl_Gl_Window
{
public:
	// Description:
	// Constructor to create an OpenGL window by specifying it's position, size, title.
	// _icon_index is the id of the icon that you want to display on the title bar.
	Fle_OpenGLWindow(int _x, int _y, int _w, int _h, const char* _title = 0, int _icon_index = 101);
	// Description:
	// Constructor to create an OpenGL window by specifying it's size and title.
	// This constructor sets the position at the center of the screen/monitor.
	// _icon_index is the id of the icon that you want to display on the title bar.
	Fle_OpenGLWindow(int _w, int _h, const char* _title = 0, int _icon_index = 101);
	// Description:
	// Destructor that destroys timers (if any) and other data.
	virtual ~Fle_OpenGLWindow();
	
	// Description:
	// Function that must be called whenever there is a need to add/pack widget inside the window.
	virtual void begin();
	// Description:
	// Function that must be called to stop adding widgets inside the window.
	// If you call begin(), then must be end().
	virtual void end();

	// Description:
	// Function to make this window as current.
	virtual void makeCurrent();
	// Description:
	// Function to resize the window by specifying the position, width and height.
	// Overridden function that will be called while resizing the window.
	virtual void resize(int _x, int _y, int _w, int _h) override;
	// Description:
	// Function to resize the window by specifying the width and height.
	// This function will not be called while resizing, only above function resize() does call.
	virtual void size(int _w, int _h);

	// Description:
	// Function to redraw/update the window.
	// Both update() and redraw() do the same work.
	virtual void redraw();
	// Description:
	// Overloaded function of redraw().
	// Both update() and redraw() do the same work.
	virtual void update();
	
	// Description:
	// Function to show the window minimized.
	// Only for Windows/WIN32.
	void showMinimized();
	// Description:
	// Function to show the window maximized.
	// Only for Windows/WIN32.
	void showMaximized();
	// Description:
	// Function to show the window full-screen without title-bar and borders.
	void showFullScreen();
	// Description:
	// Function to restore the normal window, after calling showFullScreen().
	void showNormal();

	// Description:
	// Function to set minimum size of the widget.
	// Default value is Fle_Size(10, 10).
	void setMinimumSize(const Fle_Size& _size);
	// Description:
	// Function to get minimum size of the widget.
	// Default value is Fle_Size(10, 10).
	Fle_Size getMinimumSize() const { return m_minsize; }
	// Description:
	// Function to set maximum size of the widget.
	// Widget will be expanded/resized to maximum size while resizing the parent window.
	// Default value is Fle_Size(Screen-Size + 10000000).
	void setMaximumSize(const Fle_Size& _size);
	// Description:
	// Function to get maximum size of the widget.
	Fle_Size getMaximumSize() const { return m_maxsize; }
	// Description:
	// Function to set widget as resizeable.
	// The widget will be resized while resizing the 
	// parent widget if it's true, otherwise widget will be fixed on false.
	// Default value is true
	void setResizeable(bool _b);
	// Description:
	// Function to set the fixed width of the widget.
	void setFixedWidth(int _w);
	// Description:
	// Function to set the fixed height of the widget.
	void setFixedHeight(int _h);

	// Description:
	// Function to draw an image by specifying the position, size, image data, and the depth value.
	// _channels could be 1 (grayscale image), 3 (RGB image) or 4 (RGBA image).
	// _z_depth = 1.f (most back), _z_depth = -1.f (most front).
	void drawImage(int _x, int _y, int _w, int _h, unsigned char* _data, int _channels, float _z_depth = 1.f);

	// Description:
	// Function to get the timer of timerEvent().
	Fle_Timer& getTimer() { return m_timer; }

protected:
	// Description:
	// Function that will be called only once at the start of the window.
	// It uses to initialize the OpenGL states or any other data such as textures etc.
	virtual void initializeGL();
	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// all kinds of OpenGL rendering.
	virtual void paintGL();
	// Description:
	// Function that is expected to be overridden in order to implement
	// operations while resizing the window. 
	// This function will be called whenever this window is resized.
	virtual void resizeGL(int _w, int _h);

	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// implementing the real-time updating/computing sort of stuff.
	// Test it by overriding this function and write some output std::cout << "tick\n"; in it, you will notice,
	// tick will be printed out repeatedly.
	// On WIN32, this function scales up to about 62 FPS then will go no faster. 
	virtual void timerEvent();
	// Description:
	// A virtual function that is basically an infinite loop to redraw/update the window.
	virtual void idleEvent();

	// Description:
	// Virtual functions that are expected to be overridden in the derived class for
	// handling the mouse and keyboard events.
	virtual void mouseLeftButtonPressEvent(int _x, int _y);		// when left mouse button is pressed.
	virtual void mouseRightButtonPressEvent(int _x, int _y);	// when right mouse button is pressed.
	virtual void mouseMiddleButtonPressEvent(int _x, int _y);	// when middle mouse button is pressed.
	virtual void mouseLeftButtonReleaseEvent();					// when left mouse button is released.
	virtual void mouseRightButtonReleaseEvent();				// when right mouse button is released.
	virtual void mouseMiddleButtonReleaseEvent();				// when middle mouse button is released.
	virtual void mouseWheelForwardEvent();						// when mouse wheel moved forward.
	virtual void mouseWheelBackwardEvent();						// when mouse wheel moved backward.
	virtual void mouseLeftButtonDragEvent(int _x, int _y);		// when left mouse button is dragged.
	virtual void mouseRightButtonDragEvent(int _x, int _y);		// when right mouse button is dragged.
	virtual void mouseMiddleButtonDragEvent(int _x, int _y);	// when middle mouse button is dragged.
	virtual void mouseMoveEvent(int _x, int _y);				// when mouse moves.
	virtual int keyPressEvent(int _key);						// keyboard key press events.

	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// handling events such as FL_SHOW, FL_FOCUS, etc.
	virtual int processEvents(int _event);

	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// implementing the close (top right) button callback.
	// This function is called when the close (top right) button is pressed.
	// This function should have "hide()" function in order to close or hide the window.
	virtual void closeEvent();

	// Description:
	// protected data members.

	Fle_Timer m_timer;
	Fle_Idle m_idle;

	Fle_Size m_minsize;
	Fle_Size m_maxsize;

private:
	// Description:
	// Overridden function for all kinds of OpenGL rendering.
	virtual void draw() override;

	// Description:
	// Overridden function that handles all kind of events.
	// Event handler (for internal use).
	virtual int handle(int _event) override;

	// Description:
	// Function to be called when close (top right) button is clicked (for internal use).
	static void closeCallback(Fl_Widget* _w, void* _p);
};

}

#endif // Fle_OpenGLWindow_h__