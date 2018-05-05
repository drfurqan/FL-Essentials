#pragma once
#ifndef Fle_Layout_h__
#define Fle_Layout_h__

/*********************************************************************************
created:	2017/01/30   09:42AM
filename: 	Fle_Layout.h
file base:	Fle_Layout
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Alternative vertical or horizontal layouts to add/pack widgets.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>
#include <FLE/Fle_Window.h>

#include <FL/Fl_Pack.H>
#include <FL/Fl_Box.H>

#include <vector>

namespace R3D
{

/**************************************************************************/
/* General layout for packing widgets in vertical or horizontal direction.*/
/**************************************************************************/
class FL_ESSENTIALS_EXPORT Fle_Layout : public Fl_Pack
{
public:

	// Description:
	// Alignment type meaning widgets should added vertical or horizontal.
	enum Type
	{
		VERTICAL = 0,
		HORIZONTAL = 1
	};

	// Description:
	// Constructor to create a layout to pack widgets in vertical or horizontal direction.
	Fle_Layout(int _x, int _y, int _w, int _h, Type _type = Fle_Layout::Type::HORIZONTAL, const char* _label = 0);
	// Description:
	// Destructor that destroys the data.
	virtual ~Fle_Layout();

	// Description:
	// Function that returns the total width of the widgets that this layout contains.
	int getGeometryWidth() const;
	// Description:
	// Function that returns the total height of the widgets that this layout contains.
	int getGeometryHeight() const;

	// Description:
	// Function that sets true/false to automatically adjust the layout size.
	void setAutoSizeEnabled(bool _auto_width) { m_isauto = _auto_width; }
	// Description:
	// Function that returns true automatically layout adjusted is enabled.
	bool isAutoSizeEnabled() const { return m_isauto; }

protected:
	virtual void draw() override;

	bool m_isauto;
};

/**************************************************************************/
/* Horizontal layout that start packing widgets from the most left side.  */
/**************************************************************************/
class FL_ESSENTIALS_EXPORT Fle_HLayout : public Fle_Layout
{
public:
	// Description:
	// Constructor to create a horizontal layout to pack widgets.
	Fle_HLayout(int _x, int _y, int _w, int _h, const char* _label = 0);

	// Description:
	// Destructor that destroys the data.
	virtual ~Fle_HLayout();
};

