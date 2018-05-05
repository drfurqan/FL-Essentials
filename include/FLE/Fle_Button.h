#pragma once
#ifndef Fle_Button_h__
#define Fle_Button_h__

/*********************************************************************************
created:	2017/01/27   04:02AM
filename: 	Fle_Button.h
file base:	Fle_Button
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized button widget with some necessary functionalities that I don't
			find in Fl_Button. It works as normal button with additional toggle 
			feature and button icons.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <FL/Fl_Button.H>
#include <FL/Fl_Shared_Image.H>

#include <opencv2/opencv.hpp>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_Button : public Fl_Button
{
public:
	// Description:
	// 1st constructor to create a normal click-able button.
	// Default button style/type is box(Fl_Boxtype::FL_UP_BOX).
	// Background color can specified by the member function of color().
	// Selection color can specified by the member function of selection_color().
	Fle_Button(int _x, int _y, int _w, int _h, const char* _text);
	// Description:
	// 2nd constructor to create a toggled button with ON/OFF icons/images (*.png).
	// _icon_file_on will be used for ON state of the button, and
	// _icon_file_off will be used for OFF state.
	// Default button style/type is box(Fl_Boxtype::FL_NO_BOX).
	Fle_Button(int _x, int _y, int _w, int _h, const char* _icon_file_on, const char* _icon_file_off, cv::Size _size = cv::Size(32, 32));
	Fle_Button(int _x, int _y, int _w, int _h, Fl_RGB_Image* _icon_file_on, Fl_RGB_Image* _icon_file_off = 0, cv::Size _size = cv::Size(32, 32));
	// Description:
	// Destructor that releases the images.
	virtual ~Fle_Button();

	// Description:
	// Function to load/import icon/image files from disk.
	// _icon_file_on will be used for ON state of the button, and
	// _icon_file_off will be used for OFF state.
	// Specify initial state (ON or OFF) of the button using setOn() function.
	// {*.png, bmp, gif, jpg, etc.} image format is supported.
	// Default button style/type is box(Fl_Boxtype::FL_NO_BOX).
	bool loadIcons(const char* _icon_file_on, const char* _icon_file_off = 0, cv::Size _size = cv::Size(32, 32));
	bool loadIcons(Fl_RGB_Image* _icon_file_on, Fl_RGB_Image* _icon_file_off = 0, cv::Size _size = cv::Size(32, 32));

	// Description:
	// Function to set button state to ON.
	void setOn(bool _b) { m_ison = _b; }
	// Description:
	// Function that returns true if the button state is ON.
	bool isOn() const { return m_ison; }
	// Description:
	// Function that makes this button as toggled or non-toggled button. Meaning that one click on the button will change
	// it's state to ON, and then second click will require to change it's state to OFF.
	// If it's true, button will be toggled button, Meaning that one click on the button will change
	// it's state to ON, and then second click will require to change it's state to OFF.
	// If it's false, button state will be changed after releasing the mouse click button.
	// Default value is true.
	void setToggleEnabled(bool _b) { m_toggle = _b; }
	// Description:
	// Function that returns true if the button state is ON.
	bool isToggleEnabled() const { return m_toggle; }


	// Description:
	// Function to set minimum size of the widget.
	// Default value is cv::Size(1, 1).
	void setMinimumSize(const cv::Size& _size) { m_minsize = _size; }
	// Description:
	// Function to get minimum size of the widget.
	// Default value is cv::Size(1, 1).
	cv::Size getMinimumSize() const { return m_minsize; }
	// Description:
	// Function to set maximum size of the widget.
	// Widget will be expanded/resized to maximum size while resizing the parent window.
	// Default value is (Screen-Size + 10000000).
	void setMaximumSize(const cv::Size& _size) { m_maxsize = _size; }
	// Description:
	// Function to get maximum size of the widget.
	cv::Size getMaximumSize() const { return m_maxsize; }
	// Description:
	// Function to set widget as resize-able.
	// Default value is true, meaning that the widget will be resized while resizing the 
	// parent widget if it's true, otherwise widget will be fixed on false.
	void setResizeable(bool _b);

	// Description:
	// Function to set the fixed width of the widget.
	void setFixedWidth(int _w) { m_minsize.width = _w; m_maxsize.width = _w; }
	// Description:
	// Function to set the fixed height of the widget.
	void setFixedHeight(int _h) { m_minsize.height = _h; m_maxsize.height = _h; }

	// Description:
	// Function to set fixed position of the widget.
	// Meaning that if you stretch/expand/resize the parent window,
	// this widget will not be moved, it will
	// remain be fixed while resizing the parent window.
	// Default value is the constructor's x and y arguments.
	void setFixedPosition(const cv::Point& _size) { m_fixedpos = _size; }
	// Description:
	// Function to set fixed position of the widget.
	cv::Point getFixedPosition() const { return m_fixedpos; }
	// Description:
	// Function to set X coordinate as fixed. 
	// Widget won't be moved as specified by setFixedPosition() function while resizing the parent widget.
	// Default value is false;
	void setPosXFixed(bool _b) { m_isfixedx = _b; }
	// Description:
	// Function that returns true if X coordinate of the widget is fixed.
	bool isPosXFixed() const { return m_isfixedx; }
	// Description:
	// Function to set Y coordinate as fixed. Widget won't be moved while resizing the parent widget.
	// Widget won't be moved as specified by setFixedPosition() function while resizing the parent widget.
	// Default value is false;
	void setPosYFixed(bool _b) { m_isfixedy = _b; }
	// Description:
	// Function to set Y coordinate as fixed. Widget won't be moved while resizing the parent widget.
	// Default value is false;
	bool isPosYFixed() const { return m_isfixedy; }

	// Description:
	// Function to set the left margin in pixels, 
	// meaning that the space (as border) on the left side of the box.
	// default value is zero.
	void setLeftMargin(int _value) { m_leftmargin = _value; }
	// Description:
	// Function to get the left margin in pixels.
	int getLeftMargin() const { return m_leftmargin; }
	// Description:
	// Function to set the right margin in pixels, 
	// meaning that the space (as border) on the right side of the box.
	// default value is zero.
	void setRightMargin(int _value) { m_rightmargin = _value; }
	// Description:
	// Function to get the right margin in pixels.
	int getRightMargin() const { return m_rightmargin; }
	// Description:
	// Function to set the top margin in pixels, 
	// meaning that the space (as border) on the top side of the box.
	// default value is zero.
	void setTopMargin(int _value) { m_topmargin = _value; }
	// Description:
	// Function to get the top margin in pixels.
	int getTopMargin() const { return m_topmargin; }
	// Description:
	// Function to set the bottom margin in pixels, 
	// meaning that the space (as border) on the bottom side of the box.
	// default value is zero.
	void setBottomMargin(int _value) { m_bottommargin = _value; }
	// Description:
	// Function to get the bottom margin in pixels.
	int getBottomMargin() const { return m_bottommargin; }

	// Function to set the box margins in pixels, 
	// meaning that the space (as border) on the sides of the box.
	// default value is setMargins(0,0,0,0).
	void setMargins(int _left, int _right, int _top, int _bottom)
	{
		m_leftmargin = _left;
		m_rightmargin = _right;
		m_topmargin = _top;
		m_bottommargin = _bottom;
	}

protected:
	// Description:
	// Function to be called when close (top right) button is clicked (for internal use).
	virtual int handle(int _event) override;
	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// drawing FLTK widgets such as 
	// fl_rectf
	// fl_rect
	// fl_line
	// fl_loop
	// fl_polygon
	// fl_arc
	// fl_pie
	virtual void draw() override;
	// Description:
	// Overloaded function that is being called inside the draw() function.
	void draw(int _x, int _y, int _w, int _h);
	
	Fl_Shared_Image* p_on;
	Fl_Shared_Image* p_off;
	bool m_ison;
	bool m_toggle;

	int m_leftmargin;
	int m_rightmargin;
	int m_topmargin;
	int m_bottommargin;
	cv::Size m_minsize;
	cv::Size m_maxsize;
	cv::Point m_fixedpos;
	bool m_isfixedx;
	bool m_isfixedy;
};

}

#endif // Fle_Button_h__