
#include "MyOpenGLWindow.h"

#include <Fl/gl.h>
#include <Fl/glu.h>
#include <Fl/glut.h>

MyOpenGLWindow::MyOpenGLWindow(int _w, int _h, const char* _title) : Fle_OpenGLWindow(_w, _h, _title)
{
	angle = 45.f;
	getTimer().start();
}

void MyOpenGLWindow::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
}

void MyOpenGLWindow::paintGL()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

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
	// and last 3 are the up vector, meaning flipping of the camera.
	gluLookAt(
		0.0, 0.0, 100.0, 
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	///////////////////////////////////////////////////////////

	glBegin(GL_LINES);
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);
	glEnd();

	glRotatef(45, 1, 0, 0);
	glRotatef(angle, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	drawBox(10, 20, -5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 15, 0);
	drawBox(20, 5, -5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 5, 0);
	drawBox(10, 5, -5);
	glPopMatrix();
}

void MyOpenGLWindow::timerEvent()
{
	angle = angle + 0.5;
	if (angle > 360)
		angle = angle - 360;

	update();
}


void MyOpenGLWindow::drawBox(int _w, int _h, int _d)
{
	glBegin(GL_QUADS);				// start drawing using quads

	// front
	glColor3f(1, 0, 0);				// red color
	glVertex3f(0.f, _h, _d);
	glVertex3f(0.f, 0.f, _d);
	glVertex3f(_w, 0.f, _d);
	glVertex3f(_w, _h, _d);

	// back
	glColor3f(0, 1, 0);				// green color
	glVertex3f(0.f, _h, 0.f);
	glVertex3f(_w, _h, 0.f);
	glVertex3f(_w, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);

	// top
	glColor3f(0, 0, 1);				// blue color
	glVertex3f(0.f, _h, 0.f);
	glVertex3f(0.f, _h, _d);
	glVertex3f(_w, _h, _d);
	glVertex3f(_w, _h, 0.f);

	// bottom
	glColor3f(1, 1, 0);				// yellow color
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(_w, 0.f, 0.f);
	glVertex3f(_w, 0.f, _d);
	glVertex3f(0.f, 0.f, _d);

	// left
	glColor3f(0, 1, 1);				// cyan color
	glVertex3f(0.f, _h, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, _d);
	glVertex3f(0.f, _h, _d);

	// right
	glColor3f(1, 0, 1);				// violet color
	glVertex3f(_w, _h, _d);
	glVertex3f(_w, 0.f, _d);
	glVertex3f(_w, 0.f, 0.f);
	glVertex3f(_w, _h, 0.f);

	glEnd();
}