/*********************************************************************************
created:	2017/03/05   11:36PM
filename: 	main.cpp
file base:	main
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	a demo application (FLE Photo Viewer) written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Core.h"
#include "Fle_Image_Viewer.h"

using namespace R3D;

int main(int argc, char* argv[])
{
	// library initialization with default modes.
	Fle_Core::init();
	
	// parsing arguments
	std::string file;
	if (argc == 2) file = argv[1];

	Fle_Image_Viewer w(1024, 768, "Real3D Photo Viewer");
	w.loadImage(file);
	w.show(argc, argv);
	w.showMaximized();
	w.updateGeometry();

	return Fle_Core::exec();		// execute the main loop.
}

