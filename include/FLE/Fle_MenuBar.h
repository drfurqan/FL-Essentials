#pragma once
#ifndef Fle_MenuBar_h__
#define Fle_MenuBar_h__

/*********************************************************************************
created:	2017/01/28   06:54AM
filename: 	Fle_MenuBar.h
file base:	Fle_MenuBar
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	A customized menu bar with fixed size and position compatibility.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include <FL/Fl.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_MenuBar : public Fl_Menu_Bar
{
public:
	// Description:
	// Constructor to create a menu bar.
	// Default menu bar style/type is Fl_Boxtype::FL_UP_BOX.
	// Default menu bar items style/type is Fl_Boxtype::FL_FLAT_BOX.
	Fle_MenuBar(int _x, int _y, int _w, int _h, const char* _text = 0);
	// Description:
	// Destructor that releases the images.
	virtual ~Fle_MenuBar();

	// Description:
	// Function to set the main menu bar color in RGB format.
	void setMenuBarColor(uchar _red, uchar _green, uchar _blue);
	// Description:
	// Function to get the main menu bar color in RGB format.
	Fl_Color getMenuBarColor() const;
	// Description:
	// Function to set the menu bar items background color in RGB format;
	void setMenuBarItemsColor(uchar _red, uchar _green, uchar _blue);
	// Description:
	// Function to get the menu bar items background color in RGB format;
	Fl_Color getMenuBarItemsColor() const;
	// Description:
	// Function to set the button color (in RGB format) when it is selected.
	void setSelectionColor(uchar _red, uchar _green, uchar _blue);
	// Description:
	// Function to get the selected button color (in RGB format).
	Fl_Color getSelectionColor() const;

	// Description:
	// Function to set the menu bar box type/style.
	// Default stype is Fl_Boxtype::FL_UP_BOX.
	void setMenuBarBoxType(Fl_Boxtype _type) { m_menubox = _type; }
	// Description:
	// Function to get the menu bar box type/style.
	Fl_Boxtype getMenuBarBoxType() const { return box(); }
	// Description:
	// Function to set the menu bar items box type/style.
	// Default stype is Fl_Boxtype::FL_FLAT_BOX.
	void setMenuBarItemsBoxType(Fl_Boxtype _type) { box(_type); }
	// Description:
	// Function to get the menu bar items box type/style.
	Fl_Boxtype getMenuBarItemsBoxType() const { return box(); }

	// Description:
	// Function to set ON or OFF state of the menu item (checkBox and radio).
	bool setItemState(const char* _item_name, bool _state);
	// Description:
	// Function that returns false if the menu item is not checked and true otherwise.
	bool getItemState(const char* _item_name);
	// Description:
	// Function to set ON or OFF state of the menu item (checkBox and radio).
	bool setItemState(Fl_Callback* _cb, bool _state);
	// Description:
	// Function that returns false if the menu item is not checked and true otherwise.
	bool getItemState(Fl_Callback* _cb);

	// Description:
	// Function to enable the right mouse click menu.
	void setRightClickMenuEnabled(bool _b) { m_isclickmenu = _b; }
	// Description:
	// Function that returns true if the right mouse click menu is enabled.
	bool isRightClickMenuEnabled() const { return m_isclickmenu; }
	// Description:
	// Function to set the callback to the right click menu.
	void setRightClickMenuItems(Fl_Menu_Item* _p, Fl_Callback* _cb, void* _data)
	{
		p_rightclick_menu_items = _p;
		p_rightclick_menu_item_cb = _cb;
		p_rightclick_menu_cb_data = _data;
	}

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
	// Description:
	// Overloaded function that is being called inside the draw() function.
	void draw(int _x, int _y, int _w, int _h);
	
	// Description:
	// Function to handle right mouse click event.
	int handle(int _e);

	Fl_Menu_Item* p_rightclick_menu_items;
	Fl_Callback* p_rightclick_menu_item_cb;
	void* p_rightclick_menu_cb_data;
	bool m_isclickmenu;

	Fl_Color m_menucolor;
	Fl_Boxtype m_menubox;
};

}

#endif // Fle_MenuBar_h__