/*********************************************************************************
created:	2017/01/30   09:42AM
filename: 	Fle_Layout.cpp
file base:	Fle_Layout
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Alternative vertical or horizontal layout to add/pack widgets.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Layout.h"
#include <iostream>

using namespace R3D;

/**************************************************************************/
/* General layout for packing widgets in vertical or horizontal direction.*/
/**************************************************************************/
Fle_Layout::Fle_Layout(int _x, int _y, int _w, int _h, Type _type, const char* _label) :
Fl_Pack(_x, _y, _w, _h, _label),
m_isauto(false)
{
	Fl_Pack::type(_type);	// horizontal or vertical packing of widgets
	if (_type == Fle_Layout::Type::HORIZONTAL) Fl_Pack::spacing(8);	// spacing between widgets
	else Fl_Pack::spacing(4);
	Fl_Pack::end();
}

Fle_Layout::~Fle_Layout()
{
}

int Fle_Layout::getGeometryWidth() const
{
	int width = 0;
	for (int i = 0; i < children(); i++)
		width += child(i)->w();
	return (width + (spacing() * children()) + 1);
}
int Fle_Layout::getGeometryHeight() const
{
	int height = 0;
	for (int i = 0; i < children(); i++)
		height += child(i)->h();
	return (height + (spacing() * children()) + 1);
}

void Fle_Layout::draw()
{
	if (m_isauto)
	{
		if (type() == Fle_Layout::Type::HORIZONTAL)
			size(getGeometryWidth(), Fl_Pack::h());
		else
			size(Fl_Pack::w(), getGeometryHeight());
	}

	Fl_Pack::draw();
}

/**************************************************************************/
/* Horizontal layout that start packing widgets from the most left side.  */
/**************************************************************************/
Fle_HLayout::Fle_HLayout(int _x, int _y, int _w, int _h, const char* _label) :
Fle_Layout(_x, _y, _w, _h, Fle_Layout::Type::HORIZONTAL, _label)
{
}
Fle_HLayout::~Fle_HLayout()
{
}

Fle_HLayoutL::Fle_HLayoutL(int _x, int _y, int _w, int _h, const char* _label) :
Fle_Window(_x, _y, _w, _h, _label)
{
	Fle_Window::begin();
	p_layout = new Fle_HLayout(0, 0, _w, _h);
	p_layout->end();
	Fle_Window::end();
}
Fle_HLayoutL::~Fle_HLayoutL()
{
}
void Fle_HLayoutL::begin()
{
	p_layout->begin();
}
void Fle_HLayoutL::end()
{
	p_layout->end();
	Fle_Window::end();
}
int Fle_HLayoutL::getGeometryWidth() const
{
	int width = 0;
	for (int i = 0; i < p_layout->children(); i++)
		width += p_layout->child(i)->w();
	return (width + (p_layout->spacing() * p_layout->children()));
}

Fle_HLayoutLR::Fle_HLayoutLR(int _x, int _y, int _w, int _h, const char* _label) :
Fle_Window(_x, _y, _w, _h, _label),
m_leftmargin(0),
m_rightmargin(0),
m_topmargin(0),
m_bottommargin(0)
{
	Fle_Window::begin();

	p_main = new Fle_HLayout(0, 0, _w, _h);
	p_main->color(fl_rgb_color(0, 122, 204));

	int right_side = 1;

	p_main->begin();
	p_left = new Fle_HLayoutL(0, 0, p_main->w() - right_side, p_main->h());
	p_left->setBackgroundColor(0, 122, 204);
	p_main->end();

	p_main->begin();
	p_right = new Fle_HLayoutL(0, 0, right_side, p_main->h());
	p_right->setBackgroundColor(0, 122, 204);
	p_main->end();

	p_main->resizable(p_left);

	Fle_Window::end();
}

Fle_HLayoutLR::~Fle_HLayoutLR()
{
}

void Fle_HLayoutLR::begin()
{
	endRight();
	p_left->begin();
}
void Fle_HLayoutLR::end()
{
	p_left->end();
	Fle_Window::end();
}
void Fle_HLayoutLR::beginLeft()
{
	endRight();
	p_left->begin();
}
void Fle_HLayoutLR::endLeft()
{
	p_left->end();
	Fle_Window::end();
}
void Fle_HLayoutLR::beginRight()
{
	endLeft();
	p_right->begin();
}
void Fle_HLayoutLR::endRight()
{
	p_right->end();
	Fle_Window::end();
}

