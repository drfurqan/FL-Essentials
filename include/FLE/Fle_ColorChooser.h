#pragma once
#ifndef Fle_ColorChooser_h__
#define Fle_ColorChooser_h__

/*********************************************************************************
created:	2017/11/22   04:02AM
filename: 	Fle_ColorChooser.h
file base:	Fle_ColorChooser
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized standard color chooser.

usage example:

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Menu_Button.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_ColorChooser : public Fl_Group
{
public:
	// Description:
	// Constructor that's create a color choose widget with dark theme.
	Fle_ColorChooser(int X, int Y, int W, int H, const char *L = 0);

	// Description:
	// Returns which Fl_Color_Chooser variant is currently active
	// return color modes are rgb(0), byte(1), hex(2), or hsv(3)
	int mode() { return choice.value(); }

	// Description:
	// Set which Fl_Color_Chooser variant is currently active
	// param[in] newMode color modes are rgb(0), byte(1), hex(2), or hsv(3)
	void mode(int newMode);

	// Description:
	// Returns the current hue.
	// 0 <= hue < 6. Zero is red, one is yellow, two is green, etc.
	// <em>This value is convenient for the internal calculations - some other
	// systems consider hue to run from zero to one, or from 0 to 360.</em>
	double hue() const { return hue_; }

	// Description:
	// Returns the saturation.
	// 0 <= saturation <= 1.
	double saturation() const { return saturation_; }

	// Description:
	// Returns the value/brightness.
	// 0 <= value <= 1.
	double value() const { return value_; }

	// Description:
	// Returns the current red value.
	// 0 <= r <= 1.
	double r() const { return r_; }

	// Description:
	// Returns the current green value.
	// 0 <= g <= 1.
	double g() const { return g_; }

	// Description:
	// Returns the current blue value.
	// 0 <= b <= 1.
	double b() const { return b_; }

	// Description:
	// Set the hsv values.
	// The passed values are clamped(or for hue, modulus 6 is used) to get
	// legal values.Does not do the callback.
	// param[in] H, S, V color components.
	// return 1 if a new hsv value was set, 0 if the hsv value was the previous one.
	int hsv(double H, double S, double V);

	// Description:
	// Sets the current rgb color values.
	// Does not do the callback.Does not clamp(but out of range values will
	// produce psychedelic effects in the hue selector).
	// param[in] R, G, B color components.
	// return 1 if a new rgb value was set, 0 if the rgb value was the previous one.
	int rgb(double R, double G, double B);

protected:
	Flcc_HueBox huebox;
	Flcc_ValueBox valuebox;
	Fl_Menu_Button choice;
	Flcc_Value_Input rvalue;
	Flcc_Value_Input gvalue;
	Flcc_Value_Input bvalue;
	Fl_Box resize_box;

private:
	double hue_, saturation_, value_;
	double r_, g_, b_;
	void set_valuators();
	static void rgb_cb(Fl_Widget*, void*);
	static void mode_cb(Fl_Widget*, void*);
};

}

#endif // Fle_ColorChooser_h__