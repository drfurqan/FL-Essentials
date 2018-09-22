/*********************************************************************************
created:	2017/01/27   04:02AM
filename: 	Fle_Font.h
file base:	Fle_Font
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class to set text/font properties of FLE/FLTK widgets.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Font.h>

using namespace R3D;

Fle_Font::Fle_Font(Fl_Fontsize _size, Fl_Color _color, Fl_Align _align, Fl_Font _font):
	m_size(_size),
	m_color(_color),
	m_align(_align),
	m_font(_font)
{
}
