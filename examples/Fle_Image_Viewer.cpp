/*********************************************************************************
created:	2017/01/27   02:02AM
filename: 	Fle_Image_Viewer.h
file base:	Fle_Image_Viewer
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Image Viewer application written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Image_Viewer.h"
#include "Photo_Viewer_Icons.h"

#include <FLE/Fle_Button.h>
#include <FLE/Fle_Widgets.h>
#include <FLE/Fle_Dialog.h>
#include <FLE/Fle_FileDialog.h>
#include <FLE/Fle_MessageBox.h>
#include <FLE/Fle_StringUtil.h>
#include <FLE/Fle_ImageUtil.h>
#include <FLE/Fle_WindowsUtil.h>
#include <FLE/Fle_ScrollBox.h>

#include <FL/Fl_Printer.H>
#include <FL/Fl_Copy_Surface.H>

#include <algorithm>


/************************************************************************/
/* A class that creates a background box for image display with drag
/* and drop support.
/************************************************************************/
class Fle_DND_ScrollBox : public Fle_ScrollBox
{
public:
	Fle_DND_ScrollBox(Fle_Image_Viewer* _v, int _x, int _y, int _w, int _h, const char* _title = 0) :
		Fle_ScrollBox(_x, _y, _w, _h, _title),
		p_viewer(_v)
	{
	}

protected:
	int Fle_DND_ScrollBox::handle(int _event)
	{
		switch (_event)
		{
			// events to 'accept' drag and drop.
		case FL_DND_ENTER:
		case FL_DND_DRAG:
		case FL_DND_RELEASE:
			return 1;
			break;

			// event when a user releases a file on this box.
		case FL_PASTE:
			std::string file = Fl::event_text();
			p_viewer->loadImage(file);
			return 1;
			break;
		}

		return Fle_ScrollBox::handle(_event);
	}

	Fle_Image_Viewer* p_viewer;
};

/************************************************************************/
/* A constructor that create a Image Viewer.
/************************************************************************/
Fle_Image_Viewer::Fle_Image_Viewer(int _x, int _y, int _w, int _h, const char* _title, int _icon_index) :
Fle_MainWindow(_x, _y, _w, _h, _title, _icon_index),
m_title(_title),
m_dir_nfile(0),
m_sstime(3)
{
	callback(exit_cb, this);
	setMargins(0, 0, 1, 2);
	addMenuBar();
	getMenuBar()->setRightClickMenuEnabled(false);
	addToolBar();
	addStatusBar();

	remove(0);	// setBox will delete the previous box and set a pointer to the new box.

	begin();
	p_scroll = new Fle_DND_ScrollBox(this, 0, 0, getCentralWidget()->w(), getCentralWidget()->h());
	p_scroll->getBox()->setImageDrawType(Fle_ImageDrawType::Center);
	end();
}

/************************************************************************/
/* A constructor that create a Image Viewer.
/************************************************************************/
Fle_Image_Viewer::Fle_Image_Viewer(int _w, int _h, const char* _title, int _icon_index) :
Fle_MainWindow(_w, _h, _title, _icon_index),
m_title(_title),
m_dir_nfile(0),
m_sstime(3)
{
	callback(exit_cb, this);
	setMargins(0, 0, 1, 2);
	addMenuBar();
	getMenuBar()->setRightClickMenuEnabled(false);
	addToolBar();
	addStatusBar();

	remove(0);	// setBox will delete the previous box and set a pointer to the new box.

	begin();
	p_scroll = new Fle_DND_ScrollBox(this, 0, 0, getCentralWidget()->w(), getCentralWidget()->h());
	p_scroll->getBox()->setImageDrawType(Fle_ImageDrawType::Center);
	end();
}
Fle_Image_Viewer::~Fle_Image_Viewer()
{
}

bool Fle_Image_Viewer::loadImage(const std::string& _filename)
{
	if (Fle_ImageUtil::openCVSupportedImage(_filename))
	{
		if (getScrollBox()->getBox()->loadImage(_filename))
		{
			getScrollBox()->getBox()->resetZoom();	// reset zoom, and fit to central widget size.
			updateTitle(_filename);					// update title of this window.
			updateDirectoryPaths(_filename);		// update file paths for next and previous keys.
			redraw();
													// show message at the statusbar for 3 seconds.
			getStatusBar()->showMessage("Done!", 3);
			return true;
		}
	}
	return false;
}

