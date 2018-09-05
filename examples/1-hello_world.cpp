/*********************************************************************************
created:	2017/03/05   02:57AM
filename: 	hello_world.cpp
file base:	hello_world
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Hello world example application written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>
#include <FLE/Fle_MainWindow.h>

using namespace R3D;

int main()
{
	// library initialization with default modes.
	Fle_Core::init();

	// create a main window.
	Fle_MainWindow* w = new Fle_MainWindow(1024, 500, "Hello World");
	w->setMinimumSize(Fle_Size(300, 300));
	w->setMaximumSize(Fle_Size(10000, 10000));

	// load image from disk and display in the central widget.
	w->getCentralWidget()->getBox()->loadImage("D:\\aw.jpg");
	w->getCentralWidget()->getBox()->setImageDrawType(Fle_ImageDrawType::Fit);

	// show the main window.
	w->show();				

	// execute the main loop.
	return Fle_Core::exec();
}