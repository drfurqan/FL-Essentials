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
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Box.h>

#include <FL/fl_draw.H>

using namespace R3D;

Fle_Box::Fle_Box(int _x, int _y, int _w, int _h, const char* _title) :
	Fle_ImageWidget(_x, _y, _w, _h, _title),
	m_text(""),
	m_istext(true),
	m_autoSize(false),
	m_type(Fl_Boxtype::FL_NO_BOX),
	m_leftmargin(0),
	m_rightmargin(0),
	m_topmargin(0),
	m_bottommargin(0),
	m_minsize(cv::Size(1, 1)),
	m_maxsize(cv::Size(Fl::w() + 10000000, Fl::h() + 10000000)),
	m_isfixedx(false),
	m_isfixedy(false),
	m_fixedpos(cv::Point(_x, _y)),
	m_isroi(false),
	m_border_roi(cv::Rect(0, 0, 0, 0)),
	m_border_color(fl_rgb_color(0, 255, 0))
{
	box(Fl_Boxtype::FL_NO_BOX);
	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	m_font.setSize(12);
}

Fle_Box::~Fle_Box()
{
}

void Fle_Box::setResizeable(bool _b)
{
	if (_b)
	{
		m_minsize = cv::Size(1, 1);
		m_maxsize = cv::Size(Fl::w() + 10000000, Fl::h() + 10000000);
	}
	else
	{
		m_maxsize.width = Fle_ImageWidget::w();
		m_maxsize.height = Fle_ImageWidget::h();
		m_minsize = m_maxsize;
	}
}

void Fle_Box::draw()
{
	if (m_isfixedx) Fle_ImageWidget::x(m_fixedpos.x);
	if (m_isfixedy) Fle_ImageWidget::y(m_fixedpos.y);

	if (Fle_ImageWidget::w() <= m_minsize.width) Fle_ImageWidget::w(m_minsize.width);
	if (Fle_ImageWidget::h() <= m_minsize.height) Fle_ImageWidget::h(m_minsize.height);
	if (Fle_ImageWidget::w() >= m_maxsize.width) Fle_ImageWidget::w(m_maxsize.width);
	if (Fle_ImageWidget::h() >= m_maxsize.height) Fle_ImageWidget::h(m_maxsize.height);

	draw_box(
		Fle_ImageWidget::box(), 
		Fle_ImageWidget::x() + m_leftmargin, 
		Fle_ImageWidget::y() + m_topmargin, 
		Fle_ImageWidget::w() - m_rightmargin, 
		Fle_ImageWidget::h() - m_bottommargin, 
		Fle_ImageWidget::color());

	Fle_ImageWidget::draw();

	if (m_isroi && m_border_roi.width > 0 && m_border_roi.height > 0)
	{
		draw_box(
			Fl_Boxtype::FL_BORDER_FRAME,
			m_border_roi.x,
			m_border_roi.y,
			m_border_roi.width,
			m_border_roi.height,
			m_border_color);
	}

	drawText(
		Fle_ImageWidget::x() + m_leftmargin, 
		Fle_ImageWidget::y() + m_topmargin, 
		Fle_ImageWidget::w() - m_rightmargin - m_leftmargin,
		Fle_ImageWidget::h() - m_bottommargin - m_topmargin);
}
void Fle_Box::drawText(int _x, int _y, int _w, int _h)
{
	if (!m_text.empty() && m_istext)
	{
		fl_font(m_font.getFace(), m_font.getSize());
		fl_color(m_font.getColor());
		fl_draw(m_text.c_str(), _x, _y, _w, _h, m_font.getAlignment()); // draw text over image and background

		// auto resizes itself to fit the text.
		if (m_autoSize)
		{
			int W = 0, H = 0;
			fl_measure(m_text.c_str(), W, H);
			if (W != _w || H != _h)
				Fle_ImageWidget::size(W + m_leftmargin + m_rightmargin, H + m_topmargin + m_bottommargin);
		}
	}
}