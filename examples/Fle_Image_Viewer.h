#pragma once
#ifndef Fle_Image_Viewer_h__
#define Fle_Image_Viewer_h__

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

#include <FLE/Fle_MainWindow.h>
#include <FLE/Fle_Input.h>
#include <FLE/Fle_Button.h>
#include <FLE/Fle_ScrollBox.h>

#include <FL/Fl_Slider.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Input_Choice.H>

#include <string>

using namespace R3D;

class Fle_Image_Viewer : public Fle_MainWindow
{
public:
	// Description:
	// Constructor to create a window by specifying it's position, size, title.
	// _icon_index is the id of the icon that you want to display on the title bar.
	Fle_Image_Viewer(int _x, int _y, int _w, int _h, const char* _title = 0, int _icon_index = 101);
	// Description:
	// Constructor to create a window by specifying it's size and title.
	// This constructor sets the position at the center of the screen/monitor.
	// _icon_index is the id of the icon that you want to display on the title bar.
	Fle_Image_Viewer(int _w, int _h, const char* _title = 0, int _icon_index = 101);
	// Description:
	// Destructor that destroys timer (if any) and other data.
	virtual ~Fle_Image_Viewer();

	// Description:
	// Function to set an image as background.
	bool loadImage(const std::string& _filename);

	// Description:
	// Function to update the window title.
	void updateTitle(const std::string& _s);

	// Description:
	// Function to update the paths of the directory files.
	// This function is being used in displaying the Next
	// and previous images using keyboard Left and Right keys.
	void updateDirectoryPaths(const std::string& _s);

	// Description:
	// Function to get a pointer to main image box.
	Fle_ScrollBox* getScrollBox() const { return p_scroll; }

protected:
	// Description:
	// Add bars in the main window.
	void addMenuBar();
	void addToolBar();
	void addStatusBar();

	// Description:
	// Menu items callbacks.
	static void open_cb(Fl_Widget* _w, void* _p);
	static void new_cb(Fl_Widget* _w, void* _p);
	static void save_cb(Fl_Widget* _w, void* _p);
	static void save_as_cb(Fl_Widget* _w, void* _p);
	static void print_cb(Fl_Widget* _w, void* _p);
	static void properties_cb(Fl_Widget* _w, void* _p);
	static void exit_cb(Fl_Widget* _w, void* _p);
	static void copy_cb(Fl_Widget* _w, void* _p);
	static void paste_cb(Fl_Widget* _w, void* _p);
	static void delete_cb(Fl_Widget* _w, void* _p);
	static void choicemenu_cb(Fl_Widget* _w, void* _p);
	static void zoomin_cb(Fl_Widget* _w, void* _p);
	static void zoomout_cb(Fl_Widget* _w, void* _p);
	static void rotate90_cb(Fl_Widget* _w, void* _p);
	static void rotate_90_cb(Fl_Widget* _w, void* _p);
	static void resize_cb(Fl_Widget* _w, void* _p);
	static void batchresize_cb(Fl_Widget* _w, void* _p);
	static void website_cb(Fl_Widget* _w, void* _p);
	static void download_cb(Fl_Widget* _w, void* _p);
	static void about_cb(Fl_Widget* _w, void* _p);
	static void slideshow_cb(Fl_Widget* _w, void* _p);
	static void next_cb(Fl_Widget* _w, void* _p);
	static void previous_cb(Fl_Widget* _w, void* _p);
	void nextPrevious(bool _next);
	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// implementing the real-time updating/computing sort of stuff.
	// Test it by overriding this function and write some output std::cout << "tick\n"; in it, you will notice,
	// tick will be printed out repeatedly.
	virtual void timerEvent() override;

	// Description:
	// A virtual function that is expected to be overridden in the derived class for
	// handling events such as FL_SHOW, FL_FOCUS, etc.
	virtual int processEvents(int _event) override;;

	// Description:
	// data members.
	Fle_ScrollBox* p_scroll;
	Fl_Input_Choice* p_drawtypemenu;
	double m_sstime;

	std::string m_title;
	std::string m_ptitle;
	std::vector<std::string> m_dir_files;
	int m_dir_nfile;
};

#endif // Fle_Image_Viewer_h__