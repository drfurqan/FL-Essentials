#pragma once
#ifndef Fle_MessageBox_h__
#define Fle_MessageBox_h__

/********************************************************************
created:	2013/12/25
created:	25:12:2013   22:32
filename: 	Fle_MessageBox.h
file base:	Fle_MessageBox
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved
	
purpose:	Class to display message box (inspired from windows).

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FL/Fl_Double_Window.H>
#include "Fle_Export.h"

namespace R3D
{

class FL_ESSENTIALS_EXPORT Fle_MessageBox : public Fl_Double_Window
{

public:
	// Description:
	// MessageBox for Alert, warning, information.
	// title = title of the MessageBox window.
	// message = text that should be displayed.
	// ImageId = is for Message Icon.
	// ImageId=0 (No Image), ImageId=1 (Information Image), ImageId=2 (Warning Image), ImageId=3 (Error Image)
	// 4th argument 'pos' is the display position of message box. 
	// pos=true (display at the center of the desktop screen), pos=false (random position)
	// IDI_ICON = Set icon to the message box. Specify the Resource IconId.
	Fle_MessageBox(const char* _message, const char* _title, int image_id = 1, bool _center_pos = true, int _IDI_ICON = 101);

    // Description:
    // MessageBox for Alert, warning, information.
    // title = title of the MessageBox window.
    // message = text that should be displayed.
    // if _center_pos is true then message box will be displayed at the center of the desktop screen,
	// otherwise random position on the screen.
    // pos=true (display at the center of the desktop screen), pos=false (random position)
    // IDI_ICON = Set icon to the message box. Specify the Resource IconId.
	static void Information(const char* _message, const char* _title = "Information", bool _center_pos = true, int _IDI_ICON = 101);
	static void Warning(const char* _message, const char* _title = "Warning", bool _center_pos = true, int _IDI_ICON = 101);
	static void Error(const char* _message, const char* _title = "Error", bool _center_pos = true, int _IDI_ICON = 101);

private:
   // Description:
    // Exit callback of the message box (for internal use).
    static void closeEvent(Fl_Widget* _w, void* _p);
};

}

#endif // Fle_MessageBox_h__