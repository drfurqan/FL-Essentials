#pragma once
#ifndef Fle_MainWindow_h__
#define Fle_MainWindow_h__

/*********************************************************************************
created:	2017/01/29   05:58AM
filename: 	Fle_MainWindow.h
file base:	Fle_MainWindow
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Main window class with menu, tool, and status bars.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Window.h>
#include <FLE/Fle_MenuBar.h>
#include <FLE/Fle_ToolBar.h>
#include <FLE/Fle_StatusBar.h>
#include <FLE/Fle_Color.h>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_MainWindow : public Fle_Window
{
public:
	// Description:
	// Constructor to create a window by specifying it's position, size, and title.
	// _icon_index is the id of the icon that you want to display on the title bar.
	Fle_MainWindow(int _x, int _y, int _w, int _h, const char* _title = 0, int _icon_index = 101);
	// Description:
	// Constructor to create a window by specifying it's size and title.
	// This constructor sets the position at the center of the screen/monitor.
	// _icon_index is the id of the icon that you want to display on the title bar.
	Fle_MainWindow(int _w, int _h, const char* _title = 0, int _icon_index = 101);
	// Description:
	// Destructor that destroys timer (if any) and other data.
	virtual ~Fle_MainWindow();

	// Description:
	// Function that pack widgets inside the window.
	virtual void begin() override;
	// Description:
	// Function that stop packing widgets inside the window.
	// If you call begin(), then must call end().
	virtual void end() override;

	// Description:
	// Function that must be called whenever there is a need to add widget on top of other widgets,
	// such as on top of menu bar, status bar, etc.
	virtual void beginTopArea();
	// Description:
	// Function that must be called whenever you call beginTopArea() function to stop adding widgets.
	virtual void endTopArea();

	// Description:
	// Function to resize the window by specifying the position, width and height.
	// Overridden function that will be called while resizing the window.
	virtual void resize(int _x, int _y, int _w, int _h) override;
	// Description:
	// Function to resize the window by specifying the width and height.
	// This function will not be called while resizing, only above function resize() does call.
	virtual void size(int _w, int _h) override;

	// Description:
	// Function to redraw/update the window.
	// Both update() and redraw() do the same work.
	virtual void redraw() override;
	// Description:
	// Overloaded function of redraw().
	// Both update() and redraw() do the same work.
	virtual void update() override;

	// Description:
	// Function to set the background color of the widget.
	void setBackgroundColor(uchar _red, uchar _green, uchar _blue);
	// Description:
	// Function to set the background color of the widget.
	void setBackgroundColor(Fl_Color _color);

	// Description:
	// Function to toggle (show/hide) the menu bar.
	void toggleMenuBar();
	// Description:
	// Function to toggle (show/hide) the top tool bar.
	void toggleTopToolBar();
	// Description:
	// Function to toggle (show/hide) the status bar.
	void toggleStatusBar();
	// Description:
	// Function to toggle (show/hide) the left bar.
	void toggleLeftToolBar();
	// Description:
	// Function to toggle (show/hide) the right bar.
	void toggleRightToolBar();

	// Description:
	// Function to update the contents of the window, such as toolbars, etc.
	virtual void updateGeometry();
	// Description:
	// Function to update the contents (position, width, height, etc.,) of the central area.
	// Whenever there is a change in menu bar, status bar, or central area, then call this function
	// to adjust the central area.
	void updateContents();

	// Description:
	// Function to set the left margin in pixels, 
	// meaning that the space (as border) on the left side of the central area.
	// default value is zero.
	void setLeftMargin(int _value) { m_leftmargin = _value; }
	// Description:
	// Function to get the left margin in pixels.
	int getLeftMargin() const { return m_leftmargin; }
	// Description:
	// Function to set the right margin in pixels, 
	// meaning that the space (as border) on the right side of the central area.
	// default value is zero.
	void setRightMargin(int _value) { m_rightmargin = _value; }
	// Description:
	// Function to get the right margin in pixels.
	int getRightMargin() const { return m_rightmargin; }
	// Description:
	// Function to set the top margin in pixels, 
	// meaning that the space (as border) at the top side of the central area.
	// default value is zero.
	void setTopMargin(int _value) { m_topmargin = _value; }
	// Description:
	// Function to get the top margin in pixels.
	int getTopMargin() const { return m_topmargin; }
	// Description:
	// Function to set the bottom margin in pixels, 
	// meaning that the space (as border) at the bottom side of the central area.
	// default value is zero.
	void setBottomMargin(int _value) { m_bottommargin = _value; }
	// Description:
	// Function to get the bottom margin in pixels.
	int getBottomMargin() const { return m_bottommargin; }

	// Function to set the box margins in pixels, 
	// meaning that the space (as border) on the sides of the central area.
	// default value is setMargins(0,0,0,0).
	void setMargins(int _left, int _right, int _top, int _bottom)
	{
		m_leftmargin = _left;
		m_rightmargin = _right;
		m_topmargin = _top;
		m_bottommargin = _bottom;
	}

	// Description:
	// Function to set fixed menubar height in pixels.
	void setMenuBarFixedHeight(int _h);
	// Description:
	// Function to get a pointer to menu bar.
	// You can hide() or show() the menu bar by calling both functions,
	// once you do it, don't forget to call updateContents() function to adjust the
	// central area.
	// By right clicking on the menu bar, a popup window will appear for toggling the
	// menu, top, right, left, and status bars.
	// Right click popup/menu items can be easily customized, 
	// see the following example that hides two of it's items from the popup.
	// Example:
	// getMenuBar()->getRightClickPopupItems()[0].show();	// show the 0'th indexed item which is "MenuBar".
	// getMenuBar()->getRightClickPopupItems()[1].hide();	// hide the 1'st indexed item which is "TopBar".
	// getMenuBar()->getRightClickPopupItems()[2].hide();	// hide the 2'nd indexed item which is "LeftBar".
	// getMenuBar()->getRightClickPopupItems()[3].hide();	// hide the 3'rd indexed item which is "RightBar".
	// getMenuBar()->getRightClickPopupItems()[4].show();	// show the 4'th indexed item which is "StatusBar".
	Fle_MenuBar* getMenuBar() const { return p_menubar; }

	// Description:
	// Function to set fixed menubar height in pixels.
	void setTopToolBarFixedHeight(int _h);
	// Description:
	// Function to get a pointer to menu bar.
	// You can hide() or show() the menu bar by calling both functions,
	// once you do it, don't forget to call updateContents() function to adjust the
	// central area.
	Fle_ToolBar* getTopToolBar() const { return p_toptoolbar; }

	// Description:
	// Function to set fixed width of the left bar in pixels.
	void setLeftToolBarFixedWidth(int _w);
	// Description:
	// Function to set a pointer to left toolbar.
	void setLeftToolBar(Fle_ToolBar* _p) { p_lefttoolbar = _p; }
	// Description:
	// Function to get a pointer to left toolbar.
	Fle_ToolBar* getLeftToolBar() const { return p_lefttoolbar; }
	// Description:
	// Function to set fixed width of the right bar in pixels.
	void setRightToolBarFixedWidth(int _w);
	// Description:
	// Function to get a pointer to right toolbar.
	// You can hide() or show() the menu bar by calling both functions,
	// once you do it, don't forget to call updateContents() function to adjust the
	// central area.
	Fle_ToolBar* getRightToolBar() const { return p_righttoolbar; }

	// Description:
	// Function to set statusbar height in pixels.
	void setStatusBarFixedHeight(int _h);
	// Description:
	// Function to get a pointer to status bar.
	// You can hide() or show() the status bar by calling both functions,
	// once you do it, don't forget to call updateContents() function to adjust the
	// central area.
	Fle_StatusBar* getStatusBar() const { return p_statusbar; }

	// Description:
	// Function to set a pointer to central widget of this main window.
	void setCentralWidget(Fle_Window* _w) { p_centralarea = _w; }
	// Description:
	// Function to get a pointer to central widget of this main window.
	Fle_Window* getCentralWindow() const { return p_centralarea; }

protected:
	// Description:
	// Overridden function to set the Ctr+Shift+m keys for toggling main menubar.
	virtual int keyPressEvent(int _key) override;	// keyboard key press events.

	// Description:
	// Embedded central area of the MainWindow.
	Fle_Window* p_centralarea;

	// Description:
	// Embedded main menubar at the top side of the window.
	Fle_MenuBar* p_menubar;
	// Description:
	// Embedded top toolbar.
	Fle_ToolBar* p_toptoolbar;
	// Description:
	// Embedded left toolbar at the left side of the window.
	Fle_ToolBar* p_lefttoolbar;
	// Description:
	// Embedded right toolbar at the right side of the window.
	Fle_ToolBar* p_righttoolbar;
	// Description:
	// Embedded statusbar at the bottom side of the window.
	Fle_StatusBar* p_statusbar;

	// Description:
	// margins for main window contents.
	int m_leftmargin;
	int m_rightmargin;
	int m_topmargin;
	int m_bottommargin;

private:
	// Description:
	// Callback function for the right click menu that provides toggle feature to show or hide
	// the tools bars, i.e., top tool bar, status bar, etc.
	static void rightClickMenuItem_cb(Fl_Widget* _w, void* _p);
	static void toggleMenuBar_cb(Fl_Widget* _w, void* _data);
	static void toggleTopToolBar_cb(Fl_Widget* _w, void* _data);
	static void toggleStatus_cb(Fl_Widget* _w, void* _data);
	static void toggleLeftToolBar_cb(Fl_Widget* _w, void* _data);
	static void toggleRightToolBar_cb(Fl_Widget* _w, void* _data);
};

}

#endif // Fle_MainWindow_h__