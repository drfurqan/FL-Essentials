/*********************************************************************************
created:	2017/11/04   04:02AM
filename: 	Fle_Tree.cpp
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

#include <FLE/Fle_Tree.h>
#include <FLE/Fle_StringUtil.h>

#include <FL/fl_draw.H>

using namespace R3D;

Fle_Tree::Fle_Tree(int _x, int _y, int _w, int _h, const char* _title) :
Fl_Tree(_x, _y, _w, _h, _title)
{
	color(fl_rgb_color(255, 255, 255));
	box(Fl_Boxtype::FL_THIN_UP_BOX);
	labelcolor(fl_rgb_color(78, 196, 203));
	item_labelfgcolor(fl_rgb_color(0, 0, 0));
	item_labelsize(13);

	root()->labelsize(14);
	//root()->labelfont(FL_BOLD);
	root_label("Project");

	align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TEXT_OVER_IMAGE | FL_ALIGN_CLIP);
}

Fle_Tree::~Fle_Tree()
{
}

void Fle_Tree::draw()
{
	Fl_Tree::draw();
}

void Fle_Tree::assignUserIcons(Fl_Tree* tree)
{
	static const char *L_folder_xpm[] =
	{
		"11 11 3 1",
		".  c None",
		"x  c #d8d833",
		"@  c #808011",
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
		"11 11 3 1",
		".  c None",
		"x  c #d8d8f8",
		"@  c #202060",
		".@@@@@@@@@.",
		".@xxxxxxx@.",
		".@xxxxxxx@.",
		".@xxxxxxx@.",
		".@xxxxxxx@.",
		".@xxxxxxx@.",
		".@xxxxxxx@.",
		".@xxxxxxx@.",
		".@xxxxxxx@.",
		".@xxxxxxx@.",
		".@@@@@@@@@."
	};
	static Fl_Pixmap L_documentpixmap(L_document_xpm);

	// assign user icons to tree items
	for (Fl_Tree_Item *item = tree->first(); item; item = item->next())
		item->usericon(item->has_children() ? &L_folderpixmap : &L_documentpixmap);
}

void Fle_Tree::setItemTextSize(int _size)
{
	for (Fl_Tree_Item* item = first(); item; item = next(item))
		item->labelsize(_size);
	redraw();
}

void Fle_Tree::addItems(const std::vector<std::string>& _items, const std::string& _main_node)
{
	if (_items.empty() || _main_node.empty()) return;

	begin();
	for (std::size_t i = 0; i < _items.size(); i++)
	{
		std::string s = _main_node + "/" + Fle_StringUtil::extractFileNameWithoutExt(_items[i]);
		add(s.c_str());
	}
	close(_main_node.c_str());
	end();
}

void Fle_Tree::removeItem(const std::string& _item)
{
	Fl_Tree_Item* item = find_item(_item.c_str());
	if (item) remove(item);

	//for (Fl_Tree_Item* item = first(); item; item = next(item))
	//{
	//	if (_item == std::string(item->label()))
	//		remove(item);
	//}
}

