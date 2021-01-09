/*********************************************************************************
created:	2017/08/28   11:41PM
filename: 	Fle_BoxWindow.h
file base:	Fle_BoxWindow
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized window with an image box that supports zooming/panning.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_BoxWindow.h>

#include <FL/fl_draw.H>

using namespace R3D;

Fle_BoxWindow::Fle_BoxWindow(int _x, int _y, int _w, int _h, const char* _title) :
	Fle_Window(_x, _y, _w, _h, _title)
{
	//p_box->setImageDrawType(Fle_ImageDrawType::Center);
	Fle_Window::end();
}
Fle_BoxWindow::Fle_BoxWindow(int _w, int _h, const char* _title) :
	Fle_Window(_w, _h, _title)
{
	//p_box->setImageDrawType(Fle_ImageDrawType::Center);
	Fle_Window::end();
}

Fle_BoxWindow::~Fle_BoxWindow()
{
}

void Fle_BoxWindow::zoomIn()
{
	p_box->zoomIn();
	p_box->position((w() - p_box->w()) / 2, (h() - p_box->h()) / 2);	// position the image box at center.
	redraw();
}
void Fle_BoxWindow::zoomOut()
{
	p_box->zoomOut();
	p_box->position((w() - p_box->w()) / 2, (h() - p_box->h()) / 2);	// position the image box at center.
	redraw();
}

int Fle_BoxWindow::handle(int _event)
{
	static int drag_x = 0;
	static int drag_y = 0;

	switch (_event)
	{
	case FL_FOCUS:
	case FL_UNFOCUS:
		return 1;

	case FL_PUSH:
		take_focus();						// this allows key events to work.
		switch (Fl::event_button())
		{
		case FL_LEFT_MOUSE:
			drag_x = p_box->x() - Fl::event_x();    // save where user clicked for dragging
			drag_y = p_box->y() - Fl::event_y();
			return 1;
		}
		break;

	case FL_RELEASE:
		switch (Fl::event_button())
		{
		case FL_LEFT_MOUSE:
			drag_x = 0;
			drag_y = 0;
			fl_cursor(FL_CURSOR_DEFAULT);
			return 1;
		}
		break;

	case FL_DRAG:
		switch (Fl::event_button())
		{
		case FL_LEFT_MOUSE:

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
		}
		break;

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

	return Fle_Window::handle(_event);
}
