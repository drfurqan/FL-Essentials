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
Copyright (C) 2014-2019 REAL3D

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
	// Function to get a pointer to clicked item.
	// clicked item is actually set to the focused item in handle() event, so, this is actually retuning a clicked item.
	Fl_Tree_Item * getClickedItem() const { return get_item_focus(); }

	// Description:
	// Function to remove the tree item by specifying its name.
	void removeItem(const std::string& _item);

	// Description:
	// Static function to assign the default icons to the tree items.
	static void assignUserIcons(Fl_Tree* tree);

	// Description:
	// Function to enable the right mouse click menu.
	void setRightClickPopupEnabled(bool _b) { m_is_popup = _b; }
	// Description:
	// Function that returns true if the right mouse click menu is enabled.
	bool isRightClickPopupEnabled() const { return m_is_popup; }
	// Description:
	// Function to set popup items, callback, and the user data.
	// The popup window that will appear when a use right clicks on the menu bar.
	void setRightClickPopupCallback(Fl_Menu_Item* _popup_items, Fl_Callback* _cb, void* _data)
	{
		p_rightclick_popup_items = _popup_items;
		p_rightclick_popup_item_cb = _cb;
		p_rightclick_popup_cb_data = _data;
	}
	// Description:
	// Function to set popup menu items.
	// The popup window that will appear when a use right clicks on the menu bar.
	// Usage Example:
	// static Fl_Menu_Item items[] =
	// {
	//	 { "\tUpdate Label...\t\t", 0, update_label_cb, this, 0 },

	// { 0 }
	// };
	// p_tree->setRightClickPopupMenuItems(items);
	void setRightClickPopupMenuItems(Fl_Menu_Item* _popup_items) { p_rightclick_popup_items = _popup_items; }

	// Description:
	// Function to set a pointer to right click popup items.
	void setRightClickPopupItems(Fl_Menu_Item* _p) { p_rightclick_popup_items = _p; }
	// Description:
	// Function to get a pointer to right click popup items.
	Fl_Menu_Item* getRightClickPopupItems() const { return p_rightclick_popup_items; }
	// Description:
	// Function to set a color to the right click popup window.
	void setRightClickPopupColor(Fl_Color _color) { m_rclick_pop_clr = _color; }
	// Description:
	// Function to get a color of the right click popup window.
	Fl_Color getRightClickPopupColor(Fl_Color _color) const { return m_rclick_pop_clr; }
	// Description:
	// Function to set a color to the right click popup window.
	void setRightClickPopupTextColor(Fl_Color _color) { m_rclick_pop_tclr = _color; }
	// Description:
	// Function to get a color of the right click popup window.
	Fl_Color getRightClickPopupTextColor(Fl_Color _color) const { return m_rclick_pop_tclr; }

protected:
	// Description:
	// Function to handle right mouse click event.
	int handle(int _e) override;
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
	virtual void draw() override;

	Fl_Menu_Item* p_rightclick_popup_items;
	Fl_Callback* p_rightclick_popup_item_cb;
	void* p_rightclick_popup_cb_data;
	bool m_is_popup;

	Fl_Color m_rclick_pop_clr;
	Fl_Color m_rclick_pop_tclr;
};

}

#endif // Fle_Tree_h__