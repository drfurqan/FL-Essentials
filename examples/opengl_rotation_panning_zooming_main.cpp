/*********************************************************************************
created:	2017/04/05   03:11AM
filename: 	opengl_rotation_panning_zooming_main.cpp
file base:	opengl_rotation_panning_zooming_main
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	This example presents a way to create rotation, zooming, panning for
			3D OpenGL scene. Rotation is enabled with Left mouse button events,
			zooming with mouse wheel events, and panning with middle mouse button
			events.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>

#include "opengl_rotation_panning_zooming.h"

using namespace R3D;

int main()
{
	// library initialization with default modes.
	Fle_Core::init();

	// create OpenGL window by specifying width, height and title.
	MyOpenGLWindow win(900, 500, "3D Model Manipulation in OpenGL");
	win.show();

	// execute the main loop.
	return Fle_Core::exec();
}