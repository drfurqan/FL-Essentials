#pragma once
#ifndef Fle_Window_h__
#define Fle_Window_h__

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

#include <FLE/Fle_Export.h>
#include <FLE/Fle_Box.h>
#include <FLE/Fle_Timer.h>
#include <FLE/Fle_Size.h>

#include <FL/Fl_Double_Window.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_Window : public Fl_Double_Window
{
public:
	// Description:
	// Constructor to create a window by specifying it's position, size, and title.
	// _icon_index is the id of the icon that you want to display on the title bar.
	Fle_Window(int _x, int _y, int _w, int _h, const char* _title, int _icon_index = 101);
	// Description:
	// Constructor to create a window by specifying it's size and title.
	// This constructor sets the position at the center of the screen/monitor.
	// _icon_index is the id of the icon that you want to display on the title bar.
	Fle_Window(int _w, int _h, const char* _title, int _icon_index = 101);
	// Description:
	// Destructor that destroys timers (if any) and other data.
	virtual ~Fle_Window();

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
	// Function to set the background color of the widget.
	virtual void setBackgroundColor(uchar _red, uchar _green, uchar _blue);
	// Description:
	// Function to set the background color of the widget.
	virtual void setBackgroundColor(Fl_Color _color);
	// Description:
	// Function to get the background color of the widget.
	Fl_Color getBackgroundColor() const;

	// Description:
	// Function to make this window transparent by specifying the alpha value.
	void setTransparency(float _alpha) const;

	// Description:
	// Function to set the drag and drop event enabled.
	// If enabled, then dragDropEvent() function will recieve the event text of
	// the drooped/released file.
	void setDragDropEventEnabled(bool _b) { m_dnd = _b; }
	// Description:
	// Function that returns true if the drag and drop event is enabled.
	bool isDragDropEventEnabled() const { return m_dnd; }

	// Description:
	// Function to set a pointer to embedded box.
	// It first deletes the previous one and then assign a pointer to new one.
	void setBox(Fle_Box* _b);
	// Description:
	// Function to get a pointer to embedded box.
	Fle_Box* getBox() const { return p_box; }

	// Description:
	// Function to get a reference of the timer that connects with timerEvent().
	Fle_Timer& getTimer() {	return m_timer; }

	// Description:
	// Function to get a reference of the idle that connects with idleEvent().
	Fle_Idle& getIdle() { return m_idle; }

protected:
	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// all kinds of OpenGL rendering.
	virtual void paintEvent();
	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// implementing the real-time updating/computing sort of stuff.
	// Test it by overriding this function and write some output std::cout << "tick\n"; in it, you will notice,
	// tick will be printed out repeatedly.
	// On WIN32, this function scales up to about 62 FPS then will go no faster. 
	virtual void timerEvent();
	// Description:
	// A virtual function that is basically an infinite loop.
	// Test it by overriding this function and write some output std::cout << "tick\n"; in it, you will notice,
	// tick will be printed out repeatedly with maximum frame rates.
	virtual void idleEvent();

	// Description:
	// Virtual functions that are expected to be overridden in the derived class for
	// handling the mouse and keyboard events.
	// Following function will be called...
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
	virtual void dragDropEvent(const std::string& _text);		// when a file is dropped/released on this widget. _text is the path of the dropped file.

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
	// overridden keyPressEvent function in the derived MyClass class.
	// int MyClass::keyPressEvent(int key)		// MyClass is the child class of Fle_Window.
	// {
	//	 if (key == 'a' && Fl::event_state(FL_CTRL))	// CTRL key is pressed along with 'a'.
	//	 {
	//		 angle = angle + 0.1f;
	//		 return 1;									// very important: always return 1 when you successfully handle the key. 
	//	 }
	//	 return 0;										// very important: always return 0 when the key is not handled. 
	// }
	virtual int keyPressEvent(int _key);

	// Description:
	// Overridden function that handles all kind of events.
	// Event handler (for internal use).
	// It just calls processEvents(_event) function.
	virtual int handle(int _event) override;

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
	// Overridden function for all kinds of OpenGL rendering.
	virtual void draw() override;

	Fle_Timer m_timer;
	Fle_Idle m_idle;

	Fle_Size m_minsize;
	Fle_Size m_maxsize;

	// Description:
	// Embedded box inside the Double_Window.
	Fle_Box* p_box;

	bool m_dnd;

private:
	// Description:
	// Function to be called when close (top right) button is clicked (for internal use).
	static void closeCallback(Fl_Widget* _w, void* _p);
};

}

#endif // Fle_Window_h__