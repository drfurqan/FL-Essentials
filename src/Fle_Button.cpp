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
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Button.h>
#include <FLE/Fle_MessageBox.h>

#include <FL/Fl.H>
#include <FL/fl_draw.H>

using namespace R3D;

Fle_Button::Fle_Button(int _x, int _y, int _w, int _h, const char* _text) :
Fl_Button(_x, _y, _w, _h, _text),
m_ison(true),
m_toggle(true),
p_on(nullptr),
p_off(nullptr),
m_leftmargin(0),
m_rightmargin(0),
m_topmargin(0),
m_bottommargin(0),
m_minsize(cv::Size(1, 1)),
m_maxsize(cv::Size(Fl::w() + 10000000, Fl::h() + 10000000)),
m_isfixedx(false),
m_isfixedy(false),
m_fixedpos(cv::Point(_x, _y))
{
	box(_FL_GLEAM_UP_BOX);
	align(FL_ALIGN_WRAP | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
}
Fle_Button::Fle_Button(int _x, int _y, int _w, int _h, const char* _icon_file_on, const char* _icon_file_off, cv::Size _size) :
Fl_Button(_x, _y, _w, _h, 0),
m_ison(true),
m_toggle(true),
p_on(nullptr),
p_off(nullptr),
m_leftmargin(0),
m_rightmargin(0),
m_topmargin(0),
m_bottommargin(0),
m_minsize(cv::Size(1, 1)),
m_maxsize(cv::Size(Fl::w() + 10000000, Fl::h() + 10000000)),
m_isfixedx(false),
m_isfixedy(false),
m_fixedpos(cv::Point(_x, _y))
{
	box(Fl_Boxtype::FL_FLAT_BOX);
	align(FL_ALIGN_WRAP | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	if(loadIcons(_icon_file_on, _icon_file_off, _size))
		align(FL_ALIGN_WRAP | FL_ALIGN_CENTER | FL_ALIGN_BOTTOM | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
}
Fle_Button::Fle_Button(int _x, int _y, int _w, int _h, Fl_RGB_Image* _icon_file_on, Fl_RGB_Image* _icon_file_off, cv::Size _size) :
	Fl_Button(_x, _y, _w, _h, 0),
	m_ison(true),
	m_toggle(true),
	p_on(nullptr),
	p_off(nullptr),
	m_leftmargin(0),
	m_rightmargin(0),
	m_topmargin(0),
	m_bottommargin(0),
	m_minsize(cv::Size(1, 1)),
	m_maxsize(cv::Size(Fl::w() + 10000000, Fl::h() + 10000000)),
	m_isfixedx(false),
	m_isfixedy(false),
	m_fixedpos(cv::Point(_x, _y))
{
	box(Fl_Boxtype::FL_FLAT_BOX);
	align(FL_ALIGN_WRAP | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	if (loadIcons(_icon_file_on, _icon_file_off, _size))
		align(FL_ALIGN_WRAP | FL_ALIGN_CENTER | FL_ALIGN_BOTTOM | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
}

Fle_Button::~Fle_Button()
{
	if (p_on != nullptr)
	{
		p_on->release();
		p_on = nullptr;
	}
	if (p_off != nullptr)
	{
		p_off->release();
		p_off = nullptr;
	}
}

bool Fle_Button::loadIcons(const char* _icon_file_on, const char* _icon_file_off, cv::Size _size)
{
	try
	{
		if (p_on != nullptr)
		{
			p_on->release();
			p_on = nullptr;
		}
		if (p_off != nullptr)
		{
			p_off->release();
			p_off = nullptr;
		}

		if (_icon_file_on)
		{
			p_on = Fl_Shared_Image::get(_icon_file_on, _size.width, _size.height);
			if (p_on == nullptr) { /*Fle_MessageBox::Error("Could not load ON state icon!");*/ }
		}
		if (_icon_file_off)
		{
			p_off = Fl_Shared_Image::get(_icon_file_off, _size.width, _size.height);
			if (p_off == nullptr) { /*Fle_MessageBox::Error("Could not load OFF state icon!");*/ };
		}

		if (p_on)
		{
			align(FL_ALIGN_WRAP | FL_ALIGN_CENTER | FL_ALIGN_BOTTOM | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
			return true;
		}
	}
	catch (cv::Exception& _ex)
	{
		Fle_MessageBox::Error("Something went wrong on loading PNG button images/icons.!");
		std::cout << "Exception reading image from disk: %s\n" << _ex.what();
	}
	return false;
}
bool Fle_Button::loadIcons(Fl_RGB_Image* _icon_file_on, Fl_RGB_Image* _icon_file_off, cv::Size _size)
{
	try
	{
		if (p_on != nullptr)
		{
			p_on->release();
			p_on = nullptr;
		}
		if (p_off != nullptr)
		{
			p_off->release();
			p_off = nullptr;
		}

		if (_icon_file_on)
		{
			p_on = Fl_Shared_Image::get(_icon_file_on);
			if (_icon_file_on->w() != _size.width || _icon_file_on->h() != _size.height)
				p_on->scale(_size.width, _size.height, 1);
			if (p_on == nullptr) { /*Fle_MessageBox::Error("Could not load ON state icon!");*/ }
		}
		if (_icon_file_off)
		{
			p_off = Fl_Shared_Image::get(_icon_file_off);
			if (_icon_file_off->w() != _size.width || _icon_file_off->h() != _size.height)
				p_off->scale(_size.width, _size.height, 1);
			if (p_off == nullptr) { /*Fle_MessageBox::Error("Could not load OFF state icon!");*/ };
		}

		if (p_on)
		{
			align(FL_ALIGN_WRAP | FL_ALIGN_CENTER | FL_ALIGN_BOTTOM | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
			return true;
		}
	}
	catch (cv::Exception& _ex)
	{
		Fle_MessageBox::Error("Something went wrong on loading PNG button images/icons.!");
		std::cout << "Exception reading image from disk: %s\n" << _ex.what();
	}
	return false;
}

int Fle_Button::handle(int _event)
{
	switch (_event)
	{
	case FL_PUSH:
		clear_visible_focus();
		if (!m_toggle)
			m_ison = false;
		break;
	case FL_RELEASE:
		// if mouse is inside the box, then update the image.
		if (Fl::event_x() >= x() && Fl::event_x() < (x() + w()) &&
			Fl::event_y() >= y() && Fl::event_y() < (y() + h()))
		{
			if (m_toggle)
				m_ison = !m_ison;
			else
				m_ison = true;
		}
		break;
	default:
		break;
	}
	return Fl_Button::handle(_event);		// pass other events to the base class...
}

void Fle_Button::setResizeable(bool _b)
{
	if (_b)
	{
		m_minsize = cv::Size(1, 1);
		m_maxsize = cv::Size(Fl::w() + 10000000, Fl::h() + 10000000);
	}
	else
	{
		m_maxsize.width = Fl_Button::w();
		m_maxsize.height = Fl_Button::h();
		m_minsize = m_maxsize;
	}
}

void Fle_Button::draw()
{
	if (type() == FL_HIDDEN_BUTTON) return;

	if (m_isfixedx) Fl_Button::x(m_fixedpos.x);
	if (m_isfixedy) Fl_Button::y(m_fixedpos.y);

	if (Fl_Button::w() <= m_minsize.width) Fl_Button::w(m_minsize.width);
	if (Fl_Button::h() <= m_minsize.height) Fl_Button::h(m_minsize.height);
	if (Fl_Button::w() >= m_maxsize.width) Fl_Button::w(m_maxsize.width);
	if (Fl_Button::h() >= m_maxsize.height) Fl_Button::h(m_maxsize.height);

	Fl_Color col = value() ? selection_color() : color();

	draw_box(
		value() ? (down_box() ? down_box() : fl_down(box())) : box(),
		Fl_Button::x() + m_leftmargin,
		Fl_Button::y() + m_topmargin,
		Fl_Button::w() - m_rightmargin,
		Fl_Button::h() - m_bottommargin,
		col);

	draw_backdrop();

	draw_(
		Fl_Button::x() + m_leftmargin, 
		Fl_Button::y() + m_topmargin, 
		Fl_Button::w() - m_rightmargin, 
		Fl_Button::h() - m_bottommargin);
}
void Fle_Button::draw_(int _x, int _y, int _w, int _h)
{
	int X = _x + Fl::box_dx(box());
	int Y = _y + Fl::box_dy(box());
	int W = _w - Fl::box_dw(box());
	int H = _h - Fl::box_dh(box());

	if (p_on)
	{
		X = X + (_w - p_on->w()) / 2;
		Y = Y + (_h - p_on->h()) / 2;

		if (p_on && p_off)
		{
			if (m_ison) p_on->draw(X, Y, W, H, 0, 0);
			else p_off->draw(X, Y, W, H, 0, 0);
		}
		else
		{
			p_on->draw(X, Y, W, H, 0, 0);
		}
		
		return;
	}

	if (label())
	{
		fl_font(labelfont(), labelsize());
		Fl_Color c = labelcolor();
		if (labeltype() == FL_NORMAL_LABEL && value())
		{
			Fl_Color col = value() ? selection_color() : color();
			labelcolor(fl_contrast(c, col));
			fl_color(labelcolor());
			fl_draw(label(), X, Y, W, H, align());
			labelcolor(c);
		}
		else
		{
			fl_color(labelcolor());
			fl_draw(label(), X, Y, W, H, align());
		}
	}
}