void Fle_Image_Viewer::updateTitle(const std::string& _s)
{
	m_ptitle = Fle_StringUtil::extractFileNameWithExt(_s) + " [" + std::to_string(getScrollBox()->getBox()->getImageWidth()) + " x " + std::to_string(getScrollBox()->getBox()->getImageHeight()) + "px" + "]" + " - " + m_title;
	label(m_ptitle.c_str());
}
void Fle_Image_Viewer::updateDirectoryPaths(const std::string& _file)
{
	// get all images in the directory.
	m_dir_files = Fle_ImageUtil::getDirectoryImageFiles(Fle_StringUtil::extractDirectory(_file));
	// now find the input file in the directory.
	auto it = std::find(m_dir_files.begin(), m_dir_files.end(), _file);
	// if it's found then assign the index of the input file to incremental number which is m_dir_nfile.
	if (it != m_dir_files.end())
		m_dir_nfile = static_cast<int>(std::distance(m_dir_files.begin(), it));
}

void Fle_Image_Viewer::addMenuBar()
{
	getMenuBar()->show();
	setMenuBarFixedHeight(25);
	{
		// add items to menubar.
		Fle_MenuBar* menu = getMenuBar();
		menu->add(" File /\tNew\t\t\t",			FL_CTRL + 'n',			new_cb,			this);
		menu->add(" File /\tOpen...\t\t\t",		FL_CTRL + 'o',			open_cb,		this, FL_MENU_DIVIDER);
		menu->add(" File /\tSave\t\t\t",		FL_CTRL + 's',			save_cb,		this);
		menu->add(" File /\tSave As...\t\t\t",				0,			save_as_cb,		this, FL_MENU_DIVIDER);
		menu->add(" File /\tPrint...\t\t\t",	FL_CTRL + 'p',			print_cb,		this);
		menu->add(" File /\tProperties...\t\t\t", FL_ALT + FL_Enter,	properties_cb,	this, FL_MENU_DIVIDER);
		menu->add(" File /\tExit\t\t\t",		FL_ALT + FL_F + 4,		exit_cb,		this);
		menu->add(" Edit /\tCopy\t\t\t",		FL_CTRL + 'c',			copy_cb,		this);
		menu->add(" Edit /\tPaste\t\t\t",		FL_CTRL + 'v',			paste_cb,		this, FL_MENU_DIVIDER);
		menu->add(" Edit /\tRotate 90\t\t\t",	FL_CTRL + ',',			rotate90_cb,	this);
		menu->add(" Edit /\tRotate -90\t\t\t",	FL_CTRL + '.',			rotate_90_cb,	this, FL_MENU_DIVIDER);
		menu->add(" Edit /\tZoom In\t\t\t",		FL_CTRL + '=',			zoomin_cb,		this);
		menu->add(" Edit /\tZoom Out\t\t\t",	FL_CTRL + '-',			zoomout_cb,		this, FL_MENU_DIVIDER);
		menu->add(" Edit /\tResize\t\t\t",					0,			resize_cb,		this);
		menu->add(" Edit /\tBatch Resize\t\t\t",			0,			batchresize_cb, this, FL_MENU_DIVIDER);
		menu->add(" Edit /\tDelete\t\t\t",		FL_Delete,				delete_cb,		this);
		menu->add(" View /   Fullscreen\t\t\t",				0,			fullscreen_cb, this, FL_MENU_TOGGLE);
		menu->add(" View /\tDraw\t\t\t/   Fit\t\t\t",		0,			choicemenu_cb, this, FL_MENU_RADIO);
		menu->add(" View /\tDraw\t\t\t/   Stretch\t\t\t",	0,			choicemenu_cb, this, FL_MENU_RADIO);
		menu->add(" View /\tDraw\t\t\t/   Center\t\t\t",	0,			choicemenu_cb, this, FL_MENU_RADIO);
		menu->add(" Edit /\tDelete\t\t\t", FL_Delete, delete_cb, this);
		menu->add(" Help /\tWebsite\t\t\t",		FL_CTRL + FL_F + 1,		website_cb,		this);
		menu->add(" Help /\tDownload\t\t\t",					0,		download_cb,	this, FL_MENU_DIVIDER);
		menu->add(" Help /\tAbout\t\t\t",						0,		about_cb,		this);
	}
}
void Fle_Image_Viewer::addToolBar()
{
	// set top toolbar margins and fixed height.
	//getTopToolBar()->show();
	getTopToolBar()->setMargins(5, 6, 0, 0);
	setTopToolBarFixedHeight(25);
	{
		// add a Left-Right horizontal layout in the top tool bar.
		Fle_HLayoutLR* tblayout = getTopToolBar()->addLayoutLR(23);
		tblayout->setMargins(0, 0, 2, 0);
		tblayout->setBackgroundColor(214, 219, 233);

		// begin to add/pack widgets at the most left side of the toolbar.
		//tblayout->beginLeft();
		//tblayout->endLeft();		// stop adding/packing widgets at the most left side of the toolbar.

		// begin to add/pack widgets at the most right side of the toolbar.
		tblayout->beginRight();
		//Fl_Choice* cm = Fle_Widgets::createChoiceMenu(80, 21, 1, Fle_Image_Viewer::choicemenu_cb, this);
		//Fl_Menu_Button* cm = Fle_Widgets::createDropDownMenu(60, 21, "Fit", 1, Fle_Image_Viewer::choicemenu_cb, this);
		Fl_Input_Choice* cm = Fle_Widgets::createInputChoiceMenu(90, 23, 2, Fle_Image_Viewer::choicemenu_cb, this);
		cm->box(FL_FLAT_BOX);
		cm->input()->color(Fle_Widgets::fromRGB(214, 219, 233));
		cm->add("   Fit   ");
		cm->add("   Stretch       ");
		cm->add("   Center     ");
		cm->value(2);	// set as current item.
		cm->tooltip("Photo display type.\nNote: zoom and pan only work with Center type.");
		// stop adding/packing widgets at the most right side of the toolbar.
		tblayout->endRight();
	}
}

