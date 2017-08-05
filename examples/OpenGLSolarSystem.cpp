/*********************************************************************************
created:	2017/04/28   04:56PM
filename: 	OpenGLSolarSystem.cpp
file base:	OpenGLSolarSystem
file ext:	cpp
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

#include "OpenGLSolarSystem.h"

#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/glut.H>

#include <cmath>

/************************************************************************/
/* class for planet                                                     */
/************************************************************************/
Planet::Planet()
{
	setLightingEnabled(true);
	setRenderType(Fle_AbstractOpenGLActor::RenderType::Fill);
	m_radius = 1.f;
}

void Planet::setRadius(float _r)
{
	m_radius = _r;
}

float Planet::getRadius() const
{
	return m_radius;
}

void Planet::draw()
{
	glutSolidSphere(m_radius, 72, 72);
}

/************************************************************************/
/* class for orbit                                                      */
/************************************************************************/
Orbit::Orbit()
{
	m_radius = 1.f;
	setRenderType(Fle_AbstractOpenGLActor::RenderType::Line);
}

void Orbit::setRadius(float _r)
{
	m_radius = _r;
}

float Orbit::getRadius() const
{
	return m_radius;
}

void Orbit::draw()
{
	OpenGLSolarSystem::drawLineCircle(m_radius, 72);
}
/************************************************************************/
/* class for grid                                                       */
/************************************************************************/
void Grids::draw()
{
	OpenGLSolarSystem::drawGrid(40, 150.f);
}
/************************************************************************/
/* class for 3D axis                                                    */
/************************************************************************/
void Axis3D::draw()
{
	OpenGLSolarSystem::draw3DAxis(10.f);
}


/************************************************************************/
/* class for Solar System                                               */
/************************************************************************/
OpenGLSolarSystem::OpenGLSolarSystem(int _w, int _h, const char* _title) : Fle_OpenGLWindow(_w, _h, _title)
{
	angle = 0.f;
	earth_angle = 0.f;
	moon_angle = 0.f;
	mars_angle = 0.f;
	m_moon_angle = 0.f;

	has_rotation_started = false;
	start_x = 0;
	start_y = 0;
	x_rot_angle = 25;
	y_rot_angle = 15;
	zoom = -180;

	has_panning_started = false;
	x_trans = 0;
	y_trans = 0;

	getTimer().start();
}

void OpenGLSolarSystem::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	setupLight1();

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CCW);
}

void OpenGLSolarSystem::setupCamera()
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

void OpenGLSolarSystem::setupLight0()
{
	// position of the light source. 
	// Forth component will make this light a directional or position light.
	// If it's 1 that means it's a directional light, in this case, position of the light source doesn't really matter.
	// If it's 0 that means it's a positional light, we need to specify where we want to place out light source/lamp.
	GLfloat light_position_0[] = { 0.f, 5.f, -19.f, 1.f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);

	GLfloat light_ambient_0[] = { 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_0);

	GLfloat light_diffuse_0[] = { 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_0);

	GLfloat light_specular_0[] = { 1.f, 1.f, 1.f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular_0);

	glEnable(GL_LIGHT0);	// enable light 0, meaning to turn the switch ON of bulb/lamp 0.
}
void OpenGLSolarSystem::setupLight1()
{
	// position of the light source. 
	// Forth component will make this light a directional or position light.
	// If it's 1 that means it's a directional light, in this case, position of the light source doesn't really matter.
	// If it's 0 that means it's a positional light, we need to specify where we want to place out light source/lamp.
	GLfloat light_position_1[] = { 0.f, 1.f, -19.f, 1.f };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);

	GLfloat light_ambient_1[] = { 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient_1);

	GLfloat light_diffuse_1[] = { 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse_1);

	GLfloat light_specular_1[] = { 1.f, 1.f, 1.f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular_1);

	glEnable(GL_LIGHT1);	// enable light 0, meaning to turn the switch ON of bulb/lamp 0.
}
void OpenGLSolarSystem::setupLight2()
{
	// position of the light source. 
	// Forth component will make this light a directional or position light.
	// If it's 1 that means it's a directional light, in this case, position of the light source doesn't really matter.
	// If it's 0 that means it's a positional light, we need to specify where we want to place out light source/lamp.
	GLfloat light_position_2[] = { 0.f, 0.f, -2.f, 1.f };
	glLightfv(GL_LIGHT2, GL_POSITION, light_position_2);

	GLfloat light_ambient_2[] = { 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient_2);

	GLfloat light_diffuse_2[] = { 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse_2);

	GLfloat light_specular_2[] = { 1.f, 1.f, 1.f };
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular_2);

	glEnable(GL_LIGHT2);	// enable light 0, meaning to turn the switch ON of bulb/lamp 0.
}

