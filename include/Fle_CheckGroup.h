#pragma once
#ifndef Fle_CheckGroup_h__
#define Fle_CheckGroup_h__

/*********************************************************************************
created:	2017/03/01   01:53PM
filename: 	Fle_CheckGroup.h
file base:	Fle_CheckGroup
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A group that can be toggled active or inactive.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Export.h"

#include <FL/Fl_Group.H>
#include <FL/Fl_Check_Button.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_CheckGroup : public Fl_Group
{

public:
	// Description:
	// Constructor to create a check group with position, size, and a title.
	Fle_CheckGroup(int _x, int _y, int _w, int _h, const char* _title = 0);

	// Description:
	// Function to activate the group.
	void activate();

	// Description:
	// Function to deactivate the group
	void deactivate();

	// Description:
	// Function to get the activation state of this group.
	// It returns 1 on true, and 0 on false.
	int active() const;

	// Description:
	// Function to set the activation state of this group. 
	// 0 deactivates the group, anything else activates it.
	void value(int v);

	// Description:
	// Function to get the activation state of this group.
	int value() const;

	// Description:
	// Function to set the check button's color.
	void setCheckButtonColor(Fl_Color _c);

	// Description:
	// Function to set the title size.
	virtual void labelsize(int _size);

	// Description:
	// Function to set offset between the end of the test and the group box line.
	void setOffsetSize(int _size);

protected:
	void draw();

	Fl_Check_Button* p_chkbtn;
	int m_spacesize;

private:
	void toggle();
	static void toggle_cb(Fl_Widget *w, void *arg);
};

}

#endif // Fle_CheckGroup_h__