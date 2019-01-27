/*********************************************************************************
created:	2017/11/22   04:02AM
filename: 	Fle_ColorChooser.cpp
file base:	Fle_ColorChooser
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized standard color chooser.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ColorChooser.h>

#include <math.h>  // fmod

using namespace R3D;

Fle_ColorChooser::Fle_ColorChooser(int X, int Y, int W, int H, const char* L) :
	Fl_Group(0, 0, 195, 115, L),
	huebox(0, 0, 115, 115),
	valuebox(115, 0, 20, 115),
	choice(140, 0, 55, 25),
	rvalue(140, 30, 55, 25),
	gvalue(140, 60, 55, 25),
	bvalue(140, 90, 55, 25),
	resize_box(0, 0, 115, 115)
{
	end();
	resizable(resize_box);
	Fl_Group::resize(X, Y, W, H);
	r_ = g_ = b_ = 0;
	hue_ = 0.0;
	saturation_ = 0.0;
	value_ = 0.0;
	huebox.box(FL_FLAT_BOX);
	valuebox.box(FL_FLAT_BOX);
	valuebox.color2(fl_rgb_color(78, 196, 203));

	choice.add("rgb");
	choice.add("byte");
	choice.add("hex");
	choice.add("hsv");
	choice.value(0);
	choice.color(fl_rgb_color(74 + 15, 84 + 15, 89 + 15));
	choice.color2(fl_rgb_color(253, 244, 191));
	choice.box(FL_BORDER_BOX);
	choice.down_box(FL_BORDER_BOX);
	choice.textcolor(fl_rgb_color(250, 250, 250));
	choice.textfont(FL_HELVETICA);
	choice.labelsize(14);
	choice.textsize(14);
	choice.clear_visible_focus();
	choice.tooltip("Color mode, floating point, bytes, hex, or hsv.");
	set_valuators();

	rvalue.box(FL_BORDER_BOX);
	gvalue.box(FL_BORDER_BOX);
	bvalue.box(FL_BORDER_BOX);

	rvalue.color(fl_rgb_color(74 + 10, 84 + 10, 89 + 10));
	gvalue.color(fl_rgb_color(74 + 10, 84 + 10, 89 + 10));
	bvalue.color(fl_rgb_color(74 + 10, 84 + 10, 89 + 10));

	rvalue.textcolor(fl_rgb_color(250, 250, 250));
	gvalue.textcolor(fl_rgb_color(250, 250, 250));
	bvalue.textcolor(fl_rgb_color(250, 250, 250));

	rvalue.textsize(14);
	gvalue.textsize(14);
	bvalue.textsize(14);


	rvalue.callback(rgb_cb);
	gvalue.callback(rgb_cb);
	bvalue.callback(rgb_cb);
	choice.callback(mode_cb);
}

enum 
{
	M_RGB,	/**< mode() of Fl_Color_Chooser showing RGB values */
	M_BYTE,	/**< mode() of Fl_Color_Chooser showing byte values */
	M_HEX,	/**< mode() of Fl_Color_Chooser showing hex values */
	M_HSV	/**< mode() of Fl_Color_Chooser showing HSV values */
};

void Fle_ColorChooser::rgb_cb(Fl_Widget* o, void*) 
{
	Fle_ColorChooser* c = static_cast<Fle_ColorChooser*>(o->parent());
	double R = c->rvalue.value();
	double G = c->gvalue.value();
	double B = c->bvalue.value();
	if (c->mode() == M_HSV) 
	{
		if (c->hsv(R, G, B)) 
			c->do_callback();
		return;
	}
	if (c->mode() != M_RGB)
	{
		R = R / 255.0;
		G = G / 255.0;
		B = B / 255.0;
	}
	if (c->rgb(R, G, B)) 
		c->do_callback();
}

void Fle_ColorChooser::mode_cb(Fl_Widget* o, void*)
{
	Fle_ColorChooser* c = static_cast<Fle_ColorChooser*>(o->parent());
	// force them to redraw even if value is the same:
	c->rvalue.value(-1);
	c->gvalue.value(-1);
	c->bvalue.value(-1);
	c->set_valuators();
}

void Fle_ColorChooser::mode(int newMode)
{
	choice.value(newMode);
	choice.do_callback();
}

void Fle_ColorChooser::set_valuators() 
{
	switch (mode()) 
	{
	case M_RGB:
		rvalue.range(0, 1); rvalue.step(1, 1000); rvalue.value(r_);
		gvalue.range(0, 1); gvalue.step(1, 1000); gvalue.value(g_);
		bvalue.range(0, 1); bvalue.step(1, 1000); bvalue.value(b_);
		break;
	case M_BYTE: /* FALLTHROUGH */
	case M_HEX:
		rvalue.range(0, 255); rvalue.step(1); rvalue.value(int(255 * r_ + .5));
		gvalue.range(0, 255); gvalue.step(1); gvalue.value(int(255 * g_ + .5));
		bvalue.range(0, 255); bvalue.step(1); bvalue.value(int(255 * b_ + .5));
		break;
	case M_HSV:
		rvalue.range(0, 6); rvalue.step(1, 1000); rvalue.value(hue_);
		gvalue.range(0, 1); gvalue.step(1, 1000); gvalue.value(saturation_);
		bvalue.range(0, 1); bvalue.step(1, 1000); bvalue.value(value_);
		break;
	}
}

int Fle_ColorChooser::rgb(double R, double G, double B) 
{
	if (R == r_ && G == g_ && B == b_) return 0;
	r_ = R; g_ = G; b_ = B;
	double ph = hue_;
	double ps = saturation_;
	double pv = value_;
	Fl_Color_Chooser::rgb2hsv(R, G, B, hue_, saturation_, value_);
	set_valuators();
	set_changed();
	if (value_ != pv) 
	{
		#ifdef UPDATE_HUE_BOX
		huebox.damage(FL_DAMAGE_SCROLL);
		#endif
		valuebox.damage(FL_DAMAGE_EXPOSE);
	}
	if (hue_ != ph || saturation_ != ps) 
	{
		huebox.damage(FL_DAMAGE_EXPOSE);
		valuebox.damage(FL_DAMAGE_SCROLL);
	}
	return 1;
}

int Fle_ColorChooser::hsv(double H, double S, double V) 
{
	H = fmod(H, 6.0); if (H < 0.0) H += 6.0;
	if (S < 0.0) S = 0.0; else if (S > 1.0) S = 1.0;
	if (V < 0.0) V = 0.0; else if (V > 1.0) V = 1.0;
	if (H == hue_ && S == saturation_ && V == value_) return 0;
	double ph = hue_;
	double ps = saturation_;
	double pv = value_;
	hue_ = H; saturation_ = S; value_ = V;
	if (value_ != pv) 
	{
		#ifdef UPDATE_HUE_BOX
		huebox.damage(FL_DAMAGE_SCROLL);
		#endif
		valuebox.damage(FL_DAMAGE_EXPOSE);
	}
	if (hue_ != ph || saturation_ != ps) 
	{
		huebox.damage(FL_DAMAGE_EXPOSE);
		valuebox.damage(FL_DAMAGE_SCROLL);
	}
	Fl_Color_Chooser::hsv2rgb(H, S, V, r_, g_, b_);
	set_valuators();
	set_changed();
	return 1;
}