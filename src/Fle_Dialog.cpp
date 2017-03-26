/*********************************************************************************
created:	2017/01/30   09:42AM
filename: 	Fle_StatusBar.h
file base:	Fle_StatusBar
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	StatusBar class to create a horizontal kind of bar which contains various
widgets to be added in the status bar. Widgets will be added from the most
left side by default.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Dialog.h>
#include <FLE/Fle_Input.h>
#include <FLE/Fle_Spinner.h>

#include <FL/Fl_Button.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Help_View.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Check_Button.H>

using namespace R3D;

Fle_Dialog::Fle_Dialog(int _x, int _y, int _w, int _h, const char* _title, int _status_bar_height, int _x_margin, int _y_margin) :
Fle_Window(_x, _y, _w, _h, _title),
m_leftmargin(0),
m_rightmargin(0),
m_topmargin(0),
m_bottommargin(0),
p_ok(nullptr),
p_cancel(nullptr)
{
	setBackgroundColor(80, 80, 80);

	Fle_Window::begin();
	p_main_vlayout = new Fle_VLayout(_x_margin, _y_margin, _w - _x_margin - _x_margin, _h - _y_margin - _y_margin);
	p_main_vlayout->color(fl_rgb_color(80, 80, 80));
	Fle_Window::end();

	p_main_vlayout->begin();
	p_central_hlayout = new Fle_VHLayout(0, 0, _w, _h - _status_bar_height);
	p_central_hlayout->setBackgroundColor(80, 80, 80);
	p_central_hlayout->getLayout()->setBackgroundColor(80, 80, 80);
	p_central_hlayout->getLayout()->getTopLayout()->setSpacing(10);
	p_central_hlayout->getLayout()->getBottomLayout()->setSpacing(10);
	p_central_hlayout->getLayout()->setMargins(10, 10, 10, 0);
	p_main_vlayout->end();

	p_main_vlayout->begin();

	// a separator line.
	Fle_Box* b = new Fle_Box(0, 0, _w, 1);
	b->box(FL_FLAT_BOX);
	b->color(fl_rgb_color(142, 142, 142));

	p_statusbar_vhlayout = new Fle_VHLayout(0, 0, _w, _status_bar_height);
	p_statusbar_vhlayout->setBackgroundColor(80, 80, 80);
	p_statusbar_vhlayout->getLayout()->setBackgroundColor(80, 80, 80);
	p_statusbar_vhlayout->getLayout()->setMargins(10, 20, 10, 0);
	p_main_vlayout->end();

	p_main_vlayout->resizable(p_central_hlayout);
	Fle_Window::end();
}

Fle_Dialog::Fle_Dialog(int _w, int _h, const char* _title, int _status_bar_height, int _x_margin, int _y_margin) :
Fle_Window(_w, _h, _title),
m_leftmargin(0),
m_rightmargin(0),
m_topmargin(0),
m_bottommargin(0),
p_ok(nullptr),
p_cancel(nullptr)
{
	setBackgroundColor(80, 80, 80);

	Fle_Window::begin();
	p_main_vlayout = new Fle_VLayout(_x_margin, _y_margin, _w - _x_margin - _x_margin, _h - _y_margin - _y_margin);
	p_main_vlayout->color(fl_rgb_color(80, 80, 80));
	Fle_Window::end();

	p_main_vlayout->begin();
	p_central_hlayout = new Fle_VHLayout(0, 0, _w, _h - _status_bar_height);
	p_central_hlayout->setBackgroundColor(80, 80, 80);
	p_central_hlayout->getLayout()->setBackgroundColor(80, 80, 80);
	p_central_hlayout->getLayout()->getTopLayout()->setSpacing(10);
	p_central_hlayout->getLayout()->getBottomLayout()->setSpacing(10);
	p_central_hlayout->getLayout()->setMargins(10, 10, 10, 0);
	p_main_vlayout->end();

	p_main_vlayout->begin();
	// a separator line.
	Fle_Box* b = new Fle_Box(0, 0, _w, 1);
	b->box(FL_FLAT_BOX);
	b->color(fl_rgb_color(142, 142, 142));

	p_statusbar_vhlayout = new Fle_VHLayout(0, 0, _w, _status_bar_height);
	p_statusbar_vhlayout->setBackgroundColor(80, 80, 80);
	p_statusbar_vhlayout->getLayout()->setBackgroundColor(80, 80, 80);
	p_statusbar_vhlayout->getLayout()->setMargins(10, 20, 10, 0);
	p_main_vlayout->end();

	p_main_vlayout->resizable(p_central_hlayout);
	Fle_Window::end();
}

Fle_Dialog::~Fle_Dialog()
{
}

void Fle_Dialog::begin()
{
	p_central_hlayout->begin();
}
void Fle_Dialog::end()
{
	p_central_hlayout->end();
	Fle_Window::end();
}

void Fle_Dialog::setStatusBarFixedHeight(int _h)
{
	p_central_hlayout->size(p_main_vlayout->w(), p_main_vlayout->h() - _h);
	p_statusbar_vhlayout->size(p_main_vlayout->w(), _h);
}

static void static_dialog_cb(Fl_Widget* _w, void* _p)
{
	Fle_Dialog* d = static_cast<Fle_Dialog*>(_p);
	d->hide();
	Fl::delete_widget(d);
}

int Fle_Dialog::getNumber(int _w, int _h, 
	const char* _title, 
	const char* _label, 
	double& _value, 
	double _minimum, 
	double _maximum, 
	double _step,
	const char* _checkbox_label,
	bool& _checkbox)
{
	Fle_Dialog* d = new Fle_Dialog(_w, _h, _title, 58, 0, 0);
	d->callback(static_dialog_cb, d);
	d->setMargins(10, 10, 10, 10);

	Fle_HLayout* l = d->getCentralLayout()->addHLayout(25);

	l->begin();

	Fle_Spinner* s;
	if (_label)
	{
		Fle_Box* b = new Fle_Box(0, 0, _w - 132, 25);
		b->color(fl_rgb_color(80, 80, 80));
		b->setText(_label);
		b->getFont()->setColor(fl_rgb_color(255, 255, 255));
		b->getFont()->setAlignment(FL_ALIGN_LEFT);

		s = new Fle_Spinner(0, 0, 100, 25);
	}
	else
	{
		s = new Fle_Spinner(0, 0, _w - 23, 25);
	}

	s->type(FL_FLOAT_INPUT);
	s->box(FL_FLAT_BOX);
	s->color(fl_rgb_color(110, 110, 110));
	s->selection_color(fl_rgb_color(255, 255, 255));
	s->textcolor(fl_rgb_color(255, 255, 255));
	s->value(_value);
	s->minimum(_minimum);
	s->maximum(_maximum);
	s->step(_step);

	l->end();

	Fl_Check_Button* check = nullptr;
	if (_checkbox_label)
	{
		Fle_HLayout* l = d->getCentralLayout()->addHLayout(30);
		l->begin();
		check = new Fl_Check_Button(0, 0, _w, 30, _checkbox_label);
		if (_checkbox) check->value(1);
		else check->value(0);
		check->labelsize(12);
		check->labelcolor(fl_rgb_color(255, 255, 255));
		check->clear_visible_focus();
		l->end();
	}

	Fle_HLayoutLR* hl1 = d->getStatusBar()->addLayoutLR(23);
	hl1->setBackgroundColor(80, 80, 80);

	hl1->beginRight();

	Fle_Button* ok = new Fle_Button(0, 0, 90, 22, "OK");
	ok->color(fl_rgb_color(80, 80, 80));
	ok->selection_color(fl_rgb_color(80, 80, 80));
	ok->labelcolor(fl_rgb_color(255, 255, 255));
	ok->labelsize(12);
	d->setOkButton(ok);

	Fle_Button* cancel = new Fle_Button(0, 0, 90, 22, "Cancel");
	cancel->color(fl_rgb_color(80, 80, 80));
	cancel->selection_color(fl_rgb_color(80, 80, 80));
	cancel->labelcolor(fl_rgb_color(255, 255, 255));
	cancel->labelsize(12);
	d->setCancelButton(cancel);

	hl1->endRight();

	// set dialog's margins.
	d->getCentralLayout()->getLayout()->setMargins(10, 10, 15, 0);
	// set statusbar's margins and height.
	d->getStatusBar()->getLayout()->setMargins(10, 10, 10, 0);
	d->setStatusBarFixedHeight(58);

	d->setResizeable(false);
	d->hotspot(ok);
	d->set_modal();
	d->show();
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	d->position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);

	while (d->shown())
	{
		Fl::wait();
		Fl_Widget* o;
		while ((o = Fl::readqueue()) && d->shown())
		{
			if (o == ok)
			{
				_value = s->value();
				if (check)
				{
					if (check->value() == 1) _checkbox = true;
					else _checkbox = false;
				}
				Fl::delete_widget(d);
				return 1;
			}
			else
			{
				if (o == cancel || o == d)
				{
					d->hide();
					Fl::delete_widget(d);
					return 0;
				}
			}
		}
	}
	return 0;
}
int Fle_Dialog::getNumber(int _w, int _h,
	const char* _title,
	const char* _label,
	double& _value,
	double _minimum,
	double _maximum,
	double _step)
{
	bool b = false;
	return getNumber(_w, _h, _title, _label, _value, _minimum, _maximum, _step, nullptr, b);
}

int Fle_Dialog::getNumbers(int _w, int _h, const char* _title,
	const std::vector<const char*>& _labels, 
	std::vector<double>& _values, 
	const std::vector<double>& _minimums, 
	const std::vector<double>& _maximums, 
	const std::vector<double>& _steps,
	const char* _checkbox_label,
	bool& _checkbox)
{
	Fle_Dialog* d = new Fle_Dialog(_w, _h, _title, 58, 0, 0);
	d->callback(static_dialog_cb, d);
	d->setMargins(10, 10, 10, 10);

	std::vector<Fle_Spinner*> s(_labels.size());
	for (std::size_t i = 0; i < _labels.size(); i++)
	{
		Fle_HLayout* l = d->getCentralLayout()->addHLayout(25);

		l->begin();

		Fle_Box* b = new Fle_Box(0, 0, _w - 132, 25);
		b->color(fl_rgb_color(80, 80, 80));
		b->setText(_labels[i]);
		b->getFont()->setColor(fl_rgb_color(255, 255, 255));
		b->getFont()->setAlignment(FL_ALIGN_LEFT);

		s[i] = new Fle_Spinner(0, 0, 100, 25);
		s[i]->type(FL_FLOAT_INPUT);
		s[i]->box(FL_UP_BOX);
		s[i]->color(fl_rgb_color(110, 110, 110));
		s[i]->selection_color(fl_rgb_color(255, 255, 255));
		s[i]->textcolor(fl_rgb_color(255, 255, 255));
		s[i]->value(_values[i]);
		s[i]->minimum(_minimums[i]);
		s[i]->maximum(_maximums[i]);
		s[i]->step(_steps[i]);

		l->end();
	}

	Fl_Check_Button* check = nullptr;
	if (_checkbox_label)
	{
		Fle_HLayout* l = d->getCentralLayout()->addHLayout(30);
		l->begin();
		check = new Fl_Check_Button(0, 0, _w, 30, _checkbox_label);
		if(_checkbox) check->value(1);
		else check->value(0);
		check->labelsize(12);
		check->labelcolor(fl_rgb_color(255, 255, 255));
		check->clear_visible_focus();
		l->end();
	}

	Fle_HLayoutLR* hl1 = d->getStatusBar()->addLayoutLR(23);
	hl1->setBackgroundColor(80, 80, 80);

	hl1->beginRight();

	Fle_Button* ok = new Fle_Button(0, 0, 90, 22, "OK");
	ok->color(fl_rgb_color(80, 80, 80));
	ok->selection_color(fl_rgb_color(80, 80, 80));
	ok->labelcolor(fl_rgb_color(255, 255, 255));
	ok->labelsize(12);
	d->setOkButton(ok);

	Fle_Button* cancel = new Fle_Button(0, 0, 90, 22, "Cancel");
	cancel->color(fl_rgb_color(80, 80, 80));
	cancel->selection_color(fl_rgb_color(80, 80, 80));
	cancel->labelcolor(fl_rgb_color(255, 255, 255));
	cancel->labelsize(12);
	d->setCancelButton(cancel);

	hl1->endRight();

	// set dialog's margins.
	d->getCentralLayout()->getLayout()->setMargins(10, 10, 15, 0);
	// set statusbar's margins and height.
	d->getStatusBar()->getLayout()->setMargins(10, 10, 10, 0);
	d->setStatusBarFixedHeight(58);

	d->setResizeable(false);
	d->hotspot(ok);
	d->set_modal();
	d->show();
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	d->position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);

	while (d->shown())
	{
		Fl::wait();
		Fl_Widget* o;
		while ((o = Fl::readqueue()) && d->shown())
		{
			if (o == ok)
			{
				for (std::size_t i = 0; i < _labels.size(); i++)
					_values[i] = s[i]->value();
				if (check)
				{
					if (check->value() == 1) _checkbox = true;
					else _checkbox = false;
				}
				Fl::delete_widget(d);
				return 1;
			}
			else
			{
				if (o == cancel || o == d)
				{
					d->hide();
					Fl::delete_widget(d);
					return 0;
				}
			}
		}
	}
	return 0;
}
int Fle_Dialog::getNumbers(int _w, int _h, const char* _title,
	const std::vector<const char*>& _labels,
	std::vector<double>& _values,
	const std::vector<double>& _minimums,
	const std::vector<double>& _maximums,
	const std::vector<double>& _steps)
{
	bool b = false;
	return getNumbers(_w, _h, _title, _labels, _values, _minimums, _maximums, _steps, nullptr, b);
}

int Fle_Dialog::getInput(int _w, int _h, const char* _title, const char* _label, std::string& _value)
{
	Fle_Dialog* d = new Fle_Dialog(_w, _h, _title, 58, 0, 0);
	d->callback(static_dialog_cb, d);
	d->setMargins(10, 10, 10, 10);

	Fle_HLayout* l = d->getCentralLayout()->addHLayout(25);

	l->begin();

	Fle_Input* s = new Fle_Input(0, 0, _w - 25, 25, _label);
	s->box(FL_FLAT_BOX);
	s->justify(FL_ALIGN_LEFT);
	s->color(fl_rgb_color(255, 255, 255));
	s->value(std::string(_value).c_str());
	s->textcolor(fl_rgb_color(0, 0, 0));
	s->textsize(13);

	l->end();

	Fle_HLayoutLR* hl1 = d->getStatusBar()->addLayoutLR(23);
	hl1->setBackgroundColor(80, 80, 80);

	hl1->beginRight();

	Fle_Button* ok = new Fle_Button(0, 0, 90, 22, "OK");
	ok->color(fl_rgb_color(80, 80, 80));
	ok->selection_color(fl_rgb_color(80, 80, 80));
	ok->labelcolor(fl_rgb_color(255, 255, 255));
	ok->labelsize(12);
	d->setOkButton(ok);

	Fle_Button* cancel = new Fle_Button(0, 0, 90, 22, "Cancel");
	cancel->color(fl_rgb_color(80, 80, 80));
	cancel->selection_color(fl_rgb_color(80, 80, 80));
	cancel->labelcolor(fl_rgb_color(255, 255, 255));
	cancel->labelsize(12);
	d->setCancelButton(cancel);

	hl1->endRight();

	// set dialog's margins.
	d->getCentralLayout()->getLayout()->setMargins(10, 10, 15, 0);
	// set statusbar's margins and height.
	d->getStatusBar()->getLayout()->setMargins(10, 10, 10, 0);
	d->setStatusBarFixedHeight(58);

	d->setResizeable(false);
	d->hotspot(ok);
	d->set_modal();
	d->show();
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	d->position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);

	while (d->shown())
	{
		Fl::wait();
		Fl_Widget* o;
		while ((o = Fl::readqueue()) && d->shown())
		{
			if (o == ok)
			{
				_value = s->value();
				Fl::delete_widget(d);
				return 1;
			}
			else
			{
				if (o == cancel || o == d)
				{
					d->hide();
					Fl::delete_widget(d);
					return 0;
				}
			}
		}
	}
	return 0;
}

int Fle_Dialog::getInputs(int _w, int _h, 
	const char* _title,
	const std::vector<const char*>& _labels,
	std::vector<std::string>& _values)
{
	Fle_Dialog* d = new Fle_Dialog(_w, _h, _title, 58, 0, 0);
	d->callback(static_dialog_cb, d);
	d->setMargins(10, 10, 10, 10);

	// find the longest label.
	std::size_t n = std::string(_labels[0]).length();
	for (std::size_t i = 0; i < _labels.size(); i++)
		if (std::string(_labels[i]).length() > n)
			n = std::string(_labels[i]).length();

	// create all the inputs.
	std::vector<Fle_Input*> s(_labels.size());
	for (std::size_t i = 0; i < _labels.size(); i++)
	{
		// first, create a layout in which other widgets will be packed.
		Fle_HLayout* l = d->getCentralLayout()->addHLayout(25);

		// start packing.
		l->begin();

		// create a label at the most left size.
		Fle_Box* b = new Fle_Box(0, 0, static_cast<int>(n * 7), 25);
		b->color(fl_rgb_color(80, 80, 80));
		b->setText(_labels[i]);
		b->getFont()->setColor(fl_rgb_color(255, 255, 255));
		b->getFont()->setAlignment(FL_ALIGN_LEFT);

		// create a input with the adjusted size.
		s[i] = new Fle_Input(0, 0, _w - b->w() - 32, 25, 0);
		s[i]->box(FL_FLAT_BOX);
		s[i]->justify(FL_ALIGN_LEFT);
		s[i]->color(fl_rgb_color(255, 255, 255));
		s[i]->value(std::string(_values[i]).c_str());
		s[i]->textcolor(fl_rgb_color(0, 0, 0));
		s[i]->textsize(13);

		// end packing.
		l->end();
	}

	// now, create a layout in the statusbar for Ok and Cancel buttons.
	Fle_HLayoutLR* hl1 = d->getStatusBar()->addLayoutLR(23);
	hl1->setBackgroundColor(80, 80, 80);

	// start packing in the statusbar's layout.
	hl1->beginRight();

	// add/pack Ok button first.
	Fle_Button* ok = new Fle_Button(0, 0, 90, 22, "OK");
	ok->color(fl_rgb_color(80, 80, 80));
	ok->selection_color(fl_rgb_color(80, 80, 80));
	ok->labelcolor(fl_rgb_color(255, 255, 255));
	ok->labelsize(12);
	ok->clear_visible_focus();
	d->setOkButton(ok);

	// then, add/pack cancel button.
	Fle_Button* cancel = new Fle_Button(0, 0, 90, 22, "Cancel");
	cancel->color(fl_rgb_color(80, 80, 80));
	cancel->selection_color(fl_rgb_color(80, 80, 80));
	cancel->labelcolor(fl_rgb_color(255, 255, 255));
	cancel->labelsize(12);
	cancel->clear_visible_focus();
	d->setCancelButton(cancel);

	// end packing.
	hl1->endRight();

	// set dialog's margins.
	d->getCentralLayout()->getLayout()->setMargins(10, 10, 15, 0);
	// set statusbar's margins and height.
	d->getStatusBar()->getLayout()->setMargins(10, 10, 10, 0);
	d->setStatusBarFixedHeight(58);

	// disable resizing the window. It will disable the close button also.
	d->setResizeable(false);
	d->hotspot(ok);
	d->set_modal();
	d->show();
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	d->position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);

	while (d->shown())
	{
		Fl::wait();
		Fl_Widget* o;
		while ((o = Fl::readqueue()) && d->shown())
		{
			if (o == ok)
			{
				for (std::size_t i = 0; i < _labels.size(); i++)
					_values[i] = s[i]->value();
				Fl::delete_widget(d);
				return 1;
			}
			else
			{
				if (o == cancel || o == d)
				{
					d->hide();
					Fl::delete_widget(d);
					return 0;
				}
			}
		}
	}
	return 0;
}

int Fle_Dialog::getItem(int _w, int _h, const char* _title, const char* _label, const std::vector<std::string>& _items, int& _selected_index)
{
	Fle_Dialog* d = new Fle_Dialog(_w, _h, _title, 58, 0, 0);
	d->callback(static_dialog_cb, d);
	d->setMargins(10, 10, 10, 10);

	Fle_HLayout* l = d->getCentralLayout()->addHLayout(25);

	l->begin();

	Fl_Choice* s;
	if (_label)
	{
		Fle_Box* b = new Fle_Box(0, 0, _w - 217, 25);
		b->color(fl_rgb_color(80, 80, 80));
		b->setText(_label);
		b->getFont()->setColor(fl_rgb_color(255, 255, 255));
		b->getFont()->setAlignment(FL_ALIGN_LEFT);

		s = new Fl_Choice(0, 0, 189, 25);
	}
	else
	{
		s = new Fl_Choice(0, 0, _w - 20, 25);
	}

	s->box(FL_FLAT_BOX);
	s->down_box(FL_FLAT_BOX);
	s->color(fl_rgb_color(120, 120, 120));
	s->color2(fl_rgb_color(255, 255, 255));
	s->textcolor(fl_rgb_color(255, 255, 255));
	s->textsize(13);
	for (auto const i : _items)
		s->add(std::string(i).c_str());
	s->value(_selected_index);
	s->clear_visible_focus();
	if (_title) s->tooltip(_title);

	l->end();

	Fle_HLayoutLR* hl1 = d->getStatusBar()->addLayoutLR(23);
	hl1->setBackgroundColor(80, 80, 80);

	hl1->beginRight();

	Fle_Button* ok = new Fle_Button(0, 0, 90, 22, "OK");
	ok->color(fl_rgb_color(80, 80, 80));
	ok->selection_color(fl_rgb_color(80, 80, 80));
	ok->labelcolor(fl_rgb_color(255, 255, 255));
	ok->labelsize(12);
	d->setOkButton(ok);

	Fle_Button* cancel = new Fle_Button(0, 0, 90, 22, "Cancel");
	cancel->color(fl_rgb_color(80, 80, 80));
	cancel->selection_color(fl_rgb_color(80, 80, 80));
	cancel->labelcolor(fl_rgb_color(255, 255, 255));
	cancel->labelsize(12);
	d->setCancelButton(cancel);

	hl1->endRight();

	// set dialog's margins.
	d->getCentralLayout()->getLayout()->setMargins(10, 10, 15, 0);
	// set statusbar's margins and height.
	d->getStatusBar()->getLayout()->setMargins(10, 10, 10, 0);
	d->setStatusBarFixedHeight(58);

	d->setResizeable(false);
	d->hotspot(ok);
	d->set_modal();
	d->show();
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	d->position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);

	while (d->shown())
	{
		Fl::wait();
		Fl_Widget* o;
		while ((o = Fl::readqueue()) && d->shown())
		{
			if (o == ok)
			{
				_selected_index = s->value();
				Fl::delete_widget(d);
				return 1;
			}
			else
			{
				if (o == cancel || o == d)
				{
					d->hide();
					Fl::delete_widget(d);
					return 0;
				}
			}
		}
	}
	return 0;
}

int Fle_Dialog::getText(int _w, int _h,
	const char* _title,
	std::string& _text,
	Fle_Font _text_prop,
	const char* _label,
	Fle_Font _label_prop)
{
	return Fle_Dialog::getText(_w, _h,
		_title,
		_text,
		_text_prop,
		_label,
		_label_prop,
		fl_rgb_color(80, 80, 80),
		fl_rgb_color(230, 230, 255));
}
int Fle_Dialog::getText(int _w, int _h,
const char* _title,
std::string& _text,
Fle_Font _text_prop)
{
	return Fle_Dialog::getText(_w, _h, 
		_title, 
		_text, 
		_text_prop,
		nullptr,
		Fle_Font(13, FL_WHITE, FL_ALIGN_LEFT, FL_HELVETICA_BOLD),
		fl_rgb_color(80, 80, 80),
		fl_rgb_color(230, 230, 255));
}


int Fle_Dialog::getText(int _w, int _h, 
	const char* _title, 
	std::string& _text,
	Fle_Font _text_prop,
	const char* _label, 
	Fle_Font _label_prop,
	Fl_Color _text_bkgrnd_color,
	Fl_Color _text_selection_color)
{
	Fle_Dialog* d = new Fle_Dialog(_w, _h, _title, 58, 0, 0);
	d->callback(static_dialog_cb, d);
	d->setMargins(10, 10, 10, 10);

	int lh = 74;

	if (_label)
	{
		d->begin();
		// create a label at the most left size.
		Fle_Box* b = new Fle_Box(0, 0, _w, 25);
		b->color(_text_bkgrnd_color);
		b->setText(_label);
		b->setFont(_label_prop);
		b->setFitToTextEnabled(true);

		Fle_Box* s = new Fle_Box(0, 0, _w, 1);
		s->box(FL_FLAT_BOX);
		s->color(fl_rgb_color(142, 142, 142));

		d->end();

		lh = 110;
	}

	Fle_HLayout* l = d->getCentralLayout()->addHLayout(_h - lh);
	l->begin();

	Fl_Multiline_Input* s = new Fl_Multiline_Input(0, 0, _w - 20, 25);
	s->box(FL_FLAT_BOX);
	s->color(_text_bkgrnd_color);
	s->selection_color(_text_selection_color);
	s->value(std::string(_text).c_str());
	s->align(_text_prop.getAlignment());
	s->textsize(_text_prop.getSize());
	s->textcolor(_text_prop.getColor());
	s->textfont(_text_prop.getFace());

	l->end();

	Fle_HLayoutLR* hl1 = d->getStatusBar()->addLayoutLR(23);
	hl1->setBackgroundColor(80, 80, 80);

	hl1->beginRight();

	Fle_Button* ok = new Fle_Button(0, 0, 90, 22, "OK");
	ok->color(fl_rgb_color(80, 80, 80));
	ok->selection_color(fl_rgb_color(80, 80, 80));
	ok->labelcolor(fl_rgb_color(255, 255, 255));
	ok->labelsize(12);
	d->setOkButton(ok);

	Fle_Button* cancel = new Fle_Button(0, 0, 90, 22, "Cancel");
	cancel->color(fl_rgb_color(80, 80, 80));
	cancel->selection_color(fl_rgb_color(80, 80, 80));
	cancel->labelcolor(fl_rgb_color(255, 255, 255));
	cancel->labelsize(12);
	d->setCancelButton(cancel);

	hl1->endRight();

	// set dialog's margins.
	d->getCentralLayout()->getLayout()->setMargins(10, 10, 10, 0);
	// set statusbar's margins and height.
	d->getStatusBar()->getLayout()->setMargins(10, 16, 10, 0);
	d->setStatusBarFixedHeight(58);

	d->setResizeable(false);
	d->hotspot(ok);
	d->set_modal();
	d->show();
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	d->position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);

	while (d->shown())
	{
		Fl::wait();
		Fl_Widget* o;
		while ((o = Fl::readqueue()) && d->shown())
		{
			if (o == ok)
			{
				_text = s->value();
				Fl::delete_widget(d);
				return 1;
			}
			else
			{
				if (o == cancel || o == d)
				{
					d->hide();
					Fl::delete_widget(d);
					return 0;
				}
			}
		}
	}
	return 0;
}

int Fle_Dialog::openHelpDialog(
	int _w, int _h,
	const char* _title,
	const std::string& _html_text,
	Fle_Font _text_prop,
	const char* _label,
	Fle_Font _label_prop,
	Fl_Color _text_bkgrnd_color,
	Fl_Color _text_selection_color)
{
	Fle_Dialog* d = new Fle_Dialog(_w, _h, _title, 58, 0, 0);
	d->callback(static_dialog_cb, d);
	d->setMargins(10, 10, 10, 10);

	int lh = 74;

	if (_label)
	{
		d->begin();
		// create a label at the most left size.
		Fle_Box* b = new Fle_Box(0, 0, _w, 25);
		b->color(_text_bkgrnd_color);
		b->setText(_label);
		b->setFont(_label_prop);
		b->setFitToTextEnabled(true);

		Fle_Box* s = new Fle_Box(0, 0, _w, 1);
		s->box(FL_FLAT_BOX);
		s->color(fl_rgb_color(142, 142, 142));

		d->end();

		lh = 110;
	}

	Fle_HLayout* l = d->getCentralLayout()->addHLayout(_h - lh);
	l->begin();

	Fl_Help_View* s = new Fl_Help_View(0, 0, _w - 20, 25);
	s->box(FL_FLAT_BOX);
	s->color(_text_bkgrnd_color);
	s->selection_color(_text_selection_color);
	s->value(std::string(_html_text).c_str());
	s->align(_text_prop.getAlignment());
	s->textsize(_text_prop.getSize());
	s->textcolor(_text_prop.getColor());
	s->textfont(_text_prop.getFace());

	l->end();

	Fle_HLayoutLR* hl1 = d->getStatusBar()->addLayoutLR(23);
	hl1->setBackgroundColor(80, 80, 80);

	hl1->beginRight();

	Fle_Button* ok = new Fle_Button(0, 0, 90, 22, "OK");
	ok->color(fl_rgb_color(80, 80, 80));
	ok->selection_color(fl_rgb_color(80, 80, 80));
	ok->labelcolor(fl_rgb_color(255, 255, 255));
	ok->labelsize(12);
	d->setOkButton(ok);

	hl1->endRight();

	// set dialog's margins.
	d->getCentralLayout()->getLayout()->setMargins(10, 10, 10, 0);
	// set statusbar's margins and height.
	d->getStatusBar()->getLayout()->setMargins(10, 16, 10, 0);
	d->setStatusBarFixedHeight(58);

	d->setResizeable(false);
	d->hotspot(ok);
	d->set_modal();
	d->show();
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	d->position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);

	while (d->shown())
	{
		Fl::wait();
		Fl_Widget* o;
		while ((o = Fl::readqueue()) && d->shown())
		{
			if (o == ok)
			{
				Fl::delete_widget(d);
				return 1;
			}
			else
			{
				if (o == d)
				{
					d->hide();
					Fl::delete_widget(d);
					return 0;
				}
			}
		}
	}
	return 0;
}

int Fle_Dialog::ask(int _w, int _h, 			// width and height of the dialog window.
	const char* _title,  						// title of the dialog window.
	const std::string& _text,					// initial value and the returned value of the multi-line text box.
	const char* _1st_btn_text,
	const char* _2nd_btn_text,
	const char* _3rd_btn_text,
	Fle_Font _text_prop,						// _text properties
	Fl_Color _text_bkgrnd_color,				// background color of the text box.
	Fl_Color _text_selection_color)				// text selection color
{
	Fle_Dialog* d = new Fle_Dialog(_w, _h, _title, 58, 0, 0);
	d->callback(static_dialog_cb, d);
	d->setMargins(10, 10, 10, 10);

	int lh = 74;

	Fle_HLayout* l = d->getCentralLayout()->addHLayout(_h - lh);
	l->begin();

	Fl_Help_View* s = new Fl_Help_View(0, 0, _w - 20, 25);
	s->box(FL_FLAT_BOX);
	s->color(_text_bkgrnd_color);
	s->selection_color(_text_selection_color);
	s->value(std::string(_text).c_str());
	s->align(_text_prop.getAlignment());
	s->textsize(_text_prop.getSize());
	s->textcolor(_text_prop.getColor());
	s->textfont(_text_prop.getFace());

	l->end();

	Fle_HLayoutLR* hl1 = d->getStatusBar()->addLayoutLR(23);
	hl1->setBackgroundColor(80, 80, 80);

	hl1->beginRight();

	Fle_Button* yes = new Fle_Button(0, 0, 90, 22, _1st_btn_text);
	yes->color(fl_rgb_color(80, 80, 80));
	yes->selection_color(fl_rgb_color(80, 80, 80));
	yes->labelcolor(fl_rgb_color(255, 255, 255));
	yes->labelsize(12);
	d->setOkButton(yes);

	Fle_Button* no = new Fle_Button(0, 0, 90, 22, _2nd_btn_text);
	no->color(fl_rgb_color(80, 80, 80));
	no->selection_color(fl_rgb_color(80, 80, 80));
	no->labelcolor(fl_rgb_color(255, 255, 255));
	no->labelsize(12);
	d->setCancelButton(no);

	Fle_Button* cancel = nullptr;
	if (_3rd_btn_text)
	{
		cancel = new Fle_Button(0, 0, 90, 22, _3rd_btn_text);
		cancel->color(fl_rgb_color(80, 80, 80));
		cancel->selection_color(fl_rgb_color(80, 80, 80));
		cancel->labelcolor(fl_rgb_color(255, 255, 255));
		cancel->labelsize(12);
	}

	hl1->endRight();

	// set dialog's margins.
	d->getCentralLayout()->getLayout()->setMargins(10, 10, 10, 0);
	// set statusbar's margins and height.
	d->getStatusBar()->getLayout()->setMargins(10, 16, 10, 0);
	d->setStatusBarFixedHeight(58);

	d->setResizeable(false);
	d->hotspot(yes);
	d->set_modal();
	d->show();
	int X, Y, W, H;
	Fl::screen_work_area(X, Y, W, H);
	d->position(X + W / 2 - _w / 2, Y + H / 2 - _h / 2);

	while (d->shown())
	{
		Fl::wait();
		Fl_Widget* o;
		while ((o = Fl::readqueue()) && d->shown())
		{
			if (o == yes)
			{
				Fl::delete_widget(d);
				return 1;
			}
			else
			{
				if (o == no || o == d)
				{
					d->hide();
					Fl::delete_widget(d);
					return 0;
				}
				else if (o == cancel)
				{
					d->hide();
					Fl::delete_widget(d);
					return 2;
				}
			}
		}
	}
	return 0;
}
int Fle_Dialog::ask(
	const char* _title,  						// title of the dialog window.
	const std::string& _text,
	const char* _1st_btn_text,			// first button text.
	const char* _2nd_btn_text,			// 2nd button text.
	const char* _3rd_btn_text			// 3rd button text.
	)
{
	return ask(400, 150, _title, _text, _1st_btn_text, _2nd_btn_text, _3rd_btn_text);
}

int Fle_Dialog::ask(
	const char* _title,  						// title of the dialog window.
	const std::string& _text,
	const char* _1st_btn_text,			// first button text.
	const char* _2nd_btn_text			// 2nd button text.
	)
{
	return ask(_title, _text, _1st_btn_text, _2nd_btn_text, nullptr);
}

int Fle_Dialog::exec()
{
	hotspot(p_ok);
	set_modal();
	show();

	while (visible())
	{
		Fl::wait();
		Fl_Widget* o;
		while ((o = Fl::readqueue()) && visible())
		{
			if (o == p_ok)
			{
				Fl::delete_widget(this);
				return 1;
			}
			else
			{
				if (o == p_cancel || o == this)
				{
					Fl::delete_widget(this);
					return 0;
				}
			}
		}
	}
	return 0;
}
