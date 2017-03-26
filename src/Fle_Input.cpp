/*********************************************************************************
created:	2017/02/15   02:20AM
filename: 	Fle_Input.h
file base:	Fle_Input
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Modified class for an input widget that can support various
justifications, and copy/paste support.
/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Input.h>

using namespace R3D;

Fle_InputWidget::Fle_InputWidget(int _x, int _y, int _w, int _h, const char* _lable) :
Fl_Input(_x, _y, _w, _h, _lable)
{
}

void Fle_InputWidget::copy_cb(Fl_Widget*, void* _p)
{
	Fle_InputWidget* w = static_cast<Fle_InputWidget*>(_p);
	w->copy(0);    // text selection clipboard
	w->copy(1);    // copy/paste clipboard
}

void Fle_InputWidget::paste_cb(Fl_Widget*, void* _p)
{
	Fle_InputWidget *w = static_cast<Fle_InputWidget*>(_p);
	Fl::paste(*w, 1);
}

int Fle_InputWidget::handle(int _event)
{
	switch (_event)
	{
	case FL_PUSH:
		if (Fl::event_button() == FL_RIGHT_MOUSE)
		{
			Fl_Menu_Item rclick_menu[] =
			{
				{ "     Copy     ", 0, copy_cb, (void*)this },
				{ "     Paste     ", 0, paste_cb, (void*)this },
				{ 0 }
			};

			Fl_Menu_Button mb(Fl::event_x(), Fl::event_y(), 0, 0);
			mb.box(FL_FLAT_BOX);
			mb.down_box(FL_FLAT_BOX);
			mb.color(fl_rgb_color(234, 239, 253));
			mb.color2(fl_rgb_color(253, 244, 191));
			mb.labelsize(14);
			mb.textsize(14);
			mb.clear_visible_focus();
			mb.menu(rclick_menu);
			mb.popup();

			return 1;
		}
		break;

	case FL_RELEASE:
		if (Fl::event_button() == FL_RIGHT_MOUSE)
		{
			return 1;
		}
		break;
	}

	return Fl_Input::handle(_event);
}
#include <iostream>
/************************************************************************/
/*                                                                      */
/************************************************************************/
Fle_Input::Fle_Input(int _x, int _y, int _w, int _h, const char* _lable, Fl_Align _label_align) :
Fl_Group(_x, _y, _w, _h)
{
	Fl_Group::end();
	Fl_Group::align(_label_align);
	Fl_Group::box(FL_NO_BOX);

	int gap = 0;
	int W = 0, H = 0;
	if (_lable)
	{
		// temp widget to get the width of the label in pixels.
		Fl_Box t(0, 0, 1, 1, _lable);
		t.measure_label(W, H);
		gap = 4;
	}

	Fl_Group::begin();


	if (_label_align == FL_ALIGN_LEFT)
	{
		p_label = new Fl_Box(0, 0, W, H, _lable);
		p_box = new Fl_Box(W + gap, 0, _w - W - gap, _h);
		p_input = new Fle_InputWidget(W + gap, 0, _w - W - gap, _h);
	}
	else if (_label_align == FL_ALIGN_RIGHT)
	{
		p_box = new Fl_Box(0, 0, _w - W, _h);
		p_input = new Fle_InputWidget(0, 0, _w - W, _h);
		p_label = new Fl_Box(_w - W + gap, 0, W, H, _lable);
	}

	p_label->align(_label_align | FL_ALIGN_INSIDE);
	p_label->box(FL_NO_BOX);
	p_label->labelcolor(FL_WHITE);
	p_label->labelsize(12);
	p_box->color(FL_WHITE);
	p_box->box(FL_UP_BOX);
	p_input->color(FL_WHITE);
	p_input->box(FL_UP_BOX);
	p_input->hide();
	p_box->labelsize(11);
	p_input->textsize(11);

	Fl_Group::end();
}

void Fle_Input::box(Fl_Boxtype _b)
{
	p_box->box(_b);
	p_input->box(_b);
}
Fl_Boxtype Fle_Input::box() const
{
	return p_box->box();
}
void Fle_Input::color(Fl_Color _c)
{
	p_box->color(_c);
	p_input->color(_c);
}
Fl_Color Fle_Input::color() const
{
	return p_box->color();
}

void Fle_Input::textcolor(Fl_Color _c)
{
	p_box->labelcolor(_c);
	p_input->textcolor(_c);
}
Fl_Color Fle_Input::textcolor() const
{
	return p_input->textcolor();
}
void Fle_Input::textsize(int _size)
{
	p_box->labelsize(_size);
	p_input->textsize(_size);
}
int Fle_Input::textsize() const
{
	return p_input->textsize();
}
void Fle_Input::textfont(Fl_Font _f)
{
	p_box->labelfont(_f);
	p_input->textfont(_f);
}
Fl_Font Fle_Input::textfont() const
{
	return p_input->textfont();
}

Fl_Align Fle_Input::justify() const
{
	return p_box->align();
}

void Fle_Input::justify(Fl_Align _val)
{
	p_box->align(_val | FL_ALIGN_INSIDE);
}

const char * Fle_Input::value() const
{
	return p_input->value();
}

void Fle_Input::value(const char *_val)
{
	p_box->copy_label(_val);
	p_input->value(_val);
}

int Fle_Input::handle(int _event)
{
	switch (_event) 
	{
	case FL_PUSH:
	case FL_FOCUS:
		if (!p_input->visible()) 
		{
			// Make input widget 'appear' in place of the box
			p_box->hide();
			p_input->show();
			p_input->value(p_box->label());
			redraw();
		}
		break;

	case FL_UNFOCUS:
		if (p_input->visible()) 
		{
			// Replace input widget with justified box
			p_box->show();
			p_input->hide();
			p_box->label(p_input->value());
			redraw();
		}
		break;

	default:
		break;
	}

	return Fl_Group::handle(_event);
}