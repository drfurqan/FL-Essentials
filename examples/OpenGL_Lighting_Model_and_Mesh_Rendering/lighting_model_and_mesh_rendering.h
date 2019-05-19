#pragma once
/*********************************************************************************
created:	2017/04/25   01:33AM
filename: 	lighting_model_and_mesh_rendering.h
file base:	lighting_model_and_mesh_rendering
file ext:	h
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

#include <FLE/Fle_OpenGLWindow.h>
#include <FLE/Math/Fle_Vector3D.h>
#include <FLE/Math/Fle_FaceIndices3.h>

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
	// Function to draw/render a grid by specifying the number of grids and color.
	void drawGrid(int _ngrids, float _scale = 1.f, float _red = 1.f, float _green = 1.f, float _blue = 1.f);

	// Description
	// Function to draw/render 3D axis.
	void draw3DAxis(float _size);

	// Description
	// Function to draw/render test triangles.
	void drawTriangles();

	// Description
	// Function to draw/render a circle.
	void drawCircle(float _radius, int _sides);

	// Description
	// Function to draw/render a box composed of triangular mesh with minimum and maximum coordinates.
	void drawTriangularBoxMesh(const Vector3D& _min, const Vector3D& _max);

	// Description
	// Function to draw/render a box by specifying width, height, and depth.
	void drawQuadBox(float _w, float _h, float _d);

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