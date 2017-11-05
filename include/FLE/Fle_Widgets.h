#pragma once
#ifndef Fle_Widgets_h__
#define Fle_Widgets_h__

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

Example:	This is how you can create various kind of widgets.

Fle_Widgets::createSpinner(80, 21, "Spinner: ", 80);
Fle_Widgets::createValueOutput(80, 21, "Spinner: ", 80, 0.1);
Fle_Widgets::createLabel(21, "Auto: ");
Fle_Widgets::createButton(21, "D:\\play.png");
Fle_Widgets::createButton(80, 21, "Toggle Button", 1, Fle_Widgets::ButtonType::TOGGLE);
Fle_Widgets::createLightButton(80, 21, "Button", 1, Fle_Widgets::ButtonType::TOGGLE);
Fle_Widgets::createCheckButton(80, 21, "Check", 1);
Fle_Widgets::createSeparator(1, 21);
Fle_Widgets::createIntInputSlider(80, 21, "Slider", 1);
Fle_Widgets::createClock(21, 21);
Fle_Widgets::createDial(21, 21, "Slider", 20);
Fl_Menu_Button* mb = Fle_Widgets::createDropDownMenu(100, 21, "Hello");
mb->add("  1", FL_ALT + 'r', 0, 0, FL_MENU_DIVIDER);
mb->add("  2");
mb->add("  3");
mb->value(0);	// set as current item.
Fl_Choice* cm = Fle_Widgets::createChoiceMenu(100, 21, "Hello", 1);
cm->add("  1231", FL_ALT + 'r', 0, 0, FL_MENU_DIVIDER);
cm->add("  2");
cm->add("  3");
cm->value(0);	// set as current item.
Fl_Input_Choice* inm = Fle_Widgets::createInputChoiceMenu(100, 21, "Input Choice: ");
inm->menubutton()->add("  1231", FL_ALT + 'r', 0, 0, FL_MENU_DIVIDER);
inm->menubutton()->add("  2");
inm->menubutton()->add("  3");
inm->value(0);	// set as current item.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Button.h>
#include <FLE/Fle_InputSlider.h>
#include <FLE/Fle_Input.h>
#include <FLE/Fle_Layout.h>
#include <FLE/Fle_Group.h>
#include <FLE/Fle_CheckGroup.h>
#include <FLE/Fle_Spinner.h>