/**************************************************************************/
/* Horizontal layout that start packing widgets from the most left side.  */
/**************************************************************************/
class FL_ESSENTIALS_EXPORT Fle_HLayoutL : public Fle_Window
{
public:
	// Description:
	// Constructor to create a window with Vertical-Horizontal layout which 
	// can add/pack layouts/widgets in horizontal as well as in vertical directions.
	// Always remember that if you want to make child windows resizeable,
	// make this layout as resizeable, like l->resizable(l).
	Fle_HLayoutL(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor that destroys the data.
	virtual ~Fle_HLayoutL();

	// Description:
	// Function that should be called to add widgets inside this layout.
	virtual void begin() override;
	// Description:
	// Function that stop packing widgets inside this layout.
	// If you call begin(), then must call end().
	virtual void end() override;

	// Description:
	// Overridden function to set the spacing between widgets.
	virtual void setSpacing(int _pixels) { p_layout->spacing(_pixels); }
	// Description:
	// Overridden function to set the spacing between widgets.
	virtual int getSpacing() const { return p_layout->spacing(); }

	// Description:
	// Function that returns the total width of the widgets that this layout contains.
	int getGeometryWidth() const;

	// Description:
	// Function to set a pointer to main layout.
	void setCentralLayout(Fle_HLayout* _p) { p_layout = _p; }
	// Description:
	// Function to get a pointer to main layout.
	Fle_HLayout* getCentralLayout() const { return p_layout; }

protected:
	Fle_HLayout* p_layout;
};

/**************************************************************************/
/* Left-Right Horizontal layout that can add/pack widgets at the most left*/
/* as well as the most right side.										  */
/**************************************************************************/
class FL_ESSENTIALS_EXPORT Fle_HLayoutLR : public Fle_Window
{
public:
	// Description:
	// Constructor to create a window with Vertical-Horizontal layout which 
	// can add/pack layouts/widgets in horizontal as well as in vertical directions.
	Fle_HLayoutLR(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor that destroys the data.
	virtual ~Fle_HLayoutLR();

	// Description:
	// Function that should be called to add/pack layouts/widgets at top.
	virtual void begin() override;
	// Description:
	// Function that stop adding/packing layouts/widgets at top.
	// If you call begin(), then must call end().
	virtual void end() override;

	// Description:
	// Function that should be called to add/pack layouts/widgets at top.
	virtual void beginLeft();
	// Description:
	// Function that stop adding/packing layouts/widgets at top.
	// If you call beginTop(), then must call endTop().
	virtual void endLeft();
	// Description:
	// Function that should be called to add/pack layouts/widgets at bottom.
	virtual void beginRight();
	// Description:
	// Function that stop adding/packing layouts/widgets at bottom.
	// If you call beginBottom(), then must call endBottom().
	virtual void endRight();

	// Description:
	// Overridden function that called while resizing this layout.
	virtual void resize(int _x, int _y, int _w, int _h) override;

	// Description:
	// Function to set the background color of the widget.
	void setBackgroundColor(uchar _red, uchar _green, uchar _blue);
	// Description:
	// Function to set the background color of the widget.
	void setBackgroundColor(Fl_Color _color);
	// Description:
	// Function to get the background color of the widget.
	Fl_Color getBackgroundColor() const;

	// Description:
	// Function to set the left margin in pixels, 
	// meaning that the space or border on the left side of the layout.
	// default value is zero.
	void setLeftMargin(int _value);
	// Description:
	// Function to get the left margin in pixels.
	int getLeftMargin() const { return m_leftmargin; }
	// Description:
	// Function to set the right margin in pixels, 
	// meaning that the space or border on the right side of the layout.
	// default value is zero.
	void setRightMargin(int _value);
	// Description:
	// Function to get the right margin in pixels.
	int getRightMargin() const { return m_rightmargin; }
	// Description:
	// Function to set the top margin in pixels, 
	// meaning that the space or border on the top side of the layout.
	// default value is zero.
	void setTopMargin(int _value);
	// Description:
	// Function to get the top margin in pixels.
	int getTopMargin() const { return m_topmargin; }
	// Description:
	// Function to set the bottom margin in pixels, 
	// meaning that the space or border on the bottom side of the box.
	// default value is zero.
	void setBottomMargin(int _value);
	// Description:
	// Function to get the bottom margin in pixels.
	int getBottomMargin() const { return m_bottommargin; }

	// Description:
	// Function to set the space margins in pixels, 
	// meaning that the spaces or borders on the sides of the layout.
	// default value is setMargins(0,0,0,0).
	void setMargins(int _left, int _right, int _top, int _bottom);

	// Description:
	// Function to set a pointer to main layout.
	void setCentralLayout(Fle_HLayout* _p) { p_main = _p; }
	// Description:
	// Function to get a pointer to main layout.
	Fle_HLayout* getCentralLayout() const { return p_main; }
	// Description:
	// Function to set a pointer to top layout.
	void setLeftLayout(Fle_HLayoutL* _p) { p_left = _p; }
	// Description:
	// Function to get a pointer to top layout.
	Fle_HLayoutL* getLeftLayout() const { return p_left; }
	// Description:
	// Function to set a pointer to top layout.
	void setRightLayout(Fle_HLayoutL* _p) { p_right = _p; }
	// Description:
	// Function to get a pointer to bottom layout.
	Fle_HLayoutL* getRightLayout() const { return p_right; }

protected:
	Fle_HLayout* p_main;
	Fle_HLayoutL* p_left;
	Fle_HLayoutL* p_right;

	int m_leftmargin;
	int m_rightmargin;
	int m_topmargin;
	int m_bottommargin;
};

/**************************************************************************/
/* Vertical layout that starts packing widgets from the top.			  */
/**************************************************************************/
class FL_ESSENTIALS_EXPORT Fle_VLayout : public Fle_Layout
{
public:
	// Description:
	// Constructor to create a vertical layout to pack widgets.
	Fle_VLayout(int _x, int _y, int _w, int _h, const char* _label = 0);

