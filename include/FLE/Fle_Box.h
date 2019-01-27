#pragma once
#ifndef Fle_Box_h__
#define Fle_Box_h__

/*********************************************************************************
created:	2017/01/27   04:02AM
filename: 	Fle_Box.h
file base:	Fle_Box
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized box widget with some necessary functionalities that I don't
			find in Fl_Box. setImage() method is thread-safe, you can easily update
			the image in another thread.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ImageWidget.h>
#include <FLE/Fle_Font.h>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_Box : public Fle_ImageWidget
{
public:
	// Description:
	// Constructor to create a box widget inside the parent window.
	// Default box style/type is Fl_Boxtype::FL_NO_BOX.
	// Default box position is move-able with setPositionFixed(false).
	// Default box width is expand-able with setWidthFixed(false).
	// Default box height is expand-able with setHeightFixed(false).
	// Default margins are zero with setMargins(0,0,0,0).
	// By default Box_Widget does not automatically resizes itself to fit the text with setFitToTextEnabled(false). 
	// By default, image draw type is ImageDrawType::Fit.
	// Note: zooming only wors with ImageDrawType::Center.
	Fle_Box(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor to release data.
	virtual ~Fle_Box();

	// Description:
	// Function to set or add text inside the box.
	// In case of background image, then text will be displayed over the image.
	void setText(const std::string& _text) { m_text = _text; }
	// Description:
	// Function to get the assigned text.
	std::string getText() const { return m_text; }
	// Description:
	// Function to show/hide text, if there is any text assigned by setText() function.
	void setTextEnabled(bool _b) { m_istext = _b; }
	// Description:
	// Function that returns true if text is visible.
	bool isTextEnabled() const { return m_istext; }
	// Description:
	// Function to set the text properties, it's size, color, type, alignment, etc. etc.
	void setFont(Fle_Font _font) { m_font = _font; }
	// Description:
	// Function to get a pointer to font (text properties such as size, color, type, alignment, etc. etc.).
	Fle_Font* getFont() { return &m_font; }
	// Description:
	// Function to set auto-resizing of the box enabled.
	// Box_Widget automatically resizes itself to fit the text if it's true. 
	// Default value is false.
	void setFitToTextEnabled(bool _b) { m_autoSize = _b; }
	// Description:
	// Function that returns true if auto-resizing of the box is enabled.
	bool isFitToTextEnabled() const { return m_autoSize; }

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

	// Description:
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

	// Description:
	// Function to set the position and size of the rubber band.
	void setRubberBand(const cv::Rect& _roi) { m_border_roi = _roi; }
	// Description:
	// Function to get the position and size of the rubber band.
	cv::Rect getRubberBand() const { return m_border_roi; }
	// Description:
	// Function to set rubber band enabled.
	void setRubberBandEnabled(const bool _b) { m_isroi = _b; }
	// Description:
	// Function that returns true if the rubber band is enabled.
	bool isRubberBandEnabled() const { return m_isroi; }
	// Description:
	// Function to set the rubber band color.
	void setRubberBandColor(Fl_Color _c) { m_border_color = _c; }
	// Description:
	// Function to get the rubber band color.
	Fl_Color getRubberBandColor() const { return m_border_color; }

protected:
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
	void drawText(int _x, int _y, int _w, int _h);
	
	Fle_Font m_font;
	bool m_istext;
	std::string m_text;
	bool m_autoSize;

	Fl_Boxtype m_type;
	Fl_Color m_boxcolor;

	int m_leftmargin;
	int m_rightmargin;
	int m_topmargin;
	int m_bottommargin;
	cv::Size m_minsize;
	cv::Size m_maxsize;
	cv::Point m_fixedpos;
	bool m_isfixedx;
	bool m_isfixedy;
	bool m_isroi;
	cv::Rect m_border_roi;
	Fl_Color m_border_color;
};

}

#endif // Fle_Box_h__