#include <FL/Fl_Pack.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Dial.H>
#include <FL/Fl_Clock.H>
#include <FL/Fl_Spinner.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Light_Button.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_Widgets
{
public:
	// Description:
	// Function to Convert FLTK 24 bit color to 3-channels of RGB.
	// RGB can be accessed by:
	// cv::Vec3b c = toRGB(FL_WHITE);
	// Red =   c[0];
	// Green = c[1];
	// Blue =  c[2];
	static cv::Vec3b toRGB(Fl_Color _color);
	static cv::Vec3b toBGR(Fl_Color _color);
	// Description:
	// Function to Convert RGB color to FLTK 24 bit color.
	static Fl_Color fromRGB(const cv::Vec3b& _rgb);
	// Description:
	// Function to Convert RGB color to FLTK 24 bit color.
	static Fl_Color fromRGB(uchar _r, uchar _g, uchar _b);

	// Description:
	// Function to create a group with a title.
	static Fle_Group* createGroup(int _w, int _h, const char* _title);
	// Description:
	// Description:
	// Function to create a group with a check button.
	static Fle_CheckGroup* createCheckGroup(int _w, int _h, const char* _title);

	// Description:
	// Function to create a box by specifying it's width, height, and text that would be displayed inside the box.
	// if _fit_to_text is true then the box automatically resizes itself to fit the text. 
	// The default alignment of the text is LEFT.
	static Fle_Box* createBox(int _w, int _h, const char* _text, bool _fit_to_text = true);
	// Description:
	// Function to create a box by specifying it's height and text that would be displayed inside the box.
	// This box automatically resizes itself to fit the text. 
	// The default alignment of the text is LEFT.
	static Fle_Box* createBox(int _h, const char* _text);
	// Description:
	// Function to create an image box by specifying it's width, height, and absolute path to image file.
	static Fle_Box* createImageBox(int _w, int _h, const std::string& _image_file_path);
	// Description:
	// Function to create a label box by specifying it's height and text that would be displayed inside the box.
	// This box automatically resizes itself to fit the text. 
	// The default alignment of the text is LEFT.
	// This is overridden function of createBox().
	static Fle_Box* createLabel(int _h, const char* _text, uchar _r = 0, uchar _g = 0, uchar _b = 0);
	// Description:
	// Function to create a input spinner by specifying it's width and height.
	static Fle_Spinner* createSpinner(int _w, int _h, double _value, double _step = 1, double _minumum = 0, double _maximum = 99, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to add a value output widget by specifying it's width and height.
	// Output value is changeable by dragging mouse over the widget.
	static Fl_Value_Output* createValueOutput(int _w, int _h, double _value, double _step = 1, double _minumum = 0, double _maximum = 99, Fl_Callback* _cb = 0, void* _data = 0);


	enum class ButtonType
	{
		NORMAL = 0,
		TOGGLE,
		RADIO
	};
	// Description:
	// Function to create a icon button by specifying it's width and height.
	// A button can be a single image button or a toggle button with two images, 
	// one for ON and second for OFF state. Both images will be resized with the specified _h.
	// If only _on_image_file is specified but not _off_image_file, then only one image is used for the button.
	// If both are specified, then images will be toggled by clicking on it.
	static Fle_Button* createButton(int _w, int _h, const char* _on_image_file, const char* _off_image_file, const cv::Size& _images_size, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create a icon button by specifying it's width and height.
	// A button can be a single image button or a toggle button with two images, 
	// one for ON and second for OFF state. Both images will be resized with the specified _h.
	// If only _on_image_file is specified but not _off_image_file, then only one image is used for the button.
	// If both are specified, then images will be toggled by clicking on it.
	static Fle_Button* createButton(int _w, int _h, const char* _on_image_file, const char* _off_image_file = 0, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create a squared icon button by specifying it's height.
	// A button can be a single image button or a toggle button with two images, 
	// one for ON and second for OFF state. Both images will be resized with the specified _h.
	// If only _on_image_file is specified but not _off_image_file, then only one image is used for the button.
	// If both are specified, then images will be toggled by clicking on it.
	static Fle_Button* createButton(int _h, const char* _on_image_file, const char* _off_image_file = 0, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create a button by specifying it's width, height, label/name, default/initial value, and type.
	// _name is the button text that will be displayed on the button.
	static Fle_Button* createButton(int _w, int _h, const char* _name, int _value, ButtonType _type = ButtonType::NORMAL, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create a button by specifying it's width, height, ON/OFF and icon images.
	static Fle_Button* createButton(int _w, int _h, Fl_RGB_Image* _icon_file_on, Fl_RGB_Image* _icon_file_off, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create a light button by specifying it's width, height, label/name, default/initial value, and type.
	// _name is the button text that will be displayed on the button.
	static Fl_Light_Button* createLightButton(int _w, int _h, const char* _name, int _value = 0, ButtonType _type = ButtonType::NORMAL, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create a check button by specifying it's width, height, label/name, and default/initial value.
	// _name is the button text that will be displayed on the button.
	static Fl_Check_Button* createCheckButton(int _w, int _h, const char* _name, int _value = 0, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create a drop down menu by specifying it's width, height, label/name, and default/initial index.
	static Fl_Menu_Button* createDropDownMenu(int _w, int _h, const char* _label = 0, int _current_index = 0, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create a choice menu by specifying it's width, height, label/name, and default/initial index.
	static Fl_Choice* createChoiceMenu(int _w, int _h, int _current_index = 0, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Description:
	// Function to create a input choice menu by specifying it's width, height, label/name, and default/initial index.
	// _cb is the callback with _data.

	// Callback Example:
	//void choice_cb(Fl_Widget *w, void *userdata)
	//{
	//	// Show info about the picked item
	//	Fl_Input_Choice *choice = (Fl_Input_Choice*)w;
	//	const Fl_Menu_Item *item = choice->menubutton()->mvalue();
	//	printf("*** Choice Callback:\n");
	//	printf("    item label()='%s'\n", item ? item->label() : "(No item)");
	//	printf("    item value()=%d\n", choice->menubutton()->value());
	//	printf("    input value()='%s'\n", choice->input()->value());
	//	printf("    The user %s\n", choice->menubutton()->changed()
	//		? "picked a menu item"
	//		: "typed text");
	//}
	static Fl_Input_Choice* createInputChoiceMenu(int _w, int _h, int _current_index = 0, Fl_Callback* _cb = 0, void* _data = 0);

	// Description:
	// Function to create a slider (with integer numbers) by specifying it's width, height, label/name, and default/initial index.
	// _width is the total width of the slider.
	// _value is the initial value.
	// _step is the increment/decrement step.
	// _minimum and _maximum are the bounds of the slider.
	// _cb is the callback with _data.
	static Fl_Slider* createSlider(int _w, int _h, int _value = 1, int _step = 1, int _minimum = 0, int _maximum = 99, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create a slider (with integer numbers) by specifying it's width, height, label/name, and default/initial index.
	// _width is the total width of the slider.
	// _value is the initial value.
	// _step is the increment/decrement step.
	// _minimum and _maximum are the bounds of the slider.
	// _cb is the callback with _data.
	static Fl_Value_Slider* createValueSlider(int _type, int _w, int _h, int _value = 1, int _step = 1, int _minimum = 0, int _maximum = 99, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create an input slider (with integer numbers) by specifying it's width, height, label/name, and default/initial index.
	// _label is the name of the slider that will display on the left side of the slider.
	// assign _label to 0 or nullptr if no _label is required for this widget.
	// _width is the total width of the slider.
	// _value is the initial value.
	// _step is the increment/decrement step.
	// _minimum and _maximum are the bounds of the slider.
	// _cb is the callback with _data.
	static Fle_InputSlider* createIntInputSlider(int _w, int _h, int _value = 1, int _step = 1, int _minimum = 0, int _maximum = 99, int _textbox_width = 40);
	// Description:
	// Function to create an input slider (with double numbers) by specifying it's width, height, label/name, 
	// and default/initial index.
	// _label is the name of the slider that will display on the left side of the slider.
	// assign _label to 0 or nullptr if no _label is required for this widget.
	// _width is the total width of the slider.
	// _value is the initial value.
	// _step is the increment/decrement step.
	// _minimum and _maximum are the bounds of the slider.
	// _cb is the callback with _data.
	static Fle_FloatInputSlider* createFloatInputSlider(int _w, int _h, double _value = 1, double _step = 0.1, double _minimum = 0, double _maximum = 100, int _textbox_width = 40);

	// Description:
	// Function to create an input widget that gives various justifications with copy and paste feature.
	// _name is the name of the slider that will display on the left side of the slider.
	// assign _name to 0 or nullptr if no name/label is required for this widget.
	// _width is the total width of the slider.
	// _value is the initial value.
	// _name_align is the input text alignment which could be LEFT or RIGHT.
	// _cb is the callback with _data.
	static Fle_Input* createInput(int _w, int _h, const char* _label, const char* _value, Fl_Align _name_align = FL_ALIGN_LEFT, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create an integer type input widget with width, height, and the initial value.
	// _name_align is the input text alignment which could be LEFT or RIGHT.
	// _cb is the callback with _data.
	static Fl_Int_Input* createIntInput(int _w, int _h, const char* _value, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to create an float type input widget with width, height, and the initial value.
	// _name_align is the input text alignment which could be LEFT or RIGHT.
	// _cb is the callback with _data.
	static Fl_Float_Input* createFloatInput(int _w, int _h, const char* _value, Fl_Callback* _cb = 0, void* _data = 0);

	enum class DialType
	{
		STANDARD = 0,
		LINE,
		FILL
	};
	// Description:
	// Function to create a dial widget by specifying it's width, height, label/name, 
	// initial/default value, and type.
	// _name is the name of the slider that will display on the left side of the slider.
	// assign _name to 0 or nullptr if no name/label is required for this widget.
	// _width is the total width of the slider.
	// _value is the initial value.
	// _name_align is the input text alignment which could be LEFT or RIGHT.
	// _cb is the callback with _data.
	static Fl_Dial* createDial(int _w, int _h, double _value, DialType _type = DialType::STANDARD, Fl_Callback* _cb = 0, void* _data = 0);
	// Description:
	// Function to add a clock that show the current clock time.
	static Fl_Clock* createClock(int _w, int _h, Fl_Callback* _cb = 0, void* _data = 0);

	// Description:
	// Function to add a separator between widgets.
	static void createSeparator(int _w = 1, int _h = 25, Fl_Color _color = FL_GRAY);
};

}

#endif // Fle_Widgets_h__