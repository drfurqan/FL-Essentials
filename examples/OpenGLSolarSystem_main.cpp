/*********************************************************************************
created:	2017/04/28   04:56PM
filename: 	OpenGLSolarSystem_main.cpp
file base:	OpenGLSolarSystem_main
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	This tutorial is about implementing the OpenGL material and lighting
			model by creating a 3D solar system that has a Sun, planet earth and moon.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>

#include "OpenGLSolarSystem.h"

using namespace R3D;

int main()
{
	// library initialization with default modes.
	Fle_Core::init();

	// create OpenGL window by specifying width, height and title.
	OpenGLSolarSystem win(800, 500, "3D Solar System in FLE/OpenGL");
	win.showMaximized();

	// execute the main loop.
	return Fle_Core::exec();
}