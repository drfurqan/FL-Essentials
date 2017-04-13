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

#include "triangles_and_indexed_based_rendering.h"

#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/glut.H>


MyOpenGLWindow::MyOpenGLWindow(int _w, int _h, const char* _title) : Fle_OpenGLWindow(_w, _h, _title)
{
	angle = 0.f;
	getTimer().stop();

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

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float c[4] = { 1, 0, 0, 1 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, c);
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

	//// draw a box
	//glPushMatrix();
	//glTranslatef(-10.f, -10.f, -10.f);
	//glLineWidth(1.f);
	//drawBox(20.f, 20.f, 20.f);
	//glPopMatrix();

	//// draw a grid
	//glPushMatrix();
	//glTranslatef(0.f, -20.f, 0.f);
	//glLineWidth(1.f);
	//drawGrid(10, 10.f, 1.f, 1.f, 1.f);
	//glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// wireframe mode
	drawCircle();
}

void MyOpenGLWindow::timerEvent()
{
	angle = angle + 0.5f;
	if (angle > 360.f)
		angle = angle - 360.f;

	update();
}

void MyOpenGLWindow::mouseLeftButtonPressEvent(int _x, int _y)
{
	has_rotation_started = true;
	start_x = _x;
	start_y = _y;
}
void MyOpenGLWindow::mouseLeftButtonReleaseEvent()
{
	has_rotation_started = false;
}
void MyOpenGLWindow::mouseLeftButtonDragEvent(int _x, int _y)
{
	if (has_rotation_started)
	{
		x_rot_angle = x_rot_angle + (_y - start_y);
		y_rot_angle = y_rot_angle + (_x - start_x);
		start_x = _x;
		start_y = _y;
		update();
	}
}

void MyOpenGLWindow::mouseWheelForwardEvent()
{
	zoom += 5.0f;
	update();
}
void MyOpenGLWindow::mouseWheelBackwardEvent()
{
	zoom -= 5.0f;
	update();
}

void MyOpenGLWindow::mouseMiddleButtonPressEvent(int _x, int _y)
{
	has_panning_started = true;
	start_x = _x;
	start_y = _y;
}
void MyOpenGLWindow::mouseMiddleButtonReleaseEvent()
{
	has_panning_started = false;
}
void MyOpenGLWindow::mouseMiddleButtonDragEvent(int _x, int _y)
{
	if (has_panning_started)
	{
		x_trans = x_trans + (_x - start_x) / 5.f;
		y_trans = y_trans - (_y - start_y) / 5.f;
		start_x = _x;
		start_y = _y;
		update();
	}
}

void MyOpenGLWindow::drawCircle()
{
	int nPoint = 12;
	int Ntriangles = 100;
	float radius = 10;

	std::vector<Vector3D> points;
	std::vector<FaceIndices3> indices;
	std::vector<Vector3D> normals;
	
	Vector3D center(0, 0, 0);
	points.push_back(center);


	float angle = 2.f * 3.1416f / Ntriangles;
	for (int i = 0; i<Ntriangles; i++)
	{
		float x = radius * std::cos(i * angle);
		float y = radius * std::sin(i * angle);
		float z = 0.f;

		Vector3D p(x, y, z);

		points.push_back(p);
	}

	for (int i = 2; i < Ntriangles + 1; i++)
	{
		FaceIndices3 face;
		face.v1 = 0;
		face.v2 = i - 1;
		face.v3 = i;

		indices.push_back(face);
	}

	FaceIndices3 face;
	face.set(0, Ntriangles, 1);
	indices.push_back(face);

	for (int i = 0; i < Ntriangles; i++)
	{
		int v1 = indices[i].v1;
		int v2 = indices[i].v2;
		int v3 = indices[i].v3;

		Vector3D n = (points[v2] - points[v1]).cross(points[v3] - points[v1]);
		n.normalize();
		normals.push_back(n);
	}

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < Ntriangles; i++)
	{
		int v1 = indices[i].v1;
		int v2 = indices[i].v2;
		int v3 = indices[i].v3;
		
		//glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		//glVertex3f(points[v1].x, points[v1].y, points[v1].z);
		//glVertex3f(points[v2].x, points[v2].y, points[v2].z);
		//glVertex3f(points[v3].x, points[v3].y, points[v3].z);

		glNormal3fv((float*)&normals[i]);
		glVertex3fv((float*)&points[v1]);
		glVertex3fv((float*)&points[v2]);
		glVertex3fv((float*)&points[v3]);
	}

	glEnd();


}

void MyOpenGLWindow::drawTriangle()
{
	Vector3D Points[4];
	Points[0].set(-20, 0, 0);
	Points[1].set(0, 40, 0);
	Points[2].set(20, 0, 0);
	Points[3].set(30, 30, 0);

	FaceIndices3 faces[2];
	faces[0].set(0, 1, 2);
	faces[1].set(1, 2, 3);

	Vector3D normals[2];

	normals[0] = (Points[faces[0].v2] - Points[faces[0].v1]).cross(Points[faces[0].v3] - Points[faces[0].v1]);
	normals[0].normalize();

	normals[1] = (Points[faces[1].v3] - Points[faces[1].v2]).cross(Points[faces[1].v3] - Points[faces[1].v1]);
	normals[1].normalize();


	glBegin(GL_TRIANGLES);

	for (int i = 0; i < 2; i++)
	{
		glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		glVertex3f(Points[faces[i].v1].x, Points[faces[i].v1].y, Points[faces[i].v1].z);
		glVertex3f(Points[faces[i].v2].x, Points[faces[i].v2].y, Points[faces[i].v2].z);
		glVertex3f(Points[faces[i].v3].x, Points[faces[i].v3].y, Points[faces[i].v3].z);
	}

	glEnd();

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
