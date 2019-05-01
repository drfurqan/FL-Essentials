/*********************************************************************************
created:	2017/02/15   02:20AM
filename: 	Fle_Slider.cpp
file base:	Fle_Slider
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized FL_Slider.
/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Slider.h>

#include <FL/Fl_Menu_Button.H>
#include <FL/fl_draw.H>

using namespace R3D;

Fle_Slider::Fle_Slider(int _x, int _y, int _w, int _h, const char* _lable) :
	Fl_Slider(_x, _y, _w, _h, _lable)
{
}

void Fle_Slider::draw_bg(int X, int Y, int W, int H)
{
	fl_push_clip(X, Y, W, H);
	draw_box();
	fl_pop_clip();

	Fl_Color black = active_r() ? FL_FOREGROUND_COLOR : FL_INACTIVE_COLOR;
	if (type() == FL_VERT_NICE_SLIDER) {
		draw_box(FL_THIN_DOWN_BOX, X + W / 2 - 2, Y, 4, H, black);
	}
	else if (type() == FL_HOR_NICE_SLIDER) {
		draw_box(FL_THIN_DOWN_BOX, X, Y + H / 2 - 2, W, 4, black);
	}
}

void Fle_Slider::draw(int X, int Y, int W, int H)
{

	double val;
	if (minimum() == maximum())
		val = 0.5;
	else {
		val = (value() - minimum()) / (maximum() - minimum());
		if (val > 1.0) val = 1.0;
		else if (val < 0.0) val = 0.0;
	}

	int ww = (horizontal() ? W : H);
	int xx, S;
	if (type() == FL_HOR_FILL_SLIDER || type() == FL_VERT_FILL_SLIDER) {
		S = int(val*ww + .5);
		if (minimum() > maximum()) { S = ww - S; xx = ww - S; }
		else xx = 0;
	}
	else {
		S = int(slider_size()*ww + .5);
		int T = (horizontal() ? H : W) / 2 + 1;
		if (type() == FL_VERT_NICE_SLIDER || type() == FL_HOR_NICE_SLIDER) T += 4;
		if (S < T) S = T;
		xx = int(val*(ww - S) + .5);
	}
	int xsl, ysl, wsl, hsl;
	if (horizontal()) {
		xsl = X + xx;
		wsl = S;
		ysl = Y;
		hsl = H;
	}
	else {
		ysl = Y + xx;
		hsl = S;
		xsl = X;
		wsl = W;
	}

	draw_bg(X, Y, W, H);

	Fl_Boxtype box1 = slider();
	if (!box1) { /*box1 = (Fl_Boxtype)(box()&-2); if (!box1) */box1 = FL_UP_BOX; }		// 24-04-2019: fix the box type to FL_UP_BOX only. 
	if (type() == FL_VERT_NICE_SLIDER) {
		draw_box(box1, xsl, ysl, wsl, hsl, FL_GRAY);
		int d = (hsl - 4) / 2;
		draw_box(FL_THIN_DOWN_BOX, xsl + 2, ysl + d, wsl - 4, hsl - 2 * d, selection_color());
	}
	else if (type() == FL_HOR_NICE_SLIDER) {
		draw_box(box1, xsl, ysl, wsl, hsl, FL_GRAY);
		int d = (wsl - 4) / 2;
		draw_box(FL_THIN_DOWN_BOX, xsl + d, ysl + 2, wsl - 2 * d, hsl - 4, selection_color());
	}
	else {
		if (wsl > 0 && hsl > 0) draw_box(box1, xsl, ysl, wsl, hsl, selection_color());

		if (type() != FL_HOR_FILL_SLIDER && type() != FL_VERT_FILL_SLIDER &&
			Fl::is_scheme("gtk+")) {
			if (W > H && wsl > (hsl + 8)) {
				// Draw horizontal grippers
				int yy, hh;
				hh = hsl - 8;
				xx = xsl + (wsl - hsl - 4) / 2;
				yy = ysl + 3;

				fl_color(fl_darker(selection_color()));
				fl_line(xx, yy + hh, xx + hh, yy);
				fl_line(xx + 6, yy + hh, xx + hh + 6, yy);
				fl_line(xx + 12, yy + hh, xx + hh + 12, yy);

				xx++;
				fl_color(fl_lighter(selection_color()));
				fl_line(xx, yy + hh, xx + hh, yy);
				fl_line(xx + 6, yy + hh, xx + hh + 6, yy);
				fl_line(xx + 12, yy + hh, xx + hh + 12, yy);
			}
			else if (H > W && hsl > (wsl + 8)) {
				// Draw vertical grippers
				int yy;
				xx = xsl + 4;
				ww = wsl - 8;
				yy = ysl + (hsl - wsl - 4) / 2;

				fl_color(fl_darker(selection_color()));
				fl_line(xx, yy + ww, xx + ww, yy);
				fl_line(xx, yy + ww + 6, xx + ww, yy + 6);
				fl_line(xx, yy + ww + 12, xx + ww, yy + 12);

				yy++;
				fl_color(fl_lighter(selection_color()));
				fl_line(xx, yy + ww, xx + ww, yy);
				fl_line(xx, yy + ww + 6, xx + ww, yy + 6);
				fl_line(xx, yy + ww + 12, xx + ww, yy + 12);
			}
		}
	}

	draw_label(xsl, ysl, wsl, hsl);
	if (Fl::focus() == this) {
		if (type() == FL_HOR_FILL_SLIDER || type() == FL_VERT_FILL_SLIDER) draw_focus();
		else draw_focus(box1, xsl, ysl, wsl, hsl);
	}
}

void Fle_Slider::draw()
{
	if (damage()&FL_DAMAGE_ALL)
		draw_box();

	draw(x() + Fl::box_dx(box()),
		y() + Fl::box_dy(box()),
		w() - Fl::box_dw(box()),
		h() - Fl::box_dh(box()));
}