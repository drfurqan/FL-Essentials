/*********************************************************************************
created:	2017/11/10   04:02AM
filename: 	Fle_ColorChooser.cpp
file base:	Fle_ColorChooser
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized color chooser widget.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ColorChooser.h>


using namespace R3D;

Fle_ColorChooser::Fle_ColorChooser(int _w, int _h, const char* _title)
{
	p_dialog = new Fle_Dialog(_w, _h, _title, 58, 0, 0);
	p_dialog->setBackgroundColor(74, 84, 89);
	p_dialog->callback(close_cb, p_dialog);
	p_dialog->setMargins(10, 10, 10, 10);

	p_layout = p_dialog->getCentralLayout()->addHLayout(150);

	setDefaultColors(74, 84, 89, 74, 84, 89);
	p_layout->begin();
	{
		p_cc1 = new Fl_Color_Chooser(0, 0, 285, 150);
		p_cc1->box(FL_FLAT_BOX);
		p_cc1->rgb(m_default_color1[0] / 255.0, m_default_color1[1] / 255.0, m_default_color1[2] / 255.0);
		p_cc1->color(fl_rgb_color(74, 84, 89));
		p_cc1->color2(fl_rgb_color(74, 84, 89));
		p_cc1->selection_color(fl_rgb_color(74, 84, 89));
		p_cc1->labelcolor(fl_rgb_color(255, 255, 255));
		p_cc1->labelsize(14);
		p_cc1->mode(1);
		p_cc1->when(FL_WHEN_RELEASE);
		
		p_cc2 = new Fl_Color_Chooser(0, 0, 285, 150);
		p_cc2->box(FL_FLAT_BOX);
		p_cc2->rgb(m_default_color2[0] / 255.0, m_default_color2[1] / 255.0, m_default_color2[2] / 255.0);
		p_cc2->color(fl_rgb_color(74, 84, 89));
		p_cc2->color2(fl_rgb_color(74, 84, 89));
		p_cc2->selection_color(fl_rgb_color(74, 84, 89));
		p_cc2->labelcolor(fl_rgb_color(255, 255, 255));
		p_cc2->labelsize(14);
		p_cc2->mode(1);
		p_cc2->when(FL_WHEN_RELEASE);
	}
	p_layout->end();

	Fle_HLayoutLR* hl1 = p_dialog->getStatusBar()->addLayoutLR(23);
	hl1->setBackgroundColor(74, 84, 89);
	hl1->beginRight();
	{
		p_ok = new Fle_Button(0, 0, 90, 22, "OK");
		p_ok->color(fl_rgb_color(74, 84, 89));
		p_ok->selection_color(fl_rgb_color(74, 84, 89));
		p_ok->labelcolor(fl_rgb_color(255, 255, 255));
		p_ok->labelsize(12);
		p_dialog->setOkButton(p_ok);

		p_cancel = new Fle_Button(0, 0, 90, 22, "Cancel");
		p_cancel->color(fl_rgb_color(74, 84, 89));
		p_cancel->selection_color(fl_rgb_color(74, 84, 89));
		p_cancel->labelcolor(fl_rgb_color(255, 255, 255));
		p_cancel->labelsize(12);
		p_dialog->setCancelButton(p_cancel);

		p_reset = new Fle_Button(0, 0, 90, 22, "Default");
		p_reset->color(fl_rgb_color(74, 84, 89));
		p_reset->selection_color(fl_rgb_color(74, 84, 89));
		p_reset->labelcolor(fl_rgb_color(255, 255, 255));
		p_reset->labelsize(12);
		p_reset->callback(default_colors_cb, this);
	}
	hl1->endRight();

	p_dialog->getCentralLayout()->getLayout()->setMargins(10, 10, 15, 0);	// set dialog's margins.
	p_dialog->getStatusBar()->getLayout()->setMargins(10, 10, 10, 0);	// set statusbar's margins and height.
	p_dialog->setStatusBarFixedHeight(58);
	p_dialog->setResizeable(true);
	p_dialog->hotspot(p_ok);
	p_dialog->set_modal();
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	p_dialog->position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);
}

Fle_ColorChooser::~Fle_ColorChooser()
{
}

void Fle_ColorChooser::close_cb(Fl_Widget* _w, void* _p)
{
	Fle_Dialog* d = static_cast<Fle_Dialog*>(_p);
	if (!d) return;
	d->hide();
	Fl::delete_widget(d);
}

void Fle_ColorChooser::default_colors_cb(Fl_Widget* _w, void* _p)
{
	Fle_ColorChooser* cc = static_cast<Fle_ColorChooser*>(_p);
	if (!cc) return;
	cc->p_cc1->rgb(cc->m_default_color1[0] / 255.0, cc->m_default_color1[1] / 255.0, cc->m_default_color1[2] / 255.0);
	cc->p_cc2->rgb(cc->m_default_color2[0] / 255.0, cc->m_default_color2[1] / 255.0, cc->m_default_color2[2] / 255.0);
	cc->p_cc1->do_callback();
	cc->p_cc2->do_callback();
}

void Fle_ColorChooser::setDefaultColors(unsigned char _r1, unsigned char _g1, unsigned char _b1,
	unsigned char _r2, unsigned char _g2, unsigned char _b2)
{
	m_default_color1[0] = _r1;
	m_default_color1[1] = _g1;
	m_default_color1[2] = _b1;
	m_default_color2[0] = _r2;
	m_default_color2[1] = _g2;
	m_default_color2[2] = _b2;
}

int Fle_ColorChooser::exec()
{
	p_dialog->show();
	while (p_dialog->shown())
	{
		Fl::wait();
		Fl_Widget* o;
		while ((o = Fl::readqueue()) && p_dialog->shown())
		{
			if (o == p_ok)
			{
				p_dialog->hide();
				Fl::delete_widget(p_dialog);
				return 1;
			}
			else
			{
				if (o == p_cancel || o == p_dialog)
				{
					p_dialog->hide();
					Fl::delete_widget(p_dialog);
					return 0;
				}
			}
		}
	}
	return 0;
}