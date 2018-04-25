/*********************************************************************************
created:	2017/11/04   04:02AM
filename: 	Fle_Tree.cpp
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

#include <FLE/Fle_Tree.h>

#include <FL/Fl_Menu_Button.H>
#include <FL/fl_draw.H>

using namespace R3D;

Fle_Tree::Fle_Tree(int _x, int _y, int _w, int _h, const char* _title) :
Fl_Tree(_x, _y, _w, _h, _title),
p_rightclick_popup_items(nullptr),
p_rightclick_popup_item_cb(nullptr),
p_rightclick_popup_cb_data(nullptr),
m_is_popup(true)
{
	color(fl_rgb_color(255, 255, 255));
	box(Fl_Boxtype::FL_THIN_UP_BOX);
	labelcolor(fl_rgb_color(78, 196, 203));
	item_labelfgcolor(fl_rgb_color(0, 0, 0));
	item_labelsize(13);
	setRightClickPopupColor(fl_rgb_color(234, 240, 255));
	setRightClickPopupTextColor(fl_rgb_color(0, 0, 0));
	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_TOP | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
}

Fle_Tree::~Fle_Tree()
{
}

void Fle_Tree::draw()
{
	Fl_Tree::draw();
}

int Fle_Tree::handle(int _e)
{
	switch (_e)
	{
	case FL_PUSH:	// clicked on tree
		if (Fl::visible_focus() && handle(FL_FOCUS)) 
			Fl::focus(this);

		if (Fl::event_button() == FL_LEFT_MOUSE)
		{
			Fl_Tree_Item* item = root()->find_clicked(prefs(), 0);
			if (!item)	// find clicked?
				break;

			item->deselect();		// deselect every time, otherwise if a item is already selected, click again on it never call the callback function.
		}
		else if (Fl::event_button() == FL_RIGHT_MOUSE)
		{
			Fl_Tree_Item* item = root()->find_clicked(prefs(), 0);
			if (!item)	// find clicked?
				break;

			item->deselect();		// deselect every time, otherwise if a item is already selected, click again on it never call the callback function.

			set_item_focus(item);	// becomes new focus widget, calls redraw() if needed

			if (!item->event_on_label(prefs()))	// label clicked?
				break;

			select_only(item, when());		// select only this item (handles redraw)

			if (p_rightclick_popup_items && m_is_popup)
			{
				Fl_Menu_Button mb(Fl::event_x(), Fl::event_y(), 0, 0);
				mb.box(FL_FLAT_BOX);
				mb.down_box(FL_FLAT_BOX);
				mb.color(m_rclick_pop_clr);
				mb.textcolor(m_rclick_pop_tclr);
				mb.color2(fl_rgb_color(253, 244, 191));
				mb.labelsize(12);
				mb.textsize(12);
				mb.clear_visible_focus();

				mb.menu(p_rightclick_popup_items);
				if(p_rightclick_popup_item_cb && p_rightclick_popup_cb_data)
					mb.callback(p_rightclick_popup_item_cb, p_rightclick_popup_cb_data);
				mb.popup();
			}
			return 1;          // tells caller we handled this event
		}
		break;

	case FL_RELEASE:
		if (Fl::event_button() == FL_LEFT_MOUSE)
		{
		}
		else if (Fl::event_button() == FL_RIGHT_MOUSE)
		{
		}
		break;

	default:
		return Fl_Tree::handle(_e);
	}
	return Fl_Tree::handle(_e);
}

void Fle_Tree::assignUserIcons(Fl_Tree* tree)
{
	static const char *L_folder_xpm[] =
	{
		"11 11 3 1",
		".  c None",
		"x  c #4ec4cb",
		"@  c #4ec4cb",
		"...........",
		".....@@@@..",
		"....@xxxx@.",
		"@@@@@xxxx@@",
		"@xxxxxxxxx@",
		"@xxxxxxxxx@",
		"@xxxxxxxxx@",
		"@xxxxxxxxx@",
		"@xxxxxxxxx@",
		"@xxxxxxxxx@",
		"@@@@@@@@@@@"
	};
	static Fl_Pixmap L_folderpixmap(L_folder_xpm);

	static const char *L_document_xpm[] =
	{
		"5 5 3 1",
		".  c None",
		"x  c #4ec4cb",
		"@  c #4ec4cb",
		".@@@@@.",
		".@xxx@.",
		".@xxx@.",
		".@xxx@.",
		".@@@@@."
	};
	static Fl_Pixmap L_documentpixmap(L_document_xpm);

	// assign user icons to tree items
	for (auto item = tree->first(); item; item = item->next())
		item->usericon(item->has_children() ? &L_folderpixmap : &L_documentpixmap);
}

void Fle_Tree::removeItem(const std::string& _item)
{
	auto item = find_item(_item.c_str());
	if (item) remove(item);

	//for (Fl_Tree_Item* item = first(); item; item = next(item))
	//{
	//	if (_item == std::string(item->label()))
	//		remove(item);
	//}
}

