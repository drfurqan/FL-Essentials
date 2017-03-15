/*********************************************************************************
created:	2017/03/01   01:48PM
filename: 	Fle_Group.h
file base:	Fle_Group
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A group with a title.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Group.h"

#include <FL/Fl.H>
#include <FL/fl_draw.H>

using namespace R3D;

Fle_Group::Fle_Group(int _x, int _y, int _w, int _h, const char* _title) : Fl_Group(_x, _y, _w, _h, _title)
{
    box(FL_FRAME);
	color(FL_WHITE);
	align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
	end();
}

void Fle_Group::draw()
{
    int lblW = 0, lblH, X;

    if(label() == 0)
        lblW = lblH = 0;
    else if(strlen(label()) == 0)
        lblW = lblH = 0;
    else
    {
        measure_label(lblW, lblH);
        lblW += 4;
        lblH += 2;
    }

    // align the label
    if(align() & FL_ALIGN_LEFT) X = 4;
    else if(align() & FL_ALIGN_RIGHT) X = w() - lblW - 8;
    else X = w()/2 - lblW/2 - 2;

    // draw the main group box
    if(damage() & ~FL_DAMAGE_CHILD)
        fl_draw_box(box(), x(), y()+lblH/2, w(), h()-lblH/2, color());

    // clip and draw the children
    fl_clip(x()+2, y()+lblH+1, w()-4, h()-lblH-3);
    draw_children();
    fl_pop_clip();

    // clear behind the label and draw it
    fl_color(color());
    fl_rectf(x()+X, y(), lblW+4, lblH);
    fl_color(labelcolor());
    draw_label(x()+X+2, y(), lblW, lblH, FL_ALIGN_CENTER);
}
