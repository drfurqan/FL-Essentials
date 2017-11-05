#pragma once
#ifndef Fle_Tree_h__
#define Fle_Tree_h__

/*********************************************************************************
created:	2017/11/04   04:02AM
filename: 	Fle_Tree.h
file base:	Fle_Tree
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Customized box widget with some necessary functionalities that I don't
			find in Fl_Box. setImage() method is thread-safe, you can easily update
			the image in another thread.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <FL/Fl_Tree.H>
#include <FL/Fl_Tree_Item.H>

#include <string>
#include <vector>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_Tree : public Fl_Tree
{
public:
	// Description:
	// Constructor to create a box widget inside the parent window.
	// Default box style/type is Fl_Boxtype::FL_NO_BOX.
	// Default box position is move-able with setPositionFixed(false).
	// Default box width is expand-able with setWidthFixed(false).
	// Default box height is expand-able with setHeightFixed(false).
	// Default margins are zero with setMargins(0,0,0,0).
	// By default Box_Widget does not automatically resizes itself to fit the text with setFitToTextEnabled(false). 
	// By default, image draw type is ImageDrawType::Fit.
	// Note: zooming only wors with ImageDrawType::Center.
	Fle_Tree(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor to release data.
	virtual ~Fle_Tree();

	void addItems(const std::vector<std::string>& _items, const std::string& _main_node);
	void removeItem(const std::string& _item);

	void setItemTextSize(int _size);

	static void assignUserIcons(Fl_Tree* tree);

protected:
	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// drawing FLTK widgets such as 
	// fl_rectf
	// fl_rect
	// fl_line
	// fl_loop
	// fl_polygon
	// fl_arc
	// fl_pie
	virtual void draw();
};

}

#endif // Fle_Tree_h__