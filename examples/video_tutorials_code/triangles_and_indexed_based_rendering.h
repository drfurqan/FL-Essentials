#pragma once
/*********************************************************************************
created:	2017/04/13   06:37PM
filename: 	triangles_and_indexed_based_rendering.cpp
file base:	triangles_and_indexed_based_rendering
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	In this tutorial, I have described the importance of triangles in 3D Computer
			Graphics and why we use triangles to model 3D objects in CG. Total seven properties are
			described and some of them are computed using mathematical equations and 3D math library.
			3D math library that provides by FLE, contains classes for 2D/3D/4D vectors,
			matrix4x4, triangle/face indices, and color4.

			This tutorial explains the indexed based rendering of a mesh in OpenGL.
			A data structure for a triangular circle is created that has vertices/points,
			indices/faces, and normals. After that, the circle is rendered using the computed
			vertices, normals, and the assigned indices. Clockwise, and counter-clockwise
			triangles/faces are explained and visually implemented with OpenGL Lighting.

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

using namespace R3D;

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

	void drawTriangle();

	void drawCircle();

	// Description
	// Overridden functions for left mouse button events.
	void mouseLeftButtonPressEvent(int _x, int _y) override;
	void mouseLeftButtonReleaseEvent() override;
	void mouseLeftButtonDragEvent(int _x, int _y) override;

	// Description
	// Overridden functions for mouse wheel events.
	void mouseWheelForwardEvent() override;
	void mouseWheelBackwardEvent() override;

	// Description
	// Overridden functions for middle mouse button events.
	void mouseMiddleButtonPressEvent(int _x, int _y) override;
	void mouseMiddleButtonReleaseEvent() override;
	void mouseMiddleButtonDragEvent(int _x, int _y) override;

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