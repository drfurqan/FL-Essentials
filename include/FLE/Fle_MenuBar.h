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
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

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
	// Function to set the main menu bar color in RGB format.
	void setMenuBarColor(Fl_Color _color) { m_menucolor = _color; }
	// Description:
	// Function to get the main menu bar color in RGB format.
	Fl_Color getMenuBarColor() const;
	// Description:
	// Function to set the menu bar items background color in RGB format;
	void setMenuBarItemsColor(uchar _red, uchar _green, uchar _blue);
	// Description:
	// Function to set the menu bar items background color in RGB format;
	void setMenuBarItemsColor(Fl_Color _color);
	// Description:
	// Function to get the menu bar items background color in RGB format;
	Fl_Color getMenuBarItemsColor() const;
	// Description:
	// Function to set the button color (in RGB format) when it is selected.
	void setSelectionColor(uchar _red, uchar _green, uchar _blue);
	// Description:
	// Function to set the button color (in RGB format) when it is selected.
	void setSelectionColor(Fl_Color _color);
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
	// Function to set ON or OFF state of the radio menu item.
	bool setRadioItemOn(const char* _item_name, bool _state);
	// Description:
	// Function that returns false if the menu item is not checked and true otherwise.
	bool isRadioItemOn(const char* _item_name);
	// Description:
	// Function to set ON or OFF state of the radio menu item.
	bool setRadioItemOn(Fl_Callback* _cb, bool _state);
	// Description:
	// Function that returns false if the menu item is not checked and true otherwise.
	bool isRadioItemOn(Fl_Callback* _cb);

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
	// Function to set active or deactive menu item.
	bool setItemActive(const char* _item_name, bool _state);
	// Description:
	// Function that returns true if the menu item is active.
	bool isItemActive(const char* _item_name);
	// Description:
	// Function to set active or deactive menu item.
	bool setItemActive(Fl_Callback* _cb, bool _state);
	// Description:
	// Function that returns true if the menu item is active.
	bool isItemActive(Fl_Callback* _cb);

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
	// menubar->setRightClickPopupMenuItems(items);
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
	// Description:
	// Overloaded function that is being called inside the draw() function.
	void draw(int _x, int _y, int _w, int _h);
	
	// Description:
	// Function to handle right mouse click event.
	int handle(int _e) override;

	Fl_Menu_Item* p_rightclick_popup_items;
	Fl_Callback* p_rightclick_popup_item_cb;
	void* p_rightclick_popup_cb_data;
	bool m_is_popup;

	Fl_Color m_menucolor;
	Fl_Color m_rclick_pop_clr;
	Fl_Color m_rclick_pop_tclr;
	Fl_Boxtype m_menubox;
};

}

#endif // Fle_MenuBar_h__