void Fle_HLayoutLR::resize(int _x, int _y, int _w, int _h)
{
	Fle_Window::resize(_x, _y, _w, _h);
	p_left->size(_w - p_right->getGeometryWidth(), _h);
	p_right->size(p_right->getGeometryWidth(), _h);
}
void Fle_HLayoutLR::setBackgroundColor(uchar _red, uchar _green, uchar _blue) 
{ 
	p_main->color(fl_rgb_color(_red, _green, _blue));
	p_left->setBackgroundColor(_red, _green, _blue);
	p_right->setBackgroundColor(_red, _green, _blue);
	Fle_Window::setBackgroundColor(_red, _green, _blue);
}
Fl_Color Fle_HLayoutLR::getBackgroundColor() const 
{ 
	return p_left->getBackgroundColor();
}

void Fle_HLayoutLR::setLeftMargin(int _value)
{
	m_leftmargin = _value;
	p_main->resize(m_leftmargin, m_topmargin, Fle_Window::w() - m_leftmargin - m_rightmargin, Fle_Window::h() - m_topmargin - m_bottommargin);
}
void Fle_HLayoutLR::setRightMargin(int _value)
{
	m_rightmargin = _value;
	p_main->resize(m_leftmargin, m_topmargin, Fle_Window::w() - m_leftmargin - m_rightmargin, Fle_Window::h() - m_topmargin - m_bottommargin);
}
void Fle_HLayoutLR::setTopMargin(int _value)
{
	m_topmargin = _value;
	p_main->resize(m_leftmargin, m_topmargin, Fle_Window::w() - m_leftmargin - m_rightmargin, Fle_Window::h() - m_topmargin - m_bottommargin);
}
void Fle_HLayoutLR::setBottomMargin(int _value)
{
	m_bottommargin = _value;
	p_main->resize(m_leftmargin, m_topmargin, Fle_Window::w() - m_leftmargin - m_rightmargin, Fle_Window::h() - m_topmargin - m_bottommargin);
}
void Fle_HLayoutLR::setMargins(int _left, int _right, int _top, int _bottom)
{
	m_leftmargin = _left;
	m_rightmargin = _right;
	m_topmargin = _top;
	m_bottommargin = _bottom;
	p_main->resize(m_leftmargin, m_topmargin, Fle_Window::w() - m_leftmargin - m_rightmargin, Fle_Window::h() - m_topmargin - m_bottommargin);
}



/**************************************************************************/
/* Vertical layout that starts packing widgets from the top.               */
/**************************************************************************/
Fle_VLayout::Fle_VLayout(int _x, int _y, int _w, int _h, const char* _label) :
Fle_Layout(_x, _y, _w, _h, Fle_Layout::Type::VERTICAL, _label)
{
}
Fle_VLayout::~Fle_VLayout()
{
}

/**************************************************************************/
/* Vertical layout (Top) that starts packing widgets from the top.		  */
/**************************************************************************/
Fle_VLayoutT::Fle_VLayoutT(int _x, int _y, int _w, int _h, const char* _label) :
Fle_Window(_x, _y, _w, _h, _label)
{
	Fle_Window::begin();
	p_layout = new Fle_VLayout(0, 0, _w, _h);
	p_layout->end();
	Fle_Window::end();
}
Fle_VLayoutT::~Fle_VLayoutT()
{
}
void Fle_VLayoutT::begin()
{
	p_layout->begin();
}
void Fle_VLayoutT::end()
{
	p_layout->end();
	Fle_Window::end();
}
int Fle_VLayoutT::getGeometryHeight() const
{
	int height = 0;
	for (int i = 0; i < p_layout->children(); i++)
		height += p_layout->child(i)->h();
	return (height + (p_layout->spacing() * p_layout->children()));
}


Fle_VLayoutTB::Fle_VLayoutTB(int _x, int _y, int _w, int _h, const char* _label) :
Fle_Window(_x, _y, _w, _h, _label),
m_leftmargin(0),
m_rightmargin(0),
m_topmargin(0),
m_bottommargin(0)
{
	Fle_Window::begin();

	p_main = new Fle_VLayout(0, 0, _w, _h);
	p_main->color(fl_rgb_color(0, 122, 204));

	int bottom_height = 1;

	p_main->begin();
	p_top = new Fle_VLayoutT(0, 0, p_main->w(), p_main->h() - bottom_height);
	p_top->setBackgroundColor(0, 122, 204);
	p_main->end();

	p_main->begin();
	p_bottom = new Fle_VLayoutT(0, 0, p_main->w(), bottom_height);
	p_bottom->setBackgroundColor(0, 122, 204);
	p_main->end();

	p_main->resizable(p_top);

	Fle_Window::end();
}

