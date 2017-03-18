/*********************************************************************************
created:	2017/03/14   02:11AM
filename: 	opengl_events_lights_animation_main.cpp
file base:	opengl_events_lights_animation_main
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	OpenGL program to animate the scene, written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Core.h"
#include "opengl_events_lights_animation.h"

int main(int argc, char* argv[])
{
	// library initialization with default modes.
	Fle_Core::init();

	// create OpenGL window by specifying width, height and title.
	GLWindow win(1024, 500, "OpenGL Program with Animation, Events, Lights, and Material");
	win.show();

	// execute the main loop.
	return Fle_Core::exec();
}

