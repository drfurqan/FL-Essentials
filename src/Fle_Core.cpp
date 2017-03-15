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
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Core.h"

#include <FL/Fl.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/glut.H>            // needed for OpenGL

#include <iostream>

using namespace R3D;

void Fle_Core::init()
{
	/************************************************************************/
	// FLTK default initialization.
	Fl::scheme("gleam");						// theme of FLTK widgets.
	Fl::visual(FL_DOUBLE | FL_RGB8  | FL_INDEX | FL_ALPHA | FL_MULTISAMPLE);
	Fl::gl_visual(FL_DOUBLE | FL_RGB8 | FL_DEPTH | FL_ACCUM | FL_ALPHA | FL_STENCIL | FL_MULTISAMPLE);
	Fl::use_high_res_GL(1);
	fl_register_images();						// Initialize FLTK image lib (essential)
	Fl::set_color(FL_BLACK, 50, 50, 50);		// change the black color of FLTK widgets to dark gray.
	Fl::box_color(FL_GRAY);
	Fl::set_box_color(FL_GRAY);
	Fl::visible_focus(0);						// disable dotted rectangle to focused widget.
	Fl::set_font(0, "Segoe UI");				// default windows font
	std::cout << Fl::get_font(0) << std::endl;
	/************************************************************************/
}

int Fle_Core::exec()
{
	return Fl::run();
}