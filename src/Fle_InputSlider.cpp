/*********************************************************************************
created:	2017/01/29   02:58AM
filename: 	Fle_InputSlider.cpp
file base:	Fle_InputSlider
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized FLTK input slider with an input widget.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_InputSlider.h>
#include <FLE/Fle_StringUtil.h>

using namespace R3D;

Fle_InputSlider::Fle_InputSlider(int _x, int _y, int _w, int _h, const char* _l /*= 0*/, int _textbox_width) : 
Fl_Group(_x, _y, _w, _h, _l)
{
	p_func = nullptr;
	p_ptr = nullptr;
	m_init_value = 0;
	m_step = 1;

	p_slider = new Fl_Slider(_x, _y, _w - _textbox_width, _h);
	p_slider->step(1);
	p_slider->callback(slider_cb_, static_cast<void*>(this));

	p_input = new Fl_Int_Input(_x + _w - _textbox_width, _y, _textbox_width, _h);
	p_input->callback(input_cb_, static_cast<void*>(this));
	p_input->when(FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED);

	box(FL_UP_BOX);
	align(FL_ALIGN_LEFT);
	type(FL_HOR_SLIDER);
	labelsize(13);
	textsize(13);
	value(0);
	bounds(0, 99);
	step(1);
	color(fl_rgb_color(240, 240, 240));
	selection_color(fl_rgb_color(144, 200, 246));
	end();
}

void Fle_InputSlider::set_callback(void(*_f)(int, void*), void* _p)
{
	p_func = _f;
	p_ptr = _p;
}

void Fle_InputSlider::slider_cb()
{
	static int recurse = 0;
	if (recurse) return;
	else
	{
		recurse = 1;
		char s[80];
		sprintf(s, "%d", static_cast<int>(p_slider->value()));

		p_input->value(s);          // pass slider's value to input

		if (p_func)
			(p_func)(static_cast<int>(p_slider->value()), p_ptr);

		recurse = 0;
	}
}
void Fle_InputSlider::slider_cb_(Fl_Widget* _w, void* _p)
{
	Fle_InputSlider* inp = static_cast<Fle_InputSlider*>(_p);
	if (!inp) return;

	// Unfortunately, FLTK doesn't give us an output of odd numbers from Fl_Slider.
	// Therefore, this code is written in order to get the odd number output.
	// for example if the initial value is 1 and the step value is 2, then
	// then the output should be 1, 3, 5, 7, 9, so on...
	// https://groups.google.com/forum/#!topic/fltkgeneral/01mpgj8p__4
	//if (inp->m_step > 1)
	//{
	//	Fl_Slider* s = static_cast<Fl_Slider*>(_w);
	//	if (!s) return;

	//	s->value(s->value() + inp->m_step);
	//	int v = static_cast<int>(s->value());
	//	if (v < inp->m_init_value) v = inp->m_init_value - inp->m_step;
	//	else if (v > inp->m_init_value) v = inp->m_init_value + inp->m_step;
	//	s->value(static_cast<int>(v));
	//	inp->m_init_value = v;
	//}

	inp->slider_cb();
}

void Fle_InputSlider::input_cb()
{
	static int recurse = 0;
	if (recurse) return;
	else
	{
		recurse = 1;
		int val = 0;
		if (sscanf(p_input->value(), "%d", &val) != 1)
			val = 0;

		p_slider->value(static_cast<double>(val));

		if (p_func)
			(p_func)(val, p_ptr);

		recurse = 0;
	}
}
void Fle_InputSlider::input_cb_(Fl_Widget* _w, void* _p)
{
	Fle_InputSlider* inp = static_cast<Fle_InputSlider*>(_p);
	if (!inp) return;
	inp->input_cb();
}

void Fle_InputSlider::box(Fl_Boxtype _type)
{
	p_slider->box(_type);
	p_input->box(_type);
}
Fl_Boxtype Fle_InputSlider::box() const
{
	return p_slider->box();
}
void Fle_InputSlider::type(uchar _t)
{
	p_slider->type(_t);
}
uchar Fle_InputSlider::type() const
{
	return p_slider->type();
}
void Fle_InputSlider::value(int _val)
{
	p_slider->value(static_cast<double>(_val)); 
	m_init_value = _val;
	slider_cb();
}
int Fle_InputSlider::value() const
{
	return static_cast<int>(p_slider->value());
}
void Fle_InputSlider::step(int _step)
{
	m_step = _step;
}
int Fle_InputSlider::minimum() const
{
	return static_cast<int>(p_slider->minimum());
}
void Fle_InputSlider::minimum(int val)
{
	p_slider->minimum(val);
}

int Fle_InputSlider::maximum() const
{
	return static_cast<int>(p_slider->maximum());
}

void Fle_InputSlider::maximum(int val)
{
	p_slider->maximum(val);
}
void Fle_InputSlider::bounds(int low, int high)
{
	p_slider->bounds(low, high);
}
void Fle_InputSlider::textsize(int n)
{
	p_input->textsize(n);
}
int Fle_InputSlider::textsize() const
{
	return p_input->textsize();
}
void Fle_InputSlider::color(Fl_Color _c)
{
	p_slider->color(_c);
	p_input->color(_c);
}
Fl_Color Fle_InputSlider::color() const
{
	return p_slider->color();
}
void Fle_InputSlider::selection_color(Fl_Color _c)
{
	p_slider->selection_color(_c);
	p_input->selection_color(_c);
}
Fl_Color Fle_InputSlider::selection_color() const
{
	return p_slider->selection_color();
}
void Fle_InputSlider::textcolor(Fl_Color _c)
{
	p_input->textcolor(_c);
}
Fl_Color Fle_InputSlider::textcolor() const
{
	return p_input->textcolor();
}

Fl_Slider* Fle_InputSlider::getSlider() const
{
	return p_slider;
}
Fl_Int_Input* Fle_InputSlider::getInput() const
{
	return p_input;
}