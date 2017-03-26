/*********************************************************************************
created:	2017/03/14   01:03AM
filename: 	opengl_hello_world_main.cpp
file base:	opengl_hello_world_main
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Simplest OpenGL program written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>
#include "opengl_hello_world.h"

int main(int argc, char* argv[])
{
	// library initialization with default modes.
	Fle_Core::init();

	// create OpenGL window by specifying width, height and title.
	GLWindow win(1024, 500, "Simplest OpenGL Program");
	win.show();

	// execute the main loop.
	return Fle_Core::exec();
}

