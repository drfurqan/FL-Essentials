#pragma once
#ifndef Fle_ProgressBar_h__
#define Fle_ProgressBar_h__
/*********************************************************************************
created:	2017/03/01   04:50AM
filename: 	Fle_ProgressBar.h
file base:	Fle_ProgressBar
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A class for a progress bar.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Export.h"
#include <FL/Fl_Valuator.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_ProgressBar : public Fl_Valuator
{
public:
	// Description:
	// Constructor to create a slider type progress bar with position, size.
	Fle_ProgressBar(int _x, int _y, int _w, int _h, const char* _lable = 0);

	// Description:
	// Function to set the current value.
	int value(double _value);

	// Description:
	// Function to get the current value.
	double value() const;

protected:
	void draw();

};

}

#endif // Fle_ProgressBar_h__