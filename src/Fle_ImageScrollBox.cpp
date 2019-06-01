/*********************************************************************************
created:	2017/01/27   04:02AM
filename: 	Fle_ImageScrollBox.h
file base:	Fle_ImageScrollBox
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized image box widget with image zoom/pan support.
			no zooming using mouse wheel, mouse wheel will be used for
			vertical and horizontal scrolling.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ImageScrollBox.h>
#include <FLE/Fle_ImageUtil.h>
#include <FLE/Fle_MessageBox.h>

#include <FL/fl_draw.H>

using namespace R3D;

Fle_ImageScrollBox::Fle_ImageScrollBox(int _x, int _y, int _w, int _h, const char* _title) :
	Fl_Scroll(_x, _y, _w, _h, _title),
	m_zoom_factors(cv::Vec2d(1.125, 0.875)),
	m_dtype(Fle_ImageDrawType::Fit),
	m_zoom(1.0)
{
	begin();

	p_box = new Fle_Box(0, 0, 250, 100);
	p_box->color(fl_rgb_color(238, 243, 250));
	p_box->box(FL_FLAT_BOX);
	p_box->setRubberBandColor(fl_rgb_color(255, 255, 0/*66, 192, 251*/));

	end(); // This call is necessary to prevent any additional UI widgets from becoming subcomponents of this window.

	scrollbar_size(15);
	type(Fl_Scroll::BOTH);	// hide both vertical and horizontal scrollbars
	box(FL_FLAT_BOX);
	color(fl_rgb_color(238, 243, 250));
	selection_color(fl_rgb_color(238, 243, 250));
	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	user_data((void*)this);
	resizable(p_box);
}

Fle_ImageScrollBox::~Fle_ImageScrollBox()
{
}

void Fle_ImageScrollBox::resize(int _x, int _y, int _w, int _h)
{
	Fl_Scroll::resize(_x, _y, _w, _h);
	adjustSize();
}
void Fle_ImageScrollBox::size(int _w, int _h)
{
	resize(x(), y(), _w, _h);
}

void Fle_ImageScrollBox::draw()
{
	Fl_Scroll::draw();
}
void Fle_ImageScrollBox::redraw()
{
	p_box->redraw();
	Fl_Scroll::redraw();
}

cv::Size Fle_ImageScrollBox::getNewSize(const cv::Size& _img_size, const cv::Size& _parent_size)
{
	cv::Size size(_img_size);
	if (m_dtype == Fle_ImageDrawType::Fit)
	{
		size = Fle_ImageUtil::getNewSizeKeepAspectRatio(_img_size.width, _img_size.height, _parent_size.width, _parent_size.height);
	}
	else if (m_dtype == Fle_ImageDrawType::Stretch)
	{
		size = cv::Size(_parent_size.width, _parent_size.height);
	}
	else if (m_dtype == Fle_ImageDrawType::Center)	// if there is no zooming
	{
		size = _img_size;
	}

	return size;
}
cv::Size Fle_ImageScrollBox::getSize()
{
	return getNewSize(p_box->getRoi().size(), cv::Size(w(), h()));
}

void Fle_ImageScrollBox::adjustSize(const cv::Size& _img_size)
{
	if (_img_size.width < 1 || _img_size.width < 1)
	{
		p_box->position(x() + (w() - p_box->w()) / 2, y() + (h() - p_box->h()) / 2);	// position the image box at center.
	}
	else
	{
		cv::Size s = getNewSize(_img_size, cv::Size(w(), h()));
		p_box->size(s.width * m_zoom, s.height * m_zoom);
		p_box->position(x() + (w() - p_box->w()) / 2, y() + (h() - p_box->h()) / 2);	// position the image box at center.
	}
}
void Fle_ImageScrollBox::adjustSize()
{
	adjustSize(p_box->getRoi().size());
}
void Fle_ImageScrollBox::resetZoom()
{
	m_zoom = 1.0;
	adjustSize();
}

void Fle_ImageScrollBox::zoomIn()
{
	scaleImage(m_zoom_factors[0]);
	redraw();
}
void Fle_ImageScrollBox::zoomOut()
{
	scaleImage(m_zoom_factors[1]);
	redraw();
}
void Fle_ImageScrollBox::scaleImage(const double _factor)
{
	auto imgsize = p_box->getRoi().size();
	if (imgsize.width == 0 || imgsize.height == 0)
		return;

	// set box size by multiplying with the zoom factor.
	m_zoom *= _factor;

	// limit the zoom factor by 13.
	if (m_zoom > 13.0)
		m_zoom = 13.0;

	// restrict the outward zooming.
	if (m_zoom < 1)
		m_zoom = 1.0;

	adjustSize(imgsize);
}

