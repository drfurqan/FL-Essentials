/*********************************************************************************
created:	2017/02/04   11:06PM
modified:	2017/02/24   10:39PM
filename: 	Fle_Widgets.h
file base:	Fle_Widgets
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	This class provides the pre-packed widgets to add in any parent.
/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Widgets.h>

using namespace R3D;

cv::Vec3b Fle_Widgets::toRGB(Fl_Color _color)
{
	uchar r = (_color & 0xFF000000) >> 24;
	uchar g = (_color & 0x00FF0000) >> 16;
	uchar b = (_color & 0x0000FF00) >> 8;
	return cv::Vec3b(r, g, b);
}
cv::Vec3b Fle_Widgets::toBGR(Fl_Color _color)
{
	uchar r = (_color & 0xFF000000) >> 24;
	uchar g = (_color & 0x00FF0000) >> 16;
	uchar b = (_color & 0x0000FF00) >> 8;
	return cv::Vec3b(b, g, r);
}
Fl_Color Fle_Widgets::fromRGB(const cv::Vec3b& _rgb)
{
	return fl_rgb_color(_rgb[0], _rgb[1], _rgb[2]);
}
Fl_Color Fle_Widgets::fromRGB(uchar _r, uchar _g, uchar _b)
{
	return fl_rgb_color(_r, _g, _b);
}

int Fle_Widgets::getTextWidth(const char* _text)
{
	int W = 0, H = 0;
	Fl_Box t(0, 0, 1, 1, _text);
	t.measure_label(W, H);

	return W;
}
int Fle_Widgets::getLongestTextWidth(const std::vector<const char*>& _texts)
{
	if (_texts.empty())
		return 0;

	int W = Fle_Widgets::getTextWidth(_texts[0]);
	for (std::size_t i = 0; i < _texts.size(); i++)
	{
		int tw = Fle_Widgets::getTextWidth(_texts[i]);
		if (tw > W)
			W = tw;
	}

	return W;
}

Fle_Group* Fle_Widgets::createGroup(int _w, int _h, const char* _title)
{
	Fle_Group* o = new Fle_Group(0, 0, _w, _h, _title);
	return o;
}
Fle_CheckGroup* Fle_Widgets::createCheckGroup(int _w, int _h, const char* _title)
{
	Fle_CheckGroup* o = new Fle_CheckGroup(0, 0, _w, _h, _title);
	return o;
}

Fle_Spinner* Fle_Widgets::createSpinner(int _w, int _h, double _value, double _step, double _minumum, double _maximum, Fl_Callback* _cb, void* _data)
{
	Fle_Spinner* o = new Fle_Spinner(0, 0, _w, _h);
	o->box(FL_FLAT_BOX);
	o->value(_value);
	o->step(_step);
	o->minimum(_minumum);
	o->maximum(_maximum);
	o->textsize(12);
	if (_cb) o->callback(_cb, _data);
	return o;
}
Fle_Box* Fle_Widgets::createBox(int _w, int _h, const char* _text, bool _fit_to_text)
{
	Fle_Box* o = new Fle_Box(0, 0, _w, _h);
	o->box(FL_FLAT_BOX);
	o->color(fromRGB(0, 122, 204));
	o->getFont()->setColor(fromRGB(0, 0, 0));
	o->setText(_text);
	o->getFont()->setSize(12);
	o->getFont()->setAlignment(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_LEFT | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
	o->setFitToTextEnabled(_fit_to_text);
	o->setMargins(0, 0, 0, 0);
	return o;
}
Fle_Box* Fle_Widgets::createBox(int _h, const char* _text)
{
	return createBox(100, _h, _text, true);
}
Fle_Box* Fle_Widgets::createImageBox(int _w, int _h, const std::string& _image_file_path)
{
	Fle_Box* o = createBox(_w, _h, "", false);
	o->loadImage(_image_file_path);
	return o;
}
Fle_Box* Fle_Widgets::createLabel(int _h, const char* _text, uchar _r, uchar _g, uchar _b)
{
	Fle_Box* o = createBox(_h, _text);
	o->color(fromRGB(_r, _g, _b));
	return o;
}

Fl_Value_Output* Fle_Widgets::createValueOutput(int _w, int _h, double _value, double _step, double _minumum, double _maximum, Fl_Callback* _cb, void* _data)
{
	Fl_Value_Output* o = new Fl_Value_Output(0, 0, _w, _h);
	o->box(FL_FLAT_BOX);
	o->color(FL_WHITE);
	o->value(_value);
	o->step(_step);
	o->minimum(_minumum);
	o->maximum(_maximum);
	o->textsize(12);
	if (_cb) o->callback(_cb, _data);
	return o;
}

Fle_Button* Fle_Widgets::createButton(int _w, int _h, const char* _on_image_file, const char* _off_image_file, const cv::Size& _images_size, Fl_Callback* _cb, void* _data)
{
	Fle_Button *o = new Fle_Button(0, 0, _w, _h, _on_image_file, _off_image_file, _images_size);
	o->box(FL_FLAT_BOX);
	o->clear_visible_focus();
	o->color(fl_rgb_color(214, 219, 233));
	o->color2(fl_rgb_color(253, 244, 191));
	if (_cb) o->callback(_cb, _data);
	return o;
}

Fle_Button* Fle_Widgets::createButton(int _w, int _h, const char* _on_image_file, const char* _off_image_file, Fl_Callback* _cb, void* _data)
{
	return createButton(_w + 2, _h, _on_image_file, _off_image_file, cv::Size(_h, _h), _cb, _data);
}
Fle_Button* Fle_Widgets::createButton(int _h, const char* _on_image_file, const char* _off_image_file, Fl_Callback* _cb, void* _data)
{
	return createButton(_h, _h, _on_image_file, _off_image_file, _cb, _data);
}
Fle_Button* Fle_Widgets::createButton(int _w, int _h, const char* _name, int _value, ButtonType _type, Fl_Callback* _cb, void* _data)
{
	Fle_Button* o = new Fle_Button(0, 0, _w, _h, _name);
	if (_type == Fle_Widgets::ButtonType::NORMAL) o->type(FL_NORMAL_BUTTON);
	else if (_type == Fle_Widgets::ButtonType::TOGGLE) o->type(FL_TOGGLE_BUTTON);
	else if (_type == Fle_Widgets::ButtonType::RADIO) o->type(FL_RADIO_BUTTON);
	o->box(FL_UP_BOX);
	o->clear_visible_focus();
	o->color(fl_rgb_color(214, 219, 233));
	o->color2(fl_rgb_color(253, 244, 191));
	o->labelsize(11);
	o->value(_value);
	if (_cb) o->callback(_cb, _data);
	return o;
}
Fle_Button* Fle_Widgets::createButton(int _w, int _h, Fl_RGB_Image* _icon_file_on, Fl_RGB_Image* _icon_file_off, Fl_Callback* _cb, void* _data)
{
	Fle_Button* o = new Fle_Button(0, 0, _w, _h, _icon_file_on, _icon_file_off);
	o->box(FL_FLAT_BOX);
	o->clear_visible_focus();
	o->color(fl_rgb_color(214, 219, 233));
	o->color2(fl_rgb_color(253, 244, 191));
	if (_cb) o->callback(_cb, _data);
	return o;
}
Fl_Light_Button* Fle_Widgets::createLightButton(int _w, int _h, const char* _name, int _value, ButtonType _type, Fl_Callback* _cb, void* _data)
{
	Fl_Light_Button* o = new Fl_Light_Button(0, 0, _w, _h, _name);
	if (_type == Fle_Widgets::ButtonType::NORMAL) o->type(FL_NORMAL_BUTTON);
	else if (_type == Fle_Widgets::ButtonType::TOGGLE) o->type(FL_TOGGLE_BUTTON);
	else if (_type == Fle_Widgets::ButtonType::RADIO) o->type(FL_RADIO_BUTTON);
	o->box(FL_UP_BOX);
	o->color(fl_rgb_color(214, 219, 233));
	o->labelsize(11);
	o->value(_value);
	if (_cb) o->callback(_cb, _data);
	return o;
}
Fl_Check_Button* Fle_Widgets::createCheckButton(int _w, int _h, const char* _name, int _value)
{
	Fl_Check_Button* o = new Fl_Check_Button(0, 0, _w, _h, _name);
	o->value(_value);
	o->labelsize(11);
	return o;
}

Fl_Menu_Button* Fle_Widgets::createDropDownMenu(int _w, int _h, const char* _label, int _current_index, Fl_Callback* _cb, void* _data)
{
	Fl_Menu_Button* o = new Fl_Menu_Button(0, 0, _w, _h, _label);
	o->box(FL_UP_BOX);
	o->down_box(FL_FLAT_BOX);
	o->color(fl_rgb_color(234, 240, 255));
	o->color2(fl_rgb_color(253, 244, 191));
	o->labelsize(12);
	o->textsize(12);
	o->value(_current_index);
	o->clear_visible_focus();
	if (_label) o->tooltip(_label);
	if (_cb) o->callback(_cb, _data);
	return o;
}

Fl_Choice* Fle_Widgets::createChoiceMenu(int _w, int _h, int _current_index, Fl_Callback* _cb, void* _data)
{
	Fl_Choice* o = new Fl_Choice(0, 0, _w, _h);
	o->box(FL_FLAT_BOX);
	o->down_box(FL_FLAT_BOX);
	o->color(fl_rgb_color(234, 240, 255));
	o->color2(fl_rgb_color(253, 244, 191));
	o->textsize(12);
	o->value(_current_index);
	o->clear_visible_focus();
	if (_cb) o->callback(_cb, _data);
	return o;
}

Fl_Input_Choice* Fle_Widgets::createInputChoiceMenu(int _w, int _h, int _current_index, Fl_Callback* _cb, void* _data)
{
	Fl_Input_Choice* cm = new Fl_Input_Choice(0, 0, _w, _h);
	cm->menubutton()->box(FL_FLAT_BOX);
	cm->menubutton()->down_box(FL_FLAT_BOX);
	cm->menubutton()->color(fl_rgb_color(234, 240, 255));
	cm->menubutton()->color2(fl_rgb_color(253, 244, 191));
	cm->menubutton()->labelsize(12);
	cm->menubutton()->textsize(12);
	cm->menubutton()->value(_current_index);
	cm->box(FL_FLAT_BOX);
	cm->down_box(FL_FLAT_BOX);
	cm->color(fl_rgb_color(214, 219, 233));
	cm->color2(fl_rgb_color(253, 244, 191));
	cm->labelsize(12);
	cm->textsize(12);
	cm->clear_visible_focus();
	if (_cb) cm->callback(_cb, _data);
	return cm;
}
Fl_Slider* Fle_Widgets::createSlider(int _w, int _h, int _value, int _step, int _minimum, int _maximum, Fl_Callback* _cb, void* _data)
{
	Fl_Slider* o = new Fl_Slider(0, 0, _w, _h, 0);
	o->type(FL_HOR_SLIDER);
	o->box(FL_UP_BOX);
	o->labelsize(12);
	o->value(_value);
	o->step(_step);
	o->bounds(_minimum, _maximum);
	if (_cb) o->callback(_cb, _data);
	return o;
}
Fl_Value_Slider* Fle_Widgets::createValueSlider(int _type, int _w, int _h, int _value, int _step, int _minimum, int _maximum, Fl_Callback* _cb, void* _data)
{
	Fl_Value_Slider* o = new Fl_Value_Slider(0, 0, _w, _h, 0);
	o->type(_type);
	o->box(FL_UP_BOX);
	o->labelsize(12);
	o->textsize(12);
	o->value(_value);
	o->step(_step);
	o->bounds(_minimum, _maximum);
	if (_cb) o->callback(_cb, _data);
	return o;
}

Fle_InputSlider* Fle_Widgets::createIntInputSlider(int _w, int _h, int _value, int _step, int _minimum, int _maximum, int _textbox_width)
{
	Fle_InputSlider* o = new Fle_InputSlider(0, 0, _w, _h, 0, _textbox_width);
	o->type(FL_HOR_SLIDER);
	o->box(FL_UP_BOX);
	o->labelsize(12);
	o->textsize(12);
	o->value(_value);
	o->step(_step);
	o->minimum(_minimum);
	o->maximum(_maximum);
	return o;
}

Fle_FloatInputSlider* Fle_Widgets::createFloatInputSlider(int _w, int _h, double _value, double _step, double _minimum, double _maximum, int _textbox_width)
{
	Fle_FloatInputSlider* o = new Fle_FloatInputSlider(0, 0, _w, _h, 0, _textbox_width);
	o->type(FL_HOR_SLIDER);
	o->box(FL_UP_BOX);
	o->labelsize(12);
	o->textsize(12);
	o->step(_step);
	o->value(_value);
	o->bounds(_minimum, _maximum);
	return o;
}

Fle_Input* Fle_Widgets::createInput(int _w, int _h, const char* _label, const char* _value, Fl_Align _name_align, Fl_Callback* _cb, void* _data)
{
	Fle_Input* o = new Fle_Input(0, 0, _w, _h, _label, _name_align);
	o->box(FL_FLAT_BOX);
	o->color(FL_WHITE);
	o->getLabelBox()->labelcolor(FL_BLACK);
	o->justify(FL_ALIGN_LEFT);
	o->value(_value);
	if (_cb) o->callback(_cb, _data);
	return o;
}
Fl_Int_Input* Fle_Widgets::createIntInput(int _w, int _h, const char* _value, Fl_Callback* _cb, void* _data)
{
	Fl_Int_Input* o = new Fl_Int_Input(0, 0, _w, _h, 0);
	o->box(FL_FLAT_BOX);
	o->color(FL_WHITE);
	o->value(_value);
	if (_cb) o->callback(_cb, _data);
	return o;
}
Fl_Float_Input* Fle_Widgets::createFloatInput(int _w, int _h, const char* _value, Fl_Callback* _cb, void* _data)
{
	Fl_Float_Input* o = new Fl_Float_Input(0, 0, _w, _h, 0);
	o->box(FL_FLAT_BOX);
	o->color(FL_WHITE);
	o->value(_value);
	if (_cb) o->callback(_cb, _data);
	return o;
}

Fl_Dial* Fle_Widgets::createDial(int _w, int _h, double _value, DialType _type, Fl_Callback* _cb, void* _data)
{
	Fl_Dial* o = new Fl_Dial(0, 0, _w, _h);
	o->type(static_cast<int>(_type));
	o->color((Fl_Color)238);
	o->selection_color(FL_RED);
	o->labelsize(8);
	o->value(_value);
	if (o) o->callback(_cb, _data);
	return o;
}

Fl_Clock* Fle_Widgets::createClock(int _w, int _h, Fl_Callback* _cb, void* _data)
{
	Fl_Clock* o = new Fl_Clock(0, 0, _w, _h);
	o->box(FL_FLAT_BOX);
	//o->box(FL_OSHADOW_BOX);
	o->color((Fl_Color)238);
	o->selection_color(FL_BLACK);
	o->labelfont(8);
	o->labelsize(10);
	o->align(Fl_Align(130));
	if (o) o->callback(_cb, _data);
	return o;
}

void Fle_Widgets::createSeparator(int _w, int _h, Fl_Color _color)
{
	Fl_Box* o = new Fl_Box(0, 0, _w, _h);
	o->box(FL_FLAT_BOX);
	o->clear_visible_focus();
	o->color(_color);
}

Fle_InputSlider* Fle_Widgets::createInputSlider(int _width, int _height, const char* _label, int _label_width, int _value, int _step, int _minimum, int _maximum, int _value_box_width, Fl_Color _bg_color, Fl_Color _text_color)
{
	auto l = new Fle_HLayout(0, 0, _width, _height);
	l->color(_bg_color);
	l->begin();

	auto box = Fle_Widgets::createBox(_label_width, l->h(), _label, false);		// a text box at the most left corner.
	box->color(l->color());
	box->getFont()->setColor(_text_color);
	box->getFont()->setSize(12);

	auto slider = Fle_Widgets::createIntInputSlider(_width - _label_width, l->h(), _value, _step, _minimum, _maximum, _value_box_width);
	slider->box(FL_GLEAM_UP_BOX);
	slider->color(l->color());
	slider->selection_color(fl_rgb_color(66, 192, 251));
	slider->textcolor(_text_color);
	slider->textsize(11);
	slider->getInput()->tooltip("Specify the desired value and press enter.");
	slider->getSlider()->when(FL_WHEN_RELEASE);

	l->end();

	return slider;
}
Fle_FloatInputSlider* Fle_Widgets::createFloatInputSlider(int _width, int _height, const char* _label, int _label_width, double _value, double _step, double _minimum, double _maximum, int _value_box_width, Fl_Color _bg_color, Fl_Color _text_color)
{
	auto l = new Fle_HLayout(0, 0, _width, _height);
	l->color(_bg_color);
	l->begin();

	auto box = Fle_Widgets::createBox(_label_width, l->h(), _label, false);		// a text box at the most left corner.
	box->color(l->color());
	box->getFont()->setColor(_text_color);
	box->getFont()->setSize(12);

	auto slider = Fle_Widgets::createFloatInputSlider(_width - _label_width, l->h(), _value, _step, _minimum, _maximum, _value_box_width);
	slider->box(FL_GLEAM_UP_BOX);
	slider->color(l->color());
	slider->selection_color(fl_rgb_color(66, 192, 251));
	slider->textcolor(_text_color);
	slider->textsize(11);
	slider->getInput()->tooltip("Specify the desired value and press enter.");
	slider->getSlider()->when(FL_WHEN_RELEASE);

	l->end();

	return slider;
}
Fl_Check_Button* Fle_Widgets::createCheckButton(int _width, int _height, const char* _label, int _label_width, int _value, Fl_Color _bg_color, Fl_Color _text_color)
{
	auto l = new Fle_HLayout(0, 0, _width, _height);
	l->color(_bg_color);
	l->begin();

	auto box = Fle_Widgets::createBox(_label_width, l->h(), _label, false);		// a text box at the most left corner.
	box->color(_bg_color);
	box->getFont()->setColor(_text_color);
	box->getFont()->setSize(12);

	auto btn = Fle_Widgets::createCheckButton(_width, _height, "", 0);
	btn->box(FL_FLAT_BOX);
	btn->down_box(FL_FRAME_BOX);
	btn->align(FL_ALIGN_LEFT);
	btn->color(_bg_color);
	btn->selection_color(fl_rgb_color(66, 192, 251));
	btn->labelsize(20);
	btn->value(_value);

	l->end();

	return btn;
}
Fle_InputWidget* Fle_Widgets::createTextInput(int _width, int _height, const char* _label, int _label_width, const char* _value, Fl_Color _bg_color, Fl_Color _text_color, Fl_Callback* _cb, void* _data)
{
	auto l = new Fle_HLayout(0, 0, _width, _height);
	l->color(_bg_color);
	l->begin();

	auto box = Fle_Widgets::createBox(_label_width, l->h(), _label, false);		// a text box at the most left corner.
	box->color(_bg_color);
	box->getFont()->setColor(_text_color);
	box->getFont()->setSize(12);

	auto s = new Fle_InputWidget(0, 0, _width - box->w() - 5, l->h(), "");
	s->box(FL_BORDER_BOX);
	s->color(_bg_color);
	auto c = toRGB(_bg_color);
	s->setRightClickPopupColor(fl_rgb_color(c[0] - 10, c[1] - 10, c[2] - 10));
	s->setRightClickPopupTextColor(_text_color);
	s->textcolor(_text_color);
	s->textsize(11);

	auto browse = new Fle_Button(0, 0, 30, l->h(), "...");
	browse->box(FL_BORDER_BOX);
	browse->color(_bg_color);
	browse->selection_color(_bg_color);
	browse->labelcolor(_text_color);
	browse->labelsize(12);
	browse->setFixedWidth(30);
	browse->callback(_cb, _data);
	browse->tooltip("Browse for a directory.");

	l->end();

	return s;
}
Fle_Button* Fle_Widgets::createButton(int _width, int _height, const char* _label, int _label_width, const char* _btn_text, Fl_Color _bg_color, Fl_Color _text_color)
{
	auto l = new Fle_HLayout(0, 0, _width, _height);
	l->color(_bg_color);
	l->begin();

	auto box = Fle_Widgets::createBox(_label_width, l->h(), _label, false);
	box->color(_bg_color);
	box->getFont()->setColor(_text_color);
	box->getFont()->setSize(12);

	auto b = new Fle_Button(0, 0, _width - _label_width / 2, l->h(), _btn_text);
	b->color(_bg_color);
	b->selection_color(_bg_color);
	b->labelcolor(_text_color);
	b->labelsize(12);

	l->end();

	return b;
}