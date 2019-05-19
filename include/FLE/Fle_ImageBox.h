#pragma once
#ifndef Fle_ImageBox_h__
#define Fle_ImageBox_h__

/*********************************************************************************
created:	2017/01/27   04:02AM
filename: 	Fle_ImageBox.h
file base:	Fle_ImageBox
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	customized image box widget with image zoom/pan support.
			zooming using mouse wheel, vertical and horizontal scrolling is disabled.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_ImageScrollBox.h>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_ImageBox : public Fle_ImageScrollBox
{
public:
	// Description:
	// Constructor to create a box widget inside the parent window.
	// Default box style/type is Fl_Boxtype::FL_NO_BOX.
	// By default, image draw type is ImageDrawType::Fit.
	// Note: zooming only wors with ImageDrawType::Center.
	Fle_ImageBox(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor to release data.
	virtual ~Fle_ImageBox();

protected:
	// Description:
	// Function to handle events.
	virtual int handle(int _event) override;
};

}

#endif // Fle_ImageBox_h__