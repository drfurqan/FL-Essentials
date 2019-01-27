/*********************************************************************************
created:	2017/11/22   04:02AM
filename: 	Fle_ColorChooserDialog.cpp
file base:	Fle_ColorChooserDialog
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized standard color chooser that creates a color chooser
inside of a dialog box with OK, Cancel, and Default buttons.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ColorChooserDialog.h>

using namespace R3D;

Fle_ColorChooserDialog::Fle_ColorChooserDialog(int _w, int _h, double _r, double _g, double _b, const char* _title)
{
	m_default_color[0] = 1;
	m_default_color[1] = 1;
	m_default_color[2] = 1;

	p_dialog = new Fle_Dialog(_w, _h, _title, 58, 0, 0);
	p_dialog->setBackgroundColor(74, 84, 89);
	p_dialog->callback(close_cb, p_dialog);
	p_dialog->setMargins(10, 10, 10, 10);
	p_dialog->setFixedWidth(_w);
	p_dialog->setFixedHeight(_h);

	p_layout = p_dialog->getCentralLayout()->addHLayout(150);

	p_layout->begin();
	{
		p_cc = new Fle_ColorChooser(0, 0, 285, 150);
		p_cc->box(FL_FLAT_BOX);
		p_cc->rgb(_r, _g, _b);
		p_cc->color(fl_rgb_color(74, 84, 89));
		p_cc->color2(fl_rgb_color(74, 84, 89));
		p_cc->selection_color(fl_rgb_color(74, 84, 89));
		p_cc->labelcolor(fl_rgb_color(255, 255, 255));
		p_cc->labelsize(14);
		p_cc->mode(1);
		p_cc->when(FL_WHEN_RELEASE);
	}
	p_layout->end();

	auto hl = p_dialog->getStatusBar()->addLayoutLR(23);
	hl->setBackgroundColor(74, 84, 89);
	hl->beginRight();
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
		p_reset->callback(default_color_cb, this);
	}
	hl->end();

	p_dialog->getCentralLayout()->getCentralLayout()->setMargins(10, 10, 15, 0);	// set dialog's margins.
	p_dialog->getStatusBar()->getCentralLayout()->setMargins(10, 10, 10, 0);	// set statusbar's margins and height.
	p_dialog->setStatusBarFixedHeight(58);
	p_dialog->setResizeable(true);
	p_dialog->hotspot(p_ok);
	p_dialog->set_modal();
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	p_dialog->position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);
}

Fle_ColorChooserDialog::~Fle_ColorChooserDialog()
{
}

void Fle_ColorChooserDialog::close_cb(Fl_Widget* _w, void* _p)
{
	auto d = static_cast<Fle_Dialog*>(_p);
	if (!d) return;
	d->hide();
	Fl::delete_widget(d);
}

void Fle_ColorChooserDialog::default_color_cb(Fl_Widget* _w, void* _p)
{
	auto cc = static_cast<Fle_ColorChooserDialog*>(_p);
	if (!cc) return;
	cc->p_cc->rgb(cc->m_default_color[0], cc->m_default_color[1], cc->m_default_color[2]);
	cc->p_cc->do_callback();
}

void Fle_ColorChooserDialog::setDefaultColor(double _r, double _g, double _b)
{
	m_default_color[0] = _r;
	m_default_color[1] = _g;
	m_default_color[2] = _b;
}

int Fle_ColorChooserDialog::exec()
{
	p_dialog->show();
	while (p_dialog->shown())
	{
		Fl::wait();
		Fl_Widget* o;
		while (((o = Fl::readqueue())) && p_dialog->shown())
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