void Fle_Image_Viewer::addStatusBar()
{
	// set fixed width and margins to statusbar.
	getStatusBar()->show();
	getStatusBar()->setMargins(5, 15, 0, 0);
	setStatusBarFixedHeight(45);
	//getStatusBar()->setBackgroundColor(60, 176, 205);
	//getStatusBar()->getLayout()->setBackgroundColor(60, 176, 205);
	{
		// add a Left-Right horizontal layout in the statusbar.
		Fle_HLayoutLR* layout = getStatusBar()->addLayoutLR(41);
		layout->setMargins(0, 0, 2, 0);
		layout->setBackgroundColor(0, 122, 204);
		//layout->setBackgroundColor(60, 176, 205); 0, 122, 204

		// begin to add/pack widgets at the most left side of the statusbar.
		layout->beginLeft();

		Fle_Box* p_textbox = Fle_Widgets::createBox(300, 41, "Ready", false);		// a text box at the most left corner.
		//p_textbox->color(Fle_Widgets::fromRGB(60, 176, 205));
		p_textbox->getFont()->setSize(12);
		p_textbox->getFont()->setColor(Fle_Widgets::fromRGB(255, 255, 255));

		layout->endLeft();

		getStatusBar()->setTextBox(p_textbox);		// set the text box to show messages with time interval.

		// begin to add/pack widgets at the most right side of the statusbar.
		layout->beginRight();

		Fle_Button* prev = new Fle_Button(0, 0, 40, 40, (Fl_RGB_Image*)image_previous());
		prev->color(Fle_Widgets::fromRGB(0, 122, 204));
		prev->box(FL_NO_BOX);
		prev->callback(previous_cb, this);
		prev->shortcut(FL_Right);
		prev->tooltip("Previous (Left arrow)");

		Fle_Button* slide = new Fle_Button(0, 0, 40, 40, (Fl_RGB_Image*)image_slideshow());
		slide->color(Fle_Widgets::fromRGB(0, 122, 204));
		slide->box(FL_NO_BOX);
		slide->setOn(false);
		slide->callback(slideshow_cb, this);
		slide->tooltip("Play slide show (F11)");
		slide->shortcut(FL_F + 11);
		slide->tooltip("Play slide show (F11)");

		Fle_Button* nex = new Fle_Button(0, 0, 40, 40, (Fl_RGB_Image*)image_next());
		nex->color(Fle_Widgets::fromRGB(0, 122, 204));
		nex->box(FL_NO_BOX);
		nex->callback(next_cb, this);
		nex->shortcut(FL_Left);
		nex->tooltip("Next (Right arrow)");

		Fle_Widgets::createSeparator(1, 40, Fle_Widgets::fromRGB(0, 132, 204));

		Fle_Button* lrot = new Fle_Button(0, 0, 40, 40, (Fl_RGB_Image*)image_cw());
		lrot->color(Fle_Widgets::fromRGB(0, 122, 204));
		lrot->box(FL_NO_BOX);
		lrot->callback(rotate_90_cb, this);
		lrot->shortcut(FL_CTRL + '.');
		lrot->tooltip("Rotate clockwise (Ctrl+.)");
		
		Fle_Button* rrot = new Fle_Button(0, 0, 40, 40, (Fl_RGB_Image*)image_ccw());
		rrot->color(Fle_Widgets::fromRGB(0, 122, 204));
		rrot->box(FL_NO_BOX);
		rrot->callback(rotate90_cb, this);
		rrot->shortcut(FL_CTRL + ',');
		rrot->tooltip("Rotate counterclockwise (Ctrl+,)");

		// stop adding/packing widgets at the most right side of the statusbar.
		layout->endRight();
	}
}

