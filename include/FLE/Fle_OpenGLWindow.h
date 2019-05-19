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
Copyright (C) 2014-2019 REAL3D

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
	// Function to set the width of the window.
	void setWidth(int _w) { size(_w, h()); }
	// Description:
	// Function to get the width of the window.
	int getWidth() const { return w(); }
	// Description:
	// Function to set the height of the window.
	void setHeight(int _h) { size(w(), _h); }
	// Description:
	// Function to get the height of the window.
	int getHeight() const { return h(); }

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
	// Function to set the drag and drop event enabled.
	// If enabled, then dragDropEvent() function will receive the event text of
	// the drooped/released file.
	void setDragDropEventEnabled(bool _b) { m_dnd = _b; }
	// Description:
	// Function that returns true if the drag and drop event is enabled.
	bool isDragDropEventEnabled() const { return m_dnd; }

	// Description:
	// Function to get the timer of timerEvent().
	Fle_Timer& getTimer() { return m_timer; }

	// Description:
	// Function to get a reference of the idle that connects with idleEvent().
	Fle_Idle& getIdle() { return m_idle; }

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
	// Manage this timerEvent by accessing a reference from getTimer() function.
	virtual void timerEvent();
	// Description:
	// A virtual function that is basically an infinite loop to redraw/update the window.
	// Manage this idleEvent by accessing a reference from getIdle() function.
	virtual void idleEvent();

	// Description:
	// Virtual functions that are expected to be overridden in the derived class for
	// handling the mouse and keyboard events.
	// If you want to handle the event of this widget then always return 1. But if you want to pass the
	// event to the childs of this widget then must return 0.
	// Once you return 1 from the following events, child widgets won't react from the same event.
	// Following function will be called...
	virtual int mouseLeftButtonPressEvent(int _x, int _y);		// when left mouse button is pressed.
	virtual int mouseRightButtonPressEvent(int _x, int _y);		// when right mouse button is pressed.
	virtual int mouseMiddleButtonPressEvent(int _x, int _y);	// when middle mouse button is pressed.
	virtual int mouseLeftButtonReleaseEvent();					// when left mouse button is released.
	virtual int mouseRightButtonReleaseEvent();					// when right mouse button is released.
	virtual int mouseMiddleButtonReleaseEvent();				// when middle mouse button is released.
	virtual int mouseWheelForwardEvent();						// when mouse wheel moved forward.
	virtual int mouseWheelBackwardEvent();						// when mouse wheel moved backward.
	virtual int mouseLeftButtonDragEvent(int _x, int _y);		// when left mouse button is dragged.
	virtual int mouseRightButtonDragEvent(int _x, int _y);		// when right mouse button is dragged.
	virtual int mouseMiddleButtonDragEvent(int _x, int _y);		// when middle mouse button is dragged.
	virtual int mouseMoveEvent(int _x, int _y);					// when mouse moves.
	virtual int dragDropEvent(const std::string& _text);		// when a file is dropped/released on this widget. _text is the path of the dropped file.

	// Description:
	// Virtual function that is expected to be overridden in the derived class for
	// handling the keyboard events.
	
	// You can find all supported keys from FLTK "fltk/FL/Enumerations.H" file.
	// Some keys are:
	// FL_Home, FL_Left, FL_Up, FL_Right, FL_Down, FL_Page_Up, FL_Page_Down, FL_End, FL_Print, 
	// FL_Insert, FL_Shift_L, FL_Shift_R, FL_Control_L, FL_Control_R, FL_Caps_Lock, FL_Alt_L,
	// FL_Alt_R, FL_Delete, FL_Enter, FL_Pause, FL_Tab, FL_BackSpace
	// Function Keys: FL_F => use FL_F + n for function key n. example: (FL_F + 1) = F1 key

	// Usage example: keyboard key press events.
	// overridden keyPressEvent function in the derived MyOpenGLClass class.
	// int MyOpenGLClass::keyPressEvent(int key)		// MyOpenGLClass is the child class of Fle_OpenGLWindow.
	// {
	//	 if (key == 'a' && Fl::event_state(FL_CTRL))	// CTRL key is pressed along with 'a'.
	//	 {
	//		 angle = angle + 0.1f;
	//		 return 1;									// very important: always return 1 when you successfully handle the key. 
	//	 }
	//	 return 0;										// very important: always return 0 when the key is not handled and must pass to the childs of this widget. 
	// }
	virtual int keyPressEvent(int _key);

	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// handling events such as FL_SHOW, FL_FOCUS, etc.
	// Always return 1 when you successfully handle the key event.
	// Always return 0 when the key is not handled and must pass to the childs of this widget. 
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

	bool m_dnd;

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