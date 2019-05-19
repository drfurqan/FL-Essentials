/*********************************************************************************
created:	2017/01/27   04:02AM
filename: 	Fle_ImageBox.h
file base:	Fle_ImageBox
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized image box widget with image zoom/pan support.
			zooming using mouse wheel, vertical and horizontal scrolling is disabled.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ImageBox.h>

using namespace R3D;

Fle_ImageBox::Fle_ImageBox(int _x, int _y, int _w, int _h, const char* _title) :
	Fle_ImageScrollBox(_x, _y, _w, _h, _title)
{
	scrollbar_size(0);
	type(Fl_Scroll::ALWAYS_ON);	// hide/disable both vertical and horizontal scrollbars
}

Fle_ImageBox::~Fle_ImageBox()
{
}

int Fle_ImageBox::handle(int _event)
{
	int r = Fle_ImageScrollBox::handle(_event); // first pass this event to the base class to activate the mouse events.

	switch (_event)
	{
	case FL_MOUSEWHEEL:
		if (Fl::event_dy() == 1)
		{
			zoomOut();
			return 1;
		}
		else if (Fl::event_dy() == -1)
		{
			zoomIn();
			return 1;
		}
		break;

	default:
		break;
	}

	return r;
}