void Fle_Image_Viewer::open_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;

	static const std::string filter = "All Supported Formats" "\t" "*.{jpg,jpeg,jpe,jp2,png,bmp,tif,tiff,pgm,pbm,ppm,ras,sr}";

	Fle_FileDialog d;
	int n = d.browsSingleFile(filter, "Open File");
	if (n > 0)
	{
		std::string file = d.getPath(0);
		v->loadImage(file);
	}
	else
	{
		v->getStatusBar()->showMessage("Couldn't open the file!", 5);
	}
}
void Fle_Image_Viewer::new_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;

	// the trick is to set 1 pixel by 1 pixel mat as an image with the same color as background color in order
	// to clear the screen.
	// create image with black pixels.
	cv::Mat m = cv::Mat::zeros(cv::Size(1, 1), CV_8UC3);
	// set background color to pixels.
	m.at<cv::Vec3b>(cv::Point(0, 0)) = cv::Vec3b(Fle_Widgets::toBGR(v->getScrollBox()->getBox()->color()));
	// set the 1 pixel by 1 pixel mat as an background.
	v->getScrollBox()->getBox()->setImage(m);
	v->getScrollBox()->getBox()->setFilePath("");	// empty the file path if any.
	v->getScrollBox()->getBox()->resetZoom(); // reset zoom, and fit to central widget size.
	v->updateTitle("D:\\Untitled");	// update the title of this window to untitled.
	v->redraw();
	v->getStatusBar()->showMessage("New done!", 5);
	v->m_dir_files.clear();
}
void Fle_Image_Viewer::save_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	if (v->m_dir_files.empty()) return;

	if(v->getScrollBox()->getBox()->saveImage(v->m_dir_files[v->m_dir_nfile]))
		v->getStatusBar()->showMessage("Image has been saved!", 10);
}
void Fle_Image_Viewer::save_as_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	if (v->m_dir_files.empty()) return;

	static const std::string filter = "All Supported Formats" "\t" "*.{jpg,jpeg,jpe,jp2,png,bmp,tif,tiff,pgm,pbm,ppm,ras,sr}";

	Fle_FileDialog d;
	int n = d.browsSave(filter, "Save File", "file.png");
	if (n > 0)
	{
		if(v->getScrollBox()->getBox()->saveImage(d.getPath(0)))
			v->getStatusBar()->showMessage("Image has been saved!", 10);
	}
}