cv::Rect Fle_ImageScrollBox::convertMouseCoordToPixels(int _x, int _y)
{
	cv::Rect roi = p_box->getRoi();

	if (Fl::event_inside(p_box->x(), p_box->y(), p_box->w(), p_box->h()))	// mouse should be inside of the box widget.
	{
		auto rx = _x - p_box->x();
		auto ry = _y - p_box->y();

		auto x = static_cast<double>(rx) / static_cast<double>(p_box->w());
		auto y = static_cast<double>(ry) / static_cast<double>(p_box->h());
		roi.x = x * roi.width;
		roi.y = y * roi.height;

		return roi;
	}

	return cv::Rect(0, 0, -1, -1);
}

int Fle_ImageScrollBox::handle(int _event)
{
	static int drag_x = 0;
	static int drag_y = 0;

	int r = Fl_Scroll::handle(_event);	// first pass this event to the base class to activate the mouse events on the scrollbars.

	int width = w();
	int height = h();
	if (scrollbar.visible()) width = w() - scrollbar_size();
	if (hscrollbar.visible()) height = h() - scrollbar_size();

	switch (_event)
	{
	case FL_FOCUS:
	case FL_UNFOCUS:
		return 1;

	case FL_PUSH:
		take_focus();								// this allows key events to work.
		if (Fl::event_button() == FL_LEFT_MOUSE)
		{
			drag_x = p_box->x() - Fl::event_x();    // save where user clicked for dragging
			drag_y = p_box->y() - Fl::event_y();
			return 1;
		}
		break;

	case FL_RELEASE:
		if (Fl::event_button() == FL_LEFT_MOUSE)
		{
			drag_x = 0;
			drag_y = 0;
			fl_cursor(FL_CURSOR_DEFAULT);
			return 1;
		}
		break;

	case FL_DRAG:
		if (Fl::event_button1())
		{
			// Case # 1:
			// when the width of the image box is greater than this scroll window's width
			// and height of the image box is less than the height of this scroll window,
			// then enable dragging just in x direction and image box y should be at the centered.
			if (p_box->w() > width && p_box->h() <= height)
			{
				fl_cursor(FL_CURSOR_WE);

				int dx = drag_x + Fl::event_x();
				int dy = y() + (height - p_box->h()) / 2;

				// most left side of the image box should not be moved in +x direction.
				if (dx > x()) { dx = x(); }

				// most right side of the image box should not be moved in -x direction.
				if (dx <= x() + width - p_box->w())
					dx = x() + width - p_box->w();

				p_box->position(dx, dy);
			}

			// Case # 2:
			// when the height of the image box is greater than this scroll window's height
			// and width of the image box is less than the width of this scroll window,
			// then enable dragging just in y direction and image box x should be at the centered.
			else if (p_box->h() > height && p_box->w() <= width)
			{
				fl_cursor(FL_CURSOR_NS);

				int dx = x() + (width - p_box->w()) / 2;
				int dy = drag_y + Fl::event_y();

				// top side of the image box should not be moved in +y direction.
				if (dy > y()) { dy = y(); }

				// bottom side of the image box should not be moved in -y direction.
				if (dy <= y() + height - p_box->h())
					dy = y() + height - p_box->h();

				p_box->position(dx, dy);
			}

			// Case # 3:
			// when the both height and width of the image box is greater than this scroll window's width and height
			// then enable dragging just in both directions.
			else if (p_box->w() > width && p_box->h() > height)
			{
				fl_cursor(FL_CURSOR_MOVE);

				int dx = drag_x + Fl::event_x();
				int dy = drag_y + Fl::event_y();

				if (dx > x()) { dx = x(); }

				if (dx <= x() + width - p_box->w())
					dx = x() + width - p_box->w();

				if (dy > y()) { dy = y(); }

				if (dy <= y() + height - p_box->h())
					dy = y() + height - p_box->h();

				p_box->position(dx, dy);
			}
			redraw();
			return 1;
		}
		break;
	}

	return r;
}
