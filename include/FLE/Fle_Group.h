#pragma once
#ifndef Fle_Group_h__
#define Fle_Group_h__

/*********************************************************************************
created:	2017/03/01   01:48PM
filename: 	Fle_Group.h
file base:	Fle_Group
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A group with a title.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <FL/Fl_Group.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_Group : public Fl_Group
{

public:
	// Description:
	// Constructor to create a group with position, size, and a title.
	Fle_Group(int _x, int _y, int _w, int _h, const char* _title = 0);

protected:
	virtual void draw() override;
};

}

#endif // Fle_Group_h__