void Fle_Image_Viewer::print_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;

	Fl_Printer* printer = new Fl_Printer;
	if (printer->start_job(1) == 0) 
	{
		v->getStatusBar()->showMessage("Printing the central widget!", 10);

		printer->start_page();
		int width, height;
		printer->printable_rect(&width, &height);
		printer->origin(width / 2, height / 2);
		printer->print_widget(v->getCentralWidget(), -v->getScrollBox()->getBox()->w() / 2, -v->getScrollBox()->getBox()->h() / 2);
		printer->end_page();
		printer->end_job();
	}
	delete printer;
}

void Fle_Image_Viewer::properties_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;

	if (!v->m_dir_files.empty())
		Fle_WindowsUtil::shellExecute(v->m_dir_files[v->m_dir_nfile], "properties");
}

void Fle_Image_Viewer::exit_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	v->hide();
}

void Fle_Image_Viewer::copy_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;

	Fl_Copy_Surface *copy_surf = new Fl_Copy_Surface(v->getScrollBox()->getBox()->w(), v->getScrollBox()->getBox()->h());
	copy_surf->set_current();				// direct graphics requests to the clipboard
	copy_surf->draw(v->getCentralWidget()); // draw the g widget in the clipboard
	delete copy_surf;						// after this, the clipboard is loaded
	Fl_Display_Device::display_device()->set_current();  // direct graphics requests back to the display

	v->getStatusBar()->showMessage("Copy done!", 10);
}
void Fle_Image_Viewer::paste_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;

	Fl::paste(*v, 1, Fl::clipboard_image);
}
void Fle_Image_Viewer::delete_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;

	std::remove(v->getScrollBox()->getBox()->getFilePath().c_str()); // delete file

	bool ok = !std::ifstream(v->getScrollBox()->getBox()->getFilePath().c_str());
	if (!ok)
	{
		Fle_MessageBox::Error("Couldn't delete the file!", "Error");
	}
	else
	{
		v->nextPrevious(true);
	}
}

void Fle_Image_Viewer::choicemenu_cb(Fl_Widget* _w, void* _p)
{
	//Fl_Input_Choice* inpu = static_cast<Fl_Input_Choice*>(_w);
	//if (!inpu) return;
	//Fl_Menu_* mw = static_cast<Fl_Menu_*>(inpu->menubutton());

	Fl_Menu_* mw = static_cast<Fl_Menu_*>(_w);
	const Fl_Menu_Item* m = mw->mvalue();
	if (!m) return;

	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	if (v->m_dir_files.empty()) return;

	std::string l(Fle_StringUtil::trimHeadAndTailWhiteSpaces(m->label()));
	if (l == "Fit")
		v->getScrollBox()->getBox()->setImageDrawType(Fle_ImageDrawType::Fit);
	else if (l == "Stretch")
		v->getScrollBox()->getBox()->setImageDrawType(Fle_ImageDrawType::Stretch);
	else if (l == "Center")
		v->getScrollBox()->getBox()->setImageDrawType(Fle_ImageDrawType::Center);
	v->redraw();
}
void Fle_Image_Viewer::zoomin_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	if (v->m_dir_files.empty()) return;

	v->getScrollBox()->zoomIn();
	v->redraw();
}
void Fle_Image_Viewer::zoomout_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	if (v->m_dir_files.empty()) return;

	v->getScrollBox()->zoomOut();
	v->redraw();
}