Fle_VLayoutTB::~Fle_VLayoutTB()
{
}

void Fle_VLayoutTB::begin()
{
	endBottom();
	p_top->begin();
}
void Fle_VLayoutTB::end()
{
	p_top->end();
	Fle_Window::end();
}
void Fle_VLayoutTB::beginTop()
{
	endBottom();
	p_top->begin();
}
void Fle_VLayoutTB::endTop()
{
	p_top->end();
	Fle_Window::end();
}
void Fle_VLayoutTB::beginBottom()
{
	endTop();
	p_bottom->begin();
}
void Fle_VLayoutTB::endBottom()
{
	p_bottom->end();
	Fle_Window::end();
}

void Fle_VLayoutTB::resize(int _x, int _y, int _w, int _h)
{
	Fle_Window::resize(_x, _y, _w, _h);
	p_top->size(_w, _h - p_bottom->getGeometryHeight());
	p_bottom->size(_w, p_bottom->getGeometryHeight());
}
void Fle_VLayoutTB::setBackgroundColor(uchar _red, uchar _green, uchar _blue)
{
	p_main->color(fl_rgb_color(_red, _green, _blue));
	p_top->setBackgroundColor(_red, _green, _blue);
	p_bottom->setBackgroundColor(_red, _green, _blue);
	Fle_Window::setBackgroundColor(_red, _green, _blue);
}
Fl_Color Fle_VLayoutTB::getBackgroundColor() const
{
	return p_top->getBackgroundColor();
}

