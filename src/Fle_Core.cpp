/*********************************************************************************
created:	2017/01/28   03:26AM
filename: 	Fle_Core.h
file base:	Fle_Core
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Core functionalities of Fle lib.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>

#include <FL/Fl.H>
#include <FL/gl.h>						// needed for OpenGL
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_File_Icon.H>
#include <FL/Fl_Tooltip.H>

#include <iostream>

using namespace R3D;

static int __disable_escape_key(int _event)
{
	// disable global escape key exit.
	if (_event == FL_SHORTCUT && Fl::event_key(FL_Escape))
		return 1;
	// disable global main window resizing.
	else if (Fl::event_state(FL_CTRL) && Fl::event_key('+'))
		return 1;
	else if (Fl::event_state(FL_CTRL) && Fl::event_key('-'))
		return 1;

	return 0;
}

void Fle_Core::init(int _theme)
{
	/************************************************************************/
	// FLTK default initialization.
	//Fl::scheme("gleam");						// theme of FLTK widgets.
	Fl::visual(FL_RGB);
	Fl::gl_visual(FL_RGB);
	Fl::use_high_res_GL(1);
	Fl::visible_focus(0);						// disable dotted rectangle to focused widget.
	Fl::set_font(0, "Segoe UI");				// default windows font
	Fl::add_handler(__disable_escape_key);
	Fl::menu_linespacing(10);					// vertical spacing between menu items.
	Fl_File_Icon::load_system_icons();			// load default system icons (for file browser)
	Fl_Tooltip::delay(0.5f);
	FL_NORMAL_SIZE = 13;
	Fl_Tooltip::size(11);
	Fl_Tooltip::color(fl_rgb_color(240, 240, 240));
	Fl_Tooltip::textcolor(fl_rgb_color(87, 87, 87));
	Fl_Tooltip::margin_width(6);
	Fl_Tooltip::margin_height(6);
	fl_register_images();						// Initialize FLTK image lib (essential)

	Fl_Image::scaling_algorithm(Fl_RGB_Scaling::FL_RGB_SCALING_BILINEAR);
	Fl_Image::RGB_scaling(Fl_RGB_Scaling::FL_RGB_SCALING_BILINEAR);
	/************************************************************************/

	uchar r = 74, g = 84, b = 89;

	switch (_theme)
	{
	case DARK_COLOR_THEME:
		r = 74, g = 84, b = 89;
		Fl::set_color(FL_BACKGROUND_COLOR, r, g, b);			// it will change the radio button's background color.
		Fl::set_color(FL_BACKGROUND2_COLOR, 255, 255, 255);		// it will change the radio button's background color.
		Fl::set_color(FL_SELECTION_COLOR, 253, 244, 191);		// it will change the radio button's background color.
		Fl::set_color(FL_DARK3, r, g, b);						// change the FL_MENU_DIVIDER line color
		Fl::set_color(FL_DARK2, r - 20, g - 20, b - 20);		// tool bars
		Fl::set_color(FL_LIGHT3, r - 5, g - 5, b - 5);			// change the FL_MENU_DIVIDER line color
		Fl::set_color(FL_LIGHT2, r, g, b);						// menu bar color
		Fl::set_color(FL_LIGHT1, r + 5, g + 5, b + 5);			// menu bar items color
		Fl::set_color(FL_BLACK, r - 30, g - 30, b - 30);		// change the black color of FLTK widgets to dark gray.
		break;

	case LIGHT_COLOR_THEME:
		r = 234, g = 240, b = 255;
		Fl::set_color(FL_FOREGROUND_COLOR, 0, 0, 0);			// it will change the menu's text color.
		Fl::set_color(FL_BACKGROUND_COLOR, r, g, b);			// it will change the radio button's background color.
		Fl::set_color(FL_BACKGROUND2_COLOR, 255, 255, 255);		// it will change the radio button's background color.
		Fl::set_color(FL_SELECTION_COLOR, 253, 244, 191);		// it will change the radio button's background color.
		Fl::set_color(FL_DARK3, r, g, b);						// change the FL_MENU_DIVIDER line color
		Fl::set_color(FL_DARK2, 184, 189, 203);					// tool bars
		Fl::set_color(FL_LIGHT3, r - 20, g - 20, b - 20);		// change the FL_MENU_DIVIDER line color
		Fl::set_color(FL_LIGHT2, 204, 209, 223);				// menu bar color
		Fl::set_color(FL_LIGHT1, 224, 230, 245);				// menu bar items color
		Fl::set_color(FL_BLACK, r - 10, g - 10, b - 10);		// change the black color of FLTK widgets to dark gray.
		break;

	default: 
		break;
	}

	// to make widgets flat.
	Fl::set_boxtype(Fl_Boxtype::FL_UP_BOX, Fl_Boxtype::FL_FLAT_BOX);			// change box type to flat only.
	Fl::set_boxtype(Fl_Boxtype::FL_DOWN_BOX, Fl_Boxtype::FL_BORDER_BOX);		// change menu check box type to flat only.
	Fl::set_boxtype(Fl_Boxtype::_FL_ROUND_DOWN_BOX, Fl_Boxtype::FL_BORDER_BOX);	// change menu radio box type to flat only.
	Fl::set_boxtype(Fl_Boxtype::_FL_ROUND_UP_BOX, Fl_Boxtype::FL_BORDER_BOX);	// change box type to flat only.
	Fl::box_color(FL_GRAY);
	Fl::set_box_color(FL_GRAY);
	fl_message_hotspot(0);
}

int Fle_Core::exec()
{
	return Fl::run();
}