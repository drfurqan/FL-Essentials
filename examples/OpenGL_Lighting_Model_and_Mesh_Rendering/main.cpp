/*********************************************************************************
created:	2017/04/25   01:33AM
filename: 	lighting_model_and_mesh_rendering.cpp
file base:	lighting_model_and_mesh_rendering
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	This tutorial is about implementing the OpenGL lighting model and how
can we apply surface material to 3D objects. It also presents a way to push and pop
OpenGL states/attributes to restrict the applied state/attribute to only that
specific object.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>

#include "lighting_model_and_mesh_rendering.h"

#include <iostream>

using namespace R3D;

int main()
{
	// library initialization with default modes.
	Fle_Core::init();

	// create OpenGL window by specifying width, height and title.
	MyOpenGLWindow win(800, 500, "Lighting Model in OpenGL");
	win.show();

	// execute the main loop.
	return Fle_Core::exec();
}