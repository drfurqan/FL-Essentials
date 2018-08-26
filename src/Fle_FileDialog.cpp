/**********************************************************************************
created:	2014/01/20
created:	20:1:2014   13:07
filename: 	Fle_FileDialog.cpp
file base:	Fle_FileDialog
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Class to execute the file dialog and get the opened file path.
/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_FileDialog.h>

#include "FL/Fl.H"

using namespace R3D;

Fle_FileDialog::Fle_FileDialog() : fl_nfc(nullptr)
{
}

int Fle_FileDialog::execute(FILE_CHOOSER_TYPE type, const char *filter, const char *title, const char *fname)
{
	//Fl_Group::current(nullptr);

	static char thefilter[1024] = "";
	static int thefilterindex = 0;

	if(strncmp(thefilter, filter, 1024)) 
	{
		// reset the filter and the selection if the filter has changed
		strncpy(thefilter, filter, 1024);
		thefilterindex = 0;
	}

	if(!fl_nfc) 
		fl_nfc = new Fl_Native_File_Chooser(/*Fl_Native_File_Chooser::BROWSE_FILE*/);
	switch(type)
	{
	case FILE_CHOOSER_MULTI:
		fl_nfc->type(Fl_Native_File_Chooser::BROWSE_MULTI_FILE); break;
	case FILE_CHOOSER_CREATE:
		fl_nfc->type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE); break;
	case FILE_CHOOSER_DIRECTORY:
		fl_nfc->type(Fl_Native_File_Chooser::BROWSE_DIRECTORY); break;
	default:
		fl_nfc->type(Fl_Native_File_Chooser::BROWSE_FILE); break;
	}
	fl_nfc->title(title);
	fl_nfc->filter(filter);
	fl_nfc->filter_value(thefilterindex);
	if(fname) fl_nfc->preset_file(fname);
	int ret = 0;
	switch(fl_nfc->show()) 
	{
	case -1: break; // error
	case  1: break; // cancel
	default: if(fl_nfc->filename()) ret = fl_nfc->count(); break;
	}
	thefilterindex = fl_nfc->filter_value();
	// hack to clear the KEYDOWN state that remains when calling the
	// file chooser on Mac and Windows using a keyboard shortcut
	Fl::e_state = 0;
	return ret;
}

int Fle_FileDialog::browsSingleFile(const std::string& filter, const std::string& title, const std::string& fname)
{
	return execute(FILE_CHOOSER_SINGLE, filter.c_str(), title.c_str(), fname.c_str());
}
int Fle_FileDialog::browsMultiFile(const std::string& filter, const std::string& title, const std::string& fname)
{
	return execute(FILE_CHOOSER_MULTI, filter.c_str(), title.c_str(), fname.c_str());
}
int Fle_FileDialog::browsSave(const std::string& filter, const std::string& title, const std::string& fname)
{
	return execute(FILE_CHOOSER_CREATE, filter.c_str(), title.c_str(), fname.c_str());
}
int Fle_FileDialog::chooseDirectory(const std::string& title)
{
	return execute(FILE_CHOOSER_DIRECTORY, "none", title.c_str(), 0);
}
