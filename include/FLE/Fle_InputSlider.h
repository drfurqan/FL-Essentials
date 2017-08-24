#pragma once
#ifndef Fle_InputSlider_h__
#define Fle_InputSlider_h__

/*********************************************************************************
created:	2017/01/29   02:58AM
filename: 	Fle_InputSlider.h
file base:	Fle_InputSlider
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized FLTK slider with input.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/
/*********************************************************************************
Usage example:

FLE::IntInputSlider* s_int = new FLE::IntInputSlider(200, 300, 300, 25, "Slider");
s_int->box(FL_UP_BOX);
s_int->type(FL_HOR_SLIDER);
s_int->labelsize(13);
s_int->textsize(13);
s_int->value(1);
s_int->step(1);
s_int->bounds(1, 100);
s_int->tooltip("This slider gives you integer values.");
s_int->set_callback(slider_cb);

FLE::FloatInputSlider* s_float = new FLE::FloatInputSlider(200, 330, 300, 25);
s_float->box(FL_DOWN_BOX);
s_float->type(FL_HOR_NICE_SLIDER);
s_float->labelsize(13);
s_float->textsize(13);
s_float->value(1);
s_float->step(0.1);
s_float->bounds(1, 100);
s_float->tooltip("This slider gives you float values.");
s_float->set_callback(slider_cb);

**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Slider.H>

namespace R3D
{


class FL_ESSENTIALS_EXPORT Fle_InputSlider : public Fl_Group
{

public:
	Fle_InputSlider(int _x, int _y, int _w, int _h, const char* _l = 0, int _textbox_width = 40);

	void box(Fl_Boxtype _type);
	Fl_Boxtype box() const;
	void type(uchar _t);
	uchar type() const;
	int value() const;
	void value(int _val);
	void minimum(int _val);
	int  minimum() const;
	void maximum(int _val);
	int  maximum() const;
	void bounds(int _min, int _max);
	void step(int _step);

	void color(Fl_Color _c);
	Fl_Color color() const;
	void selection_color(Fl_Color _c);
	Fl_Color selection_color() const;
	void textcolor(Fl_Color _c);
	Fl_Color textcolor() const;
	void textsize(int _size);
	int textsize() const;

	// Description:
	// Callback function can be set using this function.
	void set_callback(void(*_f)(int, void*), void*);

	Fl_Slider* getSlider() const;
	Fl_Int_Input* getInput() const;

private:
	void slider_cb();
	static void slider_cb_(Fl_Widget* _w, void* _p);
	void input_cb();
	static void input_cb_(Fl_Widget* _w, void* _p);

	Fl_Slider* p_slider;
	Fl_Int_Input* p_input;
	typedef void(*funcptr)(int _v, void* _p);
	funcptr p_func;
	void* p_ptr;
};

class FL_ESSENTIALS_EXPORT Fle_FloatInputSlider : public Fl_Group
{

public:
	Fle_FloatInputSlider(int _x, int _y, int _w, int _h, const char* _l = 0, int _textbox_width = 50);

	void box(Fl_Boxtype _type);
	Fl_Boxtype box() const;
	void type(uchar _t);
	uchar type() const;
	double value() const;
	void value(double _val);
	void minimum(double _val);
	double  minimum() const;
	void maximum(double _val);
	double  maximum() const;
	void bounds(double _min, double _max);
	void step(double _step);
	void textsize(int _size);
	int textsize() const;

	void color(Fl_Color _c);
	Fl_Color color() const;
	void selection_color(Fl_Color _c);
	Fl_Color selection_color() const;
	void textcolor(Fl_Color _c);
	Fl_Color textcolor() const;

	// Description:
	// Callback function can be set using this function.
	void set_callback(void(*_f)(double, void*), void*);

	Fl_Slider* getSlider() const;
	Fl_Float_Input* getInput() const;

private:
	void slider_cb();
	static void slider_cb_(Fl_Widget* _w, void* _p);
	void input_cb();
	static void input_cb_(Fl_Widget* _w, void* _p);

	Fl_Slider* p_slider;
	Fl_Float_Input* p_input;
	typedef void(*funcptr)(double _v, void* _p);
	funcptr p_func;
	void* p_ptr;
};

}

#endif // Fle_InputSlider_h__