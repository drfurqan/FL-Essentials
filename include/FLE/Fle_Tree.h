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

purpose:	Customized tree widget with some necessary functionalities.

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
	// Constructor to create a tree widget by specifying it's size, position, and title.
	Fle_Tree(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Description:
	// Destructor to release data.
	virtual ~Fle_Tree();

	// Description:
	// Function to add items (file paths e.g. D:\\file.jpg) to the the tree node.
	void addItems(const std::vector<std::string>& _items, const std::string& _main_node);
	// Description:
	// Function to remove the tree item by specifying its name.
	void removeItem(const std::string& _item);

	// Description:
	// Static function to assign the default icons to the tree items.
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