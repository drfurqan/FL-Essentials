/*********************************************************************************
created:	2017/04/05   03:11AM
filename: 	opengl_rotation_panning_zooming.cpp
file base:	opengl_rotation_panning_zooming
file ext:	cpp
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

#include "opengl_rotation_panning_zooming.h"

#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/glut.H>

MyOpenGLWindow::MyOpenGLWindow(int _w, int _h, const char* _title) : 
	Fle_OpenGLWindow(_w, _h, _title)
{
	angle = 0.f;
	getTimer().start();

	has_rotation_started = false;
	start_x = 0;
	start_y = 0;
	x_rot_angle = 15;
	y_rot_angle = 15;
	zoom = -100;

	has_panning_started = false;
	x_trans = 0;
	y_trans = 0;
}

void MyOpenGLWindow::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
}

void MyOpenGLWindow::setupCamera()
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

void MyOpenGLWindow::paintGL()
{
	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// camera setup
	setupCamera();

	// scene translation and rotation
	glTranslatef(x_trans, y_trans, zoom);
	glRotatef(x_rot_angle, 1.f, 0.f, 0.f);
	glRotatef(y_rot_angle, 0.f, 1.f, 0.f);

	// scene animation
	glRotatef(angle, 0.f, 1.f, 0.f);

	// draw 3D axis
	glLineWidth(2.f);
	draw3DAxis(60.f);

	// draw a box
	glPushMatrix();
	glTranslatef(-10.f, -10.f, -10.f);
	glLineWidth(1.f);
	drawBox(20.f, 20.f, 20.f);
	glPopMatrix();

	// draw a grid
	glPushMatrix();
	glTranslatef(0.f, -20.f, 0.f);
	glLineWidth(1.f);
	drawGrid(10, 10.f, 1.f, 1.f, 1.f);
	glPopMatrix();
}

void MyOpenGLWindow::timerEvent()
{
	angle = angle + 0.5f;
	if (angle > 360.f)
		angle = angle - 360.f;

	update();
}

int MyOpenGLWindow::mouseLeftButtonPressEvent(int _x, int _y)
{
	has_rotation_started = true;
	start_x = _x;
	start_y = _y;

	return 1;
}
int MyOpenGLWindow::mouseLeftButtonReleaseEvent()
{
	has_rotation_started = false;

	return 1;
}
int MyOpenGLWindow::mouseLeftButtonDragEvent(int _x, int _y)
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

int MyOpenGLWindow::mouseWheelForwardEvent()
{
	zoom += 5.0f;
	update();

	return 1;
}
int MyOpenGLWindow::mouseWheelBackwardEvent()
{
	zoom -= 5.0f;
	update();

	return 1;
}

int MyOpenGLWindow::mouseMiddleButtonPressEvent(int _x, int _y)
{
	has_panning_started = true;
	start_x = _x;
	start_y = _y;

	return 1;
}
int MyOpenGLWindow::mouseMiddleButtonReleaseEvent()
{
	has_panning_started = false;

	return 1;
}
int MyOpenGLWindow::mouseMiddleButtonDragEvent(int _x, int _y)
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

void MyOpenGLWindow::drawGrid(int _ngrids, float _scale, float _red, float _green, float _blue)
{
	int half_size = _ngrids / 2;
	glBegin(GL_LINES);
	glColor3f(_red, _green, _blue);
	for (int i = -half_size; i <= half_size; i++)
	{
		glVertex3f(float(i) * _scale, 0.f, float(-half_size)* _scale);
		glVertex3f(float(i) * _scale, 0.f, float(half_size) * _scale);

		glVertex3f(float(-half_size)* _scale, 0.f, float(i) * _scale);
		glVertex3f(float(half_size) * _scale, 0.f, float(i) * _scale);
	}
	glEnd();
}

void MyOpenGLWindow::draw3DAxis(float _size)
{
	glBegin(GL_LINES);

	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-_size, 0.f, 0.f);
	glVertex3f(_size, 0.f, 0.f);

	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.f, -_size, 0.f);
	glVertex3f(0.f, _size, 0.f);

	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.f, -_size);
	glVertex3f(0.f, 0.f, _size);

	glEnd();
}

void MyOpenGLWindow::drawBox(float _w, float _h, float _d)
{
	glBegin(GL_QUADS);				// start drawing using quads

	// front
	glColor3f(0.f, 0.f, 1.f);				// red color
	glVertex3f(0.f, _h, _d);
	glVertex3f(0.f, 0.f, _d);
	glVertex3f(_w, 0.f, _d);
	glVertex3f(_w, _h, _d);

	// back
	glColor3f(0.f, 0.f, 1.f);				// green color
	glVertex3f(0.f, _h, 0.f);
	glVertex3f(_w, _h, 0.f);
	glVertex3f(_w, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);

	// top
	glColor3f(0.f, 1.f, 0.f);				// blue color
	glVertex3f(0.f, _h, 0.f);
	glVertex3f(0.f, _h, _d);
	glVertex3f(_w, _h, _d);
	glVertex3f(_w, _h, 0.f);

	// bottom
	glColor3f(0.f, 1.f, 0.f);				// yellow color
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(_w, 0.f, 0.f);
	glVertex3f(_w, 0.f, _d);
	glVertex3f(0.f, 0.f, _d);

	// left
	glColor3f(1.f, 0.f, 0.f);				// cyan color
	glVertex3f(0.f, _h, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, _d);
	glVertex3f(0.f, _h, _d);

	// right
	glColor3f(1.f, 0.f, 0.f);				// violet color
	glVertex3f(_w, _h, _d);
	glVertex3f(_w, 0.f, _d);
	glVertex3f(_w, 0.f, 0.f);
	glVertex3f(_w, _h, 0.f);

	glEnd();
}
