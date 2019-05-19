/*********************************************************************************
created:	2017/04/28   04:56PM
filename: 	GLRenderer.cpp
file base:	GLRenderer
file ext:	cpp
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

#include "GLRenderer.h"

#include "PLYLoader.h"

#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/glut.H>

GLRenderer::GLRenderer(int _x, int _y, int _w, int _h, const char* _title) : 
	Fle_OpenGLWindow(_x, _y, _w, _h, _title)
{
	angle = 0.f;

	has_rotation_started = false;
	start_x = 0;
	start_y = 0;
	x_rot_angle = 25;
	y_rot_angle = 15;
	zoom = -60.f;

	has_panning_started = false;
	x_trans = 0;
	y_trans = 0;

	animation = true;

	getTimer().start();
}

GLRenderer::GLRenderer(int _w, int _h, const char* _title) : 
	Fle_OpenGLWindow(_w, _h, _title)
{
	angle = 0.f;

	has_rotation_started = false;
	start_x = 0;
	start_y = 0;
	x_rot_angle = 25;
	y_rot_angle = 15;
	zoom = -60.f;

	has_panning_started = false;
	x_trans = 0;
	y_trans = 0;

	animation = true;

	getTimer().start();
}

void GLRenderer::loadMesh(const std::string& _filepath)
{
	PLYLoader::load(
		_filepath,
		mesh.vertices,
		mesh.vert_normals,
		mesh.texture_coord,
		mesh.colors,
		mesh.indices);

	mesh.computeFaceNormals();

	mesh.material.diffuse_color.set(0.6, 0.7, 0.1, 0.3);

	//cv::Mat img = cv::imread("fc.jpeg", cv::IMREAD_UNCHANGED);
	//cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
	//cv::flip(img, img, 0);
	//mesh.texture.create(img);
}
void GLRenderer::loadTexture(const std::string& _filepath)
{
	cv::Mat img = cv::imread(_filepath, cv::IMREAD_UNCHANGED);
	cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
	cv::flip(img, img, 0);
	mesh.texture.create(img);
}

void GLRenderer::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CCW);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	setupLight0();
}

void GLRenderer::setupLight0()
{
	// position of the light source. 
	// Forth component will make this light a directional or position light.
	// If it's 1 that means it's a directional light, in this case, position of the light source doesn't really matter.
	// If it's 0 that means it's a positional light, we need to specify where we want to place out light source/lamp.
	GLfloat light_position_0[] = { 0.f, 5.f, -10000.f, 1.f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);

	GLfloat light_ambient_0[] = { 0.05f, 0.05f, 0.05f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_0);

	GLfloat light_diffuse_0[] = { 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_0);

	GLfloat light_specular_0[] = { 0.1f, 0.1f, 0.1f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular_0);

	glEnable(GL_LIGHT0);	// enable light 0, meaning to turn the switch ON of bulb/lamp 0.
}

void GLRenderer::setupCamera()
{
	///////////////////////////////////////////////////////////
	// set width and height of the view port.
	// w() and h() are the width and height of this window.
	glViewport(0, 0, w(), h());
	// setup perspective projection with angle, aspect ratio and near and far planes.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, static_cast<double>(w()) / static_cast<double>(h()), 0.1, 10000.0);

	// setup the camera eye. 
	// first 3 arguments (0.0, 0.0, 100.0) are for eye position
	// next 3 (0.0, 0.0, 0.0) are the eye center
	// and last 3 are the up vector.
	gluLookAt(
		0.0, 0.0, 0.1,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	///////////////////////////////////////////////////////////
}

void GLRenderer::paintGL()
{
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// camera setup
	setupCamera();

	// scene translation and rotation
	glTranslatef(x_trans, y_trans, zoom);
	glRotatef(x_rot_angle, 1.f, 0.f, 0.f);
	glRotatef(y_rot_angle, 0.f, 1.f, 0.f);

	// scene animation
	glRotatef(angle, 0.f, 1.f, 0.f);


	// draw grid
	grid.setLightingEnabled(false);
	grid.setTranslate(Vector3D(0.f, -30.f, 0.f));
	grid.setTransparency(90);
	grid.render();

	// draw axis
	axis.render();

	// draw mesh
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	if (!mesh.texture_coord.empty() && mesh.texture.hasTexture())
	{
		mesh.texture.bind();
		glEnable(GL_TEXTURE_2D);
	}

	// render all kinds of actors here
	mesh.material.render();
	mesh.render();

	if (!mesh.texture_coord.empty() && mesh.texture.hasTexture())
	{
		glDisable(GL_TEXTURE_2D);
		mesh.texture.unbind();
	}
	glPopAttrib();
}

void GLRenderer::timerEvent()
{
	if (animation)
	{
		angle = angle + 0.1f;
		if (angle > 360.f)
			angle = angle - 360.f;
	}

	update();
}

int GLRenderer::mouseLeftButtonPressEvent(int _x, int _y)
{
	has_rotation_started = true;
	start_x = _x;
	start_y = _y;

	return 1;
}
int GLRenderer::mouseLeftButtonReleaseEvent()
{
	has_rotation_started = false;

	return 1;
}
int GLRenderer::mouseLeftButtonDragEvent(int _x, int _y)
{
	if (has_rotation_started)
	{
		x_rot_angle = x_rot_angle + (_y - start_y);
		y_rot_angle = y_rot_angle + (_x - start_x);
		start_x = _x;
		start_y = _y;
		update();
	}

	return 1;
}

int GLRenderer::mouseWheelForwardEvent()
{
	zoom += 5.0f;
	update();

	return 1;
}
int GLRenderer::mouseWheelBackwardEvent()
{
	zoom -= 5.0f;
	update();

	return 1;
}

int GLRenderer::mouseMiddleButtonPressEvent(int _x, int _y)
{
	has_panning_started = true;
	start_x = _x;
	start_y = _y;

	return 1;
}
int GLRenderer::mouseMiddleButtonReleaseEvent()
{
	has_panning_started = false;

	return 1;
}
int GLRenderer::mouseMiddleButtonDragEvent(int _x, int _y)
{
	if (has_panning_started)
	{
		x_trans = x_trans + (_x - start_x) / 5.f;
		y_trans = y_trans - (_y - start_y) / 5.f;
		start_x = _x;
		start_y = _y;
		update();
	}

	return 1;
}