void OpenGLSolarSystem::paintGL()
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
	Grids grid;
	grid.setLightingEnabled(false);
	grid.setTranslate(Vector3D(0.f, -70.f, 0.f));
	grid.setTransparency(90);
	grid.render();

	setupLight0();
	setupLight2();

	glEnable(GL_LIGHT1);
	glDisable(GL_LIGHT0);

	/************************************************************************/
	/* Sun                                                                  */
	/************************************************************************/

	Planet s;
	s.setRadius(20);
	s.setAmbientColor(Color4D(0.1f, 0.1f, 0.1f, 1.f));
	s.setDiffuseColor(Color4D(1.f, 0.6f, 0.0f, 1.0f));
	s.setSpecularColor(Color4D(0.5f, 0.5f, 0.5f, 1.f));
	s.setEmissionColor(Color4D(0.6f, 0.1f, 0.1f, 1.f));
	s.setSpecularShininess(5.f);
	s.setDepthTestEnabled(true);
	s.setTranslate(Vector3D(0, -5, 0));
	s.render();

	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);

	/************************************************************************/
	/* Planet Earth                                                         */
	/************************************************************************/

	Orbit o0;
	o0.setRotAngle(90.f);
	o0.setRotAxis(Vector3D(1, 0, 0));
	o0.setRadius(50.f);
	o0.setColor(Color4D(0.9f, 0.4f, 0.f, 1.f));
	o0.render();

	// planet earth
	glPushMatrix();
	{
		glRotatef(-earth_angle, 0, 1, 0);
		Planet p;
		p.setRadius(5);
		p.setAmbientColor(Color4D(0.1f, 0.1f, 0.1f, 1.f));
		p.setDiffuseColor(Color4D(0.f, 0.6f, 0.1f, 1.f));
		p.setSpecularColor(Color4D(0.3f, 0.3f, 0.3f, 1.f));
		p.setEmissionColor(Color4D(0.0f, 0.0f, 0.0f, 1.f));
		p.setSpecularShininess(60.f);
		p.setTranslate(Vector3D(o0.getRadius(), 0.f, 0.f));
		p.render();

		// planet moon
		glPushMatrix();
		{
			glTranslatef(o0.getRadius(), 0, 0);
			glRotatef(-moon_angle, 0, 1, 0);

			Planet moon;
			moon.setRadius(2);
			moon.setAmbientColor(Color4D(0.1f, 0.1f, 0.1f, 1.f));
			moon.setDiffuseColor(Color4D(1.0f, 1.0f, 1.0f, 1.f));
			moon.setSpecularColor(Color4D(0.3f, 0.3f, 0.3f, 1.f));
			moon.setEmissionColor(Color4D(0.0f, 0.0f, 0.0f, 1.f));
			moon.setSpecularShininess(60.f);
			moon.setTranslate(Vector3D(10, 0, 0));
			moon.render();
		}
		glPopMatrix();
	}
	glPopMatrix();

	/************************************************************************/
	/* Planet XYZ                                                           */
	/************************************************************************/

	Orbit o1;
	o1.setRotAngle(90.f);
	o1.setRotAxis(Vector3D(1, 0, 0));
	o1.setRadius(80.f);
	o1.setColor(Color4D(0.9f, 0.4f, 0.f, 1.f));
	o1.setTransparency(50);
	o1.render();

	// planet XYZ
	glPushMatrix();
	{
		glRotatef(-mars_angle, 0, 1, 0);
		Planet p;
		p.setRadius(5);
		p.setAmbientColor(Color4D(0.1f, 0.1f, 0.1f, 1.f));
		p.setDiffuseColor(Color4D(0.5f, 0.1f, 0.1f, 1.f));
		p.setSpecularColor(Color4D(0.3f, 0.3f, 0.3f, 1.f));
		p.setEmissionColor(Color4D(0.0f, 0.0f, 0.0f, 1.f));
		p.setSpecularShininess(60.f);
		p.setTranslate(Vector3D(o1.getRadius(), 0.f, 0.f));
		p.render();

		// planet moon
		glPushMatrix();
		{
			glTranslatef(o1.getRadius(), 0, 0);
			glRotatef(-m_moon_angle, 0, 1, 0);

			Planet moon;
			moon.setRadius(2);
			moon.setAmbientColor(Color4D(0.1f, 0.1f, 0.1f, 1.f));
			moon.setDiffuseColor(Color4D(1.0f, 1.0f, 1.0f, 1.f));
			moon.setSpecularColor(Color4D(0.3f, 0.3f, 0.3f, 1.f));
			moon.setEmissionColor(Color4D(0.0f, 0.0f, 0.0f, 1.f));
			moon.setSpecularShininess(60.f);
			moon.setTranslate(Vector3D(10, 0, 0));
			moon.render();
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void OpenGLSolarSystem::timerEvent()
{
	angle = angle + 0.1f;
	if (angle > 360.f)
		angle = angle - 360.f;

	earth_angle = earth_angle + 0.8f;
	if (earth_angle > 360.f)
		earth_angle = earth_angle - 360.f;
	
	moon_angle = moon_angle + 2.0f;
	if (moon_angle > 360.f)
		moon_angle = moon_angle - 360.f;

	mars_angle = mars_angle + 0.2f;
	if (mars_angle > 360.f)
		mars_angle = mars_angle - 360.f;

	m_moon_angle = m_moon_angle + 0.5f;
	if (m_moon_angle > 360.f)
		m_moon_angle = m_moon_angle - 360.f;

	update();
}

void OpenGLSolarSystem::mouseLeftButtonPressEvent(int _x, int _y)
{
	has_rotation_started = true;
	start_x = _x;
	start_y = _y;
}
void OpenGLSolarSystem::mouseLeftButtonReleaseEvent()
{
	has_rotation_started = false;
}
void OpenGLSolarSystem::mouseLeftButtonDragEvent(int _x, int _y)
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

void OpenGLSolarSystem::mouseWheelForwardEvent()
{
	zoom += 5.0f;
	update();
}
void OpenGLSolarSystem::mouseWheelBackwardEvent()
{
	zoom -= 5.0f;
	update();
}

void OpenGLSolarSystem::mouseMiddleButtonPressEvent(int _x, int _y)
{
	has_panning_started = true;
	start_x = _x;
	start_y = _y;
}
void OpenGLSolarSystem::mouseMiddleButtonReleaseEvent()
{
	has_panning_started = false;
}
void OpenGLSolarSystem::mouseMiddleButtonDragEvent(int _x, int _y)
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

void OpenGLSolarSystem::drawGrid(int _ngrids, float _scale)
{
	int half_size = _ngrids / 2;
	glBegin(GL_LINES);
	for (int i = -half_size; i <= half_size; i++)
	{
		glVertex3f(float(i) * _scale, 0.f, float(-half_size)* _scale);
		glVertex3f(float(i) * _scale, 0.f, float(half_size) * _scale);

		glVertex3f(float(-half_size)* _scale, 0.f, float(i) * _scale);
		glVertex3f(float(half_size) * _scale, 0.f, float(i) * _scale);
	}
	glEnd();
}

void OpenGLSolarSystem::draw3DAxis(float _size)
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

void OpenGLSolarSystem::drawLineCircle(float _radius, int _sides)
{
	glBegin(GL_LINE_LOOP);
	float angle = 2.f * 3.1416f / _sides;
	for (int i = 0; i < _sides; i++)
	{
		float x = _radius * std::cos(i * angle);
		float y = _radius * std::sin(i * angle);
		float z = 0.f;

		glVertex3f(x, y, z);
	}
	glEnd();
}

void OpenGLSolarSystem::drawTriangularCircle(float _radius, int _sides)
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

void OpenGLSolarSystem::drawTriangularBoxMesh(const Vector3D& _min, const Vector3D& _max)
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

void OpenGLSolarSystem::drawQuadBox(float _w, float _h, float _d)
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