	// Description:
	// Destructor that destroys the data.
	virtual ~Fle_VLayout();
};

/**************************************************************************/
/* Vertical layout (Top) that starts packing widgets from the top.		  */
/**************************************************************************/
class FL_ESSENTIALS_EXPORT Fle_VLayoutT : public Fle_Window
{
public:
	// Description:
	// Constructor to create a window with Vertical-Horizontal layout which 
	// can add/pack layouts/widgets in horizontal as well as in vertical directions.
	Fle_VLayoutT(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor that destroys the data.
	virtual ~Fle_VLayoutT();

	// Description:
	// Function that should be called to add widgets inside this layout.
	virtual void begin() override;
	// Description:
	// Function that stop packing widgets inside this layout.
	// If you call begin(), then must call end().
	virtual void end() override;

	// Description:
	// Overridden function to set the spacing between widgets.
	virtual void setSpacing(int _pixels) { p_layout->spacing(_pixels); }
	// Description:
	// Overridden function to set the spacing between widgets.
	virtual int getSpacing() const { return p_layout->spacing(); }

	// Description:
	// Function that returns the total height of the widgets that this layout contains.
	int getGeometryHeight() const;

	// Description:
	// Function to set a pointer to main layout.
	void setCentralLayout(Fle_VLayout* _p) { p_layout = _p; }
	// Description:
	// Function to get a pointer to main layout.
	Fle_VLayout* getCentralLayout() const { return p_layout; }

protected:
	Fle_VLayout* p_layout;
};

/**************************************************************************/
/* Top-Bottom Vertical layout that can add/pack widgets at top as well as */
/* at bottom of this layout.											  */
/**************************************************************************/
class FL_ESSENTIALS_EXPORT Fle_VLayoutTB : public Fle_Window
{
public:
	// Description:
	// Constructor to create a window with Vertical-Horizontal layout which 
	// can add/pack layouts/widgets in horizontal as well as in vertical directions.
	Fle_VLayoutTB(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor that destroys the data.
	virtual ~Fle_VLayoutTB();

	// Description:
	// Function that should be called to add/pack layouts/widgets at top.
	virtual void begin() override;
	// Description:
	// Function that stop adding/packing layouts/widgets at top.
	// If you call begin(), then must call end().
	virtual void end() override;

	// Description:
	// Function that should be called to add/pack layouts/widgets at top.
	virtual void beginTop();
	// Description:
	// Function that stop adding/packing layouts/widgets at top.
	// If you call beginTop(), then must call endTop().
	virtual void endTop();
	// Description:
	// Function that should be called to add/pack layouts/widgets at bottom.
	virtual void beginBottom();
	// Description:
	// Function that stop adding/packing layouts/widgets at bottom.
	// If you call beginBottom(), then must call endBottom().
	virtual void endBottom();

	// Description:
	// Overridden function that called while resizing this layout.
	virtual void resize(int _x, int _y, int _w, int _h) override;

	// Description:
	// Function to set the background color of the widget.
	void setBackgroundColor(uchar _red, uchar _green, uchar _blue);
	// Description:
	// Function to set the background color of the widget.
	void setBackgroundColor(Fl_Color _color);
	// Description:
	// Function to get the background color of the widget.
	Fl_Color getBackgroundColor() const;

	// Description:
	// Function to set the left margin in pixels, 
	// meaning that the space or border on the left side of the layout.
	// default value is zero.
	void setLeftMargin(int _value);
	// Description:
	// Function to get the left margin in pixels.
	int getLeftMargin() const { return m_leftmargin; }
	// Description:
	// Function to set the right margin in pixels, 
	// meaning that the space or border on the right side of the layout.
	// default value is zero.
	void setRightMargin(int _value);
	// Description:
	// Function to get the right margin in pixels.
	int getRightMargin() const { return m_rightmargin; }
	// Description:
	// Function to set the top margin in pixels, 
	// meaning that the space or border on the top side of the layout.
	// default value is zero.
	void setTopMargin(int _value);
	// Description:
	// Function to get the top margin in pixels.
	int getTopMargin() const { return m_topmargin; }
	// Description:
	// Function to set the bottom margin in pixels, 
	// meaning that the space or border on the bottom side of the box.
	// default value is zero.
	void setBottomMargin(int _value);
	// Description:
	// Function to get the bottom margin in pixels.
	int getBottomMargin() const { return m_bottommargin; }

	// Description:
	// Function to set the space margins in pixels, 
	// meaning that the spaces or borders on the sides of the layout.
	// default value is setMargins(0,0,0,0).
	void setMargins(int _left, int _right, int _top, int _bottom);

	// Description:
	// Function to set a pointer to main layout.
	void setCentralLayout(Fle_VLayout* _p) { p_main = _p; }
	// Description:
	// Function to get a pointer to main layout.
	Fle_VLayout* getCentralLayout() const { return p_main; }
	// Description:
	// Function to set a pointer to top layout.
	void setTopLayout(Fle_VLayoutT* _p) { p_top = _p; }
	// Description:
	// Function to get a pointer to top layout.
	Fle_VLayoutT* getTopLayout() const { return p_top; }
	// Description:
	// Function to set a pointer to top layout.
	void setBottomLayout(Fle_VLayoutT* _p) { p_bottom = _p; }
	// Description:
	// Function to get a pointer to bottom layout.
	Fle_VLayoutT* getBottomLayout() const { return p_bottom; }

protected:
	Fle_VLayout* p_main;
	Fle_VLayoutT* p_top;
	Fle_VLayoutT* p_bottom;

	int m_leftmargin;
	int m_rightmargin;
	int m_topmargin;
	int m_bottommargin;
};

/**************************************************************************/
/* Vertical-Horizontal layout that can add/pack layouts/widgets in        */
/* horizontal as well as in vertical directions.						  */
/**************************************************************************/
class FL_ESSENTIALS_EXPORT Fle_VHLayout : public Fle_Window
{
public:
	// Description:
	// Constructor to create a window with Vertical-Horizontal layout which 
	// can add/pack layouts/widgets in horizontal as well as in vertical directions.
	Fle_VHLayout(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor that destroys the data.
	virtual ~Fle_VHLayout();

	// Description:
	// Function that should be called to add/pack layouts/widgets at top.
	virtual void begin() override;
	// Description:
	// Function that stop adding/packing layouts/widgets at top.
	// If you call begin(), then must call end().
	virtual void end() override;

	// Description:
	// Function that should be called to add/pack layouts/widgets at top.
	virtual void beginTop();
	// Description:
	// Function that stop adding/packing layouts/widgets at top.
	// If you call beginTop(), then must call endTop().
	virtual void endTop();
	// Description:
	// Function that should be called to add/pack layouts/widgets at bottom.
	virtual void beginBottom();
	// Description:
	// Function that stop adding/packing layouts/widgets at bottom.
	// If you call beginBottom(), then must call endBottom().
	virtual void endBottom();

	// Description:
	// Overridden function that called while resizing this layout.
	virtual void resize(int _x, int _y, int _w, int _h) override;

	// Description:
	// Function to set the left margin in pixels, 
	// meaning that the space or border on the left side of the layout.
	// default value is zero.
	void setLeftMargin(int _value) { m_leftmargin = _value; }
	// Description:
	// Function to get the left margin in pixels.
	int getLeftMargin() const { return m_leftmargin; }
	// Description:
	// Function to set the right margin in pixels, 
	// meaning that the space or border on the right side of the layout.
	// default value is zero.
	void setRightMargin(int _value) { m_rightmargin = _value; }
	// Description:
	// Function to get the right margin in pixels.
	int getRightMargin() const { return m_rightmargin; }
	// Description:
	// Function to set the top margin in pixels, 
	// meaning that the space or border on the top side of the layout.
	// default value is zero.
	void setTopMargin(int _value) { m_topmargin = _value; }
	// Description:
	// Function to get the top margin in pixels.
	int getTopMargin() const { return m_topmargin; }
	// Description:
	// Function to set the bottom margin in pixels, 
	// meaning that the space or border on the bottom side of the box.
	// default value is zero.
	void setBottomMargin(int _value) { m_bottommargin = _value; }
	// Description:
	// Function to get the bottom margin in pixels.
	int getBottomMargin() const { return m_bottommargin; }

	// Function to set the space margins in pixels, 
	// meaning that the spaces or borders on the sides of the layout.
	// default value is setMargins(0,0,0,0).
	void setMargins(int _left, int _right, int _top, int _bottom)
	{
		m_leftmargin = _left;
		m_rightmargin = _right;
		m_topmargin = _top;
		m_bottommargin = _bottom;
	}

	// Description:
	// Position for Left-Right Horizontal layout to be added at Top or Bottom of this layout. 
	enum class Position
	{
		AT_TOP = 0,
		AT_BOTTOM
	};
	// Description:
	// Function that adds/packs Left-Right Horizontal layout to this layout.
	// Left-Right Horizontal layout can add/pack widgets at the most left
	// as well as the most right side.
	// Layout can be added at Top or Bottom by specifying the Layout Position.
	Fle_HLayoutLR* addLayoutLR(int _height, Position _pos = Position::AT_TOP);
	// Description:
	// Function that adds/packs Left Horizontal layout to this layout.
	// Left Horizontal layout that start packing widgets from the most left side.
	// Layout can be added at Top or Bottom by specifying the Layout Position.
	Fle_HLayoutL* addLayoutL(int _height, Position _pos = Position::AT_TOP);
	// Description:
	// Function that adds/packs Horizontal layout to this layout.
	// Horizontal layout that start packing widgets from the most left side.
	// Layout can be added at Top or Bottom by specifying the Layout Position.
	Fle_HLayout* addHLayout(int _height, Position _pos = Position::AT_TOP);

	// Description:
	// Function that adds/packs Top-Bottom Vertical layout to this layout.
	// Top-Bottom Vertical layout can add/pack widgets at top as well as
	// at bottom of this layout.
	// Layout can be added at Top or Bottom by specifying the Layout Position.
	Fle_VLayoutTB* addLayoutTB(int _height, Position _pos = Position::AT_TOP);
	// Description:
	// Function that adds/packs Top Vertical layout to this layout.
	// Top Vertical layout that starts packing widgets from the top.
	// Layout can be added at Top or Bottom by specifying the Layout Position.
	Fle_VLayoutT* addLayoutT(int _height, Position _pos = Position::AT_TOP);
	// Description:
	// Function that adds/packs Vertical layout to this layout.
	// Vertical layout that starts packing widgets from the top.
	// Layout can be added at Top or Bottom by specifying the Layout Position.
	Fle_VLayout* addVLayout(int _height, Position _pos = Position::AT_TOP);

	// Description:
	// Function to get a pointer to the main layout of this window.
	Fle_VLayoutTB* getCentralLayout() const { return p_tblayout; }

protected:
	Fle_VLayoutTB* p_tblayout;

	int m_leftmargin;
	int m_rightmargin;
	int m_topmargin;
	int m_bottommargin;
};

}

#endif // Fle_Layout_h__