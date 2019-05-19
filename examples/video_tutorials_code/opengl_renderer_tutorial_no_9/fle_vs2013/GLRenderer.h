#pragma once
#ifndef GLRenderer_h__
#define GLRenderer_h__

/*********************************************************************************
created:	2017/04/28   04:56PM
filename: 	GLRenderer.h
file base:	GLRenderer
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	class that creates a 3D renderer with timer and mouse events.

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

#include "Actors.h"
#include "Mesh.h"

using namespace R3D;

/************************************************************************/
/* class for Solar System                                               */
/************************************************************************/
class GLRenderer : public Fle_OpenGLWindow
{
public:
	// Description:
	// Constructor to create an OpenGL window by specifying it's position, size, title.
	GLRenderer(int _x, int _y, int _w, int _h, const char* _title);
	// Description:
	// Constructor to create an OpenGL window by specifying it's size and title.
	// This constructor sets the position at the center of the screen/monitor.
	GLRenderer(int _w, int _h, const char* _title);

	// Description
	// Overridden function to initialize OpenGL states
	void initializeGL() override;

	// Description
	// Overridden function to render scene
	void paintGL() override;

	// Description
	// Overridden function for timer.
	void timerEvent() override;

	// Description
	// Function to setup the camera
	void setupCamera();

	// Description
	// Function to setup light 0 (for planets).
	void setupLight0();

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


	void loadMesh(const std::string& _filepath);
	void loadTexture(const std::string& _filepath);

	void setSceneAnimationEnabled(bool _b) { animation = _b; }

	Mesh mesh;

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


	bool animation;

	Axis3D axis;
	Grid2D grid;
};

#endif // GLRenderer_h__