void Fle_Image_Viewer::rotate90_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	if (v->m_dir_files.empty()) return;

	cv::Mat src = v->getScrollBox()->getBox()->getImage();
	v->getScrollBox()->getBox()->setImage(Fle_ImageUtil::getRotatedImage(src, 90));
	v->redraw();
	v->getStatusBar()->showMessage("Rotated counterclockwise...", 5);
}
void Fle_Image_Viewer::rotate_90_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	if (v->m_dir_files.empty()) return;
	
	cv::Mat src = v->getScrollBox()->getBox()->getImage();
	v->getScrollBox()->getBox()->setImage(Fle_ImageUtil::getRotatedImage(src, -90));
	v->redraw();
	v->getStatusBar()->showMessage("Rotated clockwise...", 5);
}
void Fle_Image_Viewer::resize_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	if (v->m_dir_files.empty()) return;

	std::vector<const char*> _labels = { "Width: ", "Height: " };
	std::vector<double> _values = { 640, 480 };
	std::vector<double> _minimums = { 1, 1 };
	std::vector<double> _maximums = { 999999, 999999 };
	std::vector<double> _steps = { 1, 1 };
	bool check = true;
	if (Fle_Dialog::getNumbers(300, 200, "Specify the New Image Size!", _labels, _values, _minimums, _maximums, _steps, "Keep Aspect Ratio", check))
	{
		cv::Mat src = v->getScrollBox()->getBox()->getImage();
		if (!src.empty())
		{
			cv::Size s(static_cast<int>(_values[0]), static_cast<int>(_values[1]));
			if (check) s = Fle_ImageUtil::getNewSizeKeepAspectRatio(src.cols, src.rows, static_cast<int>(_values[0]), static_cast<int>(_values[1]));
			cv::resize(src, src, s, 0, 0, CV_INTER_CUBIC);
			v->getScrollBox()->getBox()->setImage(src);
			v->m_ptitle = Fle_StringUtil::extractFileNameWithExt(v->m_dir_files[v->m_dir_nfile]) + " [" + std::to_string(v->getScrollBox()->getBox()->getImageWidth()) + " x " + std::to_string(v->getScrollBox()->getBox()->getImageHeight()) + "px" + "]" + " - " + v->m_title;
			v->label(v->m_ptitle.c_str());	// update title of this window.
			v->redraw();
			v->getStatusBar()->showMessage("Image has been resized...", 5);
		}
	}
}
void Fle_Image_Viewer::batchresize_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;

	Fle_FileDialog d;
	int n = d.chooseDirectory("Select Directory");
	if (n > 0)
	{
		std::vector<const char*> _labels = { "Width: ", "Height: " };
		std::vector<double> _values = { 640, 480 };
		std::vector<double> _minimums = { 1, 1 };
		std::vector<double> _maximums = { 999999, 999999 };
		std::vector<double> _steps = { 1, 1 };
		bool check = true;
		if (Fle_Dialog::getNumbers(300, 200, "Specify the New Image Size! (Batch Resize)", _labels, _values, _minimums, _maximums, _steps, "Keep Aspect Ratio", check))
		{
			std::string path = d.getPath(0);
			if(Fle_ImageUtil::batchResize(path, static_cast<int>(_values[0]), static_cast<int>(_values[1]), check))
				v->getStatusBar()->showMessage("All images have been resized...", 10);
		}
	}
}

void Fle_Image_Viewer::next_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	v->nextPrevious(true);
}
void Fle_Image_Viewer::previous_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;
	v->nextPrevious(false);
}
void Fle_Image_Viewer::fullscreen_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;

	Fl_Menu_* mw = static_cast<Fl_Menu_*>(_w);
	Fl_Menu_Item* m = const_cast<Fl_Menu_Item*>(mw->mvalue());
	if (!m) return;

	if (m->value() == 0)
	{
		v->showNormal();
		v->getStatusBar()->show();
		v->updateContents();
	}
	else
	{
		v->showFullScreen();
		v->getStatusBar()->hide();
		v->updateContents();
	}
}
void Fle_Image_Viewer::slideshow_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;

	Fle_Button* b = static_cast<Fle_Button*>(_w);
	if (!b) return;

	if (v->m_dir_files.empty())
	{
		b->setOn(false);
		return;
	}

	if (b->isOn())
	{
		double numbr = v->m_sstime;
		if (Fle_Dialog::getNumber(300, 120, "Specify the delay in slide show", "Time (sec): ", numbr, 0, 3600, 0.1))
		{
			v->m_sstime = numbr;

			v->getTimer().setTime(v->m_sstime);
			v->getTimer().stop();
			v->getTimer().start();
			v->getStatusBar()->showMessage("Playing slide show...", 3600);
		}
	}
	else
	{
		v->getTimer().stop();
		v->getStatusBar()->showMessage("Stopped slide show...", 3);
	}
}
void Fle_Image_Viewer::nextPrevious(bool _next)
{
	if (m_dir_files.empty()) return;

	if (_next)
	{
		// increment the file index and check if it's the last image then start from the first again.
		m_dir_nfile++;
		if (m_dir_nfile == m_dir_files.size())
			m_dir_nfile = 0;
	}
	else
	{
		// decrement the file index and check if it's the first image then start from the end again.
		m_dir_nfile--;
		if (m_dir_nfile < 0)
			m_dir_nfile = static_cast<int>(m_dir_files.size()) - 1;
	}

	// load the next image.
	if (getScrollBox()->getBox()->loadImage(m_dir_files[m_dir_nfile]))
	{
		getScrollBox()->getBox()->resetZoom(); // reset zoom, and fit to central widget size.
		updateTitle(m_dir_files[m_dir_nfile]);	// update the title of this window.
		redraw();
	}
}

