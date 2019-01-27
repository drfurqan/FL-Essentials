/*********************************************************************************
created:	2017/03/01   04:50AM
filename: 	Fle_ProgressBar.h
file base:	Fle_ProgressBar
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A class for a progress bar.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/


#include <FLE/Fle_ProgressBar.h>

#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

using namespace R3D;

Fle_ProgressBar::Fle_ProgressBar(int _x, int _y, int _w, int _h, const char* _lable) : 
Fl_Valuator(_x, _y, _w, _h, _lable)
{
    box(FL_THIN_DOWN_BOX);
    align(FL_ALIGN_LEFT);
    color(FL_WHITE);
    selection_color(fl_rgb_color(30,144,255));
    precision(2);
    range(0, 1);
    Fl_Valuator::value(0);
}

int Fle_ProgressBar::value(double _value)
{
	int lPercent = static_cast<int>(100.0 * (value() - minimum()) / (maximum() - minimum()));
	int cPercent = static_cast<int>(100.0 * (_value - minimum()) / (maximum() - minimum()));
    int ret = Fl_Valuator::value(_value);
    if(cPercent != lPercent && window()->shown())
        Fl::check();
    return ret;
}

double Fle_ProgressBar::value() const
{
	return Fl_Valuator::value();
}

void Fle_ProgressBar::draw()
{
    int dx = Fl::box_dx( box() ), 
		dy = Fl::box_dy( box() ), 
		dw = Fl::box_dw( box() ), 
		dh = Fl::box_dh( box() );

	double percent = static_cast<double>((value() - minimum()) / (maximum() - minimum()));
	int val1 = int(static_cast<double>(w() - dw)*percent), val2 = w() - dw - val1;

    char buf[8];
	sprintf(buf, "%d%%", static_cast<int>(percent*100.0));

    fl_font(FL_HELVETICA_BOLD, h()/2+2);
    int fW = 0, fH;
    fl_measure(buf, fW, fH);

    fl_draw_box(box(), x(), y(), w(), h(), color());
    fl_color(active_r() ? selection_color() : fl_inactive(selection_color()));
    fl_rectf(x()+dx, y()+dy, val1, h()-dh);
    fl_push_clip(x()+dx+val1, y()+dy, val2, h()-dh);
    fl_draw(buf, x()+w()/2-(fW>>1), y()+h()/2-(fH>>1), fW, fH, FL_ALIGN_CENTER);
    fl_pop_clip();

    fl_color(color());
    fl_push_clip(x()+dx, y()+dy, val1, h()-dh);
    fl_draw(buf, x()+w()/2-(fW>>1), y()+h()/2-(fH>>1), fW, fH, FL_ALIGN_CENTER);
    fl_pop_clip();

    draw_label();
}
