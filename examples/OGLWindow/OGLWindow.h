#pragma once
#ifndef OGLWindow_h__
#define OGLWindow_h__

/*********************************************************************************
created:	2017/03/14   02:10AM
filename: 	OGLWindow.h
file base:	OGLWindow
file ext:	h
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

#include <FLE/Fle_OpenGLWindow.h>

class GLWindow : public R3D::Fle_OpenGLWindow
{
public:
	// Description:
	// Constructor to create a OpenGL window by specifying it's position, size, title, and id of icon.
	GLWindow(int _x, int _y, int _w, int _h, const char* _title = 0);
	// Constructor to create a window by specifying it's size, title.
	// This constructor sets the position at the center of the screen/monitor.
	GLWindow(int _w, int _h, const char* _title = 0);

	// Description:
	// Function that will be called only once at the start of the window.
	// It uses to initialize the OpenGL states or any other data such as textures etc.
	void initializeGL() override;

	// Description:
	// Function to turn on the first light/bulb.
	void setupCamera();
	// Description:
	// Function for all kinds of OpenGL rendering.
	void paintGL() override;

	// Description:
	// keyboard key press events.
	int keyPressEvent(int _key) override;

	// Description:
	// Function to turn on the first light/bulb.
	void setupPointLight0();
	// Description:
	// Function to turn on the second light/bulb.
	void setupPointLight1();
	// Description:
	// Function to setup material for the 3D model.
	void setupMaterial();

	// Description:
	// Function to start the timer for updating/redrawing the scene in real-time.
	void timerEvent() override;

private:
	bool m_use_light_0;
	bool m_use_light_1;
	bool m_use_material;
	float m_angle;
};

#endif // OGLWindow_h__