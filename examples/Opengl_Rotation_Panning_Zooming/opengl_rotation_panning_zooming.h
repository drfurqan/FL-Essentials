#pragma once
/*********************************************************************************
created:	2017/04/05   03:11AM
filename: 	opengl_rotation_panning_zooming.h
file base:	opengl_rotation_panning_zooming
file ext:	h
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

#include <FLE/Fle_OpenGLWindow.h>

class MyOpenGLWindow : public R3D::Fle_OpenGLWindow
{
public:
	MyOpenGLWindow(int _w, int _h, const char* _title);

	// Description
	// Overridden function to initialize OpenGL states
	void initializeGL() override;

	// Description
	// Function to setup the camera
	void setupCamera();

	// Description
	// Overridden function to render scene
	void paintGL() override;

	// Description
	// Overridden function for timer.
	void timerEvent() override;

	// Description
	// Function to draw/render 3D axis.
	void draw3DAxis(float _size);

	// Description
	// Function to draw/render a box by specifying width, height, and depth.
	void drawBox(float _w, float _h, float _d);

	// Description
	// Function to draw/render a grid by specifying the number of grids and color.
	void drawGrid(int _ngrids, float _scale = 1.f, float _red = 1.f, float _green = 1.f, float _blue = 1.f);

	// Description
	// Overridden functions for left mouse button events.
	int mouseLeftButtonPressEvent(int _x, int _y) override;
	int mouseLeftButtonReleaseEvent() override;
	int mouseLeftButtonDragEvent(int _x, int _y) override;

	// Description
	// Overridden functions for mouse wheel events.
	int mouseWheelForwardEvent() override;
	int mouseWheelBackwardEvent() override;

	// Description
	// Overridden functions for middle mouse button events.
	int mouseMiddleButtonPressEvent(int _x, int _y) override;
	int mouseMiddleButtonReleaseEvent() override;
	int mouseMiddleButtonDragEvent(int _x, int _y) override;

private:
	float angle;					// angle (in degrees) for scene animation
	
	// members for left mouse button rotation
	bool has_rotation_started;
	int start_x;
	int start_y;
	float x_rot_angle;
	float y_rot_angle;

	// member for zooming
	float zoom;

	// members for panning
	bool has_panning_started;
	float x_trans;
	float y_trans;
};