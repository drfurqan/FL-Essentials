#ifndef FLE_FileDialog_h__
#define FLE_FileDialog_h__

/**********************************************************************************
created:	2014/01/20
created:	20:1:2014   13:07
filename: 	Fle_FileDialog.h
file base:	Fle_FileDialog
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class to execute the file dialog and get the opened file path.
/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>

#include "FL/Fl_Native_File_Chooser.H"

#include <string>

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_FileDialog
{
public:
	Fle_FileDialog();

	// Usage example:
	//
	//std::string filter = "All Supported Formats" "\t" "*.{jpg,jpeg,png,bmp,tif}";
	//FileDialog d;
	//int n = d.browsMultiFile(filter);
	//if (n > 0)
	//{
	//	cout << "# of Files: " << n << endl;
	//	for (int i = 0; i < n; i++)
	//		cout << d.getPath(i) << endl;
	//}

	// Description:
	// Function to browse a single file.
	// Returned value will be the total number of selected files.
	int browsSingleFile(const std::string& filter, const std::string& title = std::string("Open File"), const std::string& fname = std::string(""));
	// Description:
	// Function to browse more than one files.
	// Returned value will be the total number of selected files.
	int browsMultiFile(const std::string& filter, const std::string& title = std::string("Open Files"), const std::string& fname = std::string(""));
	// Description:
	// Function to open the file dialog for saving.
	int browsSave(const std::string& filter, const std::string& title = std::string("Save File"), const std::string& fname = std::string(""));
	// Description:
	// Function to open the file dialog for directory selection.
	int chooseDirectory(const std::string& title = std::string("Select Directory"));

	// Function to get the full path of the selected file/files/directory
	std::string getPath(int _index) { return fl_nfc ? std::string(fl_nfc->filename(_index)) : ""; }

	// Function to get the filter Id number.
	int getFilterID() { return fl_nfc ? fl_nfc->filter_value() : -1; }

private:
	typedef enum 
	{
		FILE_CHOOSER_SINGLE,
		FILE_CHOOSER_MULTI,
		FILE_CHOOSER_CREATE,
		FILE_CHOOSER_DIRECTORY
	} FILE_CHOOSER_TYPE;

	Fl_Native_File_Chooser *fl_nfc;
	int execute(FILE_CHOOSER_TYPE type, const char *filter, const char *title, const char *fname);
};

// Example to use a FLTK file chooser.
// I prefer native look so chooses Fl_Native_File_Chooser.
//void Fl_File_Chooser_cb()
//{
//	std::string formats = ("All Files (*)"
//		"\tJPEG Files (*.{jpg,jpeg})"
//		"\tBitmap Files (*.{png,gif,bmp})"
//		"\tX-Window Files (*.{xpm,xbm})");
//
//	Fl_File_Chooser::add_favorites_label = ("Add to Favorites");
//	Fl_File_Chooser::all_files_label = ("All Files (*)");
//	Fl_File_Chooser::custom_filter_label = ("Custom Filter");
//	Fl_File_Chooser::existing_file_label = ("Please choose an existing file!");
//	Fl_File_Chooser::favorites_label = ("Favorites");
//	Fl_File_Chooser::filename_label = ("Filename:");
//	Fl_File_Chooser::filesystems_label = ("File Systems");
//	Fl_File_Chooser::hidden_label = ("Show hidden files:");
//	Fl_File_Chooser::manage_favorites_label = ("Manage Favorites");
//	Fl_File_Chooser::preview_label = ("Preview");
//	Fl_File_Chooser::show_label = ("Show:");
//
//	Fl_File_Chooser fc(".", formats.c_str(), Fl_File_Chooser::SINGLE, ("Open file"));
//
//	fc.show();
//	while (fc.shown())
//		Fl::wait();
//
//	if (NULL != fc.value())
//	{
//		std::cout << fc.value() << std::endl;
//	}
//}

}

#endif // FileDialog_h__
