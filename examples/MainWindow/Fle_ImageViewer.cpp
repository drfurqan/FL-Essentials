/*********************************************************************************
created:	2018/08/05   02:02AM
filename: 	Fle_ImageViewer.cpp
file base:	Fle_ImageViewer
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	class that creates a basic GUI based application for
viewing and editing images.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_ImageViewer.h"

#include <FLE/Fle_ImageBox.h>

#include <FLE/Fle_Widgets.h>
#include <FLE/Fle_Dialog.h>
#include <FLE/Fle_FileDialog.h>
#include <FLE/Fle_MessageBox.h>

using namespace R3D;

Fle_ImageViewer::Fle_ImageViewer(int _x, int _y, int _w, int _h, const char* _title, int _icon_index) :
	Fle_MainWindow(_x, _y, _w, _h, _title, _icon_index)
{
	addMenuBar();
	addStatusBar();
	addTopBar();
	addLeftBar();
	addRightBar();

	//p_imgBox = new Fle_ImageScrollBox(0, 0, _w, _h, _title);	// no zooming using mouse wheel, mouse wheel will be used for vertical and horizontal scrolling.
	p_imgBox = new Fle_ImageBox(0, 0, _w, _h, _title);			// zooming using mouse wheel, vertical and horizontal scrolling is disabled.
	p_imgBox->setImageDrawType(Fle_ImageDrawType::Fit);
	p_imgBox->color(color());
	setCentralWidget(p_imgBox);
}

void Fle_ImageViewer::addMenuBar()
{
	auto menu = getMenuBar();

	// start adding menu actions to menubar.
	menu->add(" File /\t Open...\t\t\t", FL_CTRL + 'o', open_image, this);
	menu->add(" File /\t Save As...\t\t\t", 0, save_as_image_cb, this, FL_MENU_DIVIDER);
	menu->add(" File /\t Exit\t\t\t", FL_ALT + FL_F + 4, exit_cb, this);

	menu->add(" Help /\t About...\t\t\t", 0, about_cb, this);

	menu->show();
}
void Fle_ImageViewer::addStatusBar()
{
	auto sb = getStatusBar();
	sb->setFixedHeight(25);

	// add a Left-Right horizontal layout in the statusbar.
	auto layout = sb->addLayoutLR(21);
	layout->setMargins(5, 0, 2, 0);

	// begin to add/pack widgets at the most left side of the statusbar.
	layout->beginLeft();

	auto textbox = Fle_Widgets::createBox(300, 41, "Ready", false);		// a text box at the most left corner.
	textbox->color(sb->color());
	textbox->getFont()->setSize(11);
	textbox->getFont()->setColor(Fl::get_color(FL_FOREGROUND_COLOR));
	sb->setTextBox(textbox);		// set the text box to show messages with time interval.
	sb->setDefaultText("Ready");

	// stop adding/packing widgets at the most left side of the statusbar.
	layout->end();

	sb->show();
}
void Fle_ImageViewer::addTopBar()
{
	auto tb = getTopBar();
	tb->setFixedHeight(25);

	tb->hide();	// hide the bar.
	getMenuBar()->getRightClickPopupItems()[1].hide();	// as the bar is hidden, so hide the right click menu item as well.
}
void Fle_ImageViewer::addLeftBar()
{
	auto tb = getLeftBar();
	tb->setFixedWidth(200);

	tb->show();
}
void Fle_ImageViewer::addRightBar()
{
	auto bar = getRightBar();
	bar->setFixedWidth(200);

	auto layout = bar->addVLayout(bar->h(), Fle_VHLayout::Position::AT_TOP);
	layout->begin();
	{
		auto textBoxWidth = 70;
		auto valueBoxWidth = 30;
		auto margin = 10;

		auto group = new Fle_Group(0, 0, layout->w(), 167, "Group 1");
		group->color(layout->color());
		group->selection_color(Fl::get_color(FL_BACKGROUND_COLOR));
		group->labelcolor(Fl::get_color(FL_FOREGROUND_COLOR));
		group->labelsize(13);
		group->labelfont(FL_BOLD);
		group->begin();

		auto vt = new Fle_VLayout(margin / 2, 25, group->w() - margin, group->h());
		vt->color(group->color());
		vt->begin();
		auto s = Fle_Widgets::createInputSlider(vt->w() - margin, 18, "Value slider", textBoxWidth, 0, 1, -100, 100, valueBoxWidth, group->color(), Fl::get_color(FL_FOREGROUND_COLOR));
		s->getSlider()->when(FL_WHEN_CHANGED);
		vt->end();

		group->end();
	}

	bar->show();
}

int Fle_ImageViewer::mouseRightButtonPressEvent(int _x, int _y)
{
	// mouse should be inside of the central widget.
	if (!Fl::event_inside(p_imgBox))
		return 0;

	static Fl_Menu_Item items[] =
	{
	{ "\t Open...\t",	FL_CTRL + 'o',	open_image, this },
	{ "\t Save As...\t",			0,	save_as_image_cb, this, FL_MENU_DIVIDER },
	{ "\t Exit\t",		FL_ALT + FL_F + 4,	exit_cb, this },
	{ 0 }
	};

	Fl_Menu_Button mb(Fl::event_x(), Fl::event_y(), 0, 0);
	mb.box(FL_FLAT_BOX);
	mb.down_box(FL_FLAT_BOX);
	mb.color(Fl::get_color(FL_LIGHT1));
	mb.textcolor(Fl::get_color(FL_FOREGROUND_COLOR));
	mb.labelsize(12);
	mb.textsize(12);
	mb.clear_visible_focus();
	mb.menu(items);
	mb.popup();

	return 1;	// handle this event of this widget by returning 1. (Don't send this event to the child widgets.)
}

void Fle_ImageViewer::open_image(Fl_Widget* _w, void* _p)
{
	auto v = static_cast<Fle_ImageViewer*>(_p);
	if (!v) return;

	static const std::string filter = "All Supported Formats" "\t" "*.{jpg,jpeg,jpe,jp2,png,bmp,dib,tif,tiff,pgm,pbm,ppm,ras,sr,webp}";

	Fle_FileDialog d;
	const auto n = d.browsSingleFile(filter, "Open File", "image.png");
	if (n > 0)
	{
		if (v->getImageBox()->loadImage(d.getPath(0)), true)
		{
			v->getImageBox()->resetZoom();
			v->getImageBox()->redraw();
			v->getStatusBar()->showMessage("Opened!", 20);
		}
		else
		{
			v->getStatusBar()->showMessage("Couldn't open!", 20);
		}
	}
	v->redraw();
}
void Fle_ImageViewer::save_as_image_cb(Fl_Widget* _w, void* _p)
{
	auto v = static_cast<Fle_ImageViewer*>(_p);
	if (!v) return;

	static const std::string filter = "All Supported Formats" "\t" "*.{jpg,jpeg,jpe,jp2,png,bmp,dib,tif,tiff,pgm,pbm,ppm,ras,sr,webp}";

	Fle_FileDialog d;
	const auto n = d.browsSave(filter, "Save Image As", v->getImageBox()->getFileLocation());
	if (n > 0)
	{
		auto path = d.getPath(0);
		auto ext = Fle_StringUtil::extractFileExt(path);
		std::vector<int> compression_params;
		compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(5);
		if (ext.empty())
			path = path + ".png";

		if (v->getImageBox()->saveImage(path, compression_params))
			v->getStatusBar()->showMessage("Image has been saved successfully!", 20);
	}
	else
	{
		v->getStatusBar()->showMessage("Couldn't open the file!", 20);
	}
}
void Fle_ImageViewer::exit_cb(Fl_Widget* _w, void* _p)
{
	auto v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	//v->closeEvent();
	exit(0);
}
void Fle_ImageViewer::about_cb(Fl_Widget* _w, void* _p)
{
	auto v = static_cast<Fle_ImageViewer*>(_p);
	if (!v) return;

	v->getStatusBar()->showMessage("Author: Dr.-Ing. Furqan Ullah", 100000);

	std::ostringstream sstream;
	sstream <<
		"Example image viewer to use FL-Essentials API. It is written in <a href=\"https://github.com/drfurqan/FL-Essentials/\">FL-Essentials</a> v1.5.x."
		"<p>Author: Dr. Furqan Ullah</p>"
		"<p>Release Date: 2019/05/15 04:15AM</p>"
		"<p>Copyright(C) 2017-2019</p>"
		"<p><a href=\"http://real3d.pk/\">Website</a> " << "and <a href=\"https://www.youtube.com/user/furqanMax/\">Videos</a></p>"
		"<p><i>For all questions and bug reports, email to info@real3d.pk.</i></p>";

	if (Fle_Dialog::openHelpDialog(
		400, 290,
		"About",
		sstream.str(),
		Fle_Font(11, Fl::get_color(FL_BACKGROUND2_COLOR)),
		"FL-Essentials Image Viewer",
		Fle_Font(14, Fl::get_color(FL_BACKGROUND2_COLOR), FL_ALIGN_CENTER, FL_BOLD)),
		Fl::get_color(FL_BACKGROUND_COLOR),
		Fl::get_color(FL_SELECTION_COLOR),
		Fl::get_color(FL_BACKGROUND_COLOR))
	{
		v->getStatusBar()->showMessage("Ready", 100000);
	}
}
