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

#include <FLE/Fle_MenuBar.h>

#include <FL/fl_draw.H>

using namespace R3D;

Fle_MenuBar::Fle_MenuBar(int _x, int _y, int _w, int _h, const char* _text) :
Fl_Menu_Bar(_x, _y, _w, _h, _text),
m_menubox(Fl_Boxtype::FL_UP_BOX),
p_rightclick_menu_items(nullptr),
p_rightclick_menu_item_cb(nullptr),
p_rightclick_menu_cb_data(nullptr),
m_isclickmenu(true)
{
	// Qt colors
	//setMenuBarColor(255, 255, 255);
	//setMenuBarItemsColor(240, 240, 240);
	//setSelectionColor(144, 200, 246);
	// MS VS2013 colors
	setMenuBarColor(214, 219, 233);
	setMenuBarItemsColor(234, 240, 255);
	setSelectionColor(253, 244, 191);
	box(Fl_Boxtype::FL_FLAT_BOX);
	down_box(Fl_Boxtype::FL_FLAT_BOX);
	textsize(12);
	textfont(FL_HELVETICA);
	align(FL_ALIGN_WRAP | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
}

Fle_MenuBar::~Fle_MenuBar()
{
}

void Fle_MenuBar::draw()
{
	draw(Fl_Menu_Bar::x(), Fl_Menu_Bar::y(), Fl_Menu_Bar::w(), Fl_Menu_Bar::h());
}
void Fle_MenuBar::draw(int _x, int _y, int _w, int _h)
{
	draw_box(m_menubox, _x, _y, _w, _h, m_menucolor);
	if (!menu() || !menu()->text) return;
	const Fl_Menu_Item* m;
	int X = _x + 6;
	for (m = menu()->first(); m->text; m = m->next())
	{
		int W = m->measure(0, this) + 16;
		m->draw(X, _y, W, _h, this);
		X += W;
		if (m->flags & FL_MENU_DIVIDER)
		{
			int y1 = _y + Fl::box_dy(box());
			int y2 = y1 + _h - Fl::box_dh(box()) - 1;

			// Draw a vertical divider between menus.
			fl_color(FL_DARK3);
			fl_yxline(X - 6, y1, y2);
			fl_color(FL_LIGHT3);
			fl_yxline(X - 5, y1, y2);
		}
	}
}

int Fle_MenuBar::handle(int _e)
{
	switch (_e) 
	{
	case FL_PUSH:
		if (Fl::event_button() == FL_RIGHT_MOUSE) 
		{
			if (p_rightclick_menu_items && p_rightclick_menu_item_cb && p_rightclick_menu_cb_data && m_isclickmenu)
			{
				Fl_Menu_Button mb(Fl::event_x(), Fl::event_y(), 0, 0);
				mb.box(FL_FLAT_BOX);
				mb.down_box(FL_FLAT_BOX);
				//mb.color(fl_rgb_color(242, 244, 254));
				mb.color(fl_rgb_color(234, 240, 255));
				mb.color2(fl_rgb_color(253, 244, 191));
				mb.labelsize(12);
				mb.textsize(12);
				mb.clear_visible_focus();

				mb.menu(p_rightclick_menu_items);
				mb.callback(p_rightclick_menu_item_cb, p_rightclick_menu_cb_data);
				mb.popup();
			}
			return 1;          // tells caller we handled this event
		}
		break;

	case FL_RELEASE:
		if (Fl::event_button() == FL_RIGHT_MOUSE) 
		{
			return 1;          // tells caller we handled this event
		}
		break;
	}
	return Fl_Menu_Bar::handle(_e);
}

void Fle_MenuBar::setMenuBarItemsColor(uchar _red, uchar _green, uchar _blue)
{
	Fl_Menu_Bar::color(fl_rgb_color(_red, _green, _blue));
}
Fl_Color Fle_MenuBar::getMenuBarItemsColor() const
{
	return Fl_Menu_Bar::color();
}
void Fle_MenuBar::setMenuBarColor(uchar _red, uchar _green, uchar _blue)
{
	m_menucolor = fl_rgb_color(_red, _green, _blue);
}
Fl_Color Fle_MenuBar::getMenuBarColor() const
{
	return m_menucolor;
}
void Fle_MenuBar::setSelectionColor(uchar _red, uchar _green, uchar _blue)
{
	Fl_Menu_Bar::selection_color(fl_rgb_color(_red, _green, _blue));
}
Fl_Color Fle_MenuBar::getSelectionColor() const
{
	return Fl_Menu_Bar::selection_color();
	//uchar r = (c & 0xFF000000) >> 24;
	//uchar g = (c & 0x00FF0000) >> 16;
	//uchar b = (c & 0x0000FF00) >> 8;
	//return cv::Vec3b(r, g, b);
}

bool Fle_MenuBar::setItemState(const char* _item_name, bool _state)
{
	Fl_Menu_Item* m = (Fl_Menu_Item*)find_item(_item_name);
	if (m)
	{
		if (_state) m->set();
		else m->clear();

		return true;
	}
	return false;
}
bool Fle_MenuBar::getItemState(const char* _item_name)
{
	Fl_Menu_Item* m = (Fl_Menu_Item*)find_item(_item_name);
	if (m)
	{
		if (m->value())
			return true;
	}
	return false;
}
bool Fle_MenuBar::setItemState(Fl_Callback* _cb, bool _state)
{
	Fl_Menu_Item* m = (Fl_Menu_Item*)find_item(_cb);
	if (m)
	{
		if (_state) m->set();
		else m->clear();
		
		return true;
	}
	return false;
}
bool Fle_MenuBar::getItemState(Fl_Callback* _cb)
{
	Fl_Menu_Item* m = (Fl_Menu_Item*)find_item(_cb);
	if (m)
	{
		if (m->value())
			return true;
	}
	return false;
}
