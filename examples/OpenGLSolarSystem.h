#pragma once
/*********************************************************************************
created:	2017/04/28   04:56PM
filename: 	OpenGLSolarSystem.h
file base:	OpenGLSolarSystem
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	This tutorial is about implementing the OpenGL material and lighting
			model by creating a 3D solar system that has a Sun, planet earth and moon.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_OpenGLWindow.h>
#include <FLE/Fle_AbstractOpenGLActor.h>
#include <FLE/Math/Fle_Vector3D.h>
#include <FLE/Math/Fle_FaceIndices3.h>

using namespace R3D;

/************************************************************************/
/* class for planet                                                     */
/************************************************************************/
class Planet : public Fle_AbstractOpenGLActor
{
public:
	Planet();

	void setRadius(float _r);
	float getRadius() const;

private:
	void draw();	// overridden function that render solid sphere.

	float m_radius;
};
/************************************************************************/
/* class for orbit                                                      */
/************************************************************************/
class Orbit : public Fle_AbstractOpenGLActor
{
public:
	Orbit();

	void setRadius(float _r);
	float getRadius() const;

private:
	void draw();	// overridden function that render wireframe circle.

	float m_radius;
};

/************************************************************************/
/* class for grid                                                       */
/************************************************************************/
class Grids : public Fle_AbstractOpenGLActor
{
private:
	void draw();	// overridden function that render grids.
};

/************************************************************************/
/* class for 3D axis                                                    */
/************************************************************************/
class Axis3D : public Fle_AbstractOpenGLActor
{
private:
	void draw();	// overridden function that render 3D axis.
};

/************************************************************************/
/* class for Solar System                                               */
/************************************************************************/
class OpenGLSolarSystem : public Fle_OpenGLWindow
{
public:
	OpenGLSolarSystem(int _w, int _h, const char* _title);

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
	// Function to setup light 1 (Sun light).
	void setupLight1();
	// Description
	// Function to setup light 2.
	void setupLight2();

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

	// Static helper function to draw different shapes.
	// Description
	// Function to draw/render a grid by specifying the number of grids and color.
	static void drawGrid(int _ngrids, float _scale = 1.f);
	// Description
	// Function to draw/render 3D axis.
	static void draw3DAxis(float _size);
	// Description
	// Function to draw/render a circle.
	static void drawTriangularCircle(float _radius, int _sides);
	// Description
	// Function to draw/render a circle.
	static void drawLineCircle(float _radius, int _sides);
	// Description
	// Function to draw/render a box composed of triangular mesh with minimum and maximum coordinates.
	static void drawTriangularBoxMesh(const Vector3D& _min, const Vector3D& _max);
	// Description
	// Function to draw/render a box by specifying width, height, and depth.
	static void drawQuadBox(float _w, float _h, float _d);

private:
	float angle;					// angle (in degrees) for scene animation
	float moon_angle;				// angle (in degrees) for moon rotation
	float earth_angle;				// angle (in degrees) for earth rotation
	float mars_angle;				// angle (in degrees) for mars rotation
	float m_moon_angle;				// angle (in degrees) for mars moon rotation

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