void Fle_VLayoutTB::setLeftMargin(int _value)
{
	m_leftmargin = _value;
	p_main->resize(m_leftmargin, m_topmargin, Fle_Window::w() - m_leftmargin - m_rightmargin, Fle_Window::h() - m_topmargin - m_bottommargin);
}
void Fle_VLayoutTB::setRightMargin(int _value)
{
	m_rightmargin = _value;
	p_main->resize(m_leftmargin, m_topmargin, Fle_Window::w() - m_leftmargin - m_rightmargin, Fle_Window::h() - m_topmargin - m_bottommargin);
}
void Fle_VLayoutTB::setTopMargin(int _value)
{
	m_topmargin = _value;
	p_main->resize(m_leftmargin, m_topmargin, Fle_Window::w() - m_leftmargin - m_rightmargin, Fle_Window::h() - m_topmargin - m_bottommargin);
}
void Fle_VLayoutTB::setBottomMargin(int _value)
{
	m_bottommargin = _value;
	p_main->resize(m_leftmargin, m_topmargin, Fle_Window::w() - m_leftmargin - m_rightmargin, Fle_Window::h() - m_topmargin - m_bottommargin);
}
void Fle_VLayoutTB::setMargins(int _left, int _right, int _top, int _bottom)
{
	m_leftmargin = _left;
	m_rightmargin = _right;
	m_topmargin = _top;
	m_bottommargin = _bottom;
	p_main->resize(m_leftmargin, m_topmargin, Fle_Window::w() - m_leftmargin - m_rightmargin, Fle_Window::h() - m_topmargin - m_bottommargin);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
Fle_VHLayout::Fle_VHLayout(int _x, int _y, int _w, int _h, const char* _label) :
Fle_Window(_x, _y, _w, _h, _label),
m_leftmargin(0),
m_rightmargin(0),
m_topmargin(0),
m_bottommargin(0)
{
	Fle_Window::begin();
	p_tblayout = new Fle_VLayoutTB(0, 0, _w, _h);
	p_tblayout->end();
	Fle_Window::end();
}

Fle_VHLayout::~Fle_VHLayout()
{
}

void Fle_VHLayout::begin()
{
	p_tblayout->beginTop();
}
void Fle_VHLayout::end()
{
	p_tblayout->endTop();
	Fle_Window::end();
}
void Fle_VHLayout::beginTop()
{
	p_tblayout->beginTop();
}
void Fle_VHLayout::endTop()
{
	p_tblayout->endTop();
	Fle_Window::end();
}
void Fle_VHLayout::beginBottom()
{
	p_tblayout->beginBottom();
}
void Fle_VHLayout::endBottom()
{
	p_tblayout->endBottom();
	Fle_Window::end();
}
void Fle_VHLayout::resize(int _x, int _y, int _w, int _h)
{
	Fle_Window::resize(_x, _y, _w, _h);
	p_tblayout->resize(m_leftmargin, m_topmargin, Fle_Window::w() - m_leftmargin - m_rightmargin, Fle_Window::h() - m_topmargin - m_bottommargin);
}

Fle_HLayoutLR* Fle_VHLayout::addLayoutLR(int _height, Position _pos)
{
	if (_pos == Fle_VHLayout::Position::AT_TOP)
	{
		p_tblayout->endBottom();
		p_tblayout->beginTop();
		Fle_HLayoutLR* ho = new Fle_HLayoutLR(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endTop();
		return ho;
	}
	else if (_pos == Fle_VHLayout::Position::AT_BOTTOM)
	{
		p_tblayout->endTop();
		p_tblayout->beginBottom();
		Fle_HLayoutLR* ho = new Fle_HLayoutLR(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endBottom();
		return ho;
	}
	return nullptr;
}
Fle_HLayoutL* Fle_VHLayout::addLayoutL(int _height, Position _pos)
{
	if (_pos == Fle_VHLayout::Position::AT_TOP)
	{
		p_tblayout->endBottom();
		p_tblayout->beginTop();
		Fle_HLayoutL* ho = new Fle_HLayoutL(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endTop();
		return ho;
	}
	else if (_pos == Fle_VHLayout::Position::AT_BOTTOM)
	{
		p_tblayout->endTop();
		p_tblayout->beginBottom();
		Fle_HLayoutL* ho = new Fle_HLayoutL(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endBottom();
		return ho;
	}
	return nullptr;
}
Fle_HLayout* Fle_VHLayout::addHLayout(int _height, Position _pos)
{
	if (_pos == Fle_VHLayout::Position::AT_TOP)
	{
		p_tblayout->endBottom();
		p_tblayout->beginTop();
		Fle_HLayout* ho = new Fle_HLayout(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endTop();
		return ho;
	}
	else if (_pos == Fle_VHLayout::Position::AT_BOTTOM)
	{
		p_tblayout->endTop();
		p_tblayout->beginBottom();
		Fle_HLayout* ho = new Fle_HLayout(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endBottom();
		return ho;
	}
	return nullptr;
}


Fle_VLayoutTB* Fle_VHLayout::addLayoutTB(int _height, Position _pos)
{
	if (_pos == Fle_VHLayout::Position::AT_TOP)
	{
		p_tblayout->endBottom();
		p_tblayout->beginTop();
		Fle_VLayoutTB* ho = new Fle_VLayoutTB(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endTop();
		return ho;
	}
	else if (_pos == Fle_VHLayout::Position::AT_BOTTOM)
	{
		p_tblayout->endTop();
		p_tblayout->beginBottom();
		Fle_VLayoutTB* ho = new Fle_VLayoutTB(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endBottom();
		return ho;
	}
	return nullptr;
}

Fle_VLayoutT* Fle_VHLayout::addLayoutT(int _height, Position _pos)
{
	if (_pos == Fle_VHLayout::Position::AT_TOP)
	{
		p_tblayout->endBottom();
		p_tblayout->beginTop();
		Fle_VLayoutT* ho = new Fle_VLayoutT(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endTop();
		return ho;
	}
	else if (_pos == Fle_VHLayout::Position::AT_BOTTOM)
	{
		p_tblayout->endTop();
		p_tblayout->beginBottom();
		Fle_VLayoutT* ho = new Fle_VLayoutT(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endBottom();
		return ho;
	}
	return nullptr;
}
Fle_VLayout* Fle_VHLayout::addVLayout(int _height, Position _pos)
{
	if (_pos == Fle_VHLayout::Position::AT_TOP)
	{
		p_tblayout->endBottom();
		p_tblayout->beginTop();
		Fle_VLayout* ho = new Fle_VLayout(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endTop();
		return ho;
	}
	else if (_pos == Fle_VHLayout::Position::AT_BOTTOM)
	{
		p_tblayout->endTop();
		p_tblayout->beginBottom();
		Fle_VLayout* ho = new Fle_VLayout(0, 0, p_tblayout->w(), _height);
		ho->end();
		p_tblayout->endBottom();
		return ho;
	}
	return nullptr;
}
