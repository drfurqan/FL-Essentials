#pragma once
#ifndef Fle_Font_h__
#define Fle_Font_h__

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
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <FL/Fl.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_Font
{
public:
	Fle_Font(Fl_Fontsize _size = 14, Fl_Color _color = FL_FOREGROUND_COLOR,
		Fl_Align _align = FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP,
		Fl_Font _font = FL_HELVETICA);

	// Description:
	// Function to set the size of a font in pixels.
	// This is the approximate height of a font in pixels.
	// see Enumerations.H
	void setSize(Fl_Fontsize _size) { m_size = _size; }
	// Description:
	// Function to get the size of a font in pixels.
	// see Enumerations.H
	Fl_Fontsize getSize() const { return m_size; }

	// Description:
	// Function to set the font face such as FL_HELVETICA, FL_COURIER, FL_TIMES_BOLD, etc.
	// It is an index into the internal font table.
	// see Enumerations.H
	void setFace(Fl_Font _font) { m_font = _font; }
	// Description:
	// Function to set the font face.
	Fl_Font getFace() const { return m_font; }

	// Description:
	// Function to set the color of the text/font.
	// RGB color can be specified like this setColor(fl_rgb_color(255, 255, 255)).
	// see Enumerations.H
	void setColor(Fl_Color _color) { m_color = _color; }
	// Description:
	// Function to set the color of the text/font.
	Fl_Color getColor() const { return m_color; }

	// Description:
	// Function to set the text alignment such as FL_ALIGN_CENTER, FL_ALIGN_TOP etc.
	// see Enumerations.H
	void setAlignment(Fl_Align _align) { m_align = _align; }
	// Description:
	// Function to get the text alignment such as FL_ALIGN_CENTER, FL_ALIGN_TOP etc.
	Fl_Align getAlignment() const { return m_align; }

protected:
	// Description:
	// Size of a font in pixels.
	// This is the approximate height of a font in pixels.
	// see Enumerations.H
	Fl_Fontsize m_size;
	// Description:
	// A font number is an index into the internal font table.
	// see Enumerations.H
	Fl_Font m_font;
	// Description:
	// Font/text color.
	// see Enumerations.H
	Fl_Color m_color;
	// Description:
	// alignment of font/text.
	// FL_ALIGN_CENTER
	// FL_ALIGN_TOP
	// FL_ALIGN_BOTTOM
	// etc.
	// see Enumerations.H
	Fl_Align m_align;
};

}

#endif // Fle_Font_h__