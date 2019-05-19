/*********************************************************************************
created:	2017/04/25   01:33AM
filename: 	lighting_model_and_mesh_rendering.cpp
file base:	lighting_model_and_mesh_rendering
file ext:	cpp
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

#include "lighting_model_and_mesh_rendering.h"

#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/glut.H>

#include <cmath>

using namespace R3D;

MyOpenGLWindow::MyOpenGLWindow(int _w, int _h, const char* _title) : Fle_OpenGLWindow(_w, _h, _title)
{
	angle = 0.f;
	getTimer().start();

	has_rotation_started = false;
	start_x = 0;
	start_y = 0;
	x_rot_angle = 15;
	y_rot_angle = 15;
	zoom = -180;

	has_panning_started = false;
	x_trans = 0;
	y_trans = 0;
}

void MyOpenGLWindow::initializeGL()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	// enable light 0, meaning to turn the switch ON of bulb/lamp 0.

	// position of the light source. 
	// Forth component will make this light a directional or position light.
	// If it's 1 that means it's a directional light, in this case, position of the light source doesn't really matter.
	// If it's 0 that means it's a positional light, we need to specify where we want to place out light source/lamp.
	GLfloat light_position_0[] = { 0.f, 1.f, 100.f, 1.f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);

	GLfloat light_ambient_0[] = { 0.1f, 0.1f, 0.1f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_0);

	GLfloat light_diffuse_0[] = { 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_0);

	GLfloat light_specular_0[] = { 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular_0);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CCW);
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

	// draw a grid
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glTranslatef(0.f, -20.f, 0.f);
		glLineWidth(1.f);
		drawGrid(20, 20.f, 0.6f, 0.6f, 0.6f);
		glPopMatrix();
	}
	glPopAttrib();

	// draw 3D axis
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glLineWidth(2.f);
		draw3DAxis(160.f);
	}
	glPopAttrib();

	// draw a box
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glTranslatef(-10.f, -10.f, -10.f);
		drawQuadBox(20.f, 20.f, 20.f);
		glPopMatrix();
	}
	glPopAttrib();

	// draw a triangular box mesh
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_LIGHTING);
		GLfloat diffuse_material[] = { 0.751640f, 0.0f, 0.226480f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material);

		glPushMatrix();
		glTranslatef(30.f, 0, 0);
		drawTriangularBoxMesh(Vector3D(-10, -10, -10), Vector3D(10, 10, 10));
		glPopMatrix();
	}
	glPopAttrib();

	// draw a solid teapot
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_LIGHTING);

		GLfloat ambient_material[] = { 0.751640f, 0.606480f, 0.226480f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material);

		GLfloat diffuse_material[] = { 0.751640f, 0.606480f, 0.226480f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material);

		GLfloat speular_material[] = { 0.6f, 0.6f, 0.6f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, speular_material);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 70.0f);

		glPushMatrix();
		glTranslatef(-40.f, 0, 0);
		glutSolidTeapot(15);
		glPopMatrix();
	}
	glPopAttrib();

	// draw a circular shape
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_LIGHTING);

		GLfloat diffuse_material[] = { 0.2f, 0.6f, 0.2f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material);

		GLfloat speular_material[] = { 0.6f, 0.6f, 0.6f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, speular_material);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 30.0f);

		glPushMatrix();
		glTranslatef(0, 0, -65);
		drawCircle(50.0f, 36);
		glPopMatrix();
	}
	glPopAttrib();

	// draw a wireframe circle.
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		GLfloat diffuse_material[] = { 0, 0, 0.8f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// wireframe or fill mode
		glPushMatrix();
		glTranslatef(60, 0, 0);
		glRotatef(-90, 0, 1, 0);
		drawCircle(50.0f, 36);
		glPopMatrix();
	}
	glPopAttrib();
}

void MyOpenGLWindow::timerEvent()
{
	angle = angle + 0.1f;
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

void MyOpenGLWindow::drawTriangles()
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

void MyOpenGLWindow::drawCircle(float _radius, int _sides)
{
	std::vector<Vector3D> points;
	points.reserve(_sides);
	std::vector<FaceIndices3> indices;
	indices.reserve(_sides);
	std::vector<Vector3D> normals;
	normals.reserve(_sides);

	Vector3D center(0, 0, 0);
	points.push_back(center);


	float angle = 2.f * 3.1416f / _sides;
	for (int i = 0; i < _sides; i++)
	{
		float x = _radius * std::cos(i * angle);
		float y = _radius * std::sin(i * angle);
		float z = 0.f;

		Vector3D p(x, y, z);

		points.push_back(p);
	}

	for (int i = 2; i < _sides + 1; i++)
	{
		FaceIndices3 face;
		face.v1 = 0;
		face.v2 = i - 1;
		face.v3 = i;

		indices.push_back(face);
	}

	FaceIndices3 face;
	face.set(0, _sides, 1);
	indices.push_back(face);

	for (int i = 0; i < _sides; i++)
	{
		int v1 = indices[i].v1;
		int v2 = indices[i].v2;
		int v3 = indices[i].v3;

		Vector3D n = (points[v2] - points[v1]).cross(points[v3] - points[v1]);
		n.normalize();
		normals.push_back(n);
	}

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < _sides; i++)
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

void MyOpenGLWindow::drawTriangularBoxMesh(const Vector3D& _min, const Vector3D& _max)
{
	Vector3D P[8];
	FaceIndices3 T[12];
	P[0].set(_max.x, _max.y, _min.z);
	P[1].set(_max.x, _max.y, _max.z);
	P[2].set(_max.x, _min.y, _min.z);
	P[3].set(_max.x, _min.y, _max.z);
	P[4].set(_min.x, _min.y, _min.z);
	P[5].set(_min.x, _min.y, _max.z);
	P[6].set(_min.x, _max.y, _min.z);
	P[7].set(_min.x, _max.y, _max.z);

	// box face indices/triangles
	T[0].set(0, 1, 2);
	T[1].set(3, 2, 1);
	T[2].set(2, 3, 4);
	T[3].set(5, 4, 3);
	T[4].set(4, 5, 6);
	T[5].set(7, 6, 5);
	T[6].set(6, 7, 0);
	T[7].set(1, 0, 7);
	T[8].set(0, 2, 4);
	T[9].set(4, 6, 0);
	T[10].set(1, 5, 3);
	T[11].set(5, 1, 7);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 12; i++)
	{
		unsigned int v1 = T[i].v1;
		unsigned int v2 = T[i].v2;
		unsigned int v3 = T[i].v3;

		Vector3D n = (P[v2] - P[v1]).cross(P[v3] - P[v1]);	// compute the normal vector by cross product.
		n.normalize();										// normalize the normal vector.

		glNormal3f(n.x, n.y, n.z);							// normal vector of the triangle face.

		glVertex3f(P[v1].x, P[v1].y, P[v1].z);
		glVertex3f(P[v2].x, P[v2].y, P[v2].z);
		glVertex3f(P[v3].x, P[v3].y, P[v3].z);
	}
	glEnd();
}

void MyOpenGLWindow::drawQuadBox(float _w, float _h, float _d)
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