void Fle_Image_Viewer::timerEvent()
{
	nextPrevious(true);
}

int Fle_Image_Viewer::processEvents(int _event)
{
	switch (_event)
	{
	case FL_PASTE:
		// get image data from the clipboard.
		Fl_RGB_Image* img = static_cast<Fl_RGB_Image*>(Fl::event_clipboard());
		if (img)
		{
			// set the copied image to the image box and reset the zoom.
			getScrollBox()->getBox()->setImage(Fle_ImageUtil::getMat(img, true));
			getScrollBox()->getBox()->resetZoom(); // reset zoom, and fit to central widget size.
			updateTitle("D:\\Untitled");	// update the title of this window with untitled.
			redraw();

			getStatusBar()->showMessage("Paste done!", 3);
			m_dir_files.clear();
		}
		return 1;
		break;
	};

	return Fle_MainWindow::processEvents(_event);
}

void Fle_Image_Viewer::website_cb(Fl_Widget* _w, void* _p)
{
	fl_open_uri("http://real3d.pk/");
}
void Fle_Image_Viewer::download_cb(Fl_Widget* _w, void* _p)
{
	fl_open_uri("http://real3d.pk/softwares.html");
}
void Fle_Image_Viewer::about_cb(Fl_Widget* _w, void* _p)
{
	Fle_Image_Viewer* v = static_cast<Fle_Image_Viewer*>(_p);
	if (!v) return;

	v->getStatusBar()->showMessage("Author: Dr. Furqan Ullah", 100000);

	std::ostringstream sstream;
	sstream <<
		"<br><p>Version: 1.3.3</p>"
		"<br><p>Release Date: 2017/05/03 12:42AM</p>"
		"<br><p>Copyright(C) 2017</p>"
		"<p><a href=\"http://real3d.pk/\">Website</a> " << "and <a href=\"http://www.real3d.pk/forum/index.php\">Forum</a></p>"
		"<br><p><b><i>For all questions and bug reports, email to info@real3d.pk.<b><i></p>"
		"<br><p><b><i>Warning: This computer program is only for non-commercial purposes.<i></b></p>";
		//"<br><center><h3>FLE v1.1.0</h3></center>"
		//"<center><h6>(March 06 2017)</h6></center>"
		//"<br><center><h4><a href=\"http://real3d.pk/fle.html\">http://real3d.pk/fle.html</a></h4></center>"
		//"<p></p>"
		//"<p></p>"
		//"<center><h5>REAL3D by Dr. Furqan</h5>"
		//"<br>Copyright (C) 2017"
		//"<p><a href=\"http://real3d.pk/\">Website</a> " << "and <a href=\"http://www.real3d.pk/forum/index.php\">Forum</a>"
		//"<br>Please use my forum for all questions and bug reports or send to"
		//"<br><a href=\"mailto:info@real3d.pk\">info@real3d.pk</a></p>";
	if (Fle_Dialog::openHelpDialog(
		500, 320,
		"About",
		sstream.str(),
		Fle_Font(13, FL_WHITE),
		"REAL3D PHOTO VIEWER BY DR. FURQAN ",
		Fle_Font(16, FL_WHITE, FL_ALIGN_LEFT, FL_BOLD)))
	{
		v->getStatusBar()->showMessage("Ready", 10);
	}
}