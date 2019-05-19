/*********************************************************************************
created:	2017/01/29   02:58AM
filename: 	Fle_FloatInputSlider.cpp
file base:	Fle_FloatInputSlider
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized FLTK float slider with an input widget.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_FloatInputSlider.h>
#include <FLE/Fle_StringUtil.h>

using namespace R3D;

Fle_FloatInputSlider::Fle_FloatInputSlider(int _x, int _y, int _w, int _h, const char* _l /*= 0*/, int _textbox_width) : 
Fl_Group(_x, _y, _w, _h, _l)
{
	p_func = nullptr;
	p_ptr = nullptr;

	p_slider = new Fle_Slider(_x, _y, _w - _textbox_width, _h);
	p_slider->box(FL_UP_BOX);
	p_slider->callback(slider_cb_, static_cast<void*>(this));

	p_input = new Fl_Float_Input(_x + _w - _textbox_width + 1, _y, _textbox_width, _h);
	p_input->box(FL_UP_BOX);
	p_input->callback(input_cb_, static_cast<void*>(this));
	p_input->when(FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED);

	align(FL_ALIGN_LEFT);
	type(FL_HOR_SLIDER);
	labelsize(13);
	textsize(13);
	value(0.0);
	bounds(0, 99);
	step(0.1);
	color(fl_rgb_color(240, 240, 240));
	selection_color(fl_rgb_color(144, 200, 246));

	end();
}

void Fle_FloatInputSlider::set_callback(void(*_f)(double, void*), void* _p)
{
	p_func = _f;
	p_ptr = _p;
}

void Fle_FloatInputSlider::slider_cb()
{
	static int recurse = 0;
	if (recurse) return;
	else
	{
		recurse = 1;
		char s[80];
		std::size_t ndecimals = Fle_StringUtil::getDecimalCount(p_slider->step());
		if (ndecimals == 1)
			sprintf(s, "%.1f", p_slider->value());
		else if (ndecimals == 2)
			sprintf(s, "%.2f", p_slider->value());
		else if (ndecimals == 3)
			sprintf(s, "%.3f", p_slider->value());
		else if (ndecimals == 4)
			sprintf(s, "%.4f", p_slider->value());
		else if (ndecimals > 4)
			sprintf(s, "%.4f", p_slider->value());

		p_input->value(s);          // pass slider's value to input

		if (p_func)
			(p_func)(p_slider->value(), p_ptr);

		recurse = 0;
	}
}
void Fle_FloatInputSlider::slider_cb_(Fl_Widget* _w, void* _p)
{
	Fle_FloatInputSlider* inp = static_cast<Fle_FloatInputSlider*>(_p);
	if (!inp) return;
	inp->slider_cb();
}

void Fle_FloatInputSlider::input_cb()
{
	static int recurse = 0;
	if (recurse) return;
	else
	{
		recurse = 1;
		float val = 0.f;
		if (sscanf(p_input->value(), "%f", &val) != 1)
			val = 0.f;

		p_slider->value(static_cast<double>(val));

		if (p_func)
			(p_func)(static_cast<double>(val), p_ptr);

		recurse = 0;
	}
}
void Fle_FloatInputSlider::input_cb_(Fl_Widget* _w, void* _p)
{
	Fle_FloatInputSlider* inp = static_cast<Fle_FloatInputSlider*>(_p);
	if (!inp) return;
	inp->input_cb();
}

void Fle_FloatInputSlider::box(Fl_Boxtype _type)
{
	p_slider->box(_type);
	p_input->box(_type);
}
Fl_Boxtype Fle_FloatInputSlider::box() const
{
	return p_slider->box();
}
void Fle_FloatInputSlider::type(uchar _t)
{
	p_slider->type(_t);
}
uchar Fle_FloatInputSlider::type() const
{
	return p_slider->type();
}
void Fle_FloatInputSlider::value(double _val)
{
	p_slider->value(_val);
	slider_cb();
}
double Fle_FloatInputSlider::value() const
{
	return p_slider->value();
}
void Fle_FloatInputSlider::step(double n)
{
	p_slider->step(n);
}
double Fle_FloatInputSlider::minimum() const
{
	return p_slider->minimum();
}
void Fle_FloatInputSlider::minimum(double val)
{
	p_slider->minimum(val);
}
double Fle_FloatInputSlider::maximum() const
{
	return p_slider->maximum();
}
void Fle_FloatInputSlider::maximum(double val)
{
	p_slider->maximum(val);
}
void Fle_FloatInputSlider::bounds(double low, double high)
{
	p_slider->bounds(low, high);
}
void Fle_FloatInputSlider::textsize(int n)
{
	p_input->textsize(n);
}
int Fle_FloatInputSlider::textsize() const
{
	return p_input->textsize();
}
void Fle_FloatInputSlider::color(Fl_Color _c)
{
	p_slider->color(_c);
	p_input->color(_c);
}
Fl_Color Fle_FloatInputSlider::color() const
{
	return p_slider->color();
}
void Fle_FloatInputSlider::selection_color(Fl_Color _c)
{
	p_slider->selection_color(_c);
	p_input->selection_color(_c);
}
Fl_Color Fle_FloatInputSlider::selection_color() const
{
	return p_slider->selection_color();
}
void Fle_FloatInputSlider::textcolor(Fl_Color _c)
{
	p_input->textcolor(_c);
}
Fl_Color Fle_FloatInputSlider::textcolor() const
{
	return p_input->textcolor();
}

Fle_Slider* Fle_FloatInputSlider::getSlider() const
{
	return p_slider;
}
Fl_Float_Input* Fle_FloatInputSlider::getInput() const
{
	return p_input;
}
