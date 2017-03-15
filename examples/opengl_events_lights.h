#pragma once
#ifndef opengl_events_lights_h__
#define opengl_events_lights_h__

/*********************************************************************************
created:	2017/03/14   02:10AM
filename: 	opengl_events_lights.h
file base:	opengl_events_lights
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	OpenGL program with Events, Lights, and Material written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_OpenGLWindow.h"

using namespace R3D;

class GLWindow : public Fle_OpenGLWindow
{
public:
	GLWindow(int _w, int _h, const char* _title);

	// Description:
	// Function that will be called only once at the start of the window.
	// It uses to initialize the OpenGL states or any other data such as textures etc.
	void initializeGL();

	// Description:
	// Function for all kinds of OpenGL rendering.
	void paintGL();

	// Description:
	// keyboard key press events.
	int keyPressEvent(int _key);

	// Description:
	// Function to turn on the first light/bulb.
	void setupPointLight0();
	// Description:
	// Function to turn on the second light/bulb.
	void setupPointLight1();
	// Description:
	// Function to setup material for the 3D model.
	void setupMaterial();

private:
	bool m_use_light_0;
	bool m_use_light_1;
	bool m_use_material;
};

#endif // opengl_events_lights_h__
