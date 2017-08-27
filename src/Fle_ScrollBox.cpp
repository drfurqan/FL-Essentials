/*********************************************************************************
created:	2017/01/27   04:02AM
filename: 	Fle_ScrollBox.h
file base:	Fle_ScrollBox
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized scroll box widget with image zoom/pan support.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ScrollBox.h>
#include <FLE/Fle_ImageUtil.h>
#include <FLE/Fle_MessageBox.h>

#include <FL/fl_draw.H>

using namespace R3D;

Fle_ScrollBox::Fle_ScrollBox(int _x, int _y, int _w, int _h, const char* _title) :
Fl_Scroll(_x, _y, _w, _h, _title)
{
	p_box = new Fle_Box(0, 0, _w, _h);
	p_box->color(fl_rgb_color(214, 219, 233));
	p_box->box(FL_NO_BOX);
	p_box->setImageDrawType(Fle_ImageDrawType::Fit);

	scrollbar_size(15);

	type(Fl_Scroll::ALWAYS_ON);	// hide both vertical and horizontal scrollbars
	box(FL_NO_BOX);
	color(fl_rgb_color(214, 219, 233));
	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	user_data((void*)this);
	resizable(this);
	
	end(); // This call is necessary to prevent any additional UI widgets from becoming subcomponents of this window.
}

Fle_ScrollBox::~Fle_ScrollBox()
{
}

void Fle_ScrollBox::resize(int _x, int _y, int _w, int _h)
{
	Fl_Scroll::resize(_x, _y, _w, _h);
	p_box->position((_w - p_box->w()) / 2, (_h - p_box->h()) / 2);	// position the image box at center.
}
void Fle_ScrollBox::size(int _w, int _h)
{
	resize(x(), y(), _w, _h);
}
void Fle_ScrollBox::zoomIn()
{
	p_box->zoomIn();
	p_box->position((w() - p_box->w()) / 2, (h() - p_box->h()) / 2);	// position the image box at center.
	redraw();
}
void Fle_ScrollBox::zoomOut()
{
	p_box->zoomOut();
	p_box->position((w() - p_box->w()) / 2, (h() - p_box->h()) / 2);	// position the image box at center.
	redraw();
}
void Fle_ScrollBox::setBox(Fle_Box* _b) 
{ 
	remove(p_box); 
	delete p_box; 
	p_box = _b; 
}

int Fle_ScrollBox::handle(int _event)
{
	static int drag_x = 0;
	static int drag_y = 0;
	// mouse should be inside the widget.
	if (Fl::event_inside(this) &&
		Fl::event_x() >= x() && Fl::event_x() < x() + w() - scrollbar_size() &&
		Fl::event_y() >= y() && Fl::event_y() < y() + h() - scrollbar_size())
	{
		switch (_event)
		{
		case FL_FOCUS:
		case FL_UNFOCUS:
			return 1;

		case FL_PUSH:
			drag_x = p_box->x() - Fl::event_x();    // save where user clicked for dragging
			drag_y = p_box->y() - Fl::event_y();
			return 1;

		case FL_RELEASE:
			drag_x = 0;
			drag_y = 0;
			fl_cursor(FL_CURSOR_DEFAULT);
			return 1;

		case FL_DRAG:
			// Case # 1:
			// when the width of the image box is greater than this scroll window's width
			// and height of the image box is less than the height of this scroll window,
			// then enable dragging just in x direction and image box y should be at the centered.
			if (p_box->w() > w() && p_box->h() <= h())
			{
				fl_cursor(FL_CURSOR_WE);

				int dx = drag_x + Fl::event_x();
				int dy = (h() - p_box->h()) / 2;

				// most left side of the image box should not be moved in +x direction.
				if (dx > 0) { dx = 0; }

				// most right side of the image box should not be moved in -x direction.
				if (dx <= w() - p_box->w()) { dx = w() - p_box->w(); }

				p_box->position(dx, dy);
			}

			// Case # 2:
			// when the height of the image box is greater than this scroll window's height
			// and width of the image box is less than the width of this scroll window,
			// then enable dragging just in y direction and image box x should be at the centered.
			if (p_box->h() > h() && p_box->w() <= w())
			{
				fl_cursor(FL_CURSOR_NS);
				
				int dx = (w() - p_box->w()) / 2;
				int dy = drag_y + Fl::event_y();

				// top side of the image box should not be moved in +y direction.
				if (dy > 0) { dy = 0; }

				// bottom side of the image box should not be moved in -y direction.
				if (dy <= h() - p_box->h())
					dy = h() - p_box->h();

				p_box->position(dx, dy);
			}

			// Case # 3:
			// when the both height and width of the image box is greater than this scroll window's width and height
			// then enable dragging just in both directions.
			if (p_box->w() > w() && p_box->h() > h())
			{
				fl_cursor(FL_CURSOR_MOVE);
				
				int dx = drag_x + Fl::event_x();
				int dy = drag_y + Fl::event_y();

				if (dx > 0) { dx = 0; }

				if (dx <= w() - p_box->w())
					dx = w() - p_box->w();

				if (dy > 0) { dy = 0; }

				if (dy <= h() - p_box->h())
					dy = h() - p_box->h();

				p_box->position(dx, dy);
			}
			redraw();
			return 1;

		case FL_MOUSEWHEEL:
			switch (Fl::event_dy())
			{
			case -1:
				zoomIn();
				return 1;

			case 1:
				zoomOut();
				return 1;
			}
			break;

		default:
			break;
		}
	}

    return Fl_Scroll::handle(_event);
}
