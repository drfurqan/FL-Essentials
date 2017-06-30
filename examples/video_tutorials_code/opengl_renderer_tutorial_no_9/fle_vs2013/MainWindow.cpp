/*********************************************************************************
created:	2017/04/28   04:56PM
filename: 	GLRenderer.cpp
file base:	GLRenderer
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	class that creates a main windows with menu, statusbar, GL renderer, etc.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "MainWindow.h"
#include <FLE/Fle_Widgets.h>
#include <FLE/Fle_Dialog.h>
#include <FLE/Fle_FileDialog.h>

MainWindow::MainWindow(int _w, int _h, const char* _title) : Fle_MainWindow(_w, _h, _title)
{
	callback(exit_cb, this);
	setMargins(0, 0, 1, 2);
	addMenuBar();
	getMenuBar()->setRightClickMenuEnabled(false);
	addStatusBar();

	remove(0);	// remove the previous embedded widget in the central widget.

	// add a new GLRenderer widget in the central widget.
	begin();
	p_renderer = new GLRenderer(0, 0, getCentralWidget()->w(), getCentralWidget()->h(), _title);
	end();
}

void MainWindow::addMenuBar()
{
	getMenuBar()->show();
	setMenuBarFixedHeight(25);
	{
		// add items to menubar.
		Fle_MenuBar* menu = getMenuBar();
		menu->add(" File /\tNew\t\t\t", FL_CTRL + 'n', new_cb, this);
		menu->add(" File /\tOpen...\t\t\t", FL_CTRL + 'o', open_cb, this);
		menu->add(" File /\tOpen Texture...\t\t\t", FL_CTRL + 't', texture_cb, this, FL_MENU_DIVIDER);
		menu->add(" File /\tExit\t\t\t", FL_ALT + FL_F + 4, exit_cb, this);
		menu->add(" View /   Animation\t\t\t", FL_ALT + 'a', animation_cb, this, FL_MENU_TOGGLE);
		menu->add(" Help /\tWebsite\t\t\t", FL_CTRL + FL_F + 1, website_cb, this);
		menu->add(" Help /\tDownload\t\t\t", 0, download_cb, this, FL_MENU_DIVIDER);
		menu->add(" Help /\tAbout\t\t\t", 0, about_cb, this);
	}
}
void MainWindow::exit_cb(Fl_Widget* _w, void* _p)
{
	MainWindow* v = static_cast<MainWindow*>(_p);
	if (!v) return;

	if (Fle_Dialog::ask(400, 150, "Warning", "Are you sure you want to close?") == 1)
		v->hide();
}

void MainWindow::addStatusBar()
{
	// set fixed width and margins to statusbar.
	getStatusBar()->show();
	getStatusBar()->setMargins(5, 15, 0, 0);
	setStatusBarFixedHeight(45);
	{
		// add a Left-Right horizontal layout in the statusbar.
		Fle_HLayoutLR* layout = getStatusBar()->addLayoutLR(41);
		layout->setMargins(0, 0, 2, 0);
		layout->setBackgroundColor(0, 122, 204);

		// begin to add/pack widgets at the most left side of the statusbar.
		layout->beginLeft();
		{
			Fle_Box* p_textbox = Fle_Widgets::createBox(300, 41, "Ready", false);		// a text box at the most left corner.
			//p_textbox->color(Fle_Widgets::fromRGB(60, 176, 205));
			p_textbox->getFont()->setSize(12);
			p_textbox->getFont()->setColor(Fle_Widgets::fromRGB(255, 255, 255));
			getStatusBar()->setTextBox(p_textbox);		// set the text box to show messages with time interval.
		}
		layout->endLeft();

		// begin to add/pack widgets at the most right side of the statusbar.
		layout->beginRight();
	}
}

void MainWindow::new_cb(Fl_Widget* _w, void* _p)
{
	MainWindow* v = static_cast<MainWindow*>(_p);
	if (!v) return;
	v->p_renderer->mesh.clear();
	v->getStatusBar()->showMessage("Done!", 5);
}

void MainWindow::open_cb(Fl_Widget* _w, void* _p)
{
	MainWindow* v = static_cast<MainWindow*>(_p);
	if (!v) return;

	static const std::string filter = "All Supported Formats" "\t" "*.{ply}";

	Fle_FileDialog d;
	int n = d.browsSingleFile(filter, "Open File");
	if (n > 0)
	{
		std::string file = d.getPath(0);
		v->p_renderer->loadMesh(file);
		v->getStatusBar()->showMessage("3D file has been successfully loaded!", 10);
	}
	else
	{
		v->getStatusBar()->showMessage("Couldn't open the file!", 5);
	}
}

void MainWindow::texture_cb(Fl_Widget* _w, void* _p)
{
	MainWindow* v = static_cast<MainWindow*>(_p);
	if (!v) return;

	static const std::string filter = "All Supported Formats" "\t" "*.{jpg,jpeg,jpe,jp2,png,bmp,tif,tiff,pgm,pbm,ppm,ras,sr}";

	Fle_FileDialog d;
	int n = d.browsSingleFile(filter, "Open File");
	if (n > 0)
	{
		std::string file = d.getPath(0);
		v->p_renderer->loadTexture(file);
		v->getStatusBar()->showMessage("Texture file has been successfully loaded!", 10);
	}
	else
	{
		v->getStatusBar()->showMessage("Couldn't open the file!", 5);
	}
}

void MainWindow::animation_cb(Fl_Widget* _w, void* _p)
{
	MainWindow* v = static_cast<MainWindow*>(_p);
	if (!v) return;

	Fl_Menu_* mw = static_cast<Fl_Menu_*>(_w);
	Fl_Menu_Item* m = const_cast<Fl_Menu_Item*>(mw->mvalue());
	if (!m) return;

	if (m->value() == 0)
	{
		v->p_renderer->setSceneAnimationEnabled(true);
		v->getStatusBar()->showMessage("Animation enabled!", 5);
	}
	else
	{
		v->p_renderer->setSceneAnimationEnabled(false);
		v->getStatusBar()->showMessage("Animation disabled!", 5);
	}
}


void MainWindow::website_cb(Fl_Widget* _w, void* _p)
{
	fl_open_uri("http://real3d.pk/");
}
void MainWindow::download_cb(Fl_Widget* _w, void* _p)
{
	fl_open_uri("http://real3d.pk/softwares.html");
}
void MainWindow::about_cb(Fl_Widget* _w, void* _p)
{
	MainWindow* v = static_cast<MainWindow*>(_p);
	if (!v) return;

	v->getStatusBar()->showMessage("Author: Dr. Furqan Ullah", 100000);

	std::ostringstream sstream;
	sstream <<
		"<br><p>Written in FLE Version: 1.3.4</p>"
		"<br><p>Release Date: 2017/07/01 02:46AM</p>"
		"<br><p>Copyright(C) 2017</p>"
		"<p><a href=\"http://real3d.pk/\">Website</a> " << "and <a href=\"http://www.real3d.pk/forum/index.php\">Forum</a></p>"
		"<br><p><b><i>For all questions and bug reports, email to info@real3d.pk.<b><i></p>"
		"<br><p><b><i>Warning: This computer program is only for non-commercial purposes.<i></b></p>";

	if (Fle_Dialog::openHelpDialog(
		500, 320,
		"About",
		sstream.str(),
		Fle_Font(13, FL_WHITE),
		"3D MESH RENDERER BY DR. FURQAN ",
		Fle_Font(16, FL_WHITE, FL_ALIGN_LEFT, FL_BOLD)))
	{
		v->getStatusBar()->showMessage("Ready", 10);
	}
}